#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu
COPYFILE_DISABLE=1
export COPYFILE_DISABLE

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora source archive fixture lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora source archive fixture lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_archive_entry() {
  entry="$1"
  if ! grep -Fqx -- "$entry" "$archive_listing"; then
    printf 'fedora source archive fixture lane: missing archive entry: %s\n' "$entry" >&2
    exit 1
  fi
}

require_no_archive_pattern() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$archive_listing"; then
    printf 'fedora source archive fixture lane: forbidden archive pattern matched: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/FEDORA_LOCAL_BINARY_RPM_BUILD_PLAN.md
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'Status: active fixture lane' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'Source0: %{name}-%{version}.tar.gz' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains '%autosetup -n %{name}-%{version}' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'latticra-0.0.0.tar.gz' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'latticra-0.0.0/' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains "use Git's tracked and unignored source view" docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'exclude .git' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'refuse symlink entries' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'normalize tar metadata' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not run `mock`' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not create source RPM artifacts' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not create binary RPM artifacts' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not install Latticra' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'Add Fedora local binary RPM build lane' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'fedora_source_archive_fixture_lane: ok' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
root="${name}-${version}"
archive="${root}.tar.gz"

if [ "$root" != 'latticra-0.0.0' ]; then
  printf 'fedora source archive fixture lane: unexpected source root: %s\n' "$root" >&2
  exit 1
fi

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
archive_path="$tmpdir/$archive"
archive_listing="$tmpdir/archive.list"

mkdir -p "$tmpdir/$root"

symlink_entry=$(
  git ls-files --cached --others --exclude-standard |
    while IFS= read -r path; do
      if [ -L "$path" ]; then
        printf './%s\n' "$path"
        break
      fi
    done
)
if [ -n "$symlink_entry" ]; then
  printf 'fedora source archive fixture lane: refusing source archive with symlink entry: %s\n' "$symlink_entry" >&2
  exit 1
fi

python3 - "$archive_path" "$root" <<'PY'
import gzip
import os
import stat
import subprocess
import sys
import tarfile

archive_path = sys.argv[1]
root = sys.argv[2]
source_root = os.getcwd()


def excluded(relative):
    parts = relative.split(os.sep)
    if ".git" in parts or ".rpmwork" in parts:
        return True
    name = parts[-1]
    return name.endswith(".rpm") or name.endswith(".tar.gz")


def add_entry(archive, disk_path, archive_name):
    st = os.lstat(disk_path)
    if stat.S_ISLNK(st.st_mode):
        raise SystemExit(f"refusing source archive with symlink entry: {archive_name}")
    if not stat.S_ISDIR(st.st_mode) and not stat.S_ISREG(st.st_mode):
        raise SystemExit(f"refusing unsupported source archive entry: {archive_name}")

    info = tarfile.TarInfo(archive_name)
    info.uid = 0
    info.gid = 0
    info.uname = "root"
    info.gname = "root"
    info.mtime = 0
    info.pax_headers = {}
    if stat.S_ISDIR(st.st_mode):
        info.type = tarfile.DIRTYPE
        info.mode = 0o755
        archive.addfile(info)
        return

    info.size = st.st_size
    info.mode = 0o755 if (st.st_mode & stat.S_IXUSR) else 0o644
    with open(disk_path, "rb") as source:
        archive.addfile(info, source)


with open(archive_path, "wb") as raw:
    with gzip.GzipFile(filename="", mode="wb", fileobj=raw, mtime=0) as gz:
        with tarfile.open(fileobj=gz, mode="w", format=tarfile.PAX_FORMAT) as archive:
            add_entry(archive, source_root, root)
            proc = subprocess.run(
                ["git", "ls-files", "-z", "--cached", "--others", "--exclude-standard"],
                cwd=source_root,
                check=True,
                stdout=subprocess.PIPE,
            )
            paths = sorted(
                item.decode("utf-8")
                for item in proc.stdout.split(b"\0")
                if item
            )
            dirs = set()
            for rel in paths:
                if excluded(rel):
                    continue
                parent = os.path.dirname(rel)
                while parent:
                    dirs.add(parent)
                    parent = os.path.dirname(parent)

            for rel in sorted(dirs):
                add_entry(archive, os.path.join(source_root, rel), f"{root}/{rel}")
            for rel in paths:
                if excluded(rel):
                    continue
                add_entry(archive, os.path.join(source_root, rel), f"{root}/{rel}")
PY
tar -tzf "$archive_path" >"$archive_listing"

require_archive_entry "$root/README.md"
require_archive_entry "$root/packaging/fedora/latticra.spec"
require_archive_entry "$root/scripts/test-state-lattice.sh"
require_archive_entry "$root/scripts/test-system-bootstrap.sh"
require_archive_entry "$root/scripts/test-kernel.sh"
require_archive_entry "$root/scripts/test-kernel-lifecycle.sh"

require_no_archive_pattern '(^|/)\.git(/|$)'
require_no_archive_pattern '(^|/)\.rpmwork(/|$)'
require_no_archive_pattern '\.rpm$'
require_no_archive_pattern 'latticra-[^/]*\.tar\.gz$'

printf 'fedora_source_archive_fixture_lane: ok\n'

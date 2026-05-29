#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

COPYFILE_DISABLE=1
export COPYFILE_DISABLE

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian/freebsd/openbsd package input handoff lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian/freebsd/openbsd package input handoff lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_archive_entry() {
  entry="$1"
  if ! grep -Fqx -- "$entry" "$archive_listing"; then
    printf 'debian/freebsd/openbsd package input handoff lane: missing archive entry: %s\n' "$entry" >&2
    exit 1
  fi
}

require_no_archive_pattern() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$archive_listing"; then
    printf 'debian/freebsd/openbsd package input handoff lane: forbidden archive pattern matched: %s\n' "$pattern" >&2
    exit 1
  fi
}

sha256_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print $1 }'
  else
    shasum -a 256 "$file" | awk '{ print $1 }'
  fi
}

stage_archive_tree() {
  workdir="$1"

  python3 - "$workdir" "$root" <<'PY'
import os
import shutil
import stat
import subprocess
import sys

workdir, root = sys.argv[1:]
source_root = os.getcwd()
dest_root = os.path.join(workdir, root)
os.makedirs(dest_root, exist_ok=True)


def excluded(relative):
    parts = relative.split("/")
    if ".rpmwork" in parts or ".debwork" in parts or ".portswork" in parts:
        return True
    if parts[0] in {"build", "target"}:
        return True
    if relative.startswith("installer/latticra-installer/target/"):
        return True
    if relative.startswith("reports/") and relative.endswith(".tmp"):
        return True
    return relative.endswith((
        ".rpm",
        ".deb",
        ".dsc",
        ".changes",
        ".buildinfo",
        ".pkg",
        ".tgz",
        ".txz",
        ".tar.gz",
    ))


proc = subprocess.run(
    ["git", "ls-files", "-z", "--cached", "--others", "--exclude-standard"],
    cwd=source_root,
    check=True,
    stdout=subprocess.PIPE,
)

for raw in sorted(item for item in proc.stdout.split(b"\0") if item):
    rel = raw.decode("utf-8")
    if excluded(rel):
        continue
    src = os.path.join(source_root, rel)
    st = os.lstat(src)
    if stat.S_ISLNK(st.st_mode):
        raise SystemExit(f"refusing source archive with symlink entry: {rel}")
    if not stat.S_ISREG(st.st_mode):
        raise SystemExit(f"refusing unsupported source archive entry: {rel}")
    dest = os.path.join(dest_root, rel)
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    shutil.copy2(src, dest)
PY

  find "$workdir/$root" -exec touch -t 197001010000 {} +
}

write_archive_fixture() {
  workdir="$1"
  output="$2"
  listfile="$3"

  (
    cd "$workdir"
    find "$root" -type d -o -type f | LC_ALL=C sort >"$listfile"
    python3 - "$workdir" "$listfile" "$output" <<'PY'
import gzip
import os
import stat
import sys
import tarfile

workdir, listfile, output = sys.argv[1:]

with open(output, "wb") as raw:
    with gzip.GzipFile(filename="", mode="wb", fileobj=raw, mtime=0) as gz:
        with tarfile.open(fileobj=gz, mode="w", format=tarfile.PAX_FORMAT) as archive:
            with open(listfile, "r", encoding="utf-8") as entries:
                for line in entries:
                    rel = line.rstrip("\n")
                    path = os.path.join(workdir, rel)
                    st = os.lstat(path)
                    if stat.S_ISLNK(st.st_mode):
                        raise SystemExit(f"refusing source archive with symlink entry: {rel}")
                    if not (stat.S_ISDIR(st.st_mode) or stat.S_ISREG(st.st_mode)):
                        raise SystemExit(f"refusing unsupported source archive entry: {rel}")

                    info = archive.gettarinfo(path, arcname=rel)
                    info.uid = 0
                    info.gid = 0
                    info.uname = "root"
                    info.gname = "root"
                    info.mtime = 0
                    info.mode &= 0o777
                    info.pax_headers = {}

                    if info.isdir():
                        archive.addfile(info)
                    else:
                        with open(path, "rb") as source:
                            archive.addfile(info, source)
PY
  )
}

require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_file docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/debian/README.md
require_file packaging/debian/debian/control
require_file packaging/debian/debian/changelog
require_file packaging/debian/debian/source/format
require_file packaging/freebsd/README.md
require_file packaging/freebsd/Makefile
require_file packaging/freebsd/pkg-descr
require_file packaging/freebsd/pkg-plist
require_file packaging/openbsd/README.md
require_file packaging/openbsd/Makefile
require_file packaging/openbsd/pkg/DESCR
require_file packaging/openbsd/pkg/PLIST
require_file README.md

require_contains 'Status: active temporary package input handoff lane' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'temporary_package_input_handoff_lane_present=1' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'temporary_debian_orig_archive_staged=1' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'temporary_freebsd_distfile_staged=1' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'temporary_openbsd_distfile_staged=1' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'temporary_archive_sha256_preserved=1' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'freebsd_distinfo_file_written=0' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'openbsd_distinfo_file_written=0' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'does not run `dpkg-buildpackage`' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'does not run FreeBSD `make package`' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'does not run OpenBSD `make package`' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'Add Debian, FreeBSD, and OpenBSD package-build evidence gate contract' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_contains 'debian_freebsd_openbsd_package_input_handoff_lane: ok' docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md

require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md' docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'debian_freebsd_openbsd_package_input_handoff_lane_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_freebsd_openbsd_package_input_handoff_lane_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_freebsd_openbsd_package_input_handoff_lane_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_freebsd_openbsd_package_input_handoff_lane_present=1' packaging/debian/README.md
require_contains 'debian_freebsd_openbsd_package_input_handoff_lane_present=1' packaging/freebsd/README.md
require_contains 'debian_freebsd_openbsd_package_input_handoff_lane_present=1' packaging/openbsd/README.md
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md' README.md

debian_version="$(sed -n 's/^latticra (\([0-9][^-)]*\).*/\1/p' packaging/debian/debian/changelog | sed -n '1p')"
freebsd_version="$(awk -F= '/^DISTVERSION=/ { gsub(/[ \t]/, "", $2); print $2; exit }' packaging/freebsd/Makefile)"
openbsd_distname="$(awk -F= '/^DISTNAME=/ { gsub(/^[ \t]+|[ \t]+$/, "", $2); print $2; exit }' packaging/openbsd/Makefile)"

if [ "$debian_version" != '0.0.0' ]; then
  printf 'debian/freebsd/openbsd package input handoff lane: unexpected Debian upstream version: %s\n' "$debian_version" >&2
  exit 1
fi

if [ "$freebsd_version" != "$debian_version" ]; then
  printf 'debian/freebsd/openbsd package input handoff lane: FreeBSD version mismatch: %s\n' "$freebsd_version" >&2
  exit 1
fi

root="latticra-$debian_version"
if [ "$openbsd_distname" != "$root" ]; then
  printf 'debian/freebsd/openbsd package input handoff lane: OpenBSD DISTNAME mismatch: %s\n' "$openbsd_distname" >&2
  exit 1
fi

debian_archive="latticra_${debian_version}.orig.tar.gz"
bsd_archive="${root}.tar.gz"

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

source_dir="$tmpdir/source"
archive_path="$tmpdir/$bsd_archive"
archive_listing="$tmpdir/archive.list"
file_list="$tmpdir/files.list"
handoff_dir="$tmpdir/handoff"

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
  printf 'debian/freebsd/openbsd package input handoff lane: refusing source archive with symlink entry: %s\n' "$symlink_entry" >&2
  exit 1
fi

stage_archive_tree "$source_dir"
write_archive_fixture "$source_dir" "$archive_path" "$file_list"
tar -tzf "$archive_path" >"$archive_listing"
archive_sha="$(sha256_file "$archive_path")"

require_archive_entry "$root/README.md"
require_archive_entry "$root/src/latticra_cli.c"
require_archive_entry "$root/packaging/debian/debian/control"
require_archive_entry "$root/packaging/freebsd/Makefile"
require_archive_entry "$root/packaging/openbsd/Makefile"
require_no_archive_pattern '(^|/)\.git(/|$)'
require_no_archive_pattern '(^|/)build(/|$)'
require_no_archive_pattern '(^|/)target(/|$)'
require_no_archive_pattern '\.deb$'
require_no_archive_pattern '\.dsc$'
require_no_archive_pattern '\.changes$'
require_no_archive_pattern '\.buildinfo$'
require_no_archive_pattern '\.rpm$'
require_no_archive_pattern '\.pkg$'
require_no_archive_pattern '\.tgz$'
require_no_archive_pattern '\.txz$'
require_no_archive_pattern 'latticra[_-][^/]*\.tar\.gz$'
require_no_archive_pattern '(^|/)reports/[^/]+\.tmp$'

mkdir -p "$handoff_dir/debian"
cp "$archive_path" "$handoff_dir/debian/$debian_archive"
tar -C "$handoff_dir/debian" -xzf "$handoff_dir/debian/$debian_archive"
mkdir -p "$handoff_dir/debian/$root/debian"
cp packaging/debian/debian/control "$handoff_dir/debian/$root/debian/control"
cp packaging/debian/debian/changelog "$handoff_dir/debian/$root/debian/changelog"
cp packaging/debian/debian/copyright "$handoff_dir/debian/$root/debian/copyright"
cp packaging/debian/debian/rules "$handoff_dir/debian/$root/debian/rules"
cp packaging/debian/debian/install "$handoff_dir/debian/$root/debian/install"

mkdir -p "$handoff_dir/freebsd/distfiles"
mkdir -p "$handoff_dir/freebsd/ports/devel/latticra"
cp "$archive_path" "$handoff_dir/freebsd/distfiles/$bsd_archive"
cp packaging/freebsd/Makefile "$handoff_dir/freebsd/ports/devel/latticra/Makefile"
cp packaging/freebsd/pkg-descr "$handoff_dir/freebsd/ports/devel/latticra/pkg-descr"
cp packaging/freebsd/pkg-plist "$handoff_dir/freebsd/ports/devel/latticra/pkg-plist"

mkdir -p "$handoff_dir/openbsd/distfiles"
mkdir -p "$handoff_dir/openbsd/ports/devel/latticra/pkg"
cp "$archive_path" "$handoff_dir/openbsd/distfiles/$bsd_archive"
cp packaging/openbsd/Makefile "$handoff_dir/openbsd/ports/devel/latticra/Makefile"
cp packaging/openbsd/pkg/DESCR "$handoff_dir/openbsd/ports/devel/latticra/pkg/DESCR"
cp packaging/openbsd/pkg/PLIST "$handoff_dir/openbsd/ports/devel/latticra/pkg/PLIST"

test -f "$handoff_dir/debian/$debian_archive"
test -f "$handoff_dir/debian/$root/debian/control"
test -f "$handoff_dir/debian/$root/debian/changelog"
test -f "$handoff_dir/debian/$root/README.md"
test -f "$handoff_dir/debian/$root/src/latticra_cli.c"
test -f "$handoff_dir/freebsd/distfiles/$bsd_archive"
test -f "$handoff_dir/freebsd/ports/devel/latticra/Makefile"
test -f "$handoff_dir/freebsd/ports/devel/latticra/pkg-descr"
test -f "$handoff_dir/freebsd/ports/devel/latticra/pkg-plist"
test -f "$handoff_dir/openbsd/distfiles/$bsd_archive"
test -f "$handoff_dir/openbsd/ports/devel/latticra/Makefile"
test -f "$handoff_dir/openbsd/ports/devel/latticra/pkg/DESCR"
test -f "$handoff_dir/openbsd/ports/devel/latticra/pkg/PLIST"

if [ "$(sha256_file "$handoff_dir/debian/$debian_archive")" != "$archive_sha" ]; then
  printf 'debian/freebsd/openbsd package input handoff lane: Debian archive checksum changed during handoff\n' >&2
  exit 1
fi

if [ "$(sha256_file "$handoff_dir/freebsd/distfiles/$bsd_archive")" != "$archive_sha" ]; then
  printf 'debian/freebsd/openbsd package input handoff lane: FreeBSD distfile checksum changed during handoff\n' >&2
  exit 1
fi

if [ "$(sha256_file "$handoff_dir/openbsd/distfiles/$bsd_archive")" != "$archive_sha" ]; then
  printf 'debian/freebsd/openbsd package input handoff lane: OpenBSD distfile checksum changed during handoff\n' >&2
  exit 1
fi

if [ -e "$handoff_dir/freebsd/ports/devel/latticra/distinfo" ]; then
  printf 'debian/freebsd/openbsd package input handoff lane: unexpected FreeBSD distinfo was written\n' >&2
  exit 1
fi

if [ -e "$handoff_dir/openbsd/ports/devel/latticra/distinfo" ]; then
  printf 'debian/freebsd/openbsd package input handoff lane: unexpected OpenBSD distinfo was written\n' >&2
  exit 1
fi

if find "$handoff_dir" \( -name '*.deb' -o -name '*.dsc' -o -name '*.changes' -o -name '*.buildinfo' -o -name '*.rpm' -o -name '*.pkg' -o -name '*.tgz' -o -name '*.txz' \) | grep -q .; then
  printf 'debian/freebsd/openbsd package input handoff lane: unexpected package artifact in handoff tree\n' >&2
  exit 1
fi

printf 'debian_freebsd_openbsd_package_input_handoff_lane: ok\n'

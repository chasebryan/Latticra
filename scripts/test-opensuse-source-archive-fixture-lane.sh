#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

COPYFILE_DISABLE=1
export COPYFILE_DISABLE

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse source archive fixture lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse source archive fixture lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_archive_entry() {
  entry="$1"
  if ! grep -Fqx -- "$entry" "$archive_listing"; then
    printf 'opensuse source archive fixture lane: missing archive entry: %s\n' "$entry" >&2
    exit 1
  fi
}

require_no_archive_pattern() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$archive_listing"; then
    printf 'opensuse source archive fixture lane: forbidden archive pattern matched: %s\n' "$pattern" >&2
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

  mkdir -p "$workdir/$root"

  tar \
    --exclude='./.git' \
    --exclude='./.rpmwork' \
    --exclude='./build' \
    --exclude='./target' \
    --exclude='./*.rpm' \
    --exclude='./*.tar.gz' \
    -cf - . | tar -C "$workdir/$root" -xf -

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

require_file docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
require_file docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
require_file docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/opensuse/README.md
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes
require_file README.md

require_contains 'Status: active fixture lane' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'Source0:        %{name}-%{version}.tar.gz' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains '%autosetup -n %{name}-%{version}' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'latticra-0.0.0.tar.gz' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'latticra-0.0.0/' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'generate the archive fixture twice' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'source_archive_repeated_sha256_match=1' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'exclude .git' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'reject symlink entries before archiving' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not run `rpmbuild`' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not run `osc build`' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not create source RPM artifacts' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not create binary RPM artifacts' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'does not install Latticra' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'Add openSUSE RPM payload inspection contract' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'opensuse_source_archive_fixture_lane: ok' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md

require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'opensuse_source_archive_fixture_lane_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_source_archive_fixture_lane_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' packaging/opensuse/README.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' README.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' README.md

require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/opensuse/latticra.spec
require_contains '%autosetup -n %{name}-%{version}' packaging/opensuse/latticra.spec

name="$(awk '/^Name:/ { print $2; exit }' packaging/opensuse/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/opensuse/latticra.spec)"
root="${name}-${version}"
archive="${root}.tar.gz"

if [ "$root" != 'latticra-0.0.0' ]; then
  printf 'opensuse source archive fixture lane: unexpected source root: %s\n' "$root" >&2
  exit 1
fi

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

source_dir="$tmpdir/source"
first_archive="$tmpdir/first-$archive"
second_archive="$tmpdir/second-$archive"
archive_listing="$tmpdir/archive.list"
second_archive_listing="$tmpdir/archive-second.list"
first_file_list="$tmpdir/first-files.list"
second_file_list="$tmpdir/second-files.list"

symlink_entry=$(find . -path './.git' -prune -o -type l -print | sed -n '1p')
if [ -n "$symlink_entry" ]; then
  printf 'opensuse source archive fixture lane: refusing source archive with symlink entry: %s\n' "$symlink_entry" >&2
  exit 1
fi

stage_archive_tree "$source_dir"
write_archive_fixture "$source_dir" "$first_archive" "$first_file_list"
write_archive_fixture "$source_dir" "$second_archive" "$second_file_list"

tar -tzf "$first_archive" >"$archive_listing"
tar -tzf "$second_archive" >"$second_archive_listing"

if ! cmp -s "$archive_listing" "$second_archive_listing"; then
  printf 'opensuse source archive fixture lane: repeated archive listings differ\n' >&2
  exit 1
fi

first_sha="$(sha256_file "$first_archive")"
second_sha="$(sha256_file "$second_archive")"

if [ "$first_sha" != "$second_sha" ]; then
  printf 'opensuse source archive fixture lane: repeated archive SHA-256 mismatch\n' >&2
  exit 1
fi

require_archive_entry "$root/README.md"
require_archive_entry "$root/packaging/opensuse/latticra.spec"
require_archive_entry "$root/packaging/opensuse/latticra.changes"
require_archive_entry "$root/scripts/test-state-lattice.sh"
require_archive_entry "$root/scripts/test-system-bootstrap.sh"
require_archive_entry "$root/scripts/test-kernel.sh"
require_archive_entry "$root/scripts/test-kernel-lifecycle.sh"
require_archive_entry "$root/scripts/test-latticra-no-effect-cli-status-surface.sh"
require_archive_entry "$root/src/latticra_cli.c"

require_no_archive_pattern '(^|/)\.git(/|$)'
require_no_archive_pattern '(^|/)\.rpmwork(/|$)'
require_no_archive_pattern '(^|/)build(/|$)'
require_no_archive_pattern '(^|/)target(/|$)'
require_no_archive_pattern '\.rpm$'
require_no_archive_pattern 'latticra-[^/]*\.tar\.gz$'

printf 'opensuse_source_archive_fixture_lane: ok\n'

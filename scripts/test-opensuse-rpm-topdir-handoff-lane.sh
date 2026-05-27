#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

COPYFILE_DISABLE=1
export COPYFILE_DISABLE

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse rpm topdir handoff lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse rpm topdir handoff lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_archive_entry() {
  entry="$1"
  if ! grep -Fqx -- "$entry" "$archive_listing"; then
    printf 'opensuse rpm topdir handoff lane: missing archive entry: %s\n' "$entry" >&2
    exit 1
  fi
}

require_no_archive_pattern() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$archive_listing"; then
    printf 'opensuse rpm topdir handoff lane: forbidden archive pattern matched: %s\n' "$pattern" >&2
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
    if ".rpmwork" in parts:
        return True
    if parts[0] in {"build", "target"}:
        return True
    return relative.endswith((".rpm", ".tar.gz"))


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

require_file docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
require_file docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
require_file docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
require_file docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
require_file docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_file packaging/opensuse/README.md
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes
require_file README.md

require_contains 'Status: active temporary RPM topdir handoff lane' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'rpmtop/SOURCES/latticra-0.0.0.tar.gz' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'rpmtop/SPECS/latticra.spec' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'rpmtop/SPECS/latticra.changes' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'temporary_rpm_sources_archive_staged=1' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'temporary_rpm_source_sha256_preserved=1' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'temporary_rpm_source_listing_preserved=1' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'temporary_rpm_source0_name_matched=1' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'temporary_rpm_autosetup_root_matched=1' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'source_archive_accepted_for_build=0' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'does not run `rpmbuild`' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'does not run `osc build`' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'does not create source RPM artifacts' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'does not create binary RPM artifacts' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'scripts/test-opensuse-rpm-install-remove-transcript-contract.sh' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'Add openSUSE RPM build-evidence intake denial disposition closeout archive gate contract' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains 'opensuse_rpm_topdir_handoff_lane: ok' docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md

require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'temporary_rpm_topdir_handoff_lane_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' packaging/opensuse/README.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' README.md
require_contains 'docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' README.md

require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/opensuse/latticra.spec
require_contains '%autosetup -n %{name}-%{version}' packaging/opensuse/latticra.spec

name="$(awk '/^Name:/ { print $2; exit }' packaging/opensuse/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/opensuse/latticra.spec)"
source0="$(awk '/^Source0:/ { print $2; exit }' packaging/opensuse/latticra.spec)"
root="${name}-${version}"
archive="${root}.tar.gz"

if [ "$source0" != '%{name}-%{version}.tar.gz' ]; then
  printf 'opensuse rpm topdir handoff lane: unexpected Source0: %s\n' "$source0" >&2
  exit 1
fi

if [ "$root" != 'latticra-0.0.0' ]; then
  printf 'opensuse rpm topdir handoff lane: unexpected source root: %s\n' "$root" >&2
  exit 1
fi

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

source_dir="$tmpdir/source"
archive_path="$tmpdir/$archive"
archive_listing="$tmpdir/archive.list"
staged_archive_listing="$tmpdir/staged-archive.list"
file_list="$tmpdir/files.list"
rpmtop="$tmpdir/rpmtop"

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
  printf 'opensuse rpm topdir handoff lane: refusing source archive with symlink entry: %s\n' "$symlink_entry" >&2
  exit 1
fi

stage_archive_tree "$source_dir"
write_archive_fixture "$source_dir" "$archive_path" "$file_list"
tar -tzf "$archive_path" >"$archive_listing"
archive_sha="$(sha256_file "$archive_path")"

require_archive_entry "$root/README.md"
require_archive_entry "$root/packaging/opensuse/latticra.spec"
require_archive_entry "$root/packaging/opensuse/latticra.changes"
require_archive_entry "$root/src/latticra_cli.c"
require_no_archive_pattern '(^|/)\.git(/|$)'
require_no_archive_pattern '(^|/)\.rpmwork(/|$)'
require_no_archive_pattern '(^|/)build(/|$)'
require_no_archive_pattern '(^|/)target(/|$)'
require_no_archive_pattern '\.rpm$'
require_no_archive_pattern 'latticra-[^/]*\.tar\.gz$'

mkdir -p "$rpmtop/BUILD" "$rpmtop/BUILDROOT" "$rpmtop/RPMS" "$rpmtop/SOURCES" "$rpmtop/SPECS" "$rpmtop/SRPMS"
cp "$archive_path" "$rpmtop/SOURCES/$archive"
cp packaging/opensuse/latticra.spec "$rpmtop/SPECS/latticra.spec"
cp packaging/opensuse/latticra.changes "$rpmtop/SPECS/latticra.changes"

test -d "$rpmtop/BUILD"
test -d "$rpmtop/BUILDROOT"
test -d "$rpmtop/RPMS"
test -d "$rpmtop/SOURCES"
test -d "$rpmtop/SPECS"
test -d "$rpmtop/SRPMS"
test -f "$rpmtop/SOURCES/$archive"
test -f "$rpmtop/SPECS/latticra.spec"
test -f "$rpmtop/SPECS/latticra.changes"

tar -tzf "$rpmtop/SOURCES/$archive" >"$staged_archive_listing"
if ! cmp -s "$archive_listing" "$staged_archive_listing"; then
  printf 'opensuse rpm topdir handoff lane: staged archive listing changed\n' >&2
  exit 1
fi

if [ "$(sha256_file "$rpmtop/SOURCES/$archive")" != "$archive_sha" ]; then
  printf 'opensuse rpm topdir handoff lane: staged archive checksum changed\n' >&2
  exit 1
fi

if ! cmp -s packaging/opensuse/latticra.spec "$rpmtop/SPECS/latticra.spec"; then
  printf 'opensuse rpm topdir handoff lane: staged spec changed\n' >&2
  exit 1
fi

if ! cmp -s packaging/opensuse/latticra.changes "$rpmtop/SPECS/latticra.changes"; then
  printf 'opensuse rpm topdir handoff lane: staged changes file changed\n' >&2
  exit 1
fi

if find "$rpmtop/BUILD" "$rpmtop/BUILDROOT" "$rpmtop/RPMS" "$rpmtop/SRPMS" -mindepth 1 -print | grep -q .; then
  printf 'opensuse rpm topdir handoff lane: unexpected build output in RPM topdir\n' >&2
  exit 1
fi

if find "$rpmtop" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
  printf 'opensuse rpm topdir handoff lane: unexpected RPM artifact in handoff tree\n' >&2
  exit 1
fi

printf 'opensuse_rpm_topdir_handoff_lane: ok\n'

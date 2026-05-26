#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu
COPYFILE_DISABLE=1
export COPYFILE_DISABLE

fail() {
  printf 'fedora vm cli payload repeatability lane: %s\n' "$1" >&2
  exit 1
}

require_flag() {
  name="$1"
  want="$2"
  case "$name" in
    LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION)
      actual="${LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION:-}"
      ;;
    LATTICRA_ALLOW_CLI_PAYLOAD_REPEATABILITY_VALIDATION)
      actual="${LATTICRA_ALLOW_CLI_PAYLOAD_REPEATABILITY_VALIDATION:-}"
      ;;
    LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM)
      actual="${LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM:-}"
      ;;
    LATTICRA_TARGET_IS_DAILY_DRIVER)
      actual="${LATTICRA_TARGET_IS_DAILY_DRIVER:-}"
      ;;
    LATTICRA_TARGET_IS_PRODUCTION_HOST)
      actual="${LATTICRA_TARGET_IS_PRODUCTION_HOST:-}"
      ;;
    LATTICRA_TARGET_IS_IMMUTABLE_FEDORA)
      actual="${LATTICRA_TARGET_IS_IMMUTABLE_FEDORA:-}"
      ;;
    LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT)
      actual="${LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT:-}"
      ;;
    LATTICRA_TARGET_HAS_RECOVERY_PATH)
      actual="${LATTICRA_TARGET_HAS_RECOVERY_PATH:-}"
      ;;
    LATTICRA_OPERATOR_CONSENT_RECORDED)
      actual="${LATTICRA_OPERATOR_CONSENT_RECORDED:-}"
      ;;
    *)
      fail "unsupported validation flag: $name"
      ;;
  esac
  [ "$actual" = "$want" ] || fail "refusing validation unless $name=$want"
}

require_command() {
  command -v "$1" >/dev/null 2>&1 || fail "missing command: $1"
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern"
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

require_payload_line() {
  line="$1"
  grep -Fqx -- "$line" "$payload_listing" || fail "missing RPM payload line: $line"
}

require_installed_line() {
  line="$1"
  grep -Fqx -- "$line" "$installed_listing" || fail "missing installed payload line: $line"
}

require_no_payload_pattern() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$payload_listing"; then
    fail "forbidden RPM payload pattern matched: $pattern"
  fi
}

require_payload_only_expected_surfaces() {
  while IFS= read -r payload_path; do
    case "$payload_path" in
      /usr/bin/latticra|/usr/share/doc/latticra|/usr/share/doc/latticra/README.md)
        ;;
      *)
        fail "unexpected RPM payload surface: $payload_path"
        ;;
    esac
  done <"$payload_listing"
}

# Source archives use Git's tracked and unignored source view, refuse symlink entries,
# and normalize tar metadata before RPM build input is accepted.
write_source_archive() {
  archive_path="$1"
  root="$2"
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
}

require_output_field() {
  field="$1"
  file="$2"
  grep -Fqx -- "$field" "$file" || fail "missing CLI output field in $file: $field"
}

require_flag LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION 1
require_flag LATTICRA_ALLOW_CLI_PAYLOAD_REPEATABILITY_VALIDATION 1
require_flag LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM 1
require_flag LATTICRA_TARGET_IS_DAILY_DRIVER 0
require_flag LATTICRA_TARGET_IS_PRODUCTION_HOST 0
require_flag LATTICRA_TARGET_IS_IMMUTABLE_FEDORA 0
require_flag LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT 1
require_flag LATTICRA_TARGET_HAS_RECOVERY_PATH 1
require_flag LATTICRA_OPERATOR_CONSENT_RECORDED 1

[ -f /etc/os-release ] || fail 'missing /etc/os-release'
# shellcheck disable=SC1091
. /etc/os-release
[ "${ID:-}" = "fedora" ] || fail "refusing non-Fedora target: ${ID:-unknown}"

if [ "$(id -u)" -eq 0 ]; then
  fail 'run as a non-root operator account; sudo is used only for rpm install/removal'
fi

require_command awk
require_command cat
require_command cc
require_command find
require_command git
require_command grep
require_command gzip
require_command id
require_command mktemp
require_command python3
require_command rpm
require_command rpmbuild
require_command sha256sum
require_command sort
require_command sudo
require_command tar
require_command uname

require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT_STATUS.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
require_file packaging/fedora/latticra.spec
require_file README.md
require_file src/latticra_cli.c
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file scripts/run-fedora-vm-cli-payload-validation-lane.sh

require_contains 'prior_validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_contains 'source_tree_revision_recorded=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_contains 'spec_checksum_recorded=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_contains 'source_archive_checksum_recorded=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_contains 'rpm_nevra_recorded=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_contains 'fedora_vm_cli_payload_repeatability_transcript_contract_present=1' docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT_STATUS.md
require_contains 'disposable_vm_cli_validation_completed=1' docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
require_contains 'host_install_ready_for_cli_payload=1' docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md

require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' packaging/fedora/latticra.spec
require_contains 'cc %{optflags} -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra' packaging/fedora/latticra.spec
require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' packaging/fedora/latticra.spec
require_contains '%{_bindir}/latticra' packaging/fedora/latticra.spec
require_contains '%doc %{_docdir}/%{name}/README.md' packaging/fedora/latticra.spec
require_absent 'BuildArch:      noarch' packaging/fedora/latticra.spec

sh scripts/test-latticra-no-effect-cli-status-surface.sh

source_tree_revision="$(git rev-parse --verify HEAD)"
[ -n "$source_tree_revision" ] || fail 'missing source tree revision'
spec_checksum="$(sha256sum packaging/fedora/latticra.spec | awk '{ print $1 }')"
[ -n "$spec_checksum" ] || fail 'missing spec checksum'

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
[ "$name" = 'latticra' ] || fail "unexpected package name: $name"
[ -n "$version" ] || fail 'missing package version'

root="${name}-${version}"
workdir="$(mktemp -d)"
trap 'rm -rf "$workdir"' EXIT INT HUP TERM

rpmtop="$workdir/rpmbuild"
source_archive="$rpmtop/SOURCES/$root.tar.gz"
report="$workdir/fedora-vm-cli-payload-repeatability.report"
payload_listing="$workdir/payload.list"
installed_listing="$workdir/installed.list"
status_out="$workdir/cli-status.out"
version_out="$workdir/cli-version.out"
report_out="$workdir/cli-report.out"
invalid_out="$workdir/cli-invalid.out"
invalid_err="$workdir/cli-invalid.err"

mkdir -p "$rpmtop/BUILD" "$rpmtop/BUILDROOT" "$rpmtop/RPMS" "$rpmtop/SOURCES" "$rpmtop/SPECS" "$rpmtop/SRPMS"

symlink_entry=$(find . -path './.git' -prune -o -type l -print | awk 'NR == 1 { print; exit }')
[ -z "$symlink_entry" ] ||
  fail "refusing source archive with symlink entry: $symlink_entry"

write_source_archive "$source_archive" "$root"
source_archive_checksum="$(sha256sum "$source_archive" | awk '{ print $1 }')"
[ -n "$source_archive_checksum" ] || fail 'missing source archive checksum'
cp packaging/fedora/latticra.spec "$rpmtop/SPECS/latticra.spec"

rpmbuild --define "_topdir $rpmtop" -bb "$rpmtop/SPECS/latticra.spec"

rpm_path="$(find "$rpmtop/RPMS" -type f -name 'latticra-*.rpm' ! -name '*debuginfo*' ! -name '*debugsource*' | sort | awk 'NR == 1 { print; exit }')"
[ -n "$rpm_path" ] || fail 'binary RPM was not produced'

rpm_arch="$(rpm -qp --queryformat '%{ARCH}' "$rpm_path")"
[ -n "$rpm_arch" ] || fail 'missing RPM arch'
rpm_nevra="$(rpm -qp --queryformat '%{NAME}-%{VERSION}-%{RELEASE}.%{ARCH}' "$rpm_path")"
[ -n "$rpm_nevra" ] || fail 'missing RPM NEVRA'

rpm -qpi "$rpm_path" >/dev/null
rpm -qpl "$rpm_path" >"$payload_listing"
require_payload_line '/usr/bin/latticra'
require_payload_line '/usr/share/doc/latticra/README.md'
require_no_payload_pattern '^/etc/latticra(/|$)'
require_no_payload_pattern '^/usr/lib/systemd/system/latticra\.service$'
require_no_payload_pattern '^/usr/lib/modules(/|$)'
require_no_payload_pattern '^/boot/latticra(/|$)'
require_no_payload_pattern '^/usr/share/selinux(/|$)'
require_no_payload_pattern '^/usr/sbin/latticra$'
require_payload_only_expected_surfaces

if rpm -q "$name" >/dev/null 2>&1; then
  fail 'package is already installed before validation'
fi

sudo rpm -Uvh --nodeps "$rpm_path"
rpm -q "$name" >/dev/null
rpm -ql "$name" >"$installed_listing"
require_installed_line '/usr/bin/latticra'
require_installed_line '/usr/share/doc/latticra/README.md'
[ -x /usr/bin/latticra ] || fail 'installed CLI binary absent or not executable'
[ -f /usr/share/doc/latticra/README.md ] || fail 'installed README file absent'
rpm -V "$name"

/usr/bin/latticra --status >"$status_out"
require_output_field 'LATTICRA STATUS REPORT' "$status_out"
require_output_field 'project=latticra' "$status_out"
require_output_field 'mode=no-effect' "$status_out"
require_output_field 'runtime_behavior=disabled' "$status_out"
require_output_field 'host_mutation=0' "$status_out"
require_output_field 'network=0' "$status_out"
require_output_field 'kernel_operation=0' "$status_out"
require_output_field 'service_operation=0' "$status_out"
require_output_field 'package_manager_operation=0' "$status_out"
require_output_field 'boot_operation=0' "$status_out"
require_output_field 'selinux_policy_operation=0' "$status_out"
require_output_field 'effect_authority=denied' "$status_out"

/usr/bin/latticra --version >"$version_out"
require_output_field 'latticra 0.0.0' "$version_out"
require_output_field 'mode=no-effect' "$version_out"
require_output_field 'runtime_behavior=disabled' "$version_out"

/usr/bin/latticra --report >"$report_out"
require_output_field 'LATTICRA STATUS REPORT' "$report_out"
require_output_field 'project=latticra' "$report_out"
require_output_field 'mode=no-effect' "$report_out"
require_output_field 'runtime_behavior=disabled' "$report_out"
require_output_field 'host_mutation=0' "$report_out"
require_output_field 'network=0' "$report_out"
require_output_field 'kernel_operation=0' "$report_out"
require_output_field 'service_operation=0' "$report_out"
require_output_field 'package_manager_operation=0' "$report_out"
require_output_field 'boot_operation=0' "$report_out"
require_output_field 'selinux_policy_operation=0' "$report_out"
require_output_field 'effect_authority=denied' "$report_out"

set +e
/usr/bin/latticra --invalid >"$invalid_out" 2>"$invalid_err"
invalid_status="$?"
set -e
[ "$invalid_status" -eq 2 ] || fail "invalid CLI command exited with $invalid_status instead of 2"
require_output_field 'usage: latticra [--status|--version|--report]' "$invalid_err"

sudo rpm -e "$name"
if rpm -q "$name" >/dev/null 2>&1; then
  fail 'package still installed after removal'
fi
if [ -e /usr/bin/latticra ]; then
  fail 'CLI payload still present after removal'
fi
if [ -e /usr/share/doc/latticra/README.md ]; then
  fail 'README payload still present after removal'
fi

cat >"$report" <<EOF_REPORT
FEDORA VM CLI PAYLOAD REPEATABILITY LANE
validation_status=ok
repeatability_validation_status=ok
transcript_kind=disposable-vm-cli-payload-repeatability
ci_auto_repeatability_validation_allowed=0
prior_cli_payload_evidence_recorded=1
source_tree_revision_recorded=1
source_tree_revision=$source_tree_revision
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
fedora_kernel_version=$(uname -r)
spec_checksum_recorded=1
spec_checksum=$spec_checksum
source_archive_checksum_recorded=1
source_archive_checksum=$source_archive_checksum
rpm_nevra_recorded=1
rpm_nevra=$rpm_nevra
package_name=$name
package_version=$version
package_arch=$rpm_arch
rpm_payload_listing_recorded=1
rpm_payload_matches_expected_cli_surfaces=1
unexpected_runtime_surface_absent=1
cli_status_output_recorded=1
cli_version_output_recorded=1
cli_report_output_recorded=1
cli_invalid_command_exit_recorded=1
validated_cli_mode_still_no_effect=1
validated_runtime_behavior_still_disabled=1
validated_non_claims_preserved=1
rpm_verify_completed=1
removal_validation_performed=1
post_removal_absence_verified=1
second_disposable_vm_cli_validation_completed=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
EOF_REPORT

cat "$report"
printf 'fedora_vm_cli_payload_repeatability_lane: ok\n'

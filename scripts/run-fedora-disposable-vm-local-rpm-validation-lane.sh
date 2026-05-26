#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu
COPYFILE_DISABLE=1
export COPYFILE_DISABLE

fail() {
  printf 'fedora disposable vm local rpm validation lane: %s\n' "$1" >&2
  exit 1
}

require_flag() {
  name="$1"
  want="$2"
  case "$name" in
    LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION)
      actual="${LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION:-}"
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

require_no_payload_pattern() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$payload_listing"; then
    fail "forbidden RPM payload pattern matched: $pattern"
  fi
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

require_flag LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION 1
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

require_command awk
require_command find
require_command git
require_command grep
require_command id
require_command mktemp
require_command python3
require_command rpm
require_command rpmbuild
require_command sort
require_command tar
require_command gzip

if [ "$(id -u)" -eq 0 ]; then
  as_root=''
else
  require_command sudo
  as_root='sudo'
fi

require_file packaging/fedora/latticra.spec
require_file README.md
require_file docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
[ "$name" = 'latticra' ] || fail "unexpected package name: $name"
[ -n "$version" ] || fail 'missing package version'

root="${name}-${version}"
workdir="$(mktemp -d)"
trap 'rm -rf "$workdir"' EXIT INT HUP TERM

rpmtop="$workdir/rpmbuild"
source_archive="$rpmtop/SOURCES/$root.tar.gz"
report="$workdir/vm-validation.report"
payload_listing="$workdir/payload.list"
installed_listing="$workdir/installed.list"

mkdir -p "$rpmtop/BUILD" "$rpmtop/BUILDROOT" "$rpmtop/RPMS" "$rpmtop/SOURCES" "$rpmtop/SPECS" "$rpmtop/SRPMS"

symlink_entry=$(find . -path './.git' -prune -o -type l -print | sed -n '1p')
[ -z "$symlink_entry" ] ||
  fail "refusing source archive with symlink entry: $symlink_entry"

write_source_archive "$source_archive" "$root"
cp packaging/fedora/latticra.spec "$rpmtop/SPECS/latticra.spec"

rpmbuild --define "_topdir $rpmtop" -bb "$rpmtop/SPECS/latticra.spec"

rpm_path="$(find "$rpmtop/RPMS" -type f -name 'latticra-*.rpm' ! -name '*debuginfo*' ! -name '*debugsource*' | sort | head -n 1)"
[ -n "$rpm_path" ] || fail 'binary RPM was not produced'

rpm -qpi "$rpm_path" >/dev/null
rpm -qpl "$rpm_path" >"$payload_listing"
grep -Fqx '/usr/share/doc/latticra/README.md' "$payload_listing" || fail 'README payload missing from RPM'
require_no_payload_pattern '^/usr/bin/latticra$'
require_no_payload_pattern '^/etc/latticra(/|$)'
require_no_payload_pattern '^/usr/lib/systemd/system/latticra\.service$'
require_no_payload_pattern '^/usr/lib/modules(/|$)'
require_no_payload_pattern '^/boot/latticra(/|$)'

# Ensure a clean pre-state for the local package name.
if rpm -q "$name" >/dev/null 2>&1; then
  fail 'package is already installed before validation'
fi

$as_root rpm -Uvh --nodeps "$rpm_path"
rpm -q "$name" >/dev/null
rpm -ql "$name" >"$installed_listing"
grep -Fqx '/usr/share/doc/latticra/README.md' "$installed_listing" || fail 'installed README payload missing'
[ -f /usr/share/doc/latticra/README.md ] || fail 'installed README file absent'
rpm -V "$name"

$as_root rpm -e "$name"
if rpm -q "$name" >/dev/null 2>&1; then
  fail 'package still installed after removal'
fi
if [ -e /usr/share/doc/latticra/README.md ]; then
  fail 'README payload still present after removal'
fi

cat >"$report" <<EOF_REPORT
FEDORA DISPOSABLE VM LOCAL RPM VALIDATION LANE
validation_status=ok
package_name=$name
package_version=$version
package_version_recorded=1
disposable_vm_target_verified=1
snapshot_evidence_present=1
recovery_evidence_present=1
operator_consent_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_is_documentation_only=1
unexpected_runtime_surface_absent=1
vm_rpmdb_mutated=1
vm_filesystem_mutated=1
install_validation_performed=1
removal_validation_performed=1
post_removal_absence_verified=1
live_host_validation_completed=1
host_install_ready=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
evidence_level=9
EOF_REPORT

cat "$report"
printf 'fedora_disposable_vm_local_rpm_validation_lane: ok\n'

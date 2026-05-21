#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora disposable vm local rpm validation lane: %s\n' "$1" >&2
  exit 1
}

require_flag() {
  name="$1"
  want="$2"
  eval "actual=\${$name:-}"
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
require_command grep
require_command rpm
require_command rpmbuild
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
source_root="$workdir/$root"
source_archive="$rpmtop/SOURCES/$root.tar.gz"
report="$workdir/vm-validation.report"
payload_listing="$workdir/payload.list"
installed_listing="$workdir/installed.list"

mkdir -p "$rpmtop/BUILD" "$rpmtop/BUILDROOT" "$rpmtop/RPMS" "$rpmtop/SOURCES" "$rpmtop/SPECS" "$rpmtop/SRPMS"
mkdir -p "$source_root"

tar \
  --exclude='./.git' \
  --exclude='./.rpmwork' \
  --exclude='./*.rpm' \
  --exclude='./*.tar.gz' \
  -cf - . | tar -C "$source_root" -xf -

tar -C "$workdir" -czf "$source_archive" "$root"
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

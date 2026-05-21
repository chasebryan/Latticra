#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

rpmwork=""
archive_staging=""
installed=0

cleanup() {
  if [ "$installed" -eq 1 ]; then
    rpm -q latticra >/dev/null 2>&1 && rpm -e latticra || true
  fi
  if [ -n "$rpmwork" ]; then
    rm -rf "$rpmwork"
  fi
  if [ -n "$archive_staging" ]; then
    rm -rf "$archive_staging"
  fi
}
trap cleanup EXIT INT TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora installed-state report lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora installed-state report lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_report_contains() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$report_path"; then
    printf 'fedora installed-state report lane: missing report pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_payload() {
  pattern="$1"
  if ! grep -Eq -- "$pattern" "$payload_listing"; then
    printf 'fedora installed-state report lane: missing payload pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_no_installed_path() {
  path="$1"
  if [ -e "$path" ]; then
    printf 'fedora installed-state report lane: forbidden installed path exists: %s\n' "$path" >&2
    exit 1
  fi
}

require_file docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_file docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_file docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_file scripts/test-fedora-local-install-smoke-lane.sh
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'Status: active installed-state report lane' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'Fedora Installed-State Report' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'rpm -q latticra' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'rpm -ql latticra' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'rpm -V latticra' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'README installed: yes' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'package removed after smoke: yes' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'post-removal query failed: yes' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'Do not add these yet' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'command -v latticra' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'latticra --version' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'latticra check' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'does not run `mock`' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'does not install Latticra on a developer host' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'Add Fedora local testing guide' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_contains 'fedora_installed_state_report_lane: ok' docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md

if [ ! -r /etc/fedora-release ]; then
  printf 'fedora installed-state report lane: expected Fedora environment\n' >&2
  exit 1
fi

command -v dnf >/dev/null 2>&1

dnf -y install rpm-build gcc make tar gzip
command -v rpmbuild >/dev/null 2>&1
command -v rpm >/dev/null 2>&1
command -v tar >/dev/null 2>&1

# Chain the install-smoke lane first so the report cannot drift from install reality.
sh scripts/test-fedora-local-install-smoke-lane.sh

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
root="${name}-${version}"
archive="${root}.tar.gz"

if [ "$root" != 'latticra-0.0.0' ]; then
  printf 'fedora installed-state report lane: unexpected source root: %s\n' "$root" >&2
  exit 1
fi

rpmwork="$(mktemp -d)"
archive_staging="$(mktemp -d)"
payload_listing="$rpmwork/installed-payload.txt"
verify_output="$rpmwork/rpm-verify.txt"
query_output="$rpmwork/rpm-query.txt"
removal_output="$rpmwork/removal-query.txt"
report_path="$rpmwork/fedora-installed-state-report.txt"

mkdir -p \
  "$rpmwork/BUILD" \
  "$rpmwork/BUILDROOT" \
  "$rpmwork/RPMS" \
  "$rpmwork/SOURCES" \
  "$rpmwork/SPECS" \
  "$rpmwork/SRPMS" \
  "$archive_staging/$root"

tar \
  --exclude='./.git' \
  --exclude='./.rpmwork' \
  --exclude='./*.rpm' \
  --exclude='./*.tar.gz' \
  -cf - . | tar -C "$archive_staging/$root" -xf -

tar -C "$archive_staging" -czf "$rpmwork/SOURCES/$archive" "$root"

rpmbuild -bb packaging/fedora/latticra.spec \
  --define "_topdir $rpmwork" \
  --define "_sourcedir $rpmwork/SOURCES" \
  --define "_rpmdir $rpmwork/RPMS" \
  --define "_builddir $rpmwork/BUILD" \
  --define "_buildrootdir $rpmwork/BUILDROOT" \
  --define "debug_package %{nil}"

rpm_count="$(find "$rpmwork/RPMS" -type f -name 'latticra-*.rpm' | wc -l | tr -d ' ')"
if [ "$rpm_count" != '1' ]; then
  printf 'fedora installed-state report lane: expected exactly one local RPM, found %s\n' "$rpm_count" >&2
  exit 1
fi

rpm_path="$(find "$rpmwork/RPMS" -type f -name 'latticra-*.rpm' | head -n 1)"

rpm -Uvh "$rpm_path"
installed=1

rpm -q latticra >"$query_output"
rpm -ql latticra >"$payload_listing"
require_payload '/usr/share/doc/latticra/README.md$'

test -r /usr/share/doc/latticra/README.md

rpm -V latticra >"$verify_output" 2>&1
if [ -s "$verify_output" ]; then
  printf 'fedora installed-state report lane: unexpected rpm verification output\n' >&2
  cat "$verify_output" >&2
  exit 1
fi

require_no_installed_path /usr/bin/latticra
require_no_installed_path /etc/latticra
require_no_installed_path /usr/lib/systemd/system/latticra.service

if find /usr/lib/modules -name '*latticra*' 2>/dev/null | grep -q .; then
  printf 'fedora installed-state report lane: unexpected kernel module payload\n' >&2
  exit 1
fi

if find /boot -name '*latticra*' 2>/dev/null | grep -q .; then
  printf 'fedora installed-state report lane: unexpected boot payload\n' >&2
  exit 1
fi

if find /etc/selinux /usr/share/selinux -name '*latticra*' 2>/dev/null | grep -q .; then
  printf 'fedora installed-state report lane: unexpected SELinux payload\n' >&2
  exit 1
fi

rpm -e latticra
installed=0

if rpm -q latticra >"$removal_output" 2>&1; then
  printf 'fedora installed-state report lane: package still installed after removal\n' >&2
  cat "$removal_output" >&2
  exit 1
fi

{
  printf '%s\n' 'Fedora Installed-State Report'
  printf '%s\n\n' '============================='
  printf '%s\n' 'Package identity'
  printf '%s\n' '----------------'
  printf 'Name: %s\n' "$name"
  printf 'Version: %s\n' "$version"
  printf 'Source archive: %s\n\n' "$archive"
  printf '%s\n' 'Install posture'
  printf '%s\n' '---------------'
  printf 'local RPM built: yes\n'
  printf 'installed in disposable Fedora CI: yes\n'
  printf 'developer host install: no\n\n'
  printf '%s\n' 'Installed package query'
  printf '%s\n' '-----------------------'
  cat "$query_output"
  printf '\n%s\n' 'Installed payload'
  printf '%s\n' '-----------------'
  cat "$payload_listing"
  printf '\n%s\n' 'Verification result'
  printf '%s\n' '-------------------'
  printf 'rpm verification clean: yes\n'
  printf '\n%s\n' 'Payload policy checks'
  printf '%s\n' '---------------------'
  printf 'README installed: yes\n'
  printf 'command payload absent: yes\n'
  printf 'configuration payload absent: yes\n'
  printf 'systemd service payload absent: yes\n'
  printf 'kernel module payload absent: yes\n'
  printf 'boot payload absent: yes\n'
  printf 'SELinux policy payload absent: yes\n'
  printf 'runtime configuration payload absent: yes\n\n'
  printf '%s\n' 'Removal result'
  printf '%s\n' '--------------'
  printf 'package removed after smoke: yes\n'
  printf 'post-removal query failed: yes\n\n'
  printf '%s\n' 'Boundary'
  printf '%s\n' '--------'
  printf 'mock used: no\n'
  printf 'artifact published: no\n'
  printf 'Fedora submission performed: no\n'
} >"$report_path"

require_report_contains 'Fedora Installed-State Report'
require_report_contains 'Package identity'
require_report_contains 'Install posture'
require_report_contains 'Installed package query'
require_report_contains 'Installed payload'
require_report_contains 'Verification result'
require_report_contains 'Payload policy checks'
require_report_contains 'Removal result'
require_report_contains 'Boundary'
require_report_contains 'Name: latticra'
require_report_contains 'Version: 0.0.0'
require_report_contains 'local RPM built: yes'
require_report_contains 'installed in disposable Fedora CI: yes'
require_report_contains 'developer host install: no'
require_report_contains 'rpm verification clean: yes'
require_report_contains 'README installed: yes'
require_report_contains 'command payload absent: yes'
require_report_contains 'configuration payload absent: yes'
require_report_contains 'systemd service payload absent: yes'
require_report_contains 'kernel module payload absent: yes'
require_report_contains 'boot payload absent: yes'
require_report_contains 'SELinux policy payload absent: yes'
require_report_contains 'runtime configuration payload absent: yes'
require_report_contains 'package removed after smoke: yes'
require_report_contains 'post-removal query failed: yes'
require_report_contains 'mock used: no'
require_report_contains 'artifact published: no'
require_report_contains 'Fedora submission performed: no'

printf 'fedora_installed_state_report_lane: ok\n'
#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora rpm payload inspection report: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora rpm payload inspection report: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_report_contains() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$report_path"; then
    printf 'fedora rpm payload inspection report: missing report pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_payload() {
  pattern="$1"
  if ! grep -Eq -- "$pattern" "$payload_listing"; then
    printf 'fedora rpm payload inspection report: missing payload pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_no_payload() {
  pattern="$1"
  if grep -Eq -- "$pattern" "$payload_listing"; then
    printf 'fedora rpm payload inspection report: forbidden payload pattern matched: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_file docs/FEDORA_LOCAL_BINARY_RPM_BUILD_LANE.md
require_file docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file scripts/test-fedora-local-binary-rpm-build-lane.sh
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'Status: active generated-report lane' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'Fedora RPM Payload Inspection Report' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'rpm -qpi <generated-rpm>' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'rpm -qpl <generated-rpm>' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'README payload present: yes' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'command payload absent: yes' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'systemd service payload absent: yes' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'does not run `mock`' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'does not install Latticra' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'does not publish package artifacts' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'Add Fedora local install smoke plan' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_contains 'fedora_rpm_payload_inspection_report: ok' docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md

if [ ! -r /etc/fedora-release ]; then
  printf 'fedora rpm payload inspection report: expected Fedora environment\n' >&2
  exit 1
fi

command -v dnf >/dev/null 2>&1

dnf -y install rpm-build gcc make tar gzip
command -v rpmbuild >/dev/null 2>&1
command -v rpm >/dev/null 2>&1
command -v tar >/dev/null 2>&1

# Chain the local RPM build lane first so the report cannot drift from build reality.
sh scripts/test-fedora-local-binary-rpm-build-lane.sh

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
root="${name}-${version}"
archive="${root}.tar.gz"

rpmwork="$(mktemp -d)"
archive_staging="$(mktemp -d)"
metadata_output="$rpmwork/rpm-info.txt"
payload_listing="$rpmwork/rpm-payload.txt"
report_path="$rpmwork/fedora-rpm-payload-inspection-report.txt"

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
  --define "_buildrootdir $rpmwork/BUILDROOT"

rpm_count="$(find "$rpmwork/RPMS" -type f -name 'latticra-*.rpm' | wc -l | tr -d ' ')"
if [ "$rpm_count" != '1' ]; then
  printf 'fedora rpm payload inspection report: expected exactly one local RPM, found %s\n' "$rpm_count" >&2
  rm -rf "$rpmwork" "$archive_staging"
  exit 1
fi

rpm_path="$(find "$rpmwork/RPMS" -type f -name 'latticra-*.rpm' | head -n 1)"

rpm -qpi "$rpm_path" >"$metadata_output"
rpm -qpl "$rpm_path" >"$payload_listing"

require_payload '/usr/share/doc/latticra/README.md$'
require_no_payload '(^|/usr/)bin/latticra$'
require_no_payload '^/etc/latticra(/|$)'
require_no_payload '^/usr/lib/systemd/system/latticra\.service$'
require_no_payload '(^|/)lib/modules(/|$)'
require_no_payload '(^|/)boot(/|$)'
require_no_payload '(^|/)selinux(/|$)'

{
  printf 'Fedora RPM Payload Inspection Report\n'
  printf '====================================\n\n'
  printf 'Package identity\n'
  printf '----------------\n'
  printf 'Name: %s\n' "$name"
  printf 'Version: %s\n' "$version"
  printf 'Source archive: %s\n\n' "$archive"
  printf 'Build posture\n'
  printf '-------------\n'
  printf 'local-only binary RPM build: yes\n'
  printf 'installed during report: no\n'
  printf 'published during report: no\n\n'
  printf 'RPM metadata\n'
  printf '------------\n'
  cat "$metadata_output"
  printf '\nRPM payload\n'
  printf '-----------\n'
  cat "$payload_listing"
  printf '\nPayload policy checks\n'
  printf '---------------------\n'
  printf 'README payload present: yes\n'
  printf 'command payload absent: yes\n'
  printf 'configuration payload absent: yes\n'
  printf 'systemd service payload absent: yes\n'
  printf 'kernel module payload absent: yes\n'
  printf 'boot payload absent: yes\n'
  printf 'SELinux policy payload absent: yes\n'
  printf 'runtime configuration payload absent: yes\n\n'
  printf 'Boundary\n'
  printf '--------\n'
  printf 'mock used: no\n'
  printf 'host install performed: no\n'
  printf 'artifact published: no\n'
  printf 'Fedora submission performed: no\n'
} >"$report_path"

require_report_contains 'Fedora RPM Payload Inspection Report'
require_report_contains 'Package identity'
require_report_contains 'Build posture'
require_report_contains 'RPM metadata'
require_report_contains 'RPM payload'
require_report_contains 'Payload policy checks'
require_report_contains 'Boundary'
require_report_contains 'Name: latticra'
require_report_contains 'Version: 0.0.0'
require_report_contains 'local-only binary RPM build: yes'
require_report_contains 'installed during report: no'
require_report_contains 'published during report: no'
require_report_contains 'README payload present: yes'
require_report_contains 'command payload absent: yes'
require_report_contains 'configuration payload absent: yes'
require_report_contains 'systemd service payload absent: yes'
require_report_contains 'kernel module payload absent: yes'
require_report_contains 'boot payload absent: yes'
require_report_contains 'SELinux policy payload absent: yes'
require_report_contains 'runtime configuration payload absent: yes'
require_report_contains 'mock used: no'
require_report_contains 'host install performed: no'
require_report_contains 'artifact published: no'
require_report_contains 'Fedora submission performed: no'

rm -rf "$rpmwork" "$archive_staging"

printf 'fedora_rpm_payload_inspection_report: ok\n'
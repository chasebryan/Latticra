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
    printf 'fedora local install smoke lane: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local install smoke lane: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_payload() {
  pattern="$1"
  if ! grep -Eq -- "$pattern" "$payload_listing"; then
    printf 'fedora local install smoke lane: missing payload pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_no_installed_path() {
  path="$1"
  if [ -e "$path" ]; then
    printf 'fedora local install smoke lane: forbidden installed path exists: %s\n' "$path" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_file docs/FEDORA_LOCAL_INSTALL_SMOKE_PLAN.md
require_file docs/FEDORA_RPM_PAYLOAD_INSPECTION_REPORT.md
require_file scripts/test-fedora-rpm-payload-inspection-report.sh
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'Status: active local install smoke lane' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'disposable Fedora CI' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'rpm -Uvh <generated-rpm>' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'rpm -q latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'rpm -ql latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'rpm -V latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'rpm -e latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains '! rpm -q latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'Do not add these yet' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'command -v latticra' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'latticra --version' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'latticra check' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'does not run `mock`' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'does not install Latticra on a developer host' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'Add Fedora installed-state report lane' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md
require_contains 'fedora_local_install_smoke_lane: ok' docs/FEDORA_LOCAL_INSTALL_SMOKE_LANE.md

if [ ! -r /etc/fedora-release ]; then
  printf 'fedora local install smoke lane: expected Fedora environment\n' >&2
  exit 1
fi

command -v dnf >/dev/null 2>&1

dnf -y install rpm-build gcc make tar gzip
command -v rpmbuild >/dev/null 2>&1
command -v rpm >/dev/null 2>&1
command -v tar >/dev/null 2>&1

# Chain the payload report guard first so installed-state proof follows payload proof.
sh scripts/test-fedora-rpm-payload-inspection-report.sh

name="$(awk '/^Name:/ { print $2; exit }' packaging/fedora/latticra.spec)"
version="$(awk '/^Version:/ { print $2; exit }' packaging/fedora/latticra.spec)"
root="${name}-${version}"
archive="${root}.tar.gz"

if [ "$root" != 'latticra-0.0.0' ]; then
  printf 'fedora local install smoke lane: unexpected source root: %s\n' "$root" >&2
  exit 1
fi

rpmwork="$(mktemp -d)"
archive_staging="$(mktemp -d)"
payload_listing="$rpmwork/rpm-payload.txt"
verify_output="$rpmwork/rpm-verify.txt"

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
  printf 'fedora local install smoke lane: expected exactly one local RPM, found %s\n' "$rpm_count" >&2
  exit 1
fi

rpm_path="$(find "$rpmwork/RPMS" -type f -name 'latticra-*.rpm' | head -n 1)"
rpm -qpl "$rpm_path" >"$payload_listing"
require_payload '/usr/share/doc/latticra/README.md$'

rpm -Uvh "$rpm_path"
installed=1

rpm -q latticra >/dev/null
rpm -ql latticra >"$payload_listing"
require_payload '/usr/share/doc/latticra/README.md$'

test -r /usr/share/doc/latticra/README.md

if rpm -V latticra >"$verify_output" 2>&1; then
  :
else
  printf 'fedora local install smoke lane: rpm verification failed\n' >&2
  cat "$verify_output" >&2
  exit 1
fi

if [ -s "$verify_output" ]; then
  printf 'fedora local install smoke lane: unexpected rpm verification output\n' >&2
  cat "$verify_output" >&2
  exit 1
fi

require_no_installed_path /usr/bin/latticra
require_no_installed_path /etc/latticra
require_no_installed_path /usr/lib/systemd/system/latticra.service

if find /usr/lib/modules -name '*latticra*' 2>/dev/null | grep -q .; then
  printf 'fedora local install smoke lane: unexpected kernel module payload\n' >&2
  exit 1
fi

if find /boot -name '*latticra*' 2>/dev/null | grep -q .; then
  printf 'fedora local install smoke lane: unexpected boot payload\n' >&2
  exit 1
fi

if find /etc/selinux /usr/share/selinux -name '*latticra*' 2>/dev/null | grep -q .; then
  printf 'fedora local install smoke lane: unexpected SELinux payload\n' >&2
  exit 1
fi

rpm -e latticra
installed=0

if rpm -q latticra >/dev/null 2>&1; then
  printf 'fedora local install smoke lane: package still installed after removal\n' >&2
  exit 1
fi

printf 'fedora_local_install_smoke_lane: ok\n'
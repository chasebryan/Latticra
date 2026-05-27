#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse rpmlint osc availability: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse rpmlint osc availability: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

zypper_install() {
  if [ "$(id -u)" -eq 0 ]; then
    zypper --non-interactive refresh
    zypper --non-interactive install --force-resolution "$@"
  elif command -v sudo >/dev/null 2>&1; then
    sudo zypper --non-interactive refresh
    sudo zypper --non-interactive install --force-resolution "$@"
  else
    printf 'opensuse rpmlint osc availability: zypper install requires root or sudo\n' >&2
    exit 1
  fi
}

probe_tool_invocation() {
  tool="$1"
  if "$tool" --version >/dev/null 2>&1; then
    return 0
  fi
  "$tool" --help >/dev/null 2>&1
}

require_file docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_file docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
require_file docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
require_file docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
require_file docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
require_file docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
require_file docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
require_file scripts/test-opensuse-local-rpm-static-validation.sh
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes

require_contains 'Status: active tool availability lane' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'rpmlint installs' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'osc installs' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'does not lint the Latticra openSUSE spec yet' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'does not run `rpmbuild`, `osc build`, `spec-cleaner`, or `zypper install` against a Latticra artifact' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'does not create package artifacts' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'scripts/test-opensuse-rpm-install-remove-transcript-contract.sh' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains '.github/workflows/opensuse-rpm-install-remove-transcript-contract.yml' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'Add openSUSE RPM build-evidence intake denial review contract' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
require_contains 'opensuse_rpmlint_osc_availability: ok' docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md

if [ ! -r /etc/os-release ] || ! grep -Eq '^(ID=opensuse|ID_LIKE=.*suse|ID="opensuse|ID_LIKE=".*suse)' /etc/os-release; then
  printf 'opensuse rpmlint osc availability: expected openSUSE environment\n' >&2
  exit 1
fi

command -v zypper >/dev/null 2>&1

zypper_install rpmlint osc
command -v rpmlint >/dev/null 2>&1
probe_tool_invocation rpmlint
command -v osc >/dev/null 2>&1
probe_tool_invocation osc

sh scripts/test-opensuse-local-rpm-static-validation.sh

printf 'opensuse_rpmlint_osc_availability: ok\n'

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local rpm validation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local rpm validation plan: missing required pattern in %s: %s\n' "$file" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_file docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_file docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_file packaging/fedora/latticra.spec
require_file scripts/test-fedora-local-rpm-spec-skeleton.sh

require_contains 'Status: planning record' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'local validation steps for the Latticra RPM draft skeleton' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'Static spec skeleton guard' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'Fedora container guard' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'rpmlint availability check' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'source archive policy check' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'source RPM dry-run plan' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'local mock build plan' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'installed file inspection plan' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'local-only draft marker' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'License placeholder' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'rpmlint packaging/fedora/latticra.spec' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'version tag policy' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'source archive naming' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'license expression' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'installed file list' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'mock config used' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'installed docs' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'installed license files' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'file ownership' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'It does not run rpmbuild, rpmlint, or mock.' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'Add local RPM static validation lane' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md
require_contains 'fedora_local_rpm_validation_plan: ok' docs/FEDORA_LOCAL_RPM_VALIDATION_PLAN.md

printf 'fedora_local_rpm_validation_plan: ok\n'

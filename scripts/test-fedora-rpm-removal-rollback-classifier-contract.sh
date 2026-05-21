#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora rpm removal rollback classifier contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora rpm removal rollback classifier contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_file docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_file docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_file docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md

require_contains 'Status: contract record' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'Evidence level: 5 target, contract only' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'operator_removal_confirmation=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'package_name=latticra' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'package_identity_present=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'package_query_ready=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'installed_package_detected=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'owned_file_list_available=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'readme_owned_by_package=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'unexpected_runtime_surface_absent=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'post_removal_absence_check_planned=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'failure_report_planned=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'network_required=0' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'service_operation_requested=0' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'boot_operation_requested=0' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'kernel_operation_requested=0' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'policy_operation_requested=0' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'FEDORA RPM REMOVAL ROLLBACK CLASSIFIER' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'removal_rollback_status=removal-ready' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'removal_allowed=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'rollback_planned=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'removal_performed=0' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'host_mutation_performed=0' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'partial_failure_report_required=1' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'package-installed-but-ownership-unknown' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'Add a pure C removal/rollback classifier' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'fedora_rpm_removal_rollback_classifier_contract: ok' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md
require_contains 'does not implement removal' docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER_CONTRACT.md

printf 'fedora_rpm_removal_rollback_classifier_contract: ok\n'

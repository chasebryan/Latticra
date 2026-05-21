#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local rpm removal rollback plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local rpm removal rollback plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_file docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_file docs/status/FEDORA_RPM_GATE_CLASSIFIER_STATUS.md
require_file include/latticra/fedora_rpm_gate.h

require_contains 'Status: planning record' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'operator_removal_confirmation=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'package_name=latticra' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'package_query_ready=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'installed_package_detected=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'owned_file_list_available=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'post_removal_absence_check_planned=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'failure_report_planned=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'package_origin=local-rpm' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'readme_owned_by_package=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'unexpected_runtime_surface_absent=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'package_absent_after_removal' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'partial_failure_report_required=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'network_allowed=0' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'package_build_allowed=0' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'service_operation_allowed=0' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'boot_operation_allowed=0' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'kernel_operation_allowed=0' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'policy_operation_allowed=0' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'host_mutation_performed=0' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'removal_or_rollback_plan_present=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'post_install_verification_plan_present=1' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'Only then consider a tightly gated local RPM execution lane' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'fedora_local_rpm_removal_rollback_plan: ok' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md
require_contains 'does not implement removal' docs/FEDORA_LOCAL_RPM_REMOVAL_ROLLBACK_PLAN.md

printf 'fedora_local_rpm_removal_rollback_plan: ok\n'

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra effect substrate transition intake: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing pattern in $file: $pattern"
}

doc='docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md'
status='docs/status/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
workflow='.github/workflows/latticra-effect-substrate-transition-intake.yml'

for file in "$doc" "$status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_effect_substrate_transition_intake_present=1' "$file"
  require_contains 'transition_source_branch=build/separate-build-system-and-alignment-fixes' "$file"
  require_contains 'transition_source_role=experimental-effect-substrate-and-model1-bridge-lane' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'effect_contract_schema_required=1' "$file"
  require_contains 'effect_evidence_record_contract_required=1' "$file"
  require_contains 'effect_contract_schema_intake_satisfied=1' "$file"
  require_contains 'effect_evidence_record_contract_intake_satisfied=1' "$file"
  require_contains 'effect_allowlist_contract_required=1' "$file"
  require_contains 'effect_allowlist_contract_intake_satisfied=1' "$file"
  require_contains 'effect_allowlist_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'build_profile_boundary_required=1' "$file"
  require_contains 'build_profile_boundary_intake_satisfied=1' "$file"
  require_contains 'build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'effect_runner_review_boundary_required=1' "$file"
  require_contains 'effect_runner_review_boundary_intake_satisfied=1' "$file"
  require_contains 'effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'model1_bridge_contract_required=1' "$file"
  require_contains 'model1_bridge_contract_intake_satisfied=1' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_required=1' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_intake_satisfied=1' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_reference=docs/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY.md' "$file"
  require_contains 'model1_import_review_required=1' "$file"
  require_contains 'model1_import_review_satisfied=0' "$file"
  require_contains 'separate_build_platform_review_required=1' "$file"
  require_contains 'separate_build_platform_review_boundary_intake_satisfied=1' "$file"
  require_contains 'separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'guarded_model1_effect_demonstration_boundary_required=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_boundary_intake_satisfied=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_boundary_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY.md' "$file"
  require_contains 'guarded_model1_effect_demonstration_required=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_satisfied=0' "$file"
  require_contains 'guarded_model1_effect_demonstration_evidence_accepted=0' "$file"
  require_contains 'operator_demo_non_claim_review_required=1' "$file"
  require_contains 'operator_usable_workflow_required=1' "$file"
  require_contains 'operator_workflow_reference_required=1' "$file"
  require_contains 'promotion_allowed_by_allowlist_boundary_alone=0' "$file"
  require_contains 'effect_runner_acceptance_allowed=0' "$file"
  require_contains 'effect_runner_accepted=0' "$file"
  require_contains 'runner_dispatch_performed=0' "$file"
  require_contains 'build_separate_execution_performed=0' "$file"
  require_contains 'source_import_performed=0' "$file"
  require_contains 'artifact_acceptance_allowed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'model1_import_accepted=0' "$file"
  require_contains 'build_profile_promotion_accepted=0' "$file"
  require_contains 'root_authority_allowed=0' "$file"
  require_contains 'network_allowed=0' "$file"
  require_contains 'usb_write_allowed=0' "$file"
  require_contains 'qemu_run_allowed=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'distribution_readiness_claim=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'completion_estimate_review_required_for_capability_promotion=1' "$file"
  require_contains 'latticra_effect_substrate_transition_intake: ok' "$file"
done

require_contains 'LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md' "$status_index"
require_contains 'Effect Substrate Transition Intake' "$docs_hub"
require_contains 'effect substrate transition intake](docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md)' "$root_readme"
require_contains 'Latest Latticra effect substrate transition intake note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra effect substrate transition intake note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra effect substrate transition intake note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra effect substrate transition intake note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Model-1 import and mixed-build review boundary.' "$upcoming_work"
require_contains 'Model-1 import and mixed-build review boundary.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$current_status"
require_contains 'latticra-effect-substrate-transition-intake:' "$makefile"
require_contains 'sh ./scripts/test-latticra-effect-substrate-transition-intake.sh' "$makefile"
require_contains 'Run Latticra effect substrate transition intake guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'sh scripts/test-latticra-effect-substrate-transition-intake.sh' "$workflow"

printf 'latticra_effect_substrate_transition_intake: ok\n'

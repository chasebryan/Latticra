#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra effect allowlist build-profile boundary: %s\n' "$1" >&2
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

doc='docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md'
status='docs/status/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_STATUS.md'
transition_doc='docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md'
transition_status='docs/status/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md'
schema_doc='docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md'
schema_status='docs/status/LATTICRA_EFFECT_CONTRACT_SCHEMA_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-effect-allowlist-build-profile-boundary.yml'

for file in "$doc" "$status" "$transition_doc" "$transition_status" "$schema_doc" "$schema_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_effect_allowlist_build_profile_boundary_present=1' "$file"
  require_contains 'effect_allowlist_contract_intake_satisfied=1' "$file"
  require_contains 'build_profile_boundary_intake_satisfied=1' "$file"
  require_contains 'effect_allowlist_boundary_version=1' "$file"
  require_contains 'build_profile_boundary_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md' "$file"
  require_contains 'effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md' "$file"
  require_contains 'effect_status_surface_reference=docs/status/LATTICRA_EFFECT_STATUS_SURFACE_STATUS.md' "$file"
  require_contains 'allowed_initial_effect_classes=none,read' "$file"
  require_contains 'blocked_effect_classes=local_mutation,host_mutation,network,hardware,boot,recovery,external,unknown' "$file"
  require_contains 'allowed_build_profiles=metadata-only' "$file"
  require_contains 'blocked_build_profiles=effect-runner,host-profile,mixed-build,model1-bridge,production' "$file"
  require_contains 'operator_usable_workflow_required=1' "$file"
  require_contains 'operator_workflow_reference_required=1' "$file"
  require_contains 'deny_by_default=1' "$file"
  require_contains 'effect_runner_acceptance_allowed=0' "$file"
  require_contains 'build_profile_promotion_accepted=0' "$file"
  require_contains 'model1_bridge_contract_intake_satisfied=0' "$file"
  require_contains 'model1_import_review_satisfied=0' "$file"
  require_contains 'promotion_allowed_by_allowlist_boundary_alone=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'distribution_readiness_claim=0' "$file"
  require_contains 'latticra_effect_allowlist_build_profile_boundary: ok' "$file"
done

for field in allowlist_id allowlist_version allowed_effect allowed_scope allowed_target_pattern denied_effect_classes operator_usable_workflow_reference contract_schema_reference evidence_record_reference build_profile_reference model1_bridge_mode decision_default non_claims
do
  require_contains "$field" "$doc"
done

for field in build_profile_id build_profile_version build_profile_kind profile_authority source_revision allowed_effect_classes denied_operations effect_runner_mode local_output_scope evidence_record_required promotion_allowed
do
  require_contains "$field" "$doc"
done

for field in workflow_id workflow_user workflow_goal workflow_entrypoint workflow_inputs workflow_outputs operator_visible_result promotion_requested
do
  require_contains "$field" "$doc"
done

for file in "$transition_doc" "$transition_status"
do
  require_contains 'effect_allowlist_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'effect_allowlist_contract_intake_satisfied=1' "$file"
  require_contains 'build_profile_boundary_intake_satisfied=1' "$file"
  require_contains 'effect_runner_review_boundary_intake_satisfied=1' "$file"
  require_contains 'effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'separate_build_platform_review_boundary_intake_satisfied=1' "$file"
  require_contains 'separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'model1_bridge_contract_intake_satisfied=1' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
  require_contains 'operator_usable_workflow_required=1' "$file"
  require_contains 'operator_workflow_reference_required=1' "$file"
  require_contains 'promotion_allowed_by_allowlist_boundary_alone=0' "$file"
  require_contains 'effect_runner_acceptance_allowed=0' "$file"
  require_contains 'build_profile_promotion_accepted=0' "$file"
done

require_contains 'Model-1 import and mixed-build review boundary.' "$schema_doc"
require_contains 'Model-1 import and mixed-build review boundary.' "$schema_status"
require_contains 'LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_STATUS.md' "$status_index"
require_contains 'Effect Allowlist and Build-Profile Boundary' "$docs_hub"
require_contains 'effect allowlist and build-profile boundary](docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md)' "$root_readme"
require_contains 'Latest Latticra effect allowlist/build-profile boundary note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra effect allowlist/build-profile boundary note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra effect allowlist/build-profile boundary note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra effect allowlist/build-profile boundary note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'operator_usable_workflow_required=1' "$current_direction"
require_contains 'Model-1 import and mixed-build review boundary.' "$current_status"
require_contains 'Model-1 import and mixed-build review boundary.' "$upcoming_work"
require_contains 'latticra-effect-allowlist-build-profile-boundary:' "$makefile"
require_contains 'sh ./scripts/test-latticra-effect-allowlist-build-profile-boundary.sh' "$makefile"
require_contains 'latticra-effect-allowlist-build-profile-boundary:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-effect-allowlist-build-profile-boundary.sh' "$quality_guard"
require_contains 'Run Latticra effect allowlist/build-profile boundary guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-effect-allowlist-build-profile-boundary.sh' "$workflow"

printf 'latticra_effect_allowlist_build_profile_boundary: ok\n'

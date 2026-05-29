#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra model1 import mixed-build review boundary: %s\n' "$1" >&2
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

doc='docs/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY.md'
status='docs/status/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY_STATUS.md'
transition_doc='docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md'
transition_status='docs/status/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md'
bridge_doc='docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md'
bridge_status='docs/status/LATTICRA_MODEL1_BRIDGE_PROTOCOL_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-model1-import-mixed-build-review-boundary.yml'

for file in "$doc" "$status" "$transition_doc" "$transition_status" "$bridge_doc" "$bridge_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_model1_import_mixed_build_review_boundary_present=1' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_intake_satisfied=1' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md' "$file"
  require_contains 'effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md' "$file"
  require_contains 'effect_allowlist_build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md' "$file"
  require_contains 'effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
  require_contains 'review_source=prior-separate-build-boundary-and-bridge-protocol-contract' "$file"
  require_contains 'allowed_review_modes=static-import-scope-review,mixed-build-layout-review,bridge-protocol-compatibility-review,no-effect-evidence-review' "$file"
  require_contains 'blocked_review_modes=model1-launch,model1-import,artifact-import,artifact-copy,mixed-build-promotion,bridge-execution,runner-execution,production' "$file"
  require_contains 'import_scope_review_required=1' "$file"
  require_contains 'source_provenance_review_required=1' "$file"
  require_contains 'mixed_build_layout_review_required=1' "$file"
  require_contains 'target_identity_review_required=1' "$file"
  require_contains 'bridge_protocol_compatibility_required=1' "$file"
  require_contains 'target_evidence_record_required=1' "$file"
  require_contains 'non_claim_evidence_required=1' "$file"
  require_contains 'deny_by_default=1' "$file"
  require_contains 'model1_import_review_boundary_satisfied=1' "$file"
  require_contains 'model1_import_review_satisfied=0' "$file"
  require_contains 'model1_import_accepted=0' "$file"
  require_contains 'mixed_build_promotion_accepted=0' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'source_import_performed=0' "$file"
  require_contains 'artifact_copy_performed=0' "$file"
  require_contains 'artifact_acceptance_allowed=0' "$file"
  require_contains 'effect_runner_acceptance_allowed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed=0' "$file"
  require_contains 'network_performed=0' "$file"
  require_contains 'host_mutation_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'distribution_readiness_claim=0' "$file"
  require_contains 'guarded_model1_effect_demonstration_required=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_satisfied=0' "$file"
  require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$file"
  require_contains 'latticra_model1_import_mixed_build_review_boundary: ok' "$file"
done

for field in model1_import_review_id model1_import_review_version source_worktree source_branch source_revision source_dirty_state model1_tree_reference import_scope import_decision target_identity target_revision mixed_build_layout_reference bridge_protocol_reference compatibility_decision artifact_inventory_reference evidence_record_reference non_claims
do
  require_contains "$field" "$doc"
done

for field in mixed_build_review_id build_profile_reference report_only_profile_reference effect_enabled_profile_reference artifact_acceptance_decision promotion_decision runner_acceptance_decision bridge_execution_decision operator_workflow_reference target_evidence_fields redaction_status
do
  require_contains "$field" "$doc"
done

for file in "$transition_doc" "$transition_status"
do
  require_contains 'model1_import_mixed_build_review_boundary_required=1' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_intake_satisfied=1' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_reference=docs/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY.md' "$file"
  require_contains 'model1_import_review_satisfied=0' "$file"
  require_contains 'model1_import_accepted=0' "$file"
  require_contains 'guarded_model1_effect_demonstration_required=1' "$file"
  require_contains 'guarded_model1_effect_demonstration_satisfied=0' "$file"
  require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$file"
done

require_contains 'Model-1 import and mixed-build review boundary.' "$bridge_doc"
require_contains 'Model-1 import and mixed-build review boundary.' "$bridge_status"
require_contains 'LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY_STATUS.md' "$status_index"
require_contains 'Model-1 Import and Mixed-Build Review Boundary' "$docs_hub"
require_contains 'Model-1 import and mixed-build review boundary](docs/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY.md)' "$root_readme"
require_contains 'Latest Latticra Model-1 import and mixed-build review boundary note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra Model-1 import and mixed-build review boundary note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra Model-1 import and mixed-build review boundary note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra Model-1 import and mixed-build review boundary note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration evidence boundary.' "$upcoming_work"
require_contains 'latticra-model1-import-mixed-build-review-boundary:' "$makefile"
require_contains 'sh ./scripts/test-latticra-model1-import-mixed-build-review-boundary.sh' "$makefile"
require_contains 'latticra-model1-import-mixed-build-review-boundary:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-model1-import-mixed-build-review-boundary.sh' "$quality_guard"
require_contains 'Run Latticra Model-1 import mixed-build review boundary guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-model1-import-mixed-build-review-boundary.sh' "$workflow"

printf 'latticra_model1_import_mixed_build_review_boundary: ok\n'

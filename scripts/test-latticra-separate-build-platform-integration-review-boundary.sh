#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra separate-build platform integration review boundary: %s\n' "$1" >&2
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

doc='docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md'
status='docs/status/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY_STATUS.md'
transition_doc='docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md'
transition_status='docs/status/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md'
runner_doc='docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md'
runner_status='docs/status/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-separate-build-platform-integration-review-boundary.yml'

for file in "$doc" "$status" "$transition_doc" "$transition_status" "$runner_doc" "$runner_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_separate_build_platform_integration_review_boundary_present=1' "$file"
  require_contains 'separate_build_platform_review_boundary_intake_satisfied=1' "$file"
  require_contains 'separate_build_platform_review_boundary_version=1' "$file"
  require_contains 'transition_source_worktree=/Users/chasebryan/Latticra' "$file"
  require_contains 'transition_source_branch=build/separate-build-system-and-alignment-fixes' "$file"
  require_contains 'source_worktree_dirty=1' "$file"
  require_contains 'build_separate_tree_observed=1' "$file"
  require_contains 'build_separate_script_observed=scripts/build-separate.sh' "$file"
  require_contains 'build_separate_artifacts_observed=1' "$file"
  require_contains 'build_separate_artifacts_accepted=0' "$file"
  require_contains 'report_only_profile_observed=1' "$file"
  require_contains 'effect_enabled_profile_observed=1' "$file"
  require_contains 'effect_enabled_profile_accepted=0' "$file"
  require_contains 'model1_tree_observed=1' "$file"
  require_contains 'model1_import_accepted=0' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'allowed_review_modes=static-source-review,artifact-inventory-review,no-effect-report' "$file"
  require_contains 'blocked_review_modes=build-execution,artifact-import,artifact-copy,mixed-build,model1-bridge,runner-execution,production' "$file"
  require_contains 'source_branch_review_required=1' "$file"
  require_contains 'build_layout_review_required=1' "$file"
  require_contains 'artifact_boundary_review_required=1' "$file"
  require_contains 'platform_assumption_review_required=1' "$file"
  require_contains 'non_claim_evidence_required=1' "$file"
  require_contains 'deny_by_default=1' "$file"
  require_contains 'build_separate_execution_performed=0' "$file"
  require_contains 'source_import_performed=0' "$file"
  require_contains 'artifact_copy_performed=0' "$file"
  require_contains 'artifact_acceptance_allowed=0' "$file"
  require_contains 'mixed_build_promotion_accepted=0' "$file"
  require_contains 'model1_bridge_contract_intake_satisfied=1' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
  require_contains 'effect_runner_acceptance_allowed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'distribution_readiness_claim=0' "$file"
  require_contains 'latticra_separate_build_platform_integration_review_boundary: ok' "$file"
done

for field in separate_build_review_id separate_build_review_version source_worktree source_branch source_revision source_dirty_state build_script_reference build_profile_reference artifact_inventory_reference model1_tree_reference effect_runner_reference platform_assumptions artifact_acceptance_decision import_decision promotion_decision non_claims
do
  require_contains "$field" "$doc"
done

for file in "$transition_doc" "$transition_status"
do
  require_contains 'separate_build_platform_review_boundary_intake_satisfied=1' "$file"
  require_contains 'separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md' "$file"
  require_contains 'build_separate_execution_performed=0' "$file"
  require_contains 'source_import_performed=0' "$file"
  require_contains 'artifact_acceptance_allowed=0' "$file"
  require_contains 'model1_bridge_contract_intake_satisfied=1' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
done

require_contains 'Model-1 import and mixed-build review boundary.' "$runner_doc"
require_contains 'Model-1 import and mixed-build review boundary.' "$runner_status"
require_contains 'LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY_STATUS.md' "$status_index"
require_contains 'Separate-Build Platform Integration Review Boundary' "$docs_hub"
require_contains 'separate-build platform integration review boundary](docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md)' "$root_readme"
require_contains 'Latest Latticra separate-build platform integration review boundary note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra separate-build platform integration review boundary note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra separate-build platform integration review boundary note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra separate-build platform integration review boundary note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Model-1 import and mixed-build review boundary.' "$current_status"
require_contains 'Model-1 import and mixed-build review boundary.' "$upcoming_work"
require_contains 'latticra-separate-build-platform-integration-review-boundary:' "$makefile"
require_contains 'sh ./scripts/test-latticra-separate-build-platform-integration-review-boundary.sh' "$makefile"
require_contains 'latticra-separate-build-platform-integration-review-boundary:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-separate-build-platform-integration-review-boundary.sh' "$quality_guard"
require_contains 'Run Latticra separate-build platform integration review boundary guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-separate-build-platform-integration-review-boundary.sh' "$workflow"

printf 'latticra_separate_build_platform_integration_review_boundary: ok\n'

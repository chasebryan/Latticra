# Latticra Separate-Build Platform Integration Review Boundary

Status: no-effect separate-build platform integration review boundary
Date: 2026-05-29 CDT
Scope: fourth transition-intake prerequisite before Model-1 bridge protocol, Model-1 import, mixed-build, or effect-runner acceptance work.

## Purpose

This record defines the review boundary for the separate-build platform lane observed in the local `~/Latticra` worktree.

The current checkpoint remains `v0.3.0edge`: bounded local operator effects are visible through status surfaces, but root, network, USB, QEMU, package-manager, kernel, service, boot, production-readiness, distribution-readiness, unrestricted host authority, and runtime authority remain closed.

This boundary records what was observed in the separate-build worktree without importing files, running its build scripts, accepting artifacts, or promoting any build profile.

## Observed Source Inputs

```text
transition_source_worktree=/Users/chasebryan/Latticra
transition_source_branch=build/separate-build-system-and-alignment-fixes
transition_source_role=experimental-effect-substrate-and-model1-bridge-lane
source_worktree_dirty=1
build_separate_tree_observed=1
build_separate_script_observed=scripts/build-separate.sh
build_separate_artifacts_observed=1
build_separate_artifacts_accepted=0
report_only_profile_observed=1
effect_enabled_profile_observed=1
effect_enabled_profile_accepted=0
model1_tree_observed=1
model1_import_accepted=0
```

## Boundary Checkpoint

```text
latticra_separate_build_platform_integration_review_boundary_present=1
separate_build_platform_review_boundary_intake_satisfied=1
separate_build_platform_review_boundary_version=1
edge_checkpoint=v0.3.0edge
transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md
effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md
effect_allowlist_build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md
effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md
allowed_review_modes=static-source-review,artifact-inventory-review,no-effect-report
blocked_review_modes=build-execution,artifact-import,artifact-copy,mixed-build,model1-bridge,runner-execution,production
source_branch_review_required=1
build_layout_review_required=1
artifact_boundary_review_required=1
platform_assumption_review_required=1
non_claim_evidence_required=1
deny_by_default=1
build_separate_execution_performed=0
source_import_performed=0
artifact_copy_performed=0
artifact_acceptance_allowed=0
mixed_build_promotion_accepted=0
effect_enabled_profile_accepted=0
model1_bridge_contract_intake_satisfied=1
model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md
model1_import_review_satisfied=0
effect_runner_acceptance_allowed=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
runtime_authority_granted=0
production_readiness_claim=0
distribution_readiness_claim=0
```

## Required Separate-Build Review Fields

Every future separate-build integration review must expose these fields before review:

```text
separate_build_review_id
separate_build_review_version
source_worktree
source_branch
source_revision
source_dirty_state
build_script_reference
build_profile_reference
artifact_inventory_reference
model1_tree_reference
effect_runner_reference
platform_assumptions
artifact_acceptance_decision
import_decision
promotion_decision
non_claims
```

Initial review defaults remain conservative:

```text
source_dirty_state=dirty|clean|unknown
build_profile_reference=report-only|effect-enabled|effect-enabled-model1|unknown
artifact_acceptance_decision=not-accepted
import_decision=not-imported
promotion_decision=not-promoted
```

Any separate-build review with missing source branch, missing build layout, missing artifact inventory boundary, missing platform assumption record, or effect-capable build promotion is denied.

## Intake Satisfaction

This record satisfies only the fourth transition-intake boundary:

```text
effect_contract_schema_intake_satisfied=1
effect_evidence_record_contract_intake_satisfied=1
effect_allowlist_contract_intake_satisfied=1
build_profile_boundary_intake_satisfied=1
effect_runner_review_boundary_intake_satisfied=1
separate_build_platform_review_boundary_intake_satisfied=1
model1_bridge_contract_intake_satisfied=0
model1_import_review_satisfied=0
```

No separate-build artifact, Model-1 tree, effect-enabled profile, or runner is accepted because this boundary exists.

## Next Recommended Lane

```text
Model-1 import and mixed-build review boundary.
```

That lane should remain no-effect until it proves import scope, source provenance, mixed-build layout, target identity, bridge protocol compatibility, and non-claim evidence without launching Model-1 or dispatching effects.

## Validation

This boundary is guarded by:

```sh
sh scripts/test-latticra-separate-build-platform-integration-review-boundary.sh
```

Expected output:

```text
latticra_separate_build_platform_integration_review_boundary: ok
```

## Non-Claims

This record is not build execution, artifact import, artifact acceptance, command execution, file mutation, effect execution, runner acceptance, runner dispatch, Model-1 bridge acceptance, Model-1 import acceptance, mixed-build readiness, build-profile promotion, host mutation, network behavior, production installer readiness, production runtime readiness, production security hardening, operating-system completeness, or distribution readiness.

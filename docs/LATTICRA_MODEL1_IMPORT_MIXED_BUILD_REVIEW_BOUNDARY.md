# Latticra Model-1 Import and Mixed-Build Review Boundary

Status: no-effect Model-1 import and mixed-build review boundary
Date: 2026-05-29 CDT
Scope: sixth transition-intake prerequisite before guarded Model-1 effect demonstration or capability-promotion review.

## Purpose

This record defines the review boundary for future Model-1 import and mixed-build work.

The current checkpoint remains `v0.3.0edge`: bounded local operator effects are visible through status surfaces, but root, network, USB, QEMU, package-manager, kernel, service, boot, production-readiness, distribution-readiness, unrestricted host authority, and runtime authority remain closed.

This boundary is not an import. It defines the import-scope, source-provenance, mixed-build-layout, target-identity, bridge-protocol-compatibility, target-evidence, and non-claim evidence that must exist before any Model-1 import, mixed-build promotion, bridge execution, or guarded effect demonstration can be reviewed.

## Boundary Checkpoint

```text
latticra_model1_import_mixed_build_review_boundary_present=1
model1_import_mixed_build_review_boundary_intake_satisfied=1
model1_import_mixed_build_review_boundary_version=1
edge_checkpoint=v0.3.0edge
transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md
effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md
effect_allowlist_build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md
effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md
separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md
model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md
review_source=prior-separate-build-boundary-and-bridge-protocol-contract
allowed_review_modes=static-import-scope-review,mixed-build-layout-review,bridge-protocol-compatibility-review,no-effect-evidence-review
blocked_review_modes=model1-launch,model1-import,artifact-import,artifact-copy,mixed-build-promotion,bridge-execution,runner-execution,production
import_scope_review_required=1
source_provenance_review_required=1
mixed_build_layout_review_required=1
target_identity_review_required=1
bridge_protocol_compatibility_required=1
target_evidence_record_required=1
non_claim_evidence_required=1
deny_by_default=1
model1_import_review_boundary_satisfied=1
model1_import_review_satisfied=0
model1_import_accepted=0
mixed_build_promotion_accepted=0
model1_bridge_execution_performed=0
model1_process_launch_performed=0
source_import_performed=0
artifact_copy_performed=0
artifact_acceptance_allowed=0
effect_runner_acceptance_allowed=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
network_performed=0
host_mutation_performed=0
runtime_authority_granted=0
production_readiness_claim=0
distribution_readiness_claim=0
guarded_model1_effect_demonstration_required=1
guarded_model1_effect_demonstration_satisfied=0
```

## Required Import Review Fields

Every future Model-1 import review must expose these fields before review:

```text
model1_import_review_id
model1_import_review_version
source_worktree
source_branch
source_revision
source_dirty_state
model1_tree_reference
import_scope
import_decision
target_identity
target_revision
mixed_build_layout_reference
bridge_protocol_reference
compatibility_decision
artifact_inventory_reference
evidence_record_reference
non_claims
```

Initial import-review defaults remain conservative:

```text
import_scope=not-imported|static-review-only
import_decision=not-imported
target_identity=model1-unaccepted
target_revision=unaccepted
compatibility_decision=not-reviewed|requires-future-gate
```

## Required Mixed-Build Review Fields

Every future mixed-build review must expose these fields before review:

```text
mixed_build_review_id
build_profile_reference
report_only_profile_reference
effect_enabled_profile_reference
artifact_acceptance_decision
promotion_decision
runner_acceptance_decision
bridge_execution_decision
operator_workflow_reference
target_evidence_fields
redaction_status
```

Initial mixed-build defaults remain conservative:

```text
artifact_acceptance_decision=not-accepted
promotion_decision=not-promoted
runner_acceptance_decision=not-accepted
bridge_execution_decision=not-executed
redaction_status=required
```

Any review with missing import scope, missing source provenance, missing mixed-build layout, missing target identity, missing bridge-protocol compatibility, missing target evidence, or effect-performing promotion is denied.

## Intake Satisfaction

This record satisfies only the sixth transition-intake boundary:

```text
effect_contract_schema_intake_satisfied=1
effect_evidence_record_contract_intake_satisfied=1
effect_allowlist_contract_intake_satisfied=1
build_profile_boundary_intake_satisfied=1
effect_runner_review_boundary_intake_satisfied=1
separate_build_platform_review_boundary_intake_satisfied=1
model1_bridge_contract_intake_satisfied=1
model1_import_mixed_build_review_boundary_intake_satisfied=1
guarded_model1_effect_demonstration_satisfied=0
```

No Model-1 import, mixed build, artifact acceptance, bridge execution, runner acceptance, or effect dispatch is accepted because this boundary exists.

## Next Recommended Lane

```text
Guarded Model-1 effect demonstration evidence boundary.
```

That lane should remain no-effect until it proves request contract, bridge request and response evidence, deny-by-default behavior, operator workflow, target evidence, redaction, and non-claim review without launching Model-1 or dispatching effects.

## Validation

This boundary is guarded by:

```sh
sh scripts/test-latticra-model1-import-mixed-build-review-boundary.sh
```

Expected output:

```text
latticra_model1_import_mixed_build_review_boundary: ok
```

## Non-Claims

This record is not Model-1 launch, Model-1 import acceptance, mixed-build readiness, bridge execution, effect execution, command execution, file mutation, runner acceptance, runner dispatch, build-profile promotion, host mutation, network behavior, production installer readiness, production runtime readiness, production security hardening, operating-system completeness, or distribution readiness.

# Latticra Effect Allowlist and Build-Profile Boundary Contract

Status: no-effect allowlist and build-profile boundary contract
Date: 2026-05-29 CDT
Scope: second transition-intake prerequisite before effect-runner, build-profile, or Model-1 bridge promotion.

## Purpose

This record defines the allowlist and build-profile boundary that future effect-capable work must satisfy before implementation review.

The current checkpoint remains `v0.3.0edge`: bounded local operator effects are visible through status surfaces, but root, network, USB, QEMU, package-manager, kernel, service, boot, production-readiness, distribution-readiness, unrestricted host authority, and runtime authority remain closed.

The boundary below is intentionally product-shaped: future effect work must name an operator-usable workflow and the evidence it would produce. A contract that cannot point to something a person can actually do remains blocked, even if its internal schema is coherent.

This record does not execute effects, accept an effect runner, promote a build profile, import Model-1 behavior, or grant authority.

## Boundary Checkpoint

```text
latticra_effect_allowlist_build_profile_boundary_present=1
effect_allowlist_contract_intake_satisfied=1
build_profile_boundary_intake_satisfied=1
effect_allowlist_boundary_version=1
build_profile_boundary_version=1
edge_checkpoint=v0.3.0edge
transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md
effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md
effect_status_surface_reference=docs/status/LATTICRA_EFFECT_STATUS_SURFACE_STATUS.md
allowed_initial_effect_classes=none,read
blocked_effect_classes=local_mutation,host_mutation,network,hardware,boot,recovery,external,unknown
allowed_build_profiles=metadata-only
blocked_build_profiles=effect-runner,host-profile,mixed-build,model1-bridge,production
operator_usable_workflow_required=1
operator_workflow_reference_required=1
deny_by_default=1
effect_runner_acceptance_allowed=0
build_profile_promotion_accepted=0
model1_bridge_contract_intake_satisfied=0
model1_import_review_satisfied=0
promotion_allowed_by_allowlist_boundary_alone=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
runtime_authority_granted=0
production_readiness_claim=0
distribution_readiness_claim=0
```

## Required Allowlist Fields

Every future effect allowlist record must expose these fields before review:

```text
allowlist_id
allowlist_version
allowed_effect
allowed_scope
allowed_target_pattern
denied_effect_classes
operator_usable_workflow_reference
contract_schema_reference
evidence_record_reference
build_profile_reference
model1_bridge_mode
decision_default
non_claims
```

Initial allowed values remain small:

```text
allowed_effect=none|read
allowed_scope=metadata-only|approved-local-state
allowed_target_pattern=none|repo-status|operator-selected-output
model1_bridge_mode=none|contract-required
decision_default=deny
```

Any allowlist with an unknown, ambiguous, external, host-mutating, network, boot, recovery, hardware, or unrestricted local mutation effect is denied.

## Required Build-Profile Fields

Every future build-profile boundary record must expose these fields before review:

```text
build_profile_id
build_profile_version
build_profile_kind
profile_authority
source_revision
allowed_effect_classes
denied_operations
operator_usable_workflow_reference
effect_runner_mode
model1_bridge_mode
local_output_scope
evidence_record_required
promotion_allowed
non_claims
```

Initial build-profile defaults remain conservative:

```text
build_profile_kind=metadata-only
profile_authority=none
allowed_effect_classes=none,read
denied_operations=command_execution,file_mutation,network,host_mutation,root,usb,qemu,package_manager,kernel,service,boot
effect_runner_mode=unaccepted
model1_bridge_mode=none
local_output_scope=none|operator-selected-output
evidence_record_required=1
promotion_allowed=0
```

## Operator-Usable Workflow Boundary

Future promotion review must include an operator workflow record with these fields:

```text
workflow_id
workflow_user
workflow_goal
workflow_entrypoint
workflow_inputs
workflow_outputs
operator_visible_result
evidence_record_required
promotion_requested
```

No effect-capable lane can move past boundary review if `workflow_goal`, `workflow_entrypoint`, or `operator_visible_result` is absent.

The first accepted workflow should be narrow enough to run locally under Latticra contracts, visible enough for a reviewer to repeat, and small enough to reject without disturbing unrelated authority surfaces.

## Intake Satisfaction

This record satisfies only the second transition-intake prerequisite:

```text
effect_contract_schema_intake_satisfied=1
effect_evidence_record_contract_intake_satisfied=1
effect_allowlist_contract_intake_satisfied=1
build_profile_boundary_intake_satisfied=1
model1_bridge_contract_intake_satisfied=0
model1_import_review_satisfied=0
```

No later item is accepted because this boundary exists.

## Next Recommended Lane

```text
Model-1 import and mixed-build review boundary.
```

That lane should remain no-effect until it defines the bridge message format, trace correlation, authority handoff, target evidence fields, denial behavior, and non-claim boundary without launching Model-1 or dispatching effects.

## Validation

This boundary is guarded by:

```sh
sh scripts/test-latticra-effect-allowlist-build-profile-boundary.sh
```

Expected output:

```text
latticra_effect_allowlist_build_profile_boundary: ok
```

## Non-Claims

This record is not effect execution, command execution, file mutation, Model-1 bridge acceptance, Model-1 import acceptance, mixed-build readiness, build-profile promotion, effect-runner acceptance, host mutation, network behavior, production installer readiness, production runtime readiness, production security hardening, operating-system completeness, or distribution readiness.

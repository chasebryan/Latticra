# Latticra Effect Substrate Transition Intake

Status: no-effect transition intake contract
Date: 2026-05-29 CDT
Scope: coordination contract for bringing the effect-substrate and Model-1 bridge work toward the main Latticra status spine.

## Purpose

This record defines how the active effect-substrate work may be reviewed for future intake.

The current public checkpoint is `v0.3.0edge`: bounded local operator effects are visible through `latticra --effect-status`, while root, network, USB, QEMU, package-manager, kernel, service, boot, production-readiness, distribution-readiness, and unrestricted host authority remain closed.

The incoming effect-substrate direction is real, but it must land through explicit gates. The project should not treat a demo runner, local build profile, Model-1 import, or branch-local effect prototype as production authority.

## Intake Fields

```text
latticra_effect_substrate_transition_intake_present=1
transition_source_branch=build/separate-build-system-and-alignment-fixes
transition_source_role=experimental-effect-substrate-and-model1-bridge-lane
edge_checkpoint=v0.3.0edge
effect_status_surface_required=1
effect_contract_schema_required=1
effect_evidence_record_contract_required=1
effect_contract_schema_intake_satisfied=1
effect_evidence_record_contract_intake_satisfied=1
effect_allowlist_contract_required=1
effect_allowlist_contract_intake_satisfied=1
effect_allowlist_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md
build_profile_boundary_required=1
build_profile_boundary_intake_satisfied=1
build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md
effect_runner_review_boundary_required=1
effect_runner_review_boundary_intake_satisfied=1
effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md
model1_bridge_contract_required=1
model1_bridge_contract_intake_satisfied=1
model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md
model1_import_review_required=1
model1_import_review_satisfied=0
separate_build_platform_review_required=1
separate_build_platform_review_boundary_intake_satisfied=1
separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md
operator_demo_non_claim_review_required=1
operator_usable_workflow_required=1
operator_workflow_reference_required=1
promotion_allowed_by_allowlist_boundary_alone=0
effect_runner_acceptance_allowed=0
effect_runner_accepted=0
runner_dispatch_performed=0
build_profile_promotion_accepted=0
completion_estimate_review_required_for_capability_promotion=1
production_readiness_claim_allowed=0
unrestricted_host_authority_allowed=0
```

## Required Order

Future intake should proceed in this order:

```text
1. effect contract schema and evidence record contract - satisfied
2. allowlist and build-profile boundary review - satisfied
3. effect runner implementation review boundary - satisfied
4. separate-build platform integration review boundary - satisfied
5. Model-1 bridge protocol contract - satisfied
6. Model-1 import and mixed-build review
7. guarded Model-1 effect demonstration
```

No later item should be treated as accepted just because an earlier item exists.

## Authority Boundary

This intake record preserves:

```text
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
model1_bridge_execution_performed=0
model1_process_launch_performed=0
effect_runner_accepted=0
runner_dispatch_performed=0
build_separate_execution_performed=0
source_import_performed=0
artifact_acceptance_allowed=0
model1_import_accepted=0
build_profile_promotion_accepted=0
root_authority_allowed=0
network_allowed=0
usb_write_allowed=0
qemu_run_allowed=0
package_manager_operation_allowed=0
kernel_operation_allowed=0
service_operation_allowed=0
boot_operation_allowed=0
production_readiness_claim=0
distribution_readiness_claim=0
runtime_authority_granted=0
```

## Next Recommended Slice

```text
Model-1 import and mixed-build review boundary.
```

That next slice should remain no-effect until it proves import scope, source provenance, mixed-build layout, target identity, bridge protocol compatibility, and non-claim evidence without launching Model-1 or dispatching effects.

## Validation

This intake is guarded by:

```sh
sh scripts/test-latticra-effect-substrate-transition-intake.sh
```

Expected output:

```text
latticra_effect_substrate_transition_intake: ok
```

## Non-Claims

This record is not effect execution, command execution, file mutation, Model-1 bridge acceptance, Model-1 import acceptance, mixed-build readiness, build-profile promotion, host mutation, production installer readiness, production runtime readiness, production security hardening, operating-system completeness, or distribution readiness.

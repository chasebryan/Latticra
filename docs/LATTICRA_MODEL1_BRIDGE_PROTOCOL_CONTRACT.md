# Latticra Model-1 Bridge Protocol Contract

Status: no-effect Model-1 bridge protocol contract
Date: 2026-05-29 CDT
Scope: fifth transition-intake prerequisite before Model-1 import, mixed-build review, or guarded Model-1 effect demonstration work.

## Purpose

This record defines the first protocol contract for a future Latticra Substrate to Model-1 bridge.

The current checkpoint remains `v0.3.0edge`: bounded local operator effects are visible through status surfaces, but root, network, USB, QEMU, package-manager, kernel, service, boot, production-readiness, distribution-readiness, unrestricted host authority, and runtime authority remain closed.

This protocol contract is not a bridge implementation. It defines the message fields, trace correlation, authority handoff, target evidence fields, denial behavior, and non-claim boundary that must exist before any Model-1 bridge implementation or import review can be accepted.

## Protocol Checkpoint

```text
latticra_model1_bridge_protocol_contract_present=1
model1_bridge_contract_intake_satisfied=1
model1_bridge_protocol_version=1
edge_checkpoint=v0.3.0edge
transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md
effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md
effect_allowlist_build_profile_boundary_reference=docs/LATTICRA_EFFECT_ALLOWLIST_BUILD_PROFILE_BOUNDARY_CONTRACT.md
effect_runner_review_boundary_reference=docs/LATTICRA_EFFECT_RUNNER_IMPLEMENTATION_REVIEW_BOUNDARY.md
separate_build_platform_review_boundary_reference=docs/LATTICRA_SEPARATE_BUILD_PLATFORM_INTEGRATION_REVIEW_BOUNDARY.md
allowed_initial_transports=stdio-json-lines,local-pipe
blocked_initial_transports=network-socket,ffi-shared-memory,unrestricted-shell,host-service,production-daemon
bridge_message_format_required=1
trace_correlation_required=1
authority_handoff_required=1
target_evidence_fields_required=1
denial_behavior_required=1
deny_by_default=1
model1_bridge_execution_performed=0
model1_process_launch_performed=0
model1_import_review_satisfied=0
model1_import_accepted=0
mixed_build_promotion_accepted=0
effect_runner_acceptance_allowed=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
runtime_authority_granted=0
production_readiness_claim=0
distribution_readiness_claim=0
```

## Required Bridge Request Fields

Every future bridge request must expose these fields before review:

```text
bridge_protocol_id
bridge_protocol_version
message_id
trace_id
contract_id
source_revision
request_family
requested_effect
allowed_effect
authority_decision_reference
allowlist_reference
build_profile_reference
operator_workflow_reference
target_identity
target_mode
transport_mode
payload_digest
evidence_record_required
non_claims
```

Initial request defaults remain conservative:

```text
target_identity=model1-unaccepted
target_mode=not-launched|contract-required
transport_mode=stdio-json-lines|local-pipe
requested_effect=none|read|local_mutation|host_mutation|network|hardware|boot|recovery|external|unknown
allowed_effect=none|read
evidence_record_required=1
```

Any bridge request with missing trace correlation, missing contract reference, missing authority decision, missing allowlist reference, missing build-profile reference, missing target evidence requirement, or effect-performing target mode is denied.

## Required Bridge Response Fields

Every future bridge response must expose these fields before review:

```text
message_id
trace_id
contract_id
target_identity
target_revision
target_decision
target_denial_reason
target_evidence_id
target_observation_digest
target_effect_performed
target_command_execution_performed
target_file_mutation_performed
target_network_performed
target_runtime_authority_granted
redaction_status
```

Initial response defaults:

```text
target_decision=not-launched|deny|requires-future-gate|unsupported
target_effect_performed=0
target_command_execution_performed=0
target_file_mutation_performed=0
target_network_performed=0
target_runtime_authority_granted=0
redaction_status=required
```

## Denial Behavior

The bridge protocol must deny by default:

```text
unknown_message_type -> deny
missing_trace_id -> deny
missing_contract_id -> deny
missing_authority_decision_reference -> deny
missing_allowlist_reference -> deny
missing_build_profile_reference -> deny
missing_target_evidence_fields -> deny
effect_performing_target_mode -> deny
unaccepted_model1_import -> deny
```

Operator confirmation cannot override denial in this protocol contract.

## Intake Satisfaction

This record satisfies only the fifth transition-intake boundary:

```text
effect_contract_schema_intake_satisfied=1
effect_evidence_record_contract_intake_satisfied=1
effect_allowlist_contract_intake_satisfied=1
build_profile_boundary_intake_satisfied=1
effect_runner_review_boundary_intake_satisfied=1
separate_build_platform_review_boundary_intake_satisfied=1
model1_bridge_contract_intake_satisfied=1
model1_import_review_satisfied=0
```

No Model-1 tree, mixed build, bridge execution, or effect dispatch is accepted because this protocol contract exists.

## Next Recommended Lane

```text
Model-1 import and mixed-build review boundary.
```

That lane should remain no-effect until it proves import scope, source provenance, mixed-build layout, target identity, bridge protocol compatibility, and non-claim evidence without launching Model-1 or dispatching effects.

## Validation

This protocol contract is guarded by:

```sh
sh scripts/test-latticra-model1-bridge-protocol-contract.sh
```

Expected output:

```text
latticra_model1_bridge_protocol_contract: ok
```

## Non-Claims

This record is not Model-1 launch, Model-1 import acceptance, mixed-build readiness, bridge execution, effect execution, command execution, file mutation, runner acceptance, runner dispatch, build-profile promotion, host mutation, network behavior, production installer readiness, production runtime readiness, production security hardening, operating-system completeness, or distribution readiness.

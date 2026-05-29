# Latticra Effect Contract Schema

Status: no-effect schema and evidence record contract
Date: 2026-05-29 CDT
Scope: required effect-contract and evidence-record fields before effect-runner, build-profile, or Model-1 bridge promotion.

## Purpose

This record defines the first required contract shape for future Latticra effect-capable work.

The current checkpoint remains `v0.3.0edge`: bounded local operator effects are visible through status surfaces, but root, network, USB, QEMU, package-manager, kernel, service, boot, production-readiness, distribution-readiness, unrestricted host authority, and runtime authority remain closed.

The schema below gives future effect-runner, build-profile, and Model-1 bridge work a stable review shape. It does not execute effects, accept a runner, promote a build profile, import Model-1 behavior, or grant authority.

## Schema Checkpoint

```text
latticra_effect_contract_schema_present=1
effect_contract_schema_version=1
effect_evidence_record_contract_present=1
effect_evidence_record_schema_version=1
edge_checkpoint=v0.3.0edge
transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md
effect_status_surface_reference=docs/status/LATTICRA_EFFECT_STATUS_SURFACE_STATUS.md
allowed_initial_effect_classes=none,read
blocked_effect_classes=local_mutation,host_mutation,network,hardware,boot,recovery,external,unknown
deny_by_default=1
effect_runner_acceptance_allowed=0
build_profile_promotion_accepted=0
model1_bridge_execution_performed=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
runtime_authority_granted=0
production_readiness_claim=0
distribution_readiness_claim=0
```

## Required Effect Contract Fields

Every future effect contract must expose these fields before review:

```text
contract_id
contract_version
contract_subject
request_family
requested_effect
allowed_effect
effect_scope
effect_target
source_identity
source_revision
operator_intent
authority_reference
allowlist_reference
build_profile
model1_bridge_mode
evidence_record_required
deny_by_default
non_claims
```

Initial allowed values are intentionally small:

```text
requested_effect=none|read|local_mutation|host_mutation|network|hardware|boot|recovery|external|unknown
allowed_effect=none|read
effect_scope=metadata-only|approved-local-state
build_profile=unaccepted|metadata-only
model1_bridge_mode=none|contract-required
evidence_record_required=1
deny_by_default=1
```

Any contract with an unknown, ambiguous, or unclassified effect is denied.

## Required Evidence Record Fields

Every future policy decision must be able to produce an evidence record with these fields:

```text
evidence_record_id
contract_id
trace_id
source_revision
request_hash
decision_timestamp
decision_result
denial_reason
pre_execution_boundary
post_execution_result
stdout_digest
stderr_digest
artifact_digest
redaction_status
secret_capture_performed
effect_execution_performed
command_execution_performed
file_mutation_performed
network_performed
host_mutation_performed
runtime_authority_granted
```

Initial evidence defaults remain conservative:

```text
decision_result=allow-no-effect|allow-read-report|deny|requires-future-gate|unsupported
secret_capture_performed=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
network_performed=0
host_mutation_performed=0
runtime_authority_granted=0
```

## Intake Satisfaction

This schema satisfies only the first transition-intake prerequisite:

```text
effect_contract_schema_intake_satisfied=1
effect_evidence_record_contract_intake_satisfied=1
effect_allowlist_contract_intake_satisfied=0
build_profile_boundary_intake_satisfied=0
model1_bridge_contract_intake_satisfied=0
model1_import_review_satisfied=0
```

No later item is accepted because this schema exists.

## Next Recommended Lane

```text
Model-1 import and mixed-build review boundary.
```

That lane should remain no-effect until it defines the bridge message format, trace correlation, authority handoff, target evidence fields, denial behavior, and non-claim boundary without launching Model-1 or dispatching effects.

## Validation

This schema is guarded by:

```sh
sh scripts/test-latticra-effect-contract-schema.sh
```

Expected output:

```text
latticra_effect_contract_schema: ok
```

## Non-Claims

This record is not effect execution, command execution, file mutation, Model-1 bridge acceptance, Model-1 import acceptance, mixed-build readiness, build-profile promotion, host mutation, network behavior, production installer readiness, production runtime readiness, production security hardening, operating-system completeness, or distribution readiness.

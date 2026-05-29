# Latticra Effect Contract Schema Status

Status: no-effect schema status
Date: 2026-05-29 CDT
Scope: status checkpoint for the effect contract schema and evidence record contract.

## Summary

Latticra now has a guarded effect-contract schema and evidence-record contract for future effect-substrate intake.

The status meaning is narrow: the first transition-intake prerequisite is defined, and future effect-runner, build-profile, and Model-1 bridge work now has required fields to satisfy before review. This does not accept effect execution, command execution, file mutation, Model-1 bridge execution, or production readiness.

## Status Fields

```text
latticra_effect_contract_schema_present=1
latticra_effect_contract_schema_guard_present=1
effect_contract_schema_version=1
effect_evidence_record_contract_present=1
effect_evidence_record_schema_version=1
edge_checkpoint=v0.3.0edge
transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md
effect_status_surface_reference=docs/status/LATTICRA_EFFECT_STATUS_SURFACE_STATUS.md
allowed_initial_effect_classes=none,read
blocked_effect_classes=local_mutation,host_mutation,network,hardware,boot,recovery,external,unknown
deny_by_default=1
effect_contract_schema_intake_satisfied=1
effect_evidence_record_contract_intake_satisfied=1
effect_allowlist_contract_intake_satisfied=0
build_profile_boundary_intake_satisfied=0
model1_bridge_contract_intake_satisfied=0
model1_import_review_satisfied=0
effect_runner_acceptance_allowed=0
build_profile_promotion_accepted=0
model1_bridge_execution_performed=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
network_performed=0
host_mutation_performed=0
runtime_authority_granted=0
production_readiness_claim=0
distribution_readiness_claim=0
```

## Required Field Coverage

```text
required_effect_contract_fields=contract_id,contract_version,contract_subject,request_family,requested_effect,allowed_effect,effect_scope,effect_target,source_identity,source_revision,operator_intent,authority_reference,allowlist_reference,build_profile,model1_bridge_mode,evidence_record_required,deny_by_default,non_claims
required_evidence_record_fields=evidence_record_id,contract_id,trace_id,source_revision,request_hash,decision_timestamp,decision_result,denial_reason,pre_execution_boundary,post_execution_result,stdout_digest,stderr_digest,artifact_digest,redaction_status,secret_capture_performed,effect_execution_performed,command_execution_performed,file_mutation_performed,network_performed,host_mutation_performed,runtime_authority_granted
```

## Public Meaning

The careful public meaning is:

```text
Latticra has a no-effect schema for future effect contracts and effect evidence records.
```

That does not mean Latticra has accepted effect execution, command execution, host mutation, network behavior, Model-1 bridge execution, mixed-build readiness, production runtime behavior, production installer readiness, or production security capability.

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-latticra-effect-contract-schema.sh
```

Expected output:

```text
latticra_effect_contract_schema: ok
```

## Next Recommended Lane

```text
Model-1 import and mixed-build review boundary.
```

## Non-Claims

This status record is not effect execution, command execution, file mutation, Model-1 bridge acceptance, Model-1 import acceptance, mixed-build readiness, build-profile promotion, host mutation, network behavior, production installer readiness, production runtime readiness, production security hardening, operating-system completeness, or distribution readiness.

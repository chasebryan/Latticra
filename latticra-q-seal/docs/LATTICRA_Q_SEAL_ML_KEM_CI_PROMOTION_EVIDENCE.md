# Latticra Q-Seal ML-KEM CI Promotion Evidence

Status: fail-closed CI promotion readiness slice
Date: 2026-05-27
Scope: CI and release-claim promotion evidence before ML-KEM implementation promotion.

This slice records the CI promotion gate that must be satisfied before any clean-room ML-KEM primitive implementation can move from design frame to implementation candidate. It keeps vector execution, ACVP submission, implementation promotion, release claims, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_ci_promotion_evidence.h
latticra-q-seal/src/q_seal_ml_kem_ci_promotion_evidence.c
latticra-q-seal/tests/q_seal_ml_kem_ci_promotion_evidence_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
latticra-q-seal/evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_EVIDENCE.md
scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
```

## Current Fields

```text
ml_kem_ci_promotion_evidence_present=1
formal_title=Latticra Q-Seal ML-KEM CI Promotion Evidence
promotion_profile=latticra-q-seal-ml-kem-ci-promotion-evidence/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203-and-SP-800-227
promotion_scope=ML-KEM-evidence-gates-before-implementation-promotion
promotion_state=ci-promotion-blocked
ssdf_secure_build_gate_recorded=1
fips_203_parameter_gate_bound=1
sp_800_227_kem_usage_gate_bound=1
make_quality_security_standards_bound=1
local_wrapper_scripts_recorded=1
qseal_subsystem_scripts_recorded=1
readiness_gate_bound=1
implementation_binding_manifest_required=1
implementation_binding_manifest_bound=1
replay_transcript_gate_bound=1
acvp_verdict_receipt_gate_bound=1
validation_claim_gate_bound=1
module_boundary_gate_bound=1
kat_acvp_gate_passing_recorded=0
constant_time_gate_passing_recorded=0
memory_safety_gate_passing_recorded=0
side_channel_gate_passing_recorded=0
negative_test_gate_passing_recorded=0
provider_differential_gate_passing_recorded=0
implementation_binding_ci_result_recorded=0
promotion_workflow_recorded=0
release_claim_gate_recorded=0
signed_artifact_receipt_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_promotion_items_total=23
required_promotion_items_satisfied=13
blocked_reason=ci-vector-acvp-verdict-validation-claim-module-boundary-constant-time-memory-side-channel-provider-binding-workflow-release-evidence-missing
status=ml-kem-ci-promotion-evidence-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
```

Expected output:

```text
latticra q-seal ml-kem ci promotion evidence invariants: ok
latticra q-seal ml-kem ci promotion evidence: ok
```

# Latticra Q-Seal ML-KEM Review Disposition Ledger

Status: fail-closed review disposition fixture
Date: 2026-05-27
Scope: reviewer finding disposition and approval receipt records before implementation promotion.

This slice records the disposition ledger shape that future clean-room ML-KEM review evidence must satisfy after code-owner review and source digest receipts exist. It keeps reviewer approval, finding closure, implementation promotion, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled. The reviewer identity import fixture is recorded in `LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_FIXTURE.md`, and the reviewer role-mapping fixture is recorded in `LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md`.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_review_disposition_ledger.h
latticra-q-seal/src/q_seal_ml_kem_review_disposition_ledger.c
latticra-q-seal/tests/q_seal_ml_kem_review_disposition_ledger_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
latticra-q-seal/evidence/ML_KEM_REVIEW_DISPOSITION_LEDGER.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEW_DISPOSITION_LEDGER.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md
scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
```

## Current Fields

```text
ml_kem_review_disposition_ledger_present=1
formal_title=Latticra Q-Seal ML-KEM Review Disposition Ledger
disposition_profile=latticra-q-seal-ml-kem-review-disposition-ledger/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
disposition_scope=ML-KEM-review-finding-disposition-before-promotion
disposition_state=review-disposition-fixture-blocked
review_disposition_ledger_present=1
fips_203_algorithm_bound=1
ssdf_review_practice_bound=1
clean_room_review_policy_recorded=1
code_owner_review_gate_bound=1
source_digest_receipt_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
dual_reviewer_disposition_required=1
cryptography_disposition_required=1
security_disposition_required=1
standards_traceability_disposition_required=1
side_channel_disposition_required=1
source_digest_disposition_required=1
finding_severity_taxonomy_recorded=1
rejection_disposition_policy_recorded=1
approval_receipt_required=1
reviewer_identity_disposition_recorded=0
code_owner_disposition_recorded=0
cryptography_disposition_recorded=0
security_disposition_recorded=0
standards_traceability_disposition_recorded=0
side_channel_disposition_recorded=0
source_digest_disposition_recorded=0
blocking_findings_closed=0
approval_receipt_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_disposition_items_total=26
required_disposition_items_satisfied=17
status=ml-kem-review-disposition-ledger-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
sh scripts/test-latticra-q-seal-ml-kem-review-disposition-ledger.sh
```

Expected output:

```text
latticra q-seal ml-kem review disposition ledger invariants: ok
latticra q-seal ml-kem review disposition ledger: ok
```

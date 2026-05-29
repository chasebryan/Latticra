# Latticra Q-Seal ML-KEM Reviewer Identity Fixture

Status: fail-closed reviewer identity import fixture
Date: 2026-05-27
Scope: reviewer identity, role mapping, independence attestation, and approval authority records.

This slice records the reviewer identity import fixture that future clean-room ML-KEM review evidence must satisfy before implementation promotion. It keeps reviewer identity import, reviewer approval, approval authority, implementation promotion, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled. The downstream reviewer role-mapping fixture is recorded in `LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md`.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_reviewer_identity_fixture.h
latticra-q-seal/src/q_seal_ml_kem_reviewer_identity_fixture.c
latticra-q-seal/tests/q_seal_ml_kem_reviewer_identity_fixture_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
latticra-q-seal/evidence/ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_IDENTITY_FIXTURE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md
scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
```

## Current Fields

```text
ml_kem_reviewer_identity_fixture_present=1
formal_title=Latticra Q-Seal ML-KEM Reviewer Identity Fixture
identity_profile=latticra-q-seal-ml-kem-reviewer-identity-fixture/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
identity_scope=ML-KEM-reviewer-identity-import-before-promotion
identity_state=reviewer-identity-import-fixture-blocked
reviewer_identity_fixture_present=1
fips_203_algorithm_bound=1
ssdf_review_practice_bound=1
clean_room_review_policy_recorded=1
code_owner_review_gate_bound=1
review_disposition_ledger_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
dual_reviewer_identity_required=1
cryptography_reviewer_identity_required=1
security_reviewer_identity_required=1
code_owner_identity_required=1
reviewer_independence_required=1
identity_schema_recorded=1
identity_import_template_recorded=1
pii_minimization_policy_recorded=1
reviewer_identities_imported=0
cryptography_reviewer_identity_recorded=0
security_reviewer_identity_recorded=0
code_owner_identity_recorded=0
independence_attestation_recorded=0
identity_import_reviewed=0
approval_authority_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_identity_items_total=23
required_identity_items_satisfied=16
status=ml-kem-reviewer-identity-fixture-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
sh scripts/test-latticra-q-seal-ml-kem-reviewer-identity-fixture.sh
```

Expected output:

```text
latticra q-seal ml-kem reviewer identity fixture invariants: ok
latticra q-seal ml-kem reviewer identity fixture: ok
```

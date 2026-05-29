# Latticra Q-Seal ML-KEM Reviewer Role Mapping

Status: fail-closed reviewer role-mapping fixture
Date: 2026-05-27
Scope: reviewer role mapping, separation, and approval authority before implementation promotion.

This slice records the reviewer role-mapping fixture that future clean-room ML-KEM review evidence must satisfy after reviewer identity import exists. It keeps reviewer identity import, role-mapping import, reviewer approval, approval authority, implementation promotion, operation execution, production crypto claims, FIPS claims, network behavior, host mutation, and runtime authority disabled.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_reviewer_role_mapping.h
latticra-q-seal/src/q_seal_ml_kem_reviewer_role_mapping.c
latticra-q-seal/tests/q_seal_ml_kem_reviewer_role_mapping_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
latticra-q-seal/evidence/ML_KEM_REVIEWER_ROLE_MAPPING.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_REVIEWER_ROLE_MAPPING.md
scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
```

## Current Fields

```text
ml_kem_reviewer_role_mapping_present=1
formal_title=Latticra Q-Seal ML-KEM Reviewer Role Mapping
mapping_profile=latticra-q-seal-ml-kem-reviewer-role-mapping/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
mapping_scope=ML-KEM-reviewer-role-mapping-before-promotion
mapping_state=reviewer-role-mapping-fixture-blocked
reviewer_role_mapping_present=1
fips_203_algorithm_bound=1
ssdf_review_practice_bound=1
clean_room_review_policy_recorded=1
code_owner_review_gate_bound=1
review_disposition_ledger_bound=1
reviewer_identity_fixture_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
role_schema_recorded=1
cryptography_role_required=1
security_role_required=1
code_owner_role_required=1
standards_traceability_role_required=1
side_channel_role_required=1
source_digest_role_required=1
dual_reviewer_separation_required=1
conflict_of_interest_policy_recorded=1
pii_minimization_policy_bound=1
approval_authority_mapping_required=1
reviewer_identities_imported=0
role_mapping_records_imported=0
cryptography_role_mapped=0
security_role_mapped=0
code_owner_role_mapped=0
standards_traceability_role_mapped=0
side_channel_role_mapped=0
source_digest_role_mapped=0
separation_review_recorded=0
approval_authority_mapped=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_role_mapping_items_total=30
required_role_mapping_items_satisfied=20
status=ml-kem-reviewer-role-mapping-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
sh scripts/test-latticra-q-seal-ml-kem-reviewer-role-mapping.sh
```

Expected output:

```text
latticra q-seal ml-kem reviewer role mapping invariants: ok
latticra q-seal ml-kem reviewer role mapping: ok
```

# Latticra Q-Seal ML-KEM Clean-Room Author Attestation Gate

Status: fail-closed clean-room author attestation slice
Date: 2026-05-27
Scope: per-file clean-room author attestation before ML-KEM source acceptance.

This slice records the author-attestation schema that future clean-room ML-KEM implementation files must satisfy before source acceptance can treat those files as implementation candidates. It binds SSDF provenance policy, per-file author columns, digest evidence, implementation traceability, code-owner review, review disposition, and reviewer role mapping. It does not create source files, import identities, record real author attestations, accept source author attestations, execute ML-KEM operations, emit shared secrets, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_clean_room_author_attestation_gate.h
latticra-q-seal/src/q_seal_ml_kem_clean_room_author_attestation_gate.c
latticra-q-seal/tests/q_seal_ml_kem_clean_room_author_attestation_gate_invariants.c
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-clean-room-author-attestation-gate.sh
latticra-q-seal/evidence/ML_KEM_CLEAN_ROOM_AUTHOR_ATTESTATION_GATE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_CLEAN_ROOM_AUTHOR_ATTESTATION_GATE.md
scripts/test-latticra-q-seal-ml-kem-clean-room-author-attestation-gate.sh
```

## Current Fields

```text
ml_kem_clean_room_author_attestation_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Clean-Room Author Attestation Gate
attestation_profile=latticra-q-seal-ml-kem-clean-room-author-attestation-gate/0.1
standards_basis=NIST-SP-800-218-SSDF,NIST-FIPS-203,NIST-SP-800-227
source_boundary=clean-room-no-apple-code
attestation_scope=ML-KEM-clean-room-author-attestation-before-source-acceptance
attestation_state=author-attestation-template-recorded-author-signoff-blocked
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
source_layout_bound=1
implementation_file_digest_plan_bound=1
implementation_traceability_matrix_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
receipt_replay_results_bound=1
fips_conformance_matrix_bound=1
sp800_227_usage_profile_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
ssdf_provenance_policy_bound=1
no_third_party_source_policy_recorded=1
author_attestation_schema_recorded=1
per_file_author_columns_recorded=1
review_independence_required=1
source_files_created=0
author_identity_imported=0
per_file_author_attestations_recorded=0
clean_room_attestation_reviewed=0
provenance_exception_reviewed=0
source_author_attestation_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_attestation_items_total=30
required_attestation_items_satisfied=24
blocked_reason=source-files-author-identity-per-file-attestations-attestation-review-provenance-review-and-acceptance-missing
status=ml-kem-clean-room-author-attestation-gate-blocked
```

## Attestation Schema

```text
attestation_id
normalized_repo_path
file_role
author_identity_reference
clean_room_source_basis
prohibited_source_confirmation
third_party_source_exception_id
fips_203_trace_reference
sp800_227_trace_reference
digest_row_reference
review_disposition_id
attestation_status
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-clean-room-author-attestation-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-clean-room-author-attestation-gate.sh
```

Expected output:

```text
latticra q-seal ml-kem clean-room author attestation gate invariants: ok
latticra q-seal ml-kem clean-room author attestation gate: ok
```

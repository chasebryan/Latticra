# Latticra Q-Seal ML-KEM Evidence Import Review Gate

This slice adds the fail-closed evidence import review gate for Latticra Q-Seal ML-KEM. It sits between the vector fixture digest ledger, receipt replay results, reviewer role mapping, and CI promotion evidence so imported evidence metadata cannot be mistaken for implementation readiness.

It records the evidence Q-Seal will require before accepting the pre-implementation import packet: an evidence import packet manifest, vector fixture digest rows, receipt replay transcripts, source digest receipts, parameter-set coverage, operation-family coverage, negative-case coverage, replay tamper evidence, reviewer role-map records, and review acceptance. It does not load vectors, submit ACVP sessions, promote implementation source, execute ML-KEM, claim production cryptography, claim FIPS validation, or grant runtime authority.

```text
evidence_import_review_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Evidence Import Review Gate
evidence_import_profile=latticra-q-seal-ml-kem-evidence-import-review-gate/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
evidence_import_scope=ML-KEM-evidence-import-review-before-implementation-or-promotion
evidence_import_state=evidence-import-review-recorded-import-evidence-missing
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
evidence_import_packet_manifest_bound=1
vector_fixture_digest_ledger_bound=1
receipt_replay_results_bound=1
reviewer_role_mapping_bound=1
reviewer_identity_fixture_bound=1
review_disposition_ledger_bound=1
source_digest_verification_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
clean_room_source_boundary_recorded=1
offline_evidence_intake_recorded=1
digest_algorithm_sha256_required=1
immutable_import_record_required=1
source_url_digest_size_license_required=1
parameter_set_coverage_required=1
operation_family_coverage_required=1
replay_transcript_required=1
tamper_replay_required=1
reviewer_role_import_required=1
dual_reviewer_separation_required=1
approval_authority_required=1
no_implicit_operation_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
fixture_digest_rows_imported=0
receipt_replay_transcripts_imported=0
reviewer_role_records_imported=0
source_digest_receipts_imported=0
parameter_set_coverage_recorded=0
operation_family_coverage_recorded=0
negative_case_coverage_recorded=0
replay_tamper_evidence_recorded=0
evidence_import_reviewed=0
evidence_import_gate_accepted=0
vector_execution_allowed=0
acvp_submission_allowed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_evidence_import_items_total=37
required_evidence_import_items_satisfied=27
status=ml-kem-evidence-import-review-gate-blocked
```

## Guardrail

The gate keeps Q-Seal from treating draft rows, planned replay evidence, or declared review roles as accepted implementation evidence. The packet manifest, imported digest rows, replay transcripts, reviewer role maps, coverage records, tamper evidence, and review acceptance must be recorded together before the import packet can clear, and even then operation execution remains disabled.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-import-review-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-evidence-import-review-gate.sh
```

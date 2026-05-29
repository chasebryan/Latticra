# Latticra Q-Seal ML-KEM Evidence Import Packet Manifest

Status: evidence import packet manifest
Date: 2026-05-28
Scope: fail-closed packet manifest for reviewed ML-KEM fixture, replay, digest, coverage, and reviewer-role import rows before evidence-import review.

This manifest defines the row shape required before the evidence import review gate can accept real ML-KEM evidence. It binds fixture digest ledger rows, replay transcripts, source digest receipts, reviewer identities, reviewer roles, review dispositions, implementation binding, and CI promotion evidence. It does not import live KAT vectors, execute vectors, submit to ACVP, promote implementation code, copy Apple corecrypto code, copy external provider code, claim FIPS validation, claim production cryptography, or grant runtime authority.

## Current Fields

```text
ml_kem_evidence_import_packet_manifest_present=1
formal_title=Latticra Q-Seal ML-KEM Evidence Import Packet Manifest
evidence_packet_profile=latticra-q-seal-ml-kem-evidence-import-packet-manifest/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
evidence_packet_scope=ML-KEM-evidence-import-packet-manifest-before-import-review
evidence_packet_state=evidence-import-packet-recorded-packet-rows-missing
fips_203_algorithm_bound=1
acvp_ml_kem_schema_bound=1
evidence_import_review_gate_bound=1
vector_fixture_digest_ledger_bound=1
receipt_replay_results_bound=1
source_digest_receipt_bound=1
source_digest_verification_bound=1
reviewer_identity_fixture_bound=1
reviewer_role_mapping_bound=1
review_disposition_ledger_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
clean_room_source_boundary_recorded=1
offline_packet_intake_recorded=1
digest_algorithm_sha256_required=1
immutable_packet_record_required=1
source_url_column_required=1
source_digest_column_required=1
bundle_size_column_required=1
license_column_required=1
storage_path_column_required=1
parameter_set_column_required=1
operation_family_column_required=1
negative_case_column_required=1
replay_transcript_column_required=1
tamper_evidence_column_required=1
reviewer_role_column_required=1
reviewer_identity_column_required=1
disposition_column_required=1
import_timestamp_column_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
fixture_digest_packet_rows_imported=0
receipt_replay_packet_rows_imported=0
source_digest_packet_rows_imported=0
reviewer_role_packet_rows_imported=0
coverage_packet_rows_imported=0
tamper_packet_rows_imported=0
evidence_packet_reviewed=0
evidence_packet_manifest_accepted=0
vector_execution_allowed=0
acvp_submission_allowed=0
operation_execution_allowed=0
implementation_promotion_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_evidence_packet_items_total=41
required_evidence_packet_items_satisfied=33
status=ml-kem-evidence-import-packet-manifest-blocked
```

## Required Packet Rows

```text
fixture_digest_packet_rows_imported=0
receipt_replay_packet_rows_imported=0
source_digest_packet_rows_imported=0
reviewer_role_packet_rows_imported=0
coverage_packet_rows_imported=0
tamper_packet_rows_imported=0
evidence_packet_reviewed=0
evidence_packet_manifest_accepted=0
```

## Non-Claims

This manifest is not imported evidence, not reviewed vector evidence, not ACVP submission evidence, not source approval, not a FIPS validation claim, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.

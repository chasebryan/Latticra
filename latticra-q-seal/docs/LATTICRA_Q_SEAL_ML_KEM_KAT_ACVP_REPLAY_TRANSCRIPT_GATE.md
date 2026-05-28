# Latticra Q-Seal ML-KEM KAT/ACVP Replay Transcript Gate

Status: replay transcript evidence gate
Date: 2026-05-28

This document mirrors `latticra-q-seal/evidence/ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md` for the Q-Seal documentation set. The replay transcript gate records the evidence requirements a future ML-KEM KAT/ACVP replay lane must satisfy before transcripts can be accepted as proof for promotion decisions.

The current slice is a gate only. It does not load vectors, execute ML-KEM, generate ACVP responses, submit ACVP material, emit shared secrets, or claim production cryptography readiness.

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_kat_acvp_replay_transcript_gate.h
latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
latticra-q-seal/tests/q_seal_ml_kem_kat_acvp_replay_transcript_gate_invariants.c
latticra-q-seal/evidence/ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate.sh
scripts/test-latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate.sh
```

## Current Fields

```text
ml_kem_kat_acvp_replay_transcript_gate_present=1
replay_transcript_gate_present=1
formal_title=Latticra Q-Seal ML-KEM KAT/ACVP Replay Transcript Gate
transcript_profile=latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF
transcript_scope=ML-KEM-KAT-ACVP-replay-transcripts-before-evidence-acceptance
transcript_state=replay-transcript-gate-recorded-transcripts-missing
fips_203_algorithm_bound=1
nist_acvp_ml_kem_bound=1
ssdf_evidence_integrity_bound=1
kat_manifest_bound=1
kat_runner_contract_bound=1
kat_result_schema_bound=1
kat_result_row_fixture_bound=1
acvp_parser_contract_bound=1
acvp_response_contract_bound=1
acvp_submission_package_contract_bound=1
vector_fixture_digest_ledger_bound=1
receipt_replay_results_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
provider_differential_bound=1
clean_room_source_boundary_recorded=1
deterministic_replay_transcript_schema_recorded=1
transcript_digest_sha256_required=1
transcript_command_fingerprint_required=1
fixture_digest_reference_required=1
implementation_digest_reference_required=1
parameter_set_coverage_required=1
operation_family_coverage_required=1
positive_kat_transcript_lane_recorded=1
negative_kat_transcript_lane_recorded=1
malformed_kat_transcript_lane_recorded=1
implicit_rejection_transcript_lane_recorded=1
acvp_keygen_transcript_lane_recorded=1
acvp_encap_decap_transcript_lane_recorded=1
acvp_decapsulation_val_transcript_lane_recorded=1
acvp_key_check_transcript_lane_recorded=1
provider_differential_transcript_lane_recorded=1
no_secret_material_logging_required=1
offline_only_replay_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
kat_replay_transcripts_recorded=0
acvp_replay_transcripts_recorded=0
transcript_digests_verified=0
ci_replay_transcript_recorded=0
review_disposition_recorded=0
transcript_gate_accepted=0
kat_execution_allowed=0
acvp_response_generation_allowed=0
acvp_submission_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_transcript_items_total=44
required_transcript_items_satisfied=38
status=ml-kem-kat-acvp-replay-transcript-gate-blocked
```

## Promotion Blockers

The replay transcript gate remains blocked until transcript rows, transcript digests, CI replay evidence, reviewer disposition, and explicit acceptance are recorded. Those blockers keep deterministic KAT/ACVP replay evidence separate from runtime cryptographic authority.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate.sh
```

Expected output:

```text
latticra q-seal ml-kem kat acvp replay transcript gate invariants: ok
latticra q-seal ml-kem kat acvp replay transcript gate: ok
```

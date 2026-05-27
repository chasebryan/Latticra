# Latticra Q-Seal ML-KEM Source Digest Manifest

Status: implementation-source digest template
Date: 2026-05-27
Scope: clean-room source and test digest evidence before ML-KEM implementation promotion.

This manifest records the digest policy and source-integrity template for future clean-room ML-KEM implementation files. It does not create implementation files, hash live primitive source, accept source digests, approve generated source, import third-party code, execute ML-KEM operations, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Current Fields

```text
ml_kem_source_digest_manifest_present=1
formal_title=Latticra Q-Seal ML-KEM Source Digest Manifest
digest_profile=latticra-q-seal-ml-kem-source-digest-manifest/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
digest_algorithm=SHA-256
source_boundary=clean-room-no-apple-code
digest_state=source-digest-template-blocked
fips_203_algorithm_bound=1
ssdf_source_integrity_bound=1
digest_algorithm_sha256_recorded=1
clean_room_source_boundary_recorded=1
planned_source_units_count=9
planned_test_units_count=9
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
digest_template_recorded=1
hash_command_policy_recorded=1
third_party_source_denial_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
implementation_files_created=0
source_file_digests_recorded=0
test_file_digests_recorded=0
build_script_digests_recorded=0
reviewed_digest_receipt_recorded=0
reproducible_source_snapshot_recorded=0
digest_verification_ci_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_digest_items_total=20
required_digest_items_satisfied=14
status=ml-kem-source-digest-manifest-blocked
```

## Promotion Blockers

```text
implementation_files_created=0
source_file_digests_recorded=0
test_file_digests_recorded=0
build_script_digests_recorded=0
reviewed_digest_receipt_recorded=0
reproducible_source_snapshot_recorded=0
digest_verification_ci_recorded=0
```

## Non-Claims

This manifest is not live source-integrity evidence, not a hash of primitive code, not a code snapshot, not ACVP evidence, not FIPS validation, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.

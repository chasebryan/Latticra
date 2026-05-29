# Latticra Seal Signed Receipt Proof Path Surface

Status: report surface for the Latticra Seal signed receipt proof path
Scope: deterministic local report surface after the bounded verification-only signed receipt proof path implementation. This document does not create signed receipts, create signatures, verify signatures, load trust roots, perform revocation lookup, load trust stores, load key material, handle private keys, generate keys, invoke signers, persist receipts, enforce policy, enforce capabilities, perform runtime handoff, grant runtime authority, read host paths, write host paths, use networks, implement Panel UI behavior, or claim production security readiness.

## Purpose

This document records the first operator-visible report surface for the Latticra Seal signed receipt proof path.

The surface renders one deterministic local fixture that binds verified receipt-promotion metadata to metadata-only signing-operation metadata, confirms digest/public-key agreement, and still reports the result as verification-only because trust-root and revocation boundaries remain absent.

## Added Files

```text
tests/seal_signed_receipt_proof_path_surface.c
scripts/latticra-seal-signed-receipt-proof-path.sh
```

## Report Runner

```sh
sh scripts/latticra-seal-signed-receipt-proof-path.sh
```

## Surface Posture

```text
signed_receipt_proof_path_surface_present=1
signed_receipt_proof_path_mode=verification-only
uses_local_deterministic_fixture=1
fixture_receipt_promotion_present=1
fixture_signing_operation_present=1
report_file_loading_supported=0
trust_root_loading_supported=0
revocation_lookup_supported=0
signature_creation_supported=0
signature_verification_supported=0
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Expected Report Posture

The report surface emits:

```text
LATTICRA SEAL SIGNED RECEIPT PROOF PATH
proof_path_profile=latticra-seal-signed-receipt-proof-path/0.1
receipt_profile=latticra-seal-verified-receipt/0.1
verify_profile=latticra-seal-ed25519-verify/0.1
signing_operation_profile=latticra-seal-signing-operation/0.1
signer_invocation_profile=latticra-seal-signer-invocation/0.1
message_digest_algorithm=SHA-256
message_digest_hex=aaaabbbbccccddddeeeeffff0000111122223333444455556666777788889999
public_key_identity_label=local-development-proof-key
signature_algorithm=Ed25519-development
trust_source=local-test-vector
verification_state=verified
receipt_state=verified
signing_operation_state=operation-metadata-only
proof_path_state=verification-only
local_verify_result_present=1
receipt_promotion_present=1
signing_operation_present=1
receipt_verified=1
cryptographic_verification_supported=1
cryptographic_verification_performed=1
signing_operation_ready=1
signing_operation_metadata_only=1
digest_matches=1
public_key_matches=1
trust_root_required=1
trust_root_verified=0
revocation_required=1
revocation_checked=0
verification_only=1
proof_path_verified=0
authority_usable=0
capability_gate_allowed=0
runtime_authority_granted=0
signature_performed=0
signer_invoked=0
private_key_handling=0
key_generation_performed=0
trust_store_loaded=0
revocation_lookup_performed=0
handoff_performed=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
error=ok
status=signed-receipt-proof-path-verification-only
```

## Boundary

This report surface compiles and runs a local deterministic fixture only.

It does not read receipt files, write receipt files, create signatures, verify signatures beyond the local metadata fixture already represented by the implementation, load trust roots, perform revocation lookup, load trust stores, load key material, handle private keys, generate keys, invoke signers, contact networks, evaluate external policy, enforce capabilities, grant authority, turn proof-path metadata into runtime permission, or claim production proof.

The report is evidence that the implementation can render a no-effect verification-only summary. It is not proof of production trust or revocation freshness.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signed-receipt-proof-path-surface.sh
```

Expected output:

```text
latticra seal signed receipt proof path surface: ok
```

The underlying implementation remains covered by:

```sh
sh scripts/test-latticra-seal-signed-receipt-proof-path.sh
```

## Claim Boundary

This surface does not justify the public claim that Latticra Seal produces production-valid signed receipt proofs.

It only makes the local verification-only proof-path posture inspectable before any future trust-root or revocation boundary work is considered.

## Current Next Valid Slice

The signed receipt proof path implementation is represented by `docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_IMPLEMENTATION.md`, with status in `docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.

That future slice must not load trust stores, perform network revocation lookup, grant authority, or turn verification-only metadata into capability permission without separate implementation, review, and status evidence.

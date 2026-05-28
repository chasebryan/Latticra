# Latticra Seal Signed Receipt Proof Path Implementation

Status: bounded verification-only implementation for the Latticra Seal signed receipt proof path
Scope: C metadata implementation after the signed receipt proof path contract. This implementation does not create signed receipts, create signatures, verify signatures, load trust roots, perform revocation lookup, load trust stores, load key material, handle private keys, generate keys, invoke signers, enforce policy, enforce capabilities, perform runtime handoff, grant runtime authority, perform effects, read host paths, write host paths, use networks, implement Panel UI behavior, or claim production proof readiness.

## Purpose

This slice connects existing Seal verification evidence without promoting it to authority.

The implementation accepts a verified receipt-promotion record and a metadata-only signing-operation record, confirms that they agree on digest and public-key identity, and emits a verification-only proof-path summary.

## Implemented Files

```text
include/latticra/seal_signed_receipt_proof_path.h
src/seal_signed_receipt_proof_path.c
tests/seal_signed_receipt_proof_path_invariants.c
scripts/test-latticra-seal-signed-receipt-proof-path.sh
.github/workflows/latticra-seal-signed-receipt-proof-path.yml
```

## Implementation Posture

```text
signed_receipt_proof_path_profile=latticra-seal-signed-receipt-proof-path/0.1
signed_receipt_proof_path_mode=verification-only
signed_receipt_proof_path_status=implemented-no-effect
signed_receipt_proof_path_contract_present=1
signed_receipt_proof_path_implementation_present=1
local_verify_result_present=1
receipt_promotion_present=1
signing_operation_present=1
receipt_verified=1
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
```

## Behavior

The implementation provides:

```text
latticra_seal_signed_receipt_proof_path_error_t
latticra_seal_signed_receipt_proof_path_t
latticra_seal_signed_receipt_proof_path_error_label
latticra_seal_signed_receipt_proof_path_from_metadata
latticra_seal_signed_receipt_proof_path_is_verification_only
latticra_seal_signed_receipt_proof_path_render
```

`latticra_seal_signed_receipt_proof_path_from_metadata` requires:

```text
verified_receipt_promotion_error=ok
receipt_state=verified
verification_state=verified
receipt_authority_neutral=1
signing_operation_state=operation-metadata-only
signing_operation_ready=1
signing_operation_metadata_only=1
message_digest_match=1
public_key_identity_match=1
```

The result is still only:

```text
proof_path_state=verification-only
proof_path_verified=0
trust_root_verified=0
revocation_checked=0
authority_usable=0
runtime_authority_granted=0
```

## Closed Cases

The invariant test covers fail-closed cases for:

```text
missing receipt
missing output
receipt-not-verified
receipt-authority-not-neutral
digest-mismatch
public-key-mismatch
signing-operation-not-metadata-only
rendering non-verification-only state
small render buffer
```

Failures do not sign, verify signatures, load trust roots, perform revocation lookup, load key material, handle private keys, generate keys, invoke signers, perform effects, touch host paths, use networks, or grant authority.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signed-receipt-proof-path.sh
```

Expected output:

```text
seal signed receipt proof path invariants: ok
```

## Boundary

This is a verification-only proof-path summary.

It proves that local verified receipt metadata and metadata-only signing-operation metadata agree on digest and public-key identity. It does not prove production trust, revocation freshness, authority usability, capability allowance, runtime allowance, or effect permission.

## Current Next Valid Slice

The signed receipt proof path contract is represented by `docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT.md`, with status in `docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt proof path report surface/status checkpoint that remains verification-only until trust-root and revocation boundaries are implemented.

That future slice must preserve the no-effect posture and must not perform effects, verify signatures, create signatures, load trust roots, perform revocation lookup, or grant authority.

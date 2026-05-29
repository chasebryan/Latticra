# Latticra Seal Signed Receipt Proof Path Contract

Status: contract for a future verification-only Latticra Seal signed receipt proof path
Scope: contract-only planning after the Seal Panel dashboard view-model surface/status checkpoint. This document does not implement signed receipts, create signatures, verify signatures, claim cryptographic proof, load trust roots, perform revocation lookup, load public-key trust stores, load key material, handle private keys, generate keys, use hardware keys, persist receipts, enforce policy, enforce capabilities, perform effects, execute runtime handoff, grant runtime authority, read host paths, write host paths, use networks, implement Panel UI behavior, or claim production security readiness.

## Purpose

This contract defines the next Latticra Seal proof-path slice before any implementation is allowed.

The future signed receipt proof path should answer:

```text
Which receipt artifact is being considered?
Which digest binds the receipt report content?
Which signature request metadata is attached?
Which signer identity, algorithm, and public-key identity are claimed?
Which verification policy and verification receipt metadata are attached?
Which trust-root and revocation boundaries are still missing?
Why is the result verification-only and not authority?
```

The answer must remain contract-only, local, deterministic, verification-only, denied-by-default, and report-only.

## Required Predecessors

A future implementation plan may only proceed after these predecessor surfaces remain present and guarded:

```text
docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md
docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md
docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md
docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md
docs/status/SEAL_SIGNATURE_REQUEST_STATUS.md
docs/status/SEAL_VERIFICATION_POLICY_STATUS.md
docs/status/SEAL_VERIFICATION_RECEIPT_STATUS.md
docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md
docs/status/SEAL_ED25519_VERIFY_STATUS.md
```

## Proof Path Profile

The future proof-path record must use this profile:

```text
signed_receipt_proof_path_profile=latticra-seal-signed-receipt-proof-path/0.1
signed_receipt_proof_path_mode=contract-only
signed_receipt_proof_path_status=not-implemented
proof_path_scope=verification-only
proof_path_authority=none
```

## Required Proof Path Fields

The future proof-path record must expose bounded metadata fields for:

```text
signed_receipt_proof_path_profile=
signed_receipt_proof_path_mode=
signed_receipt_proof_path_status=
proof_path_scope=
proof_path_authority=
receipt_artifact_id=
receipt_report_profile=
receipt_report_digest_algorithm=
receipt_report_digest_hex=
signature_request_profile=
signature_request_id=
signer_identity_label=
signature_algorithm_label=
public_key_identity_label=
trust_source_label=
verification_policy_profile=
verification_state=
verification_receipt_profile=
verification_receipt_id=
proof_path_state=
blocked_reason=
next_required_evidence=
```

## Required Defaults

The future proof-path implementation, if added later, must default to:

```text
signed_receipt_proof_path_contract_present=1
signed_receipt_proof_path_planning_only=1
signed_receipt_proof_path_implemented=0
signed_receipt_proof_path_report_surface_present=0
verification_only_until_trust_root_and_revocation=1
receipt_digest_required=1
signature_request_required=1
verification_policy_required=1
verification_receipt_required=1
trust_root_required_for_promotion=1
revocation_boundary_required_for_promotion=1
crypto_backend_required_for_promotion=1
operator_review_required=1
signed_receipt_created=0
signature_created=0
signer_invoked=0
signature_verification_performed=0
cryptographic_verification_performed=0
verified_receipt_authority=0
capability_gate_allowed=0
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Required Source Bindings

The future proof path must bind only caller-provided, deterministic metadata from existing guarded records:

```text
required_source_operator_receipt_report=1
required_source_report_envelope=1
required_source_signature_request=1
required_source_signing_authorization=1
required_source_signer_handoff=1
required_source_signer_invocation=1
required_source_signing_operation=1
required_source_key_handling=1
required_source_key_material=1
required_source_public_key_parsing=1
required_source_key_parsing=1
required_source_verification_policy=1
required_source_verification_receipt=1
```

Missing, malformed, stale, unverifiable, or unsupported source metadata must remain visible and denied.

## Required States

The future proof path may only report these states until a separate implementation, trust-root boundary, revocation boundary, and verified receipt promotion path exist:

```text
proof_path_state=missing-evidence
proof_path_state=malformed-evidence
proof_path_state=unsupported-trust-root
proof_path_state=unsupported-revocation
proof_path_state=unverified-metadata
proof_path_state=verification-only-blocked
```

The future proof path must not report `verified`, `trusted`, `authority-usable`, `capability-allowed`, or `runtime-allowed` states under this contract.

## Required Denial Rule

A signed receipt proof path may describe a candidate evidence chain but must not authorize it.

Every future record must preserve:

```text
proof_path_authority=none
signature_verification_performed=0
cryptographic_verification_performed=0
verified_receipt_authority=0
capability_gate_allowed=0
runtime_authority_granted=0
effect_performed=0
```

## Forbidden Behavior

This contract does not allow:

```text
signed receipt creation
signature creation
signature verification
cryptographic proof claims
verified receipt authority
trust-root loading
trust-store loading
revocation lookup
network trust lookup
private-key loading
key generation
hardware-key use
signer process execution
receipt persistence
policy enforcement
capability enforcement
runtime handoff execution
tool execution
shell execution
host reads
host writes
network behavior
Panel UI rendering
turning receipt evidence into execution grants
turning receipt evidence into effect grants
production security-product claims
```

## Required Future Implementation Plan

A future implementation plan must specify:

```text
exact header path
exact source path
exact test path
bounded struct sizes
enum labels
source metadata copy behavior
required source fixture strings
missing source behavior
malformed source behavior
unsupported trust-root behavior
unsupported revocation behavior
report shape
small-buffer behavior
null-input behavior
no-effect invariants
status/report-surface follow-up path
```

## Promotion Rule

This contract does not authorize a signed receipt proof implementation.

The proof path may be considered only as verification-only metadata until a future implementation plan, implementation, report surface, status record, public-entrypoint alignment, and negative-case evidence all remain merged and guarded.

Even after that sequence, trust-root handling, revocation handling, verified receipt promotion, capability enforcement, and runtime authority each require separate contracts, implementations, tests, review, and status records before they can affect any decision.

## Boundary

This is a contract-only planning slice.

It does not change implementation behavior, add runtime behavior, grant authority, or change public readiness.

## Current Next Valid Slice

The signed receipt proof path implementation is now represented by `docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_IMPLEMENTATION.md`.

The current next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.

That future slice must preserve the no-effect posture and must not perform effects, verify signatures, create signatures, load trust roots, perform revocation lookup, or grant authority.

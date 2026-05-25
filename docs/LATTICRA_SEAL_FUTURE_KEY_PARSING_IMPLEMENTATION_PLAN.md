# Latticra Seal Future Key Parsing Implementation Plan

Status: implementation planning contract for a future bounded no-effect Latticra Seal key parsing surface
Scope: implementation plan only after the Latticra Seal future key parsing implementation contract. This document does not implement public-key parsing, parse key bytes, load key material, handle private keys, generate keys, use hardware keys, load trust stores, perform revocation lookup, sign, verify signatures, invoke a signer, execute a signer process, seal objects, perform runtime handoff, grant runtime authority, read host files, write host files, use networks, execute shells, execute tools, enforce capabilities, persist policy, interact with kernels, claim Fedora approval, claim production readiness, or change operating-system behavior.

## Purpose

This plan defines the exact future implementation shape for a bounded no-effect Seal key parsing layer.

The future implementation may parse caller-provided public-key bytes into metadata only. It must not load key material from files, handle private keys, consult trust stores, verify signatures, perform signing, contact networks, or grant authority.

This document is a plan, not parser code.

## Required Contract

The implementation plan depends on:

```text
docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_CONTRACT.md
scripts/test-latticra-seal-future-key-parsing-implementation-contract.sh
docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md
docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
include/latticra/seal_public_key_parsing.h
src/seal_public_key_parsing.c
tests/seal_public_key_parsing_invariants.c
scripts/test-latticra-seal-public-key-parsing-contract.sh
scripts/test-latticra-seal-public-key-parsing.sh
scripts/test-latticra-seal-public-key-parsing-status.sh
```

The contract and predecessor metadata/status guards must remain merged and green before implementation code is added.

## Future Files

The future implementation slice should add:

```text
include/latticra/seal_key_parsing.h
src/seal_key_parsing.c
tests/seal_key_parsing_invariants.c
scripts/test-latticra-seal-key-parsing.sh
docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md
```

A later status/public-entry slice may add:

```text
docs/status/SEAL_KEY_PARSING_STATUS.md
scripts/test-latticra-seal-key-parsing-status.sh
```

## Header API Plan

The future header should define:

```text
LATTICRA_SEAL_KEY_PARSING_PROFILE_MAX
LATTICRA_SEAL_KEY_PARSING_LABEL_MAX
LATTICRA_SEAL_KEY_PARSING_FORMAT_MAX
LATTICRA_SEAL_KEY_PARSING_ALGORITHM_MAX
LATTICRA_SEAL_KEY_PARSING_REASON_MAX
LATTICRA_SEAL_KEY_PARSING_STATUS_MAX
LATTICRA_SEAL_KEY_PARSING_INPUT_MAX 4096u
LATTICRA_SEAL_KEY_PARSING_REPORT_MAX 8192u
latticra_seal_key_parsing_error_t
latticra_seal_key_parsing_format_t
latticra_seal_key_parsing_input_t
latticra_seal_key_parsing_result_t
latticra_seal_key_parsing_error_label
latticra_seal_key_parsing_format_label
latticra_seal_key_parsing_from_public_key_bytes
latticra_seal_key_parsing_is_no_effect
latticra_seal_key_parsing_render
```

Recommended function signatures:

```text
const char *latticra_seal_key_parsing_error_label(latticra_seal_key_parsing_error_t error);
const char *latticra_seal_key_parsing_format_label(latticra_seal_key_parsing_format_t format);

latticra_status_t latticra_seal_key_parsing_from_public_key_bytes(
    const latticra_seal_public_key_parsing_t *predecessor,
    const unsigned char *public_key_bytes,
    size_t public_key_len,
    latticra_seal_key_parsing_format_t requested_format,
    latticra_seal_key_parsing_result_t *out);

int latticra_seal_key_parsing_is_no_effect(
    const latticra_seal_key_parsing_result_t *key_parsing);

latticra_status_t latticra_seal_key_parsing_render(
    const latticra_seal_key_parsing_result_t *key_parsing,
    char *buffer,
    size_t buffer_len);
```

The first implementation should parse and report public-key byte metadata only. It must not open files or load key material.

## Format Model

The future format enum should include:

```text
LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32
LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_HEX_PUBLIC_KEY_64
LATTICRA_SEAL_KEY_PARSING_FORMAT_PEM_PUBLIC_KEY_UNSUPPORTED
LATTICRA_SEAL_KEY_PARSING_FORMAT_DER_PUBLIC_KEY_UNSUPPORTED
LATTICRA_SEAL_KEY_PARSING_FORMAT_PRIVATE_KEY_DENIED
LATTICRA_SEAL_KEY_PARSING_FORMAT_UNKNOWN
```

Stable labels:

```text
ed25519-raw-public-key-32
ed25519-hex-public-key-64
pem-public-key-unsupported
der-public-key-unsupported
private-key-denied
unknown
```

The first implementation may accept only fixed-size Ed25519 public-key byte forms. PEM and DER are explicitly planned as unsupported until a separate parser contract exists.

## Error Model

The future error enum should include:

```text
LATTICRA_SEAL_KEY_PARSING_OK
LATTICRA_SEAL_KEY_PARSING_INVALID_INPUT
LATTICRA_SEAL_KEY_PARSING_INVALID_PREDECESSOR
LATTICRA_SEAL_KEY_PARSING_PREDECESSOR_NOT_READY
LATTICRA_SEAL_KEY_PARSING_UNSUPPORTED_FORMAT
LATTICRA_SEAL_KEY_PARSING_OVERSIZED_INPUT
LATTICRA_SEAL_KEY_PARSING_INVALID_PUBLIC_KEY_BYTES
LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED
LATTICRA_SEAL_KEY_PARSING_KEY_MATERIAL_LOADING_DENIED
LATTICRA_SEAL_KEY_PARSING_TRUST_STORE_DENIED
LATTICRA_SEAL_KEY_PARSING_REVOCATION_DENIED
LATTICRA_SEAL_KEY_PARSING_EFFECT_DENIED
LATTICRA_SEAL_KEY_PARSING_BUFFER_TOO_SMALL
```

## Record Fields

The future result record should include:

```text
key_parsing_profile
public_key_parsing_profile
key_material_profile
requested_key_parsing
requested_public_key_parsing
key_parsing_input_format
key_parsing_input_length
key_parsing_algorithm
key_parsing_state
key_parsing_ready
public_key_parsing_state
public_key_parsing_ready
public_key_parsed
key_material_loaded
private_key_handling
key_generation_performed
hardware_key_used
trust_store_loaded
revocation_lookup_performed
signature_performed
verification_performed
signer_invoked
handoff_performed
effect_performed
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
blocked_reason
mode
status
error
```

## Current Plan Checkpoint

This planning slice must keep the repository in a no-parser state:

```text
future_key_parsing_contract_present=1
future_key_parsing_implementation_plan_present=1
future_key_parsing_implementation_present=0
public_key_parser_implementation_present=0
key_parsing_header_present=0
key_parsing_source_present=0
key_parsing_invariant_test_present=0
public_key_parsed=0
key_material_loaded=0
private_key_handling=0
signature_performed=0
verification_performed=0
signer_invoked=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Future Successful Result

The future implementation may emit for a valid caller-provided 32-byte Ed25519 public key:

```text
key_parsing_profile=latticra-seal-key-parsing/0.1
requested_key_parsing=public-key-bytes-only
key_parsing_input_format=ed25519-raw-public-key-32
key_parsing_input_length=32
key_parsing_algorithm=Ed25519-development
key_parsing_state=public-key-parsed-metadata-only
key_parsing_ready=1
public_key_parsing_state=public-key-parsing-metadata-only
public_key_parsing_ready=1
public_key_parsed=1
key_material_loaded=0
private_key_handling=0
key_generation_performed=0
hardware_key_used=0
trust_store_loaded=0
revocation_lookup_performed=0
signature_performed=0
verification_performed=0
signer_invoked=0
handoff_performed=0
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
blocked_reason=none
mode=metadata-only
status=key-parsing-metadata
```

The future implementation must never set `key_material_loaded=1`, `private_key_handling=1`, `signature_performed=1`, `verification_performed=1`, `host_read_performed=1`, `host_write_performed=1`, `network_performed=1`, or `runtime_authority_granted=1`.

## Failure Behavior

The future builder should:

```text
reject null output
reject null predecessor metadata
reject predecessor public_key_parsing_ready=0
reject predecessor public_key_parsing_state not public-key-parsing-metadata-only
reject predecessor requested_public_key_parsing not metadata-only
reject predecessor public_key_parsed=1
reject predecessor key_material_loaded=1
reject predecessor private_key_handling=1
reject predecessor signature_performed=1
reject predecessor verification_performed=1
reject predecessor signer_invoked=1
reject predecessor runtime_authority_granted=1
reject predecessor host_read_performed=1
reject predecessor host_write_performed=1
reject predecessor network_performed=1
reject null public-key bytes
reject zero-length public-key bytes
reject oversized public-key bytes
reject unsupported format labels
reject PEM private-key markers
reject DER private-key requests
reject trust-store requests
reject revocation lookup requests
clear output on small report buffers
render deterministic metadata only
```

Failures must not sign, verify signatures, invoke a signer, load key material, handle private keys, generate keys, use hardware keys, load trust stores, look up revocation status, read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform runtime handoff, persist policy, seal objects, or grant runtime authority.

## Required Report Format

The report should begin with:

```text
LATTICRA SEAL KEY PARSING
```

It should render all fields as stable `key=value` lines.

Required report fields:

```text
key_parsing_profile=latticra-seal-key-parsing/0.1
requested_key_parsing
key_parsing_input_format
key_parsing_input_length
key_parsing_algorithm=Ed25519-development
key_parsing_state
key_parsing_ready
public_key_parsed
key_material_loaded=0
private_key_handling=0
signature_performed=0
verification_performed=0
signer_invoked=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
blocked_reason
mode=metadata-only
status=key-parsing-metadata
```

Small report buffers fail closed and clear the output buffer.

## Exact Implementation Test List

The future implementation test should prove:

```text
ed25519 raw public key bytes parse as metadata only
ed25519 hex public key bytes parse as metadata only
public_key_parsed=1 only for valid public-key byte inputs
key_material_loaded=0 after successful parsing
private_key_handling=0 after successful parsing
signature_performed=0 after successful parsing
verification_performed=0 after successful parsing
signer_invoked=0 after successful parsing
runtime_authority_granted=0 after successful parsing
host_read_performed=0 after successful parsing
host_write_performed=0 after successful parsing
network_performed=0 after successful parsing
predecessor not ready fails closed
unsupported format fails closed
private key marker fails closed
oversized input fails closed
small report buffers fail closed
```

## Documentation Update Plan

The implementation slice should update:

```text
README.md
STATUS.md
docs/FOUNDATION_INDEX.md
docs/status/README.md
docs/status/CURRENT_STATUS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
```

and add:

```text
docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md
```

## Implementation Gate

Bounded no-effect key parsing implementation code may be added only after this plan is merged.

No key material loading, private-key handling, trust-store behavior, revocation lookup, signing, verification, signer invocation behavior, runtime authority, host behavior, network behavior, capability enforcement, object sealing, or kernel behavior may begin from this plan alone.

## Validation

This implementation plan is guarded by:

```sh
sh scripts/test-latticra-seal-future-key-parsing-implementation-plan.sh
```

Expected output:

```text
seal future key parsing implementation plan: ok
```

## Next Valid Slice

The next valid Latticra Seal slice is bounded no-effect key parsing implementation.

That future implementation slice may add guarded public-key byte parsing metadata only. It must not add key material loading, private-key handling, key generation, hardware-key use, trust-store behavior, revocation lookup, signing, verification, signer invocation behavior, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior.

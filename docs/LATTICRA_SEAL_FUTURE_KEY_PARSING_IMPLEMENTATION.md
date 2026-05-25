# Latticra Seal Future Key Parsing Implementation

Status: initial bounded no-effect key parsing implementation
Scope: bounded C metadata surface for parsing caller-provided public-key bytes after ready public-key parsing metadata. This slice does not load key material, handle private keys, generate keys, use hardware keys, load trust stores, perform revocation lookup, sign, verify signatures, invoke a signer, execute a signer process, seal objects, perform runtime handoff, grant runtime authority, read host files, write host files, use networks, execute shells, execute tools, enforce capabilities, persist policy, interact with kernels, claim Fedora approval, claim production readiness, or change operating-system behavior.

## Purpose

This document records the first Latticra Seal key parsing implementation.

The implementation consumes ready public-key parsing metadata and caller-provided public-key bytes.

It parses only fixed-size public-key byte forms into metadata.

It does not load key material.

It does not handle private keys.

It does not sign.

It does not verify signatures.

## Files

```text
include/latticra/seal_key_parsing.h
src/seal_key_parsing.c
tests/seal_key_parsing_invariants.c
scripts/test-latticra-seal-key-parsing.sh
docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md
```

## Required predecessors

This implementation depends on the future key parsing implementation plan, the future key parsing implementation contract, and the public-key parsing metadata/status surface:

```text
docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_PLAN.md
docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_CONTRACT.md
docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md
docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
include/latticra/seal_public_key_parsing.h
src/seal_public_key_parsing.c
tests/seal_public_key_parsing_invariants.c
scripts/test-latticra-seal-future-key-parsing-implementation-plan.sh
scripts/test-latticra-seal-future-key-parsing-implementation-contract.sh
scripts/test-latticra-seal-public-key-parsing-contract.sh
scripts/test-latticra-seal-public-key-parsing.sh
scripts/test-latticra-seal-public-key-parsing-status.sh
```

## Implemented surface

The key parsing metadata surface adds:

```text
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

The implementation accepts:

```text
LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32
LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_HEX_PUBLIC_KEY_64
```

It records PEM and DER public-key input as unsupported until a separate parser contract exists.

It denies private-key formats and private-key markers.

Even when key_parsing_ready=1, these fields remain zero:

```text
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
```

## Current metadata output

The successful raw Ed25519 public-key byte path renders:

```text
key_parsing_profile=latticra-seal-key-parsing/0.1
public_key_parsing_profile=latticra-seal-public-key-parsing/0.1
key_material_profile=latticra-seal-key-material/0.1
requested_key_parsing=public-key-bytes-only
requested_public_key_parsing=metadata-only
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
error=ok
```

The successful hex Ed25519 public-key byte path uses:

```text
key_parsing_input_format=ed25519-hex-public-key-64
key_parsing_input_length=64
status=key-parsing-metadata
```

## Failure behavior

The implementation fails closed for:

```text
null output
null predecessor metadata
invalid predecessor metadata
predecessor public_key_parsing_ready=0
predecessor public_key_parsing_state not public-key-parsing-metadata-only
predecessor requested_public_key_parsing not metadata-only
predecessor public_key_parsed=1
predecessor key_material_loaded=1
predecessor private_key_handling=1
predecessor key_generation_performed=1
predecessor hardware_key_used=1
predecessor trust_store_loaded=1
predecessor revocation_lookup_performed=1
predecessor signature_performed=1
predecessor verification_performed=1
predecessor signer_invoked=1
predecessor handoff_performed=1
predecessor effect_performed=1
predecessor runtime_authority_granted=1
predecessor host_read_performed=1
predecessor host_write_performed=1
predecessor network_performed=1
missing public-key bytes
empty public-key bytes
oversized public-key bytes
raw Ed25519 public-key input not exactly 32 bytes
hex Ed25519 public-key input not exactly 64 ASCII hex bytes
PEM public-key input
DER public-key input
private-key format requests
private key markers
small report buffers
```

Failure records keep authority and effect fields at zero. Denial details are represented by `error`, `key_parsing_state`, `status`, and `blocked_reason`.

## Validation

The implementation is covered by:

```sh
sh scripts/test-latticra-seal-future-key-parsing-implementation-plan.sh
sh scripts/test-latticra-seal-key-parsing.sh
sh scripts/test-latticra-seal-public-key-parsing-status.sh
```

Expected output:

```text
seal future key parsing implementation plan: ok
seal key parsing invariants: ok
seal public-key parsing status: ok
```

## Current next valid slice

The next valid Latticra Seal slice is key parsing status/public-entry alignment or another narrow status/index alignment follow-up.

That future slice must not add key material loading, private-key handling, key generation, hardware-key use, trust-store behavior, signing, verification, signer invocation behavior, host behavior, network behavior, runtime authority, capability enforcement, object sealing, or kernel behavior unless separately implemented and guarded.

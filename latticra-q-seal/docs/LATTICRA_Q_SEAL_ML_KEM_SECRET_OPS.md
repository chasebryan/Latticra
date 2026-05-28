# Latticra Q-Seal ML-KEM Secret Ops

Status: candidate constant-time and zeroization helper implementation
Date: 2026-05-27
Scope: low-level secret-state utilities for future ML-KEM work.

This slice adds candidate C helpers for wiping buffers, comparing equal-length byte strings without secret-dependent early exit, and selecting between equal-length byte strings with a mask. The selection helper allows exact output aliases and rejects partial output/input overlap before writing. These helpers do not implement ML-KEM key generation, encapsulation, decapsulation, shared-secret release, provider binding, production cryptography, FIPS validation, host mutation, or runtime authority.

The operation gates remain closed. The helpers are implementation building blocks that still require the existing secret-state, zeroization, constant-time, side-channel, compiler, and implementation-binding evidence before any ML-KEM primitive can use them as promoted secret-material handling.

```text
ml_kem_secret_ops_present=1
secret_ops_profile=latticra-q-seal-ml-kem-secret-ops/0.2
standards_source=NIST-FIPS-203
secure_zero_candidate_present=1
constant_time_equal_candidate_present=1
constant_time_select_candidate_present=1
secret_dependent_early_return_forbidden=1
secret_indexed_memory_forbidden=1
branchless_select_mask_recorded=1
equal_length_input_contract_required=1
zero_length_public_input_allowed=1
exact_select_alias_allowed=1
partial_select_overlap_rejected=1
partial_select_overlap_failure_writes_output=0
invalid_argument_status_recorded=1
operation_execution_allowed=0
key_generation_enabled=0
encapsulation_enabled=0
decapsulation_enabled=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
status=ml-kem-secret-ops-candidate-present
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_secret_ops.h
latticra-q-seal/src/q_seal_ml_kem_secret_ops.c
latticra-q-seal/tests/q_seal_ml_kem_secret_ops_invariants.c
latticra-q-seal/evidence/ML_KEM_SECRET_OPS.md
latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_OPS.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
sh scripts/test-latticra-q-seal-ml-kem-secret-ops.sh
make latticra-q-seal-ml-kem-secret-ops
```

Expected output:

```text
latticra q-seal ml-kem secret ops invariants: ok
latticra q-seal ml-kem secret ops: ok
```

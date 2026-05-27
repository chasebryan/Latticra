# Latticra Q-Seal ML-KEM Memory-Safety Evidence

Status: memory-safety policy recorded; analysis and test evidence blocked
Date: 2026-05-27

## Purpose

The Latticra Q-Seal ML-KEM memory-safety evidence contract defines the promotion gate for future clean-room ML-KEM primitive code that touches buffers, encoded keys, ciphertexts, secret intermediates, and shared-secret material. It records required evidence for bounded buffers, fixed-capacity API policy, allocation policy, size overflow checks, bounds checks, integer overflow review, sanitizer runs, static analysis, fuzzing, aliasing and lifetime review, secret-buffer isolation, constant-time memory copies, zeroization binding, cross-platform word-size review, and implementation binding.

This slice does not implement ML-KEM, allocate or copy cryptographic buffers, run sanitizer or static-analysis tools, execute fuzzing, promote implementation code, execute operations, or allow production cryptography claims.

## Source Posture

```text
fips_203_url=https://csrc.nist.gov/pubs/fips/203/final
fips_140_3_url=https://csrc.nist.gov/pubs/fips/140-3/final
nist_ssdf_url=https://csrc.nist.gov/pubs/sp/800/218/final
```

## Evidence Fields

```text
ml_kem_memory_safety_evidence_present=1
evidence_profile=latticra-q-seal-ml-kem-memory-safety-evidence/0.1
formal_title=Latticra Q-Seal ML-KEM Memory-Safety Evidence
standards_source=NIST-FIPS-203
module_security_source=NIST-FIPS-140-3-software-firmware-security
secure_development_source=NIST-SP-800-218-SSDF
evidence_scope=ML-KEM-buffer-bounds-integer-lifetime-and-secret-memory-safety
evidence_state=policy-recorded-analysis-and-test-evidence-missing
fips_203_source_verified=1
fips_140_3_software_security_tracked=1
nist_ssdf_source_tracked=1
implementation_frame_bound=1
negative_test_evidence_bound=1
bounded_buffer_policy_required=1
fixed_capacity_api_policy_required=1
allocation_policy_required=1
size_overflow_checks_recorded=0
bounds_check_review_recorded=0
integer_overflow_review_recorded=0
sanitizer_asan_ubsan_recorded=0
static_analysis_recorded=0
fuzz_memory_safety_recorded=0
aliasing_lifetime_review_recorded=0
secret_buffer_isolation_recorded=0
constant_time_memory_copy_review_recorded=0
zeroization_memory_safety_bound=0
cross_platform_word_size_review_recorded=0
implementation_binding_recorded=0
memory_safety_tests_executed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_memory_safety_items_total=20
required_memory_safety_items_satisfied=8
status=ml-kem-memory-safety-evidence-blocked
```

## Files

```text
latticra-q-seal/include/latticra/q_seal_ml_kem_memory_safety_evidence.h
latticra-q-seal/src/q_seal_ml_kem_memory_safety_evidence.c
latticra-q-seal/tests/q_seal_ml_kem_memory_safety_evidence_invariants.c
latticra-q-seal/evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
```

## Runtime Blockers

Implementation promotion remains blocked until:

- size overflow checks, bounds review, and integer-overflow review are recorded;
- sanitizer and static-analysis evidence are recorded;
- memory-safety fuzzing evidence is recorded;
- aliasing, lifetime, and secret-buffer isolation reviews are recorded;
- constant-time memory-copy and zeroization bindings are recorded;
- cross-platform word-size review and implementation binding are recorded.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
make latticra-q-seal-ml-kem-memory-safety-evidence
```

Expected output:

```text
latticra q-seal ml-kem memory-safety evidence invariants: ok
latticra q-seal ml-kem memory-safety evidence: ok
```

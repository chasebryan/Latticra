# Latticra Seal PQC Integration Frame

Status: authority-neutral post-quantum cryptography integration frame
Research date: 2026-05-27
Scope: Apple corecrypto source review, NIST ML-KEM/ML-DSA standards tracking, candidate open-source provider posture, and Latticra Seal promotion blockers before any post-quantum cryptographic behavior.

This frame prepares Latticra for post-quantum cryptography integration. It does not vendor Apple corecrypto, vendor liboqs, implement ML-KEM, implement ML-DSA, perform encryption, perform signing, generate keys, store keys, load trust stores, run network lookup, claim FIPS validation, claim production cryptography, migrate deployed cryptography, enforce capabilities, execute effects, mutate host state, or grant runtime authority.

## Research Result

The Apple release is important, but it is not a dependency we can directly embed.

Source findings:

```text
apple_security_blog=https://security.apple.com/blog/formal-verification-corecrypto/
apple_corecrypto_source=https://github.com/apple/corecrypto/tree/2026-05
apple_corecrypto_license=https://github.com/apple/corecrypto/blob/main/License.txt
nist_fips_203=https://csrc.nist.gov/pubs/fips/203/final
nist_fips_204=https://csrc.nist.gov/pubs/fips/204/final
nist_fips_205=https://csrc.nist.gov/pubs/fips/205/final
liboqs_source=https://github.com/open-quantum-safe/liboqs
liboqs_project=https://openquantumsafe.org/
```

Apple published corecrypto ML-KEM and ML-DSA implementations, formal verification material, Isabelle theories, and supporting tools for independent evaluation. The default corecrypto license is evaluation-only, time-limited for internal verification, non-sublicensable, and does not allow redistribution. Latticra can use the Apple release as a high-assurance design and verification reference, but must not copy, vendor, redistribute, or build a product dependency from Apple corecrypto without separate legal permission.

NIST FIPS 203 tracks ML-KEM for key establishment. NIST FIPS 204 tracks ML-DSA for digital signatures. NIST FIPS 205 tracks SLH-DSA as a stateless hash-based signature standard and backup signature planning path. Open Quantum Safe liboqs is the current candidate open-source implementation provider for a future prototype lane because it exposes a C API, includes ML-KEM and ML-DSA, and is MIT-licensed with third-party notice review. It still remains blocked from production Latticra use until module boundaries, notices, KAT/ACVP vectors, side-channel review, constant-time posture, dependency review, and Latticra's production-crypto claim gates are complete.

## Files

```text
include/latticra/seal_pqc_integration_frame.h
src/seal_pqc_integration_frame.c
tests/seal_pqc_integration_frame_invariants.c
scripts/test-latticra-seal-pqc-integration-frame.sh
docs/LATTICRA_SEAL_PQC_INTEGRATION_FRAME.md
docs/status/SEAL_PQC_INTEGRATION_FRAME_STATUS.md
```

## Current Fields

```text
seal_pqc_integration_frame_present=1
pqc_integration_profile=latticra-seal-pqc-integration-frame/0.1
research_date=2026-05-27
apple_corecrypto_source=github.com/apple/corecrypto@2026-05
apple_corecrypto_license=evaluation-only-no-redistribution
apple_corecrypto_ml_kem_published=1
apple_corecrypto_ml_dsa_published=1
apple_corecrypto_formal_verification_published=1
apple_corecrypto_reference_allowed=1
apple_corecrypto_embedding_allowed=0
apple_corecrypto_redistribution_allowed=0
nist_fips_203_ml_kem_tracked=1
nist_fips_204_ml_dsa_tracked=1
nist_fips_205_slh_dsa_backup_tracked=1
ml_kem_key_establishment_planned=1
ml_dsa_signature_planned=1
hybrid_classical_pqc_transition_required=1
candidate_provider=liboqs
candidate_provider_source=github.com/open-quantum-safe/liboqs
candidate_provider_license=MIT-with-third-party-notice-review
liboqs_candidate_tracked=1
liboqs_mit_license_tracked=1
liboqs_prototype_only_warning_tracked=1
candidate_provider_production_use_allowed=0
cryptographic_module_boundary_required=1
algorithm_parameter_inventory_required=1
known_answer_tests_required=1
cavp_acvp_vector_review_required=1
constant_time_review_required=1
side_channel_review_required=1
fips_140_3_claim_gate_required=1
sp_800_57_key_management_required=1
source_notice_review_required=1
third_party_code_vendored=0
cryptographic_behavior_changed=0
post_quantum_migration_claim_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
key_generation_allowed=0
key_storage_allowed=0
encryption_performed=0
signing_performed=0
network_lookup_allowed=0
runtime_authority_granted=0
frame_state=prepared-authority-neutral
blocked_reason=license-validation-and-provider-review-required
status=pqc-integration-frame-prepared
```

## Integration Direction

Apple corecrypto is a design and assurance reference for Latticra's PQC posture. It should influence the design frame in these ways:

- prefer standardized ML-KEM for future key-establishment planning;
- prefer standardized ML-DSA for future post-quantum signature planning;
- keep SLH-DSA visible as backup signature planning;
- require hybrid classical plus post-quantum transition planning before any migration claim;
- require compositional verification and conventional testing evidence before authority promotion;
- keep side-channel, constant-time, compiler, platform, parameter, and key-lifecycle assumptions visible.

The future implementation candidate is a separate provider adapter, likely liboqs first for prototype and test-vector work. That adapter must be compile-time gated and authority-neutral until legal, notice, dependency, KAT, side-channel, CAVP/ACVP, cryptographic module boundary, and FIPS/CMVP claim reviews are complete.

## Validation

Current guard:

```sh
sh scripts/test-latticra-seal-pqc-integration-frame.sh
```

Expected output:

```text
seal pqc integration frame invariants: ok
latticra seal pqc integration frame: ok
```

## Next Valid Slice

The next valid cryptographic slice is a no-effect `liboqs` provider-adapter contract that defines build flags, API shape, KAT fixtures, license notices, dependency inventory, and failure behavior without vendoring source, linking liboqs by default, performing cryptographic operations in production paths, generating keys, storing keys, or granting runtime authority.

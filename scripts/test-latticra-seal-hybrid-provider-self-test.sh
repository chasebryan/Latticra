#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-hybrid-provider-self-test.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

OPENSSL_CFLAGS="${OPENSSL_CFLAGS:-}"
OPENSSL_LIBS="${OPENSSL_LIBS:-}"

if [ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ] && command -v pkg-config >/dev/null 2>&1; then
  if pkg-config --exists openssl; then
    OPENSSL_CFLAGS="$(pkg-config --cflags openssl)"
    OPENSSL_LIBS="$(pkg-config --libs openssl)"
  fi
fi

if [ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ] && command -v brew >/dev/null 2>&1; then
  openssl_prefix="$(brew --prefix openssl@3 2>/dev/null || brew --prefix openssl 2>/dev/null || true)"
  if [ -n "$openssl_prefix" ]; then
    OPENSSL_CFLAGS="-I$openssl_prefix/include"
    OPENSSL_LIBS="-L$openssl_prefix/lib -lcrypto"
  fi
fi

if [ -z "$OPENSSL_LIBS" ]; then
  OPENSSL_LIBS="-lcrypto"
fi

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal hybrid provider self-test: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal hybrid provider self-test: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-seal-hybrid-provider-self-test"

require_file include/latticra/seal_hybrid_provider_self_test.h
require_file src/seal_hybrid_provider_self_test.c
require_file src/seal_hybrid_envelope.c
require_file tests/seal_hybrid_provider_self_test_invariants.c
require_file docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_file docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md

require_contains 'latticra_seal_hybrid_provider_self_test_run' include/latticra/seal_hybrid_provider_self_test.h
require_contains 'ECDH-P-256' src/seal_hybrid_provider_self_test.c
require_contains 'ML-KEM-512' src/seal_hybrid_provider_self_test.c
require_contains 'ML-KEM-768' src/seal_hybrid_provider_self_test.c
require_contains 'ML-KEM-1024' src/seal_hybrid_provider_self_test.c
require_contains 'EVP_PKEY_derive' src/seal_hybrid_provider_self_test.c
require_contains 'EVP_PKEY_encapsulate' src/seal_hybrid_provider_self_test.c
require_contains 'EVP_PKEY_decapsulate' src/seal_hybrid_provider_self_test.c
require_contains 'EVP_PKEY_is_a' src/seal_hybrid_provider_self_test.c
require_contains 'i2d_PUBKEY' src/seal_hybrid_provider_self_test.c
require_contains 'd2i_PUBKEY' src/seal_hybrid_provider_self_test.c
require_contains 'build_hybrid_transcript_aad' src/seal_hybrid_provider_self_test.c
require_contains 'transcript_ml_kem_public_key_label' src/seal_hybrid_provider_self_test.c
require_contains 'record_envelope_provider_crypto_evidence' src/seal_hybrid_provider_self_test.c
require_contains 'hybrid_envelope_commitment_constant_time_compare_cases_total' include/latticra/seal_hybrid_provider_self_test.h
require_contains 'hybrid_transcript_tamper_constant_time_compare_cases_total' include/latticra/seal_hybrid_provider_self_test.h
require_contains 'hybrid_envelope_wrong_pqc_secret_constant_time_compare_cases_total' include/latticra/seal_hybrid_provider_self_test.h
require_contains 'hybrid_envelope_successful_record_tail_cleared_cases_total' include/latticra/seal_hybrid_provider_self_test.h
require_contains 'hybrid_envelope_successful_plaintext_tail_cleared_cases_total' include/latticra/seal_hybrid_provider_self_test.h
require_contains 'ml_kem_keypair_algorithm_identity_verified_cases_total' include/latticra/seal_hybrid_provider_self_test.h
require_contains 'ml_kem_public_key_algorithm_identity_verified_cases_total' include/latticra/seal_hybrid_provider_self_test.h
require_contains 'record_commitment_constant_time_compare == 1u' src/seal_hybrid_provider_self_test.c
require_contains 'buffer_tail_is_zero' src/seal_hybrid_provider_self_test.c
require_contains 'successful_record_tail_cleared != 1u' src/seal_hybrid_provider_self_test.c
require_contains 'successful_plaintext_tail_cleared != 1u' src/seal_hybrid_provider_self_test.c
require_contains 'hybrid_envelope_commitment_constant_time_compare_cases_total++' src/seal_hybrid_provider_self_test.c
require_contains 'hybrid_envelope_successful_record_tail_cleared_cases_total++' src/seal_hybrid_provider_self_test.c
require_contains 'hybrid_envelope_successful_plaintext_tail_cleared_cases_total++' src/seal_hybrid_provider_self_test.c
require_contains 'ml_kem_keypair_algorithm_identity_verified_cases_total++' src/seal_hybrid_provider_self_test.c
require_contains 'ml_kem_public_key_algorithm_identity_verified_cases_total++' src/seal_hybrid_provider_self_test.c
require_contains 'latticra_seal_hybrid_envelope_seal_record' src/seal_hybrid_provider_self_test.c
require_contains 'latticra_seal_hybrid_envelope_open_record' src/seal_hybrid_provider_self_test.c
require_contains 'OPENSSL_cleanse' src/seal_hybrid_provider_self_test.c
require_contains 'secret_material_output_emitted=0' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'hybrid_provider_self_test_present=1' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'NIST-SP-800-90A-REV1' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'hybrid_envelope_provider_crypto_evidence_bound=1' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'hybrid_envelope_provider_crypto_cases_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'hybrid_envelope_commitment_constant_time_compare_cases_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'hybrid_envelope_successful_record_tail_cleared_cases_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'hybrid_envelope_successful_plaintext_tail_cleared_cases_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'ml_kem_keypair_algorithm_identity_verified_cases_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'ml_kem_public_key_algorithm_identity_verified_cases_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'p256_ecdh_peer_public_key_only=1' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'ml_kem_encapsulation_public_key_only_cases_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'ml_kem_ciphertext_tampering_rejected_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'hybrid_envelope_wrong_pqc_secret_rejected_total=3' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'ml_kem_public_key_transcript_bound=1' docs/LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST.md
require_contains 'p256_shared_secret_match=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'p256_peer_public_keys_reimported=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'p256_ecdh_peer_public_key_only=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_shared_secret_match=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_keypair_algorithm_identity_verified_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_public_key_reimported_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_public_key_algorithm_identity_verified_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_encapsulation_public_key_only_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_tampered_ciphertext_shared_secret_mismatch_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_ciphertext_tampering_rejected_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_parameter_sets_tested=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_512_ciphertext_bytes=768' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_768_ciphertext_bytes=1088' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_1024_ciphertext_bytes=1568' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_authenticated=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_records_authenticated_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_provider_crypto_evidence_bound=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_provider_crypto_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_hkdf_provider_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_hkdf_sha256_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_aes_gcm_provider_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_aes_gcm_96bit_nonce_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_aes_gcm_128bit_tag_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_commitment_mac_provider_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_commitment_mac_hmac_sha256_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_commitment_constant_time_compare_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_random_bytes_ex_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_random_bytes_strength_bits_requested=256' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_no_legacy_crypto_fallback_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_successful_record_tail_cleared_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_successful_plaintext_tail_cleared_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_transcript_aad_bound=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_transcript_cases_bound_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_transcript_tampering_rejected_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_transcript_tamper_constant_time_compare_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_wrong_pqc_secret_rejected_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'hybrid_envelope_wrong_pqc_secret_constant_time_compare_cases_total=3' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'provider_algorithm_transcript_bound=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'p256_public_key_transcript_bound=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_public_key_transcript_bound=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_public_key_transcript_bytes_total_nonzero=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_ciphertext_transcript_bound=1' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'ml_kem_ciphertext_transcript_bytes_total=3424' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md
require_contains 'runtime_authority_granted=0' docs/status/SEAL_HYBRID_PROVIDER_SELF_TEST_STATUS.md

cc $CFLAGS $OPENSSL_CFLAGS -Iinclude \
  src/seal_hybrid_envelope.c \
  src/seal_hybrid_provider_self_test.c \
  tests/seal_hybrid_provider_self_test_invariants.c \
  $OPENSSL_LIBS \
  -o "$binary"

"$binary"

printf 'latticra seal hybrid provider self-test: ok\n'

# Latticra Seal Hybrid Envelope Implementation

Status: local substrate encryption implementation.

This lane adds a C substrate encryption surface for Latticra Seal without changing the current ML-KEM implementation gate. The API combines a 32-byte classical shared secret and a 32-byte post-quantum shared secret with OpenSSL provider-backed HKDF-SHA256, then uses the derived 32-byte key with OpenSSL provider-fetched AES-256-GCM.

The high-level `latticra_seal_hybrid_envelope_seal` API generates fresh 32-byte salt and 96-bit GCM nonce material inside the substrate before encryption. `latticra_seal_hybrid_envelope_open` requires the recorded salt, nonce, tag, and AAD and releases plaintext only after authentication succeeds.

Decrypt paths stage OpenSSL's pre-authentication AES-GCM plaintext into internal substrate memory. Caller-owned plaintext output is populated only after tag verification succeeds; the staged plaintext buffer is cleansed before return on both success and authentication failure.

The attached-record API, `latticra_seal_hybrid_envelope_seal_record` and `latticra_seal_hybrid_envelope_open_record`, stores the versioned envelope header, generated salt, generated nonce, authentication tag, ciphertext, and a 32-byte record commitment in one binary record. Record AAD is framed as `LSEHAAD1 || protected-header || caller-aad-length || caller-aad`, so record metadata and caller AAD are authenticated with the ciphertext and callers cannot accidentally drop or swap detached fields.

Attached records append an HMAC-SHA256 commitment over `LSEHCOM1 || record-header || caller-aad-length || caller-aad || ciphertext` under a separate HKDF-SHA256 output label. The commitment input is streamed into HMAC field-by-field rather than assembled as one attacker-sized buffer. Record open verifies this commitment before building record AAD or attempting AES-GCM decryption, so header, tag, ciphertext, caller AAD, nonce, salt, wrong-key, or trailer tampering cannot stage unauthenticated plaintext.

The committed detached API, `latticra_seal_hybrid_envelope_encrypt_committed`, `latticra_seal_hybrid_envelope_decrypt_committed`, `latticra_seal_hybrid_envelope_seal_committed`, and `latticra_seal_hybrid_envelope_open_committed`, keeps the detached salt, nonce, tag, ciphertext, and caller AAD field model while adding a 32-byte HMAC-SHA256 key commitment. The commitment covers `LSEDCOM1 || suite-id || kdf-domain || salt || nonce || tag || caller-aad-length || caller-aad || ciphertext-length || ciphertext` under a separate HKDF-SHA256 output label and is verified before AES-GCM decrypt or detached AAD framing can stage plaintext.

The detached API also frames caller AAD before AES-GCM as `LSEDAAD1 || caller-aad-length || caller-aad`. That keeps low-level detached encryption from authenticating a bare byte string with no substrate context.

The invariant suite includes deterministic known-answer vectors for the fixed hybrid shared secrets, salt, nonce, detached AAD frame, plaintext, HKDF framing, AES-256-GCM result, committed-detached HMAC, and attached-record authentication tag. This pins the construction against accidental changes to the HKDF labels, length framing, info string, detached AAD frame, committed-detached field ordering, record protected-header AAD, GCM nonce handling, ciphertext, or tag.

Detached and attached-record encryption use separate HKDF info labels. Both labels bind the current HKDF-SHA256/AES-256-GCM suite id into the key schedule. This keeps the low-level detached API and the safer attached-record API in distinct, suite-bound KDF domains even when the same hybrid shared secrets, salt, nonce, plaintext, and caller AAD are used in deterministic fixtures.

The HKDF input is role-labeled, algorithm-labeled, and length-framed, binding both the classical and post-quantum shared-secret components in a fixed order. The fixed component labels pin the current substrate suite to a classical 32-byte KEM/shared-secret input and a PQC ML-KEM-shaped 32-byte shared-secret input before any AEAD key is derived; callers still remain responsible for obtaining those shared secrets from approved upstream mechanisms. The two 32-byte components must also be distinct before HKDF can run. Negative invariants reject legacy unlabeled vectors, mutate each component independently, swap the two valid-size components, and reject duplicate classical/PQC component bytes before KDF; each authenticated-input mismatch requires failure before plaintext release.

Attached records encode the cryptographic suite and attached-record KDF domain in the protected header. Those bytes are validated before open and authenticated as AES-GCM AAD with the rest of the protected header. The attached-record HKDF info label also carries the current suite id, so suite 1 records use a suite-bound KDF domain.

Attached-record open validates the record magic, version, flags, suite, KDF domain, and canonical ciphertext length before any framed AAD allocation, HKDF, AES-GCM decrypt, or plaintext release. Malformed records are rejected as records, not downgraded into decrypt attempts.

The record AAD frame uses an explicit label and an eight-byte caller AAD length field before caller AAD bytes. This pins the attached-record AEAD input as a self-describing substrate record rather than a bare concatenation.

The envelope rejects all-zero classical or post-quantum shared-secret buffers before HKDF or random salt/nonce generation. This prevents placeholder or uninitialized material from being accepted as a real hybrid secret.

The envelope also rejects all-zero salt or nonce material before HKDF. Generated seal and attached-record paths use OpenSSL 3 `RAND_bytes_ex` with a 256-bit CSPRNG strength request and retry output if an all-zero salt or nonce is ever observed, while detached and record-open paths fail closed on all-zero caller-supplied or record-carried salt/nonce inputs.

Attached-record open validates record-carried salt and nonce material before building the framed record AAD or deriving the AEAD key. All-zero record salt or nonce inputs are rejected as weak material with no HKDF, no AES-GCM decrypt, and no plaintext release.

Writable outputs are checked for unsafe overlap with input buffers before cryptographic work starts. Detached encrypt/decrypt, generated-salt seal, attached-record seal, and attached-record open reject overlapping output ranges before HKDF, AES-GCM, random salt/nonce generation, record AAD allocation, header writes, tag writes, or plaintext release.

Tamper invariants cover detached ciphertext, detached salt, detached nonce, committed-detached ciphertext, salt, nonce, tag, AAD, and commitment changes, plus attached-record ciphertext, attached-record nonce, attached-record caller AAD, and attached-record commitment changes. Legacy detached tampering must fail AES-GCM authentication, cleanse caller-owned plaintext output, cleanse staged plaintext, and keep plaintext unreleased. Committed-detached and record byte or caller-AAD tampering must fail the key commitment before AES-GCM decryption stages plaintext.

HKDF input buffers are passed through the OpenSSL EVP_KDF HKDF provider API in extract-and-expand mode with SHA-256 bound in the provider parameters. AES-256-GCM is fetched by provider algorithm name with a 96-bit nonce and 128-bit authentication tag bound through the EVP AEAD controls. HKDF input material is cleansed before the KDF helper returns. The derived AEAD key is cleansed before encrypt or decrypt returns, including authentication-failure paths where plaintext is not released.

seal_hybrid_envelope_present=1
seal_hybrid_envelope_profile=latticra-seal-hybrid-envelope/0.1
seal_hybrid_envelope_cli_command=latticra-seal hybrid
kdf_algorithm=HKDF-SHA256
aead_algorithm=AES-256-GCM
standards_source=NIST-FIPS-197,NIST-SP-800-38D,RFC-5869,NIST-SP-800-56C-REV2,RFC-2104,NIST-SP-800-227
hkdf_provider_api_used=1
hkdf_extract_expand_standard_api_used=1
hkdf_sha256_digest_bound=1
hkdf_manual_fallback_used=0
aes_gcm_provider_api_used=1
aes_gcm_provider_cipher_fetched=1
aes_gcm_96bit_nonce_configured=1
aes_gcm_128bit_tag_bound=1
aes_gcm_static_cipher_fallback_used=0
random_bytes_ex_api_used=1
random_bytes_strength_bits_requested=256
random_bytes_manual_fallback_used=0
generated_salt_csprng_success=1
generated_nonce_csprng_success=1
generated_salt_random_bytes=32
generated_nonce_random_bytes=12
kdf_domain_separated=1
detached_kdf_domain_reported=1
attached_record_kdf_domain_reported=1
detached_suite_id=1
detached_suite_kdf_bound=1
classical_shared_secret_bytes=32
pqc_shared_secret_bytes=32
salt_bytes=32
nonce_bytes=12
tag_bytes=16
detached_commitment_bytes=32
detached_commitment_label=LSEDCOM1
record_header_bytes=80
record_protected_header_bytes=64
record_commitment_bytes=32
record_magic=LSEHENV1
record_version=1
record_suite_id=1
record_suite_authenticated=1
record_kdf_domain_authenticated=1
record_suite_kdf_bound=1
record_salt_nonce_nonzero=1
record_header_shape_validated=1
malformed_record_rejected_before_kdf=1
detached_committed_api_present=1
detached_key_commitment_present=1
detached_commitment_key_kdf_bound=1
detached_commitment_verified=1
detached_commitment_checked_before_decrypt=1
detached_commitment_caller_aad_bound=1
detached_commitment_input_streamed=1
detached_commitment_key_material_zeroized=1
record_key_commitment_present=1
record_commitment_key_kdf_bound=1
record_commitment_verified=1
record_commitment_checked_before_decrypt=1
record_commitment_caller_aad_bound=1
record_commitment_input_streamed=1
record_commitment_key_material_zeroized=1
detached_aad_label=LSEDAAD1
detached_aad_frame_bytes=16
detached_aad_framed=1
detached_aad_label_authenticated=1
detached_caller_aad_length_authenticated=1
detached_caller_aad_authenticated=1
record_aad_label=LSEHAAD1
record_aad_frame_bytes=80
record_aad_framed=1
record_aad_label_authenticated=1
record_caller_aad_authenticated=1
hybrid_classical_pqc_secret_required=1
classical_shared_secret_bound=1
pqc_shared_secret_bound=1
hybrid_secret_length_framed=1
hybrid_secret_role_labeled=1
hybrid_secret_algorithm_labeled=1
hybrid_secret_order_bound=1
hybrid_secret_components_distinct=1
nonzero_classical_shared_secret_required=1
nonzero_pqc_shared_secret_required=1
nonzero_salt_required=1
nonzero_nonce_required=1
weak_shared_secret_rejected_before_kdf=1
duplicate_hybrid_shared_secret_rejected_before_kdf=1
weak_salt_rejected_before_kdf=1
weak_nonce_rejected_before_kdf=1
generated_salt_nonce_nonzero_required=1
failed_seal_clears_ciphertext=1
failed_seal_clears_salt=1
failed_seal_clears_nonce=1
failed_seal_clears_tag=1
failed_encrypt_clears_ciphertext=1
failed_encrypt_clears_tag=1
failed_commitment_output_cleared=1
failed_plaintext_output_cleared=1
failed_record_output_cleared=1
unsafe_buffer_overlap_rejected=1
hkdf_intermediate_material_zeroized=1
associated_data_supported=1
authenticated_decryption_required=1
unauthenticated_plaintext_staged=1
staged_plaintext_cleared=1
plaintext_released_after_authentication=1
detached_suite_id=1
detached_suite_kdf_bound=1
substrate_generates_salt=1
substrate_generates_nonce=1
detached_salt_caller_supplied_reported=1
detached_nonce_caller_supplied_reported=1
attached_record_salt_generated_reported=1
attached_record_nonce_generated_reported=1
seal_open_api_present=1
attached_record_api_present=1
detached_committed_api_present=1
attached_record_header_validated_before_open=1
attached_record_authenticated_before_plaintext_release=1
unauthenticated_plaintext_staged=1
staged_plaintext_cleared=1
plaintext_released_after_authentication=1
record_header_authenticated=1
detached_key_commitment_present=1
detached_commitment_key_kdf_bound=1
detached_commitment_verified=1
detached_commitment_checked_before_decrypt=1
detached_commitment_caller_aad_bound=1
detached_commitment_input_streamed=1
detached_commitment_key_material_zeroized=1
record_key_commitment_present=1
record_commitment_key_kdf_bound=1
record_commitment_verified=1
record_commitment_checked_before_decrypt=1
record_commitment_caller_aad_bound=1
record_commitment_input_streamed=1
record_commitment_key_material_zeroized=1
record_suite_validated_before_open=1
record_suite_authenticated=1
record_kdf_domain_authenticated=1
record_suite_kdf_bound=1
record_salt_nonce_nonzero=1
record_header_shape_validated=1
malformed_record_rejected_before_kdf=1
detached_aad_framed=1
detached_aad_label_authenticated=1
detached_caller_aad_length_authenticated=1
detached_caller_aad_authenticated=1
record_aad_framed=1
record_aad_label_authenticated=1
record_caller_aad_authenticated=1
classical_shared_secret_bound=1
pqc_shared_secret_bound=1
hybrid_secret_length_framed=1
hybrid_secret_role_labeled=1
hybrid_secret_algorithm_labeled=1
hybrid_secret_order_bound=1
hybrid_secret_components_distinct=1
known_answer_vector_present=1
hybrid_secret_unlabeled_legacy_vector_rejected=1
hybrid_secret_algorithm_unlabeled_legacy_vector_rejected=1
hybrid_secret_component_mismatch_rejected=1
hybrid_secret_component_swap_rejected=1
duplicate_hybrid_shared_secret_rejected_before_kdf=1
detached_ciphertext_tampering_rejected=1
detached_salt_tampering_rejected=1
detached_nonce_tampering_rejected=1
detached_committed_ciphertext_tampering_rejected_before_decrypt=1
detached_committed_salt_tampering_rejected_before_decrypt=1
detached_committed_nonce_tampering_rejected_before_decrypt=1
detached_committed_tag_tampering_rejected_before_decrypt=1
detached_committed_aad_tampering_rejected_before_decrypt=1
detached_committed_commitment_tampering_rejected_before_decrypt=1
record_ciphertext_tampering_rejected=1
record_nonce_tampering_rejected=1
record_commitment_tampering_rejected=1
record_caller_aad_tampering_rejected_before_decrypt=1
known_answer_vector_ciphertext_bytes=66
known_answer_vector_tag_bytes=16
detached_committed_known_answer_vector_present=1
detached_committed_known_answer_vector_commitment_bytes=32
record_known_answer_vector_present=1
record_known_answer_vector_bytes=178
record_known_answer_vector_tag_bytes=16
record_known_answer_vector_commitment_bytes=32
failed_decrypt_clears_plaintext=1
failed_record_seal_clears_record=1
failed_record_open_clears_plaintext=1
failed_plaintext_output_cleared=1
failed_record_output_cleared=1
hkdf_intermediate_material_zeroized=1
key_material_zeroization_required=1
secret_material_emitted=0
cli_secret_material_output=redacted
cli_salt_output=redacted
cli_nonce_output=redacted
cli_ciphertext_output=redacted
cli_tag_output=redacted
cli_record_output=redacted
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
test_runner=sh scripts/test-latticra-seal-hybrid-envelope.sh

The envelope is intentionally a hybrid envelope primitive, not an ML-KEM implementation claim. Q-Seal still tracks ML-KEM parameter sets, vectors, ACVP intake, side-channel review, zeroization review, and source binding before ML-KEM key generation, encapsulation, or decapsulation can be promoted.

Operational constraints:

- Callers that use the detached low-level API must provide fresh nonce material for each encryption under the same derived key.
- Callers that use the attached-record API receive generated salt and nonce material inside the record header.
- Detached and attached-record encryption use distinct HKDF info labels and
  report the active KDF domain.
- Detached HKDF info binds the current suite id into the derived key domain.
- Attached records bind the cryptographic suite and KDF domain into the
  authenticated protected header.
- Attached-record HKDF info binds the current record suite id into the derived
  key domain.
- Attached records append a 32-byte HMAC-SHA256 commitment under a separate
  HKDF label from the AES-256-GCM key.
- Attached-record commitments bind caller AAD length and caller AAD bytes
  before AES-GCM decrypt can run.
- Attached-record open verifies the record commitment before framed record AAD
  allocation, AES-GCM decrypt, staged plaintext, or plaintext release.
- Committed detached seal/encrypt returns a 32-byte HMAC-SHA256 commitment
  beside detached salt, nonce, tag, and ciphertext fields.
- Committed detached open/decrypt verifies the detached commitment before
  detached AAD framing, AES-GCM decrypt, staged plaintext, or plaintext release.
- Detached commitments bind the suite id, detached KDF domain, salt, nonce, tag,
  caller AAD length, caller AAD bytes, ciphertext length, and ciphertext bytes.
- Attached-record open rejects malformed magic, version, flag, suite, KDF
  domain, truncation, and length-field cases before framed AAD allocation,
  HKDF, AES-GCM decrypt, or plaintext release.
- Attached-record open rejects all-zero record-carried salt or nonce material
  before framed AAD allocation, HKDF, AES-GCM decrypt, or plaintext release.
- Attached records frame AEAD AAD with a record label, protected header, caller
  AAD length, and caller AAD before authentication.
- Detached encrypt/decrypt frames caller AAD with a detached label and caller
  AAD length before authentication.
- Reports distinguish caller-supplied detached salt/nonce material from
  attached-record generated salt/nonce material.
- Classical and post-quantum shared-secret inputs must both be present,
  32 bytes long, and nonzero before HKDF can run.
- Classical and post-quantum shared-secret inputs are both length-framed into
  the HKDF input with explicit component role labels; legacy unlabeled vectors
  and changes to either component fail AES-GCM authentication.
- The hybrid combiner treats the classical and post-quantum components as
  ordered inputs; swapping the valid-size components fails AES-GCM
  authentication before plaintext release.
- The hybrid combiner rejects identical classical and post-quantum component
  bytes before HKDF, so a caller cannot accidentally collapse the hybrid model
  into a single shared-secret lane.
- Salt and nonce material must be present, correctly sized, and nonzero before
  HKDF can run.
- Detached ciphertext, salt, or nonce tampering must fail authentication before
  plaintext release.
- Committed detached ciphertext, salt, nonce, tag, AAD, or commitment tampering
  must fail commitment verification before AES-GCM decrypt, staged plaintext, or
  plaintext release.
- Attached-record ciphertext or nonce tampering must fail authentication before
  plaintext release.
- Attached-record commitment tampering must fail commitment verification before
  AES-GCM decrypt, staged plaintext, or plaintext release.
- Attached-record caller AAD tampering must fail commitment verification before
  AES-GCM decrypt, staged plaintext, or plaintext release.
- Callers must bind policy, manifest, or transcript material through AAD.
- Decryption stages AES-GCM plaintext internally and releases it to
  caller-owned output only after the authentication tag verifies.
- Internal staged plaintext is cleansed before decrypt returns.
- Failed detached seal calls clear caller-provided salt, nonce, ciphertext, and
  tag output buffers when those buffers are available.
- Failed detached encrypt calls clear caller-provided ciphertext and tag output
  buffers when those buffers are available.
- Failed decrypt and record-open calls clear caller-provided plaintext buffers
  when a buffer is available and report `failed_plaintext_output_cleared=1`
  on those failure paths.
- Failed record-seal calls clear the provided record buffer capacity when a
  record buffer is available and report `failed_record_output_cleared=1`
  on those failure paths.
- Writable output buffers must not overlap plaintext, ciphertext, AAD, key
  material, salt, nonce, tag, or record inputs; unsafe overlap is rejected
  before HKDF, AES-GCM, record AAD allocation, or random salt/nonce generation.
- HKDF input buffers are passed through OpenSSL EVP_KDF HKDF extract-and-expand
  with SHA-256 bound in provider parameters, and are cleansed on every KDF
  return path.
- AES-256-GCM is fetched through the OpenSSL provider cipher API, configured
  with a 96-bit nonce and 128-bit tag, and rejects static-cipher fallback on
  the OpenSSL 3 provider path.
- Generated salt and nonce buffers are filled through OpenSSL 3
  `RAND_bytes_ex` with a 256-bit strength request, are checked for all-zero
  output, and are retried before failing closed.
- The implementation zeroizes derived key material and never reports or emits shared secrets.
- FIPS and production cryptography claims remain closed until a validated module boundary and release gate exist.

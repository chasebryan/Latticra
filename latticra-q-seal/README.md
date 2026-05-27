# Latticra Q-Seal

Status: clean-room quantum-resistant cryptography subsystem foundation
Date: 2026-05-27

Latticra Q-Seal is the formal Latticra subsystem for clean-room, standards-first post-quantum cryptography work.

This directory is the dedicated home for Q-Seal source, headers, tests, docs, and local validation. The current foundation does not implement encryption, key encapsulation, signatures, key generation, key storage, provider linking, production cryptography, FIPS validation, network behavior, host mutation, or runtime authority.

## Directory Layout

```text
latticra-q-seal/
  README.md
  evidence/Q_SEAL_READINESS.md
  evidence/ML_KEM_ACVP_INTAKE.md
  evidence/ML_KEM_API_MISUSE_RESISTANCE.md
  evidence/ML_KEM_CODE_OWNER_REVIEW.md
  evidence/ML_KEM_CI_PROMOTION_EVIDENCE.md
  evidence/ML_KEM_CONSTANT_TIME_REVIEW.md
  evidence/ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
  evidence/ML_KEM_IMPLEMENTATION_FRAME.md
  evidence/ML_KEM_KAT_MANIFEST.md
  evidence/ML_KEM_MEMORY_SAFETY_EVIDENCE.md
  evidence/ML_KEM_NEGATIVE_TEST_EVIDENCE.md
  evidence/ML_KEM_PROVIDER_DIFFERENTIAL.md
  evidence/ML_KEM_RANDOMNESS_SOURCE.md
  evidence/ML_KEM_SECRET_STATE_CONTRACT.md
  evidence/ML_KEM_SIDE_CHANNEL_REVIEW.md
  evidence/ML_KEM_SOURCE_DIGEST_MANIFEST.md
  evidence/ML_KEM_VECTOR_SCHEMA.md
  evidence/ML_KEM_VECTOR_SOURCE.md
  evidence/ML_KEM_ZEROIZATION_EVIDENCE.md
  include/latticra/q_seal.h
  include/latticra/q_seal_readiness.h
  include/latticra/q_seal_ml_kem.h
  include/latticra/q_seal_ml_kem_acvp_intake.h
  include/latticra/q_seal_ml_kem_api_misuse_resistance.h
  include/latticra/q_seal_ml_kem_code_owner_review.h
  include/latticra/q_seal_ml_kem_ci_promotion_evidence.h
  include/latticra/q_seal_ml_kem_constant_time_review.h
  include/latticra/q_seal_ml_kem_evidence_gate.h
  include/latticra/q_seal_ml_kem_implementation_binding_manifest.h
  include/latticra/q_seal_ml_kem_implementation_frame.h
  include/latticra/q_seal_ml_kem_memory_safety_evidence.h
  include/latticra/q_seal_ml_kem_negative_test_evidence.h
  include/latticra/q_seal_ml_kem_provider_differential.h
  include/latticra/q_seal_ml_kem_randomness_source.h
  include/latticra/q_seal_ml_kem_secret_state_contract.h
  include/latticra/q_seal_ml_kem_side_channel_review.h
  include/latticra/q_seal_ml_kem_source_digest_manifest.h
  include/latticra/q_seal_ml_kem_vector_schema.h
  include/latticra/q_seal_ml_kem_vector_source.h
  include/latticra/q_seal_ml_kem_zeroization_evidence.h
  src/q_seal.c
  src/q_seal_readiness.c
  src/q_seal_ml_kem.c
  src/q_seal_ml_kem_acvp_intake.c
  src/q_seal_ml_kem_api_misuse_resistance.c
  src/q_seal_ml_kem_code_owner_review.c
  src/q_seal_ml_kem_ci_promotion_evidence.c
  src/q_seal_ml_kem_constant_time_review.c
  src/q_seal_ml_kem_evidence_gate.c
  src/q_seal_ml_kem_implementation_binding_manifest.c
  src/q_seal_ml_kem_implementation_frame.c
  src/q_seal_ml_kem_memory_safety_evidence.c
  src/q_seal_ml_kem_negative_test_evidence.c
  src/q_seal_ml_kem_provider_differential.c
  src/q_seal_ml_kem_randomness_source.c
  src/q_seal_ml_kem_secret_state_contract.c
  src/q_seal_ml_kem_side_channel_review.c
  src/q_seal_ml_kem_source_digest_manifest.c
  src/q_seal_ml_kem_vector_schema.c
  src/q_seal_ml_kem_vector_source.c
  src/q_seal_ml_kem_zeroization_evidence.c
  tests/q_seal_foundation_invariants.c
  tests/q_seal_readiness_invariants.c
  tests/q_seal_ml_kem_parameters_invariants.c
  tests/q_seal_ml_kem_acvp_intake_invariants.c
  tests/q_seal_ml_kem_api_misuse_resistance_invariants.c
  tests/q_seal_ml_kem_code_owner_review_invariants.c
  tests/q_seal_ml_kem_ci_promotion_evidence_invariants.c
  tests/q_seal_ml_kem_constant_time_review_invariants.c
  tests/q_seal_ml_kem_evidence_gate_invariants.c
  tests/q_seal_ml_kem_implementation_binding_manifest_invariants.c
  tests/q_seal_ml_kem_implementation_frame_invariants.c
  tests/q_seal_ml_kem_memory_safety_evidence_invariants.c
  tests/q_seal_ml_kem_negative_test_evidence_invariants.c
  tests/q_seal_ml_kem_provider_differential_invariants.c
  tests/q_seal_ml_kem_randomness_source_invariants.c
  tests/q_seal_ml_kem_secret_state_contract_invariants.c
  tests/q_seal_ml_kem_side_channel_review_invariants.c
  tests/q_seal_ml_kem_source_digest_manifest_invariants.c
  tests/q_seal_ml_kem_vector_schema_invariants.c
  tests/q_seal_ml_kem_vector_source_invariants.c
  tests/q_seal_ml_kem_zeroization_evidence_invariants.c
  scripts/test-latticra-q-seal-foundation.sh
  scripts/test-latticra-q-seal-readiness.sh
  scripts/test-latticra-q-seal-ml-kem-parameters.sh
  scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
  scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
  scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
  scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
  scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
  scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
  scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
  scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
  scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
  scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
  scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
  scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
  scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
  scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
  scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
  scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
  scripts/test-latticra-q-seal-ml-kem-vector-source.sh
  scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
  docs/LATTICRA_Q_SEAL_FOUNDATION.md
  docs/LATTICRA_Q_SEAL_READINESS.md
  docs/LATTICRA_Q_SEAL_ML_KEM_PARAMETERS.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ACVP_INTAKE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_API_MISUSE_RESISTANCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_CODE_OWNER_REVIEW.md
  docs/LATTICRA_Q_SEAL_ML_KEM_CI_PROMOTION_EVIDENCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_CONSTANT_TIME_REVIEW.md
  docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_GATE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_BINDING_MANIFEST.md
  docs/LATTICRA_Q_SEAL_ML_KEM_IMPLEMENTATION_FRAME.md
  docs/LATTICRA_Q_SEAL_ML_KEM_MEMORY_SAFETY_EVIDENCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_NEGATIVE_TEST_EVIDENCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL.md
  docs/LATTICRA_Q_SEAL_ML_KEM_RANDOMNESS_SOURCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SECRET_STATE_CONTRACT.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SIDE_CHANNEL_REVIEW.md
  docs/LATTICRA_Q_SEAL_ML_KEM_SOURCE_DIGEST_MANIFEST.md
  docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SCHEMA.md
  docs/LATTICRA_Q_SEAL_ML_KEM_VECTOR_SOURCE.md
  docs/LATTICRA_Q_SEAL_ML_KEM_ZEROIZATION_EVIDENCE.md
```

## Foundation Fields

```text
latticra_q_seal_present=1
formal_title=Latticra Q-Seal
subsystem_directory=latticra-q-seal
q_seal_profile=latticra-q-seal-foundation/0.1
clean_room_profile=latticra-clean-room-pqc/0.1
source_boundary=clean-room-no-apple-code
implementation_lane=standards-first-no-effect
nist_fips_203_ml_kem_tracked=1
nist_fips_204_ml_dsa_tracked=1
nist_fips_205_slh_dsa_backup_tracked=1
ml_kem_work_packet_next=1
ml_dsa_work_packet_planned=1
liboqs_comparison_provider_allowed=1
apple_corecrypto_reference_allowed=1
apple_corecrypto_code_copied=0
provider_linked=0
key_generation_performed=0
encapsulation_performed=0
decapsulation_performed=0
signing_performed=0
verification_performed=0
encryption_performed=0
production_crypto_claim_allowed=0
runtime_authority_granted=0
```

## ML-KEM Evidence Gate

```text
ml_kem_evidence_gate_present=1
standards_source=NIST-FIPS-203
standards_errata_state=errata-review-required
parameter_sets_recorded=1
known_answer_test_manifest_present=1
known_answer_vectors_verified=0
acvp_vector_review_recorded=0
constant_time_review_recorded=0
side_channel_review_recorded=0
required_evidence_items_total=16
required_evidence_items_satisfied=3
operations_enabled=0
production_crypto_claim_allowed=0
status=ml-kem-evidence-gate-fail-closed
```

## ACVP Intake

```text
ml_kem_acvp_intake_present=1
acvp_document=NIST-ACVP-ML-KEM-JSON
algorithm=ML-KEM
revision=FIPS203
keygen_mode_required=1
encap_decap_mode_required=1
vector_json_loaded=0
network_session_enabled=0
acvp_submission_allowed=0
operation_execution_allowed=0
required_intake_items_total=13
required_intake_items_satisfied=9
status=ml-kem-acvp-intake-offline-blocked
```

## Provider Differential

```text
ml_kem_provider_differential_present=1
candidate_provider=liboqs-comparison-only
provider_comparison_only=1
provider_linking_enabled=0
provider_runtime_used=0
positive_vector_comparison_recorded=0
negative_vector_comparison_recorded=0
mismatch_triage_recorded=0
operation_execution_allowed=0
required_comparison_items_total=10
required_comparison_items_satisfied=3
status=ml-kem-provider-differential-blocked
```

## ML-KEM Vector Schema

```text
ml_kem_vector_schema_present=1
acvp_document=NIST-ACVP-ML-KEM-JSON
algorithm_ml_kem_recorded=1
revision_fips203_recorded=1
keygen_mode_schema_recorded=1
encap_decap_mode_schema_recorded=1
keygen_prompt_fields_recorded=1
keygen_response_fields_recorded=1
encap_decap_prompt_fields_recorded=1
encap_decap_response_fields_recorded=1
aft_test_type_recorded=1
val_test_type_recorded=1
implicit_rejection_case_recorded=1
vector_bundle_loaded=0
vector_json_parser_implemented=0
response_generation_enabled=0
vector_execution_enabled=0
required_schema_items_total=18
required_schema_items_satisfied=15
status=ml-kem-vector-schema-blocked
```

## ML-KEM Vector Source Intake

```text
ml_kem_vector_source_intake_present=1
approved_source_authority=NIST-ACVP-or-reviewed-equivalent
digest_algorithm=SHA-256
source_freshness_policy_recorded=1
bundle_source_url_recorded=0
bundle_digest_recorded=0
bundle_license_review_recorded=0
bundle_hash_verified=0
bundle_schema_crosscheck_recorded=0
errata_review_binding_recorded=0
bundle_fetch_performed=0
bundle_imported=0
network_fetch_enabled=0
vector_processing_allowed=0
required_source_items_total=14
required_source_items_satisfied=5
status=ml-kem-vector-source-intake-blocked
```

## ML-KEM Negative-Test Evidence

```text
ml_kem_negative_test_evidence_present=1
acvp_source=NIST-ACVP-ML-KEM
evidence_scope=ML-KEM-malformed-input-negative-vector-behavior
acvp_ml_kem_schema_tracked=1
vector_schema_bound=1
vector_source_bound=1
malformed_ciphertext_tests_required=1
malformed_key_tests_required=1
negative_replay_tests_required=1
length_validation_tests_recorded=0
encoding_canonicality_tests_recorded=0
invalid_ciphertext_tests_recorded=0
invalid_public_key_tests_recorded=0
invalid_secret_key_tests_recorded=0
decapsulation_failure_tests_recorded=0
implicit_rejection_tests_recorded=0
fuzzing_corpus_recorded=0
negative_tests_executed=0
parser_execution_allowed=0
required_negative_test_items_total=18
required_negative_test_items_satisfied=7
status=ml-kem-negative-test-evidence-blocked
```

## ML-KEM Memory-Safety Evidence

```text
ml_kem_memory_safety_evidence_present=1
secure_development_source=NIST-SP-800-218-SSDF
evidence_scope=ML-KEM-buffer-bounds-integer-lifetime-and-secret-memory-safety
fips_140_3_software_security_tracked=1
nist_ssdf_source_tracked=1
bounded_buffer_policy_required=1
fixed_capacity_api_policy_required=1
allocation_policy_required=1
size_overflow_checks_recorded=0
bounds_check_review_recorded=0
integer_overflow_review_recorded=0
sanitizer_asan_ubsan_recorded=0
static_analysis_recorded=0
fuzz_memory_safety_recorded=0
memory_safety_tests_executed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
required_memory_safety_items_total=20
required_memory_safety_items_satisfied=8
status=ml-kem-memory-safety-evidence-blocked
```

## ML-KEM API Misuse Resistance

```text
ml_kem_api_misuse_resistance_present=1
secure_development_source=NIST-SP-800-218-SSDF
resistance_scope=ML-KEM-public-api-parameter-buffer-key-and-error-misuse-resistance
explicit_algorithm_identifier_required=1
parameter_set_validation_required=1
buffer_length_preflight_required=1
typed_key_material_required=1
no_implicit_rng_required=1
error_taxonomy_recorded=0
api_state_machine_recorded=0
misuse_case_matrix_recorded=0
wrong_parameter_set_tests_recorded=0
null_and_overlap_tests_recorded=0
api_misuse_tests_executed=0
public_api_execution_allowed=0
required_api_misuse_items_total=21
required_api_misuse_items_satisfied=11
status=ml-kem-api-misuse-resistance-blocked
```

## ML-KEM Source Digest Manifest

```text
ml_kem_source_digest_manifest_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
digest_algorithm=SHA-256
source_boundary=clean-room-no-apple-code
fips_203_algorithm_bound=1
ssdf_source_integrity_bound=1
clean_room_source_boundary_recorded=1
planned_source_units_count=9
planned_test_units_count=9
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
digest_template_recorded=1
hash_command_policy_recorded=1
third_party_source_denial_recorded=1
implementation_files_created=0
source_file_digests_recorded=0
test_file_digests_recorded=0
build_script_digests_recorded=0
reviewed_digest_receipt_recorded=0
reproducible_source_snapshot_recorded=0
digest_verification_ci_recorded=0
operation_execution_allowed=0
required_digest_items_total=20
required_digest_items_satisfied=14
status=ml-kem-source-digest-manifest-blocked
```

## ML-KEM Code Owner Review

```text
ml_kem_code_owner_review_evidence_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
review_scope=ML-KEM-clean-room-source-review-before-promotion
clean_room_review_policy_recorded=1
implementation_binding_manifest_bound=1
source_digest_manifest_bound=1
ci_promotion_evidence_bound=1
dual_reviewer_required=1
cryptography_reviewer_required=1
security_reviewer_required=1
code_owner_file_required=1
reviewer_independence_required=1
standards_traceability_required=1
side_channel_reviewer_required=1
reviewer_identities_recorded=0
code_owner_file_recorded=0
cryptography_review_recorded=0
security_review_recorded=0
standards_traceability_review_recorded=0
side_channel_review_recorded=0
source_digest_review_recorded=0
blocking_findings_closed=0
approval_receipt_recorded=0
operation_execution_allowed=0
required_review_items_total=23
required_review_items_satisfied=14
status=ml-kem-code-owner-review-blocked
```

## ML-KEM CI Promotion Evidence

```text
ml_kem_ci_promotion_evidence_present=1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203-and-SP-800-227
promotion_scope=ML-KEM-evidence-gates-before-implementation-promotion
ssdf_secure_build_gate_recorded=1
fips_203_parameter_gate_bound=1
sp_800_227_kem_usage_gate_bound=1
make_quality_security_standards_bound=1
local_wrapper_scripts_recorded=1
qseal_subsystem_scripts_recorded=1
readiness_gate_bound=1
implementation_binding_manifest_bound=1
kat_acvp_gate_passing_recorded=0
constant_time_gate_passing_recorded=0
memory_safety_gate_passing_recorded=0
side_channel_gate_passing_recorded=0
negative_test_gate_passing_recorded=0
provider_differential_gate_passing_recorded=0
implementation_binding_ci_result_recorded=0
promotion_workflow_recorded=0
release_claim_gate_recorded=0
signed_artifact_receipt_recorded=0
operation_execution_allowed=0
required_promotion_items_total=19
required_promotion_items_satisfied=9
status=ml-kem-ci-promotion-evidence-blocked
```

## ML-KEM Constant-Time Review

```text
ml_kem_constant_time_review_present=1
analysis_policy=no-secret-dependent-control-flow-or-addresses
secret_dependent_branch_forbidden=1
secret_dependent_memory_index_forbidden=1
secret_dependent_loop_bound_forbidden=1
secret_dependent_early_return_forbidden=1
constant_time_compare_required=1
decapsulation_implicit_rejection_required=1
compiler_optimization_review_required=1
dudect_measurement_recorded=0
ctgrind_or_static_analysis_recorded=0
generated_assembly_review_recorded=0
optimizer_flag_review_recorded=0
secret_state_inventory_bound=0
negative_timing_test_recorded=0
cross_platform_timing_review_recorded=0
formal_reviewer_signoff_recorded=0
ci_constant_time_gate_recorded=0
implementation_binding_recorded=0
implementation_promotion_allowed=0
operation_execution_allowed=0
required_review_items_total=18
required_review_items_satisfied=8
status=ml-kem-constant-time-review-blocked
```

## ML-KEM Randomness Source

```text
ml_kem_randomness_source_contract_present=1
random_bit_generation_source=NIST-SP-800-90A-and-NIST-SP-800-90B
keygen_seed_material_required=1
encapsulation_seed_material_required=1
deterministic_test_seed_separation_required=1
entropy_source_inventory_recorded=0
entropy_source_validation_recorded=0
drbg_selection_recorded=0
drbg_security_strength_recorded=0
seed_derivation_policy_recorded=0
reseed_policy_recorded=0
prediction_resistance_policy_recorded=0
health_tests_policy_recorded=0
failure_mode_policy_recorded=0
platform_rng_boundary_recorded=0
random_bytes_generated=0
random_bit_generation_allowed=0
key_generation_randomness_allowed=0
encapsulation_randomness_allowed=0
required_randomness_items_total=18
required_randomness_items_satisfied=6
status=ml-kem-randomness-source-blocked
```

## ML-KEM Zeroization Evidence

```text
ml_kem_zeroization_evidence_present=1
module_security_source=NIST-FIPS-140-3-zeroization-requirements
zeroization_scope=ML-KEM-secret-intermediates-key-and-seed-material
fips_140_3_zeroization_tracked=1
secret_state_contract_bound=1
zeroization_required=1
secret_material_inventory_required=1
compiler_barrier_required=1
zeroization_primitive_selected=0
zeroization_primitive_implemented=0
dead_store_elimination_review_recorded=0
volatile_or_intrinsic_strategy_recorded=0
stack_heap_register_clear_policy_recorded=0
error_path_zeroization_recorded=0
decapsulation_failure_zeroization_recorded=0
test_harness_memory_scan_recorded=0
generated_assembly_review_recorded=0
zeroization_performed=0
secret_material_handling_allowed=0
required_zeroization_items_total=19
required_zeroization_items_satisfied=6
status=ml-kem-zeroization-evidence-blocked
```

## ML-KEM Side-Channel Review

```text
ml_kem_side_channel_review_present=1
module_security_source=NIST-FIPS-140-3-non-invasive-security-posture
review_scope=ML-KEM-keygen-encap-decap-side-channel-surface
fips_140_3_non_invasive_security_tracked=1
constant_time_review_bound=1
secret_state_contract_bound=1
power_analysis_review_required=1
timing_leakage_review_required=1
cache_access_review_required=1
leakage_model_recorded=0
power_analysis_test_recorded=0
timing_measurement_recorded=0
cache_access_analysis_recorded=0
fault_injection_review_recorded=0
microarchitectural_leakage_review_recorded=0
compiler_artifact_review_recorded=0
side_channel_tests_executed=0
implementation_promotion_allowed=0
operation_execution_allowed=0
required_review_items_total=19
required_review_items_satisfied=7
status=ml-kem-side-channel-review-blocked
```

## Implementation Binding Manifest

```text
ml_kem_implementation_binding_manifest_present=1
standards_basis=NIST-FIPS-203-and-SP-800-227
source_boundary=clean-room-no-apple-code
planned_source_units_count=9
planned_test_units_count=9
fips_203_algorithm_bound=1
sp_800_227_kem_usage_bound=1
kat_manifest_bound=1
acvp_intake_bound=1
vector_schema_bound=1
vector_source_bound=1
negative_test_evidence_bound=1
memory_safety_evidence_bound=1
api_misuse_resistance_bound=1
constant_time_review_bound=1
randomness_source_bound=1
zeroization_evidence_bound=1
side_channel_review_bound=1
provider_differential_bound=1
secret_state_contract_bound=1
ci_promotion_evidence_bound=1
implementation_code_present=0
keygen_binding_approved=0
encaps_binding_approved=0
decaps_binding_approved=0
operation_execution_allowed=0
required_binding_items_total=26
required_binding_items_satisfied=21
status=ml-kem-implementation-binding-blocked
```

## Implementation Frame

```text
ml_kem_implementation_frame_present=1
source_boundary=clean-room-no-apple-code
planned_module_count=9
implementation_code_present=0
constant_time_design_recorded=0
zeroization_design_recorded=0
test_vector_binding_recorded=0
formal_review_recorded=0
operations_enabled=0
required_design_items_total=12
required_design_items_satisfied=3
status=ml-kem-implementation-frame-blocked
```

## Secret-State Contract

```text
ml_kem_secret_state_contract_present=1
source_boundary=clean-room-no-apple-code
secret_dependent_branch_forbidden=1
secret_indexed_memory_forbidden=1
secret_dependent_early_return_forbidden=1
constant_time_compare_recorded=0
constant_time_decapsulation_recorded=0
zeroization_primitive_implemented=0
shared_secret_emitted=0
operations_enabled=0
required_secret_state_items_total=19
required_secret_state_items_satisfied=4
status=ml-kem-secret-state-contract-blocked
```

## Readiness Profile

```text
q_seal_readiness_profile_present=1
standards_basis=NIST-FIPS-203-and-NIST-ACVP-ML-KEM
source_boundary=clean-room-no-apple-code
readiness_state=design-frame-ready-runtime-crypto-blocked
foundation_present=1
ml_kem_parameters_present=1
evidence_gate_present=1
acvp_intake_present=1
vector_schema_present=1
vector_source_intake_present=1
negative_test_evidence_present=1
memory_safety_evidence_present=1
api_misuse_resistance_present=1
source_digest_manifest_present=1
code_owner_review_present=1
ci_promotion_evidence_present=1
constant_time_review_present=1
randomness_source_contract_present=1
zeroization_evidence_present=1
side_channel_review_present=1
provider_differential_present=1
implementation_binding_manifest_present=1
implementation_frame_present=1
secret_state_contract_present=1
components_total=20
components_present=20
runtime_blockers_total=18
required_readiness_items_total=328
required_readiness_items_satisfied=158
design_frame_integration_ready=1
runtime_crypto_ready=0
operations_enabled=0
shared_secret_emitted=0
production_crypto_claim_allowed=0
runtime_authority_granted=0
status=q-seal-readiness-profile-blocked
```

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-foundation.sh
sh scripts/test-latticra-q-seal-foundation.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-readiness.sh
sh scripts/test-latticra-q-seal-readiness.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-parameters.sh
sh scripts/test-latticra-q-seal-ml-kem-parameters.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-evidence-gate.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh scripts/test-latticra-q-seal-ml-kem-acvp-intake.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-schema.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-vector-source.sh
sh scripts/test-latticra-q-seal-ml-kem-vector-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-negative-test-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-memory-safety-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh scripts/test-latticra-q-seal-ml-kem-api-misuse-resistance.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-source-digest-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
sh scripts/test-latticra-q-seal-ml-kem-code-owner-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-ci-promotion-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh scripts/test-latticra-q-seal-ml-kem-constant-time-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh scripts/test-latticra-q-seal-ml-kem-randomness-source.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh scripts/test-latticra-q-seal-ml-kem-zeroization-evidence.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh scripts/test-latticra-q-seal-ml-kem-side-channel-review.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh scripts/test-latticra-q-seal-ml-kem-provider-differential.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-binding-manifest.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh scripts/test-latticra-q-seal-ml-kem-implementation-frame.sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
sh scripts/test-latticra-q-seal-ml-kem-secret-state-contract.sh
```

Expected output:

```text
latticra q-seal foundation invariants: ok
latticra q-seal foundation: ok
latticra q-seal readiness invariants: ok
latticra q-seal readiness: ok
latticra q-seal ml-kem parameters invariants: ok
latticra q-seal ml-kem parameters: ok
latticra q-seal ml-kem evidence gate invariants: ok
latticra q-seal ml-kem evidence gate: ok
latticra q-seal ml-kem acvp intake invariants: ok
latticra q-seal ml-kem acvp intake: ok
latticra q-seal ml-kem vector schema invariants: ok
latticra q-seal ml-kem vector schema: ok
latticra q-seal ml-kem vector source invariants: ok
latticra q-seal ml-kem vector source: ok
latticra q-seal ml-kem negative-test evidence invariants: ok
latticra q-seal ml-kem negative-test evidence: ok
latticra q-seal ml-kem memory-safety evidence invariants: ok
latticra q-seal ml-kem memory-safety evidence: ok
latticra q-seal ml-kem api misuse resistance invariants: ok
latticra q-seal ml-kem api misuse resistance: ok
latticra q-seal ml-kem source digest manifest invariants: ok
latticra q-seal ml-kem source digest manifest: ok
latticra q-seal ml-kem code owner review invariants: ok
latticra q-seal ml-kem code owner review: ok
latticra q-seal ml-kem ci promotion evidence invariants: ok
latticra q-seal ml-kem ci promotion evidence: ok
latticra q-seal ml-kem constant-time review invariants: ok
latticra q-seal ml-kem constant-time review: ok
latticra q-seal ml-kem randomness source invariants: ok
latticra q-seal ml-kem randomness source: ok
latticra q-seal ml-kem zeroization evidence invariants: ok
latticra q-seal ml-kem zeroization evidence: ok
latticra q-seal ml-kem side-channel review invariants: ok
latticra q-seal ml-kem side-channel review: ok
latticra q-seal ml-kem provider differential invariants: ok
latticra q-seal ml-kem provider differential: ok
latticra q-seal ml-kem implementation binding manifest invariants: ok
latticra q-seal ml-kem implementation binding manifest: ok
latticra q-seal ml-kem implementation frame invariants: ok
latticra q-seal ml-kem implementation frame: ok
latticra q-seal ml-kem secret-state contract invariants: ok
latticra q-seal ml-kem secret-state contract: ok
```

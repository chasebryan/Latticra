# Latticra Q-Seal ML-KEM Source Layout Gate

Status: fail-closed source-layout evidence gate
Scope: clean-room ML-KEM file-role taxonomy before source acceptance.

This evidence record defines the source-layout gate for future clean-room ML-KEM implementation files. It binds planned source and test roles to FIPS 203, SP 800-227, SSDF provenance, digest rows, per-file standards trace, per-file test trace, author attestation, code-owner review, review disposition, reviewer role mapping, and CI promotion evidence. It does not create implementation source files, record layout rows, approve source layout, execute ML-KEM operations, emit shared secrets, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

```text
source_layout_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Source Layout Gate
layout_profile=latticra-q-seal-ml-kem-source-layout-gate/0.1
standards_basis=NIST-FIPS-203,NIST-SP-800-227,NIST-SP-800-218-SSDF
source_boundary=clean-room-no-apple-code
layout_scope=ML-KEM-source-layout-and-file-role-boundary-before-source-acceptance
layout_state=source-layout-recorded-source-files-blocked
clean_room_source_boundary_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
planned_source_units_count=9
planned_test_units_count=9
implementation_unit_roles_recorded=1
test_unit_roles_recorded=1
public_api_boundary_recorded=1
internal_primitive_boundary_recorded=1
secret_state_boundary_recorded=1
randomness_boundary_recorded=1
zeroization_boundary_recorded=1
constant_time_boundary_recorded=1
parameter_set_coverage_recorded=1
negative_test_lane_recorded=1
kat_acvp_lane_recorded=1
digest_manifest_lane_recorded=1
review_owner_lane_recorded=1
implementation_binding_manifest_bound=1
implementation_file_digest_plan_bound=1
clean_room_author_attestation_gate_bound=1
per_file_standards_trace_gate_bound=1
per_file_test_trace_gate_bound=1
implementation_traceability_matrix_bound=1
primitive_source_acceptance_gate_bound=1
source_digest_manifest_bound=1
source_digest_receipt_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
ci_promotion_evidence_bound=1
source_files_created=0
source_layout_rows_recorded=0
layout_digest_rows_recorded=0
layout_reviewed=0
layout_acceptance_approved=0
source_layout_accepted=0
operation_execution_allowed=0
shared_secret_emission_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_layout_items_total=38
required_layout_items_satisfied=32
blocked_reason=source-files-layout-rows-digest-rows-review-layout-approval-and-acceptance-missing
status=ml-kem-source-layout-gate-blocked
```

## Acceptance Blockers

```text
source_files_created=0
source_layout_rows_recorded=0
layout_digest_rows_recorded=0
layout_reviewed=0
layout_acceptance_approved=0
source_layout_accepted=0
```

## Non-Claims

This evidence is not implementation source, cryptographic execution evidence, KAT pass evidence, ACVP validation evidence, source-digest receipt evidence, code-owner approval, FIPS validation, production readiness, shared-secret handling authority, or runtime authority.

# Latticra Q-Seal ML-KEM Module Boundary Gate

This slice adds the fail-closed FIPS module-boundary and security-policy gate for Latticra Q-Seal ML-KEM. It sits between algorithm evidence and public validation claims so KATs, ACVP replay, ACVP verdict receipts, source digests, or local provider tests cannot be mistaken for a FIPS 140-3 module boundary or CMVP-ready security policy.

It records the evidence Q-Seal will require: module boundary schema, security-policy gate binding, services and roles columns, operational environment fields, self-test policy fields, algorithm certificate fields, entropy and zeroization boundary fields, source digest policy binding, and no implicit FIPS wording. It does not execute ML-KEM, accept a module boundary, claim FIPS validation, claim production cryptography, or grant runtime authority.

```text
module_boundary_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Module Boundary Gate
module_boundary_profile=latticra-q-seal-ml-kem-module-boundary-gate/0.1
standards_basis=NIST-FIPS-203,NIST-FIPS-140-3,NIST-CMVP,NIST-SP-800-218-SSDF
module_boundary_scope=ML-KEM-FIPS-module-boundary-and-security-policy-before-CMVP-or-claims
module_boundary_state=module-boundary-gate-recorded-boundary-evidence-missing
fips_203_algorithm_bound=1
fips_140_3_module_security_bound=1
cmvp_program_bound=1
validation_claim_gate_bound=1
security_policy_gate_bound=1
acvp_verdict_receipt_gate_bound=1
ci_promotion_evidence_bound=1
implementation_binding_manifest_bound=1
source_layout_gate_bound=1
implementation_file_digest_plan_bound=1
source_digest_verification_bound=1
zeroization_evidence_bound=1
randomness_source_bound=1
side_channel_review_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
clean_room_source_boundary_recorded=1
module_boundary_schema_recorded=1
security_policy_template_recorded=1
services_roles_columns_recorded=1
operational_environment_columns_recorded=1
self_test_policy_columns_recorded=1
algorithm_certificate_columns_recorded=1
entropy_boundary_columns_recorded=1
zeroization_boundary_columns_recorded=1
source_digest_policy_bound=1
no_implicit_fips_claim_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
module_boundary_evidence_recorded=0
cryptographic_module_name_recorded=0
module_version_recorded=0
operational_environment_recorded=0
fips_140_3_security_policy_recorded=0
roles_services_authentication_recorded=0
self_test_policy_recorded=0
approved_algorithm_inventory_recorded=0
entropy_source_boundary_recorded=0
zeroization_boundary_review_recorded=0
acvp_algorithm_certificate_bound=0
cmvp_submission_identifier_recorded=0
module_boundary_review_recorded=0
reviewer_disposition_recorded=0
module_boundary_gate_accepted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
operation_execution_allowed=0
runtime_authority_granted=0
required_module_boundary_items_total=46
required_module_boundary_items_satisfied=31
status=ml-kem-module-boundary-gate-blocked
```

## Guardrail

This gate keeps Q-Seal honest at the module boundary. Algorithm readiness and ACVP verdict evidence are necessary inputs, but they are not enough to describe a cryptographic module or publish FIPS-related wording without module name/version, accepted security-policy gate evidence, operational environment, services and roles, self-tests, entropy boundary, zeroization boundary, algorithm certificate, CMVP submission, and reviewer-disposition evidence.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
```

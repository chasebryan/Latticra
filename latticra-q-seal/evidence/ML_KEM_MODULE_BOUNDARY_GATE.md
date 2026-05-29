# Latticra Q-Seal ML-KEM Module Boundary Gate

Status: FIPS module boundary and security-policy gate
Scope: fail-closed ML-KEM cryptographic module boundary, FIPS 140-3 security policy, CMVP submission, and ACVP certificate evidence before any FIPS, validation, migration, production, or runtime claim.

This gate records the module-boundary evidence Q-Seal must require before ML-KEM can be described as a FIPS/CMVP-ready module or included in validation-language release claims. It separates algorithm-level evidence from cryptographic-module evidence: ACVP verdicts, KAT replay, source digests, local provider tests, and security-policy templates do not establish a FIPS 140-3 module boundary, module version, accepted security-policy gate, roles/services table, operational environment, entropy boundary, zeroization review, or CMVP submission record. It does not execute ML-KEM, grant production cryptography, claim FIPS validation, import Apple or external provider code, mutate host files, open a network session, or grant runtime authority.

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

## Required Module Evidence

Before Q-Seal can accept a module boundary, it must record:

- cryptographic module name, version, source digest, and release artifact binding;
- accepted security-policy gate evidence for the claimed module;
- operational environment and build configuration for the module;
- services, roles, authentication, self-test, approved-algorithm inventory, entropy boundary, and zeroization boundary evidence;
- ACVP algorithm certificate identifiers and CMVP submission identifiers when validation wording depends on them;
- reviewer disposition proving the boundary and policy were independently reviewed.

Satisfying this gate would only accept module-boundary evidence. FIPS claims, public validation wording, production cryptography, operation execution, and runtime authority remain governed by separate gates.

## Non-Claims

This gate is not FIPS validation, not CMVP certification, not an ACVP certificate, not a production release, not primitive source, not provider linking, not network behavior, not host mutation, and not runtime authority.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-module-boundary-gate.sh
```

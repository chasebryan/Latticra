# Latticra Q-Seal ML-KEM Security Policy Gate

Status: FIPS 140-3 security-policy evidence gate
Scope: fail-closed ML-KEM cryptographic module security-policy evidence before module-boundary acceptance, CMVP submission, FIPS wording, production cryptography, or runtime authority.

This gate records the security-policy evidence Q-Seal must require before an ML-KEM cryptographic module can be described with FIPS 140-3 or CMVP wording. It follows the repo's clean-room posture and binds the security-policy surface to FIPS 140-3, SP 800-140B Rev. 1, CMVP, ML-KEM algorithm evidence, module-boundary evidence, reviewer disposition, and source-digest evidence. It does not accept a security policy, execute ML-KEM, claim FIPS validation, import Apple or external provider code, mutate host files, open a network session, or grant runtime authority.

```text
security_policy_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Security Policy Gate
security_policy_profile=latticra-q-seal-ml-kem-security-policy-gate/0.1
standards_basis=NIST-FIPS-140-3,NIST-SP-800-140B-REV-1,NIST-CMVP,NIST-FIPS-203,NIST-SP-800-218-SSDF
security_policy_scope=ML-KEM-FIPS-140-3-security-policy-before-module-boundary-or-claims
security_policy_state=security-policy-gate-recorded-policy-evidence-missing
fips_140_3_module_security_bound=1
sp800_140b_rev1_security_policy_bound=1
cmvp_program_bound=1
fips_203_algorithm_bound=1
module_boundary_gate_bound=1
validation_claim_gate_bound=1
acvp_verdict_receipt_gate_bound=1
source_digest_verification_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
clean_room_source_boundary_recorded=1
security_policy_template_recorded=1
non_proprietary_policy_required=1
module_identification_section_required=1
cryptographic_module_specification_section_required=1
approved_algorithms_section_required=1
roles_services_authentication_section_required=1
software_firmware_security_section_required=1
operational_environment_section_required=1
self_tests_section_required=1
entropy_boundary_section_required=1
life_cycle_assurance_section_required=1
mitigation_other_attacks_section_required=1
acronyms_references_section_required=1
no_implicit_fips_claim_policy_recorded=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
security_policy_evidence_recorded=0
security_policy_document_digest_recorded=0
module_name_version_recorded=0
security_level_table_recorded=0
approved_security_functions_table_recorded=0
services_roles_table_recorded=0
self_test_table_recorded=0
entropy_source_statement_recorded=0
operational_environment_recorded=0
guidance_statement_recorded=0
reviewer_disposition_recorded=0
security_policy_gate_accepted=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
operation_execution_allowed=0
runtime_authority_granted=0
required_security_policy_items_total=41
required_security_policy_items_satisfied=29
status=ml-kem-security-policy-gate-blocked
```

## Required Security Policy Evidence

Before Q-Seal can accept a security-policy gate, it must record:

- a security-policy document digest and source/release binding;
- module name, version, and cryptographic module specification;
- security level, approved security functions, services, roles, authentication, self-test, entropy, operational environment, and guidance tables;
- reviewer disposition tying the policy to the module boundary, source digests, ACVP verdict evidence, and CMVP submission context.

Satisfying this gate would only accept security-policy evidence. FIPS claims, public validation wording, production cryptography, operation execution, and runtime authority remain governed by separate gates.

## Non-Claims

This gate is not FIPS validation, not CMVP certification, not an ACVP certificate, not a production release, not primitive source, not provider linking, not network behavior, not host mutation, and not runtime authority.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh
```

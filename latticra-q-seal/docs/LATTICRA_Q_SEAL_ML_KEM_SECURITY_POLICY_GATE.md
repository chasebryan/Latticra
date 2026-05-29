# Latticra Q-Seal ML-KEM Security Policy Gate

This slice adds the fail-closed FIPS 140-3 security-policy gate for Latticra Q-Seal ML-KEM. It sits below the module-boundary and validation-claim gates so algorithm evidence, KAT/ACVP evidence, and source digests cannot be mistaken for an accepted SP 800-140B Rev. 1 security policy.

It records the security-policy evidence Q-Seal will require: non-proprietary policy posture, module identification, cryptographic module specification, approved algorithms, services/roles/authentication, software/firmware security, operational environment, self-tests, entropy boundary, life-cycle assurance, mitigation-of-other-attacks, references, source digest binding, and reviewer disposition. It does not execute ML-KEM, accept a security policy, claim FIPS validation, claim production cryptography, or grant runtime authority.

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

## Guardrail

This gate keeps Q-Seal honest at the security-policy boundary. Algorithm readiness, ACVP verdict evidence, source digests, and module-boundary templates are necessary inputs, but they are not enough to publish or accept a FIPS 140-3 security policy without document digest, module identification, services/roles/authentication, self-test, approved-function, entropy, operational-environment, guidance, and reviewer-disposition evidence.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh
```

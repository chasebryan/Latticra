# Latticra Q-Seal ML-KEM Validation Claim Gate

Status: validation and release claim gate
Scope: fail-closed ML-KEM public validation, FIPS, post-quantum migration, and release wording evidence before any claim publication.

This gate records the evidence Q-Seal must require before Latticra can publish validation-language claims for ML-KEM. It separates internal KAT/ACVP evidence, ACVP verdict receipts, and implementation-review evidence from public claims such as "validated", "FIPS", "ACVP passed", "production quantum-resistant cryptography", or migration-readiness wording. It does not execute ML-KEM, grant production cryptography, claim FIPS validation, open a network session, import Apple or external provider code, mutate host files, or grant runtime authority.

```text
validation_claim_gate_present=1
formal_title=Latticra Q-Seal ML-KEM Validation Claim Gate
validation_claim_profile=latticra-q-seal-ml-kem-validation-claim-gate/0.1
standards_basis=NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-CMVP,NIST-SP-800-218-SSDF
validation_claim_scope=ML-KEM-public-validation-and-release-claims-before-publication
validation_claim_state=validation-claim-gate-recorded-claim-evidence-missing
fips_203_algorithm_bound=1
acvp_ml_kem_protocol_bound=1
acvp_verdict_receipt_gate_bound=1
replay_transcript_gate_bound=1
acvp_submission_package_contract_bound=1
ci_promotion_evidence_bound=1
implementation_binding_manifest_bound=1
readiness_profile_bound=1
module_boundary_gate_bound=1
code_owner_review_bound=1
review_disposition_ledger_bound=1
reviewer_role_mapping_bound=1
source_digest_verification_bound=1
provider_differential_bound=1
clean_room_source_boundary_recorded=1
public_claim_taxonomy_recorded=1
no_implicit_fips_claim_policy_recorded=1
no_implicit_acvp_claim_policy_recorded=1
module_boundary_required=1
security_policy_required=1
acvp_certificate_or_validation_record_required=1
cmvp_certificate_required=1
implementation_digest_receipt_required=1
release_artifact_digest_required=1
release_notes_claim_review_required=1
docs_public_surface_review_required=1
operator_warning_required=1
rollback_claim_revocation_required=1
no_secret_material_logging_required=1
apple_corecrypto_code_copied=0
external_provider_code_copied=0
implementation_claim_evidence_recorded=0
acvp_pass_evidence_recorded=0
cmvp_certificate_recorded=0
module_boundary_recorded=0
security_policy_recorded=0
release_artifact_digest_recorded=0
public_claim_review_recorded=0
reviewer_disposition_recorded=0
validation_claim_gate_accepted=0
public_validation_claim_allowed=0
fips_validation_claim_allowed=0
post_quantum_migration_claim_allowed=0
production_crypto_claim_allowed=0
operation_execution_allowed=0
runtime_authority_granted=0
required_validation_claim_items_total=41
required_validation_claim_items_satisfied=32
status=ml-kem-validation-claim-gate-blocked
```

## Required Claim Evidence

Before any public validation claim can be accepted, Q-Seal must record:

- implementation evidence tied to reviewed source digests and release artifacts;
- ACVP pass evidence bound to the ACVP verdict receipt gate;
- CMVP certificate or explicit validation record when FIPS wording is used;
- accepted module-boundary gate evidence and security policy evidence for the claimed cryptographic module;
- release artifact digests and public documentation review showing exact claim wording;
- reviewer disposition and rollback/revocation plan for claim correction.

Satisfying this gate would only allow validation-language claims. Runtime cryptography, operation execution, production cryptography claims, and runtime authority remain separate gates.

## Non-Claims

This gate is not FIPS validation, not CMVP certification, not ACVP execution, not a production release, not primitive code, not generated source, not provider linking, not network behavior, not host mutation, and not runtime authority.

## Validation

```sh
sh latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
sh scripts/test-latticra-q-seal-ml-kem-validation-claim-gate.sh
```

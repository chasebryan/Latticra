# Latticra Q-Seal ML-KEM Reviewer Identity Fixture

Status: reviewer identity import fixture
Date: 2026-05-27
Scope: reviewer identity, role mapping, and independence import records before ML-KEM implementation promotion.

This fixture records the required reviewer identity import shape for future code-owner, cryptography, and security review evidence. It does not import reviewer identities, record personal data, approve reviewers, close findings, approve implementation promotion, execute ML-KEM operations, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

The downstream reviewer role-mapping fixture is recorded in `ML_KEM_REVIEWER_ROLE_MAPPING.md`; it remains fail-closed until reviewer identities are mapped to cryptography, security, code-owner, standards, side-channel, and source-digest review roles with separation and approval-authority evidence.

## Current Fields

```text
ml_kem_reviewer_identity_fixture_present=1
formal_title=Latticra Q-Seal ML-KEM Reviewer Identity Fixture
identity_profile=latticra-q-seal-ml-kem-reviewer-identity-fixture/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
identity_scope=ML-KEM-reviewer-identity-import-before-promotion
identity_state=reviewer-identity-import-fixture-blocked
reviewer_identity_fixture_present=1
fips_203_algorithm_bound=1
ssdf_review_practice_bound=1
clean_room_review_policy_recorded=1
code_owner_review_gate_bound=1
review_disposition_ledger_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
dual_reviewer_identity_required=1
cryptography_reviewer_identity_required=1
security_reviewer_identity_required=1
code_owner_identity_required=1
reviewer_independence_required=1
identity_schema_recorded=1
identity_import_template_recorded=1
pii_minimization_policy_recorded=1
reviewer_identities_imported=0
cryptography_reviewer_identity_recorded=0
security_reviewer_identity_recorded=0
code_owner_identity_recorded=0
independence_attestation_recorded=0
identity_import_reviewed=0
approval_authority_recorded=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_identity_items_total=23
required_identity_items_satisfied=16
status=ml-kem-reviewer-identity-fixture-blocked
```

## Required Identity Rows

```text
reviewer_identities_imported=required
cryptography_reviewer_identity_recorded=required
security_reviewer_identity_recorded=required
code_owner_identity_recorded=required
independence_attestation_recorded=required
identity_import_reviewed=required
approval_authority_recorded=required
```

## Non-Claims

This fixture is not reviewer identity evidence, not a personal-data store, not reviewer approval, not finding closure, not implementation promotion, not primitive code, not ACVP evidence, not FIPS validation, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.

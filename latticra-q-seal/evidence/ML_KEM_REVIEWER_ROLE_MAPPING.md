# Latticra Q-Seal ML-KEM Reviewer Role Mapping

Status: reviewer role-mapping fixture
Date: 2026-05-27
Scope: reviewer identity role mapping, separation, and approval-authority records before ML-KEM implementation promotion.

This fixture records the role-mapping evidence shape for future clean-room ML-KEM review evidence. It does not import reviewer identities, record personal data, approve reviewers, close findings, approve implementation promotion, execute ML-KEM operations, claim production cryptography, claim FIPS validation, use the network, mutate host files, or grant runtime authority.

## Current Fields

```text
ml_kem_reviewer_role_mapping_present=1
formal_title=Latticra Q-Seal ML-KEM Reviewer Role Mapping
mapping_profile=latticra-q-seal-ml-kem-reviewer-role-mapping/0.1
standards_basis=NIST-SP-800-218-SSDF-and-FIPS-203
mapping_scope=ML-KEM-reviewer-role-mapping-before-promotion
mapping_state=reviewer-role-mapping-fixture-blocked
reviewer_role_mapping_present=1
fips_203_algorithm_bound=1
ssdf_review_practice_bound=1
clean_room_review_policy_recorded=1
code_owner_review_gate_bound=1
review_disposition_ledger_bound=1
reviewer_identity_fixture_bound=1
implementation_binding_manifest_bound=1
ci_promotion_evidence_bound=1
role_schema_recorded=1
cryptography_role_required=1
security_role_required=1
code_owner_role_required=1
standards_traceability_role_required=1
side_channel_role_required=1
source_digest_role_required=1
dual_reviewer_separation_required=1
conflict_of_interest_policy_recorded=1
pii_minimization_policy_bound=1
approval_authority_mapping_required=1
reviewer_identities_imported=0
role_mapping_records_imported=0
cryptography_role_mapped=0
security_role_mapped=0
code_owner_role_mapped=0
standards_traceability_role_mapped=0
side_channel_role_mapped=0
source_digest_role_mapped=0
separation_review_recorded=0
approval_authority_mapped=0
operation_execution_allowed=0
production_crypto_claim_allowed=0
fips_claim_allowed=0
runtime_authority_granted=0
required_role_mapping_items_total=30
required_role_mapping_items_satisfied=20
status=ml-kem-reviewer-role-mapping-blocked
```

## Required Mapping Rows

```text
reviewer_identities_imported=required
role_mapping_records_imported=required
cryptography_role_mapped=required
security_role_mapped=required
code_owner_role_mapped=required
standards_traceability_role_mapped=required
side_channel_role_mapped=required
source_digest_role_mapped=required
separation_review_recorded=required
approval_authority_mapped=required
```

## Non-Claims

This fixture is not reviewer identity evidence, not a personal-data store, not reviewer approval, not finding closure, not implementation promotion, not primitive code, not ACVP evidence, not FIPS validation, not production cryptography, not provider linking, not network behavior, not host mutation, and not runtime authority.

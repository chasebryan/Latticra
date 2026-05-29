# Latticra Identity, Credential, and Access Management Baseline Status

Status: status record for identity, credential, and access management baseline
Date: 2026-05-26

## Scope

This record tracks the identity, credential, and access-management baseline for human identity, service identity, machine identity, privileged access, phishing-resistant MFA, SSO/federation context, account lifecycle, credential handling, break-glass access, identity event logging, and access-management non-claims.

It does not implement an identity provider, MFA provider, account provisioning, account deprovisioning, credential storage, remote access, privileged access, hosted administration, SSO federation, authorization enforcement, compliance, or runtime authority.

## Current fields

```text
identity_credential_access_management_baseline_present=1
identity_credential_access_management_status_present=1
identity_credential_access_management_guard_present=1
nsa_zero_trust_user_pillar_tracked=1
cisa_nsa_esf_iam_best_practices_tracked=1
nist_sp_800_63_4_digital_identity_tracked=1
cisa_cpg_account_security_tracked=1
phishing_guidance_tracked=1
it_product_design_mfa_goal_tracked=1
phishing_resistant_mfa_required_for_privileged_access=1
mfa_required_for_remote_access=1
privileged_access_inventory_required=1
service_account_inventory_required=1
local_account_inventory_required=1
account_lifecycle_contract_required=1
least_privilege_role_review_required=1
break_glass_account_policy_required=1
federation_sso_context_required=1
credential_secret_storage_review_required=1
credential_reuse_forbidden=1
default_credentials_forbidden=1
identity_event_logging_required=1
privileged_behavior_monitoring_required=1
help_desk_identity_verification_required=1
access_exception_owner_required=1
access_exception_expiration_required=1
implementation_behavior_changed=0
identity_provider_added=0
mfa_provider_added=0
account_provisioning_added=0
account_deprovisioning_added=0
remote_access_enabled=0
privileged_access_granted=0
credential_storage_added=0
hosted_admin_surface_added=0
identity_security_claim_allowed=0
hosted_service_claim_allowed=0
compliance_claim_allowed=0
external_endorsement_claimed=0
```

## Validation

```sh
sh scripts/test-identity-credential-access-management-baseline.sh
```

Expected output:

```text
identity_credential_access_management_baseline: ok
```

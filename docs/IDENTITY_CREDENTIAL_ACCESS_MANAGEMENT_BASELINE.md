# Latticra Identity, Credential, and Access Management Baseline

Status: identity, credential, and access management baseline
Source refresh date: 2026-05-26
Scope: human identity, service identity, machine identity, privileged access, phishing-resistant MFA, SSO/federation context, account lifecycle, credential handling, break-glass access, identity event logging, and access-management non-claims before hosted services, remote access, privileged operator access, or identity-security claims.

This baseline records identity, credential, and access-management requirements only. It does not implement an identity provider, MFA provider, account provisioning, account deprovisioning, credential storage, remote access, privileged access, hosted administration, SSO federation, authorization enforcement, compliance, or runtime authority.

## Authoritative Identity and Access Sources

Date checked: 2026-05-26

| Source | Latticra use |
| --- | --- |
| NSA Advancing Zero Trust Maturity Throughout the User Pillar | ICAM maturity, user identity, credentials, access policy, and user-pillar visibility vocabulary |
| CISA and NSA Identity and Access Management: Recommended Best Practices for Administrators | asset identity inventory, local identity inventory, MFA inventory, SSO context, and privileged behavior monitoring vocabulary |
| NIST SP 800-63-4 Digital Identity Guidelines | identity proofing, authentication, authenticator management, federation, assurance levels, subscriber accounts, and assertions vocabulary |
| CISA Cross-Sector Cybersecurity Performance Goals | MFA, account security, log collection, secure log storage, and privileged-access baseline expectations |
| CISA Require Multifactor Authentication and phishing-resistant MFA guidance | phishing-resistant MFA preference for remote and privileged access |
| CISA/NSA/FBI/MS-ISAC Phishing Guidance: Stopping the Attack Cycle at Phase One | phishing-resistant MFA, social-engineering resistance, and account-compromise reduction vocabulary |
| CISA IT and Product Design Sector-Specific Goals | MFA for software-development environments and authorization trust-relationship monitoring vocabulary |

Authoritative URLs:

```text
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3328152/nsa-releases-recommendations-for-maturing-identity-credential-and-access-manage/
https://www.cisa.gov/sites/default/files/2023-12/ESF%20IDENTITY%20AND%20ACCESS%20MANAGEMENT%20RECOMMENDED%20BEST%20PRACTICES%20FOR%20ADMINISTRATORS%20PP-23-0248_508C.pdf
https://csrc.nist.gov/pubs/sp/800/63/4/final
https://csrc.nist.gov/pubs/sp/800/63/B/4/final
https://csrc.nist.gov/pubs/sp/800/63/C/4/final
https://www.cisa.gov/cross-sector-cybersecurity-performance-goals
https://www.cisa.gov/secure-our-world/require-multifactor-authentication
https://www.cisa.gov/news-events/news/cisa-nsa-fbi-ms-isac-publish-guide-preventing-phishing-intrusions
https://www.cisa.gov/news-events/news/cisa-releases-new-sector-specific-goals-it-and-product-design
```

## Current Fields

```text
identity_credential_access_management_baseline_present=1
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

## Required ICAM Promotion Gate

No hosted service, hosted administration surface, remote access path, privileged operator role, service-account runtime authority, SSO/federation claim, MFA claim, identity-security claim, or production access-management claim may be promoted until this gate is complete:

```text
operator_identity_source_recorded=1
human_account_inventory_present=1
local_identity_inventory_present=1
service_identity_inventory_present=1
machine_identity_inventory_present=1
privileged_role_inventory_present=1
role_to_effect_mapping_recorded=1
least_privilege_review_recorded=1
phishing_resistant_mfa_path_recorded=1
mfa_exception_recorded=1
break_glass_account_recorded=1
break_glass_monitoring_recorded=1
session_lifetime_and_reauth_recorded=1
credential_storage_and_rotation_recorded=1
credential_recovery_path_recorded=1
help_desk_identity_verification_recorded=1
joiner_mover_leaver_process_recorded=1
identity_event_logging_recorded=1
privileged_behavior_review_recorded=1
authorization_trust_relationships_reviewed=1
access_exception_owner_recorded=1
access_exception_expiration_recorded=1
operator_visible_non_claims_recorded=1
```

Until this gate is complete:

```text
production_identity_provider_allowed=0
remote_access_allowed=0
privileged_operator_access_allowed=0
service_account_runtime_authority_allowed=0
hosted_admin_console_allowed=0
password_only_privileged_access_allowed=0
default_credential_allowed=0
shared_admin_account_allowed=0
production_credential_storage_allowed=0
identity_security_claim_allowed=0
single_sign_on_claim_allowed=0
mfa_claim_allowed=0
hosted_service_claim_allowed=0
```

## Latticra Boundary

Current Latticra identity and access posture is metadata-only and no-effect.

```text
latticra_operator_identity_metadata_only=1
latticra_access_policy_metadata_only=1
latticra_authorization_enforcement_added=0
latticra_account_database_added=0
latticra_remote_login_added=0
latticra_privileged_session_added=0
latticra_identity_runtime_authority_granted=0
```

## Current Evidence

Current supporting evidence:

```text
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
SECURITY.md
scripts/test-high-assurance-security-baseline.sh
scripts/test-identity-credential-access-management-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-identity-credential-access-management-baseline.sh
```

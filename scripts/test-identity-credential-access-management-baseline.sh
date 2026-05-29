#!/usr/bin/env sh
set -eu

doc="docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md"
status_doc="docs/status/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'identity credential access management baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'identity credential access management baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: identity, credential, and access management baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Authoritative Identity and Access Sources' "$doc"
require_contains 'NSA Advancing Zero Trust Maturity Throughout the User Pillar' "$doc"
require_contains 'CISA and NSA Identity and Access Management: Recommended Best Practices for Administrators' "$doc"
require_contains 'NIST SP 800-63-4 Digital Identity Guidelines' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals' "$doc"
require_contains 'CISA Require Multifactor Authentication and phishing-resistant MFA guidance' "$doc"
require_contains 'CISA/NSA/FBI/MS-ISAC Phishing Guidance: Stopping the Attack Cycle at Phase One' "$doc"
require_contains 'CISA IT and Product Design Sector-Specific Goals' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3328152/nsa-releases-recommendations-for-maturing-identity-credential-and-access-manage/' "$doc"
require_contains 'https://www.cisa.gov/sites/default/files/2023-12/ESF%20IDENTITY%20AND%20ACCESS%20MANAGEMENT%20RECOMMENDED%20BEST%20PRACTICES%20FOR%20ADMINISTRATORS%20PP-23-0248_508C.pdf' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/63/4/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/63/B/4/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/63/C/4/final' "$doc"
require_contains 'https://www.cisa.gov/cross-sector-cybersecurity-performance-goals' "$doc"
require_contains 'https://www.cisa.gov/secure-our-world/require-multifactor-authentication' "$doc"
require_contains 'https://www.cisa.gov/news-events/news/cisa-nsa-fbi-ms-isac-publish-guide-preventing-phishing-intrusions' "$doc"
require_contains 'https://www.cisa.gov/news-events/news/cisa-releases-new-sector-specific-goals-it-and-product-design' "$doc"

for field in \
  'identity_credential_access_management_baseline_present=1' \
  'identity_credential_access_management_guard_present=1' \
  'nsa_zero_trust_user_pillar_tracked=1' \
  'cisa_nsa_esf_iam_best_practices_tracked=1' \
  'nist_sp_800_63_4_digital_identity_tracked=1' \
  'cisa_cpg_account_security_tracked=1' \
  'phishing_guidance_tracked=1' \
  'it_product_design_mfa_goal_tracked=1' \
  'phishing_resistant_mfa_required_for_privileged_access=1' \
  'mfa_required_for_remote_access=1' \
  'privileged_access_inventory_required=1' \
  'service_account_inventory_required=1' \
  'local_account_inventory_required=1' \
  'account_lifecycle_contract_required=1' \
  'least_privilege_role_review_required=1' \
  'break_glass_account_policy_required=1' \
  'federation_sso_context_required=1' \
  'credential_secret_storage_review_required=1' \
  'credential_reuse_forbidden=1' \
  'default_credentials_forbidden=1' \
  'identity_event_logging_required=1' \
  'privileged_behavior_monitoring_required=1' \
  'help_desk_identity_verification_required=1' \
  'access_exception_owner_required=1' \
  'access_exception_expiration_required=1' \
  'implementation_behavior_changed=0' \
  'identity_provider_added=0' \
  'mfa_provider_added=0' \
  'account_provisioning_added=0' \
  'account_deprovisioning_added=0' \
  'remote_access_enabled=0' \
  'privileged_access_granted=0' \
  'credential_storage_added=0' \
  'hosted_admin_surface_added=0' \
  'identity_security_claim_allowed=0' \
  'hosted_service_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'identity_credential_access_management_status_present=1' "$status_doc"

for gate in \
  'operator_identity_source_recorded=1' \
  'human_account_inventory_present=1' \
  'local_identity_inventory_present=1' \
  'service_identity_inventory_present=1' \
  'machine_identity_inventory_present=1' \
  'privileged_role_inventory_present=1' \
  'role_to_effect_mapping_recorded=1' \
  'least_privilege_review_recorded=1' \
  'phishing_resistant_mfa_path_recorded=1' \
  'mfa_exception_recorded=1' \
  'break_glass_account_recorded=1' \
  'break_glass_monitoring_recorded=1' \
  'session_lifetime_and_reauth_recorded=1' \
  'credential_storage_and_rotation_recorded=1' \
  'credential_recovery_path_recorded=1' \
  'help_desk_identity_verification_recorded=1' \
  'joiner_mover_leaver_process_recorded=1' \
  'identity_event_logging_recorded=1' \
  'privileged_behavior_review_recorded=1' \
  'authorization_trust_relationships_reviewed=1' \
  'access_exception_owner_recorded=1' \
  'access_exception_expiration_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'production_identity_provider_allowed=0' \
  'remote_access_allowed=0' \
  'privileged_operator_access_allowed=0' \
  'service_account_runtime_authority_allowed=0' \
  'hosted_admin_console_allowed=0' \
  'password_only_privileged_access_allowed=0' \
  'default_credential_allowed=0' \
  'shared_admin_account_allowed=0' \
  'production_credential_storage_allowed=0' \
  'identity_security_claim_allowed=0' \
  'single_sign_on_claim_allowed=0' \
  'mfa_claim_allowed=0' \
  'hosted_service_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for boundary_field in \
  'latticra_operator_identity_metadata_only=1' \
  'latticra_access_policy_metadata_only=1' \
  'latticra_authorization_enforcement_added=0' \
  'latticra_account_database_added=0' \
  'latticra_remote_login_added=0' \
  'latticra_privileged_session_added=0' \
  'latticra_identity_runtime_authority_granted=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'caller_identity_known=1' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'operator_or_automation_context_known=1' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'tool, MCP, model, runtime, signer, updater, and installer workloads require separate authority contracts' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'dependency_inventory_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'license and notice review' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'identity_credential_access_management_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-identity-credential-access-management-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md' SECURITY.md
require_contains 'identity_credential_access_management_baseline_present=1' README.md
require_contains 'identity_credential_access_management_baseline_present=1' STATUS.md
require_contains 'IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE_STATUS.md' docs/status/README.md
require_contains 'identity_credential_access_management_baseline_present=1' docs/status/README.md
require_contains 'Latest identity, credential, and access management baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Identity, credential, and access management baseline' docs/security.html
require_contains 'IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-identity-credential-access-management-baseline.sh' Makefile
require_contains 'identity-credential-access-management-baseline:' Makefile
require_contains 'sh ./scripts/test-identity-credential-access-management-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-identity-credential-access-management-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'identity_credential_access_management_baseline: ok\n'

#!/usr/bin/env sh
set -eu

doc="docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md"
status_doc="docs/status/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'secure configuration change management baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'secure configuration change management baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_file docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_file docs/security/C_CPP_SECURITY_PROFILE.md
require_file installer/latticra-installer/src/config.rs
require_file installer/scripts/latticra-installer-apply.sh
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-installer-config-authority-allowlist.sh
require_file scripts/test-installer-ui-artifact-authority.sh
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: secure configuration and change management baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Authoritative Configuration Sources' "$doc"
require_contains 'NIST SP 800-128 Guide for Security-Focused Configuration Management of Information Systems' "$doc"
require_contains 'NIST SP 800-70 Rev. 5 National Checklist Program for IT Products' "$doc"
require_contains 'NIST SP 800-53 Rev. 5 Configuration Management controls' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals' "$doc"
require_contains 'CISA/FBI Product Security Bad Practices' "$doc"
require_contains 'NSA and CISA Red and Blue Teams Share Top Ten Cybersecurity Misconfigurations' "$doc"
require_contains 'CISA/NSA/FBI secure-by-design and secure-by-default principles' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/128/upd1/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/70/r5/final' "$doc"
require_contains 'https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final' "$doc"
require_contains 'https://www.cisa.gov/cybersecurity-performance-goals-cpgs' "$doc"
require_contains 'https://www.cisa.gov/resources-tools/resources/product-security-bad-practices' "$doc"
require_contains 'https://www.cisa.gov/news-events/alerts/2025/01/17/cisa-and-fbi-release-updated-guidance-product-security-bad-practices' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3549369/nsa-and-cisa-advise-on-top-ten-cybersecurity-misconfigurations/' "$doc"
require_contains 'https://www.cisa.gov/news-events/news/us-and-international-partners-publish-secure-design-and-default-principles-and-approaches' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3361073/nsa-us-and-international-partners-issue-guidance-on-securing-technology-by-desi/' "$doc"

for field in \
  'secure_configuration_change_management_baseline_present=1' \
  'secure_configuration_change_management_guard_present=1' \
  'nist_sp_800_128_configuration_management_tracked=1' \
  'nist_sp_800_70_rev5_checklist_tracked=1' \
  'nist_sp_800_53_configuration_management_tracked=1' \
  'cisa_cpg_secure_configuration_tracked=1' \
  'cisa_fbi_product_security_bad_practices_config_tracked=1' \
  'nsa_cisa_top_misconfigurations_tracked=1' \
  'cisa_nsa_fbi_secure_by_default_tracked=1' \
  'configuration_item_inventory_required=1' \
  'secure_baseline_configuration_required=1' \
  'configuration_checklist_required=1' \
  'approved_change_record_required=1' \
  'configuration_change_owner_required=1' \
  'configuration_change_risk_review_required=1' \
  'configuration_change_test_evidence_required=1' \
  'configuration_rollback_plan_required=1' \
  'configuration_drift_detection_required=1' \
  'default_credential_forbidden=1' \
  'insecure_default_configuration_forbidden=1' \
  'configuration_secret_review_required=1' \
  'configuration_exception_owner_required=1' \
  'configuration_exception_expiration_required=1' \
  'implementation_behavior_changed=0' \
  'configuration_enforcement_added=0' \
  'configuration_scanner_added=0' \
  'host_configuration_changed=0' \
  'infrastructure_configuration_changed=0' \
  'change_approval_workflow_added=0' \
  'drift_detection_added=0' \
  'rollback_execution_added=0' \
  'production_configuration_claim_allowed=0' \
  'hosted_service_configuration_claim_allowed=0' \
  'configuration_hardening_claim_allowed=0' \
  'secure_default_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'secure_configuration_change_management_status_present=1' "$status_doc"

for gate in \
  'configuration_item_inventory_present=1' \
  'configuration_owner_recorded=1' \
  'baseline_configuration_recorded=1' \
  'configuration_checklist_recorded=1' \
  'secure_default_review_recorded=1' \
  'default_credential_absence_recorded=1' \
  'insecure_default_configuration_absence_recorded=1' \
  'change_request_recorded=1' \
  'change_owner_recorded=1' \
  'change_risk_review_recorded=1' \
  'change_test_evidence_recorded=1' \
  'rollback_plan_recorded=1' \
  'drift_detection_plan_recorded=1' \
  'configuration_secret_review_recorded=1' \
  'configuration_log_event_recorded=1' \
  'exception_owner_recorded=1' \
  'exception_expiration_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'host_configuration_change_allowed=0' \
  'production_configuration_claim_allowed=0' \
  'secure_default_claim_allowed=0' \
  'configuration_hardening_claim_allowed=0' \
  'configuration_scanning_claim_allowed=0' \
  'configuration_enforcement_allowed=0' \
  'drift_detection_claim_allowed=0' \
  'hosted_service_configuration_claim_allowed=0' \
  'infrastructure_as_code_claim_allowed=0' \
  'compliance_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for boundary_field in \
  'latticra_configuration_metadata_only=1' \
  'latticra_installer_config_authority_allowlist_guarded=1' \
  'latticra_installer_ui_artifact_authority_guarded=1' \
  'latticra_host_configuration_mutation_added=0' \
  'latticra_configuration_enforcement_added=0' \
  'latticra_configuration_scanning_added=0' \
  'latticra_drift_detection_added=0' \
  'latticra_change_approval_workflow_added=0' \
  'latticra_configuration_authority_granted=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'installer_config_authority_slug_allowlist_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'configuration_change_logging_required=1' docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_contains 'kev_nvd_review_required_before_release=1' docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_contains 'no hardcoded default passwords, tokens, or private keys' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'AUTHORITY_SLUG_MAX_LEN' installer/latticra-installer/src/config.rs
require_contains 'validate_authority_slug' installer/latticra-installer/src/config.rs
require_contains 'secure configuration baseline and change-control evidence' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'secure_configuration_change_management_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-secure-configuration-change-management-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md' SECURITY.md
require_contains 'secure_configuration_change_management_baseline_present=1' README.md
require_contains 'secure_configuration_change_management_baseline_present=1' STATUS.md
require_contains 'SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE_STATUS.md' docs/status/README.md
require_contains 'secure_configuration_change_management_baseline_present=1' docs/status/README.md
require_contains 'Latest secure configuration and change management baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Secure configuration and change management baseline' docs/security.html
require_contains 'SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-secure-configuration-change-management-baseline.sh' Makefile
require_contains 'secure-configuration-change-management-baseline:' Makefile
require_contains 'sh ./scripts/test-secure-configuration-change-management-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-secure-configuration-change-management-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'secure_configuration_change_management_baseline: ok\n'

#!/usr/bin/env sh
set -eu

doc="docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md"
status_doc="docs/status/DATA_CLASSIFICATION_PROTECTION_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'data classification protection baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'data classification protection baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_file docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md
require_file docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
require_file docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md
require_file docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md
require_file docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_file docs/security/C_CPP_SECURITY_PROFILE.md
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-secret-material-guard.sh
require_file scripts/test-report-redaction-boundary.sh
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: data classification and protection baseline' "$doc"
require_contains 'Source refresh date: 2026-05-27' "$doc"
require_contains 'Authoritative Data Protection Sources' "$doc"
require_contains 'NSA Zero Trust Data Pillar guidance' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals' "$doc"
require_contains 'CISA/FBI/NSA/MS-ISAC #StopRansomware Guide' "$doc"
require_contains 'FBI ransomware and data-extortion guidance' "$doc"
require_contains 'NIST SP 800-60 Vol. 1 Rev. 1 and SP 800-60 Rev. 2 draft' "$doc"
require_contains 'NIST SP 800-122 Guide to Protecting the Confidentiality of PII' "$doc"
require_contains 'NIST Privacy Framework 1.0 and 1.1 draft' "$doc"
require_contains 'NIST SP 800-53 Rev. 5 Media Protection, Privacy, Access Control, Audit, and System and Communications Protection controls' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3735130/nsa-issues-guidance-for-maturing-data-security/' "$doc"
require_contains 'https://www.cisa.gov/cross-sector-cybersecurity-performance-goals' "$doc"
require_contains 'https://www.cisa.gov/stopransomware/ransomware-guide' "$doc"
require_contains 'https://www.fbi.gov/scams-and-safety/common-scams-and-crimes/ransomware' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/60/v1/r1/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/60/r2/iwd' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/122/final' "$doc"
require_contains 'https://www.nist.gov/privacy-framework' "$doc"
require_contains 'https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final' "$doc"

for field in \
  'data_classification_protection_baseline_present=1' \
  'data_classification_protection_guard_present=1' \
  'nsa_zero_trust_data_pillar_tracked=1' \
  'cisa_cpg_data_protection_tracked=1' \
  'stopransomware_data_extortion_guidance_tracked=1' \
  'fbi_ransomware_data_extortion_guidance_tracked=1' \
  'nist_sp_800_60_information_categorization_tracked=1' \
  'nist_sp_800_122_pii_protection_tracked=1' \
  'nist_privacy_framework_tracked=1' \
  'nist_sp_800_53_data_protection_controls_tracked=1' \
  'data_inventory_required=1' \
  'data_classification_required=1' \
  'sensitive_data_flow_map_required=1' \
  'data_owner_required=1' \
  'data_minimization_required=1' \
  'pii_handling_review_required=1' \
  'data_retention_disposal_required=1' \
  'data_encryption_access_control_required=1' \
  'backup_data_protection_required=1' \
  'secret_pii_log_redaction_required=1' \
  'data_loss_prevention_plan_required=1' \
  'data_exception_owner_required=1' \
  'data_exception_expiration_required=1' \
  'implementation_behavior_changed=0' \
  'sensitive_data_collection_added=0' \
  'pii_collection_added=0' \
  'telemetry_export_added=0' \
  'data_storage_service_added=0' \
  'analytics_service_added=0' \
  'encryption_at_rest_added=0' \
  'dlp_added=0' \
  'data_retention_enforcement_added=0' \
  'data_purge_execution_added=0' \
  'breach_notification_service_added=0' \
  'production_data_protection_claim_allowed=0' \
  'customer_data_handling_claim_allowed=0' \
  'privacy_compliance_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'data_classification_protection_status_present=1' "$status_doc"

for gate in \
  'data_inventory_present=1' \
  'data_owner_recorded=1' \
  'data_classification_recorded=1' \
  'information_type_categorization_recorded=1' \
  'sensitive_data_flow_map_recorded=1' \
  'pii_presence_review_recorded=1' \
  'pii_confidentiality_impact_recorded=1' \
  'data_minimization_review_recorded=1' \
  'collection_purpose_recorded=1' \
  'access_control_recorded=1' \
  'encryption_at_rest_decision_recorded=1' \
  'encryption_in_transit_decision_recorded=1' \
  'retention_period_recorded=1' \
  'disposal_process_recorded=1' \
  'backup_data_protection_recorded=1' \
  'log_report_redaction_recorded=1' \
  'secret_marker_and_pii_scan_recorded=1' \
  'data_loss_prevention_plan_recorded=1' \
  'incident_response_handoff_recorded=1' \
  'exception_owner_recorded=1' \
  'exception_expiration_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'sensitive_data_collection_allowed=0' \
  'pii_collection_allowed=0' \
  'telemetry_export_allowed=0' \
  'customer_data_handling_claim_allowed=0' \
  'data_storage_service_claim_allowed=0' \
  'analytics_claim_allowed=0' \
  'encryption_at_rest_claim_allowed=0' \
  'dlp_claim_allowed=0' \
  'privacy_compliance_claim_allowed=0' \
  'breach_notification_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for boundary_field in \
  'latticra_data_metadata_only=1' \
  'latticra_report_redaction_boundary_guarded=1' \
  'latticra_secret_material_guarded=1' \
  'latticra_sensitive_data_collection_added=0' \
  'latticra_pii_collection_added=0' \
  'latticra_telemetry_export_added=0' \
  'latticra_data_storage_service_added=0' \
  'latticra_dlp_runtime_added=0' \
  'latticra_data_purge_runtime_added=0' \
  'latticra_data_authority_granted=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'log_redaction_required=1' docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_contains 'retention_disposal_policy_required=1' docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_contains 'backup_encryption_and_access_control_recorded=1' docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md
require_contains 'side_channel_sensitive_data_review_required=1' docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
require_contains 'credential_secret_storage_review_required=1' docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md
require_contains 'network_data_flow_map_recorded=1' docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md
require_contains 'configuration_secret_review_required=1' docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_contains 'user-facing reports must not leak sensitive internals' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'data classification and protection evidence' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'data_classification_protection_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-data-classification-protection-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md' SECURITY.md
require_contains 'data_classification_protection_baseline_present=1' README.md
require_contains 'data_classification_protection_baseline_present=1' STATUS.md
require_contains 'DATA_CLASSIFICATION_PROTECTION_BASELINE_STATUS.md' docs/status/README.md
require_contains 'data_classification_protection_baseline_present=1' docs/status/README.md
require_contains 'Latest data classification and protection baseline note: 2026-05-27 CDT' docs/status/CURRENT_STATUS.md
require_contains 'DATA_CLASSIFICATION_PROTECTION_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Data classification and protection baseline' docs/security.html
require_contains 'DATA_CLASSIFICATION_PROTECTION_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-data-classification-protection-baseline.sh' Makefile
require_contains 'data-classification-protection-baseline:' Makefile
require_contains 'sh ./scripts/test-data-classification-protection-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-data-classification-protection-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'data_classification_protection_baseline: ok\n'

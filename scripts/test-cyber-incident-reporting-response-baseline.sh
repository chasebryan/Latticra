#!/usr/bin/env sh
set -eu

doc="docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md"
status_doc="docs/status/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'cyber incident reporting response baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'cyber incident reporting response baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
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
require_file scripts/test-zero-trust-runtime-authority-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: cyber incident reporting and response baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Authoritative Reporting and Response Sources' "$doc"
require_contains 'CISA Reporting a Cyber Incident' "$doc"
require_contains 'FBI Cyber' "$doc"
require_contains 'CISA/FBI/NSA/MS-ISAC #StopRansomware Guide' "$doc"
require_contains 'FBI 2025 IC3 Annual Report' "$doc"
require_contains 'https://www.cisa.gov/reporting-cyber-incident' "$doc"
require_contains 'https://www.fbi.gov/investigate/cyber' "$doc"
require_contains 'https://www.cisa.gov/stopransomware/ransomware-guide' "$doc"
require_contains 'https://www.cisa.gov/stopransomware/report-ransomware' "$doc"
require_contains 'https://www.fbi.gov/how-we-can-help-you/scams-and-safety/common-frauds-and-scams/ransomware' "$doc"
require_contains 'https://www.fbi.gov/file-repository/2025_ic3report.pdf' "$doc"

for field in \
  'cyber_incident_reporting_response_baseline_present=1' \
  'cyber_incident_reporting_response_guard_present=1' \
  'cisa_reporting_channel_documented=1' \
  'fbi_cyber_reporting_channel_documented=1' \
  'ic3_reporting_channel_documented=1' \
  'stopransomware_joint_guidance_tracked=1' \
  'fbi_ic3_annual_report_refresh_required=1' \
  'incident_classification_required=1' \
  'authorized_testing_boundary_required=1' \
  'evidence_preservation_required=1' \
  'volatile_evidence_preservation_required=1' \
  'chain_of_custody_required_before_claim=1' \
  'out_of_band_communications_required_for_compromise=1' \
  'ransomware_data_extortion_response_checklist_required=1' \
  'legal_regulatory_notification_review_required=1' \
  'law_enforcement_contact_path_required=1' \
  'internal_external_notification_plan_required=1' \
  'operator_confirmation_metadata_only_required=1' \
  'implementation_behavior_changed=0' \
  'monitoring_added=0' \
  'detection_added=0' \
  'containment_added=0' \
  'forensic_collection_added=0' \
  'federal_reporting_performed=0' \
  'law_enforcement_contact_performed=0' \
  'customer_notification_performed=0' \
  'breach_notification_authority_claimed=0' \
  'incident_response_service_claimed=0' \
  'ransomware_recovery_capability_claimed=0' \
  'production_monitoring_claimed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'cyber_incident_reporting_response_status_present=1' "$status_doc"

for route in \
  'reporting_subject_known=1' \
  'incident_class_known=1' \
  'affected_asset_identity_known=1' \
  'affected_data_sensitivity_known=1' \
  'operator_authorization_known=1' \
  'organization_reporting_owner_known=1' \
  'cisa_reporting_route_visible=1' \
  'fbi_field_office_route_visible=1' \
  'ic3_route_visible=1' \
  'local_law_enforcement_or_regulator_review_prompt_visible=1' \
  'privacy_legal_notification_review_prompt_visible=1' \
  'do_not_transmit_without_operator_approval=1'
do
  require_contains "$route" "$doc"
done

for gate in \
  'incident_kind_known=1' \
  'requested_response_effect_known=1' \
  'caller_identity_known=1' \
  'operator_or_organization_context_known=1' \
  'asset_scope_recorded=1' \
  'data_scope_recorded=1' \
  'legal_regulatory_review_required=1' \
  'evidence_preservation_plan_recorded=1' \
  'volatile_evidence_decision_recorded=1' \
  'chain_of_custody_plan_recorded=1' \
  'out_of_band_communications_plan_recorded=1' \
  'restoration_priority_recorded=1' \
  'reporting_route_selected_by_operator=1' \
  'policy_decision_reported=1' \
  'denial_reason_reported=1' \
  'audit_record_emitted=1' \
  'operator_confirmation_recorded_as_metadata_only=1' \
  'operator_confirmation_non_override_test_present=1' \
  'non_claim_review_completed=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'host_isolation_allowed=0' \
  'forensic_collection_allowed=0' \
  'credential_rotation_allowed=0' \
  'system_restore_allowed=0' \
  'federal_report_submission_allowed=0' \
  'law_enforcement_contact_allowed=0' \
  'customer_notification_allowed=0' \
  'breach_notification_allowed=0' \
  'ransomware_payment_decision_allowed=0' \
  'indicator_publication_allowed=0' \
  'artifact_deletion_allowed=0' \
  'incident_response_service_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

require_contains 'cyber_incident_reporting_response_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-cyber-incident-reporting-response-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md' SECURITY.md
require_contains 'cyber_incident_reporting_response_baseline_present=1' README.md
require_contains 'cyber_incident_reporting_response_baseline_present=1' STATUS.md
require_contains 'CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE_STATUS.md' docs/status/README.md
require_contains 'cyber_incident_reporting_response_baseline_present=1' docs/status/README.md
require_contains 'Latest cyber incident reporting and response baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Cyber incident reporting and response baseline' docs/security.html
require_contains 'CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-cyber-incident-reporting-response-baseline.sh' Makefile
require_contains 'cyber-incident-reporting-response-baseline:' Makefile
require_contains 'sh ./scripts/test-cyber-incident-reporting-response-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-cyber-incident-reporting-response-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'cyber_incident_reporting_response_baseline: ok\n'

#!/usr/bin/env sh
set -eu

doc="docs/SECURITY_LOGGING_MONITORING_BASELINE.md"
status_doc="docs/status/SECURITY_LOGGING_MONITORING_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'security logging monitoring baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'security logging monitoring baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_file docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-report-redaction-boundary.sh
require_file scripts/test-secret-material-guard.sh
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: security logging, monitoring, and detection baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Authoritative Logging and Detection Sources' "$doc"
require_contains 'CISA/FBI/NSA international Best Practices for Event Logging and Threat Detection' "$doc"
require_contains 'NSA release for Best Practices for Event Logging and Threat Detection' "$doc"
require_contains 'CISA Logging Made Easy' "$doc"
require_contains 'CISA Use Logging on Business Systems' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals' "$doc"
require_contains 'NIST SP 800-92 Guide to Computer Security Log Management' "$doc"
require_contains 'NIST SP 800-92 Rev. 1 initial public draft' "$doc"
require_contains 'NIST Cybersecurity Framework 2.0 Detect function' "$doc"
require_contains 'NIST SP 800-53 Rev. 5 Audit and Accountability controls' "$doc"
require_contains 'https://www.cisa.gov/resources-tools/resources/best-practices-event-logging-and-threat-detection' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3880942/nsa-joins-allies-in-releasing-best-practices-for-event-logging/' "$doc"
require_contains 'https://www.cisa.gov/resources-tools/services/logging-made-easy' "$doc"
require_contains 'https://www.cisa.gov/use-logging-business-systems' "$doc"
require_contains 'https://www.cisa.gov/cross-sector-cybersecurity-performance-goals' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/92/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/92/r1/ipd' "$doc"
require_contains 'https://www.nist.gov/cyberframework/detect' "$doc"
require_contains 'https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final' "$doc"

for field in \
  'security_logging_monitoring_baseline_present=1' \
  'security_logging_monitoring_guard_present=1' \
  'cisa_fbi_nsa_event_logging_guidance_tracked=1' \
  'nsa_event_logging_release_tracked=1' \
  'cisa_logging_made_easy_tracked=1' \
  'cisa_use_logging_on_business_systems_tracked=1' \
  'cisa_cpg_log_collection_tracked=1' \
  'nist_sp_800_92_log_management_tracked=1' \
  'nist_sp_800_92_rev1_draft_tracked=1' \
  'nist_csf_detect_function_tracked=1' \
  'nist_sp_800_53_audit_accountability_tracked=1' \
  'security_event_source_inventory_required=1' \
  'audit_event_selection_required=1' \
  'runtime_authority_decision_logging_required=1' \
  'identity_access_event_logging_required=1' \
  'privileged_action_logging_required=1' \
  'security_error_logging_required=1' \
  'configuration_change_logging_required=1' \
  'log_redaction_required=1' \
  'secret_free_log_guard_required=1' \
  'log_integrity_tamper_resistance_required=1' \
  'time_synchronization_required=1' \
  'retention_disposal_policy_required=1' \
  'critical_log_source_disable_alert_required=1' \
  'detection_triage_owner_required=1' \
  'incident_handoff_path_required=1' \
  'operator_log_access_review_required=1' \
  'implementation_behavior_changed=0' \
  'log_collector_added=0' \
  'siem_added=0' \
  'telemetry_export_added=0' \
  'host_sensor_added=0' \
  'network_sensor_added=0' \
  'alerting_service_added=0' \
  'log_storage_added=0' \
  'detection_rule_added=0' \
  'production_monitoring_claim_allowed=0' \
  'detection_service_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'security_logging_monitoring_status_present=1' "$status_doc"

for gate in \
  'security_event_source_inventory_present=1' \
  'log_source_owner_recorded=1' \
  'log_schema_or_field_contract_present=1' \
  'audit_event_selection_recorded=1' \
  'runtime_decision_event_recorded=1' \
  'denial_reason_event_recorded=1' \
  'identity_access_event_recorded=1' \
  'privileged_action_event_recorded=1' \
  'configuration_change_event_recorded=1' \
  'security_relevant_error_event_recorded=1' \
  'event_severity_taxonomy_recorded=1' \
  'time_source_recorded=1' \
  'log_redaction_review_recorded=1' \
  'secret_marker_scan_recorded=1' \
  'log_integrity_control_recorded=1' \
  'log_access_control_recorded=1' \
  'retention_period_recorded=1' \
  'disposal_process_recorded=1' \
  'centralization_or_export_path_recorded=1' \
  'critical_log_source_disable_alert_recorded=1' \
  'detection_triage_owner_recorded=1' \
  'incident_handoff_path_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'production_log_monitoring_allowed=0' \
  'production_audit_claim_allowed=0' \
  'siem_integration_claim_allowed=0' \
  'telemetry_export_allowed=0' \
  'host_monitoring_allowed=0' \
  'network_monitoring_allowed=0' \
  'alerting_service_allowed=0' \
  'detection_service_claim_allowed=0' \
  'security_operations_claim_allowed=0' \
  'log_collection_service_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for boundary_field in \
  'latticra_local_report_metadata_only=1' \
  'latticra_runtime_policy_decision_reports_local=1' \
  'latticra_report_redaction_boundary_guarded=1' \
  'latticra_secret_material_guarded=1' \
  'latticra_log_collection_service_added=0' \
  'latticra_remote_telemetry_added=0' \
  'latticra_detection_runtime_added=0' \
  'latticra_monitoring_authority_granted=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'audit_record_required_before_authority=1' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'policy_decision_reported=1' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'denial_reason_reported=1' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'report_redaction_boundary_guard_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_engine_log_redaction_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_engine_log_sanitization_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_engine_event_boundary_sanitization_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_engine_failure_event_sanitization_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_event_ingestion_sanitization_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_evidence_log_redaction_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_status_event_sanitization_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_status_boundary_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_direct_status_assignment_forbidden=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_blocked_plan_sanitization_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_blocked_plan_error_injection_guard_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_console_navigation_root_boundary_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'installer_ui_console_navigation_path_reflection_denial_required=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'evidence_preservation_required=1' docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
require_contains 'audit_record_emitted=1' docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
require_contains 'sanitize_log_line(line.as_ref())' scripts/test-report-redaction-boundary.sh
require_contains 'secret_content_pattern=' scripts/test-secret-material-guard.sh
require_contains 'security_logging_monitoring_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/SECURITY_LOGGING_MONITORING_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-security-logging-monitoring-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/SECURITY_LOGGING_MONITORING_BASELINE.md' SECURITY.md
require_contains 'security_logging_monitoring_baseline_present=1' README.md
require_contains 'security_logging_monitoring_baseline_present=1' STATUS.md
require_contains 'SECURITY_LOGGING_MONITORING_BASELINE_STATUS.md' docs/status/README.md
require_contains 'security_logging_monitoring_baseline_present=1' docs/status/README.md
require_contains 'Latest security logging, monitoring, and detection baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'SECURITY_LOGGING_MONITORING_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Security logging, monitoring, and detection baseline' docs/security.html
require_contains 'SECURITY_LOGGING_MONITORING_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-security-logging-monitoring-baseline.sh' Makefile
require_contains 'security-logging-monitoring-baseline:' Makefile
require_contains 'sh ./scripts/test-security-logging-monitoring-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-security-logging-monitoring-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'security_logging_monitoring_baseline: ok\n'

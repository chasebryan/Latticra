# Latticra Security Logging, Monitoring, and Detection Baseline

Status: security logging, monitoring, and detection baseline
Source refresh date: 2026-05-26
Scope: security event source inventory, audit event selection, runtime-authority decision logs, identity and access events, privileged actions, log redaction, log integrity, retention, disposal, time source, detection triage, incident handoff, and monitoring non-claims before hosted services, production monitoring, detection services, SIEM export, or security operations claims.

This baseline records logging, monitoring, and detection requirements only. It does not implement a log collector, SIEM, telemetry export, host sensor, network sensor, detection rule, alerting service, log storage, monitoring service, incident detection service, compliance, or runtime authority.

## Authoritative Logging and Detection Sources

Date checked: 2026-05-26

| Source | Latticra use |
| --- | --- |
| CISA/FBI/NSA international Best Practices for Event Logging and Threat Detection | event logging baseline, threat detection, cloud/enterprise/mobile/OT visibility, and resource-aware logging vocabulary |
| NSA release for Best Practices for Event Logging and Threat Detection | national-security, DoD, DIB, and living-off-the-land detection context |
| CISA Logging Made Easy | centralized log management, user activity visibility, Sysmon data, real-time alerting, and locally run privacy caveats |
| CISA Use Logging on Business Systems | what-to-log, centralization, monitoring, alerting, and log-review planning vocabulary |
| CISA Cross-Sector Cybersecurity Performance Goals | log collection, account security, incident response, and baseline operational practice context |
| NIST SP 800-92 Guide to Computer Security Log Management | log management infrastructure, generation, transmission, storage, access, analysis, and disposal vocabulary |
| NIST SP 800-92 Rev. 1 initial public draft | current log-management planning playbook vocabulary for future improvement plans |
| NIST Cybersecurity Framework 2.0 Detect function | security continuous monitoring and event discovery vocabulary |
| NIST SP 800-53 Rev. 5 Audit and Accountability controls | audit event, audit record, audit storage, audit review, and audit reduction vocabulary |

Authoritative URLs:

```text
https://www.cisa.gov/resources-tools/resources/best-practices-event-logging-and-threat-detection
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3880942/nsa-joins-allies-in-releasing-best-practices-for-event-logging/
https://www.cisa.gov/resources-tools/services/logging-made-easy
https://www.cisa.gov/use-logging-business-systems
https://www.cisa.gov/cybersecurity-performance-goals-cpgs
https://csrc.nist.gov/pubs/sp/800/92/final
https://csrc.nist.gov/pubs/sp/800/92/r1/ipd
https://www.nist.gov/cyberframework/detect
https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final
```

## Current Fields

```text
security_logging_monitoring_baseline_present=1
security_logging_monitoring_guard_present=1
cisa_fbi_nsa_event_logging_guidance_tracked=1
nsa_event_logging_release_tracked=1
cisa_logging_made_easy_tracked=1
cisa_use_logging_on_business_systems_tracked=1
cisa_cpg_log_collection_tracked=1
nist_sp_800_92_log_management_tracked=1
nist_sp_800_92_rev1_draft_tracked=1
nist_csf_detect_function_tracked=1
nist_sp_800_53_audit_accountability_tracked=1
security_event_source_inventory_required=1
audit_event_selection_required=1
runtime_authority_decision_logging_required=1
identity_access_event_logging_required=1
privileged_action_logging_required=1
security_error_logging_required=1
configuration_change_logging_required=1
log_redaction_required=1
secret_free_log_guard_required=1
log_integrity_tamper_resistance_required=1
time_synchronization_required=1
retention_disposal_policy_required=1
critical_log_source_disable_alert_required=1
detection_triage_owner_required=1
incident_handoff_path_required=1
operator_log_access_review_required=1
implementation_behavior_changed=0
log_collector_added=0
siem_added=0
telemetry_export_added=0
host_sensor_added=0
network_sensor_added=0
alerting_service_added=0
log_storage_added=0
detection_rule_added=0
production_monitoring_claim_allowed=0
detection_service_claim_allowed=0
compliance_claim_allowed=0
external_endorsement_claimed=0
```

## Required Logging and Monitoring Promotion Gate

No hosted service, production runtime, remote access path, privileged administration surface, security monitoring claim, detection-service claim, SIEM integration, telemetry export, or production audit claim may be promoted until this gate is complete:

```text
security_event_source_inventory_present=1
log_source_owner_recorded=1
log_schema_or_field_contract_present=1
audit_event_selection_recorded=1
runtime_decision_event_recorded=1
denial_reason_event_recorded=1
identity_access_event_recorded=1
privileged_action_event_recorded=1
configuration_change_event_recorded=1
security_relevant_error_event_recorded=1
event_severity_taxonomy_recorded=1
time_source_recorded=1
log_redaction_review_recorded=1
secret_marker_scan_recorded=1
log_integrity_control_recorded=1
log_access_control_recorded=1
retention_period_recorded=1
disposal_process_recorded=1
centralization_or_export_path_recorded=1
critical_log_source_disable_alert_recorded=1
detection_triage_owner_recorded=1
incident_handoff_path_recorded=1
operator_visible_non_claims_recorded=1
```

Until this gate is complete:

```text
production_log_monitoring_allowed=0
production_audit_claim_allowed=0
siem_integration_claim_allowed=0
telemetry_export_allowed=0
host_monitoring_allowed=0
network_monitoring_allowed=0
alerting_service_allowed=0
detection_service_claim_allowed=0
security_operations_claim_allowed=0
log_collection_service_claim_allowed=0
```

## Latticra Boundary

Current Latticra logging and reporting work remains local, deterministic, and no-effect.

```text
latticra_local_report_metadata_only=1
latticra_runtime_policy_decision_reports_local=1
latticra_report_redaction_boundary_guarded=1
latticra_secret_material_guarded=1
latticra_log_collection_service_added=0
latticra_remote_telemetry_added=0
latticra_detection_runtime_added=0
latticra_monitoring_authority_granted=0
```

## Current Evidence

Current supporting evidence:

```text
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
SECURITY.md
scripts/test-report-redaction-boundary.sh
scripts/test-secret-material-guard.sh
scripts/test-high-assurance-security-baseline.sh
scripts/test-security-logging-monitoring-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-security-logging-monitoring-baseline.sh
```

# Latticra Security Logging, Monitoring, and Detection Baseline Status

Status: status record for security logging, monitoring, and detection baseline
Date: 2026-05-26

## Scope

This record tracks the security logging, monitoring, and detection baseline for security event source inventory, audit event selection, runtime-authority decision logs, identity and access events, privileged actions, log redaction, log integrity, retention, disposal, time source, detection triage, incident handoff, and monitoring non-claims.

It does not implement a log collector, SIEM, telemetry export, host sensor, network sensor, detection rule, alerting service, log storage, monitoring service, incident detection service, compliance, or runtime authority.

## Current fields

```text
security_logging_monitoring_baseline_present=1
security_logging_monitoring_status_present=1
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

## Validation

```sh
sh scripts/test-security-logging-monitoring-baseline.sh
```

Expected output:

```text
security_logging_monitoring_baseline: ok
```

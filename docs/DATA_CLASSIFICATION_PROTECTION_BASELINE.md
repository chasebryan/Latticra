# Latticra Data Classification and Protection Baseline

Status: data classification and protection baseline
Source refresh date: 2026-05-27
Scope: data inventory, data classification, sensitive-data flow mapping, PII review, data minimization, retention, disposal, encryption and access-control planning, backup data protection, log/report redaction, data-loss prevention planning, exception ownership, and data-handling non-claims before hosted services, telemetry export, data storage services, production analytics, customer-data handling, or production data-protection claims.

This baseline records data classification and protection requirements only. It does not implement data collection, PII collection, telemetry export, data storage, analytics, encryption at rest, DLP, privacy engineering, data purge, data retention enforcement, breach notification, compliance, or runtime authority.

## Authoritative Data Protection Sources

Date checked: 2026-05-27

| Source | Latticra use |
| --- | --- |
| NSA Zero Trust Data Pillar guidance | data inventory, data tagging, labeling, encryption, access control, loss prevention, and data-at-rest/in-transit protection vocabulary |
| CISA Cross-Sector Cybersecurity Performance Goals | asset/data protection, secure configuration, backup/recovery, account security, and baseline operational data-protection context |
| CISA/FBI/NSA/MS-ISAC #StopRansomware Guide | data extortion, exfiltration, offline backups, encryption, recovery, and incident-response handoff vocabulary |
| FBI ransomware and data-extortion guidance | data theft, data ransom, law-enforcement reporting, and victim response context |
| NIST SP 800-60 Vol. 1 Rev. 1 and SP 800-60 Rev. 2 draft | information type categorization, confidentiality/integrity/availability impact, and security category vocabulary |
| NIST SP 800-122 Guide to Protecting the Confidentiality of PII | PII identification, confidentiality impact, safeguards, incident planning, and PII handling vocabulary |
| NIST Privacy Framework 1.0 and 1.1 draft | data processing inventory, privacy risk management, governance, control, communication, and protection vocabulary |
| NIST SP 800-53 Rev. 5 Media Protection, Privacy, Access Control, Audit, and System and Communications Protection controls | data access, media protection, retention/disposal, PII processing, audit, and transmission protection vocabulary |

Authoritative URLs:

```text
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3735130/nsa-issues-guidance-for-maturing-data-security/
https://www.cisa.gov/cybersecurity-performance-goals-cpgs
https://www.cisa.gov/stopransomware/ransomware-guide
https://www.fbi.gov/scams-and-safety/common-scams-and-crimes/ransomware
https://csrc.nist.gov/pubs/sp/800/60/v1/r1/final
https://csrc.nist.gov/pubs/sp/800/60/r2/iwd
https://csrc.nist.gov/pubs/sp/800/122/final
https://www.nist.gov/privacy-framework
https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final
```

## Current Fields

```text
data_classification_protection_baseline_present=1
data_classification_protection_guard_present=1
nsa_zero_trust_data_pillar_tracked=1
cisa_cpg_data_protection_tracked=1
stopransomware_data_extortion_guidance_tracked=1
fbi_ransomware_data_extortion_guidance_tracked=1
nist_sp_800_60_information_categorization_tracked=1
nist_sp_800_122_pii_protection_tracked=1
nist_privacy_framework_tracked=1
nist_sp_800_53_data_protection_controls_tracked=1
data_inventory_required=1
data_classification_required=1
sensitive_data_flow_map_required=1
data_owner_required=1
data_minimization_required=1
pii_handling_review_required=1
data_retention_disposal_required=1
data_encryption_access_control_required=1
backup_data_protection_required=1
secret_pii_log_redaction_required=1
data_loss_prevention_plan_required=1
data_exception_owner_required=1
data_exception_expiration_required=1
implementation_behavior_changed=0
sensitive_data_collection_added=0
pii_collection_added=0
telemetry_export_added=0
data_storage_service_added=0
analytics_service_added=0
encryption_at_rest_added=0
dlp_added=0
data_retention_enforcement_added=0
data_purge_execution_added=0
breach_notification_service_added=0
production_data_protection_claim_allowed=0
customer_data_handling_claim_allowed=0
privacy_compliance_claim_allowed=0
external_endorsement_claimed=0
```

## Required Data Promotion Gate

No hosted service, production runtime, production installer, production package, telemetry export, analytics feature, data storage service, customer-data handling claim, PII processing claim, encryption-at-rest claim, DLP claim, data retention claim, data deletion claim, breach-notification claim, privacy claim, or production data-protection claim may be promoted until this gate is complete:

```text
data_inventory_present=1
data_owner_recorded=1
data_classification_recorded=1
information_type_categorization_recorded=1
sensitive_data_flow_map_recorded=1
pii_presence_review_recorded=1
pii_confidentiality_impact_recorded=1
data_minimization_review_recorded=1
collection_purpose_recorded=1
access_control_recorded=1
encryption_at_rest_decision_recorded=1
encryption_in_transit_decision_recorded=1
retention_period_recorded=1
disposal_process_recorded=1
backup_data_protection_recorded=1
log_report_redaction_recorded=1
secret_marker_and_pii_scan_recorded=1
data_loss_prevention_plan_recorded=1
incident_response_handoff_recorded=1
exception_owner_recorded=1
exception_expiration_recorded=1
operator_visible_non_claims_recorded=1
```

Until this gate is complete:

```text
sensitive_data_collection_allowed=0
pii_collection_allowed=0
telemetry_export_allowed=0
customer_data_handling_claim_allowed=0
data_storage_service_claim_allowed=0
analytics_claim_allowed=0
encryption_at_rest_claim_allowed=0
dlp_claim_allowed=0
privacy_compliance_claim_allowed=0
breach_notification_claim_allowed=0
```

## Latticra Boundary

Current Latticra data-related records remain evidence and no-effect contract work.

```text
latticra_data_metadata_only=1
latticra_report_redaction_boundary_guarded=1
latticra_secret_material_guarded=1
latticra_sensitive_data_collection_added=0
latticra_pii_collection_added=0
latticra_telemetry_export_added=0
latticra_data_storage_service_added=0
latticra_dlp_runtime_added=0
latticra_data_purge_runtime_added=0
latticra_data_authority_granted=0
```

## Current Evidence

Current supporting evidence:

```text
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/SECURITY_LOGGING_MONITORING_BASELINE.md
docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md
docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md
docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md
docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
docs/security/C_CPP_SECURITY_PROFILE.md
SECURITY.md
scripts/test-secret-material-guard.sh
scripts/test-report-redaction-boundary.sh
scripts/test-data-classification-protection-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-data-classification-protection-baseline.sh
```

# Latticra Cyber Incident Reporting and Response Baseline

Status: cyber incident reporting and response baseline
Source refresh date: 2026-05-26
Scope: vulnerability reports, suspected compromise triage, ransomware and data-extortion reporting paths, evidence preservation, communications routing, public non-claims, and future incident-response automation gates.

This baseline records reporting and response posture only. It does not implement monitoring, detection, containment, forensic acquisition, recovery, federal reporting, customer notification, breach notification, law-enforcement contact, ransomware recovery, or incident-response services.

## Authoritative Reporting and Response Sources

Date checked: 2026-05-26

| Source | Latticra use |
| --- | --- |
| CISA Reporting a Cyber Incident | federal reporting path vocabulary and voluntary cyber incident reporting expectation |
| FBI Cyber | FBI/IC3 reporting path vocabulary for cyber-enabled crime, fraud, ongoing threats, and field-office escalation |
| CISA/FBI/NSA/MS-ISAC #StopRansomware Guide | ransomware and data-extortion prevention, response, evidence preservation, out-of-band communication, and contact-path vocabulary |
| CISA Report Ransomware | ransomware incident reporting route awareness |
| FBI Ransomware | FBI ransomware reporting route awareness |
| FBI 2025 IC3 Annual Report | current FBI cybercrime trend refresh checkpoint |

Authoritative URLs:

```text
https://www.cisa.gov/reporting-cyber-incident
https://www.fbi.gov/investigate/cyber
https://www.cisa.gov/stopransomware/ransomware-guide
https://www.cisa.gov/stopransomware/report-ransomware
https://www.fbi.gov/how-we-can-help-you/scams-and-safety/common-frauds-and-scams/ransomware
https://www.fbi.gov/file-repository/2025_ic3report.pdf
```

## Current Fields

```text
cyber_incident_reporting_response_baseline_present=1
cyber_incident_reporting_response_guard_present=1
cisa_reporting_channel_documented=1
fbi_cyber_reporting_channel_documented=1
ic3_reporting_channel_documented=1
stopransomware_joint_guidance_tracked=1
fbi_ic3_annual_report_refresh_required=1
incident_classification_required=1
authorized_testing_boundary_required=1
evidence_preservation_required=1
volatile_evidence_preservation_required=1
chain_of_custody_required_before_claim=1
out_of_band_communications_required_for_compromise=1
ransomware_data_extortion_response_checklist_required=1
legal_regulatory_notification_review_required=1
law_enforcement_contact_path_required=1
internal_external_notification_plan_required=1
operator_confirmation_metadata_only_required=1
implementation_behavior_changed=0
monitoring_added=0
detection_added=0
containment_added=0
forensic_collection_added=0
federal_reporting_performed=0
law_enforcement_contact_performed=0
customer_notification_performed=0
breach_notification_authority_claimed=0
incident_response_service_claimed=0
ransomware_recovery_capability_claimed=0
production_monitoring_claimed=0
external_endorsement_claimed=0
```

## Reporting Route Requirements

Latticra must not present itself as reporting on behalf of users or operators. Future reporting-capable features require a separate operator-approved contract and review.

Minimum route fields before any report-assistance feature exists:

```text
reporting_subject_known=1
incident_class_known=1
affected_asset_identity_known=1
affected_data_sensitivity_known=1
operator_authorization_known=1
organization_reporting_owner_known=1
cisa_reporting_route_visible=1
fbi_field_office_route_visible=1
ic3_route_visible=1
local_law_enforcement_or_regulator_review_prompt_visible=1
privacy_legal_notification_review_prompt_visible=1
do_not_transmit_without_operator_approval=1
```

## Response Gate

No future incident-response request may isolate hosts, collect forensic artifacts, contact law enforcement, submit federal reports, notify customers, rotate credentials, restore systems, delete artifacts, publish indicators, or make breach/ransomware claims until this gate is complete:

```text
incident_kind_known=1
requested_response_effect_known=1
caller_identity_known=1
operator_or_organization_context_known=1
asset_scope_recorded=1
data_scope_recorded=1
legal_regulatory_review_required=1
evidence_preservation_plan_recorded=1
volatile_evidence_decision_recorded=1
chain_of_custody_plan_recorded=1
out_of_band_communications_plan_recorded=1
restoration_priority_recorded=1
reporting_route_selected_by_operator=1
policy_decision_reported=1
denial_reason_reported=1
audit_record_emitted=1
operator_confirmation_recorded_as_metadata_only=1
operator_confirmation_non_override_test_present=1
non_claim_review_completed=1
```

Until this gate is complete:

```text
host_isolation_allowed=0
forensic_collection_allowed=0
credential_rotation_allowed=0
system_restore_allowed=0
federal_report_submission_allowed=0
law_enforcement_contact_allowed=0
customer_notification_allowed=0
breach_notification_allowed=0
ransomware_payment_decision_allowed=0
indicator_publication_allowed=0
artifact_deletion_allowed=0
incident_response_service_claim_allowed=0
```

## Current Evidence

Current supporting evidence:

```text
SECURITY.md
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
scripts/test-high-assurance-security-baseline.sh
scripts/test-zero-trust-runtime-authority-baseline.sh
scripts/test-cyber-incident-reporting-response-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-cyber-incident-reporting-response-baseline.sh
```

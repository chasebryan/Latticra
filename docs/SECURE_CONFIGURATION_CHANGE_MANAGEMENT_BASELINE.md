# Latticra Secure Configuration and Change Management Baseline

Status: secure configuration and change management baseline
Source refresh date: 2026-05-26
Scope: secure configuration baselines, configuration item inventory, configuration checklists, secure defaults, approved change records, rollback evidence, drift detection, exception ownership, and configuration non-claims before hosted services, production installers, production runtime, infrastructure automation, or hardening claims.

This baseline records secure configuration and change-management requirements only. It does not implement host configuration, infrastructure configuration, configuration scanning, configuration enforcement, drift detection, change approval workflow, rollback execution, compliance, or runtime authority.

## Authoritative Configuration Sources

Date checked: 2026-05-26

| Source | Latticra use |
| --- | --- |
| NIST SP 800-128 Guide for Security-Focused Configuration Management of Information Systems | security-focused configuration management, baseline configuration, configuration control, configuration monitoring, and SecCM vocabulary |
| NIST SP 800-70 Rev. 5 National Checklist Program for IT Products | security configuration checklist, secure posture verification, unauthorized change detection, and checklist artifact vocabulary |
| NIST SP 800-53 Rev. 5 Configuration Management controls | CM family vocabulary for baseline configuration, change control, configuration settings, least functionality, and configuration monitoring |
| CISA Cross-Sector Cybersecurity Performance Goals | secure configuration, default password, asset inventory, vulnerability reduction, and operational baseline context |
| CISA/FBI Product Security Bad Practices | default password, insecure default, missing security artifact, and customer-risk reduction blockers |
| NSA and CISA Red and Blue Teams Share Top Ten Cybersecurity Misconfigurations | common misconfiguration classes, default configurations, poor patch/configuration hygiene, and enterprise misconfiguration visibility vocabulary |
| CISA/NSA/FBI secure-by-design and secure-by-default principles | secure default baseline, manufacturer ownership of customer security outcomes, and no burden-shifting configuration expectations |

Authoritative URLs:

```text
https://csrc.nist.gov/pubs/sp/800/128/upd1/final
https://csrc.nist.gov/pubs/sp/800/70/r5/final
https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final
https://www.cisa.gov/cybersecurity-performance-goals-cpgs
https://www.cisa.gov/resources-tools/resources/product-security-bad-practices
https://www.cisa.gov/news-events/alerts/2025/01/17/cisa-and-fbi-release-updated-guidance-product-security-bad-practices
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3549369/nsa-and-cisa-advise-on-top-ten-cybersecurity-misconfigurations/
https://www.cisa.gov/news-events/news/us-and-international-partners-publish-secure-design-and-default-principles-and-approaches
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3361073/nsa-us-and-international-partners-issue-guidance-on-securing-technology-by-desi/
```

## Current Fields

```text
secure_configuration_change_management_baseline_present=1
secure_configuration_change_management_guard_present=1
nist_sp_800_128_configuration_management_tracked=1
nist_sp_800_70_rev5_checklist_tracked=1
nist_sp_800_53_configuration_management_tracked=1
cisa_cpg_secure_configuration_tracked=1
cisa_fbi_product_security_bad_practices_config_tracked=1
nsa_cisa_top_misconfigurations_tracked=1
cisa_nsa_fbi_secure_by_default_tracked=1
configuration_item_inventory_required=1
secure_baseline_configuration_required=1
configuration_checklist_required=1
approved_change_record_required=1
configuration_change_owner_required=1
configuration_change_risk_review_required=1
configuration_change_test_evidence_required=1
configuration_rollback_plan_required=1
configuration_drift_detection_required=1
default_credential_forbidden=1
insecure_default_configuration_forbidden=1
configuration_secret_review_required=1
configuration_exception_owner_required=1
configuration_exception_expiration_required=1
implementation_behavior_changed=0
configuration_enforcement_added=0
configuration_scanner_added=0
host_configuration_changed=0
infrastructure_configuration_changed=0
change_approval_workflow_added=0
drift_detection_added=0
rollback_execution_added=0
production_configuration_claim_allowed=0
hosted_service_configuration_claim_allowed=0
configuration_hardening_claim_allowed=0
secure_default_claim_allowed=0
compliance_claim_allowed=0
external_endorsement_claimed=0
```

## Required Configuration Promotion Gate

No hosted service, production runtime, production installer, production package, infrastructure automation lane, host mutation lane, configuration hardening claim, secure-default claim, configuration scanning claim, drift-detection claim, compliance claim, or production configuration claim may be promoted until this gate is complete:

```text
configuration_item_inventory_present=1
configuration_owner_recorded=1
baseline_configuration_recorded=1
configuration_checklist_recorded=1
secure_default_review_recorded=1
default_credential_absence_recorded=1
insecure_default_configuration_absence_recorded=1
change_request_recorded=1
change_owner_recorded=1
change_risk_review_recorded=1
change_test_evidence_recorded=1
rollback_plan_recorded=1
drift_detection_plan_recorded=1
configuration_secret_review_recorded=1
configuration_log_event_recorded=1
exception_owner_recorded=1
exception_expiration_recorded=1
operator_visible_non_claims_recorded=1
```

Until this gate is complete:

```text
host_configuration_change_allowed=0
production_configuration_claim_allowed=0
secure_default_claim_allowed=0
configuration_hardening_claim_allowed=0
configuration_scanning_claim_allowed=0
configuration_enforcement_allowed=0
drift_detection_claim_allowed=0
hosted_service_configuration_claim_allowed=0
infrastructure_as_code_claim_allowed=0
compliance_claim_allowed=0
```

## Latticra Boundary

Current Latticra configuration-related records remain evidence and no-effect contract work.

```text
latticra_configuration_metadata_only=1
latticra_installer_config_authority_allowlist_guarded=1
latticra_installer_ui_artifact_authority_guarded=1
latticra_host_configuration_mutation_added=0
latticra_configuration_enforcement_added=0
latticra_configuration_scanning_added=0
latticra_drift_detection_added=0
latticra_change_approval_workflow_added=0
latticra_configuration_authority_granted=0
```

## Current Evidence

Current supporting evidence:

```text
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
docs/SECURITY_LOGGING_MONITORING_BASELINE.md
docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
docs/security/C_CPP_SECURITY_PROFILE.md
installer/latticra-installer/src/config.rs
installer/scripts/latticra-installer-apply.sh
SECURITY.md
scripts/test-installer-config-authority-allowlist.sh
scripts/test-installer-ui-artifact-authority.sh
scripts/test-high-assurance-security-baseline.sh
scripts/test-secure-configuration-change-management-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-secure-configuration-change-management-baseline.sh
```

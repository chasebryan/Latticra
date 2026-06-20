#!/usr/bin/env sh
set -eu

doc="docs/SECURITY_VALIDATION_ASSESSMENT_BASELINE.md"
status_doc="docs/status/SECURITY_VALIDATION_ASSESSMENT_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'security validation assessment baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'security validation assessment baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_file docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_file docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_file docs/PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE.md
require_file docs/AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md
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

require_contains 'Status: security validation and assessment baseline' "$doc"
require_contains 'Source refresh date: 2026-06-12' "$doc"
require_contains 'Authoritative Validation Sources' "$doc"
require_contains 'CISA Secure by Design' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals 2.0' "$doc"
require_contains 'CISA Secure by Demand Guide' "$doc"
require_contains 'CISA/FBI Product Security Bad Practices' "$doc"
require_contains 'NSA and CISA Top Ten Cybersecurity Misconfigurations' "$doc"
require_contains 'NIST SP 800-115 Technical Guide to Information Security Testing and Assessment' "$doc"
require_contains 'NIST SP 800-37 Rev. 2 Risk Management Framework' "$doc"
require_contains 'NIST SP 800-53A Rev. 5 Assessing Security and Privacy Controls' "$doc"
require_contains 'NIST SP 800-53 Rev. 5 Assessment, Authorization, Risk Assessment, System Integrity, and System Acquisition controls' "$doc"
require_contains 'NIST SP 800-218 SSDF v1.1' "$doc"
require_contains 'https://www.cisa.gov/securebydesign' "$doc"
require_contains 'https://www.cisa.gov/cross-sector-cybersecurity-performance-goals' "$doc"
require_contains 'https://www.cisa.gov/resources-tools/resources/secure-demand-guide' "$doc"
require_contains 'https://www.cisa.gov/news-events/alerts/2025/01/17/cisa-and-fbi-release-updated-guidance-product-security-bad-practices' "$doc"
require_contains 'https://www.cisa.gov/news-events/cybersecurity-advisories/aa23-278a' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/115/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/37/r2/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/53/a/r5/final' "$doc"
require_contains 'https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/218/final' "$doc"

for field in \
  'security_validation_assessment_baseline_present=1' \
  'security_validation_assessment_guard_present=1' \
  'cisa_secure_by_design_validation_tracked=1' \
  'cisa_cpg_third_party_validation_tracked=1' \
  'cisa_cpg_2_0_validation_tracked=1' \
  'cisa_secure_by_demand_validation_tracked=1' \
  'cisa_fbi_product_security_bad_practices_tracked=1' \
  'nsa_cisa_top_misconfigurations_tracked=1' \
  'nist_sp_800_115_security_testing_tracked=1' \
  'nist_sp_800_37_rmf_tracked=1' \
  'nist_sp_800_53a_assessment_tracked=1' \
  'nist_sp_800_53_assessment_controls_tracked=1' \
  'nist_sp_800_218_ssdf_verification_tracked=1' \
  'assessment_scope_required=1' \
  'rules_of_engagement_required=1' \
  'authorization_boundary_required=1' \
  'test_authorization_required=1' \
  'control_objective_mapping_required=1' \
  'safe_test_environment_required=1' \
  'test_data_handling_required=1' \
  'static_dynamic_fuzz_testing_required=1' \
  'vulnerability_scanning_plan_required=1' \
  'penetration_test_plan_required=1' \
  'red_team_exercise_plan_required=1' \
  'finding_severity_and_owner_required=1' \
  'remediation_and_retest_required=1' \
  'independent_review_required=1' \
  'security_assessment_report_required=1' \
  'poam_or_exception_required=1' \
  'continuous_monitoring_required=1' \
  'external_claim_review_required=1' \
  'implementation_behavior_changed=0' \
  'assessment_execution_added=0' \
  'vulnerability_scan_executed=0' \
  'penetration_test_executed=0' \
  'red_team_exercise_executed=0' \
  'third_party_assessment_performed=0' \
  'certification_assessment_performed=0' \
  'compliance_assessment_performed=0' \
  'security_validation_claim_allowed=0' \
  'third_party_validation_claim_allowed=0' \
  'penetration_test_claim_allowed=0' \
  'red_team_claim_allowed=0' \
  'certification_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'production_protection_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'security_validation_assessment_status_present=1' "$status_doc"

for gate in \
  'authorization_boundary_recorded=1' \
  'system_description_recorded=1' \
  'assessment_scope_recorded=1' \
  'rules_of_engagement_recorded=1' \
  'test_authorization_recorded=1' \
  'control_objective_mapping_recorded=1' \
  'tooling_and_methodology_recorded=1' \
  'safe_test_environment_recorded=1' \
  'test_data_handling_recorded=1' \
  'static_analysis_results_recorded=1' \
  'dynamic_test_results_recorded=1' \
  'fuzzing_results_recorded=1' \
  'vulnerability_scan_results_recorded=1' \
  'manual_review_results_recorded=1' \
  'penetration_test_findings_recorded=1' \
  'red_team_findings_recorded=1' \
  'finding_severity_owner_due_date_recorded=1' \
  'remediation_evidence_recorded=1' \
  'retest_evidence_recorded=1' \
  'residual_risk_acceptance_recorded=1' \
  'independent_assessor_review_recorded=1' \
  'security_assessment_report_recorded=1' \
  'poam_or_exception_recorded=1' \
  'continuous_monitoring_plan_recorded=1' \
  'public_claim_review_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'security_release_claim_allowed=0' \
  'third_party_validation_claim_allowed=0' \
  'penetration_test_claim_allowed=0' \
  'red_team_claim_allowed=0' \
  'certification_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'high_assurance_assessment_claim_allowed=0' \
  'production_protection_claim_allowed=0'
do
  require_contains "$closed" "$doc"
  require_contains "$closed" "$status_doc"
done

for boundary_field in \
  'latticra_security_validation_metadata_only=1' \
  'latticra_defensive_threat_model_guarded=1' \
  'latticra_quality_security_standards_guarded=1' \
  'latticra_quality_safety_guards_guarded=1' \
  'latticra_security_assessment_execution_added=0' \
  'latticra_vulnerability_scan_executed=0' \
  'latticra_penetration_test_claimed=0' \
  'latticra_red_team_claimed=0' \
  'latticra_third_party_assessment_claimed=0' \
  'latticra_certification_claimed=0' \
  'latticra_compliance_claimed=0' \
  'latticra_production_protection_claimed=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'defensive_threat_model_validation_refinement_present=1' docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
require_contains 'supply_chain_security_baseline_present=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'vulnerability_management_release_gate_baseline_present=1' docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_contains 'security_logging_monitoring_baseline_present=1' docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_contains 'secure_configuration_change_management_baseline_present=1' docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_contains 'platform_boot_firmware_integrity_baseline_present=1' docs/PLATFORM_BOOT_FIRMWARE_INTEGRITY_BASELINE.md
require_contains 'ai_agentic_automation_security_baseline_present=1' docs/AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md
require_contains 'security_validation_assessment_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/SECURITY_VALIDATION_ASSESSMENT_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-security-validation-assessment-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/SECURITY_VALIDATION_ASSESSMENT_BASELINE.md' SECURITY.md
require_contains 'security_validation_assessment_baseline_present=1' README.md
require_contains 'security_validation_assessment_baseline_present=1' STATUS.md
require_contains 'SECURITY_VALIDATION_ASSESSMENT_BASELINE_STATUS.md' docs/status/README.md
require_contains 'security_validation_assessment_baseline_present=1' docs/status/README.md
require_contains 'Latest security validation and assessment baseline note: 2026-06-12 CDT' docs/status/CURRENT_STATUS.md
require_contains 'SECURITY_VALIDATION_ASSESSMENT_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Security validation and assessment baseline' docs/security.html
require_contains 'SECURITY_VALIDATION_ASSESSMENT_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-security-validation-assessment-baseline.sh' Makefile
require_contains 'security-validation-assessment-baseline:' Makefile
require_contains 'sh ./scripts/test-security-validation-assessment-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-security-validation-assessment-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'security_validation_assessment_baseline: ok\n'

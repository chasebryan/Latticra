#!/usr/bin/env sh
set -eu

doc="docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'defensive threat model validation refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'defensive threat model validation refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/DEFENSIVE_THREAT_MODEL_CONTRACT.md
require_file docs/DEFENSIVE_THREAT_MODEL_IMPLEMENTATION_PLAN.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
require_file scripts/test-defensive-threat-model-contract.sh
require_file scripts/test-defensive-threat-model-implementation-plan.sh
require_file scripts/test-defensive-threat-model-validation.sh
require_file docs/RUNTIME_BOUNDARY_CONTRACT.md
require_file docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md
require_file docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
require_file scripts/test-runtime-boundary.sh

require_contains 'Status: defensive threat model validation refinement' "$doc"
require_contains 'Source: local follow-up slice' "$doc"
require_contains 'defensive_threat_model_contract_present=1' "$doc"
require_contains 'defensive_threat_model_implementation_plan_present=1' "$doc"
require_contains 'defensive_threat_model_validation_present=1' "$doc"
require_contains 'defensive_threat_model_validation_refinement_present=1' "$doc"
require_contains 'defensive_threat_model_contract_guard_present=1' "$doc"
require_contains 'defensive_threat_model_plan_guard_present=1' "$doc"
require_contains 'defensive_threat_model_validation_guard_present=1' "$doc"
require_contains 'defensive_threat_model_validation_refinement_guard_present=1' "$doc"
require_contains 'protected_asset_matrix_present=1' "$doc"
require_contains 'trust_boundary_matrix_present=1' "$doc"
require_contains 'assumption_matrix_present=1' "$doc"
require_contains 'abuse_case_mapping_present=1' "$doc"
require_contains 'evidence_matrix_present=1' "$doc"
require_contains 'external_standards_alignment_ledger_present=1' "$doc"
require_contains 'validation_matrix_present=1' "$doc"
require_contains 'non_goal_matrix_present=1' "$doc"
require_contains 'compatibility_expectations_present=1' "$doc"
require_contains 'current_gaps_present=1' "$doc"
require_contains 'external_source_refresh_checkpoint_present=1' "$doc"
require_contains 'external_standards_refresh_needed=1' "$doc"
require_contains 'manual_source_review_required=1' "$doc"
require_contains 'manual_source_review_completed_for_current_baseline=1' "$doc"
require_contains 'high_assurance_security_baseline_present=1' "$doc"
require_contains 'nsa_zero_trust_guideline_observed=1' "$doc"
require_contains 'nsa_cisa_memory_safe_languages_observed=1' "$doc"
require_contains 'cisa_fbi_product_security_bad_practices_observed=1' "$doc"
require_contains 'nist_high_assurance_references_observed=1' "$doc"
require_contains 'runtime_boundary_policy_expansion_next=1' "$doc"
require_contains 'abuse_case_fixture_expansion_next=1' "$doc"
require_contains 'mode=validation-refinement' "$doc"
require_contains 'implementation_behavior_changed=0' "$doc"
require_contains 'security_controls_added=0' "$doc"
require_contains 'runtime_execution_added=0' "$doc"
require_contains 'effect_execution_added=0' "$doc"
require_contains 'capability_enforcement_added=0' "$doc"
require_contains 'cryptographic_verification_added=0' "$doc"
require_contains 'signing_added=0' "$doc"
require_contains 'host_behavior_changed=0' "$doc"
require_contains 'network_behavior_changed=0' "$doc"
require_contains 'mcp_behavior_changed=0' "$doc"
require_contains 'agent_execution_added=0' "$doc"
require_contains 'model_execution_added=0' "$doc"
require_contains 'tool_execution_added=0' "$doc"
require_contains 'shell_execution_added=0' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'certification_claim_allowed=0' "$doc"
require_contains 'accreditation_claim_allowed=0' "$doc"
require_contains 'compliance_claim_allowed=0' "$doc"
require_contains 'runtime_protection_claim_allowed=0' "$doc"
require_contains 'malware_prevention_claim_allowed=0' "$doc"
require_contains 'ransomware_prevention_claim_allowed=0' "$doc"
require_contains 'sandbox_claim_allowed=0' "$doc"
require_contains 'production_protection_claim_allowed=0' "$doc"
require_contains 'production_readiness_claimed=0' "$doc"
require_contains 'external_endorsement_claimed=0' "$doc"
require_contains 'Date checked: 2026-05-26' "$doc"
require_contains 'nsa_zero_trust_guideline_observed=1' "$doc"
require_contains 'nsa_cisa_memory_safe_languages_observed=1' "$doc"
require_contains 'fbi_recent_cyber_alerts_observed=1' "$doc"
require_contains 'cisa_fbi_product_security_bad_practices_reference_verified=1' "$doc"
require_contains 'cisa_zero_trust_maturity_model_reference_verified=1' "$doc"
require_contains 'nist_sp_800_53_release_5_2_0_reference_verified=1' "$doc"
require_contains 'fips_140_3_reference_verified=1' "$doc"
require_contains 'recurring_manual_source_review_required=1' "$doc"
require_contains 'external_alignment_claim=source-tracking-only' "$doc"
require_contains 'certification_from_external_alignment=0' "$doc"
require_contains 'compliance_from_external_alignment=0' "$doc"
require_contains 'protection_from_external_alignment=0' "$doc"
require_contains 'runtime boundary source needs fuller policy expansion after threat-model validation' "$doc"
require_contains 'abuse-case mapping needs broader fixture coverage' "$doc"
require_contains 'sh scripts/test-defensive-threat-model-validation-refinement.sh' "$doc"
require_contains 'runtime boundary policy expansion after threat-model validation' "$doc"

require_contains 'defensive_threat_model_contract_present=1' README.md
require_contains 'defensive_threat_model_validation_present=1' README.md
require_contains 'defensive_threat_model_validation_refinement_present=1' README.md
require_contains 'high_assurance_security_baseline_present=1' README.md
require_contains 'docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md' README.md
require_contains 'Defensive threat model validation refinement' STATUS.md
require_contains 'Runtime boundary policy expansion after threat-model validation' STATUS.md
require_contains 'defensive_threat_model_validation_refinement_present=1' STATUS.md
require_contains 'high_assurance_security_baseline_present=1' STATUS.md
require_contains 'DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md' docs/status/README.md
require_contains 'defensive_threat_model_validation_refinement_present=1' docs/status/README.md
require_contains 'Defensive threat model validation refinement' docs/status/CURRENT_STATUS.md
require_contains 'Runtime boundary policy expansion after threat-model validation' docs/status/CURRENT_STATUS.md
require_contains 'DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md' docs/FOUNDATION_INDEX.md
require_contains 'Defensive threat model validation refinement' docs/FOUNDATION_INDEX.md
require_contains 'Runtime boundary policy expansion after threat-model validation' docs/FOUNDATION_INDEX.md
require_contains 'defensive threat model validation refinement' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Runtime boundary policy expansion after threat-model validation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Defensive threat model validation refinement' docs/project_notes/UPCOMING_WORK.md
require_contains 'Runtime boundary policy expansion after threat-model validation' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md' docs/project_notes/README.md

printf 'defensive_threat_model_validation_refinement: ok\n'

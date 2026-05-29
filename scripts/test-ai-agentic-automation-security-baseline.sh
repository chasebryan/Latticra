#!/usr/bin/env sh
set -eu

doc="docs/AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md"
status_doc="docs/status/AI_AGENTIC_AUTOMATION_SECURITY_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ai agentic automation security baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ai agentic automation security baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_file docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md
require_file docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_file docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
require_file docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file docs/MEMORY_SAFETY_ROADMAP.md
require_file docs/NADIA_OFFLINE_AI_FOUNDATION.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
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

require_contains 'Status: AI and agentic automation security baseline' "$doc"
require_contains 'Source refresh date: 2026-05-27' "$doc"
require_contains 'Authoritative AI Security Sources' "$doc"
require_contains 'NSA/CISA/FBI and partners Deploying AI Systems Securely' "$doc"
require_contains 'CISA and NCSC Guidelines for Secure AI System Development' "$doc"
require_contains 'NSA Artificial Intelligence Security Center MCP Security Design Considerations' "$doc"
require_contains 'NSA/CISA and partners Careful Adoption of Agentic AI Services' "$doc"
require_contains 'NIST AI Risk Management Framework 1.0' "$doc"
require_contains 'NIST AI RMF Generative AI Profile NIST AI 600-1' "$doc"
require_contains 'NIST AI RMF Profile on Trustworthy AI in Critical Infrastructure concept note' "$doc"
require_contains 'NIST SP 800-218 SSDF v1.1 and SP 800-218A AI SSDF Community Profile' "$doc"
require_contains 'https://www.nsa.gov/serve-from-netstorage/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3741371/nsa-publishes-guidance-for-strengthening-ai-system-security/index.html' "$doc"
require_contains 'https://www.cisa.gov/ai' "$doc"
require_contains 'https://www.cisa.gov/news-events/news/dhs-cisa-and-uk-ncsc-release-joint-guidelines-secure-ai-system-development' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4496698/nsa-releases-security-design-considerations-for-ai-driven-automation-leveraging/' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4475134/nsa-joins-the-asds-acsc-and-others-to-release-guidance-on-agentic-artificial-in/' "$doc"
require_contains 'https://www.nist.gov/itl/ai-risk-management-framework' "$doc"
require_contains 'https://www.nist.gov/publications/artificial-intelligence-risk-management-framework-generative-artificial-intelligence' "$doc"
require_contains 'https://www.nist.gov/programs-projects/concept-note-ai-rmf-profile-trustworthy-ai-critical-infrastructure' "$doc"
require_contains 'https://csrc.nist.gov/projects/ssdf/publications' "$doc"

for field in \
  'ai_agentic_automation_security_baseline_present=1' \
  'ai_agentic_automation_security_guard_present=1' \
  'nsa_deploying_ai_systems_securely_tracked=1' \
  'cisa_secure_ai_system_development_guidelines_tracked=1' \
  'nsa_mcp_ai_automation_design_guidance_tracked=1' \
  'nsa_agentic_ai_adoption_guidance_tracked=1' \
  'nist_ai_rmf_tracked=1' \
  'nist_genai_profile_tracked=1' \
  'nist_ai_rmf_critical_infrastructure_profile_tracked=1' \
  'nist_ssdf_ai_profile_tracked=1' \
  'nist_ssdf_core_tracked=1' \
  'ai_system_inventory_required=1' \
  'model_component_provenance_required=1' \
  'external_model_review_required=1' \
  'model_data_prompt_lineage_required=1' \
  'prompt_context_boundary_required=1' \
  'prompt_injection_boundary_required=1' \
  'tool_invocation_boundary_required=1' \
  'agentic_authority_boundary_required=1' \
  'human_approval_for_high_impact_required=1' \
  'sensitive_data_ai_review_required=1' \
  'ai_red_team_test_plan_required=1' \
  'ai_evaluation_monitoring_required=1' \
  'model_update_rollback_required=1' \
  'ai_logging_redaction_required=1' \
  'ai_incident_response_handoff_required=1' \
  'ai_exception_owner_required=1' \
  'ai_exception_expiration_required=1' \
  'implementation_behavior_changed=0' \
  'model_loading_added=0' \
  'inference_execution_added=0' \
  'prompt_evaluation_added=0' \
  'training_finetuning_added=0' \
  'agentic_planning_added=0' \
  'mcp_behavior_added=0' \
  'tool_invocation_added=0' \
  'autonomous_action_added=0' \
  'network_ai_service_added=0' \
  'external_model_download_added=0' \
  'ai_runtime_authority_granted=0' \
  'production_ai_claim_allowed=0' \
  'ai_security_claim_allowed=0' \
  'ai_safety_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'ai_agentic_automation_security_status_present=1' "$status_doc"

for gate in \
  'ai_system_inventory_present=1' \
  'model_component_owner_recorded=1' \
  'model_component_source_recorded=1' \
  'model_card_or_equivalent_review_recorded=1' \
  'license_and_use_restriction_review_recorded=1' \
  'training_data_or_provider_lineage_recorded=1' \
  'prompt_source_boundary_recorded=1' \
  'context_sharing_scope_recorded=1' \
  'tool_catalog_and_permissions_recorded=1' \
  'tool_invocation_policy_recorded=1' \
  'agentic_authority_policy_recorded=1' \
  'human_approval_policy_recorded=1' \
  'sensitive_data_ai_flow_review_recorded=1' \
  'prompt_injection_abuse_case_recorded=1' \
  'model_output_abuse_case_recorded=1' \
  'ai_red_team_or_adversarial_test_plan_recorded=1' \
  'ai_evaluation_monitoring_plan_recorded=1' \
  'model_update_rollback_plan_recorded=1' \
  'ai_incident_response_handoff_recorded=1' \
  'exception_owner_recorded=1' \
  'exception_expiration_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'model_loading_allowed=0' \
  'prompt_evaluation_allowed=0' \
  'inference_execution_allowed=0' \
  'training_finetuning_allowed=0' \
  'agentic_planning_allowed=0' \
  'mcp_behavior_allowed=0' \
  'tool_invocation_allowed=0' \
  'autonomous_effect_allowed=0' \
  'external_ai_service_allowed=0' \
  'model_download_allowed=0' \
  'production_ai_claim_allowed=0' \
  'ai_security_claim_allowed=0' \
  'ai_safety_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for boundary_field in \
  'latticra_ai_metadata_only=1' \
  'latticra_nadia_contract_only=1' \
  'latticra_seal_agentic_metadata_only=1' \
  'latticra_mcp_implementation_added=0' \
  'latticra_model_loading_added=0' \
  'latticra_inference_execution_added=0' \
  'latticra_prompt_evaluation_added=0' \
  'latticra_tool_invocation_added=0' \
  'latticra_agent_execution_added=0' \
  'latticra_autonomous_effect_added=0' \
  'latticra_external_ai_service_added=0' \
  'latticra_ai_runtime_authority_granted=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'Runtime and agentic automation authority must remain per-request, least-privilege, auditable, and denied unless prerequisites pass' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'data_classification_protection_baseline_present=1' docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md
require_contains 'security_logging_monitoring_baseline_present=1' docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_contains 'cyber_incident_reporting_response_baseline_present=1' docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
require_contains 'vulnerability_management_release_gate_baseline_present=1' docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_contains 'supply_chain_security_baseline_present=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'memory_safety_roadmap_present=1' docs/MEMORY_SAFETY_ROADMAP.md
require_contains 'prompt_evaluation_authority=0' docs/NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16.md
require_contains 'LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'ai_agentic_automation_security_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-ai-agentic-automation-security-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md' SECURITY.md
require_contains 'ai_agentic_automation_security_baseline_present=1' README.md
require_contains 'ai_agentic_automation_security_baseline_present=1' STATUS.md
require_contains 'AI_AGENTIC_AUTOMATION_SECURITY_BASELINE_STATUS.md' docs/status/README.md
require_contains 'ai_agentic_automation_security_baseline_present=1' docs/status/README.md
require_contains 'Latest AI and agentic automation security baseline note: 2026-05-27 CDT' docs/status/CURRENT_STATUS.md
require_contains 'AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'AI and agentic automation security baseline' docs/security.html
require_contains 'AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-ai-agentic-automation-security-baseline.sh' Makefile
require_contains 'ai-agentic-automation-security-baseline:' Makefile
require_contains 'sh ./scripts/test-ai-agentic-automation-security-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-ai-agentic-automation-security-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'ai_agentic_automation_security_baseline: ok\n'

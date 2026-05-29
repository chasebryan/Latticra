# Latticra AI and Agentic Automation Security Baseline

Status: AI and agentic automation security baseline
Source refresh date: 2026-05-27
Scope: AI system inventory, model and component provenance, external model review, prompt and context boundaries, tool invocation boundaries, agentic authority gates, adversarial testing, monitoring, incident handoff, rollback planning, human approval, sensitive-data handling, and AI non-claims before model loading, prompt evaluation, inference, training, fine-tuning, agentic planning, MCP behavior, tool execution, autonomous effects, external AI services, production AI claims, or AI security claims.

This baseline records AI and agentic automation security requirements only. It does not implement model loading, prompt evaluation, inference, training, fine-tuning, model downloads, external AI service calls, MCP behavior, agentic planning, tool invocation, autonomous actions, production AI behavior, AI safety guarantees, or runtime authority.

## Authoritative AI Security Sources

Date checked: 2026-05-27

| Source | Latticra use |
| --- | --- |
| NSA/CISA/FBI and partners Deploying AI Systems Securely | secure deployment, operation, monitoring, model/component acquisition, and resilience vocabulary for externally developed AI systems |
| CISA and NCSC Guidelines for Secure AI System Development | secure-by-design AI lifecycle, secure development, secure deployment, secure operation, and customer security outcome vocabulary |
| NSA Artificial Intelligence Security Center MCP Security Design Considerations | MCP, dynamic tool invocation, context sharing, implicit trust, serialization risk, and agentic tool-boundary vocabulary |
| NSA/CISA and partners Careful Adoption of Agentic AI Services | privilege, design, behavior, structure, accountability, governance, monitoring, human oversight, and incremental deployment vocabulary |
| NIST AI Risk Management Framework 1.0 | AI lifecycle risk management, trustworthiness, governance, mapping, measurement, and management vocabulary |
| NIST AI RMF Generative AI Profile NIST AI 600-1 | generative AI risk identification, measurement, evaluation, content provenance, data governance, and abuse-case vocabulary |
| NIST AI RMF Profile on Trustworthy AI in Critical Infrastructure concept note | high-stakes and critical-infrastructure AI requirements vocabulary for future profiles and supply-chain communication |
| NIST SP 800-218 SSDF v1.1 and SP 800-218A AI SSDF Community Profile | secure software development, AI model development, dual-use foundation model, vulnerability response, and lifecycle assurance vocabulary |

Authoritative URLs:

```text
https://www.nsa.gov/serve-from-netstorage/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3741371/nsa-publishes-guidance-for-strengthening-ai-system-security/index.html
https://www.cisa.gov/ai
https://www.cisa.gov/news-events/news/dhs-cisa-and-uk-ncsc-release-joint-guidelines-secure-ai-system-development
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4496698/nsa-releases-security-design-considerations-for-ai-driven-automation-leveraging/
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4475134/nsa-joins-the-asds-acsc-and-others-to-release-guidance-on-agentic-artificial-in/
https://www.nist.gov/itl/ai-risk-management-framework
https://www.nist.gov/publications/artificial-intelligence-risk-management-framework-generative-artificial-intelligence
https://www.nist.gov/programs-projects/concept-note-ai-rmf-profile-trustworthy-ai-critical-infrastructure
https://csrc.nist.gov/projects/ssdf/publications
```

## Current Fields

```text
ai_agentic_automation_security_baseline_present=1
ai_agentic_automation_security_guard_present=1
nsa_deploying_ai_systems_securely_tracked=1
cisa_secure_ai_system_development_guidelines_tracked=1
nsa_mcp_ai_automation_design_guidance_tracked=1
nsa_agentic_ai_adoption_guidance_tracked=1
nist_ai_rmf_tracked=1
nist_genai_profile_tracked=1
nist_ai_rmf_critical_infrastructure_profile_tracked=1
nist_ssdf_ai_profile_tracked=1
nist_ssdf_core_tracked=1
ai_system_inventory_required=1
model_component_provenance_required=1
external_model_review_required=1
model_data_prompt_lineage_required=1
prompt_context_boundary_required=1
prompt_injection_boundary_required=1
tool_invocation_boundary_required=1
agentic_authority_boundary_required=1
human_approval_for_high_impact_required=1
sensitive_data_ai_review_required=1
ai_red_team_test_plan_required=1
ai_evaluation_monitoring_required=1
model_update_rollback_required=1
ai_logging_redaction_required=1
ai_incident_response_handoff_required=1
ai_exception_owner_required=1
ai_exception_expiration_required=1
implementation_behavior_changed=0
model_loading_added=0
inference_execution_added=0
prompt_evaluation_added=0
training_finetuning_added=0
agentic_planning_added=0
mcp_behavior_added=0
tool_invocation_added=0
autonomous_action_added=0
network_ai_service_added=0
external_model_download_added=0
ai_runtime_authority_granted=0
production_ai_claim_allowed=0
ai_security_claim_allowed=0
ai_safety_claim_allowed=0
external_endorsement_claimed=0
```

## Required AI Promotion Gate

No model loading, prompt evaluation, inference, training, fine-tuning, agentic planning, MCP behavior, tool invocation, autonomous effect, external AI service, model download, AI-assisted security claim, production AI claim, or AI safety claim may be promoted until this gate is complete:

```text
ai_system_inventory_present=1
model_component_owner_recorded=1
model_component_source_recorded=1
model_card_or_equivalent_review_recorded=1
license_and_use_restriction_review_recorded=1
training_data_or_provider_lineage_recorded=1
prompt_source_boundary_recorded=1
context_sharing_scope_recorded=1
tool_catalog_and_permissions_recorded=1
tool_invocation_policy_recorded=1
agentic_authority_policy_recorded=1
human_approval_policy_recorded=1
sensitive_data_ai_flow_review_recorded=1
prompt_injection_abuse_case_recorded=1
model_output_abuse_case_recorded=1
ai_red_team_or_adversarial_test_plan_recorded=1
ai_evaluation_monitoring_plan_recorded=1
model_update_rollback_plan_recorded=1
ai_incident_response_handoff_recorded=1
exception_owner_recorded=1
exception_expiration_recorded=1
operator_visible_non_claims_recorded=1
```

Until this gate is complete:

```text
model_loading_allowed=0
prompt_evaluation_allowed=0
inference_execution_allowed=0
training_finetuning_allowed=0
agentic_planning_allowed=0
mcp_behavior_allowed=0
tool_invocation_allowed=0
autonomous_effect_allowed=0
external_ai_service_allowed=0
model_download_allowed=0
production_ai_claim_allowed=0
ai_security_claim_allowed=0
ai_safety_claim_allowed=0
```

## Latticra Boundary

Current Latticra AI-related records remain metadata-only and no-effect contract work.

```text
latticra_ai_metadata_only=1
latticra_nadia_contract_only=1
latticra_seal_agentic_metadata_only=1
latticra_mcp_implementation_added=0
latticra_model_loading_added=0
latticra_inference_execution_added=0
latticra_prompt_evaluation_added=0
latticra_tool_invocation_added=0
latticra_agent_execution_added=0
latticra_autonomous_effect_added=0
latticra_external_ai_service_added=0
latticra_ai_runtime_authority_granted=0
```

## Current Evidence

Current supporting evidence:

```text
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md
docs/SECURITY_LOGGING_MONITORING_BASELINE.md
docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
docs/MEMORY_SAFETY_ROADMAP.md
docs/NADIA_OFFLINE_AI_FOUNDATION.md
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
SECURITY.md
scripts/test-ai-agentic-automation-security-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-ai-agentic-automation-security-baseline.sh
```

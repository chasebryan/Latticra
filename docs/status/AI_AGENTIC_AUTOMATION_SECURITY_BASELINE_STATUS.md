# Latticra AI and Agentic Automation Security Baseline Status

Status: status record for AI and agentic automation security baseline
Date: 2026-05-27

## Scope

This record tracks the AI and agentic automation security baseline for AI system inventory, model and component provenance, external model review, prompt and context boundaries, tool invocation boundaries, agentic authority gates, adversarial testing, monitoring, incident handoff, rollback planning, human approval, sensitive-data handling, and AI non-claims.

It does not implement model loading, prompt evaluation, inference, training, fine-tuning, model downloads, external AI service calls, MCP behavior, agentic planning, tool invocation, autonomous actions, production AI behavior, AI safety guarantees, or runtime authority.

## Current fields

```text
ai_agentic_automation_security_baseline_present=1
ai_agentic_automation_security_status_present=1
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

## Validation

```sh
sh scripts/test-ai-agentic-automation-security-baseline.sh
```

Expected output:

```text
ai_agentic_automation_security_baseline: ok
```

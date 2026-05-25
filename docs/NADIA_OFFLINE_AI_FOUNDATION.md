# Nadia Offline AI Foundation

Status: Stage-0 foundation contract
Date: 2026-05-25
Scope: Latticra-native offline AI identity, installation surface, Console interoperability, local evidence posture, and staged development plan.

## Name

The Latticra offline AI is named **Nadia**.

Nadia is named after Nobel Peace Prize laureate Nadia Murad, whose testimony and advocacy have helped bring public attention to the enslavement and abuse of thousands of women in Iraq and Syria.

This name gives the Latticra offline AI a human-rights awareness posture: technical capability should be bound to dignity, witness, community responsibility, and careful authority.

Nadia's Latticra component identity is:

```text
public_name=Nadia
system_name=Latticra Nadia Witness Foundation
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
command_name=latticra-nadia
component_key=nadia_offline_ai
```

## Purpose

Nadia is the future offline AI companion for Latticra software development, systems engineering, and AI development workflows.

Her long-term role is to help operators:

- understand and improve Latticra source, contracts, tests, and evidence;
- reason about C, constrained C++, Rust Panel code, Lat, LIR, L-UI, Nucleus, Runtime Boundary, and Seal surfaces;
- plan bounded implementation slices before tool authority is granted;
- use local project context without requiring network access;
- learn from accepted local work through operator-reviewed productivity evidence;
- keep community-awareness principles visible while building powerful local AI tools.

## Stage-0 Foundation

Stage-0 makes Nadia visible and installable without claiming model capability.

Stage-0 establishes:

```text
nadia_stage_0_foundation_present=1
panel_install_surface_present=1
console_interop_surface_present=1
local_config_surface_present=1
local_component_marker_present=1
offline_by_default=1
network_authority=0
tool_execution_authority=0
model_runtime_present=0
model_weights_installed=0
self_modification_authority=0
production_ai_claimed=0
```

Stage-0 does not install model weights, run inference, execute tools, mutate source, train a model, use the network, or claim autonomous software-development capability.

## Awareness Principles

Nadia's development should remain aligned with the reason for her name:

```text
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1
sensationalism_allowed=0
coercive_use_allowed=0
dehumanizing_use_allowed=0
```

This does not make Stage-0 a policy engine or content-moderation system. It establishes a naming and design commitment that later AI capability must honor through explicit contracts, evidence, and operator-visible boundaries.

## Local Layout

When enabled through Latticra Panel, Nadia reserves a user-local foundation under the guarded Latticra prefix:

```text
etc/latticra/nadia.toml
share/latticra/nadia/README.md
share/latticra/nadia/context-packs/
share/latticra/nadia/model-registry/
share/latticra/nadia/productivity-ledger/
share/latticra/nadia/runtime-invocation/
share/latticra/nadia/model-load/
share/latticra/nadia/prompt-receipt/
share/latticra/nadia/prompt-materialization/
share/latticra/nadia/awareness-dialogue/
share/latticra/nadia/prompt-evaluation-handoff/
share/latticra/nadia/tokenization-boundary/
share/latticra/nadia/tokenizer-specification/
share/latticra/nadia/tokenizer-manifest/
share/latticra/components/nadia-offline-ai.installed
bin/latticra-nadia
```

These paths are placeholders for future offline capability. They are intentionally local, inspectable, and receipt-visible.

## Console Interoperability

Nadia must interoperate with the embedded Latticra Console before receiving any broader authority.

Stage-0 Console behavior is metadata-only:

```text
nadia status
```

The command reports whether the Panel configuration has selected the Nadia component and repeats the denied authority posture. It does not launch an external host process.

After user-local installation, the CLI surface is:

```text
latticra-nadia status
latticra nadia status
```

The installed shim reports Stage-0 metadata only.

## Productivity Learning

Nadia's learning loop must begin as a local productivity ledger, not as silent self-training.

Stage-0 reserves the ledger path and policy vocabulary:

```text
productivity_ledger=operator-reviewed-local
accepted_patch_memory=planned
test_outcome_memory=planned
retrieval_index_updates=planned
weight_training=0
silent_self_modification=0
```

Future stages may let Nadia learn from accepted patches, test outcomes, rejected plans, and operator notes. That learning must remain local, auditable, reversible, and separated from model-weight training unless a later contract explicitly permits it.

## Development Stages

### Stage-0: Foundation

Establish name, component identity, Panel install surface, Console status surface, local config, local directories, CLI shim, status record, and deterministic guard.

### Stage-1: Local Context Engine

Build a no-network project indexer for docs, headers, sources, tests, scripts, installer configs, and status records. Produce context packs for Latticra-specific coding tasks without running inference.

Current Stage-1 status:

```text
nadia_stage_1_local_context_engine_present=1
context_pack_command=scripts/nadia-context-pack.sh
installed_context_pack_command=latticra-nadia context-pack
local_file_read_for_indexing=operator_invoked
source_mutation_authority=0
network_authority=0
model_runtime_present=0
```

See [`NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md`](NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md).

### Stage-2: Offline Inference Runtime

Add a pluggable local runtime boundary for operator-provided models, likely GGUF-compatible first. Record model hashes, quantization, context length, hardware profile, and memory budget before use.

Current Stage-2 status:

```text
nadia_stage_2_runtime_profile_present=1
runtime_profile_command=scripts/nadia-runtime-profile.sh
installed_runtime_profile_command=latticra-nadia runtime-profile
model_file_measurement=operator_provided_optional
runtime_family=llama.cpp-compatible
model_format=gguf
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
```

See [`NADIA_RUNTIME_PROFILE_STAGE_2.md`](NADIA_RUNTIME_PROFILE_STAGE_2.md).

### Stage-3: Developer Workbench

Integrate Nadia with Latticra Console and Panel workflows for code navigation, patch planning, test selection, and evidence review. Keep source mutation behind explicit operator action.

Current Stage-3 status:

```text
nadia_stage_3_developer_workbench_present=1
prompt_plan_command=scripts/nadia-prompt-plan.sh
installed_prompt_plan_command=latticra-nadia prompt-plan
requires_context_pack=1
requires_runtime_profile=1
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
source_mutation_authority=0
```

See [`NADIA_DEVELOPER_WORKBENCH_STAGE_3.md`](NADIA_DEVELOPER_WORKBENCH_STAGE_3.md).

### Stage-4: Systems Engineering Mode

Specialize prompt-plan validation with mode labels and validator sets for C, constrained C++, Rust Panel code, Lat/LIR/L-UI, Runtime Boundary, Seal, AI infrastructure, awareness safety, and Linux/Fedora integration.

```text
nadia_stage_4_systems_engineering_mode_present=1
mode_validation_command=scripts/nadia-mode-validate.sh
installed_mode_validation_command=latticra-nadia mode-validate
requires_prompt_plan=1
mode_taxonomy_present=1
mode_allowed=1
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
source_mutation_authority=0
```

See [`NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4.md`](NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4.md).

### Stage-5: Productivity Loop

Use the local productivity ledger to improve retrieval, ranking, plan templates, test recommendations, and project-specific memory. Any model training or distillation remains a separate future contract.

```text
nadia_stage_5_productivity_loop_present=1
productivity_ledger_command=scripts/nadia-productivity-ledger.sh
installed_productivity_ledger_command=latticra-nadia productivity-ledger
requires_mode_validation=1
learning_scope=operator-reviewed-local-productivity
ledger_append_only=1
project_memory_scope=local-metadata-only
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
training_performed=0
distillation_performed=0
source_mutation_authority=0
```

See [`NADIA_PRODUCTIVITY_LOOP_STAGE_5.md`](NADIA_PRODUCTIVITY_LOOP_STAGE_5.md).

### Stage-6: Protective Safety Boundary

Make Nadia's absolute protective boundary explicit before any prompt evaluation, model runtime, retrieval, or tool authority is considered.

```text
nadia_stage_6_protective_safety_boundary_present=1
protective_safety_command=scripts/nadia-protective-safety-boundary.sh
installed_protective_safety_command=latticra-nadia protective-safety
requires_productivity_entry=1
absolute_protective_boundary=1
sexual_user_request_authority=0
sexual_content_generation=0
sexual_roleplay_authority=0
sexualized_namesake_or_survivor_content=0
sexual_request_refusal=always
user_override_authority=0
prompt_injection_override_authority=0
manipulation_resistance=required
policy_bypass_authority=0
namesake_cause_awareness=1
awareness_context=non_sensational_human_rights
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
training_performed=0
distillation_performed=0
source_mutation_authority=0
```

See [`NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6.md`](NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6.md).

### Stage-7: Guarded Tool Authority

Add a report-only tool-authority preflight after the protective-safety boundary. Stage-7 can classify a proposed tool class but cannot execute tools.

```text
nadia_stage_7_guarded_tool_authority_present=1
tool_authority_preflight_command=scripts/nadia-tool-authority-preflight.sh
installed_tool_authority_preflight_command=latticra-nadia tool-preflight
requires_protective_safety=1
tool_authority_stage=preflight-only
preflight_decision=report_only_no_execution
tool_execution_authority=0
tool_execution_performed=0
tool_selection_authority=0
shell_execution_authority=0
network_tool_authority=0
source_mutation_authority=0
destructive_action_authority=0
credential_access_authority=0
requires_operator_approval=1
requires_nucleus_gate=1
requires_runtime_boundary_gate=1
requires_seal_receipt=1
requires_protective_safety_boundary=1
authority_transition_allowed=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md`](NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md).

### Stage-8: Prompt Evaluation Contract

Define the contract required before any future prompt evaluation. Stage-8 can verify Stage-7 tool preflight evidence and write receipt fields, but it cannot materialize or evaluate prompts.

```text
nadia_stage_8_prompt_evaluation_contract_present=1
prompt_evaluation_contract_command=scripts/nadia-prompt-evaluation-contract.sh
installed_prompt_evaluation_contract_command=latticra-nadia prompt-contract
requires_tool_preflight=1
prompt_evaluation_stage=contract-only
prompt_contract_status=contract_only
prompt_materialized=0
prompt_text_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
prompt_receipt_required=1
refusal_policy_required=1
protective_safety_required=1
tool_preflight_required=1
runtime_profile_required=1
model_registry_review_required=1
operator_review_required=1
contract_promotion_allowed=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
tool_execution_authority=0
tool_execution_performed=0
model_runtime_invoked=0
inference_performed=0
source_mutation_authority=0
```

See [`NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8.md`](NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8.md).

### Stage-9: Local Model Registry Contract

Record local model-candidate metadata after prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-9 can record candidate labels, runtime/profile linkage, provenance labels, license review labels, context budget, and quantization metadata, but it cannot select, install, load, inspect, benchmark, or run a model.

```text
nadia_stage_9_local_model_registry_contract_present=1
model_registry_contract_command=scripts/nadia-local-model-registry-contract.sh
installed_model_registry_contract_command=latticra-nadia model-registry
requires_prompt_contract=1
requires_runtime_profile=1
local_model_registry_stage=contract-only
registry_contract_status=metadata_only
model_registry_authority=0
candidate_recorded=1
candidate_review_status=operator_review_required
candidate_usable_for_inference=0
candidate_selected_for_runtime=0
model_selection_authority=0
model_install_authority=0
model_download_authority=0
model_copy_authority=0
model_load_authority=0
model_weight_inspection_authority=0
registry_promotion_allowed=0
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
model_runtime_invoked=0
inference_performed=0
model_weights_installed=0
model_weights_loaded=0
model_weights_downloaded=0
tool_execution_authority=0
source_mutation_authority=0
network_authority=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9.md`](NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9.md).

### Stage-10: Inference Readiness Contract

Record inference-readiness metadata after local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-10 can verify prerequisite evidence and record a blocked readiness decision, but it cannot load model weights, invoke a runtime, generate tokens, materialize or evaluate prompts, or run inference.

```text
nadia_stage_10_inference_readiness_contract_present=1
inference_readiness_contract_command=scripts/nadia-inference-readiness-contract.sh
installed_inference_readiness_contract_command=latticra-nadia inference-readiness
requires_model_registry_contract=1
inference_readiness_stage=contract-only
inference_readiness_contract_status=contract_only
inference_readiness_authority=0
inference_ready=0
readiness_decision=blocked_contract_only
readiness_evidence_present=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_future_runtime_invocation_contract=1
readiness_promotion_allowed=0
runtime_invocation_authority=0
token_generation_authority=0
model_session_authority=0
model_selection_authority=0
model_load_authority=0
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
model_runtime_present=0
model_runtime_invoked=0
runtime_invoked=0
inference_authority=0
inference_performed=0
model_weights_loaded=0
model_weights_downloaded=0
model_weights_inspected=0
tool_execution_authority=0
source_mutation_authority=0
network_authority=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10.md`](NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10.md).

### Stage-11: Runtime Invocation Contract

Record runtime-invocation metadata after inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-11 can verify prerequisite evidence and record a blocked invocation decision, but it cannot spawn a runtime process, execute a runtime binary, create a runtime session, load model weights, generate tokens, materialize or evaluate prompts, or run inference.

```text
nadia_stage_11_runtime_invocation_contract_present=1
runtime_invocation_contract_command=scripts/nadia-runtime-invocation-contract.sh
installed_runtime_invocation_contract_command=latticra-nadia runtime-invocation
requires_inference_readiness_contract=1
runtime_invocation_stage=contract-only
runtime_invocation_contract_status=contract_only
runtime_invocation_authority=0
runtime_invocation_allowed=0
runtime_invoked=0
invocation_decision=blocked_contract_only
invocation_evidence_present=1
requires_model_registry_contract=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_future_model_load_contract=1
invocation_promotion_allowed=0
runtime_process_spawn_authority=0
runtime_binary_execution_authority=0
runtime_session_authority=0
model_session_authority=0
token_generation_authority=0
model_runtime_present=0
model_runtime_invoked=0
runtime_process_spawned=0
runtime_binary_executed=0
runtime_session_created=0
model_weights_loaded=0
model_weights_downloaded=0
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
token_generation_performed=0
inference_authority=0
inference_performed=0
tool_execution_authority=0
source_mutation_authority=0
network_authority=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11.md`](NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11.md).

### Stage-12: Model Load Contract

Record model-load metadata after runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-12 can verify prerequisite evidence and record a blocked model-load decision, but it cannot open model files, map model weights, verify weights, load weights, attach weights to a runtime, generate tokens, materialize or evaluate prompts, or run inference.

```text
nadia_stage_12_model_load_contract_present=1
model_load_contract_command=scripts/nadia-model-load-contract.sh
installed_model_load_contract_command=latticra-nadia model-load
requires_runtime_invocation_contract=1
model_load_stage=contract-only
model_load_contract_status=contract_only
model_load_authority=0
model_load_allowed=0
model_loaded=0
load_decision=blocked_contract_only
load_evidence_present=1
requires_inference_readiness_contract=1
requires_model_registry_contract=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_model_weight_measurement_contract=1
requires_future_prompt_receipt_contract=1
load_promotion_allowed=0
model_file_open_authority=0
model_weight_read_authority=0
model_weight_mapping_authority=0
model_weight_verification_authority=0
model_weight_inspection_authority=0
runtime_model_attach_authority=0
model_session_authority=0
token_generation_authority=0
model_file_opened=0
model_file_descriptor_opened=0
model_memory_map_created=0
model_weights_mapped=0
model_weights_loaded=0
model_weights_attached=0
model_weight_measurement_performed=0
model_weight_verification_performed=0
model_load_performed=0
model_runtime_invoked=0
runtime_process_spawned=0
runtime_session_created=0
token_generation_performed=0
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
inference_authority=0
inference_performed=0
tool_execution_authority=0
source_mutation_authority=0
network_authority=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_MODEL_LOAD_CONTRACT_STAGE_12.md`](NADIA_MODEL_LOAD_CONTRACT_STAGE_12.md).

### Stage-13: Prompt Receipt Contract

Record prompt-receipt metadata after model-load metadata, runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-13 can verify prerequisite evidence and record a blocked prompt-receipt decision, but it cannot receive prompt text, read prompt sources, store prompt content, hash prompt content, classify prompt content, materialize prompts, evaluate prompts, generate tokens, or run inference.

```text
nadia_stage_13_prompt_receipt_contract_present=1
prompt_receipt_contract_command=scripts/nadia-prompt-receipt-contract.sh
installed_prompt_receipt_contract_command=latticra-nadia prompt-receipt
requires_model_load_contract=1
prompt_receipt_stage=contract-only
prompt_receipt_contract_status=contract_only
prompt_receipt_authority=0
prompt_receipt_allowed=0
prompt_received=0
receipt_decision=blocked_contract_only
receipt_evidence_present=1
requires_runtime_invocation_contract=1
requires_inference_readiness_contract=1
requires_model_registry_contract=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_prompt_source_boundary=1
requires_future_prompt_materialization_contract=1
prompt_receipt_promotion_allowed=0
prompt_source_open_authority=0
prompt_source_read_authority=0
prompt_text_materialization_authority=0
prompt_content_storage_authority=0
prompt_hash_authority=0
prompt_classification_authority=0
prompt_source_opened=0
prompt_source_read=0
prompt_bytes_read=0
prompt_text_received=0
prompt_text_materialized=0
prompt_content_stored=0
prompt_hash_computed=0
prompt_classified=0
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
model_loaded=0
model_weights_loaded=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
tool_execution_authority=0
source_mutation_authority=0
network_authority=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13.md`](NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13.md).

### Stage-14: Prompt Materialization Contract

Record prompt-materialization metadata after prompt-receipt metadata, model-load metadata, runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-14 can verify prerequisite evidence and record a blocked prompt-materialization decision, but it cannot allocate prompt buffers, materialize prompt text, tokenize prompts, evaluate prompts, generate tokens, or run inference.

```text
nadia_stage_14_prompt_materialization_contract_present=1
prompt_materialization_contract_command=scripts/nadia-prompt-materialization-contract.sh
installed_prompt_materialization_contract_command=latticra-nadia prompt-materialization
requires_prompt_receipt_contract=1
prompt_materialization_stage=contract-only
prompt_materialization_contract_status=contract_only
prompt_materialization_authority=0
prompt_materialization_allowed=0
prompt_materialized=0
prompt_text_materialized=0
materialization_decision=blocked_contract_only
materialization_evidence_present=1
requires_model_load_contract=1
requires_runtime_invocation_contract=1
requires_inference_readiness_contract=1
requires_model_registry_contract=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_prompt_source_boundary=1
requires_prompt_buffer_boundary=1
requires_future_prompt_evaluation_handoff_contract=1
prompt_materialization_promotion_allowed=0
prompt_source_open_authority=0
prompt_source_read_authority=0
prompt_text_materialization_authority=0
prompt_buffer_allocation_authority=0
prompt_buffer_write_authority=0
prompt_tokenization_authority=0
prompt_source_opened=0
prompt_source_read=0
prompt_bytes_read=0
prompt_text_received=0
prompt_materialization_performed=0
prompt_buffer_allocated=0
prompt_buffer_written=0
prompt_bytes_materialized=0
prompt_tokens_created=0
prompt_tokenized=0
prompt_content_stored=0
prompt_hash_computed=0
prompt_classified=0
prompt_evaluation_authority=0
prompt_evaluated=0
model_loaded=0
model_weights_loaded=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
tool_execution_authority=0
source_mutation_authority=0
network_authority=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14.md`](NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14.md).

### Stage-15: Awareness Dialogue Contract

Record awareness-dialogue metadata after prompt-materialization metadata, prompt-receipt metadata, model-load metadata, runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-15 can define Nadia Initiative Q&A awareness scope and respectful dialogue requirements, but it cannot generate dialogue, evaluate prompts, generate tokens, run inference, or use the network.

```text
nadia_stage_15_awareness_dialogue_contract_present=1
awareness_dialogue_contract_command=scripts/nadia-awareness-dialogue-contract.sh
installed_awareness_dialogue_contract_command=latticra-nadia awareness-dialogue
future_qa_dialogue_capability_planned=1
awareness_dialogue_stage=contract-only
awareness_dialogue_contract_status=contract_only
awareness_dialogue_authority=0
awareness_dialogue_allowed=0
dialogue_generation_authority=0
dialogue_generation_allowed=0
qa_dialogue_generated=0
dialogue_scope=official-nadia-initiative-awareness-work
dialogue_format=question-and-answer
q_and_a_format_required=1
survivor_centered_dialogue_required=1
respectful_tone_required=1
source_attribution_required=1
official_source_grounding_required=1
source_snapshot_policy=operator-reviewed-offline
live_web_lookup_authority=0
topic_yazidi_genocide_awareness=1
topic_survivor_voice_and_dignity=1
topic_conflict_related_sexual_violence_awareness_non_graphic=1
topic_genocide_prevention=1
topic_justice_and_accountability=1
topic_women_peace_justice_security=1
topic_sinjar_reconstruction=1
topic_security_and_safe_return=1
topic_education_restoration=1
topic_healthcare_and_mental_health=1
topic_livelihoods_and_food_security=1
topic_wash_clean_water_sanitation_hygiene=1
topic_womens_empowerment=1
topic_legal_rights_and_reparations_awareness=1
topic_cultural_preservation_and_memorialization=1
topic_community_driven_survivor_centric_development=1
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
survivor_impersonation_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
hate_or_collective_blame_allowed=0
medical_advice_authority=0
legal_advice_authority=0
trauma_counseling_authority=0
crisis_intervention_authority=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15.md`](NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15.md).

### Stage-16: Prompt Evaluation Handoff Contract

Record prompt-evaluation handoff metadata after awareness-dialogue metadata, prompt-materialization metadata, prompt-receipt metadata, model-load metadata, runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-16 can verify awareness-dialogue evidence and package a blocked prompt-evaluation handoff, but it cannot tokenize prompts, evaluate prompts, generate dialogue, generate tokens, run inference, or use the network.

```text
nadia_stage_16_prompt_evaluation_handoff_contract_present=1
prompt_evaluation_handoff_contract_command=scripts/nadia-prompt-evaluation-handoff-contract.sh
installed_prompt_evaluation_handoff_contract_command=latticra-nadia prompt-evaluation-handoff
prompt_evaluation_handoff_contract_status=contract_only
prompt_evaluation_handoff_stage=contract-only
prompt_evaluation_handoff_authority=0
prompt_evaluation_handoff_allowed=0
prompt_evaluation_handoff_performed=0
prompt_evaluation_authority=0
prompt_evaluated=0
evaluation_handoff_decision=blocked_contract_only
evaluation_handoff_evidence_present=1
requires_awareness_dialogue_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_protective_safety_boundary=1
requires_operator_review=1
requires_official_source_snapshot=1
requires_future_tokenization_contract=1
prompt_evaluation_handoff_promotion_allowed=0
future_qa_dialogue_capability_planned=1
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0
dialogue_scope=official-nadia-initiative-awareness-work
q_and_a_format_required=1
survivor_centered_dialogue_required=1
official_source_grounding_required=1
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16.md`](NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16.md).

### Stage-17: Tokenization Boundary Contract

Record tokenization-boundary metadata after prompt-evaluation handoff metadata, awareness-dialogue metadata, prompt-materialization metadata, prompt-receipt metadata, model-load metadata, runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-17 can verify prompt-evaluation handoff evidence and package a blocked tokenization boundary, but it cannot open tokenizer files, load vocabularies, tokenize prompts, evaluate prompts, generate dialogue, generate tokens, run inference, or use the network.

```text
nadia_stage_17_tokenization_boundary_contract_present=1
tokenization_boundary_contract_command=scripts/nadia-tokenization-boundary-contract.sh
installed_tokenization_boundary_contract_command=latticra-nadia tokenization-boundary
tokenization_boundary_contract_status=contract_only
tokenization_boundary_stage=contract-only
tokenization_boundary_authority=0
tokenization_boundary_allowed=0
tokenization_boundary_performed=0
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenized=0
prompt_tokens_created=0
tokenizer_file_opened=0
tokenizer_vocab_loaded=0
prompt_evaluation_authority=0
prompt_evaluated=0
tokenization_decision=blocked_contract_only
tokenization_evidence_present=1
requires_prompt_evaluation_handoff_contract=1
requires_awareness_dialogue_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_prompt_buffer_boundary=1
requires_protective_safety_boundary=1
requires_operator_review=1
requires_official_source_snapshot=1
requires_future_tokenizer_specification_contract=1
tokenization_boundary_promotion_allowed=0
qa_dialogue_generated=0
answer_text_generated=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17.md`](NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17.md).

### Stage-18: Tokenizer Specification Contract

Record tokenizer-specification metadata after tokenization-boundary metadata, prompt-evaluation handoff metadata, awareness-dialogue metadata, prompt-materialization metadata, prompt-receipt metadata, model-load metadata, runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-18 can define future tokenizer review requirements, but it cannot load tokenizer manifests, open tokenizer files, load vocabularies, tokenize prompts, evaluate prompts, generate dialogue, generate tokens, run inference, or use the network.

```text
nadia_stage_18_tokenizer_specification_contract_present=1
tokenizer_specification_contract_command=scripts/nadia-tokenizer-specification-contract.sh
installed_tokenizer_specification_contract_command=latticra-nadia tokenizer-specification
tokenizer_specification_contract_status=contract_only
tokenizer_specification_stage=contract-only
tokenizer_specification_authority=0
tokenizer_specification_allowed=0
tokenizer_specification_performed=0
tokenizer_specification_metadata_present=1
tokenizer_family=model-compatible-tokenizer
tokenizer_format=operator-reviewed-offline-specification
tokenizer_specification_decision=blocked_contract_only
tokenizer_specification_evidence_present=1
tokenizer_source_policy=operator-reviewed-offline
tokenizer_path_recorded=0
tokenizer_manifest_loaded=0
requires_tokenization_boundary_contract=1
requires_future_tokenizer_manifest_contract=1
tokenizer_specification_promotion_allowed=0
requires_model_tokenizer_compatibility_review=1
requires_unicode_policy_review=1
requires_normalization_policy_review=1
requires_special_token_policy_review=1
requires_bos_eos_policy_review=1
requires_chat_template_policy_review=1
requires_prompt_template_boundary=1
tokenizer_file_opened=0
tokenizer_file_read=0
tokenizer_vocab_loaded=0
prompt_tokenized=0
prompt_evaluated=0
qa_dialogue_generated=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18.md`](NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18.md).

### Stage-19: Tokenizer Manifest Contract

Record tokenizer-manifest metadata after tokenizer-specification metadata, tokenization-boundary metadata, prompt-evaluation handoff metadata, awareness-dialogue metadata, prompt-materialization metadata, prompt-receipt metadata, model-load metadata, runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present. Stage-19 can define future tokenizer manifest review requirements, but it cannot load tokenizer manifests, parse tokenizer manifests, open tokenizer files, load vocabularies, tokenize prompts, evaluate prompts, generate dialogue, generate tokens, run inference, or use the network.

```text
nadia_stage_19_tokenizer_manifest_contract_present=1
tokenizer_manifest_contract_command=scripts/nadia-tokenizer-manifest-contract.sh
installed_tokenizer_manifest_contract_command=latticra-nadia tokenizer-manifest
tokenizer_manifest_contract_status=contract_only
tokenizer_manifest_stage=contract-only
tokenizer_manifest_authority=0
tokenizer_manifest_allowed=0
tokenizer_manifest_performed=0
tokenizer_manifest_metadata_present=1
tokenizer_manifest_family=operator-reviewed-tokenizer-manifest
tokenizer_manifest_format=contract-only-offline-manifest
tokenizer_manifest_decision=blocked_contract_only
tokenizer_manifest_evidence_present=1
tokenizer_manifest_source_policy=operator-reviewed-offline
tokenizer_manifest_path_recorded=0
tokenizer_manifest_schema_planned=1
requires_tokenizer_specification_contract=1
requires_tokenization_boundary_contract=1
requires_future_tokenizer_artifact_inventory_contract=1
tokenizer_manifest_promotion_allowed=0
tokenizer_manifest_open_authority=0
tokenizer_manifest_read_authority=0
tokenizer_manifest_parse_authority=0
tokenizer_manifest_load_authority=0
tokenizer_manifest_opened=0
tokenizer_manifest_read=0
tokenizer_manifest_parsed=0
tokenizer_manifest_loaded=0
tokenizer_file_opened=0
tokenizer_file_read=0
tokenizer_vocab_loaded=0
prompt_tokenized=0
prompt_evaluated=0
qa_dialogue_generated=0
sexual_request_refusal=always
manipulation_resistance=required
```

See [`NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19.md`](NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19.md).

### Stage-20: Tokenizer Artifact Inventory Contract

Only after tokenizer-manifest metadata, tokenizer-specification metadata, tokenization-boundary metadata, prompt-evaluation handoff metadata, awareness-dialogue metadata, prompt-materialization metadata, prompt-receipt metadata, model-load metadata, runtime-invocation metadata, inference-readiness metadata, local model-registry metadata, prompt-evaluation contracts, protective-safety refusal behavior, runtime-profile metadata, and tool-denial behavior are present, consider a tokenizer artifact inventory contract. The default remains no tokenizer manifest loading, no tokenizer file opening, no tokenizer vocabulary loading, no prompt tokenization, no prompt evaluation, no token generation, no inference, no tool execution, no source mutation, no network authority, and no sexual user functionality.

## Non-Claims

The current Nadia foundation is not:

- a production AI assistant;
- an autonomous coding agent;
- a sexual assistant, roleplay surface, or adult-content generator;
- a model runtime;
- a model distribution channel;
- a training system;
- a network service;
- a sandbox;
- a security product;
- a replacement for Latticra Seal, Nucleus, or Runtime Boundary.

## Promotion Gate

Before Stage-20 starts, Latticra should keep these guards passing:

```sh
sh scripts/test-nadia-offline-ai-stage-0.sh
sh scripts/test-nadia-local-context-engine-stage-1.sh
sh scripts/test-nadia-runtime-profile-stage-2.sh
sh scripts/test-nadia-developer-workbench-stage-3.sh
sh scripts/test-nadia-systems-engineering-mode-stage-4.sh
sh scripts/test-nadia-productivity-loop-stage-5.sh
sh scripts/test-nadia-protective-safety-boundary-stage-6.sh
sh scripts/test-nadia-guarded-tool-authority-stage-7.sh
sh scripts/test-nadia-prompt-evaluation-contract-stage-8.sh
sh scripts/test-nadia-local-model-registry-contract-stage-9.sh
sh scripts/test-nadia-inference-readiness-contract-stage-10.sh
sh scripts/test-nadia-runtime-invocation-contract-stage-11.sh
sh scripts/test-nadia-model-load-contract-stage-12.sh
sh scripts/test-nadia-prompt-receipt-contract-stage-13.sh
sh scripts/test-nadia-prompt-materialization-contract-stage-14.sh
sh scripts/test-nadia-awareness-dialogue-contract-stage-15.sh
sh scripts/test-nadia-prompt-evaluation-handoff-contract-stage-16.sh
sh scripts/test-nadia-tokenization-boundary-contract-stage-17.sh
sh scripts/test-nadia-tokenizer-specification-contract-stage-18.sh
sh scripts/test-nadia-tokenizer-manifest-contract-stage-19.sh
```

Before tokenizer artifact inventory starts, a separate tokenizer artifact inventory contract must exist and name tokenizer artifact inventory metadata, tokenizer-manifest denial fields, tokenizer-file denial fields, prompt-tokenization denial fields, refusal boundary inheritance, operator review gates, and non-claims.

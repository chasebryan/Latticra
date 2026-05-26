# Nadia Prompt Evaluation Input Contract Stage-28 Status

Status: implementation status record

Scope: prompt-evaluation-input metadata before prompt evaluation input creation, runtime invocation, prompt evaluation, dialogue generation, token generation, inference, or tool execution.

## Summary

Nadia Stage-28 adds a prompt-evaluation-input contract generator.

It consumes the Stage-27 context-window assembly report as prerequisite evidence and records a future review lane for prompt-evaluation input schema, context-window references, prompt-token-sequence references, safety-envelope policy, runtime-denial policy, and prompt-evaluation runtime handoff requirements. It remains contract-only: no prompt text is read, no context window is assembled, no prompt evaluation input is created, no runtime is invoked, no prompt is evaluated, and no dialogue is generated.

## Status Fields

```text
nadia_stage_28_prompt_evaluation_input_contract_present=1
nadia_prompt_evaluation_input_contract_generator_present=1
prompt_evaluation_input_contract_command=scripts/nadia-prompt-evaluation-input-contract.sh
installed_prompt_evaluation_input_contract_command=latticra-nadia prompt-evaluation-input
prompt_evaluation_input_contract_status=contract_only
prompt_evaluation_input_stage=contract-only
prompt_evaluation_input_authority=0
prompt_evaluation_input_allowed=0
prompt_evaluation_input_created=0
prompt_evaluation_input_metadata_present=1
prompt_evaluation_input_family=operator-reviewed-prompt-evaluation-input
prompt_evaluation_input_format=contract-only-offline-evaluation-input
prompt_evaluation_input_decision=blocked_contract_only
prompt_evaluation_input_evidence_present=1
prompt_evaluation_input_source_policy=operator-reviewed-offline
prompt_evaluation_input_plan_recorded=1
prompt_evaluation_input_method_planned=offline-prompt-evaluation-input-policy-review
prompt_evaluation_input_result_recorded=0
prompt_evaluation_input_runtime_invoked=0
requires_context_window_assembly_contract=1
requires_future_prompt_evaluation_runtime_handoff_contract=1
prompt_evaluation_input_promotion_allowed=0
```

## Guardrails

```text
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_loaded=0
prompt_evaluation_input_opened=0
prompt_evaluation_input_read=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_serialized=0
prompt_evaluation_input_written=0
prompt_evaluation_input_context_reference_recorded=0
prompt_evaluation_input_token_reference_recorded=0
prompt_evaluation_input_safety_envelope_recorded=0
context_window_assembled=0
context_window_serialized=0
prompt_token_sequence_recorded=0
prompt_token_ids_recorded=0
prompt_attention_mask_created=0
prompt_position_ids_created=0
prompt_text_read=0
prompt_text_received=0
prompt_text_materialized=0
prompt_tokens_created=0
prompt_token_count_recorded=0
prompt_tokenized=0
runtime_invoked=0
runtime_session_created=0
prompt_evaluated=0
qa_dialogue_generated=0
sexual_request_refusal=always
manipulation_resistance=required
```

Stage-28 inherits all Nadia protective-safety and awareness-dialogue restrictions:

```text
sexual_user_request_authority=0
sexual_content_generation=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
erotic_content_allowed=0
roleplay_allowed=0
survivor_impersonation_allowed=0
survivor_identifying_speculation_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
hate_or_collective_blame_allowed=0
sexual_request_refusal=always
manipulation_resistance=required
prompt_injection_override_authority=0
policy_bypass_authority=0
namesake_cause_awareness=1
```

## Installer and Console Surface

The Latticra Panel and installed `latticra-nadia` wrapper expose `prompt-evaluation-input` as metadata-only. The command delegates to `scripts/nadia-prompt-evaluation-input-contract.sh` after installation and writes reports under `share/latticra/nadia/prompt-evaluation-input/`.

## Next Boundary

Nadia can now produce a prompt-evaluation-input contract that packages Stage-27 context-window assembly evidence and records review requirements for a future prompt-evaluation runtime handoff contract.

Prompt evaluation, runtime invocation, token generation, and dialogue generation remain blocked until a later contract explicitly names the runtime handoff format, evaluation request shape, safety inheritance, operator review gates, and non-claims.

That later prompt-evaluation runtime handoff contract is the next boundary; Stage-28 only records the prerequisite metadata.

## Validation

```sh
sh scripts/test-nadia-prompt-evaluation-input-contract-stage-28.sh
```

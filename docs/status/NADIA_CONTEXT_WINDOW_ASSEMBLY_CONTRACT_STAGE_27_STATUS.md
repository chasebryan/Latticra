# Nadia Context Window Assembly Contract Stage-27 Status

Status: implementation status record

Scope: context-window assembly metadata before context window assembly, prompt evaluation input creation, runtime invocation, prompt evaluation, dialogue generation, token generation, inference, or tool execution.

## Summary

Nadia Stage-27 adds a context-window assembly contract generator.

It consumes the Stage-26 prompt-token-sequence report as prerequisite evidence and records a future review lane for context-window layout, token budget, truncation, ordering, attention-mask policy, position-ID policy, and prompt-evaluation-input policy. It remains contract-only: no prompt text is read, no context window is assembled, no prompt evaluation input is created, no runtime is invoked, no prompt is evaluated, and no dialogue is generated.

## Status Fields

```text
nadia_stage_27_context_window_assembly_contract_present=1
nadia_context_window_assembly_contract_generator_present=1
context_window_assembly_contract_command=scripts/nadia-context-window-assembly-contract.sh
installed_context_window_assembly_contract_command=latticra-nadia context-window-assembly
context_window_assembly_contract_status=contract_only
context_window_assembly_stage=contract-only
context_window_assembly_authority=0
context_window_assembly_allowed=0
context_window_assembly_performed=0
context_window_assembly_metadata_present=1
context_window_family=operator-reviewed-context-window-assembly
context_window_format=contract-only-offline-context-window
context_window_assembly_decision=blocked_contract_only
context_window_assembly_evidence_present=1
context_window_assembly_source_policy=operator-reviewed-offline
context_window_assembly_plan_recorded=1
context_window_assembly_method_planned=offline-context-window-policy-review
context_window_assembly_result_recorded=0
context_window_assembly_runtime_invoked=0
requires_prompt_token_sequence_contract=1
requires_future_prompt_evaluation_input_contract=1
context_window_assembly_promotion_allowed=0
```

## Guardrails

```text
context_window_assembled=0
context_window_token_budget_recorded=0
context_window_entry_count_recorded=0
context_window_truncation_applied=0
context_window_serialized=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_written=0
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

Stage-27 inherits all Nadia protective-safety and awareness-dialogue restrictions:

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

The Latticra Panel and installed `latticra-nadia` wrapper expose `context-window-assembly` as metadata-only. The command delegates to `scripts/nadia-context-window-assembly-contract.sh` after installation and writes reports under `share/latticra/nadia/context-window-assembly/`.

## Next Boundary

Nadia can now produce a context-window assembly contract that packages Stage-26 prompt-token-sequence evidence and records review requirements for a future prompt-evaluation-input contract.

Prompt-evaluation input creation remains blocked until a later contract explicitly names the evaluation input format, context-window reference shape, runtime-denial fields, safety inheritance, operator review gates, and non-claims.

That later prompt evaluation input contract is the next boundary; Stage-27 only records the prerequisite metadata.

Stage-28 now defines a prompt-evaluation-input contract that keeps prompt evaluation input creation, runtime invocation, prompt evaluation, dialogue generation, token generation, and inference blocked.

## Validation

```sh
sh scripts/test-nadia-context-window-assembly-contract-stage-27.sh
```

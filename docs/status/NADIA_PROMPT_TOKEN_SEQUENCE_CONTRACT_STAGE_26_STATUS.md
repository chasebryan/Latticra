# Nadia Prompt Token Sequence Contract Stage-26 Status

Status: implementation status record

Scope: prompt-token-sequence metadata before prompt token ID recording, token order recording, token offset recording, attention mask creation, position ID creation, context window assembly, prompt evaluation input creation, runtime invocation, dialogue generation, token generation, inference, or tool execution.

## Summary

Nadia Stage-26 adds a prompt-token-sequence contract generator.

It consumes the Stage-25 prompt-tokenization report as prerequisite evidence and records a future review lane for prompt token IDs, token order, token offsets, attention masks, position IDs, context-window policy, and prompt evaluation inputs. It remains contract-only: no prompt text is read, no prompt tokens are created, no token IDs or token order are recorded, no context window is assembled, no runtime is invoked, no prompt is evaluated, and no dialogue is generated.

## Status Fields

```text
nadia_stage_26_prompt_token_sequence_contract_present=1
nadia_prompt_token_sequence_contract_generator_present=1
prompt_token_sequence_contract_command=scripts/nadia-prompt-token-sequence-contract.sh
installed_prompt_token_sequence_contract_command=latticra-nadia prompt-token-sequence
prompt_token_sequence_contract_status=contract_only
prompt_token_sequence_stage=contract-only
prompt_token_sequence_authority=0
prompt_token_sequence_allowed=0
prompt_token_sequence_recorded=0
prompt_token_sequence_metadata_present=1
prompt_token_sequence_family=operator-reviewed-prompt-token-sequence
prompt_token_sequence_format=contract-only-offline-sequence
prompt_token_sequence_decision=blocked_contract_only
prompt_token_sequence_evidence_present=1
prompt_token_sequence_source_policy=operator-reviewed-offline
prompt_token_sequence_plan_recorded=1
prompt_token_sequence_method_planned=offline-token-sequence-policy-review
prompt_token_sequence_result_recorded=0
prompt_token_sequence_count_recorded=0
prompt_token_sequence_order_recorded=0
prompt_token_sequence_runtime_invoked=0
requires_prompt_tokenization_contract=1
requires_future_context_window_assembly_contract=1
prompt_token_sequence_promotion_allowed=0
```

## Guardrails

```text
prompt_token_ids_recorded=0
prompt_token_order_recorded=0
prompt_token_offsets_recorded=0
prompt_token_byte_offsets_recorded=0
prompt_attention_mask_created=0
prompt_position_ids_created=0
context_window_assembled=0
prompt_evaluation_input_created=0
prompt_text_read=0
prompt_text_received=0
prompt_text_materialized=0
prompt_tokens_created=0
prompt_token_count_recorded=0
prompt_token_sequence_recorded=0
prompt_tokenized=0
runtime_invoked=0
runtime_session_created=0
prompt_evaluated=0
qa_dialogue_generated=0
sexual_request_refusal=always
manipulation_resistance=required
```

Stage-26 inherits all Nadia protective-safety and awareness-dialogue restrictions:

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

The Latticra Panel and installed `latticra-nadia` wrapper expose `prompt-token-sequence` as metadata-only. The command delegates to `scripts/nadia-prompt-token-sequence-contract.sh` after installation and writes reports under `share/latticra/nadia/prompt-token-sequence/`.

## Next Boundary

Nadia can now produce a prompt-token-sequence contract that packages Stage-25 prompt-tokenization evidence and records review requirements for a future context-window assembly contract.

Stage-27 now defines a context-window assembly contract that keeps context window assembly, prompt evaluation input creation, runtime invocation, prompt evaluation, dialogue generation, token generation, and inference blocked.

Context-window assembly remains blocked until a later contract explicitly names the context window format, prompt evaluation input shape, truncation policy, safety inheritance, runtime-denial fields, operator review gates, and non-claims.

That later context window assembly contract is the next boundary; Stage-26 only records the prerequisite metadata.

## Validation

```sh
sh scripts/test-nadia-prompt-token-sequence-contract-stage-26.sh
```

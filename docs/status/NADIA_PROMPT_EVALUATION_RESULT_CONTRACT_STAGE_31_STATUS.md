# Nadia Prompt Evaluation Result Contract Stage-31 Status

Status: implementation status record

Scope: prompt-evaluation result metadata before result recording, model-output recording, runtime invocation, prompt evaluation, dialogue generation, token generation, inference, or tool execution.

## Summary

Nadia Stage-31 adds a prompt-evaluation result contract generator.

It consumes the Stage-30 prompt-evaluation invocation report as prerequisite evidence and records a future review lane for prompt-evaluation result schema, invocation references, runtime handoff references, evaluation input references, generated-text denial policy, token-generation denial policy, result-review policy, and survivor-centered safety requirements. It remains contract-only: no result record is created, no model output is recorded, no runtime is invoked, no prompt is evaluated, no token is generated, and no dialogue is generated.

## Status Fields

```text
nadia_stage_31_prompt_evaluation_result_contract_present=1
nadia_prompt_evaluation_result_contract_generator_present=1
prompt_evaluation_result_contract_command=scripts/nadia-prompt-evaluation-result-contract.sh
installed_prompt_evaluation_result_contract_command=latticra-nadia prompt-evaluation-result
prompt_evaluation_result_contract_status=contract_only
prompt_evaluation_result_stage=contract-only
prompt_evaluation_result_authority=0
prompt_evaluation_result_allowed=0
prompt_evaluation_result_recorded=0
prompt_evaluation_result_created=0
prompt_evaluation_result_performed=0
prompt_evaluation_result_metadata_present=1
prompt_evaluation_result_family=operator-reviewed-prompt-evaluation-result
prompt_evaluation_result_format=contract-only-offline-evaluation-result
prompt_evaluation_result_decision=blocked_contract_only
prompt_evaluation_result_evidence_present=1
prompt_evaluation_result_source_policy=operator-reviewed-offline
prompt_evaluation_result_plan_recorded=1
prompt_evaluation_result_method_planned=offline-prompt-evaluation-result-policy-review
prompt_evaluation_result_result_recorded=0
prompt_evaluation_result_runtime_invoked=0
requires_prompt_evaluation_invocation_contract=1
requires_future_prompt_evaluation_result_review_contract=1
prompt_evaluation_result_promotion_allowed=0
```

## Guardrails

```text
prompt_evaluation_result_recorded=0
prompt_evaluation_result_created=0
prompt_evaluation_result_loaded=0
prompt_evaluation_result_opened=0
prompt_evaluation_result_read=0
prompt_evaluation_result_validated=0
prompt_evaluation_result_serialized=0
prompt_evaluation_result_written=0
prompt_evaluation_result_record_created=0
prompt_evaluation_result_record_validated=0
prompt_evaluation_result_record_serialized=0
prompt_evaluation_result_record_written=0
prompt_evaluation_result_record_submitted=0
prompt_evaluation_result_model_output_recorded=0
prompt_evaluation_result_output_text_recorded=0
prompt_evaluation_result_score_recorded=0
prompt_evaluation_result_token_logprobs_recorded=0
prompt_evaluation_result_runtime_invoked=0
prompt_evaluation_invocation_request_created=0
prompt_evaluation_invocation_request_submitted=0
runtime_handoff_created=0
runtime_handoff_submitted=0
prompt_evaluation_request_created=0
prompt_evaluation_request_submitted=0
runtime_invocation_requested=0
runtime_invoked=0
runtime_session_created=0
prompt_evaluated=0
token_generation_performed=0
inference_performed=0
qa_dialogue_generated=0
answer_text_generated=0
sexual_request_refusal=always
manipulation_resistance=required
```

Stage-31 inherits all Nadia protective-safety and awareness-dialogue restrictions:

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

The Latticra Panel and installed `latticra-nadia` wrapper expose `prompt-evaluation-result` as metadata-only. The command delegates to `scripts/nadia-prompt-evaluation-result-contract.sh` after installation and writes reports under `share/latticra/nadia/prompt-evaluation-result/`.

## Next Boundary

Nadia can now produce a prompt-evaluation result contract that packages Stage-30 prompt-evaluation invocation evidence and records review requirements for a future prompt-evaluation result review contract.

Runtime invocation, prompt evaluation, token generation, inference, result recording, model-output recording, and dialogue generation remain blocked until a later contract explicitly names result review shape, runtime execution denial fields, safety inheritance, operator review gates, and non-claims.

That later prompt-evaluation result review contract is the next boundary; Stage-31 only records the prerequisite metadata.

## Validation

```sh
sh scripts/test-nadia-prompt-evaluation-result-contract-stage-31.sh
```

# Nadia Prompt Evaluation Invocation Contract Stage-30 Status

Status: implementation status record

Scope: prompt-evaluation invocation metadata before runtime invocation, prompt evaluation, dialogue generation, token generation, inference, or tool execution.

## Summary

Nadia Stage-30 adds a prompt-evaluation invocation contract generator.

It consumes the Stage-29 prompt-evaluation runtime handoff report as prerequisite evidence and records a future review lane for prompt-evaluation invocation schema, runtime handoff references, evaluation input references, runtime profile references, runtime-invocation contract references, model-load contract references, inference-readiness contract references, invocation-denial policy, token-generation denial policy, and prompt-evaluation result requirements. It remains contract-only: no runtime handoff is performed, no invocation request is created, no runtime is invoked, no prompt is evaluated, no token is generated, and no dialogue is generated.

## Status Fields

```text
nadia_stage_30_prompt_evaluation_invocation_contract_present=1
nadia_prompt_evaluation_invocation_contract_generator_present=1
prompt_evaluation_invocation_contract_command=scripts/nadia-prompt-evaluation-invocation-contract.sh
installed_prompt_evaluation_invocation_contract_command=latticra-nadia prompt-evaluation-invocation
prompt_evaluation_invocation_contract_status=contract_only
prompt_evaluation_invocation_stage=contract-only
prompt_evaluation_invocation_authority=0
prompt_evaluation_invocation_allowed=0
prompt_evaluation_invocation_performed=0
prompt_evaluation_invocation_metadata_present=1
prompt_evaluation_invocation_family=operator-reviewed-prompt-evaluation-invocation
prompt_evaluation_invocation_format=contract-only-offline-evaluation-invocation
prompt_evaluation_invocation_decision=blocked_contract_only
prompt_evaluation_invocation_evidence_present=1
prompt_evaluation_invocation_source_policy=operator-reviewed-offline
prompt_evaluation_invocation_plan_recorded=1
prompt_evaluation_invocation_method_planned=offline-prompt-evaluation-invocation-policy-review
prompt_evaluation_invocation_result_recorded=0
prompt_evaluation_invocation_runtime_invoked=0
requires_prompt_evaluation_runtime_handoff_contract=1
requires_future_prompt_evaluation_result_contract=1
prompt_evaluation_invocation_promotion_allowed=0
```

## Guardrails

```text
prompt_evaluation_invocation_performed=0
prompt_evaluation_invocation_created=0
prompt_evaluation_invocation_loaded=0
prompt_evaluation_invocation_opened=0
prompt_evaluation_invocation_read=0
prompt_evaluation_invocation_validated=0
prompt_evaluation_invocation_serialized=0
prompt_evaluation_invocation_written=0
prompt_evaluation_invocation_request_created=0
prompt_evaluation_invocation_request_validated=0
prompt_evaluation_invocation_request_serialized=0
prompt_evaluation_invocation_request_submitted=0
prompt_evaluation_invocation_request_scheduled=0
prompt_evaluation_invocation_request_queued=0
prompt_evaluation_invocation_runtime_selected=0
prompt_evaluation_invocation_model_selected=0
prompt_evaluation_invocation_session_created=0
prompt_evaluation_invocation_runtime_invoked=0
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
sexual_request_refusal=always
manipulation_resistance=required
```

Stage-30 inherits all Nadia protective-safety and awareness-dialogue restrictions:

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

The Latticra Panel and installed `latticra-nadia` wrapper expose `prompt-evaluation-invocation` as metadata-only. The command delegates to `scripts/nadia-prompt-evaluation-invocation-contract.sh` after installation and writes reports under `share/latticra/nadia/prompt-evaluation-invocation/`.

## Next Boundary

Nadia can now produce a prompt-evaluation invocation contract that packages Stage-29 prompt-evaluation runtime handoff evidence and records review requirements for a future prompt-evaluation result contract.

Runtime invocation, prompt evaluation, token generation, inference, and dialogue generation remain blocked until a later contract explicitly names result shape, runtime execution denial fields, safety inheritance, operator review gates, and non-claims.

That later prompt-evaluation result contract is the next boundary; Stage-30 only records the prerequisite metadata.

## Validation

```sh
sh scripts/test-nadia-prompt-evaluation-invocation-contract-stage-30.sh
```

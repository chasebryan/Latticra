# Nadia Prompt Evaluation Input Contract Stage-28

Status: Stage-28 implementation contract

Scope: prompt-evaluation-input metadata before prompt evaluation input creation, runtime invocation, prompt evaluation, dialogue generation, token generation, inference, or tool execution.

## Purpose

Stage-28 gives Nadia a prompt-evaluation-input contract after the context-window assembly contract is present.

The contract records how future reviewed prompt-evaluation input packaging must reference the Stage-27 context-window assembly contract, prompt-token-sequence boundary, prompt-tokenization boundary, tokenizer-runtime-attachment boundary, context-window policy, token-budget policy, truncation policy, ordering policy, attention-mask policy, position-ID policy, input-schema policy, safety-envelope policy, and runtime-denial policy. It preserves the absolute rule that Nadia cannot yet read prompt text, assemble context windows, create prompt evaluation inputs, invoke a runtime, evaluate prompts, generate dialogue, generate tokens, or run inference. The script only measures the Stage-27 contract report as evidence that the prerequisite metadata exists.

## Contract Fields

Stage-28 adds:

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
requires_prompt_token_sequence_contract=1
requires_prompt_tokenization_contract=1
requires_tokenizer_runtime_attachment_contract=1
requires_tokenizer_artifact_binding_contract=1
requires_tokenizer_artifact_verification_contract=1
requires_tokenizer_artifact_measurement_contract=1
requires_tokenizer_artifact_inventory_contract=1
requires_tokenizer_manifest_contract=1
requires_tokenizer_specification_contract=1
requires_tokenization_boundary_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_future_prompt_evaluation_runtime_handoff_contract=1
prompt_evaluation_input_promotion_allowed=0
```

Stage-28 does not generate dialogue, receive prompt text, read prompt sources, allocate prompt buffers, materialize prompt text, create prompt token buffers, create prompt tokens, count prompt tokens, record prompt token IDs, record prompt token order, record prompt token offsets, create attention masks, create position IDs, assemble context windows, serialize context windows, create prompt evaluation inputs, validate prompt evaluation inputs, serialize prompt evaluation inputs, write prompt evaluation inputs, open tokenizer manifests, read tokenizer manifests, parse tokenizer manifests, validate tokenizer manifests, load tokenizer manifests, resolve tokenizer artifact paths, scan artifact directories, stat tokenizer artifacts, open tokenizer artifacts, read tokenizer artifacts, hash tokenizer artifacts, bind tokenizer artifacts, attach tokenizers to a runtime, create runtime sessions, open tokenizer files, read tokenizer files, load tokenizer vocabularies, evaluate prompts, load model weights, invoke a runtime, generate tokens, run inference, execute tools, mutate source, train, distill, download, or use the network.

## Input Requirements

The prompt-evaluation-input contract names future review requirements:

```text
requires_context_window_assembly_reference=1
requires_context_window_policy_reference=1
requires_context_window_token_budget_policy=1
requires_context_window_truncation_policy=1
requires_context_window_ordering_policy=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_attention_mask_policy=1
requires_position_id_policy=1
requires_evaluation_input_schema_policy=1
requires_evaluation_input_context_reference_policy=1
requires_evaluation_input_token_sequence_reference_policy=1
requires_evaluation_input_safety_envelope_policy=1
requires_evaluation_input_runtime_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_input_creation=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1
```

## Denial Boundary

Stage-28 preserves explicit prompt-evaluation-input denial fields:

```text
prompt_evaluation_input_authority=0
prompt_evaluation_input_allowed=0
prompt_evaluation_input_open_authority=0
prompt_evaluation_input_read_authority=0
prompt_evaluation_input_write_authority=0
prompt_evaluation_input_execute_authority=0
prompt_evaluation_input_runtime_authority=0
prompt_evaluation_input_context_reference_authority=0
prompt_evaluation_input_token_sequence_reference_authority=0
prompt_evaluation_input_runtime_handoff_authority=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_loaded=0
prompt_evaluation_input_opened=0
prompt_evaluation_input_read=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_serialized=0
prompt_evaluation_input_written=0
prompt_evaluation_input_schema_validated=0
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
tokenizer_runtime_attachment_performed=0
tokenizer_attached_to_runtime=0
runtime_session_created=0
runtime_invoked=0
prompt_evaluated=0
qa_dialogue_generated=0
```

## Commands

Repository command:

```sh
sh scripts/nadia-prompt-evaluation-input-contract.sh \
  --context-window-assembly reports/nadia/context-window-assembly/latest-context-window-assembly-contract.txt \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-prompt-evaluation-input.XXXXXX")"
```

Installed command:

```sh
latticra-nadia prompt-evaluation-input
```

## Non-Claims

Stage-28 Nadia is not yet a Q&A assistant, dialogue generator, prompt evaluator, prompt reader, prompt materializer, tokenizer, tokenizer loader, tokenizer registry, tokenizer manifest loader, tokenizer manifest parser, tokenizer artifact scanner, tokenizer artifact inventory reader, tokenizer artifact hasher, tokenizer artifact measurer, tokenizer artifact verifier, tokenizer artifact binder, tokenizer runtime attachment layer, prompt tokenizer, token counter, token sequence recorder, token ID recorder, token offset recorder, context-window assembler, prompt-evaluation-input creator, prompt-evaluation runtime handoff layer, model loader, inference runtime, runtime process launcher, token generator, model selector, tool executor, shell runner, network client, source mutator, training system, distillation system, security product, sexual assistant, roleplay surface, adult-content generator, legal adviser, medical adviser, trauma counselor, crisis intervention service, or production AI assistant.

## Validation

Run:

```sh
sh scripts/test-nadia-prompt-evaluation-input-contract-stage-28.sh
```

Expected output:

```text
nadia_prompt_evaluation_input_contract_stage_28: ok
```

# Nadia Context Window Assembly Contract Stage-27

Status: Stage-27 implementation contract

Scope: context-window assembly metadata before context window assembly, prompt evaluation input creation, runtime invocation, prompt evaluation, dialogue generation, token generation, inference, or tool execution.

## Purpose

Stage-27 gives Nadia a context-window assembly contract after the prompt-token-sequence contract is present.

The contract records how future reviewed context-window assembly must reference the Stage-26 prompt-token-sequence contract, prompt-tokenization boundary, tokenizer-runtime-attachment boundary, prompt-materialization boundary, prompt-receipt boundary, context-window layout policy, token-budget policy, truncation policy, ordering policy, attention-mask policy, position-ID policy, and prompt-evaluation-input policy. It preserves the absolute rule that Nadia cannot yet read prompt text, assemble context windows, create prompt evaluation inputs, invoke a runtime, evaluate prompts, generate dialogue, generate tokens, or run inference. The script only measures the Stage-26 contract report as evidence that the prerequisite metadata exists.

## Contract Fields

Stage-27 adds:

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
requires_future_prompt_evaluation_input_contract=1
context_window_assembly_promotion_allowed=0
```

Stage-27 does not generate dialogue, receive prompt text, read prompt sources, allocate prompt buffers, materialize prompt text, create prompt token buffers, create prompt tokens, count prompt tokens, record prompt token IDs, record prompt token order, record prompt token offsets, create attention masks, create position IDs, assemble context windows, serialize context windows, create prompt evaluation inputs, open tokenizer manifests, read tokenizer manifests, parse tokenizer manifests, validate tokenizer manifests, load tokenizer manifests, resolve tokenizer artifact paths, scan artifact directories, stat tokenizer artifacts, open tokenizer artifacts, read tokenizer artifacts, hash tokenizer artifacts, bind tokenizer artifacts, attach tokenizers to a runtime, create runtime sessions, open tokenizer files, read tokenizer files, load tokenizer vocabularies, evaluate prompts, load model weights, invoke a runtime, generate tokens, run inference, execute tools, mutate source, train, distill, download, or use the network.

## Assembly Requirements

The context-window assembly contract names future review requirements:

```text
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_tokenizer_runtime_attachment_reference=1
requires_prompt_materialization_reference=1
requires_prompt_receipt_reference=1
requires_context_window_layout_policy=1
requires_context_window_token_budget_policy=1
requires_context_window_truncation_policy=1
requires_context_window_ordering_policy=1
requires_attention_mask_policy=1
requires_position_id_policy=1
requires_prompt_evaluation_input_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_context_window_assembly=1
requires_no_prompt_evaluation_input_creation=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1
```

## Denial Boundary

Stage-27 preserves explicit context-window denial fields:

```text
context_window_assembly_authority=0
context_window_assembly_allowed=0
context_window_assembly_open_authority=0
context_window_assembly_read_authority=0
context_window_assembly_write_authority=0
context_window_assembly_execute_authority=0
context_window_assembly_runtime_authority=0
context_window_assembly_prompt_evaluation_input_authority=0
context_window_assembly_context_write_authority=0
context_window_assembly_performed=0
context_window_assembly_result_recorded=0
context_window_assembly_runtime_invoked=0
context_window_loaded=0
context_window_opened=0
context_window_read=0
context_window_validated=0
context_window_assembled=0
context_window_bytes_read=0
context_window_hash_computed=0
context_window_entries_loaded=0
context_window_token_budget_recorded=0
context_window_entry_count_recorded=0
context_window_truncation_applied=0
context_window_serialized=0
context_window_file_written=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_written=0
prompt_token_sequence_recorded=0
prompt_token_ids_recorded=0
prompt_token_order_recorded=0
prompt_token_offsets_recorded=0
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
sh scripts/nadia-context-window-assembly-contract.sh \
  --prompt-token-sequence reports/nadia/prompt-token-sequence/latest-prompt-token-sequence-contract.txt \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-context-window-assembly.XXXXXX")"
```

Installed command:

```sh
latticra-nadia context-window-assembly
```

## Non-Claims

Stage-27 Nadia is not yet a Q&A assistant, dialogue generator, prompt evaluator, prompt reader, prompt materializer, tokenizer, tokenizer loader, tokenizer registry, tokenizer manifest loader, tokenizer manifest parser, tokenizer artifact scanner, tokenizer artifact inventory reader, tokenizer artifact hasher, tokenizer artifact measurer, tokenizer artifact verifier, tokenizer artifact binder, tokenizer runtime attachment layer, prompt tokenizer, token counter, token sequence recorder, token ID recorder, token offset recorder, context-window assembler, prompt-evaluation-input creator, model loader, inference runtime, runtime process launcher, token generator, model selector, tool executor, shell runner, network client, source mutator, training system, distillation system, security product, sexual assistant, roleplay surface, adult-content generator, legal adviser, medical adviser, trauma counselor, crisis intervention service, or production AI assistant.

## Validation

Run:

```sh
sh scripts/test-nadia-context-window-assembly-contract-stage-27.sh
```

Expected output:

```text
nadia_context_window_assembly_contract_stage_27: ok
```

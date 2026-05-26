# Nadia Prompt Materialization Contract Stage-14

Status: Stage-14 implementation contract
Date: 2026-05-25
Scope: prompt-materialization metadata before prompt buffer allocation, prompt text materialization, prompt tokenization, prompt evaluation, token generation, inference, or tool execution.

## Purpose

Stage-14 gives Nadia a prompt-materialization contract without materializing prompt text.

The contract consumes a Stage-13 prompt-receipt contract, verifies inherited non-executing prompt, model-load, runtime, model, tool, and protective-safety posture, and records the review fields that would be required before any later prompt-evaluation handoff contract can exist.

## Capability

Stage-14 adds:

```text
nadia_stage_14_prompt_materialization_contract_present=1
nadia_prompt_materialization_contract_generator_present=1
prompt_materialization_contract_command=scripts/nadia-prompt-materialization-contract.sh
installed_prompt_materialization_contract_command=latticra-nadia prompt-materialization
requires_prompt_receipt_contract=1
prompt_receipt_stage_required=13-prompt-receipt-contract
prompt_materialization_contract_status=contract_only
prompt_materialization_stage=contract-only
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
requires_refusal_policy_review=1
requires_prompt_source_boundary=1
requires_prompt_buffer_boundary=1
requires_runtime_boundary_gate=1
requires_nucleus_gate=1
requires_seal_receipt=1
requires_future_prompt_evaluation_handoff_contract=1
prompt_materialization_promotion_allowed=0
prompt_source_open_authority=0
prompt_source_read_authority=0
prompt_text_materialization_authority=0
prompt_buffer_allocation_authority=0
prompt_buffer_write_authority=0
prompt_content_storage_authority=0
prompt_hash_authority=0
prompt_classification_authority=0
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
model_runtime_invoked=0
runtime_process_spawned=0
runtime_session_created=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
tool_execution_authority=0
source_mutation_authority=0
network_authority=0
training_performed=0
distillation_performed=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

Stage-14 does not receive prompt text, read prompt sources, allocate a prompt buffer, materialize prompt text, tokenize prompts, store prompt content, hash prompt content, classify prompt content, evaluate prompts, load model weights, invoke a runtime, generate tokens, run inference, execute tools, mutate source, train, distill, download, or use the network.

## Inputs

The prompt-materialization contract requires:

```text
prompt_receipt=Stage-13 Nadia prompt-receipt contract
request_class=operator request classification label
```

Sexualized request classifications fail closed.

## Outputs

The contract writes:

```text
nadia-prompt-materialization-contract-<timestamp>.txt
latest-prompt-materialization-contract.txt
```

The report records:

```text
stage=14-prompt-materialization-contract
prompt_materialization_contract_status=contract_only
prompt_materialization_authority=0
prompt_materialization_allowed=0
prompt_materialized=0
prompt_text_materialized=0
materialization_decision=blocked_contract_only
prompt_buffer_allocated=0
prompt_tokenized=0
prompt_evaluated=0
token_generation_performed=0
inference_performed=0
sexual_request_refusal=always
```

## Usage

With explicit evidence input:

```sh
sh scripts/nadia-prompt-materialization-contract.sh \
  --prompt-receipt /path/to/latest-prompt-receipt-contract.txt \
  --request-class software-development \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-prompt-materialization.XXXXXX")"
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia prompt-materialization
```

## Non-Claims

Stage-14 Nadia is not a prompt materializer, prompt tokenizer, prompt receiver, prompt reader, prompt store, prompt evaluator, model loader, inference runtime, runtime process launcher, token generator, model selector, tool executor, shell runner, network client, source mutator, training system, distillation system, security product, sexual assistant, roleplay surface, adult-content generator, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-prompt-materialization-contract-stage-14.sh
```

Expected result:

```text
nadia_prompt_materialization_contract_stage_14: ok
```

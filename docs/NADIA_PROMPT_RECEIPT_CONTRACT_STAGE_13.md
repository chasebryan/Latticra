# Nadia Prompt Receipt Contract Stage-13

Status: Stage-13 implementation contract
Date: 2026-05-25
Scope: prompt-receipt metadata before prompt source opening, prompt text receipt, prompt materialization, prompt evaluation, token generation, inference, or tool execution.

## Purpose

Stage-13 gives Nadia a prompt-receipt contract without receiving prompt text.

The contract consumes a Stage-12 model-load contract, verifies inherited non-executing model-load, runtime, model, prompt, tool, and protective-safety posture, and records the review fields that would be required before any later prompt-materialization contract can exist.

## Capability

Stage-13 adds:

```text
nadia_stage_13_prompt_receipt_contract_present=1
nadia_prompt_receipt_contract_generator_present=1
prompt_receipt_contract_command=scripts/nadia-prompt-receipt-contract.sh
installed_prompt_receipt_contract_command=latticra-nadia prompt-receipt
requires_model_load_contract=1
model_load_stage_required=12-model-load-contract
prompt_receipt_contract_status=contract_only
prompt_receipt_stage=contract-only
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
requires_refusal_policy_review=1
requires_prompt_source_boundary=1
requires_runtime_boundary_gate=1
requires_nucleus_gate=1
requires_seal_receipt=1
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

Stage-13 does not receive prompt text, read prompt sources, store prompt content, hash prompt content, classify prompt content, materialize prompts, evaluate prompts, load model weights, invoke a runtime, generate tokens, run inference, execute tools, mutate source, train, distill, download, or use the network.

## Inputs

The prompt-receipt contract requires:

```text
model_load=Stage-12 Nadia model-load contract
request_class=operator request classification label
```

Sexualized request classifications fail closed.

## Outputs

The contract writes:

```text
nadia-prompt-receipt-contract-<timestamp>.txt
latest-prompt-receipt-contract.txt
```

The report records:

```text
stage=13-prompt-receipt-contract
prompt_receipt_contract_status=contract_only
prompt_receipt_authority=0
prompt_receipt_allowed=0
prompt_received=0
receipt_decision=blocked_contract_only
prompt_source_opened=0
prompt_text_received=0
prompt_text_materialized=0
prompt_evaluated=0
token_generation_performed=0
inference_performed=0
sexual_request_refusal=always
```

## Usage

With explicit evidence input:

```sh
sh scripts/nadia-prompt-receipt-contract.sh \
  --model-load /path/to/latest-model-load-contract.txt \
  --request-class software-development \
  --output /private/tmp/latticra-nadia-prompt-receipt
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia prompt-receipt
```

## Non-Claims

Stage-13 Nadia is not a prompt receiver, prompt reader, prompt store, prompt materializer, prompt evaluator, model loader, inference runtime, runtime process launcher, token generator, model selector, tool executor, shell runner, network client, source mutator, training system, distillation system, security product, sexual assistant, roleplay surface, adult-content generator, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-prompt-receipt-contract-stage-13.sh
```

Expected result:

```text
nadia_prompt_receipt_contract_stage_13: ok
```

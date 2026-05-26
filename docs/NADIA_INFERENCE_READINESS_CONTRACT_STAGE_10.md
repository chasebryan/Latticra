# Nadia Inference Readiness Contract Stage-10

Status: Stage-10 implementation contract
Date: 2026-05-25
Scope: inference-readiness metadata before runtime invocation, model loading, prompt evaluation, inference, or tool execution.

## Purpose

Stage-10 gives Nadia an inference-readiness contract without running inference.

The contract consumes a Stage-9 local model-registry contract, verifies inherited non-executing model, prompt, runtime, tool, and protective-safety posture, and records the review fields that would be required before any later runtime invocation contract can exist.

## Capability

Stage-10 adds:

```text
nadia_stage_10_inference_readiness_contract_present=1
nadia_inference_readiness_contract_generator_present=1
inference_readiness_contract_command=scripts/nadia-inference-readiness-contract.sh
installed_inference_readiness_contract_command=latticra-nadia inference-readiness
requires_model_registry_contract=1
model_registry_stage_required=9-local-model-registry-contract
inference_readiness_contract_status=contract_only
inference_readiness_stage=contract-only
inference_readiness_authority=0
inference_ready=0
readiness_decision=blocked_contract_only
readiness_evidence_present=1
requires_prompt_contract=1
requires_runtime_profile=1
requires_protective_safety_boundary=1
requires_tool_preflight=1
requires_operator_review=1
requires_model_provenance_review=1
requires_model_license_review=1
requires_refusal_policy_review=1
requires_runtime_boundary_gate=1
requires_nucleus_gate=1
requires_seal_receipt=1
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
model_weights_installed=0
model_weights_loaded=0
model_weights_downloaded=0
model_weights_inspected=0
tool_execution_authority=0
source_mutation_authority=0
network_authority=0
training_performed=0
distillation_performed=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

Stage-10 does not materialize prompts, evaluate prompts, load model weights, invoke a runtime, run inference, execute tools, mutate source, train, distill, download, or use the network.

## Inputs

The inference-readiness contract requires:

```text
model_registry=Stage-9 Nadia local model-registry contract
request_class=operator request classification label
```

Sexualized request classifications fail closed.

## Outputs

The contract writes:

```text
nadia-inference-readiness-contract-<timestamp>.txt
latest-inference-readiness-contract.txt
```

The report records:

```text
stage=10-inference-readiness-contract
inference_readiness_contract_status=contract_only
inference_readiness_authority=0
inference_ready=0
readiness_decision=blocked_contract_only
runtime_invocation_authority=0
model_runtime_invoked=0
inference_authority=0
inference_performed=0
model_weights_loaded=0
sexual_request_refusal=always
```

## Usage

With explicit evidence input:

```sh
sh scripts/nadia-inference-readiness-contract.sh \
  --model-registry /path/to/latest-model-registry-contract.txt \
  --request-class software-development \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-inference-readiness.XXXXXX")"
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia inference-readiness
```

## Non-Claims

Stage-10 Nadia is not an inference runtime, model loader, prompt evaluator, prompt materializer, model selector, tool executor, shell runner, network client, source mutator, training system, distillation system, security product, sexual assistant, roleplay surface, adult-content generator, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-inference-readiness-contract-stage-10.sh
```

Expected result:

```text
nadia_inference_readiness_contract_stage_10: ok
```

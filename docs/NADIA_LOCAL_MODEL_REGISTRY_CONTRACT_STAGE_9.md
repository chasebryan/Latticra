# Nadia Local Model Registry Contract Stage-9

Status: Stage-9 implementation contract
Date: 2026-05-25
Scope: local model-registry metadata before model selection, model installation, prompt evaluation, inference, or tool execution.

## Purpose

Stage-9 gives Nadia a local model-registry contract without selecting or running a model.

The contract consumes a Stage-8 prompt-evaluation contract and a Stage-2 runtime profile, verifies the inherited non-executing safety posture, and records a local model candidate as metadata for later operator review.

## Capability

Stage-9 adds:

```text
nadia_stage_9_local_model_registry_contract_present=1
nadia_model_registry_contract_generator_present=1
model_registry_contract_command=scripts/nadia-local-model-registry-contract.sh
installed_model_registry_contract_command=latticra-nadia model-registry
requires_prompt_contract=1
prompt_contract_stage_required=8-prompt-evaluation-contract
requires_runtime_profile=1
runtime_profile_stage_required=2-runtime-profile-boundary
registry_contract_status=metadata_only
local_model_registry_stage=contract-only
model_registry_authority=0
candidate_recorded=1
candidate_review_status=operator_review_required
candidate_usable_for_inference=0
candidate_selected_for_runtime=0
model_selection_authority=0
model_install_authority=0
model_download_authority=0
model_copy_authority=0
model_load_authority=0
model_benchmark_authority=0
model_weight_inspection_authority=0
registry_promotion_allowed=0
prompt_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
model_runtime_present=0
model_runtime_invoked=0
inference_performed=0
model_weights_installed=0
model_weights_loaded=0
model_weights_copied=0
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

Stage-9 does not download, install, copy, load, inspect, benchmark, or execute model weights. It does not materialize prompts, evaluate prompts, run inference, execute tools, mutate source, train, distill, or use the network.

## Inputs

The local model-registry contract requires:

```text
prompt_contract=Stage-8 Nadia prompt-evaluation contract
runtime_profile=Stage-2 Nadia runtime profile
model_id=operator-provided local candidate label
model_family=operator-provided family label
model_format=operator/runtime profile format label
quantization=operator-provided quantization label
source=operator-provided local provenance label
license=operator review label
```

Sexualized candidate labels fail closed.

## Outputs

The contract writes:

```text
nadia-model-registry-contract-<timestamp>.txt
latest-model-registry-contract.txt
```

The report records:

```text
stage=9-local-model-registry-contract
registry_contract_status=metadata_only
local_model_registry_stage=contract-only
model_registry_authority=0
candidate_review_status=operator_review_required
candidate_usable_for_inference=0
model_selection_authority=0
model_install_authority=0
model_runtime_invoked=0
inference_performed=0
model_weights_installed=0
sexual_request_refusal=always
```

## Usage

With explicit evidence inputs:

```sh
sh scripts/nadia-local-model-registry-contract.sh \
  --prompt-contract /path/to/latest-prompt-contract.txt \
  --runtime-profile /path/to/latest-runtime-profile.txt \
  --model-id local-coding-assistant-candidate \
  --quantization q4_k_m \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-model-registry.XXXXXX")"
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia model-registry
```

## Non-Claims

Stage-9 Nadia is not a model selector, inference runtime, model installer, model distributor, model downloader, weight inspector, benchmark runner, prompt evaluator, tool executor, shell runner, network client, source mutator, training system, distillation system, security product, sexual assistant, roleplay surface, adult-content generator, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-local-model-registry-contract-stage-9.sh
```

Expected result:

```text
nadia_local_model_registry_contract_stage_9: ok
```

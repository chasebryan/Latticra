# Nadia Runtime Profile Stage-2

Status: Stage-2 implementation contract
Date: 2026-05-25
Scope: offline runtime and model-profile metadata before inference.

## Purpose

Stage-2 gives Nadia a local runtime-profile boundary before any model is run.

The runtime-profile boundary records operator-selected runtime settings and optional operator-provided model-file measurements. It creates evidence that a future inference run can inspect before prompt evaluation, while keeping execution denied.

## Capability

Stage-2 adds:

```text
nadia_stage_2_runtime_profile_present=1
nadia_runtime_profile_generator_present=1
runtime_profile_command=scripts/nadia-runtime-profile.sh
installed_runtime_profile_command=latticra-nadia runtime-profile
model_file_measurement=operator_provided_optional
runtime_family=llama.cpp-compatible
model_format=gguf
network_authority=0
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
model_weights_installed=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0
```

This stage can measure a local model file when the operator provides a path. It does not download, install, copy, load, mmap, execute, or evaluate model weights.

## Profile Fields

The runtime-profile generator records:

```text
runtime_family
runtime_binary
model_format
model_file
model_file_present
model_file_bytes
model_file_measurement
context_window_tokens
memory_budget_mib
thread_policy
gpu_policy
```

The default runtime family is `llama.cpp-compatible` because GGUF-oriented local runtimes are a practical first target for offline development, but Stage-2 does not vendor or execute llama.cpp.

## Usage

Without a model file:

```sh
sh scripts/nadia-runtime-profile.sh --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-runtime.XXXXXX")"
```

With an operator-provided local model file:

```sh
sh scripts/nadia-runtime-profile.sh \
  --model /path/to/model.gguf \
  --context-tokens 8192 \
  --memory-mib 16384 \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-runtime.XXXXXX")"
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia runtime-profile
```

## Non-Claims

Stage-2 Nadia is not an inference runtime, model installer, model distributor, prompt evaluator, autonomous coding agent, embedding service, training system, source mutator, network retriever, security product, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-runtime-profile-stage-2.sh
```

Expected result:

```text
nadia_runtime_profile_stage_2: ok
```

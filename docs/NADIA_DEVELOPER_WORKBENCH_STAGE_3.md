# Nadia Developer Workbench Stage-3

Status: Stage-3 implementation contract
Date: 2026-05-25
Scope: prompt-plan generation from local context-pack and runtime-profile evidence.

## Purpose

Stage-3 gives Nadia a developer-workbench planning surface before prompt evaluation exists.

The workbench combines Stage-1 context-pack evidence and Stage-2 runtime-profile evidence into an auditable prompt plan. The plan is designed for future offline inference, but the current stage stops before prompt execution.

## Capability

Stage-3 adds:

```text
nadia_stage_3_developer_workbench_present=1
nadia_prompt_plan_generator_present=1
prompt_plan_command=scripts/nadia-prompt-plan.sh
installed_prompt_plan_command=latticra-nadia prompt-plan
requires_context_pack=1
requires_runtime_profile=1
context_pack_measured=1
runtime_profile_measured=1
network_authority=0
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0
```

Stage-3 does not summarize with AI, call an inference runtime, evaluate a prompt, mutate source, execute tools, or use the network.

## Inputs

The prompt-plan generator requires:

```text
context_pack=Stage-1 Nadia local context pack
runtime_profile=Stage-2 Nadia runtime profile
task=operator-provided task label
```

The default task label is `latticra-development-planning`.

## Outputs

The prompt-plan generator writes:

```text
nadia-prompt-plan-<timestamp>.txt
latest-prompt-plan.txt
```

The prompt plan records:

```text
stage=3-developer-workbench-planning
context_pack_measurement=<local measurement>
runtime_profile_measurement=<local measurement>
task=<operator task label>
prompt_evaluated=0
inference_performed=0
source_mutation_authority=0
```

## Usage

With explicit evidence files:

```sh
sh scripts/nadia-prompt-plan.sh \
  --context-pack /path/to/latest-context-pack.txt \
  --runtime-profile /path/to/latest-runtime-profile.txt \
  --task "runtime boundary refactor planning" \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-plans.XXXXXX")"
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia prompt-plan
```

## Non-Claims

Stage-3 Nadia is not an inference runtime, prompt evaluator, code generator, autonomous coding agent, source mutator, training system, network retriever, security product, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-developer-workbench-stage-3.sh
```

Expected result:

```text
nadia_developer_workbench_stage_3: ok
```

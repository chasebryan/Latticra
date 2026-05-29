# Nadia Systems Engineering Mode Stage-4

Status: Stage-4 implementation contract
Date: 2026-05-25
Scope: systems-engineering mode taxonomy and prompt-plan validation before prompt evaluation.

## Purpose

Stage-4 gives Nadia a mode taxonomy for software-development work before any prompt evaluation exists.

The mode validator reads a Stage-3 prompt plan, checks that it is still a planning artifact, and records which systems-engineering mode and validator set should govern the future prompt surface.

## Capability

Stage-4 adds:

```text
nadia_stage_4_systems_engineering_mode_present=1
nadia_mode_validation_generator_present=1
mode_validation_command=scripts/nadia-mode-validate.sh
installed_mode_validation_command=latticra-nadia mode-validate
requires_prompt_plan=1
prompt_plan_stage_required=3-developer-workbench-planning
mode_taxonomy_present=1
mode_allowed=1
network_authority=0
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0
```

Stage-4 does not summarize with AI, call an inference runtime, evaluate a prompt, mutate source, execute tools, or use the network.

## Modes

The initial mode taxonomy is:

```text
systems-engineering
ai-development
c-substrate
cpp-authority
rust-panel
lat-lir-l-ui
seal-boundary
runtime-boundary
fedora-validation
awareness-safety
```

Unknown modes fail closed.

## Inputs

The validator requires:

```text
prompt_plan=Stage-3 Nadia prompt plan
mode=operator-selected systems-engineering mode label
```

The default mode is `systems-engineering`.

## Outputs

The mode validator writes:

```text
nadia-mode-validation-<timestamp>.txt
latest-mode-validation.txt
```

The validation report records:

```text
stage=4-systems-engineering-mode-validation
mode=<operator mode>
prompt_plan_stage=3-developer-workbench-planning
mode_allowed=1
validator_set=<mode validator set>
prompt_evaluated=0
inference_performed=0
source_mutation_authority=0
```

## Usage

With an explicit prompt plan:

```sh
sh scripts/nadia-mode-validate.sh \
  --prompt-plan /path/to/latest-prompt-plan.txt \
  --mode runtime-boundary \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-mode.XXXXXX")"
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia mode-validate
```

## Non-Claims

Stage-4 Nadia is not an inference runtime, prompt evaluator, code generator, autonomous coding agent, source mutator, training system, network retriever, security product, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-systems-engineering-mode-stage-4.sh
```

Expected result:

```text
nadia_systems_engineering_mode_stage_4: ok
```

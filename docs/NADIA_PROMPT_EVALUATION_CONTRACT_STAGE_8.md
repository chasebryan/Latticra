# Nadia Prompt Evaluation Contract Stage-8

Status: Stage-8 implementation contract
Date: 2026-05-25
Scope: prompt-evaluation contract before prompt materialization, prompt evaluation, inference, or tool execution.

## Purpose

Stage-8 gives Nadia a prompt-evaluation contract without evaluating prompts.

The contract consumes a Stage-7 guarded tool-authority preflight, verifies report-only tool posture and protective-safety restrictions, and records the receipt fields that would be required before any future prompt evaluation path can exist.

## Capability

Stage-8 adds:

```text
nadia_stage_8_prompt_evaluation_contract_present=1
nadia_prompt_evaluation_contract_generator_present=1
prompt_evaluation_contract_command=scripts/nadia-prompt-evaluation-contract.sh
installed_prompt_evaluation_contract_command=latticra-nadia prompt-contract
requires_tool_preflight=1
tool_preflight_stage_required=7-guarded-tool-authority-preflight
prompt_evaluation_stage=contract-only
prompt_contract_status=contract_only
prompt_materialized=0
prompt_text_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
prompt_receipt_required=1
refusal_policy_required=1
protective_safety_required=1
tool_preflight_required=1
runtime_profile_required=1
model_registry_review_required=1
operator_review_required=1
contract_promotion_allowed=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
tool_execution_authority=0
tool_execution_performed=0
source_mutation_authority=0
model_runtime_invoked=0
inference_performed=0
network_authority=0
training_performed=0
distillation_performed=0
```

Stage-8 does not materialize prompts, evaluate prompts, call an inference runtime, execute tools, mutate source, train, distill, or use the network.

## Inputs

The prompt-evaluation contract requires:

```text
tool_preflight=Stage-7 Nadia guarded tool-authority preflight
request_class=operator request classification label
```

Sexualized request classifications fail closed.

## Outputs

The contract writes:

```text
nadia-prompt-contract-<timestamp>.txt
latest-prompt-contract.txt
```

The report records:

```text
stage=8-prompt-evaluation-contract
prompt_evaluation_stage=contract-only
prompt_evaluation_authority=0
prompt_materialized=0
prompt_evaluated=0
model_runtime_invoked=0
inference_performed=0
tool_execution_authority=0
sexual_request_refusal=always
```

## Usage

With an explicit tool preflight:

```sh
sh scripts/nadia-prompt-evaluation-contract.sh \
  --tool-preflight /path/to/latest-tool-preflight.txt \
  --request-class software-development \
  --output "$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-prompt-contracts.XXXXXX")"
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia prompt-contract
```

## Non-Claims

Stage-8 Nadia is not a prompt evaluator, inference runtime, tool executor, shell runner, network client, source mutator, credential reader, sexual assistant, roleplay surface, adult-content generator, training system, distillation system, security product, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-prompt-evaluation-contract-stage-8.sh
```

Expected result:

```text
nadia_prompt_evaluation_contract_stage_8: ok
```

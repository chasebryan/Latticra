# Nadia Guarded Tool Authority Stage-7

Status: Stage-7 implementation contract
Date: 2026-05-25
Scope: report-only tool-authority preflight after protective-safety validation.

## Purpose

Stage-7 gives Nadia a tool-authority preflight without granting tool execution.

The preflight consumes a Stage-6 protective-safety report, verifies the non-sexual-use and anti-manipulation boundary, and records whether a proposed tool class is inside a report-only planning boundary. It does not run the tool.

## Capability

Stage-7 adds:

```text
nadia_stage_7_guarded_tool_authority_present=1
nadia_tool_authority_preflight_present=1
tool_authority_preflight_command=scripts/nadia-tool-authority-preflight.sh
installed_tool_authority_preflight_command=latticra-nadia tool-preflight
requires_protective_safety=1
protective_safety_stage_required=6-protective-safety-boundary
tool_authority_stage=preflight-only
preflight_decision=report_only_no_execution
tool_execution_authority=0
tool_execution_performed=0
tool_selection_authority=0
shell_execution_authority=0
network_tool_authority=0
source_mutation_authority=0
destructive_action_authority=0
credential_access_authority=0
requires_operator_approval=1
requires_nucleus_gate=1
requires_runtime_boundary_gate=1
requires_seal_receipt=1
requires_protective_safety_boundary=1
authority_transition_allowed=0
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
```

Stage-7 does not execute tools, evaluate prompts, call an inference runtime, mutate source, train, distill, or use the network.

## Inputs

The tool-authority preflight requires:

```text
protective_safety=Stage-6 Nadia protective-safety report
tool_class=operator-proposed tool class label
action=operator-reviewed action label
```

Initial report-only tool classes are:

```text
metadata-read
report-only
test-recommendation
documentation-plan
local-evidence-review
```

Network, shell, destructive, source-mutation, credential, and secret-bearing classes fail closed.

## Outputs

The preflight writes:

```text
nadia-tool-preflight-<timestamp>.txt
latest-tool-preflight.txt
```

The report records:

```text
stage=7-guarded-tool-authority-preflight
preflight_decision=report_only_no_execution
tool_execution_authority=0
tool_execution_performed=0
requires_protective_safety_boundary=1
authority_transition_allowed=0
```

## Usage

With an explicit protective-safety report:

```sh
sh scripts/nadia-tool-authority-preflight.sh \
  --protective-safety /path/to/latest-protective-safety.txt \
  --tool-class local-evidence-review \
  --action "review generated receipts" \
  --output /private/tmp/latticra-nadia-tools
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia tool-preflight
```

## Non-Claims

Stage-7 Nadia is not a tool executor, shell runner, network client, source mutator, credential reader, inference runtime, prompt evaluator, sexual assistant, roleplay surface, adult-content generator, training system, distillation system, security product, or production AI assistant.

## Validation

```sh
sh scripts/test-nadia-guarded-tool-authority-stage-7.sh
```

Expected result:

```text
nadia_guarded_tool_authority_stage_7: ok
```

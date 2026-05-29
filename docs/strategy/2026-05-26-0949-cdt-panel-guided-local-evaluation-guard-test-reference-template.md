# Latticra Panel-Guided Local Evaluation Guard/Test Reference Template

Status: draft guard/test reference template
Created: 2026-05-26 09:49 CDT
Decision: reference template only
Promotion decision: no product-readiness promotion recommended
Scope: guard or test reference requirements for future Panel-guided local evaluation evidence.

## Purpose

This template defines how a future guard, test, workflow harness, or manual transcript should be referenced for Panel-guided local evaluation evidence.

It does not implement a guard, run a test, validate a workflow, capture evidence, or change project posture.

## Source review

This template follows:

```text
docs/strategy/2026-05-26-0119-cdt-panel-guided-local-evaluation-estimate-impact-review-template.md
```

The target workflow remains:

```text
Evaluate Latticra locally through Latticra Panel without granting runtime authority.
```

## Reference header

```text
reference name:
created:
reviewer:
reference status: missing|planned|present|ran_passed|ran_failed|blocked
guard or test path:
guard or test type: shell|unit|integration|manual-transcript|workflow-harness|other
workflow evidence bundle:
acceptance checklist:
repository commit:
```

## Required reference outcome

Use one outcome:

```text
no_guard_or_test_reference
guard_or_test_reference_planned
guard_or_test_reference_present_not_run
guard_or_test_reference_ran_passed
guard_or_test_reference_ran_failed
guard_or_test_reference_blocked
```

This template result:

```text
guard_or_test_reference_present=0
guard_or_test_ran=0
guard_or_test_passed=0
workflow_validated=0
estimate_change_recommended=0
reason=this file defines the future reference shape only
```

## Required reference fields

```text
guard_or_test_name:
guard_or_test_path:
guard_or_test_owner:
guard_or_test_scope:
guard_or_test_inputs:
guard_or_test_outputs:
guard_or_test_result:
guard_or_test_timestamp:
guard_or_test_environment:
guard_or_test_log:
```

If any required field is missing, the reference is incomplete.

## Required coverage claims

A future guard or test reference must say whether it covers:

```text
status_and_non_claim_entry=0|1
platform_prerequisite_capture=0|1
panel_launch_capture=0|1
dry_run_first_capture=0|1
plan_capture=0|1
dry_run_validation_capture=0|1
receipt_log_console_capture=0|1
reset_or_uninstall_capture=0|1
failure_state_capture=0|1
limitations_and_support_capture=0|1
review_gate_capture=0|1
```

Coverage must be explicit. Do not infer coverage from a broad test name.

## Required preservation assertions

The guard or test reference must preserve:

```text
runtime_authority_granted=0
effect_execution_performed=0
network_authority_granted=0
root_authority_required_by_default=0
hidden_mutation_detected=0
product_readiness_promotion=0
security_boundary_claim=0
installer_readiness_claim=0
```

If any assertion cannot be checked, record it as `unchecked`, not `passed`.

## Allowed reference types

Allowed reference types:

```text
existing guard script
new planned guard script
manual transcript review
workflow harness
focused integration check
documentation consistency check
status/index consistency check
```

Allowed only as planning references until they exist and are run:

```text
planned guard
planned transcript
planned workflow harness
```

## Blocked reference types

Blocked for this workflow unless a separate contract exists:

```text
root-requiring test
network-requiring test
runtime-authority test
effect-execution test
host-mutation test
production installer test
security hardening test
malware-prevention test
ransomware-prevention test
platform package approval test
```

If a blocked reference type is needed, this workflow must be superseded by a separate capability-promotion packet.

## Minimum pass evidence

A future passing guard or test reference must provide:

```text
command or transcript id:
exit status or review result:
captured output path:
reviewed evidence bundle:
checked preservation assertions:
failure-state coverage result:
non-claim review link:
public-entrypoint review link:
estimate-impact review link:
```

Do not mark `guard_or_test_reference_ran_passed` without captured output or transcript evidence.

## Failure handling

If the guard or test fails, record:

```text
failure label:
failed phase:
failed assertion:
output path:
remediation note:
workflow blocked=1
estimate_change_recommended=0
public_entrypoint_change_recommended=0
```

Failure must not be reframed as product-readiness evidence.

## Manual transcript reference rule

Manual transcript evidence may be referenced only if it includes:

```text
operator:
date:
platform:
commands or UI steps:
observed outputs:
authority labels:
failure or success labels:
reset or cleanup notes:
reviewer signature or note:
```

Manual transcript evidence must still pass non-claim, public-entrypoint, and estimate-impact review before it affects posture.

## Review gate output

```text
guard_or_test_reference_present=0|1
guard_or_test_reference_complete=0|1
guard_or_test_ran=0|1
guard_or_test_passed=0|1
coverage_complete=0|1
preservation_assertions_complete=0|1
blocked_reference_type_detected=0|1
workflow_blocked=0|1
estimate_change_recommended=0|1
public_entrypoint_change_recommended=0|1
reference_outcome:
```

This template output:

```text
guard_or_test_reference_present=0
guard_or_test_reference_complete=0
guard_or_test_ran=0
guard_or_test_passed=0
coverage_complete=0
preservation_assertions_complete=0
blocked_reference_type_detected=0
workflow_blocked=0
estimate_change_recommended=0
public_entrypoint_change_recommended=0
reference_outcome=not_performed
```

## Non-claims

This template does not implement a guard, run a test, validate workflow evidence, capture transcripts, provide product readiness, provide Panel readiness, provide installer readiness, grant runtime authority, execute effects, enforce capabilities, provide cryptographic authority, provide signing authority, perform host behavior, perform network behavior, execute models, execute tools, execute shell behavior, harden security, prevent malware, prevent ransomware, provide sandboxing, provide operating-system behavior, or provide production support.

It records a guard/test reference form only.

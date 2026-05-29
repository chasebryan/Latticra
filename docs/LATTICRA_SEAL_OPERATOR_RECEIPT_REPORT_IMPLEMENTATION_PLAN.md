# Latticra Seal Operator Receipt Report Implementation Plan

Status: implementation planning contract fulfilled by the no-effect Latticra Seal operator receipt report implementation
Scope: implementation plan record after the Latticra Seal operator receipt report contract. This document does not itself write receipt files, create artifacts, execute tools, perform runtime behavior, grant runtime authority, enforce capabilities, perform effects, verify signatures, parse public keys, load key material, handle private keys, query trust stores, use networks, read host files beyond future caller-provided metadata, mutate host files, implement MCP behavior, control AI agents, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This plan defined the exact implementation shape for a no-effect Seal operator receipt report.

The implementation combines existing report-only Seal metadata into one deterministic operator-facing receipt record while preserving denial, non-execution, and zero runtime authority.

## Required contract

The implementation plan depends on:

```text
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_CONTRACT.md
scripts/test-latticra-seal-operator-receipt-report-contract.sh
```

The contract must remain merged and guarded before implementation code is added.

## Implemented files

The implementation slice added:

```text
include/latticra/seal_operator_receipt_report.h
src/seal_operator_receipt_report.c
tests/seal_operator_receipt_report_invariants.c
scripts/test-latticra-seal-operator-receipt-report.sh
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
```

A later report-surface slice may add:

```text
tests/seal_operator_receipt_report_surface.c
scripts/latticra-seal-operator-receipt-report.sh
scripts/test-latticra-seal-operator-receipt-report-surface.sh
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md
docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md
```

## Header API plan

The header defines:

```text
LATTICRA_SEAL_OPERATOR_RECEIPT_PROFILE_MAX
LATTICRA_SEAL_OPERATOR_RECEIPT_STATE_MAX
LATTICRA_SEAL_OPERATOR_RECEIPT_REASON_MAX
LATTICRA_SEAL_OPERATOR_RECEIPT_CAPABILITY_MAX
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MAX
latticra_seal_operator_receipt_report_error_t
latticra_seal_operator_receipt_report_sources_t
latticra_seal_operator_receipt_report_t
latticra_seal_operator_receipt_report_error_label
latticra_seal_operator_receipt_report_from_sources
latticra_seal_operator_receipt_report_is_report_only
latticra_seal_operator_receipt_report_render
```

## Error model

The error enum includes:

```text
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_INVALID_INPUT
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_CAPABILITY_METADATA
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_POLICY_DECISION
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_REQUEST_FRESHNESS
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_SIGNED_REQUEST
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MISSING_RUNTIME_DRY_RUN
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_NON_REPORT_ONLY_SOURCE
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SOURCE_WOULD_ALLOW_EFFECT
LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_BUFFER_TOO_SMALL
```

## Source binding record

The source binding record includes:

```text
source_capability_metadata_present
source_policy_decision_present
source_request_freshness_present
source_signed_request_present
source_runtime_dry_run_present
source_denial_reason_present
source_capability_metadata_report_only
source_policy_decision_report_only
source_request_freshness_report_only
source_signed_request_report_only
source_runtime_dry_run_report_only
```

## Receipt record fields

The receipt record includes:

```text
operator_receipt_profile
receipt_mode
receipt_status
source_capability_metadata_present
source_policy_decision_present
source_request_freshness_present
source_signed_request_present
source_runtime_dry_run_present
source_denial_reason_present
capability_name
capability_known
capability_candidate
policy_decision_state
request_freshness_state
signed_request_state
runtime_dry_run_state
blocked_reason
default_action_deny
would_allow
would_deny
would_require_operator_review
would_execute_tool
would_read_host
would_write_host
would_use_network
would_grant_runtime_authority
receipt_complete
receipt_invalid
report_only
runtime_authority_granted
effect_performed
host_read_performed
host_write_performed
network_performed
error
```

## Initial constants

The implementation emits for a complete denied receipt:

```text
operator_receipt_profile=latticra-seal-operator-receipt-report/0.1
receipt_mode=report-only
receipt_status=denied-report-only
source_capability_metadata_present=1
source_policy_decision_present=1
source_request_freshness_present=1
source_signed_request_present=1
source_runtime_dry_run_present=1
source_denial_reason_present=1
capability_name=seal.capability.report
capability_known=1
capability_candidate=1
policy_decision_state=report-only
request_freshness_state=report-only
signed_request_state=report-only
runtime_dry_run_state=report-only
blocked_reason=known-capability-candidate-still-denied
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
would_grant_runtime_authority=0
receipt_complete=1
receipt_invalid=0
report_only=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

The implementation emits for missing or invalid source metadata:

```text
receipt_status=invalid-source-denied
receipt_complete=0
receipt_invalid=1
default_action_deny=1
would_allow=0
would_deny=1
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
would_grant_runtime_authority=0
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Function behavior

The builder:

```text
accept report-only capability metadata input
accept report-only policy decision input
accept report-only request freshness input
accept report-only signed request input
accept report-only runtime dry-run input
reject null output
reject missing source metadata
reject non-report-only source metadata
reject source metadata that would allow an effect
copy descriptive capability and decision fields only
copy no authority from upstream inputs
render deterministic metadata only
```

## Required report format

The report should begin with:

```text
LATTICRA SEAL OPERATOR RECEIPT REPORT
```

It should render all fields as stable `key=value` lines.

Required report fields:

```text
operator_receipt_profile=latticra-seal-operator-receipt-report/0.1
receipt_mode=report-only
receipt_status=denied-report-only
source_capability_metadata_present=1
source_policy_decision_present=1
source_request_freshness_present=1
source_signed_request_present=1
source_runtime_dry_run_present=1
source_denial_reason_present=1
capability_name=seal.capability.report
capability_known=1
capability_candidate=1
policy_decision_state=report-only
request_freshness_state=report-only
signed_request_state=report-only
runtime_dry_run_state=report-only
blocked_reason=known-capability-candidate-still-denied
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
would_grant_runtime_authority=0
receipt_complete=1
receipt_invalid=0
report_only=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Required invariant tests

The invariant test verifies:

```text
valid report-only inputs produce a complete denied receipt
operator_receipt_profile is stable
receipt_mode remains report-only
receipt_status remains denied-report-only
all source present flags remain one for complete receipt
capability_name is copied descriptively
capability_known remains one
capability_candidate remains one
policy_decision_state remains report-only
request_freshness_state remains report-only
signed_request_state remains report-only
runtime_dry_run_state remains report-only
blocked_reason remains known-capability-candidate-still-denied
default_action_deny remains one
would_allow remains zero
would_deny remains one
would_require_operator_review remains one
would_execute_tool remains zero
would_read_host remains zero
would_write_host remains zero
would_use_network remains zero
would_grant_runtime_authority remains zero
receipt_complete remains one for complete denied receipt
receipt_invalid remains zero for complete denied receipt
missing source metadata fails closed
non-report-only source metadata fails closed
source metadata that would allow an effect fails closed
small report buffers fail closed
null inputs fail closed
```

## Required build runner

The test runner compiles only local C sources and fixtures.

Runner:

```sh
sh scripts/test-latticra-seal-operator-receipt-report.sh
```

It compiles:

```text
src/seal_operator_receipt_report.c
src/seal_capability_metadata.c
tests/seal_operator_receipt_report_invariants.c
```

## Explicit non-goals

The implementation must not:

```text
write receipt files
create persistent receipt artifacts
execute tools
execute shell commands
control AI agents
implement MCP behavior
read host files
write host files
use the network
evaluate external policies
load policy files
verify signatures
sign receipts
parse keys
load key material
handle private keys
query trust stores
query revocation sources
validate freshness against live time
mutate replay caches
grant authority
perform runtime handoff
perform effects
claim malware prevention
claim ransomware prevention
claim production readiness
```

The report may render only caller-provided in-memory metadata from existing local fixtures.

Operator receipt report implementation work is now represented by `docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md`.

Operator receipt report surface/status work is now represented by `docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md` and `docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md`.

## Current validation

This implementation plan is covered by:

```sh
sh scripts/test-latticra-seal-operator-receipt-report-implementation-plan.sh
```

Expected output:

```text
latticra seal operator receipt report implementation plan: ok
```

## Current next valid slice

The operator receipt report surface/status checkpoint is now represented by `docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md` and `docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md`.

The local capability registry schema contract is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md`.

The local capability registry schema implementation plan is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md`.

The local capability registry schema implementation is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md`.

The local capability registry schema surface is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md`.

The local capability registry schema status checkpoint is now represented by `docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md`.

The Panel-visible Seal dashboard planning checkpoint is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md`.

The Seal Panel dashboard view-model contract is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The Seal Panel dashboard view-model implementation plan is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.

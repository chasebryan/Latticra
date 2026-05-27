# Latticra Seal Operator Receipt Report Contract

Status: Latticra Seal operator receipt report contract
Scope: contract-only planning for a future bundled local operator receipt report after the Seal product spine status checkpoint. This document does not implement a receipt report, write receipt files, create artifacts, execute tools, perform runtime behavior, grant runtime authority, enforce capabilities, perform effects, verify signatures, parse public keys, load key material, handle private keys, query trust stores, use networks, read host files beyond future caller-provided metadata, mutate host files, implement MCP behavior, control AI agents, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This contract defines the next Latticra Seal product slice: a future operator-visible receipt report that bundles the existing report-only Seal metadata chain into one local, inspectable decision artifact.

The future receipt report should answer:

```text
What capability was requested?
Was the capability known only as a candidate?
What did policy decide?
Was freshness metadata present?
Was signed-request metadata present?
What would the runtime dry-run do?
Why is the request still denied?
Did anything execute?
Was runtime authority granted?
```

## Required predecessors

The future implementation may only proceed after these predecessor surfaces remain present and guarded:

```text
docs/latticra-seal/PRODUCT.md
docs/status/SEAL_PRODUCT_SPINE_STATUS.md
docs/LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_SURFACE.md
docs/status/SEAL_CAPABILITY_METADATA_REPORT_SURFACE_STATUS.md
docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
docs/status/SEAL_POLICY_DECISION_STATUS.md
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md
docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
docs/status/SEAL_SIGNED_REQUEST_STATUS.md
docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md
docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md
```

## Future implementation name

```text
Latticra Seal operator receipt report
```

## Future files

The future implementation should use a bounded C surface and deterministic shell guards:

```text
include/latticra/seal_operator_receipt_report.h
src/seal_operator_receipt_report.c
tests/seal_operator_receipt_report_invariants.c
tests/seal_operator_receipt_report_surface.c
scripts/test-latticra-seal-operator-receipt-report.sh
scripts/latticra-seal-operator-receipt-report.sh
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md
docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md
```

## Receipt profile

The future report must use this profile:

```text
operator_receipt_profile=latticra-seal-operator-receipt-report/0.1
receipt_mode=report-only
receipt_status=denied-report-only
```

## Required source bindings

The future receipt report must bind source metadata explicitly:

```text
source_capability_metadata_present=1
source_policy_decision_present=1
source_request_freshness_present=1
source_signed_request_present=1
source_runtime_dry_run_present=1
source_denial_reason_present=1
```

If any required source metadata is absent, malformed, or not report-only, the receipt must fail closed:

```text
receipt_complete=0
receipt_invalid=1
would_allow=0
would_deny=1
runtime_authority_granted=0
```

## Required report fields

The future report must render deterministic fields for:

```text
operator_receipt_profile=
receipt_mode=
receipt_status=
source_capability_metadata_present=
source_policy_decision_present=
source_request_freshness_present=
source_signed_request_present=
source_runtime_dry_run_present=
source_denial_reason_present=
capability_name=
capability_known=
capability_candidate=
policy_decision_state=
request_freshness_state=
signed_request_state=
runtime_dry_run_state=
blocked_reason=
default_action_deny=
would_allow=
would_deny=
would_require_operator_review=
would_execute_tool=
would_read_host=
would_write_host=
would_use_network=
would_grant_runtime_authority=
receipt_complete=
receipt_invalid=
report_only=
runtime_authority_granted=
effect_performed=
host_read_performed=
host_write_performed=
network_performed=
```

## Required denied posture

The default operator receipt report must preserve:

```text
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
would_grant_runtime_authority=0
report_only=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Failure behavior

The future implementation must fail closed when:

```text
capability metadata is missing
policy decision metadata is missing
request freshness metadata is missing
signed request metadata is missing
runtime dry-run metadata is missing
any source metadata is not report-only
any source metadata would allow an effect
the output buffer is null
the output buffer is too small
```

Failure must produce no effects, no host reads, no host writes, no network behavior, no runtime handoff, no tool execution, and no runtime authority.

## Non-goals

This contract does not allow:

```text
runtime enforcement
capability enforcement
tool execution
AI-agent execution control
MCP protocol behavior
signature verification
signing
key parsing
key material loading
private-key handling
trust-store loading
revocation lookup
nonce storage
replay-cache mutation
host mutation
network behavior
kernel behavior
production security-product claims
malware prevention claims
ransomware prevention claims
```

## Validation requirements

The future implementation guard must verify:

```text
all required predecessor docs and status records exist
the receipt profile is stable
all source bindings are rendered
missing source metadata fails closed
non-report-only source metadata fails closed
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
runtime_authority_granted=0
small output buffer fails closed
```

## Current guard

This contract is covered by:

```sh
sh scripts/test-latticra-seal-operator-receipt-report-contract.sh
```

Expected output:

```text
latticra seal operator receipt report contract: ok
```

## Current next valid slice

The no-effect operator receipt report implementation, report surface, and status record are now current follow-up checkpoints.

The operator receipt report surface/status checkpoint is now represented by `docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md` and `docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md`.

The local capability registry schema contract is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md`.

The local capability registry schema implementation plan is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md`.

The local capability registry schema implementation is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md`.

The local capability registry schema surface is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md`.

The local capability registry schema status checkpoint is now represented by `docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md`.

The Panel-visible Seal dashboard planning checkpoint is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md`.

The Seal Panel dashboard view-model contract is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The next valid Latticra Seal slice is a Seal Panel dashboard view-model implementation plan or a signed receipt proof path.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.

# Latticra Seal Operator Receipt Report Implementation

Status: no-effect Latticra Seal operator receipt report implementation
Scope: bounded C metadata implementation for composing existing report-only Seal source records into one deterministic operator receipt. This implementation does not write receipt files, create persistent artifacts, execute tools, perform runtime behavior, grant runtime authority, enforce capabilities, perform effects, verify signatures, parse public keys, load key material, handle private keys, query trust stores, use networks, mutate host files, implement MCP behavior, control AI agents, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

The operator receipt report makes the current Seal denial chain easier to inspect.

It combines these caller-provided in-memory records:

```text
capability metadata
policy decision metadata
request freshness metadata
signed request metadata
runtime dry-run metadata
```

The result is still denied, report-only, and no-effect. It is an operator-facing evidence bundle, not an enforcement path.

## Files

```text
include/latticra/seal_operator_receipt_report.h
src/seal_operator_receipt_report.c
tests/seal_operator_receipt_report_invariants.c
scripts/test-latticra-seal-operator-receipt-report.sh
docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_IMPLEMENTATION.md
```

## Public API

The implementation adds:

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

## Error Model

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

Invalid source metadata is represented as denied metadata inside the receipt record. A null output pointer is still a hard `LATTICRA_STATUS_NULL_ARGUMENT` API error. A too-small render buffer returns `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clears the caller-provided buffer when possible. Unterminated source strings are denied before descriptive source text is copied into the receipt. Unterminated or authority-bearing receipt structs are rejected before rendering and clear the caller-provided buffer when possible.

## Complete Denied Receipt

A complete report-only receipt renders:

```text
LATTICRA SEAL OPERATOR RECEIPT REPORT
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
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
would_grant_runtime_authority=0
unknown_tool_denied=1
unsigned_request_denied=1
invalid_schema_denied=1
stale_request_denied=1
replayed_request_denied=1
invalid_signature_denied=1
blocked_reason=known-capability-candidate-still-denied
receipt_complete=1
receipt_invalid=0
report_only=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
error=ok
```

## Fail-Closed Behavior

Missing, malformed, non-report-only, or effect-allowing source metadata produces:

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

The implementation copies descriptive state only. It never copies authority, effect, host I/O, or network behavior from upstream sources.

Additional public-struct hardening rejects:

```text
unterminated source strings before receipt copy
unterminated receipt strings before rendering
tampered receipt effect flags before rendering
tampered receipt authority flags before rendering
```

## Validation

Current guard:

```sh
sh scripts/test-latticra-seal-operator-receipt-report.sh
```

Expected output:

```text
seal operator receipt report invariants: ok
latticra seal operator receipt report: ok
```

The guard compiles the new receipt implementation with the deterministic capability metadata fixture and verifies complete receipt rendering, missing source denial, non-report-only source denial, effect-allowing source denial, null handling, small-buffer handling, source-string rejection before copy, and receipt render rejection for unterminated strings or tampered effect flags.

## Current Next Valid Slice

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

# Latticra Seal Operator Receipt Report Surface

Status: report surface for the Latticra Seal operator receipt report
Scope: deterministic local report surface after the no-effect operator receipt report implementation. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This document records the first operator-visible report surface for the Latticra Seal operator receipt report.

The report surface renders one deterministic denied receipt that binds capability metadata, policy decision metadata, request freshness metadata, signed request metadata, runtime dry-run metadata, and the denial reason into one local operator-facing report.

## Added files

```text
tests/seal_operator_receipt_report_surface.c
scripts/latticra-seal-operator-receipt-report.sh
```

## Report runner

```sh
sh scripts/latticra-seal-operator-receipt-report.sh
```

## Expected report posture

The report surface renders the current operator receipt posture for a known local fixture capability candidate, including:

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

## Boundary

This report surface compiles and runs a local deterministic fixture only.

It does not execute tools, execute shell commands beyond compiling and running the local test fixture, read host files beyond the repository sources needed for local compilation, write host files beyond the temporary test binary/report path, use the network, evaluate external policies, load policy files, load production capability files, load production allowlist files, verify signatures, validate freshness against live time, mutate replay caches, grant authority, turn capability matches into execution grants, turn capability matches into effect grants, claim production readiness, claim AI-agent security, or claim MCP implementation.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-operator-receipt-report-surface.sh
```

Expected output:

```text
latticra seal operator receipt report surface: ok
```

The underlying operator receipt report implementation remains covered by:

```sh
sh scripts/test-latticra-seal-operator-receipt-report.sh
```

## Claim Boundary

This report surface does not justify the public claim that Latticra Seal is a production security product.

It makes the denied receipt posture easier to inspect before any future capability enforcement or runtime authority path is considered.

## Next Valid Slice

The operator receipt report status alignment is now represented by `docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md`.

The local capability registry schema contract is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md`.

The local capability registry schema implementation plan is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md`.

The local capability registry schema implementation is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md`.

The local capability registry schema surface is now represented by `docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md`.

The local capability registry schema status checkpoint is now represented by `docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md`.

The Panel-visible Seal dashboard planning checkpoint is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md`.

The Seal Panel dashboard view-model contract is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The Seal Panel dashboard view-model implementation plan is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.

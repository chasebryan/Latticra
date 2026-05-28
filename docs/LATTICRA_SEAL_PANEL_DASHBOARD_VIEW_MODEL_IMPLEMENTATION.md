# Latticra Seal Panel Dashboard View Model Implementation

Status: bounded no-effect implementation for the Latticra Seal Panel dashboard view model
Scope: C implementation after the Seal Panel dashboard view-model implementation plan. This implementation does not render Panel UI, launch Latticra Panel, read report files, auto-discover host paths, watch directories, write dashboard artifacts, create receipts, execute tools, evaluate policy, enforce policy, enforce capabilities, verify signatures, parse keys, query trust stores, use networks, mutate host files, perform runtime behavior, grant runtime authority, perform effects, control AI agents, implement MCP behavior, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This slice turns the guarded Seal Panel dashboard view-model plan into a fixed-capacity in-memory C model.

It accepts caller-provided report strings only, performs bounded marker checks, and emits deterministic operator-facing rows. Missing, malformed, and stale source evidence remains visible. No row can become an execution grant, host grant, network grant, runtime authority grant, or effect.

## Implemented Files

```text
include/latticra/seal_panel_dashboard_view_model.h
src/seal_panel_dashboard_view_model.c
tests/seal_panel_dashboard_view_model_invariants.c
scripts/test-latticra-seal-panel-dashboard-view-model.sh
docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
.github/workflows/latticra-seal-panel-dashboard-view-model.yml
```

## Implemented API

```text
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_PROFILE_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_ID_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_LABEL_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_ID_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_LABEL_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SUMMARY_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BLOCKED_REASON_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_NEXT_ACTION_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_REPORT_MAX
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_REPORT_MAX
latticra_seal_panel_dashboard_view_model_error_t
latticra_seal_panel_dashboard_view_model_category_t
latticra_seal_panel_dashboard_view_model_state_t
latticra_seal_panel_dashboard_view_model_decision_t
latticra_seal_panel_dashboard_view_model_severity_t
latticra_seal_panel_dashboard_view_model_source_t
latticra_seal_panel_dashboard_view_model_row_t
latticra_seal_panel_dashboard_view_model_t
latticra_seal_panel_dashboard_view_model_error_label
latticra_seal_panel_dashboard_view_model_category_label
latticra_seal_panel_dashboard_view_model_state_label
latticra_seal_panel_dashboard_view_model_decision_label
latticra_seal_panel_dashboard_view_model_severity_label
latticra_seal_panel_dashboard_view_model_init
latticra_seal_panel_dashboard_view_model_add_source_report
latticra_seal_panel_dashboard_view_model_add_required_rows
latticra_seal_panel_dashboard_view_model_validate
latticra_seal_panel_dashboard_view_model_is_report_only
latticra_seal_panel_dashboard_view_model_render
```

The API exposes no file-path input, directory scanner, host inventory reader, network loader, trust-store loader, signature verifier, policy evaluator, capability enforcer, Panel launcher, runtime handoff function, or effect executor.

## Initial Output

The initialized model preserves:

```text
seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1
seal_panel_dashboard_view_model_mode=report-only
seal_panel_dashboard_view_model_status=planned-no-effect
seal_panel_dashboard_view_model_contract_present=1
seal_panel_dashboard_view_model_implementation_plan_present=1
view_model_entry_count=0
view_model_entry_count_max=16
view_model_source_count=0
view_model_source_count_max=16
input_contract_mode=caller-provided-report-strings
caller_provided_report_strings_only=1
missing_source_row_visible=1
malformed_source_row_visible=1
stale_source_row_visible=1
missing_source_default_decision=review
malformed_source_default_decision=deny
stale_source_default_decision=deny
unknown_source_default_decision=deny
operator_review_required_for_any_missing_source=1
authority_absent_for_all_rows=1
panel_ui_implemented=0
dashboard_view_model_implemented=1
report_file_loading_implemented=0
auto_discover_reports=0
auto_scan_host_paths=0
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
error=ok
```

## Caller-Provided Source Reports

`latticra_seal_panel_dashboard_view_model_add_source_report` accepts only in-memory caller-provided source report strings.

It performs bounded marker checks for:

```text
runtime_authority_granted=1
grants_runtime_authority=1
effect_performed=1
can_execute_tool=1
host_read_performed=1
host_write_performed=1
network_performed=1
can_use_network=1
source_report_malformed=1
source_report_stale=1
```

Authority-bearing, effect-bearing, host-touching, and network-touching source strings are rejected before they become source records.

Malformed and stale source strings are not hidden. They become visible denied rows.

## Required Rows

The required rows are fixed:

```text
row_id=seal.product.spine
row_id=seal.operator.receipt
row_id=seal.local.capability.registry.schema
row_id=seal.policy.decision
row_id=seal.signed.request
row_id=seal.request.freshness
row_id=seal.runtime.dry.run
row_id=seal.verification.receipt
row_id=seal.capability.gate
row_id=seal.effect.decision
row_id=seal.runtime.handoff
row_id=seal.status.rollup
```

Every row preserves:

```text
denied_by_default=1
requires_operator_review=1
authority_absent=1
can_execute_tool=0
can_read_host=0
can_write_host=0
can_use_network=0
grants_runtime_authority=0
effect_performed=0
```

## Failure Behavior

Missing source evidence emits:

```text
row_state=missing
row_decision=review
row_severity=warning
source_missing=1
row_blocked_reason=source-missing-no-authority
```

Malformed source evidence emits:

```text
row_state=malformed
row_decision=deny
row_severity=blocked
source_malformed=1
row_blocked_reason=malformed-source-denied
```

Stale source evidence emits:

```text
row_state=stale
row_decision=deny
row_severity=blocked
source_stale=1
row_blocked_reason=stale-source-denied
```

## Report Shape

The renderer emits deterministic local metadata:

```text
LATTICRA SEAL PANEL DASHBOARD VIEW MODEL REPORT
seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1
seal_panel_dashboard_view_model_mode=report-only
seal_panel_dashboard_view_model_status=planned-no-effect
seal_panel_dashboard_view_model_contract_present=1
seal_panel_dashboard_view_model_implementation_plan_present=1
view_model_entry_count=12
view_model_entry_count_max=16
view_model_source_count=12
view_model_source_count_max=16
input_contract_mode=caller-provided-report-strings
missing_source_row_visible=1
malformed_source_row_visible=1
stale_source_row_visible=1
missing_source_default_decision=review
malformed_source_default_decision=deny
stale_source_default_decision=deny
unknown_source_default_decision=deny
operator_review_required_for_any_missing_source=1
authority_absent_for_all_rows=1
panel_ui_implemented=0
dashboard_view_model_implemented=1
report_file_loading_implemented=0
auto_discover_reports=0
auto_scan_host_paths=0
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
row_id=seal.product.spine
row_label=Seal product spine
row_category=mode
row_source=seal.product.spine
row_state=present
row_decision=deny
row_severity=info
row_summary=Product spine evidence remains report-only and denied by default.
row_blocked_reason=report-only-source-denied-by-default
row_next_action=keep in operator review until signed authority exists
evidence_present=1
source_missing=0
source_malformed=0
source_stale=0
denied_by_default=1
requires_operator_review=1
authority_absent=1
can_execute_tool=0
can_read_host=0
can_write_host=0
can_use_network=0
grants_runtime_authority=0
effect_performed=0
error=ok
```

## Failure Gates

The implementation rejects:

```text
null output
null source input
small render buffer
unterminated public struct strings before rendering
tampered source count before row construction
tampered row count before row construction
source capacity overflow
row capacity overflow
invalid category
invalid state
invalid decision
invalid severity
source that would grant authority
source that would perform an effect
source that would touch the host
source that would use the network
```

Invalid input preserves:

```text
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Boundary

This is a no-effect local metadata implementation.

It does not load report files, scan host paths, run tools, invoke shells, evaluate policy, enforce capabilities, verify signatures, query trust stores, use networks, render Panel UI, launch Panel, grant runtime authority, perform host reads, perform host writes, perform effects, or turn dashboard rows into execution grants.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-panel-dashboard-view-model.sh
```

Expected output:

```text
seal panel dashboard view model invariants: ok
latticra seal panel dashboard view model: ok
```

## Current Next Valid Slice

The Seal Panel dashboard view-model implementation plan status checkpoint is represented by `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.

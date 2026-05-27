# Latticra Seal Panel Dashboard View Model Surface

Status: report surface for the Latticra Seal Panel dashboard view model
Scope: deterministic report surface after the bounded no-effect Seal Panel dashboard view-model implementation. This surface does not render Panel UI, launch Latticra Panel, read report files, auto-discover host paths, watch directories, write dashboard artifacts, create receipts, execute tools, evaluate policy, enforce policy, enforce capabilities, verify signatures, parse keys, query trust stores, use networks, mutate host files, perform runtime behavior, grant runtime authority, perform effects, control AI agents, implement MCP behavior, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This surface makes the implemented Seal Panel dashboard view model reproducible from a local guard.

It compiles a tiny runner that builds the deterministic source fixture in memory, adds the required dashboard rows, validates the no-effect model, and writes the rendered report to stdout.

## Implemented Surface Files

```text
tests/seal_panel_dashboard_view_model_surface.c
scripts/latticra-seal-panel-dashboard-view-model.sh
scripts/test-latticra-seal-panel-dashboard-view-model-surface.sh
docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md
.github/workflows/latticra-seal-panel-dashboard-view-model-surface.yml
```

## Report Runner

Run:

```sh
sh scripts/latticra-seal-panel-dashboard-view-model.sh
```

The runner uses only caller-provided in-memory fixture strings. It does not read a report path, scan a directory, launch Panel, inspect the host, run tools, or contact a network.

## Expected Report

The report surface emits:

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
row_id=seal.status.rollup
error=ok
```

All twelve required rows render with:

```text
row_decision=deny
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

## Validation

Run:

```sh
sh scripts/test-latticra-seal-panel-dashboard-view-model-surface.sh
```

Expected output:

```text
latticra seal panel dashboard view model surface: ok
```

The underlying implementation remains covered by:

```sh
sh scripts/test-latticra-seal-panel-dashboard-view-model.sh
```

## Status

This surface is tracked by `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md`.

## Boundary

This is a deterministic report surface only.

It does not add Panel UI, report file loading, host scanning, network lookup, shell execution, tool execution, policy enforcement, capability enforcement, signature verification, runtime handoff execution, runtime authority, effect execution, host reads, host writes, or production security claims.

## Current Next Valid Slice

The Seal Panel dashboard view-model status checkpoint is represented by `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.

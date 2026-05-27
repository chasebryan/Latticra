# Latticra Seal Panel Dashboard View Model Contract

Status: contract for the future Latticra Seal Panel dashboard view model
Scope: view-model contract after the Panel-visible Seal dashboard planning checkpoint. This document does not implement a dashboard view model, render Panel UI, launch Latticra Panel, read report files, auto-discover host paths, write dashboard artifacts, create receipts, execute tools, evaluate policy, enforce policy, enforce capabilities, verify signatures, parse keys, query trust stores, use networks, mutate host files, perform runtime behavior, grant runtime authority, perform effects, control AI agents, implement MCP behavior, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This contract defines the exact no-effect view-model vocabulary a future Seal Panel dashboard implementation must satisfy.

The view model is a local display contract only. It turns already-available Seal evidence into operator-facing rows while preserving denial, missing-source visibility, and absent authority.

## Predecessor

This contract follows the Panel dashboard planning checkpoint:

```text
docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md
docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md
```

The view-model contract must preserve:

```text
panel_ui_implemented=0
dashboard_view_model_implemented=0
report_file_loading_implemented=0
auto_scan_host_paths=0
runtime_authority_granted=0
effect_performed=0
```

## Contract Fields

The future view model must include a header:

```text
seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1
seal_panel_dashboard_view_model_mode=contract-only
seal_panel_dashboard_view_model_status=not-implemented
seal_panel_dashboard_view_model_contract_present=1
predecessor_panel_dashboard_planning_status_present=1
view_model_entry_count_max=16
view_model_row_id_max=64
view_model_label_max=96
view_model_summary_max=192
view_model_blocked_reason_max=160
view_model_next_action_max=160
input_contract_mode=caller-provided-report-strings
auto_discover_reports=0
auto_scan_host_paths=0
report_file_loading_implemented=0
panel_ui_implemented=0
dashboard_view_model_implemented=0
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
production_security_product=0
```

Each future row must include:

```text
row_id=required
row_label=required
row_category=required
row_source=required
row_state=required
row_decision=required
row_severity=required
row_summary=required
row_blocked_reason=required
row_next_action=required
evidence_present=required
source_missing=required
source_malformed=required
source_stale=required
denied_by_default=required
requires_operator_review=required
authority_absent=required
can_execute_tool=required
can_read_host=required
can_write_host=required
can_use_network=required
grants_runtime_authority=required
effect_performed=required
```

## Required Rows

The first implementation must support these rows:

```text
row=seal.product.spine
row=seal.operator.receipt
row=seal.local.capability.registry.schema
row=seal.policy.decision
row=seal.signed.request
row=seal.request.freshness
row=seal.runtime.dry.run
row=seal.verification.receipt
row=seal.capability.gate
row=seal.effect.decision
row=seal.runtime.handoff
row=seal.status.rollup
```

## Allowed Labels

Allowed category labels:

```text
category=mode
category=evidence
category=decision
category=authority
category=source
category=next-step
```

Allowed row states:

```text
state=present
state=missing
state=malformed
state=stale
state=blocked
state=planned
```

Allowed decisions:

```text
decision=deny
decision=review
decision=unknown
decision=not-applicable
```

Allowed severities:

```text
severity=info
severity=warning
severity=blocked
```

## Failure Behavior

Missing, malformed, or stale source evidence must remain visible as rows. A future implementation must not hide missing evidence or silently promote it to success.

Required failure behavior:

```text
missing_source_row_visible=1
malformed_source_row_visible=1
stale_source_row_visible=1
missing_source_default_decision=review
malformed_source_default_decision=deny
stale_source_default_decision=deny
unknown_source_default_decision=deny
operator_review_required_for_any_missing_source=1
authority_absent_for_all_rows=1
```

## Boundary

This contract is documentation/status alignment only.

It does not implement the view model, parse report text, load report files, scan host paths, render Panel UI, launch Panel, create receipts, execute tools, evaluate policy, enforce policy, enforce capabilities, verify signatures, read keys, load trust stores, use a network, perform runtime handoff, perform effects, or change current Seal authority.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-panel-dashboard-view-model-contract.sh
```

Expected output:

```text
latticra seal panel dashboard view model contract: ok
```

## Next Valid Slice

The Seal Panel dashboard view-model contract status checkpoint is represented by `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The next valid Latticra Seal slice is a Seal Panel dashboard view-model implementation plan or a signed receipt proof path.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.

# Latticra Seal Panel Dashboard View Model Implementation Plan

Status: implementation plan for a future no-effect Latticra Seal Panel dashboard view model
Scope: implementation planning after the Seal Panel dashboard view-model contract. This document does not implement a dashboard view model, render Panel UI, launch Latticra Panel, read report files, auto-discover host paths, write dashboard artifacts, create receipts, execute tools, evaluate policy, enforce policy, enforce capabilities, verify signatures, parse keys, query trust stores, use networks, mutate host files, perform runtime behavior, grant runtime authority, perform effects, control AI agents, implement MCP behavior, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This plan maps the Seal Panel dashboard view-model contract into a future deterministic no-effect implementation.

The future implementation should convert caller-provided report strings into bounded operator-facing rows while preserving denial, missing-source visibility, stale-source visibility, malformed-source visibility, and absent authority.

## Required Contract

The implementation plan depends on:

```text
docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md
docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md
scripts/test-latticra-seal-panel-dashboard-view-model-contract.sh
scripts/test-latticra-seal-panel-dashboard-view-model-contract-status.sh
```

The contract must remain merged and guarded before implementation code is added.

## Planned Files

A future implementation slice may add:

```text
include/latticra/seal_panel_dashboard_view_model.h
src/seal_panel_dashboard_view_model.c
tests/seal_panel_dashboard_view_model_invariants.c
scripts/test-latticra-seal-panel-dashboard-view-model.sh
docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
```

A later report-surface slice may add:

```text
tests/seal_panel_dashboard_view_model_surface.c
scripts/latticra-seal-panel-dashboard-view-model.sh
scripts/test-latticra-seal-panel-dashboard-view-model-surface.sh
docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md
docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md
```

## Plan Fields

The plan records:

```text
seal_panel_dashboard_view_model_implementation_plan_present=1
predecessor_view_model_contract_status_present=1
seal_panel_dashboard_view_model_plan_profile=latticra-seal-panel-dashboard-view-model-implementation-plan/0.1
seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1
seal_panel_dashboard_view_model_mode=implementation-plan-only
seal_panel_dashboard_view_model_status=not-implemented
view_model_entry_count_max=16
view_model_source_count_max=16
view_model_row_id_max=64
view_model_label_max=96
view_model_summary_max=192
view_model_blocked_reason_max=160
view_model_next_action_max=160
input_contract_mode=caller-provided-report-strings
caller_provided_report_strings_only=1
deterministic_fixture_planned=1
bounded_key_value_scan_planned=1
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

## Header API Plan

The future header should define:

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
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_REPORT_MAX
latticra_seal_panel_dashboard_view_model_error_t
latticra_seal_panel_dashboard_view_model_source_t
latticra_seal_panel_dashboard_view_model_row_t
latticra_seal_panel_dashboard_view_model_t
latticra_seal_panel_dashboard_view_model_error_label
latticra_seal_panel_dashboard_view_model_init
latticra_seal_panel_dashboard_view_model_add_source_report
latticra_seal_panel_dashboard_view_model_add_required_rows
latticra_seal_panel_dashboard_view_model_validate
latticra_seal_panel_dashboard_view_model_is_report_only
latticra_seal_panel_dashboard_view_model_render
```

The API must not include a file-path input, directory scanner, host inventory reader, network loader, trust-store loader, signature verifier, policy evaluator, capability enforcer, Panel launcher, runtime handoff function, or effect executor.

## Source Record Plan

Each caller-provided source report record should include:

```text
source_id
source_label
source_report_present
source_report_text_present
source_report_malformed
source_report_stale
source_report_only
source_required
source_runtime_authority_granted
source_effect_performed
source_host_read_performed
source_host_write_performed
source_network_performed
source_blocked_reason
```

The implementation must accept source report strings only from the caller. It must not locate files, open paths, scan directories, watch folders, invoke commands, or query services.

## Row Record Plan

Every row should include:

```text
row_id
row_label
row_category
row_source
row_state
row_decision
row_severity
row_summary
row_blocked_reason
row_next_action
evidence_present
source_missing
source_malformed
source_stale
denied_by_default
requires_operator_review
authority_absent
can_execute_tool
can_read_host
can_write_host
can_use_network
grants_runtime_authority
effect_performed
```

Required initial rows:

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

## Error Model

The future error enum should include:

```text
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_PROFILE
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_SOURCE_ID
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_ROW_ID
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_CATEGORY
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_STATE
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_DECISION
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_SEVERITY
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_CAPACITY_EXCEEDED
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_CAPACITY_EXCEEDED
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MISSING_SOURCE
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MALFORMED_SOURCE
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STALE_SOURCE
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK
LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BUFFER_TOO_SMALL
```

## Initial Constants

The initialized view model should emit:

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
auto_discover_reports=0
auto_scan_host_paths=0
report_file_loading_implemented=0
panel_ui_implemented=0
dashboard_view_model_implemented=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

The future implementation may set `dashboard_view_model_implemented=1` only in the implementation slice. This plan and its status record must keep `dashboard_view_model_implemented=0`.

## Function Behavior

The future builder should:

```text
initialize a caller-provided view-model record
accept caller-provided report strings only
add bounded source report records
add the required initial dashboard rows
map missing source evidence to visible review rows
map malformed source evidence to visible denied rows
map stale source evidence to visible denied rows
validate bounded category values
validate bounded state values
validate bounded decision values
validate bounded severity values
reject null output
reject null source input
reject source capacity overflow
reject row capacity overflow
reject any source that would grant authority
reject any source that would perform an effect
reject any source that would touch the host
reject any source that would use the network
render deterministic metadata only
return BUFFER_TOO_SMALL for insufficient render buffers
```

The implementation must not expose a file-path input API.

## Required Report Shape

The render function should produce:

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

Rows should render as stable `key=value` blocks using the required row fields from the view-model contract.

## Required Invariant Tests

The invariant test should cover:

```text
default view model initializes as report-only
default profile is stable
caller-provided source reports are accepted without file loading
all required rows are present
missing source creates a visible review row
malformed source creates a visible denied row
stale source creates a visible denied row
unknown source remains denied by default
operator review is required for missing evidence
authority remains absent for every row
tool execution remains impossible
host read remains impossible
host write remains impossible
network use remains impossible
runtime authority remains zero
effect performed remains zero
source capacity overflow is rejected
row capacity overflow is rejected
invalid category is rejected
invalid state is rejected
invalid decision is rejected
invalid severity is rejected
small render buffer is rejected
null inputs fail closed
```

## Forbidden Behavior

The implementation must not add:

```text
Panel UI rendering
Panel launching
report file loading
report path auto-discovery
host path scanning
host inventory reading
registry file loading
remote registry loading
trust-store lookup
signature verification
policy evaluation
policy enforcement
capability enforcement
runtime enforcement
tool execution
shell execution
AI-agent execution control
MCP protocol behavior
host reads
host writes
network behavior
runtime handoff execution
runtime authority grants
turning dashboard rows into execution grants
turning dashboard rows into effect grants
malware prevention claims
ransomware prevention claims
production security-product claims
```

## Current Validation

This implementation plan is covered by:

```sh
sh scripts/test-latticra-seal-panel-dashboard-view-model-implementation-plan.sh
```

Expected output:

```text
latticra seal panel dashboard view model implementation plan: ok
```

## Current Next Valid Slice

The Seal Panel dashboard view-model implementation plan status checkpoint is represented by `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md`.

The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.

The Seal Panel dashboard view-model implementation is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md`.

The current next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.

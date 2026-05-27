# Latticra Seal Panel Dashboard Planning Checkpoint

Status: planning checkpoint for a Panel-visible Latticra Seal dashboard
Scope: dashboard planning after the local capability registry schema report surface/status checkpoint. This document does not implement Panel UI, launch Latticra Panel, read report files, write dashboard artifacts, create receipts, execute tools, perform shell behavior beyond guard validation, perform runtime behavior, grant runtime authority, perform effects, enforce capabilities, enforce policy, verify signatures, parse keys, query trust stores, use networks, mutate host files, control AI agents, implement MCP behavior, claim malware prevention, claim ransomware prevention, or claim production security readiness.

## Purpose

This checkpoint defines the next visible Seal product surface: a future read-only Panel dashboard that can show current Seal evidence without expanding authority.

The dashboard must help an operator answer five questions:

```text
what_request_or_surface_is_being_reviewed=1
what_evidence_exists=1
what_is_denied_or_blocked=1
what_authority_is_absent=1
what_next_guarded_slice_is_valid=1
```

## Predecessor

This checkpoint follows the local capability registry schema report surface/status checkpoint:

```text
docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md
docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md
```

The dashboard plan must preserve that predecessor's posture:

```text
registry_loader_implemented=0
registry_file_loading_supported=0
registry_network_loading_supported=0
registry_signature_verification_supported=0
registry_trust_store_supported=0
runtime_authority_granted=0
effect_performed=0
```

## Planned Dashboard Shape

The future Panel-visible dashboard should be a dense local operator surface, not a marketing page.

Planned dashboard regions:

```text
seal_status_summary=planned
current_mode_summary=planned
evidence_source_list=planned
denied_decision_list=planned
authority_absence_list=planned
operator_review_queue_preview=planned
receipt_and_report_links=planned
next_guarded_slice_hint=planned
```

Planned source rows:

```text
product_spine_source=planned
operator_receipt_report_source=planned
local_capability_registry_schema_source=planned
policy_decision_source=planned
signed_request_source=planned
request_freshness_source=planned
runtime_dry_run_source=planned
verification_receipt_source=planned
capability_gate_source=planned
effect_decision_source=planned
runtime_handoff_source=planned
status_rollup_source=planned
```

## Planning Fields

The checkpoint records:

```text
seal_panel_dashboard_profile=latticra-seal-panel-dashboard-planning/0.1
seal_panel_dashboard_mode=planning-only
seal_panel_dashboard_status=not-implemented
panel_visible_target=1
panel_dashboard_planning_checkpoint_present=1
predecessor_local_capability_registry_schema_status_present=1
local_report_sources_planned=1
operator_receipt_report_source_planned=1
local_capability_registry_schema_source_planned=1
policy_decision_source_planned=1
runtime_dry_run_source_planned=1
verification_receipt_source_planned=1
capability_gate_source_planned=1
effect_decision_source_planned=1
panel_ui_implemented=0
dashboard_view_model_implemented=0
report_file_loading_implemented=0
panel_launch_performed=0
panel_workflow_run=0
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
production_security_product=0
```

## Future Acceptance Gates

A future dashboard implementation must not begin until a separate guarded contract defines:

```text
exact_view_model_fields=required
exact_source_report_inputs=required
missing_source_behavior=required
malformed_source_behavior=required
stale_source_behavior=required
redaction_rules=required
operator_review_copy=required
no_effect_execution_path=required
guard_tests=required
```

The first implementation should use a local deterministic fixture or caller-provided report strings. It must not auto-scan host paths, load registry files, fetch network state, run tools, execute model behavior, or grant authority.

## Boundary

This checkpoint is planning/status alignment only.

It does not create a dashboard, implement a view model, render Panel UI, launch Panel, read reports, write reports, create receipts, execute tools, evaluate policy, enforce policy, enforce capabilities, parse signatures, verify signatures, read keys, load trust stores, use a network, perform runtime handoff, perform effects, or change current Seal authority.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-panel-dashboard-planning-checkpoint.sh
```

Expected output:

```text
latticra seal panel dashboard planning checkpoint: ok
```

## Next Valid Slice

The Panel-visible Seal dashboard planning status checkpoint is represented by `docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md`.

The Seal Panel dashboard view-model contract is now represented by `docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md`, with status in `docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md`.

The next valid Latticra Seal slice is a Seal Panel dashboard view-model implementation plan or a signed receipt proof path.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.

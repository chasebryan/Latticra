#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal panel dashboard view model status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal panel dashboard view model status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md"
surface_doc="docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md"
implementation_doc="docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md"
product_doc="docs/latticra-seal/PRODUCT.md"
seal_status="docs/latticra-seal/STATUS.md"

require_file "$status_file"
require_file "$surface_doc"
require_file "$implementation_doc"
require_file "$product_doc"
require_file "$seal_status"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file scripts/latticra-seal-panel-dashboard-view-model.sh
require_file scripts/test-latticra-seal-panel-dashboard-view-model.sh
require_file scripts/test-latticra-seal-panel-dashboard-view-model-surface.sh
require_file tests/seal_panel_dashboard_view_model_surface.c
require_file .github/workflows/latticra-seal-panel-dashboard-view-model-surface.yml
require_file .github/workflows/latticra-seal-panel-dashboard-view-model-status.yml

require_contains 'Status: status record for the Latticra Seal Panel dashboard view-model surface' "$status_file"
require_contains 'seal_panel_dashboard_view_model_implementation_present=1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_surface_document_present=1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_surface_fixture_present=1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_runner_present=1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_surface_guard_present=1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_status_present=1' "$status_file"
require_contains 'operator_visible_panel_dashboard_view_model=1' "$status_file"
require_contains 'uses_local_deterministic_fixture=1' "$status_file"
require_contains 'caller_provided_report_strings_only=1' "$status_file"
require_contains 'panel_ui_implemented=0' "$status_file"
require_contains 'dashboard_view_model_implemented=1' "$status_file"
require_contains 'report_file_loading_implemented=0' "$status_file"
require_contains 'auto_discover_reports=0' "$status_file"
require_contains 'auto_scan_host_paths=0' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'runtime_behavior_added=0' "$status_file"
require_contains 'host_behavior_added=0' "$status_file"
require_contains 'network_behavior_added=0' "$status_file"
require_contains 'external_service_behavior_added=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1' "$status_file"
require_contains 'view_model_entry_count=12' "$status_file"
require_contains 'view_model_source_count=12' "$status_file"
require_contains 'row_id=seal.product.spine' "$status_file"
require_contains 'row_id=seal.status.rollup' "$status_file"
require_contains 'row_decision=deny' "$status_file"
require_contains 'can_execute_tool=0' "$status_file"
require_contains 'can_read_host=0' "$status_file"
require_contains 'can_write_host=0' "$status_file"
require_contains 'can_use_network=0' "$status_file"
require_contains 'grants_runtime_authority=0' "$status_file"
require_contains 'signed receipt proof path' "$status_file"
require_contains 'sh scripts/test-latticra-seal-panel-dashboard-view-model-surface.sh' .github/workflows/latticra-seal-panel-dashboard-view-model-surface.yml
require_contains 'sh scripts/test-latticra-seal-panel-dashboard-view-model-status.sh' .github/workflows/latticra-seal-panel-dashboard-view-model-status.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-panel-dashboard-view-model-surface.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-panel-dashboard-view-model-status.yml

require_contains 'panel_dashboard_view_model_surface=1' "$product_doc"
require_contains 'panel_dashboard_view_model_status=1' "$product_doc"
require_contains 'panel_dashboard_view_model_surface_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_status_present=1' "$product_doc"
require_contains 'seal_panel_dashboard=view-model-report-surface' "$product_doc"
require_contains 'seal_panel_dashboard_view_model=report-surface' "$product_doc"
require_contains 'signed receipt proof path' "$product_doc"

require_contains 'panel_dashboard_view_model_surface_present=1' "$seal_status"
require_contains 'panel_dashboard_view_model_status_present=1' "$seal_status"
require_contains 'latticra_seal_panel_dashboard_view_model_surface_present=1' README.md
require_contains 'latticra_seal_panel_dashboard_view_model_status_present=1' README.md
require_contains 'seal_panel_dashboard_view_model_surface_present=1' README.md
require_contains 'seal_panel_dashboard_view_model_status_present=1' README.md
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md' README.md
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md' README.md
require_contains 'Latest Seal Panel dashboard view-model surface/status note: 2026-05-27 CDT' STATUS.md
require_contains 'Latest Seal Panel dashboard view-model surface/status note: 2026-05-27 CDT' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md' docs/status/README.md
require_contains 'Latticra Seal Panel dashboard view-model surface/status' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal Panel dashboard view-model surface/status' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-panel-dashboard-view-model.sh
sh scripts/test-latticra-seal-panel-dashboard-view-model-surface.sh

printf 'latticra seal panel dashboard view model status: ok\n'

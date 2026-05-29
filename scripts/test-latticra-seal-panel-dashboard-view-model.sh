#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-panel-dashboard-view-model.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal panel dashboard view model: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal panel dashboard view model: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/seal_panel_dashboard_view_model_invariants"

require_file include/latticra/seal_panel_dashboard_view_model.h
require_file src/seal_panel_dashboard_view_model.c
require_file tests/seal_panel_dashboard_view_model_invariants.c
require_file docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md
require_file docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md
require_file README.md
require_file STATUS.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/status/README.md
require_file .github/workflows/latticra-seal-panel-dashboard-view-model.yml

require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK' include/latticra/seal_panel_dashboard_view_model.h
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY' include/latticra/seal_panel_dashboard_view_model.h
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT' include/latticra/seal_panel_dashboard_view_model.h
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST' include/latticra/seal_panel_dashboard_view_model.h
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK' include/latticra/seal_panel_dashboard_view_model.h
require_contains 'latticra_seal_panel_dashboard_view_model_add_source_report' include/latticra/seal_panel_dashboard_view_model.h
require_contains 'latticra_seal_panel_dashboard_view_model_add_required_rows' include/latticra/seal_panel_dashboard_view_model.h
require_contains 'latticra_seal_panel_dashboard_view_model_render' include/latticra/seal_panel_dashboard_view_model.h
require_contains 'LATTICRA SEAL PANEL DASHBOARD VIEW MODEL REPORT' src/seal_panel_dashboard_view_model.c
require_contains 'caller-provided-report-strings' src/seal_panel_dashboard_view_model.c
require_contains 'runtime_authority_granted=1' src/seal_panel_dashboard_view_model.c
require_contains 'effect_performed=1' src/seal_panel_dashboard_view_model.c
require_contains 'host_read_performed=1' src/seal_panel_dashboard_view_model.c
require_contains 'network_performed=1' src/seal_panel_dashboard_view_model.c
require_contains 'report_file_loading_implemented=%u' src/seal_panel_dashboard_view_model.c
require_contains 'dashboard_view_model_implemented=%u' src/seal_panel_dashboard_view_model.c
require_contains 'model_contract_error' src/seal_panel_dashboard_view_model.c
require_contains 'row_id=%s' src/seal_panel_dashboard_view_model.c
require_contains 'can_execute_tool=%u' src/seal_panel_dashboard_view_model.c
require_contains 'grants_runtime_authority=%u' src/seal_panel_dashboard_view_model.c
require_contains 'source-missing-no-authority' src/seal_panel_dashboard_view_model.c
require_contains 'malformed-source-denied' src/seal_panel_dashboard_view_model.c
require_contains 'stale-source-denied' src/seal_panel_dashboard_view_model.c
require_contains 'Seal Panel dashboard view-model' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'dashboard_view_model_implemented=1' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'report_file_loading_implemented=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'auto_discover_reports=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'auto_scan_host_paths=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'row_id=seal.product.spine' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'row_id=seal.status.rollup' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'source_missing=1' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'source_malformed=1' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'source_stale=1' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'unterminated public struct strings before rendering' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'runtime_authority_granted=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'effect_performed=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'can_execute_tool=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'can_read_host=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'can_write_host=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'can_use_network=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'grants_runtime_authority=0' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'The next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.' docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_contains 'latticra_seal_panel_dashboard_view_model_implementation_present=1' README.md
require_contains 'seal_panel_dashboard_view_model_implementation_present=1' README.md
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md' README.md
require_contains 'Latest Seal Panel dashboard view-model implementation note: 2026-05-27 CDT' STATUS.md
require_contains 'Latest Seal Panel dashboard view-model implementation note: 2026-05-27 CDT' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md' docs/status/README.md
require_contains 'seal panel dashboard view model invariants: ok' tests/seal_panel_dashboard_view_model_invariants.c
require_contains 'unterminated render rejected' tests/seal_panel_dashboard_view_model_invariants.c
require_contains 'sh scripts/test-latticra-seal-panel-dashboard-view-model.sh' .github/workflows/latticra-seal-panel-dashboard-view-model.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-panel-dashboard-view-model.yml

cc $CFLAGS \
  -Iinclude \
  src/seal_panel_dashboard_view_model.c \
  tests/seal_panel_dashboard_view_model_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra seal panel dashboard view model: ok\n'

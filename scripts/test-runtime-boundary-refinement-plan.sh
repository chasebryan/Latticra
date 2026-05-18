#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'runtime-boundary-refinement-plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime-boundary-refinement-plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_file docs/RUNTIME_BOUNDARY_CONTRACT.md
require_file docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md
require_file docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
require_file docs/LAT_PIPELINE_IMPLEMENTATION.md
require_file docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md
require_file include/latticra/runtime_boundary.h
require_file include/latticra/lat_pipeline.h
require_file include/latticra/lir.h

require_contains 'Status: refinement planning contract' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'planning-only refinement' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'Lat pipeline' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'Lat-specific LIR metadata' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'lat_pipeline_status' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'lat_pipeline_error' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'lat_lir_has_lat_state_nodes' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'lat_lir_has_lat_transition_nodes' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'lat_lir_has_transition_source_edges' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'runtime_boundary_reports_lat_pipeline_status' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'runtime_boundary_reports_lat_specific_lir_node_evidence' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'runtime_boundary_keeps_lat_and_lir_execute_future_gated' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'must not change existing behavior' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'This plan is not implementation evidence by itself.' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'does not implement runtime behavior' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_contains 'does not implement runtime behavior' docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md

printf 'runtime_boundary_refinement_plan: ok\n'

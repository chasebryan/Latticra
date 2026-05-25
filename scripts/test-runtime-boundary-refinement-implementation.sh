#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'runtime-boundary-refinement-implementation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime-boundary-refinement-implementation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_file docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
require_file include/latticra/runtime_boundary.h
require_file src/runtime_boundary.c
require_file tests/runtime_boundary_lat_pipeline_evidence.c
require_file scripts/test-runtime-boundary.sh

require_contains 'Status: runtime boundary refinement implementation with Lat pipeline comment evidence' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'no-effect runtime-boundary evidence reporting' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_status' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_comment_count' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_lir_has_transition_source_edges' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'runtime_boundary_reports_lat_pipeline_evidence' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'does not provide runtime behavior' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE' include/latticra/runtime_boundary.h
require_contains 'const latticra_lat_pipeline_result_t *lat_pipeline' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_status' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_comment_count' include/latticra/runtime_boundary.h
require_contains 'lat_lir_transition_edge_count' include/latticra/runtime_boundary.h
require_contains 'lat-pipeline-validate' src/runtime_boundary.c
require_contains 'lat_pipeline_status=' src/runtime_boundary.c
require_contains 'lat_pipeline_comment_count=' src/runtime_boundary.c
require_contains 'lat_lir_has_transition_source_edges=' src/runtime_boundary.c
require_contains 'runtime_boundary_reports_lat_pipeline_evidence' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_comment_count=2' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'runtime_boundary_keeps_lat_lir_execution_future_gated' tests/runtime_boundary_lat_pipeline_evidence.c

printf 'runtime_boundary_refinement_implementation: ok\n'

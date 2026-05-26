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

require_contains 'Status: runtime boundary refinement implementation with Lat pipeline stage-summary, parse-error, semantic-error, downstream-stage-error, span, and comment evidence' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'no-effect runtime-boundary evidence reporting' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_status' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_parse_error' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_semantic_error' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_model_error' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_lowering_error' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_lir_error' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_last_completed_stage' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_failed_stage' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_no_effect_chain_ok' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_evidence_level' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_span_start_line' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_pipeline_comment_count' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'lat_lir_has_transition_source_edges' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'runtime_boundary_reports_lat_pipeline_evidence' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'does not provide runtime behavior' docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_contains 'LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE' include/latticra/runtime_boundary.h
require_contains 'const latticra_lat_pipeline_result_t *lat_pipeline' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_status' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_parse_error' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_semantic_error' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_model_error' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_lowering_error' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_lir_error' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_last_completed_stage' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_failed_stage' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_no_effect_chain_ok' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_evidence_level' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_span' include/latticra/runtime_boundary.h
require_contains 'lat_pipeline_comment_count' include/latticra/runtime_boundary.h
require_contains 'lat_lir_transition_edge_count' include/latticra/runtime_boundary.h
require_contains 'lat-pipeline-validate' src/runtime_boundary.c
require_contains 'lat_pipeline_status=' src/runtime_boundary.c
require_contains 'lat_pipeline_parse_error=' src/runtime_boundary.c
require_contains 'lat_pipeline_semantic_error=' src/runtime_boundary.c
require_contains 'lat_pipeline_model_error=' src/runtime_boundary.c
require_contains 'lat_pipeline_lowering_error=' src/runtime_boundary.c
require_contains 'lat_pipeline_lir_error=' src/runtime_boundary.c
require_contains 'lat_pipeline_last_completed_stage=' src/runtime_boundary.c
require_contains 'lat_pipeline_failed_stage=' src/runtime_boundary.c
require_contains 'lat_pipeline_no_effect_chain_ok=' src/runtime_boundary.c
require_contains 'lat_pipeline_evidence_level=' src/runtime_boundary.c
require_contains 'lat_pipeline_span_start_line=' src/runtime_boundary.c
require_contains 'lat_pipeline_comment_count=' src/runtime_boundary.c
require_contains 'lat_lir_has_transition_source_edges=' src/runtime_boundary.c
require_contains 'runtime_boundary_reports_lat_pipeline_evidence' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'runtime_boundary_denies_parse_failed_lat_pipeline_metadata' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'runtime_boundary_denies_model_failed_lat_pipeline_metadata' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_parse_error=unsupported_block_comment' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_semantic_error=unknown_transition_source' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_model_error=unsupported_clause' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_last_completed_stage=report' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_failed_stage=parse' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_no_effect_chain_ok=1' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_evidence_level=2' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_span_start_line=2' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'lat_pipeline_comment_count=2' tests/runtime_boundary_lat_pipeline_evidence.c
require_contains 'runtime_boundary_keeps_lat_lir_execution_future_gated' tests/runtime_boundary_lat_pipeline_evidence.c

printf 'runtime_boundary_refinement_implementation: ok\n'

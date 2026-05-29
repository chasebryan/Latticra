#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'lat-pipeline-report-refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lat-pipeline-report-refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_file docs/LAT_PIPELINE_IMPLEMENTATION.md
require_file include/latticra/lat_pipeline.h
require_file src/lat_pipeline.c
require_file tests/lat_pipeline_invariants.c
require_file tests/lat_pipeline_report_refinement.c
require_file scripts/test-lat-pipeline.sh
require_file .github/workflows/lat-pipeline-report-refinement.yml

require_contains 'Status: Lat pipeline report refinement implementation with comment, first-declaration, and first-clause metadata' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'last_completed_stage' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'failed_stage' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'model_ok' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'comment_count' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'first_comment_start_line' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'first_clause_node_index' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'no_effect_chain_ok' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'evidence_level' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'does not provide' docs/LAT_PIPELINE_REPORT_REFINEMENT.md

require_contains 'LATTICRA_LAT_PIPELINE_STAGE_PARSE' include/latticra/lat_pipeline.h
require_contains 'LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC' include/latticra/lat_pipeline.h
require_contains 'LATTICRA_LAT_PIPELINE_STAGE_MODEL' include/latticra/lat_pipeline.h
require_contains 'LATTICRA_LAT_PIPELINE_STAGE_REPORT' include/latticra/lat_pipeline.h
require_contains 'last_completed_stage' include/latticra/lat_pipeline.h
require_contains 'failed_stage' include/latticra/lat_pipeline.h
require_contains 'model_ok' include/latticra/lat_pipeline.h
require_contains 'comment_count' include/latticra/lat_pipeline.h
require_contains 'first_comment_span' include/latticra/lat_pipeline.h
require_contains 'first_clause_node_index' include/latticra/lat_pipeline.h
require_contains 'first_clause_value' include/latticra/lat_pipeline.h
require_contains 'no_effect_chain_ok' include/latticra/lat_pipeline.h
require_contains 'evidence_level' include/latticra/lat_pipeline.h
require_contains 'latticra_lat_pipeline_stage_label' include/latticra/lat_pipeline.h

require_contains 'latticra_lat_pipeline_stage_label' src/lat_pipeline.c
require_contains 'finalize_pipeline_report_refinement' src/lat_pipeline.c
require_contains 'last_completed_stage=' src/lat_pipeline.c
require_contains 'failed_stage=' src/lat_pipeline.c
require_contains 'model_ok=' src/lat_pipeline.c
require_contains 'comment_count=' src/lat_pipeline.c
require_contains 'first_comment_start_line=' src/lat_pipeline.c
require_contains 'first_clause_operator=' src/lat_pipeline.c
require_contains 'no_effect_chain_ok=' src/lat_pipeline.c
require_contains 'evidence_level=' src/lat_pipeline.c

require_contains 'lat_pipeline_exposes_comment_metadata' tests/lat_pipeline_invariants.c
require_contains 'comment_count=4' tests/lat_pipeline_invariants.c
require_contains 'first_comment_start_line=1' tests/lat_pipeline_invariants.c
require_contains 'lat_pipeline_report_refinement_labels_are_stable' tests/lat_pipeline_report_refinement.c
require_contains 'lat_pipeline_report_refinement_reports_success_stage_summary' tests/lat_pipeline_report_refinement.c
require_contains 'comment_count=0' tests/lat_pipeline_report_refinement.c
require_contains 'first_comment_start_line=1' tests/lat_pipeline_report_refinement.c
require_contains 'lat_pipeline_report_refinement_reports_parse_failure_stage' tests/lat_pipeline_report_refinement.c
require_contains 'lat_pipeline_report_refinement_reports_semantic_failure_stage' tests/lat_pipeline_report_refinement.c
require_contains 'lat_pipeline_report_refinement_null_result_sets_unknown_stage' tests/lat_pipeline_report_refinement.c

require_contains 'tests/lat_pipeline_report_refinement.c' scripts/test-lat-pipeline.sh

printf 'lat_pipeline_report_refinement: ok\n'

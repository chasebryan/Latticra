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
require_file tests/lat_pipeline_report_refinement.c
require_file scripts/test-lat-pipeline.sh
require_file .github/workflows/lat-pipeline-report-refinement.yml

require_contains 'Status: initial Lat pipeline report refinement implementation' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'last_completed_stage' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'failed_stage' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'no_effect_chain_ok' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'evidence_level' docs/LAT_PIPELINE_REPORT_REFINEMENT.md
require_contains 'does not provide' docs/LAT_PIPELINE_REPORT_REFINEMENT.md

require_contains 'LATTICRA_LAT_PIPELINE_STAGE_PARSE' include/latticra/lat_pipeline.h
require_contains 'LATTICRA_LAT_PIPELINE_STAGE_SEMANTIC' include/latticra/lat_pipeline.h
require_contains 'LATTICRA_LAT_PIPELINE_STAGE_REPORT' include/latticra/lat_pipeline.h
require_contains 'last_completed_stage' include/latticra/lat_pipeline.h
require_contains 'failed_stage' include/latticra/lat_pipeline.h
require_contains 'no_effect_chain_ok' include/latticra/lat_pipeline.h
require_contains 'evidence_level' include/latticra/lat_pipeline.h
require_contains 'latticra_lat_pipeline_stage_label' include/latticra/lat_pipeline.h

require_contains 'latticra_lat_pipeline_stage_label' src/lat_pipeline.c
require_contains 'finalize_pipeline_report_refinement' src/lat_pipeline.c
require_contains 'last_completed_stage=' src/lat_pipeline.c
require_contains 'failed_stage=' src/lat_pipeline.c
require_contains 'no_effect_chain_ok=' src/lat_pipeline.c
require_contains 'evidence_level=' src/lat_pipeline.c

require_contains 'lat_pipeline_report_refinement_labels_are_stable' tests/lat_pipeline_report_refinement.c
require_contains 'lat_pipeline_report_refinement_reports_success_stage_summary' tests/lat_pipeline_report_refinement.c
require_contains 'lat_pipeline_report_refinement_reports_parse_failure_stage' tests/lat_pipeline_report_refinement.c
require_contains 'lat_pipeline_report_refinement_reports_semantic_failure_stage' tests/lat_pipeline_report_refinement.c
require_contains 'lat_pipeline_report_refinement_null_result_sets_unknown_stage' tests/lat_pipeline_report_refinement.c

require_contains 'tests/lat_pipeline_report_refinement.c' scripts/test-lat-pipeline.sh

printf 'lat_pipeline_report_refinement: ok\n'

#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'lat-pipeline-diagnostic-integration-refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lat-pipeline-diagnostic-integration-refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_REFINEMENT.md
require_file include/latticra/lat_pipeline_diagnostics.h
require_file src/lat_pipeline_diagnostics.c
require_file src/lat_pipeline_diagnostics_eval.c
require_file src/lat_pipeline_diagnostics_report.c
require_file tests/lat_pipeline_diagnostic_integration_refinement.c
require_file scripts/test-lat-pipeline.sh
require_file .github/workflows/lat-pipeline-diagnostic-integration-refinement.yml

require_contains 'LATTICRA_LAT_PIPELINE_DIAGNOSTIC_SEMANTIC' include/latticra/lat_pipeline_diagnostics.h
require_contains 'latticra_lat_pipeline_diagnostics_evaluate' include/latticra/lat_pipeline_diagnostics.h
require_contains 'latticra_lat_pipeline_diagnostic_class_label' src/lat_pipeline_diagnostics.c
require_contains 'semantic_diagnostic_count' src/lat_pipeline_diagnostics_eval.c
require_contains 'LAT PIPELINE DIAGNOSTIC REPORT' src/lat_pipeline_diagnostics_report.c
require_contains 'lat_pipeline_diagnostic_integration_reports_semantic_failure' tests/lat_pipeline_diagnostic_integration_refinement.c
require_contains 'src/lat_pipeline_diagnostics_eval.c' scripts/test-lat-pipeline.sh

printf 'lat_pipeline_diagnostic_integration_refinement: ok\n'

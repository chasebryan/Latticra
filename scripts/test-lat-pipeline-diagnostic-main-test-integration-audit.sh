#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'lat-pipeline-diagnostic-main-test-audit: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lat-pipeline-diagnostic-main-test-audit: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/LAT_PIPELINE_DIAGNOSTIC_MAIN_TEST_INTEGRATION_AUDIT.md
require_file scripts/test-lat-pipeline.sh
require_file tests/lat_pipeline_diagnostic_integration_refinement.c
require_file src/lat_pipeline_diagnostics.c
require_file src/lat_pipeline_diagnostics_eval.c
require_file src/lat_pipeline_diagnostics_report.c
require_file src/lat_to_lir_diagnostics.c
require_file .github/workflows/lat-pipeline.yml

require_contains 'src/lat_pipeline_diagnostics.c' scripts/test-lat-pipeline.sh
require_contains 'src/lat_pipeline_diagnostics_eval.c' scripts/test-lat-pipeline.sh
require_contains 'src/lat_pipeline_diagnostics_report.c' scripts/test-lat-pipeline.sh
require_contains 'src/lat_to_lir_diagnostics.c' scripts/test-lat-pipeline.sh
require_contains 'tests/lat_pipeline_diagnostic_integration_refinement.c' scripts/test-lat-pipeline.sh
require_contains 'lat_pipeline_diagnostic_integration_reports_semantic_failure' tests/lat_pipeline_diagnostic_integration_refinement.c
require_contains 'lat_pipeline_diagnostic_integration_reports_model_failure' tests/lat_pipeline_diagnostic_integration_refinement.c
require_contains 'sh scripts/test-lat-pipeline.sh' .github/workflows/lat-pipeline.yml
require_contains 'main Lat pipeline test runner' docs/LAT_PIPELINE_DIAGNOSTIC_MAIN_TEST_INTEGRATION_AUDIT.md

printf 'lat_pipeline_diagnostic_main_test_integration_audit: ok\n'

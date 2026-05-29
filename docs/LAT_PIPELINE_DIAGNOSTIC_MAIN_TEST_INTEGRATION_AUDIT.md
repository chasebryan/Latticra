# Lat Pipeline Diagnostic Main Test Integration Audit

Status: initial audit guard

This record verifies that the Lat pipeline diagnostic integration is covered by the main Lat pipeline test runner, not only by its focused guard.

Audit expectations:

```text
scripts/test-lat-pipeline.sh links src/lat_pipeline_diagnostics.c
scripts/test-lat-pipeline.sh links src/lat_pipeline_diagnostics_eval.c
scripts/test-lat-pipeline.sh links src/lat_pipeline_diagnostics_report.c
scripts/test-lat-pipeline.sh links src/lat_to_lir_diagnostics.c
scripts/test-lat-pipeline.sh compiles tests/lat_pipeline_diagnostic_integration_refinement.c
.github/workflows/lat-pipeline.yml runs scripts/test-lat-pipeline.sh
```

Validation:

```sh
sh scripts/test-lat-pipeline-diagnostic-main-test-integration-audit.sh
sh scripts/test-lat-pipeline.sh
```

Boundary: audit/guard only. No Lat execution is added.

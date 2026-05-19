#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'lir-report-refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lir-report-refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/LIR_REPORT_REFINEMENT.md
require_file include/latticra/lir.h
require_file src/lir.c
require_file src/lat_to_lir.c
require_file tests/lir_report_refinement.c
require_file scripts/test-lir-shape.sh
require_file .github/workflows/lir-report-refinement.yml

require_contains 'report_classification' docs/LIR_REPORT_REFINEMENT.md
require_contains 'shape_kind' docs/LIR_REPORT_REFINEMENT.md
require_contains 'contains_edge_count' docs/LIR_REPORT_REFINEMENT.md
require_contains 'no_effect_chain_ok' docs/LIR_REPORT_REFINEMENT.md
require_contains 'evidence_level' docs/LIR_REPORT_REFINEMENT.md

require_contains 'LATTICRA_LIR_REPORT_MATERIALIZED' include/latticra/lir.h
require_contains 'LATTICRA_LIR_SHAPE_L_UI_CARD_GRAPH' include/latticra/lir.h
require_contains 'latticra_lir_report_classification_label' include/latticra/lir.h
require_contains 'latticra_lir_shape_kind_label' include/latticra/lir.h

require_contains 'finalize_lir_report_refinement' src/lir.c
require_contains 'report_classification=' src/lir.c
require_contains 'shape_kind=' src/lir.c
require_contains 'contains_edge_count=' src/lir.c
require_contains 'finalize_lir_report_refinement' src/lat_to_lir.c

require_contains 'lir_report_refinement_reports_materialized_l_ui_shape' tests/lir_report_refinement.c
require_contains 'tests/lir_report_refinement.c' scripts/test-lir-shape.sh

printf 'lir_report_refinement: ok\n'

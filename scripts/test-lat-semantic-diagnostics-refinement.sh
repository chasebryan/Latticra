#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'lat-semantic-diagnostics-refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lat-semantic-diagnostics-refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/LAT_SEMANTIC_DIAGNOSTICS_REFINEMENT.md
require_file include/latticra/lat_semantic.h
require_file src/lat_semantic.c
require_file tests/lat_semantic_diagnostics_refinement.c
require_file scripts/test-lat-semantic-validation.sh
require_file .github/workflows/lat-semantic-diagnostics-refinement.yml

require_contains 'diagnostic_class' docs/LAT_SEMANTIC_DIAGNOSTICS_REFINEMENT.md
require_contains 'parse_diagnostic_count' docs/LAT_SEMANTIC_DIAGNOSTICS_REFINEMENT.md
require_contains 'first_diagnostic_declaration_index' docs/LAT_SEMANTIC_DIAGNOSTICS_REFINEMENT.md
require_contains 'LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_EFFECT' include/latticra/lat_semantic.h
require_contains 'latticra_lat_semantic_diagnostic_class_label' include/latticra/lat_semantic.h
require_contains 'diagnostic_class_for_error' src/lat_semantic.c
require_contains 'diagnostic_class=' src/lat_semantic.c
require_contains 'lat_semantic_diagnostics_refinement_reports_effect_class' tests/lat_semantic_diagnostics_refinement.c
require_contains 'tests/lat_semantic_diagnostics_refinement.c' scripts/test-lat-semantic-validation.sh

printf 'lat_semantic_diagnostics_refinement: ok\n'

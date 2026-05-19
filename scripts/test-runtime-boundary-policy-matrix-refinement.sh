#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'runtime-boundary-policy-matrix-refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime-boundary-policy-matrix-refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md
require_file include/latticra/runtime_boundary.h
require_file src/runtime_boundary.c
require_file tests/runtime_boundary_policy_matrix_refinement.c
require_file scripts/test-runtime-boundary.sh
require_file .github/workflows/runtime-boundary-policy-matrix-refinement.yml

require_contains 'policy_matrix_cell' docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md
require_contains 'matrix_effect_allowed' docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md
require_contains 'matrix_mode_allowed' docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md
require_contains 'matrix_requires_authority' docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md
require_contains 'matrix_requires_future_gate' docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md

require_contains 'LATTICRA_RUNTIME_BOUNDARY_MATRIX_NO_EFFECT_VALIDATION' include/latticra/runtime_boundary.h
require_contains 'LATTICRA_RUNTIME_BOUNDARY_MATRIX_FUTURE_GATED_OPERATION' include/latticra/runtime_boundary.h
require_contains 'LATTICRA_RUNTIME_BOUNDARY_MATRIX_BLOCKED_EFFECT' include/latticra/runtime_boundary.h
require_contains 'LATTICRA_RUNTIME_BOUNDARY_MATRIX_PREREQUISITE_DENIED' include/latticra/runtime_boundary.h
require_contains 'latticra_runtime_boundary_policy_matrix_cell_label' include/latticra/runtime_boundary.h

require_contains 'finalize_policy_matrix_metadata' src/runtime_boundary.c
require_contains 'policy_matrix_cell=' src/runtime_boundary.c
require_contains 'matrix_requires_future_gate=' src/runtime_boundary.c

require_contains 'runtime_boundary_policy_matrix_reports_validation_cell' tests/runtime_boundary_policy_matrix_refinement.c
require_contains 'runtime_boundary_policy_matrix_reports_invalid_cell' tests/runtime_boundary_policy_matrix_refinement.c

printf 'runtime_boundary_policy_matrix_refinement: ok\n'

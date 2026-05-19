#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'runtime-boundary-domain-matrix-refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime-boundary-domain-matrix-refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file include/latticra/runtime_boundary_domain_matrix.h
require_file src/runtime_boundary_domain_matrix.c
require_file src/runtime_boundary_domain_matrix_eval.c
require_file tests/runtime_boundary_domain_matrix_refinement.c
require_file scripts/test-runtime-boundary.sh
require_file .github/workflows/runtime-boundary-domain-matrix-refinement.yml

require_contains 'LATTICRA_RUNTIME_BOUNDARY_DOMAIN_MATRIX_DECLARATIVE' include/latticra/runtime_boundary_domain_matrix.h
require_contains 'latticra_runtime_boundary_domain_matrix_evaluate' include/latticra/runtime_boundary_domain_matrix.h
require_contains 'latticra_runtime_boundary_domain_matrix_cell_label' src/runtime_boundary_domain_matrix.c
require_contains 'domain_future_gated' src/runtime_boundary_domain_matrix_eval.c
require_contains 'runtime_boundary_domain_matrix_reports_declarative_host_domain' tests/runtime_boundary_domain_matrix_refinement.c
require_contains 'src/runtime_boundary_domain_matrix_eval.c' scripts/test-runtime-boundary.sh

printf 'runtime_boundary_domain_matrix_refinement: ok\n'

#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'rbdm-main-test-audit: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'rbdm-main-test-audit: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_MAIN_TEST_INTEGRATION_AUDIT.md
require_file scripts/test-runtime-boundary.sh
require_file tests/runtime_boundary_domain_matrix_report_integration.c
require_file src/runtime_boundary_domain_matrix_report.c
require_file .github/workflows/runtime-boundary.yml

require_contains 'tests/runtime_boundary_*.c' scripts/test-runtime-boundary.sh
require_contains 'src/runtime_boundary_domain_matrix_report.c' scripts/test-runtime-boundary.sh
require_contains 'src/runtime_boundary_domain_matrix_eval.c' scripts/test-runtime-boundary.sh
require_contains 'runtime_boundary_domain_matrix_report_integration' tests/runtime_boundary_domain_matrix_report_integration.c
require_contains 'latticra_runtime_boundary_domain_matrix_report' tests/runtime_boundary_domain_matrix_report_integration.c
require_contains 'sh scripts/test-runtime-boundary.sh' .github/workflows/runtime-boundary.yml
require_contains 'main runtime-boundary test runner' docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_MAIN_TEST_INTEGRATION_AUDIT.md

printf 'rbdm_main_test_integration_audit: ok\n'

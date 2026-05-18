#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'runtime-boundary-report-refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime-boundary-report-refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_file docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
require_file include/latticra/runtime_boundary.h
require_file src/runtime_boundary.c
require_file tests/runtime_boundary_report_refinement.c
require_file scripts/test-runtime-boundary.sh
require_file .github/workflows/runtime-boundary-report-refinement.yml

require_contains 'Status: initial runtime boundary report refinement implementation' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_contains 'report_classification' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_contains 'boundary_domain' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_contains 'authorization_state' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_contains 'evidence_level' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_contains 'declarative' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_contains 'boundary-seeking' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_contains 'reserved-for-future' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
require_contains 'does not provide' docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md

require_contains 'LATTICRA_RUNTIME_BOUNDARY_REPORT_DECLARATIVE' include/latticra/runtime_boundary.h
require_contains 'LATTICRA_RUNTIME_BOUNDARY_REPORT_BOUNDARY_SEEKING' include/latticra/runtime_boundary.h
require_contains 'LATTICRA_RUNTIME_BOUNDARY_DOMAIN_FILESYSTEM' include/latticra/runtime_boundary.h
require_contains 'LATTICRA_RUNTIME_BOUNDARY_AUTH_RESERVED_FOR_FUTURE' include/latticra/runtime_boundary.h
require_contains 'report_classification' include/latticra/runtime_boundary.h
require_contains 'boundary_domain' include/latticra/runtime_boundary.h
require_contains 'authorization_state' include/latticra/runtime_boundary.h
require_contains 'evidence_level' include/latticra/runtime_boundary.h

require_contains 'latticra_runtime_boundary_report_classification_label' src/runtime_boundary.c
require_contains 'latticra_runtime_boundary_domain_label' src/runtime_boundary.c
require_contains 'latticra_runtime_boundary_authorization_state_label' src/runtime_boundary.c
require_contains 'finalize_report_refinement_metadata' src/runtime_boundary.c
require_contains 'report_classification=' src/runtime_boundary.c
require_contains 'boundary_domain=' src/runtime_boundary.c
require_contains 'authorization_state=' src/runtime_boundary.c
require_contains 'evidence_level=' src/runtime_boundary.c

require_contains 'runtime_boundary_report_refinement_classifies_declarative_pipeline' tests/runtime_boundary_report_refinement.c
require_contains 'runtime_boundary_report_refinement_marks_future_gate_boundary_seeking' tests/runtime_boundary_report_refinement.c
require_contains 'runtime_boundary_report_refinement_maps_effect_domains' tests/runtime_boundary_report_refinement.c
require_contains 'runtime_boundary_report_refinement_marks_invalid_unknown_request' tests/runtime_boundary_report_refinement.c
require_contains 'runtime_boundary_report_refinement_marks_denied_prerequisite' tests/runtime_boundary_report_refinement.c

printf 'runtime_boundary_report_refinement: ok\n'

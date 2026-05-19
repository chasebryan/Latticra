#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nucleus-task-report-refinement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nucleus-task-report-refinement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/NUCLEUS_TASK_REPORT_REFINEMENT.md
require_file include/latticra/nucleus_task.h
require_file src/nucleus_task.c
require_file tests/nucleus_task_report_refinement.c
require_file scripts/test-nucleus-task-execution.sh
require_file .github/workflows/nucleus-task-report-refinement.yml

require_contains 'report_classification' docs/NUCLEUS_TASK_REPORT_REFINEMENT.md
require_contains 'task_domain' docs/NUCLEUS_TASK_REPORT_REFINEMENT.md
require_contains 'authorization_state' docs/NUCLEUS_TASK_REPORT_REFINEMENT.md
require_contains 'prerequisites_satisfied' docs/NUCLEUS_TASK_REPORT_REFINEMENT.md
require_contains 'no_effect_chain_ok' docs/NUCLEUS_TASK_REPORT_REFINEMENT.md

require_contains 'LATTICRA_NUCLEUS_TASK_REPORT_ACCEPTED' include/latticra/nucleus_task.h
require_contains 'LATTICRA_NUCLEUS_TASK_DOMAIN_AUTHORITY' include/latticra/nucleus_task.h
require_contains 'LATTICRA_NUCLEUS_TASK_AUTH_CHECKED' include/latticra/nucleus_task.h
require_contains 'report_classification' include/latticra/nucleus_task.h
require_contains 'no_effect_chain_ok' include/latticra/nucleus_task.h

require_contains 'finalize_task_report_refinement' src/nucleus_task.c
require_contains 'report_classification=' src/nucleus_task.c
require_contains 'task_domain=' src/nucleus_task.c
require_contains 'authorization_state=' src/nucleus_task.c

require_contains 'nucleus_task_report_refinement_reports_accepted_state_report' tests/nucleus_task_report_refinement.c
require_contains 'nucleus_task_report_refinement_reports_invalid_request' tests/nucleus_task_report_refinement.c
require_contains 'tests/nucleus_task_report_refinement.c' scripts/test-nucleus-task-execution.sh

printf 'nucleus_task_report_refinement: ok\n'

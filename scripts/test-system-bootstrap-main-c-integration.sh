#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'system bootstrap main C integration: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'system bootstrap main C integration: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file .github/workflows/c.yml
require_file include/latticra/system_bootstrap.h
require_file src/system_bootstrap.c
require_file tests/system_bootstrap.c
require_file scripts/test-system-bootstrap.sh
require_file docs/SYSTEM_BOOTSTRAP_IMPLEMENTATION.md

require_contains 'Run system bootstrap guard' .github/workflows/c.yml
require_contains 'sh scripts/test-system-bootstrap.sh' .github/workflows/c.yml

require_contains 'latticra_system_bootstrap_default_request' include/latticra/system_bootstrap.h
require_contains 'latticra_system_bootstrap_run' include/latticra/system_bootstrap.h
require_contains 'latticra_system_bootstrap_report' include/latticra/system_bootstrap.h
require_contains 'LATTICRA_SYSTEM_BOOTSTRAP_REPORT_MAX' include/latticra/system_bootstrap.h

require_contains 'latticra_system_bootstrap_run' src/system_bootstrap.c
require_contains 'latticra_nucleus_task_classify' src/system_bootstrap.c
require_contains 'latticra_runtime_boundary_classify' src/system_bootstrap.c
require_contains 'LATTICRA SYSTEM BOOTSTRAP REPORT' src/system_bootstrap.c

require_contains 'bootstrap_run_is_no_effect' tests/system_bootstrap.c
require_contains 'bootstrap_report_is_deterministic' tests/system_bootstrap.c
require_contains 'runtime_entry_status=not-entered' tests/system_bootstrap.c
require_contains 'no_effect=1' tests/system_bootstrap.c

require_contains 'src/system_bootstrap.c' scripts/test-system-bootstrap.sh
require_contains 'tests/system_bootstrap.c' scripts/test-system-bootstrap.sh
require_contains 'system_bootstrap: ok' tests/system_bootstrap.c

require_contains 'Status: first system-building implementation slice' docs/SYSTEM_BOOTSTRAP_IMPLEMENTATION.md
require_contains 'compiled no-effect system bootstrap report surface' docs/SYSTEM_BOOTSTRAP_IMPLEMENTATION.md
require_contains 'sh scripts/test-system-bootstrap.sh' docs/SYSTEM_BOOTSTRAP_IMPLEMENTATION.md
require_contains 'does not add' docs/SYSTEM_BOOTSTRAP_IMPLEMENTATION.md

printf 'system_bootstrap_main_c_integration: ok\n'

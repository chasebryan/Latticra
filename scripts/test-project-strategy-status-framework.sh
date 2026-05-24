#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'project strategy/status framework: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'project strategy/status framework: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file .github/FUNDING.yml
require_file STATUS.md
require_file README.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/C_CPP_FOUNDATION_DIRECTION.md
require_file docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_file docs/LANGUAGE_STRATEGY.md
require_file docs/strategy/README.md
require_file docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/status/ANNOUNCEMENTS.md
require_file docs/project_notes/README.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
require_file docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
require_file docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
require_file docs/RUNTIME_BOUNDARY_CONTRACT.md
require_file docs/L_UI_RENDERING_IMPLEMENTATION.md
require_file docs/LIR_SHAPE_IMPLEMENTATION.md
require_file docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
require_file docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md
require_file include/latticra/lat_parser.h
require_file include/latticra/l_ui_renderer.h
require_file include/latticra/nucleus_task.h
require_file src/lat_parser.c
require_file src/l_ui_renderer.c
require_file src/nucleus_task.c
require_file tests/lat_language_grammar_invariants.c
require_file tests/l_ui_rendering_invariants.c
require_file tests/nucleus_task_execution_invariants.c
require_file scripts/test-lat-language-grammar.sh
require_file scripts/test-l-ui-rendering.sh
require_file scripts/test-nucleus-task-execution.sh
require_file scripts/test-lat-specific-lir-refinement.sh

require_contains 'buy_me_a_coffee: Bryforge' .github/FUNDING.yml
require_contains 'https://buymeacoffee.com/Bryforge' README.md
require_contains 'The simulacrum is never what hides the truth.' README.md
require_contains '## What Latticra is' README.md
require_contains '## Current status at a glance' README.md
require_contains '## Design doctrine' README.md
require_contains 'C is the metal.' README.md
require_contains 'C++ is the disciplined structure.' README.md
require_contains 'Latticra is the contract.' README.md
require_contains '## Architecture map' README.md
require_contains '## What exists today' README.md
require_contains '## What Latticra does not claim' README.md
require_contains '## Documentation entry points' README.md
require_contains '## Development philosophy' README.md
require_contains '## Support' README.md
require_contains 'STATUS.md' README.md
require_contains 'docs/status/CURRENT_STATUS.md' README.md
require_contains 'docs/status/ANNOUNCEMENTS.md' README.md
require_contains 'docs/strategy/README.md' README.md
require_contains 'docs/project_notes/README.md' README.md
require_contains 'C_CPP_FOUNDATION_DIRECTION.md' README.md
require_contains 'CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md' README.md
require_contains 'NUCLEUS_TASK_EXECUTION_CONTRACT.md' README.md
require_contains 'NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md' README.md
require_contains 'RUNTIME_BOUNDARY_CONTRACT.md' README.md
require_contains 'L_UI_RENDERING_IMPLEMENTATION.md' README.md
require_contains 'LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md' README.md

require_contains 'Status: public status shortcut' STATUS.md
require_contains 'Overall Latticra system' STATUS.md
require_contains 'C/C++ foundation direction' STATUS.md
require_contains 'Constrained C++ authority layer' STATUS.md
require_contains 'Runtime / operating-system-universe direction' STATUS.md
require_contains 'planning estimates only' STATUS.md
require_contains 'Lat-specific LIR refinement implementation' STATUS.md

require_contains 'Status: active language direction' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C is the metal.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C++ is the disciplined structure.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'Latticra is the contract.' docs/C_CPP_FOUNDATION_DIRECTION.md

require_contains 'Status: constrained C++ authority layer contract' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'C++ is permitted only as a governed authority layer above the C substrate.' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Allowed C++ responsibilities' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Forbidden C++ posture' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md

require_contains 'Status: Nucleus task execution contract' docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
require_contains 'Status: initial implementation contract' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
require_contains 'Status: Runtime boundary contract' docs/RUNTIME_BOUNDARY_CONTRACT.md

require_contains 'Scope: C, constrained C++, Lat, L-UI, LIR, and implementation ordering.' docs/LANGUAGE_STRATEGY.md
require_contains 'C_CPP_FOUNDATION_DIRECTION.md' docs/LANGUAGE_STRATEGY.md

require_contains 'Project operations documents' docs/FOUNDATION_INDEX.md
require_contains '../STATUS.md' docs/FOUNDATION_INDEX.md
require_contains '../SECURITY.md' docs/FOUNDATION_INDEX.md
require_contains 'C_CPP_FOUNDATION_DIRECTION.md' docs/FOUNDATION_INDEX.md
require_contains 'CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'NUCLEUS_TASK_EXECUTION_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'RUNTIME_BOUNDARY_CONTRACT.md' docs/FOUNDATION_INDEX.md

require_contains 'Status: active strategy index' docs/strategy/README.md
require_contains '2026-05-15-2249-cdt-national-security-open-system-strategy.md' docs/strategy/README.md
require_contains 'Status: active strategy record' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'C is the metal.' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md

require_contains 'Status: active status index' docs/status/README.md
require_contains 'CURRENT_STATUS.md' docs/status/README.md
require_contains 'ANNOUNCEMENTS.md' docs/status/README.md
require_contains 'Status: public status record' docs/status/CURRENT_STATUS.md
require_contains 'Status: public announcement log' docs/status/ANNOUNCEMENTS.md

require_contains 'Status: active project notes index' docs/project_notes/README.md
require_contains 'CURRENT_DIRECTION.md' docs/project_notes/README.md
require_contains 'UPCOMING_WORK.md' docs/project_notes/README.md
require_contains 'Status: active project note' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Status: active project note' docs/project_notes/UPCOMING_WORK.md

require_contains 'LATTICRA_LAT_SOURCE_MAX 65536u' include/latticra/lat_parser.h
require_contains 'latticra_lat_parse_result_t' include/latticra/lat_parser.h
require_contains 'latticra_l_ui_render_result_t' include/latticra/l_ui_renderer.h
require_contains 'latticra_nucleus_task_result_t' include/latticra/nucleus_task.h
require_contains 'lat_grammar_accepts_minimal_module' tests/lat_language_grammar_invariants.c
require_contains 'l_ui_rendering_accepts_semantically_valid_l_ui_fixture' tests/l_ui_rendering_invariants.c
require_contains 'nucleus_task_execution_denies_unknown_request' tests/nucleus_task_execution_invariants.c

printf 'project_strategy_status_framework: ok\n'

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
require_file docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md
require_file docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md
require_file docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md
require_file docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md
require_file docs/LIR_SHAPE_CONTRACT.md
require_file docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md
require_file docs/LIR_SHAPE_IMPLEMENTATION.md
require_file docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_file docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_file docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
require_file docs/LAT_SPECIFIC_LIR_REFINEMENT_CONTRACT.md
require_file docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION_PLAN.md
require_file docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md
require_file tests/lat_specific_lir_refinement_invariants.c
require_file scripts/test-lat-specific-lir-refinement.sh
require_file docs/L_UI_RENDERING_CONTRACT.md
require_file docs/L_UI_RENDERING_IMPLEMENTATION_PLAN.md
require_file docs/L_UI_RENDERING_IMPLEMENTATION.md
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
require_file fixtures/lat/minimal_module.lat
require_file scripts/test-c-cpp-foundation-direction.sh
require_file scripts/test-constrained-cpp-authority-layer-contract.sh
require_file scripts/test-l-ui-source-buffer-literal-nul-policy.sh
require_file scripts/test-l-ui-semantic-validation-contract.sh
require_file scripts/test-l-ui-semantic-validation-implementation-plan.sh
require_file scripts/test-l-ui-semantic-validation.sh
require_file scripts/test-lir-shape-contract.sh
require_file scripts/test-lir-shape-implementation-plan.sh
require_file scripts/test-lir-shape.sh
require_file scripts/test-l-ui-rendering-contract.sh
require_file scripts/test-l-ui-rendering-implementation-plan.sh
require_file scripts/test-nucleus-task-execution-contract.sh
require_file scripts/test-nucleus-task-execution-implementation-plan.sh
require_file scripts/test-runtime-boundary-contract.sh
require_file scripts/test-lat-language-grammar-contract.sh
require_file scripts/test-lat-language-grammar-implementation-plan.sh

require_contains 'buy_me_a_coffee: Bryforge' .github/FUNDING.yml
require_contains 'https://buymeacoffee.com/Bryforge' README.md
require_contains '## Motto' README.md
require_contains 'The simulacrum is never what hides the truth.' README.md
require_contains '## Mission' README.md
require_contains '## Direction checkpoint' README.md
require_contains 'C is the metal.' README.md
require_contains 'C++ is the disciplined structure.' README.md
require_contains 'Latticra is the contract.' README.md
require_contains 'This does not mean unrestricted C++.' README.md
require_contains '## Status and strategy' README.md
require_contains '## Support' README.md
require_contains 'STATUS.md' README.md
require_contains 'docs/status/CURRENT_STATUS.md' README.md
require_contains 'docs/status/ANNOUNCEMENTS.md' README.md
require_contains 'docs/strategy/README.md' README.md
require_contains 'docs/project_notes/README.md' README.md
require_contains 'C_CPP_FOUNDATION_DIRECTION.md' README.md
require_contains 'CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md' README.md
require_contains 'NUCLEUS_TASK_EXECUTION_CONTRACT.md' README.md
require_contains 'NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md' README.md
require_contains 'NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md' README.md
require_contains 'RUNTIME_BOUNDARY_CONTRACT.md' README.md
require_contains 'L_UI_RENDERING_IMPLEMENTATION.md' README.md
require_contains 'constrained C/C++ foundation direction' README.md
require_contains 'constrained C++ authority-layer contract' README.md
require_contains 'Nucleus task execution contract' README.md
require_contains 'Nucleus task execution implementation plan' README.md
require_contains 'Nucleus task execution implementation' README.md
require_contains 'Runtime boundary contract' README.md
require_contains 'runtime behavior' README.md
require_contains 'command execution' README.md
require_contains 'L-UI rendering implementation' README.md
require_contains 'literal source-buffer NUL rejection policy enforcement' README.md
require_contains 'semantic validation implementation' README.md
require_contains 'LIR shape implementation' README.md
require_contains 'Lat language grammar implementation' README.md
require_contains 'unrestricted C++ authority' README.md
require_contains 'effect-performing implemented C++ authority layer' README.md
require_contains 'interactive L-UI rendering' README.md
require_contains 'terminal-control L-UI rendering' README.md
require_contains 'LIR execution' README.md
require_contains 'Lat execution' README.md
require_contains 'Lat compiler' README.md
require_contains 'Lat interpreter' README.md
require_contains 'Lat-specific LIR refinement implementation' README.md
require_contains 'LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md' README.md
require_contains 'sh scripts/test-lat-specific-lir-refinement.sh' README.md

require_contains 'Status: public status shortcut' STATUS.md
require_contains 'Overall Latticra system' STATUS.md
require_contains 'Constrained C++ authority layer implementation plan' STATUS.md
require_contains 'L-UI rendering implementation' STATUS.md
require_contains 'Nucleus task execution contract' STATUS.md
require_contains 'Nucleus task execution implementation plan' STATUS.md
require_contains 'Nucleus task execution implementation' STATUS.md
require_contains 'Runtime boundary contract' STATUS.md
require_contains 'Runtime boundary implementation plan' STATUS.md
require_contains 'runtime behavior' STATUS.md
require_contains 'command execution' STATUS.md
require_contains 'planning estimates only' STATUS.md
require_contains '19%' STATUS.md
require_contains '86%' STATUS.md
require_contains '74%' STATUS.md
require_contains '68%' STATUS.md
require_contains '42%' STATUS.md
require_contains '10%' STATUS.md
require_contains '14%' STATUS.md
require_contains '4%' STATUS.md
require_contains 'C/C++ foundation direction' STATUS.md
require_contains 'Constrained C++ authority layer' STATUS.md
require_contains 'effect-performing implemented C++ authority layer' STATUS.md
require_contains '23%' STATUS.md
require_contains '78%' STATUS.md
require_contains '72%' STATUS.md
require_contains '46%' STATUS.md
require_contains '18%' STATUS.md
require_contains 'Lat-specific LIR refinement implementation' STATUS.md

require_contains 'Status: active language direction' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C is the metal.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C++ is the disciplined structure.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'Latticra is the contract.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'A constrained C/C++ foundation for a security-conscious system.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C secure substrate' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C++ governed authority layer' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'Not unrestricted C++' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'sh scripts/test-c-cpp-foundation-direction.sh' docs/C_CPP_FOUNDATION_DIRECTION.md

require_contains 'Status: constrained C++ authority layer contract' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'C++ is permitted only as a governed authority layer above the C substrate.' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Allowed C++ responsibilities' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Forbidden C++ posture' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Ownership policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Allocation policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Exception policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'RTTI and reflection policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Template policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'C ABI boundary policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Effect gate policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Audit policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Validator policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Error/result policy' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'Future implementation gate' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'cpp_authority_layer_preserves_no_effect_flags' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'sh scripts/test-constrained-cpp-authority-layer-contract.sh' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
require_contains 'This document does not implement C++ infrastructure' docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md

require_contains 'Status: Nucleus task execution contract' docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
require_contains 'This document does not implement Nucleus task execution.' docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
require_contains 'First task execution posture' docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
require_contains 'default policy: deny' docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
require_contains 'operator confirmation allowed to override: no' docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
require_contains 'NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md' docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
require_contains 'sh scripts/test-nucleus-task-execution-contract.sh' docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md

require_contains 'Status: implementation planning contract' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
require_contains 'This document does not implement Nucleus task execution.' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
require_contains 'latticra_nucleus_task_request_t' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
require_contains 'latticra_nucleus_task_report' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
require_contains 'Nucleus task execution code may be added only after this plan is merged.' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
require_contains 'sh scripts/test-nucleus-task-execution-implementation-plan.sh' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md

require_contains 'Status: initial implementation contract' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
require_contains 'This slice implements task classification and report generation only.' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
require_contains 'It does not execute tasks.' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
require_contains 'sh scripts/test-nucleus-task-execution.sh' docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md

require_contains 'Status: Runtime boundary contract' docs/RUNTIME_BOUNDARY_CONTRACT.md
require_contains 'This document does not implement a runtime.' docs/RUNTIME_BOUNDARY_CONTRACT.md
require_contains 'runtime implemented? no' docs/RUNTIME_BOUNDARY_CONTRACT.md
require_contains 'command execution allowed: no' docs/RUNTIME_BOUNDARY_CONTRACT.md
require_contains 'RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md' docs/RUNTIME_BOUNDARY_CONTRACT.md
require_contains 'sh scripts/test-runtime-boundary-contract.sh' docs/RUNTIME_BOUNDARY_CONTRACT.md

require_contains 'Scope: C, constrained C++, Lat, L-UI, LIR, and implementation ordering.' docs/LANGUAGE_STRATEGY.md
require_contains 'C_CPP_FOUNDATION_DIRECTION.md' docs/LANGUAGE_STRATEGY.md
require_contains 'C is the metal.' docs/LANGUAGE_STRATEGY.md
require_contains 'C++ is the disciplined structure.' docs/LANGUAGE_STRATEGY.md
require_contains 'Latticra is the contract.' docs/LANGUAGE_STRATEGY.md
require_contains 'This does not mean unrestricted C++.' docs/LANGUAGE_STRATEGY.md
require_contains 'C secure substrate' docs/LANGUAGE_STRATEGY.md
require_contains 'C++ governed authority layer' docs/LANGUAGE_STRATEGY.md
require_contains 'Rust is not the current public foundation direction for Latticra.' docs/LANGUAGE_STRATEGY.md
require_contains 'C and constrained C++ implementations' docs/LANGUAGE_STRATEGY.md

require_contains 'Project operations documents' docs/FOUNDATION_INDEX.md
require_contains '../STATUS.md' docs/FOUNDATION_INDEX.md
require_contains '../SECURITY.md' docs/FOUNDATION_INDEX.md
require_contains 'C_CPP_FOUNDATION_DIRECTION.md' docs/FOUNDATION_INDEX.md
require_contains 'CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'NUCLEUS_TASK_EXECUTION_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md' docs/FOUNDATION_INDEX.md
require_contains 'NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'RUNTIME_BOUNDARY_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'LANGUAGE_STRATEGY.md' docs/FOUNDATION_INDEX.md
require_contains 'project strategy/status framework + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'language naming policy + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'C/C++ foundation direction + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'constrained C++ authority layer contract + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'Nucleus task execution contract + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'Nucleus task execution implementation plan + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'Nucleus task execution implementation + invariants' docs/FOUNDATION_INDEX.md
require_contains 'Runtime boundary contract + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'L-UI semantic validation implementation + invariants' docs/FOUNDATION_INDEX.md
require_contains 'LIR shape implementation + invariants' docs/FOUNDATION_INDEX.md
require_contains 'Lat language grammar implementation + invariants' docs/FOUNDATION_INDEX.md
require_contains 'Constrained C++ authority layer implementation plan' docs/FOUNDATION_INDEX.md
require_contains 'L-UI rendering implementation + invariants' docs/FOUNDATION_INDEX.md

require_contains 'Status: active strategy index' docs/strategy/README.md
require_contains '2026-05-15-2249-cdt-national-security-open-system-strategy.md' docs/strategy/README.md
require_contains 'Strategic planning rules' docs/strategy/README.md
require_contains 'anti-malware and anti-ransomware goals as design targets' docs/strategy/README.md
require_contains 'Quality bar' docs/strategy/README.md

require_contains 'Status: active strategy record' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Last updated: 2026-05-16 16:15 CDT' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Jean Baudrillard' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'national-security-grade discipline' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Direction checkpoint' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'C is the metal.' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'C++ is the disciplined structure.' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Latticra is the contract.' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'constrained C++ authority-layer contract' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Constrained C++ authority layer implementation plan' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'implemented C++ authority layer' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains '19%' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains '74%' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains '14%' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains '4%' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Buy Me a Coffee: Bryforge' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md

require_contains 'Status: active status index' docs/status/README.md
require_contains 'CURRENT_STATUS.md' docs/status/README.md
require_contains 'ANNOUNCEMENTS.md' docs/status/README.md
require_contains 'completion percentages' docs/status/README.md

require_contains 'Status: public status record' docs/status/CURRENT_STATUS.md
require_contains 'Last updated: 2026-05-16 16:15 CDT' docs/status/CURRENT_STATUS.md
require_contains 'governed C++ authority-layer planning' docs/status/CURRENT_STATUS.md
require_contains 'Constrained C++ authority layer contract' docs/status/CURRENT_STATUS.md
require_contains 'Constrained C++ authority layer implementation plan' docs/status/CURRENT_STATUS.md
require_contains 'L-UI rendering implementation' docs/status/CURRENT_STATUS.md
require_contains 'Nucleus task execution contract' docs/status/CURRENT_STATUS.md
require_contains 'Nucleus task execution implementation plan' docs/status/CURRENT_STATUS.md
require_contains 'Nucleus task execution implementation' docs/status/CURRENT_STATUS.md
require_contains 'Runtime boundary contract' docs/status/CURRENT_STATUS.md
require_contains 'Runtime boundary implementation plan' docs/status/CURRENT_STATUS.md
require_contains 'runtime behavior' docs/status/CURRENT_STATUS.md
require_contains 'command execution' docs/status/CURRENT_STATUS.md
require_contains 'effect-performing implemented C++ authority layer' docs/status/CURRENT_STATUS.md
require_contains 'interactive L-UI rendering' docs/status/CURRENT_STATUS.md
require_contains 'terminal-control L-UI rendering' docs/status/CURRENT_STATUS.md
require_contains 'C/C++ foundation direction' docs/status/CURRENT_STATUS.md
require_contains 'Constrained C++ authority layer' docs/status/CURRENT_STATUS.md
require_contains '74%' docs/status/CURRENT_STATUS.md
require_contains '68%' docs/status/CURRENT_STATUS.md
require_contains '42%' docs/status/CURRENT_STATUS.md
require_contains '14%' docs/status/CURRENT_STATUS.md
require_contains '4%' docs/status/CURRENT_STATUS.md
require_contains '23%' docs/status/CURRENT_STATUS.md
require_contains '78%' docs/status/CURRENT_STATUS.md
require_contains '72%' docs/status/CURRENT_STATUS.md
require_contains '46%' docs/status/CURRENT_STATUS.md
require_contains '18%' docs/status/CURRENT_STATUS.md
require_contains 'Lat-specific LIR refinement implementation' docs/status/CURRENT_STATUS.md

require_contains 'Status: public announcement log' docs/status/ANNOUNCEMENTS.md
require_contains '2026-05-16 16:15 CDT' docs/status/ANNOUNCEMENTS.md
require_contains 'Constrained C++ authority layer contract' docs/status/ANNOUNCEMENTS.md
require_contains 'sh scripts/test-constrained-cpp-authority-layer-contract.sh' docs/status/ANNOUNCEMENTS.md
require_contains 'Constrained C++ authority layer implementation plan' docs/status/ANNOUNCEMENTS.md
require_contains 'Non-claims' docs/status/ANNOUNCEMENTS.md
require_contains 'Lat-specific LIR refinement implementation' docs/status/ANNOUNCEMENTS.md
require_contains 'sh scripts/test-lat-specific-lir-refinement.sh' docs/status/ANNOUNCEMENTS.md

require_contains 'Status: active project notes index' docs/project_notes/README.md
require_contains 'CURRENT_DIRECTION.md' docs/project_notes/README.md
require_contains 'UPCOMING_WORK.md' docs/project_notes/README.md
require_contains 'Status: active project note' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Current C++ authority boundary' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Constrained C++ authority layer implementation plan' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'effect-performing C++ authority layer' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Current L-UI rendering boundary' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Current Nucleus task boundary' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Current runtime boundary' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Nucleus task execution implementation plan' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Nucleus task execution implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Runtime boundary implementation plan' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Status: active project note' docs/project_notes/UPCOMING_WORK.md
require_contains 'Recommended next slice' docs/project_notes/UPCOMING_WORK.md
require_contains 'Constrained C++ authority layer implementation plan' docs/project_notes/UPCOMING_WORK.md
require_contains 'L-UI rendering implementation' docs/project_notes/UPCOMING_WORK.md
require_contains 'Nucleus task execution contract' docs/project_notes/UPCOMING_WORK.md
require_contains 'Nucleus task execution implementation plan' docs/project_notes/UPCOMING_WORK.md
require_contains 'Nucleus task execution implementation' docs/project_notes/UPCOMING_WORK.md
require_contains 'Runtime boundary contract' docs/project_notes/UPCOMING_WORK.md
require_contains 'Runtime boundary implementation plan' docs/project_notes/UPCOMING_WORK.md
require_contains 'C/C++ foundation direction' docs/project_notes/UPCOMING_WORK.md
require_contains 'Runtime boundary refinement plan' docs/project_notes/UPCOMING_WORK.md
require_contains 'Lat-specific LIR refinement no-effect' docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: LIR shape contract' docs/LIR_SHAPE_CONTRACT.md
require_contains 'Status: initial implementation contract' docs/LIR_SHAPE_IMPLEMENTATION.md
require_contains 'Lat language grammar contract' docs/LIR_SHAPE_IMPLEMENTATION.md
require_contains 'Status: Lat language grammar contract' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'Lat / Latticra Language' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains '.lat' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'Lat-Core' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'Status: implementation planning contract' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_contains 'latticra_lat_parse_result_t' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_contains 'LATTICRA_LAT_SOURCE_MAX 65536u' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_contains 'Status: initial implementation contract' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
require_contains 'latticra_lat_parse_source' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
require_contains 'Constrained C++ authority layer contract' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md

require_contains 'LATTICRA_LAT_SOURCE_MAX 65536u' include/latticra/lat_parser.h
require_contains 'latticra_lat_parse_result_t' include/latticra/lat_parser.h
require_contains 'latticra_lat_parse_source' include/latticra/lat_parser.h
require_contains 'LATTICRA_LIR_NODE_LAT_STATE' include/latticra/lir.h
require_contains 'LATTICRA_LIR_EDGE_TRANSITIONS_FROM' include/latticra/lir.h
require_contains 'latticra_l_ui_render_result_t' include/latticra/l_ui_renderer.h
require_contains 'latticra_l_ui_render_report' include/latticra/l_ui_renderer.h
require_contains 'latticra_nucleus_task_result_t' include/latticra/nucleus_task.h
require_contains 'latticra_nucleus_task_report' include/latticra/nucleus_task.h
require_contains 'LAT GRAMMAR REPORT' src/lat_parser.c
require_contains 'LATTICRA L-UI RENDER REPORT' src/l_ui_renderer.c
require_contains 'LATTICRA NUCLEUS TASK REPORT' src/nucleus_task.c
require_contains 'lat_grammar_accepts_minimal_module' tests/lat_language_grammar_invariants.c
require_contains 'lat_specific_lir_uses_lat_declaration_node_kinds' tests/lat_specific_lir_refinement_invariants.c
require_contains 'l_ui_rendering_accepts_semantically_valid_l_ui_fixture' tests/l_ui_rendering_invariants.c
require_contains 'nucleus_task_execution_denies_unknown_request' tests/nucleus_task_execution_invariants.c
require_contains 'lat module RootModule' fixtures/lat/minimal_module.lat
require_contains 'Run constrained C++ authority layer contract guard' .github/workflows/c.yml
require_contains 'Run L-UI rendering tests' .github/workflows/c.yml
require_contains 'Run Nucleus task execution contract guard' .github/workflows/c.yml
require_contains 'Run Nucleus task execution implementation plan guard' .github/workflows/c.yml
require_contains 'Run Nucleus task execution tests' .github/workflows/c.yml
require_contains 'Run runtime boundary contract guard' .github/workflows/c.yml

printf 'project_strategy_status_framework: ok\n'

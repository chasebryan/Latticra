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
require_file docs/FOUNDATION_INDEX.md
require_file docs/C_CPP_FOUNDATION_DIRECTION.md
require_file docs/LANGUAGE_STRATEGY.md
require_file docs/strategy/README.md
require_file docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/status/ANNOUNCEMENTS.md
require_file docs/project_notes/README.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md
require_file docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md
require_file docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md
require_file docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md
require_file docs/LIR_SHAPE_CONTRACT.md
require_file docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md
require_file docs/LIR_SHAPE_IMPLEMENTATION.md
require_file docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_file docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_file scripts/test-c-cpp-foundation-direction.sh
require_file scripts/test-l-ui-source-buffer-literal-nul-policy.sh
require_file scripts/test-l-ui-semantic-validation-contract.sh
require_file scripts/test-l-ui-semantic-validation-implementation-plan.sh
require_file scripts/test-l-ui-semantic-validation.sh
require_file scripts/test-lir-shape-contract.sh
require_file scripts/test-lir-shape-implementation-plan.sh
require_file scripts/test-lir-shape.sh
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
require_contains 'constrained C/C++ foundation direction' README.md
require_contains 'literal source-buffer NUL rejection policy enforcement' README.md
require_contains 'semantic validation implementation' README.md
require_contains 'LIR shape implementation' README.md
require_contains 'Lat language grammar contract' README.md
require_contains 'Lat language grammar implementation plan' README.md
require_contains 'unrestricted C++ authority' README.md
require_contains 'LIR execution' README.md
require_contains 'Lat parser implementation' README.md
require_contains 'Lat grammar implementation' README.md

require_contains 'Status: public status shortcut' STATUS.md
require_contains 'Overall Latticra system' STATUS.md
require_contains 'Lat language grammar implementation' STATUS.md
require_contains 'planning estimates only' STATUS.md
require_contains '18%' STATUS.md
require_contains '86%' STATUS.md
require_contains '73%' STATUS.md
require_contains '67%' STATUS.md
require_contains '41%' STATUS.md
require_contains '7%' STATUS.md
require_contains '10%' STATUS.md
require_contains '12%' STATUS.md
require_contains 'C/C++ foundation direction' STATUS.md
require_contains 'C is the metal.' STATUS.md
require_contains 'C++ is the disciplined structure.' STATUS.md
require_contains 'Latticra is the contract.' STATUS.md
require_contains 'unrestricted C++ authority' STATUS.md

require_contains 'Status: active language direction' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C is the metal.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C++ is the disciplined structure.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'Latticra is the contract.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'A constrained C/C++ foundation for a security-conscious system.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C secure substrate' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'C++ governed authority layer' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'Not unrestricted C++' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'Rust is not the current public foundation direction for Latticra.' docs/C_CPP_FOUNDATION_DIRECTION.md
require_contains 'sh scripts/test-c-cpp-foundation-direction.sh' docs/C_CPP_FOUNDATION_DIRECTION.md

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
require_contains 'LANGUAGE_STRATEGY.md' docs/FOUNDATION_INDEX.md
require_contains 'strategy/README.md' docs/FOUNDATION_INDEX.md
require_contains 'strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md' docs/FOUNDATION_INDEX.md
require_contains 'status/CURRENT_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'status/ANNOUNCEMENTS.md' docs/FOUNDATION_INDEX.md
require_contains 'project_notes/CURRENT_DIRECTION.md' docs/FOUNDATION_INDEX.md
require_contains 'project_notes/UPCOMING_WORK.md' docs/FOUNDATION_INDEX.md
require_contains 'project strategy/status framework + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'language naming policy + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'C/C++ foundation direction + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'L-UI semantic validation implementation + invariants' docs/FOUNDATION_INDEX.md
require_contains 'LIR shape implementation + invariants' docs/FOUNDATION_INDEX.md
require_contains 'Lat language grammar contract + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'Lat language grammar implementation plan + guardrails' docs/FOUNDATION_INDEX.md
require_contains 'Lat language grammar implementation' docs/FOUNDATION_INDEX.md

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
require_contains 'This is a constrained C/C++ foundation direction.' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'constrained C/C++ substrate and authority layers' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'explicit trust boundaries' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'constrained C substrate behavior' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'governed C++ authority-layer planning' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'C/C++ foundation direction' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains '73%' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains '7%' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains '12%' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Lat language grammar implementation' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'unrestricted C++ authority' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Buy Me a Coffee: Bryforge' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md

require_contains 'Status: active status index' docs/status/README.md
require_contains 'CURRENT_STATUS.md' docs/status/README.md
require_contains 'ANNOUNCEMENTS.md' docs/status/README.md
require_contains 'completion percentages' docs/status/README.md

require_contains 'Status: public status record' docs/status/CURRENT_STATUS.md
require_contains 'Last updated: 2026-05-16 16:15 CDT' docs/status/CURRENT_STATUS.md
require_contains 'constrained C/C++ foundation direction' docs/status/CURRENT_STATUS.md
require_contains 'Direction checkpoint' docs/status/CURRENT_STATUS.md
require_contains 'C is the metal.' docs/status/CURRENT_STATUS.md
require_contains 'C++ is the disciplined structure.' docs/status/CURRENT_STATUS.md
require_contains 'Latticra is the contract.' docs/status/CURRENT_STATUS.md
require_contains 'C/C++ foundation direction' docs/status/CURRENT_STATUS.md
require_contains '12%' docs/status/CURRENT_STATUS.md
require_contains '73%' docs/status/CURRENT_STATUS.md
require_contains '67%' docs/status/CURRENT_STATUS.md
require_contains '41%' docs/status/CURRENT_STATUS.md
require_contains 'Lat / Latticra Programming Language' docs/status/CURRENT_STATUS.md
require_contains '7%' docs/status/CURRENT_STATUS.md
require_contains 'Lat language grammar implementation plan' docs/status/CURRENT_STATUS.md
require_contains 'Lat language grammar implementation' docs/status/CURRENT_STATUS.md
require_contains 'unrestricted C++ authority' docs/status/CURRENT_STATUS.md

require_contains 'Status: public announcement log' docs/status/ANNOUNCEMENTS.md
require_contains '2026-05-16 16:15 CDT' docs/status/ANNOUNCEMENTS.md
require_contains 'C/C++ foundation direction' docs/status/ANNOUNCEMENTS.md
require_contains 'Lat grammar implementation plan' docs/status/ANNOUNCEMENTS.md
require_contains 'sh scripts/test-lat-language-grammar-implementation-plan.sh' docs/status/ANNOUNCEMENTS.md
require_contains 'Lat language grammar implementation' docs/status/ANNOUNCEMENTS.md
require_contains 'Non-claims' docs/status/ANNOUNCEMENTS.md

require_contains 'Status: active project notes index' docs/project_notes/README.md
require_contains 'CURRENT_DIRECTION.md' docs/project_notes/README.md
require_contains 'UPCOMING_WORK.md' docs/project_notes/README.md
require_contains 'Status: active project note' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Last updated: 2026-05-16 16:15 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'C/C++ foundation checkpoint' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Lat grammar implementation plan' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'bounded Lat parser implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'unrestricted C++ authority' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Status: active project note' docs/project_notes/UPCOMING_WORK.md
require_contains 'Last updated: 2026-05-16 16:15 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'Recommended next slice' docs/project_notes/UPCOMING_WORK.md
require_contains 'Lat language grammar implementation' docs/project_notes/UPCOMING_WORK.md
require_contains 'Constrained C++ authority layer contract' docs/project_notes/UPCOMING_WORK.md
require_contains 'C/C++ foundation direction' docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: LIR shape contract' docs/LIR_SHAPE_CONTRACT.md
require_contains 'Status: initial implementation contract' docs/LIR_SHAPE_IMPLEMENTATION.md
require_contains 'Lat language grammar contract' docs/LIR_SHAPE_IMPLEMENTATION.md
require_contains 'Status: Lat language grammar contract' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'Lat / Latticra Language' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains '.lat' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'Lat-Core' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'Lat language grammar implementation plan' docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
require_contains 'Status: implementation planning contract' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_contains 'latticra_lat_parse_result_t' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_contains 'LATTICRA_LAT_SOURCE_MAX 65536u' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_contains 'fixtures/lat/minimal_module.lat' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
require_contains 'lat_grammar_accepts_minimal_module' docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md

printf 'project_strategy_status_framework: ok\n'

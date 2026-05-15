#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq "$pattern" "$file"; then
    printf 'l-ui parser implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'The first parser should be implemented in C.' "$doc"
require_contains 'include/latticra/l_ui_parser.h' "$doc"
require_contains 'src/l_ui_parser.c' "$doc"
require_contains 'tests/l_ui_parser_invariants.c' "$doc"
require_contains 'scripts/test-l-ui-parser.sh' "$doc"
require_contains 'LATTICRA_L_UI_SOURCE_MAX = 65536' "$doc"
require_contains 'Parse result shape' "$doc"
require_contains 'Public API plan' "$doc"
require_contains 'Exact test list for first parser PR' "$doc"
require_contains 'Parser approach' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'CI requirement' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for error in \
  LATTICRA_L_UI_PARSE_OK \
  LATTICRA_L_UI_PARSE_NULL_ARGUMENT \
  LATTICRA_L_UI_PARSE_EMPTY_SOURCE \
  LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION \
  LATTICRA_L_UI_PARSE_MISSING_CARD \
  LATTICRA_L_UI_PARSE_MISSING_PURPOSE \
  LATTICRA_L_UI_PARSE_MISSING_EFFECT \
  LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT \
  LATTICRA_L_UI_PARSE_MISSING_BOUNDARY \
  LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY \
  LATTICRA_L_UI_PARSE_MISSING_RAIL \
  LATTICRA_L_UI_PARSE_UNKNOWN_RAIL \
  LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX \
  LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING \
  LATTICRA_L_UI_PARSE_UNTERMINATED_STRING \
  LATTICRA_L_UI_PARSE_UNBALANCED_BRACE \
  LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER \
  LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE \
  LATTICRA_L_UI_PARSE_INTERNAL_ERROR
do
  require_contains "$error" "$doc"
done

for test_name in \
  valid_fixture_parses_successfully \
  null_source_is_rejected \
  null_result_is_rejected \
  empty_source_is_rejected \
  oversized_source_is_rejected \
  unsupported_version_is_rejected \
  missing_card_is_rejected \
  missing_purpose_is_rejected \
  missing_effect_is_rejected \
  unsupported_effect_is_rejected \
  missing_boundary_is_rejected \
  unsupported_boundary_is_rejected \
  missing_required_rail_is_rejected \
  missing_required_binding_is_rejected \
  unknown_binding_prefix_is_rejected \
  forbidden_behavior_marker_is_rejected \
  valid_parse_returns_no_effect_flags \
  error_results_preserve_no_execution_flags \
  parse_error_labels_are_stable
do
  require_contains "$test_name" "$doc"
done

for flag in \
  'no_effect=1' \
  'execution_allowed=0' \
  'mutation_allowed=0' \
  'server_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0'
do
  require_contains "$flag" "$doc"
done

for forbidden in \
  'read files directly' \
  'write files' \
  'open sockets' \
  'call server code' \
  'call update code' \
  'call recovery code' \
  'call hardware code' \
  'mutate state lattice' \
  'perform live movement' \
  'execute L-UI source' \
  'render UI' \
  'use unbounded allocation' \
  'accept unsupported effects'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_parser_implementation_plan: ok\n'

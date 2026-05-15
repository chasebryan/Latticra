#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq "$pattern" "$file"; then
    printf 'l-ui parser line-column precision implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser line-column precision implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'The precision implementation should be in C.' "$doc"
require_contains 'Proposed module touch points' "$doc"
require_contains 'Public API rule' "$doc"
require_contains 'Internal helper shapes' "$doc"
require_contains 'Newline scanner behavior' "$doc"
require_contains 'Parser touch-point plan' "$doc"
require_contains 'Error location mapping' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for helper in \
  'location_default' \
  'find_slice_location' \
  'find_unbalanced_brace_location' \
  'find_unterminated_string_location' \
  'set_error_at'
do
  require_contains "$helper" "$doc"
done

for touch_point in \
  'src/l_ui_parser.c' \
  'tests/l_ui_parser_location_invariants.c' \
  'scripts/test-l-ui-parser-location.sh' \
  '.github/workflows/c.yml'
do
  require_contains "$touch_point" "$doc"
done

for newline_rule in \
  'LF:' \
  'CRLF:' \
  'CR:' \
  'Line and column are one-based.' \
  'Columns are byte-based' \
  'host text mode'
do
  require_contains "$newline_rule" "$doc"
done

for error_name in \
  unsupported_version \
  unsupported_effect \
  unsupported_boundary \
  unknown_binding_prefix \
  forbidden_behavior_marker \
  unterminated_string \
  unbalanced_brace \
  missing_effect \
  missing_boundary \
  missing_rail
do
  require_contains "$error_name" "$doc"
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

for test_name in \
  unsupported_version_reports_precise_location \
  unsupported_effect_reports_effect_token_location \
  unsupported_boundary_reports_boundary_token_location \
  unknown_binding_prefix_reports_binding_target_location \
  forbidden_marker_reports_marker_location \
  unterminated_string_reports_opening_quote_location \
  unbalanced_open_brace_reports_opening_brace_location \
  unbalanced_close_brace_reports_closing_brace_location \
  missing_effect_reports_card_body_location \
  missing_boundary_reports_card_body_location \
  missing_rail_reports_card_body_location \
  location_scanner_handles_lf_newlines \
  location_scanner_handles_crlf_newlines \
  location_scanner_handles_cr_newlines \
  location_columns_are_byte_based \
  success_result_remains_line_one_column_one \
  error_locations_preserve_no_effect_flags \
  location_reports_are_deterministic
do
  require_contains "$test_name" "$doc"
done

for forbidden in \
  'add file I/O to parser code' \
  'write files' \
  'open network connections' \
  'call server code' \
  'call update code' \
  'call recovery code' \
  'call hardware code' \
  'mutate state lattice' \
  'perform live movement' \
  'run L-UI behavior' \
  'render an interactive UI' \
  'change diagnostic report shape' \
  'accept unsupported effects'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_parser_line_column_precision_implementation_plan: ok\n'

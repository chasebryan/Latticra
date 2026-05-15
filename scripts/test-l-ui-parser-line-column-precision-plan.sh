#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_LINE_COLUMN_PRECISION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq "$pattern" "$file"; then
    printf 'l-ui parser line-column precision plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser line-column precision plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: precision planning contract' "$doc"
require_contains 'This plan does not implement precise location tracking.' "$doc"
require_contains 'Line and column must be one-based.' "$doc"
require_contains 'Columns count bytes in the in-memory source buffer' "$doc"
require_contains 'Newline policy' "$doc"
require_contains 'Source scanning helper plan' "$doc"
require_contains 'Parse result behavior' "$doc"
require_contains 'Error location plan' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Exact future test list' "$doc"
require_contains 'Diagnostic report impact' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for newline_rule in \
  '\n' \
  '\r\n' \
  '\r' \
  'counts as one newline' \
  'Other bytes increment column by 1.' \
  'host platform text mode'
do
  require_contains "$newline_rule" "$doc"
done

for helper in \
  'find_slice_location' \
  'find_unbalanced_brace_location' \
  'find_unterminated_string_location'
do
  require_contains "$helper" "$doc"
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

for error_name in \
  ok \
  null_argument \
  empty_source \
  unsupported_version \
  missing_card \
  missing_purpose \
  missing_effect \
  unsupported_effect \
  missing_boundary \
  unsupported_boundary \
  missing_rail \
  unknown_rail \
  unknown_binding_prefix \
  missing_required_binding \
  unterminated_string \
  unbalanced_brace \
  forbidden_behavior_marker \
  source_too_large \
  internal_error
do
  require_contains "$error_name" "$doc"
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

printf 'l_ui_parser_line_column_precision_plan: ok\n'

#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui parser source-span implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser source-span implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'The source-span implementation should be in C.' "$doc"
require_contains 'Public API change' "$doc"
require_contains 'Parse result integration' "$doc"
require_contains 'Diagnostic integration' "$doc"
require_contains 'Report format changes' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Internal helper plan' "$doc"
require_contains 'Span defaults' "$doc"
require_contains 'Span calculation rules' "$doc"
require_contains 'Initial span targets' "$doc"
require_contains 'Span mapping plan' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for field in \
  start_offset \
  end_offset \
  start_line \
  start_column \
  end_line \
  end_column \
  latticra_l_ui_source_span_t \
  'latticra_l_ui_parse_result_t' \
  'latticra_l_ui_diagnostic_t'
do
  require_contains "$field" "$doc"
done

for report_field in \
  'span_start_offset=<n>' \
  'span_end_offset=<n>' \
  'span_start_line=<n>' \
  'span_start_column=<n>' \
  'span_end_line=<n>' \
  'span_end_column=<n>'
do
  require_contains "$report_field" "$doc"
done

for helper in \
  span_default \
  span_for_range \
  find_slice_span \
  find_unterminated_string_span \
  find_unbalanced_brace_span \
  set_error_with_span
do
  require_contains "$helper" "$doc"
done

for target in \
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
  require_contains "$target" "$doc"
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
  unsupported_effect_reports_effect_span \
  unsupported_boundary_reports_boundary_span \
  unknown_binding_prefix_reports_binding_span \
  forbidden_marker_reports_marker_span \
  unterminated_string_reports_string_span \
  unbalanced_open_brace_reports_brace_span \
  unbalanced_close_brace_reports_brace_span \
  missing_effect_reports_empty_card_body_span \
  missing_boundary_reports_empty_card_body_span \
  missing_rail_reports_empty_card_body_span \
  span_offsets_are_zero_based \
  span_end_offset_is_exclusive \
  span_line_columns_are_one_based \
  span_columns_are_byte_based \
  span_scanner_handles_lf_newlines \
  span_scanner_handles_crlf_newlines \
  span_scanner_handles_cr_newlines \
  span_metadata_preserves_no_effect_flags \
  span_reports_are_deterministic \
  parse_result_report_includes_span_fields \
  diagnostic_report_includes_span_fields \
  diagnostic_copies_parse_result_span \
  success_span_uses_default_empty_span
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_parser_source_span_invariants.c \
  scripts/test-l-ui-parser-source-span.sh \
  docs/L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md \
  .github/workflows/c.yml
do
  require_contains "$path" "$doc"
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
  'accept unsupported effects'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_parser_source_span_implementation_plan: ok\n'

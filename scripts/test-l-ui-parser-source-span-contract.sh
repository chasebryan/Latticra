#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_SOURCE_SPAN_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui parser source-span contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser source-span contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: source-span contract' "$doc"
require_contains 'This document does not implement source spans.' "$doc"
require_contains 'Source unit rules' "$doc"
require_contains 'Line and column range rules' "$doc"
require_contains 'Newline policy' "$doc"
require_contains 'Proposed span struct' "$doc"
require_contains 'Parse result integration' "$doc"
require_contains 'Diagnostic integration' "$doc"
require_contains 'Initial span targets' "$doc"
require_contains 'Span target behavior' "$doc"
require_contains 'Empty span rule' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for field in \
  start_offset \
  end_offset \
  start_line \
  start_column \
  end_line \
  end_column
do
  require_contains "$field" "$doc"
done

for rule in \
  '`start_offset` is zero-based' \
  '`end_offset` is zero-based and exclusive' \
  '`start_offset <= end_offset`' \
  'Line and column are one-based.' \
  'Columns are byte-based' \
  'host text mode' \
  'Empty spans are allowed only for missing constructs.'
do
  require_contains "$rule" "$doc"
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
  span_reports_are_deterministic
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
  'accept unsupported effects'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_parser_source_span_contract: ok\n'

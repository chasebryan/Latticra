#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_DIAGNOSTICS.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq "$pattern" "$file"; then
    printf 'l-ui parser diagnostics contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser diagnostics contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: diagnostics contract' "$doc"
require_contains 'This document does not implement new diagnostics.' "$doc"
require_contains 'Diagnostic shape' "$doc"
require_contains 'Severity levels' "$doc"
require_contains 'Stable diagnostic codes' "$doc"
require_contains 'Stable messages' "$doc"
require_contains 'Line and column behavior' "$doc"
require_contains 'Hint language' "$doc"
require_contains 'Report integration' "$doc"
require_contains 'Required test plan for future diagnostics implementation' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for code in \
  'LUI0000 ok' \
  'LUI0001 null_argument' \
  'LUI0002 empty_source' \
  'LUI0003 unsupported_version' \
  'LUI0004 missing_card' \
  'LUI0005 missing_purpose' \
  'LUI0006 missing_effect' \
  'LUI0007 unsupported_effect' \
  'LUI0008 missing_boundary' \
  'LUI0009 unsupported_boundary' \
  'LUI0010 missing_rail' \
  'LUI0011 unknown_rail' \
  'LUI0012 unknown_binding_prefix' \
  'LUI0013 missing_required_binding' \
  'LUI0014 unterminated_string' \
  'LUI0015 unbalanced_brace' \
  'LUI0016 forbidden_behavior_marker' \
  'LUI0017 source_too_large' \
  'LUI0018 internal_error'
do
  require_contains "$code" "$doc"
done

for message in \
  'Parse completed successfully.' \
  'Parser received a null argument.' \
  'L-UI source is empty.' \
  'L-UI version is not supported.' \
  'Required card declaration is missing.' \
  'Required purpose clause is missing.' \
  'Required effect clause is missing.' \
  'Effect declaration is not supported.' \
  'Required boundary clause is missing.' \
  'Boundary declaration is not supported.' \
  'Required rail is missing.' \
  'Rail name is not supported.' \
  'Binding prefix is not supported.' \
  'Required binding is missing.' \
  'String literal is not terminated.' \
  'Braces are not balanced.' \
  'Source contains a forbidden behavior marker.' \
  'Source exceeds the supported size limit.' \
  'Parser reached an internal error.'
do
  require_contains "$message" "$doc"
done

for rule in \
  'line=1' \
  'column=1' \
  'Line and column should be one-based.' \
  'Diagnostics must preserve no-effect flags.' \
  'diagnostic_severity=<severity>' \
  'diagnostic_code=<code>' \
  'diagnostic_message=<message>' \
  'diagnostic_hint=<hint-or-empty>'
do
  require_contains "$rule" "$doc"
done

for test_name in \
  ok_result_has_lui0000 \
  empty_source_reports_lui0002 \
  unsupported_version_reports_lui0003 \
  missing_card_reports_lui0004 \
  missing_purpose_reports_lui0005 \
  missing_effect_reports_lui0006 \
  unsupported_effect_reports_lui0007 \
  missing_boundary_reports_lui0008 \
  unsupported_boundary_reports_lui0009 \
  missing_rail_reports_lui0010 \
  unknown_binding_prefix_reports_lui0012 \
  missing_required_binding_reports_lui0013 \
  unterminated_string_reports_lui0014 \
  unbalanced_brace_reports_lui0015 \
  forbidden_marker_reports_lui0016 \
  source_too_large_reports_lui0017 \
  error_diagnostics_preserve_no_effect_flags \
  unknown_error_reports_internal \
  line_and_column_are_one_based \
  messages_are_stable
do
  require_contains "$test_name" "$doc"
done

printf 'l_ui_parser_diagnostics_contract: ok\n'

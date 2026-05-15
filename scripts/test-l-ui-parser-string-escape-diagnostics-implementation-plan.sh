#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui parser string escape diagnostics implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser string escape diagnostics implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'Parser-level string escape diagnostics should be implemented in C.' "$doc"
require_contains 'Public API decision' "$doc"
require_contains 'Parse error label decision' "$doc"
require_contains 'Diagnostic mapping decision' "$doc"
require_contains 'Stable messages' "$doc"
require_contains 'Stable hints' "$doc"
require_contains 'Parser helper plan' "$doc"
require_contains 'Validation targets' "$doc"
require_contains 'Validation order' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Capacity behavior' "$doc"
require_contains 'NUL behavior' "$doc"
require_contains 'AST compatibility behavior' "$doc"
require_contains 'Report compatibility behavior' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_CONTRACT.md \
  docs/L_UI_PARSER_DIAGNOSTICS.md \
  docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md \
  docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c
do
  require_contains "$related" "$doc"
done

for parser_error in \
  'LATTICRA_L_UI_PARSE_INTERNAL_ERROR = 18' \
  'LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE = 19' \
  'LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE = 20' \
  'LATTICRA_L_UI_PARSE_UNTERMINATED_ESCAPE = 21' \
  'LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING = 22' \
  'LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING = 23' \
  'LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE = 24'
do
  require_contains "$parser_error" "$doc"
done

for label in \
  invalid_string_escape \
  invalid_hex_escape \
  unterminated_escape \
  decoded_nul_in_string \
  literal_nul_in_string \
  string_value_too_large
do
  require_contains "$label" "$doc"
done

for diagnostic_code in \
  'LUI0019 invalid_string_escape' \
  'LUI0020 invalid_hex_escape' \
  'LUI0021 unterminated_escape' \
  'LUI0022 decoded_nul_in_string' \
  'LUI0023 literal_nul_in_string' \
  'LUI0024 string_value_too_large'
do
  require_contains "$diagnostic_code" "$doc"
done

for message in \
  'LUI0019: String literal escape is not supported.' \
  'LUI0020: Hex string escape must use exactly two uppercase hexadecimal digits.' \
  'LUI0021: String literal escape is not terminated.' \
  'LUI0022: Decoded NUL bytes are not supported in AST strings.' \
  'LUI0023: Literal NUL bytes are not supported in AST strings.' \
  'LUI0024: Decoded string value exceeds the supported AST storage limit.'
do
  require_contains "$message" "$doc"
done

for hint in \
  'LUI0019: Use only' \
  'LUI0020: Use exactly two uppercase hex digits, such as \x0A or \x7F.' \
  'LUI0021: Complete the escape sequence or remove the trailing backslash.' \
  'LUI0022: Avoid \x00 until length-carrying AST strings exist.' \
  'LUI0023: Remove literal NUL bytes from the source string.' \
  'LUI0024: Shorten the decoded purpose or text value.'
do
  require_contains "$hint" "$doc"
done

for helper in \
  is_upper_hex_digit \
  upper_hex_value \
  validate_string_literal_escape_span \
  validate_l_ui_string_literal_escapes \
  latticra_l_ui_parse_source \
  latticra_l_ui_diagnostic_from_parse_result \
  latticra_l_ui_diagnostic_report
do
  require_contains "$helper" "$doc"
done

for target in \
  'purpose "..."' \
  'first text "..."' \
  'second text "..."' \
  'card names' \
  'rail names' \
  'field names' \
  'binding values' \
  'effect values' \
  'boundary values'
do
  require_contains "$target" "$doc"
done

for order_item in \
  'null argument check' \
  'empty source check' \
  'source size check' \
  'unterminated string check' \
  'unbalanced brace check' \
  'version check' \
  'card check' \
  'purpose presence check' \
  'effect presence and supported effect checks' \
  'boundary presence and supported boundary checks' \
  'forbidden behavior marker check' \
  'required rail checks' \
  'unknown binding prefix check' \
  'required binding checks'
do
  require_contains "$order_item" "$doc"
done

for span_rule in \
  '\a      -> span covers \a' \
  '\x0a    -> span covers \x0a' \
  '\xGG    -> span covers \xGG' \
  '\       -> span covers the trailing backslash' \
  '\x      -> span covers \x' \
  '\x0     -> span covers \x0' \
  '\x00    -> span covers \x00' \
  'literal NUL -> span covers the literal NUL source byte' \
  'oversized decoded output -> span covers the full source value range between quotes' \
  'Line and column should point to the first byte of the rejected span.'
do
  require_contains "$span_rule" "$doc"
done

for behavior in \
  LATTICRA_L_UI_AST_PURPOSE_MAX \
  LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE \
  LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING \
  LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING \
  'ast.parse_result.error = parser-level string escape error' \
  'failed-parse detailed report only' \
  'Accepted escapes must continue to decode in AST values exactly as the current string-literal escape implementation defines.'
do
  require_contains "$behavior" "$doc"
done

for compat in \
  'accepted string-literal escape decoding' \
  'existing diagnostic codes LUI0000 through LUI0018' \
  'existing parser error labels for current errors' \
  'latticra_l_ui_ast_report existing required fields' \
  'latticra_l_ui_ast_detailed_report existing required fields for accepted sources' \
  'latticra_l_ui_diagnostic_report existing required fields' \
  'existing accepted fixture summary counts'
do
  require_contains "$compat" "$doc"
done

for count in \
  'rail_count=9' \
  'field_count=23' \
  'text_count=2' \
  'effect=none' \
  'boundary=preview_only'
do
  require_contains "$count" "$doc"
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
  string_escape_diagnostic_rejects_unknown_escape_lui0019 \
  string_escape_diagnostic_rejects_lowercase_hex_lui0020 \
  string_escape_diagnostic_rejects_short_hex_lui0020 \
  string_escape_diagnostic_rejects_invalid_hex_lui0020 \
  string_escape_diagnostic_rejects_unterminated_escape_lui0021 \
  string_escape_diagnostic_rejects_decoded_nul_lui0022 \
  string_escape_diagnostic_rejects_literal_nul_lui0023 \
  string_escape_diagnostic_rejects_oversized_decoded_output_lui0024 \
  string_escape_diagnostic_reports_source_span \
  string_escape_diagnostic_reports_line_column \
  string_escape_diagnostic_preserves_no_effect_flags \
  string_escape_diagnostic_does_not_change_accepted_escape_decoding \
  string_escape_diagnostic_does_not_change_existing_error_codes \
  string_escape_diagnostic_uses_failed_parse_ast_report \
  string_escape_diagnostic_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_parser_string_escape_diagnostics_invariants.c \
  scripts/test-l-ui-parser-string-escape-diagnostics.sh \
  docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md \
  .github/workflows/c.yml
do
  require_contains "$path" "$doc"
done

for forbidden in \
  'add file I/O to parser or AST code' \
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
  'treat text nodes as commands' \
  'treat bindings as executable references' \
  'accept lowercase hex escapes' \
  'accept Unicode escapes' \
  'accept unknown escapes literally' \
  'allow decoded NUL bytes before length-carrying AST strings exist' \
  'broaden accepted grammar beyond the string-literal escape contract' \
  'change accepted escape decoding semantics'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_parser_string_escape_diagnostics_implementation_plan: ok\n'

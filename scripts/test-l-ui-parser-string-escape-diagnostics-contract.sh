#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui parser string escape diagnostics contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser string escape diagnostics contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: parser string escape diagnostics contract' "$doc"
require_contains 'This document does not implement parser-level string escape diagnostics.' "$doc"
require_contains 'Relationship to existing diagnostics' "$doc"
require_contains 'Current boundary' "$doc"
require_contains 'Diagnostic purpose' "$doc"
require_contains 'Proposed parser error additions' "$doc"
require_contains 'Proposed diagnostic codes' "$doc"
require_contains 'Stable messages' "$doc"
require_contains 'Hint language' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Validation order' "$doc"
require_contains 'Accepted escape compatibility' "$doc"
require_contains 'AST compatibility' "$doc"
require_contains 'Report relationship' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility rule' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_PARSER_DIAGNOSTICS.md \
  docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION_PLAN.md \
  docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md \
  docs/L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md \
  docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md \
  docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c
do
  require_contains "$related" "$doc"
done

for parser_error in \
  LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE \
  LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE \
  LATTICRA_L_UI_PARSE_UNTERMINATED_ESCAPE \
  LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING \
  LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING \
  LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE
do
  require_contains "$parser_error" "$doc"
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
  'String literal escape is not supported.' \
  'Hex string escape must use exactly two uppercase hexadecimal digits.' \
  'String literal escape is not terminated.' \
  'Decoded NUL bytes are not supported in AST strings.' \
  'Literal NUL bytes are not supported in AST strings.' \
  'Decoded string value exceeds the supported AST storage limit.'
do
  require_contains "$message" "$doc"
done

for hint in \
  'Use only' \
  'Use exactly two uppercase hex digits' \
  'Complete the escape sequence or remove the trailing backslash.' \
  'Avoid \x00 until length-carrying AST strings exist.' \
  'Remove literal NUL bytes from the source string.' \
  'Shorten the decoded purpose or text value.'
do
  require_contains "$hint" "$doc"
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

for accepted_escape in \
  '\\' \
  '\"' \
  '\n' \
  '\r' \
  '\t' \
  '\xNN' \
  'exactly two uppercase hexadecimal digits'
do
  require_contains "$accepted_escape" "$doc"
done

for report_field in \
  'diagnostic_severity=error' \
  'diagnostic_code=<LUI0019-through-LUI0024>' \
  'diagnostic_message=<stable-message>' \
  'diagnostic_hint=<stable-hint>' \
  'failed-parse report path'
do
  require_contains "$report_field" "$doc"
done

for compat in \
  'accepted string-literal escape decoding' \
  'latticra_l_ui_ast_report existing required fields' \
  'latticra_l_ui_ast_detailed_report existing required fields for accepted sources' \
  'latticra_l_ui_diagnostic_report existing required fields' \
  'existing diagnostic codes LUI0000 through LUI0018' \
  'existing parser error labels for current errors' \
  'existing accepted fixture summary counts'
do
  require_contains "$compat" "$doc"
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

for gate in \
  'parser enum additions' \
  'diagnostic code additions' \
  'parse error labels' \
  'stable messages' \
  'stable hints' \
  'source-span rules' \
  'validation order' \
  'AST compatibility behavior' \
  'report compatibility behavior' \
  'exact test file names' \
  'exact invariant tests'
do
  require_contains "$gate" "$doc"
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
  'broaden accepted grammar beyond the string-literal escape contract'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_parser_string_escape_diagnostics_contract: ok\n'

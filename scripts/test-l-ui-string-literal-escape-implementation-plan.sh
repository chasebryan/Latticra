#!/usr/bin/env sh
set -eu

doc="docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui string-literal escape implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui string-literal escape implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'String-literal escape decoding should be implemented in C.' "$doc"
require_contains 'Public API decision' "$doc"
require_contains 'Parser-level validation decision' "$doc"
require_contains 'Decoding helper plan' "$doc"
require_contains 'Extraction targets' "$doc"
require_contains 'Accepted escape behavior' "$doc"
require_contains 'Rejected escape behavior' "$doc"
require_contains 'NUL byte behavior' "$doc"
require_contains 'Capacity behavior' "$doc"
require_contains 'AST failure behavior' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Detailed report relationship' "$doc"
require_contains 'Successful parse rule' "$doc"
require_contains 'Failed parse compatibility' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for helper in \
  is_upper_hex_digit \
  upper_hex_value \
  decode_l_ui_string_literal_value \
  extract_decoded_quoted_value_after_token \
  latticra_l_ui_parse_ast \
  latticra_l_ui_parse_source \
  LATTICRA_STATUS_BUFFER_TOO_SMALL \
  LATTICRA_L_UI_PARSE_INTERNAL_ERROR
do
  require_contains "$helper" "$doc"
done

for target in \
  'purpose "..." -> ast.card.purpose' \
  'first text "..." -> ast.texts[0].value' \
  'second text "..." -> ast.texts[1].value' \
  'latticra_l_ui_ast_card_t.purpose' \
  'latticra_l_ui_ast_text_t.value' \
  LATTICRA_L_UI_AST_PURPOSE_MAX
do
  require_contains "$target" "$doc"
done

for escape_rule in \
  '\\ -> 0x5C' \
  '\" -> 0x22' \
  '\n -> 0x0A' \
  '\r -> 0x0D' \
  '\t -> 0x09' \
  '\x41 -> 0x41' \
  '\x7F -> 0x7F' \
  '\x80 -> 0x80' \
  '\xFF -> 0xFF' \
  'where `\xNN` uses exactly two uppercase hexadecimal digits.'
do
  require_contains "$escape_rule" "$doc"
done

for rejected in \
  '\a' \
  '\b' \
  '\f' \
  '\v' \
  '\u1234' \
  '\U00000000' \
  '\x0a' \
  '\x0' \
  '\x001' \
  '\xGG' \
  'Lowercase hex digits must fail in the first implementation.' \
  'Any backslash followed by an unsupported escape marker must fail instead of being copied literally.'
do
  require_contains "$rejected" "$doc"
done

for nul_rule in \
  'Decoded NUL bytes must be rejected in the first implementation.' \
  '\x00' \
  'literal `0x00` source byte' \
  'NUL-terminated fixed-size C strings without explicit decoded lengths.'
do
  require_contains "$nul_rule" "$doc"
done

for failure_rule in \
  'latticra_l_ui_parse_source remains a structural parser for the current L-UI fixture shape.' \
  'latticra_l_ui_parse_ast performs string-literal escape decoding while constructing AST values.' \
  'invalid escapes found during AST decoding classify the AST result as LATTICRA_L_UI_PARSE_INTERNAL_ERROR.' \
  'The implementation must not silently truncate decoded values.' \
  'ast.rail_count = 0' \
  'ast.field_count = 0' \
  'ast.text_count = 0' \
  'Do not add a new public `purpose_span` field in the first implementation.' \
  'If parsing fails structurally, decoding must not run.'
do
  require_contains "$failure_rule" "$doc"
done

for report_field in \
  'purpose=<decoded-purpose-as-current-C-string>' \
  'purpose_escaped=<report-safe-purpose>' \
  'value=<decoded-text-as-current-C-string>' \
  'value_escaped=<report-safe-text>' \
  escape_report_string
do
  require_contains "$report_field" "$doc"
done

for compat in \
  'latticra_l_ui_parse_source existing accepted fixture behavior' \
  'latticra_l_ui_ast_report existing required fields' \
  'latticra_l_ui_ast_detailed_report existing required fields' \
  'latticra_l_ui_diagnostic_report existing required fields' \
  'parser error labels' \
  'existing escaped report field semantics' \
  'existing accepted fixture summary counts' \
  'Fixtures without source escapes must produce the same AST values they produced before this implementation.'
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
  string_escape_decodes_backslash \
  string_escape_decodes_quote \
  string_escape_decodes_newline \
  string_escape_decodes_carriage_return \
  string_escape_decodes_tab \
  string_escape_decodes_uppercase_hex \
  string_escape_decodes_high_byte_hex \
  string_escape_rejects_lowercase_hex \
  string_escape_rejects_short_hex \
  string_escape_rejects_invalid_hex \
  string_escape_rejects_unknown_escape \
  string_escape_rejects_unterminated_escape \
  string_escape_rejects_decoded_nul_until_length_storage_exists \
  string_escape_rejects_literal_nul_until_length_storage_exists \
  string_escape_rejects_oversized_decoded_output \
  string_escape_preserves_source_spans \
  string_escape_updates_detailed_report_escaped_fields \
  string_escape_preserves_no_effect_flags \
  string_escape_does_not_change_parse_source_summary \
  string_escape_does_not_change_failed_parse_report \
  string_escape_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_string_literal_escape_invariants.c \
  scripts/test-l-ui-string-literal-escape.sh \
  docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md \
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
  'silently truncate decoded values' \
  'emit raw control bytes in escaped report fields' \
  'decode bindings, field names, rail names, card names, effect values, or boundary values in this slice' \
  'broaden accepted grammar beyond the string-literal escape contract' \
  'add parser-level escape diagnostics without a parser diagnostics contract' \
  'add length-carrying AST string storage without a storage contract'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_string_literal_escape_implementation_plan: ok\n'

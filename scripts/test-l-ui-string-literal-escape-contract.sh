#!/usr/bin/env sh
set -eu

doc="docs/L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui string-literal escape contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui string-literal escape contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: string-literal escape contract' "$doc"
require_contains 'This document does not implement string-literal escape decoding.' "$doc"
require_contains 'Escape decoding purpose' "$doc"
require_contains 'Accepted escape set' "$doc"
require_contains 'Hex escape rule' "$doc"
require_contains 'Unknown escape rule' "$doc"
require_contains 'Unterminated escape rule' "$doc"
require_contains 'Output byte rule' "$doc"
require_contains 'NUL byte rule' "$doc"
require_contains 'Storage rule' "$doc"
require_contains 'Source-span rule' "$doc"
require_contains 'Report relationship' "$doc"
require_contains 'Failed parse behavior' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility rule' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for target in \
  card.purpose \
  text.value \
  latticra_l_ui_ast_card_t.purpose \
  latticra_l_ui_ast_text_t.value \
  LATTICRA_L_UI_PARSE_INTERNAL_ERROR
do
  require_contains "$target" "$doc"
done

for escape_rule in \
  'backslash `0x5C`' \
  'double quote `0x22`' \
  'LF `0x0A`' \
  'CR `0x0D`' \
  'horizontal tab `0x09`' \
  'byte value from two uppercase hexadecimal digits' \
  'No other escape sequences should be accepted'
do
  require_contains "$escape_rule" "$doc"
done

for reject_rule in \
  'Lowercase hexadecimal digits should be rejected' \
  'Unknown escape sequences should be rejected' \
  'Unterminated escape sequences should be rejected' \
  'reject decoded NUL bytes' \
  'must not silently truncate decoded output'
do
  require_contains "$reject_rule" "$doc"
done

for report_field in \
  'purpose=<decoded-or-current-literal-purpose>' \
  'purpose_escaped=<report-escaped-purpose>' \
  'value=<decoded-or-current-literal-text>' \
  'value_escaped=<report-escaped-text>'
do
  require_contains "$report_field" "$doc"
done

for compat in \
  'latticra_l_ui_parse_source existing accepted fixture behavior' \
  'latticra_l_ui_ast_report existing required fields' \
  'latticra_l_ui_ast_detailed_report existing required fields' \
  'latticra_l_ui_diagnostic_report existing required fields' \
  'existing escaped report field semantics'
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
  string_escape_decodes_backslash \
  string_escape_decodes_quote \
  string_escape_decodes_newline \
  string_escape_decodes_carriage_return \
  string_escape_decodes_tab \
  string_escape_decodes_uppercase_hex \
  string_escape_rejects_lowercase_hex \
  string_escape_rejects_short_hex \
  string_escape_rejects_invalid_hex \
  string_escape_rejects_unknown_escape \
  string_escape_rejects_unterminated_escape \
  string_escape_rejects_decoded_nul_until_length_storage_exists \
  string_escape_rejects_oversized_decoded_output \
  string_escape_preserves_source_spans \
  string_escape_updates_detailed_report_escaped_fields \
  string_escape_preserves_no_effect_flags \
  string_escape_does_not_change_failed_parse_report \
  string_escape_is_deterministic
do
  require_contains "$test_name" "$doc"
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
  'broaden accepted grammar beyond this contract without a grammar update'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_string_literal_escape_contract: ok\n'

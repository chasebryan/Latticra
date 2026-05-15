#!/usr/bin/env sh
set -eu

doc="docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui ast escaped string report implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui ast escaped string report implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'Escaped string reporting should be implemented in C.' "$doc"
require_contains 'Public API decision' "$doc"
require_contains 'Private helper shape' "$doc"
require_contains 'Destination sizes' "$doc"
require_contains 'Escaped fields' "$doc"
require_contains 'Field placement' "$doc"
require_contains 'Escape rules' "$doc"
require_contains 'Hex rule' "$doc"
require_contains 'Byte-oriented rule' "$doc"
require_contains 'Too-small behavior' "$doc"
require_contains 'NUL behavior' "$doc"
require_contains 'Failed parse behavior' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for helper in \
  escape_report_string \
  LATTICRA_L_UI_AST_ESCAPED_PURPOSE_MAX \
  LATTICRA_L_UI_AST_ESCAPED_TEXT_MAX \
  LATTICRA_STATUS_BUFFER_TOO_SMALL
do
  require_contains "$helper" "$doc"
done

for field in \
  purpose_escaped \
  value_escaped \
  purpose \
  value \
  card.purpose \
  text.value
do
  require_contains "$field" "$doc"
done

for placement in \
  '[card]' \
  '[text <index>]' \
  'print `purpose_escaped` immediately after `purpose`' \
  'print `value_escaped` immediately after `value`' \
  'Do not add escaped fields to failed-parse reports.'
do
  require_contains "$placement" "$doc"
done

for escape_rule in \
  'newline LF `0x0A`' \
  'carriage return CR `0x0D`' \
  'horizontal tab `0x09`' \
  'double quote `0x22`' \
  'backslash `0x5C`' \
  'NUL `0x00`' \
  'other control bytes `0x01`-`0x1F`' \
  'DEL `0x7F`' \
  'non-ASCII bytes `0x80`-`0xFF`' \
  'Printable ASCII bytes from `0x20` through `0x7E`'
do
  require_contains "$escape_rule" "$doc"
done

for rule in \
  '0123456789ABCDEF' \
  'Lowercase hexadecimal output is not allowed.' \
  'Escaping is byte-oriented' \
  'unsigned char' \
  'strlen(...)' \
  'private helper test path through explicit `input_len`'
do
  require_contains "$rule" "$doc"
done

for compat in \
  latticra_l_ui_ast_report \
  latticra_l_ui_parse_ast \
  latticra_l_ui_parse_source \
  latticra_l_ui_parse_result_report \
  latticra_l_ui_diagnostic_report \
  'latticra_l_ui_ast_detailed_report existing required fields'
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
  escape_preserves_printable_ascii \
  escape_newline_as_backslash_n \
  escape_carriage_return_as_backslash_r \
  escape_tab_as_backslash_t \
  escape_quote_as_backslash_quote \
  escape_backslash_as_double_backslash \
  escape_nul_as_hex_00 \
  escape_control_bytes_as_uppercase_hex \
  escape_del_as_uppercase_hex \
  escape_non_ascii_bytes_as_uppercase_hex \
  escape_rejects_small_buffers \
  escape_is_deterministic \
  detailed_report_contains_escaped_purpose \
  detailed_report_contains_escaped_text_values \
  detailed_report_escaped_fields_are_additive \
  detailed_report_escape_preserves_no_effect_flags \
  detailed_report_escape_does_not_change_failed_parse_report
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_ast_escaped_string_report_invariants.c \
  scripts/test-l-ui-ast-escaped-string-report.sh \
  docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md \
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
  'emit memory addresses' \
  'emit raw control bytes in escaped fields' \
  'emit raw non-ASCII bytes in escaped fields'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_ast_escaped_string_report_implementation_plan: ok\n'

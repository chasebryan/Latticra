#!/usr/bin/env sh
set -eu

doc="docs/L_UI_AST_ESCAPED_STRING_REPORT_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui ast escaped string report contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui ast escaped string report contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: escaped string report contract' "$doc"
require_contains 'This document does not implement escaped string reporting.' "$doc"
require_contains 'Escaping purpose' "$doc"
require_contains 'Escaped fields' "$doc"
require_contains 'Report key naming' "$doc"
require_contains 'Required escape sequences' "$doc"
require_contains 'Hex format' "$doc"
require_contains 'Determinism rules' "$doc"
require_contains 'Byte-oriented rule' "$doc"
require_contains 'Buffer sizing rule' "$doc"
require_contains 'Helper function plan' "$doc"
require_contains 'Detailed report integration' "$doc"
require_contains 'Failed parse behavior' "$doc"
require_contains 'Compatibility rule' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for field in \
  card.purpose \
  text.value \
  purpose_escaped \
  value_escaped
do
  require_contains "$field" "$doc"
done

for escape in \
  '\\n' \
  '\\r' \
  '\\t' \
  '\\"' \
  '\\\\' \
  '\\x00' \
  '\\x1F' \
  '\\x7F' \
  '\\x80' \
  '\\xFF'
do
  require_contains "$escape" "$doc"
done

for byte_rule in \
  'Printable ASCII bytes from `0x20` through `0x7E`' \
  'Hex escapes must use uppercase hexadecimal digits' \
  'Escaping is byte-oriented' \
  'input_len * 4 + 1' \
  'escape_report_string'
do
  require_contains "$byte_rule" "$doc"
done

for compat in \
  latticra_l_ui_ast_report \
  latticra_l_ui_parse_ast \
  latticra_l_ui_parse_source \
  latticra_l_ui_parse_result_report \
  latticra_l_ui_diagnostic_report \
  latticra_l_ui_ast_detailed_report
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

printf 'l_ui_ast_escaped_string_report_contract: ok\n'

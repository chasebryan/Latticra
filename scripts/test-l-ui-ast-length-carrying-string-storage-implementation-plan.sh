#!/usr/bin/env sh
set -eu

doc="docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui ast length-carrying string storage implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui ast length-carrying string storage implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement length-carrying AST strings.' "$doc"
require_contains 'Relationship to previous contracts' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Public struct field placement' "$doc"
require_contains 'Public API compatibility decision' "$doc"
require_contains 'Default initialization rules' "$doc"
require_contains 'Source-backed extraction length assignment' "$doc"
require_contains 'String-literal decode helper shape' "$doc"
require_contains 'Extraction helper shape' "$doc"
require_contains 'Fill helper shape' "$doc"
require_contains 'Capacity behavior' "$doc"
require_contains 'NUL behavior' "$doc"
require_contains 'Report field additions' "$doc"
require_contains 'Length-aware escaped report helper shape' "$doc"
require_contains 'AST report compatibility' "$doc"
require_contains 'Parser diagnostics compatibility' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_CONTRACT.md \
  docs/L_UI_PARSER_AST_IMPLEMENTATION.md \
  docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md \
  docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md \
  docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md \
  docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser_ast.c \
  src/l_ui_parser.c \
  src/l_ui_parser_diagnostics.c
do
  require_contains "$related" "$doc"
done

for field in \
  'size_t purpose_len;' \
  'size_t value_len;' \
  latticra_l_ui_ast_card_t \
  latticra_l_ui_ast_text_t \
  'ast.card.purpose_len = 0' \
  'ast.texts[index].value_len = 0' \
  'ast.card.purpose_len == strlen(ast.card.purpose)' \
  'ast.texts[index].value_len == strlen(ast.texts[index].value)'
do
  require_contains "$field" "$doc"
done

for helper in \
  decode_l_ui_string_literal_value \
  extract_decoded_quoted_value_after_token \
  'size_t *decoded_len' \
  '`decoded_len` must be set only on success' \
  'fill_text' \
  'value_len' \
  'extracted_purpose_len'
do
  require_contains "$helper" "$doc"
done

for capacity in \
  LATTICRA_L_UI_AST_PURPOSE_MAX \
  'decoded_len < destination_len' \
  'compatibility C string still needs a trailing NUL byte' \
  LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE
do
  require_contains "$capacity" "$doc"
done

for nul_rule in \
  'This implementation must not accept decoded or literal NUL bytes.' \
  '\x00 -> LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING' \
  'literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  'A later decoded-NUL acceptance contract may change this, but not this implementation.'
do
  require_contains "$nul_rule" "$doc"
done

for report in \
  'purpose_len=<decoded-purpose-byte-length>' \
  'value_len=<decoded-text-byte-length>' \
  'purpose_escaped=<purpose_escaped>' \
  'value_escaped=<value_escaped>' \
  escape_report_string \
  escape_report_bytes \
  'callers pass explicit AST lengths instead of strlen'
do
  require_contains "$report" "$doc"
done

for compat in \
  'latticra_l_ui_ast_report' \
  'compact AST report' \
  'Failed-parse detailed reports should remain unchanged' \
  'accepted string-literal escape decoding' \
  'parser-level invalid string escape diagnostics' \
  'existing diagnostic codes LUI0000 through LUI0024' \
  'existing parser error labels for current errors' \
  'latticra_l_ui_diagnostic_report existing required fields' \
  'failed-parse detailed report behavior'
do
  require_contains "$compat" "$doc"
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
  ast_string_storage_sets_purpose_len \
  ast_string_storage_sets_text_value_len \
  ast_string_storage_len_matches_strlen_for_non_nul_values \
  ast_string_storage_len_tracks_decoded_newline \
  ast_string_storage_len_tracks_decoded_tab \
  ast_string_storage_len_tracks_decoded_high_byte_hex \
  ast_string_storage_preserves_existing_c_string_fields \
  ast_string_storage_updates_detailed_report_lengths \
  ast_string_storage_escaped_report_uses_explicit_lengths \
  ast_string_storage_still_rejects_decoded_nul_until_acceptance_contract \
  ast_string_storage_still_rejects_literal_nul_until_acceptance_contract \
  ast_string_storage_still_rejects_oversized_decoded_output \
  ast_string_storage_preserves_source_spans \
  ast_string_storage_preserves_no_effect_flags \
  ast_string_storage_does_not_change_existing_diagnostic_codes \
  ast_string_storage_does_not_change_failed_parse_report \
  ast_string_storage_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_ast_length_carrying_string_storage_invariants.c \
  scripts/test-l-ui-ast-length-carrying-string-storage.sh \
  docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md \
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
  'accept decoded NUL bytes without a separate acceptance contract' \
  'accept literal NUL bytes without a separate acceptance contract' \
  'broaden accepted string escapes' \
  'remove existing C-string fields' \
  'silently truncate decoded values' \
  'change accepted escape decoding semantics' \
  'change existing parser diagnostic codes' \
  'make raw `purpose=` or `value=` report fields the assertion target for embedded NUL bytes'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_ast_length_carrying_string_storage_implementation_plan: ok\n'

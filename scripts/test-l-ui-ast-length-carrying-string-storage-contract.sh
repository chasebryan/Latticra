#!/usr/bin/env sh
set -eu

doc="docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui ast length-carrying string storage contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui ast length-carrying string storage contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: AST string storage contract' "$doc"
require_contains 'This document does not implement length-carrying AST strings.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Current boundary' "$doc"
require_contains 'Storage purpose' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Compatibility rule' "$doc"
require_contains 'NUL byte rule' "$doc"
require_contains 'Source-backed extraction rule' "$doc"
require_contains 'Decoding relationship' "$doc"
require_contains 'Capacity rule' "$doc"
require_contains 'Report behavior' "$doc"
require_contains 'Escaped report rule' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Parser diagnostics compatibility' "$doc"
require_contains 'AST compatibility behavior' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
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
  latticra_l_ui_ast_card_t.purpose \
  latticra_l_ui_ast_text_t.value \
  latticra_l_ui_ast_card_t.purpose_len \
  latticra_l_ui_ast_text_t.value_len \
  purpose_len \
  value_len \
  'size_t purpose_len;' \
  'size_t value_len;'
do
  require_contains "$field" "$doc"
done

for nul_rule in \
  '\x00 -> LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING' \
  'literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  'Decoded NUL bytes may be accepted only after' \
  'length-carrying AST storage is implemented' \
  'report escaping uses explicit lengths' \
  'parser string escape diagnostics are updated by a separate contract' \
  'string-literal escape decoding behavior is updated by a separate contract'
do
  require_contains "$nul_rule" "$doc"
done

for extraction in \
  'purpose "..." -> ast.card.purpose + ast.card.purpose_len' \
  'first text "..." -> ast.texts[0].value + ast.texts[0].value_len' \
  'second text "..." -> ast.texts[1].value + ast.texts[1].value_len'
do
  require_contains "$extraction" "$doc"
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

for capacity in \
  LATTICRA_L_UI_AST_PURPOSE_MAX \
  'decoded_len < destination_buffer_len' \
  LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE \
  'compatibility buffer still needs a trailing NUL byte'
do
  require_contains "$capacity" "$doc"
done

for report_field in \
  'purpose_len=<decoded-purpose-byte-length>' \
  'value_len=<decoded-text-byte-length>' \
  'purpose=<C-string-compatible-purpose>' \
  'purpose_escaped=<length-aware-report-safe-purpose>' \
  'value=<C-string-compatible-text>' \
  'value_escaped=<length-aware-report-safe-text>' \
  'escape_report_bytes' \
  'input_len'
do
  require_contains "$report_field" "$doc"
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

for gate in \
  'public struct field placement' \
  'default initialization rules' \
  'source-backed extraction length assignment' \
  'string-literal decode length assignment' \
  'report field additions' \
  'length-aware escaped report helper shape' \
  'parser diagnostics compatibility' \
  'capacity behavior' \
  'exact test file names' \
  'exact invariant tests' \
  'compatibility expectations'
do
  require_contains "$gate" "$doc"
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
  'make raw `purpose=` or `value=` report fields the assertion target for embedded NUL bytes'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_ast_length_carrying_string_storage_contract: ok\n'

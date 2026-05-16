#!/usr/bin/env sh
set -eu

doc="docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui decoded NUL acceptance implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui decoded NUL acceptance implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement decoded NUL acceptance.' "$doc"
require_contains 'Relationship to previous contracts' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Acceptance scope' "$doc"
require_contains 'Parser validation changes' "$doc"
require_contains 'Parser diagnostic compatibility' "$doc"
require_contains 'Decode helper changes' "$doc"
require_contains 'AST storage expectations' "$doc"
require_contains 'C-string prefix compatibility' "$doc"
require_contains 'Report expectations' "$doc"
require_contains 'Escaped report helper expectations' "$doc"
require_contains 'Source-span expectations' "$doc"
require_contains 'Parser validation order' "$doc"
require_contains 'Accepted escape compatibility' "$doc"
require_contains 'Compact report compatibility' "$doc"
require_contains 'Failed parse compatibility' "$doc"
require_contains 'Fixture compatibility' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md \
  docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_CONTRACT.md \
  docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md \
  docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md \
  docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md \
  docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c
do
  require_contains "$related" "$doc"
done

for scope in \
  'accept only escaped decoded NUL through uppercase hex syntax' \
  '\x00' \
  'purpose "A\x00B"' \
  'text "left\x00right"' \
  'Literal source NUL bytes remain rejected.'
do
  require_contains "$scope" "$doc"
done

for parser in \
  'src/l_ui_parser.c' \
  'LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING' \
  'escaped `\x00` in supported source-backed string values is accepted and counted as one decoded byte' \
  'LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING'
do
  require_contains "$parser" "$doc"
done

for diagnostic in \
  'LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING' \
  'LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  'LUI0022 decoded_nul_in_string' \
  'LUI0023 literal_nul_in_string' \
  '\x00 -> accepted in source-backed string values' \
  'literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  '`LUI0022` remains reserved and stable'
do
  require_contains "$diagnostic" "$doc"
done

for decode in \
  'src/l_ui_parser_ast.c' \
  'allow decoded byte `0x00` when and only when it is produced by escaped `\x00`' \
  'reject literal source NUL bytes before value materialization' \
  '"A\x00B" -> decoded bytes: A, 0x00, B -> length 3'
do
  require_contains "$decode" "$doc"
done

for ast_rule in \
  'ast.card.purpose' \
  'ast.card.purpose_len' \
  'ast.texts[index].value' \
  'ast.texts[index].value_len' \
  'purpose_len != strlen(purpose)' \
  'value_len != strlen(value)' \
  'The explicit length field is authoritative.' \
  "purpose[0] == 'A'" \
  "purpose[1] == '\\0'" \
  "purpose[2] == 'B'" \
  'purpose_len == 3' \
  'strlen(purpose) == 1'
do
  require_contains "$ast_rule" "$doc"
done

for report in \
  'purpose_len=3' \
  'purpose_escaped=A\x00B' \
  'value_len=10' \
  'value_escaped=left\x00right' \
  'purpose=<C-string-compatible-prefix>' \
  'value=<C-string-compatible-prefix>' \
  'not raw `purpose=` or `value=` fields' \
  'escape_report_bytes(input, input_len, output, output_len)' \
  'ast.card.purpose_len' \
  'ast.texts[index].value_len'
do
  require_contains "$report" "$doc"
done

for validation in \
  'null argument checks' \
  'source size checks' \
  'structural parse checks' \
  'string escape validation' \
  'AST construction' \
  'Structural parse errors must retain priority over decoded-NUL acceptance.'
do
  require_contains "$validation" "$doc"
done

for accepted_escape in \
  '\\' \
  '\"' \
  '\n' \
  '\r' \
  '\t' \
  '\xNN' \
  'exactly two uppercase hexadecimal digits' \
  '\x0a -> LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE' \
  '\a -> LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE' \
  'literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING'
do
  require_contains "$accepted_escape" "$doc"
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
  decoded_nul_accepts_purpose_x00 \
  decoded_nul_accepts_text_x00 \
  decoded_nul_counts_purpose_len \
  decoded_nul_counts_text_value_len \
  decoded_nul_preserves_c_string_prefix_compatibility \
  decoded_nul_reports_purpose_escaped_x00 \
  decoded_nul_reports_text_value_escaped_x00 \
  decoded_nul_does_not_emit_lui0022_for_x00 \
  decoded_nul_still_rejects_literal_nul_lui0023 \
  decoded_nul_still_rejects_lowercase_hex_lui0020 \
  decoded_nul_still_rejects_unknown_escape_lui0019 \
  decoded_nul_preserves_source_spans \
  decoded_nul_preserves_no_effect_flags \
  decoded_nul_does_not_change_failed_parse_report \
  decoded_nul_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_decoded_nul_acceptance_invariants.c \
  scripts/test-l-ui-decoded-nul-acceptance.sh \
  .github/workflows/c.yml \
  docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md
do
  require_contains "$path" "$doc"
done

for forbidden in \
  'accept literal NUL source bytes' \
  'accept lowercase hex escapes' \
  'accept unknown escapes' \
  'broaden accepted escape forms' \
  'remove `LUI0022` from the diagnostic code table' \
  'remove `LUI0023` literal NUL rejection' \
  'remove existing C-string fields' \
  'make raw `purpose=` or `value=` report fields the assertion target for embedded NUL bytes' \
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
  'treat bindings as executable references'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_decoded_nul_acceptance_implementation_plan: ok\n'

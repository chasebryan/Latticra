#!/usr/bin/env sh
set -eu

doc="docs/L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui decoded NUL acceptance contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui decoded NUL acceptance contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: decoded NUL acceptance contract' "$doc"
require_contains 'This document does not implement decoded NUL acceptance.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Current boundary' "$doc"
require_contains 'Acceptance decision' "$doc"
require_contains 'Literal NUL remains rejected' "$doc"
require_contains 'Parser diagnostic transition' "$doc"
require_contains 'Accepted escape compatibility' "$doc"
require_contains 'AST storage behavior' "$doc"
require_contains 'Decode helper behavior' "$doc"
require_contains 'Parser validation order' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Detailed report behavior' "$doc"
require_contains 'Compact report compatibility' "$doc"
require_contains 'AST compatibility behavior' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
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

for acceptance in \
  'A future implementation may accept escaped decoded NUL bytes only through the existing uppercase hex escape form:' \
  '\x00' \
  'purpose "A\x00B"' \
  'text "left\x00right"' \
  'The decoded AST byte sequence should contain the NUL byte at that position' \
  'the explicit length field should include that byte'
do
  require_contains "$acceptance" "$doc"
done

for literal_nul in \
  'Literal `0x00` bytes in the source buffer remain rejected.' \
  'LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  'LUI0023 literal_nul_in_string' \
  'escaped NUL is deterministic and operator-visible in reports' \
  'accepting literal NUL requires a separate source-buffer contract'
do
  require_contains "$literal_nul" "$doc"
done

for transition in \
  'LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING' \
  'LUI0022 decoded_nul_in_string' \
  '`LUI0022` must remain a stable diagnostic code for compatibility' \
  'should no longer trigger it after decoded-NUL acceptance is implemented' \
  '`LUI0023 literal_nul_in_string` remains active'
do
  require_contains "$transition" "$doc"
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
  '\a -> LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE'
do
  require_contains "$accepted_escape" "$doc"
done

for ast_rule in \
  'ast.card.purpose' \
  'ast.card.purpose_len' \
  'ast.texts[index].value' \
  'ast.texts[index].value_len' \
  'purpose_len != strlen(purpose)' \
  'value_len != strlen(value)' \
  'The explicit length field is authoritative.'
do
  require_contains "$ast_rule" "$doc"
done

for report_rule in \
  'purpose_len=3' \
  'purpose_escaped=A\x00B' \
  'value_len=10' \
  'value_escaped=left\x00right' \
  'purpose=<C-string-compatible-prefix>' \
  'value=<C-string-compatible-prefix>' \
  'purpose_len' \
  'purpose_escaped' \
  'value_len' \
  'value_escaped' \
  'not raw `purpose=` or `value=` fields'
do
  require_contains "$report_rule" "$doc"
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
  'parser validation changes' \
  'decode helper changes' \
  'AST storage expectations' \
  'report expectations' \
  'diagnostic compatibility behavior' \
  'source-span expectations' \
  'exact test file names' \
  'exact invariant tests' \
  'compatibility expectations' \
  'non-claims'
do
  require_contains "$gate" "$doc"
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

printf 'l_ui_decoded_nul_acceptance_contract: ok\n'
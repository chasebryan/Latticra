#!/usr/bin/env sh
set -eu

doc="docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui source-buffer literal NUL policy implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui source-buffer literal NUL policy implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement literal NUL acceptance.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Policy decision' "$doc"
require_contains 'Parser behavior plan' "$doc"
require_contains 'Diagnostic behavior plan' "$doc"
require_contains 'Source-span plan' "$doc"
require_contains 'AST behavior plan' "$doc"
require_contains 'Report behavior plan' "$doc"
require_contains 'Escaped decoded NUL compatibility' "$doc"
require_contains 'Accepted escape compatibility' "$doc"
require_contains 'Source-buffer construction test plan' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation update plan' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_CONTRACT.md \
  docs/L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md \
  docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION_PLAN.md \
  docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md \
  docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md \
  docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c
do
  require_contains "$related" "$doc"
done

for policy in \
  'Literal `0x00` bytes in L-UI source buffers remain rejected.' \
  'The accepted way to express a decoded NUL byte inside a source-backed string value remains:' \
  '\x00' \
  'This plan is for policy enforcement and regression coverage, not literal-NUL acceptance.'
do
  require_contains "$policy" "$doc"
done

for parser in \
  'src/l_ui_parser.c' \
  'should continue detecting literal source-buffer NUL bytes before AST materialization' \
  'LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  'empty_source' \
  'unterminated_string' \
  'invalid_string_escape' \
  'invalid_hex_escape' \
  'decoded_nul_in_string' \
  'internal_error'
do
  require_contains "$parser" "$doc"
done

for diagnostic in \
  'LUI0023 literal_nul_in_string' \
  'Literal NUL bytes are not supported in AST strings.' \
  'Remove literal NUL bytes from the source string.' \
  'LUI0022 decoded_nul_in_string' \
  'literal source NUL must not emit it'
do
  require_contains "$diagnostic" "$doc"
done

for span in \
  'span_end_offset - span_start_offset == 1' \
  'source[span_start_offset] == 0x00' \
  'Line and column remain one-based byte positions'
do
  require_contains "$span" "$doc"
done

for ast_rule in \
  'ast.parse_result.error = LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  'ast.rail_count = 0' \
  'ast.field_count = 0' \
  'ast.text_count = 0' \
  'ast.card.rail_count = 0' \
  'ast.card.field_count = 0' \
  'ast.card.text_count = 0' \
  'ast.card.purpose_len = 0' \
  'ast.texts[index].value_len = 0'
do
  require_contains "$ast_rule" "$doc"
done

for report in \
  'parse_error=literal_nul_in_string' \
  'rail_count=0' \
  'field_count=0' \
  'text_count=0' \
  'purpose=' \
  'value=' \
  'purpose_escaped=' \
  'value_escaped='
do
  require_contains "$report" "$doc"
done

for escaped in \
  'purpose "A\x00B"' \
  'text "left\x00right"' \
  'The existing decoded-NUL acceptance tests should remain valid.'
do
  require_contains "$escaped" "$doc"
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

require_contains 'make_source_binary(buffer, buffer_len, purpose, purpose_len, top_text, top_text_len, bottom_text, bottom_text_len, source_len)' "$doc"

for test_name in \
  literal_nul_policy_rejects_purpose_literal_nul \
  literal_nul_policy_rejects_text_literal_nul \
  literal_nul_policy_reports_lui0023 \
  literal_nul_policy_span_covers_literal_nul_byte \
  literal_nul_policy_preserves_no_effect_flags \
  literal_nul_policy_does_not_emit_decoded_nul_lui0022 \
  literal_nul_policy_does_not_materialize_partial_ast \
  literal_nul_policy_does_not_change_escaped_x00_acceptance \
  literal_nul_policy_does_not_change_failed_parse_report \
  literal_nul_policy_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_source_buffer_literal_nul_policy_invariants.c \
  scripts/test-l-ui-source-buffer-literal-nul-policy.sh \
  .github/workflows/c.yml \
  docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md
do
  require_contains "$path" "$doc"
done

for doc_path in \
  README.md \
  STATUS.md \
  docs/FOUNDATION_INDEX.md \
  docs/status/CURRENT_STATUS.md \
  docs/status/ANNOUNCEMENTS.md \
  docs/project_notes/UPCOMING_WORK.md \
  docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_CONTRACT.md \
  docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md
do
  require_contains "$doc_path" "$doc"
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

for compat in \
  'escaped decoded NUL acceptance' \
  'literal source NUL rejection' \
  'LUI0023 diagnostic mapping' \
  'accepted string-literal escape decoding' \
  'parser diagnostic code stability' \
  'existing C-string fields' \
  'purpose_len and value_len semantics' \
  'failed-parse detailed report behavior' \
  'existing accepted fixture counts'
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

for forbidden in \
  'accept literal NUL source bytes without a separate acceptance contract' \
  'treat literal source NUL as escaped decoded NUL' \
  'remove `LUI0023` literal NUL rejection' \
  'remove `LUI0022` diagnostic compatibility' \
  'hide literal source NUL in diagnostics' \
  'produce a partial AST for literal source NUL input' \
  'make raw `purpose=` or `value=` report fields the assertion target for embedded NUL bytes' \
  'broaden accepted escape forms' \
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

require_contains 'sh scripts/test-l-ui-source-buffer-literal-nul-policy-implementation-plan.sh' "$doc"
require_contains 'Literal source-buffer NUL policy implementation code may be added only after this plan is merged.' "$doc"

printf 'l_ui_source_buffer_literal_nul_policy_implementation_plan: ok\n'

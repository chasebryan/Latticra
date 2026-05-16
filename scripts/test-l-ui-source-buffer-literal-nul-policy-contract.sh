#!/usr/bin/env sh
set -eu

doc="docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui source-buffer literal NUL policy contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui source-buffer literal NUL policy contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: source-buffer literal NUL policy contract' "$doc"
require_contains 'This document does not implement literal NUL acceptance.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Current boundary' "$doc"
require_contains 'Policy decision' "$doc"
require_contains 'Rationale' "$doc"
require_contains 'Escaped decoded NUL remains accepted' "$doc"
require_contains 'Literal NUL diagnostic behavior' "$doc"
require_contains 'Parser behavior' "$doc"
require_contains 'AST behavior' "$doc"
require_contains 'Report behavior' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Future source-buffer model requirements' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Current validation command' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
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
  'Literal `0x00` bytes in L-UI source buffers remain forbidden.' \
  'The accepted way to express a decoded NUL byte inside a source-backed string value is the escaped form:' \
  '\x00' \
  'LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  'LUI0023 literal_nul_in_string'
do
  require_contains "$policy" "$doc"
done

for rationale in \
  'source buffers still cross C APIs and C-compatible tooling' \
  'many tools treat NUL as a string terminator' \
  'embedded source NUL can hide or truncate source text in logs and diagnostics' \
  'escaped `\x00` is deterministic and visible' \
  'accepting literal source NUL requires a separate source-buffer ownership model'
do
  require_contains "$rationale" "$doc"
done

for escaped in \
  'purpose "A\x00B"' \
  'text "left\x00right"' \
  'ast.card.purpose_len' \
  'ast.texts[index].value_len'
do
  require_contains "$escaped" "$doc"
done

for parser in \
  'Parser validation should keep detecting literal source NUL bytes before AST materialization.' \
  'empty source' \
  'unterminated string' \
  'invalid hex escape' \
  'decoded NUL' \
  'internal error' \
  'Literal source NUL remains a distinct source-buffer error.'
do
  require_contains "$parser" "$doc"
done

for ast in \
  'Literal source NUL input should not produce a partial AST.' \
  'ast.parse_result.error = LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING' \
  'ast.rail_count = 0' \
  'ast.field_count = 0' \
  'ast.text_count = 0' \
  'failed-parse detailed report only'
do
  require_contains "$ast" "$doc"
done

for report in \
  'Literal source NUL failures should continue to use failed-parse detailed report behavior.' \
  'No decoded AST value should be materialized for literal source NUL input.' \
  'purpose_len' \
  'purpose_escaped' \
  'value_len' \
  'value_escaped'
do
  require_contains "$report" "$doc"
done

for span in \
  'spans should cover exactly the literal `0x00` byte in the source buffer' \
  'Line and column remain one-based byte positions' \
  'Escaped decoded NUL spans remain source-oriented'
do
  require_contains "$span" "$doc"
done

for future in \
  'source buffer ownership rules' \
  'source length authority rules' \
  'source display and logging behavior' \
  'diagnostic rendering for literal NUL' \
  'file fixture policy' \
  'C API compatibility rules' \
  'command-line tooling behavior' \
  'report escaping behavior' \
  'exact tests' \
  'non-claims'
do
  require_contains "$future" "$doc"
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

for forbidden in \
  'accept literal NUL source bytes without a separate implementation plan' \
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

require_contains 'sh scripts/test-l-ui-source-buffer-literal-nul-policy-contract.sh' "$doc"

printf 'l_ui_source_buffer_literal_nul_policy_contract: ok\n'

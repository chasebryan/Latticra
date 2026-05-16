#!/usr/bin/env sh
set -eu

doc="docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lat language grammar implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'lat language grammar implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement Lat parsing.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Implementation files' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Capacity constants' "$doc"
require_contains 'Parse error enum' "$doc"
require_contains 'Declaration kind enum' "$doc"
require_contains 'Effect enum' "$doc"
require_contains 'Source span struct' "$doc"
require_contains 'AST module struct' "$doc"
require_contains 'AST declaration struct' "$doc"
require_contains 'AST clause struct' "$doc"
require_contains 'Parse result struct' "$doc"
require_contains 'Accepted fixture paths' "$doc"
require_contains 'Parser ownership rules' "$doc"
require_contains 'String literal handling' "$doc"
require_contains 'Forbidden behavior markers' "$doc"
require_contains 'Report format' "$doc"
require_contains 'Source-span mapping' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation update plan' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md \
  docs/LANGUAGE_NAMING_POLICY.md \
  docs/LANGUAGE_STRATEGY.md \
  docs/C_CPP_FOUNDATION_DIRECTION.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/EFFECT_GATES.md \
  docs/STATE_LATTICE.md \
  include/latticra/lir.h \
  include/latticra/state_lattice.h
do
  require_contains "$related" "$doc"
done

for path in \
  include/latticra/lat_parser.h \
  src/lat_parser.c \
  tests/lat_language_grammar_invariants.c \
  scripts/test-lat-language-grammar.sh \
  .github/workflows/c.yml \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md \
  fixtures/lat/minimal_module.lat
do
  require_contains "$path" "$doc"
done

for api in \
  latticra_lat_parse_error_t \
  latticra_lat_declaration_kind_t \
  latticra_lat_effect_t \
  latticra_lat_source_span_t \
  latticra_lat_parse_result_t \
  latticra_lat_ast_module_t \
  latticra_lat_ast_declaration_t \
  latticra_lat_ast_clause_t \
  latticra_lat_parse_error_label \
  latticra_lat_declaration_kind_label \
  latticra_lat_effect_label \
  latticra_lat_parse_source \
  latticra_lat_parse_report
do
  require_contains "$api" "$doc"
done

for constant in \
  'LATTICRA_LAT_SOURCE_MAX 65536u' \
  'LATTICRA_LAT_NAME_MAX 64u' \
  'LATTICRA_LAT_VALUE_MAX 128u' \
  'LATTICRA_LAT_DECLARATION_MAX 64u' \
  'LATTICRA_LAT_CLAUSE_MAX 128u' \
  'LATTICRA_LAT_REPORT_MAX 4096u'
do
  require_contains "$constant" "$doc"
done

for error_name in \
  LATTICRA_LAT_PARSE_OK \
  LATTICRA_LAT_PARSE_NULL_ARGUMENT \
  LATTICRA_LAT_PARSE_EMPTY_SOURCE \
  LATTICRA_LAT_PARSE_SOURCE_TOO_LARGE \
  LATTICRA_LAT_PARSE_UNSUPPORTED_EXTENSION_CLAIM \
  LATTICRA_LAT_PARSE_MISSING_MODULE \
  LATTICRA_LAT_PARSE_INVALID_MODULE_NAME \
  LATTICRA_LAT_PARSE_UNBALANCED_BRACE \
  LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION \
  LATTICRA_LAT_PARSE_INVALID_DECLARATION_NAME \
  LATTICRA_LAT_PARSE_UNTERMINATED_STRING \
  LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE \
  LATTICRA_LAT_PARSE_INVALID_HEX_ESCAPE \
  LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING \
  LATTICRA_LAT_PARSE_CAPACITY_EXCEEDED \
  LATTICRA_LAT_PARSE_FORBIDDEN_BEHAVIOR_MARKER \
  LATTICRA_LAT_PARSE_INTERNAL_ERROR
do
  require_contains "$error_name" "$doc"
done

for error_label in \
  ok \
  null_argument \
  empty_source \
  source_too_large \
  unsupported_extension_claim \
  missing_module \
  invalid_module_name \
  unbalanced_brace \
  unknown_declaration \
  invalid_declaration_name \
  unterminated_string \
  invalid_string_escape \
  invalid_hex_escape \
  literal_nul_in_string \
  capacity_exceeded \
  forbidden_behavior_marker \
  internal_error
do
  require_contains "$error_label" "$doc"
done

for decl in \
  LATTICRA_LAT_DECLARATION_STATE \
  LATTICRA_LAT_DECLARATION_POLICY \
  LATTICRA_LAT_DECLARATION_TRANSITION \
  LATTICRA_LAT_DECLARATION_ASSERTION \
  LATTICRA_LAT_DECLARATION_EFFECT \
  LATTICRA_LAT_DECLARATION_UNKNOWN
do
  require_contains "$decl" "$doc"
done

for effect in \
  LATTICRA_LAT_EFFECT_NONE \
  LATTICRA_LAT_EFFECT_READ \
  LATTICRA_LAT_EFFECT_LOCAL_MUTATION \
  LATTICRA_LAT_EFFECT_HOST_MUTATION \
  LATTICRA_LAT_EFFECT_NETWORK \
  LATTICRA_LAT_EFFECT_HARDWARE \
  LATTICRA_LAT_EFFECT_BOOT \
  LATTICRA_LAT_EFFECT_RECOVERY \
  LATTICRA_LAT_EFFECT_EXTERNAL \
  LATTICRA_LAT_EFFECT_UNKNOWN
do
  require_contains "$effect" "$doc"
done

for struct_field in \
  'size_t start_offset;' \
  'size_t end_offset;' \
  'size_t start_line;' \
  'size_t start_column;' \
  'size_t end_line;' \
  'size_t end_column;' \
  'char module_name[LATTICRA_LAT_NAME_MAX];' \
  'size_t declaration_count;' \
  'size_t state_count;' \
  'size_t policy_count;' \
  'size_t transition_count;' \
  'size_t assertion_count;' \
  'size_t effect_count;' \
  'latticra_lat_declaration_kind_t kind;' \
  'char name[LATTICRA_LAT_NAME_MAX];' \
  'char source_name[LATTICRA_LAT_NAME_MAX];' \
  'size_t first_clause_index;' \
  'size_t clause_count;' \
  'char keyword[LATTICRA_LAT_NAME_MAX];' \
  'char left[LATTICRA_LAT_NAME_MAX];' \
  'char operator_text[LATTICRA_LAT_NAME_MAX];' \
  'char right[LATTICRA_LAT_VALUE_MAX];' \
  'latticra_lat_effect_t effect;' \
  'latticra_status_t status;' \
  'latticra_lat_parse_error_t error;'
do
  require_contains "$struct_field" "$doc"
done

for fixture in \
  'fixtures/lat/minimal_module.lat' \
  'lat module RootModule' \
  'state RootCell' \
  'origin = "0/0"' \
  'host_effect = none' \
  'external_effect = none'
do
  require_contains "$fixture" "$doc"
done

for ownership in \
  'never retain pointers into caller-owned source buffers' \
  'copy names and values into bounded fixed-size fields' \
  'reject capacity overflow deterministically' \
  'preserve source spans' \
  'return status codes' \
  'avoid heap allocation' \
  'avoid file I/O' \
  'avoid global mutable state' \
  'avoid execution or evaluation'
do
  require_contains "$ownership" "$doc"
done

for string_rule in \
  '\\' \
  '\"' \
  '\n' \
  '\r' \
  '\t' \
  '\xHH' \
  'unterminated strings' \
  'unsupported escapes' \
  'invalid hex escapes' \
  'literal source-buffer NUL bytes' \
  'Escaped decoded NUL through `\x00`'
do
  require_contains "$string_rule" "$doc"
done

for marker in \
  exec \
  spawn \
  syscall \
  socket \
  open_file \
  write_file \
  hardware_write
do
  require_contains "$marker" "$doc"
done

for report in \
  'LAT GRAMMAR REPORT' \
  'status=<integer-status>' \
  'error=<lat-error-label>' \
  'module=<module-name>' \
  'declaration_count=<count>' \
  'state_count=<count>' \
  'policy_count=<count>' \
  'transition_count=<count>' \
  'assertion_count=<count>' \
  'effect_count=<count>' \
  'clause_count=<count>' \
  'span_start_offset=<offset>' \
  'span_end_column=<column>'
do
  require_contains "$report" "$doc"
done

for mapping in \
  'module -> full module declaration span' \
  'declaration -> full declaration span' \
  'field assignment -> assignment clause span' \
  'require clause -> requirement clause span' \
  'ensure clause -> ensure clause span' \
  'effect clause -> effect clause span' \
  'string literal -> string token span if exposed later' \
  'identifier reference -> identifier token span if exposed later'
do
  require_contains "$mapping" "$doc"
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
  lat_grammar_accepts_minimal_module \
  lat_grammar_accepts_state_declaration \
  lat_grammar_accepts_policy_declaration \
  lat_grammar_accepts_transition_declaration \
  lat_grammar_accepts_assertion_declaration \
  lat_grammar_accepts_effect_declaration \
  lat_grammar_rejects_plain_l_extension_claim \
  lat_grammar_rejects_unknown_keyword \
  lat_grammar_rejects_unterminated_string \
  lat_grammar_rejects_invalid_escape \
  lat_grammar_rejects_literal_source_nul \
  lat_grammar_reports_source_spans \
  lat_grammar_preserves_no_effect_flags \
  lat_grammar_report_is_deterministic \
  lat_grammar_report_rejects_small_buffer \
  lat_grammar_error_labels_are_stable \
  lat_grammar_kind_labels_are_stable \
  lat_grammar_does_not_lower_to_lir \
  lat_grammar_does_not_execute_declarations \
  lat_grammar_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for doc_path in \
  README.md \
  STATUS.md \
  docs/FOUNDATION_INDEX.md \
  docs/status/CURRENT_STATUS.md \
  docs/status/ANNOUNCEMENTS.md \
  docs/project_notes/CURRENT_DIRECTION.md \
  docs/project_notes/UPCOMING_WORK.md \
  docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md \
  docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md \
  scripts/test-project-strategy-status-framework.sh \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
do
  require_contains "$doc_path" "$doc"
done

for compat in \
  'language naming policy' \
  '.lat canonical extension' \
  'C/C++ foundation direction' \
  'L-UI parser behavior' \
  'L-UI semantic validation behavior' \
  'LIR shape behavior' \
  'state lattice behavior' \
  'Nucleus preview behavior' \
  'escaped decoded NUL acceptance' \
  'literal source-buffer NUL rejection' \
  'no-effect flags'
do
  require_contains "$compat" "$doc"
done

for forbidden in \
  'claim plain `L` as the public language name' \
  'claim `.l` as the canonical source extension' \
  'execute declarations' \
  'mutate state' \
  'lower to LIR' \
  'render L-UI' \
  'call Nucleus task execution' \
  'evaluate host state' \
  'write files' \
  'read files' \
  'open network connections' \
  'call server code' \
  'call update code' \
  'call recovery code' \
  'call hardware code' \
  'broaden L-UI behavior' \
  'weaken semantic validation' \
  'accept literal source-buffer NUL' \
  'imply a compiler, interpreter, runtime, package manager, sandbox, or operating-system surface'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-lat-language-grammar-implementation-plan.sh' "$doc"
require_contains 'Lat grammar parser implementation code may be added only after this plan is merged.' "$doc"

printf 'lat_language_grammar_implementation_plan: ok\n'

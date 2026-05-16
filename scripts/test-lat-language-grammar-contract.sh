#!/usr/bin/env sh
set -eu

doc="docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lat language grammar contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'lat language grammar contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: Lat language grammar contract' "$doc"
require_contains 'It does not implement a parser, compiler, interpreter, runtime, package format, command behavior, Nucleus task execution, LIR lowering, L-UI rendering, or operating-system behavior.' "$doc"
require_contains 'Naming boundary' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'First grammar target' "$doc"
require_contains 'Source unit' "$doc"
require_contains 'Initial declaration kinds' "$doc"
require_contains 'Lexical grammar' "$doc"
require_contains 'Comment policy' "$doc"
require_contains 'String literal policy' "$doc"
require_contains 'Effect literals' "$doc"
require_contains 'State declaration grammar' "$doc"
require_contains 'Policy declaration grammar' "$doc"
require_contains 'Transition declaration grammar' "$doc"
require_contains 'Assertion declaration grammar' "$doc"
require_contains 'Effect declaration grammar' "$doc"
require_contains 'Expression grammar' "$doc"
require_contains 'Module report model' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'LIR relationship' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Future implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/LANGUAGE_NAMING_POLICY.md \
  docs/LANGUAGE_STRATEGY.md \
  docs/LIR_SHAPE_CONTRACT.md \
  docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/EFFECT_GATES.md \
  docs/STATE_LATTICE.md \
  docs/TRI_PLANE_TRANSITION.md \
  docs/NUCLEUS_PREVIEW.md \
  include/latticra/lir.h \
  include/latticra/state_lattice.h
do
  require_contains "$related" "$doc"
done

for naming in \
  'Lat / Latticra Language' \
  '.lat' \
  'Plain `L` is not the public language name' \
  '`.l` is not the canonical source extension'
do
  require_contains "$naming" "$doc"
done

for target in \
  Lat-Core \
  'Lat-Orch remains future work' \
  'state, policy, assertion, and transition declaration subset'
do
  require_contains "$target" "$doc"
done

for decl in \
  state \
  policy \
  transition \
  assertion \
  effect
do
  require_contains "$decl" "$doc"
done

for lexical in \
  identifier \
  keyword \
  string_literal \
  integer_literal \
  boolean_literal \
  effect_literal \
  operator \
  punctuation \
  comment \
  whitespace \
  '[A-Za-z_][A-Za-z0-9_]*'
do
  require_contains "$lexical" "$doc"
done

for keyword in \
  module \
  require \
  ensure \
  where \
  true \
  false \
  local_mutation \
  host_mutation \
  network \
  hardware \
  recovery \
  external
do
  require_contains "$keyword" "$doc"
done

for escape in \
  '\\' \
  '\"' \
  '\n' \
  '\r' \
  '\t' \
  '\xHH' \
  'Escaped decoded NUL through `\x00`' \
  'Literal source-buffer NUL bytes remain forbidden.'
do
  require_contains "$escape" "$doc"
done

for state_field in \
  origin \
  route \
  axis \
  path \
  breadcrumb \
  trace \
  safe_portal \
  rollback \
  health \
  risk \
  lock \
  dark_phase \
  host_effect \
  external_effect
do
  require_contains "$state_field" "$doc"
done

for expr in \
  comparison_expression \
  logical_and_expression \
  logical_or_expression \
  parenthesized_expression \
  '==' \
  '!=' \
  '<=' \
  '>=' \
  '&&' \
  '||'
do
  require_contains "$expr" "$doc"
done

for report in \
  'LAT GRAMMAR REPORT' \
  'module=<module-name>' \
  'state_count=<count>' \
  'policy_count=<count>' \
  'transition_count=<count>' \
  'assertion_count=<count>' \
  'effect_count=<count>'
do
  require_contains "$report" "$doc"
done

for span in \
  'module declarations' \
  'state declarations' \
  'policy declarations' \
  'transition declarations' \
  'assertion declarations' \
  'effect declarations' \
  'field assignments' \
  'require clauses' \
  'ensure clauses' \
  'effect clauses' \
  'string literals' \
  'identifier references'
do
  require_contains "$span" "$doc"
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
  'language naming policy' \
  '.lat canonical extension' \
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

for gate in \
  'public API shape' \
  'parser result structs' \
  'AST structs' \
  'capacity constants' \
  'error enum labels' \
  'diagnostic/report format' \
  'accepted fixture paths' \
  'parser ownership rules' \
  'string literal handling' \
  'source-span mapping' \
  'exact tests' \
  'compatibility expectations' \
  'non-claims'
do
  require_contains "$gate" "$doc"
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
  lat_grammar_does_not_lower_to_lir \
  lat_grammar_does_not_execute_declarations \
  lat_grammar_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for forbidden in \
  'claim plain `L` as the public language name' \
  'claim `.l` as the canonical source extension' \
  'implement a parser before an implementation plan' \
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
  'remove escaped decoded NUL support' \
  'imply a compiler, interpreter, runtime, package manager, sandbox, or operating-system surface'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-lat-language-grammar-contract.sh' "$doc"

printf 'lat_language_grammar_contract: ok\n'

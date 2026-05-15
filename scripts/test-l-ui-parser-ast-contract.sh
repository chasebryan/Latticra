#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_AST_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui parser ast contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser ast contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: AST contract' "$doc"
require_contains 'This document does not implement an AST.' "$doc"
require_contains 'AST purpose' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Ownership rule' "$doc"
require_contains 'Public API rule' "$doc"
require_contains 'Proposed capacity constants' "$doc"
require_contains 'Proposed node kinds' "$doc"
require_contains 'Card node' "$doc"
require_contains 'Rail node' "$doc"
require_contains 'Field node' "$doc"
require_contains 'Text node' "$doc"
require_contains 'Source-span usage' "$doc"
require_contains 'AST result shape' "$doc"
require_contains 'AST report shape' "$doc"
require_contains 'Initial accepted fixture' "$doc"
require_contains 'Diagnostics relationship' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Non-claims' "$doc"

for constant in \
  LATTICRA_L_UI_AST_RAIL_MAX \
  LATTICRA_L_UI_AST_FIELD_MAX \
  LATTICRA_L_UI_AST_TEXT_MAX \
  LATTICRA_L_UI_AST_LABEL_MAX \
  LATTICRA_L_UI_AST_BINDING_MAX \
  LATTICRA_L_UI_AST_PURPOSE_MAX \
  LATTICRA_L_UI_AST_REPORT_MAX
do
  require_contains "$constant" "$doc"
done

for node_kind in \
  card \
  rail \
  field \
  text \
  binding \
  layout \
  theme \
  action \
  condition
do
  require_contains "$node_kind" "$doc"
done

for field in \
  card_name \
  purpose \
  boundary \
  effect \
  rail_count \
  field_count \
  text_count \
  first_field_index \
  first_text_index \
  binding_span \
  source spans
do
  require_contains "$field" "$doc"
done

for rail in \
  top \
  state \
  trace \
  safety \
  gates \
  effects \
  policy \
  execution \
  bottom
do
  require_contains "$rail" "$doc"
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
  valid_fixture_builds_ast_summary \
  ast_card_name_is_nucleus_preview \
  ast_counts_match_fixture \
  ast_preserves_effect_none \
  ast_preserves_boundary_preview_only \
  ast_contains_required_rails \
  ast_contains_required_fields \
  ast_contains_text_nodes \
  ast_nodes_have_source_spans \
  ast_bindings_have_binding_spans \
  ast_rejects_failed_parse \
  ast_preserves_no_effect_flags \
  ast_report_contains_required_fields \
  ast_report_is_deterministic \
  ast_capacity_limits_are_enforced \
  ast_does_not_retain_source_pointers \
  ast_labels_are_stable
do
  require_contains "$test_name" "$doc"
done

for forbidden in \
  'add file I/O to parser code' \
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
  'accept unsupported effects' \
  'treat text nodes as commands' \
  'treat bindings as executable references'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_parser_ast_contract: ok\n'

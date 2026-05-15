#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_AST_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui parser ast implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser ast implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'The AST implementation should be in C.' "$doc"
require_contains 'Public API change' "$doc"
require_contains 'Proposed capacity constants' "$doc"
require_contains 'AST node kind enum' "$doc"
require_contains 'Card struct' "$doc"
require_contains 'Rail struct' "$doc"
require_contains 'Field struct' "$doc"
require_contains 'Text struct' "$doc"
require_contains 'AST result struct' "$doc"
require_contains 'Public API plan' "$doc"
require_contains 'Module shape' "$doc"
require_contains 'Ownership and lifetime rules' "$doc"
require_contains 'Source-span integration' "$doc"
require_contains 'Successful parse rule' "$doc"
require_contains 'First accepted fixture summary' "$doc"
require_contains 'AST report shape' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Required rails' "$doc"
require_contains 'Required field names' "$doc"
require_contains 'Required text values' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Implementation gate' "$doc"
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

for api in \
  latticra_l_ui_ast_node_kind_label \
  latticra_l_ui_parse_ast \
  latticra_l_ui_ast_report
do
  require_contains "$api" "$doc"
done

for type_name in \
  latticra_l_ui_ast_node_kind_t \
  latticra_l_ui_ast_card_t \
  latticra_l_ui_ast_rail_t \
  latticra_l_ui_ast_field_t \
  latticra_l_ui_ast_text_t \
  latticra_l_ui_ast_result_t
do
  require_contains "$type_name" "$doc"
done

for node_kind in \
  LATTICRA_L_UI_AST_NODE_CARD \
  LATTICRA_L_UI_AST_NODE_RAIL \
  LATTICRA_L_UI_AST_NODE_FIELD \
  LATTICRA_L_UI_AST_NODE_TEXT \
  LATTICRA_L_UI_AST_NODE_BINDING \
  LATTICRA_L_UI_AST_NODE_UNKNOWN
do
  require_contains "$node_kind" "$doc"
done

for field in \
  name \
  purpose \
  effect \
  boundary \
  span \
  first_field_index \
  first_text_index \
  binding_span \
  parse_result \
  rails \
  fields \
  texts
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

for field_name in \
  origin \
  route \
  axis \
  path \
  breadcrumb \
  trace \
  health \
  risk \
  lock \
  dark_phase \
  safe_portal \
  rollback \
  host \
  external \
  requested \
  request \
  policy \
  reason \
  executed \
  mutation \
  server \
  recovery \
  hardware
do
  require_contains "$field_name" "$doc"
done

for text_value in \
  'Latticra / Nucleus Preview / effect-bound' \
  'preview-only no-live-movement no-host-effect no-external-effect'
do
  require_contains "$text_value" "$doc"
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
  ast_labels_are_stable \
  ast_node_kind_labels_are_stable
do
  require_contains "$test_name" "$doc"
done

for path in \
  src/l_ui_parser_ast.c \
  tests/l_ui_parser_ast_invariants.c \
  scripts/test-l-ui-parser-ast.sh \
  docs/L_UI_PARSER_AST_IMPLEMENTATION.md \
  .github/workflows/c.yml
do
  require_contains "$path" "$doc"
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

printf 'l_ui_parser_ast_implementation_plan: ok\n'

#!/usr/bin/env sh
set -eu

doc="docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lir shape implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'lir shape implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement LIR.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Implementation files' "$doc"
require_contains 'Public header plan' "$doc"
require_contains 'Capacity constants' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Source kind enum' "$doc"
require_contains 'Node kind enum' "$doc"
require_contains 'Edge kind enum' "$doc"
require_contains 'Resolved binding kind enum' "$doc"
require_contains 'Error enum' "$doc"
require_contains 'Node struct' "$doc"
require_contains 'Edge struct' "$doc"
require_contains 'Binding reference struct' "$doc"
require_contains 'Text reference struct' "$doc"
require_contains 'Module struct' "$doc"
require_contains 'L-UI lowering behavior' "$doc"
require_contains 'Initial deterministic node plan' "$doc"
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
  docs/LIR_SHAPE_CONTRACT.md \
  docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md \
  docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md \
  docs/L_UI_PARSER_AST_IMPLEMENTATION.md \
  docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md \
  docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_semantic.c
do
  require_contains "$related" "$doc"
done

for path in \
  include/latticra/lir.h \
  include/latticra/l_ui_parser.h \
  src/lir.c \
  .github/workflows/c.yml \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  tests/lir_shape_invariants.c \
  scripts/test-lir-shape.sh
do
  require_contains "$path" "$doc"
done

for constant in \
  'LATTICRA_LIR_NAME_MAX 64u' \
  'LATTICRA_LIR_VALUE_MAX 128u' \
  'LATTICRA_LIR_BINDING_MAX 96u' \
  'LATTICRA_LIR_NODE_MAX 96u' \
  'LATTICRA_LIR_EDGE_MAX 128u' \
  'LATTICRA_LIR_BINDING_REF_MAX 32u' \
  'LATTICRA_LIR_TEXT_MAX 16u' \
  'LATTICRA_LIR_REPORT_MAX 8192u'
do
  require_contains "$constant" "$doc"
done

for api in \
  latticra_lir_source_kind_t \
  latticra_lir_node_kind_t \
  latticra_lir_edge_kind_t \
  latticra_lir_resolved_binding_kind_t \
  latticra_lir_error_t \
  latticra_lir_node_t \
  latticra_lir_edge_t \
  latticra_lir_binding_ref_t \
  latticra_lir_text_ref_t \
  latticra_lir_module_t \
  latticra_lir_error_label \
  latticra_lir_source_kind_label \
  latticra_lir_node_kind_label \
  latticra_lir_edge_kind_label \
  latticra_lir_resolved_binding_kind_label \
  latticra_lir_lower_l_ui_ast \
  latticra_lir_report
do
  require_contains "$api" "$doc"
done

for source_kind in \
  LATTICRA_LIR_SOURCE_UNKNOWN \
  LATTICRA_LIR_SOURCE_L_UI_CARD \
  LATTICRA_LIR_SOURCE_LAT_MODULE \
  LATTICRA_LIR_SOURCE_INTERNAL_FIXTURE \
  unknown \
  l_ui_card \
  lat_module \
  internal_fixture
do
  require_contains "$source_kind" "$doc"
done

for node_kind in \
  LATTICRA_LIR_NODE_MODULE \
  LATTICRA_LIR_NODE_CARD \
  LATTICRA_LIR_NODE_RAIL \
  LATTICRA_LIR_NODE_FIELD \
  LATTICRA_LIR_NODE_TEXT \
  LATTICRA_LIR_NODE_BINDING \
  LATTICRA_LIR_NODE_EFFECT \
  LATTICRA_LIR_NODE_BOUNDARY \
  LATTICRA_LIR_NODE_UNKNOWN
do
  require_contains "$node_kind" "$doc"
done

for edge_kind in \
  LATTICRA_LIR_EDGE_CONTAINS \
  LATTICRA_LIR_EDGE_BINDS \
  LATTICRA_LIR_EDGE_ANNOTATES \
  LATTICRA_LIR_EDGE_ORDERS_BEFORE \
  LATTICRA_LIR_EDGE_UNKNOWN \
  contains \
  binds \
  annotates \
  orders_before
do
  require_contains "$edge_kind" "$doc"
done

for resolved in \
  LATTICRA_LIR_BINDING_STATE_VALUE \
  LATTICRA_LIR_BINDING_PREVIEW_VALUE \
  LATTICRA_LIR_BINDING_UNSUPPORTED \
  state_value \
  preview_value \
  unsupported
do
  require_contains "$resolved" "$doc"
done

for error in \
  LATTICRA_LIR_OK \
  LATTICRA_LIR_NULL_ARGUMENT \
  LATTICRA_LIR_SEMANTIC_FAILED \
  LATTICRA_LIR_CAPACITY_EXCEEDED \
  LATTICRA_LIR_UNSUPPORTED_SOURCE_KIND \
  LATTICRA_LIR_UNSUPPORTED_NODE_KIND \
  LATTICRA_LIR_UNSUPPORTED_EFFECT \
  LATTICRA_LIR_UNSUPPORTED_BOUNDARY \
  LATTICRA_LIR_INTERNAL_ERROR \
  semantic_failed \
  capacity_exceeded \
  unsupported_source_kind \
  unsupported_node_kind \
  unsupported_effect \
  unsupported_boundary
do
  require_contains "$error" "$doc"
done

for struct_field in \
  'latticra_lir_node_kind_t kind;' \
  'char name[LATTICRA_LIR_NAME_MAX];' \
  'char value[LATTICRA_LIR_VALUE_MAX];' \
  'char binding[LATTICRA_LIR_BINDING_MAX];' \
  'latticra_l_ui_source_span_t source_span;' \
  'size_t parent_index;' \
  'size_t first_child_index;' \
  'size_t child_count;' \
  'unsigned int flags;' \
  'size_t from_index;' \
  'size_t to_index;' \
  'latticra_lir_edge_kind_t edge_kind;' \
  'size_t field_node_index;' \
  'char binding_target[LATTICRA_LIR_BINDING_MAX];' \
  'char binding_prefix[LATTICRA_LIR_NAME_MAX];' \
  'latticra_lir_resolved_binding_kind_t resolved_kind;' \
  'size_t text_node_index;' \
  'size_t value_len;' \
  'char escaped_value[LATTICRA_LIR_VALUE_MAX];' \
  'latticra_lir_error_t error;' \
  'latticra_lir_source_kind_t source_kind;'
do
  require_contains "$struct_field" "$doc"
done

for prerequisite in \
  'ast != NULL' \
  'semantic != NULL' \
  'module != NULL' \
  'ast->parse_result.error == LATTICRA_L_UI_PARSE_OK' \
  'semantic->error == LATTICRA_L_UI_SEMANTIC_OK' \
  'semantic->parser_error == LATTICRA_L_UI_PARSE_OK' \
  'semantic->no_effect == 1' \
  'semantic->execution_allowed == 0' \
  'semantic->mutation_allowed == 0' \
  'semantic->server_allowed == 0' \
  'semantic->recovery_allowed == 0' \
  'semantic->hardware_allowed == 0'
do
  require_contains "$prerequisite" "$doc"
done

for count in \
  '0: module' \
  '1: card' \
  '2-10: rails in current L-UI order' \
  '11-33: fields in current AST order' \
  '34-35: text nodes' \
  '36-58: binding nodes' \
  '59: effect' \
  '60: boundary' \
  'node_count=61' \
  'binding_count=23' \
  'text_count=2' \
  'edge_count >= 60'
do
  require_contains "$count" "$doc"
done

for report in \
  'LATTICRA LIR REPORT' \
  'status=<integer-status>' \
  'error=<lir-error-label>' \
  'source_kind=<source-kind-label>' \
  'module=<module-name>' \
  'card=<card-name>' \
  'node_count=<count>' \
  'edge_count=<count>' \
  'binding_count=<count>' \
  'text_count=<count>' \
  'span_start_offset=<offset>' \
  'span_end_column=<column>'
do
  require_contains "$report" "$doc"
done

for mapping in \
  'module -> ast.card.span' \
  'card -> ast.card.span' \
  'rail -> ast.rails[index].span' \
  'field -> ast.fields[index].span' \
  'binding -> ast.fields[index].binding_span' \
  'text -> ast.texts[index].span' \
  'effect -> ast.card.span' \
  'boundary -> ast.card.span'
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
  lir_shape_accepts_semantically_valid_l_ui_fixture \
  lir_shape_rejects_parser_failed_ast \
  lir_shape_rejects_semantic_failed_ast \
  lir_shape_preserves_card_metadata \
  lir_shape_preserves_rail_nodes \
  lir_shape_preserves_field_nodes \
  lir_shape_preserves_binding_nodes \
  lir_shape_preserves_text_nodes_with_lengths \
  lir_shape_preserves_source_spans \
  lir_shape_preserves_no_effect_flags \
  lir_shape_report_is_deterministic \
  lir_shape_report_rejects_small_buffer \
  lir_shape_does_not_change_ast_report \
  lir_shape_does_not_change_semantic_report \
  lir_shape_does_not_change_escaped_x00_acceptance \
  lir_shape_does_not_change_literal_nul_rejection \
  lir_shape_error_labels_are_stable \
  lir_shape_kind_labels_are_stable \
  lir_shape_is_deterministic
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
  docs/LIR_SHAPE_CONTRACT.md \
  scripts/test-project-strategy-status-framework.sh \
  docs/LIR_SHAPE_IMPLEMENTATION.md
do
  require_contains "$doc_path" "$doc"
done

for compat in \
  'existing parser behavior' \
  'existing parser diagnostic codes' \
  'existing AST construction behavior' \
  'existing detailed AST report behavior' \
  'existing semantic validation behavior' \
  'escaped decoded NUL acceptance' \
  'literal source-buffer NUL rejection' \
  'source-span byte offset behavior' \
  'current accepted fixture counts'
do
  require_contains "$compat" "$doc"
done

for forbidden in \
  'lower invalid semantic input' \
  'execute bindings' \
  'evaluate host state' \
  'call Nucleus task execution' \
  'render L-UI' \
  'execute Lat' \
  'mutate state' \
  'write files' \
  'read files' \
  'open network connections' \
  'call server code' \
  'call update code' \
  'call recovery code' \
  'call hardware code' \
  'broaden accepted syntax' \
  'weaken parser diagnostics' \
  'weaken semantic validation' \
  'accept literal source-buffer NUL' \
  'remove escaped decoded NUL support' \
  'make raw C-string fields authoritative for embedded NUL values'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-lir-shape-implementation-plan.sh' "$doc"
require_contains 'LIR shape implementation code may be added only after this plan is merged.' "$doc"

printf 'lir_shape_implementation_plan: ok\n'

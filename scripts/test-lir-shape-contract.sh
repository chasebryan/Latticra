#!/usr/bin/env sh
set -eu

doc="docs/LIR_SHAPE_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lir shape contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'lir shape contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: LIR shape contract' "$doc"
require_contains 'This document does not implement LIR.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'LIR role' "$doc"
require_contains 'First LIR unit' "$doc"
require_contains 'Source kind' "$doc"
require_contains 'Node kinds' "$doc"
require_contains 'Node shape' "$doc"
require_contains 'Edge shape' "$doc"
require_contains 'Binding shape' "$doc"
require_contains 'Text shape' "$doc"
require_contains 'Effect and boundary shape' "$doc"
require_contains 'Semantic prerequisite' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Report model' "$doc"
require_contains 'Capacity policy' "$doc"
require_contains 'Error model' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Future implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_PARSER_AST_IMPLEMENTATION.md \
  docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md \
  docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md \
  docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md \
  docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md \
  docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_semantic.c
do
  require_contains "$related" "$doc"
done

for pipeline in \
  'source bytes' \
  'structural parser' \
  'AST construction' \
  'semantic validation' \
  'LIR lowering' \
  'future analysis, rendering, planning, or execution only if separately allowed'
do
  require_contains "$pipeline" "$doc"
done

for root in \
  'latticra_lir_module_t' \
  'source_kind' \
  'module_name' \
  'card_name' \
  'node_count' \
  'edge_count' \
  'binding_count' \
  'text_count'
do
  require_contains "$root" "$doc"
done

for source_kind in \
  unknown \
  l_ui_card \
  lat_module \
  internal_fixture
do
  require_contains "$source_kind" "$doc"
done

for node_kind in \
  module \
  card \
  rail \
  field \
  text \
  binding \
  effect \
  boundary
do
  require_contains "$node_kind" "$doc"
done

for node_field in \
  kind \
  name \
  value \
  binding \
  source_span \
  parent_index \
  first_child_index \
  child_count \
  flags
do
  require_contains "$node_field" "$doc"
done

for edge in \
  from_index \
  to_index \
  edge_kind \
  contains \
  binds \
  annotates \
  orders_before
do
  require_contains "$edge" "$doc"
done

for binding_shape in \
  field_node_index \
  binding_target \
  binding_prefix \
  resolved_kind \
  state_value \
  preview_value \
  unsupported
do
  require_contains "$binding_shape" "$doc"
done

for text_shape in \
  text_node_index \
  value_len \
  escaped_value \
  '`value_len` remains authoritative for embedded NUL values' \
  'Raw C-string compatibility fields must not be the assertion target for embedded NUL values.'
do
  require_contains "$text_shape" "$doc"
done

for prereq in \
  'semantic_error=ok' \
  'parser_error=ok' \
  'no_effect=1' \
  'execution_allowed=0' \
  'mutation_allowed=0' \
  'server_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0'
do
  require_contains "$prereq" "$doc"
done

for report in \
  'LATTICRA LIR REPORT' \
  'source_kind=<kind>' \
  'module=<name>' \
  'card=<name>' \
  'node_count=<count>' \
  'edge_count=<count>' \
  'binding_count=<count>' \
  'text_count=<count>'
do
  require_contains "$report" "$doc"
done

for capacity in \
  'LATTICRA_LIR_NODE_MAX' \
  'LATTICRA_LIR_EDGE_MAX' \
  'LATTICRA_LIR_BINDING_MAX' \
  'LATTICRA_LIR_TEXT_MAX' \
  'A future implementation plan must name exact constants before code is added.'
do
  require_contains "$capacity" "$doc"
done

for error in \
  null_argument \
  semantic_failed \
  capacity_exceeded \
  unsupported_source_kind \
  unsupported_node_kind \
  unsupported_effect \
  unsupported_boundary \
  internal_error
do
  require_contains "$error" "$doc"
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

for count in \
  'rail_count=9' \
  'field_count=23' \
  'text_count=2' \
  'effect=none' \
  'boundary=preview_only'
do
  require_contains "$count" "$doc"
done

for gate in \
  'public API shape' \
  'LIR struct names' \
  'capacity constants' \
  'node enum labels' \
  'edge enum labels' \
  'error enum labels' \
  'report format' \
  'semantic prerequisite behavior' \
  'source-span mapping' \
  'exact tests' \
  'compatibility expectations' \
  'non-claims'
do
  require_contains "$gate" "$doc"
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
  lir_shape_is_deterministic
do
  require_contains "$test_name" "$doc"
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

require_contains 'sh scripts/test-lir-shape-contract.sh' "$doc"

printf 'lir_shape_contract: ok\n'

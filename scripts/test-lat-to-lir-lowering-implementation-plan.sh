#!/usr/bin/env sh
set -eu

doc="docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lat-to-lir lowering implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'lat-to-lir lowering implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document is plan-only. It does not implement Lat-to-LIR lowering.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Implementation files' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Capacity constants' "$doc"
require_contains 'Error enum' "$doc"
require_contains 'Result struct' "$doc"
require_contains 'Semantic prerequisite behavior' "$doc"
require_contains 'LIR module metadata mapping' "$doc"
require_contains 'Source-span conversion' "$doc"
require_contains 'Node mapping' "$doc"
require_contains 'Edge mapping' "$doc"
require_contains 'Binding and text counts' "$doc"
require_contains 'Effect handling' "$doc"
require_contains 'Report format' "$doc"
require_contains 'Exact test list' "$doc"
require_contains 'Test command' "$doc"
require_contains 'Documentation update plan' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Implementation boundary' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/LAT_TO_LIR_LOWERING_CONTRACT.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md \
  docs/LAT_SEMANTIC_VALIDATION_CONTRACT.md \
  docs/LAT_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md \
  docs/LAT_LANGUAGE_FOUNDATION_ANALYSIS.md \
  docs/LIR_SHAPE_CONTRACT.md \
  docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  include/latticra/lat_parser.h \
  include/latticra/lat_semantic.h \
  include/latticra/lir.h \
  fixtures/lat/foundation_model.lat
do
  require_contains "$related" "$doc"
done

for file_path in \
  include/latticra/lat_to_lir.h \
  src/lat_to_lir.c \
  tests/lat_to_lir_lowering_invariants.c \
  scripts/test-lat-to-lir-lowering.sh \
  docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md
do
  require_contains "$file_path" "$doc"
done

for api in \
  latticra_lat_to_lir_error_t \
  latticra_lat_to_lir_result_t \
  latticra_lat_to_lir_error_label \
  latticra_lir_lower_lat_module \
  latticra_lat_to_lir_report \
  latticra_lat_parse_result_t \
  latticra_lat_semantic_result_t \
  latticra_lir_module_t
do
  require_contains "$api" "$doc"
done

for capacity in \
  LATTICRA_LAT_TO_LIR_REPORT_MAX \
  LATTICRA_LAT_TO_LIR_MODULE_NODE_COST \
  LATTICRA_LAT_TO_LIR_DECLARATION_NODE_COST \
  LATTICRA_LAT_TO_LIR_CLAUSE_NODE_COST \
  LATTICRA_LAT_TO_LIR_DECLARATION_EDGE_COST \
  LATTICRA_LAT_TO_LIR_CLAUSE_EDGE_COST \
  LATTICRA_LAT_TO_LIR_TRANSITION_SOURCE_EDGE_COST \
  '1 + declaration_count + clause_count' \
  'declaration_count + clause_count + transition_count'
do
  require_contains "$capacity" "$doc"
done

for error in \
  LATTICRA_LAT_TO_LIR_OK \
  LATTICRA_LAT_TO_LIR_NULL_ARGUMENT \
  LATTICRA_LAT_TO_LIR_PARSE_NOT_OK \
  LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK \
  LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID \
  LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION \
  LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED \
  LATTICRA_LAT_TO_LIR_UNSUPPORTED_DECLARATION_KIND \
  LATTICRA_LAT_TO_LIR_UNSUPPORTED_CLAUSE_KIND \
  LATTICRA_LAT_TO_LIR_UNSUPPORTED_EFFECT \
  LATTICRA_LAT_TO_LIR_UNSUPPORTED_LIR_SHAPE \
  LATTICRA_LAT_TO_LIR_INTERNAL_ERROR \
  semantic_not_valid \
  no_effect_violation \
  unsupported_lir_shape
do
  require_contains "$error" "$doc"
done

for result_field in \
  declaration_count \
  state_count \
  policy_count \
  transition_count \
  assertion_count \
  effect_count \
  clause_count \
  node_count \
  edge_count \
  binding_count \
  text_count \
  no_effect \
  execution_allowed \
  mutation_allowed \
  server_allowed \
  recovery_allowed \
  hardware_allowed
do
  require_contains "$result_field" "$doc"
done

for prereq in \
  'parse_result->error != LATTICRA_LAT_PARSE_OK' \
  'semantic_result->error != LATTICRA_LAT_SEMANTIC_OK' \
  'semantic_result->semantic_valid != 1' \
  'no_effect=1' \
  'execution_allowed=0' \
  'mutation_allowed=0' \
  'server_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0'
do
  require_contains "$prereq" "$doc"
done

for module_mapping in \
  'module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE' \
  'module->module_name = parse_result->module.module_name' \
  'module->card_name = ""' \
  'module->effect = "none"' \
  'module->boundary = "lat_semantic_only"'
do
  require_contains "$module_mapping" "$doc"
done

for node_mapping in \
  'Lat module declaration -> LATTICRA_LIR_NODE_MODULE' \
  'state declaration      -> LATTICRA_LIR_NODE_FIELD' \
  'policy declaration     -> LATTICRA_LIR_NODE_FIELD' \
  'transition declaration -> LATTICRA_LIR_NODE_FIELD' \
  'assertion declaration  -> LATTICRA_LIR_NODE_FIELD' \
  'effect declaration     -> LATTICRA_LIR_NODE_EFFECT' \
  'field clause           -> LATTICRA_LIR_NODE_FIELD' \
  'require clause         -> LATTICRA_LIR_NODE_BINDING' \
  'ensure clause          -> LATTICRA_LIR_NODE_BINDING' \
  'effect clause          -> LATTICRA_LIR_NODE_EFFECT'
do
  require_contains "$node_mapping" "$doc"
done

for edge_mapping in \
  'module contains declaration -> LATTICRA_LIR_EDGE_CONTAINS' \
  'declaration contains clause -> LATTICRA_LIR_EDGE_CONTAINS' \
  'transition references source state -> LATTICRA_LIR_EDGE_BINDS'
do
  require_contains "$edge_mapping" "$doc"
done

for report in \
  'LAT TO LIR LOWERING REPORT' \
  'status=<integer-status>' \
  'error=<error-label>' \
  'module=<module-name>' \
  'clause_count=<count>' \
  'node_count=<count>' \
  'edge_count=<count>' \
  'binding_count=<count>' \
  'text_count=<count>' \
  'span_start_offset=<offset>'
do
  require_contains "$report" "$doc"
done

for test_name in \
  lat_to_lir_rejects_null_arguments \
  lat_to_lir_rejects_parse_error \
  lat_to_lir_rejects_semantic_error \
  lat_to_lir_rejects_semantic_not_valid \
  lat_to_lir_accepts_foundation_model \
  lat_to_lir_sets_source_kind_lat_module \
  lat_to_lir_preserves_module_name \
  lat_to_lir_preserves_declaration_counts \
  lat_to_lir_preserves_transition_source_metadata \
  lat_to_lir_preserves_effect_none \
  lat_to_lir_preserves_source_spans \
  lat_to_lir_preserves_no_effect_flags \
  lat_to_lir_counts_nodes_and_edges_deterministically \
  lat_to_lir_report_is_deterministic \
  lat_to_lir_report_rejects_small_buffer \
  lat_to_lir_error_labels_are_stable \
  lat_to_lir_does_not_execute_lat \
  lat_to_lir_does_not_mutate_state \
  lat_to_lir_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for compile_item in \
  '-std=c99 -Wall -Wextra -Werror -pedantic' \
  src/lat_parser.c \
  src/lat_semantic.c \
  src/lat_to_lir.c \
  src/lir.c \
  tests/lat_to_lir_lowering_invariants.c
do
  require_contains "$compile_item" "$doc"
done

for forbidden in \
  'execute Lat declarations' \
  'interpret transition behavior' \
  'mutate state' \
  'render L-UI' \
  'call Nucleus task execution' \
  'evaluate host state' \
  'write files' \
  'read files' \
  'open network connections' \
  'call update code' \
  'call recovery code' \
  'call hardware code' \
  'broaden accepted Lat syntax' \
  'weaken Lat semantic validation' \
  'weaken existing LIR shape behavior' \
  'invent source byte offsets' \
  'imply a compiler, interpreter, runtime, package manager, or operating-system surface'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-lat-to-lir-lowering-implementation-plan.sh' "$doc"
require_contains 'Lat-to-LIR lowering implementation code may be added only after this plan is merged and guarded.' "$doc"

printf 'lat_to_lir_lowering_implementation_plan: ok\n'

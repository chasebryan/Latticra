#!/usr/bin/env sh
set -eu

doc="docs/LAT_TO_LIR_LOWERING_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'lat-to-lir lowering contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'lat-to-lir lowering contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: Lat-to-LIR lowering contract' "$doc"
require_contains 'This is contract-only work. It does not implement lowering code.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'First lowering target' "$doc"
require_contains 'Input prerequisite' "$doc"
require_contains 'Output target' "$doc"
require_contains 'Proposed public API boundary' "$doc"
require_contains 'Node mapping rules' "$doc"
require_contains 'Edge mapping rules' "$doc"
require_contains 'Source-span preservation' "$doc"
require_contains 'Effect preservation' "$doc"
require_contains 'Report model' "$doc"
require_contains 'Error model' "$doc"
require_contains 'Capacity policy' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Future implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md \
  docs/LAT_SEMANTIC_VALIDATION_CONTRACT.md \
  docs/LAT_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md \
  docs/LAT_LANGUAGE_FOUNDATION_ANALYSIS.md \
  docs/LIR_SHAPE_CONTRACT.md \
  docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  include/latticra/lat_parser.h \
  include/latticra/lat_semantic.h \
  include/latticra/lir.h
do
  require_contains "$related" "$doc"
done

for pipeline in \
  'Lat source -> bounded grammar parser -> Lat semantic validation -> future Lat-to-LIR lowering' \
  'Lat-Core semantic module -> LIR module metadata' \
  'Lat-Orch remains future work.'
do
  require_contains "$pipeline" "$doc"
done

for prereq in \
  'parser_error=ok' \
  'semantic_error=ok' \
  'semantic_valid=1' \
  'no_effect=1' \
  'execution_allowed=0' \
  'mutation_allowed=0' \
  'server_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0'
do
  require_contains "$prereq" "$doc"
done

for target in \
  'latticra_lir_module_t' \
  'lat_module' \
  'latticra_lir_lower_lat_module' \
  'latticra_lat_parse_result_t' \
  'latticra_lat_semantic_result_t'
do
  require_contains "$target" "$doc"
done

for mapping in \
  'Lat module      -> LIR module node' \
  'state           -> LIR node kind field' \
  'policy          -> LIR node kind field' \
  'transition      -> LIR node kind field' \
  'assertion       -> LIR node kind field' \
  'effect          -> LIR effect node' \
  'require clause  -> LIR binding or metadata node' \
  'ensure clause   -> LIR binding or metadata node' \
  'field assignment -> LIR field metadata'
do
  require_contains "$mapping" "$doc"
done

for edge in \
  'module contains declaration' \
  'declaration contains clause' \
  'transition references source state' \
  'policy annotates requirement metadata' \
  'assertion annotates checked metadata' \
  'effect annotates effect boundary metadata'
do
  require_contains "$edge" "$doc"
done

for span in \
  'module span comes from the Lat module span' \
  'declaration span comes from the Lat declaration span' \
  'clause span comes from the Lat clause span' \
  'lowering must not invent byte offsets'
do
  require_contains "$span" "$doc"
done

for report in \
  'LAT TO LIR LOWERING REPORT' \
  'source_kind=lat_module' \
  'module=<module-name>' \
  'declaration_count=<count>' \
  'state_count=<count>' \
  'policy_count=<count>' \
  'transition_count=<count>' \
  'assertion_count=<count>' \
  'effect_count=<count>' \
  'node_count=<count>' \
  'edge_count=<count>'
do
  require_contains "$report" "$doc"
done

for error in \
  null_argument \
  parse_not_ok \
  semantic_not_ok \
  semantic_not_valid \
  capacity_exceeded \
  unsupported_declaration_kind \
  unsupported_clause_kind \
  unsupported_effect \
  unsupported_lir_shape \
  internal_error
do
  require_contains "$error" "$doc"
done

for gate in \
  'public API shape' \
  'exact error enum labels' \
  'exact node mapping' \
  'exact edge mapping' \
  'exact capacity accounting' \
  'source-span mapping' \
  'report format' \
  'semantic prerequisite behavior' \
  'compatibility expectations' \
  'exact tests' \
  'non-claims'
do
  require_contains "$gate" "$doc"
done

for test_name in \
  lat_to_lir_rejects_parse_error \
  lat_to_lir_rejects_semantic_error \
  lat_to_lir_accepts_foundation_model \
  lat_to_lir_sets_source_kind_lat_module \
  lat_to_lir_preserves_module_name \
  lat_to_lir_preserves_declaration_counts \
  lat_to_lir_preserves_transition_source_metadata \
  lat_to_lir_preserves_effect_none \
  lat_to_lir_preserves_source_spans \
  lat_to_lir_preserves_no_effect_flags \
  lat_to_lir_report_is_deterministic \
  lat_to_lir_report_rejects_small_buffer \
  lat_to_lir_does_not_execute_lat \
  lat_to_lir_does_not_mutate_state \
  lat_to_lir_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for forbidden in \
  'lower parser-failed input' \
  'lower semantic-failed input' \
  'execute Lat declarations' \
  'interpret transition behavior' \
  'mutate state' \
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
  'broaden accepted Lat syntax' \
  'weaken Lat semantic validation' \
  'weaken existing LIR shape behavior' \
  'invent source byte offsets' \
  'imply a compiler, interpreter, runtime, package manager, or operating-system surface'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-lat-to-lir-lowering-contract.sh' "$doc"

printf 'lat_to_lir_lowering_contract: ok\n'

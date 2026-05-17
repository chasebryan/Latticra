#!/usr/bin/env sh
set -eu

doc="docs/L_UI_RENDERING_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui rendering contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui rendering contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: L-UI rendering contract' "$doc"
require_contains 'This document does not implement L-UI rendering.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Rendering role' "$doc"
require_contains 'First rendering unit' "$doc"
require_contains 'Input prerequisites' "$doc"
require_contains 'Render modes' "$doc"
require_contains 'Output target' "$doc"
require_contains 'Rendered report model' "$doc"
require_contains 'Suggested section order' "$doc"
require_contains 'Rail rendering' "$doc"
require_contains 'Field and binding rendering' "$doc"
require_contains 'Text rendering' "$doc"
require_contains 'Source-span rendering' "$doc"
require_contains 'LIR rendering' "$doc"
require_contains 'Authority rendering' "$doc"
require_contains 'Error model' "$doc"
require_contains 'Capacity policy' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Future implementation gate' "$doc"
require_contains 'Future file policy' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_PARSER_AST_IMPLEMENTATION.md \
  docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md \
  docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md \
  docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md \
  docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md \
  docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md \
  docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md \
  docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  include/latticra/lir.h \
  include/latticra/cpp/authority.hpp \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_semantic.c \
  src/lir.c \
  src/cpp/authority.cpp
do
  require_contains "$related" "$doc"
done

for pipeline in \
  'source bytes' \
  'structural parser' \
  'AST construction' \
  'semantic validation' \
  'LIR lowering' \
  'constrained authority validation' \
  'L-UI rendering' \
  'operator-visible text output'
do
  require_contains "$pipeline" "$doc"
done

for unit in \
  'latticra_l_ui_render_result_t' \
  'latticra_l_ui_render_request_t' \
  card \
  rail \
  field \
  text \
  binding \
  effect \
  boundary \
  source_span \
  authority
do
  require_contains "$unit" "$doc"
done

for prereq in \
  'parser_error=ok' \
  'semantic_error=ok' \
  'lir_error=ok' \
  'authority_status=ok' \
  'no_effect=1' \
  'execution_allowed=0' \
  'mutation_allowed=0' \
  'server_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0'
do
  require_contains "$prereq" "$doc"
done

for mode in \
  summary \
  detailed \
  diagnostics_only \
  authority_only \
  'Render modes must not imply interactive UI, live terminal control, command execution, or event handling.'
do
  require_contains "$mode" "$doc"
done

for output_rule in \
  'caller-provided char buffer' \
  'explicit buffer length' \
  'NUL-terminated on success' \
  'cleared on too-small failure' \
  'no heap allocation' \
  'no file output' \
  'no terminal escape control by default' \
  'stdout' \
  'stderr' \
  'sockets' \
  'devices'
do
  require_contains "$output_rule" "$doc"
done

for report in \
  'LATTICRA L-UI RENDER REPORT' \
  'status=<status-label>' \
  'mode=<render-mode-label>' \
  'card=<card-name>' \
  'effect=<effect-label>' \
  'boundary=<boundary-label>' \
  'rail_count=<count>' \
  'field_count=<count>' \
  'text_count=<count>' \
  'binding_count=<count>' \
  'node_count=<count>' \
  'edge_count=<count>'
do
  require_contains "$report" "$doc"
done

for section in \
  HEADER \
  CARD \
  AUTHORITY \
  RAILS \
  FIELDS \
  TEXT \
  BINDINGS \
  LIR \
  SOURCE_SPANS \
  NO_EFFECT_FLAGS
do
  require_contains "$section" "$doc"
done

for rail_render in \
  'rail index' \
  'rail name' \
  'field count' \
  'text count' \
  'source span' \
  'must not invent rails or reorder them'
do
  require_contains "$rail_render" "$doc"
done

for field_render in \
  'field index' \
  'field name' \
  'binding target' \
  'binding prefix' \
  'binding source span' \
  'Bindings remain symbolic.'
do
  require_contains "$field_render" "$doc"
done

for text_rule in \
  'value_len is authoritative' \
  'escaped output is used for operator-visible text' \
  'escaped decoded NUL through \x00 remains representable' \
  'literal source-buffer NUL remains rejected before rendering' \
  'raw C-string fields are not authoritative for embedded NUL values'
do
  require_contains "$text_rule" "$doc"
done

for span in \
  start_offset \
  end_offset \
  start_line \
  start_column \
  end_line \
  end_column \
  'must not invent byte positions'
do
  require_contains "$span" "$doc"
done

for lir in \
  source_kind \
  module_name \
  card_name \
  node_count \
  edge_count \
  binding_count \
  text_count \
  'Rendering must not execute LIR'
do
  require_contains "$lir" "$doc"
done

for authority in \
  'authority status' \
  'authority validator' \
  'authority requested effect' \
  'authority denial reason' \
  'authority no-effect flags' \
  'must not broaden authority'
do
  require_contains "$authority" "$doc"
done

for error in \
  ok \
  null_argument \
  invalid_input \
  parser_failed \
  semantic_failed \
  lir_failed \
  authority_failed \
  capacity_exceeded \
  unsupported_render_mode \
  unsupported_effect \
  unsupported_boundary \
  internal_error
do
  require_contains "$error" "$doc"
done

for capacity in \
  LATTICRA_L_UI_RENDER_REPORT_MAX \
  LATTICRA_L_UI_RENDER_LINE_MAX \
  LATTICRA_L_UI_RENDER_SECTION_MAX \
  'Small output buffers should return a stable capacity error and clear the output buffer.'
do
  require_contains "$capacity" "$doc"
done

for compat in \
  'existing parser behavior' \
  'existing parser diagnostic codes' \
  'existing AST construction behavior' \
  'existing detailed AST report behavior' \
  'existing escaped string report behavior' \
  'existing source-backed text behavior' \
  'existing length-carrying string behavior' \
  'existing decoded NUL acceptance' \
  'existing literal source-buffer NUL rejection' \
  'existing semantic validation behavior' \
  'existing LIR shape behavior' \
  'existing constrained C++ authority behavior' \
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
  'implementation language' \
  'public API shape' \
  'public header path' \
  'source file path' \
  'render request struct' \
  'render result struct' \
  'render mode enum' \
  'render error enum' \
  'capacity constants' \
  'output buffer rules' \
  'section order' \
  'source-span rendering rules' \
  'embedded NUL rendering rules' \
  'authority metadata rendering rules' \
  'exact tests' \
  'compatibility expectations' \
  'non-claims'
do
  require_contains "$gate" "$doc"
done

for path in \
  include/latticra/l_ui_renderer.h \
  src/l_ui_renderer.c \
  tests/l_ui_rendering_invariants.c \
  scripts/test-l-ui-rendering.sh \
  docs/L_UI_RENDERING_IMPLEMENTATION_PLAN.md \
  docs/L_UI_RENDERING_IMPLEMENTATION.md
do
  require_contains "$path" "$doc"
done

for test_name in \
  l_ui_rendering_accepts_semantically_valid_l_ui_fixture \
  l_ui_rendering_requires_semantic_success \
  l_ui_rendering_requires_lir_success \
  l_ui_rendering_requires_authority_success \
  l_ui_rendering_preserves_card_metadata \
  l_ui_rendering_preserves_rail_order \
  l_ui_rendering_preserves_field_bindings \
  l_ui_rendering_preserves_text_lengths \
  l_ui_rendering_preserves_escaped_x00_visibility \
  l_ui_rendering_preserves_source_spans \
  l_ui_rendering_preserves_no_effect_flags \
  l_ui_rendering_report_is_deterministic \
  l_ui_rendering_report_rejects_small_buffer \
  l_ui_rendering_does_not_change_ast_report \
  l_ui_rendering_does_not_change_lir_report \
  l_ui_rendering_does_not_execute_bindings \
  l_ui_rendering_does_not_call_nucleus_execution \
  l_ui_rendering_is_deterministic
do
  require_contains "$test_name" "$doc"
done

for forbidden in \
  'render parser-failed input as a valid surface' \
  'render semantic-failed input as a valid surface' \
  'render LIR-failed input as a valid surface' \
  'bypass constrained authority validation' \
  'execute bindings' \
  'evaluate host state' \
  'evaluate runtime state' \
  'call Nucleus task execution' \
  'execute Lat' \
  'execute LIR' \
  'mutate state' \
  'write files' \
  'read files' \
  'open network connections' \
  'call server code' \
  'call update code' \
  'call recovery code' \
  'call hardware code' \
  'emit terminal escape control by default' \
  'create an interactive UI loop' \
  'broaden accepted syntax' \
  'weaken parser diagnostics' \
  'weaken semantic validation' \
  'weaken LIR validation' \
  'weaken constrained C++ authority validation' \
  'accept literal source-buffer NUL' \
  'remove escaped decoded NUL support' \
  'make raw C-string fields authoritative for embedded NUL values' \
  'imply a production UI, runtime, sandbox, malware prevention, ransomware prevention, or operating-system surface'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-l-ui-rendering-contract.sh' "$doc"

printf 'l_ui_rendering_contract: ok\n'

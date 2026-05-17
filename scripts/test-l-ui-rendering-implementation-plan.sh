#!/usr/bin/env sh
set -eu

doc="docs/L_UI_RENDERING_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui rendering implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui rendering implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement L-UI rendering.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Implementation files' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Capacity constants' "$doc"
require_contains 'Render error enum' "$doc"
require_contains 'Render mode enum' "$doc"
require_contains 'Authority summary struct' "$doc"
require_contains 'Render request struct' "$doc"
require_contains 'Render result struct' "$doc"
require_contains 'Input prerequisite behavior' "$doc"
require_contains 'Output buffer rules' "$doc"
require_contains 'Report format' "$doc"
require_contains 'Section order' "$doc"
require_contains 'Rail rendering rules' "$doc"
require_contains 'Field and binding rendering rules' "$doc"
require_contains 'Text rendering rules' "$doc"
require_contains 'Source-span rendering rules' "$doc"
require_contains 'LIR rendering rules' "$doc"
require_contains 'Authority metadata rendering rules' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation update plan' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_RENDERING_CONTRACT.md \
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

for path in \
  include/latticra/l_ui_renderer.h \
  src/l_ui_renderer.c \
  tests/l_ui_rendering_invariants.c \
  scripts/test-l-ui-rendering.sh \
  .github/workflows/c.yml \
  docs/L_UI_RENDERING_IMPLEMENTATION.md
do
  require_contains "$path" "$doc"
done

for api in \
  latticra_l_ui_render_error_t \
  latticra_l_ui_render_mode_t \
  latticra_l_ui_render_authority_summary_t \
  latticra_l_ui_render_request_t \
  latticra_l_ui_render_result_t \
  latticra_l_ui_render_error_label \
  latticra_l_ui_render_mode_label \
  latticra_l_ui_render \
  latticra_l_ui_render_report
do
  require_contains "$api" "$doc"
done

for constant in \
  'LATTICRA_L_UI_RENDER_LABEL_MAX 64u' \
  'LATTICRA_L_UI_RENDER_REASON_MAX 128u' \
  'LATTICRA_L_UI_RENDER_REPORT_MAX 16384u' \
  'LATTICRA_L_UI_RENDER_LINE_MAX 512u' \
  'LATTICRA_L_UI_RENDER_SECTION_MAX 16u' \
  'LATTICRA_L_UI_RENDER_AUTHORITY_REPORT_MAX 4096u'
do
  require_contains "$constant" "$doc"
done

for error in \
  LATTICRA_L_UI_RENDER_OK \
  LATTICRA_L_UI_RENDER_NULL_ARGUMENT \
  LATTICRA_L_UI_RENDER_INVALID_INPUT \
  LATTICRA_L_UI_RENDER_PARSER_FAILED \
  LATTICRA_L_UI_RENDER_SEMANTIC_FAILED \
  LATTICRA_L_UI_RENDER_LIR_FAILED \
  LATTICRA_L_UI_RENDER_AUTHORITY_FAILED \
  LATTICRA_L_UI_RENDER_CAPACITY_EXCEEDED \
  LATTICRA_L_UI_RENDER_UNSUPPORTED_RENDER_MODE \
  LATTICRA_L_UI_RENDER_UNSUPPORTED_EFFECT \
  LATTICRA_L_UI_RENDER_UNSUPPORTED_BOUNDARY \
  LATTICRA_L_UI_RENDER_INTERNAL_ERROR
do
  require_contains "$error" "$doc"
done

for label in \
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
  internal_error \
  summary \
  detailed \
  diagnostics_only \
  authority_only
do
  require_contains "$label" "$doc"
done

for mode in \
  LATTICRA_L_UI_RENDER_MODE_SUMMARY \
  LATTICRA_L_UI_RENDER_MODE_DETAILED \
  LATTICRA_L_UI_RENDER_MODE_DIAGNOSTICS_ONLY \
  LATTICRA_L_UI_RENDER_MODE_AUTHORITY_ONLY
do
  require_contains "$mode" "$doc"
done

for field in \
  'latticra_status_t status;' \
  'char status_label[LATTICRA_L_UI_RENDER_LABEL_MAX];' \
  'char validator_label[LATTICRA_L_UI_RENDER_LABEL_MAX];' \
  'char requested_effect_label[LATTICRA_L_UI_RENDER_LABEL_MAX];' \
  'char denial_reason[LATTICRA_L_UI_RENDER_REASON_MAX];' \
  'latticra_l_ui_render_mode_t mode;' \
  'const latticra_l_ui_ast_result_t *ast;' \
  'const latticra_l_ui_semantic_result_t *semantic;' \
  'const latticra_lir_module_t *lir;' \
  'const latticra_l_ui_render_authority_summary_t *authority;' \
  'latticra_l_ui_render_error_t error;' \
  'char card_name[LATTICRA_L_UI_RENDER_LABEL_MAX];' \
  'char effect[LATTICRA_L_UI_RENDER_LABEL_MAX];' \
  'char boundary[LATTICRA_L_UI_RENDER_LABEL_MAX];' \
  'size_t rail_count;' \
  'size_t field_count;' \
  'size_t text_count;' \
  'size_t binding_count;' \
  'size_t node_count;' \
  'size_t edge_count;' \
  'size_t section_count;' \
  'latticra_l_ui_source_span_t span;'
do
  require_contains "$field" "$doc"
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

for output_rule in \
  'write only to caller-provided buffers' \
  'require explicit buffer length' \
  'NUL-terminate on success' \
  'clear the buffer on too-small failure' \
  'return LATTICRA_STATUS_BUFFER_TOO_SMALL for small buffers' \
  'avoid heap allocation' \
  'avoid file output' \
  'avoid stdout' \
  'avoid stderr' \
  'avoid terminal escape control'
do
  require_contains "$output_rule" "$doc"
done

for report in \
  'LATTICRA L-UI RENDER REPORT' \
  'status=<integer-status>' \
  'error=<render-error-label>' \
  'mode=<render-mode-label>' \
  'card=<card-name>' \
  'effect=<effect-label>' \
  'boundary=<boundary-label>' \
  'rail_count=<count>' \
  'field_count=<count>' \
  'text_count=<count>' \
  'binding_count=<count>' \
  'node_count=<count>' \
  'edge_count=<count>' \
  'section_count=<count>' \
  'authority_status=<authority-status-label>' \
  'authority_validator=<authority-validator-label>' \
  'authority_requested_effect=<authority-effect-label>' \
  'authority_denial_reason=<authority-denial-reason>'
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

for render_line in \
  'rail[<index>].name=<rail-name>' \
  'rail[<index>].field_count=<count>' \
  'field[<index>].name=<field-name>' \
  'field[<index>].binding=<binding-target>' \
  'field[<index>].binding_prefix=<binding-prefix>' \
  'text[<index>].value_len=<length>' \
  'text[<index>].escaped_value=<escaped-text>'
do
  require_contains "$render_line" "$doc"
done

for text_rule in \
  'value_len is authoritative' \
  'escaped output is used for operator-visible text' \
  'escaped decoded NUL through \x00 remains visible' \
  'literal source-buffer NUL remains rejected before rendering' \
  'raw C-string fields are not authoritative for embedded NUL values'
do
  require_contains "$text_rule" "$doc"
done

for lir_rule in \
  source_kind \
  module_name \
  card_name \
  'node kind labels' \
  'edge kind labels' \
  'Rendering must not execute LIR'
do
  require_contains "$lir_rule" "$doc"
done

for authority_rule in \
  authority_status \
  authority_validator \
  authority_requested_effect \
  authority_denial_reason \
  'Rendering authority metadata must not broaden authority'
do
  require_contains "$authority_rule" "$doc"
done

for test_name in \
  l_ui_rendering_accepts_semantically_valid_l_ui_fixture \
  l_ui_rendering_requires_semantic_success \
  l_ui_rendering_requires_lir_success \
  l_ui_rendering_requires_authority_success \
  l_ui_rendering_rejects_non_no_effect_flags \
  l_ui_rendering_preserves_card_metadata \
  l_ui_rendering_preserves_rail_order \
  l_ui_rendering_preserves_field_bindings \
  l_ui_rendering_preserves_text_lengths \
  l_ui_rendering_preserves_escaped_x00_visibility \
  l_ui_rendering_preserves_source_spans \
  l_ui_rendering_preserves_no_effect_flags \
  l_ui_rendering_report_is_deterministic \
  l_ui_rendering_report_rejects_small_buffer \
  l_ui_rendering_rejects_unsupported_mode \
  l_ui_rendering_does_not_change_ast_report \
  l_ui_rendering_does_not_change_lir_report \
  l_ui_rendering_does_not_execute_bindings \
  l_ui_rendering_does_not_call_nucleus_execution \
  l_ui_rendering_is_deterministic
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
  docs/L_UI_RENDERING_CONTRACT.md \
  scripts/test-project-strategy-status-framework.sh \
  docs/L_UI_RENDERING_IMPLEMENTATION.md
do
  require_contains "$doc_path" "$doc"
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
  'no-effect flags' \
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

require_contains 'sh scripts/test-l-ui-rendering-implementation-plan.sh' "$doc"
require_contains 'L-UI renderer implementation code may be added only after this plan is merged.' "$doc"

printf 'l_ui_rendering_implementation_plan: ok\n'

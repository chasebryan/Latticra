#!/usr/bin/env sh
set -eu

doc="docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui semantic validation implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui semantic validation implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement semantic validation.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Implementation files' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Semantic error enum' "$doc"
require_contains 'Semantic result struct' "$doc"
require_contains 'Semantic diagnostic mapping' "$doc"
require_contains 'Semantic report format' "$doc"
require_contains 'Rail semantic checks' "$doc"
require_contains 'Field semantic checks' "$doc"
require_contains 'Binding semantic checks' "$doc"
require_contains 'Text semantic checks' "$doc"
require_contains 'Card semantic checks' "$doc"
require_contains 'Parser-failed behavior' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation update plan' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md \
  docs/L_UI_PARSER.md \
  docs/L_UI_PARSER_AST_IMPLEMENTATION.md \
  docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md \
  docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md \
  docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md \
  docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md \
  docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c
do
  require_contains "$related" "$doc"
done

for path in \
  include/latticra/l_ui_parser.h \
  src/l_ui_parser_semantic.c \
  src/l_ui_parser_diagnostics.c \
  .github/workflows/c.yml \
  docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md \
  tests/l_ui_semantic_validation_invariants.c \
  scripts/test-l-ui-semantic-validation.sh
do
  require_contains "$path" "$doc"
done

for api in \
  latticra_l_ui_semantic_error_t \
  latticra_l_ui_semantic_result_t \
  latticra_l_ui_semantic_error_label \
  latticra_l_ui_validate_semantics \
  latticra_l_ui_semantic_report
do
  require_contains "$api" "$doc"
done

for enum_name in \
  LATTICRA_L_UI_SEMANTIC_OK \
  LATTICRA_L_UI_SEMANTIC_PARSER_FAILED \
  LATTICRA_L_UI_SEMANTIC_DUPLICATE_RAIL \
  LATTICRA_L_UI_SEMANTIC_MISSING_REQUIRED_RAIL \
  LATTICRA_L_UI_SEMANTIC_DUPLICATE_FIELD \
  LATTICRA_L_UI_SEMANTIC_FIELD_RAIL_MISMATCH \
  LATTICRA_L_UI_SEMANTIC_BINDING_FIELD_MISMATCH \
  LATTICRA_L_UI_SEMANTIC_UNSUPPORTED_BINDING_TARGET \
  LATTICRA_L_UI_SEMANTIC_TEXT_RAIL_MISMATCH \
  LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH \
  LATTICRA_L_UI_SEMANTIC_INTERNAL_ERROR
do
  require_contains "$enum_name" "$doc"
done

for label in \
  ok \
  parser_failed \
  duplicate_rail \
  missing_required_rail \
  duplicate_field \
  field_rail_mismatch \
  binding_field_mismatch \
  unsupported_binding_target \
  text_rail_mismatch \
  card_count_mismatch \
  internal_error
do
  require_contains "$label" "$doc"
done

for field in \
  'latticra_status_t status;' \
  'latticra_l_ui_semantic_error_t error;' \
  'latticra_l_ui_parse_error_t parser_error;' \
  'latticra_l_ui_source_span_t span;' \
  'size_t rail_index;' \
  'size_t field_index;' \
  'size_t text_index;' \
  'char card_name[LATTICRA_L_UI_AST_NAME_MAX];' \
  'char rail_name[LATTICRA_L_UI_AST_NAME_MAX];' \
  'char field_name[LATTICRA_L_UI_AST_NAME_MAX];' \
  'char binding[LATTICRA_L_UI_AST_BINDING_MAX];'
do
  require_contains "$field" "$doc"
done

for code in \
  'LUI1000-LUI1099' \
  'LUI1000 semantic_validation_failed' \
  'LUI1001 duplicate_rail' \
  'LUI1002 missing_required_rail' \
  'LUI1003 duplicate_field' \
  'LUI1004 field_rail_mismatch' \
  'LUI1005 binding_field_mismatch' \
  'LUI1006 unsupported_binding_target' \
  'LUI1007 text_rail_mismatch' \
  'LUI1008 card_count_mismatch' \
  'LUI1009 semantic_internal_error'
do
  require_contains "$code" "$doc"
done

for report in \
  'L-UI SEMANTIC VALIDATION RESULT' \
  'status=<integer-status>' \
  'error=<semantic-error-label>' \
  'parser_error=<parser-error-label>' \
  'card=<card-name>' \
  'rail=<rail-name>' \
  'field=<field-name>' \
  'binding=<binding>' \
  'rail_index=<index>' \
  'field_index=<index>' \
  'text_index=<index>' \
  'span_start_offset=<offset>' \
  'span_end_column=<column>'
do
  require_contains "$report" "$doc"
done

for rail in \
  'top: text_count=1, field_count=0' \
  'state: field_count=4, text_count=0' \
  'trace: field_count=2, text_count=0' \
  'safety: field_count=4, text_count=0' \
  'gates: field_count=2, text_count=0' \
  'effects: field_count=3, text_count=0' \
  'policy: field_count=3, text_count=0' \
  'execution: field_count=5, text_count=0' \
  'bottom: text_count=1, field_count=0'
do
  require_contains "$rail" "$doc"
done

for ownership in \
  'state: origin, route, axis, path' \
  'trace: breadcrumb, trace' \
  'safety: health, risk, lock, dark_phase' \
  'gates: safe_portal, rollback' \
  'effects: host, external, requested' \
  'policy: request, policy, reason' \
  'execution: executed, mutation, server, recovery, hardware'
do
  require_contains "$ownership" "$doc"
done

for binding in \
  'origin -> state.origin' \
  'route -> state.route' \
  'requested -> preview.requested_effect' \
  'server -> preview.server_interaction_allowed' \
  'hardware -> preview.hardware_allowed' \
  'unsupported binding prefixes are rejected' \
  'mismatched field/binding pairs are rejected'
do
  require_contains "$binding" "$doc"
done

for text_rule in \
  'top rail -> first text node' \
  'bottom rail -> second text node' \
  'exactly two text nodes exist' \
  'value_len is used for length-aware checks'
do
  require_contains "$text_rule" "$doc"
done

for parser_failed in \
  'LATTICRA_L_UI_SEMANTIC_PARSER_FAILED' \
  'parser_error=<existing parser error>' \
  'This does not replace parser diagnostics or failed-parse AST reports.'
do
  require_contains "$parser_failed" "$doc"
done

for test_name in \
  semantic_validation_accepts_current_fixture \
  semantic_validation_rejects_duplicate_rail \
  semantic_validation_rejects_missing_required_rail \
  semantic_validation_rejects_duplicate_field \
  semantic_validation_rejects_field_rail_mismatch \
  semantic_validation_rejects_binding_field_mismatch \
  semantic_validation_rejects_unsupported_binding_target \
  semantic_validation_rejects_text_rail_mismatch \
  semantic_validation_rejects_card_count_mismatch \
  semantic_validation_skips_when_parser_failed \
  semantic_validation_reports_source_spans \
  semantic_validation_preserves_no_effect_flags \
  semantic_validation_does_not_change_ast_report \
  semantic_validation_does_not_change_escaped_x00_acceptance \
  semantic_validation_does_not_change_literal_nul_rejection \
  semantic_validation_is_deterministic \
  semantic_validation_report_rejects_small_buffer \
  semantic_validation_error_labels_are_stable
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
  docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md \
  scripts/test-project-strategy-status-framework.sh
do
  require_contains "$doc_path" "$doc"
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
  'existing parser behavior' \
  'existing parser diagnostic codes' \
  'existing AST construction behavior' \
  'existing detailed AST report behavior' \
  'escaped decoded NUL acceptance' \
  'literal source-buffer NUL rejection' \
  'source-span byte offset behavior' \
  'current accepted fixture counts'
do
  require_contains "$compat" "$doc"
done

for forbidden in \
  'execute bindings' \
  'evaluate host state' \
  'call Nucleus task execution' \
  'render L-UI' \
  'lower to LIR' \
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
  'accept literal source-buffer NUL' \
  'remove escaped decoded NUL support' \
  'make raw `value=` or `purpose=` fields authoritative for embedded NUL values' \
  'change compact AST report behavior' \
  'change failed-parse detailed report behavior'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-l-ui-semantic-validation-implementation-plan.sh' "$doc"
require_contains 'Semantic validation implementation code may be added only after this plan is merged.' "$doc"

printf 'l_ui_semantic_validation_implementation_plan: ok\n'

#!/usr/bin/env sh
set -eu

doc="docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui semantic validation contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui semantic validation contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: semantic validation contract' "$doc"
require_contains 'This document does not implement semantic validation.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Semantic validation layer' "$doc"
require_contains 'Initial semantic scope' "$doc"
require_contains 'Required rail semantics' "$doc"
require_contains 'Field ownership semantics' "$doc"
require_contains 'Binding semantics' "$doc"
require_contains 'Text semantics' "$doc"
require_contains 'Card semantics' "$doc"
require_contains 'Semantic diagnostic model' "$doc"
require_contains 'Semantic report model' "$doc"
require_contains 'Source-span behavior' "$doc"
require_contains 'AST relationship' "$doc"
require_contains 'Public API expectation' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Future implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
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

for pipeline in \
  'source bytes' \
  'structural parser' \
  'parser diagnostics' \
  'AST construction' \
  'semantic validation' \
  'semantic report' \
  'future rendering or lowering only if allowed'
do
  require_contains "$pipeline" "$doc"
done

for scope in \
  'required rail set' \
  'rail uniqueness' \
  'field uniqueness within a rail' \
  'required field ownership' \
  'binding prefix policy' \
  'binding target consistency' \
  'text node placement' \
  'card effect boundary' \
  'card boundary policy' \
  'no-effect preservation'
do
  require_contains "$scope" "$doc"
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
  'state.' \
  'preview.' \
  'origin -> state.origin' \
  'requested -> preview.requested_effect' \
  'server -> preview.server_interaction_allowed' \
  'hardware -> preview.hardware_allowed' \
  'mismatched field/binding pairs as semantic errors'
do
  require_contains "$binding" "$doc"
done

for text_rule in \
  'exactly two text nodes exist' \
  'the top rail owns the first text node' \
  'the bottom rail owns the second text node' \
  'text values use explicit `value_len` when inspected' \
  'raw `value=` compatibility fields are not authoritative for embedded NUL values'
do
  require_contains "$text_rule" "$doc"
done

for card_rule in \
  'NucleusPreview' \
  'effect=none' \
  'boundary=preview_only' \
  'rail_count=9' \
  'field_count=23' \
  'text_count=2'
do
  require_contains "$card_rule" "$doc"
done

for diag in \
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
  require_contains "$diag" "$doc"
done

for report in \
  'L-UI SEMANTIC VALIDATION RESULT' \
  'status=<ok|error>' \
  'semantic_error=<label>' \
  'card=<card-name>' \
  'rail_count=<count>' \
  'field_count=<count>' \
  'text_count=<count>'
do
  require_contains "$report" "$doc"
done

for span in \
  'rail errors should use the rail span' \
  'field errors should use the field span' \
  'binding errors should use the binding span' \
  'text errors should use the text span' \
  'card-level errors should use the card span' \
  'should not invent byte positions'
do
  require_contains "$span" "$doc"
done

for api in \
  'latticra_l_ui_semantic_result_t' \
  'latticra_l_ui_validate_semantics' \
  'latticra_l_ui_semantic_error_label' \
  'latticra_l_ui_semantic_report'
do
  require_contains "$api" "$doc"
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
  'no-effect flags' \
  'current accepted fixture counts'
do
  require_contains "$compat" "$doc"
done

for gate in \
  'public API shape' \
  'semantic result struct fields' \
  'semantic error enum labels' \
  'diagnostic code mapping' \
  'report format' \
  'rail semantic checks' \
  'field semantic checks' \
  'binding semantic checks' \
  'text semantic checks' \
  'exact tests' \
  'compatibility expectations' \
  'non-claims'
do
  require_contains "$gate" "$doc"
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
  semantic_validation_is_deterministic
do
  require_contains "$test_name" "$doc"
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
  'make raw `value=` or `purpose=` fields authoritative for embedded NUL values'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-l-ui-semantic-validation-contract.sh' "$doc"

printf 'l_ui_semantic_validation_contract: ok\n'

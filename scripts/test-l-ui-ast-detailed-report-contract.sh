#!/usr/bin/env sh
set -eu

doc="docs/L_UI_AST_DETAILED_REPORT_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui ast detailed report contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui ast detailed report contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: detailed report contract' "$doc"
require_contains 'This document does not implement detailed AST reporting.' "$doc"
require_contains 'Detailed report purpose' "$doc"
require_contains 'Report function plan' "$doc"
require_contains 'Report capacity' "$doc"
require_contains 'Top-level report shape' "$doc"
require_contains 'Span field format' "$doc"
require_contains 'Card section' "$doc"
require_contains 'Rail section' "$doc"
require_contains 'Field section' "$doc"
require_contains 'Text section' "$doc"
require_contains 'Determinism rules' "$doc"
require_contains 'Escaping policy' "$doc"
require_contains 'Failed parse behavior' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility rule' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for api in \
  latticra_l_ui_ast_detailed_report \
  LATTICRA_L_UI_AST_DETAILED_REPORT_MAX
do
  require_contains "$api" "$doc"
done

for title in \
  'L-UI AST DETAILED REPORT' \
  '[card]' \
  '[rail <index>]' \
  '[field <index>]' \
  '[text <index>]'
do
  require_contains "$title" "$doc"
done

for span_field in \
  'span_start_offset=<n>' \
  'span_end_offset=<n>' \
  'span_start_line=<n>' \
  'span_start_column=<n>' \
  'span_end_line=<n>' \
  'span_end_column=<n>' \
  'binding_span_start_offset=<n>' \
  'binding_span_end_offset=<n>' \
  'binding_span_start_line=<n>' \
  'binding_span_start_column=<n>' \
  'binding_span_end_line=<n>' \
  'binding_span_end_column=<n>'
do
  require_contains "$span_field" "$doc"
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

for compat in \
  latticra_l_ui_ast_report \
  latticra_l_ui_parse_ast \
  latticra_l_ui_parse_source \
  latticra_l_ui_parse_result_report \
  latticra_l_ui_diagnostic_report
do
  require_contains "$compat" "$doc"
done

for rule in \
  'Report sections must appear in a fixed order.' \
  'Rails must appear in AST rail order.' \
  'Fields must appear in AST field order.' \
  'Text nodes must appear in AST text order.' \
  'Missing/unpopulated capacity slots must not be printed.' \
  'Output must not include memory addresses.' \
  'Output must not depend on platform locale.'
do
  require_contains "$rule" "$doc"
done

for test_name in \
  detailed_report_contains_title \
  detailed_report_contains_card_section \
  detailed_report_contains_all_rails \
  detailed_report_contains_all_fields \
  detailed_report_contains_all_text_nodes \
  detailed_report_preserves_rail_order \
  detailed_report_preserves_field_order \
  detailed_report_preserves_text_order \
  detailed_report_includes_card_span \
  detailed_report_includes_rail_spans \
  detailed_report_includes_field_spans \
  detailed_report_includes_binding_spans \
  detailed_report_includes_text_spans \
  detailed_report_preserves_no_effect_flags \
  detailed_report_is_deterministic \
  detailed_report_rejects_bad_arguments \
  detailed_report_rejects_small_buffers \
  detailed_report_omits_unused_capacity_slots
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
  'treat text nodes as commands' \
  'treat bindings as executable references' \
  'emit memory addresses'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_ast_detailed_report_contract: ok\n'

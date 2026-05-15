#!/usr/bin/env sh
set -eu

doc="docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui ast detailed report implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui ast detailed report implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'The detailed AST report implementation should be in C.' "$doc"
require_contains 'Public API addition' "$doc"
require_contains 'Module shape' "$doc"
require_contains 'Report capacity' "$doc"
require_contains 'Failed-parse behavior' "$doc"
require_contains 'Escaping policy' "$doc"
require_contains 'Exact section order' "$doc"
require_contains 'Top-level summary format' "$doc"
require_contains 'Card section format' "$doc"
require_contains 'Rail section format' "$doc"
require_contains 'Field section format' "$doc"
require_contains 'Text section format' "$doc"
require_contains 'Helper plan' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for api in \
  latticra_l_ui_ast_detailed_report \
  LATTICRA_L_UI_AST_DETAILED_REPORT_MAX \
  LATTICRA_STATUS_BUFFER_TOO_SMALL
do
  require_contains "$api" "$doc"
done

for value in \
  'LATTICRA_L_UI_AST_DETAILED_REPORT_MAX = 16384' \
  'L-UI AST DETAILED REPORT' \
  'parse_error=<error-label>' \
  'card=NucleusPreview' \
  'purpose=operator-visible Nucleus preview report' \
  'effect=none' \
  'boundary=preview_only' \
  'rail_count=9' \
  'field_count=23' \
  'text_count=2'
do
  require_contains "$value" "$doc"
done

for section in \
  '1. top-level summary' \
  '2. card section' \
  '3. rail sections in AST order' \
  '4. field sections in AST order' \
  '5. text sections in AST order' \
  '[card]' \
  '[rail <index>]' \
  '[field <index>]' \
  '[text <index>]'
do
  require_contains "$section" "$doc"
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

for helper in \
  append_text \
  append_span_fields \
  append_card_section \
  append_rail_section \
  append_field_section \
  append_text_section \
  append_failed_parse_report
do
  require_contains "$helper" "$doc"
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

for compat in \
  latticra_l_ui_ast_report \
  latticra_l_ui_parse_ast \
  latticra_l_ui_parse_source \
  latticra_l_ui_parse_result_report \
  latticra_l_ui_diagnostic_report
do
  require_contains "$compat" "$doc"
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
  detailed_report_omits_unused_capacity_slots \
  detailed_report_handles_failed_parse
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_parser_ast_detailed_report_invariants.c \
  scripts/test-l-ui-ast-detailed-report.sh \
  docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md \
  .github/workflows/c.yml
do
  require_contains "$path" "$doc"
done

for forbidden in \
  'add file I/O to parser or AST code' \
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

printf 'l_ui_ast_detailed_report_implementation_plan: ok\n'

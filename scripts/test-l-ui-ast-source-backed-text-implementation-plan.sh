#!/usr/bin/env sh
set -eu

doc="docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui ast source-backed text implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui ast source-backed text implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'Source-backed text extraction should be implemented in C.' "$doc"
require_contains 'Public API decision' "$doc"
require_contains 'Extraction helper plan' "$doc"
require_contains 'Extraction targets' "$doc"
require_contains 'Quote handling behavior' "$doc"
require_contains 'Escape handling boundary' "$doc"
require_contains 'Capacity behavior' "$doc"
require_contains 'Span decision' "$doc"
require_contains 'Successful parse rule' "$doc"
require_contains 'Failed parse behavior' "$doc"
require_contains 'Detailed report relationship' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'No-effect preservation' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for helper in \
  extract_quoted_value_after_token \
  copy_extracted_value \
  latticra_l_ui_parse_ast \
  latticra_l_ui_parse_source \
  LATTICRA_STATUS_BUFFER_TOO_SMALL \
  LATTICRA_L_UI_PARSE_INTERNAL_ERROR
do
  require_contains "$helper" "$doc"
done

for target in \
  'purpose "..." -> ast.card.purpose' \
  'first text "..." -> ast.texts[0].value' \
  'second text "..." -> ast.texts[1].value' \
  'latticra_l_ui_ast_card_t.purpose' \
  'latticra_l_ui_ast_text_t.value' \
  LATTICRA_L_UI_AST_PURPOSE_MAX \
  LATTICRA_L_UI_AST_TEXT_MAX
do
  require_contains "$target" "$doc"
done

for behavior in \
  'copy bytes between the opening and closing quote' \
  'The surrounding quotes must not be copied into AST values.' \
  'copy raw bytes between quotes without decoding escapes' \
  'The implementation must not silently truncate extracted values.' \
  'Do not add a new public `purpose_span` field in the first implementation.' \
  'If parsing fails, extraction must not run.' \
  'No source-backed text values should be extracted for failed parses.'
do
  require_contains "$behavior" "$doc"
done

for report_field in \
  'purpose=<literal-purpose>' \
  'purpose_escaped=<escaped-purpose>' \
  'value=<literal-text>' \
  'value_escaped=<escaped-text>'
do
  require_contains "$report_field" "$doc"
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

for compat in \
  latticra_l_ui_parse_source \
  latticra_l_ui_ast_report \
  'latticra_l_ui_ast_detailed_report existing required fields' \
  latticra_l_ui_diagnostic_report \
  'parser error labels' \
  'existing accepted fixture summary counts'
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
  source_backed_purpose_matches_fixture_source \
  source_backed_top_text_matches_fixture_source \
  source_backed_bottom_text_matches_fixture_source \
  source_backed_text_values_are_copied \
  source_backed_text_does_not_retain_source_pointers \
  source_backed_text_excludes_quotes \
  source_backed_text_preserves_ast_counts \
  source_backed_text_preserves_no_effect_flags \
  source_backed_text_updates_detailed_report_literals \
  source_backed_text_updates_detailed_report_escaped_fields \
  source_backed_text_rejects_or_classifies_oversized_purpose \
  source_backed_text_rejects_or_classifies_oversized_text \
  source_backed_text_does_not_change_failed_parse_report \
  source_backed_text_is_deterministic \
  source_backed_text_does_not_decode_escapes
do
  require_contains "$test_name" "$doc"
done

for path in \
  tests/l_ui_ast_source_backed_text_invariants.c \
  scripts/test-l-ui-ast-source-backed-text.sh \
  docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md \
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
  'retain source-buffer pointers in the AST' \
  'silently truncate extracted values' \
  'broaden accepted grammar without a grammar contract' \
  'decode string escapes without a string-literal escape contract'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_ast_source_backed_text_implementation_plan: ok\n'

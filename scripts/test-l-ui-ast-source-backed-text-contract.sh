#!/usr/bin/env sh
set -eu

doc="docs/L_UI_AST_SOURCE_BACKED_TEXT_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'l-ui ast source-backed text contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui ast source-backed text contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: source-backed text contract' "$doc"
require_contains 'The source-backed extraction implementation is documented separately' "$doc"
require_contains 'The later string-literal escape decoder is documented separately' "$doc"
require_contains 'Extraction purpose' "$doc"
require_contains 'Extraction targets' "$doc"
require_contains 'No grammar broadening rule' "$doc"
require_contains 'Ownership rule' "$doc"
require_contains 'Capacity rule' "$doc"
require_contains 'Span rule' "$doc"
require_contains 'Quote handling rule' "$doc"
require_contains 'Escape handling relationship' "$doc"
require_contains 'Detailed report relationship' "$doc"
require_contains 'Failed parse behavior' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility rule' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for target in \
  card.purpose \
  text.value \
  'purpose "..."' \
  'text "..."' \
  'latticra_l_ui_ast_card_t.purpose' \
  'latticra_l_ui_ast_text_t.value' \
  LATTICRA_L_UI_AST_PURPOSE_MAX \
  LATTICRA_L_UI_AST_TEXT_MAX \
  latticra_l_ui_parse_source
do
  require_contains "$target" "$doc"
done

for escape_relation in \
  'string-literal escape decoding for accepted source escapes' \
  'The initial source-backed extraction phase copied raw bytes between quotes without decoding escapes.' \
  'Current source-backed AST values now decode accepted string-literal escapes' \
  'L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md' \
  'L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md' \
  'L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md' \
  'Accepted escapes such as' \
  'Rejected escapes are classified through' \
  LATTICRA_L_UI_PARSE_INTERNAL_ERROR
do
  require_contains "$escape_relation" "$doc"
done

for report_field in \
  'purpose=<literal-purpose>' \
  'purpose_escaped=<escaped-purpose>' \
  'value=<literal-text>' \
  'value_escaped=<escaped-text>' \
  'escaped report fields remain the stable assertion target'
do
  require_contains "$report_field" "$doc"
done

for behavior in \
  'The surrounding quotes are not copied into AST values.' \
  'Escaped quotes are respected when finding the closing quote.' \
  'Source spans refer to source byte ranges, not decoded output byte ranges.' \
  'It does not truncate silently.' \
  'The AST does not retain borrowed pointers into the source buffer.'
do
  require_contains "$behavior" "$doc"
done

for count in \
  'rail_count=9' \
  'field_count=23' \
  'text_count=2'
do
  require_contains "$count" "$doc"
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
  latticra_l_ui_parse_source \
  latticra_l_ui_ast_report \
  'latticra_l_ui_ast_detailed_report existing required fields' \
  latticra_l_ui_diagnostic_report \
  'parser error labels' \
  'existing accepted fixture summary'
do
  require_contains "$compat" "$doc"
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
  source_backed_text_decodes_accepted_string_escapes
do
  require_contains "$test_name" "$doc"
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
  'broaden accepted grammar without a grammar contract'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_ast_source_backed_text_contract: ok\n'
#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq "$pattern" "$file"; then
    printf 'l-ui parser diagnostics implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser diagnostics implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'The first diagnostics implementation should be in C.' "$doc"
require_contains 'Proposed module shape' "$doc"
require_contains 'Diagnostic enums' "$doc"
require_contains 'Diagnostic result shape' "$doc"
require_contains 'Public API plan' "$doc"
require_contains 'Parser result report extension' "$doc"
require_contains 'Mapping table' "$doc"
require_contains 'Hint mapping' "$doc"
require_contains 'Line and column behavior' "$doc"
require_contains 'No-effect flags' "$doc"
require_contains 'Exact test list' "$doc"
require_contains 'CI requirement' "$doc"
require_contains 'Documentation requirement' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for constant in \
  LATTICRA_L_UI_DIAGNOSTIC_OK \
  LATTICRA_L_UI_DIAGNOSTIC_ERROR \
  LATTICRA_L_UI_DIAGNOSTIC_INTERNAL \
  LATTICRA_L_UI_DIAGNOSTIC_CODE_MAX \
  LATTICRA_L_UI_DIAGNOSTIC_MESSAGE_MAX \
  LATTICRA_L_UI_DIAGNOSTIC_HINT_MAX \
  LATTICRA_L_UI_DIAGNOSTIC_REPORT_MAX
do
  require_contains "$constant" "$doc"
done

for api in \
  latticra_l_ui_diagnostic_severity_label \
  latticra_l_ui_diagnostic_from_parse_result \
  latticra_l_ui_diagnostic_report
do
  require_contains "$api" "$doc"
done

for field in \
  severity \
  code \
  message \
  hint \
  line \
  column \
  no_effect \
  execution_allowed \
  mutation_allowed \
  server_allowed \
  recovery_allowed \
  hardware_allowed
do
  require_contains "$field" "$doc"
done

for mapping in \
  'LUI0000' \
  'LUI0001' \
  'LUI0002' \
  'LUI0003' \
  'LUI0004' \
  'LUI0005' \
  'LUI0006' \
  'LUI0007' \
  'LUI0008' \
  'LUI0009' \
  'LUI0010' \
  'LUI0011' \
  'LUI0012' \
  'LUI0013' \
  'LUI0014' \
  'LUI0015' \
  'LUI0016' \
  'LUI0017' \
  'LUI0018'
do
  require_contains "$mapping" "$doc"
done

for message in \
  'Parse completed successfully.' \
  'Parser received a null argument.' \
  'L-UI source is empty.' \
  'L-UI version is not supported.' \
  'Required card declaration is missing.' \
  'Required purpose clause is missing.' \
  'Required effect clause is missing.' \
  'Effect declaration is not supported.' \
  'Required boundary clause is missing.' \
  'Boundary declaration is not supported.' \
  'Required rail is missing.' \
  'Rail name is not supported.' \
  'Binding prefix is not supported.' \
  'Required binding is missing.' \
  'String literal is not terminated.' \
  'Braces are not balanced.' \
  'Source contains a forbidden behavior marker.' \
  'Source exceeds the supported size limit.' \
  'Parser reached an internal error.'
do
  require_contains "$message" "$doc"
done

for hint in \
  'Provide non-null source and result pointers.' \
  'Provide L-UI source beginning with: lui 0.1' \
  'Use version header: lui 0.1' \
  'Add card NucleusPreview { ... }' \
  'Add a purpose string.' \
  'Add effect none.' \
  'Use only effect none.' \
  'Add boundary preview_only.' \
  'Use only boundary preview_only.' \
  'Add the required NucleusPreview rails.' \
  'Use only documented rail names.' \
  'Use only state. or preview. binding prefixes.' \
  'Add all required NucleusPreview bindings.' \
  'Close the string literal.' \
  'Balance opening and closing braces.' \
  'Remove behavior markers outside the static report grammar.' \
  'Keep L-UI source at or below LATTICRA_L_UI_SOURCE_MAX.' \
  'Report the internal parser error.'
do
  require_contains "$hint" "$doc"
done

for test_name in \
  ok_result_has_lui0000 \
  empty_source_reports_lui0002 \
  unsupported_version_reports_lui0003 \
  missing_card_reports_lui0004 \
  missing_purpose_reports_lui0005 \
  missing_effect_reports_lui0006 \
  unsupported_effect_reports_lui0007 \
  missing_boundary_reports_lui0008 \
  unsupported_boundary_reports_lui0009 \
  missing_rail_reports_lui0010 \
  unknown_binding_prefix_reports_lui0012 \
  missing_required_binding_reports_lui0013 \
  unterminated_string_reports_lui0014 \
  unbalanced_brace_reports_lui0015 \
  forbidden_marker_reports_lui0016 \
  source_too_large_reports_lui0017 \
  internal_error_reports_lui0018 \
  error_diagnostics_preserve_no_effect_flags \
  line_and_column_are_one_based \
  messages_are_stable \
  hints_are_stable \
  diagnostic_report_contains_required_fields \
  diagnostic_report_rejects_bad_arguments_and_small_buffers \
  severity_labels_are_stable
do
  require_contains "$test_name" "$doc"
done

for forbidden in \
  'parse files directly' \
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
  'accept unsupported effects'
do
  require_contains "$forbidden" "$doc"
done

printf 'l_ui_parser_diagnostics_implementation_plan: ok\n'

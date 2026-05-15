# Latticra L-UI Parser

Status: implementation contract
Scope: no-effect C parser, parse summaries, source locations, and source spans for the first L-UI source fixture.

## Purpose

The L-UI Parser validates in-memory `.lui` source and returns a compact no-effect parse summary.

It does not render UI, run L-UI behavior, perform file I/O, call Nucleus task handling, or mutate state.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser.c
tests/l_ui_parser_invariants.c
tests/l_ui_parser_location_invariants.c
tests/l_ui_parser_source_span_invariants.c
scripts/test-l-ui-parser.sh
scripts/test-l-ui-parser-location.sh
scripts/test-l-ui-parser-source-span.sh
```

## Source-size limit

The parser defines:

```text
LATTICRA_L_UI_SOURCE_MAX = 65536
```

Input larger than this is rejected with:

```text
source_too_large
```

## Public API

Current API:

```text
latticra_l_ui_parse_error_label
latticra_l_ui_parse_source
latticra_l_ui_parse_result_report
```

The parser accepts in-memory source only. It does not read files directly.

## Parse result

The parse result contains:

```text
status
error
line
column
span
card_name
rail_count
field_count
effect
boundary
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
```

The source span contains:

```text
start_offset
end_offset
start_line
start_column
end_line
end_column
```

For a valid fixture, the expected summary is:

```text
status=ok
error=ok
card_name=NucleusPreview
rail_count=9
field_count=23
effect=none
boundary=preview_only
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
span_start_offset=0
span_end_offset=0
span_start_line=1
span_start_column=1
span_end_line=1
span_end_column=1
```

## Accepted fixture

The first accepted source is:

```text
examples/l-ui/nucleus-preview-card.lui
```

## Error labels

The parser exposes stable labels for:

```text
ok
null_argument
empty_source
unsupported_version
missing_card
missing_purpose
missing_effect
unsupported_effect
missing_boundary
unsupported_boundary
missing_rail
unknown_rail
unknown_binding_prefix
missing_required_binding
unterminated_string
unbalanced_brace
forbidden_behavior_marker
source_too_large
internal_error
```

## Validation strategy

The parser is intentionally conservative. It performs:

- source length check;
- quote balance check;
- brace balance check;
- required header and card checks;
- required effect and boundary checks;
- forbidden marker checks;
- required rail checks;
- required binding checks;
- point-location metadata;
- source-span metadata;
- no-effect summary output.

It does not produce a full AST yet.

## Report shape

The parser result report renders deterministic text and appends span fields:

```text
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

## Test commands

Run:

```sh
sh scripts/test-l-ui-parser.sh
sh scripts/test-l-ui-parser-location.sh
sh scripts/test-l-ui-parser-source-span.sh
```

The main C workflow runs these checks after existing state, transition, Nucleus, L-UI static report, grammar fixture, parser design, and parser plan guards.

## Required invariants

The parser tests verify:

```text
valid_fixture_parses_successfully
null_source_is_rejected
null_result_is_rejected
empty_source_is_rejected
oversized_source_is_rejected
unsupported_version_is_rejected
missing_card_is_rejected
missing_purpose_is_rejected
missing_effect_is_rejected
unsupported_effect_is_rejected
missing_boundary_is_rejected
unsupported_boundary_is_rejected
missing_required_rail_is_rejected
missing_required_binding_is_rejected
unknown_binding_prefix_is_rejected
forbidden_behavior_marker_is_rejected
unterminated_string_is_rejected
unbalanced_brace_is_rejected
valid_parse_returns_no_effect_flags
error_results_preserve_no_execution_flags
parse_error_labels_are_stable
```

The source-span tests verify span offsets, exclusive end offsets, one-based line/column ranges, byte-based columns, LF/CRLF/CR handling, report fields, diagnostic span copying, and default success spans.

## Current evidence level

This implementation is an L2 tested model for no-effect L-UI source validation, point locations, and source-span metadata.

It is not a renderer, interactive UI, shell, compositor, command language, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, AST system, or security boundary.

## Next implementation step

The next implementation candidate after source spans is:

```text
L-UI parser AST contract
```

That future work should define AST shape, node ownership, source-span usage, and no-effect boundaries before any AST implementation.

## Non-claims

This document and implementation do not claim AST construction, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.

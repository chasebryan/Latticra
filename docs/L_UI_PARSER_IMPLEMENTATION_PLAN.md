# Latticra L-UI Parser Implementation Plan

Status: implementation planning contract
Scope: implementation language, module shape, API, source-size limit, exact test list, and no-effect constraints before parser code.

## Purpose

This document defines the implementation plan for the first L-UI parser.

The parser should be implemented only after the parser design contract is merged and guarded. This plan decides what parser code is allowed to look like before code is introduced.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_SOURCE_GRAMMAR.md
docs/L_UI_PARSER_DESIGN.md
examples/l-ui/nucleus-preview-card.lui
scripts/test-l-ui-grammar-fixtures.sh
scripts/test-l-ui-parser-design.sh
```

Those documents and guards remain the source of truth for syntax, error categories, no-effect constraints, and fixture expectations.

## Implementation language decision

The first parser should be implemented in C.

Reason:

- Latticra's current implementation foundation is C;
- the parser must stay portable and small;
- the parser output should become part of the low-level Latticra ABI;
- no dynamic runtime should be required;
- the parser can be tested with the existing C workflow.

Rust tooling can be added later for validation helpers, but the first parser should remain a C no-effect parser.

## Proposed module shape

```text
include/latticra/l_ui_parser.h
src/l_ui_parser.c
tests/l_ui_parser_invariants.c
scripts/test-l-ui-parser.sh
```

## Source-size limit

The first parser should define:

```text
LATTICRA_L_UI_SOURCE_MAX = 65536
```

Input larger than this must return `source_too_large`.

## Parse result shape

The first parser should return a compact summary rather than a full AST.

Planned struct fields:

```text
status
error
line
column
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

## Error enum

The first C parser should implement these errors exactly:

```text
LATTICRA_L_UI_PARSE_OK
LATTICRA_L_UI_PARSE_NULL_ARGUMENT
LATTICRA_L_UI_PARSE_EMPTY_SOURCE
LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION
LATTICRA_L_UI_PARSE_MISSING_CARD
LATTICRA_L_UI_PARSE_MISSING_PURPOSE
LATTICRA_L_UI_PARSE_MISSING_EFFECT
LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT
LATTICRA_L_UI_PARSE_MISSING_BOUNDARY
LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY
LATTICRA_L_UI_PARSE_MISSING_RAIL
LATTICRA_L_UI_PARSE_UNKNOWN_RAIL
LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX
LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING
LATTICRA_L_UI_PARSE_UNTERMINATED_STRING
LATTICRA_L_UI_PARSE_UNBALANCED_BRACE
LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER
LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

## Public API plan

Initial functions:

```text
const char *latticra_l_ui_parse_error_label(latticra_l_ui_parse_error_t error);

latticra_status_t latticra_l_ui_parse_source(
    const char *source,
    size_t source_len,
    latticra_l_ui_parse_result_t *result);
```

Optional later function, not required in first parser PR:

```text
latticra_status_t latticra_l_ui_parse_file(...)
```

The first parser should parse in-memory source only. It should not perform file I/O.

## No-effect output flags

For valid fixtures, the parser must return:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

These flags must also remain safe on denied/error results.

## First accepted source

The first accepted fixture is:

```text
examples/l-ui/nucleus-preview-card.lui
```

The parser should accept this fixture and produce:

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
```

## Exact test list for first parser PR

The first parser implementation PR should include tests for:

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
valid_parse_returns_no_effect_flags
error_results_preserve_no_execution_flags
parse_error_labels_are_stable
```

## Parser approach

The first parser should be simple and conservative.

Allowed approach:

- bounded source length check;
- string scanning;
- required-pattern validation;
- brace balance check;
- string literal quote balance check;
- required rail and binding validation;
- forbidden marker validation;
- normalized summary output.

Not required in first parser:

- complete AST;
- nested object model;
- renderer integration;
- file I/O;
- allocation-heavy tokenizer;
- recovery parser;
- interactive diagnostics;
- command execution.

## Forbidden implementation behavior

The parser implementation must not:

- read files directly;
- write files;
- open sockets;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- mutate state lattice;
- perform live movement;
- execute L-UI source;
- render UI;
- use unbounded allocation;
- accept unsupported effects.

## CI requirement

The first parser PR must add:

```text
scripts/test-l-ui-parser.sh
```

and wire it into:

```text
.github/workflows/c.yml
```

## Documentation requirement

The first parser PR must update:

```text
README.md
docs/FOUNDATION_INDEX.md
docs/L_UI_PARSER_DESIGN.md
```

and add:

```text
docs/L_UI_PARSER.md
```

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-parser-implementation-plan.sh
```

The guard is static. It does not implement the parser.

## Implementation gate

Parser code may be added only after this plan is merged.

## Non-claims

This document does not implement L-UI parsing, rendering, command execution, Nucleus execution, live movement, origin mutation, recovery execution, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.

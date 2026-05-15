# Latticra L-UI AST Escaped String Report Contract

Status: escaped string report contract
Scope: stable escaping rules for detailed AST report string values before broader L-UI text values are accepted.

## Purpose

This document defines the escaped string report contract for L-UI AST reports.

The current detailed AST report renders current fixture text literally because the accepted text values are controlled. Before broader L-UI text values are accepted, reports need stable escaping rules for newlines, tabs, quotes, backslashes, control bytes, and non-printable bytes.

This document does not implement escaped string reporting.

## Current boundary

The current detailed AST report provides deterministic metadata for:

```text
card
rails
fields
text nodes
source spans
binding spans
no-effect flags
```

The current detailed report does not yet define broad escaping behavior for arbitrary text values.

This contract does not add:

```text
escaped string implementation
new parser grammar
new accepted text values
renderer integration
interactive UI behavior
command behavior
Nucleus task handling
live movement
state mutation
server interaction
update behavior
recovery behavior
hardware behavior
boot behavior
```

## Escaping purpose

Escaped string reporting should make text output:

- deterministic;
- single-line when required;
- safe for logs;
- safe for fixture comparisons;
- independent of terminal behavior;
- independent of platform locale;
- unambiguous for quotes and backslashes;
- readable for common whitespace;
- explicit for control and non-printable bytes.

Escaping must remain metadata-only.

## Escaped fields

The first escaping implementation should apply to report values that may contain arbitrary source text:

```text
card.purpose
text.value
```

It may later apply to labels or bindings if broader syntax permits non-identifier bytes, but current labels and bindings remain controlled identifiers.

## Report key naming

The implementation plan must choose whether to replace existing value keys or add escaped variants.

Preferred first implementation:

```text
purpose_escaped=<escaped-string>
value_escaped=<escaped-string>
```

Existing literal keys may remain for the current controlled fixture until a compatibility plan changes them.

## Required escape sequences

The first escaping implementation should support:

| Input byte | Report text |
| --- | --- |
| newline LF `0x0A` | `\n` |
| carriage return CR `0x0D` | `\r` |
| horizontal tab `0x09` | `\t` |
| double quote `0x22` | `\"` |
| backslash `0x5C` | `\\` |
| NUL `0x00` | `\x00` |
| other control bytes `0x01`-`0x1F` | `\xNN` |
| DEL `0x7F` | `\x7F` |
| non-ASCII bytes `0x80`-`0xFF` | `\xNN` |

Printable ASCII bytes from `0x20` through `0x7E`, except double quote and backslash, may be emitted literally.

## Hex format

Hex escapes must use uppercase hexadecimal digits:

```text
\x00
\x09
\x1F
\x7F
\x80
\xFF
```

Lowercase hex output is not allowed.

## Determinism rules

Escaped string output must be deterministic.

Rules:

1. The same byte sequence must always produce the same escaped text.
2. Escaped output must not depend on platform locale.
3. Escaped output must not depend on terminal capabilities.
4. Escaped output must not include memory addresses.
5. Escaped output must not include raw control bytes.
6. Escaped output must not include raw non-ASCII bytes.
7. Escaped output must be NUL-terminated in C buffers.
8. Escaped output must fail with a stable status when the destination buffer is too small.

## Byte-oriented rule

Escaping is byte-oriented, not Unicode-codepoint-oriented.

The first implementation should treat source text as bytes and render non-ASCII bytes with `\xNN` escapes. A future Unicode display contract may define higher-level behavior later.

## Buffer sizing rule

Worst-case escaped size is four output characters per input byte plus the terminating NUL:

```text
input_len * 4 + 1
```

The implementation plan must define bounded destination sizes and too-small behavior before code is added.

## Helper function plan

A future implementation may add a private helper such as:

```text
escape_report_string
```

Possible helper shape:

```text
static latticra_status_t escape_report_string(
    const char *input,
    size_t input_len,
    char *output,
    size_t output_len);
```

The helper should remain private until a public need is proven.

## Detailed report integration

A future detailed report may render:

```text
purpose_escaped=<escaped-purpose>
value_escaped=<escaped-text>
```

The implementation plan must decide exact placement in:

```text
[card]
[text <index>]
```

## Failed parse behavior

Escaping should not change failed-parse detailed report behavior.

Failed parse detailed reports should continue to render:

```text
parse_error=<error-label>
rail_count=0
field_count=0
text_count=0
```

## Compatibility rule

Escaped string reporting must be additive for the first implementation.

It must not change:

```text
latticra_l_ui_ast_report
latticra_l_ui_parse_ast
latticra_l_ui_parse_source
latticra_l_ui_parse_result_report
latticra_l_ui_diagnostic_report
latticra_l_ui_ast_detailed_report existing required fields
```

## No-effect rule

Escaped string reporting is metadata output only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Implementation gate

Escaped string report implementation must not begin until a separate implementation plan defines:

1. public API decision;
2. private helper shape;
3. destination buffer sizes;
4. exact escaped report fields;
5. exact report placement;
6. too-small behavior;
7. test file names;
8. exact invariant tests;
9. compatibility expectations.

## Future test list

A future implementation plan should include tests for:

```text
escape_preserves_printable_ascii
escape_newline_as_backslash_n
escape_carriage_return_as_backslash_r
escape_tab_as_backslash_t
escape_quote_as_backslash_quote
escape_backslash_as_double_backslash
escape_nul_as_hex_00
escape_control_bytes_as_uppercase_hex
escape_del_as_uppercase_hex
escape_non_ascii_bytes_as_uppercase_hex
escape_rejects_small_buffers
escape_is_deterministic
detailed_report_contains_escaped_purpose
detailed_report_contains_escaped_text_values
detailed_report_escaped_fields_are_additive
detailed_report_escape_preserves_no_effect_flags
detailed_report_escape_does_not_change_failed_parse_report
```

## Forbidden behavior

A future escaped string implementation must not:

- add file I/O to parser or AST code;
- write files;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- mutate state lattice;
- perform live movement;
- run L-UI behavior;
- render an interactive UI;
- treat text nodes as commands;
- treat bindings as executable references;
- emit memory addresses;
- emit raw control bytes in escaped fields;
- emit raw non-ASCII bytes in escaped fields.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-ast-escaped-string-report-contract.sh
```

The guard is static. It does not implement escaped string reporting.

## Non-claims

This document does not implement escaped string reporting, broaden accepted L-UI text syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.

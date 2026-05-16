# Latticra L-UI Source Buffer Literal NUL Policy Implementation Plan

Status: implementation planning contract
Scope: exact implementation and test plan for enforcing the policy that literal `0x00` bytes in L-UI source buffers remain rejected.

## Purpose

This document defines the implementation plan for L-UI source-buffer literal NUL policy enforcement.

The policy contract is already merged and guarded. This plan defines exact parser behavior, diagnostic behavior, AST behavior, report behavior, source-span expectations, tests, documentation updates, and non-claims before any implementation slice changes or extends literal source-buffer handling.

This document does not implement literal NUL acceptance.

## Relationship to previous work

This plan depends on:

```text
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_CONTRACT.md
docs/L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md
docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION_PLAN.md
docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_ast.c
src/l_ui_parser_diagnostics.c
```

Those files remain the source of truth for escaped decoded NUL acceptance, explicit AST string lengths, parser diagnostics, AST decoding, detailed reports, and no-effect behavior.

## Implementation language decision

Literal source-buffer NUL policy enforcement should remain in C.

Reason:

- source validation lives in `src/l_ui_parser.c`;
- AST construction lives in `src/l_ui_parser_ast.c`;
- diagnostics live in `src/l_ui_parser_diagnostics.c`;
- tests are C fixtures and shell runners;
- the behavior is byte-oriented and bounded.

## Policy decision

Literal `0x00` bytes in L-UI source buffers remain rejected.

The accepted way to express a decoded NUL byte inside a source-backed string value remains:

```text
\x00
```

This plan is for policy enforcement and regression coverage, not literal-NUL acceptance.

## Parser behavior plan

Parser validation in:

```text
src/l_ui_parser.c
```

should continue detecting literal source-buffer NUL bytes before AST materialization.

Literal source NUL inside a quoted value should report:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

Literal source NUL should not be classified as:

```text
empty_source
unterminated_string
invalid_string_escape
invalid_hex_escape
decoded_nul_in_string
internal_error
```

## Diagnostic behavior plan

Literal source NUL should map to:

```text
LUI0023 literal_nul_in_string
```

The diagnostic message and hint remain stable:

```text
Literal NUL bytes are not supported in AST strings.
Remove literal NUL bytes from the source string.
```

`LUI0022 decoded_nul_in_string` remains available as a stable compatibility diagnostic, but literal source NUL must not emit it.

## Source-span plan

For literal source NUL failures, the parse-result and diagnostic span should cover exactly the literal `0x00` byte in the source buffer.

Expected span rule:

```text
span_end_offset - span_start_offset == 1
source[span_start_offset] == 0x00
```

Line and column remain one-based byte positions in the in-memory source buffer.

## AST behavior plan

Literal source NUL input should not produce a partial AST.

Expected failed-parse AST state:

```text
ast.parse_result.error = LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
ast.card.rail_count = 0
ast.card.field_count = 0
ast.card.text_count = 0
ast.card.purpose_len = 0
ast.texts[index].value_len = 0
```

## Report behavior plan

Literal source NUL failures should use failed-parse detailed report behavior.

Expected report behavior:

```text
parse_error=literal_nul_in_string
rail_count=0
field_count=0
text_count=0
```

The report should not include materialized AST string sections for literal source NUL input:

```text
purpose=
value=
purpose_escaped=
value_escaped=
```

## Escaped decoded NUL compatibility

This implementation plan must not roll back escaped decoded NUL acceptance.

The following should remain accepted:

```text
purpose "A\x00B"
text "left\x00right"
```

The existing decoded-NUL acceptance tests should remain valid.

## Accepted escape compatibility

Do not broaden or reduce the accepted escape set.

Still accepted:

```text
\\
\"
\n
\r
\t
\xNN
```

where `\xNN` uses exactly two uppercase hexadecimal digits.

Still rejected:

```text
\x0a -> LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE
\a -> LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE
literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

## Source-buffer construction test plan

Literal source NUL tests should construct source buffers with explicit byte lengths.

Tests should not rely on C string termination to place the literal NUL.

Recommended helper shape:

```text
make_source_binary(buffer, buffer_len, purpose, purpose_len, top_text, top_text_len, bottom_text, bottom_text_len, source_len)
```

This helper should preserve embedded literal NUL bytes in the source buffer and pass the explicit `source_len` to parser APIs.

## Exact implementation test list

The implementation PR should include tests for:

```text
literal_nul_policy_rejects_purpose_literal_nul
literal_nul_policy_rejects_text_literal_nul
literal_nul_policy_reports_lui0023
literal_nul_policy_span_covers_literal_nul_byte
literal_nul_policy_preserves_no_effect_flags
literal_nul_policy_does_not_emit_decoded_nul_lui0022
literal_nul_policy_does_not_materialize_partial_ast
literal_nul_policy_does_not_change_escaped_x00_acceptance
literal_nul_policy_does_not_change_failed_parse_report
literal_nul_policy_is_deterministic
```

## Test file plan

Add or update:

```text
tests/l_ui_source_buffer_literal_nul_policy_invariants.c
scripts/test-l-ui-source-buffer-literal-nul-policy.sh
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-l-ui-source-buffer-literal-nul-policy-contract.sh
```

and before:

```text
sh scripts/test-l-ui-string-literal-escape-contract.sh
```

## Documentation update plan

The implementation PR should update:

```text
README.md
STATUS.md
docs/FOUNDATION_INDEX.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/UPCOMING_WORK.md
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_CONTRACT.md
docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md
```

and add:

```text
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md
```

## No-effect preservation

Literal source NUL rejection is metadata-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility expectations

This implementation plan must not change:

```text
escaped decoded NUL acceptance
literal source NUL rejection
LUI0023 diagnostic mapping
accepted string-literal escape decoding
parser diagnostic code stability
existing C-string fields
purpose_len and value_len semantics
failed-parse detailed report behavior
existing accepted fixture counts
```

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Forbidden implementation behavior

Future source-buffer work must not:

- accept literal NUL source bytes without a separate acceptance contract;
- treat literal source NUL as escaped decoded NUL;
- remove `LUI0023` literal NUL rejection;
- remove `LUI0022` diagnostic compatibility;
- hide literal source NUL in diagnostics;
- produce a partial AST for literal source NUL input;
- make raw `purpose=` or `value=` report fields the assertion target for embedded NUL bytes;
- broaden accepted escape forms;
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
- treat bindings as executable references.

## Current validation command

This implementation plan is guarded by:

```sh
sh scripts/test-l-ui-source-buffer-literal-nul-policy-implementation-plan.sh
```

The guard is static. It does not implement literal source NUL acceptance.

## Implementation gate

Literal source-buffer NUL policy implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement literal source NUL acceptance, source-buffer ownership changes, Unicode display behavior, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.

# Latticra L-UI Source Buffer Literal NUL Policy Contract

Status: source-buffer literal NUL policy contract
Scope: policy for literal `0x00` bytes in L-UI source buffers after escaped decoded NUL acceptance.

## Purpose

This document defines the L-UI policy for literal NUL bytes in source buffers.

L-UI now accepts escaped decoded NUL bytes through:

```text
\x00
```

inside supported source-backed AST string values. That does not mean literal `0x00` bytes in the source buffer are accepted.

This contract keeps literal source NUL bytes rejected by default and defines what a future source-buffer model would need to prove before that boundary could change.

This document does not implement literal NUL acceptance.

## Relationship to previous work

This contract depends on:

```text
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

## Current boundary

The current system provides:

```text
escaped decoded NUL acceptance through \x00
purpose_len and value_len fields
length-aware escaped detailed report fields
literal source NUL rejection
parser-level literal NUL diagnostics
no-effect flags
```

This contract does not add:

```text
literal source NUL acceptance
new source-buffer ownership model
new accepted escape sequences
Unicode display behavior
renderer behavior
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

## Policy decision

Literal `0x00` bytes in L-UI source buffers remain forbidden.

The accepted way to express a decoded NUL byte inside a source-backed string value is the escaped form:

```text
\x00
```

Literal NUL bytes in the source buffer should continue to report:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
LUI0023 literal_nul_in_string
```

## Rationale

Literal source NUL bytes remain forbidden because:

- source buffers still cross C APIs and C-compatible tooling;
- many tools treat NUL as a string terminator;
- embedded source NUL can hide or truncate source text in logs and diagnostics;
- escaped `\x00` is deterministic and visible;
- detailed reports already render escaped decoded NUL as `\x00`;
- accepting literal source NUL requires a separate source-buffer ownership model.

## Escaped decoded NUL remains accepted

This policy must not roll back escaped decoded NUL support.

The following remains accepted in supported source-backed string values:

```text
purpose "A\x00B"
text "left\x00right"
```

The decoded AST byte sequence contains a NUL byte, and the explicit length fields remain authoritative:

```text
ast.card.purpose_len
ast.texts[index].value_len
```

## Literal NUL diagnostic behavior

Literal source NUL inside a validated quoted string value should report:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
LUI0023 literal_nul_in_string
```

The diagnostic span should cover the literal source NUL byte.

The diagnostic should preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Parser behavior

Parser validation should keep detecting literal source NUL bytes before AST materialization.

Literal source NUL should not be treated as:

```text
empty source
unterminated string
invalid hex escape
decoded NUL
internal error
```

Literal source NUL remains a distinct source-buffer error.

## AST behavior

Literal source NUL input should not produce a partial AST.

Failed parse behavior remains:

```text
ast.parse_result.error = LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

## Report behavior

Literal source NUL failures should continue to use failed-parse detailed report behavior.

No decoded AST value should be materialized for literal source NUL input.

Detailed report embedded-NUL surfaces remain reserved for escaped decoded NUL values:

```text
purpose_len
purpose_escaped
value_len
value_escaped
```

## Source-span behavior

For literal source NUL failures, spans should cover exactly the literal `0x00` byte in the source buffer.

Line and column remain one-based byte positions in the in-memory source buffer.

Escaped decoded NUL spans remain source-oriented and cover the source bytes `\x00` when relevant.

## Future source-buffer model requirements

A future implementation may revisit literal source NUL only after a separate implementation plan defines:

1. source buffer ownership rules;
2. source length authority rules;
3. source display and logging behavior;
4. diagnostic rendering for literal NUL;
5. file fixture policy;
6. C API compatibility rules;
7. command-line tooling behavior;
8. report escaping behavior;
9. exact tests;
10. non-claims.

Until that exists, literal source NUL remains forbidden.

## Compatibility expectations

This policy must not change:

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

## No-effect rule

Literal NUL rejection is metadata-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Future test list

A future implementation plan for source-buffer literal NUL policy enforcement should include tests for:

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

## Forbidden behavior

Future source-buffer work must not:

- accept literal NUL source bytes without a separate implementation plan;
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

This contract is guarded by:

```sh
sh scripts/test-l-ui-source-buffer-literal-nul-policy-contract.sh
```

The guard is static. It does not implement literal source NUL acceptance.

## Non-claims

This document does not implement literal source NUL acceptance, source-buffer ownership changes, Unicode display behavior, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.

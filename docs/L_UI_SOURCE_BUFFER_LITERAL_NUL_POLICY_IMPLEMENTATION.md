# Latticra L-UI Source Buffer Literal NUL Policy Implementation

Status: initial implementation contract
Scope: enforcement tests and documentation for rejecting literal `0x00` bytes in L-UI source buffers while preserving escaped decoded NUL acceptance.

## Purpose

This implementation locks down the L-UI source-buffer literal NUL policy.

Literal `0x00` bytes in L-UI source buffers remain rejected.

Escaped decoded NUL remains accepted through:

```text
\x00
```

inside supported source-backed string values.

This implementation does not accept literal source NUL bytes.

## Implementation files

```text
tests/l_ui_source_buffer_literal_nul_policy_invariants.c
scripts/test-l-ui-source-buffer-literal-nul-policy.sh
.github/workflows/c.yml
```

Related active files:

```text
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_ast.c
src/l_ui_parser_diagnostics.c
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_CONTRACT.md
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION_PLAN.md
docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md
```

## Behavior

Literal source-buffer NUL remains rejected as:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
LUI0023 literal_nul_in_string
```

Literal source NUL is not treated as:

```text
empty_source
unterminated_string
invalid_string_escape
invalid_hex_escape
decoded_nul_in_string
internal_error
```

## Escaped decoded NUL compatibility

Escaped decoded NUL remains accepted:

```text
purpose "A\x00B"
text "left\x00right"
```

The decoded AST byte sequence contains a NUL byte, and explicit length fields remain authoritative:

```text
ast.card.purpose_len
ast.texts[index].value_len
```

## Diagnostic behavior

Literal source NUL maps to:

```text
LUI0023 literal_nul_in_string
```

Stable message:

```text
Literal NUL bytes are not supported in AST strings.
```

Stable hint:

```text
Remove literal NUL bytes from the source string.
```

`LUI0022 decoded_nul_in_string` remains available as a compatibility diagnostic, but literal source NUL must not emit it.

## Source-span behavior

Literal source NUL spans cover exactly one source byte:

```text
span_end_offset - span_start_offset == 1
source[span_start_offset] == 0x00
```

Line and column remain one-based byte positions in the in-memory source buffer.

## AST behavior

Literal source NUL input does not produce a partial AST.

Expected failed AST state:

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

## Report behavior

Literal source NUL failures use failed-parse detailed report behavior.

Expected report fields:

```text
parse_error=literal_nul_in_string
rail_count=0
field_count=0
text_count=0
```

Failed reports do not materialize string sections for literal source NUL input:

```text
purpose_escaped=
value_escaped=
```

## Test command

Run:

```sh
sh scripts/test-l-ui-source-buffer-literal-nul-policy.sh
```

The main C workflow runs this check after the source-buffer literal NUL policy implementation-plan guard and before the string-literal escape guards.

## Required invariants

The implementation tests verify:

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

## No-effect boundary

Literal source NUL rejection is metadata-only.

It preserves:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility

This implementation does not change:

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

The first accepted fixture still reports:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Current evidence level

This implementation is an L2 tested source-buffer policy enforcement model for literal source NUL rejection.

It is not literal source NUL acceptance, source-buffer ownership changes, Unicode display behavior, L-UI rendering, command behavior, Nucleus task execution, runtime security, malware prevention, ransomware prevention, sandboxing, or an operating system.

## Next implementation step

The next implementation candidate is:

```text
L-UI semantic validation contract
```

That future work should define semantic checks beyond structural parsing, including field/binding consistency, duplicate handling, rail semantics, and reportable validation errors.

## Non-claims

This document and implementation do not accept literal source NUL bytes, change source-buffer ownership, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, claim malware prevention, claim ransomware prevention, or claim operating-system completeness.

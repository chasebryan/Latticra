# Latticra Lat Language Grammar Implementation

Status: implementation with line-comment metadata refinement
Scope: bounded no-effect Lat / Latticra Language grammar parser, parse result model, AST metadata, line-comment metadata, report surface, fixture, and invariants.

## Purpose

This implementation adds the first bounded parser for the Lat / Latticra Language grammar.

The parser accepts the first Lat-Core declaration grammar shape and records module, declaration, clause, effect, source-span, and no-effect metadata.

The parser also records deterministic line-comment metadata for audit visibility. Line comments are skipped by the grammar, may contain otherwise forbidden behavior marker words, and do not change no-effect flags or clause/operator behavior.

This implementation does not execute Lat, compile Lat, interpret Lat, lower Lat to LIR, render L-UI, call Nucleus task behavior, read files, write files, open network connections, mutate state, or touch hardware.

## Implementation files

```text
include/latticra/lat_parser.h
src/lat_parser.c
tests/lat_language_grammar_invariants.c
scripts/test-lat-language-grammar.sh
fixtures/lat/minimal_module.lat
.github/workflows/c.yml
```

Related active files:

```text
docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
docs/LANGUAGE_NAMING_POLICY.md
docs/LANGUAGE_STRATEGY.md
docs/C_CPP_FOUNDATION_DIRECTION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
```

## Public API

The public API adds:

```text
latticra_lat_parse_error_t
latticra_lat_declaration_kind_t
latticra_lat_effect_t
latticra_lat_source_span_t
latticra_lat_parse_result_t
latticra_lat_ast_module_t
latticra_lat_ast_declaration_t
latticra_lat_ast_clause_t
latticra_lat_parse_error_label
latticra_lat_declaration_kind_label
latticra_lat_effect_label
latticra_lat_parse_source
latticra_lat_parse_report
```

## Capacity constants

The first Lat parser implementation uses exact bounded constants:

```text
LATTICRA_LAT_SOURCE_MAX 65536u
LATTICRA_LAT_NAME_MAX 64u
LATTICRA_LAT_VALUE_MAX 128u
LATTICRA_LAT_DECLARATION_MAX 64u
LATTICRA_LAT_CLAUSE_MAX 128u
LATTICRA_LAT_REPORT_MAX 4096u
```

## Grammar accepted in this slice

The implementation accepts a bounded module wrapper:

```text
lat module <ModuleName> {
  ... declarations ...
}
```

Accepted declaration kinds:

```text
state
policy
transition
assertion
effect
```

Accepted clause forms:

```text
field = value
require left operator right
ensure left operator right
effect target = effect_value
```

Transition declarations preserve the `from <StateName>` source state in `source_name`.

## Fixture

The first repository Lat fixture is:

```text
fixtures/lat/minimal_module.lat
```

It contains a minimal `RootModule` with a `RootCell` state declaration.

## Error labels

Stable parse error labels include:

```text
ok
null_argument
empty_source
source_too_large
unsupported_extension_claim
missing_module
invalid_module_name
unbalanced_brace
unknown_declaration
invalid_declaration_name
unterminated_string
invalid_string_escape
invalid_hex_escape
literal_nul_in_string
capacity_exceeded
forbidden_behavior_marker
internal_error
```

## No-effect boundary

Lat grammar parsing is metadata-only.

It preserves:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Forbidden behavior markers

The parser rejects behavior markers before execution contracts exist:

```text
exec
spawn
syscall
socket
open_file
write_file
hardware_write
```

Markers inside line comments are ignored by the marker scan.

## Source-span behavior

The parser records source-span metadata for module, declaration, and clause records.

Source spans are byte-offset and line/column based.

The parser does not invent byte offsets.

## Report format

`latticra_lat_parse_report` emits a deterministic bounded report beginning with:

```text
LAT GRAMMAR REPORT
```

and including:

```text
status
error
module
declaration_count
state_count
policy_count
transition_count
assertion_count
effect_count
clause_count
comment_count
first_comment_start_offset
first_comment_end_offset
first_comment_start_line
first_comment_start_column
first_comment_end_line
first_comment_end_column
first_declaration_index
first_declaration_kind
first_declaration_name
first_declaration_source
first_declaration_first_clause_index
first_declaration_clause_count
first_clause_index
first_clause_keyword
first_clause_left
first_clause_operator
first_clause_right
first_clause_effect
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
span_start_offset
span_end_offset
span_start_line
span_start_column
span_end_line
span_end_column
```

The first declaration and first clause fields are copied from the parsed AST only when parsing succeeds. They are report metadata only; clause operators are not evaluated.

Small output buffers return:

```text
LATTICRA_STATUS_BUFFER_TOO_SMALL
```

and clear the output buffer.

## Test command

Run:

```sh
sh scripts/test-lat-language-grammar.sh
```

The main C workflow runs this check after the Lat grammar implementation-plan guard and before the state lattice tests.

## Required invariants

The Lat grammar tests verify:

```text
lat_grammar_accepts_minimal_module
lat_grammar_accepts_state_declaration
lat_grammar_accepts_policy_declaration
lat_grammar_accepts_transition_declaration
lat_grammar_accepts_assertion_declaration
lat_grammar_accepts_effect_declaration
lat_grammar_rejects_plain_l_extension_claim
lat_grammar_rejects_unknown_keyword
lat_grammar_rejects_unterminated_string
lat_grammar_rejects_invalid_escape
lat_grammar_rejects_literal_source_nul
lat_grammar_reports_source_spans
lat_grammar_preserves_no_effect_flags
lat_grammar_report_is_deterministic
lat_grammar_report_rejects_small_buffer
lat_grammar_error_labels_are_stable
lat_grammar_kind_labels_are_stable
lat_grammar_does_not_lower_to_lir
lat_grammar_does_not_execute_declarations
lat_grammar_is_deterministic
```

## Compatibility

This implementation does not change:

```text
language naming policy
.lat canonical extension
C/C++ foundation direction
L-UI parser behavior
L-UI semantic validation behavior
LIR shape behavior
state lattice behavior
Nucleus preview behavior
escaped decoded NUL acceptance
literal source-buffer NUL rejection
no-effect flags
```

## Current evidence level

This implementation is an L2 tested grammar parser foundation for bounded Lat-Core metadata.

It is not Lat execution, Lat compilation, Lat interpretation, LIR lowering, L-UI rendering, command behavior, Nucleus task execution, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

## Next implementation step

The next implementation candidate is:

```text
Constrained C++ authority layer contract
```

That future work should define the governed C++ layer before any C++ policy, validator, effect-gate, or audit implementation.

## Non-claims

This document and implementation do not implement Lat execution, Lat compilation, Lat interpretation, LIR lowering, L-UI rendering, command behavior, Nucleus task handling, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

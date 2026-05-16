# Latticra Lat Language Grammar Implementation Plan

Status: implementation planning contract
Scope: exact public API, parser result structs, AST structs, capacities, error labels, reports, fixture paths, parser ownership rules, string handling, source-span mapping, tests, compatibility expectations, and non-claims before Lat parser code.

## Purpose

This document defines the implementation plan for the first Lat / Latticra Language grammar parser.

The Lat grammar contract is already merged and guarded. This plan names the exact public API, result shape, AST metadata, capacity constants, error labels, report format, fixture paths, ownership rules, string literal handling, source-span mapping, tests, and compatibility expectations required before parser code is added.

This document does not implement Lat parsing.

## Relationship to previous work

This plan depends on:

```text
docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
docs/LANGUAGE_NAMING_POLICY.md
docs/LANGUAGE_STRATEGY.md
docs/C_CPP_FOUNDATION_DIRECTION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
docs/EFFECT_GATES.md
docs/STATE_LATTICE.md
include/latticra/lir.h
include/latticra/state_lattice.h
```

Those files remain the source of truth for naming, `.lat` extension policy, C/C++ foundation direction, LIR shape, effect vocabulary, and state-lattice vocabulary.

## Implementation language decision

The first Lat grammar parser should be implemented in C.

Reason:

- current parser, AST, semantic validation, and LIR foundations are C;
- C is the secure substrate;
- the first Lat parser should be bounded, deterministic, and no-effect;
- tests and runners use C and POSIX shell;
- constrained C++ policy layers are planned separately and should not precede a stable C parser substrate.

## Implementation files

The implementation PR should modify or add:

```text
include/latticra/lat_parser.h
src/lat_parser.c
tests/lat_language_grammar_invariants.c
scripts/test-lat-language-grammar.sh
.github/workflows/c.yml
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
```

The implementation should not add C++ infrastructure, LIR lowering, L-UI rendering, Lat execution, runtime behavior, file I/O, network I/O, state mutation, recovery behavior, update behavior, or hardware behavior.

## Public API shape

Add public API names:

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

Recommended function signatures:

```text
const char *latticra_lat_parse_error_label(latticra_lat_parse_error_t error);
const char *latticra_lat_declaration_kind_label(latticra_lat_declaration_kind_t kind);
const char *latticra_lat_effect_label(latticra_lat_effect_t effect);

latticra_status_t latticra_lat_parse_source(
    const char *source,
    size_t source_len,
    latticra_lat_parse_result_t *result);

latticra_status_t latticra_lat_parse_report(
    const latticra_lat_parse_result_t *result,
    char *buffer,
    size_t buffer_len);
```

## Capacity constants

Add exact bounded constants:

```text
LATTICRA_LAT_SOURCE_MAX 65536u
LATTICRA_LAT_NAME_MAX 64u
LATTICRA_LAT_VALUE_MAX 128u
LATTICRA_LAT_DECLARATION_MAX 64u
LATTICRA_LAT_CLAUSE_MAX 128u
LATTICRA_LAT_REPORT_MAX 4096u
```

The first implementation should reject sources larger than `LATTICRA_LAT_SOURCE_MAX`.

## Parse error enum

Add parse error enum values:

```text
LATTICRA_LAT_PARSE_OK
LATTICRA_LAT_PARSE_NULL_ARGUMENT
LATTICRA_LAT_PARSE_EMPTY_SOURCE
LATTICRA_LAT_PARSE_SOURCE_TOO_LARGE
LATTICRA_LAT_PARSE_UNSUPPORTED_EXTENSION_CLAIM
LATTICRA_LAT_PARSE_MISSING_MODULE
LATTICRA_LAT_PARSE_INVALID_MODULE_NAME
LATTICRA_LAT_PARSE_UNBALANCED_BRACE
LATTICRA_LAT_PARSE_UNKNOWN_DECLARATION
LATTICRA_LAT_PARSE_INVALID_DECLARATION_NAME
LATTICRA_LAT_PARSE_UNTERMINATED_STRING
LATTICRA_LAT_PARSE_INVALID_STRING_ESCAPE
LATTICRA_LAT_PARSE_INVALID_HEX_ESCAPE
LATTICRA_LAT_PARSE_LITERAL_NUL_IN_STRING
LATTICRA_LAT_PARSE_CAPACITY_EXCEEDED
LATTICRA_LAT_PARSE_FORBIDDEN_BEHAVIOR_MARKER
LATTICRA_LAT_PARSE_INTERNAL_ERROR
```

Stable labels:

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

## Declaration kind enum

Add declaration kind enum values:

```text
LATTICRA_LAT_DECLARATION_STATE
LATTICRA_LAT_DECLARATION_POLICY
LATTICRA_LAT_DECLARATION_TRANSITION
LATTICRA_LAT_DECLARATION_ASSERTION
LATTICRA_LAT_DECLARATION_EFFECT
LATTICRA_LAT_DECLARATION_UNKNOWN
```

Stable labels:

```text
state
policy
transition
assertion
effect
unknown
```

## Effect enum

Add effect enum values:

```text
LATTICRA_LAT_EFFECT_NONE
LATTICRA_LAT_EFFECT_READ
LATTICRA_LAT_EFFECT_LOCAL_MUTATION
LATTICRA_LAT_EFFECT_HOST_MUTATION
LATTICRA_LAT_EFFECT_NETWORK
LATTICRA_LAT_EFFECT_HARDWARE
LATTICRA_LAT_EFFECT_BOOT
LATTICRA_LAT_EFFECT_RECOVERY
LATTICRA_LAT_EFFECT_EXTERNAL
LATTICRA_LAT_EFFECT_UNKNOWN
```

Stable labels:

```text
none
read
local_mutation
host_mutation
network
hardware
boot
recovery
external
unknown
```

Effects remain metadata only.

## Source span struct

Use a Lat source-span struct compatible with existing source-span conventions:

```text
size_t start_offset;
size_t end_offset;
size_t start_line;
size_t start_column;
size_t end_line;
size_t end_column;
```

A future implementation may reuse `latticra_l_ui_source_span_t` only if that does not create unwanted coupling.

## AST module struct

Add module metadata fields:

```text
char module_name[LATTICRA_LAT_NAME_MAX];
latticra_lat_source_span_t span;
size_t declaration_count;
size_t state_count;
size_t policy_count;
size_t transition_count;
size_t assertion_count;
size_t effect_count;
```

## AST declaration struct

Add declaration metadata fields:

```text
latticra_lat_declaration_kind_t kind;
char name[LATTICRA_LAT_NAME_MAX];
char source_name[LATTICRA_LAT_NAME_MAX];
latticra_lat_source_span_t span;
size_t first_clause_index;
size_t clause_count;
```

`source_name` is used by transition declarations for the `from <StateName>` source state.

## AST clause struct

Add clause metadata fields:

```text
char keyword[LATTICRA_LAT_NAME_MAX];
char left[LATTICRA_LAT_NAME_MAX];
char operator_text[LATTICRA_LAT_NAME_MAX];
char right[LATTICRA_LAT_VALUE_MAX];
latticra_lat_effect_t effect;
latticra_lat_source_span_t span;
```

Clause values are metadata only.

## Parse result struct

Add parse result fields:

```text
latticra_status_t status;
latticra_lat_parse_error_t error;
latticra_lat_source_span_t span;
latticra_lat_ast_module_t module;
latticra_lat_ast_declaration_t declarations[LATTICRA_LAT_DECLARATION_MAX];
latticra_lat_ast_clause_t clauses[LATTICRA_LAT_CLAUSE_MAX];
size_t declaration_count;
size_t clause_count;
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

The result must be fully initialized on success and failure.

## Accepted fixture paths

The implementation PR should add at least one fixture file:

```text
fixtures/lat/minimal_module.lat
```

Recommended fixture content:

```text
lat module RootModule {
  state RootCell {
    origin = "0/0"
    route = "ROOT"
    axis = "ROOT"
    path = "/"
    host_effect = none
    external_effect = none
  }
}
```

Additional in-test string fixtures may be used for policy, transition, assertion, and effect declarations.

## Parser ownership rules

The first parser should:

- never retain pointers into caller-owned source buffers;
- copy names and values into bounded fixed-size fields;
- reject capacity overflow deterministically;
- preserve source spans;
- return status codes;
- avoid heap allocation;
- avoid file I/O;
- avoid global mutable state;
- avoid execution or evaluation.

## String literal handling

String handling should align with L-UI string policy:

```text
\\
\"
\n
\r
\t
\xHH
```

The first Lat parser should reject:

```text
unterminated strings
unsupported escapes
invalid hex escapes
literal source-buffer NUL bytes
string values that exceed bounded storage
```

Escaped decoded NUL through `\x00` may be accepted only if explicit length-carrying storage is implemented in the same parser slice. If not, it should be rejected in the first parser implementation plan follow-up.

## Forbidden behavior markers

The parser should reject obvious behavior markers that imply execution before contracts exist:

```text
exec
spawn
syscall
socket
open_file
write_file
hardware_write
```

These markers may appear only in comments if comments are stripped before validation.

## Report format

`latticra_lat_parse_report` should emit a deterministic bounded report:

```text
LAT GRAMMAR REPORT
status=<integer-status>
error=<lat-error-label>
module=<module-name>
declaration_count=<count>
state_count=<count>
policy_count=<count>
transition_count=<count>
assertion_count=<count>
effect_count=<count>
clause_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
span_start_offset=<offset>
span_end_offset=<offset>
span_start_line=<line>
span_start_column=<column>
span_end_line=<line>
span_end_column=<column>
```

Small output buffers should return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the buffer.

## Source-span mapping

Use these source-span mappings:

```text
module -> full module declaration span
declaration -> full declaration span
field assignment -> assignment clause span
require clause -> requirement clause span
ensure clause -> ensure clause span
effect clause -> effect clause span
string literal -> string token span if exposed later
identifier reference -> identifier token span if exposed later
```

The parser must not invent byte offsets.

## No-effect preservation

Lat grammar parsing is metadata-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Exact implementation test list

The implementation PR should include tests for:

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

## Test file plan

Add:

```text
tests/lat_language_grammar_invariants.c
scripts/test-lat-language-grammar.sh
fixtures/lat/minimal_module.lat
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-lat-language-grammar-contract.sh
```

and before:

```text
sh scripts/test-state-lattice.sh
```

## Documentation update plan

The implementation PR should update:

```text
README.md
STATUS.md
docs/FOUNDATION_INDEX.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
scripts/test-project-strategy-status-framework.sh
```

and add:

```text
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
```

## Compatibility expectations

The implementation must not change:

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

## Forbidden implementation behavior

Lat grammar implementation must not:

- claim plain `L` as the public language name;
- claim `.l` as the canonical source extension;
- execute declarations;
- mutate state;
- lower to LIR;
- render L-UI;
- call Nucleus task execution;
- evaluate host state;
- write files;
- read files;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- broaden L-UI behavior;
- weaken semantic validation;
- accept literal source-buffer NUL;
- imply a compiler, interpreter, runtime, package manager, sandbox, or operating-system surface.

## Current validation command

This implementation plan is guarded by:

```sh
sh scripts/test-lat-language-grammar-implementation-plan.sh
```

The guard is static. It does not implement Lat parsing.

## Implementation gate

Lat grammar parser implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement Lat, Lat-Core, Lat-Orch, a parser, compiler, interpreter, runtime, package manager, LIR lowering, L-UI rendering, command behavior, Nucleus task handling, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

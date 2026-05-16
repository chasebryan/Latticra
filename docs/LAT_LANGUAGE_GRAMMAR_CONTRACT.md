# Latticra Lat Language Grammar Contract

Status: Lat language grammar contract
Scope: first grammar contract for Lat / Latticra Language before parser implementation, LIR lowering, execution, runtime behavior, or operating-system behavior.

## Purpose

This document defines the first grammar contract for:

```text
Lat / Latticra Language
```

Lat is the approved short name for the Latticra Language. The canonical source extension is:

```text
.lat
```

This contract defines the first syntax shape for Lat-Core declarations only. It does not implement a parser, compiler, interpreter, runtime, package format, command behavior, Nucleus task execution, LIR lowering, L-UI rendering, or operating-system behavior.

## Naming boundary

Lat must follow the language naming policy:

```text
docs/LANGUAGE_NAMING_POLICY.md
```

The public language name is:

```text
Lat / Latticra Language
```

The canonical source extension is:

```text
.lat
```

Forbidden public claims:

```text
L
.l
```

Plain `L` is not the public language name, and `.l` is not the canonical source extension.

## Relationship to previous work

This contract depends on:

```text
docs/LANGUAGE_NAMING_POLICY.md
docs/LANGUAGE_STRATEGY.md
docs/LIR_SHAPE_CONTRACT.md
docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md
docs/LIR_SHAPE_IMPLEMENTATION.md
docs/EFFECT_GATES.md
docs/STATE_LATTICE.md
docs/TRI_PLANE_TRANSITION.md
docs/NUCLEUS_PREVIEW.md
include/latticra/lir.h
include/latticra/state_lattice.h
```

Those files remain the source of truth for public naming, language-family roles, LIR shape, effect vocabulary, state-lattice fixtures, no-effect preview behavior, and Nucleus preview boundaries.

## First grammar target

The first grammar target is:

```text
Lat-Core
```

Lat-Core is the state, policy, assertion, and transition declaration subset of Lat.

Lat-Orch remains future work and must not be implemented or implied by this contract.

## Source unit

A Lat source unit should represent one module-like document:

```text
lat module <ModuleName> {
  ... declarations ...
}
```

The first grammar should require an explicit module wrapper.

## Initial declaration kinds

The first Lat-Core grammar should define these declaration kinds:

```text
state
policy
transition
assertion
effect
```

These declarations are metadata only until separate parser, semantic, lowering, and execution contracts exist.

## Lexical grammar

The first lexical grammar should include:

```text
identifier
keyword
string_literal
integer_literal
boolean_literal
effect_literal
operator
punctuation
comment
whitespace
```

Identifier policy:

```text
[A-Za-z_][A-Za-z0-9_]*
```

Reserved keywords:

```text
lat
module
state
policy
transition
assertion
effect
from
require
ensure
where
let
true
false
none
read
local_mutation
host_mutation
network
hardware
boot
recovery
external
```

Future implementation may add keywords only through a separate contract or implementation plan.

## Comment policy

The first grammar should allow line comments only:

```text
// comment text
```

Block comments are out of scope until a later contract.

## String literal policy

Lat string literals should use quoted strings:

```text
"text"
```

String escapes should align with the L-UI string-literal escape policy unless a future Lat-specific contract changes it:

```text
\\
\"
\n
\r
\t
\xHH
```

Escaped decoded NUL through `\x00` may be represented only with explicit length-carrying storage in a future implementation.

Literal source-buffer NUL bytes remain forbidden.

## Effect literals

Initial effect literals:

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
```

The first parser may accept effect declarations as metadata, but it must not perform the effect.

## State declaration grammar

Lat example syntax only:

```text
state RootCell {
  origin = "0/0"
  route = "ROOT"
  axis = "ROOT"
  path = "/"
  host_effect = none
  external_effect = none
}
```

State declarations should allow fields compatible with the current state lattice vocabulary:

```text
origin
route
axis
path
breadcrumb
trace
safe_portal
rollback
health
risk
lock
dark_phase
host_effect
external_effect
```

This grammar does not mutate runtime state.

## Policy declaration grammar

Lat example syntax only:

```text
policy SafePreview {
  require risk != "high"
  require lock == "open"
  ensure host_effect == none
  ensure external_effect == none
}
```

Policy declarations should describe requirements and assertions as metadata only.

## Transition declaration grammar

Lat example syntax only:

```text
transition MoveRight from RootCell {
  require lock == "open"
  require risk != "high"
  effect host = none
  effect external = none
}
```

Transition declarations should require:

```text
transition name
source state name
require clauses
effect clauses
```

Transition declarations must not execute movement, mutate state, or call Nucleus task execution.

## Assertion declaration grammar

Lat example syntax only:

```text
assertion RootCellIsSafe {
  require health == "ok"
  require host_effect == none
  require external_effect == none
}
```

Assertions are metadata until a future validator implements them.

## Effect declaration grammar

Lat example syntax only:

```text
effect PreviewOnly {
  host = none
  external = none
  network = none
  hardware = none
}
```

Effect declarations describe intended effect boundaries only. They do not grant capability.

## Expression grammar

The first expression grammar should be deliberately small:

```text
identifier
string_literal
integer_literal
boolean_literal
effect_literal
comparison_expression
logical_and_expression
logical_or_expression
parenthesized_expression
```

Initial comparison operators:

```text
==
!=
<
<=
>
>=
```

Initial logical operators:

```text
&&
||
```

No function calls, loops, arbitrary arithmetic, imports, macros, generic types, allocation, host calls, network calls, or hardware calls are in scope.

## Module report model

A future Lat grammar parser should produce deterministic bounded reports.

Suggested report fields:

```text
LAT GRAMMAR REPORT
status=<status>
module=<module-name>
state_count=<count>
policy_count=<count>
transition_count=<count>
assertion_count=<count>
effect_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
```

## Source-span behavior

Future Lat parser and AST work should preserve source spans for:

```text
module declarations
state declarations
policy declarations
transition declarations
assertion declarations
effect declarations
field assignments
require clauses
ensure clauses
effect clauses
string literals
identifier references
```

Lat source-span behavior must not invent byte offsets.

## LIR relationship

Lat grammar work must not lower to LIR until a separate Lat-to-LIR lowering contract exists.

The first relationship is planning-only:

```text
Lat source -> future Lat parser -> future Lat AST -> future Lat semantic validation -> future LIR lowering
```

The current LIR shape implementation lowers semantically valid L-UI ASTs only.

## No-effect rule

Lat grammar work is metadata-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Lat grammar work must not execute declarations, mutate state, render UI, lower to LIR, call Nucleus task code, write files, read files, open network connections, call server code, call update code, call recovery code, or touch hardware.

## Compatibility expectations

Lat grammar work must not change:

```text
language naming policy
.lat canonical extension
L-UI parser behavior
L-UI semantic validation behavior
LIR shape behavior
state lattice behavior
Nucleus preview behavior
escaped decoded NUL acceptance
literal source-buffer NUL rejection
no-effect flags
```

## Future implementation gate

Lat parser implementation must not begin until a separate implementation plan defines:

1. public API shape;
2. parser result structs;
3. AST structs;
4. capacity constants;
5. error enum labels;
6. diagnostic/report format;
7. accepted fixture paths;
8. parser ownership rules;
9. string literal handling;
10. source-span mapping;
11. exact tests;
12. compatibility expectations;
13. non-claims.

That next planning slice is:

```text
Lat language grammar implementation plan
```

## Future test list

A future implementation plan should include tests for:

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
lat_grammar_does_not_lower_to_lir
lat_grammar_does_not_execute_declarations
lat_grammar_is_deterministic
```

## Forbidden behavior

Lat grammar work must not:

- claim plain `L` as the public language name;
- claim `.l` as the canonical source extension;
- implement a parser before an implementation plan;
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
- remove escaped decoded NUL support;
- imply a compiler, interpreter, runtime, package manager, sandbox, or operating-system surface.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-lat-language-grammar-contract.sh
```

The guard is static. It does not implement Lat.

## Non-claims

This document does not implement Lat, Lat-Core, Lat-Orch, a parser, compiler, interpreter, runtime, package manager, LIR lowering, L-UI rendering, command behavior, Nucleus task handling, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

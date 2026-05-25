# Latticra Lat Language Foundation Analysis

Status: foundation analysis proposal
Scope: deeper Lat / Latticra Language foundation after the initial bounded grammar parser.

## Purpose

Lat should mature as a contract and declaration language, not as an accidental executable scripting surface. The existing grammar parser is a necessary first slice, but a stronger foundation requires a semantic layer that decides what a parsed Lat document means, what names are valid, what relationships are permitted, and what remains explicitly non-operational.

This analysis defines the next foundation layer:

```text
Lat source -> bounded parser -> Lat AST metadata -> semantic validation -> normalized Lat model -> LIR metadata lowering
```

The parser, semantic validation, normalized model, and Lat-to-LIR metadata lowering phases now exist in bounded no-effect form. This analysis remains the foundation record for the semantic and normalization direction.

## Current foundation summary

The current Lat parser already establishes important constraints:

- source size is bounded;
- names, values, declarations, clauses, and reports use fixed-size storage;
- the parser preserves source spans;
- declarations are metadata only;
- no execution, mutation, server, recovery, or hardware behavior is allowed;
- Lat uses the public name `Lat / Latticra Language` and `.lat`, not plain `L` or `.l`.

That is the right parser posture. The missing foundation is semantic meaning.

## Main gap

A grammar parser can say:

```text
this document has a transition declaration
```

It cannot yet say:

```text
the transition source state exists
the effect target is allowed
the declaration name is unique
the field name belongs to the Lat-Core state vocabulary
the document still preserves the no-effect boundary
```

Without these semantic checks, Lat remains syntactically bounded but architecturally loose.

## Foundation principle

The next layer should be semantic validation, not execution.

Lat semantic validation should answer:

1. Is the parsed module internally coherent?
2. Are declaration names unique and resolvable?
3. Are transition references valid?
4. Are state fields from the known state-lattice vocabulary?
5. Are effect targets known and denied by default unless they are `none`?
6. Are policy and assertion clauses restricted to requirement/assurance forms?
7. Are reports deterministic, bounded, source-aware, and operator-readable?

It should not answer:

- how to execute a transition;
- how to mutate state;
- how to lower to LIR;
- how to render L-UI;
- how to call Nucleus;
- how to authorize real host, network, recovery, or hardware effects.

## Proposed Lat foundation phases

### Phase 0: Naming and role policy

Lat is the approved short name. `.lat` is the canonical extension. Plain `L` and `.l` remain forbidden.

### Phase 1: Lexical and grammar parser

Current parser role:

```text
source bytes -> bounded AST metadata + parse report
```

It owns source spans, syntax errors, declaration records, clause records, and no-effect parse reports.

### Phase 2: Semantic validation

Proposed role:

```text
parse result -> semantic diagnostics + semantic report
```

It owns:

- duplicate declaration detection;
- transition source resolution;
- declaration-specific clause rules;
- state-field vocabulary checking;
- effect-target checking;
- first default-deny effect validation;
- stable diagnostic labels;
- deterministic semantic reports.

### Phase 3: Lat model normalization

Current role:

```text
parse result + semantic result -> normalized Lat module model
```

The normalized model carries explicit declaration and clause index tables for states, policies, transitions, assertions, and effect declarations. It remains no-effect and does not read source bytes.

### Phase 4: Lat-to-LIR lowering

Current role:

```text
semantic Lat module metadata -> bounded LIR shape
```

The current implementation remains metadata-only and no-effect. It does not execute Lat or LIR.

### Phase 5: Effect-gated runtime interpretation

Future role:

```text
validated Lat / LIR -> runtime request classification -> effect gate -> denied or authorized behavior
```

This must wait for explicit runtime, threat-model, effect-gate, audit, and authority-layer contracts.

## Semantic validation rules proposed for this slice

### Module rule

The parser must have succeeded before semantic validation runs.

```text
parse.error == ok
```

If parsing did not succeed, semantic validation returns a semantic `parse_not_ok` diagnostic and does not reinterpret the source.

### Declaration identity rule

Declaration names are globally unique within a module for this slice.

Reason: global uniqueness prevents ambiguity before namespacing, imports, traits, modules, or overloads exist.

### State declaration rule

A `state` declaration may contain only field assignments.

Allowed fields:

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

`host_effect` and `external_effect` must use known effect labels, and this first semantic slice accepts only `none` as an allowed declared effect value.

### Policy declaration rule

A `policy` declaration may contain only:

```text
require left operator right
ensure left operator right
```

Field assignments and effect assignments are rejected in policies for this slice.

### Transition declaration rule

A `transition` declaration must name an existing source state:

```text
transition MoveRight from RootCell { ... }
```

`RootCell` must resolve to a declared state.

A transition may contain requirement clauses and explicit no-effect metadata clauses:

```text
require lock == "open"
effect host = none
effect external = none
```

This first semantic slice rejects non-`none` declared effects.

### Assertion declaration rule

An `assertion` declaration may contain only `require` or `ensure` clauses.

Assertions are semantic checks, not runtime actions.

### Effect declaration rule

An `effect` declaration may contain only known effect targets:

```text
host
external
network
hardware
boot
recovery
local
```

The value must be a known Lat effect label. This first slice accepts only `none` as an allowed declared value.

## Diagnostic model

Semantic diagnostics should be stable, bounded, source-span-aware, and deterministic.

Each diagnostic records:

```text
error label
source span
declaration index
clause index
name
detail
```

The semantic result records the first error as the summary error while retaining a bounded diagnostic list.

## Evidence level

This proposal targets an L2 implementation slice:

```text
contract + implementation plan + C implementation + invariant tests + deterministic report
```

It does not claim runtime capability.

## Non-claims

This analysis does not implement Lat execution, Lat compilation, Lat interpretation, LIR lowering, L-UI rendering, command behavior, Nucleus task handling, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

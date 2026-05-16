# Latticra Language Naming Policy

Status: language naming policy
Scope: public naming and file-extension policy for the Latticra native language family.

## Purpose

This document corrects the early shorthand that called the native Latticra programming language `L`.

Plain `L` is too collision-prone for a public language name or file extension. Latticra should use project-specific language names and extensions before language implementation begins.

This policy does not implement a programming language, parser, compiler, runtime, package format, or execution model.

## Collision rule

Latticra must not claim plain:

```text
L
.l
```

as the public native language name or canonical file extension.

Reason:

- single-letter language names are ambiguous;
- existing language literature already uses L-like names and variants;
- `.l` is too short and too likely to collide with existing tools;
- Latticra should avoid avoidable naming confusion before syntax stabilizes.

## Public native language name

The public native language name should be:

```text
Latticra Language
```

The approved short name should be:

```text
Lat
```

`Lat` is a project-specific shorthand for Latticra Language.

## File extension policy

The canonical source file extension for the native Latticra Language should be:

```text
.lat
```

Reserved related extensions:

```text
.lat
.lui
.lir
```

Meaning:

| Extension | Meaning |
| --- | --- |
| `.lat` | Latticra Language source, including future Lat-Core and Lat-Orch forms. |
| `.lui` | Latticra UI declaration source. |
| `.lir` | Latticra Intermediate Representation, internal or generated unless later promoted. |

The project should not use `.l` for Latticra source.

## Dialect naming policy

Rename the intended language-family labels as follows:

| Old shorthand | New public label | Role |
| --- | --- | --- |
| `L` | `Lat` / `Latticra Language` | Native Latticra language family. |
| `L-Core` | `Lat-Core` | State, policy, assertion, and transition declarations. |
| `L-Orch` | `Lat-Orch` | Nucleus orchestration planning and effect-gated task descriptions. |
| `L-UI` | `L-UI` | Operator interface declaration language; existing `.lui` files remain valid. |
| `LIR` | `LIR` | Latticra Intermediate Representation. |

`L-UI` may keep its existing name because it is already a compound project-specific label and has an existing `.lui` fixture path.

`LIR` may remain as an internal representation name because it expands to Latticra Intermediate Representation, but `.lir` should be treated as internal or generated until a later contract promotes it.

## Documentation rule

Future docs should write:

```text
Lat / Latticra Language
```

instead of:

```text
L
```

when referring to the native Latticra language.

Historical references may say:

```text
formerly documented as L
```

only when explaining the migration.

## Syntax example rule

Syntax examples should be marked as:

```text
Lat example syntax only
```

not:

```text
L syntax
```

until a grammar contract exists.

## Implementation boundary

This policy does not change:

```text
L-UI parser behavior
.lui fixtures
LIR shape
AST behavior
string-literal escape behavior
parser diagnostics
state lattice behavior
Nucleus preview behavior
```

## Future implementation gate

Before implementing native Latticra Language parsing, a future contract must define:

1. canonical language name;
2. canonical file extension;
3. dialect boundaries;
4. grammar scope;
5. parser input ownership;
6. effect boundary;
7. non-claims;
8. exact fixture paths;
9. exact tests.

That future work should use the names and extensions from this policy.

## Forbidden behavior

Future language work must not:

- claim plain `L` as the public language name;
- claim `.l` as the canonical source extension;
- imply compatibility with unrelated L-like languages;
- imply a completed compiler or runtime before implementation exists;
- treat `.lat` files as executable before an execution contract exists;
- treat `.lui` files as commands;
- broaden L-UI behavior through the language naming policy.

## Current validation command

This policy is guarded by:

```sh
sh scripts/test-language-naming-policy.sh
```

The guard is static. It does not implement a language.

## Non-claims

This document does not implement Lat, Lat-Core, Lat-Orch, L-UI rendering, LIR lowering, a parser, compiler, runtime, package manager, command behavior, Nucleus task execution, live movement, state mutation, server interaction, recovery behavior, hardware behavior, boot readiness, sandboxing, or operating-system completeness.

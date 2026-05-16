# Latticra Naming System

Status: initial naming system
Scope: professional terminology, public architecture naming, and implementation naming rules.

## Purpose

Latticra needs a professional naming system before implementation work expands.

Public names should fit academic systems work, embedded software, formal state models, deterministic validation, and real implementation.

## Naming principles

1. Use names that describe function before metaphor.
2. Keep exploratory names out of public architecture unless they become formalized.
3. Avoid names that make Latticra sound like a game, fantasy world, or toy operating system.
4. Prefer systems, formal methods, embedded software, and computer-science vocabulary.
5. Preserve strong conceptual meaning through precise implementation terms.
6. Avoid public dependency on predecessor project names.

## Primary project names

| Name | Meaning |
| --- | --- |
| Latticra | Lattice-oriented systems architecture and implementation project. |
| Lat / Latticra Language | Native Latticra programming language family. |
| Nucleus | Latticra supervisor and orchestration core. |
| L-UI | Terminal/operator interface declaration language or dialect. |
| LIR | Latticra Intermediate Representation. |

## Preferred implementation vocabulary

| Concept | Latticra term |
| --- | --- |
| Software universe | Lattice universe |
| State space | State lattice |
| Movement | Transition |
| Multi-plane movement | Tri-plane transition model |
| Route/origin/axis/path | Route/origin/axis/path |
| Visibility surface | Lens or visibility rail |
| Rails | Operator rails or state rails |
| Portal-like boundary | Gate or transition gate |
| Safe transition boundary | Recovery gate |
| Mirror-like view | Reflection surface or state reflection |
| Entity | Cell actor or lattice actor |
| Inactive context | Shadow context |
| Nested scope | Domain stack or nested domain |
| Split/fault boundary | Partition, split domain, or fault boundary |
| Recursive structure | Recursive lattice or recursive domain |
| Floor/layer concept | Layer, tier, or plane |
| Staged candidate work | Staged candidate system |
| Verification and repair work | Verification and repair suite |
| Hardware evidence path | Substrate evidence path |
| Native language family | Lat / Latticra Language |

## Names to avoid in formal architecture

Avoid these as official Latticra component names unless a later design explicitly approves them:

```text
black arts
ghost
magic
spell
haunt
arena
game
world map
fantasy universe
hacker magic
```

These can remain private brainstorming vocabulary, but Latticra implementation names should be clearer.

## Naming levels

Use distinct naming levels:

```text
Project name: Latticra
Supervisor name: Nucleus
Language name: Lat / Latticra Language
Interface dialect: L-UI
Intermediate form: LIR
State model: State lattice
Transition model: Tri-plane transition
Gate model: Effect gate
```

## File and module naming rules

Use uppercase snake-case for major public docs already in the repository:

```text
STATE_LATTICE.md
TRI_PLANE_TRANSITION.md
EFFECT_GATES.md
```

Use lowercase snake_case for C/Rust source:

```text
state_lattice.c
tri_plane_transition.rs
effect_gate.h
```

Use `lat_` or explicit `latticra_` prefixes for native language internals when needed:

```text
lat_parser
lat_runtime
latticra_ir
```

Use `l_ui_` for existing L-UI parser and report code:

```text
l_ui_parser
l_ui_parser_ast
l_ui_parser_diagnostics
```

## Review rule

A new Latticra name should answer:

1. What does it do?
2. Is it professional?
3. Is it understandable without project lore?
4. Does it avoid overclaiming?
5. Can a systems engineer understand it from the public docs?

## Current decision

The native language name is:

```text
Lat / Latticra Language
```

The canonical native source extension is:

```text
.lat
```

The supervisor name is:

```text
Nucleus
```

The UI language or dialect is:

```text
L-UI
```

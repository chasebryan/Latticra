# Latticra Naming System

Status: initial naming system
Scope: professional terminology, Phase1 concept translation, and implementation naming rules.

## Purpose

Latticra needs a professional naming system before implementation begins.

Phase1 was allowed to use exploratory and expressive names while discovering what was possible. Latticra should use names that fit academic systems work, embedded software, formal state models, and real implementation.

## Naming principles

1. Use names that describe function before mythology.
2. Keep experimental names in Phase1 unless they become formalized.
3. Avoid names that make Latticra sound like a game, fantasy world, or toy OS.
4. Prefer systems, formal methods, embedded software, and computer-science vocabulary.
5. Preserve powerful conceptual meaning through precise implementation terms.
6. Avoid overloading Base1, Phase1, and Fyr names inside Latticra.

## Primary project names

| Name | Meaning |
| --- | --- |
| Latticra | Real-system implementation track for lattice/grid/matrix-based software universes. |
| L | Native Latticra language family. |
| Nucleus | Latticra supervisor and orchestration core. |
| L-UI | Terminal/operator interface language or dialect. |
| LIR | Latticra Intermediate Representation. |

## Preferred implementation vocabulary

| Concept | Latticra term |
| --- | --- |
| Software universe | Lattice universe |
| State space | State lattice |
| Movement | Transition |
| Phase movement | Lattice transition |
| Trilateral Phase Movement | Tri-plane transition model |
| Route/origin/axis/path | Keep as route/origin/axis/path |
| Optics | Lens or visibility rail |
| Rails | Operator rails or state rails |
| Portal | Gate or transition gate |
| Safe portal | Recovery gate |
| Mirror | Reflection surface or state reflection |
| Entity | Cell actor or lattice actor |
| Ghost | Shadow context or inactive context |
| Nest | Domain stack or nested domain |
| Fracture | Partition, split domain, or fault boundary |
| Fractal | Recursive lattice or recursive domain |
| Floor | Layer, tier, or plane |
| Black Arts | Staged candidate system |
| White Arts | Verification and repair suite |
| Base1 | Substrate evidence lineage |
| Fyr | Phase-native language ancestor to L |

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

These can remain historical or Phase1-era vocabulary, but Latticra implementation names should be clearer.

## Naming levels

Use distinct naming levels:

```text
Project name: Latticra
Supervisor name: Nucleus
Language name: L
Interface dialect: L-UI
Intermediate form: LIR
State model: State lattice
Transition model: Tri-plane transition
Gate model: Effect gate
```

## File and module naming rules

Use lowercase kebab-case for docs:

```text
state-lattice.md
tri-plane-transition.md
effect-gates.md
```

Use lowercase snake_case for C/Rust source:

```text
lattice_state.c
tri_plane_transition.rs
effect_gate.h
```

Use `l_` prefix for L language internals only when needed:

```text
l_parser
l_runtime
l_ir
```

## Review rule

A new Latticra name should answer:

1. What does it do?
2. Is it professional?
3. Is it distinct from Phase1 simulation names?
4. Does it avoid overclaiming?
5. Can a systems engineer understand it without lore?

## Current decision

The native language name is planned as:

```text
L
```

The supervisor name is planned as:

```text
Nucleus
```

The UI language or dialect is planned as:

```text
L-UI
```

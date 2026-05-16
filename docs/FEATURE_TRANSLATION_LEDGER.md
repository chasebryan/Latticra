# Latticra Feature Vocabulary Ledger

Status: initial vocabulary ledger
Scope: mapping exploratory concept labels into professional Latticra architecture terms.

## Purpose

Latticra needs stable public vocabulary before broad implementation work expands.

This ledger prevents informal, exploratory, or metaphor-heavy names from becoming unclear implementation contracts.

The public project should describe features by their Latticra purpose, behavior, evidence level, and effect boundary rather than by predecessor-project lore.

## Vocabulary table

| Exploratory concept | Latticra term | Notes |
| --- | --- | --- |
| General state movement | Lattice transition | General state movement inside a structured lattice. |
| Multi-plane transition check | Tri-plane transition model | Transition checked across spatial, state, and safety planes. |
| Portal-like boundary | Gate | A controlled transition boundary. |
| Safe transition boundary | Recovery gate | A gate associated with recovery visibility or recovery eligibility. |
| Mirror-like state view | Reflection surface | Read-only view or reflection of state. |
| Modeled entity | Lattice actor | A modeled actor within a state lattice. |
| Inactive context | Shadow context | An inactive, pending, or non-primary context. |
| Nested scope | Domain stack | Nested scope or domain stack. |
| Split/fault boundary | Partition boundary | Split, isolation, or fault boundary. |
| Recursive structure | Recursive lattice | Recursive state domain or repeated lattice pattern. |
| Floor/layer concept | Layer / plane / tier | Use the most precise term per context. |
| Visibility concept | Lens / visibility rail | Operator visibility and state display surface. |
| Rail display concept | Operator rails | Terminal/state display rails. |
| Hardware evidence track | Substrate evidence path | Boot, recovery, hardware, and validation evidence path. |
| Native language path | Lat / Latticra Language | Public native language family and programming-language direction. |
| Staged candidate work | Staged candidate system | Candidate staging, never automatic system behavior. |
| Verification and repair work | Verification and repair suite | Defensive validation, maintenance, and repair-oriented checks. |
| Matrix | State matrix | Structured multi-dimensional state surface. |
| Universe | Lattice universe | Structured software universe with explicit contracts. |
| Origin | Origin | Keep term. |
| Route | Route | Keep term. |
| Axis | Axis | Keep term. |
| Path | Path | Keep term. |
| Trace | Trace | Keep term. |

## Promotion categories

Each translated feature should be assigned one category:

```text
historical-only
concept-candidate
fixture-candidate
tested-model-candidate
read-only-surface-candidate
implementation-candidate
blocked
```

## Initial category assignments

| Latticra term | Initial category | Reason |
| --- | --- | --- |
| State lattice | fixture-candidate | First implementation target. |
| Tri-plane transition model | tested-model-candidate | Needs pure transition and denial tests before surface work. |
| Gate | concept-candidate | Needs effect-gate contract first. |
| Recovery gate | concept-candidate | Must not perform recovery until evidence supports it. |
| Reflection surface | read-only-surface-candidate | Safe as inspection only. |
| Lattice actor | concept-candidate | Needs strict non-claim and lifecycle rules. |
| Shadow context | concept-candidate | Needs visibility rules. |
| Domain stack | tested-model-candidate | Can derive from nested-domain lessons. |
| Partition boundary | concept-candidate | Needs failure and isolation vocabulary. |
| Recursive lattice | concept-candidate | Needs mathematical definition before implementation. |
| Lens / visibility rail | read-only-surface-candidate | UI/reporting only at first. |
| Staged candidate system | tested-model-candidate | Must remain approval-gated. |
| Verification and repair suite | concept-candidate | Must remain defensive and evidence-bound. |

## Rejected direct public names

Do not directly import these names as formal Latticra public components:

```text
black arts
ghost
magic
arena
game
hacker console
simulator OS
```

They may appear in private brainstorming, but not as public Latticra implementation names.

## Promotion rule

A feature may enter implementation only after it has:

1. a Latticra name;
2. a direct Latticra purpose;
3. evidence level;
4. non-claims;
5. effect boundary;
6. test plan;
7. failure behavior.

## First implementation candidate

The first implementation candidate remains:

```text
state lattice fixture
```

It should include labels for origin, route, axis, path, breadcrumb, trace, safe_portal, rollback, health, risk, lock, dark_phase, host_effect, and external_effect.

## Non-claims

This ledger does not implement any feature.

It translates and constrains vocabulary before implementation begins.

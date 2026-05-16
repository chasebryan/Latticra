# Latticra UI Terminal Language

Status: initial L-UI design
Scope: terminal/operator UI language direction, rails, reports, and non-claims.

## Purpose

Latticra should define its terminal and operator interface language before implementation code expands.

The terminal UI should not be a pile of hard-coded strings. It should become a controlled, declarative surface that can render state, effects, gates, evidence, and supervisor reports clearly.

## Name

The planned UI language or dialect is:

```text
L-UI
```

L-UI is part of the Latticra language family, but it should remain narrower than full Lat.

## Role

L-UI describes:

- operator rails;
- state cards;
- evidence reports;
- update reports;
- effect-gate reports;
- policy-denial messages;
- supervisor status panels;
- terminal-safe layouts.

## Design principles

1. Declarative before imperative.
2. Terminal-safe before graphical.
3. Text-first before animation.
4. Readable on narrow terminals.
5. Copy-safe command output.
6. No hidden mutation.
7. Effect-free by default.
8. Accessibility and fallback modes from the beginning.

## Initial surface vocabulary

```text
rail
card
row
field
status
warning
reason
gate
trace
breadcrumb
state
```

## Example direction

Example syntax only:

```text
card StateOverview {
  row "origin" = state.origin
  row "route" = state.route
  row "axis" = state.axis
  row "host effect" = state.host_effect
  row "external effect" = state.external_effect
}
```

This syntax is not implemented yet.

## Operator rails

Initial rail categories:

```text
top rail      -> identity, target, architecture, channel
state rail    -> origin, route, axis, path, breadcrumb, trace
safety rail   -> health, risk, lock, gates, effects
bottom rail   -> result, reason, next action, evidence level
```

## Required report fields

Every report surface that describes a request should eventually include:

```text
request_id
source
effect
policy_result
reason
evidence_level
rollback_state
host_effect
external_effect
```

## L-UI and Nucleus

Nucleus supplies state. L-UI renders it.

L-UI should not own policy decisions, effect gates, update behavior, server interaction, or hidden task execution.

## L-UI and Lat

Lat may eventually generate or validate L-UI documents.

Early L-UI should be static and fixture-backed.

## Color and accessibility

L-UI must support:

- plain text mode;
- no-color mode;
- narrow terminal mode;
- screen-reader-friendly output where possible;
- clear labels independent of color.

## First implementation target

The first L-UI implementation target should be a static report fixture for the state lattice.

It must be:

```text
deterministic
ASCII-safe
copy-safe
read-only
effect-free
```

## Non-claims

This document does not implement L-UI.

It defines the UI language direction and terminal boundary before implementation begins.
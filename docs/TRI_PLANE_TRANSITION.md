# Latticra Tri-Plane Transition Model

Status: initial implementation contract
Scope: pure preview transitions across spatial, state, and safety planes.

## Purpose

The Tri-Plane Transition Model is the second Latticra implementation unit.

It models lattice movement as a pure preview transition. It accepts a current state lattice and a movement request, then returns a preview result and next-state copy without mutating the input state.

## Implementation files

```text
include/latticra/tri_plane_transition.h
src/tri_plane_transition.c
tests/tri_plane_transition_invariants.c
scripts/test-tri-plane-transition.sh
```

## Planes

A transition is evaluated across three conceptual planes:

```text
Spatial plane
  origin / route / axis / path

State plane
  breadcrumb / trace / current state labels

Safety plane
  safe_portal / rollback / health / risk / lock / dark_phase / host_effect / external_effect
```

## Movement vocabulary

Initial movement values:

```text
up
down
left
right
enter
back
root
unknown
```

## Result vocabulary

Initial transition results:

```text
allowed-preview
denied
```

Initial denial/decision reasons:

```text
ok
null-argument
unknown-direction
lock-closed
risk-high
rollback-unavailable
```

## Preview-only boundary

The model is preview-only.

It must not:

- mutate the input state;
- mutate origin;
- execute recovery;
- touch host state;
- use networking;
- touch hardware;
- change boot state;
- perform external effects;
- perform hidden allocation;
- depend on server interaction.

## Default safe preview

A safe `right` preview from the default state may produce a next-state copy like:

```text
axis=RIGHT
path=ROOT>0/1
breadcrumb=ROOT>RIGHT
host_effect=none
external_effect=none
origin_mutated=0
recovery_executed=0
```

## Denial behavior

Denied transitions preserve the current state as the returned next-state copy.

Denied transitions must keep:

```text
host_effect=none
external_effect=none
origin_mutated=0
recovery_executed=0
```

## Required denial cases

The initial tests must verify:

- unknown direction is denied;
- closed lock denies transition;
- high risk denies transition;
- `back` requires `rollback=available`;
- denied transitions preserve no-effect state.

## Public API

Initial API:

```text
latticra_movement_label
latticra_transition_result_label
latticra_transition_reason_label
latticra_tri_plane_preview
```

## Test command

Run:

```sh
sh scripts/test-tri-plane-transition.sh
```

The main C workflow runs both state-lattice and tri-plane transition tests.

## Current evidence level

This implementation is an L2 tested model for pure preview transitions.

It is not live lattice movement, Nucleus execution, server interaction, self-update, recovery behavior, hardware behavior, boot behavior, or a security boundary.

## Next implementation step

The next implementation candidate after this model is:

```text
Nucleus preview request classification
```

That future work should classify requests and effects, but still avoid live mutation.

## Non-claims

This document and implementation do not claim live movement, origin mutation, recovery execution, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.

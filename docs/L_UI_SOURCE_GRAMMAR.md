# Latticra L-UI Source Grammar Draft

Status: grammar draft and fixture contract
Scope: L-UI source shape, static fixtures, reserved words, validation guards, and non-claims.

## Purpose

This document defines the first draft of L-UI source syntax.

L-UI is the planned terminal/operator UI dialect for Latticra. This draft exists before a parser so the project can refine syntax, fixtures, names, and boundaries before implementation work begins.

## Current boundary

This is not a parser.

This is not a renderer engine.

This is not an interactive UI.

This is not a command language.

This is not live Nucleus execution.

This document defines a source grammar direction and fixture rules only.

## File extension

Planned extension:

```text
.lui
```

## Version header

Every L-UI fixture should begin with:

```text
lui 0.1
```

## Initial top-level forms

Initial forms:

```text
card <Name> {
  ...
}
```

Reserved future forms:

```text
rail <Name> { ... }
layout <Name> { ... }
theme <Name> { ... }
```

Only `card` fixtures are used in the first draft.

## Card grammar direction

Draft shape:

```text
lui 0.1

card NucleusPreview {
  purpose "operator-visible Nucleus preview report"
  effect none
  boundary preview_only

  rail top {
    text "Latticra / Nucleus Preview / effect-bound"
  }

  rail state {
    field origin bind state.origin
    field route bind state.route
    field axis bind state.axis
    field path bind state.path
  }
}
```

## Required card clauses

Every initial card fixture must include:

```text
purpose "..."
effect none
boundary preview_only
```

## Required Nucleus preview rails

The initial `NucleusPreview` fixture must include these rails:

```text
top
state
trace
safety
gates
effects
policy
execution
bottom
```

## Bind syntax

Field binding direction:

```text
field <label> bind <source.path>
```

Allowed source prefixes in the first draft:

```text
state.
preview.
```

Examples:

```text
field origin bind state.origin
field requested_effect bind preview.requested_effect
field policy bind preview.policy
```

## Literal syntax

String literals use double quotes:

```text
text "preview-only no-live-movement no-host-effect no-external-effect"
```

## Effect rule

The only allowed effect declaration in the first draft is:

```text
effect none
```

No other effect value is allowed in initial fixtures.

## Boundary rule

The initial allowed boundary is:

```text
boundary preview_only
```

This means the fixture is intended for static, no-effect report layout only.

## Forbidden fixture behavior

An L-UI fixture must not include behavior that implies:

- command execution;
- state mutation;
- live movement;
- host effects;
- network effects;
- hardware effects;
- boot effects;
- recovery behavior;
- update behavior;
- server interaction;
- hidden side effects.

## First fixture

The first fixture is:

```text
examples/l-ui/nucleus-preview-card.lui
```

It should mirror the existing C static report rails while remaining source-only.

## Guard script

Fixture validation is performed by:

```sh
sh scripts/test-l-ui-grammar-fixtures.sh
```

The guard script performs static checks only. It does not parse or execute L-UI.

## Future parser rule

A future parser may only be added after:

1. this grammar draft is stable;
2. fixtures are reviewed;
3. forbidden behavior tests exist;
4. syntax and error reporting rules are documented;
5. parsing remains no-effect.

## Non-claims

This document and its fixtures do not implement L-UI parsing, rendering, command execution, Nucleus execution, live movement, origin mutation, recovery execution, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.

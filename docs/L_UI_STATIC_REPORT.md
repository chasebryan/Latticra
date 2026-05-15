# Latticra L-UI Static Report Fixture

Status: initial implementation contract
Scope: terminal-facing static report fixture for Nucleus preview and state lattice data.

## Purpose

The L-UI Static Report Fixture is the fourth Latticra implementation unit.

It defines a deterministic terminal-facing layout that composes the state lattice and Nucleus preview classification into operator-visible rails.

This is not a parser, renderer engine, interactive UI, shell, compositor, or live control surface.

## Implementation files

```text
include/latticra/l_ui_static_report.h
src/l_ui_static_report.c
tests/l_ui_static_report_invariants.c
scripts/test-l-ui-static-report.sh
```

## Report kind

Initial report kind:

```text
nucleus-preview
```

## Required rails

The static report must render:

```text
L-UI STATIC REPORT
kind=nucleus-preview
rail.top=Latticra / Nucleus Preview / effect-bound
rail.state=origin:<origin> route:<route> axis:<axis> path:<path>
rail.trace=breadcrumb:<breadcrumb> trace:<trace>
rail.safety=health:<health> risk:<risk> lock:<lock> dark_phase:<dark_phase>
rail.gates=safe_portal:<safe_portal> rollback:<rollback>
rail.effects=host:<host_effect> external:<external_effect> requested:<requested_effect>
rail.policy=request:<request> policy:<policy> reason:<reason>
rail.execution=executed:<0|1> mutation:<0|1> server:<0|1> recovery:<0|1> hardware:<0|1>
rail.bottom=preview-only no-live-movement no-host-effect no-external-effect
```

## Preview-only boundary

The fixture must not:

- parse L-UI source;
- execute commands;
- mutate state;
- perform live movement;
- interact with servers;
- perform update behavior;
- perform recovery behavior;
- touch hardware;
- touch boot state;
- perform host effects;
- perform external effects.

## Public API

Initial API:

```text
latticra_l_ui_report_kind_label
latticra_l_ui_nucleus_preview_card
```

## Test command

Run:

```sh
sh scripts/test-l-ui-static-report.sh
```

The main C workflow runs state-lattice, tri-plane transition, Nucleus preview, and L-UI static report tests.

## Required invariants

The tests must verify:

- report title is stable;
- report kind is stable;
- top rail is present;
- state rail is present;
- trace rail is present;
- safety rail is present;
- gate rail is present;
- effect rail is present;
- policy rail is present;
- execution rail is present;
- bottom boundary rail is present;
- denied requests can be rendered;
- bad arguments are rejected;
- small buffers are rejected.

## Current evidence level

This implementation is an L2 tested model for a terminal-facing static report fixture.

It is not a live L-UI language implementation, renderer, shell, compositor, parser, supervisor executor, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after this model is:

```text
L-UI source grammar draft
```

That future work should define syntax and fixtures before adding a parser.

## Non-claims

This document and implementation do not claim live UI execution, L-UI parsing, live Nucleus execution, live movement, origin mutation, recovery execution, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.

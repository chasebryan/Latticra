# Latticra L-UI Parser Fixture Integration

Status: initial implementation contract
Scope: repository fixture validation through the in-memory L-UI parser.

## Purpose

This document describes the fixture integration test for the L-UI parser.

The parser remains in-memory only. The test harness reads the repository `.lui` fixture and passes the source bytes into the parser.

## Implementation files

```text
tests/l_ui_parser_fixture_integration.c
scripts/test-l-ui-parser-fixture-integration.sh
examples/l-ui/nucleus-preview-card.lui
```

## Fixture under test

```text
examples/l-ui/nucleus-preview-card.lui
```

## Boundary

The parser still does not perform file I/O.

Only the test harness reads the fixture file.

The integration test must not add:

- L-UI rendering;
- interactive UI behavior;
- Nucleus task handling;
- live movement;
- state mutation;
- recovery behavior;
- server interaction;
- self-update behavior;
- host effects;
- network effects;
- hardware effects;
- boot effects.

## Expected parse summary

The repository fixture must parse as:

```text
error=ok
card_name=NucleusPreview
rail_count=9
field_count=23
effect=none
boundary=preview_only
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Test command

Run:

```sh
sh scripts/test-l-ui-parser-fixture-integration.sh
```

The main C workflow runs this check after the in-memory parser invariant test.

## Current evidence level

This implementation is an L2 tested integration between the repository L-UI fixture and the in-memory parser.

It is not a renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after fixture integration is:

```text
L-UI parser result report
```

That future work should render parse results as deterministic text while preserving no-effect behavior.

## Non-claims

This document and implementation do not claim L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.

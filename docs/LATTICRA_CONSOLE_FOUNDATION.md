# Latticra Console Foundation

Status: Stage-0 foundation
Scope: LC identity, Panel installability, configurable metadata, substrate bridge, host-embedding plan, and future OS-base direction.

## Purpose

Latticra Console, shortened to LC, is the planned main operator base for Latticra.

LC should become the primary interaction surface for the Latticra substrate and the surrounding system. It is designed to be configurable and installable through Latticra Panel, embeddable inside a host environment, and eventually capable of growing into an OS-like user environment after explicit evidence gates.

This Stage-0 slice makes LC real without overclaiming authority.

## Phase1 Lessons Retained

The Phase1 reference is useful as a learning source, not as code to copy. Its relevant lessons are:

- a command registry should be the source of truth for help, command discovery, and future capability metadata;
- operator consoles need a guarded host boundary from the first implementation slice;
- OS-track language should stay staged and evidence-bound;
- help, status, and inspection commands should exist before effectful commands.

LC applies those lessons to Latticra's own architecture: Lat, LIR, Nucleus, Runtime Boundary, Latticra Seal, Panel, Nadia, and the System Substrate.

## Installed Identity

```text
console_name=Latticra Console
short_name=LC
component_key=latticra_console
panel_installable=1
configurable=1
panel_console_bridge=panel-aware
```

The Panel component creates:

```text
etc/latticra/lc.toml
share/latticra/lc/README.md
share/latticra/lc/commands/seed-registry.txt
share/latticra/lc/profiles
share/latticra/lc/substrate
share/latticra/lc/host-embedding
share/latticra/components/latticra-console.installed
```

The user-local wrapper is:

```text
latticra-lc
```

The umbrella wrapper routes:

```text
latticra lc status
```

## Stage-0 Commands

```text
help
status
plan
save
dry-run
reset
uninstall
clear
lc status
lc commands
lc substrate
lc host
lc os
pwd
cd
```

These commands are registry-backed in the C foundation. Each command carries:

```text
name
usage
category
effect
capability_label
no_effect
panel_visible
launches_host_process
requires_future_gate
```

The Stage-0 registry is still metadata-only. It reports identity, seed command metadata, substrate bridge, host-embedding plan, and future OS-base posture. It does not launch host commands.

## C Foundation

The C foundation is intentionally deterministic:

```text
include/latticra/latticra_console.h
src/latticra_console.c
tools/latticra_console_report.c
tests/latticra_console_foundation.c
scripts/test-latticra-console-foundation.sh
```

The report surface emits:

```text
LATTICRA CONSOLE REPORT
component_key=latticra_console
console_status=ready-report-only
command_registry_status=seed-registry-ready
command_registry_source=c-static-table
command_registry_no_effect=1
command_registry_host_process_launch_allowed=0
substrate_bridge_status=metadata-bound-ready
panel_installable=1
future_os_base_claim=planned_not_claimed
execution_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
```

## Authority Baseline

LC Stage-0 does not:

- execute shell commands;
- launch external host processes;
- read arbitrary host files;
- write arbitrary host files;
- mutate the host;
- use the network;
- enforce runtime policy;
- boot hardware;
- claim to be a production OS;
- replace Linux, Fedora, macOS, Windows, or any other host OS.

## Next Slices

1. Add a generated help/man surface backed by the registry.
2. Bind LC command metadata to Runtime Boundary and Seal capability labels.
3. Add Panel profile presets for LC hosted, LC embedded, and LC OS-base planning.
4. Add host-embedding contracts before any host integration behavior.
5. Add boot-adjacent planning only after read-only host and VM evidence exists.

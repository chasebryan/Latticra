# UI Configuration Model

The Latticra Panel is now GUI-first. It exposes a guided first-run workbench rather than a numbered terminal menu, because the panel is expected to be the first major user-facing surface for Latticra.

The graphical panel uses one shared `InstallerConfig` model, generates the same plan preview used by the guarded installer engine, and keeps authority boundaries visible before any install path runs.

## First-run design principles

- Strong safe defaults before manual toggles
- Visual guided profiles instead of numbered terminal choices
- Dry-run first, local writes later
- Visible authority status at all times
- Plan and receipt evidence before action
- Embedded panel-aware console instead of a separate TUI
- Adaptive maximized/resizable layout for Fedora workstations and smaller screens

## Profiles

### Guided Workbench

Default profile. Enables Lat tooling, LIR contracts, Seal report-only files, docs, and developer helpers while keeping dry-run enabled and host/network authority denied.

### Seal Report-Only

Minimal report-only Seal-side layout and documentation for users who only want receipts, reports, and evidence posture.

### Fedora Validation VM

For a Fedora or Fedora-like validation VM. Enables the Fedora validation workspace and keeps the run dry by default.

### Custom

Lets the operator manually choose components after the guided profiles are understood.

## Components

- Lat language tooling
- LIR contracts
- Latticra Seal report-only subsystem
- Fedora validation files
- Documentation and examples
- Developer CLI helpers

## Safety and evidence

- Dry-run mode
- Explicit guarded local-prefix write authority
- Explicit network authority, currently disabled
- Component manifest requirement
- Artifact measurement requirement
- Verification-policy metadata requirement
- Operator receipt writing

## Behavior

- Create prefix layout
- Create component markers
- Create CLI shims
- Preserve existing files

## Program delivery

- Build the Latticra Panel binary when Cargo is available
- Build Latticra from source when a supported root build system is available
- Install the Latticra payload tree
- Install the desktop entry
- Install user-local command wrappers

## Embedded Latticra Console

The embedded console is panel-aware and intentionally not an unrestricted shell. It supports quick operator commands such as:

```text
help
status
plan
save
dry-run
profile guided
profile seal
profile fedora
mode dry
mode local
clear
```

The console exists inside the GUI so users can stay in one coherent Latticra control surface while still getting terminal-style feedback and procedure visibility.

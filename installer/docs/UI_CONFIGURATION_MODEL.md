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

- Latticra Console (LC)
- Lat language tooling
- LIR contracts
- Latticra Seal report-only subsystem
- Nadia offline AI foundation
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
lc status
lc commands
lc substrate
lc host
lc os
plan
save
dry-run
nadia status
nadia context
nadia runtime
nadia plan
nadia mode
nadia ledger
nadia safety
nadia tool
nadia prompt-contract
nadia model-registry
nadia inference-readiness
nadia runtime-invocation
nadia model-load
nadia prompt-receipt
nadia prompt-materialization
nadia awareness-dialogue
nadia prompt-evaluation-handoff
nadia tokenization-boundary
nadia tokenizer-specification
nadia tokenizer-manifest
nadia tokenizer-artifact-inventory
nadia tokenizer-artifact-measurement
nadia tokenizer-artifact-verification
nadia tokenizer-artifact-binding
nadia tokenizer-runtime-attachment
nadia prompt-tokenization
nadia prompt-token-sequence
nadia context-window-assembly
nadia prompt-evaluation-input
nadia prompt-evaluation-runtime-handoff
nadia prompt-evaluation-invocation
nadia prompt-evaluation-result
nadia prompt-evaluation-result-review
nadia prompt-evaluation-result-disposition
nadia prompt-evaluation-result-release
nadia prompt-evaluation-result-release-receipt
nadia prompt-evaluation-result-release-receipt-review
nadia prompt-evaluation-result-release-receipt-review-disposition
profile guided
profile seal
profile fedora
mode dry
mode local
clear
```

The console exists inside the GUI so users can stay in one coherent Latticra control surface while still getting terminal-style feedback and procedure visibility.

LC is the standalone and Panel-installable console foundation for substrate interaction, host embedding planning, and future OS-base work. Its current Panel and standalone commands are metadata-only and do not execute external host commands.

Nadia's Stage-0, Stage-1, Stage-2, Stage-3, Stage-4, Stage-5, Stage-6, Stage-7, Stage-8, Stage-9, Stage-10, Stage-11, Stage-12, Stage-13, Stage-14, Stage-15, Stage-16, Stage-17, Stage-18, Stage-19, Stage-20, Stage-21, Stage-22, Stage-23, Stage-24, Stage-25, Stage-26, Stage-27, Stage-28, Stage-29, Stage-30, Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, and Stage-37 console surfaces are metadata-only inside the Panel and do not launch an external host process or model runtime.

Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, and Stage-37 console surfaces are metadata-only result, review, disposition, release, release receipt, release receipt review, and release receipt review disposition surfaces inside the Panel.

Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, and Stage-37 console surfaces are metadata-only and remain covered by the Stage-37 metadata-only console posture.

Nadia's Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, and Stage-37 console surfaces are metadata-only and remain covered by the Stage-37 metadata-only console posture.

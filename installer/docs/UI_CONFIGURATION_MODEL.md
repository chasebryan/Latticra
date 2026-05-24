# UI Configuration Model

The Latticra Panel exposes a small set of high-value choices without pretending that every future install scenario is solved. The graphical panel and terminal panel use the same `InstallerConfig` model, generate the same plan preview, and launch the same guarded installer engine.

## Profiles

### Developer Local

For local Latticra development. Enables Lat tooling, LIR contracts, Seal report-only files, docs, and developer helpers.

### Seal Report-Only

For users who only want the report-only Seal-side layout and documentation. This is the default profile.

### Fedora Validation VM

For a Fedora or Fedora-like validation VM. Enables the Fedora validation workspace.

### Custom

Lets the operator manually choose components.

## Components

- Lat language tooling
- LIR contracts
- Latticra Seal report-only subsystem
- Fedora validation files
- Documentation and examples
- Developer CLI helpers

## Safety and evidence

- Dry-run mode
- Explicit host mutation authority
- Explicit network authority, currently unused and expected to remain disabled
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

## Terminal panel

The terminal panel is available through:

```sh
make -C installer terminal
```

After a local install it is available through:

```sh
latticra-panel --terminal
```

The terminal panel intentionally mirrors the graphical panel's profile, component, safety, evidence, behavior, plan, and execution controls while remaining usable from shells, SSH sessions, and systems without a working desktop session.

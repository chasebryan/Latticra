# UI Configuration Model

The graphical installer exposes a small set of high-value choices without pretending that every future install scenario is solved.

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

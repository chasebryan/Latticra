# Latticra Installer Roadmap

## Current stage

The installer supports a guarded user-local installation under `~/.local/share/latticra` with command wrappers in `~/.local/bin`.

It currently installs:

- Latticra source/payload snapshot
- installer configuration
- component markers
- LIR contract workspace
- Latticra Seal report-only configuration
- receipts and measurements
- `latticra`, `lat`, and `latticra-seal` command wrappers
- optional graphical installer binary when Cargo is available

## Boundaries

The installer does not currently claim:

- production OS installer readiness
- kernel mutation authority
- systemd mutation authority
- SELinux mutation authority
- package-manager integration
- bootloader integration
- network authority

## Next stages

1. Add signed release artifact ingestion.
2. Add stronger manifest validation.
3. Add uninstall receipts.
4. Add Fedora package integration plan.
5. Add VM validation mode.
6. Add system-level installer only after explicit design review.

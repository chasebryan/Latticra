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
- reset receipts for managed local uninstall
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
- firmware/SeaBIOS/GRUB mutation authority
- network authority

## Next stages

1. Add signed release artifact ingestion.
2. Add stronger manifest validation.
3. Add Fedora package integration plan.
4. Use the boot-preview preflight report to classify local QEMU/GRUB readiness before any VM validation mode runs.
5. Use the boot-preview evidence manifest, boot-preview evidence capture template, and QEMU argv template to record future artifact paths, serial logs, checksums, QEMU argv records, and recovery evidence only after the compatibility guard is satisfied.
6. Add failed-install recovery receipts.
7. Add system-level installer only after explicit design review.

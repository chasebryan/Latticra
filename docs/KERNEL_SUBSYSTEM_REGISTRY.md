# Kernel Subsystem Registry

Status: kernel subsystem registry implementation
Scope: compiled metadata registry for first kernel subsystem posture.

## Purpose

This slice adds a compiled kernel subsystem registry on top of the kernel seed.

The registry evaluates the current kernel seed and exposes deterministic entries for:

```text
boot
runtime
scheduler
memory
process
filesystem
network
device
security
```

## Implementation files

```text
include/latticra/kernel_subsystem_registry.h
src/kernel_subsystem_registry.c
tests/kernel_subsystem_registry.c
scripts/test-kernel-subsystem-registry.sh
tools/kernel_subsystem_registry_report.c
scripts/test-kernel-subsystem-registry-report-runner.sh
.github/workflows/kernel-subsystem-registry.yml
docs/KERNEL_SUBSYSTEM_REGISTRY.md
```

## Validation

Run:

```sh
sh scripts/test-kernel-subsystem-registry.sh
sh scripts/test-kernel-subsystem-registry-report-runner.sh
```

Expected output:

```text
kernel_subsystem_registry: ok
kernel_subsystem_registry_report_runner: ok
```

## Boundary

This registry is metadata-only and report-only.

It does not start the scheduler, allocate memory, create processes, mount filesystems, open network channels, operate devices, enforce a production security boundary, boot hardware, or replace an operating system.

The registry records subsystem posture so later implementation slices can grow one subsystem at a time under tests.

# System Bootstrap Implementation

Status: first system-building implementation slice
Scope: compiled no-effect system bootstrap report surface.

## Purpose

This slice adds the first Latticra system bootstrap implementation surface.

The bootstrap surface coordinates existing no-effect Nucleus task classification and runtime-boundary classification into one deterministic operator-visible report.

This is the first implementation step that assembles existing system components into a single startup-facing C API.

## Evidence level

Evidence level: compiled implementation slice.

The evidence is:

```text
public C header
C implementation
focused invariant test
shell guard script
GitHub workflow
implementation record
```

## Implementation files

This slice adds:

```text
include/latticra/system_bootstrap.h
src/system_bootstrap.c
tests/system_bootstrap.c
scripts/test-system-bootstrap.sh
.github/workflows/system-bootstrap.yml
docs/SYSTEM_BOOTSTRAP_IMPLEMENTATION.md
```

## Public API

The public API exposes:

```text
latticra_system_bootstrap_default_request
latticra_system_bootstrap_run
latticra_system_bootstrap_report
```

The bootstrap result carries:

```text
bootstrap id
phase label
system status label
effect boundary label
runtime entry status label
source identity
source span
Nucleus task result
runtime boundary result
aggregate no-effect posture
compiled evidence level
```

## Effect boundary

The system bootstrap is report-only and no-effect.

It does not perform external effects, mutate host state, enter runtime execution, run commands, contact servers, perform recovery actions, touch hardware, or claim operating-system completeness.

The bootstrap coordinates existing classification/report surfaces only.

## Failure behavior

The bootstrap functions return existing `latticra_status_t` values.

Null request/result/report-buffer inputs are rejected with the existing null-argument or buffer-too-small status values.

If a lower no-effect classification surface fails, the bootstrap reports failure through the result status and deterministic status labels.

## Validation

Run:

```sh
sh scripts/test-system-bootstrap.sh
```

The focused test verifies:

```text
default request construction
system bootstrap run remains no-effect
runtime entry remains not entered
Nucleus task remains not executed
deterministic report fields are emitted
null guard behavior is stable
```

## Non-claims

This implementation does not add:

```text
kernel behavior
bootloader behavior
installer behavior
runtime execution
command execution
Lat execution
LIR execution
file I/O
network I/O
state mutation
server interaction
self-update
recovery behavior
hardware behavior
sandboxing
malware prevention
ransomware prevention
production security boundary
operating-system replacement
```

## Next possible implementation lane

A later slice may add a system bootstrap main-test integration audit or a small operator command wrapper, but only after this bootstrap surface compiles and stays no-effect.
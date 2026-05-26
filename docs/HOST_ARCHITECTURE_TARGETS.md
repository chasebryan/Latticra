# Latticra Host Architecture Targets

Status: initial target architecture policy
Scope: x86_64, ARM64, profiles, portability, and non-claims.

## Purpose

Latticra should plan target host architectures from the beginning.

The initial target families are:

```text
x86_64
ARM64 / AArch64
```

## Architecture rule

No architecture-specific behavior may enter the core without a profile boundary.

Architecture-specific work must declare:

- target family;
- execution mode;
- evidence level;
- effect class;
- fallback behavior;
- non-claims.

## Initial target profiles

```text
x86_64-hosted
x86_64-qemu
x86_64-uefi-preview
x86_64-seabios-grub-preview
x86_64-grub2-bios-preview
x86_64-grub2-uefi-preview
aarch64-hosted
aarch64-qemu
aarch64-device-readonly
```

## Profile meanings

| Profile | Meaning | Initial status |
| --- | --- | --- |
| `x86_64-hosted` | Runs as a hosted process on an x86_64 OS. | Planning target. |
| `x86_64-qemu` | Runs or validates in QEMU for x86_64. | Planning target. |
| `x86_64-uefi-preview` | Boot-adjacent preview profile. | Future target. |
| `x86_64-seabios-grub-preview` | Future SeaBIOS plus GRUB compatibility evidence profile. | Contract-only target. |
| `x86_64-grub2-bios-preview` | Future GRUB 2 BIOS boot evidence profile. | Contract-only target. |
| `x86_64-grub2-uefi-preview` | Future GRUB 2 UEFI boot evidence profile. | Contract-only target. |
| `aarch64-hosted` | Runs as a hosted process on an ARM64 OS. | Planning target. |
| `aarch64-qemu` | Runs or validates in QEMU for ARM64. | Planning target. |
| `aarch64-device-readonly` | Real-device read-only evidence profile. | Future target. |

## Implementation order

Recommended order:

```text
1. hosted reference model
2. portable C state lattice fixture
3. validation tests on host
4. QEMU profile planning
5. read-only real-device evidence planning
6. boot-adjacent profile only after evidence
```

## C portability policy

C code intended for architecture-neutral layers should avoid assumptions about:

- pointer width beyond explicit contracts;
- endianness;
- structure packing;
- alignment;
- host OS APIs;
- filesystem layout;
- network availability.

## Architecture-specific code policy

Architecture-specific code must live behind named boundaries.

Possible future structure:

```text
src/arch/x86_64/
src/arch/aarch64/
include/latticra/arch.h
```

Do not create this structure until implementation requires it.

## Hardware evidence policy

Real-device evidence must record:

```text
device identity
architecture
firmware/boot context if relevant
operator checklist
read-only or mutating classification
logs or report
non-claims
```

## Non-claims

This document does not claim Latticra currently runs on x86_64 or ARM64.

It defines the target architecture policy before implementation begins.

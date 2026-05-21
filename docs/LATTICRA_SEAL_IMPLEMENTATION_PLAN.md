# Latticra Seal Implementation Plan

Status: Latticra Seal implementation planning contract
Scope: exact first implementation plan for a no-effect Seal report surface before artifact reads, signing, encryption, key management, post-quantum implementation, Linux integrity integration, Fedora integration, runtime enforcement, network behavior, host mutation, or kernel behavior.

## Purpose

This document defines the first implementation plan for Latticra Seal.

This plan is intentionally narrow. The first implementation must produce deterministic report metadata only. It must not perform cryptographic enforcement.

## Required predecessor

The first Seal implementation must follow:

```text
docs/LATTICRA_SEAL_CONTRACT.md
```

No implementation code should be added unless the Seal contract remains present and guarded.

## First implementation name

```text
Latticra Seal report surface
```

## First implementation goal

Add a no-effect report surface that makes the Latticra Seal posture inspectable.

The first report answers:

```text
Is the Seal contract present?
Is the Seal implementation plan present?
Is Seal still report-only?
Does Seal currently support artifact measurement?
Does Seal currently support signing?
Does Seal currently support capability enforcement?
Does Seal currently support sealed objects?
Did the report perform effects?
Did the report grant authority?
```

## Non-goals

The first implementation must not add:

```text
artifact hashing
file reads
file writes
network access
key generation
key storage
signature generation
signature verification
encryption
decryption
capability enforcement
runtime execution
host mutation
kernel interaction
Fedora approval claims
production-readiness claims
```

## Proposed files

The first implementation should use bounded C surfaces consistent with the repository direction.

```text
include/latticra/seal_report.h
src/seal_report.c
tests/seal_report_invariants.c
scripts/test-latticra-seal-report.sh
docs/LATTICRA_SEAL_REPORT_IMPLEMENTATION.md
```

The implementation may also add status/index alignment files after the report exists.

## Public C API shape

The first public API should be small and deterministic.

```c
typedef struct latticra_seal_report {
    unsigned contract_present;
    unsigned implementation_plan_present;
    unsigned report_only_supported;
    unsigned artifact_measurement_supported;
    unsigned signature_supported;
    unsigned capability_enforcement_supported;
    unsigned sealed_objects_supported;
    unsigned effect_performed;
    unsigned host_read_performed;
    unsigned host_mutation_performed;
    unsigned network_performed;
    unsigned runtime_authority_granted;
    unsigned evidence_level;
    const char *seal_profile;
    const char *status;
    const char *non_claims;
} latticra_seal_report_t;

latticra_seal_report_t latticra_seal_report_default(void);
int latticra_seal_report_render(
    const latticra_seal_report_t *report,
    char *out,
    unsigned out_capacity
);
```

## Required default values

The default report must state:

```text
contract_present=1
implementation_plan_present=1
report_only_supported=1
artifact_measurement_supported=0
signature_supported=0
capability_enforcement_supported=0
sealed_objects_supported=0
effect_performed=0
host_read_performed=0
host_mutation_performed=0
network_performed=0
runtime_authority_granted=0
evidence_level=2
status=report-only
```

Evidence level 2 means contract plus implementation planning and deterministic report design. It does not mean cryptographic security.

## Rendered report requirements

The report renderer must emit deterministic text.

Required labels:

```text
LATTICRA SEAL REPORT
seal_profile=
contract_present=
implementation_plan_present=
report_only_supported=
artifact_measurement_supported=
signature_supported=
capability_enforcement_supported=
sealed_objects_supported=
effect_performed=
host_read_performed=
host_mutation_performed=
network_performed=
runtime_authority_granted=
evidence_level=
status=
non_claims=
```

The renderer must not allocate dynamically.

The renderer must return failure if the output buffer is null or too small.

## Invariant tests

The first invariant tests must verify:

```text
default report is report-only
default report performs no effects
default report performs no host reads
default report performs no host mutation
default report performs no network behavior
default report grants no runtime authority
artifact measurement remains unsupported
signature support remains unsupported
capability enforcement remains unsupported
sealed objects remain unsupported
rendered report contains all required labels
small render buffer fails closed
```

## Guard script requirements

The first guard script must check:

```text
docs/LATTICRA_SEAL_CONTRACT.md exists
docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md exists
docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md exists
Seal contract says this is not cryptographic enforcement
Seal plan forbids artifact hashing in the first implementation
Seal plan forbids signing in the first implementation
Seal plan forbids encryption in the first implementation
Seal plan forbids capability enforcement in the first implementation
```

## Promotion path

After this implementation plan is merged, the next allowed implementation is:

```text
no-effect Seal report implementation
```

After the report implementation is guarded, the next allowed contract is:

```text
read-only artifact measurement contract
```

Artifact measurement must not be added directly to the first report implementation.

## Current status

This file is only an implementation plan. It does not implement Seal.

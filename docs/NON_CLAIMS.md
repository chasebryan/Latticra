# Latticra Non-Claims

Status: initial non-claims boundary
Scope: claims Latticra does not currently make.

## Purpose

This document protects Latticra from premature, confusing, or unsafe claims.

Latticra is an implementation track, but it is not automatically a finished implementation.

## Current non-claims

Latticra does not currently claim to be:

- a finished operating system;
- a daily-driver platform;
- a bootable release image;
- an installer;
- a recovery system;
- a hardened sandbox;
- a security boundary;
- a cryptographic enforcement layer;
- a kernel;
- a hypervisor;
- a virtual machine monitor;
- a container runtime;
- a firmware replacement;
- a production language runtime;
- a production systems platform.

## Hardware non-claims

Latticra does not currently claim:

- hardware boot success;
- disk safety;
- firmware safety;
- device compatibility;
- driver support;
- recovery success;
- rollback success;
- network safety;
- system integrity guarantees.

## Security non-claims

Latticra does not currently claim:

- malware prevention;
- ransomware prevention;
- exploit mitigation;
- secure boot enforcement;
- verified boot enforcement;
- process isolation;
- memory isolation;
- privilege isolation;
- sandbox escape resistance;
- tamper resistance;
- cryptographic correctness.

## Preview boundary

Preview and modeled behavior must not be described as real-world capability unless the evidence ladder supports that claim.

Examples:

```text
Allowed: Latticra has an L1 fixture for a lattice state model.
Blocked: Latticra has a real executable software universe.

Allowed: Latticra has an L2 tested transition model.
Blocked: Latticra can safely move a live system between domains.

Allowed: Latticra has L7 real-device read-only evidence.
Blocked: Latticra is hardware-ready for general use.
```

## Promotion language

Use narrow evidence language.

Prefer:

```text
contracted
documented
fixture-backed
tested
preview-only
read-only validated
virtual-target evidenced
real-device read-only evidenced
gated experimental
```

Avoid:

```text
finished
secure
production-ready
unbreakable
hardened
fully bootable
daily-driver ready
a complete OS
```

## Review rule

Every future claim should answer:

1. What evidence level supports this?
2. What tests or reports support this?
3. What does this still not prove?
4. What can fail?
5. What effects are possible?
6. What effects are impossible?
7. Is the user/operator boundary clear?

## Current project status

Latticra currently claims only a repository identity, documentation seed, and real-system contract direction.

No real-system execution capability is claimed yet.

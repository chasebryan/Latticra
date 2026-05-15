# Latticra Evidence Ladder

Status: initial evidence ladder
Scope: promotion levels for concepts, components, hardware paths, and real-system claims.

## Purpose

The evidence ladder defines how an idea moves from simulation to real implementation.

Latticra must not treat concepts as real-system capabilities until evidence supports them.

## Ladder

### L0: Concept

The idea has a name and a written description.

Allowed outputs:

- notes;
- diagrams;
- design vocabulary;
- non-claims.

Not allowed:

- implementation claims;
- hardware claims;
- security claims.

### L1: Simulation fixture

The idea exists as deterministic simulation data or a static fixture.

Required evidence:

- fixture file;
- expected output;
- no mutation;
- no host effect;
- no external effect.

### L2: Tested model

The idea has tests that preserve required behavior and forbidden behavior.

Required evidence:

- unit tests, docs tests, or validation scripts;
- denied-behavior tests;
- explicit non-claims.

### L3: Read-only command surface

The idea is inspectable through a command or report.

Required evidence:

- command output;
- status labels;
- deterministic behavior;
- no mutation;
- no host or external effect.

### L4: Runtime preview

The idea is wired into a runtime model but remains preview-only.

Required evidence:

- runtime state model;
- invariant tests;
- failure state;
- rollback visibility when relevant;
- operator-facing status.

### L5: Guarded local experiment

The idea performs a narrow local operation under explicit gates.

Required evidence:

- opt-in command;
- confirmation path;
- audit output;
- rollback or reset path;
- failure handling;
- no hidden effects.

### L6: VM or emulator evidence

The idea runs inside a VM, emulator, or controlled local virtual target.

Required evidence:

- launch command;
- logs;
- validation report;
- reproducibility notes;
- no real-device claim.

### L7: Real-device read-only evidence

The idea observes or validates real hardware without changing it.

Required evidence:

- hardware target identity;
- read-only operator checklist;
- captured logs or report;
- redaction review;
- non-mutation proof.

### L8: Real-device gated execution

The idea performs a narrow real-world action on real hardware.

Required evidence:

- explicit operator approval;
- device identity;
- preflight checks;
- backup/recovery plan;
- rollback or failure behavior;
- post-run validation.

### L9: Promoted real-system capability

The capability is part of the Latticra implementation contract.

Required evidence:

- repeated successful evidence;
- tests;
- documentation;
- release note;
- support boundary;
- safety review.

## Promotion rule

A concept may move up one level only when the evidence for the next level exists.

No concept may skip directly from simulation to real-device execution.

## Demotion rule

A promoted concept must be demoted when evidence becomes stale, contradicted, unreproducible, unsafe, or ambiguous.

## Claim language

Use exact level labels when describing capability.

Good:

```text
This is an L2 tested model.
This is an L4 runtime preview.
This has L7 real-device read-only evidence.
```

Bad:

```text
This is production-ready.
This is secure.
This is a finished operating system.
This can recover systems safely.
```

## Current project level

Latticra currently begins at L0/L1 contract and fixture planning.

No real-system execution level is claimed yet.

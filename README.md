# Latticra

Status: early real-system implementation seed
Scope: evidence-bound systems architecture, L-UI, and the Latticra Programming Language.

Latticra is a contract-first systems architecture project focused on explicit state models, deterministic parsers, operator-visible reports, effect boundaries, and eventually the Latticra Programming Language.

It is not a finished operating system, sandbox, installer, recovery system, production runtime, or security boundary.

## Motto

> “The simulacrum is never what hides the truth.” — Jean Baudrillard

## Mission

Latticra is being built toward a defensive, auditable, open systems architecture.

The long-term goal is to make unsafe or malicious behavior harder to hide and easier to inspect through contract-driven source handling, explicit effects, deterministic diagnostics, operator-visible state, and carefully promoted implementation slices.

This is a mission direction, not a current security guarantee.

## Direction checkpoint

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

Latticra uses a constrained C/C++ foundation direction: C owns the secure substrate, C++ is limited to governed policy/validator/effect-gate/audit layers, and Lat / Latticra Language remains the contract/declaration layer.

This does not mean unrestricted C++.

## Core idea

Latticra treats complex computing behavior as structured state spaces with explicit contracts.

The system direction includes:

- constrained C/C++ foundation direction;
- state lattices;
- transition models;
- effect gates;
- operator-visible reports;
- source-aware diagnostics;
- L-UI interface declarations;
- Lat / Latticra Programming Language planning;
- LIR / Latticra Intermediate Representation planning.

## First principles

1. No real-world claim without evidence.
2. No mutation before read-only visibility.
3. No execution before a contract.
4. No hardware effect before an explicit gate.
5. No recovery action before rollback and failure behavior are documented.
6. No concept promotion before tests and review.
7. No confusion between research, prototypes, and implementation.

## Initial documentation

Start with [`docs/FOUNDATION_INDEX.md`](docs/FOUNDATION_INDEX.md) for the full foundation map.

Core seed documents:

- [`docs/REAL_SYSTEM_CONTRACT.md`](docs/REAL_SYSTEM_CONTRACT.md) — project identity, real-system boundary, evidence rules, and non-claims.
- [`docs/EVIDENCE_LADDER.md`](docs/EVIDENCE_LADDER.md) — promotion path from concept to implementation candidate.
- [`docs/PRECURSOR_PROMOTION_RULE.md`](docs/PRECURSOR_PROMOTION_RULE.md) — how precursor research may be promoted into Latticra.
- [`docs/NON_CLAIMS.md`](docs/NON_CLAIMS.md) — claims Latticra does not currently make.
- [`docs/ARCHITECTURE_SEED.md`](docs/ARCHITECTURE_SEED.md) — initial architecture vocabulary and direction.
- [`docs/C_CPP_FOUNDATION_DIRECTION.md`](docs/C_CPP_FOUNDATION_DIRECTION.md) — constrained C/C++ foundation direction.
- [`docs/LANGUAGE_NAMING_POLICY.md`](docs/LANGUAGE_NAMING_POLICY.md) — Lat / Latticra Language naming and extension policy.
- [`docs/LANGUAGE_STRATEGY.md`](docs/LANGUAGE_STRATEGY.md) — C, constrained C++, Lat, L-UI, and LIR roles.
- [`docs/SUPERVISOR_ARCHITECTURE.md`](docs/SUPERVISOR_ARCHITECTURE.md) — Nucleus supervisor and orchestration architecture.
- [`docs/ROADMAP.md`](docs/ROADMAP.md) — design-first implementation sequence.

## Status and strategy

Public status and strategy records are available here:

- [`STATUS.md`](STATUS.md) — root status shortcut.
- [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md) — current progress, completion estimates, and next priorities.
- [`docs/status/ANNOUNCEMENTS.md`](docs/status/ANNOUNCEMENTS.md) — announcement log and milestone notes.
- [`docs/strategy/README.md`](docs/strategy/README.md) — strategy index and update rules.
- [`docs/project_notes/README.md`](docs/project_notes/README.md) — short project notes and upcoming work.

Completion percentages are planning estimates only. They are not release promises, security certifications, or production-readiness metrics.

## Current implementation areas

The repository currently includes guarded documents, tests, and no-effect C implementation slices for:

- constrained C/C++ foundation direction;
- state lattice fixtures;
- tri-plane transition preview modeling;
- Nucleus preview reporting;
- L-UI grammar fixtures;
- L-UI parser result reports;
- L-UI diagnostics;
- line/column and source-span metadata;
- L-UI AST construction;
- detailed AST reports;
- escaped string reporting;
- source-backed AST text extraction;
- length-carrying AST string storage;
- decoded NUL acceptance through escaped `\x00`;
- literal source-buffer NUL rejection policy enforcement;
- semantic validation contract;
- semantic validation implementation plan;
- semantic validation implementation;
- LIR shape contract;
- LIR shape implementation plan;
- LIR shape implementation;
- Lat language grammar contract;
- Lat language grammar implementation plan.

Run the current implementation checks with the scripts listed in [`docs/FOUNDATION_INDEX.md`](docs/FOUNDATION_INDEX.md) or through the repository C workflow.

## Current boundary

Latticra does not yet provide:

- a kernel;
- a bootable image;
- an installer;
- a recovery writer;
- a production language runtime;
- a hardened sandbox;
- unrestricted C++ authority;
- network interaction;
- self-update execution;
- Nucleus task execution;
- L-UI rendering;
- LIR execution;
- Lat parser implementation;
- Lat grammar implementation;
- literal source NUL acceptance;
- live movement;
- operating-system replacement;
- malware prevention guarantees;
- ransomware prevention guarantees.

## Support

Sponsorship helps fund Latticra planning, documentation, tests, and implementation work.

Support Bryforge:

```text
https://buymeacoffee.com/Bryforge
```

GitHub funding metadata is also provided in `.github/FUNDING.yml`.

## Security

See [`SECURITY.md`](SECURITY.md) for vulnerability reporting, supported branch status, safe testing rules, and security non-claims.

## License

Latticra uses Apache-2.0. See [`LICENSE`](LICENSE) and [`docs/LICENSE_POLICY.md`](docs/LICENSE_POLICY.md).

## North star

Latticra is intended to become a professional, evidence-bound software universe architecture built from explicit contracts, deterministic validation, and carefully promoted implementation slices.

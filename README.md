# Latticra

Status: early-stage systems architecture implementation seed.

Latticra is a contract-first systems architecture project for high-assurance infrastructure engineering. The project focuses on explicit state models, deterministic validation, constrained authority, bounded intermediate representations, disabled-by-default effects, and operator-visible reports.

The long-term direction is a disciplined software architecture suitable for mission-critical infrastructure settings. The current repository is foundational engineering work, not a deployed platform or certified product.

## Architecture posture

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

Current roles:

```text
C: substrate, ABI boundaries, bounded records, implementation surfaces
Constrained C++: policy, validation, gate, and audit logic
Lat / Latticra Language: declaration and contract layer
LIR: bounded intermediate representation
L-UI: operator-visible declaration and reporting surface
Nucleus: coordination, classification, and report boundary
Runtime boundary: disabled-by-default line before operational behavior
```

## Current implementation posture

The repository contains guarded documents, tests, and no-effect implementation slices for C/C++ direction, constrained authority reporting, Nucleus classification, runtime-boundary planning, L-UI parsing/rendering, LIR shape metadata, Lat grammar parsing, and state-lattice models.

Current implementation remains report/classification oriented. It is not active runtime behavior.

## Boundary

Latticra does not currently provide a kernel, bootable image, installer, production runtime, unrestricted authority, active task execution, runtime behavior, terminal-control UI behavior, accreditation, certification, or operating-system replacement.

## Documentation

Start with [`docs/FOUNDATION_INDEX.md`](docs/FOUNDATION_INDEX.md).

Important records:

- [`STATUS.md`](STATUS.md)
- [`SECURITY.md`](SECURITY.md)
- [`docs/RUNTIME_BOUNDARY_CONTRACT.md`](docs/RUNTIME_BOUNDARY_CONTRACT.md)
- [`docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md`](docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md)
- [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md)

## Validation

The repository uses shell guards and C invariant tests through the C workflow.

## License

Latticra uses Apache-2.0. See [`LICENSE`](LICENSE) and [`docs/LICENSE_POLICY.md`](docs/LICENSE_POLICY.md).

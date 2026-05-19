# Latticra

Status: early-stage systems architecture implementation seed.

Latticra is a contract-first systems architecture project for high-assurance infrastructure engineering. The project focuses on explicit state models, deterministic validation, constrained authority, bounded intermediate representations, disabled-by-default effects, and operator-visible reports.

The long-term direction is a disciplined software architecture suitable for mission-critical infrastructure settings. The current repository is foundational engineering work, not a deployed platform or certified product.

## Motto

> “The simulacrum is never what hides the truth.” — Jean Baudrillard

## Mission

Latticra is being built as a defensive, auditable, open systems architecture. The project is intended to mature toward infrastructure settings where behavior must be inspectable, explicit, bounded, and governed before it becomes operational.

## Direction checkpoint

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

This does not mean unrestricted C++.

Current roles:

```text
C: substrate, ABI boundaries, bounded records, implementation surfaces
Constrained C++: policy, validation, gate, and audit logic
Lat / Latticra Language: declaration, semantic validation, lowering metadata, and contract layer
LIR: bounded intermediate representation
L-UI: operator-visible declaration and reporting surface
Nucleus: coordination, classification, and report boundary
Runtime boundary: disabled-by-default line before operational behavior
```

## Current implementation posture

The repository contains guarded documents, tests, and no-effect implementation slices for constrained C/C++ foundation direction, constrained C++ authority-layer contract, constrained authority reporting, Nucleus task execution contract, Nucleus task execution implementation plan, Nucleus task execution implementation, Nucleus task report refinement, Runtime boundary contract, Runtime boundary refinement plan, Runtime boundary refinement implementation, Runtime boundary report refinement, Runtime boundary policy matrix refinement, L-UI rendering implementation, literal source-buffer NUL rejection policy enforcement, semantic validation implementation, LIR shape implementation, Lat language grammar implementation, Lat semantic validation foundation, Lat-to-LIR lowering implementation, Lat pipeline implementation, Lat pipeline report refinement, Lat-specific LIR refinement implementation, and state-lattice models.

Lat now has a bounded no-effect path from grammar parsing to semantic validation to LIR metadata lowering. The current lowering implementation consumes parser and semantic metadata, preserves source spans and no-effect flags, emits deterministic lowering reports, and materializes a `lat_module` LIR shape without executing Lat.

The Lat pipeline now composes source parsing, semantic validation, Lat-to-LIR lowering, and deterministic pipeline reporting into one bounded no-effect integration path. It is a metadata/report boundary, not a compiler, interpreter, executor, runtime, or operating-system surface.

The Lat pipeline report refinement now adds deterministic stage-summary metadata for the last completed stage, failed stage, per-stage OK flags, no-effect-chain status, and evidence level. These fields make the pipeline report easier to audit without changing no-effect behavior.

The Lat-specific LIR refinement now gives Lat declarations explicit LIR node kinds and a transition-source edge kind while preserving the existing no-effect metadata path and bounded report posture.

The Nucleus task report refinement now adds deterministic report classification, task-domain labeling, authorization-state labeling, prerequisite status, and no-effect-chain status to Nucleus task reports. These fields make task classification easier to audit without adding task execution.

The Runtime boundary refinement implementation now carries no-effect Lat pipeline evidence and Lat-specific LIR evidence through runtime-boundary records and reports. It adds a validation-only `lat-pipeline-validate` request path while preserving disabled-by-default behavior and future-gated execution requests.

The Runtime boundary report refinement now adds deterministic report classification, boundary-domain labeling, authorization-state labeling, and evidence-level reporting. These fields describe boundary intent; they do not grant runtime authority or execute effects.

The Runtime boundary policy matrix refinement now adds deterministic policy-matrix metadata for matrix cell, effect allowance, mode allowance, authority requirement, and future-gate requirement. These fields make the policy decision shape easier to audit without changing the denied-by-default runtime boundary.

Current implementation remains report/classification oriented. It is not active runtime behavior.

## Boundary

Latticra does not currently provide a kernel, bootable image, installer, production runtime, runtime behavior, command execution, unrestricted C++ authority, effect-performing implemented C++ authority layer, effect-performing task execution, interactive L-UI rendering, terminal-control L-UI rendering, LIR execution, Lat execution, Lat compiler, Lat interpreter, accreditation, certification, or operating-system replacement.

## Initial documentation

Start with [`docs/FOUNDATION_INDEX.md`](docs/FOUNDATION_INDEX.md).

Important records:

- [`STATUS.md`](STATUS.md)
- [`SECURITY.md`](SECURITY.md)
- [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md)
- [`docs/status/ANNOUNCEMENTS.md`](docs/status/ANNOUNCEMENTS.md)
- [`docs/strategy/README.md`](docs/strategy/README.md)
- [`docs/project_notes/README.md`](docs/project_notes/README.md)
- [`docs/C_CPP_FOUNDATION_DIRECTION.md`](docs/C_CPP_FOUNDATION_DIRECTION.md)
- [`docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md`](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md)
- [`docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md`](docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md)
- [`docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md`](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md)
- [`docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md`](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md)
- [`docs/NUCLEUS_TASK_REPORT_REFINEMENT.md`](docs/NUCLEUS_TASK_REPORT_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_CONTRACT.md`](docs/RUNTIME_BOUNDARY_CONTRACT.md)
- [`docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md`](docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md)
- [`docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md`](docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md)
- [`docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md`](docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md)
- [`docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md`](docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md)
- [`docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md`](docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md`](docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md)
- [`docs/L_UI_RENDERING_IMPLEMENTATION.md`](docs/L_UI_RENDERING_IMPLEMENTATION.md)
- [`docs/LAT_LANGUAGE_FOUNDATION_ANALYSIS.md`](docs/LAT_LANGUAGE_FOUNDATION_ANALYSIS.md)
- [`docs/LAT_SEMANTIC_VALIDATION_CONTRACT.md`](docs/LAT_SEMANTIC_VALIDATION_CONTRACT.md)
- [`docs/LAT_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md`](docs/LAT_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md)
- [`docs/LAT_TO_LIR_LOWERING_CONTRACT.md`](docs/LAT_TO_LIR_LOWERING_CONTRACT.md)
- [`docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION_PLAN.md`](docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION_PLAN.md)
- [`docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md`](docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md)
- [`docs/LAT_PIPELINE_CONTRACT.md`](docs/LAT_PIPELINE_CONTRACT.md)
- [`docs/LAT_PIPELINE_IMPLEMENTATION_PLAN.md`](docs/LAT_PIPELINE_IMPLEMENTATION_PLAN.md)
- [`docs/LAT_PIPELINE_IMPLEMENTATION.md`](docs/LAT_PIPELINE_IMPLEMENTATION.md)
- [`docs/LAT_PIPELINE_REPORT_REFINEMENT.md`](docs/LAT_PIPELINE_REPORT_REFINEMENT.md)
- [`docs/LAT_SPECIFIC_LIR_REFINEMENT_CONTRACT.md`](docs/LAT_SPECIFIC_LIR_REFINEMENT_CONTRACT.md)
- [`docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION_PLAN.md`](docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION_PLAN.md)
- [`docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md`](docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md)

## Status and strategy

Status and strategy records are maintained in `STATUS.md`, `docs/status/CURRENT_STATUS.md`, `docs/status/ANNOUNCEMENTS.md`, `docs/strategy/README.md`, and `docs/project_notes/README.md`.

## Validation

The repository uses shell guards and C invariant tests through the C workflow.

Lat semantic validation is covered by:

```sh
sh scripts/test-lat-semantic-validation.sh
```

Lat-to-LIR lowering is covered by:

```sh
sh scripts/test-lat-to-lir-lowering.sh
```

Lat pipeline integration is covered by:

```sh
sh scripts/test-lat-pipeline.sh
```

Lat pipeline report refinement is covered by:

```sh
sh scripts/test-lat-pipeline-report-refinement.sh
sh scripts/test-lat-pipeline.sh
```

Lat-specific LIR refinement is covered by:

```sh
sh scripts/test-lat-specific-lir-refinement.sh
```

Nucleus task report refinement is covered by:

```sh
sh scripts/test-nucleus-task-report-refinement.sh
sh scripts/test-nucleus-task-execution.sh
```

Runtime boundary refinement planning is covered by:

```sh
sh scripts/test-runtime-boundary-refinement-plan.sh
```

Runtime boundary refinement implementation is covered by:

```sh
sh scripts/test-runtime-boundary-refinement-implementation.sh
```

Runtime boundary report refinement is covered by:

```sh
sh scripts/test-runtime-boundary-report-refinement.sh
sh scripts/test-runtime-boundary.sh
```

Runtime boundary policy matrix refinement is covered by:

```sh
sh scripts/test-runtime-boundary-policy-matrix-refinement.sh
sh scripts/test-runtime-boundary.sh
```

## Support

Support Bryforge:

```text
https://buymeacoffee.com/Bryforge
```

## Security

See [`SECURITY.md`](SECURITY.md) for vulnerability reporting, supported branch status, safe testing rules, and security non-claims.

## License

Latticra uses Apache-2.0. See [`LICENSE`](LICENSE) and [`docs/LICENSE_POLICY.md`](docs/LICENSE_POLICY.md).

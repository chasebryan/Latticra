# Latticra

Status: early-stage systems architecture implementation seed.

Latticra is a contract-first systems architecture project for high-assurance infrastructure engineering. The project focuses on explicit state models, deterministic validation, constrained authority, bounded intermediate representations, disabled-by-default effects, and operator-visible reports.

The current repository is foundational engineering work, not a deployed platform or certified product.

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

The repository contains guarded documents, tests, and no-effect implementation slices for constrained C/C++ foundation direction, constrained C++ authority-layer contract, constrained authority reporting, authority implementation review, Nucleus task execution contract, Nucleus task execution implementation plan, Nucleus task execution implementation, Nucleus task report refinement, Nucleus task no-effect report alignment, Nucleus task report-only execution refinement, Nucleus report-only announcement review, Runtime boundary contract, Runtime boundary refinement plan, Runtime boundary refinement implementation, Runtime boundary report refinement, Runtime boundary policy matrix refinement, Runtime boundary domain matrix refinement, Runtime boundary domain matrix report integration, L-UI rendering implementation, L-UI rendering detailed report refinement, literal source-buffer NUL rejection policy enforcement, semantic validation implementation, Lat semantic diagnostics refinement, LIR shape implementation, LIR report refinement, Lat language grammar implementation, Lat semantic validation foundation, Lat-to-LIR lowering implementation, Lat pipeline implementation, Lat pipeline report refinement, Lat pipeline diagnostic integration refinement, Lat pipeline diagnostic main test audit, Lat-specific LIR refinement implementation, status announcement review, public entry-point consistency scan, Fedora RPM gate evidence, disposable Fedora VM local RPM validation evidence, and state-lattice models.

Lat now has a bounded no-effect path from grammar parsing to semantic validation to LIR metadata lowering. The Lat pipeline composes source parsing, semantic validation, Lat-to-LIR lowering, LIR metadata, deterministic pipeline reporting, and companion diagnostic reporting into a no-effect integration boundary.

The Lat pipeline diagnostic integration refinement adds a companion diagnostic surface that combines pipeline error/stage state with Lat semantic diagnostic class, semantic error, diagnostic count, and first-diagnostic indices while preserving no-execution behavior.

The Lat pipeline diagnostic main test audit verifies that the diagnostic integration is covered by both the focused guard and the main Lat pipeline test runner.

The constrained C++ authority implementation review confirms the authority layer remains no-effect, metadata-only, fixed-capacity, and denied-by-default.

The L-UI rendering detailed report refinement adds explicit report classification, detail level, detailed-report availability, detailed section count, deterministic section sequence, no-effect-chain status, and evidence level to the no-effect renderer report surface.

The Nucleus task no-effect report alignment adds explicit report-alignment, no-effect-policy, and representation-gate labels to Nucleus task records and deterministic reports while preserving non-execution behavior.

The Nucleus task report-only execution refinement adds explicit execution-status, effect-status, and runtime-status labels to Nucleus task records and deterministic reports while preserving report-only, non-executing behavior.

The Nucleus report-only announcement review confirms that no separate public announcement is needed because the recent Nucleus report-only and project-notes slices were documentation/status alignment only and did not change capability posture.

The Runtime boundary domain matrix report integration adds deterministic report rendering for domain-matrix cell, domain label, domain flags, effect-allowed state, authority-available state, and evidence level.

Current implementation remains report/classification oriented. It is not active runtime behavior.

## Fedora disposable VM local RPM validation

Latticra now has one evidence-backed host-facing validation path: **disposable Fedora VM local RPM validation**.

The validated path is narrow:

```text
disposable_vm_validation_completed=1
live_host_validation_completed=1
host_install_ready=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
```

The validated package is a local, documentation-only, noarch RPM:

```text
latticra-0.0.0-0.1.local.fc44.noarch.rpm
```

The validated payload remains:

```text
/usr/share/doc/latticra/README.md
```

The successful disposable Fedora VM transcript recorded package build, RPM install, RPM verification, RPM removal, and post-removal absence verification.

This does **not** mean Latticra is production ready, Fedora approved, Fedora distribution ready, daily-driver safe, immutable-Fedora ready, a production installer, a bootable OS replacement, a security product, a sandbox, or a malware/ransomware prevention system.

Evidence records:

- [`docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md`](docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md)

## Boundary

Latticra does not currently provide a kernel, bootable image, production installer, Fedora-approved package, Fedora distribution-ready package, daily-driver installer, immutable Fedora installer, production runtime, runtime behavior, command execution, unrestricted C++ authority, effect-performing implemented C++ authority layer, effect-performing task execution, interactive L-UI rendering, terminal-control L-UI rendering, LIR execution, Lat execution, Lat compiler, Lat interpreter, accreditation, certification, or operating-system replacement.

The only install-readiness statement currently supported by evidence is disposable Fedora VM local RPM validation for the documentation-only local RPM described above.

## Initial documentation

Start with [`docs/FOUNDATION_INDEX.md`](docs/FOUNDATION_INDEX.md).

Important records:

- [`STATUS.md`](STATUS.md)
- [`SECURITY.md`](SECURITY.md)
- [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md)
- [`docs/status/ANNOUNCEMENTS.md`](docs/status/ANNOUNCEMENTS.md)
- [`docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md`](docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md)
- [`docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md`](docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md)
- [`docs/status/AUTHORITY_STATUS_ANNOUNCEMENT_REVIEW.md`](docs/status/AUTHORITY_STATUS_ANNOUNCEMENT_REVIEW.md)
- [`docs/status/COMPLETION_PERCENTAGE_REVIEW.md`](docs/status/COMPLETION_PERCENTAGE_REVIEW.md)
- [`docs/status/L_UI_RENDERING_DETAILED_REPORT_REFINEMENT_STATUS.md`](docs/status/L_UI_RENDERING_DETAILED_REPORT_REFINEMENT_STATUS.md)
- [`docs/status/L_UI_RENDERING_README_STATUS_ALIGNMENT.md`](docs/status/L_UI_RENDERING_README_STATUS_ALIGNMENT.md)
- [`docs/status/NUCLEUS_REPORT_ONLY_ANNOUNCEMENT_REVIEW.md`](docs/status/NUCLEUS_REPORT_ONLY_ANNOUNCEMENT_REVIEW.md)
- [`docs/status/NUCLEUS_REPORT_ONLY_ANNOUNCEMENT_README_ALIGNMENT.md`](docs/status/NUCLEUS_REPORT_ONLY_ANNOUNCEMENT_README_ALIGNMENT.md)
- [`docs/status/NUCLEUS_TASK_NO_EFFECT_REPORT_ALIGNMENT_STATUS.md`](docs/status/NUCLEUS_TASK_NO_EFFECT_REPORT_ALIGNMENT_STATUS.md)
- [`docs/status/NUCLEUS_TASK_README_STATUS_ALIGNMENT.md`](docs/status/NUCLEUS_TASK_README_STATUS_ALIGNMENT.md)
- [`docs/status/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT_STATUS.md`](docs/status/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT_STATUS.md)
- [`docs/status/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_README_STATUS_ALIGNMENT.md`](docs/status/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_README_STATUS_ALIGNMENT.md)
- [`docs/status/PROJECT_NOTES_FOLLOWUP_STATUS_INDEX_CHECK.md`](docs/status/PROJECT_NOTES_FOLLOWUP_STATUS_INDEX_CHECK.md)
- [`docs/status/PROJECT_NOTES_NUCLEUS_ANNOUNCEMENT_README_ALIGNMENT_STATUS_CHECK.md`](docs/status/PROJECT_NOTES_NUCLEUS_ANNOUNCEMENT_README_ALIGNMENT_STATUS_CHECK.md)
- [`docs/status/PROJECT_NOTES_NUCLEUS_REPORT_ONLY_ALIGNMENT_STATUS_INDEX_CHECK.md`](docs/status/PROJECT_NOTES_NUCLEUS_REPORT_ONLY_ALIGNMENT_STATUS_INDEX_CHECK.md)
- [`docs/status/STATUS_ANNOUNCEMENT_REVIEW.md`](docs/status/STATUS_ANNOUNCEMENT_REVIEW.md)
- [`docs/status/STATUS_ANNOUNCEMENT_CONSISTENCY_REVIEW.md`](docs/status/STATUS_ANNOUNCEMENT_CONSISTENCY_REVIEW.md)
- [`docs/status/PUBLIC_ENTRY_POINT_CONSISTENCY_SCAN.md`](docs/status/PUBLIC_ENTRY_POINT_CONSISTENCY_SCAN.md)
- [`docs/status/CPP_AUTHORITY_IMPLEMENTATION_REVIEW_STATUS.md`](docs/status/CPP_AUTHORITY_IMPLEMENTATION_REVIEW_STATUS.md)
- [`docs/status/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_STATUS.md`](docs/status/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_STATUS.md)
- [`docs/status/LAT_PIPELINE_DIAGNOSTIC_MAIN_TEST_AUDIT_STATUS.md`](docs/status/LAT_PIPELINE_DIAGNOSTIC_MAIN_TEST_AUDIT_STATUS.md)
- [`docs/status/RBDM_REPORT_INTEGRATION_STATUS.md`](docs/status/RBDM_REPORT_INTEGRATION_STATUS.md)
- [`docs/strategy/README.md`](docs/strategy/README.md)
- [`docs/strategy/2026-05-19-1845-cdt-strategy-estimate-review.md`](docs/strategy/2026-05-19-1845-cdt-strategy-estimate-review.md)
- [`docs/project_notes/README.md`](docs/project_notes/README.md)
- [`docs/C_CPP_FOUNDATION_DIRECTION.md`](docs/C_CPP_FOUNDATION_DIRECTION.md)
- [`docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md`](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md)
- [`docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md`](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md)
- [`docs/CPP_AUTHORITY_IMPLEMENTATION_REVIEW.md`](docs/CPP_AUTHORITY_IMPLEMENTATION_REVIEW.md)
- [`docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md`](docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md)
- [`docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md`](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md)
- [`docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md`](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md)
- [`docs/NUCLEUS_TASK_REPORT_REFINEMENT.md`](docs/NUCLEUS_TASK_REPORT_REFINEMENT.md)
- [`docs/NUCLEUS_TASK_NO_EFFECT_REPORT_ALIGNMENT.md`](docs/NUCLEUS_TASK_NO_EFFECT_REPORT_ALIGNMENT.md)
- [`docs/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT.md`](docs/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_CONTRACT.md`](docs/RUNTIME_BOUNDARY_CONTRACT.md)
- [`docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md`](docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md)
- [`docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md`](docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md)
- [`docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md`](docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md)
- [`docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md`](docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md)
- [`docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md`](docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md`](docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REFINEMENT.md`](docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_INTEGRATION.md`](docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_INTEGRATION.md)
- [`docs/L_UI_RENDERING_IMPLEMENTATION.md`](docs/L_UI_RENDERING_IMPLEMENTATION.md)
- [`docs/L_UI_RENDERING_DETAILED_REPORT_REFINEMENT.md`](docs/L_UI_RENDERING_DETAILED_REPORT_REFINEMENT.md)
- [`docs/LAT_SEMANTIC_DIAGNOSTICS_REFINEMENT.md`](docs/LAT_SEMANTIC_DIAGNOSTICS_REFINEMENT.md)
- [`docs/LIR_SHAPE_IMPLEMENTATION.md`](docs/LIR_SHAPE_IMPLEMENTATION.md)
- [`docs/LIR_REPORT_REFINEMENT.md`](docs/LIR_REPORT_REFINEMENT.md)
- [`docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md`](docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md)
- [`docs/LAT_PIPELINE_IMPLEMENTATION.md`](docs/LAT_PIPELINE_IMPLEMENTATION.md)
- [`docs/LAT_PIPELINE_REPORT_REFINEMENT.md`](docs/LAT_PIPELINE_REPORT_REFINEMENT.md)
- [`docs/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_REFINEMENT.md`](docs/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_REFINEMENT.md)
- [`docs/LAT_PIPELINE_DIAGNOSTIC_MAIN_TEST_INTEGRATION_AUDIT.md`](docs/LAT_PIPELINE_DIAGNOSTIC_MAIN_TEST_INTEGRATION_AUDIT.md)
- [`docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md`](docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md)

## Status and strategy

Status and strategy records are maintained in `STATUS.md`, `docs/status/CURRENT_STATUS.md`, `docs/status/ANNOUNCEMENTS.md`, `docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md`, `docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md`, `docs/status/AUTHORITY_STATUS_ANNOUNCEMENT_REVIEW.md`, `docs/status/COMPLETION_PERCENTAGE_REVIEW.md`, `docs/status/L_UI_RENDERING_DETAILED_REPORT_REFINEMENT_STATUS.md`, `docs/status/L_UI_RENDERING_README_STATUS_ALIGNMENT.md`, `docs/status/NUCLEUS_REPORT_ONLY_ANNOUNCEMENT_REVIEW.md`, `docs/status/NUCLEUS_REPORT_ONLY_ANNOUNCEMENT_README_ALIGNMENT.md`, `docs/status/NUCLEUS_TASK_NO_EFFECT_REPORT_ALIGNMENT_STATUS.md`, `docs/status/NUCLEUS_TASK_README_STATUS_ALIGNMENT.md`, `docs/status/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT_STATUS.md`, `docs/status/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_README_STATUS_ALIGNMENT.md`, `docs/status/PROJECT_NOTES_FOLLOWUP_STATUS_INDEX_CHECK.md`, `docs/status/PROJECT_NOTES_NUCLEUS_ANNOUNCEMENT_README_ALIGNMENT_STATUS_CHECK.md`, `docs/status/PROJECT_NOTES_NUCLEUS_REPORT_ONLY_ALIGNMENT_STATUS_INDEX_CHECK.md`, `docs/status/STATUS_ANNOUNCEMENT_REVIEW.md`, `docs/status/STATUS_ANNOUNCEMENT_CONSISTENCY_REVIEW.md`, `docs/status/PUBLIC_ENTRY_POINT_CONSISTENCY_SCAN.md`, `docs/status/CPP_AUTHORITY_IMPLEMENTATION_REVIEW_STATUS.md`, `docs/status/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_STATUS.md`, `docs/status/LAT_PIPELINE_DIAGNOSTIC_MAIN_TEST_AUDIT_STATUS.md`, `docs/status/RBDM_REPORT_INTEGRATION_STATUS.md`, `docs/strategy/README.md`, and `docs/project_notes/README.md`.

## Validation

The repository uses shell guards and C invariant tests through the C workflow.

Fedora disposable VM local RPM validation evidence status is covered by:

```sh
sh scripts/test-fedora-disposable-vm-local-rpm-validation-evidence-status.sh
```

Fedora disposable VM RPM README alignment is covered by:

```sh
sh scripts/test-fedora-disposable-vm-rpm-readme-alignment.sh
```

Lat pipeline diagnostic integration refinement is covered by:

```sh
sh scripts/test-lat-pipeline-diagnostic-integration-refinement.sh
sh scripts/test-lat-pipeline.sh
```

Lat pipeline diagnostic main test audit is covered by:

```sh
sh scripts/test-lat-pipeline-diagnostic-main-test-integration-audit.sh
sh scripts/test-lat-pipeline.sh
```

Lat-specific LIR refinement is covered by:

```sh
sh scripts/test-lat-specific-lir-refinement.sh
```

L-UI rendering detailed report refinement is covered by:

```sh
sh scripts/test-l-ui-rendering-detailed-report-refinement.sh
sh scripts/test-l-ui-rendering.sh
```

Nucleus task no-effect report alignment is covered by:

```sh
sh scripts/test-nucleus-task-no-effect-report-alignment.sh
sh scripts/test-nucleus-task-execution.sh
```

Nucleus task report-only execution refinement is covered by:

```sh
sh scripts/test-nucleus-task-report-only-execution-refinement.sh
sh scripts/test-nucleus-task-execution.sh
```

Runtime boundary domain matrix report integration is covered by:

```sh
sh scripts/test-runtime-boundary-domain-matrix-report-integration.sh
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

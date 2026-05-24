# Latticra

Status: early-stage, evidence-bound systems architecture repository.

## Motto

> “The simulacrum is never what hides the truth.” — Jean Baudrillard

## Mission

Latticra is a contract-first systems architecture project for high-assurance infrastructure engineering, Linux/Fedora integration research, Lat language development, bounded intermediate representation work, no-effect runtime-boundary modeling, and AI-era tool-boundary planning.

The repository is foundational engineering work. It is not a deployed platform, certified product, production runtime, or operating-system replacement.

## Direction checkpoint

    C is the metal.
    C++ is the disciplined structure.
    Latticra is the contract.

This does not mean unrestricted C++.

C owns the secure substrate. Constrained C++ owns governed policy, validator, effect-gate, and audit layers. Lat / Latticra Language remains the declaration and contract layer.

## Status and strategy

Start with the current project status, strategy, and project-note entry points:

- [STATUS.md](STATUS.md)
- [docs/status/CURRENT_STATUS.md](docs/status/CURRENT_STATUS.md)
- [docs/status/ANNOUNCEMENTS.md](docs/status/ANNOUNCEMENTS.md)
- [docs/strategy/README.md](docs/strategy/README.md)
- [docs/project_notes/README.md](docs/project_notes/README.md)
- [docs/C_CPP_FOUNDATION_DIRECTION.md](docs/C_CPP_FOUNDATION_DIRECTION.md)
- [docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md)
- [docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md](docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md)
- [docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md)
- [docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md)
- [docs/RUNTIME_BOUNDARY_CONTRACT.md](docs/RUNTIME_BOUNDARY_CONTRACT.md)
- [docs/L_UI_RENDERING_IMPLEMENTATION.md](docs/L_UI_RENDERING_IMPLEMENTATION.md)
- [docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md](docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md)
- [docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md](docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md)
- [docs/LIR_SHAPE_IMPLEMENTATION.md](docs/LIR_SHAPE_IMPLEMENTATION.md)
- [docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md](docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md)
- [docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md](docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md)

Guarded status vocabulary includes: constrained C/C++ foundation direction, constrained C++ authority-layer contract, Nucleus task execution contract, Nucleus task execution implementation plan, Nucleus task execution implementation, Runtime boundary contract, runtime behavior, command execution, L-UI rendering implementation, literal source-buffer NUL rejection policy enforcement, semantic validation implementation, LIR shape implementation, Lat language grammar implementation, unrestricted C++ authority, effect-performing implemented C++ authority layer, interactive L-UI rendering, terminal-control L-UI rendering, LIR execution, Lat execution, Lat compiler, Lat interpreter, and Lat-specific LIR refinement implementation.

Lat-specific LIR refinement validation entry point:

    sh scripts/test-lat-specific-lir-refinement.sh

## What Latticra is

Latticra is being built as a defensive, auditable, open systems architecture. Before any future system effect becomes operational, the request, identity, capability, policy, boundary, and evidence posture should be explicit and inspectable.

Today, Latticra focuses on explicit state and boundary models, deterministic validation and report surfaces, constrained authority vocabulary, disabled-by-default effect posture, bounded C implementation records, constrained C++ policy and audit direction, Lat language parsing and validation, LIR reporting, L-UI report direction, Nucleus task-boundary reports, Runtime Boundary classification before operational behavior, Latticra Seal tool-boundary planning, Fedora/Linux validation evidence, Latticra Panel local installation evidence, and visual theorem engines.

## What Latticra accomplishes today

Current evidence-backed and guarded areas include:

    public_project_identity=1
    foundation_documents_and_contracts=1
    status_and_strategy_records=1
    deterministic_shell_guards=1
    c_invariant_tests=1
    lat_parse_validate_lower_pipeline_present=1
    lir_metadata_reporting_present=1
    runtime_boundary_report_classification_present=1
    nucleus_report_only_task_boundary_present=1
    latticra_seal_report_only_tool_boundary_metadata_present=1
    latticra_seal_runtime_dry_run_report_surface_present=1
    latticra_seal_guarded_allowlist_report_surface_present=1
    production_runtime_present=0

## What Latticra is not

Latticra does not currently provide a kernel, bootable image, production installer, Fedora-approved package, Fedora distribution-ready package, daily-driver installer, immutable Fedora installer, production runtime, runtime behavior, command execution authority, unrestricted C++ authority, effect-performing C++ authority, effect-performing task execution, interactive L-UI rendering, terminal-control L-UI rendering, LIR execution, Lat execution, Lat compiler, Lat interpreter, accreditation, certification, or operating-system replacement.

The project also does not currently claim to be a finished security product, sandbox, malware/ransomware prevention system, AI-agent security product, or production MCP implementation.

## Architecture map

Lat / Latticra Language: contract and declaration language direction. Current posture: parse, validate, diagnose, and lower metadata; no execution.

LIR / Latticra Intermediate Representation: bounded intermediate representation and graph-shape metadata. Current posture: metadata/reporting; no LIR execution.

L-UI: operator-visible declaration and reporting surface. Current posture: parser, validation, and reporting foundations; no terminal-control renderer.

Nucleus: coordination, classification, task records, and task-boundary reports. Current posture: report-only, denied-by-default, no effect-performing execution.

Runtime Boundary: disabled-by-default classification line before operational behavior. Current posture: boundary classification and reports; no runtime authority.

Latticra Seal: trust-boundary, request-boundary, policy-boundary, tool-boundary, and crypto-profile planning. Current posture: report-only runtime dry-run and guarded allowlist candidate-denial paths.

Latticra Panel: GUI-first local workbench for guided first-run configuration, evidence review, dry-run, and guarded local-prefix install. Current posture: user-local, no root, no network authority.

Fedora/Linux substrate: current host-facing validation lane and integration target. Current posture: local-only package and validation records; not distribution-ready.

## Lat, LIR, and L-UI

Lat is the Latticra language direction. The current Lat path is no-effect and metadata-oriented.

    lat_parser_present=1
    lat_semantic_validation_present=1
    lat_diagnostics_present=1
    lat_to_lir_lowering_present=1
    lat_pipeline_reporting_present=1
    lir_metadata_reporting_present=1
    lat_execution=0
    lir_execution=0
    compiler_product=0
    interpreter_product=0

## Latticra Seal

Latticra Seal is the trust-boundary and tool-boundary subsystem inside the Latticra ecosystem.

Latticra Seal now has a report-only runtime gate path with core negative-test evidence for AI-era tool-boundary planning.

Current Seal posture:

    seal_agentic_automation_metadata_present=1
    seal_parameter_schema_metadata_present=1
    seal_request_freshness_metadata_present=1
    seal_signed_request_metadata_present=1
    seal_policy_decision_metadata_present=1
    seal_runtime_gate_metadata_present=1
    seal_runtime_dry_run_metadata_present=1
    seal_runtime_dry_run_report_surface_present=1
    latticra_seal_runtime_dry_run_report_surface_present=1
    seal_guarded_allowlist_metadata_present=1
    seal_guarded_allowlist_report_surface_present=1
    latticra_seal_guarded_allowlist_report_surface_present=1
    operator_visible_runtime_dry_run_report=1
    operator_visible_guarded_allowlist_report=1
    runtime_dry_run_status_index_alignment_present=1
    guarded_allowlist_status_index_alignment_present=1
    blocked_reason=default-deny-dry-run
    known_fixture_tool_candidate_visible=1
    allow_candidate_grants_authority=0
    allow_candidate_executes_tool=0
    allow_candidate_reads_host=0
    allow_candidate_writes_host=0
    allow_candidate_uses_network=0
    would_execute_tool=0
    would_read_host=0
    would_write_host=0
    would_use_network=0
    would_grant_runtime_authority=0
    runtime_authority_granted=0
    effect_performed=0
    host_read_performed=0
    host_write_performed=0
    network_performed=0

The current runtime dry-run lane is a report-only runtime dry-run path with operator-visible denial reporting. The current guarded allowlist lane records known local fixture tools as candidates only. These are report-only runtime dry-run and guarded allowlist candidate-denial paths.

Relevant Seal records include docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md, docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md, docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md, docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md, docs/status/SEAL_RUNTIME_DRY_RUN_STATUS_INDEX_ALIGNMENT.md, docs/status/SEAL_RUNTIME_DRY_RUN_PUBLIC_ENTRYPOINT_ALIGNMENT.md, docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md, docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION_PLAN.md, docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md, docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE.md, docs/status/SEAL_GUARDED_ALLOWLIST_REPORT_SURFACE_STATUS.md, docs/status/SEAL_GUARDED_ALLOWLIST_STATUS_INDEX_ALIGNMENT.md, docs/status/SEAL_GUARDED_ALLOWLIST_PUBLIC_ENTRYPOINT_ALIGNMENT.md, SEAL_CORE_EVIDENCE_STATUS.md, and SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md.

## Latticra Panel installer

Latticra Panel is the graphical local installer and control panel for Latticra, Lat, LIR, and Latticra Seal.

Latticra Panel is also the GUI-first local installer and first-run control workbench for Latticra, Lat, LIR, and Latticra Seal.

Run the installer from source:

    make -C installer gui

Safe dry-run:

    make -C installer dry-run

Guarded user-local install:

    make -C installer local-example
    make -C installer verify-local

Open after install:

    export PATH="$HOME/.local/bin:$PATH"
    latticra-panel

This installer is user-local only. It does not use root, modify the kernel, modify systemd, change SELinux, or use network authority.

Full installer notes are in [installer/README.md](installer/README.md).

## Fedora disposable VM local RPM validation

Latticra now has one evidence-backed host-facing validation path: Fedora disposable VM local RPM validation.

The validated path is narrow:

    disposable_vm_validation_completed=1
    live_host_validation_completed=1
    host_install_ready=1
    production_installer_ready=0
    fedora_distribution_ready=0
    fedora_approval_claimed=0
    daily_driver_install_ready=0
    immutable_fedora_ready=0
    evidence_level=9

The historical validated package record is:

    latticra-0.0.0-0.1.local.fc44.noarch.rpm

The validated documentation payload record includes:

    /usr/share/doc/latticra/README.md

The successful disposable Fedora VM transcript recorded package build, RPM install, RPM verification, RPM removal, and post-removal absence verification.

This does **not** mean Latticra is production ready, Fedora approved, Fedora distribution ready, daily-driver safe, immutable-Fedora ready, a production installer, a bootable OS replacement, a security product, a sandbox, or a malware/ransomware prevention system.

The only install-readiness statement currently supported by evidence is disposable Fedora VM local RPM validation.

Evidence records:

- [docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md](docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md)
- [docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md](docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md)
- [docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md)
- [docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md)

Fedora disposable VM RPM README alignment is covered by:

    sh scripts/test-fedora-disposable-vm-rpm-readme-alignment.sh

## Validation

Core examples:

    sh scripts/test-lat-pipeline.sh
    sh scripts/test-lat-specific-lir-refinement.sh
    sh scripts/test-runtime-boundary.sh
    sh scripts/test-nucleus-task-execution.sh
    sh scripts/test-l-ui-rendering.sh

Fedora disposable VM local RPM validation evidence status is covered by:

    sh scripts/test-fedora-disposable-vm-local-rpm-validation-evidence-status.sh

Fedora disposable VM RPM README alignment is covered by:

    sh scripts/test-fedora-disposable-vm-rpm-readme-alignment.sh

## Visual theorem engines

Latticra includes C-based visual theorem engines that render symbolic substrate models as MP4 video demonstrations.

See docs/VISUAL_THEOREM_ENGINES.md.

## Documentation map

Start with:

- [docs/FOUNDATION_INDEX.md](docs/FOUNDATION_INDEX.md)
- [STATUS.md](STATUS.md)
- [docs/status/CURRENT_STATUS.md](docs/status/CURRENT_STATUS.md)
- [docs/status/ANNOUNCEMENTS.md](docs/status/ANNOUNCEMENTS.md)
- [docs/status/README.md](docs/status/README.md)
- [docs/strategy/README.md](docs/strategy/README.md)
- [docs/project_notes/README.md](docs/project_notes/README.md)
- [SECURITY.md](SECURITY.md)
- [CONTRIBUTING.md](CONTRIBUTING.md)

## Development philosophy

Latticra follows an evidence-first development model.

    No contract without identity.
    No authority without capability.
    No effect without a boundary.
    No promotion without evidence.

## Security

See [SECURITY.md](SECURITY.md).

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md).

## License posture

The current canonical repository license file is [LICENSE](LICENSE), which contains Apache-2.0. The project also maintains an active license transition policy in [docs/LICENSE_POLICY.md](docs/LICENSE_POLICY.md).

## Support

Support Bryforge:

    https://buymeacoffee.com/Bryforge

## About Chase Bryan

Chase Bryan is a computer scientist, systems builder, and low-level software developer focused on operating systems, programming languages, security architecture, Linux-native tooling, and evidence-bound systems design.

## Latticra in 5 minutes

[https://x.com/ckbryan91/status/2057763410771603832?s=20](https://x.com/ckbryan91/status/2057763410771603832?s=20)

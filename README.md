# Latticra

Status: early-stage, evidence-bound systems architecture repository.

## Motto

> “The simulacrum is never what hides the truth.” — Jean Baudrillard

## Mission

Latticra is a contract-first systems architecture project for high-assurance infrastructure engineering, Linux/Fedora integration research, Lat language development, bounded intermediate representation work, no-effect runtime-boundary modeling, and AI-era tool-boundary planning.

The repository is foundational engineering work. It is not a deployed platform, certified product, production runtime, or operating-system replacement.

## Direction checkpoint

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

This does not mean unrestricted C++. It means C owns the secure substrate, constrained C++ owns governed policy, validator, effect-gate, and audit layers, and Lat / Latticra language work remains the declaration and contract layer.

## Status and strategy

Start with the current project status, strategy, and project-note entry points:

- [`STATUS.md`](STATUS.md)
- [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md)
- [`docs/status/ANNOUNCEMENTS.md`](docs/status/ANNOUNCEMENTS.md)
- [`docs/strategy/README.md`](docs/strategy/README.md)
- [`docs/project_notes/README.md`](docs/project_notes/README.md)
- [`docs/C_CPP_FOUNDATION_DIRECTION.md`](docs/C_CPP_FOUNDATION_DIRECTION.md)
- [`docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md`](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md)
- [`docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md`](docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md)
- [`docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md`](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md)
- [`docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md`](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md)
- [`docs/RUNTIME_BOUNDARY_CONTRACT.md`](docs/RUNTIME_BOUNDARY_CONTRACT.md)
- [`docs/L_UI_RENDERING_IMPLEMENTATION.md`](docs/L_UI_RENDERING_IMPLEMENTATION.md)
- [`docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md`](docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md)
- [`docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md`](docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md)
- [`docs/LIR_SHAPE_IMPLEMENTATION.md`](docs/LIR_SHAPE_IMPLEMENTATION.md)
- [`docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md`](docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md)
- [`docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md`](docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md)

Guarded status vocabulary includes: constrained C/C++ foundation direction, constrained C++ authority-layer contract, Nucleus task execution contract, Nucleus task execution implementation plan, Nucleus task execution implementation, Runtime boundary contract, runtime behavior, command execution, L-UI rendering implementation, literal source-buffer NUL rejection policy enforcement, semantic validation implementation, LIR shape implementation, Lat language grammar implementation, unrestricted C++ authority, effect-performing implemented C++ authority layer, interactive L-UI rendering, terminal-control L-UI rendering, LIR execution, Lat execution, Lat compiler, Lat interpreter, and Lat-specific LIR refinement implementation.

Lat-specific LIR refinement validation entry point:

```sh
sh scripts/test-lat-specific-lir-refinement.sh
```

## What Latticra is

Latticra is being built as a defensive, auditable, open systems architecture.

Its core idea is simple: before any future system effect becomes operational, the request, identity, capability, policy, boundary, and evidence posture should be explicit and inspectable.

Today, Latticra focuses on:

- explicit state and boundary models;
- deterministic validation and report surfaces;
- constrained authority vocabulary;
- disabled-by-default effect posture;
- bounded C implementation records;
- constrained C++ policy and audit direction;
- Lat language parsing, validation, diagnostics, and metadata lowering;
- LIR bounded intermediate representation reporting;
- L-UI operator-visible report direction;
- Nucleus coordination and task-boundary reports;
- Runtime Boundary classification before operational behavior;
- Latticra Seal tool-boundary and trust-boundary planning;
- Fedora/Linux validation evidence for narrow host-facing paths.

## What Latticra accomplishes today

The current repository accomplishes an evidence-bound foundation, not a production platform.

Current evidence-backed and guarded areas include:

```text
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
fedora_disposable_vm_local_rpm_validation_present=1
production_runtime_present=0
```

This means Latticra currently provides contracts, metadata surfaces, local deterministic tests, report-only C slices, planning records, and validation evidence. It does not yet provide active runtime enforcement.

## What Latticra is not

Latticra does not currently provide a kernel, bootable image, production installer, Fedora-approved package, Fedora distribution-ready package, daily-driver installer, immutable Fedora installer, production runtime, runtime behavior, command execution authority, unrestricted C++ authority, effect-performing C++ authority, effect-performing task execution, interactive L-UI rendering, terminal-control L-UI rendering, LIR execution, Lat execution, Lat compiler product, Lat interpreter product, accreditation, certification, or operating-system replacement.

The project also does not currently claim to be a finished security product, sandbox, malware/ransomware prevention system, AI-agent security product, or production MCP implementation.

## Architecture map

Latticra is organized as a layered systems architecture. The layers are still early, evidence-bound, and mostly no-effect.

```text
Lat
  Contract/declaration language direction.

LIR
  Bounded intermediate representation and graph-shape metadata.

L-UI
  Operator-visible declaration and reporting surface.

Nucleus
  Coordination, classification, task records, and report boundaries.

Runtime Boundary
  Disabled-by-default classification line before operational behavior.

Latticra Seal
  Trust-boundary, request-boundary, policy-boundary, and tool-boundary planning.

Fedora/Linux substrate
  Current host-facing validation lane and integration target.
```

The current direction is not to replace Linux immediately. The current direction is to mature Latticra as a governed layer of contracts, metadata, reports, validation, and future authority gates that can be validated on Linux/Fedora before deeper independence is claimed.

## Lat, LIR, and report-only language posture

Lat is the Latticra language direction.

The current Lat path is no-effect and metadata-oriented. It gives the project a bounded path from grammar parsing to semantic validation to LIR metadata lowering.

Current posture:

```text
lat_parser_present=1
lat_semantic_validation_present=1
lat_diagnostics_present=1
lat_to_lir_lowering_present=1
lir_metadata_reporting_present=1
lat_execution=0
lir_execution=0
compiler_product=0
interpreter_product=0
```

The goal is not execution first. The goal is inspectable declaration, deterministic validation, and evidence-bearing representation before execution becomes a valid topic.

## Latticra Seal

<p align="center">
  <img src="assets/latticra-seal-mascot-simple-0.png" alt="Latticra Seal mascot" width="360">
</p>

Latticra Seal is a substructure inside the Latticra ecosystem.

Its role is to model trust-boundary, request-boundary, policy-boundary, and tool-boundary behavior for AI-era automation and MCP-style tool invocation planning while remaining evidence-bound and no-effect.

Seal is not a separate production security product. It is the Latticra subsystem that asks:

```text
What is the tool?
Who or what requested it?
Were the parameters declared?
Is the request fresh?
Is the request signed?
Was policy evaluated?
Is runtime authority still denied?
What report proves the boundary decision?
```

Current Seal posture:

```text
seal_agentic_automation_metadata_present=1
seal_parameter_schema_metadata_present=1
seal_request_freshness_metadata_present=1
seal_signed_request_metadata_present=1
seal_policy_decision_metadata_present=1
seal_runtime_gate_metadata_present=1
seal_runtime_dry_run_metadata_present=1
seal_runtime_dry_run_report_surface_present=1
operator_visible_runtime_dry_run_report=1
runtime_dry_run_status_index_alignment_present=1
runtime_gate_report_only=1
policy_decision_state=report-only
runtime_gate_state=report-only
blocked_reason=default-deny-dry-run
default_action_deny=1
would_allow=0
would_deny=1
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
```

The completed core blocked-request case set currently covers:

```text
unknown_tool_case_validated=1
unsigned_request_case_validated=1
stale_request_case_validated=1
replayed_request_case_validated=1
core_blocked_case_set_complete=1
```

The current runtime dry-run lane records what would remain denied without executing tools, touching host state, using the network, or granting authority.

A careful public claim is:

```text
Latticra Seal now has a report-only runtime dry-run path with operator-visible denial reporting for AI-era tool-boundary planning.
```

That is intentionally limited. It does not mean Latticra Seal currently implements runtime enforcement, policy enforcement, cryptographic verification, MCP protocol behavior, MCP server behavior, MCP client behavior, AI-agent execution control, tool execution, host behavior, network behavior, object sealing, key storage, revocation lookup, or production agent security.

Relevant Seal records:

- [`docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md`](docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md)
- [`docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md`](docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md)
- [`docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md`](docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md)
- [`docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md`](docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md)
- [`docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md`](docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md)
- [`docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md`](docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_RUNTIME_ENFORCEMENT_GATE_CONTRACT.md`](docs/LATTICRA_SEAL_RUNTIME_ENFORCEMENT_GATE_CONTRACT.md)
- [`docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md`](docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md)
- [`docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION_PLAN.md`](docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION_PLAN.md)
- [`docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md`](docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE.md)
- [`docs/status/SEAL_CORE_BLOCKED_CASES_STATUS.md`](docs/status/SEAL_CORE_BLOCKED_CASES_STATUS.md)
- [`docs/status/SEAL_CORE_EVIDENCE_STATUS.md`](docs/status/SEAL_CORE_EVIDENCE_STATUS.md)
- [`docs/status/SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md`](docs/status/SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md)
- [`docs/status/SEAL_CORE_EVIDENCE_PUBLIC_ENTRYPOINT_ALIGNMENT.md`](docs/status/SEAL_CORE_EVIDENCE_PUBLIC_ENTRYPOINT_ALIGNMENT.md)
- [`docs/status/SEAL_POLICY_DECISION_STATUS.md`](docs/status/SEAL_POLICY_DECISION_STATUS.md)
- [`docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md`](docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md)
- [`docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md`](docs/status/SEAL_RUNTIME_DRY_RUN_REPORT_SURFACE_STATUS.md)
- [`docs/status/SEAL_RUNTIME_DRY_RUN_STATUS_INDEX_ALIGNMENT.md`](docs/status/SEAL_RUNTIME_DRY_RUN_STATUS_INDEX_ALIGNMENT.md)
- [`docs/status/SEAL_RUNTIME_DRY_RUN_PUBLIC_ENTRYPOINT_ALIGNMENT.md`](docs/status/SEAL_RUNTIME_DRY_RUN_PUBLIC_ENTRYPOINT_ALIGNMENT.md)

## Fedora disposable VM local RPM validation

Latticra now has one evidence-backed host-facing validation path: **Fedora disposable VM local RPM validation**.

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

The only install-readiness statement currently supported by evidence is disposable Fedora VM local RPM validation for the documentation-only local RPM described above.

Evidence records:

- [`docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md`](docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md)
- [`docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md`](docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md)

## Validation

The repository uses shell guards and C invariant tests through the C workflow.

Core examples:

```sh
sh scripts/test-lat-pipeline.sh
sh scripts/test-runtime-boundary.sh
sh scripts/test-nucleus-task-execution.sh
sh scripts/test-l-ui-rendering.sh
```

Seal case validation:

```sh
sh scripts/test-latticra-seal-unknown-tool-case.sh
sh scripts/test-latticra-seal-unsigned-request-case.sh
sh scripts/test-latticra-seal-stale-request-case.sh
sh scripts/test-latticra-seal-replayed-request-case.sh
```

Seal runtime dry-run validation:

```sh
sh scripts/test-latticra-seal-runtime-dry-run.sh
sh scripts/test-latticra-seal-runtime-dry-run-report-surface.sh
sh scripts/test-latticra-seal-runtime-dry-run-report-surface-status.sh
sh scripts/test-latticra-seal-runtime-dry-run-status-index-alignment.sh
```

Fedora disposable VM local RPM validation evidence status is covered by:

```sh
sh scripts/test-fedora-disposable-vm-local-rpm-validation-evidence-status.sh
```

Fedora disposable VM RPM README alignment is covered by:

```sh
sh scripts/test-fedora-disposable-vm-rpm-readme-alignment.sh
```

## Documentation map

Start with:

- [`docs/FOUNDATION_INDEX.md`](docs/FOUNDATION_INDEX.md)
- [`STATUS.md`](STATUS.md)
- [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md)
- [`docs/status/ANNOUNCEMENTS.md`](docs/status/ANNOUNCEMENTS.md)
- [`docs/status/README.md`](docs/status/README.md)
- [`docs/strategy/README.md`](docs/strategy/README.md)
- [`docs/project_notes/README.md`](docs/project_notes/README.md)
- [`SECURITY.md`](SECURITY.md)

Important architecture records:

- [`docs/C_CPP_FOUNDATION_DIRECTION.md`](docs/C_CPP_FOUNDATION_DIRECTION.md)
- [`docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md`](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md)
- [`docs/LAT_PIPELINE_IMPLEMENTATION.md`](docs/LAT_PIPELINE_IMPLEMENTATION.md)
- [`docs/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_REFINEMENT.md`](docs/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_REFINEMENT.md)
- [`docs/LIR_REPORT_REFINEMENT.md`](docs/LIR_REPORT_REFINEMENT.md)
- [`docs/L_UI_RENDERING_IMPLEMENTATION.md`](docs/L_UI_RENDERING_IMPLEMENTATION.md)
- [`docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md`](docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md)
- [`docs/RUNTIME_BOUNDARY_CONTRACT.md`](docs/RUNTIME_BOUNDARY_CONTRACT.md)

## Development philosophy

Latticra follows an evidence-first development model.

The repository should only claim what its contracts, tests, reports, and validation records support.

```text
No contract without identity.
No authority without capability.
No effect without a boundary.
No promotion without evidence.
```

## Support

Support Bryforge:

```text
https://buymeacoffee.com/Bryforge
```

## Security

See [`SECURITY.md`](SECURITY.md) for vulnerability reporting, supported branch status, safe testing rules, and security non-claims.

<details>
<summary><strong>About Me</strong></summary>

# Chase Bryan

I am a computer scientist, systems builder, and low-level software developer focused on operating systems, programming languages, security architecture, and Linux-native tooling.

My work centers around **Latticra**, a systems research and development project exploring new ways to structure secure computing environments, kernel-adjacent design, Fedora/Linux integration, policy boundaries, and developer-first infrastructure.

I am especially interested in:

- Operating systems and kernel-level architecture
- C, C++, Rust, and systems programming
- Programming language design
- Linux, Fedora, and open-source ecosystems
- Secure computation and cryptographic foundations
- Tool boundary planning, MCP, and AI-era software architecture

My goal is to build technology that is practical, secure, understandable, and grounded in real engineering evidence — not hype.

I use GitHub as the public workspace for my projects, experiments, documentation, and long-term development efforts.

</details>

## License

Latticra uses Apache-2.0. See [`LICENSE`](LICENSE) and [`docs/LICENSE_POLICY.md`](docs/LICENSE_POLICY.md).

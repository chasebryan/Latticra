# Latticra

**Status:** early-stage, evidence-bound systems architecture repository  
**README review snapshot:** 2026-05-24 CDT  
**Default branch:** `main`

> “The simulacrum is never what hides the truth.” — Jean Baudrillard

**Featured handbook:** [The Latticra System Substrate PDF](docs/latticra-system-substrate/the-latticra-system-substrate.pdf)  
**Editable handbook:** [The Latticra System Substrate DOCX](docs/latticra-system-substrate/the-latticra-system-substrate.docx)  
**System Substrate docs:** [docs/latticra-system-substrate/](docs/latticra-system-substrate/)  
**Seal subsystem docs:** [docs/latticra-seal/](docs/latticra-seal/)

Latticra is an evidence-bound systems substrate for Linux-era and AI-era computing. Its purpose is to make system actions, automation, tool execution, and agentic workflows safer through deny-by-default authority, contract-first validation, cryptographic-verification planning, no-effect reporting, runtime gating, and auditable evidence.

This repository is foundational engineering work. It is not a deployed platform, certified product, production runtime, hardened sandbox, Fedora-approved package, daily-driver installer, bootable operating system, or operating-system replacement.

---

## Contents

- [What Latticra is](#what-latticra-is)
- [Current status at a glance](#current-status-at-a-glance)
- [Design doctrine](#design-doctrine)
- [Architecture map](#architecture-map)
- [What exists today](#what-exists-today)
- [What Latticra does not claim](#what-latticra-does-not-claim)
- [Quick start](#quick-start)
- [Latticra Panel](#latticra-panel)
- [Lat, LIR, and L-UI](#lat-lir-and-l-ui)
- [Nucleus and Runtime Boundary](#nucleus-and-runtime-boundary)
- [The Latticra System Substrate](#the-latticra-system-substrate)
- [Latticra Seal](#latticra-seal)
- [Fedora and local RPM work](#fedora-and-local-rpm-work)
- [Visual theorem engines](#visual-theorem-engines)
- [Repository map](#repository-map)
- [Documentation entry points](#documentation-entry-points)
- [Development philosophy](#development-philosophy)
- [Security](#security)
- [Contributing](#contributing)
- [License posture](#license-posture)
- [Support](#support)

---

## What Latticra is

Latticra is a contract-first systems architecture project for high-assurance infrastructure engineering, Linux/Fedora integration research, Lat language development, bounded intermediate representation work, no-effect runtime-boundary modeling, and AI-era tool-boundary planning.

The core idea is simple:

> Before any future system effect becomes operational, the request, identity, capability, policy, boundary, and evidence posture should be explicit, inspectable, denied by default, and supported by tests or validation records.

Latticra currently focuses on:

- explicit state and boundary models;
- deterministic validation and report surfaces;
- constrained authority vocabulary;
- disabled-by-default effect posture;
- bounded C implementation records;
- constrained C++ policy, validator, effect-gate, and audit direction;
- Rust-based local GUI workbench work through Latticra Panel;
- Lat language parsing, validation, diagnostics, and metadata lowering;
- LIR bounded intermediate-representation reporting;
- L-UI operator-visible declaration and reporting surfaces;
- Nucleus coordination and task-boundary reports;
- Runtime Boundary classification before operational behavior;
- Latticra Seal tool-boundary and trust-boundary planning;
- Fedora/Linux validation evidence for narrow host-facing paths;
- visual theorem engines for symbolic Latticra substrate demonstrations.

---

## Current status at a glance

The authoritative status files are [`STATUS.md`](STATUS.md) and [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md). This README summarizes them for orientation only.

| Area | Current posture |
| --- | --- |
| Overall system | Early-stage, evidence-bound foundation |
| Current public estimate | Roughly 39% overall system planning estimate |
| Foundation documents and contracts | Mature relative to implementation; around 90% planning estimate |
| Public documentation posture | Strong but still evolving; around 84% planning estimate |
| Lat / Latticra Language | No-effect parse / validate / lower path exists; no execution |
| LIR | Bounded metadata/reporting exists; no LIR execution |
| L-UI | Parser, validation, and report/rendering foundations exist; no interactive terminal-control renderer |
| Nucleus | Report-only task-boundary and classification work exists; no effect-performing execution |
| Runtime Boundary | Denied-by-default classification and reporting exists; no runtime authority |
| Latticra Seal | Report-only tool-boundary, runtime dry-run, guarded allowlist, report-envelope metadata, signature-request metadata, and crypto-profile planning surfaces exist; no production enforcement |
| Fedora integration | Local-only package and validation lanes exist; not Fedora-approved or distribution-ready |
| Latticra Panel | GUI-first local installer/control workbench exists; user-local and guarded |
| Security hardening | Early; no production security boundary claimed |
| Product readiness | Early; no production platform claimed |

Planning estimates are not release promises, product-readiness metrics, or security guarantees.

---

## Design doctrine

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

This does not mean unrestricted C++. It means:

- **C** owns narrow substrate, fixed-capacity structures, no-effect reports, deterministic invariants, and low-level implementation records.
- **Constrained C++** owns future governed policy, validator, effect-gate, and audit layers under strict authority rules.
- **Lat / Latticra Language** owns declaration, contract, and inspectable system intent.
- **Rust** is currently used where it is practical for the Latticra Panel GUI workbench.
- **Shell guards** preserve deterministic status, evidence, and regression checks.

Latticra is not rejecting memory safety. It is rejecting uncontrolled authority. The project direction is to use each language only where its role is explicit, reviewable, and evidence-bound.

---

## Architecture map

```text
Lat / Latticra Language
  Contract and declaration language direction.
  Current posture: parse, validate, diagnose, lower metadata; no execution.

LIR / Latticra Intermediate Representation
  Bounded intermediate representation and graph-shape metadata.
  Current posture: metadata/reporting; no LIR execution.

L-UI
  Operator-visible declaration and reporting surface.
  Current posture: parser, validation, reporting/rendering foundations; no terminal-control renderer.

Nucleus
  Coordination, classification, task records, and task-boundary reports.
  Current posture: report-only, denied-by-default, no effect-performing execution.

Runtime Boundary
  Disabled-by-default classification line before operational behavior.
  Current posture: boundary classification and reports; no runtime authority.

Latticra Seal
  Trust-boundary, request-boundary, policy-boundary, tool-boundary, and crypto-profile planning.
  Current posture: report-only runtime dry-run, guarded allowlist candidate-denial, sealed report-envelope metadata, signature-request metadata, signing authorization metadata, and signer handoff metadata paths.

Latticra Panel
  GUI-first local workbench for guided first-run configuration, evidence review, dry-run, and guarded local-prefix install.
  Current posture: user-local, no root, no network authority.

Fedora/Linux substrate
  Current host-facing validation lane and integration target.
  Current posture: local-only package/validation records; not distribution-ready.
```

The current direction is not to replace Linux immediately. The current direction is to mature Latticra as a governed layer of contracts, metadata, reports, validation, and future authority gates that can be validated on Linux/Fedora before deeper independence is claimed.

---

## What exists today

Current evidence-backed and guarded areas include:

```text
public_project_identity=1
foundation_documents_and_contracts=1
status_and_strategy_records=1
deterministic_shell_guards=1
c_invariant_tests=1
no_effect_cli_status_surface=1
lat_parse_validate_lower_pipeline_present=1
lir_metadata_reporting_present=1
l_ui_parser_validation_reporting_present=1
runtime_boundary_report_classification_present=1
nucleus_report_only_task_boundary_present=1
latticra_seal_report_only_tool_boundary_metadata_present=1
latticra_seal_runtime_dry_run_report_surface_present=1
latticra_seal_guarded_allowlist_report_surface_present=1
latticra_seal_report_envelope_metadata_present=1
latticra_seal_signature_request_contract_present=1
latticra_seal_signature_request_metadata_present=1
latticra_seal_signature_request_status_present=1
latticra_seal_signing_authorization_contract_present=1
latticra_seal_signing_authorization_metadata_present=1
latticra_seal_signing_authorization_status_present=1
latticra_seal_signer_handoff_contract_present=1
latticra_seal_signer_handoff_metadata_present=1
latticra_seal_signer_handoff_status_present=1
latticra_panel_gui_workbench_present=1
fedora_local_rpm_draft_present=1
visual_theorem_engines_present=1
production_runtime_present=0
```

This means Latticra currently provides contracts, metadata surfaces, local deterministic tests, report-only implementation slices, planning records, validation evidence, and guarded local tooling. It does not yet provide active production runtime enforcement.

---

## What Latticra does not claim

Latticra does **not** currently provide:

- a kernel;
- a bootable image;
- a production installer;
- a Fedora-approved package;
- a Fedora distribution-ready package;
- a daily-driver installer;
- an immutable Fedora installer;
- a production runtime;
- effect-performing runtime behavior;
- unrestricted command execution authority;
- unrestricted C++ authority;
- effect-performing C++ authority;
- effect-performing Nucleus task execution;
- runtime enforcement;
- policy enforcement;
- cryptographic key authority;
- production cryptography;
- MCP server behavior;
- MCP client behavior;
- AI-agent execution control;
- malware containment;
- ransomware prevention;
- hardened sandboxing;
- kernel isolation;
- secure boot;
- secure update delivery;
- hardware recovery safety;
- accreditation;
- certification;
- operating-system completeness;
- operating-system replacement.

The project also does not claim external endorsement, agency endorsement, Fedora approval, production security certification, or production readiness.

---

## Quick start

Clone the repository:

```sh
git clone https://github.com/Bryforge/Latticra.git
cd Latticra
```

Read the public status first:

```sh
sed -n '1,220p' STATUS.md
sed -n '1,260p' docs/status/CURRENT_STATUS.md
```

Build and run the current no-effect CLI status surface:

```sh
mkdir -p build
cc -std=c99 -Wall -Wextra -pedantic src/latticra_cli.c -o build/latticra
./build/latticra --status
```

Expected posture from the CLI is no-effect:

```text
mode=no-effect
runtime_behavior=disabled
host_mutation=0
network=0
effect_authority=denied
```

Run selected validation guards:

```sh
sh scripts/test-lat-pipeline.sh
sh scripts/test-lat-specific-lir-refinement.sh
sh scripts/test-runtime-boundary.sh
sh scripts/test-nucleus-task-execution.sh
sh scripts/test-l-ui-rendering.sh
```

Run selected Latticra Seal blocked-case and boundary guards:

```sh
sh scripts/test-latticra-seal-unknown-tool-case.sh
sh scripts/test-latticra-seal-unsigned-request-case.sh
sh scripts/test-latticra-seal-stale-request-case.sh
sh scripts/test-latticra-seal-replayed-request-case.sh
sh scripts/test-latticra-seal-runtime-dry-run.sh
sh scripts/test-latticra-seal-guarded-allowlist.sh
```

Run selected Fedora/local packaging status guards when working on Fedora validation lanes:

```sh
sh scripts/test-fedora-build-lane.sh
sh scripts/test-fedora-developer-workflow.sh
sh scripts/test-fedora-local-rpm-spec-skeleton.sh
```

---

## Latticra Panel

Latticra Panel is the GUI-first local installer and first-run control workbench for Latticra, Lat, LIR, and Latticra Seal.

The panel is designed as the main first impression for Latticra. It opens as a maximized, resizable GUI workbench with guided defaults, visible authority boundaries, component configuration, delivery controls, plan/evidence review, and an embedded Latticra Console for panel-aware commands.

### Fedora prerequisites

```sh
sudo dnf install -y rust cargo make gcc pkgconf-pkg-config \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel mesa-libGL-devel wayland-devel desktop-file-utils gtk3
```

Make sure the user-local command path is available:

```sh
export PATH="$HOME/.local/bin:$PATH"
```

### Run from source

```sh
make -C installer gui
```

Equivalent direct command:

```sh
cd installer/latticra-installer
LATTICRA_INSTALLER_ROOT="$PWD/.." cargo run
```

### Panel commands

```sh
make -C installer help
make -C installer gui
make -C installer build-gui
make -C installer dry-run
make -C installer local-example
make -C installer verify-local
make -C installer uninstall-local
make -C installer refresh-desktop
make -C installer fmt
make -C installer tree
make -C installer clean
```

### First-run flow

1. Open **Guided Workbench**.
2. Keep dry-run mode enabled.
3. Generate and inspect the plan.
4. Run Dry-Install to validate and write a receipt.
5. Review the embedded console, plan, and engine log.
6. Enable guarded local-prefix writes only after the dry-run evidence looks correct.

### Embedded Latticra Console

The embedded console is not an unrestricted shell. It is a panel-aware operator console for common actions:

```text
help
status
plan
save
dry-run
profile guided
profile seal
profile fedora
mode dry
mode local
clear
```

### Panel profiles

```text
Guided Workbench
  Safe first-run profile with Lat, LIR, Seal, docs, and helper commands enabled under dry-run authority.

Seal Report-Only
  Minimal report-only Seal layout for receipts, reports, and documentation.

Fedora Validation VM
  Fedora/Linux validation workspace for VM testing and host-facing evidence capture.

Custom
  Manual operator profile for users who understand the selected components and authority posture.
```

### Seal crypto profile planning in the Panel

The Panel exposes Seal crypto-profile configuration as planning and reporting metadata only:

```text
Report-only / no key authority
BLAKE2b + Ed25519
XChaCha20-Poly1305
Hybrid Seal profile
Custom Seal profile
```

These profile names do not grant key authority, perform signing, encrypt payloads, execute tools, read host state, write host state, or use the network by themselves.

### Dry-run

```sh
make -C installer dry-run
```

This uses:

```text
installer/configs/default.installer.toml
```

The default configuration keeps dry-run enabled, host mutation disabled, and network authority disabled.

### Guarded user-local install

```sh
make -C installer local-example
make -C installer verify-local
```

This uses:

```text
installer/configs/local-prefix-example.installer.toml
```

It is intentionally user-local. It does not use root authority, kernel mutation, systemd mutation, SELinux mutation, or network authority.

### Open after install

```sh
latticra-panel
```

Or open **Latticra Panel** from the desktop app grid.

### Installed paths

```text
~/.local/bin/latticra
~/.local/bin/lat
~/.local/bin/latticra-seal
~/.local/bin/latticra-panel
~/.local/share/applications/latticra-panel.desktop
~/.local/share/icons/hicolor/256x256/apps/latticra-panel.png
~/.local/share/latticra
```

### Safety baseline

```text
no root
no kernel mutation
no systemd mutation
no SELinux mutation
no network authority
user-local prefix only
dry-run first
receipt/evidence before action
```

Full installer notes are in [`installer/README.md`](installer/README.md).

---

## Lat, LIR, and L-UI

Lat is the Latticra language direction.

The current Lat path is no-effect and metadata-oriented. It gives the project a bounded path from grammar parsing to semantic validation to LIR metadata lowering.

Current posture:

```text
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
```

LIR is the bounded intermediate representation layer. It currently provides graph-shape metadata, report classification, edge summaries, no-effect-chain status, and evidence fields. It does not execute.

L-UI is the operator-visible declaration and report surface. It currently has parser, semantic validation, and reporting/rendering foundations. It is not currently an interactive terminal-control renderer.

Relevant documents:

- [`docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md`](docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md)
- [`docs/LAT_SEMANTIC_VALIDATION_CONTRACT.md`](docs/LAT_SEMANTIC_VALIDATION_CONTRACT.md)
- [`docs/LAT_SEMANTIC_DIAGNOSTICS_REFINEMENT.md`](docs/LAT_SEMANTIC_DIAGNOSTICS_REFINEMENT.md)
- [`docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md`](docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md)
- [`docs/LAT_PIPELINE_IMPLEMENTATION.md`](docs/LAT_PIPELINE_IMPLEMENTATION.md)
- [`docs/LAT_PIPELINE_REPORT_REFINEMENT.md`](docs/LAT_PIPELINE_REPORT_REFINEMENT.md)
- [`docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md`](docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md)
- [`docs/LIR_SHAPE_IMPLEMENTATION.md`](docs/LIR_SHAPE_IMPLEMENTATION.md)
- [`docs/LIR_REPORT_REFINEMENT.md`](docs/LIR_REPORT_REFINEMENT.md)
- [`docs/L_UI_RENDERING_IMPLEMENTATION.md`](docs/L_UI_RENDERING_IMPLEMENTATION.md)

---

## The Latticra System Substrate

The main project handbook is now **The Latticra System Substrate: An Effect at Modern Security**.

Downloads:

- [PDF edition](docs/latticra-system-substrate/the-latticra-system-substrate.pdf)
- [Editable DOCX edition](docs/latticra-system-substrate/the-latticra-system-substrate.docx)
- [Documentation landing page](docs/latticra-system-substrate/)

This book supersedes the former standalone Latticra Seal handbook as the primary reader-facing project guide. It presents Latticra as an early, evidence-bound system substrate for making security-relevant effects visible, typed, reviewable, reproducible, and eventually governable.

It covers the larger Latticra project: Seal, Panel, guarded local-prefix installation, receipts, reports, command contracts, Lat/LIR contract surfaces, validation lanes, runtime-boundary metadata, and research artifacts.

It should not be read as a claim that Latticra is a production security product, hardened sandbox, malware prevention system, ransomware prevention system, kernel enforcement layer, root installer, network authority, or operating-system replacement.

---

## Nucleus and Runtime Boundary

Nucleus is the coordination and task-boundary layer. Its current implementation is report-only and denied by default.

Current Nucleus posture:

```text
nucleus_task_boundary_present=1
nucleus_task_report_refinement_present=1
nucleus_no_effect_report_alignment_present=1
nucleus_report_only_execution_status_present=1
effect_performing_task_execution=0
command_execution=0
runtime_authority_granted=0
```

Runtime Boundary is the disabled-by-default classification line before operational behavior.

Current Runtime Boundary posture:

```text
runtime_boundary_classification_present=1
runtime_boundary_report_refinement_present=1
runtime_boundary_policy_matrix_present=1
runtime_boundary_domain_matrix_present=1
runtime_behavior=0
effect_authority=denied
```

Relevant documents:

- [`docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md`](docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md)
- [`docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md`](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md)
- [`docs/NUCLEUS_TASK_REPORT_REFINEMENT.md`](docs/NUCLEUS_TASK_REPORT_REFINEMENT.md)
- [`docs/NUCLEUS_TASK_NO_EFFECT_REPORT_ALIGNMENT.md`](docs/NUCLEUS_TASK_NO_EFFECT_REPORT_ALIGNMENT.md)
- [`docs/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT.md`](docs/NUCLEUS_TASK_REPORT_ONLY_EXECUTION_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_CONTRACT.md`](docs/RUNTIME_BOUNDARY_CONTRACT.md)
- [`docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md`](docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md)
- [`docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md`](docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md`](docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md)
- [`docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REFINEMENT.md`](docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REFINEMENT.md)

---

## Latticra Seal

<p align="center">
  <img src="assets/latticra-seal-mascot-simple-0.png" alt="Latticra Seal mascot" width="360">
</p>

Latticra Seal is the trust-boundary and tool-boundary subsystem inside the Latticra ecosystem.

Its role is to model request-boundary, policy-boundary, trust-boundary, verification-boundary, runtime-gate, and tool-boundary behavior for AI-era automation and MCP-style tool invocation planning while remaining evidence-bound and no-effect.

Seal asks:

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
seal_guarded_allowlist_metadata_present=1
seal_guarded_allowlist_report_surface_present=1
seal_report_envelope_metadata_present=1
seal_report_envelope_ready_metadata_present=1
seal_signature_request_contract_present=1
seal_signature_request_metadata_present=1
seal_signature_request_status_present=1
seal_signing_authorization_contract_present=1
seal_signing_authorization_metadata_present=1
seal_signing_authorization_status_present=1
seal_signer_handoff_contract_present=1
seal_signer_handoff_metadata_present=1
seal_signer_handoff_status_present=1
runtime_gate_report_only=1
policy_decision_state=report-only
runtime_gate_state=report-only
default_action_deny=1
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
would_grant_runtime_authority=0
signature_performed=0
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

A careful public claim is:

```text
Latticra Seal has report-only runtime dry-run and guarded allowlist candidate-denial paths for AI-era tool-boundary planning.
```

Latticra Seal now has a report-only runtime gate path with core negative-test evidence for AI-era tool-boundary planning.

The sealed report-envelope metadata slice extends that path for ready metadata-only runtime handoff reports without adding signing, runtime handoff execution, host behavior, network behavior, or runtime authority.

The signature-request metadata slice classifies future signing requests after sealed report envelopes. It does not add signing, verification, private-key handling, host behavior, network behavior, capability enforcement, or runtime authority.

The signature-request status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The signing authorization contract defines the next metadata-only classification boundary after signature-request readiness. It does not add signing, verification, private-key handling, host behavior, network behavior, capability enforcement, or runtime authority.

The signing authorization metadata implementation classifies ready signature requests as authorized-metadata-only for a future signing path while preserving no signing, verification, private-key handling, host behavior, network behavior, capability enforcement, or runtime authority.

The signing authorization status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The signer handoff contract defines the next metadata-only classification boundary after signing authorization readiness. It does not add signing, verification, signer invocation, private-key handling, host behavior, network behavior, capability enforcement, or runtime authority.

The signer handoff metadata implementation classifies ready signing authorization metadata as handoff-metadata-only for a future signer path while preserving no signing, verification, signer invocation, private-key handling, host behavior, network behavior, capability enforcement, or runtime authority.

The signer handoff status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

That claim is intentionally limited. It does not mean Latticra Seal currently implements production runtime enforcement, policy enforcement, cryptographic key authority, MCP protocol behavior, MCP server behavior, MCP client behavior, AI-agent execution control, host behavior, network behavior, object sealing, key storage, or revocation lookup.

Relevant Seal records:

- [`docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md`](docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md)
- [`docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md`](docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md)
- [`docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md`](docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md)
- [`docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md`](docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md)
- [`docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md`](docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md)
- [`docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md`](docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_RUNTIME_ENFORCEMENT_GATE_CONTRACT.md`](docs/LATTICRA_SEAL_RUNTIME_ENFORCEMENT_GATE_CONTRACT.md)
- [`docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md`](docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md)
- [`docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md`](docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_CONTRACT.md)
- [`docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_CONTRACT.md`](docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_CONTRACT.md)
- [`docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_REPORT_ENVELOPE_CONTRACT.md`](docs/LATTICRA_SEAL_REPORT_ENVELOPE_CONTRACT.md)
- [`docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_SIGNATURE_REQUEST_CONTRACT.md`](docs/LATTICRA_SEAL_SIGNATURE_REQUEST_CONTRACT.md)
- [`docs/LATTICRA_SEAL_SIGNATURE_REQUEST_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_SIGNATURE_REQUEST_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md`](docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md`](docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md)
- [`docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md)
- [`docs/status/SEAL_SIGNER_HANDOFF_STATUS.md`](docs/status/SEAL_SIGNER_HANDOFF_STATUS.md)
- [`docs/status/SEAL_SIGNATURE_REQUEST_STATUS.md`](docs/status/SEAL_SIGNATURE_REQUEST_STATUS.md)
- [`docs/status/SEAL_SIGNING_AUTHORIZATION_STATUS.md`](docs/status/SEAL_SIGNING_AUTHORIZATION_STATUS.md)
- [`docs/status/SEAL_CORE_BLOCKED_CASES_STATUS.md`](docs/status/SEAL_CORE_BLOCKED_CASES_STATUS.md)
- [`docs/status/SEAL_CORE_EVIDENCE_STATUS.md`](docs/status/SEAL_CORE_EVIDENCE_STATUS.md)
- [`docs/status/SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md`](docs/status/SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md)

---

## Fedora and local RPM work

Latticra has a Fedora-facing validation lane, but it is intentionally narrow.

The current RPM packaging work is a **local-only draft**. It records packaging shape and local validation behavior. It does not claim Fedora approval, Fedora distribution readiness, production installation readiness, or daily-driver readiness.

Current local RPM package posture:

```text
local_only_draft=1
fedora_approval_claimed=0
fedora_distribution_ready=0
production_installer_ready=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

The current local spec builds a no-effect CLI binary from:

```text
src/latticra_cli.c
```

and installs:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

The CLI itself reports no-effect status and disabled runtime behavior.

Relevant Fedora records:

- [`docs/FEDORA_DEVELOPER_WORKFLOW.md`](docs/FEDORA_DEVELOPER_WORKFLOW.md)
- [`docs/FEDORA_PACKAGE_METADATA_PLAN.md`](docs/FEDORA_PACKAGE_METADATA_PLAN.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md)
- [`packaging/fedora/latticra.spec`](packaging/fedora/latticra.spec)

---

## Visual theorem engines

Latticra includes C-based visual theorem engines that render symbolic substrate models as MP4 video demonstrations.

These engines are mathematical art engines and speculative computation-model demonstrations. They are not production runtime components, proof assistants, physics engines, or security mechanisms.

Current engine paths:

```text
latt-field-engines/substrate-engine/
latt-field-engines/visual-theorem-engine/
```

Build both engines:

```sh
scripts/render-visual-theorem-engines.sh build
```

Render the substrate engine:

```sh
scripts/render-visual-theorem-engines.sh substrate 96
```

Render the theorem engine:

```sh
scripts/render-visual-theorem-engines.sh theorem 60
```

Render both:

```sh
scripts/render-visual-theorem-engines.sh all 96
```

Requirements:

```text
gcc
ffmpeg
standard C math library linked with -lm
```

On Fedora:

```sh
sudo dnf install gcc ffmpeg
```

See [`docs/VISUAL_THEOREM_ENGINES.md`](docs/VISUAL_THEOREM_ENGINES.md).

---

## Repository map

High-level map:

```text
.
├── README.md
├── STATUS.md
├── SECURITY.md
├── CONTRIBUTING.md
├── LICENSE
├── docs/
│   ├── FOUNDATION_INDEX.md
│   ├── status/
│   ├── strategy/
│   ├── project_notes/
│   ├── architecture/
│   ├── roadmap/
│   └── many contract, implementation, status, and validation records
├── include/latticra/
│   └── public C headers for bounded no-effect implementation slices
├── src/
│   └── C implementation and no-effect CLI surfaces
├── scripts/
│   └── shell guards, validation scripts, report scripts, and render scripts
├── installer/
│   └── Latticra Panel GUI workbench, configs, manifests, scripts, docs, and receipts/plans
├── packaging/fedora/
│   └── local-only Fedora RPM draft
├── latt-field-engines/
│   └── C visual theorem engines
└── assets/
    └── project images and mascot assets
```

Installer map:

```text
installer/
  Makefile
  README.md
  INSTALLER_ROADMAP.md
  TREE.txt
  configs/
    default.installer.toml
    local-prefix-example.installer.toml
  docs/
    INSTALL_BUTTON_EXECUTION_MODEL.md
    INSTALLER_READINESS_CONTRACT.md
    RECEIPTS_AND_EVIDENCE.md
    UI_CONFIGURATION_MODEL.md
  manifests/
    components.toml
  scripts/
    latticra-installer-apply.sh
    latticra-installer-dry-run.sh
    latticra-installer-uninstall.sh
    latticra-installer-verify.sh
  latticra-installer/
    Cargo.toml
    Cargo.lock
    assets/latticra-seal.png
    src/main.rs
    src/config.rs
    src/engine.rs
    src/ui.rs
```

---

## Documentation entry points

Start here:

- [`STATUS.md`](STATUS.md)
- [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md)
- [`docs/status/ANNOUNCEMENTS.md`](docs/status/ANNOUNCEMENTS.md)
- [`docs/FOUNDATION_INDEX.md`](docs/FOUNDATION_INDEX.md)
- [`docs/latticra-system-substrate/`](docs/latticra-system-substrate/)
- [`docs/latticra/DOCUMENTATION_MAP.md`](docs/latticra/DOCUMENTATION_MAP.md)
- [`docs/strategy/README.md`](docs/strategy/README.md)
- [`docs/project_notes/README.md`](docs/project_notes/README.md)
- [`SECURITY.md`](SECURITY.md)
- [`CONTRIBUTING.md`](CONTRIBUTING.md)

Architecture and language direction:

- [`docs/C_CPP_FOUNDATION_DIRECTION.md`](docs/C_CPP_FOUNDATION_DIRECTION.md)
- [`docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md`](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md)
- [`docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md`](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md)
- [`docs/architecture/LATTICRA_LANGUAGE_FOUNDATION.md`](docs/architecture/LATTICRA_LANGUAGE_FOUNDATION.md)
- [`docs/LANGUAGE_STRATEGY.md`](docs/LANGUAGE_STRATEGY.md)
- [`docs/NAMING_SYSTEM.md`](docs/NAMING_SYSTEM.md)

Runtime, Nucleus, and boundary direction:

- [`docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md`](docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md)
- [`docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md`](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md)
- [`docs/RUNTIME_BOUNDARY_CONTRACT.md`](docs/RUNTIME_BOUNDARY_CONTRACT.md)
- [`docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md`](docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md)

Installer and Fedora direction:

- [`installer/README.md`](installer/README.md)
- [`installer/docs/UI_CONFIGURATION_MODEL.md`](installer/docs/UI_CONFIGURATION_MODEL.md)
- [`docs/FEDORA_DEVELOPER_WORKFLOW.md`](docs/FEDORA_DEVELOPER_WORKFLOW.md)
- [`packaging/fedora/latticra.spec`](packaging/fedora/latticra.spec)

Visual theorem engines:

- [`docs/VISUAL_THEOREM_ENGINES.md`](docs/VISUAL_THEOREM_ENGINES.md)

---

## Development philosophy

Latticra follows an evidence-first development model.

```text
No contract without identity.
No authority without capability.
No effect without a boundary.
No promotion without evidence.
```

Implementation work should not be added until the relevant contract identifies:

1. purpose;
2. evidence level;
3. effect boundary;
4. failure behavior;
5. non-claims;
6. tests or validation path.

Security-relevant changes should be small, reviewable, tested, and explicit about what they do **not** claim.

---

## Security

See [`SECURITY.md`](SECURITY.md).

Current security posture:

```text
finished_operating_system=0
hardened_sandbox=0
production_runtime=0
security_boundary=0
kernel_isolation=0
malware_containment=0
ransomware_prevention=0
secure_boot=0
production_cryptography=0
```

Security reports should target the current `main` branch unless another branch or release line is explicitly identified as supported.

---

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md).

Contributions should preserve the project posture:

```text
open source
auditable
transparent
security-conscious
evidence-bound
community-improvable
```

Changes that affect runtime behavior, state mutation, external effects, command behavior, file behavior, network behavior, hardware behavior, boot behavior, recovery behavior, or security claims require explicit tests and documentation.

---

## License posture

The current canonical repository license file is [`LICENSE`](LICENSE), which contains Apache-2.0.

The project also maintains an active license transition policy in [`docs/LICENSE_POLICY.md`](docs/LICENSE_POLICY.md). That policy states that new software work is intended to move toward:

```text
AGPL-3.0-or-later
```

There is no silent relicensing. Existing files remain under their current license state unless a future migration PR updates them clearly and intentionally.

File-level SPDX identifiers and path-level notices should be respected.

Branding, names, logos, marks, and Bryforge/Latticra identity are handled separately from software and documentation licenses.

This section is project guidance, not legal advice.

---

## Support

Support Bryforge:

```text
https://buymeacoffee.com/Bryforge
```

---

<details>
<summary><strong>About Chase Bryan</strong></summary>

Chase Bryan is a computer scientist, systems builder, and low-level software developer focused on operating systems, programming languages, security architecture, Linux-native tooling, and evidence-bound systems design.

Latticra is the public workspace for this research and development direction.

</details>

<details>
<summary><strong>Latticra in 5 minutes</strong></summary>

Read the short overview here:

[**Latticra in 5 minutes**](https://x.com/ckbryan91/status/2057763410771603832?s=20)

</details>

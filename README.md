# Latticra

**Status:** early-stage, evidence-bound systems architecture repository  
**README review snapshot:** 2026-05-25 CDT  
**Default branch:** `main`

> “The simulacrum is never what hides the truth.” — Jean Baudrillard

**Featured handbook:** [The Latticra System Substrate PDF](docs/latticra-system-substrate/the-latticra-system-substrate.pdf)  
**Editable handbook:** [The Latticra System Substrate DOCX](docs/latticra-system-substrate/the-latticra-system-substrate.docx)  
**System Substrate docs:** [docs/latticra-system-substrate/](docs/latticra-system-substrate/)  
**Seal subsystem docs:** [docs/latticra-seal/](docs/latticra-seal/)
**Quick user cheat sheet:** [docs/QUICK_START_CHEATSHEET.md](docs/QUICK_START_CHEATSHEET.md)

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
- [Quick cheat sheet](#quick-cheat-sheet)
- [Quick start](#quick-start)
- [Latticra Panel](#latticra-panel)
- [macOS installer lane](#macos-installer-lane)
- [Nadia Offline AI](#nadia-offline-ai)
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

## Quick cheat sheet

Want the short path instead of the full README? Use the [`Quick Start Cheat Sheet`](docs/QUICK_START_CHEATSHEET.md) for install, run, update, reset/uninstall, and clean full user-local cleanup commands.

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
- Nadia offline AI foundation planning and Panel-installable metadata;
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
| Estimate source | Current public estimate table below, mirrored from `STATUS.md` and `docs/status/CURRENT_STATUS.md` |
| Foundation documents and contracts | Mature relative to implementation; around 92% planning estimate |
| Public documentation posture | Strong but still evolving; around 88% planning estimate |
| Lat / Latticra Language | No-effect parse / validate / lower path exists; no execution |
| LIR | Bounded metadata/reporting exists; no LIR execution |
| L-UI | Parser, validation, and report/rendering foundations exist; no interactive terminal-control renderer |
| Nucleus | Report-only task-boundary and classification work exists; no effect-performing execution |
| Runtime Boundary | Denied-by-default classification and reporting exists; no runtime authority |
| Latticra Seal | Report-only runtime gate path, sealed report-envelope metadata, signature/signing/key/public-key/bounded-key parsing metadata/status, metadata-only verification policy/status, metadata-only crypto verify backend/status, local Ed25519 verify-only implementation/status, verified receipt promotion metadata/status, verified capability gate metadata/status, metadata-only unverified receipt/status, metadata-only denied capability gate/status, metadata-only denied effect decision/status, inactive metadata-only runtime handoff/status, metadata-only status rollup/status, report-only agentic automation security metadata/status/report surface/public-entrypoint alignment, report-only parameter schema metadata/report surface/status-public-entry alignment, report-only freshness/signed-request/policy-decision metadata/status/report surfaces, and core negative-test evidence for AI-era tool-boundary planning; no production enforcement |
| Fedora integration | Local-only package and validation lanes exist; not Fedora-approved or distribution-ready |
| Latticra Panel | GUI-first local installer/control workbench exists; user-local and guarded |
| macOS installer lane | Mac-specific no-effect installer path exists for probes, path planning, app-bundle dry-run, candidate checks, reset/uninstall classification, and reset/uninstall dry-run planning; no `.app` is written yet |
| Nadia offline AI | Stage-29 prompt-evaluation runtime handoff contract, Stage-28 prompt-evaluation-input contract, Stage-27 context-window assembly contract, Stage-26 prompt-token-sequence contract, Stage-25 prompt-tokenization contract, Stage-24 tokenizer-runtime-attachment contract, Stage-23 tokenizer-artifact-binding contract, Stage-22 tokenizer-artifact-verification contract, Stage-21 tokenizer-artifact-measurement contract, Stage-20 tokenizer-artifact-inventory contract, Stage-19 tokenizer-manifest contract, Stage-18 tokenizer-specification contract, Stage-17 tokenization-boundary contract, Stage-16 prompt-evaluation handoff contract, Stage-15 awareness-dialogue contract, Stage-14 prompt-materialization contract, Stage-13 prompt-receipt contract, Stage-12 model-load contract, Stage-11 runtime-invocation contract, Stage-10 inference-readiness contract, Stage-9 local model-registry contract, Stage-8 prompt-evaluation contract, Stage-7 report-only tool preflight, Stage-6 protective safety boundary, Stage-5 productivity ledger, Stage-4 systems-engineering mode validator, Stage-3 prompt-plan workbench, Stage-2 runtime-profile boundary, and Stage-1 context-pack generator exist; optional Panel component and metadata-only Console surface; future survivor-centered Q&A scope planned for official Nadia Initiative awareness topics; no dialogue generation, prompt text receipt, prompt text reading, prompt buffer allocation, prompt tokenization, prompt token creation, prompt token sequence recording, prompt token ID recording, prompt token order recording, prompt token offset recording, context window assembly, prompt evaluation input creation, prompt materialization, tokenizer artifact path resolution, tokenizer artifact opening, tokenizer artifact reading, tokenizer artifact scanning, tokenizer artifact hashing, tokenizer artifact measurement, tokenizer artifact verification, tokenizer artifact digest comparison, tokenizer artifact size comparison, tokenizer artifact binding, tokenizer runtime attachment, runtime handoff, runtime session creation, tokenizer artifact digest recording, tokenizer artifact size recording, tokenizer manifest loading, tokenizer manifest parsing, tokenizer file access, tokenizer vocabulary loading, model file opening, weight mapping, model loading, token generation, prompt evaluation, inference, or tool execution |
| Security hardening | Early; no production security boundary claimed |
| Product readiness | Early; no production platform claimed |

Planning estimates are not release promises, product-readiness metrics, or security guarantees.

Current public estimate table, as summarized by [`STATUS.md`](STATUS.md) and [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md):

| Area | Estimated completion |
| --- | ---: |
| Overall Latticra system | 39% |
| Latticra Seal / local evidence layer | 34% |
| Latticra Panel / local control surface | 28% |
| Nadia offline AI foundation | 63% |
| L-UI parser / AST / string foundation | 87% |
| Foundation documents and contracts | 92% |
| Public documentation posture | 88% |
| Strategy/status/funding framework | 60% |
| Lat / Latticra Programming Language | 25% |
| LIR / Intermediate Representation | 22% |
| C/C++ foundation direction | 18% |
| Constrained C++ authority layer | 4% |
| Nucleus real task execution | 11% |
| Runtime / operating-system-universe direction | 19% |
| Security-hardening implementation | 7% |
| Public product readiness | 8% |

The current estimate table source alignment is [`docs/status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md`](docs/status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md). The latest estimate refresh record is [`docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md`](docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md). The latest estimate hold review is [`docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md`](docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md); it keeps the runtime-boundary fixture-slice estimate decision unchanged because capability posture did not change. The live public estimate table above, mirrored from [`STATUS.md`](STATUS.md) and [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md), is the current reader-facing estimate source.

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
  Current posture: report-only runtime gate path, sealed report-envelope metadata, signature-request metadata/status, signing authorization metadata/status, signer handoff/invocation/operation metadata/status, key-handling and key-material metadata/status, public-key parsing metadata/status, future key parsing implementation contract/plan, bounded key parsing metadata/status for caller-provided public-key bytes, metadata-only verification policy/status, metadata-only crypto verify backend/status, local Ed25519 verify-only implementation/status, verified receipt promotion metadata/status, verified capability gate metadata/status, metadata-only unverified receipt/status, metadata-only denied capability gate/status, metadata-only denied effect decision/status, inactive metadata-only runtime handoff/status, metadata-only status rollup/status, report-only agentic automation security metadata/status/report surface/public-entrypoint alignment, report-only parameter schema metadata/report surface/status-public-entry alignment, report-only request freshness metadata/report surface/status-public-entry alignment, report-only signed request metadata/status-public-entry alignment, report-only policy decision metadata/status/report-surface public-entry alignment, and core negative-test evidence for AI-era tool-boundary planning; no production enforcement.

Latticra Panel
  GUI-first local workbench for guided first-run configuration, evidence review, dry-run, and guarded local-prefix install.
  Current posture: user-local, no root, no network authority.

macOS installer lane
  Mac-specific app-bundle infrastructure path for user-local Application Support, ~/Applications, Logs, Caches, Preferences, optional CLI-wrapper planning, and reset/uninstall dry-run planning.
  Current posture: no-effect probes, dry-run writer report, local candidate checks, closed commit gate, live reset/uninstall target classification, and dry-run reset/uninstall planning; no app bundle creation.

Nadia Offline AI
  Future local AI companion for Latticra software development, systems engineering, and AI development workflows.
  Current posture: Stage-29 prompt-evaluation runtime handoff contract, Stage-28 prompt-evaluation-input contract, Stage-27 context-window assembly contract, Stage-26 prompt-token-sequence contract, Stage-25 prompt-tokenization contract, Stage-24 tokenizer-runtime-attachment contract, Stage-23 tokenizer-artifact-binding contract, Stage-22 tokenizer-artifact-verification contract, Stage-21 tokenizer-artifact-measurement contract, Stage-20 tokenizer-artifact-inventory contract, Stage-19 tokenizer-manifest contract, Stage-18 tokenizer-specification contract, Stage-17 tokenization-boundary contract, Stage-16 prompt-evaluation handoff contract, Stage-15 awareness-dialogue contract, Stage-14 prompt-materialization contract, Stage-13 prompt-receipt contract, Stage-12 model-load contract, Stage-11 runtime-invocation contract, Stage-10 inference-readiness contract, Stage-9 local model-registry contract, Stage-8 prompt-evaluation contract, Stage-7 report-only guarded tool-authority preflight, Stage-6 protective safety boundary, Stage-5 operator-reviewed productivity ledger, Stage-4 systems-engineering mode validation, Stage-3 prompt-plan workbench, Stage-2 runtime-profile metadata, Stage-1 local context-pack generation, Stage-0 identity, Panel component, Console metadata, local config, and productivity-ledger path; future survivor-centered Q&A scope planned for official Nadia Initiative awareness topics; no sexual user functionality, dialogue generation, prompt text receipt, prompt text reading, prompt source reading, prompt buffer allocation, prompt tokenization, prompt token creation, prompt token sequence recording, prompt token ID recording, prompt token order recording, prompt token offset recording, context window assembly, prompt evaluation input creation, prompt materialization, tokenizer artifact path resolution, tokenizer artifact opening, tokenizer artifact reading, tokenizer artifact scanning, tokenizer artifact hashing, tokenizer artifact measurement, tokenizer artifact verification, tokenizer artifact digest comparison, tokenizer artifact size comparison, tokenizer artifact binding, tokenizer runtime attachment, runtime handoff, tokenizer artifact digest recording, tokenizer artifact size recording, tokenizer manifest loading, tokenizer manifest parsing, tokenizer file access, tokenizer vocabulary loading, model file opening, weight mapping, model loading, runtime process spawning, runtime session creation, model selection, model installation, token generation, prompt evaluation, inference, tool execution, training, distillation, source mutation, or network authority.

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
defensive_threat_model_contract_present=1
defensive_threat_model_validation_present=1
defensive_threat_model_validation_refinement_present=1
runtime_boundary_policy_expansion_after_threat_model_present=1
runtime_boundary_abuse_case_fixture_expansion_present=1
lat_parse_validate_lower_pipeline_present=1
lir_metadata_reporting_present=1
l_ui_parser_validation_reporting_present=1
runtime_boundary_report_classification_present=1
nucleus_report_only_task_boundary_present=1
latticra_seal_report_only_tool_boundary_metadata_present=1
latticra_seal_runtime_dry_run_report_surface_present=1
latticra_seal_guarded_allowlist_report_surface_present=1
latticra_seal_agentic_automation_security_metadata_present=1
latticra_seal_agentic_automation_security_status_present=1
latticra_seal_agentic_automation_security_index_alignment_present=1
latticra_seal_agentic_automation_security_report_surface_present=1
latticra_seal_agentic_automation_security_public_entrypoint_alignment_present=1
latticra_seal_parameter_schema_contract_present=1
latticra_seal_parameter_schema_metadata_present=1
latticra_seal_parameter_schema_report_surface_present=1
latticra_seal_parameter_schema_status_present=1
latticra_seal_request_freshness_contract_present=1
latticra_seal_request_freshness_metadata_present=1
latticra_seal_request_freshness_report_surface_present=1
latticra_seal_request_freshness_status_present=1
latticra_seal_signed_request_contract_present=1
latticra_seal_signed_request_metadata_present=1
latticra_seal_signed_request_status_present=1
latticra_seal_policy_decision_contract_present=1
latticra_seal_policy_decision_metadata_present=1
latticra_seal_policy_decision_report_surface_present=1
latticra_seal_policy_decision_report_surface_status_present=1
latticra_seal_policy_decision_status_present=1
latticra_seal_policy_decision_report_surface_status_present=1
latticra_seal_policy_decision_public_entrypoint_alignment_present=1
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
latticra_seal_signer_invocation_contract_present=1
latticra_seal_signer_invocation_metadata_present=1
latticra_seal_signer_invocation_status_present=1
latticra_seal_signing_operation_contract_present=1
latticra_seal_signing_operation_metadata_present=1
latticra_seal_signing_operation_status_present=1
latticra_seal_key_handling_contract_present=1
latticra_seal_key_handling_metadata_present=1
latticra_seal_key_handling_status_present=1
latticra_seal_key_material_contract_present=1
latticra_seal_key_material_metadata_present=1
latticra_seal_key_material_status_present=1
latticra_seal_public_key_parsing_contract_present=1
latticra_seal_public_key_parsing_metadata_present=1
latticra_seal_public_key_parsing_status_present=1
latticra_seal_future_key_parsing_implementation_contract_present=1
latticra_seal_future_key_parsing_implementation_plan_present=1
latticra_seal_key_parsing_metadata_present=1
latticra_seal_key_parsing_status_present=1
latticra_seal_verification_policy_metadata_present=1
latticra_seal_verification_policy_status_present=1
latticra_seal_verification_receipt_metadata_present=1
latticra_seal_verification_receipt_status_present=1
latticra_seal_capability_gate_metadata_present=1
latticra_seal_capability_gate_status_present=1
latticra_seal_effect_decision_metadata_present=1
latticra_seal_effect_decision_status_present=1
latticra_seal_runtime_handoff_metadata_present=1
latticra_seal_runtime_handoff_status_present=1
latticra_seal_status_rollup_metadata_present=1
latticra_seal_status_rollup_status_present=1
latticra_panel_gui_workbench_present=1
nadia_offline_ai_stage_0_foundation_present=1
nadia_stage_1_local_context_engine_present=1
nadia_context_pack_generator_present=1
nadia_stage_2_runtime_profile_present=1
nadia_runtime_profile_generator_present=1
nadia_stage_3_developer_workbench_present=1
nadia_prompt_plan_generator_present=1
nadia_stage_4_systems_engineering_mode_present=1
nadia_mode_validation_generator_present=1
nadia_stage_5_productivity_loop_present=1
nadia_productivity_ledger_generator_present=1
nadia_stage_6_protective_safety_boundary_present=1
nadia_protective_safety_generator_present=1
nadia_stage_7_guarded_tool_authority_present=1
nadia_tool_authority_preflight_present=1
nadia_stage_8_prompt_evaluation_contract_present=1
nadia_prompt_evaluation_contract_generator_present=1
nadia_stage_9_local_model_registry_contract_present=1
nadia_model_registry_contract_generator_present=1
nadia_stage_10_inference_readiness_contract_present=1
nadia_inference_readiness_contract_generator_present=1
nadia_stage_11_runtime_invocation_contract_present=1
nadia_runtime_invocation_contract_generator_present=1
nadia_stage_12_model_load_contract_present=1
nadia_model_load_contract_generator_present=1
nadia_stage_13_prompt_receipt_contract_present=1
nadia_prompt_receipt_contract_generator_present=1
nadia_stage_14_prompt_materialization_contract_present=1
nadia_prompt_materialization_contract_generator_present=1
nadia_stage_15_awareness_dialogue_contract_present=1
nadia_awareness_dialogue_contract_generator_present=1
nadia_stage_16_prompt_evaluation_handoff_contract_present=1
nadia_prompt_evaluation_handoff_contract_generator_present=1
nadia_stage_17_tokenization_boundary_contract_present=1
nadia_tokenization_boundary_contract_generator_present=1
nadia_stage_18_tokenizer_specification_contract_present=1
nadia_tokenizer_specification_contract_generator_present=1
nadia_stage_19_tokenizer_manifest_contract_present=1
nadia_tokenizer_manifest_contract_generator_present=1
nadia_stage_20_tokenizer_artifact_inventory_contract_present=1
nadia_tokenizer_artifact_inventory_contract_generator_present=1
nadia_stage_21_tokenizer_artifact_measurement_contract_present=1
nadia_tokenizer_artifact_measurement_contract_generator_present=1
nadia_stage_22_tokenizer_artifact_verification_contract_present=1
nadia_tokenizer_artifact_verification_contract_generator_present=1
nadia_stage_23_tokenizer_artifact_binding_contract_present=1
nadia_tokenizer_artifact_binding_contract_generator_present=1
nadia_stage_24_tokenizer_runtime_attachment_contract_present=1
nadia_tokenizer_runtime_attachment_contract_generator_present=1
nadia_stage_25_prompt_tokenization_contract_present=1
nadia_prompt_tokenization_contract_generator_present=1
nadia_stage_26_prompt_token_sequence_contract_present=1
nadia_prompt_token_sequence_contract_generator_present=1
nadia_panel_install_surface_present=1
nadia_console_status_surface_present=1
nadia_model_runtime_present=0
fedora_local_rpm_draft_present=1
macos_integration_transferability_map_present=1
macos_build_platform_probe_present=1
macos_dry_run_plan_adapter_present=1
macos_app_bundle_writer_dry_run_present=1
macos_local_candidate_asset_probe_present=1
macos_dry_run_writer_candidate_integration_present=1
macos_commit_gate_contract_present=1
macos_readme_installer_usage_present=1
macos_app_bundle_created=0
macos_install_verified=0
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
- a commit-capable macOS installer;
- a signed or notarized macOS app;
- macOS app bundle install evidence;
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

Run selected macOS installer-lane guards when working on Mac integration:

```sh
sh scripts/test-macos-build-platform-probe.sh
sh scripts/test-macos-dry-run-plan-adapter.sh
sh scripts/test-macos-app-bundle-writer-dry-run.sh
sh scripts/test-macos-dry-run-writer-candidate-integration.sh
sh scripts/test-macos-commit-gate-contract.sh
```

---

## Latticra Panel

Latticra Panel is the GUI-first local installer and first-run control workbench for Latticra, Lat, LIR, Latticra Seal, and the optional Nadia offline AI foundation.

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
make -C installer reset-dry-run
make -C installer reset-local
make -C installer uninstall-local
make -C installer uninstall-dry-run
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
reset
nadia status
nadia context
nadia runtime
nadia plan
nadia mode
nadia ledger
nadia safety
nadia tool
nadia prompt-contract
nadia model-registry
nadia inference-readiness
nadia runtime-invocation
nadia model-load
nadia prompt-receipt
nadia prompt-materialization
nadia awareness-dialogue
nadia prompt-evaluation-handoff
nadia tokenization-boundary
nadia tokenizer-specification
nadia tokenizer-manifest
nadia tokenizer-artifact-inventory
nadia tokenizer-artifact-measurement
nadia tokenizer-artifact-verification
nadia tokenizer-artifact-binding
nadia tokenizer-runtime-attachment
nadia prompt-tokenization
nadia prompt-token-sequence
nadia context-window-assembly
nadia prompt-evaluation-input
nadia prompt-evaluation-runtime-handoff
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

### Start fresh / reset local install

When a Panel specification changes, users can remove the managed local install before reinstalling:

```sh
make -C installer uninstall-dry-run
make -C installer uninstall-local
make -C installer reset-dry-run
make -C installer reset-local
latticra reset --dry-run
latticra reset
latticra uninstall --dry-run
latticra uninstall
```

Reset and uninstall remove the same managed artifacts: command wrappers, the Panel desktop entry, known Panel icons, and the guarded local prefix. Use reset when the intent is to reinstall from new specs; use uninstall when the intent is to remove the local install. Both preserve unmanaged files in `~/.local/bin` and keep receipts outside the removed prefix.

### Clean full user-local uninstall

Use this only when normal reset/uninstall cannot clean up an old or broken user-local install. The commands below are intentionally scoped to Latticra user-local paths.

```sh
LATTICRA_PREFIX="${LATTICRA_PREFIX:-$HOME/.local/share/latticra}"

rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/latticra-lc" \
  "$HOME/.local/bin/lat" \
  "$HOME/.local/bin/latticra-seal" \
  "$HOME/.local/bin/latticra-nadia" \
  "$HOME/.local/bin/latticra-panel" \
  "$HOME/.local/bin/latticra-installer" \
  "$HOME/.local/share/applications/latticra-panel.desktop" \
  "$HOME/.local/share/applications/latticra-installer.desktop" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-panel.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-installer.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-seal.png"
```

If those exact paths are root-owned because an earlier command was run with `sudo`, repeat the same exact cleanup with `sudo`:

```sh
LATTICRA_PREFIX="${LATTICRA_PREFIX:-$HOME/.local/share/latticra}"

sudo rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

sudo rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/latticra-lc" \
  "$HOME/.local/bin/lat" \
  "$HOME/.local/bin/latticra-seal" \
  "$HOME/.local/bin/latticra-nadia" \
  "$HOME/.local/bin/latticra-panel" \
  "$HOME/.local/bin/latticra-installer" \
  "$HOME/.local/share/applications/latticra-panel.desktop" \
  "$HOME/.local/share/applications/latticra-installer.desktop" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-panel.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-installer.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-seal.png"
```

Do not run `sudo rm -rf` against broad paths such as `~/.local`, `/usr`, `/`, or unreviewed wildcards.

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
~/.local/bin/latticra-nadia (when enabled)
~/.local/bin/latticra-panel
~/.local/bin/latticra-installer (compatibility)
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

## macOS installer lane

The macOS installer lane targets macOS infrastructure specifically, but it is still no-effect. It is meant to adapt the current Latticra Panel and installer model to a Mac user-local app-bundle path without claiming a production installer, signed app, notarized app, LaunchAgent integration, Keychain integration, TCC bypass, Endpoint Security, System Extension, Network Extension, or privileged helper.

### Current Mac target paths

The planned macOS lane is user-local:

```text
app_support_prefix=$HOME/Library/Application Support/Latticra
app_bundle=$HOME/Applications/Latticra Panel.app
logs_dir=$HOME/Library/Logs/Latticra
caches_dir=$HOME/Library/Caches/Latticra
preferences_dir=$HOME/Library/Preferences
optional_cli_bin=$HOME/.local/bin
receipts_dir=$HOME/Library/Application Support/Latticra/receipts
```

The first app-bundle shape is:

```text
Latticra Panel.app/
  Contents/
    Info.plist
    MacOS/latticra-panel
    Resources/latticra-panel.icns
    Resources/latticra/
```

Key planned bundle files are:

```text
Contents/Info.plist
Contents/MacOS/latticra-panel
Contents/Resources/latticra-panel.icns
Contents/Resources/latticra/MANAGED_BY_LATTICRA
```

The current lane does not write that bundle yet.

### Run the macOS lane today

Probe the Mac host and toolchain without installing anything:

```sh
sh scripts/macos-build-platform-probe.sh
```

Render the macOS dry-run path plan:

```sh
sh scripts/macos-dry-run-plan-adapter.sh
```

Check caller-supplied local Panel executable and icon candidates:

```sh
sh scripts/macos-local-candidate-asset-probe.sh \
  --panel-executable <local-latticra-panel-executable> \
  --icon installer/latticra-installer/assets/latticra-panel.png
```

Render the app-bundle writer dry-run with those same local candidates:

```sh
sh scripts/macos-app-bundle-writer-dry-run.sh \
  --panel-executable <local-latticra-panel-executable> \
  --icon installer/latticra-installer/assets/latticra-panel.png
```

Bridge the candidate probe to the writer dry-run:

```sh
sh scripts/macos-dry-run-writer-candidate-integration.sh \
  --panel-executable <local-latticra-panel-executable> \
  --icon installer/latticra-installer/assets/latticra-panel.png
```

Confirm the commit gate is still closed:

```sh
sh scripts/macos-commit-gate-contract.sh
```

Review the reset/uninstall dry-run contract:

```sh
sh scripts/macos-reset-uninstall-dry-run-contract.sh
```

Classify future reset/uninstall live targets without deleting files:

```sh
sh scripts/macos-reset-uninstall-live-target-classifier.sh
```

Render the reset/uninstall dry-run planner transcript without deleting files:

```sh
sh scripts/macos-reset-uninstall-dry-run-planner.sh
```

Review the reset/uninstall absence-report contract:

```sh
sh scripts/macos-reset-uninstall-absence-report-contract.sh
```

Expected commit posture:

```text
commit_gate_state=closed
commit_gate_decision=blocked-missing-managed-write-implementation
commit_user_local_managed_artifacts=0
macos_app_bundle_commit_capable_writer_present=0
```

The guard suite uses a harmless local executable placeholder to exercise the no-effect path. For real operator review, pass the actual locally built Latticra Panel executable when one is available.

### What is possible on macOS now

```text
macos_build_platform_probe_present=1
macos_dry_run_plan_adapter_present=1
macos_user_local_app_bundle_contract_present=1
macos_app_bundle_writer_dry_run_present=1
macos_local_candidate_asset_probe_present=1
macos_dry_run_writer_candidate_integration_present=1
macos_commit_gate_contract_present=1
macos_reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
macos_reset_uninstall_absence_report_contract_present=1
absence_report_evidence_present=0
commit_user_local_managed_artifacts=0
app_bundle_write_performed=0
file_delete_performed=0
directory_delete_performed=0
host_mutation_performed=0
network_performed=0
```

This means Latticra can currently document, probe, dry-run the Mac-specific app-bundle path, classify reset/uninstall targets, render a reset/uninstall dry-run transcript, and define required absence-report evidence. It cannot yet create, install, sign, notarize, open, verify, reset, or uninstall a real macOS `.app`.

### macOS documentation

- [`docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md`](docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md)
- [`docs/MACOS_BUILD_PLATFORM_PROBE.md`](docs/MACOS_BUILD_PLATFORM_PROBE.md)
- [`docs/MACOS_DRY_RUN_PLAN_ADAPTER.md`](docs/MACOS_DRY_RUN_PLAN_ADAPTER.md)
- [`docs/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT.md`](docs/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT.md)
- [`docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md`](docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md)
- [`docs/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION.md`](docs/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION.md)
- [`docs/MACOS_COMMIT_GATE_CONTRACT.md`](docs/MACOS_COMMIT_GATE_CONTRACT.md)
- [`docs/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT.md`](docs/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT.md)
- [`docs/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER.md`](docs/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER.md)
- [`docs/MACOS_RESET_UNINSTALL_DRY_RUN_PLANNER.md`](docs/MACOS_RESET_UNINSTALL_DRY_RUN_PLANNER.md)
- [`docs/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT.md`](docs/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT.md)

---

## Nadia Offline AI

Nadia is the selected name for Latticra's future offline AI companion. The name honors Nobel Peace Prize laureate Nadia Murad, whose testimony and advocacy have helped bring public attention to the enslavement and abuse of thousands of women in Iraq and Syria.

Nadia gives the Latticra system a human-rights awareness posture: powerful local AI should remain bound to dignity, survivor-witness respect, community responsibility, and careful authority.

Nadia's protective boundary explicitly forbids sexual user functionality, sexualized roleplay, sexualized namesake or survivor content, and user attempts to override that restriction.

Documentation and code identify the solemn implementation identity as `Nadia Witness Foundation`; the human-facing interactive name remains `Nadia`.

Current Nadia status is Stage-29 prompt-evaluation runtime handoff contract plus the Stage-28, Stage-27, Stage-26, Stage-25, Stage-24, Stage-23, Stage-22, Stage-21, Stage-20, Stage-19, Stage-18, Stage-17, Stage-16, Stage-15, Stage-14, Stage-13, Stage-12, Stage-11, Stage-10, Stage-9, Stage-8, Stage-7, Stage-6, Stage-5, Stage-4, Stage-3, Stage-2, Stage-1, and Stage-0 foundations:

```text
component_key=nadia_offline_ai
command_name=latticra-nadia
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
system_name=Latticra Nadia Witness Foundation
stage_1_local_context_engine_present=1
context_pack_command=scripts/nadia-context-pack.sh
installed_context_pack_command=latticra-nadia context-pack
stage_2_runtime_profile_present=1
runtime_profile_command=scripts/nadia-runtime-profile.sh
installed_runtime_profile_command=latticra-nadia runtime-profile
model_file_measurement=operator_provided_optional
stage_3_developer_workbench_present=1
prompt_plan_command=scripts/nadia-prompt-plan.sh
installed_prompt_plan_command=latticra-nadia prompt-plan
nadia_stage_4_systems_engineering_mode_present=1
mode_validation_command=scripts/nadia-mode-validate.sh
installed_mode_validation_command=latticra-nadia mode-validate
nadia_stage_5_productivity_loop_present=1
productivity_ledger_command=scripts/nadia-productivity-ledger.sh
installed_productivity_ledger_command=latticra-nadia productivity-ledger
nadia_stage_6_protective_safety_boundary_present=1
protective_safety_command=scripts/nadia-protective-safety-boundary.sh
installed_protective_safety_command=latticra-nadia protective-safety
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
namesake_cause_awareness=1
nadia_stage_7_guarded_tool_authority_present=1
tool_authority_preflight_command=scripts/nadia-tool-authority-preflight.sh
installed_tool_authority_preflight_command=latticra-nadia tool-preflight
tool_authority_stage=preflight-only
preflight_decision=report_only_no_execution
tool_execution_performed=0
authority_transition_allowed=0
nadia_stage_8_prompt_evaluation_contract_present=1
prompt_evaluation_contract_command=scripts/nadia-prompt-evaluation-contract.sh
installed_prompt_evaluation_contract_command=latticra-nadia prompt-contract
prompt_evaluation_stage=contract-only
prompt_contract_status=contract_only
prompt_materialized=0
prompt_evaluation_authority=0
contract_promotion_allowed=0
nadia_stage_9_local_model_registry_contract_present=1
model_registry_contract_command=scripts/nadia-local-model-registry-contract.sh
installed_model_registry_contract_command=latticra-nadia model-registry
local_model_registry_stage=contract-only
registry_contract_status=metadata_only
model_registry_authority=0
candidate_review_status=operator_review_required
candidate_usable_for_inference=0
model_selection_authority=0
model_install_authority=0
model_load_authority=0
model_weight_inspection_authority=0
registry_promotion_allowed=0
nadia_stage_10_inference_readiness_contract_present=1
inference_readiness_contract_command=scripts/nadia-inference-readiness-contract.sh
installed_inference_readiness_contract_command=latticra-nadia inference-readiness
inference_readiness_stage=contract-only
inference_readiness_contract_status=contract_only
inference_readiness_authority=0
inference_ready=0
readiness_decision=blocked_contract_only
runtime_invocation_authority=0
token_generation_authority=0
model_session_authority=0
inference_authority=0
runtime_invoked=0
readiness_promotion_allowed=0
nadia_stage_11_runtime_invocation_contract_present=1
runtime_invocation_contract_command=scripts/nadia-runtime-invocation-contract.sh
installed_runtime_invocation_contract_command=latticra-nadia runtime-invocation
runtime_invocation_stage=contract-only
runtime_invocation_contract_status=contract_only
runtime_invocation_authority=0
runtime_invocation_allowed=0
invocation_decision=blocked_contract_only
runtime_process_spawn_authority=0
runtime_binary_execution_authority=0
runtime_session_authority=0
runtime_process_spawned=0
runtime_binary_executed=0
runtime_session_created=0
token_generation_performed=0
invocation_promotion_allowed=0
nadia_stage_12_model_load_contract_present=1
model_load_contract_command=scripts/nadia-model-load-contract.sh
installed_model_load_contract_command=latticra-nadia model-load
model_load_stage=contract-only
model_load_contract_status=contract_only
model_load_authority=0
model_load_allowed=0
model_loaded=0
load_decision=blocked_contract_only
model_file_open_authority=0
model_weight_mapping_authority=0
model_weight_verification_authority=0
model_file_opened=0
model_memory_map_created=0
model_weights_mapped=0
model_weights_loaded=0
model_load_performed=0
load_promotion_allowed=0
nadia_stage_13_prompt_receipt_contract_present=1
prompt_receipt_contract_command=scripts/nadia-prompt-receipt-contract.sh
installed_prompt_receipt_contract_command=latticra-nadia prompt-receipt
prompt_receipt_stage=contract-only
prompt_receipt_contract_status=contract_only
prompt_receipt_authority=0
prompt_receipt_allowed=0
prompt_received=0
receipt_decision=blocked_contract_only
prompt_source_open_authority=0
prompt_source_read_authority=0
prompt_source_opened=0
prompt_source_read=0
prompt_bytes_read=0
prompt_text_received=0
prompt_text_materialized=0
prompt_content_stored=0
prompt_evaluation_authority=0
prompt_evaluated=0
nadia_stage_14_prompt_materialization_contract_present=1
prompt_materialization_contract_command=scripts/nadia-prompt-materialization-contract.sh
installed_prompt_materialization_contract_command=latticra-nadia prompt-materialization
prompt_materialization_stage=contract-only
prompt_materialization_contract_status=contract_only
prompt_materialization_authority=0
prompt_materialization_allowed=0
prompt_materialized=0
materialization_decision=blocked_contract_only
prompt_materialization_promotion_allowed=0
prompt_buffer_allocation_authority=0
prompt_buffer_write_authority=0
prompt_tokenization_authority=0
prompt_materialization_performed=0
prompt_buffer_allocated=0
prompt_buffer_written=0
prompt_bytes_materialized=0
prompt_tokens_created=0
prompt_tokenized=0
nadia_stage_15_awareness_dialogue_contract_present=1
awareness_dialogue_contract_command=scripts/nadia-awareness-dialogue-contract.sh
installed_awareness_dialogue_contract_command=latticra-nadia awareness-dialogue
future_qa_dialogue_capability_planned=1
awareness_dialogue_stage=contract-only
awareness_dialogue_contract_status=contract_only
awareness_dialogue_authority=0
awareness_dialogue_allowed=0
dialogue_generation_authority=0
qa_dialogue_generated=0
dialogue_scope=official-nadia-initiative-awareness-work
dialogue_format=question-and-answer
q_and_a_format_required=1
survivor_centered_dialogue_required=1
official_source_grounding_required=1
live_web_lookup_authority=0
topic_yazidi_genocide_awareness=1
topic_survivor_voice_and_dignity=1
topic_conflict_related_sexual_violence_awareness_non_graphic=1
topic_genocide_prevention=1
topic_justice_and_accountability=1
topic_sinjar_reconstruction=1
topic_womens_empowerment=1
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
nadia_stage_16_prompt_evaluation_handoff_contract_present=1
prompt_evaluation_handoff_contract_command=scripts/nadia-prompt-evaluation-handoff-contract.sh
installed_prompt_evaluation_handoff_contract_command=latticra-nadia prompt-evaluation-handoff
prompt_evaluation_handoff_stage=contract-only
prompt_evaluation_handoff_contract_status=contract_only
prompt_evaluation_handoff_authority=0
prompt_evaluation_handoff_allowed=0
prompt_evaluation_handoff_performed=0
evaluation_handoff_decision=blocked_contract_only
requires_awareness_dialogue_contract=1
requires_future_tokenization_contract=1
prompt_evaluation_handoff_promotion_allowed=0
nadia_stage_17_tokenization_boundary_contract_present=1
tokenization_boundary_contract_command=scripts/nadia-tokenization-boundary-contract.sh
installed_tokenization_boundary_contract_command=latticra-nadia tokenization-boundary
tokenization_boundary_stage=contract-only
tokenization_boundary_contract_status=contract_only
tokenization_boundary_authority=0
tokenization_boundary_allowed=0
tokenization_boundary_performed=0
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenized=0
prompt_tokens_created=0
tokenizer_file_opened=0
tokenizer_vocab_loaded=0
tokenization_decision=blocked_contract_only
requires_prompt_evaluation_handoff_contract=1
requires_future_tokenizer_specification_contract=1
tokenization_boundary_promotion_allowed=0
nadia_stage_18_tokenizer_specification_contract_present=1
tokenizer_specification_contract_command=scripts/nadia-tokenizer-specification-contract.sh
installed_tokenizer_specification_contract_command=latticra-nadia tokenizer-specification
tokenizer_specification_stage=contract-only
tokenizer_specification_contract_status=contract_only
tokenizer_specification_authority=0
tokenizer_specification_allowed=0
tokenizer_specification_performed=0
tokenizer_specification_metadata_present=1
tokenizer_family=model-compatible-tokenizer
tokenizer_format=operator-reviewed-offline-specification
tokenizer_specification_decision=blocked_contract_only
tokenizer_path_recorded=0
tokenizer_manifest_loaded=0
requires_tokenization_boundary_contract=1
requires_future_tokenizer_manifest_contract=1
tokenizer_specification_promotion_allowed=0
nadia_stage_19_tokenizer_manifest_contract_present=1
tokenizer_manifest_contract_command=scripts/nadia-tokenizer-manifest-contract.sh
installed_tokenizer_manifest_contract_command=latticra-nadia tokenizer-manifest
tokenizer_manifest_stage=contract-only
tokenizer_manifest_contract_status=contract_only
tokenizer_manifest_authority=0
tokenizer_manifest_allowed=0
tokenizer_manifest_performed=0
tokenizer_manifest_metadata_present=1
tokenizer_manifest_family=operator-reviewed-tokenizer-manifest
tokenizer_manifest_format=contract-only-offline-manifest
tokenizer_manifest_decision=blocked_contract_only
tokenizer_manifest_path_recorded=0
tokenizer_manifest_schema_planned=1
tokenizer_manifest_opened=0
tokenizer_manifest_read=0
tokenizer_manifest_parsed=0
tokenizer_manifest_validated=0
tokenizer_manifest_loaded=0
requires_tokenizer_specification_contract=1
requires_future_tokenizer_artifact_inventory_contract=1
tokenizer_manifest_promotion_allowed=0
nadia_stage_20_tokenizer_artifact_inventory_contract_present=1
tokenizer_artifact_inventory_contract_command=scripts/nadia-tokenizer-artifact-inventory-contract.sh
installed_tokenizer_artifact_inventory_contract_command=latticra-nadia tokenizer-artifact-inventory
tokenizer_artifact_inventory_stage=contract-only
tokenizer_artifact_inventory_contract_status=contract_only
tokenizer_artifact_inventory_authority=0
tokenizer_artifact_inventory_allowed=0
tokenizer_artifact_inventory_performed=0
tokenizer_artifact_inventory_metadata_present=1
tokenizer_artifact_inventory_family=operator-reviewed-tokenizer-artifact-inventory
tokenizer_artifact_inventory_format=contract-only-offline-inventory
tokenizer_artifact_inventory_decision=blocked_contract_only
tokenizer_artifact_inventory_path_recorded=0
tokenizer_artifact_inventory_schema_planned=1
tokenizer_artifact_inventory_entry_count=0
tokenizer_artifact_inventory_file_count=0
tokenizer_artifact_path_resolved=0
tokenizer_artifact_scan_performed=0
tokenizer_artifact_stat_performed=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_hash_computed=0
tokenizer_artifact_measurement_performed=0
requires_tokenizer_manifest_contract=1
requires_future_tokenizer_artifact_measurement_contract=1
tokenizer_artifact_inventory_promotion_allowed=0
nadia_stage_21_tokenizer_artifact_measurement_contract_present=1
tokenizer_artifact_measurement_contract_command=scripts/nadia-tokenizer-artifact-measurement-contract.sh
installed_tokenizer_artifact_measurement_contract_command=latticra-nadia tokenizer-artifact-measurement
tokenizer_artifact_measurement_stage=contract-only
tokenizer_artifact_measurement_contract_status=contract_only
tokenizer_artifact_measurement_authority=0
tokenizer_artifact_measurement_allowed=0
tokenizer_artifact_measurement_performed=0
tokenizer_artifact_measurement_metadata_present=1
tokenizer_artifact_measurement_family=operator-reviewed-tokenizer-artifact-measurement
tokenizer_artifact_measurement_format=contract-only-offline-measurement
tokenizer_artifact_measurement_decision=blocked_contract_only
tokenizer_artifact_measurement_plan_recorded=1
tokenizer_artifact_measurement_result_recorded=0
tokenizer_artifact_measurement_digest_recorded=0
tokenizer_artifact_measurement_size_recorded=0
tokenizer_artifact_measurement_hash_computed=0
tokenizer_artifact_digest_recorded=0
tokenizer_artifact_size_recorded=0
requires_tokenizer_artifact_inventory_contract=1
requires_future_tokenizer_artifact_verification_contract=1
tokenizer_artifact_measurement_promotion_allowed=0
nadia_stage_22_tokenizer_artifact_verification_contract_present=1
tokenizer_artifact_verification_contract_command=scripts/nadia-tokenizer-artifact-verification-contract.sh
installed_tokenizer_artifact_verification_contract_command=latticra-nadia tokenizer-artifact-verification
tokenizer_artifact_verification_stage=contract-only
tokenizer_artifact_verification_contract_status=contract_only
tokenizer_artifact_verification_authority=0
tokenizer_artifact_verification_allowed=0
tokenizer_artifact_verification_performed=0
tokenizer_artifact_verification_metadata_present=1
tokenizer_artifact_verification_family=operator-reviewed-tokenizer-artifact-verification
tokenizer_artifact_verification_format=contract-only-offline-verification
tokenizer_artifact_verification_decision=blocked_contract_only
tokenizer_artifact_verification_plan_recorded=1
tokenizer_artifact_verification_comparison_performed=0
tokenizer_artifact_verification_result_recorded=0
tokenizer_artifact_verification_digest_match_recorded=0
tokenizer_artifact_verification_size_match_recorded=0
tokenizer_artifact_verification_hash_computed=0
requires_tokenizer_artifact_measurement_contract=1
requires_future_tokenizer_artifact_binding_contract=1
tokenizer_artifact_verification_promotion_allowed=0
nadia_stage_23_tokenizer_artifact_binding_contract_present=1
tokenizer_artifact_binding_contract_command=scripts/nadia-tokenizer-artifact-binding-contract.sh
installed_tokenizer_artifact_binding_contract_command=latticra-nadia tokenizer-artifact-binding
tokenizer_artifact_binding_stage=contract-only
tokenizer_artifact_binding_contract_status=contract_only
tokenizer_artifact_binding_authority=0
tokenizer_artifact_binding_allowed=0
tokenizer_artifact_binding_performed=0
tokenizer_artifact_binding_metadata_present=1
tokenizer_artifact_binding_family=operator-reviewed-tokenizer-artifact-binding
tokenizer_artifact_binding_format=contract-only-offline-binding
tokenizer_artifact_binding_decision=blocked_contract_only
tokenizer_artifact_binding_plan_recorded=1
tokenizer_artifact_binding_result_recorded=0
tokenizer_artifact_binding_record_created=0
tokenizer_artifact_binding_hash_computed=0
tokenizer_artifact_binding_bound=0
tokenizer_artifact_binding_runtime_attachment_performed=0
tokenizer_artifact_bound_to_manifest=0
tokenizer_artifact_bound_to_tokenizer=0
tokenizer_attached_to_runtime=0
requires_tokenizer_artifact_verification_contract=1
requires_future_tokenizer_runtime_attachment_contract=1
tokenizer_artifact_binding_promotion_allowed=0
nadia_stage_24_tokenizer_runtime_attachment_contract_present=1
tokenizer_runtime_attachment_contract_command=scripts/nadia-tokenizer-runtime-attachment-contract.sh
installed_tokenizer_runtime_attachment_contract_command=latticra-nadia tokenizer-runtime-attachment
tokenizer_runtime_attachment_stage=contract-only
tokenizer_runtime_attachment_contract_status=contract_only
tokenizer_runtime_attachment_authority=0
tokenizer_runtime_attachment_allowed=0
tokenizer_runtime_attachment_performed=0
tokenizer_runtime_attachment_metadata_present=1
tokenizer_runtime_attachment_family=operator-reviewed-tokenizer-runtime-attachment
tokenizer_runtime_attachment_format=contract-only-offline-attachment
tokenizer_runtime_attachment_decision=blocked_contract_only
tokenizer_runtime_attachment_plan_recorded=1
tokenizer_runtime_attachment_result_recorded=0
tokenizer_runtime_attachment_record_created=0
tokenizer_runtime_attachment_attached=0
tokenizer_runtime_attachment_runtime_invoked=0
tokenizer_runtime_attachment_session_created=0
runtime_session_created=0
runtime_invoked=0
requires_tokenizer_artifact_binding_contract=1
requires_future_prompt_tokenization_contract=1
tokenizer_runtime_attachment_promotion_allowed=0
nadia_stage_25_prompt_tokenization_contract_present=1
prompt_tokenization_contract_command=scripts/nadia-prompt-tokenization-contract.sh
installed_prompt_tokenization_contract_command=latticra-nadia prompt-tokenization
prompt_tokenization_stage=contract-only
prompt_tokenization_contract_status=contract_only
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenization_performed=0
prompt_tokenization_metadata_present=1
prompt_tokenization_family=operator-reviewed-prompt-tokenization
prompt_tokenization_format=contract-only-offline-tokenization
prompt_tokenization_decision=blocked_contract_only
prompt_tokenization_plan_recorded=1
prompt_tokenization_result_recorded=0
prompt_tokens_created=0
prompt_token_count_recorded=0
prompt_token_sequence_recorded=0
prompt_token_buffer_created=0
prompt_tokenization_runtime_invoked=0
prompt_tokenized=0
requires_tokenizer_runtime_attachment_contract=1
requires_future_prompt_token_sequence_contract=1
prompt_tokenization_promotion_allowed=0
nadia_stage_26_prompt_token_sequence_contract_present=1
prompt_token_sequence_contract_command=scripts/nadia-prompt-token-sequence-contract.sh
installed_prompt_token_sequence_contract_command=latticra-nadia prompt-token-sequence
prompt_token_sequence_stage=contract-only
prompt_token_sequence_contract_status=contract_only
prompt_token_sequence_authority=0
prompt_token_sequence_allowed=0
prompt_token_sequence_recorded=0
prompt_token_sequence_metadata_present=1
prompt_token_sequence_family=operator-reviewed-prompt-token-sequence
prompt_token_sequence_format=contract-only-offline-sequence
prompt_token_sequence_decision=blocked_contract_only
prompt_token_sequence_plan_recorded=1
prompt_token_sequence_result_recorded=0
prompt_token_sequence_count_recorded=0
prompt_token_sequence_order_recorded=0
prompt_token_ids_recorded=0
prompt_attention_mask_created=0
context_window_assembled=0
prompt_token_sequence_runtime_invoked=0
requires_prompt_tokenization_contract=1
requires_future_context_window_assembly_contract=1
prompt_token_sequence_promotion_allowed=0
nadia_stage_27_context_window_assembly_contract_present=1
context_window_assembly_contract_command=scripts/nadia-context-window-assembly-contract.sh
installed_context_window_assembly_contract_command=latticra-nadia context-window-assembly
context_window_assembly_stage=contract-only
context_window_assembly_contract_status=contract_only
context_window_assembly_authority=0
context_window_assembly_allowed=0
context_window_assembly_performed=0
context_window_assembly_metadata_present=1
context_window_family=operator-reviewed-context-window-assembly
context_window_format=contract-only-offline-context-window
context_window_assembly_decision=blocked_contract_only
context_window_assembly_plan_recorded=1
context_window_assembly_result_recorded=0
context_window_assembly_runtime_invoked=0
context_window_assembled=0
context_window_token_budget_recorded=0
prompt_evaluation_input_created=0
requires_prompt_token_sequence_contract=1
requires_future_prompt_evaluation_input_contract=1
context_window_assembly_promotion_allowed=0
nadia_stage_28_prompt_evaluation_input_contract_present=1
prompt_evaluation_input_contract_command=scripts/nadia-prompt-evaluation-input-contract.sh
installed_prompt_evaluation_input_contract_command=latticra-nadia prompt-evaluation-input
prompt_evaluation_input_stage=contract-only
prompt_evaluation_input_contract_status=contract_only
prompt_evaluation_input_authority=0
prompt_evaluation_input_allowed=0
prompt_evaluation_input_created=0
prompt_evaluation_input_metadata_present=1
prompt_evaluation_input_family=operator-reviewed-prompt-evaluation-input
prompt_evaluation_input_format=contract-only-offline-evaluation-input
prompt_evaluation_input_decision=blocked_contract_only
prompt_evaluation_input_plan_recorded=1
prompt_evaluation_input_result_recorded=0
prompt_evaluation_input_runtime_invoked=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_serialized=0
prompt_evaluation_input_written=0
requires_context_window_assembly_contract=1
requires_future_prompt_evaluation_runtime_handoff_contract=1
prompt_evaluation_input_promotion_allowed=0
nadia_stage_29_prompt_evaluation_runtime_handoff_contract_present=1
prompt_evaluation_runtime_handoff_contract_command=scripts/nadia-prompt-evaluation-runtime-handoff-contract.sh
installed_prompt_evaluation_runtime_handoff_contract_command=latticra-nadia prompt-evaluation-runtime-handoff
prompt_evaluation_runtime_handoff_stage=contract-only
prompt_evaluation_runtime_handoff_contract_status=contract_only
prompt_evaluation_runtime_handoff_authority=0
prompt_evaluation_runtime_handoff_allowed=0
prompt_evaluation_runtime_handoff_performed=0
prompt_evaluation_runtime_handoff_metadata_present=1
prompt_evaluation_runtime_handoff_family=operator-reviewed-prompt-evaluation-runtime-handoff
prompt_evaluation_runtime_handoff_format=contract-only-offline-runtime-handoff
prompt_evaluation_runtime_handoff_decision=blocked_contract_only
prompt_evaluation_runtime_handoff_plan_recorded=1
prompt_evaluation_runtime_handoff_result_recorded=0
prompt_evaluation_runtime_handoff_runtime_invoked=0
prompt_evaluation_runtime_handoff_request_created=0
prompt_evaluation_runtime_handoff_request_submitted=0
runtime_handoff_created=0
runtime_invocation_requested=0
requires_prompt_evaluation_input_contract=1
requires_future_prompt_evaluation_invocation_contract=1
prompt_evaluation_runtime_handoff_promotion_allowed=0
local_file_read_for_indexing=operator_invoked
offline_by_default=1
panel_install_surface_present=1
console_status_surface_present=1
human_dignity_principle=1
community_awareness_posture=1
model_runtime_present=0
model_runtime_invoked=0
model_weights_installed=0
model_weights_loaded=0
model_weights_downloaded=0
network_authority=0
tool_execution_authority=0
source_mutation_authority=0
self_modification_authority=0
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
```

From the repository:

```sh
sh scripts/nadia-context-pack.sh --repo . --output /private/tmp/latticra-nadia-context
```

After a guarded local install with Nadia enabled:

```sh
latticra-nadia context-pack
latticra-nadia runtime-profile
latticra-nadia prompt-plan
latticra-nadia mode-validate
latticra-nadia productivity-ledger
latticra-nadia protective-safety
latticra-nadia tool-preflight
latticra-nadia prompt-contract
latticra-nadia model-registry
latticra-nadia inference-readiness
latticra-nadia runtime-invocation
latticra-nadia model-load
latticra-nadia prompt-receipt
latticra-nadia prompt-materialization
latticra-nadia awareness-dialogue
latticra-nadia prompt-evaluation-handoff
latticra-nadia tokenization-boundary
latticra-nadia tokenizer-specification
latticra-nadia tokenizer-manifest
latticra-nadia tokenizer-artifact-inventory
latticra-nadia tokenizer-artifact-measurement
latticra-nadia tokenizer-artifact-verification
latticra-nadia tokenizer-artifact-binding
latticra-nadia tokenizer-runtime-attachment
latticra-nadia prompt-tokenization
latticra-nadia prompt-token-sequence
latticra-nadia context-window-assembly
latticra-nadia prompt-evaluation-input
latticra-nadia prompt-evaluation-runtime-handoff
```

See [`docs/NADIA_OFFLINE_AI_FOUNDATION.md`](docs/NADIA_OFFLINE_AI_FOUNDATION.md), [`docs/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md`](docs/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md), [`docs/NADIA_RUNTIME_PROFILE_STAGE_2.md`](docs/NADIA_RUNTIME_PROFILE_STAGE_2.md), [`docs/NADIA_DEVELOPER_WORKBENCH_STAGE_3.md`](docs/NADIA_DEVELOPER_WORKBENCH_STAGE_3.md), [`docs/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4.md`](docs/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4.md), [`docs/NADIA_PRODUCTIVITY_LOOP_STAGE_5.md`](docs/NADIA_PRODUCTIVITY_LOOP_STAGE_5.md), [`docs/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6.md`](docs/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6.md), [`docs/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md`](docs/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md), [`docs/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8.md`](docs/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8.md), [`docs/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9.md`](docs/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9.md), [`docs/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10.md`](docs/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10.md), [`docs/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11.md`](docs/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11.md), [`docs/NADIA_MODEL_LOAD_CONTRACT_STAGE_12.md`](docs/NADIA_MODEL_LOAD_CONTRACT_STAGE_12.md), [`docs/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13.md`](docs/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13.md), [`docs/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14.md`](docs/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14.md), [`docs/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15.md`](docs/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15.md), [`docs/NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16.md`](docs/NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16.md), [`docs/NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17.md`](docs/NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17.md), [`docs/NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18.md`](docs/NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18.md), [`docs/NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19.md`](docs/NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19.md), [`docs/NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20.md`](docs/NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20.md), [`docs/NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21.md`](docs/NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21.md), [`docs/NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22.md`](docs/NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22.md), [`docs/NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23.md`](docs/NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23.md), [`docs/status/NADIA_OFFLINE_AI_STAGE_0_STATUS.md`](docs/status/NADIA_OFFLINE_AI_STAGE_0_STATUS.md), [`docs/status/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1_STATUS.md`](docs/status/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1_STATUS.md), [`docs/status/NADIA_RUNTIME_PROFILE_STAGE_2_STATUS.md`](docs/status/NADIA_RUNTIME_PROFILE_STAGE_2_STATUS.md), [`docs/status/NADIA_DEVELOPER_WORKBENCH_STAGE_3_STATUS.md`](docs/status/NADIA_DEVELOPER_WORKBENCH_STAGE_3_STATUS.md), [`docs/status/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4_STATUS.md`](docs/status/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4_STATUS.md), [`docs/status/NADIA_PRODUCTIVITY_LOOP_STAGE_5_STATUS.md`](docs/status/NADIA_PRODUCTIVITY_LOOP_STAGE_5_STATUS.md), [`docs/status/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6_STATUS.md`](docs/status/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6_STATUS.md), [`docs/status/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7_STATUS.md`](docs/status/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7_STATUS.md), [`docs/status/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8_STATUS.md`](docs/status/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8_STATUS.md), [`docs/status/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9_STATUS.md`](docs/status/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9_STATUS.md), [`docs/status/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10_STATUS.md`](docs/status/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10_STATUS.md), [`docs/status/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11_STATUS.md`](docs/status/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11_STATUS.md), [`docs/status/NADIA_MODEL_LOAD_CONTRACT_STAGE_12_STATUS.md`](docs/status/NADIA_MODEL_LOAD_CONTRACT_STAGE_12_STATUS.md), [`docs/status/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13_STATUS.md`](docs/status/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13_STATUS.md), [`docs/status/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14_STATUS.md`](docs/status/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14_STATUS.md), [`docs/status/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15_STATUS.md`](docs/status/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15_STATUS.md), [`docs/status/NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16_STATUS.md`](docs/status/NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT_STAGE_16_STATUS.md), [`docs/status/NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17_STATUS.md`](docs/status/NADIA_TOKENIZATION_BOUNDARY_CONTRACT_STAGE_17_STATUS.md), [`docs/status/NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18_STATUS.md`](docs/status/NADIA_TOKENIZER_SPECIFICATION_CONTRACT_STAGE_18_STATUS.md), [`docs/status/NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19_STATUS.md`](docs/status/NADIA_TOKENIZER_MANIFEST_CONTRACT_STAGE_19_STATUS.md), [`docs/status/NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20_STATUS.md`](docs/status/NADIA_TOKENIZER_ARTIFACT_INVENTORY_CONTRACT_STAGE_20_STATUS.md), [`docs/status/NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21_STATUS.md`](docs/status/NADIA_TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STAGE_21_STATUS.md), [`docs/status/NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22_STATUS.md`](docs/status/NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT_STAGE_22_STATUS.md), and [`docs/status/NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23_STATUS.md`](docs/status/NADIA_TOKENIZER_ARTIFACT_BINDING_CONTRACT_STAGE_23_STATUS.md).

Current Nadia continuation docs: [`docs/NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24.md`](docs/NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24.md), [`docs/NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25.md`](docs/NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25.md), [`docs/NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26.md`](docs/NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26.md), [`docs/NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27.md`](docs/NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27.md), [`docs/NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28.md`](docs/NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28.md), [`docs/NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29.md`](docs/NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29.md), [`docs/status/NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24_STATUS.md`](docs/status/NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT_STAGE_24_STATUS.md), [`docs/status/NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25_STATUS.md`](docs/status/NADIA_PROMPT_TOKENIZATION_CONTRACT_STAGE_25_STATUS.md), [`docs/status/NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26_STATUS.md`](docs/status/NADIA_PROMPT_TOKEN_SEQUENCE_CONTRACT_STAGE_26_STATUS.md), [`docs/status/NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27_STATUS.md`](docs/status/NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STAGE_27_STATUS.md), [`docs/status/NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28_STATUS.md`](docs/status/NADIA_PROMPT_EVALUATION_INPUT_CONTRACT_STAGE_28_STATUS.md), and [`docs/status/NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29_STATUS.md`](docs/status/NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29_STATUS.md).

---

## Lat, LIR, and L-UI

Lat is the Latticra language direction.

The current Lat path is no-effect and metadata-oriented. It gives the project a bounded path from grammar parsing to semantic validation to model normalization to LIR metadata lowering.

Current posture:

```text
lat_parser_present=1
lat_semantic_validation_present=1
lat_diagnostics_present=1
lat_model_normalization_present=1
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
- [`docs/LAT_MODEL_NORMALIZATION_IMPLEMENTATION.md`](docs/LAT_MODEL_NORMALIZATION_IMPLEMENTATION.md)
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
runtime_boundary_policy_expansion_after_threat_model_present=1
runtime_boundary_abuse_case_fixture_expansion_present=1
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
- [`docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md`](docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md)
- [`docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md`](docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md)
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
seal_agentic_automation_security_metadata_present=1
seal_agentic_automation_security_status_present=1
seal_agentic_automation_security_index_alignment_present=1
seal_agentic_automation_security_report_surface_present=1
seal_agentic_automation_security_public_entrypoint_alignment_present=1
seal_parameter_schema_contract_present=1
seal_parameter_schema_metadata_present=1
seal_parameter_schema_report_surface_present=1
seal_parameter_schema_status_present=1
seal_request_freshness_contract_present=1
seal_request_freshness_metadata_present=1
seal_request_freshness_report_surface_present=1
seal_request_freshness_status_present=1
seal_signed_request_contract_present=1
seal_signed_request_metadata_present=1
seal_signed_request_status_present=1
seal_policy_decision_contract_present=1
seal_policy_decision_metadata_present=1
seal_policy_decision_report_surface_present=1
seal_policy_decision_report_surface_status_present=1
seal_policy_decision_status_present=1
seal_policy_decision_report_surface_status_present=1
seal_policy_decision_public_entrypoint_alignment_present=1
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
seal_signer_invocation_contract_present=1
seal_signer_invocation_metadata_present=1
seal_signer_invocation_status_present=1
seal_signing_operation_contract_present=1
seal_signing_operation_metadata_present=1
seal_signing_operation_status_present=1
seal_key_handling_contract_present=1
seal_key_handling_metadata_present=1
seal_key_handling_status_present=1
seal_key_material_contract_present=1
seal_key_material_metadata_present=1
seal_key_material_status_present=1
seal_public_key_parsing_contract_present=1
seal_public_key_parsing_metadata_present=1
seal_public_key_parsing_status_present=1
seal_future_key_parsing_implementation_contract_present=1
seal_future_key_parsing_implementation_plan_present=1
seal_key_parsing_metadata_present=1
seal_key_parsing_status_present=1
seal_verification_policy_metadata_present=1
seal_verification_policy_status_present=1
seal_crypto_verify_backend_contract_present=1
seal_crypto_verify_backend_metadata_present=1
seal_crypto_verify_backend_status_present=1
crypto_verify_state=unsupported
cryptographic_verification_supported=0
cryptographic_verification_performed=0
verified=0
authority_usable=0
capability_gate_allowed=0
seal_ed25519_verify_only_contract_present=1
seal_ed25519_verify_implementation_present=1
seal_ed25519_verify_metadata_present=1
seal_ed25519_verify_status_present=1
ed25519_verify_profile=latticra-seal-ed25519-verify/0.1
ed25519_verify_state=verified
ed25519_cryptographic_verification_supported=1
ed25519_cryptographic_verification_performed=1
ed25519_verified=1
ed25519_authority_usable=0
ed25519_capability_gate_allowed=0
ed25519_runtime_authority_granted=0
seal_verified_receipt_promotion_contract_present=1
seal_verified_receipt_promotion_implementation_present=1
seal_verified_receipt_promotion_status_present=1
verified_receipt_promotion_state=verified
verified_receipt_promotion_cryptographic_verification_performed=1
verified_receipt_promotion_verified=1
verified_receipt_promotion_authority_usable=0
verified_receipt_promotion_capability_gate_allowed=0
verified_receipt_promotion_runtime_authority_granted=0
seal_verified_capability_gate_contract_present=1
seal_verified_capability_gate_implementation_present=1
seal_verified_capability_gate_status_present=1
verified_capability_gate_profile=latticra-seal-verified-capability-gate/0.1
verified_capability_gate_allowed=1
verified_capability_gate_state=allowed-metadata-only
verified_capability_gate_runtime_authority_granted=0
verified_capability_gate_effect_performed=0
verified_capability_gate_host_read_performed=0
verified_capability_gate_host_write_performed=0
verified_capability_gate_network_performed=0
seal_verification_receipt_metadata_present=1
seal_verification_receipt_status_present=1
seal_capability_gate_metadata_present=1
seal_capability_gate_status_present=1
seal_effect_decision_metadata_present=1
seal_effect_decision_status_present=1
seal_runtime_handoff_metadata_present=1
seal_runtime_handoff_status_present=1
seal_status_rollup_metadata_present=1
seal_status_rollup_status_present=1
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

The signer invocation contract defines the next metadata-only classification boundary after signer handoff readiness. It does not add signing, verification, signer invocation behavior, private-key handling, host behavior, network behavior, capability enforcement, or runtime authority.

The signer invocation metadata implementation classifies ready signer handoff metadata as invocation-metadata-only for a future signer path while preserving no signing, verification, signer invocation behavior, private-key handling, host behavior, network behavior, capability enforcement, or runtime authority.

The signer invocation status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The signing operation metadata implementation classifies ready signer invocation metadata into a metadata-only signing-operation eligibility record. It does not add signing, verification, signer invocation behavior, private-key handling, host behavior, network behavior, capability enforcement, or runtime authority.

The signing operation status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The key-handling metadata implementation classifies ready signing operation metadata into a metadata-only key-handling eligibility record. It does not add public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust-store behavior, signing, verification, signer invocation behavior, host behavior, network behavior, capability enforcement, or runtime authority.

The key-handling status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The key-material boundary contract defines the metadata-only classification boundary after key-handling readiness. It does not add public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust-store behavior, signing, verification, signer invocation behavior, host behavior, network behavior, capability enforcement, or runtime authority.

The key-material metadata implementation classifies ready key-handling metadata into a metadata-only key-material eligibility record. It does not add public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust-store behavior, signing, verification, signer invocation behavior, host behavior, network behavior, capability enforcement, or runtime authority.

The key-material status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The public-key parsing boundary contract defines the next metadata-only classification boundary after key-material status readiness. It does not add public-key parsing, key material loading, private-key handling, key generation, hardware-key use, trust-store behavior, signing, verification, signer invocation behavior, host behavior, network behavior, capability enforcement, or runtime authority.

The public-key parsing metadata implementation classifies ready key-material metadata into a metadata-only public-key parsing eligibility record. It still parses no public keys, loads no key material, handles no private keys, performs no signing or verification, invokes no signer, touches no host or network behavior, enforces no capability, and grants no runtime authority.

The public-key parsing status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The future key parsing implementation contract defines the next planning boundary after public-key parsing status readiness. It adds no parser, loads no key material, handles no private keys, performs no signing or verification, invokes no signer, touches no host or network behavior, enforces no capability, and grants no runtime authority.

The future key parsing implementation plan names a later bounded no-effect key parsing surface for caller-provided public-key bytes only. It still adds no parser code in this slice, loads no key material, handles no private keys, performs no signing or verification, reads no host files, uses no network, and grants no runtime authority.

The bounded key parsing metadata implementation now accepts caller-provided Ed25519 public-key bytes in raw 32-byte or ASCII hex 64-byte form, records deterministic metadata with `public_key_parsed=1`, and keeps key material loading, private-key handling, signing, verification, trust-store behavior, host behavior, network behavior, capability enforcement, and runtime authority at zero.

The key parsing status record makes that bounded public-key byte metadata checkpoint visible from the public entry points without changing implementation behavior.

The verification policy metadata implementation records unsupported verification-policy posture from existing signature metadata and a caller-provided public-key identity label. It does not perform cryptographic verification, consume public-key bytes, load key material, handle private keys, query trust stores or revocation sources, touch host or network behavior, enforce capabilities, or grant runtime authority.

The verification policy status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The crypto verify backend metadata implementation records an unsupported backend posture from verification policy metadata. It does not perform cryptographic verification, parse public keys, load key material, handle private keys, query trust stores or revocation sources, touch host or network behavior, enforce capabilities, or grant runtime authority.

The crypto verify backend status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The Ed25519 verify-only implementation performs local provider-backed verification over caller-supplied message bytes, public-key bytes, and signature bytes. A successful verify-only result records `crypto_verify_state=verified`, `cryptographic_verification_performed=1`, and `verified=1`, while keeping authority, capability-gate allowance, runtime authority, signing, key generation, private-key handling, host behavior, and network behavior at zero.

The Ed25519 verify status record makes that local verify-only checkpoint visible from the public entry points without changing implementation behavior or claiming production cryptography.

The verified receipt promotion metadata implementation promotes a successful Ed25519 verify-only result into deterministic verified receipt metadata. The promoted receipt records `receipt_state=verified`, `cryptographic_verification_performed=1`, and `verified=1`, while keeping authority, capability-gate allowance, runtime authority, signing, key generation, private-key handling, host behavior, and network behavior at zero.

The verified receipt promotion status record makes that authority-neutral promotion checkpoint visible from the public entry points without changing implementation behavior.

The verified capability gate metadata implementation evaluates verified receipt metadata against a narrow local report/evaluate-only allowlist. It can record `gate_allowed=1` for metadata-only requests while keeping runtime authority, effect execution, host reads, host writes, and network behavior at zero.

The verified capability gate status record makes that metadata-only gate checkpoint visible from the public entry points without changing implementation behavior or adding capability enforcement.

The verification receipt metadata implementation records unverified receipt metadata from the verification policy posture. It does not perform cryptographic verification, assert verified receipt authority, authorize capability gates, load key material, handle private keys, query trust stores or revocation sources, touch host or network behavior, enforce capabilities, or grant runtime authority.

The verification receipt status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The capability gate metadata implementation records denied-by-default capability gate posture from unverified receipt metadata. It does not enforce capabilities, perform effects, verify signatures, assert verified receipt authority, touch host or network behavior, or grant runtime authority.

The capability gate status record makes that metadata-only denied checkpoint visible from the public entry points without changing implementation behavior.

The effect decision metadata implementation records denied-by-gate effect decision posture from capability gate metadata. It does not perform effects, enforce capabilities, touch host or network behavior, run a runtime handoff, or grant runtime authority.

The effect decision status record makes that metadata-only denied checkpoint visible from the public entry points without changing implementation behavior.

The runtime handoff metadata implementation records inactive runtime handoff posture from denied effect decision metadata. It does not execute runtime behavior, perform effects, touch host or network behavior, enforce capabilities, or grant runtime authority.

The runtime handoff status record makes that inactive metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The status rollup metadata implementation summarizes the implemented Seal chain after inactive runtime handoff metadata. It does not verify signatures, enforce capabilities, perform effects, touch host or network behavior, or grant runtime authority.

The status rollup status record makes that metadata-only rollup checkpoint visible from the public entry points without changing implementation behavior.

The agentic automation security metadata implementation records report-only AI-era/local automation posture after status rollup metadata. It does not implement MCP protocol behavior, MCP server behavior, MCP client behavior, AI-agent execution, model execution, tool execution, shell execution, host behavior, network behavior, capability enforcement, cryptographic verification, or runtime authority.

The agentic automation security public-entrypoint alignment makes that report-only agentic automation security metadata and its operator-visible deterministic agentic automation security report surface visible from public entry points without changing implementation behavior.

The parameter schema metadata implementation records report-only declared parameter-schema posture after the agentic automation security layer. It does not parse schemas, validate schemas, implement schema languages, execute tools, execute shell commands, touch host behavior, touch network behavior, enforce capabilities, perform cryptographic verification, or grant runtime authority.

The parameter schema status record makes that report-only parameter schema metadata and its operator-visible deterministic parameter schema report surface visible from public entry points without changing implementation behavior.

The request freshness metadata implementation records report-only freshness/replay posture after the parameter schema layer. It does not parse timestamps, trust clocks, store nonces, maintain replay caches, hash context or parameters, validate freshness, detect replay, verify signatures, execute tools, touch host behavior, touch network behavior, enforce capabilities, perform cryptographic verification, or grant runtime authority.

The request freshness status record makes that report-only request freshness metadata and its operator-visible deterministic request freshness report surface visible from public entry points without changing implementation behavior.

The signed request metadata implementation records report-only signature posture after request freshness metadata. It does not generate signatures, verify signatures, parse public keys, load trust stores, handle private keys, generate keys, use hardware keys, query revocation sources, perform network trust lookup, enforce signed requests, execute tools, touch host behavior, touch network behavior, enforce capabilities, perform cryptographic verification, or grant runtime authority.

The signed request status record makes that report-only signed request metadata visible from public entry points without changing implementation behavior.

The policy decision metadata implementation records report-only default-deny policy posture after signed request metadata. It does not evaluate real policies, enforce policies, execute runtime behavior, perform effects, touch host behavior, touch network behavior, enforce capabilities, perform cryptographic verification, verify signatures, validate freshness, detect replay, or grant runtime authority.

The policy decision public-entrypoint alignment makes that report-only policy decision metadata and its operator-visible deterministic policy decision report surface visible from public entry points without changing implementation behavior.

That claim is intentionally limited. It does not mean Latticra Seal currently implements production runtime enforcement, policy enforcement, cryptographic key authority, MCP protocol behavior, MCP server behavior, MCP client behavior, AI-agent execution control, host behavior, network behavior, object sealing, key storage, or revocation lookup.

Relevant Seal records:

- [`docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md`](docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md)
- [`docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md`](docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md)
- [`docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md)
- [`docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md`](docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md)
- [`docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_INDEX_ALIGNMENT.md`](docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_INDEX_ALIGNMENT.md)
- [`docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md`](docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md)
- [`docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE_STATUS.md`](docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE_STATUS.md)
- [`docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md`](docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md)
- [`docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md`](docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md)
- [`docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md`](docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md)
- [`docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md`](docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md)
- [`docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md`](docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md)
- [`docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md`](docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md)
- [`docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md`](docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md)
- [`docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md`](docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md)
- [`docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md)
- [`docs/status/SEAL_SIGNED_REQUEST_STATUS.md`](docs/status/SEAL_SIGNED_REQUEST_STATUS.md)
- [`docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md`](docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md`](docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md)
- [`docs/status/SEAL_POLICY_DECISION_STATUS.md`](docs/status/SEAL_POLICY_DECISION_STATUS.md)
- [`docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md`](docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md)
- [`docs/status/SEAL_POLICY_DECISION_PUBLIC_ENTRYPOINT_ALIGNMENT.md`](docs/status/SEAL_POLICY_DECISION_PUBLIC_ENTRYPOINT_ALIGNMENT.md)
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
- [`docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md`](docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md)
- [`docs/LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md`](docs/LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_SIGNING_OPERATION_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_SIGNING_OPERATION_IMPLEMENTATION.md)
- [`docs/status/SEAL_SIGNING_OPERATION_STATUS.md`](docs/status/SEAL_SIGNING_OPERATION_STATUS.md)
- [`docs/LATTICRA_SEAL_KEY_HANDLING_CONTRACT.md`](docs/LATTICRA_SEAL_KEY_HANDLING_CONTRACT.md)
- [`docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md)
- [`docs/status/SEAL_KEY_HANDLING_STATUS.md`](docs/status/SEAL_KEY_HANDLING_STATUS.md)
- [`docs/LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md`](docs/LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md)
- [`docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md)
- [`docs/status/SEAL_KEY_MATERIAL_STATUS.md`](docs/status/SEAL_KEY_MATERIAL_STATUS.md)
- [`docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md`](docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md)
- [`docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md)
- [`docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md`](docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md)
- [`docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_CONTRACT.md`](docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_PLAN.md`](docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_PLAN.md)
- [`docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md)
- [`docs/status/SEAL_KEY_PARSING_STATUS.md`](docs/status/SEAL_KEY_PARSING_STATUS.md)
- [`docs/LATTICRA_SEAL_VERIFICATION_POLICY_CONTRACT.md`](docs/LATTICRA_SEAL_VERIFICATION_POLICY_CONTRACT.md)
- [`docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md)
- [`docs/status/SEAL_VERIFICATION_POLICY_STATUS.md`](docs/status/SEAL_VERIFICATION_POLICY_STATUS.md)
- [`docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md`](docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md)
- [`docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_IMPLEMENTATION.md)
- [`docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md`](docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md)
- [`docs/LATTICRA_SEAL_ED25519_VERIFY_ONLY_CONTRACT.md`](docs/LATTICRA_SEAL_ED25519_VERIFY_ONLY_CONTRACT.md)
- [`docs/LATTICRA_SEAL_ED25519_VERIFY_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_ED25519_VERIFY_IMPLEMENTATION.md)
- [`docs/status/SEAL_ED25519_VERIFY_STATUS.md`](docs/status/SEAL_ED25519_VERIFY_STATUS.md)
- [`docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_CONTRACT.md`](docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_IMPLEMENTATION.md)
- [`docs/status/SEAL_VERIFIED_RECEIPT_PROMOTION_STATUS.md`](docs/status/SEAL_VERIFIED_RECEIPT_PROMOTION_STATUS.md)
- [`docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_CONTRACT.md`](docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_CONTRACT.md)
- [`docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_IMPLEMENTATION.md)
- [`docs/status/SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md`](docs/status/SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md)
- [`docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md`](docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md)
- [`docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md)
- [`docs/status/SEAL_VERIFICATION_RECEIPT_STATUS.md`](docs/status/SEAL_VERIFICATION_RECEIPT_STATUS.md)
- [`docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md`](docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md)
- [`docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md)
- [`docs/status/SEAL_CAPABILITY_GATE_STATUS.md`](docs/status/SEAL_CAPABILITY_GATE_STATUS.md)
- [`docs/LATTICRA_SEAL_EFFECT_DECISION_CONTRACT.md`](docs/LATTICRA_SEAL_EFFECT_DECISION_CONTRACT.md)
- [`docs/LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md)
- [`docs/status/SEAL_EFFECT_DECISION_STATUS.md`](docs/status/SEAL_EFFECT_DECISION_STATUS.md)
- [`docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md`](docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md)
- [`docs/LATTICRA_SEAL_RUNTIME_HANDOFF_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_RUNTIME_HANDOFF_IMPLEMENTATION.md)
- [`docs/status/SEAL_RUNTIME_HANDOFF_STATUS.md`](docs/status/SEAL_RUNTIME_HANDOFF_STATUS.md)
- [`docs/LATTICRA_SEAL_STATUS_ROLLUP_CONTRACT.md`](docs/LATTICRA_SEAL_STATUS_ROLLUP_CONTRACT.md)
- [`docs/LATTICRA_SEAL_STATUS_ROLLUP_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_STATUS_ROLLUP_IMPLEMENTATION.md)
- [`docs/status/SEAL_STATUS_ROLLUP_STATUS.md`](docs/status/SEAL_STATUS_ROLLUP_STATUS.md)
- [`docs/status/SEAL_SIGNER_INVOCATION_STATUS.md`](docs/status/SEAL_SIGNER_INVOCATION_STATUS.md)
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
fedora_vm_cli_payload_validation_status=blocked-pending-real-vm-run
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
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

The manually gated disposable Fedora VM CLI payload validation runner exists, but no reviewed real-VM CLI validation transcript has been accepted yet. The current evidence is runner-readiness only, not host install readiness for the CLI payload.

Relevant Fedora records:

- [`docs/FEDORA_DEVELOPER_WORKFLOW.md`](docs/FEDORA_DEVELOPER_WORKFLOW.md)
- [`docs/FEDORA_PACKAGE_METADATA_PLAN.md`](docs/FEDORA_PACKAGE_METADATA_PLAN.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md)
- [`docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md`](docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md)
- [`docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md`](docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md)
- [`docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md`](docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md)
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

- [`docs/QUICK_START_CHEATSHEET.md`](docs/QUICK_START_CHEATSHEET.md)
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
- [`docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md`](docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md)
- [`docs/DEFENSIVE_THREAT_MODEL_CONTRACT.md`](docs/DEFENSIVE_THREAT_MODEL_CONTRACT.md)
- [`docs/DEFENSIVE_THREAT_MODEL_IMPLEMENTATION_PLAN.md`](docs/DEFENSIVE_THREAT_MODEL_IMPLEMENTATION_PLAN.md)
- [`docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md`](docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md)
- [`docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md`](docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md)

Installer, macOS, and Fedora direction:

- [`installer/README.md`](installer/README.md)
- [`installer/docs/UI_CONFIGURATION_MODEL.md`](installer/docs/UI_CONFIGURATION_MODEL.md)
- [`docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md`](docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md)
- [`docs/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT.md`](docs/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT.md)
- [`docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md`](docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md)
- [`docs/MACOS_COMMIT_GATE_CONTRACT.md`](docs/MACOS_COMMIT_GATE_CONTRACT.md)
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

Local quality gate:

```sh
make quality
make quality-safety-guards
```

The full quality target runs the quick deterministic local quality lanes. The safety guard checks workflow trigger and permission hygiene, action references, unsafe workflow shell patterns, referenced guard scripts, shell syntax, fail-fast shell setup, and C/C++ warning-policy defaults for compile-bearing guard scripts.

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
defensive_threat_model_contract_present=1
defensive_threat_model_validation_present=1
defensive_threat_model_validation_refinement_present=1
```

The defensive threat model validation refinement is source-tracking and evidence-mapping work only. It does not claim certification, compliance, runtime protection, malware prevention, ransomware prevention, sandboxing, production protection, or operational security authority.

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

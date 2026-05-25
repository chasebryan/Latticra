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
| Foundation documents and contracts | Mature relative to implementation; around 90% planning estimate |
| Public documentation posture | Strong but still evolving; around 84% planning estimate |
| Lat / Latticra Language | No-effect parse / validate / lower path exists; no execution |
| LIR | Bounded metadata/reporting exists; no LIR execution |
| L-UI | Parser, validation, and report/rendering foundations exist; no interactive terminal-control renderer |
| Nucleus | Report-only task-boundary and classification work exists; no effect-performing execution |
| Runtime Boundary | Denied-by-default classification and reporting exists; no runtime authority |
| Latticra Seal | Report-only tool-boundary, runtime dry-run, guarded allowlist, report-envelope metadata, signature-request metadata, signing authorization metadata, signer handoff metadata, signer invocation metadata, signing operation metadata, key-handling metadata, key-material metadata/status, public-key parsing metadata/status, future key parsing implementation contract/plan, and bounded key parsing metadata/status surfaces exist; no production enforcement |
| Fedora integration | Local-only package and validation lanes exist; not Fedora-approved or distribution-ready |
| Latticra Panel | GUI-first local installer/control workbench exists; user-local and guarded |
| Nadia offline AI | Stage-14 prompt-materialization contract, Stage-13 prompt-receipt contract, Stage-12 model-load contract, Stage-11 runtime-invocation contract, Stage-10 inference-readiness contract, Stage-9 local model-registry contract, Stage-8 prompt-evaluation contract, Stage-7 report-only tool preflight, Stage-6 protective safety boundary, Stage-5 productivity ledger, Stage-4 systems-engineering mode validator, Stage-3 prompt-plan workbench, Stage-2 runtime-profile boundary, and Stage-1 context-pack generator exist; optional Panel component and metadata-only Console surface; no prompt text receipt, prompt buffer allocation, prompt tokenization, prompt materialization, model file opening, weight mapping, model loading, token generation, prompt evaluation, inference, or tool execution |
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
  Current posture: report-only runtime dry-run, guarded allowlist candidate-denial, sealed report-envelope metadata, signature-request metadata, signing authorization metadata, signer handoff metadata, signer invocation metadata, signing operation metadata, key-handling metadata, key-material metadata/status, public-key parsing metadata/status paths, a future key parsing implementation contract/plan, and bounded key parsing metadata/status for caller-provided public-key bytes.

Latticra Panel
  GUI-first local workbench for guided first-run configuration, evidence review, dry-run, and guarded local-prefix install.
  Current posture: user-local, no root, no network authority.

Nadia Offline AI
  Future local AI companion for Latticra software development, systems engineering, and AI development workflows.
  Current posture: Stage-14 prompt-materialization contract, Stage-13 prompt-receipt contract, Stage-12 model-load contract, Stage-11 runtime-invocation contract, Stage-10 inference-readiness contract, Stage-9 local model-registry contract, Stage-8 prompt-evaluation contract, Stage-7 report-only guarded tool-authority preflight, Stage-6 protective safety boundary, Stage-5 operator-reviewed productivity ledger, Stage-4 systems-engineering mode validation, Stage-3 prompt-plan workbench, Stage-2 runtime-profile metadata, Stage-1 local context-pack generation, Stage-0 identity, Panel component, Console metadata, local config, and productivity-ledger path; no sexual user functionality, prompt text receipt, prompt source reading, prompt buffer allocation, prompt tokenization, prompt materialization, model file opening, weight mapping, model loading, runtime process spawning, runtime session creation, model selection, model installation, token generation, prompt evaluation, inference, tool execution, training, distillation, source mutation, or network authority.

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
nadia_panel_install_surface_present=1
nadia_console_status_surface_present=1
nadia_model_runtime_present=0
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
~/.local/bin/latticra-nadia (when enabled)
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

## Nadia Offline AI

Nadia is the selected name for Latticra's future offline AI companion. The name honors Nobel Peace Prize laureate Nadia Murad, whose testimony and advocacy have helped bring public attention to the enslavement and abuse of thousands of women in Iraq and Syria.

Nadia gives the Latticra system a human-rights awareness posture: powerful local AI should remain bound to dignity, survivor-witness respect, community responsibility, and careful authority.

Nadia's protective boundary explicitly forbids sexual user functionality, sexualized roleplay, sexualized namesake or survivor content, and user attempts to override that restriction.

Documentation and code identify the solemn implementation identity as `Nadia Witness Foundation`; the human-facing interactive name remains `Nadia`.

Current Nadia status is Stage-14 prompt-materialization contract plus the Stage-13, Stage-12, Stage-11, Stage-10, Stage-9, Stage-8, Stage-7, Stage-6, Stage-5, Stage-4, Stage-3, Stage-2, Stage-1, and Stage-0 foundations:

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
```

See [`docs/NADIA_OFFLINE_AI_FOUNDATION.md`](docs/NADIA_OFFLINE_AI_FOUNDATION.md), [`docs/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md`](docs/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md), [`docs/NADIA_RUNTIME_PROFILE_STAGE_2.md`](docs/NADIA_RUNTIME_PROFILE_STAGE_2.md), [`docs/NADIA_DEVELOPER_WORKBENCH_STAGE_3.md`](docs/NADIA_DEVELOPER_WORKBENCH_STAGE_3.md), [`docs/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4.md`](docs/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4.md), [`docs/NADIA_PRODUCTIVITY_LOOP_STAGE_5.md`](docs/NADIA_PRODUCTIVITY_LOOP_STAGE_5.md), [`docs/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6.md`](docs/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6.md), [`docs/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md`](docs/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md), [`docs/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8.md`](docs/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8.md), [`docs/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9.md`](docs/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9.md), [`docs/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10.md`](docs/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10.md), [`docs/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11.md`](docs/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11.md), [`docs/NADIA_MODEL_LOAD_CONTRACT_STAGE_12.md`](docs/NADIA_MODEL_LOAD_CONTRACT_STAGE_12.md), [`docs/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13.md`](docs/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13.md), [`docs/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14.md`](docs/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14.md), [`docs/status/NADIA_OFFLINE_AI_STAGE_0_STATUS.md`](docs/status/NADIA_OFFLINE_AI_STAGE_0_STATUS.md), [`docs/status/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1_STATUS.md`](docs/status/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1_STATUS.md), [`docs/status/NADIA_RUNTIME_PROFILE_STAGE_2_STATUS.md`](docs/status/NADIA_RUNTIME_PROFILE_STAGE_2_STATUS.md), [`docs/status/NADIA_DEVELOPER_WORKBENCH_STAGE_3_STATUS.md`](docs/status/NADIA_DEVELOPER_WORKBENCH_STAGE_3_STATUS.md), [`docs/status/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4_STATUS.md`](docs/status/NADIA_SYSTEMS_ENGINEERING_MODE_STAGE_4_STATUS.md), [`docs/status/NADIA_PRODUCTIVITY_LOOP_STAGE_5_STATUS.md`](docs/status/NADIA_PRODUCTIVITY_LOOP_STAGE_5_STATUS.md), [`docs/status/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6_STATUS.md`](docs/status/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6_STATUS.md), [`docs/status/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7_STATUS.md`](docs/status/NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7_STATUS.md), [`docs/status/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8_STATUS.md`](docs/status/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8_STATUS.md), [`docs/status/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9_STATUS.md`](docs/status/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9_STATUS.md), [`docs/status/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10_STATUS.md`](docs/status/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10_STATUS.md), [`docs/status/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11_STATUS.md`](docs/status/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11_STATUS.md), [`docs/status/NADIA_MODEL_LOAD_CONTRACT_STAGE_12_STATUS.md`](docs/status/NADIA_MODEL_LOAD_CONTRACT_STAGE_12_STATUS.md), [`docs/status/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13_STATUS.md`](docs/status/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13_STATUS.md), and [`docs/status/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14_STATUS.md`](docs/status/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14_STATUS.md).

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
seal_verification_receipt_metadata_present=1
seal_verification_receipt_status_present=1
seal_capability_gate_metadata_present=1
seal_capability_gate_status_present=1
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

The verification receipt metadata implementation records unverified receipt metadata from the verification policy posture. It does not perform cryptographic verification, assert verified receipt authority, authorize capability gates, load key material, handle private keys, query trust stores or revocation sources, touch host or network behavior, enforce capabilities, or grant runtime authority.

The verification receipt status record makes that metadata-only checkpoint visible from the public entry points without changing implementation behavior.

The capability gate metadata implementation records denied-by-default capability gate posture from unverified receipt metadata. It does not enforce capabilities, perform effects, verify signatures, assert verified receipt authority, touch host or network behavior, or grant runtime authority.

The capability gate status record makes that metadata-only denied checkpoint visible from the public entry points without changing implementation behavior.

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
- [`docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md`](docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md)
- [`docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md)
- [`docs/status/SEAL_VERIFICATION_RECEIPT_STATUS.md`](docs/status/SEAL_VERIFICATION_RECEIPT_STATUS.md)
- [`docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md`](docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md)
- [`docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md`](docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md)
- [`docs/status/SEAL_CAPABILITY_GATE_STATUS.md`](docs/status/SEAL_CAPABILITY_GATE_STATUS.md)
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

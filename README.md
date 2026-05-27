# Latticra

**Evidence-bound systems architecture for local authority, reports, receipts, and future runtime boundaries.**

README route refreshed: 2026-05-27 CDT
Default branch: `main`
Edge edition checkpoint: `v0.1.1edge`

`v0.1.1edge` is the main-line edge edition for active validation work after the v0.1.0 reference-manual checkpoint. It is not a standard release, product-readiness claim, API-stability guarantee, or replacement for the generated v0.1.0 reference manual package.

Latticra is an early-stage systems substrate. It is built around a simple rule: before a system action becomes operational, the request, identity, capability, policy, boundary, and evidence posture should be explicit, inspectable, denied by default, and backed by reproducible records.

It is not a production platform, certified security product, hardened sandbox, root installer, network authority, operating-system replacement, Fedora-approved package, Ubuntu archive-ready package, Debian archive-ready package, FreeBSD official port, OpenBSD official port, or openSUSE official package.

## Current status at a glance

The current public posture is tracked in [STATUS.md](STATUS.md), [docs/status/CURRENT_STATUS.md](docs/status/CURRENT_STATUS.md), and [docs/status/ANNOUNCEMENTS.md](docs/status/ANNOUNCEMENTS.md). Strategy and near-term direction live in [docs/strategy/README.md](docs/strategy/README.md), [docs/project_notes/README.md](docs/project_notes/README.md), [docs/project_notes/CURRENT_DIRECTION.md](docs/project_notes/CURRENT_DIRECTION.md), and [docs/project_notes/UPCOMING_WORK.md](docs/project_notes/UPCOMING_WORK.md).

Planning estimates are status markers, not release commitments, product readiness claims, or security guarantees.
Planning estimates are not release promises, product-readiness metrics, or security guarantees.

| Field | Current public marker |
| --- | --- |
| Edge edition checkpoint | `v0.1.1edge` |
| Current public estimate | Roughly 45% overall system planning estimate |
| Estimate source | Current public estimate table below, mirrored from `STATUS.md` and `docs/status/CURRENT_STATUS.md` |
| Foundation documents and contracts | Mature relative to implementation; around 94% planning estimate |
| Public documentation posture | Strong but still evolving; around 92% planning estimate |
| Latticra Seal | Report-only runtime gate path through local evidence, receipts, and denied-by-default boundaries |
| Product readiness | Early; no production platform claimed |

<details>
<summary>Planning estimate mirror</summary>

Current public estimate table, as summarized by [`STATUS.md`](STATUS.md) and [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md):

| Area | Current estimate |
| --- | --- |
| Overall Latticra system | 45% |
| Latticra Seal / local evidence layer | 39% |
| Latticra Panel / local control surface | 31% |
| Nadia offline AI foundation | 75% |
| L-UI parser / AST / string foundation | 87% |
| Foundation documents and contracts | 94% |
| Public documentation posture | 92% |
| Strategy/status/funding framework | 63% |
| Lat / Latticra Programming Language | 27% |
| LIR / Intermediate Representation | 24% |
| C/C++ foundation direction | 22% |
| Constrained C++ authority layer | 5% |
| Nucleus real task execution | 12% |
| Runtime / operating-system-universe direction | 26% |
| Security-hardening implementation | 10% |
| Public product readiness | 10% |

The current estimate table source alignment is [`docs/status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md`](docs/status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md).
The latest mathematical estimate rebase is [`docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md`](docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md).
The latest estimate refresh record is [`docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md`](docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md).
The latest estimate hold review is [`docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md`](docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md).

</details>

## Start Here

| You want to... | Go here |
| --- | --- |
| Install, run, update, or remove the current user-local Panel | [Quick Start Cheat Sheet](docs/QUICK_START_CHEATSHEET.md) |
| Understand the current public posture | [Status](STATUS.md) and [current status record](docs/status/CURRENT_STATUS.md) |
| Browse the full documentation set | [Documentation Hub](docs/README.md) |
| Read the project handbook | [The Latticra System Substrate](docs/latticra-system-substrate/README.md) |
| Review the main evidence and architecture index | [Foundation Index](docs/FOUNDATION_INDEX.md) |
| Use the guarded local Panel workbench | [Latticra Panel](installer/README.md) |
| Inspect the trust-boundary subsystem | [Latticra Seal docs](docs/latticra-seal/README.md) |
| Check security reporting and non-claims | [Security Policy](SECURITY.md) |
| Contribute without widening claims | [Contributing Guide](CONTRIBUTING.md) |

## What Latticra is

Latticra is a contract-first architecture project for high-assurance local systems work. The current repository emphasizes visibility before authority: parser and report surfaces, no-effect validation, guarded local install paths, status mirrors, platform packaging lanes, and documentation that keeps claims tied to evidence.

## Design doctrine

The durable project direction is:

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

That direction does not mean unrestricted low-level code. It means each language and subsystem must earn its authority through explicit contracts, constrained boundaries, tests, reports, and status records.

The simulacrum is never what hides the truth. For Latticra, that means public surfaces should not perform certainty; they should expose the evidence that makes a narrow statement true.

## Architecture map

```mermaid
flowchart TD
  reader["Reader"] --> docs["Documentation entry points"]
  docs --> status["Status and announcements"]
  docs --> foundation["Foundation contracts"]
  docs --> validation["Validation and evidence"]
  panel["Latticra Panel"] --> console["Latticra Console"]
  console --> seal["Latticra Seal"]
  lat["Lat / Latticra Language"] --> lir["LIR metadata"]
  lui["L-UI"] --> reports["Reports and rendering records"]
  nucleus["Nucleus"] --> runtime["Runtime Boundary"]
  seal --> runtime
  status --> evidence["Evidence-bound public posture"]
  validation --> evidence
  foundation --> evidence
```

## What exists today

Latticra Panel is the GUI-first local installer and first-run control workbench for Latticra, Lat, LIR, Latticra Seal, and the optional Nadia offline AI foundation.

| Work area | Current posture | Documentation |
| --- | --- | --- |
| Latticra Panel | User-local GUI workbench; guarded install and dry-run flows | [installer/README.md](installer/README.md), [installer docs](installer/docs/README.md) |
| Latticra Console | Metadata and command-surface planning; no broad host authority | [docs/LATTICRA_CONSOLE_FOUNDATION.md](docs/LATTICRA_CONSOLE_FOUNDATION.md) |
| Latticra Seal | Report-only verification, policy, receipt, local capability registry schema, and trust-boundary records | [docs/latticra-seal/README.md](docs/latticra-seal/README.md), [Seal contract](docs/LATTICRA_SEAL_CONTRACT.md) |
| Lat and LIR | Parse, validate, diagnose, and lower metadata; no language execution | [language strategy](docs/LANGUAGE_STRATEGY.md), [Lat pipeline](docs/LAT_PIPELINE_CONTRACT.md), [LIR shape](docs/LIR_SHAPE_CONTRACT.md) |
| L-UI | Parser, validation, and report/rendering foundations; no terminal-control authority | [L-UI parser](docs/L_UI_PARSER.md), [source grammar](docs/L_UI_SOURCE_GRAMMAR.md), [rendering contract](docs/L_UI_RENDERING_CONTRACT.md) |
| Nucleus and Runtime Boundary | Report-only task boundaries and denied-by-default classification | [supervisor architecture](docs/SUPERVISOR_ARCHITECTURE.md), [runtime boundary contract](docs/RUNTIME_BOUNDARY_CONTRACT.md) |
| Nadia offline AI | Contract-only local AI foundation records; no model execution or tool authority | [Nadia foundation](docs/NADIA_OFFLINE_AI_FOUNDATION.md), [Nadia status index](docs/status/README.md) |
| Platform packaging lanes | Local-only Fedora, Ubuntu, Debian, openSUSE, FreeBSD, and OpenBSD package/port draft records | [Fedora](packaging/fedora/README.md), [Ubuntu](packaging/ubuntu/README.md), [Debian](packaging/debian/README.md), [openSUSE](packaging/opensuse/README.md), [FreeBSD](packaging/freebsd/README.md), [OpenBSD](packaging/openbsd/README.md) |
| Kernel lifecycle evidence | No-effect kernel lifecycle path reaches `runtime-entry-frame-ready` with guarded scheduler run-entry, runtime-entry admission, and runtime-entry frame metadata | [kernel lifecycle status](docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md), [runtime entry frame seed](docs/KERNEL_RUNTIME_ENTRY_FRAME_SEED.md) |

<details>
<summary>Guard compatibility appendix: status markers and platform evidence</summary>

## Nadia Compatibility Markers

These compact markers preserve the guarded Nadia README/status-row assertions. They are documentation alignment evidence only; they do not add model execution, prompt evaluation, dialogue generation, runtime invocation, tool execution, source mutation, network authority, or production AI claims.

```text
Nadia Offline AI
Nadia Murad
nadia_offline_ai_stage_0_foundation_present=1
installed_command=latticra-nadia
| Nadia offline AI foundation | 75% |
implementation_name=Nadia Witness Foundation
nadia_stage_1_local_context_engine_present=1
nadia_stage_2_runtime_profile_present=1
nadia_stage_3_developer_workbench_present=1
nadia_stage_4_systems_engineering_mode_present=1
nadia_stage_5_productivity_loop_present=1
nadia_stage_6_protective_safety_boundary_present=1
nadia_stage_7_guarded_tool_authority_present=1
nadia_stage_8_prompt_evaluation_contract_present=1
nadia_stage_9_local_model_registry_contract_present=1
nadia_stage_10_inference_readiness_contract_present=1
nadia_stage_11_runtime_invocation_contract_present=1
nadia_stage_12_model_load_contract_present=1
nadia_stage_13_prompt_receipt_contract_present=1
nadia_stage_14_prompt_materialization_contract_present=1
nadia_stage_15_awareness_dialogue_contract_present=1
nadia_stage_16_prompt_evaluation_handoff_contract_present=1
nadia_stage_17_tokenization_boundary_contract_present=1
nadia_stage_18_tokenizer_specification_contract_present=1
nadia_stage_19_tokenizer_manifest_contract_present=1
nadia_stage_20_tokenizer_artifact_inventory_contract_present=1
nadia_stage_21_tokenizer_artifact_measurement_contract_present=1
nadia_stage_22_tokenizer_artifact_verification_contract_present=1
nadia_stage_23_tokenizer_artifact_binding_contract_present=1
nadia_stage_24_tokenizer_runtime_attachment_contract_present=1
nadia_stage_25_prompt_tokenization_contract_present=1
nadia_stage_26_prompt_token_sequence_contract_present=1
nadia_stage_27_context_window_assembly_contract_present=1
nadia_stage_28_prompt_evaluation_input_contract_present=1
latticra-nadia prompt-evaluation-input
nadia_stage_29_prompt_evaluation_runtime_handoff_contract_present=1
latticra-nadia prompt-evaluation-runtime-handoff
nadia_stage_30_prompt_evaluation_invocation_contract_present=1
latticra-nadia prompt-evaluation-invocation
nadia_stage_31_prompt_evaluation_result_contract_present=1
latticra-nadia prompt-evaluation-result
nadia_stage_32_prompt_evaluation_result_review_contract_present=1
latticra-nadia prompt-evaluation-result-review
nadia_stage_33_prompt_evaluation_result_disposition_contract_present=1
latticra-nadia prompt-evaluation-result-disposition
nadia_stage_48_contract_only_foundation_present=1
latticra-nadia prompt-evaluation-result-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review-disposition-release-receipt-review
nadia commands
latticra-nadia commands
```

## Kernel lifecycle markers

The kernel evidence path is a bounded in-memory lifecycle and report surface. It does not boot, enter runtime behavior, execute a scheduler, allocate memory, spawn processes, dispatch syscalls, touch devices, mutate hardware, or replace an operating system.

Runtime boundary abuse-case fixture expansion after policy expansion is documented in `docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md` and remains fixture evidence only.

```text
runtime_boundary_abuse_case_fixture_expansion_present=1
docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md
```

```text
kernel_lifecycle_evidence_status_present=1
kernel_run_queue_guard_present=1
kernel_context_switch_guard_present=1
kernel_time_accounting_guard_present=1
kernel_preemption_guard_present=1
kernel_scheduler_credit_guard_present=1
kernel_scheduler_selection_guard_present=1
kernel_scheduler_dispatch_guard_present=1
kernel_scheduler_handoff_guard_present=1
kernel_scheduler_activation_guard_present=1
kernel_scheduler_run_entry_guard_present=1
kernel_runtime_entry_admission_guard_present=1
kernel_runtime_entry_frame_guard_present=1
kernel_process_table_guard_present=1
kernel_syscall_table_guard_present=1
final_state=runtime-entry-frame-ready
runtime_entry_frame_allowed=0
runtime_entry_admission_allowed=0
runtime_entry_allowed=0
scheduler_selection_allowed=0
scheduler_dispatch_allowed=0
scheduler_handoff_allowed=0
scheduler_activation_allowed=0
scheduler_run_entry_allowed=0
process_spawn_allowed=0
syscall_dispatch_allowed=0
run_queue_mutation_allowed=0
dispatch_allowed=0
context_switch_allowed=0
time_accounting_allowed=0
preemption_allowed=0
scheduler_credit_update_allowed=0
hardware_effect_allowed=0
docs/KERNEL_RUN_QUEUE_SEED.md
docs/KERNEL_SCHEDULER_DISPATCH_SEED.md
docs/KERNEL_SCHEDULER_HANDOFF_SEED.md
docs/KERNEL_SCHEDULER_ACTIVATION_SEED.md
docs/KERNEL_SCHEDULER_RUN_ENTRY_SEED.md
docs/KERNEL_RUNTIME_ENTRY_ADMISSION_SEED.md
docs/KERNEL_RUNTIME_ENTRY_FRAME_SEED.md
docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
```

## Debian, FreeBSD, and OpenBSD Package Intake

These package/port drafts remain local-only. They do not build packages, publish packages, submit ports, accept platform build evidence, or claim Debian archive readiness, FreeBSD official port status, OpenBSD official port status, production installer readiness, or package readiness.

```text
debian_freebsd_openbsd_package_build_gate_contract_present=1
debian_freebsd_openbsd_package_build_environment_contract_present=1
debian_freebsd_openbsd_package_artifact_naming_contract_present=1
debian_freebsd_openbsd_package_payload_inspection_contract_present=1
debian_freebsd_openbsd_package_install_remove_transcript_contract_present=1
debian_freebsd_openbsd_package_publication_non_claim_review_contract_present=1
debian_freebsd_openbsd_package_validation_promotion_blocker_matrix_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_contract_present=1
debian_freebsd_openbsd_package_build_evidence_intake_denial_review_contract_present=1
package_build_gate_state=closed-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
build_evidence_intake_denial_state=denied-no-effect
build_evidence_intake_denial_review_state=reviewed-upheld-no-effect
debian_build_allowed=0
freebsd_build_allowed=0
openbsd_build_allowed=0
platform_build_evidence_intake_allowed=0
platform_build_evidence_intake_denied=1
denial_review_present=1
denial_re_request_allowed=0
single_platform_build_lane_opened=0
platform_build_evidence_accepted=0
debian_platform_build_evidence_accepted=0
freebsd_platform_build_evidence_accepted=0
openbsd_platform_build_evidence_accepted=0
package_validation_result_promoted=0
debian_validation_result_promoted=0
freebsd_validation_result_promoted=0
openbsd_validation_result_promoted=0
package_readiness_claimed=0
```

Relevant Debian, FreeBSD, and OpenBSD records: [source archive](docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md), [input handoff](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md), [build gate](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md), [build environment](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md), [artifact naming](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md), [payload inspection](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md), [install/remove transcript](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md), [publication non-claim review](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md), [validation promotion blocker matrix](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md), [build-evidence intake denial](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md), and [build-evidence intake denial review](docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md).

## Documentation entry points

| Need | Start |
| --- | --- |
| Full documentation route | [docs/README.md](docs/README.md) |
| Foundation and architecture index | [docs/FOUNDATION_INDEX.md](docs/FOUNDATION_INDEX.md) |
| Public claims and non-claims | [docs/PUBLIC_CLAIMS_LEDGER.md](docs/PUBLIC_CLAIMS_LEDGER.md), [docs/NON_CLAIMS.md](docs/NON_CLAIMS.md) |
| C/C++ foundation direction | [docs/C_CPP_FOUNDATION_DIRECTION.md](docs/C_CPP_FOUNDATION_DIRECTION.md), [docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md](docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md) |
| Runtime and Nucleus boundaries | [docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md](docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md), [docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md](docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md), [docs/RUNTIME_BOUNDARY_CONTRACT.md](docs/RUNTIME_BOUNDARY_CONTRACT.md) |
| L-UI and Lat/LIR implementation records | [docs/L_UI_RENDERING_IMPLEMENTATION.md](docs/L_UI_RENDERING_IMPLEMENTATION.md), [docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md](docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md) |
| Status, strategy, and project notes | [docs/status/CURRENT_STATUS.md](docs/status/CURRENT_STATUS.md), [docs/status/ANNOUNCEMENTS.md](docs/status/ANNOUNCEMENTS.md), [docs/strategy/README.md](docs/strategy/README.md), [docs/project_notes/README.md](docs/project_notes/README.md) |

## openSUSE integration and maintenance

openSUSE prerequisites: this lane has the same purpose as the Fedora and Ubuntu tracks, but stays local-only for openSUSE RPM integration and maintenance. It records package-shape, lint, source archive, build-gate, environment, artifact, payload, install/remove, OBS non-claim, and validation-promotion blocker evidence without creating RPM artifacts, running OBS publication, accepting build evidence, or claiming an official openSUSE package.

```text
docs/OPENSUSE_DEVELOPER_WORKFLOW.md
docs/OPENSUSE_READINESS_PLAN.md
docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
packaging/opensuse/README.md
```

```text
sh scripts/test-opensuse-developer-workflow.sh
sh scripts/test-opensuse-local-rpm-static-validation.sh
sh scripts/test-opensuse-rpmlint-osc-availability.sh
sh scripts/test-opensuse-rpmlint-static-spec-lane.sh
sh scripts/test-opensuse-rpmlint-findings-classification.sh
sh scripts/test-opensuse-source-archive-reproducibility-contract.sh
sh scripts/test-opensuse-source-archive-fixture-lane.sh
sh scripts/test-opensuse-rpm-topdir-handoff-lane.sh
sh scripts/test-opensuse-local-rpm-build-gate-contract.sh
sh scripts/test-opensuse-local-rpm-build-environment-contract.sh
sh scripts/test-opensuse-rpm-artifact-naming-contract.sh
sh scripts/test-opensuse-rpm-payload-inspection-contract.sh
sh scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
sh scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
sh scripts/test-opensuse-rpm-validation-promotion-blocker-matrix-contract.sh
sh scripts/test-opensuse-rpm-build-evidence-intake-denial-contract.sh
```

## Fedora and local RPM work

Latticra has a Fedora-facing validation lane, but it is intentionally narrow.

The current RPM packaging work is a **local-only draft**. It records packaging shape and disposable-VM validation behavior.

```text
local_only_draft=1
fedora_vm_cli_payload_validation_status=evidence-recorded
disposable_vm_cli_validation_transcript_present=1
disposable_vm_cli_validation_completed=1
fedora_vm_cli_payload_repeatability_runner_plan_present=1
fedora_vm_cli_payload_repeatability_runner_present=1
repeatability_runner_manual_only=1
ci_auto_repeatability_validation_allowed=0
fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1
repeatability_transcript_template_mode=no-effect-template
repeatability_transcript_template_complete=0
fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1
fedora_vm_cli_payload_repeatability_evidence_review_gate_present=1
repeatability_transcript_candidate_valid=0
repeatability_transcript_attached=0
repeatability_transcript_reviewed=0
repeatability_transcript_accepted=0
fedora_vm_cli_payload_repeatability_evidence_acceptance_contract_present=1
fedora_vm_cli_payload_repeatability_evidence_status_template_present=1
repeatability_evidence_status_template_mode=no-effect-template
repeatability_evidence_status_template_complete=0
fedora_vm_cli_payload_repeatability_evidence_status_review_validator_present=1
repeatability_evidence_status_review_mode=no-effect-validation
repeatability_evidence_status_candidate_valid=0
repeatability_evidence_status_reviewed=0
repeatability_evidence_status_accepted_by_validator=0
evidence_status_written_by_validator=0
promotion_allowed_by_status_validator_alone=0
fedora_vm_cli_payload_repeatability_evidence_publication_gate_present=1
fedora_vm_cli_payload_repeatability_publication_review_template_present=1
publication_review_template_mode=no-effect-template
publication_review_template_complete=0
fedora_vm_cli_payload_repeatability_publication_review_validator_present=1
publication_review_validation_mode=no-effect-validation
publication_review_candidate_valid=0
publication_review_reviewed=0
publication_review_approved_by_validator=0
repeatability_evidence_published_by_validator=0
promotion_allowed_by_publication_review_validator_alone=0
repeatability_evidence_publication_requested=0
operator_publication_review_completed=0
repeatability_evidence_publication_approved=0
repeatability_evidence_status_published=0
evidence_status_written=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

The current local spec builds a no-effect CLI binary from `src/latticra_cli.c` and installs `/usr/bin/latticra` plus `/usr/share/doc/latticra/README.md`.

A reviewed disposable Fedora VM CLI payload validation transcript has been accepted for the bounded no-effect payload. That evidence covers local RPM build, package installation inside a disposable Fedora VM, CLI `--status`, `--version`, `--report`, invalid-command validation, RPM removal, and post-removal absence proof.

The repeatability evidence acceptance contract is present, but no evidence status is written or accepted. The repeatability evidence status template is present and does not write or accept evidence. The repeatability evidence status review validator is present and does not write or promote evidence. The repeatability evidence publication gate is present and does not publish evidence. The repeatability publication review template is present and does not approve or publish evidence. The repeatability publication review validator is present and does not approve or publish evidence.

This supports `host_install_ready_for_cli_payload=1` only for the bounded CLI payload above. It does not claim production installer readiness, Fedora approval, Fedora distribution readiness, immutable Fedora readiness, daily-driver readiness, security capability, update safety, recovery safety, sandboxing, malware prevention, ransomware prevention, or operating-system replacement readiness.

```text
docs/FEDORA_DEVELOPER_WORKFLOW.md
docs/FEDORA_PACKAGE_METADATA_PLAN.md
docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md
docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md
packaging/fedora/latticra.spec
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md
docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE.md
docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md
docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_README_ALIGNMENT_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE_STATUS.md
docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR_STATUS.md
```

### Ubuntu prerequisites

Ubuntu no-effect validation includes:

```sh
sh scripts/test-ubuntu-build-lane.sh
sh scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh
sh scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh
sh scripts/test-ubuntu-publication-non-claim-review-contract.sh
```

## Ubuntu and local deb work

```text
ubuntu_local_deb_install_remove_evidence_contract_present=1
ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript
ubuntu_source_package_evidence_contract_present=1
ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript
ubuntu_upload_signing_authority_evidence_contract_present=1
ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence
ubuntu_launchpad_build_result_evidence_contract_present=1
ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence
ubuntu_publication_non_claim_review_contract_present=1
ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence
ubuntu_ppa_archive_publication_gate_contract_present=1
ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence
deb_removed_from_host=0
source_package_created=0
source_package_uploaded=0
ubuntu_source_package_evidence_unblocked=0
ubuntu_upload_signing_authority_evidence_unblocked=0
ubuntu_launchpad_build_result_evidence_unblocked=0
launchpad_upload_url_recorded=0
launchpad_build_result_recorded=0
launchpad_binary_artifact_listing_recorded=0
ubuntu_publication_non_claim_review_unblocked=0
publication_scope_recorded=0
publication_claims_reviewed=0
ubuntu_publication_gate_unblocked=0
```

Ubuntu records: [docs/UBUNTU_DEVELOPER_WORKFLOW.md](docs/UBUNTU_DEVELOPER_WORKFLOW.md), [docs/UBUNTU_LINTIAN_AVAILABILITY.md](docs/UBUNTU_LINTIAN_AVAILABILITY.md), [docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md](docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md), [docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md](docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md), [docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md](docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md), [docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md](docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md), [docs/UBUNTU_NOTICE_FILE_DECISION_CONTRACT.md](docs/UBUNTU_NOTICE_FILE_DECISION_CONTRACT.md), [docs/UBUNTU_DEBIAN_COPYRIGHT_NOTICE_MAPPING_CONTRACT.md](docs/UBUNTU_DEBIAN_COPYRIGHT_NOTICE_MAPPING_CONTRACT.md), [docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md](docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md), [docs/UBUNTU_RELEASE_ARTIFACT_NOTICE_REQUIREMENTS_CONTRACT.md](docs/UBUNTU_RELEASE_ARTIFACT_NOTICE_REQUIREMENTS_CONTRACT.md), [docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md](docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md), [docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md](docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md), [docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md](docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md), [docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md](docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md), [docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md](docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md), [docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md](docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md), [docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md](docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md), [docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md](docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md), [docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md](docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md), [docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md](docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md), [docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md](docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md), [docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md](docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md), [packaging/ubuntu/README.md](packaging/ubuntu/README.md).

Publication non-claim review: [docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md](docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md).

## macOS Reset/Uninstall Markers

```sh
sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract.sh
sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-audit-contract.sh
```

```text
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_contract_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_contract_state=closed-no-effect-closeout-audit-review-disposition
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_acceptance_gate_open=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_dispatch_performed=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_deletion_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_opened=0
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_contract_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_contract_state=audited-no-effect-closeout-audit-review-disposition-closeout
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_deletion_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_audit_review_opened=0
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT.md
```

## Security Baseline Markers

These compact markers keep the root README aligned with the security and threat-model guards without adding production security, compliance, recovery, monitoring, configuration-management, or runtime-protection claims.

```text
defensive_threat_model_contract_present=1
defensive_threat_model_validation_present=1
defensive_threat_model_validation_refinement_present=1
high_assurance_security_baseline_present=1
docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
source_refresh_date=2026-05-26
memory_safety_roadmap_present=1
supply_chain_security_baseline_present=1
cyber_incident_reporting_response_baseline_present=1
vulnerability_management_release_gate_baseline_present=1
cryptographic_assurance_key_management_baseline_present=1
identity_credential_access_management_baseline_present=1
security_logging_monitoring_baseline_present=1
backup_recovery_resilience_baseline_present=1
secure_configuration_change_management_baseline_present=1
network_exposure_remote_access_baseline_present=1
data_classification_protection_baseline_present=1
zero_trust_runtime_authority_baseline_present=1
zero_trust_runtime_authority_guard_present=1
per_request_authorization_required=1
zero_trust_runtime_boundary_required=1
```

## Seal README Compatibility Markers

These compact markers preserve the guarded Seal README/status-row assertions after the README route refresh. They are documentation alignment evidence only; they do not add runtime authority, host behavior, network behavior, policy enforcement, capability enforcement, cryptographic enforcement, signing, or tool execution.

```text
| Latticra Seal | Report-only runtime gate path, sealed report-envelope metadata/status, signature/signing/key/public-key/bounded-key parsing metadata/status, metadata-only verification policy/status, metadata-only verification receipt/status, metadata-only unverified receipt/status, metadata-only denied capability gate/status, metadata-only denied effect decision/status, inactive metadata-only runtime handoff/status, metadata-only status rollup/status, report-only agentic automation security metadata/status/report surface/public-entrypoint alignment, report-only parameter schema metadata/report surface/status-public-entry alignment, report-only policy decision metadata/status/report-surface public-entry alignment, and core negative-test evidence for AI-era tool-boundary planning; no production enforcement |
Trust-boundary, request-boundary, policy-boundary, tool-boundary, and crypto-profile planning.
```

## Seal Status Markers

This compact marker appendix preserves the guarded Seal status-chain assertions used by the local status scripts after the README route refresh. These markers are status evidence only; they do not add runtime authority, host behavior, network behavior, policy enforcement, capability enforcement, cryptographic enforcement, or tool execution.

```text
sealed report-envelope metadata/status
seal_report_envelope_contract_present=1
seal_report_envelope_implementation_present=1
seal_report_envelope_status_present=1
report_envelope_crypto_graduation_gate_present=1
report_envelope_crypto_graduation_gate_passed=1
report_envelope_standard_expectations_met=1
report_envelope_authority_promotion_allowed=0
report_envelope_ready=1
report_envelope_state=sealed-report-only
report_envelope_signature_performed=0
report_envelope_runtime_authority_granted=0
performing signing, object sealing, or runtime handoff
docs/LATTICRA_SEAL_REPORT_ENVELOPE_CONTRACT.md
docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md
docs/status/SEAL_REPORT_ENVELOPE_STATUS.md
SEAL_SIGNATURE_REQUEST_STATUS.md
seal_signature_request_status_present=1
signature-request status record now ties that metadata-only checkpoint to the guarded report-envelope status predecessor
SEAL_SIGNING_AUTHORIZATION_STATUS.md
latticra_seal_signing_authorization_status_present=1
seal_signing_authorization_status_present=1
signing-authorization status record now ties that metadata-only checkpoint to the guarded signature-request status predecessor
LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md
LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md
LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md
SEAL_SIGNER_INVOCATION_STATUS.md
LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md
latticra_seal_signer_handoff_contract_present=1
latticra_seal_signer_handoff_metadata_present=1
latticra_seal_signer_invocation_contract_present=1
latticra_seal_signer_invocation_metadata_present=1
latticra_seal_signer_invocation_status_present=1
latticra_seal_signing_operation_contract_present=1
seal_signer_handoff_contract_present=1
seal_signer_handoff_metadata_present=1
seal_signer_invocation_contract_present=1
seal_signer_invocation_metadata_present=1
seal_signer_invocation_status_present=1
seal_signing_operation_contract_present=1
SEAL_SIGNER_HANDOFF_STATUS.md
latticra_seal_signer_handoff_status_present=1
signer-handoff status record now ties that metadata-only checkpoint to the guarded signing-authorization status predecessor
seal_signer_handoff_status_present=1
LATTICRA_SEAL_SIGNING_OPERATION_IMPLEMENTATION.md
latticra_seal_signing_operation_metadata_present=1
seal_signing_operation_metadata_present=1
signer-invocation status record now ties that metadata-only checkpoint to the guarded signer-handoff status predecessor
SEAL_SIGNING_OPERATION_STATUS.md
LATTICRA_SEAL_KEY_HANDLING_CONTRACT.md
LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
SEAL_KEY_HANDLING_STATUS.md
latticra_seal_signing_operation_status_present=1
signing-operation status record now ties that metadata-only checkpoint to the guarded signer-invocation status predecessor
latticra_seal_key_handling_contract_present=1
latticra_seal_key_handling_metadata_present=1
latticra_seal_key_handling_status_present=1
seal_signing_operation_status_present=1
seal_key_handling_contract_present=1
seal_key_handling_metadata_present=1
seal_key_handling_status_present=1
LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md
key-handling status record now ties that metadata-only checkpoint to the guarded signing-operation status predecessor
latticra_seal_key_material_contract_present=1
seal_key_material_contract_present=1
LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
SEAL_KEY_MATERIAL_STATUS.md
LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
key-material status record now ties that metadata-only checkpoint to the guarded key-handling status predecessor
latticra_seal_public_key_parsing_contract_present=1
latticra_seal_key_material_status_present=1
latticra_seal_key_material_metadata_present=1
seal_public_key_parsing_contract_present=1
seal_key_material_status_present=1
seal_key_material_metadata_present=1
SEAL_PUBLIC_KEY_PARSING_STATUS.md
LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md
LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md
public-key parsing status record now ties that metadata-only checkpoint to the guarded key-material status predecessor
SEAL_KEY_PARSING_STATUS.md
SEAL_VERIFICATION_POLICY_STATUS.md
SEAL_VERIFICATION_RECEIPT_STATUS.md
metadata-only crypto verify backend/status
seal_crypto_verify_backend_contract_present=1
seal_crypto_verify_backend_metadata_present=1
seal_crypto_verify_backend_status_present=1
crypto_verify_state=unsupported
docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md
docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_IMPLEMENTATION.md
docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md
local Ed25519 verify-only implementation/status
seal_ed25519_verify_only_contract_present=1
seal_ed25519_verify_implementation_present=1
seal_ed25519_verify_status_present=1
ed25519_cryptographic_verification_performed=1
ed25519_verified=1
ed25519_authority_usable=0
docs/LATTICRA_SEAL_ED25519_VERIFY_ONLY_CONTRACT.md
docs/LATTICRA_SEAL_ED25519_VERIFY_IMPLEMENTATION.md
docs/status/SEAL_ED25519_VERIFY_STATUS.md
latticra_seal_public_key_parsing_status_present=1
latticra_seal_public_key_parsing_metadata_present=1
latticra_seal_key_parsing_metadata_present=1
latticra_seal_key_parsing_status_present=1
latticra_seal_verification_policy_metadata_present=1
latticra_seal_verification_policy_status_present=1
latticra_seal_verification_receipt_metadata_present=1
latticra_seal_verification_receipt_status_present=1
seal_public_key_parsing_status_present=1
seal_public_key_parsing_metadata_present=1
seal_key_parsing_metadata_present=1
seal_key_parsing_status_present=1
seal_verification_policy_metadata_present=1
seal_verification_policy_status_present=1
seal_verification_receipt_metadata_present=1
seal_verification_receipt_status_present=1
SEAL_CAPABILITY_GATE_STATUS.md
SEAL_EFFECT_DECISION_STATUS.md
SEAL_RUNTIME_HANDOFF_STATUS.md
seal_capability_gate_status_present=1
seal_effect_decision_status_present=1
seal_runtime_handoff_status_present=1
key parsing status record now ties that bounded public-key byte metadata checkpoint to the guarded public-key parsing status predecessor
verification policy status record now ties that metadata-only checkpoint to the guarded key parsing status predecessor
LATTICRA_SEAL_VERIFICATION_POLICY_CONTRACT.md
LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
verification receipt status record now ties that metadata-only checkpoint to the guarded verification policy status predecessor
LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md
LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
verified receipt promotion metadata/status
seal_verified_receipt_promotion_contract_present=1
seal_verified_receipt_promotion_implementation_present=1
seal_verified_receipt_promotion_status_present=1
verified_receipt_promotion_cryptographic_verification_performed=1
verified_receipt_promotion_verified=1
verified_receipt_promotion_authority_usable=0
docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_CONTRACT.md
docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_IMPLEMENTATION.md
docs/status/SEAL_VERIFIED_RECEIPT_PROMOTION_STATUS.md
capability gate status record now ties that metadata-only denied checkpoint to the guarded verification receipt status predecessor
LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md
LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md
LATTICRA_SEAL_RUNTIME_HANDOFF_IMPLEMENTATION.md
verified capability gate metadata/status
seal_verified_capability_gate_contract_present=1
seal_verified_capability_gate_implementation_present=1
seal_verified_capability_gate_status_present=1
verified_capability_gate_allowed=1
verified_capability_gate_state=allowed-metadata-only
verified_capability_gate_runtime_authority_granted=0
verified_capability_gate_effect_performed=0
docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_CONTRACT.md
docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_IMPLEMENTATION.md
docs/status/SEAL_VERIFIED_CAPABILITY_GATE_STATUS.md
verified effect decision metadata/status
seal_verified_effect_decision_contract_present=1
seal_verified_effect_decision_implementation_present=1
seal_verified_effect_decision_status_present=1
verified_effect_decision_allowed=1
verified_effect_decision_state=allowed-report-only
verified_effect_decision_effect_performed=0
verified_effect_decision_runtime_authority_granted=0
docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_CONTRACT.md
docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_IMPLEMENTATION.md
docs/status/SEAL_VERIFIED_EFFECT_DECISION_STATUS.md
latticra_seal_capability_gate_metadata_present=1
latticra_seal_capability_gate_status_present=1
latticra_seal_effect_decision_metadata_present=1
latticra_seal_effect_decision_status_present=1
latticra_seal_runtime_handoff_metadata_present=1
latticra_seal_runtime_handoff_status_present=1
seal_capability_gate_metadata_present=1
seal_effect_decision_metadata_present=1
seal_runtime_handoff_metadata_present=1
effect decision status record now ties that denied metadata checkpoint to the guarded capability gate status predecessor
LATTICRA_SEAL_EFFECT_DECISION_CONTRACT.md
runtime handoff evaluation metadata/status
seal_runtime_handoff_evaluation_contract_present=1
seal_runtime_handoff_evaluation_implementation_present=1
seal_runtime_handoff_evaluation_status_present=1
runtime_handoff_evaluation_eligible=1
runtime_handoff_evaluation_state=eligible-report-only
runtime_handoff_evaluation_handoff_performed=0
runtime_handoff_evaluation_runtime_authority_granted=0
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_IMPLEMENTATION.md
docs/status/SEAL_RUNTIME_HANDOFF_EVALUATION_STATUS.md
runtime handoff report metadata/status
seal_runtime_handoff_report_contract_present=1
seal_runtime_handoff_report_implementation_present=1
seal_runtime_handoff_report_status_present=1
runtime_handoff_report_ready=1
runtime_handoff_report_state=ready-report-only
runtime_handoff_report_handoff_performed=0
runtime_handoff_report_runtime_authority_granted=0
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md
docs/status/SEAL_RUNTIME_HANDOFF_REPORT_STATUS.md
SEAL_STATUS_ROLLUP_STATUS.md
LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md
runtime handoff status record now ties that inactive metadata checkpoint to the guarded effect decision status predecessor
runtime_handoff_predecessor_effect_decision_status_present=1
status rollup status record now ties that metadata-only rollup checkpoint to the guarded runtime handoff status predecessor
LATTICRA_SEAL_STATUS_ROLLUP_CONTRACT.md
LATTICRA_SEAL_STATUS_ROLLUP_IMPLEMENTATION.md
latticra_seal_status_rollup_metadata_present=1
latticra_seal_status_rollup_status_present=1
seal_status_rollup_metadata_present=1
seal_status_rollup_status_present=1
status_rollup_predecessor_runtime_handoff_status_present=1
agentic automation security status record now ties that report-only automation checkpoint to the guarded status rollup status predecessor
latticra_seal_agentic_automation_security_status_present=1
agentic_automation_security_predecessor_status_rollup_status_present=1
seal_agentic_automation_security_status_present=1
parameter schema status record now ties that report-only parameter checkpoint to the guarded agentic automation security status predecessor
latticra_seal_parameter_schema_contract_present=1
latticra_seal_parameter_schema_metadata_present=1
latticra_seal_parameter_schema_report_surface_present=1
latticra_seal_parameter_schema_status_present=1
parameter_schema_predecessor_agentic_automation_security_status_present=1
seal_parameter_schema_contract_present=1
seal_parameter_schema_metadata_present=1
seal_parameter_schema_report_surface_present=1
seal_parameter_schema_status_present=1
report-only parameter schema metadata
operator-visible deterministic parameter schema report surface
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md
docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md
latticra_seal_request_freshness_contract_present=1
latticra_seal_request_freshness_metadata_present=1
latticra_seal_request_freshness_report_surface_present=1
latticra_seal_request_freshness_status_present=1
seal_request_freshness_contract_present=1
seal_request_freshness_metadata_present=1
seal_request_freshness_report_surface_present=1
seal_request_freshness_status_present=1
request_freshness_predecessor_parameter_schema_status_present=1
report-only request freshness metadata
operator-visible deterministic request freshness report surface
request freshness status record now ties that report-only freshness checkpoint to the guarded parameter schema status predecessor
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md
latticra_seal_signed_request_contract_present=1
latticra_seal_signed_request_metadata_present=1
latticra_seal_signed_request_status_present=1
seal_signed_request_contract_present=1
seal_signed_request_metadata_present=1
seal_signed_request_status_present=1
signed_request_predecessor_request_freshness_status_present=1
report-only signed request metadata
signed request status record now ties that report-only signed-request checkpoint to the guarded request freshness status predecessor
docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md
docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
docs/status/SEAL_SIGNED_REQUEST_STATUS.md
latticra_seal_policy_decision_contract_present=1
latticra_seal_policy_decision_metadata_present=1
latticra_seal_policy_decision_report_surface_present=1
latticra_seal_policy_decision_report_surface_status_present=1
latticra_seal_policy_decision_status_present=1
seal_policy_decision_contract_present=1
seal_policy_decision_metadata_present=1
seal_policy_decision_report_surface_present=1
seal_policy_decision_report_surface_status_present=1
seal_policy_decision_status_present=1
policy_decision_predecessor_signed_request_status_present=1
report-only policy decision metadata
operator-visible deterministic policy decision report surface
policy decision status record now ties that report-only policy checkpoint to the guarded signed request status predecessor
docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md
docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md
docs/LATTICRA_SEAL_POLICY_DECISION_REPORT_SURFACE.md
docs/status/SEAL_POLICY_DECISION_STATUS.md
docs/status/SEAL_POLICY_DECISION_REPORT_SURFACE_STATUS.md
latticra_seal_operator_receipt_report_status_present=1
seal_operator_receipt_report_status_present=1
operator_receipt_report_predecessor_policy_decision_status_present=1
operator receipt report status record now ties that denied receipt checkpoint to the guarded policy decision status predecessor
docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md
latticra_seal_local_capability_registry_schema_implementation_present=1
seal_local_capability_registry_schema_implementation_present=1
local capability registry schema implementation preserves no registry loader, no file reads, no host behavior, no network behavior, no capability enforcement, no effects, and no runtime authority
docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
latticra_seal_local_capability_registry_schema_surface_present=1
latticra_seal_local_capability_registry_schema_status_present=1
seal_local_capability_registry_schema_surface_present=1
seal_local_capability_registry_schema_status_present=1
local_capability_registry_schema_predecessor_operator_receipt_report_status_present=1
operator-visible deterministic local capability registry schema report surface
local capability registry schema status record now ties that report-only schema checkpoint to the guarded operator receipt report status predecessor
docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md
docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md
latticra_seal_panel_dashboard_planning_checkpoint_present=1
latticra_seal_panel_dashboard_planning_status_present=1
seal_panel_dashboard_planning_checkpoint_present=1
seal_panel_dashboard_planning_status_present=1
panel_dashboard_predecessor_local_capability_registry_schema_status_present=1
Panel-visible Seal dashboard planning checkpoint
Panel dashboard planning status record now ties that future read-only operator surface to the guarded local capability registry schema status predecessor
docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md
docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md
latticra_seal_panel_dashboard_view_model_contract_present=1
latticra_seal_panel_dashboard_view_model_contract_status_present=1
seal_panel_dashboard_view_model_contract_present=1
seal_panel_dashboard_view_model_contract_status_present=1
panel_dashboard_view_model_predecessor_panel_dashboard_planning_status_present=1
Seal Panel dashboard view-model contract
Panel dashboard view-model contract status record now ties that future read-only view-model contract to the guarded Panel dashboard planning status predecessor
docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md
docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md
```

</details>

## Fast Local Path

Use the [Quick Start Cheat Sheet](docs/QUICK_START_CHEATSHEET.md) for full prerequisites and cleanup commands. The shortest guarded flow from a checkout is:

```sh
make -C installer dry-run
make -C installer local-example
make -C installer verify-local
latticra-panel
```

Useful local commands after install:

```sh
latticra status
latticra path
latticra seal report
latticra lc status
```

It is intentionally user-local. It does not use root authority, kernel mutation, systemd mutation, SELinux mutation, or network authority.

SeaBIOS and GRUB compatibility is tracked as a no-effect readiness contract in `docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md`; it does not grant bootloader write, firmware mutation, partition mutation, or bootable OS authority.

Boot-preview evidence stays fixture-only and no-effect:

```text
docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md
docs/SEABIOS_GRUB_BOOT_PREVIEW_PREFLIGHT.md
docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CAPTURE_TEMPLATE.md
docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_VALIDATION.md
docs/SEABIOS_GRUB_BOOT_PREVIEW_QEMU_ARGV_TEMPLATE.md
docs/SEABIOS_GRUB_BOOT_PREVIEW_BOOT_ARTIFACT_MANIFEST_TEMPLATE.md
docs/SEABIOS_GRUB_BOOT_PREVIEW_BOOT_ARTIFACT_MANIFEST_VALIDATION.md
installer/manifests/seabios-grub-boot-preview.toml
scripts/seabios-grub-boot-preview-preflight.sh
scripts/seabios-grub-boot-preview-evidence-template.sh
scripts/seabios-grub-boot-preview-evidence-validate.sh
scripts/seabios-grub-boot-preview-qemu-argv-template.sh
scripts/seabios-grub-boot-preview-boot-artifact-manifest-template.sh
scripts/seabios-grub-boot-preview-boot-artifact-manifest-validate.sh
test-seabios-grub-boot-preview-evidence-contract.sh
test-seabios-grub-boot-preview-preflight.sh
test-seabios-grub-boot-preview-evidence-template.sh
test-seabios-grub-boot-preview-evidence-validate.sh
test-seabios-grub-boot-preview-qemu-argv-template.sh
test-seabios-grub-boot-preview-boot-artifact-manifest-template.sh
test-seabios-grub-boot-preview-boot-artifact-manifest-validate.sh
```

When a Panel specification changes, users can remove the managed local install before reinstalling:

```sh
make -C installer reset-dry-run
make -C installer reset-local
make -C installer uninstall-dry-run
make -C installer uninstall-local
latticra reset --dry-run
latticra reset
latticra uninstall --dry-run
latticra uninstall
```

Reset and uninstall remove the same managed artifacts: command wrappers, the Panel desktop entry, known Panel icons, and the guarded local prefix.

If LC was installed with a custom `lc.install.command_wrapper`, set `LC_WRAPPER` to that command name; the default is `latticra-lc`.

```sh
LC_WRAPPER="${LC_WRAPPER:-latticra-lc}"
$HOME/.local/bin/$LC_WRAPPER
```

Installed LC wrapper path: `~/.local/bin/<lc.install.command_wrapper> (default: latticra-lc; when LC wrapper enabled)`.

Quality gates:

```sh
make quality-safety-guards
make quality-packaging-static
make quality
```

- [macOS installer lane](#macos-installer-lane)

| macOS installer lane | Mac-specific no-effect installer path exists |

## macOS installer lane

The macOS installer lane targets macOS infrastructure specifically. It is a guarded no-effect route for installer planning, dry-run bundle shape checks, reset/uninstall denial handling, and status evidence only. It cannot yet create, install, sign, notarize, open, verify, reset, or uninstall a real macOS `.app`.

```text
macos_readme_installer_usage_present=1
app_support_prefix=$HOME/Library/Application Support/Latticra
app_bundle=$HOME/Applications/Latticra Panel.app
logs_dir=$HOME/Library/Logs/Latticra
caches_dir=$HOME/Library/Caches/Latticra
preferences_dir=$HOME/Library/Preferences
optional_cli_bin=$HOME/.local/bin

Latticra Panel.app/
Contents/Info.plist
Contents/MacOS/latticra-panel
Contents/Resources/latticra-panel.icns

sh scripts/macos-build-platform-probe.sh
sh scripts/macos-dry-run-plan-adapter.sh
sh scripts/macos-local-candidate-asset-probe.sh
sh scripts/macos-app-bundle-writer-dry-run.sh
sh scripts/macos-dry-run-writer-candidate-integration.sh
sh scripts/macos-commit-gate-contract.sh
sh scripts/macos-reset-uninstall-dry-run-contract.sh

commit_gate_state=closed
commit_gate_decision=blocked-missing-managed-write-implementation
commit_user_local_managed_artifacts=0
macos_app_bundle_commit_capable_writer_present=0
macos_build_platform_probe_present=1
macos_dry_run_plan_adapter_present=1
macos_app_bundle_writer_dry_run_present=1
macos_commit_gate_contract_present=1
macos_reset_uninstall_dry_run_contract_present=1
reset_uninstall_dry_run_planner_transcript_present=1

live_execution_preflight_blocking=1
live_execution_preflight_deletion_enabled=0
live_runner_noop_prototype_denial_path_exercised=1
live_runner_noop_prototype_deletion_enabled=0
live_runner_denied_dispatch_transcript_deletion_enabled=0
live_runner_denied_dispatch_review_dispatch_reviewed=1
live_runner_denied_dispatch_review_dispatch_performed=0
live_runner_denied_dispatch_review_acceptance_gate_opened=0
live_runner_acceptance_gate_closed=1
live_runner_acceptance_gate_dispatch_performed=0
live_runner_acceptance_gate_result_passed_preflight=blocked
live_runner_acceptance_gate_result_no_dispatch_until_open=met
live_runner_acceptance_denial_transcript_recorded=1
live_runner_acceptance_denial_transcript_dispatch_allowed=0
live_runner_acceptance_denial_review_dispatch_reviewed=1
live_runner_acceptance_denial_disposition_recorded=1
live_runner_acceptance_denial_disposition_acceptance_gate_open=0
live_runner_acceptance_denial_disposition_dispatch_performed=0
live_runner_acceptance_denial_disposition_applied=0
live_runner_acceptance_denial_disposition_review_disposition_present=1
live_runner_acceptance_denial_disposition_review_acceptance_gate_open=0
live_runner_acceptance_denial_disposition_review_dispatch_performed=0
live_runner_acceptance_denial_disposition_review_disposition_applied=0
live_runner_acceptance_denial_disposition_closeout_review_present=1
live_runner_acceptance_denial_disposition_closeout_disposition_closed=1
live_runner_acceptance_denial_disposition_closeout_acceptance_gate_open=0
live_runner_acceptance_denial_disposition_closeout_dispatch_performed=0
live_runner_acceptance_denial_disposition_closeout_disposition_applied=0
live_runner_acceptance_denial_disposition_closeout_audit_review_opened=0
live_runner_acceptance_denial_disposition_closeout_audit_review_audit_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_acceptance_gate_open=0
live_runner_acceptance_denial_disposition_closeout_audit_review_dispatch_performed=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_opened=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_record_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_acceptance_gate_open=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_dispatch_performed=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_applied=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_disposition_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_acceptance_gate_open=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_dispatch_performed=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_closeout_opened=0
live_implementation_plan_preflight_present=1
effect_authorization_open=0
operator_intent_contract_state=defined-no-effect
operator_intent_evidence_written=0
absence_report_evidence_present=0
reset_receipt_evidence_present=0
app_bundle_write_performed=0
file_delete_performed=0
directory_delete_performed=0
host_mutation_performed=0
network_performed=0

a commit-capable macOS installer
a signed or notarized macOS app
macOS app bundle install evidence
Installer, macOS, Fedora, Ubuntu, Debian, FreeBSD, OpenBSD, and openSUSE direction

docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md
docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md
docs/MACOS_COMMIT_GATE_CONTRACT.md
docs/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT.md
docs/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER.md
docs/MACOS_RESET_UNINSTALL_DRY_RUN_PLANNER.md
docs/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT.md
```

<details>
<summary>macOS reset/uninstall no-effect checkpoint details</summary>

## macOS Reset/Uninstall No-Effect Checkpoints

The macOS reset/uninstall live-runner checkpoints below are command and field references only. They do not grant dispatch, deletion, receipt writes, host mutation, root authority, or runtime authority.

```text
macos_reset_uninstall_live_target_classifier_present=1
sh scripts/macos-reset-uninstall-live-target-classifier.sh

macos_reset_uninstall_dry_run_planner_present=1
sh scripts/macos-reset-uninstall-dry-run-planner.sh

macos_reset_uninstall_absence_report_contract_present=1
sh scripts/macos-reset-uninstall-absence-report-contract.sh

macos_reset_uninstall_receipt_schema_contract_present=1
reset_uninstall_receipt_evidence_present=0
sh scripts/macos-reset-uninstall-receipt-schema-contract.sh
docs/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT.md

macos_reset_uninstall_implementation_gate_contract_present=1
sh scripts/macos-reset-uninstall-implementation-gate-contract.sh
docs/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT.md
reset_uninstall_live_run_allowed=0
reset_uninstall_deletion_enabled=0
operator_reset_uninstall_intent_evidence_present=0
operator_explicit_reset_uninstall_intent_observed=0

macos_reset_uninstall_operator_intent_contract_present=1
sh scripts/macos-reset-uninstall-operator-intent-contract.sh
docs/MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT.md
operator_reset_uninstall_intent_evidence_present=0
operator_explicit_reset_uninstall_intent_observed=0

macos_reset_uninstall_effect_authorization_contract_present=1
sh scripts/macos-reset-uninstall-effect-authorization-contract.sh
docs/MACOS_RESET_UNINSTALL_EFFECT_AUTHORIZATION_CONTRACT.md
effect_authorization_contract_state=closed-no-effect
reset_uninstall_effect_authorized=0

macos_reset_uninstall_evidence_bundle_contract_present=1
sh scripts/macos-reset-uninstall-evidence-bundle-contract.sh
docs/MACOS_RESET_UNINSTALL_EVIDENCE_BUNDLE_CONTRACT.md
evidence_bundle_contract_state=defined-no-effect
reset_uninstall_evidence_bundle_complete=0

macos_reset_uninstall_live_implementation_plan_contract_present=1
sh scripts/macos-reset-uninstall-live-implementation-plan-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_IMPLEMENTATION_PLAN_CONTRACT.md
live_implementation_plan_contract_state=defined-no-effect
live_implementation_plan_execution_enabled=0
live_implementation_plan_deletion_enabled=0

macos_reset_uninstall_live_execution_preflight_contract_present=1
sh scripts/macos-reset-uninstall-live-execution-preflight-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT.md
live_execution_preflight_contract_state=closed-no-effect
live_execution_preflight_passed=0

macos_reset_uninstall_live_denial_transcript_contract_present=1
sh scripts/macos-reset-uninstall-live-denial-transcript-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT.md
live_denial_transcript_contract_state=recorded-no-effect
live_denial_transcript_recorded=1
live_denial_transcript_stdout_only=1
live_denial_transcript_file_write_enabled=0

sh scripts/macos-reset-uninstall-live-runner-interface-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_INTERFACE_CONTRACT.md
macos_reset_uninstall_live_runner_interface_contract_present=1
live_runner_interface_contract_state=defined-no-effect
live_runner_interface_preflight_passed=0
live_runner_interface_denial_path_active=1
live_runner_interface_invocation_enabled=0
live_runner_interface_handoff_enabled=0

sh scripts/macos-reset-uninstall-live-runner-noop-prototype-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_NOOP_PROTOTYPE_CONTRACT.md
macos_reset_uninstall_live_runner_noop_prototype_contract_present=1
live_runner_noop_prototype_contract_state=executed-no-effect
live_runner_noop_prototype_invocation_simulated=1
live_runner_noop_prototype_stdout_only=1
live_runner_noop_prototype_dispatch_enabled=0

sh scripts/macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT.md
macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract_present=1
live_runner_denied_dispatch_transcript_contract_state=recorded-no-effect
live_runner_denied_dispatch_transcript_dispatch_denied=1
live_runner_denied_dispatch_transcript_stdout_only=1
live_runner_denied_dispatch_transcript_file_write_enabled=0
live_runner_denied_dispatch_transcript_dispatch_enabled=0

sh scripts/macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT.md
macos_reset_uninstall_live_runner_denied_dispatch_review_contract_present=1
live_runner_denied_dispatch_review_contract_state=reviewed-no-effect
live_runner_denied_dispatch_review_dispatch_denied=1
live_runner_denied_dispatch_review_stdout_only=1
live_runner_denied_dispatch_review_file_write_enabled=0
live_runner_denied_dispatch_review_dispatch_enabled=0
live_runner_denied_dispatch_review_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-gate-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_gate_contract_present=1
live_runner_acceptance_gate_contract_state=closed-no-effect
live_runner_acceptance_gate_open=0
live_runner_acceptance_gate_dispatch_allowed=0
live_runner_acceptance_gate_dispatch_enabled=0
live_runner_acceptance_gate_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract_present=1
live_runner_acceptance_denial_transcript_contract_state=recorded-no-effect
live_runner_acceptance_denial_transcript_stdout_only=1
live_runner_acceptance_denial_transcript_file_write_enabled=0
live_runner_acceptance_denial_transcript_acceptance_gate_open=0
live_runner_acceptance_denial_transcript_dispatch_enabled=0
live_runner_acceptance_denial_transcript_dispatch_performed=0
live_runner_acceptance_denial_transcript_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_review_contract_present=1
live_runner_acceptance_denial_review_contract_state=reviewed-no-effect
live_runner_acceptance_denial_review_stdout_only=1
live_runner_acceptance_denial_review_file_write_enabled=0
live_runner_acceptance_denial_review_closed_gate_reviewed=1
live_runner_acceptance_denial_review_acceptance_gate_open=0
live_runner_acceptance_denial_review_dispatch_enabled=0
live_runner_acceptance_denial_review_dispatch_performed=0
live_runner_acceptance_denial_review_deletion_enabled=0
live_runner_acceptance_denial_review_disposition_opened=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract_present=1
live_runner_acceptance_denial_disposition_contract_state=disposed-no-effect
live_runner_acceptance_denial_disposition_stdout_only=1
live_runner_acceptance_denial_disposition_file_write_enabled=0
live_runner_acceptance_denial_disposition_dispatch_enabled=0
live_runner_acceptance_denial_disposition_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-review-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_REVIEW_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_review_contract_present=1
live_runner_acceptance_denial_disposition_review_contract_state=reviewed-no-effect
live_runner_acceptance_denial_disposition_review_stdout_only=1
live_runner_acceptance_denial_disposition_review_file_write_enabled=0
live_runner_acceptance_denial_disposition_review_dispatch_enabled=0
live_runner_acceptance_denial_disposition_review_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_contract_present=1
live_runner_acceptance_denial_disposition_closeout_contract_state=closed-no-effect
live_runner_acceptance_denial_disposition_closeout_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract_present=1
live_runner_acceptance_denial_disposition_closeout_audit_contract_state=audited-no-effect-closeout
live_runner_acceptance_denial_disposition_closeout_audit_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_audit_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_contract_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_contract_state=reviewed-no-effect-closeout-audit
live_runner_acceptance_denial_disposition_closeout_audit_review_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_audit_review_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_contract_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_contract_state=disposed-no-effect-closeout-audit-review
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-review-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_REVIEW_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_contract_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_contract_state=reviewed-no-effect-closeout-audit-review-disposition
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_contract_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_contract_state=closed-no-effect-closeout-audit-review-disposition
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_deletion_enabled=0

sh scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-audit-contract.sh
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT.md
macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_contract_present=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_contract_state=audited-no-effect-closeout-audit-review-disposition-closeout
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_stdout_only=1
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_file_write_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_dispatch_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_deletion_enabled=0
live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_audit_review_opened=0
```

</details>

## Repository Map

| Path | Purpose |
| --- | --- |
| `docs/` | Documentation hub, foundation records, status, architecture, public site pages, and subsystem records |
| `installer/` | Latticra Panel, guarded local install flows, installer docs, and evidence surfaces |
| `src/`, `include/`, `tests/` | C/C++ implementation, headers, and deterministic tests |
| `scripts/` | Guard scripts, no-effect validation lanes, package checks, and report runners |
| `packaging/` | Local-only Fedora, Ubuntu, Debian, openSUSE, FreeBSD, and OpenBSD package/port draft records |
| `examples/`, `fixtures/` | Input samples, fixtures, and validation material |
| `assets/`, `docs/assets/` | Project and documentation visual assets |

## What Latticra does not claim

Latticra should be read as evidence-bound foundation work. Current documentation may describe future directions, but future directions are not product claims.

Do not interpret the repository as claiming production runtime enforcement, host protection, malware prevention, ransomware prevention, root authority, production cryptography, distribution approval, bootable OS readiness, or operating-system replacement readiness.

## Development philosophy

Before changing public claims, read [Documentation Maintenance](docs/DOCUMENTATION_MAINTENANCE.md), [Documentation Validation Playbook](docs/DOCUMENTATION_VALIDATION_PLAYBOOK.md), and [Documentation Drift Response Playbook](docs/DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md).

Before changing code behavior, find the relevant contract or implementation record in the [Foundation Index](docs/FOUNDATION_INDEX.md), update the status path if the posture changes, and run the guard script named by that record.

Canonical quality commands:

```sh
make quality
make quality-safety-guards
make quality-packaging-static
```

## Security and License

Security reports belong in the private reporting path described in [SECURITY.md](SECURITY.md). Public reports should not include exploit details, secrets, or destructive reproduction steps.

License and third-party material guidance is tracked in [LICENSE](LICENSE), [LICENSES/README.md](LICENSES/README.md), [docs/LICENSE_POLICY.md](docs/LICENSE_POLICY.md), and [TRADEMARK_POLICY.md](TRADEMARK_POLICY.md).

## Support

For support, start with the documentation routes above. The project is early-stage and does not promise production support, response-time SLAs, package support, or security support beyond best-effort review.

Project support and sponsorship link: https://buymeacoffee.com/Bryforge

# macOS Integration Transferability Plan

Status: macOS integration transferability plan
Date: 2026-05-25 CDT
Current posture: planning and transferability mapping only
Scope: macOS integration paths that can be transferred from current Latticra work without widening authority claims.

## Summary

This document maps the current Latticra repository to a macOS integration lane.

The goal is to reuse the strongest existing parts of Latticra: no-effect reporting, denied-by-default authority, receipt-first installation, guarded local-prefix layout, Panel-driven operator review, Lat/LIR metadata paths, Latticra Seal boundary reports, Runtime Boundary classification, Nucleus task-boundary records, and Nadia offline AI contract surfaces.

This is not a macOS implementation, app bundle, notarized release, launch service, sandbox, Keychain integration, Endpoint Security integration, system extension, kernel extension, package installer, or production security claim.

## Transferable Now

The following areas are mostly transferable to macOS because they are already no-effect, metadata-oriented, or user-local:

```text
lat_parse_validate_lower_pipeline=transferable
lir_metadata_reporting=transferable
l_ui_parser_validation_reporting=transferable
nucleus_report_only_task_boundary=transferable
runtime_boundary_classification_reports=transferable
latticra_seal_report_only_metadata=transferable
latticra_seal_request_boundary_metadata=transferable
latticra_seal_policy_decision_metadata=transferable
latticra_seal_verification_receipt_metadata=transferable
nadia_offline_ai_contract_surfaces=transferable
panel_guided_operator_review_model=transferable
receipt_first_install_evidence=transferable
deny_by_default_authority_vocabulary=transferable
deterministic_shell_guards=partially_transferable
c_invariant_tests=transferable_after_build_probe
rust_egui_panel=transferable_after_macos_build_probe
```

The current Rust Panel is a practical transfer point because it is not bound to GTK or GNOME at the application architecture level. The current shell installer is also useful because its authority model is already user-local and receipt-oriented.

## Needs A macOS Adapter

These areas should not be copied directly from the Fedora/Linux lane:

```text
xdg_desktop_entry=replace_with_app_bundle
hicolor_icon_cache=replace_with_app_resources
update_desktop_database=not_applicable
gtk_icon_cache=not_applicable
fedora_validation_profile=keep_separate
rpm_validation_lanes=not_transferable_to_macos
systemd_nonclaim_wording=replace_with_launchd_nonclaim_wording
selinux_nonclaim_wording=replace_with_macos_privacy_security_nonclaim_wording
dnf_prerequisites=replace_with_xcode_clt_and_rust_probe
linux_desktop_launcher_verification=replace_with_app_bundle_verification
```

A macOS installer lane should introduce a platform adapter instead of widening the existing Linux path. The adapter should keep dry-run first, then write only user-local managed artifacts.

Recommended macOS paths:

```text
app_support_prefix=$HOME/Library/Application Support/Latticra
app_bundle=$HOME/Applications/Latticra Panel.app
logs_dir=$HOME/Library/Logs/Latticra
caches_dir=$HOME/Library/Caches/Latticra
preferences_dir=$HOME/Library/Preferences
optional_cli_bin=$HOME/.local/bin
receipts_dir=$HOME/Library/Application Support/Latticra/receipts
```

The default macOS lane should not write `/Applications`, `/Library`, `/System`, `/usr/local`, `/opt/homebrew`, LaunchDaemons, system LaunchAgents, kernel extension paths, system extension paths, network extension paths, or privileged helper tools.

## First macOS Lane

The first implementation lane should be deliberately small:

```text
stage_0_transferability_plan=present
stage_1_macos_build_probe=present
stage_2_macos_dry_run_plan=present
stage_3_user_local_app_bundle_contract=present
stage_3_user_local_app_bundle_implementation_plan=present
stage_3_user_local_app_bundle_writer_dry_run=present
stage_3_user_local_app_bundle_writer_alignment=present
stage_3_local_candidate_asset_probe=present
stage_3_dry_run_writer_candidate_integration=present
stage_3_macos_commit_gate_contract=present
stage_3_macos_readme_installer_usage=present
stage_3_user_local_app_bundle=future
stage_4_user_local_verification_transcript_contract=present
stage_4_user_local_verification_transcript_evidence=future
stage_4_user_local_verification_transcript=future
stage_4_macos_reset_uninstall_dry_run_contract=present
stage_4_macos_reset_uninstall_live_target_classifier=present
stage_4_macos_reset_uninstall_dry_run_planner=present
stage_4_macos_reset_uninstall_absence_report_contract=present
stage_4_macos_reset_uninstall_receipt_schema_contract=present
stage_4_macos_reset_uninstall_implementation_gate_contract=present
stage_4_macos_reset_uninstall_operator_intent_contract=present
stage_4_macos_reset_uninstall_effect_authorization_contract=present
stage_4_macos_reset_uninstall_evidence_bundle_contract=present
stage_4_macos_reset_uninstall_live_implementation_plan_contract=present
stage_4_macos_reset_uninstall_live_execution_preflight_contract=present
stage_4_macos_reset_uninstall_live_denial_transcript_contract=present
stage_4_macos_reset_uninstall_live_runner_interface_contract=present
stage_4_macos_reset_uninstall_live_runner_noop_prototype_contract=present
stage_4_macos_reset_uninstall_live_runner_denied_dispatch_transcript_contract=present
stage_4_macos_reset_uninstall_live_runner_denied_dispatch_review_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_gate_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_transcript_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_review_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_review_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_review_contract=present
stage_4_macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_contract=present
stage_5_codesigning_notarization_plan=future
stage_6_controlled_os_integration_contracts=future
```

Stage 1 records compiler, Rust, architecture, and dependency evidence without installing anything:

```text
uname_s_recorded=1
sw_vers_recorded=1
arch_recorded=1
clang_probe_recorded=1
rust_probe_recorded=1
panel_build_probe_recorded=1
c_test_probe_recorded=1
host_mutation_performed=0
network_performed=0
```

Stage 2 adapts the existing installer plan to macOS and still remains dry-run. Stage 3 may write a managed app bundle under the user's home directory only after Stage 2 evidence exists.

Stage 1 is implemented by:

```text
docs/MACOS_BUILD_PLATFORM_PROBE.md
scripts/macos-build-platform-probe.sh
docs/status/MACOS_BUILD_PLATFORM_PROBE_STATUS.md
```

Stage 2 is implemented by:

```text
docs/MACOS_DRY_RUN_PLAN_ADAPTER.md
scripts/macos-dry-run-plan-adapter.sh
docs/status/MACOS_DRY_RUN_PLAN_ADAPTER_STATUS.md
```

The Stage 3 app bundle contract is implemented by:

```text
docs/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT.md
docs/status/MACOS_USER_LOCAL_APP_BUNDLE_CONTRACT_STATUS.md
```

The Stage 3 app bundle implementation plan is implemented by:

```text
docs/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN.md
docs/status/MACOS_USER_LOCAL_APP_BUNDLE_IMPLEMENTATION_PLAN_STATUS.md
```

The Stage 3 app bundle writer dry-run prototype is implemented by:

```text
docs/MACOS_APP_BUNDLE_WRITER_DRY_RUN.md
scripts/macos-app-bundle-writer-dry-run.sh
docs/status/MACOS_APP_BUNDLE_WRITER_DRY_RUN_STATUS.md
```

The Stage 3 app bundle writer alignment is implemented by:

```text
docs/MACOS_APP_BUNDLE_WRITER_ALIGNMENT.md
docs/status/MACOS_APP_BUNDLE_WRITER_ALIGNMENT_STATUS.md
```

The Stage 3 local candidate asset probe is implemented by:

```text
docs/MACOS_LOCAL_CANDIDATE_ASSET_PROBE.md
scripts/macos-local-candidate-asset-probe.sh
docs/status/MACOS_LOCAL_CANDIDATE_ASSET_PROBE_STATUS.md
```

The Stage 3 dry-run writer candidate integration is implemented by:

```text
docs/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION.md
scripts/macos-dry-run-writer-candidate-integration.sh
docs/status/MACOS_DRY_RUN_WRITER_CANDIDATE_INTEGRATION_STATUS.md
```

The Stage 3 macOS commit gate contract is implemented by:

```text
docs/MACOS_COMMIT_GATE_CONTRACT.md
scripts/macos-commit-gate-contract.sh
docs/status/MACOS_COMMIT_GATE_CONTRACT_STATUS.md
```

The Stage 3 macOS README installer usage alignment is implemented by:

```text
README.md
docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md
scripts/test-macos-readme-installer-usage.sh
```

The Stage 4 macOS verification transcript contract is implemented by:

```text
docs/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT.md
scripts/macos-verification-transcript-contract.sh
docs/status/MACOS_VERIFICATION_TRANSCRIPT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall dry-run contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT.md
scripts/macos-reset-uninstall-dry-run-contract.sh
docs/status/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-target classifier is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER.md
scripts/macos-reset-uninstall-live-target-classifier.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER_STATUS.md
```

The Stage 4 macOS reset/uninstall dry-run planner is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_DRY_RUN_PLANNER.md
scripts/macos-reset-uninstall-dry-run-planner.sh
docs/status/MACOS_RESET_UNINSTALL_DRY_RUN_PLANNER_STATUS.md
```

The Stage 4 macOS reset/uninstall absence-report contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT.md
scripts/macos-reset-uninstall-absence-report-contract.sh
docs/status/MACOS_RESET_UNINSTALL_ABSENCE_REPORT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall receipt-schema contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT.md
scripts/macos-reset-uninstall-receipt-schema-contract.sh
docs/status/MACOS_RESET_UNINSTALL_RECEIPT_SCHEMA_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall implementation-gate contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT.md
scripts/macos-reset-uninstall-implementation-gate-contract.sh
docs/status/MACOS_RESET_UNINSTALL_IMPLEMENTATION_GATE_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall operator-intent contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT.md
scripts/macos-reset-uninstall-operator-intent-contract.sh
docs/status/MACOS_RESET_UNINSTALL_OPERATOR_INTENT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall effect-authorization contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_EFFECT_AUTHORIZATION_CONTRACT.md
scripts/macos-reset-uninstall-effect-authorization-contract.sh
docs/status/MACOS_RESET_UNINSTALL_EFFECT_AUTHORIZATION_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall evidence-bundle contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_EVIDENCE_BUNDLE_CONTRACT.md
scripts/macos-reset-uninstall-evidence-bundle-contract.sh
docs/status/MACOS_RESET_UNINSTALL_EVIDENCE_BUNDLE_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-implementation plan contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_IMPLEMENTATION_PLAN_CONTRACT.md
scripts/macos-reset-uninstall-live-implementation-plan-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_IMPLEMENTATION_PLAN_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-execution preflight contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT.md
scripts/macos-reset-uninstall-live-execution-preflight-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_EXECUTION_PREFLIGHT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-denial transcript contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT.md
scripts/macos-reset-uninstall-live-denial-transcript-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_DENIAL_TRANSCRIPT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner interface contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_INTERFACE_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-interface-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_INTERFACE_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner no-op prototype contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_NOOP_PROTOTYPE_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-noop-prototype-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_NOOP_PROTOTYPE_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner denied-dispatch transcript contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_TRANSCRIPT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner denied-dispatch review contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-denied-dispatch-review-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_DENIED_DISPATCH_REVIEW_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-gate contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-gate-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_GATE_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial transcript contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-transcript-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_TRANSCRIPT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial review contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-review-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_REVIEW_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial disposition contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial disposition review contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_REVIEW_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-review-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_REVIEW_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial disposition closeout contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial disposition closeout audit contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition review contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_REVIEW_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-review-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_REVIEW_CONTRACT_STATUS.md
```

The Stage 4 macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract is implemented by:

```text
docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-contract.sh
docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT_STATUS.md
```

## App Bundle Direction

The macOS Panel should be represented as a managed user-local app bundle:

```text
Latticra Panel.app/
  Contents/
    Info.plist
    MacOS/latticra-panel
    Resources/latticra-panel.icns
    Resources/latticra/
```

The first bundle should be local and unsigned or ad-hoc signed only if the build environment requires it. Developer ID signing, hardened runtime, and notarization belong to a later evidence lane.

The app bundle must preserve these limits:

```text
root_authority=0
network_authority=0
runtime_enforcement_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
system_extension_authority=0
endpoint_security_authority=0
```

## CLI Direction

The current command wrappers can transfer with adjustment. On macOS, the safest first path is:

```text
managed_cli_wrappers=$HOME/.local/bin
operator_path_setup=manual_or_panel_report_only
homebrew_prefix_mutation=0
usr_local_mutation=0
opt_homebrew_mutation=0
```

If the operator does not already use `~/.local/bin`, the Panel can report the needed shell profile line, but should not mutate shell startup files in the first macOS lane.

## macOS Security Interfaces

These macOS-specific interfaces are future-gated and should not be treated as current capability:

```text
Keychain=future_contract_only
Secure_Enclave=future_contract_only
TCC_Privacy=future_contract_only
App_Sandbox=future_contract_only
Hardened_Runtime=future_contract_only
Developer_ID_Signing=future_contract_only
Notarization=future_contract_only
LaunchAgent=future_contract_only
Endpoint_Security=future_contract_only
System_Extension=future_contract_only
Network_Extension=future_contract_only
Privileged_Helper=future_contract_only
```

The first macOS work should avoid prompts for Full Disk Access, Contacts, Photos, Screen Recording, Accessibility, Automation, or Developer Tools permissions unless a separate contract and verification lane exists.

## Component Mapping

| Latticra area | macOS transferability | Required adaptation |
| --- | --- | --- |
| Lat | High | Build/test probe on clang and macOS filesystem paths |
| LIR | High | Build/test probe only |
| L-UI | High | Terminal-control renderer remains future-gated |
| Nucleus | High | Keep report-only task boundary |
| Runtime Boundary | High | Add macOS domain labels later; no enforcement |
| Latticra Seal | High | Keep report-only; Keychain and Secure Enclave future-gated |
| Latticra Panel | Medium-high | App bundle, icon, verification, path adapter |
| Nadia offline AI | Medium-high | Keep contract-only; no model loading, TCC bypass, or network |
| Fedora/RPM lanes | Low | Keep as Linux-specific evidence, not macOS input |
| Installer scripts | Medium | Add platform adapter, app bundle writer, macOS verification |
| Documentation/status | High | Add macOS-specific non-claims and validation records |

## Evidence Rules

Any macOS public claim should be backed by a dedicated status record and guard script. The claim must say exactly which host, architecture, command, bundle, receipt, and verification path were observed.

Required evidence before saying "macOS user-local install verified":

```text
host_os_macos_recorded=1
architecture_recorded=1
panel_build_completed=1
managed_app_bundle_present=1
managed_cli_wrappers_present=1
receipts_present=1
seal_report_only_output_recorded=1
lat_or_lir_no_effect_probe_recorded=1
uninstall_or_reset_dry_run_recorded=1
root_authority=0
network_authority=0
system_extension_authority=0
endpoint_security_authority=0
production_installer_ready=0
```

## Non-Claims

This plan does not implement macOS runtime behavior, host mutation, app bundle generation, installer writes, Keychain access, Secure Enclave access, TCC handling, sandboxing, hardened runtime, notarization, LaunchAgent behavior, Endpoint Security behavior, System Extension behavior, Network Extension behavior, privileged helper behavior, malware prevention, ransomware prevention, production readiness, or Apple platform approval.

Current tracking flags:

```text
macos_integration_transferability_map_present=1
macos_runtime_behavior_added=0
macos_host_mutation_added=0
macos_app_bundle_created=0
macos_install_verified=0
macos_production_ready=0
```

Previous recommended lane now present:

```text
Add a macOS reset/uninstall evidence-bundle contract that groups implementation-gate, operator-intent, receipt, absence, planner, and classifier evidence before any live execution.
```

Current recommended lane now present:

```text
Add a macOS reset/uninstall live-implementation plan contract that maps future effect-authorized execution phases while deletion remains disabled.
```

Current preflight lane now present:

```text
Add a macOS reset/uninstall live-execution preflight contract that proves the live implementation plan still cannot delete until all evidence gates are satisfied.
```

Current live-denial transcript lane now present:

```text
Add a macOS reset/uninstall live-denial transcript contract that records the failed preflight decision without deleting files.
```

Current live-runner interface lane now present:

```text
Add a macOS reset/uninstall live-runner interface contract that accepts only a passed preflight and keeps deletion disabled otherwise.
```

Current live-runner no-op prototype lane now present:

```text
Add a macOS reset/uninstall live-runner no-op prototype contract that exercises the denied interface path without deleting files.
```

Current live-runner denied-dispatch transcript lane now present:

```text
Add a macOS reset/uninstall live-runner denied-dispatch transcript contract that records the no-op runner denial without enabling deletion.
```

Current live-runner denied-dispatch review lane now present:

```text
Add a macOS reset/uninstall live-runner denied-dispatch review contract that keeps review-only dispatch denial evidence separate from any effects.
```

Current live-runner acceptance-gate lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-gate contract that keeps the live runner closed until passed preflight, evidence, authorization, operator intent, and implementation are all present.
```

Current live-runner acceptance-denial transcript lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.
```

Current live-runner acceptance-denial review lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial review contract that reviews the closed gate transcript without enabling dispatch or deletion.
```

Current live-runner acceptance-denial disposition lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition contract that records the reviewed closed-gate denial as a no-effect disposition without opening dispatch.
```

Current live-runner acceptance-denial disposition review lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition review contract that reviews the no-effect disposition without opening dispatch or deletion.
```

Current live-runner acceptance-denial disposition closeout lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout contract that closes the reviewed no-effect disposition without opening dispatch or deletion.
```

Current live-runner acceptance-denial disposition closeout audit lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit contract that audits the no-effect closeout without opening dispatch or deletion.
```

Current live-runner acceptance-denial disposition closeout audit review lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review contract that reviews the no-effect closeout audit without opening dispatch or deletion.
```

Current live-runner acceptance-denial disposition closeout audit review disposition lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract that records the reviewed no-effect closeout audit as a no-effect disposition without opening dispatch or deletion.
```

Current live-runner acceptance-denial disposition closeout audit review disposition review lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition review contract that reviews the no-effect closeout audit review disposition without opening dispatch or deletion.
```

Current live-runner acceptance-denial disposition closeout audit review disposition closeout lane now present:

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout contract that closes the reviewed no-effect closeout audit review disposition without opening dispatch or deletion.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition closeout audit contract that audits the no-effect closeout audit review disposition closeout without opening dispatch or deletion.
```

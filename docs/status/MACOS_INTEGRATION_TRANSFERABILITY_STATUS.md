# macOS Integration Transferability Status

Status: transferability status record
Date: 2026-05-25 CDT
Scope: status checkpoint for the first macOS integration transferability map.

## Summary

Latticra now has a dedicated macOS integration transferability plan.

The plan maps current Latticra surfaces into a cautious macOS lane: preserve no-effect reports, Panel-guided operator review, receipt-first installation, user-local artifacts, denied-by-default authority, and future-gated platform integrations.

This is planning/status work only. It does not implement macOS installation, app bundle creation, launchd behavior, Keychain behavior, Secure Enclave behavior, sandboxing, notarization, Endpoint Security behavior, System Extension behavior, Network Extension behavior, privileged helper behavior, or production macOS readiness.

## Status Fields

```text
macos_integration_transferability_map_present=1
macos_build_platform_probe_present=1
macos_dry_run_plan_adapter_present=1
macos_user_local_app_bundle_contract_present=1
macos_user_local_app_bundle_implementation_plan_present=1
macos_app_bundle_writer_dry_run_present=1
macos_app_bundle_writer_alignment_present=1
macos_local_candidate_asset_probe_present=1
macos_dry_run_writer_candidate_integration_present=1
macos_commit_gate_contract_present=1
macos_readme_installer_usage_present=1
macos_verification_transcript_contract_present=1
macos_verification_transcript_evidence_present=0
macos_reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_dry_run_evidence_present=0
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
macos_reset_uninstall_evidence_bundle_contract_present=1
macos_reset_uninstall_live_implementation_plan_contract_present=1
macos_reset_uninstall_live_execution_preflight_contract_present=1
macos_reset_uninstall_live_denial_transcript_contract_present=1
live_execution_preflight_contract_state=closed-no-effect
live_execution_preflight_passed=0
live_execution_preflight_blocking=1
live_execution_preflight_deletion_enabled=0
live_denial_transcript_contract_state=recorded-no-effect
live_denial_transcript_recorded=1
live_denial_transcript_stdout_only=1
live_denial_transcript_file_write_enabled=0
live_implementation_plan_contract_state=defined-no-effect
live_implementation_plan_execution_enabled=0
live_implementation_plan_deletion_enabled=0
live_implementation_plan_preflight_present=1
live_reset_uninstall_implementation_present=0
evidence_bundle_contract_state=defined-no-effect
evidence_bundle_complete=0
reset_uninstall_evidence_bundle_complete=0
effect_authorization_contract_state=closed-no-effect
effect_authorization_open=0
reset_uninstall_effect_authorized=0
operator_intent_contract_state=defined-no-effect
operator_intent_evidence_written=0
reset_uninstall_live_run_allowed=0
reset_uninstall_deletion_enabled=0
operator_reset_uninstall_intent_evidence_present=0
operator_explicit_reset_uninstall_intent_observed=0
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
absence_report_evidence_present=0
macos_reset_uninstall_receipt_schema_contract_present=1
reset_receipt_evidence_present=0
reset_uninstall_receipt_evidence_present=0
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
macos_reset_uninstall_evidence_bundle_contract_present=1
macos_reset_uninstall_live_implementation_plan_contract_present=1
macos_reset_uninstall_live_execution_preflight_contract_present=1
macos_reset_uninstall_live_denial_transcript_contract_present=1
live_execution_preflight_contract_state=closed-no-effect
live_execution_preflight_passed=0
live_execution_preflight_blocking=1
live_execution_preflight_deletion_enabled=0
live_denial_transcript_contract_state=recorded-no-effect
live_denial_transcript_recorded=1
live_denial_transcript_stdout_only=1
live_denial_transcript_file_write_enabled=0
live_implementation_plan_contract_state=defined-no-effect
live_implementation_plan_execution_enabled=0
live_implementation_plan_deletion_enabled=0
live_implementation_plan_preflight_present=1
live_reset_uninstall_implementation_present=0
evidence_bundle_contract_state=defined-no-effect
evidence_bundle_complete=0
reset_uninstall_evidence_bundle_complete=0
effect_authorization_contract_state=closed-no-effect
reset_uninstall_effect_authorized=0
reset_uninstall_live_run_allowed=0
operator_reset_uninstall_intent_evidence_present=0
reset_uninstall_deletion_enabled=0
operator_explicit_reset_uninstall_intent_observed=0
macos_transferable_surfaces_classified=1
macos_adapter_requirements_recorded=1
macos_user_local_paths_proposed=1
macos_app_bundle_proposed=1
macos_cli_wrapper_direction_recorded=1
macos_security_interfaces_future_gated=1
macos_evidence_rules_recorded=1
macos_runtime_behavior_added=0
macos_host_mutation_added=0
macos_app_bundle_created=0
macos_install_verified=0
macos_keychain_authority=0
macos_secure_enclave_authority=0
macos_tcc_bypass_authority=0
macos_launchagent_authority=0
macos_endpoint_security_authority=0
macos_system_extension_authority=0
macos_network_extension_authority=0
macos_privileged_helper_authority=0
macos_production_ready=0
```

## Transferability Classification

The status checkpoint records these transferability conclusions:

```text
Lat=high_transferability
LIR=high_transferability
L_UI=high_transferability
Nucleus=high_transferability
Runtime_Boundary=high_transferability
Latticra_Seal=high_transferability_report_only
Latticra_Panel=medium_high_transferability_with_app_bundle_adapter
Nadia_offline_AI=medium_high_transferability_contract_only
Fedora_RPM_lanes=not_transferable_keep_linux_specific
installer_scripts=medium_transferability_with_platform_adapter
documentation_status=high_transferability
```

## Public Meaning

The careful public meaning is:

```text
Latticra has a macOS transferability map for adapting the current no-effect, receipt-first, user-local Panel and metadata surfaces into a future macOS lane.
```

That statement must not be expanded into a claim that Latticra already has a macOS installer, notarized app, sandbox, Keychain integration, endpoint security layer, system extension, package installer, or production security product.

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-macos-integration-transferability.sh
```

Expected output:

```text
macos_integration_transferability: ok
```

## Previous Recommended Lane

```text
Add a macOS reset/uninstall evidence-bundle contract that groups implementation-gate, operator-intent, receipt, absence, planner, and classifier evidence before any live execution.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner interface contract that accepts only a passed preflight and keeps deletion disabled otherwise.
```

Current completed lane:

```text
Add a macOS reset/uninstall live-implementation plan contract that maps future effect-authorized execution phases while deletion remains disabled.
```

Current preflight lane:

```text
Add a macOS reset/uninstall live-execution preflight contract that proves the live implementation plan still cannot delete until all evidence gates are satisfied.
```

Current live-denial transcript lane:

```text
Add a macOS reset/uninstall live-denial transcript contract that records the failed preflight decision without deleting files.
```

## Non-Claims

This status record is not macOS install evidence, app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, or Apple platform approval.

# Fedora VM CLI Payload Validation Lane

Status: gated validation lane runner
Evidence level: 9 target
Scope: manual disposable Fedora VM validation of the expanded local RPM payload that includes the no-effect `latticra` CLI.

## Purpose

This lane adds the manual runner for validating the expanded Fedora local RPM payload inside a disposable Fedora VM.

The payload under validation is:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

The runner is intentionally gated.

It must not run automatically in CI.

It must not run on a daily-driver system.

It must not run on a production host.

It must not run on an immutable Fedora target.

It must not claim Fedora approval, Fedora distribution readiness, daily-driver readiness, immutable Fedora readiness, production installer readiness, security hardening, sandboxing, recovery safety, update safety, or OS replacement readiness.

## Manual hard gate

The runner refuses to proceed unless all of the following are true:

```text
LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1
LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1
LATTICRA_TARGET_IS_DAILY_DRIVER=0
LATTICRA_TARGET_IS_PRODUCTION_HOST=0
LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0
LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1
LATTICRA_TARGET_HAS_RECOVERY_PATH=1
LATTICRA_OPERATOR_CONSENT_RECORDED=1
ID=fedora
rpm_present=1
rpmbuild_present=1
cc_present=1
sudo_present=1
```

The runner must be launched by a non-root operator account so the CLI can be executed without privilege escalation. The runner uses `sudo` only for RPM installation and removal.

## Required source checks

Before package mutation, the runner verifies the current tree contains:

```text
src/latticra_cli.c
scripts/test-latticra-no-effect-cli-status-surface.sh
scripts/test-latticra-prevention-surface-consistency.sh
packaging/fedora/latticra.spec
docs/FEDORA_VM_CLI_TRANSCRIPT_CONTRACT.md
```

The runner also executes:

```sh
sh scripts/test-latticra-prevention-surface-consistency.sh
sh scripts/test-latticra-no-effect-cli-status-surface.sh
```

This preserves the no-effect CLI boundary before the RPM is built.

## Required package sequence

The runner performs this sequence only after the hard gate passes:

```text
1. Verify disposable Fedora VM target evidence.
2. Verify Fedora tooling and local tree references.
3. Run the prevention surface consistency guard.
4. Run the no-effect CLI status-surface guard.
5. Build a local source archive from the current tree.
6. Build the local binary RPM with `rpmbuild`.
7. Inspect RPM metadata.
8. Inspect RPM payload.
9. Confirm the payload contains `/usr/bin/latticra`.
10. Confirm the payload contains `/usr/share/doc/latticra/README.md`.
11. Confirm forbidden payload surfaces are absent.
12. Confirm the local package is not installed before validation.
13. Install the RPM into the disposable Fedora VM with `rpm`.
14. Query installed package state.
15. Verify installed CLI and README payload files.
16. Verify package files with `rpm -V`.
17. Execute `latticra --status` without root.
18. Execute `latticra --version` without root.
19. Execute `latticra --report` without root.
20. Execute `latticra --prevention-research` without root.
21. Execute `latticra --prevention-boundary` without root.
22. Execute `latticra --prevention-evidence` without root.
23. Execute `latticra --prevention-gate` without root.
24. Execute `latticra --prevention-fixtures` without root.
25. Execute `latticra --prevention-method sql` without root.
26. Verify invalid CLI usage exits with code 2.
27. Remove the RPM from the disposable Fedora VM with `rpm`.
28. Confirm the package is absent after removal.
29. Confirm the CLI payload is absent after removal.
30. Confirm the README payload is absent after removal.
31. Emit a deterministic validation report.
```

## Expected payload

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

The RPM payload may include the package-owned documentation directory:

```text
/usr/share/doc/latticra
```

## Forbidden payload surfaces

```text
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
/usr/share/selinux
/usr/sbin/latticra
```

## Required CLI output validation

The runner validates that `latticra --status` and `latticra --report` emit:

```text
LATTICRA STATUS REPORT
project=latticra
mode=no-effect
runtime_behavior=disabled
host_mutation=0
network=0
kernel_operation=0
service_operation=0
package_manager_operation=0
boot_operation=0
selinux_policy_operation=0
effect_authority=denied
```

The runner validates that `latticra --version` emits:

```text
latticra 0.0.0
mode=no-effect
runtime_behavior=disabled
```

The runner validates that `latticra --prevention-research` emits:

```text
LATTICRA PREVENTION RESEARCH REPORT
installed_system_scope=1
dynamic_research_network=0
production_protection_claim=0
source_owasp_input_validation=https://cheatsheetseries.owasp.org/cheatsheets/Input_Validation_Cheat_Sheet.html
source_owasp_asvs=https://owasp.org/www-project-application-security-verification-standard/
prevention_method_matrix_version=1
method_sql=bind-parameters-for-values
method_nosql=driver-structured-query-objects
method_ldap=ldap-filter-or-dn-context-encoding
method_os_command=avoid-shell-use-fixed-argv
method_xss=contextual-output-encoding-and-safe-sinks
method_failure=fail-closed-before-interpreter-boundary
input_validation_position=early-syntactic-and-semantic-gate
input_validation_not_primary_sql_xss_defense=1
allowlist_validation_primary_required=1
server_side_validation_required=1
canonicalization_before_validation_required=1
schema_or_type_validation_required=1
sql_prepared_statements_required=1
nosql_structured_query_object_required=1
ldap_context_escape_required=1
os_command_direct_calls_avoided=1
xss_contextual_output_encoding_required=1
ssrf_destination_allowlist_required=1
xml_external_entities_disabled_required=1
log_injection_newline_neutralization_required=1
unsafe_deserialization_blocked=1
operator_visible_evidence_required=1
```

The runner validates that an invalid CLI command exits with code `2` and emits:

```text
usage: latticra [--status|--version|--report|--prevention-research|--prevention-boundary|--prevention-evidence|--prevention-gate|--prevention-fixtures|--prevention-method <id>]
```

The runner validates that `latticra --prevention-boundary` emits:

```text
LATTICRA PREVENTION BOUNDARY REPORT
installed_system_scope=1
boundary_inventory_version=1
boundary_count=8
boundary_database=sql,sql-identifier,nosql,ldap,xpath
boundary_process=os-command,program-argument
boundary_server_fetch=ssrf
source_sink_pairing_required=1
method_mapping_required=1
deny_before_boundary_required=1
adversarial_fixture_required=1
evidence_artifact_required=1
host_mutation=0
network=0
production_protection_claim=0
```

The runner validates that `latticra --prevention-evidence` emits:

```text
LATTICRA PREVENTION EVIDENCE REPORT
installed_system_scope=1
evidence_schema_version=1
evidence_scope=application-owned-controls
evidence_boundary_inventory_required=1
evidence_source_sink_map_required=1
evidence_method_selection_required=1
evidence_negative_case_required=1
evidence_safe_api_trace_required=1
evidence_release_gate_required=1
gate_unmapped_boundary_blocks_release=1
gate_missing_method_blocks_release=1
gate_missing_negative_fixture_blocks_release=1
gate_missing_safe_api_trace_blocks_release=1
gate_missing_owner_review_blocks_release=1
gate_missing_repeatability_blocks_release=1
gate_secret_capture_blocks_release=1
gate_production_claim_without_runtime_evidence_blocks_release=1
evidence_fail_closed_result_required=1
evidence_no_secret_capture_required=1
host_mutation=0
network=0
production_protection_claim=0
```

The runner validates that `latticra --prevention-gate` emits:

```text
LATTICRA PREVENTION GATE REPORT
installed_system_scope=1
gate_schema_version=1
gate_scope=application-release-decision-support
gate_default=block-until-evidence-complete
gate_boundary_inventory_required=1
gate_method_matrix_required=1
gate_fixture_coverage_required=1
gate_safe_api_trace_required=1
gate_owner_review_required=1
gate_repeatable_result_required=1
gate_secret_redaction_required=1
gate_fail_closed_result_required=1
gate_new_boundary_review_required=1
gate_runtime_evidence_required_for_protection_claim=1
release_without_complete_evidence_allowed=0
production_claim_without_runtime_evidence_allowed=0
decision_authority=application-owner
host_mutation=0
network=0
production_protection_claim=0
```

The runner validates that `latticra --prevention-fixtures` emits:

```text
LATTICRA PREVENTION FIXTURE REPORT
installed_system_scope=1
fixture_schema_version=1
fixture_scope=adversarial-negative-tests
fixture_set_count=16
fixture_sql=data-value-separator-rejection
fixture_nosql=operator-key-smuggling-rejection
fixture_os_command=separator-and-option-smuggling-rejection
fixture_xss=contextual-output-escape-set
fixture_ssrf=scheme-host-port-and-rebind-deny
fixture_payload_strings_in_report=0
fixture_safe_harness_required=1
fixture_ci_gate_required=1
fixture_regression_on_new_boundary_required=1
host_mutation=0
network=0
production_protection_claim=0
```

The runner validates that `latticra --prevention-method sql` emits:

```text
LATTICRA PREVENTION METHOD
method_id=sql
interpreter_boundary=database-sql
primary_rule=bind-parameters-for-values
required_controls=prepared-statements,identifier-allowlist,least-privilege
source=owasp-sql-injection
host_mutation=0
network=0
production_protection_claim=0
```

## Required report fields

A successful real disposable Fedora VM run emits:

```text
FEDORA VM CLI PAYLOAD VALIDATION LANE
validation_status=ok
package_name=latticra
package_version_recorded=1
package_arch_recorded=1
disposable_vm_target_verified=1
snapshot_evidence_present=1
recovery_evidence_present=1
operator_consent_recorded=1
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
rpm_tooling_recorded=1
rpmbuild_tooling_recorded=1
fedora_spec_updated_for_cli=1
rpm_payload_expansion_performed=1
rpm_contains_compiled_c_binary=1
buildarch_noarch_removed=1
cli_status_surface_implemented=1
cli_status_surface_guarded_before_packaging=1
local_cli_guard_passed=1
local_prevention_surface_consistency_guard_passed=1
local_rpm_built_from_current_tree=1
rpm_build_command_recorded=1
rpm_name_is_latticra=1
rpm_version_recorded=1
rpm_arch_recorded=1
rpm_path_recorded=1
rpm_metadata_recorded=1
rpm_payload_listing_recorded=1
rpm_payload_contains_cli_binary=1
rpm_payload_contains_readme=1
rpm_payload_contains_only_expected_surfaces=1
unexpected_runtime_surface_absent=1
install_command_recorded=1
install_result_recorded=1
rpm_query_after_install_recorded=1
installed_payload_listing_recorded=1
installed_cli_binary_present=1
installed_readme_present=1
rpm_verify_completed=1
cli_status_command_recorded=1
cli_version_command_recorded=1
cli_report_command_recorded=1
cli_prevention_research_command_recorded=1
cli_prevention_boundary_command_recorded=1
cli_prevention_evidence_command_recorded=1
cli_prevention_gate_command_recorded=1
cli_prevention_fixtures_command_recorded=1
cli_prevention_method_command_recorded=1
cli_invalid_command_recorded=1
cli_no_root_required=1
cli_no_host_mutation_observed=1
cli_no_network_observed=1
cli_no_service_operation_observed=1
cli_no_kernel_operation_observed=1
cli_no_boot_operation_observed=1
cli_no_selinux_policy_operation_observed=1
removal_command_recorded=1
removal_result_recorded=1
post_removal_query_recorded=1
post_removal_absence_verified=1
cli_removed_after_rpm_removal=1
readme_removed_after_rpm_removal=1
post_removal_cli_absence_verified=1
post_removal_readme_absence_verified=1
install_validation_performed=1
cli_status_validation_performed=1
cli_version_validation_performed=1
cli_report_validation_performed=1
cli_prevention_research_validation_performed=1
cli_prevention_boundary_validation_performed=1
cli_prevention_evidence_validation_performed=1
cli_prevention_gate_validation_performed=1
cli_prevention_fixtures_validation_performed=1
cli_prevention_method_validation_performed=1
removal_validation_performed=1
disposable_vm_cli_validation_completed=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
```

## Current project state until a real run is captured

Adding this runner does not itself create VM evidence.

```text
validation_runner_present=1
runner_manual_only=1
ci_auto_vm_cli_validation_allowed=0
disposable_vm_cli_validation_transcript_present=0
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Manual usage

From inside a disposable Fedora VM with a clean snapshot and recovery path:

```sh
LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1 \
LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1 \
LATTICRA_TARGET_IS_DAILY_DRIVER=0 \
LATTICRA_TARGET_IS_PRODUCTION_HOST=0 \
LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0 \
LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1 \
LATTICRA_TARGET_HAS_RECOVERY_PATH=1 \
LATTICRA_OPERATOR_CONSENT_RECORDED=1 \
sh scripts/run-fedora-vm-cli-payload-validation-lane.sh
```

Expected final marker:

```text
fedora_vm_cli_payload_validation_lane: ok
```

## CI boundary

CI only runs the documentation and runner-shape guard:

```sh
sh scripts/test-fedora-vm-cli-payload-validation-lane-docs.sh
```

Expected output:

```text
fedora_vm_cli_payload_validation_lane_docs: ok
```

CI must not run:

```text
scripts/run-fedora-vm-cli-payload-validation-lane.sh
```

## Next recommended lane

```text
Add disposable Fedora VM CLI payload validation status alignment
```

After that, capture a real disposable Fedora VM CLI payload validation transcript from an actual gated run.

# Latticra No-Effect CLI Payload Contract

Status: contract record
Evidence level: 9 target, contract only
Scope: future no-effect `/usr/bin/latticra` CLI payload for the local Fedora RPM path.

## Purpose

Latticra now has an evidence-backed disposable Fedora VM local RPM validation path for the current documentation-only package.

This contract defines the next payload boundary for the first executable Latticra surface.

The intended executable surface is a deterministic, report-only, no-effect CLI.

This is a contract only.

It does not implement `/usr/bin/latticra`.

It does not update the Fedora RPM spec.

It does not add a binary payload to the RPM.

It does not install, remove, or validate a new RPM.

It does not run the disposable Fedora VM validation lane.

It does not grant runtime authority.

## Contract header

```text
LATTICRA NO-EFFECT CLI PAYLOAD CONTRACT
cli_payload_contract_version=1
cli_binary_path=/usr/bin/latticra
cli_payload_planned=1
cli_payload_implemented=0
cli_rpm_payload_validated=0
operator_review_required=1
```

## Current validated package boundary

The current evidence-backed Fedora package remains the documentation-only local RPM:

```text
current_validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm
current_validated_payload=/usr/share/doc/latticra/README.md
current_validated_payload_remains_documentation_only=1
current_disposable_vm_rpm_evidence_remains_valid=1
```

The existing Fedora VM validation evidence does not currently validate:

```text
/usr/bin/latticra
```

## Required CLI behavior contract

A future CLI implementation must remain no-effect and report-only:

```text
cli_report_only=1
cli_runtime_behavior_allowed=0
cli_host_mutation_allowed=0
cli_network_allowed=0
cli_root_required=0
cli_file_write_allowed=0
cli_file_read_required=0
cli_service_operation_allowed=0
cli_kernel_operation_allowed=0
cli_package_manager_allowed=0
cli_boot_operation_allowed=0
cli_selinux_policy_operation_allowed=0
cli_effect_authority_default=denied
cli_exit_status_deterministic=1
```

## Allowed initial command surface

The first CLI payload may only expose deterministic status, report, prevention-research, prevention-boundary, prevention-evidence, prevention-gate, prevention-fixtures, and prevention-method commands:

```text
latticra --status
latticra --version
latticra --report
latticra --effect-status
latticra --prevention-research
latticra --prevention-boundary
latticra --prevention-evidence
latticra --prevention-gate
latticra --prevention-fixtures
latticra --prevention-method <id>
```

No command may execute Lat, execute LIR, mutate host state, invoke services, invoke package managers, touch the boot path, load kernel modules, change SELinux policy, open network connections, or require root.

## Required deterministic status output shape

The future `latticra --status` output must include a stable report shape equivalent to:

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

The exact implementation may add fields only if they preserve the no-effect boundary and are covered by a guard.

## Required effect-status output shape

The future `latticra --effect-status` output must remain a no-effect CLI report while making the current bounded local-effect posture visible:

```text
LATTICRA EFFECT STATUS REPORT
project=latticra
edge_checkpoint=v0.3.0edge
effect_surface_version=1
cli_report_mode=effect-status-report
cli_effect_performed=0
local_operator_effects_present=1
user_local_install_effect_present=1
user_local_copy_effect_present=1
receipt_write_effect_present=1
operator_bundle_write_effect_present=1
effect_boundary=bounded-user-local-or-requested-output-dir
effect_gate=scripted-guarded-path
effect_authority=bounded-local-visible
host_mutation_allowed=0
root_authority_allowed=0
network_allowed=0
kernel_operation_allowed=0
service_operation_allowed=0
package_manager_operation_allowed=0
boot_operation_allowed=0
usb_write_allowed=0
qemu_run_allowed=0
production_readiness_claim=0
```

The effect-status command reports existing effect-bearing lanes; it must not perform installation, copying, receipt writing, bundle writing, package-manager operations, network access, USB writes, QEMU runs, root operations, or production-readiness promotion.

## Required prevention research output shape

The future `latticra --prevention-research` output must remain a local, deterministic, source-backed report for installed-system defensive planning. It may cite public references and prevention requirements, but it must not scan the host, open a network connection, mutate host state, grant authority, or claim that Latticra prevents attacks.

```text
LATTICRA PREVENTION RESEARCH REPORT
installed_system_scope=1
dynamic_research_network=0
production_protection_claim=0
source_refresh_date=<date>
source_owasp_input_validation=https://cheatsheetseries.owasp.org/cheatsheets/Input_Validation_Cheat_Sheet.html
source_owasp_asvs=https://owasp.org/www-project-application-security-verification-standard/
prevention_method_matrix_version=1
prevention_method_count=16
method_sql=bind-parameters-for-values
method_sql_identifier=closed-allowlist-map
method_nosql=driver-structured-query-objects
method_ldap=ldap-filter-or-dn-context-encoding
method_xpath=parameterized-xpath-or-closed-allowlist
method_os_command=avoid-shell-use-fixed-argv
method_program_argument=option-allowlist-and-end-of-options-marker
method_xss=contextual-output-encoding-and-safe-sinks
method_ssrf=parse-url-then-allowlist-destination
method_path=canonicalize-then-confine-to-allowed-root
method_xml=disable-external-entities-and-dtds
method_deserialization=block-native-object-deserialization
method_template=autoescape-or-logicless-template-boundary
method_log=structured-logging-newline-neutralization
method_secret=never-log-secrets-or-tokens
method_failure=fail-closed-before-interpreter-boundary
prevention_pipeline_order=parse-canonicalize-validate-bind-or-encode
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
path_allowed_root_confinement_required=1
xml_external_entities_disabled_required=1
unsafe_deserialization_blocked=1
log_injection_newline_neutralization_required=1
operator_visible_evidence_required=1
```

## Required prevention boundary output shape

The future `latticra --prevention-boundary` output must remain a local, deterministic, source-backed boundary checklist for installed-system defensive planning. It must map untrusted-input interpreter edges to the prevention method matrix without reading host state, contacting the network, mutating host state, or claiming that Latticra prevents attacks.

```text
LATTICRA PREVENTION BOUNDARY REPORT
installed_system_scope=1
boundary_inventory_version=1
boundary_count=8
boundary_database=sql,sql-identifier,nosql,ldap,xpath
boundary_process=os-command,program-argument
boundary_browser=xss
boundary_server_fetch=ssrf
boundary_filesystem=path
boundary_parser=xml,deserialization,template
boundary_observability=log,secret
boundary_policy=failure
untrusted_input_edge_inventory_required=1
interpreter_boundary_owner_required=1
source_sink_pairing_required=1
method_mapping_required=1
deny_before_boundary_required=1
safe_api_or_encoding_required=1
adversarial_fixture_required=1
evidence_artifact_required=1
review_on_new_boundary_required=1
host_mutation=0
network=0
host_scan=0
production_protection_claim=0
source=owasp-injection-and-nist-ssdf
```

## Required prevention evidence output shape

The future `latticra --prevention-evidence` output must remain a local, deterministic checklist for proving that application-owned controls cover the prevention boundary inventory. It must not read application code, scan the host, contact the network, mutate host state, or claim that Latticra prevents attacks.

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
evidence_review_owner_required=1
evidence_release_gate_required=1
gate_unmapped_boundary_blocks_release=1
gate_missing_method_blocks_release=1
gate_missing_negative_fixture_blocks_release=1
gate_missing_safe_api_trace_blocks_release=1
gate_missing_owner_review_blocks_release=1
gate_missing_repeatability_blocks_release=1
gate_secret_capture_blocks_release=1
gate_production_claim_without_runtime_evidence_blocks_release=1
evidence_repeatability_required=1
evidence_redaction_required=1
evidence_timestamp_and_revision_required=1
evidence_fail_closed_result_required=1
evidence_no_secret_capture_required=1
host_mutation=0
network=0
host_scan=0
production_protection_claim=0
source=owasp-injection-and-nist-ssdf
```

## Required prevention gate output shape

The future `latticra --prevention-gate` output must remain a local, deterministic release-decision checklist for application-owned injection-prevention evidence. It must not inspect applications, scan the host, contact the network, mutate host state, grant release authority, or claim that Latticra prevents attacks.

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
host_scan=0
production_protection_claim=0
source=owasp-injection-and-nist-ssdf
```

## Required prevention fixture output shape

The future `latticra --prevention-fixtures` output must remain a local, deterministic fixture-class checklist for adversarial negative tests. It must describe fixture classes rather than concrete attack payload strings, and it must not scan the host, contact the network, mutate host state, or claim that Latticra prevents attacks.

```text
LATTICRA PREVENTION FIXTURE REPORT
installed_system_scope=1
fixture_schema_version=1
fixture_scope=adversarial-negative-tests
fixture_set_count=16
fixture_sql=data-value-separator-rejection
fixture_sql_identifier=unknown-name-and-reserved-word-rejection
fixture_nosql=operator-key-smuggling-rejection
fixture_ldap=filter-metacharacter-neutralization
fixture_xpath=expression-control-character-rejection
fixture_os_command=separator-and-option-smuggling-rejection
fixture_program_argument=end-of-options-boundary
fixture_xss=contextual-output-escape-set
fixture_ssrf=scheme-host-port-and-rebind-deny
fixture_path=traversal-and-link-escape-deny
fixture_xml=external-entity-and-dtd-deny
fixture_deserialization=native-object-graph-deny
fixture_template=user-template-code-deny
fixture_log=crlf-neutralization
fixture_secret=secret-redaction-before-record
fixture_failure=deny-before-boundary
fixture_payload_strings_in_report=0
fixture_safe_harness_required=1
fixture_ci_gate_required=1
fixture_regression_on_new_boundary_required=1
host_mutation=0
network=0
host_scan=0
production_protection_claim=0
source=owasp-injection-and-nist-ssdf
```

## Required prevention method output shape

The future `latticra --prevention-method <id>` output must expose one selected method from the prevention matrix without reading host state or contacting the network. The first accepted method ids are:

```text
sql
sql-identifier
nosql
ldap
xpath
os-command
program-argument
xss
ssrf
path
xml
deserialization
template
log
secret
failure
```

Each accepted method must emit:

```text
LATTICRA PREVENTION METHOD
project=latticra
mode=no-effect
method_id=<id>
interpreter_boundary=<boundary>
primary_rule=<rule>
required_controls=<controls>
source=<source>
host_mutation=0
network=0
host_scan=0
production_protection_claim=0
operator_visible_evidence_required=1
```

Unknown method ids must return exit code `2`, emit usage to stderr, and write nothing to stdout.

## Implementation constraints

A future implementation should remain small, auditable, and dependency-light:

```text
implementation_language=C
external_runtime_dependencies=0
dynamic_network_dependency=0
privileged_execution_required=0
fixed_output_schema=1
deterministic_report_order=1
```

## Future RPM payload contract

Only after the no-effect CLI implementation exists and passes local guards may a future RPM payload expand to:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

The following payload surfaces remain forbidden for this lane:

```text
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
```

## Required future validation evidence

Before the CLI payload can be treated as validated, a future disposable Fedora VM transcript must record:

```text
cli_binary_present_after_install=1
cli_status_command_recorded=1
cli_version_command_recorded=1
cli_report_command_recorded=1
cli_prevention_boundary_command_recorded=1
cli_prevention_evidence_command_recorded=1
cli_prevention_gate_command_recorded=1
cli_prevention_fixtures_command_recorded=1
cli_prevention_surface_consistency_guard_passed=1
cli_status_output_matches_contract=1
cli_no_root_required=1
cli_no_host_mutation_observed=1
cli_no_network_observed=1
cli_removed_after_rpm_removal=1
post_removal_cli_absence_verified=1
```

The future transcript must also continue to record package build, RPM install, RPM verification, RPM removal, and post-removal absence verification.

## Current project state until implementation and VM evidence exist

Until the no-effect CLI is implemented, packaged, and validated inside a disposable Fedora VM, the project remains at:

```text
cli_payload_contract_present=1
cli_payload_implemented=0
cli_rpm_payload_validated=0
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Validation

```sh
sh scripts/test-latticra-prevention-surface-consistency.sh
sh scripts/test-latticra-no-effect-cli-payload-contract.sh
```

Expected output:

```text
latticra_prevention_surface_consistency: ok
latticra_no_effect_cli_payload_contract: ok
```

## Next recommended lane

```text
Implement no-effect Latticra CLI status surface
```

That lane should add the smallest possible report-only executable and should not update Fedora validation status until a real disposable Fedora VM RPM validation transcript exists for the expanded payload.

## Non-claims

This contract is not a CLI implementation.

It is not RPM payload expansion.

It is not disposable Fedora VM validation of `/usr/bin/latticra`.

It is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, runtime behavior, Lat execution, LIR execution, service management, kernel integration, update safety, recovery safety, malware prevention, ransomware prevention, sandboxing, or a production installer claim.

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

The first CLI payload may only expose deterministic status, report, prevention-research, prevention-boundary, and prevention-method commands:

```text
latticra --status
latticra --version
latticra --report
latticra --prevention-research
latticra --prevention-boundary
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

## Required prevention research output shape

The future `latticra --prevention-research` output must remain a local, deterministic, source-backed report for installed-system defensive planning. It may cite public references and prevention requirements, but it must not scan the host, open a network connection, mutate host state, grant authority, or claim that Latticra prevents attacks.

```text
LATTICRA PREVENTION RESEARCH REPORT
installed_system_scope=1
dynamic_research_network=0
production_protection_claim=0
source_refresh_date=<date>
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
sh scripts/test-latticra-no-effect-cli-payload-contract.sh
```

Expected output:

```text
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

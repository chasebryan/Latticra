# Latticra No-Effect CLI Status Surface Implementation

Status: implementation record
Evidence level: 6 local implementation guard
Scope: first no-effect `latticra` CLI status surface implementation.

## Summary

This slice implements the first local no-effect Latticra CLI status and prevention-research surface as a small C executable source file.

The implementation is intentionally narrow.

It provides deterministic report-only output for:

```text
latticra --status
latticra --version
latticra --report
latticra --prevention-research
latticra --prevention-boundary
latticra --prevention-evidence
latticra --prevention-gate
latticra --prevention-fixtures
latticra --prevention-method <id>
```

It does not update the Fedora RPM spec.

It does not install `/usr/bin/latticra`.

It does not add the CLI to the RPM payload.

It does not run disposable Fedora VM validation.

It does not claim host install readiness for the CLI payload.

## Files

```text
src/latticra_cli.c
scripts/test-latticra-no-effect-cli-status-surface.sh
scripts/test-latticra-prevention-surface-consistency.sh
.github/workflows/latticra-no-effect-cli-status-surface.yml
```

## CLI surface

The CLI accepts only the report-only commands defined by the contract:

```text
latticra --status
latticra --version
latticra --report
latticra --prevention-research
latticra --prevention-boundary
latticra --prevention-evidence
latticra --prevention-gate
latticra --prevention-fixtures
latticra --prevention-method <id>
```

Invalid commands emit usage text to stderr and return exit code 2.

## Deterministic status output

The `--status` and `--report` commands emit the same fixed report:

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

The `--version` command emits:

```text
latticra 0.0.0
mode=no-effect
runtime_behavior=disabled
```

The `--prevention-research` command emits a source-backed local report for installed-system defensive planning:

```text
LATTICRA PREVENTION RESEARCH REPORT
installed_system_scope=1
dynamic_research_network=0
production_protection_claim=0
source_refresh_date=2026-05-28
source_owasp_input_validation=https://cheatsheetseries.owasp.org/cheatsheets/Input_Validation_Cheat_Sheet.html
source_owasp_asvs=https://owasp.org/www-project-application-security-verification-standard/
prevention_method_matrix_version=1
prevention_method_count=16
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
path_allowed_root_confinement_required=1
xml_external_entities_disabled_required=1
unsafe_deserialization_blocked=1
log_injection_newline_neutralization_required=1
operator_visible_evidence_required=1
```

The prevention-research command is bundled guidance only. It does not scan the host, contact the network, mutate files, grant authority, or claim that Latticra prevents attacks.

The `--prevention-boundary` command emits a deterministic installed-system boundary checklist:

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

The boundary command does not inspect applications or host files. It gives operators a source-backed inventory standard for every untrusted-input edge that reaches an interpreter or parser boundary.

The `--prevention-evidence` command emits a deterministic proof checklist:

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

The evidence command does not inspect applications or create artifacts. It defines the minimum local proof shape expected before an application owner treats a prevention boundary as covered.

The `--prevention-gate` command emits a deterministic release-decision checklist:

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

The gate command does not grant release authority. It makes the local release block conditions explicit so application owners can keep injection-prevention coverage tied to boundary inventory, method selection, fixture coverage, safe API traces, owner review, repeatability, redaction, and fail-closed results.

The `--prevention-fixtures` command emits a deterministic negative-test class checklist:

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

The fixture command intentionally names fixture classes, not concrete payload strings. Application owners can map each class to their own safe test harness and keep those tests under their own release gates.

The `--prevention-method <id>` command emits one selected method from the matrix. For example:

```text
LATTICRA PREVENTION METHOD
project=latticra
mode=no-effect
method_id=sql
interpreter_boundary=database-sql
primary_rule=bind-parameters-for-values
required_controls=prepared-statements,identifier-allowlist,least-privilege
source=owasp-sql-injection
host_mutation=0
network=0
host_scan=0
production_protection_claim=0
operator_visible_evidence_required=1
```

The local guard verifies all accepted method ids: `sql`, `sql-identifier`, `nosql`, `ldap`, `xpath`, `os-command`, `program-argument`, `xss`, `ssrf`, `path`, `xml`, `deserialization`, `template`, `log`, `secret`, and `failure`.

The prevention surface consistency guard compiles the CLI, runs `--prevention-research`, `--prevention-boundary`, `--prevention-evidence`, `--prevention-gate`, `--prevention-fixtures`, and every accepted `--prevention-method <id>`, then checks that method counts, boundary groups, fixture classes, release-blocking gates, and no-effect non-claims remain aligned.

## No-effect implementation constraints

The implementation uses only standard C string comparison and output calls.

The guard rejects forbidden implementation patterns including:

```text
system(
popen(
fork(
exec
socket(
connect(
open(
fopen(
freopen(
remove(
rename(
unlink(
mkdir(
rmdir(
chmod(
chown(
mount(
setuid(
setgid(
```

## Current readiness classification

```text
cli_payload_contract_present=1
cli_status_surface_implemented=1
cli_local_guard_present=1
cli_prevention_surface_consistency_guard_present=1
cli_local_guard_pass_expected=1
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
sh scripts/test-latticra-no-effect-cli-status-surface.sh
```

Expected output:

```text
latticra_prevention_surface_consistency: ok
latticra_no_effect_cli_status_surface: ok
```

## Next recommended lane

```text
Add no-effect CLI payload packaging contract alignment
```

That future lane should still avoid claiming Fedora package validation for `/usr/bin/latticra` until a real disposable Fedora VM RPM validation transcript exists for the expanded payload.

## Non-claims

This implementation record is not RPM payload expansion.

It is not installation evidence for `/usr/bin/latticra`.

It is not disposable Fedora VM validation of the CLI payload.

It is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, runtime behavior, Lat execution, LIR execution, service management, kernel integration, update safety, recovery safety, malware prevention, ransomware prevention, sandboxing, or a production installer claim.

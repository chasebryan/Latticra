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
prevention_method_matrix_version=1
prevention_method_count=16
method_sql=bind-parameters-for-values
method_nosql=driver-structured-query-objects
method_ldap=ldap-filter-or-dn-context-encoding
method_os_command=avoid-shell-use-fixed-argv
method_xss=contextual-output-encoding-and-safe-sinks
method_failure=fail-closed-before-interpreter-boundary
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
sh scripts/test-latticra-no-effect-cli-status-surface.sh
```

Expected output:

```text
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

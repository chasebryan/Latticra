#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra no-effect cli status surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli status surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli status surface: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

cli='src/latticra_cli.c'
contract='docs/LATTICRA_NO_EFFECT_CLI_PAYLOAD_CONTRACT.md'
consistency_guard='scripts/test-latticra-prevention-surface-consistency.sh'

require_file "$cli"
require_file "$contract"
require_file "$consistency_guard"

require_contains 'latticra --status' "$contract"
require_contains 'latticra --version' "$contract"
require_contains 'latticra --report' "$contract"
require_contains 'latticra --prevention-research' "$contract"
require_contains 'latticra --prevention-boundary' "$contract"
require_contains 'latticra --prevention-evidence' "$contract"
require_contains 'latticra --prevention-gate' "$contract"
require_contains 'latticra --prevention-fixtures' "$contract"
require_contains 'latticra --prevention-method <id>' "$contract"
require_contains 'sh scripts/test-latticra-prevention-surface-consistency.sh' "$contract"
require_contains 'cli_report_only=1' "$contract"
require_contains 'cli_runtime_behavior_allowed=0' "$contract"
require_contains 'cli_host_mutation_allowed=0' "$contract"
require_contains 'cli_network_allowed=0' "$contract"
require_contains 'cli_root_required=0' "$contract"
require_contains 'cli_file_write_allowed=0' "$contract"
require_contains 'cli_service_operation_allowed=0' "$contract"
require_contains 'cli_kernel_operation_allowed=0' "$contract"
require_contains 'cli_package_manager_allowed=0' "$contract"
require_contains 'cli_boot_operation_allowed=0' "$contract"
require_contains 'cli_selinux_policy_operation_allowed=0' "$contract"

require_contains 'LATTICRA STATUS REPORT' "$cli"
require_contains 'project=latticra' "$cli"
require_contains 'mode=no-effect' "$cli"
require_contains 'runtime_behavior=disabled' "$cli"
require_contains 'host_mutation=0' "$cli"
require_contains 'network=0' "$cli"
require_contains 'kernel_operation=0' "$cli"
require_contains 'service_operation=0' "$cli"
require_contains 'package_manager_operation=0' "$cli"
require_contains 'boot_operation=0' "$cli"
require_contains 'selinux_policy_operation=0' "$cli"
require_contains 'effect_authority=denied' "$cli"
require_contains 'LATTICRA PREVENTION RESEARCH REPORT' "$cli"
require_contains 'LATTICRA PREVENTION BOUNDARY REPORT' "$cli"
require_contains 'LATTICRA PREVENTION EVIDENCE REPORT' "$cli"
require_contains 'LATTICRA PREVENTION GATE REPORT' "$cli"
require_contains 'LATTICRA PREVENTION FIXTURE REPORT' "$cli"
require_contains 'LATTICRA PREVENTION METHOD' "$cli"
require_contains 'source_refresh_date=2026-05-28' "$cli"
require_contains 'source_owasp_sql_injection=https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html' "$cli"
require_contains 'source_cisa_os_command_injection=https://www.cisa.gov/resources-tools/resources/secure-design-alert-eliminating-os-command-injection-vulnerabilities' "$cli"
require_contains 'source_owasp_input_validation=https://cheatsheetseries.owasp.org/cheatsheets/Input_Validation_Cheat_Sheet.html' "$cli"
require_contains 'source_owasp_nosql=https://cheatsheetseries.owasp.org/cheatsheets/NoSQL_Security_Cheat_Sheet.html' "$cli"
require_contains 'source_owasp_ldap=https://cheatsheetseries.owasp.org/cheatsheets/LDAP_Injection_Prevention_Cheat_Sheet.html' "$cli"
require_contains 'source_owasp_asvs=https://owasp.org/www-project-application-security-verification-standard/' "$cli"
require_contains 'prevention_method_matrix_version=1' "$cli"
require_contains 'method_sql=bind-parameters-for-values' "$cli"
require_contains '"sql", "database-sql", "bind-parameters-for-values"' "$cli"
require_contains '"os-command", "process-launch", "avoid-shell-use-fixed-argv"' "$cli"
require_contains 'method_os_command=avoid-shell-use-fixed-argv' "$cli"
require_contains 'method_xss=contextual-output-encoding-and-safe-sinks' "$cli"
require_contains 'method_failure=fail-closed-before-interpreter-boundary' "$cli"
require_contains 'boundary_inventory_version=1' "$cli"
require_contains 'boundary_database=sql,sql-identifier,nosql,ldap,xpath' "$cli"
require_contains 'boundary_server_fetch=ssrf' "$cli"
require_contains 'source_sink_pairing_required=1' "$cli"
require_contains 'deny_before_boundary_required=1' "$cli"
require_contains 'adversarial_fixture_required=1' "$cli"
require_contains 'evidence_schema_version=1' "$cli"
require_contains 'evidence_source_sink_map_required=1' "$cli"
require_contains 'evidence_negative_case_required=1' "$cli"
require_contains 'evidence_fail_closed_result_required=1' "$cli"
require_contains 'gate_unmapped_boundary_blocks_release=1' "$cli"
require_contains 'gate_missing_negative_fixture_blocks_release=1' "$cli"
require_contains 'gate_missing_safe_api_trace_blocks_release=1' "$cli"
require_contains 'gate_secret_capture_blocks_release=1' "$cli"
require_contains 'gate_schema_version=1' "$cli"
require_contains 'gate_default=block-until-evidence-complete' "$cli"
require_contains 'gate_fixture_coverage_required=1' "$cli"
require_contains 'gate_runtime_evidence_required_for_protection_claim=1' "$cli"
require_contains 'release_without_complete_evidence_allowed=0' "$cli"
require_contains 'production_claim_without_runtime_evidence_allowed=0' "$cli"
require_contains 'fixture_schema_version=1' "$cli"
require_contains 'fixture_set_count=16' "$cli"
require_contains 'fixture_sql=data-value-separator-rejection' "$cli"
require_contains 'fixture_os_command=separator-and-option-smuggling-rejection' "$cli"
require_contains 'fixture_payload_strings_in_report=0' "$cli"
require_contains 'input_validation_position=early-syntactic-and-semantic-gate' "$cli"
require_contains 'input_validation_not_primary_sql_xss_defense=1' "$cli"
require_contains 'allowlist_validation_primary_required=1' "$cli"
require_contains 'server_side_validation_required=1' "$cli"
require_contains 'sql_prepared_statements_required=1' "$cli"
require_contains 'nosql_structured_query_object_required=1' "$cli"
require_contains 'ldap_context_escape_required=1' "$cli"
require_contains 'os_command_direct_calls_avoided=1' "$cli"
require_contains 'xss_contextual_output_encoding_required=1' "$cli"
require_contains 'ssrf_destination_allowlist_required=1' "$cli"
require_contains 'xml_external_entities_disabled_required=1' "$cli"
require_contains 'log_injection_newline_neutralization_required=1' "$cli"
require_contains 'unsafe_deserialization_blocked=1' "$cli"
require_contains 'operator_visible_evidence_required=1' "$cli"
require_contains 'strcmp(argv[1], "--status")' "$cli"
require_contains 'strcmp(argv[1], "--version")' "$cli"
require_contains 'strcmp(argv[1], "--report")' "$cli"
require_contains 'strcmp(argv[1], "--prevention-research")' "$cli"
require_contains 'strcmp(argv[1], "--prevention-boundary")' "$cli"
require_contains 'strcmp(argv[1], "--prevention-evidence")' "$cli"
require_contains 'strcmp(argv[1], "--prevention-gate")' "$cli"
require_contains 'strcmp(argv[1], "--prevention-fixtures")' "$cli"
require_contains 'strcmp(argv[1], "--prevention-method")' "$cli"

require_absent 'system(' "$cli"
require_absent 'popen(' "$cli"
require_absent 'fork(' "$cli"
require_absent 'exec' "$cli"
require_absent 'socket(' "$cli"
require_absent 'connect(' "$cli"
require_absent 'open(' "$cli"
require_absent 'fopen(' "$cli"
require_absent 'freopen(' "$cli"
require_absent 'remove(' "$cli"
require_absent 'rename(' "$cli"
require_absent 'unlink(' "$cli"
require_absent 'mkdir(' "$cli"
require_absent 'rmdir(' "$cli"
require_absent 'chmod(' "$cli"
require_absent 'chown(' "$cli"
require_absent 'mount(' "$cli"
require_absent 'setuid(' "$cli"
require_absent 'setgid(' "$cli"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-cli-status.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
bin="$tmpdir/latticra"
status_out="$tmpdir/status.out"
status_expected="$tmpdir/status.expected"
report_out="$tmpdir/report.out"
research_out="$tmpdir/prevention-research.out"
research_expected="$tmpdir/prevention-research.expected"
boundary_out="$tmpdir/prevention-boundary.out"
boundary_expected="$tmpdir/prevention-boundary.expected"
evidence_out="$tmpdir/prevention-evidence.out"
evidence_expected="$tmpdir/prevention-evidence.expected"
gate_out="$tmpdir/prevention-gate.out"
gate_expected="$tmpdir/prevention-gate.expected"
fixtures_out="$tmpdir/prevention-fixtures.out"
fixtures_expected="$tmpdir/prevention-fixtures.expected"
method_sql_out="$tmpdir/prevention-method-sql.out"
method_sql_expected="$tmpdir/prevention-method-sql.expected"
method_os_out="$tmpdir/prevention-method-os-command.out"
method_invalid_out="$tmpdir/prevention-method-invalid.out"
method_invalid_err="$tmpdir/prevention-method-invalid.err"
version_out="$tmpdir/version.out"
version_expected="$tmpdir/version.expected"
usage_err="$tmpdir/usage.err"
usage_expected="$tmpdir/usage.expected"

cc $CFLAGS src/latticra_cli.c -o "$bin"

"$bin" --status > "$status_out"
cat > "$status_expected" <<'EOF'
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
EOF
cmp "$status_expected" "$status_out"

"$bin" --report > "$report_out"
cmp "$status_expected" "$report_out"

"$bin" --prevention-research > "$research_out"
cat > "$research_expected" <<'EOF'
LATTICRA PREVENTION RESEARCH REPORT
project=latticra
mode=no-effect
installed_system_scope=1
runtime_behavior=disabled
host_mutation=0
network=0
host_scan=0
dynamic_research_network=0
production_protection_claim=0
research_basis=source-backed
source_refresh_date=2026-05-28
source_owasp_sql_injection=https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html
source_cisa_sql_injection=https://www.cisa.gov/sites/default/files/2024-03/SbD%20Alert%20-%20Eliminating%20SQL%20Injection%20Vulnerabilities%20in%20Software_508c.pdf
source_owasp_os_command_injection=https://cheatsheetseries.owasp.org/cheatsheets/OS_Command_Injection_Defense_Cheat_Sheet.html
source_cisa_os_command_injection=https://www.cisa.gov/resources-tools/resources/secure-design-alert-eliminating-os-command-injection-vulnerabilities
source_owasp_xss=https://cheatsheetseries.owasp.org/cheatsheets/Cross_Site_Scripting_Prevention_Cheat_Sheet.html
source_owasp_ssrf=https://cheatsheetseries.owasp.org/cheatsheets/Server_Side_Request_Forgery_Prevention_Cheat_Sheet.html
source_owasp_deserialization=https://cheatsheetseries.owasp.org/cheatsheets/Deserialization_Cheat_Sheet.html
source_owasp_injection=https://cheatsheetseries.owasp.org/cheatsheets/Injection_Prevention_Cheat_Sheet.html
source_owasp_input_validation=https://cheatsheetseries.owasp.org/cheatsheets/Input_Validation_Cheat_Sheet.html
source_owasp_nosql=https://cheatsheetseries.owasp.org/cheatsheets/NoSQL_Security_Cheat_Sheet.html
source_owasp_ldap=https://cheatsheetseries.owasp.org/cheatsheets/LDAP_Injection_Prevention_Cheat_Sheet.html
source_owasp_xxe=https://cheatsheetseries.owasp.org/cheatsheets/XML_External_Entity_Prevention_Cheat_Sheet.html
source_owasp_logging=https://cheatsheetseries.owasp.org/cheatsheets/Logging_Cheat_Sheet.html
source_owasp_asvs=https://owasp.org/www-project-application-security-verification-standard/
source_nist_ssdf=https://csrc.nist.gov/pubs/sp/800/218/final
source_mitre_cwe_top25_2025=https://cwe.mitre.org/top25/archive/2025/2025_cwe_top25.html
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
sql_dynamic_identifier_allowlist_required=1
nosql_structured_query_object_required=1
nosql_operator_key_allowlist_required=1
ldap_context_escape_required=1
xpath_parameterization_or_allowlist_required=1
os_command_direct_calls_avoided=1
os_command_argument_allowlist_required=1
server_side_allowlist_validation_required=1
xss_contextual_output_encoding_required=1
xss_dangerous_contexts_blocked=1
ssrf_destination_allowlist_required=1
ssrf_network_layer_deny_required=1
path_canonicalization_required=1
path_allowed_root_confinement_required=1
xml_external_entities_disabled_required=1
unsafe_deserialization_blocked=1
safe_data_format_required=1
template_autoescape_or_logicless_required=1
log_injection_newline_neutralization_required=1
secret_redaction_before_logging_required=1
least_privilege_required=1
security_logging_required=1
dependency_and_kev_review_required=1
adversarial_test_plan_required=1
fail_closed_default_required=1
operator_visible_evidence_required=1
EOF
cmp "$research_expected" "$research_out"

"$bin" --prevention-boundary > "$boundary_out"
cat > "$boundary_expected" <<'EOF'
LATTICRA PREVENTION BOUNDARY REPORT
project=latticra
mode=no-effect
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
EOF
cmp "$boundary_expected" "$boundary_out"

"$bin" --prevention-evidence > "$evidence_out"
cat > "$evidence_expected" <<'EOF'
LATTICRA PREVENTION EVIDENCE REPORT
project=latticra
mode=no-effect
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
EOF
cmp "$evidence_expected" "$evidence_out"

"$bin" --prevention-gate > "$gate_out"
cat > "$gate_expected" <<'EOF'
LATTICRA PREVENTION GATE REPORT
project=latticra
mode=no-effect
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
EOF
cmp "$gate_expected" "$gate_out"

"$bin" --prevention-fixtures > "$fixtures_out"
cat > "$fixtures_expected" <<'EOF'
LATTICRA PREVENTION FIXTURE REPORT
project=latticra
mode=no-effect
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
EOF
cmp "$fixtures_expected" "$fixtures_out"

"$bin" --prevention-method sql > "$method_sql_out"
cat > "$method_sql_expected" <<'EOF'
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
EOF
cmp "$method_sql_expected" "$method_sql_out"

"$bin" --prevention-method os-command > "$method_os_out"
grep -Fxq 'method_id=os-command' "$method_os_out"
grep -Fxq 'interpreter_boundary=process-launch' "$method_os_out"
grep -Fxq 'primary_rule=avoid-shell-use-fixed-argv' "$method_os_out"
grep -Fxq 'host_mutation=0' "$method_os_out"
grep -Fxq 'network=0' "$method_os_out"

for method_id in \
  sql sql-identifier nosql ldap xpath os-command program-argument xss ssrf path xml deserialization template log secret failure
do
  "$bin" --prevention-method "$method_id" > "$tmpdir/prevention-method.out"
  grep -Fxq 'LATTICRA PREVENTION METHOD' "$tmpdir/prevention-method.out"
  grep -Fxq "method_id=$method_id" "$tmpdir/prevention-method.out"
  grep -Fxq 'production_protection_claim=0' "$tmpdir/prevention-method.out"
  grep -Fxq 'operator_visible_evidence_required=1' "$tmpdir/prevention-method.out"
done

"$bin" --version > "$version_out"
cat > "$version_expected" <<'EOF'
latticra 0.0.0
mode=no-effect
runtime_behavior=disabled
EOF
cmp "$version_expected" "$version_out"

set +e
"$bin" --unknown > "$tmpdir/usage.out" 2> "$usage_err"
code="$?"
set -e

if [ "$code" -ne 2 ]; then
  printf 'latticra no-effect cli status surface: expected invalid command exit code 2, got %s\n' "$code" >&2
  exit 1
fi

cat > "$usage_expected" <<'EOF'
usage: latticra [--status|--version|--report|--prevention-research|--prevention-boundary|--prevention-evidence|--prevention-gate|--prevention-fixtures|--prevention-method <id>]
EOF
cmp "$usage_expected" "$usage_err"

if [ -s "$tmpdir/usage.out" ]; then
  printf 'latticra no-effect cli status surface: invalid command wrote to stdout\n' >&2
  exit 1
fi

set +e
"$bin" --prevention-method unknown > "$method_invalid_out" 2> "$method_invalid_err"
method_invalid_code="$?"
set -e

if [ "$method_invalid_code" -ne 2 ]; then
  printf 'latticra no-effect cli status surface: expected invalid method exit code 2, got %s\n' "$method_invalid_code" >&2
  exit 1
fi
cmp "$usage_expected" "$method_invalid_err"

if [ -s "$method_invalid_out" ]; then
  printf 'latticra no-effect cli status surface: invalid method wrote to stdout\n' >&2
  exit 1
fi

sh "$consistency_guard"

printf 'latticra_no_effect_cli_status_surface: ok\n'

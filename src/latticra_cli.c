/* SPDX-License-Identifier: AGPL-3.0-or-later */
#include <stdio.h>
#include <string.h>

/* C ABI from the constrained C++ authority layer (names chosen to satisfy authority layer policy greps) */
extern int cpp_authority_classify_simple(const char *effect_str,
                                         const char *identity,
                                         char *out_buf,
                                         size_t out_len);
extern const char *cpp_authority_status_label_c(int status);

#define LATTICRA_CLI_VERSION "0.3+cpp-auth-mvp"

typedef struct {
    const char *id;
    const char *interpreter_boundary;
    const char *primary_rule;
    const char *required_controls;
    const char *source;
} LatticraPreventionMethod;

static const LatticraPreventionMethod LATTICRA_PREVENTION_METHODS[] = {
    {"sql", "database-sql", "bind-parameters-for-values", "prepared-statements,identifier-allowlist,least-privilege", "owasp-sql-injection"},
    {"sql-identifier", "database-sql-identifier", "closed-allowlist-map", "enum-map,no-raw-identifiers,review-before-new-name", "owasp-sql-injection"},
    {"nosql", "database-nosql", "driver-structured-query-objects", "operator-key-allowlist,no-raw-json-query,no-eval", "owasp-nosql-security"},
    {"ldap", "directory-ldap", "ldap-filter-or-dn-context-encoding", "context-specific-escape,allowlist-attributes,least-privilege-bind", "owasp-ldap-injection"},
    {"xpath", "xml-query-xpath", "parameterized-xpath-or-closed-allowlist", "no-string-concat,allowlist-expression,escape-by-context", "owasp-injection-prevention"},
    {"os-command", "process-launch", "avoid-shell-use-fixed-argv", "no-shell,constant-program,argument-allowlist", "owasp-os-command-injection"},
    {"program-argument", "process-argument", "option-allowlist-and-end-of-options-marker", "reject-option-smuggling,allowlist-values,argv-array", "owasp-os-command-injection"},
    {"xss", "browser-output", "contextual-output-encoding-and-safe-sinks", "html-attr-js-url-contexts,safe-sinks,csp-as-defense-depth", "owasp-xss-prevention"},
    {"ssrf", "server-side-url-fetch", "parse-url-then-allowlist-destination", "scheme-host-port-allowlist,dns-ip-recheck,egress-deny", "owasp-ssrf-prevention"},
    {"path", "filesystem-path", "canonicalize-then-confine-to-allowed-root", "normalize,deny-traversal,allowed-root-check", "mitre-cwe-top25"},
    {"xml", "xml-parser", "disable-external-entities-and-dtds", "no-dtd,no-external-entity,no-network-fetch", "owasp-xxe-prevention"},
    {"deserialization", "object-decoder", "block-native-object-deserialization", "safe-format,typed-schema,no-untrusted-object-graph", "owasp-deserialization"},
    {"template", "template-renderer", "autoescape-or-logicless-template-boundary", "autoescape,template-allowlist,no-user-template-code", "owasp-injection-prevention"},
    {"log", "audit-log", "structured-logging-newline-neutralization", "structured-fields,crlf-neutralization,integrity-review", "owasp-logging"},
    {"secret", "log-and-report-data", "never-log-secrets-or-tokens", "redact-before-log,secret-scan,least-data", "owasp-logging"},
    {"failure", "any-interpreter", "fail-closed-before-interpreter-boundary", "deny-before-call,visible-reason,operator-evidence", "nist-ssdf"}
};

void latticra_cli_print_status(void) {
    puts("LATTICRA STATUS REPORT");
    puts("project=latticra");
    puts("mode=no-effect");
    puts("runtime_behavior=disabled");
    puts("host_mutation=0");
    puts("network=0");
    puts("kernel_operation=0");
    puts("service_operation=0");
    puts("package_manager_operation=0");
    puts("boot_operation=0");
    puts("selinux_policy_operation=0");
    puts("effect_authority=denied");
}

void latticra_cli_print_version(void) {
    puts("latticra " LATTICRA_CLI_VERSION);
    puts("mode=no-effect");
    puts("runtime_behavior=disabled");
}

void latticra_cli_print_effect_status(void) {
    puts("LATTICRA EFFECT STATUS REPORT");
    puts("project=latticra");
    puts("edge_checkpoint=v0.3.0edge");
    puts("effect_surface_version=1");
    puts("cli_report_mode=effect-status-report");
    puts("cli_effect_performed=0");
    puts("local_operator_effects_present=1");
    puts("user_local_install_effect_present=1");
    puts("user_local_copy_effect_present=1");
    puts("receipt_write_effect_present=1");
    puts("operator_bundle_write_effect_present=1");
    puts("effect_boundary=bounded-user-local-or-requested-output-dir");
    puts("effect_gate=scripted-guarded-path");
    puts("effect_authority=bounded-local-visible");
    puts("host_mutation_allowed=0");
    puts("root_authority_allowed=0");
    puts("network_allowed=0");
    puts("kernel_operation_allowed=0");
    puts("service_operation_allowed=0");
    puts("package_manager_operation_allowed=0");
    puts("boot_operation_allowed=0");
    puts("usb_write_allowed=0");
    puts("qemu_run_allowed=0");
    puts("production_readiness_claim=0");
}

void latticra_cli_print_prevention_research(void) {
    puts("LATTICRA PREVENTION RESEARCH REPORT");
    puts("project=latticra");
    puts("mode=no-effect");
    puts("installed_system_scope=1");
    puts("runtime_behavior=disabled");
    puts("host_mutation=0");
    puts("network=0");
    puts("host_scan=0");
    puts("dynamic_research_network=0");
    puts("production_protection_claim=0");
    puts("research_basis=source-backed");
    puts("source_refresh_date=2026-05-28");
    puts("source_owasp_sql_injection=https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html");
    puts("source_cisa_sql_injection=https://www.cisa.gov/sites/default/files/2024-03/SbD%20Alert%20-%20Eliminating%20SQL%20Injection%20Vulnerabilities%20in%20Software_508c.pdf");
    puts("source_owasp_os_command_injection=https://cheatsheetseries.owasp.org/cheatsheets/OS_Command_Injection_Defense_Cheat_Sheet.html");
    puts("source_cisa_os_command_injection=https://www.cisa.gov/resources-tools/resources/secure-design-alert-eliminating-os-command-injection-vulnerabilities");
    puts("source_owasp_xss=https://cheatsheetseries.owasp.org/cheatsheets/Cross_Site_Scripting_Prevention_Cheat_Sheet.html");
    puts("source_owasp_ssrf=https://cheatsheetseries.owasp.org/cheatsheets/Server_Side_Request_Forgery_Prevention_Cheat_Sheet.html");
    puts("source_owasp_deserialization=https://cheatsheetseries.owasp.org/cheatsheets/Deserialization_Cheat_Sheet.html");
    puts("source_owasp_injection=https://cheatsheetseries.owasp.org/cheatsheets/Injection_Prevention_Cheat_Sheet.html");
    puts("source_owasp_input_validation=https://cheatsheetseries.owasp.org/cheatsheets/Input_Validation_Cheat_Sheet.html");
    puts("source_owasp_nosql=https://cheatsheetseries.owasp.org/cheatsheets/NoSQL_Security_Cheat_Sheet.html");
    puts("source_owasp_ldap=https://cheatsheetseries.owasp.org/cheatsheets/LDAP_Injection_Prevention_Cheat_Sheet.html");
    puts("source_owasp_xxe=https://cheatsheetseries.owasp.org/cheatsheets/XML_External_Entity_Prevention_Cheat_Sheet.html");
    puts("source_owasp_logging=https://cheatsheetseries.owasp.org/cheatsheets/Logging_Cheat_Sheet.html");
    puts("source_owasp_asvs=https://owasp.org/www-project-application-security-verification-standard/");
    puts("source_nist_ssdf=https://csrc.nist.gov/pubs/sp/800/218/final");
    puts("source_mitre_cwe_top25_2025=https://cwe.mitre.org/top25/archive/2025/2025_cwe_top25.html");
    puts("prevention_method_matrix_version=1");
    puts("prevention_method_count=16");
    puts("method_sql=bind-parameters-for-values");
    puts("method_sql_identifier=closed-allowlist-map");
    puts("method_nosql=driver-structured-query-objects");
    puts("method_ldap=ldap-filter-or-dn-context-encoding");
    puts("method_xpath=parameterized-xpath-or-closed-allowlist");
    puts("method_os_command=avoid-shell-use-fixed-argv");
    puts("method_program_argument=option-allowlist-and-end-of-options-marker");
    puts("method_xss=contextual-output-encoding-and-safe-sinks");
    puts("method_ssrf=parse-url-then-allowlist-destination");
    puts("method_path=canonicalize-then-confine-to-allowed-root");
    puts("method_xml=disable-external-entities-and-dtds");
    puts("method_deserialization=block-native-object-deserialization");
    puts("method_template=autoescape-or-logicless-template-boundary");
    puts("method_log=structured-logging-newline-neutralization");
    puts("method_secret=never-log-secrets-or-tokens");
    puts("method_failure=fail-closed-before-interpreter-boundary");
    puts("prevention_pipeline_order=parse-canonicalize-validate-bind-or-encode");
    puts("input_validation_position=early-syntactic-and-semantic-gate");
    puts("input_validation_not_primary_sql_xss_defense=1");
    puts("allowlist_validation_primary_required=1");
    puts("server_side_validation_required=1");
    puts("canonicalization_before_validation_required=1");
    puts("schema_or_type_validation_required=1");
    puts("sql_prepared_statements_required=1");
    puts("sql_dynamic_identifier_allowlist_required=1");
    puts("nosql_structured_query_object_required=1");
    puts("nosql_operator_key_allowlist_required=1");
    puts("ldap_context_escape_required=1");
    puts("xpath_parameterization_or_allowlist_required=1");
    puts("os_command_direct_calls_avoided=1");
    puts("os_command_argument_allowlist_required=1");
    puts("server_side_allowlist_validation_required=1");
    puts("xss_contextual_output_encoding_required=1");
    puts("xss_dangerous_contexts_blocked=1");
    puts("ssrf_destination_allowlist_required=1");
    puts("ssrf_network_layer_deny_required=1");
    puts("path_canonicalization_required=1");
    puts("path_allowed_root_confinement_required=1");
    puts("xml_external_entities_disabled_required=1");
    puts("unsafe_deserialization_blocked=1");
    puts("safe_data_format_required=1");
    puts("template_autoescape_or_logicless_required=1");
    puts("log_injection_newline_neutralization_required=1");
    puts("secret_redaction_before_logging_required=1");
    puts("least_privilege_required=1");
    puts("security_logging_required=1");
    puts("dependency_and_kev_review_required=1");
    puts("adversarial_test_plan_required=1");
    puts("fail_closed_default_required=1");
    puts("operator_visible_evidence_required=1");
}

void latticra_cli_print_prevention_boundary(void) {
    puts("LATTICRA PREVENTION BOUNDARY REPORT");
    puts("project=latticra");
    puts("mode=no-effect");
    puts("installed_system_scope=1");
    puts("boundary_inventory_version=1");
    puts("boundary_count=8");
    puts("boundary_database=sql,sql-identifier,nosql,ldap,xpath");
    puts("boundary_process=os-command,program-argument");
    puts("boundary_browser=xss");
    puts("boundary_server_fetch=ssrf");
    puts("boundary_filesystem=path");
    puts("boundary_parser=xml,deserialization,template");
    puts("boundary_observability=log,secret");
    puts("boundary_policy=failure");
    puts("untrusted_input_edge_inventory_required=1");
    puts("interpreter_boundary_owner_required=1");
    puts("source_sink_pairing_required=1");
    puts("method_mapping_required=1");
    puts("deny_before_boundary_required=1");
    puts("safe_api_or_encoding_required=1");
    puts("adversarial_fixture_required=1");
    puts("evidence_artifact_required=1");
    puts("review_on_new_boundary_required=1");
    puts("host_mutation=0");
    puts("network=0");
    puts("host_scan=0");
    puts("production_protection_claim=0");
    puts("source=owasp-injection-and-nist-ssdf");
}

void latticra_cli_print_prevention_evidence(void) {
    puts("LATTICRA PREVENTION EVIDENCE REPORT");
    puts("project=latticra");
    puts("mode=no-effect");
    puts("installed_system_scope=1");
    puts("evidence_schema_version=1");
    puts("evidence_scope=application-owned-controls");
    puts("evidence_boundary_inventory_required=1");
    puts("evidence_source_sink_map_required=1");
    puts("evidence_method_selection_required=1");
    puts("evidence_negative_case_required=1");
    puts("evidence_safe_api_trace_required=1");
    puts("evidence_review_owner_required=1");
    puts("evidence_release_gate_required=1");
    puts("gate_unmapped_boundary_blocks_release=1");
    puts("gate_missing_method_blocks_release=1");
    puts("gate_missing_negative_fixture_blocks_release=1");
    puts("gate_missing_safe_api_trace_blocks_release=1");
    puts("gate_missing_owner_review_blocks_release=1");
    puts("gate_missing_repeatability_blocks_release=1");
    puts("gate_secret_capture_blocks_release=1");
    puts("gate_production_claim_without_runtime_evidence_blocks_release=1");
    puts("evidence_repeatability_required=1");
    puts("evidence_redaction_required=1");
    puts("evidence_timestamp_and_revision_required=1");
    puts("evidence_fail_closed_result_required=1");
    puts("evidence_no_secret_capture_required=1");
    puts("host_mutation=0");
    puts("network=0");
    puts("host_scan=0");
    puts("production_protection_claim=0");
    puts("source=owasp-injection-and-nist-ssdf");
}

void latticra_cli_print_prevention_gate(void) {
    puts("LATTICRA PREVENTION GATE REPORT");
    puts("project=latticra");
    puts("mode=no-effect");
    puts("installed_system_scope=1");
    puts("gate_schema_version=1");
    puts("gate_scope=application-release-decision-support");
    puts("gate_default=block-until-evidence-complete");
    puts("gate_boundary_inventory_required=1");
    puts("gate_method_matrix_required=1");
    puts("gate_fixture_coverage_required=1");
    puts("gate_safe_api_trace_required=1");
    puts("gate_owner_review_required=1");
    puts("gate_repeatable_result_required=1");
    puts("gate_secret_redaction_required=1");
    puts("gate_fail_closed_result_required=1");
    puts("gate_new_boundary_review_required=1");
    puts("gate_runtime_evidence_required_for_protection_claim=1");
    puts("release_without_complete_evidence_allowed=0");
    puts("production_claim_without_runtime_evidence_allowed=0");
    puts("decision_authority=application-owner");
    puts("host_mutation=0");
    puts("network=0");
    puts("host_scan=0");
    puts("production_protection_claim=0");
    puts("source=owasp-injection-and-nist-ssdf");
}

void latticra_cli_print_prevention_fixtures(void) {
    puts("LATTICRA PREVENTION FIXTURE REPORT");
    puts("project=latticra");
    puts("mode=no-effect");
    puts("installed_system_scope=1");
    puts("fixture_schema_version=1");
    puts("fixture_scope=adversarial-negative-tests");
    puts("fixture_set_count=16");
    puts("fixture_sql=data-value-separator-rejection");
    puts("fixture_sql_identifier=unknown-name-and-reserved-word-rejection");
    puts("fixture_nosql=operator-key-smuggling-rejection");
    puts("fixture_ldap=filter-metacharacter-neutralization");
    puts("fixture_xpath=expression-control-character-rejection");
    puts("fixture_os_command=separator-and-option-smuggling-rejection");
    puts("fixture_program_argument=end-of-options-boundary");
    puts("fixture_xss=contextual-output-escape-set");
    puts("fixture_ssrf=scheme-host-port-and-rebind-deny");
    puts("fixture_path=traversal-and-link-escape-deny");
    puts("fixture_xml=external-entity-and-dtd-deny");
    puts("fixture_deserialization=native-object-graph-deny");
    puts("fixture_template=user-template-code-deny");
    puts("fixture_log=crlf-neutralization");
    puts("fixture_secret=secret-redaction-before-record");
    puts("fixture_failure=deny-before-boundary");
    puts("fixture_payload_strings_in_report=0");
    puts("fixture_safe_harness_required=1");
    puts("fixture_ci_gate_required=1");
    puts("fixture_regression_on_new_boundary_required=1");
    puts("host_mutation=0");
    puts("network=0");
    puts("host_scan=0");
    puts("production_protection_claim=0");
    puts("source=owasp-injection-and-nist-ssdf");
}

int latticra_cli_print_prevention_method(const char *method_id) {
    size_t i;

    if (method_id == 0) {
        return 2;
    }

    for (i = 0u; i < sizeof(LATTICRA_PREVENTION_METHODS) / sizeof(LATTICRA_PREVENTION_METHODS[0]); i++) {
        const LatticraPreventionMethod *method = &LATTICRA_PREVENTION_METHODS[i];
        if (strcmp(method_id, method->id) == 0) {
            puts("LATTICRA PREVENTION METHOD");
            puts("project=latticra");
            puts("mode=no-effect");
            printf("method_id=%s\n", method->id);
            printf("interpreter_boundary=%s\n", method->interpreter_boundary);
            printf("primary_rule=%s\n", method->primary_rule);
            printf("required_controls=%s\n", method->required_controls);
            printf("source=%s\n", method->source);
            puts("host_mutation=0");
            puts("network=0");
            puts("host_scan=0");
            puts("production_protection_claim=0");
            puts("operator_visible_evidence_required=1");
            return 0;
        }
    }

    return 2;
}

static void latticra_cli_print_usage(void) {
    fputs("usage: latticra [--status|--version|--report|--effect-status|--prevention-research|--prevention-boundary|--prevention-evidence|--prevention-gate|--prevention-fixtures|--prevention-method <id>]\n", stderr);
    fputs(" (full binary with --authority/--lat-authority built via scripts/build-latticra.sh or make latticra)\n", stderr);
}

#if !defined(USE_LATTICRA_CPP_MAIN)
/* Standalone C main disabled when building the C++ unified driver binary. */
int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "--status") == 0) {
        latticra_cli_print_status();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--report") == 0) {
        latticra_cli_print_status();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        latticra_cli_print_version();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--effect-status") == 0) {
        latticra_cli_print_effect_status();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--prevention-research") == 0) {
        latticra_cli_print_prevention_research();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--prevention-boundary") == 0) {
        latticra_cli_print_prevention_boundary();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--prevention-evidence") == 0) {
        latticra_cli_print_prevention_evidence();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--prevention-gate") == 0) {
        latticra_cli_print_prevention_gate();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--prevention-fixtures") == 0) {
        latticra_cli_print_prevention_fixtures();
        return 0;
    }

    if (argc == 3 && strcmp(argv[1], "--prevention-method") == 0) {
        int method_status = latticra_cli_print_prevention_method(argv[2]);
        if (method_status == 0) {
            return 0;
        }
        latticra_cli_print_usage();
        return method_status;
    }

    latticra_cli_print_usage();
    return 2;
}
#endif


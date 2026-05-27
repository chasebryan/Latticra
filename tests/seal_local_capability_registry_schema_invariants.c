#include "latticra/seal_local_capability_registry_schema.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static latticra_seal_local_capability_registry_entry_t valid_entry(const char *suffix) {
    latticra_seal_local_capability_registry_entry_t entry;

    memset(&entry, 0, sizeof(entry));
    (void)snprintf(entry.capability_id,
                   sizeof(entry.capability_id),
                   "seal.local.registry.%s",
                   suffix != NULL ? suffix : "entry");
    copy_literal(entry.capability_namespace, sizeof(entry.capability_namespace), "seal.local");
    (void)snprintf(entry.capability_name,
                   sizeof(entry.capability_name),
                   "seal.local.registry.%s",
                   suffix != NULL ? suffix : "entry");
    copy_literal(entry.capability_description,
                 sizeof(entry.capability_description),
                 "Describes local Seal capability schema metadata without effects.");
    entry.capability_scope =
        LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_OPERATOR_REVIEW_BOUNDARY;
    entry.capability_effect_class = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NONE;
    entry.capability_authority_class =
        LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_DESCRIPTIVE_ONLY;
    copy_literal(entry.capability_default_decision,
                 sizeof(entry.capability_default_decision),
                 "deny");
    entry.capability_requires_guarded_allowlist = 1u;
    entry.capability_requires_policy_decision = 1u;
    entry.capability_requires_runtime_gate = 1u;
    entry.capability_requires_runtime_dry_run = 1u;
    entry.capability_requires_operator_review = 1u;
    entry.capability_requires_verification_receipt = 1u;
    entry.capability_requires_signed_request = 1u;
    entry.capability_grants_authority = 0u;
    entry.capability_executes_tool = 0u;
    entry.capability_reads_host = 0u;
    entry.capability_writes_host = 0u;
    entry.capability_uses_network = 0u;
    entry.capability_report_only = 1u;
    entry.capability_deprecated = 0u;
    copy_literal(entry.capability_blocked_reason,
                 sizeof(entry.capability_blocked_reason),
                 "registry-schema-is-descriptive-only");
    return entry;
}

static int initialized_schema_is_report_only(void) {
    latticra_seal_local_capability_registry_schema_t schema;

    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_init(&schema) ==
                    LATTICRA_STATUS_OK,
                "schema init");
    EXPECT_TRUE(strcmp(schema.registry_schema_profile,
                       "latticra-seal-local-capability-registry-schema/0.1") == 0,
                "profile");
    EXPECT_TRUE(strcmp(schema.registry_format_version, "0.1") == 0, "format");
    EXPECT_TRUE(strcmp(schema.registry_scope, "local-only") == 0, "scope");
    EXPECT_TRUE(strcmp(schema.registry_mode, "report-only") == 0, "mode");
    EXPECT_TRUE(strcmp(schema.registry_status, "contract-only") == 0, "status");
    EXPECT_TRUE(schema.registry_contract_present == 1u, "contract present");
    EXPECT_TRUE(schema.registry_schema_planning_only == 1u, "planning only");
    EXPECT_TRUE(schema.registry_loader_implemented == 0u, "loader");
    EXPECT_TRUE(schema.registry_file_loading_supported == 0u, "file loading");
    EXPECT_TRUE(schema.registry_network_loading_supported == 0u, "network loading");
    EXPECT_TRUE(schema.registry_signature_verification_supported == 0u, "signature");
    EXPECT_TRUE(schema.registry_trust_store_supported == 0u, "trust store");
    EXPECT_TRUE(schema.registry_entry_count == 0u, "entry count");
    EXPECT_TRUE(schema.registry_entry_count_max == 16u, "entry max");
    EXPECT_TRUE(schema.registry_entry_id_max == 64u, "id max");
    EXPECT_TRUE(schema.registry_namespace_max == 64u, "namespace max");
    EXPECT_TRUE(schema.registry_name_max == 96u, "name max");
    EXPECT_TRUE(schema.registry_description_max == 256u, "description max");
    EXPECT_TRUE(schema.registry_blocked_reason_max == 160u, "reason max");
    EXPECT_TRUE(schema.default_action_deny == 1u, "default deny");
    EXPECT_TRUE(schema.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(schema.effect_performed == 0u, "effect");
    EXPECT_TRUE(schema.host_read_performed == 0u, "read");
    EXPECT_TRUE(schema.host_write_performed == 0u, "write");
    EXPECT_TRUE(schema.network_performed == 0u, "network");
    EXPECT_TRUE(schema.last_error == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK,
                "last error");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_validate(&schema) ==
                    LATTICRA_STATUS_OK,
                "validate");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_is_report_only(&schema) == 1,
                "helper");
    return 0;
}

static int default_fixture_entry_stays_denied(void) {
    latticra_seal_local_capability_registry_schema_t schema;
    const latticra_seal_local_capability_registry_entry_t *entry;
    char rendered[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_init(&schema) ==
                    LATTICRA_STATUS_OK,
                "schema init fixture");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_add_default_entry(&schema) ==
                    LATTICRA_STATUS_OK,
                "add default");
    EXPECT_TRUE(schema.last_error == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK,
                "default ok");
    EXPECT_TRUE(schema.registry_entry_count == 1u, "default count");
    entry = &schema.entries[0];
    EXPECT_TRUE(strcmp(entry->capability_id, "seal.local.registry.schema") == 0, "id");
    EXPECT_TRUE(strcmp(entry->capability_namespace, "seal.local") == 0, "namespace");
    EXPECT_TRUE(strcmp(entry->capability_name, "seal.local.registry.schema") == 0, "name");
    EXPECT_TRUE(entry->capability_scope ==
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_OPERATOR_REVIEW_BOUNDARY,
                "scope");
    EXPECT_TRUE(entry->capability_effect_class ==
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NONE,
                "effect");
    EXPECT_TRUE(entry->capability_authority_class ==
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_DESCRIPTIVE_ONLY,
                "authority");
    EXPECT_TRUE(strcmp(entry->capability_default_decision, "deny") == 0, "decision");
    EXPECT_TRUE(entry->capability_requires_guarded_allowlist == 1u, "allowlist");
    EXPECT_TRUE(entry->capability_requires_policy_decision == 1u, "policy");
    EXPECT_TRUE(entry->capability_requires_runtime_gate == 1u, "gate");
    EXPECT_TRUE(entry->capability_requires_runtime_dry_run == 1u, "dry run");
    EXPECT_TRUE(entry->capability_requires_operator_review == 1u, "operator");
    EXPECT_TRUE(entry->capability_requires_verification_receipt == 1u, "receipt");
    EXPECT_TRUE(entry->capability_requires_signed_request == 1u, "signed");
    EXPECT_TRUE(entry->capability_grants_authority == 0u, "grants");
    EXPECT_TRUE(entry->capability_executes_tool == 0u, "executes");
    EXPECT_TRUE(entry->capability_reads_host == 0u, "reads");
    EXPECT_TRUE(entry->capability_writes_host == 0u, "writes");
    EXPECT_TRUE(entry->capability_uses_network == 0u, "network");
    EXPECT_TRUE(entry->capability_report_only == 1u, "report only");
    EXPECT_TRUE(strcmp(entry->capability_blocked_reason,
                       "registry-schema-is-descriptive-only") == 0,
                "reason");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_is_report_only(&schema) == 1,
                "fixture helper");

    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_render(
                    &schema,
                    rendered,
                    sizeof(rendered)) == LATTICRA_STATUS_OK,
                "render");
    EXPECT_TRUE(strstr(rendered,
                       "LATTICRA SEAL LOCAL CAPABILITY REGISTRY SCHEMA REPORT") != 0,
                "render header");
    EXPECT_TRUE(strstr(rendered,
                       "registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1") != 0,
                "render profile");
    EXPECT_TRUE(strstr(rendered, "registry_entry_count=1") != 0, "render count");
    EXPECT_TRUE(strstr(rendered, "registry_loader_implemented=0") != 0, "render loader");
    EXPECT_TRUE(strstr(rendered, "registry_file_loading_supported=0") != 0,
                "render file");
    EXPECT_TRUE(strstr(rendered, "registry_network_loading_supported=0") != 0,
                "render network loader");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0,
                "render runtime authority");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "render effect");
    EXPECT_TRUE(strstr(rendered, "capability_id=seal.local.registry.schema") != 0,
                "render id");
    EXPECT_TRUE(strstr(rendered, "capability_scope=operator-review-boundary") != 0,
                "render scope");
    EXPECT_TRUE(strstr(rendered, "capability_effect_class=none") != 0,
                "render effect class");
    EXPECT_TRUE(strstr(rendered, "capability_authority_class=descriptive-only") != 0,
                "render authority class");
    EXPECT_TRUE(strstr(rendered, "capability_default_decision=deny") != 0,
                "render decision");
    EXPECT_TRUE(strstr(rendered, "capability_grants_authority=0") != 0,
                "render grants");
    EXPECT_TRUE(strstr(rendered, "capability_executes_tool=0") != 0,
                "render execution");
    EXPECT_TRUE(strstr(rendered, "capability_reads_host=0") != 0, "render read");
    EXPECT_TRUE(strstr(rendered, "capability_writes_host=0") != 0, "render write");
    EXPECT_TRUE(strstr(rendered, "capability_uses_network=0") != 0, "render network");
    EXPECT_TRUE(strstr(rendered, "capability_report_only=1") != 0, "render report");
    EXPECT_TRUE(strstr(rendered, "error=ok") != 0, "render error");
    return 0;
}

static int invalid_entry_sets_error(
    latticra_seal_local_capability_registry_entry_t entry,
    latticra_seal_local_capability_registry_schema_error_t expected_error) {
    latticra_seal_local_capability_registry_schema_t schema;

    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_init(&schema) ==
                    LATTICRA_STATUS_OK,
                "invalid init");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_add_entry(&schema, &entry) ==
                    LATTICRA_STATUS_OK,
                "invalid add");
    EXPECT_TRUE(schema.last_error == expected_error, "invalid expected error");
    EXPECT_TRUE(schema.registry_entry_count == 0u, "invalid not added");
    EXPECT_TRUE(schema.runtime_authority_granted == 0u, "invalid runtime authority");
    EXPECT_TRUE(schema.effect_performed == 0u, "invalid effect");
    EXPECT_TRUE(schema.host_read_performed == 0u, "invalid read");
    EXPECT_TRUE(schema.host_write_performed == 0u, "invalid write");
    EXPECT_TRUE(schema.network_performed == 0u, "invalid network");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_is_report_only(&schema) == 0,
                "invalid helper");
    return 0;
}

static int invalid_entries_fail_closed(void) {
    latticra_seal_local_capability_registry_entry_t entry;

    entry = valid_entry("invalid-scope");
    entry.capability_scope = (latticra_seal_local_capability_registry_scope_t)99;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_SCOPE) == 0,
                "invalid scope");

    entry = valid_entry("invalid-effect");
    entry.capability_effect_class =
        (latticra_seal_local_capability_registry_effect_class_t)99;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_EFFECT_CLASS) == 0,
                "invalid effect");

    entry = valid_entry("invalid-authority");
    entry.capability_authority_class =
        (latticra_seal_local_capability_registry_authority_class_t)99;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_AUTHORITY_CLASS) == 0,
                "invalid authority");

    entry = valid_entry("allow");
    copy_literal(entry.capability_default_decision,
                 sizeof(entry.capability_default_decision),
                 "allow");
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_DEFAULT_DECISION) == 0,
                "allow rejected");

    entry = valid_entry("grant");
    entry.capability_grants_authority = 1u;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_GRANT_AUTHORITY) == 0,
                "grant rejected");

    entry = valid_entry("execute");
    entry.capability_executes_tool = 1u;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT) == 0,
                "execute rejected");

    entry = valid_entry("read");
    entry.capability_reads_host = 1u;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT) == 0,
                "read rejected");

    entry = valid_entry("write");
    entry.capability_writes_host = 1u;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT) == 0,
                "write rejected");

    entry = valid_entry("network");
    entry.capability_uses_network = 1u;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT) == 0,
                "network rejected");

    entry = valid_entry("non-report");
    entry.capability_report_only = 0u;
    EXPECT_TRUE(invalid_entry_sets_error(
                    entry,
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_NON_REPORT_ONLY_ENTRY) == 0,
                "non report rejected");
    return 0;
}

static int failure_cases_stay_bounded(void) {
    latticra_seal_local_capability_registry_schema_t schema;
    latticra_seal_local_capability_registry_entry_t entry;
    char tiny[1];
    unsigned i;

    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_init(0) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null init");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_validate(0) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null validate");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_add_entry(0, 0) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null add schema");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_render(0, tiny, sizeof(tiny)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null render schema");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_is_report_only(0) == 0,
                "null helper");

    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_init(&schema) ==
                    LATTICRA_STATUS_OK,
                "failure init");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_add_entry(&schema, 0) ==
                    LATTICRA_STATUS_OK,
                "null entry status");
    EXPECT_TRUE(schema.last_error == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_INPUT,
                "null entry error");
    EXPECT_TRUE(schema.registry_entry_count == 0u, "null entry count");

    entry = valid_entry("capacity");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_init(&schema) ==
                    LATTICRA_STATUS_OK,
                "capacity init");
    for (i = 0u; i < LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX; ++i) {
        (void)snprintf(entry.capability_id, sizeof(entry.capability_id), "seal.local.%u", i);
        (void)snprintf(entry.capability_name, sizeof(entry.capability_name), "seal.local.%u", i);
        EXPECT_TRUE(latticra_seal_local_capability_registry_schema_add_entry(&schema, &entry) ==
                        LATTICRA_STATUS_OK,
                    "capacity add");
    }
    EXPECT_TRUE(schema.registry_entry_count == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX,
                "capacity full");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_add_entry(&schema, &entry) ==
                    LATTICRA_STATUS_OK,
                "capacity overflow status");
    EXPECT_TRUE(schema.last_error ==
                    LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_CAPACITY_EXCEEDED,
                "capacity overflow error");

    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_render(&schema, tiny, sizeof(tiny)) ==
                    LATTICRA_STATUS_BUFFER_TOO_SMALL,
                "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render cleared");
    EXPECT_TRUE(latticra_seal_local_capability_registry_schema_render(&schema, 0, sizeof(tiny)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null render buffer");
    return 0;
}

int main(void) {
    if (initialized_schema_is_report_only() != 0) {
        return 1;
    }
    if (default_fixture_entry_stays_denied() != 0) {
        return 1;
    }
    if (invalid_entries_fail_closed() != 0) {
        return 1;
    }
    if (failure_cases_stay_bounded() != 0) {
        return 1;
    }
    printf("seal local capability registry schema invariants: ok\n");
    return 0;
}

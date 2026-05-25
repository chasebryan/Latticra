#include "latticra/lat_model.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

#define EXPECT_STR_EQ(actual, expected, message) \
    do { \
        if (strcmp((actual), (expected)) != 0) { \
            fprintf(stderr, "FAIL: %s: expected '%s' got '%s'\n", message, (expected), (actual)); \
            return 1; \
        } \
    } while (0)

static const char FOUNDATION_MODEL[] =
    "lat module FoundationModule {\n"
    "  state RootCell {\n"
    "    origin = \"0/0\"\n"
    "    route = \"ROOT\"\n"
    "    axis = \"ROOT\"\n"
    "    path = \"/\"\n"
    "    health = \"ok\"\n"
    "    risk = \"low\"\n"
    "    lock = \"open\"\n"
    "    host_effect = none\n"
    "    external_effect = none\n"
    "  }\n"
    "  effect PreviewOnly {\n"
    "    host = none\n"
    "    external = none\n"
    "    network = none\n"
    "    hardware = none\n"
    "  }\n"
    "  policy SafePreview {\n"
    "    require risk != \"high\"\n"
    "    require lock == \"open\"\n"
    "    ensure host_effect == none\n"
    "    ensure external_effect == none\n"
    "  }\n"
    "  transition MoveRight from RootCell {\n"
    "    require lock == \"open\"\n"
    "    effect host = none\n"
    "    effect external = none\n"
    "  }\n"
    "  assertion RootCellIsSafe {\n"
    "    require health == \"ok\"\n"
    "    require host_effect == none\n"
    "    require external_effect == none\n"
    "  }\n"
    "}\n";

static int normalize_foundation(
    latticra_lat_parse_result_t *parse,
    latticra_lat_semantic_result_t *semantic,
    latticra_lat_model_t *model) {
    EXPECT_TRUE(latticra_lat_parse_source(FOUNDATION_MODEL, strlen(FOUNDATION_MODEL), parse) == LATTICRA_STATUS_OK, "parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(parse, semantic) == LATTICRA_STATUS_OK, "semantic status OK");
    EXPECT_TRUE(latticra_lat_model_normalize_module(parse, semantic, model) == LATTICRA_STATUS_OK, "model status OK");
    EXPECT_TRUE(model->error == LATTICRA_LAT_MODEL_OK, "model OK");
    return 0;
}

static int lat_model_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_model_error_label(LATTICRA_LAT_MODEL_OK), "ok", "model ok label");
    EXPECT_STR_EQ(latticra_lat_model_error_label(LATTICRA_LAT_MODEL_NULL_ARGUMENT), "null_argument", "model null label");
    EXPECT_STR_EQ(latticra_lat_model_error_label(LATTICRA_LAT_MODEL_PARSE_NOT_OK), "parse_not_ok", "model parse label");
    EXPECT_STR_EQ(latticra_lat_model_error_label(LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK), "semantic_not_ok", "model semantic label");
    EXPECT_STR_EQ(latticra_lat_model_error_label(LATTICRA_LAT_MODEL_NO_EFFECT_VIOLATION), "no_effect_violation", "model flags label");
    EXPECT_STR_EQ(latticra_lat_model_clause_role_label(LATTICRA_LAT_MODEL_CLAUSE_FIELD), "field", "field role label");
    EXPECT_STR_EQ(latticra_lat_model_clause_role_label(LATTICRA_LAT_MODEL_CLAUSE_REQUIRE), "require", "require role label");
    EXPECT_STR_EQ(latticra_lat_model_clause_role_label(LATTICRA_LAT_MODEL_CLAUSE_ENSURE), "ensure", "ensure role label");
    EXPECT_STR_EQ(latticra_lat_model_clause_role_label(LATTICRA_LAT_MODEL_CLAUSE_EFFECT), "effect", "effect role label");
    return 0;
}

static int lat_model_normalizes_foundation_counts(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "foundation normalized");
    EXPECT_STR_EQ(model.module_name, "FoundationModule", "model module name");
    EXPECT_TRUE(model.declaration_count == 5u, "model declaration count");
    EXPECT_TRUE(model.clause_count == 23u, "model clause count");
    EXPECT_TRUE(model.state_count == 1u, "model state count");
    EXPECT_TRUE(model.policy_count == 1u, "model policy count");
    EXPECT_TRUE(model.transition_count == 1u, "model transition count");
    EXPECT_TRUE(model.assertion_count == 1u, "model assertion count");
    EXPECT_TRUE(model.effect_count == 1u, "model effect count");
    return 0;
}

static int lat_model_builds_typed_declaration_indices(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    size_t state_index;
    size_t transition_index;

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "typed declaration model normalized");
    state_index = model.state_indices[0];
    transition_index = model.transition_indices[0];
    EXPECT_TRUE(state_index == 0u, "state index table");
    EXPECT_TRUE(model.effect_indices[0] == 1u, "effect index table");
    EXPECT_TRUE(model.policy_indices[0] == 2u, "policy index table");
    EXPECT_TRUE(transition_index == 3u, "transition index table");
    EXPECT_TRUE(model.assertion_indices[0] == 4u, "assertion index table");
    EXPECT_TRUE(model.declarations[state_index].kind == LATTICRA_LAT_DECLARATION_STATE, "state kind normalized");
    EXPECT_STR_EQ(model.declarations[state_index].name, "RootCell", "state name normalized");
    EXPECT_STR_EQ(model.declarations[transition_index].source_name, "RootCell", "transition source normalized");
    EXPECT_TRUE(model.declarations[transition_index].source_declaration_index == state_index, "transition source resolved");
    return 0;
}

static int lat_model_builds_clause_roles_and_owners(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    size_t state_index;
    size_t policy_index;
    size_t transition_index;
    size_t state_clause_index;
    size_t policy_clause_index;
    size_t transition_effect_index;

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "clause model normalized");
    state_index = model.state_indices[0];
    policy_index = model.policy_indices[0];
    transition_index = model.transition_indices[0];
    state_clause_index = model.declarations[state_index].first_clause_index;
    policy_clause_index = model.declarations[policy_index].first_clause_index;
    transition_effect_index = model.declarations[transition_index].first_clause_index + 1u;

    EXPECT_TRUE(model.clauses[state_clause_index].role == LATTICRA_LAT_MODEL_CLAUSE_FIELD, "state field role");
    EXPECT_TRUE(model.clauses[state_clause_index].owner_declaration_index == state_index, "state field owner");
    EXPECT_STR_EQ(model.clauses[state_clause_index].name, "origin", "state field name");
    EXPECT_STR_EQ(model.clauses[state_clause_index].operator_text, "=", "state field operator");
    EXPECT_STR_EQ(model.clauses[state_clause_index].value, "0/0", "state field value");
    EXPECT_TRUE(model.clauses[state_clause_index].effect == LATTICRA_LAT_EFFECT_UNKNOWN, "state field effect unknown");
    EXPECT_TRUE(model.clauses[policy_clause_index].role == LATTICRA_LAT_MODEL_CLAUSE_REQUIRE, "policy require role");
    EXPECT_TRUE(model.clauses[policy_clause_index + 2u].role == LATTICRA_LAT_MODEL_CLAUSE_ENSURE, "policy ensure role");
    EXPECT_TRUE(model.clauses[transition_effect_index].role == LATTICRA_LAT_MODEL_CLAUSE_EFFECT, "transition effect role");
    EXPECT_TRUE(model.clauses[transition_effect_index].effect == LATTICRA_LAT_EFFECT_NONE, "transition effect remains none");
    return 0;
}

static int lat_model_rejects_parse_failure(void) {
    static const char source[] = "lat module Bad { unknown Thing { } }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;

    EXPECT_TRUE(latticra_lat_parse_source(source, strlen(source), &parse) == LATTICRA_STATUS_OK, "bad parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(&parse, &semantic) == LATTICRA_STATUS_OK, "bad semantic status OK");
    EXPECT_TRUE(latticra_lat_model_normalize_module(&parse, &semantic, &model) == LATTICRA_STATUS_OK, "bad model status OK");
    EXPECT_TRUE(model.error == LATTICRA_LAT_MODEL_PARSE_NOT_OK, "parse failure rejected");
    EXPECT_TRUE(model.declaration_count == 0u, "parse failure declaration count");
    return 0;
}

static int lat_model_rejects_semantic_failure(void) {
    static const char source[] =
        "lat module BadTransition {\n"
        "  transition MoveRight from MissingState {\n"
        "    require lock == \"open\"\n"
        "    effect host = none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;

    EXPECT_TRUE(latticra_lat_parse_source(source, strlen(source), &parse) == LATTICRA_STATUS_OK, "semantic parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(&parse, &semantic) == LATTICRA_STATUS_OK, "semantic failure status OK");
    EXPECT_TRUE(latticra_lat_model_normalize_module(&parse, &semantic, &model) == LATTICRA_STATUS_OK, "semantic model status OK");
    EXPECT_TRUE(model.error == LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK, "semantic failure rejected");
    return 0;
}

static int lat_model_preserves_no_effect_flags(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "flags model normalized");
    EXPECT_TRUE(model.no_effect == 1, "model no effect");
    EXPECT_TRUE(model.execution_allowed == 0, "model execution flag");
    EXPECT_TRUE(model.mutation_allowed == 0, "model mutation flag");
    EXPECT_TRUE(model.server_allowed == 0, "model server flag");
    EXPECT_TRUE(model.recovery_allowed == 0, "model recovery flag");
    EXPECT_TRUE(model.hardware_allowed == 0, "model hardware flag");
    return 0;
}

static int lat_model_report_is_deterministic(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    char one[LATTICRA_LAT_MODEL_REPORT_MAX];
    char two[LATTICRA_LAT_MODEL_REPORT_MAX];

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "report model normalized");
    EXPECT_TRUE(latticra_lat_model_report(&model, one, sizeof(one)) == LATTICRA_STATUS_OK, "first model report");
    EXPECT_TRUE(latticra_lat_model_report(&model, two, sizeof(two)) == LATTICRA_STATUS_OK, "second model report");
    EXPECT_STR_EQ(one, two, "model report deterministic");
    EXPECT_TRUE(strstr(one, "LAT MODEL NORMALIZATION REPORT\n") != 0, "model report header");
    EXPECT_TRUE(strstr(one, "error=ok\n") != 0, "model report ok");
    EXPECT_TRUE(strstr(one, "first_transition_source_index=0\n") != 0, "model transition source report");
    EXPECT_TRUE(strstr(one, "first_clause_index=0\n") != 0, "model first clause index report");
    EXPECT_TRUE(strstr(one, "first_clause_role=field\n") != 0, "model first clause role report");
    EXPECT_TRUE(strstr(one, "first_clause_effect=unknown\n") != 0, "model first clause effect report");
    EXPECT_TRUE(strstr(one, "first_clause_name=origin\n") != 0, "model first clause name report");
    EXPECT_TRUE(strstr(one, "first_clause_operator==\n") != 0, "model first clause operator report");
    EXPECT_TRUE(strstr(one, "first_clause_value=0/0\n") != 0, "model first clause value report");
    return 0;
}

static int lat_model_report_rejects_small_buffer(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lat_model_t model;
    char tiny[8];

    EXPECT_TRUE(normalize_foundation(&parse, &semantic, &model) == 0, "small report model normalized");
    EXPECT_TRUE(latticra_lat_model_report(&model, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small model report rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small model report cleared");
    return 0;
}

int main(void) {
    if (lat_model_labels_are_stable() != 0) return 1;
    if (lat_model_normalizes_foundation_counts() != 0) return 1;
    if (lat_model_builds_typed_declaration_indices() != 0) return 1;
    if (lat_model_builds_clause_roles_and_owners() != 0) return 1;
    if (lat_model_rejects_parse_failure() != 0) return 1;
    if (lat_model_rejects_semantic_failure() != 0) return 1;
    if (lat_model_preserves_no_effect_flags() != 0) return 1;
    if (lat_model_report_is_deterministic() != 0) return 1;
    if (lat_model_report_rejects_small_buffer() != 0) return 1;

    puts("lat_model_normalization_invariants: ok");
    return 0;
}

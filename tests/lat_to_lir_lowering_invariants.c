#include "latticra/lat_to_lir.h"

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

static int lower_foundation(
    latticra_lat_parse_result_t *parse,
    latticra_lat_semantic_result_t *semantic,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *lowering) {
    EXPECT_TRUE(latticra_lat_parse_source(FOUNDATION_MODEL, strlen(FOUNDATION_MODEL), parse) == LATTICRA_STATUS_OK, "parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(parse, semantic) == LATTICRA_STATUS_OK, "semantic status OK");
    EXPECT_TRUE(latticra_lir_lower_lat_module(parse, semantic, module, lowering) == LATTICRA_STATUS_OK, "lowering status OK");
    return 0;
}

static int lat_to_lir_accepts_foundation_model(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "foundation lowered");
    EXPECT_TRUE(parse.error == LATTICRA_LAT_PARSE_OK, "parse ok");
    EXPECT_TRUE(semantic.error == LATTICRA_LAT_SEMANTIC_OK, "semantic ok");
    EXPECT_TRUE(lowering.error == LATTICRA_LAT_TO_LIR_OK, "lowering ok");
    EXPECT_TRUE(module.error == LATTICRA_LIR_OK, "lir ok");
    return 0;
}

static int lat_to_lir_sets_source_kind_lat_module(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "source kind lowered");
    EXPECT_TRUE(module.source_kind == LATTICRA_LIR_SOURCE_LAT_MODULE, "source kind set");
    EXPECT_STR_EQ(latticra_lir_source_kind_label(module.source_kind), "lat_module", "source kind label");
    return 0;
}

static int lat_to_lir_preserves_counts(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "count source lowered");
    EXPECT_TRUE(lowering.declaration_count == 5u, "declaration count");
    EXPECT_TRUE(lowering.clause_count == 23u, "clause count");
    EXPECT_TRUE(module.node_count == 29u, "node count");
    EXPECT_TRUE(module.edge_count == 29u, "edge count");
    return 0;
}

static int lat_to_lir_preserves_metadata(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "metadata source lowered");
    EXPECT_STR_EQ(module.module_name, "FoundationModule", "module name");
    EXPECT_STR_EQ(module.effect, "none", "effect label");
    EXPECT_STR_EQ(module.boundary, "lat_semantic_only", "boundary label");
    EXPECT_STR_EQ(module.nodes[4].name, "MoveRight", "transition node name");
    EXPECT_STR_EQ(module.nodes[4].binding, "RootCell", "transition source metadata");
    EXPECT_TRUE(module.edges[28].edge_kind == LATTICRA_LIR_EDGE_BINDS, "transition edge");
    return 0;
}

static int lat_to_lir_rejects_parse_error(void) {
    static const char source[] = "lat module Bad { unknown Thing { } }\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(latticra_lat_parse_source(source, strlen(source), &parse) == LATTICRA_STATUS_OK, "bad parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(&parse, &semantic) == LATTICRA_STATUS_OK, "bad semantic status OK");
    EXPECT_TRUE(latticra_lir_lower_lat_module(&parse, &semantic, &module, &lowering) == LATTICRA_STATUS_OK, "bad lowering status OK");
    EXPECT_TRUE(lowering.error == LATTICRA_LAT_TO_LIR_PARSE_NOT_OK, "parse failure rejected");
    return 0;
}

static int lat_to_lir_rejects_semantic_error(void) {
    static const char source[] =
        "lat module BadTransition {\n"
        "  transition MoveRight from MissingState {\n"
        "    require lock == \"open\"\n"
        "    effect host = none\n"
        "  }\n"
        "}\n";
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(latticra_lat_parse_source(source, strlen(source), &parse) == LATTICRA_STATUS_OK, "semantic parse status OK");
    EXPECT_TRUE(latticra_lat_validate_module(&parse, &semantic) == LATTICRA_STATUS_OK, "semantic failure status OK");
    EXPECT_TRUE(latticra_lir_lower_lat_module(&parse, &semantic, &module, &lowering) == LATTICRA_STATUS_OK, "semantic lowering status OK");
    EXPECT_TRUE(lowering.error == LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK, "semantic failure rejected");
    return 0;
}

static int lat_to_lir_preserves_no_effect_flags(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "flags source lowered");
    EXPECT_TRUE(module.no_effect == 1, "module no effect");
    EXPECT_TRUE(module.execution_allowed == 0, "module execution flag");
    EXPECT_TRUE(module.mutation_allowed == 0, "module mutation flag");
    EXPECT_TRUE(lowering.no_effect == 1, "result no effect");
    EXPECT_TRUE(lowering.execution_allowed == 0, "result execution flag");
    EXPECT_TRUE(lowering.mutation_allowed == 0, "result mutation flag");
    return 0;
}

static int lat_to_lir_report_is_deterministic(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    char one[LATTICRA_LAT_TO_LIR_REPORT_MAX];
    char two[LATTICRA_LAT_TO_LIR_REPORT_MAX];
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "report source lowered");
    EXPECT_TRUE(latticra_lat_to_lir_report(&lowering, one, sizeof(one)) == LATTICRA_STATUS_OK, "first report");
    EXPECT_TRUE(latticra_lat_to_lir_report(&lowering, two, sizeof(two)) == LATTICRA_STATUS_OK, "second report");
    EXPECT_STR_EQ(one, two, "report deterministic");
    EXPECT_TRUE(strstr(one, "LAT TO LIR LOWERING REPORT\n") != 0, "report header");
    EXPECT_TRUE(strstr(one, "error=ok\n") != 0, "report ok");
    return 0;
}

static int lat_to_lir_report_rejects_small_buffer(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    char tiny[8];
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "small report source lowered");
    EXPECT_TRUE(latticra_lat_to_lir_report(&lowering, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer rejected");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    return 0;
}

static int lat_to_lir_error_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lat_to_lir_error_label(LATTICRA_LAT_TO_LIR_OK), "ok", "ok label");
    EXPECT_STR_EQ(latticra_lat_to_lir_error_label(LATTICRA_LAT_TO_LIR_NULL_ARGUMENT), "null_argument", "null label");
    EXPECT_STR_EQ(latticra_lat_to_lir_error_label(LATTICRA_LAT_TO_LIR_PARSE_NOT_OK), "parse_not_ok", "parse label");
    EXPECT_STR_EQ(latticra_lat_to_lir_error_label(LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK), "semantic_not_ok", "semantic label");
    EXPECT_STR_EQ(latticra_lat_to_lir_error_label(LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION), "no_effect_violation", "flag label");
    EXPECT_STR_EQ(latticra_lat_to_lir_error_label(LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED), "capacity_exceeded", "capacity label");
    return 0;
}

int main(void) {
    if (lat_to_lir_accepts_foundation_model() != 0) return 1;
    if (lat_to_lir_sets_source_kind_lat_module() != 0) return 1;
    if (lat_to_lir_preserves_counts() != 0) return 1;
    if (lat_to_lir_preserves_metadata() != 0) return 1;
    if (lat_to_lir_rejects_parse_error() != 0) return 1;
    if (lat_to_lir_rejects_semantic_error() != 0) return 1;
    if (lat_to_lir_preserves_no_effect_flags() != 0) return 1;
    if (lat_to_lir_report_is_deterministic() != 0) return 1;
    if (lat_to_lir_report_rejects_small_buffer() != 0) return 1;
    if (lat_to_lir_error_labels_are_stable() != 0) return 1;

    puts("lat_to_lir_lowering_invariants: ok");
    return 0;
}

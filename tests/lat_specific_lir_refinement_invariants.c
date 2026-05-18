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
    EXPECT_TRUE(lowering->error == LATTICRA_LAT_TO_LIR_OK, "lowering OK");
    EXPECT_TRUE(module->error == LATTICRA_LIR_OK, "module OK");
    return 0;
}

static int lat_specific_lir_labels_are_stable(void) {
    EXPECT_STR_EQ(latticra_lir_node_kind_label(LATTICRA_LIR_NODE_LAT_STATE), "lat_state", "lat state label");
    EXPECT_STR_EQ(latticra_lir_node_kind_label(LATTICRA_LIR_NODE_LAT_POLICY), "lat_policy", "lat policy label");
    EXPECT_STR_EQ(latticra_lir_node_kind_label(LATTICRA_LIR_NODE_LAT_TRANSITION), "lat_transition", "lat transition label");
    EXPECT_STR_EQ(latticra_lir_node_kind_label(LATTICRA_LIR_NODE_LAT_ASSERTION), "lat_assertion", "lat assertion label");
    EXPECT_STR_EQ(latticra_lir_node_kind_label(LATTICRA_LIR_NODE_LAT_REQUIREMENT), "lat_requirement", "lat requirement label");
    EXPECT_STR_EQ(latticra_lir_node_kind_label(LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION), "lat_effect_declaration", "lat effect declaration label");
    EXPECT_STR_EQ(latticra_lir_edge_kind_label(LATTICRA_LIR_EDGE_TRANSITIONS_FROM), "transitions_from", "transition source edge label");
    return 0;
}

static int lat_specific_lir_uses_lat_declaration_node_kinds(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "foundation lowered");
    EXPECT_TRUE(module.nodes[1].kind == LATTICRA_LIR_NODE_LAT_STATE, "state declaration node");
    EXPECT_TRUE(module.nodes[2].kind == LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION, "effect declaration node");
    EXPECT_TRUE(module.nodes[3].kind == LATTICRA_LIR_NODE_LAT_POLICY, "policy declaration node");
    EXPECT_TRUE(module.nodes[4].kind == LATTICRA_LIR_NODE_LAT_TRANSITION, "transition declaration node");
    EXPECT_TRUE(module.nodes[5].kind == LATTICRA_LIR_NODE_LAT_ASSERTION, "assertion declaration node");
    return 0;
}

static int lat_specific_lir_uses_lat_requirement_node_kind(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    size_t policy_index;
    size_t clause_index;
    size_t node_index;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "foundation lowered for requirement");
    policy_index = 2u;
    clause_index = parse.declarations[policy_index].first_clause_index;
    node_index = 1u + parse.declaration_count + clause_index;
    EXPECT_TRUE(module.nodes[node_index].kind == LATTICRA_LIR_NODE_LAT_REQUIREMENT, "requirement node kind");
    EXPECT_STR_EQ(module.nodes[node_index].binding, "require", "requirement binding label");
    return 0;
}

static int lat_specific_lir_uses_transition_source_edge_kind(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "foundation lowered for edge");
    EXPECT_TRUE(module.edges[module.edge_count - 1u].edge_kind == LATTICRA_LIR_EDGE_TRANSITIONS_FROM, "transition source edge kind");
    EXPECT_TRUE(module.edges[module.edge_count - 1u].from_index == 4u, "transition edge from transition");
    EXPECT_TRUE(module.edges[module.edge_count - 1u].to_index == 1u, "transition edge to source state");
    return 0;
}

static int lat_specific_lir_preserves_counts_and_no_effect_flags(void) {
    latticra_lat_parse_result_t parse;
    latticra_lat_semantic_result_t semantic;
    latticra_lir_module_t module;
    latticra_lat_to_lir_result_t lowering;
    EXPECT_TRUE(lower_foundation(&parse, &semantic, &module, &lowering) == 0, "foundation lowered for counts");
    EXPECT_TRUE(module.node_count == 29u, "node count preserved");
    EXPECT_TRUE(module.edge_count == 29u, "edge count preserved");
    EXPECT_TRUE(module.no_effect == 1, "module no effect");
    EXPECT_TRUE(module.execution_allowed == 0, "module execution flag");
    EXPECT_TRUE(module.mutation_allowed == 0, "module mutation flag");
    EXPECT_TRUE(module.server_allowed == 0, "module server flag");
    EXPECT_TRUE(module.recovery_allowed == 0, "module recovery flag");
    EXPECT_TRUE(module.hardware_allowed == 0, "module hardware flag");
    return 0;
}

int main(void) {
    if (lat_specific_lir_labels_are_stable() != 0) return 1;
    if (lat_specific_lir_uses_lat_declaration_node_kinds() != 0) return 1;
    if (lat_specific_lir_uses_lat_requirement_node_kind() != 0) return 1;
    if (lat_specific_lir_uses_transition_source_edge_kind() != 0) return 1;
    if (lat_specific_lir_preserves_counts_and_no_effect_flags() != 0) return 1;

    puts("lat_specific_lir_refinement_invariants: ok");
    return 0;
}

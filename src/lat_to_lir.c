#include "latticra/lat_to_lir.h"

#include <stdio.h>
#include <string.h>

#define LATTICRA_LAT_TO_LIR_ROOT_PARENT 0u
#define LATTICRA_LAT_TO_LIR_MODULE_INDEX 0u
#define LATTICRA_LAT_TO_LIR_FIRST_DECL_INDEX 1u

static void copy_text(char *destination, size_t destination_len, const char *source) {
    if (destination == 0 || destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source == 0 ? "" : source);
}

static void lat_span_default(latticra_lat_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static void lir_span_default(latticra_l_ui_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static latticra_l_ui_source_span_t convert_span(latticra_lat_source_span_t span) {
    latticra_l_ui_source_span_t converted;
    converted.start_offset = span.start_offset;
    converted.end_offset = span.end_offset;
    converted.start_line = span.start_line;
    converted.start_column = span.start_column;
    converted.end_line = span.end_line;
    converted.end_column = span.end_column;
    return converted;
}

static void result_default(latticra_lat_to_lir_result_t *result) {
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_LAT_TO_LIR_OK;
    lat_span_default(&result->span);
    result->module_name[0] = '\0';
    result->declaration_count = 0u;
    result->clause_count = 0u;
    result->node_count = 0u;
    result->edge_count = 0u;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
}

static void module_default(latticra_lir_module_t *module) {
    size_t index;
    if (module == 0) return;
    module->status = LATTICRA_STATUS_OK;
    module->error = LATTICRA_LIR_OK;
    module->source_kind = LATTICRA_LIR_SOURCE_UNKNOWN;
    module->report_classification = LATTICRA_LIR_REPORT_EMPTY;
    module->shape_kind = LATTICRA_LIR_SHAPE_UNKNOWN;
    module->module_name[0] = '\0';
    module->card_name[0] = '\0';
    module->effect[0] = '\0';
    module->boundary[0] = '\0';
    lir_span_default(&module->source_span);
    module->node_count = 0u;
    module->edge_count = 0u;
    module->binding_count = 0u;
    module->text_count = 0u;
    module->contains_edge_count = 0u;
    module->binds_edge_count = 0u;
    module->annotates_edge_count = 0u;
    module->orders_before_edge_count = 0u;
    module->transitions_from_edge_count = 0u;
    module->no_effect_chain_ok = 1;
    module->evidence_level = 0u;
    module->no_effect = 1;
    module->execution_allowed = 0;
    module->mutation_allowed = 0;
    module->server_allowed = 0;
    module->recovery_allowed = 0;
    module->hardware_allowed = 0;
    for (index = 0u; index < LATTICRA_LIR_NODE_MAX; index++) {
        module->nodes[index].kind = LATTICRA_LIR_NODE_UNKNOWN;
        module->nodes[index].name[0] = '\0';
        module->nodes[index].value[0] = '\0';
        module->nodes[index].binding[0] = '\0';
        lir_span_default(&module->nodes[index].source_span);
        module->nodes[index].parent_index = 0u;
        module->nodes[index].first_child_index = 0u;
        module->nodes[index].child_count = 0u;
        module->nodes[index].flags = 0u;
    }
    for (index = 0u; index < LATTICRA_LIR_EDGE_MAX; index++) {
        module->edges[index].from_index = 0u;
        module->edges[index].to_index = 0u;
        module->edges[index].edge_kind = LATTICRA_LIR_EDGE_UNKNOWN;
        lir_span_default(&module->edges[index].source_span);
    }
    for (index = 0u; index < LATTICRA_LIR_BINDING_REF_MAX; index++) {
        module->bindings[index].field_node_index = 0u;
        module->bindings[index].binding_target[0] = '\0';
        module->bindings[index].binding_prefix[0] = '\0';
        lir_span_default(&module->bindings[index].source_span);
        module->bindings[index].resolved_kind = LATTICRA_LIR_BINDING_UNSUPPORTED;
    }
    for (index = 0u; index < LATTICRA_LIR_TEXT_MAX; index++) {
        module->texts[index].text_node_index = 0u;
        module->texts[index].value[0] = '\0';
        module->texts[index].value_len = 0u;
        module->texts[index].escaped_value[0] = '\0';
        lir_span_default(&module->texts[index].source_span);
    }
}

const char *latticra_lat_to_lir_error_label(latticra_lat_to_lir_error_t error) {
    switch (error) {
    case LATTICRA_LAT_TO_LIR_OK: return "ok";
    case LATTICRA_LAT_TO_LIR_NULL_ARGUMENT: return "null_argument";
    case LATTICRA_LAT_TO_LIR_PARSE_NOT_OK: return "parse_not_ok";
    case LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK: return "semantic_not_ok";
    case LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID: return "semantic_not_valid";
    case LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION: return "no_effect_violation";
    case LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED: return "capacity_exceeded";
    case LATTICRA_LAT_TO_LIR_UNSUPPORTED_EFFECT: return "unsupported_effect";
    case LATTICRA_LAT_TO_LIR_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

static int lir_no_effect_chain_ok(const latticra_lir_module_t *module) {
    return module != 0 &&
           module->no_effect == 1 &&
           module->execution_allowed == 0 &&
           module->mutation_allowed == 0 &&
           module->server_allowed == 0 &&
           module->recovery_allowed == 0 &&
           module->hardware_allowed == 0;
}

static latticra_lir_shape_kind_t lir_shape_kind_for_source(latticra_lir_source_kind_t source_kind) {
    switch (source_kind) {
    case LATTICRA_LIR_SOURCE_L_UI_CARD: return LATTICRA_LIR_SHAPE_L_UI_CARD_GRAPH;
    case LATTICRA_LIR_SOURCE_LAT_MODULE: return LATTICRA_LIR_SHAPE_LAT_MODULE_GRAPH;
    case LATTICRA_LIR_SOURCE_INTERNAL_FIXTURE: return LATTICRA_LIR_SHAPE_INTERNAL_FIXTURE_GRAPH;
    case LATTICRA_LIR_SOURCE_UNKNOWN:
    default: return LATTICRA_LIR_SHAPE_UNKNOWN;
    }
}

static void finalize_lir_report_refinement(latticra_lir_module_t *module) {
    size_t index;
    if (module == 0) return;

    module->contains_edge_count = 0u;
    module->binds_edge_count = 0u;
    module->annotates_edge_count = 0u;
    module->orders_before_edge_count = 0u;
    module->transitions_from_edge_count = 0u;

    for (index = 0u; index < module->edge_count && index < LATTICRA_LIR_EDGE_MAX; index++) {
        switch (module->edges[index].edge_kind) {
        case LATTICRA_LIR_EDGE_CONTAINS:
            module->contains_edge_count += 1u;
            break;
        case LATTICRA_LIR_EDGE_BINDS:
            module->binds_edge_count += 1u;
            break;
        case LATTICRA_LIR_EDGE_ANNOTATES:
            module->annotates_edge_count += 1u;
            break;
        case LATTICRA_LIR_EDGE_ORDERS_BEFORE:
            module->orders_before_edge_count += 1u;
            break;
        case LATTICRA_LIR_EDGE_TRANSITIONS_FROM:
            module->transitions_from_edge_count += 1u;
            break;
        case LATTICRA_LIR_EDGE_UNKNOWN:
        default:
            break;
        }
    }

    module->no_effect_chain_ok = lir_no_effect_chain_ok(module);
    module->shape_kind = module->node_count == 0u ? LATTICRA_LIR_SHAPE_UNKNOWN : lir_shape_kind_for_source(module->source_kind);

    if (module->status != LATTICRA_STATUS_OK || module->error == LATTICRA_LIR_NULL_ARGUMENT || module->source_kind == LATTICRA_LIR_SOURCE_UNKNOWN) {
        module->report_classification = LATTICRA_LIR_REPORT_INVALID;
        module->evidence_level = 0u;
        return;
    }
    if (module->error != LATTICRA_LIR_OK) {
        module->report_classification = LATTICRA_LIR_REPORT_REJECTED;
        module->evidence_level = 1u;
        return;
    }
    if (module->node_count == 0u) {
        module->report_classification = LATTICRA_LIR_REPORT_EMPTY;
        module->evidence_level = 0u;
        return;
    }
    module->report_classification = LATTICRA_LIR_REPORT_MATERIALIZED;
    module->evidence_level = module->no_effect_chain_ok ? 2u : 1u;
}

static void copy_summary(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_to_lir_result_t *result) {
    if (parse_result == 0 || result == 0) return;
    result->span = parse_result->module.span;
    copy_text(result->module_name, sizeof(result->module_name), parse_result->module.module_name);
    result->declaration_count = parse_result->declaration_count;
    result->clause_count = parse_result->clause_count;
    result->no_effect = parse_result->no_effect;
    result->execution_allowed = parse_result->execution_allowed;
    result->mutation_allowed = parse_result->mutation_allowed;
}

static int no_effect_ok(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result) {
    return parse_result != 0 && semantic_result != 0 &&
           parse_result->no_effect == 1 &&
           parse_result->execution_allowed == 0 &&
           parse_result->mutation_allowed == 0 &&
           parse_result->server_allowed == 0 &&
           parse_result->recovery_allowed == 0 &&
           parse_result->hardware_allowed == 0 &&
           semantic_result->no_effect == 1 &&
           semantic_result->execution_allowed == 0 &&
           semantic_result->mutation_allowed == 0 &&
           semantic_result->server_allowed == 0 &&
           semantic_result->recovery_allowed == 0 &&
           semantic_result->hardware_allowed == 0;
}

static latticra_lir_node_kind_t declaration_node_kind(latticra_lat_declaration_kind_t kind) {
    switch (kind) {
    case LATTICRA_LAT_DECLARATION_STATE: return LATTICRA_LIR_NODE_LAT_STATE;
    case LATTICRA_LAT_DECLARATION_POLICY: return LATTICRA_LIR_NODE_LAT_POLICY;
    case LATTICRA_LAT_DECLARATION_TRANSITION: return LATTICRA_LIR_NODE_LAT_TRANSITION;
    case LATTICRA_LAT_DECLARATION_ASSERTION: return LATTICRA_LIR_NODE_LAT_ASSERTION;
    case LATTICRA_LAT_DECLARATION_EFFECT: return LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION;
    case LATTICRA_LAT_DECLARATION_UNKNOWN:
    default: return LATTICRA_LIR_NODE_UNKNOWN;
    }
}

static latticra_lir_node_kind_t clause_node_kind(const char *keyword) {
    if (keyword == 0) return LATTICRA_LIR_NODE_UNKNOWN;
    if (strcmp(keyword, "field") == 0) return LATTICRA_LIR_NODE_FIELD;
    if (strcmp(keyword, "require") == 0) return LATTICRA_LIR_NODE_LAT_REQUIREMENT;
    if (strcmp(keyword, "ensure") == 0) return LATTICRA_LIR_NODE_LAT_REQUIREMENT;
    if (strcmp(keyword, "effect") == 0) return LATTICRA_LIR_NODE_EFFECT;
    return LATTICRA_LIR_NODE_UNKNOWN;
}

static void set_node(
    latticra_lir_node_t *node,
    latticra_lir_node_kind_t kind,
    const char *name,
    const char *value,
    const char *binding,
    latticra_lat_source_span_t span,
    size_t parent_index,
    size_t first_child_index,
    size_t child_count) {
    if (node == 0) return;
    node->kind = kind;
    copy_text(node->name, sizeof(node->name), name);
    copy_text(node->value, sizeof(node->value), value);
    copy_text(node->binding, sizeof(node->binding), binding);
    node->source_span = convert_span(span);
    node->parent_index = parent_index;
    node->first_child_index = first_child_index;
    node->child_count = child_count;
    node->flags = 0u;
}

static int append_edge(
    latticra_lir_module_t *module,
    size_t from_index,
    size_t to_index,
    latticra_lir_edge_kind_t kind,
    latticra_lat_source_span_t span) {
    if (module == 0 || module->edge_count >= LATTICRA_LIR_EDGE_MAX) return 0;
    module->edges[module->edge_count].from_index = from_index;
    module->edges[module->edge_count].to_index = to_index;
    module->edges[module->edge_count].edge_kind = kind;
    module->edges[module->edge_count].source_span = convert_span(span);
    module->edge_count += 1u;
    return 1;
}

static size_t declaration_node_index(size_t declaration_index) {
    return LATTICRA_LAT_TO_LIR_FIRST_DECL_INDEX + declaration_index;
}

static size_t clause_node_index(const latticra_lat_parse_result_t *parse_result, size_t clause_index) {
    return LATTICRA_LAT_TO_LIR_FIRST_DECL_INDEX + parse_result->declaration_count + clause_index;
}

static size_t find_state_declaration_index(const latticra_lat_parse_result_t *parse_result, const char *name) {
    size_t index;
    if (parse_result == 0 || name == 0) return LATTICRA_LAT_DECLARATION_MAX;
    for (index = 0u; index < parse_result->declaration_count; index++) {
        if (parse_result->declarations[index].kind == LATTICRA_LAT_DECLARATION_STATE && strcmp(parse_result->declarations[index].name, name) == 0) return index;
    }
    return LATTICRA_LAT_DECLARATION_MAX;
}

latticra_status_t latticra_lir_lower_lat_module(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *result) {
    size_t index;
    size_t required_nodes;
    size_t required_edges;

    if (parse_result == 0 || semantic_result == 0 || module == 0 || result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    result_default(result);
    module_default(module);
    copy_summary(parse_result, result);

    if (parse_result->error != LATTICRA_LAT_PARSE_OK) {
        result->error = LATTICRA_LAT_TO_LIR_PARSE_NOT_OK;
        module->error = LATTICRA_LIR_SEMANTIC_FAILED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->error != LATTICRA_LAT_SEMANTIC_OK) {
        result->error = LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK;
        module->error = LATTICRA_LIR_SEMANTIC_FAILED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->semantic_valid != 1) {
        result->error = LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID;
        module->error = LATTICRA_LIR_SEMANTIC_FAILED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }
    if (!no_effect_ok(parse_result, semantic_result)) {
        result->error = LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION;
        module->error = LATTICRA_LIR_SEMANTIC_FAILED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }

    required_nodes = 1u + parse_result->declaration_count + parse_result->clause_count;
    required_edges = parse_result->declaration_count + parse_result->clause_count + parse_result->module.transition_count;
    if (required_nodes > LATTICRA_LIR_NODE_MAX || required_edges > LATTICRA_LIR_EDGE_MAX) {
        result->error = LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED;
        module->error = LATTICRA_LIR_CAPACITY_EXCEEDED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }

    module->status = LATTICRA_STATUS_OK;
    module->error = LATTICRA_LIR_OK;
    module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
    copy_text(module->module_name, sizeof(module->module_name), parse_result->module.module_name);
    copy_text(module->card_name, sizeof(module->card_name), "");
    copy_text(module->effect, sizeof(module->effect), "none");
    copy_text(module->boundary, sizeof(module->boundary), "lat_semantic_only");
    module->source_span = convert_span(parse_result->module.span);
    module->node_count = required_nodes;
    module->binding_count = 0u;
    module->text_count = 0u;
    module->no_effect = 1;
    module->execution_allowed = 0;
    module->mutation_allowed = 0;
    module->server_allowed = 0;
    module->recovery_allowed = 0;
    module->hardware_allowed = 0;

    set_node(&module->nodes[LATTICRA_LAT_TO_LIR_MODULE_INDEX], LATTICRA_LIR_NODE_MODULE, parse_result->module.module_name, "lat_module", "", parse_result->module.span, LATTICRA_LAT_TO_LIR_ROOT_PARENT, LATTICRA_LAT_TO_LIR_FIRST_DECL_INDEX, parse_result->declaration_count);

    for (index = 0u; index < parse_result->declaration_count; index++) {
        const latticra_lat_ast_declaration_t *declaration = &parse_result->declarations[index];
        size_t node_index = declaration_node_index(index);
        const char *kind_label = latticra_lat_declaration_kind_label(declaration->kind);
        set_node(&module->nodes[node_index], declaration_node_kind(declaration->kind), declaration->name, kind_label, declaration->source_name, declaration->span, LATTICRA_LAT_TO_LIR_MODULE_INDEX, clause_node_index(parse_result, declaration->first_clause_index), declaration->clause_count);
        if (!append_edge(module, LATTICRA_LAT_TO_LIR_MODULE_INDEX, node_index, LATTICRA_LIR_EDGE_CONTAINS, declaration->span)) goto capacity_failed;
    }

    for (index = 0u; index < parse_result->clause_count; index++) {
        const latticra_lat_ast_clause_t *clause = &parse_result->clauses[index];
        size_t owner = 0u;
        size_t decl_index;
        latticra_lir_node_kind_t kind = clause_node_kind(clause->keyword);
        if (kind == LATTICRA_LIR_NODE_UNKNOWN) {
            result->error = LATTICRA_LAT_TO_LIR_UNSUPPORTED_EFFECT;
            module->error = LATTICRA_LIR_UNSUPPORTED_NODE_KIND;
            finalize_lir_report_refinement(module);
            return LATTICRA_STATUS_OK;
        }
        for (decl_index = 0u; decl_index < parse_result->declaration_count; decl_index++) {
            size_t first = parse_result->declarations[decl_index].first_clause_index;
            size_t last = first + parse_result->declarations[decl_index].clause_count;
            if (index >= first && index < last) {
                owner = declaration_node_index(decl_index);
                break;
            }
        }
        set_node(&module->nodes[clause_node_index(parse_result, index)], kind, clause->left, clause->right, clause->keyword, clause->span, owner, 0u, 0u);
        if (!append_edge(module, owner, clause_node_index(parse_result, index), LATTICRA_LIR_EDGE_CONTAINS, clause->span)) goto capacity_failed;
    }

    for (index = 0u; index < parse_result->declaration_count; index++) {
        const latticra_lat_ast_declaration_t *declaration = &parse_result->declarations[index];
        if (declaration->kind == LATTICRA_LAT_DECLARATION_TRANSITION) {
            size_t state_index = find_state_declaration_index(parse_result, declaration->source_name);
            if (state_index >= LATTICRA_LAT_DECLARATION_MAX) {
                result->error = LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID;
                module->error = LATTICRA_LIR_SEMANTIC_FAILED;
                finalize_lir_report_refinement(module);
                return LATTICRA_STATUS_OK;
            }
            if (!append_edge(module, declaration_node_index(index), declaration_node_index(state_index), LATTICRA_LIR_EDGE_TRANSITIONS_FROM, declaration->span)) goto capacity_failed;
        }
    }

    result->error = LATTICRA_LAT_TO_LIR_OK;
    result->node_count = module->node_count;
    result->edge_count = module->edge_count;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    finalize_lir_report_refinement(module);
    return LATTICRA_STATUS_OK;

capacity_failed:
    result->error = LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED;
    result->node_count = 0u;
    result->edge_count = 0u;
    module_default(module);
    module->error = LATTICRA_LIR_CAPACITY_EXCEEDED;
    module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
    finalize_lir_report_refinement(module);
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lat_to_lir_report(
    const latticra_lat_to_lir_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    written = snprintf(
        buffer,
        buffer_len,
        "LAT TO LIR LOWERING REPORT\n"
        "status=%d\n"
        "error=%s\n"
        "module=%s\n"
        "declaration_count=%zu\n"
        "clause_count=%zu\n"
        "node_count=%zu\n"
        "edge_count=%zu\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "span_start_offset=%zu\n"
        "span_end_offset=%zu\n"
        "span_start_line=%zu\n"
        "span_start_column=%zu\n"
        "span_end_line=%zu\n"
        "span_end_column=%zu\n",
        (int)result->status,
        latticra_lat_to_lir_error_label(result->error),
        result->module_name,
        result->declaration_count,
        result->clause_count,
        result->node_count,
        result->edge_count,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->span.start_offset,
        result->span.end_offset,
        result->span.start_line,
        result->span.start_column,
        result->span.end_line,
        result->span.end_column);
    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}

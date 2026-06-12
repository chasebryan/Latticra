#include "latticra/lat_to_lir.h"

#include <stdio.h>
#include <string.h>

#define LATTICRA_LAT_TO_LIR_ROOT_PARENT 0u
#define LATTICRA_LAT_TO_LIR_MODULE_INDEX 0u
#define LATTICRA_LAT_TO_LIR_FIRST_DECL_INDEX 1u
#define LATTICRA_LAT_TO_LIR_ESCAPED_NAME_MAX ((LATTICRA_LAT_NAME_MAX * 4u) + 1u)
#define LATTICRA_LAT_TO_LIR_ESCAPED_VALUE_MAX ((LATTICRA_LAT_VALUE_MAX * 4u) + 1u)

static void copy_text(char *destination, size_t destination_len, const char *source) {
    if (destination == 0 || destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source == 0 ? "" : source);
}

static latticra_status_t escape_report_string(
    const char *input,
    char *output,
    size_t output_len) {
    static const char hex[] = "0123456789ABCDEF";
    size_t input_index;
    size_t output_index = 0u;

    if (input == 0 || output == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    if (output_len == 0u) return LATTICRA_STATUS_BUFFER_TOO_SMALL;

    for (input_index = 0u; input[input_index] != '\0'; input_index++) {
        unsigned char byte = (unsigned char)input[input_index];
        const char *short_escape = 0;
        size_t needed;

        if (byte == '\n') short_escape = "\\n";
        else if (byte == '\r') short_escape = "\\r";
        else if (byte == '\t') short_escape = "\\t";
        else if (byte == '"') short_escape = "\\\"";
        else if (byte == '\\') short_escape = "\\\\";

        if (short_escape != 0) {
            needed = strlen(short_escape);
            if (output_index + needed >= output_len) {
                output[0] = '\0';
                return LATTICRA_STATUS_BUFFER_TOO_SMALL;
            }
            (void)memcpy(output + output_index, short_escape, needed);
            output_index += needed;
        } else if (byte >= 0x20u && byte <= 0x7Eu) {
            if (output_index + 1u >= output_len) {
                output[0] = '\0';
                return LATTICRA_STATUS_BUFFER_TOO_SMALL;
            }
            output[output_index] = (char)byte;
            output_index += 1u;
        } else {
            if (output_index + 4u >= output_len) {
                output[0] = '\0';
                return LATTICRA_STATUS_BUFFER_TOO_SMALL;
            }
            output[output_index++] = '\\';
            output[output_index++] = 'x';
            output[output_index++] = hex[(byte >> 4u) & 0x0Fu];
            output[output_index++] = hex[byte & 0x0Fu];
        }
    }
    output[output_index] = '\0';
    return LATTICRA_STATUS_OK;
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
    result->model_error = LATTICRA_LAT_MODEL_OK;
    lat_span_default(&result->span);
    result->module_name[0] = '\0';
    result->declaration_count = 0u;
    result->clause_count = 0u;
    result->model_declaration_count = 0u;
    result->model_clause_count = 0u;
    result->first_declaration_node_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->first_declaration_kind = LATTICRA_LAT_DECLARATION_UNKNOWN;
    result->first_declaration_name[0] = '\0';
    result->first_declaration_source[0] = '\0';
    result->first_declaration_parse_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->first_declaration_first_clause_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->first_declaration_clause_count = 0u;
    result->first_declaration_source_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->first_transition_source_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->first_clause_node_index = LATTICRA_LAT_MODEL_NO_INDEX;
    result->first_clause_role = LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN;
    result->first_clause_effect = LATTICRA_LAT_EFFECT_UNKNOWN;
    result->first_clause_name[0] = '\0';
    result->first_clause_operator[0] = '\0';
    result->first_clause_value[0] = '\0';
    result->node_count = 0u;
    result->edge_count = 0u;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->network_allowed = 0;
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
    module->network_allowed = 0;
    module->recovery_allowed = 0;
    module->hardware_allowed = 0;
    for (index = 0u; index < LATTICRA_LIR_NODE_MAX; index++) {
        module->nodes[index].kind = LATTICRA_LIR_NODE_UNKNOWN;
        module->nodes[index].name[0] = '\0';
        module->nodes[index].value[0] = '\0';
        module->nodes[index].operator_text[0] = '\0';
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
    case LATTICRA_LAT_TO_LIR_INTERNAL_ERROR: return "internal_error";
    case LATTICRA_LAT_TO_LIR_MODEL_NOT_OK: return "model_not_ok";
    default: return "internal_error";
    }
}

static int lir_no_effect_chain_ok(const latticra_lir_module_t *module) {
    return module != 0 &&
           module->no_effect == 1 &&
           module->execution_allowed == 0 &&
           module->mutation_allowed == 0 &&
           module->server_allowed == 0 &&
           module->network_allowed == 0 &&
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

static size_t first_transition_source_index(const latticra_lat_model_t *model) {
    size_t transition_index;
    if (model == 0 || model->first_transition_index == LATTICRA_LAT_MODEL_NO_INDEX) return LATTICRA_LAT_MODEL_NO_INDEX;
    transition_index = model->first_transition_index;
    if (transition_index >= model->declaration_count || transition_index >= LATTICRA_LAT_DECLARATION_MAX) return LATTICRA_LAT_MODEL_NO_INDEX;
    return model->declarations[transition_index].source_declaration_index;
}

static void copy_model_summary(
    const latticra_lat_model_t *model,
    latticra_lat_to_lir_result_t *result) {
    if (model == 0 || result == 0) return;
    result->status = model->status;
    result->model_error = model->error;
    result->span = model->span;
    copy_text(result->module_name, sizeof(result->module_name), model->module_name);
    result->declaration_count = model->declaration_count;
    result->clause_count = model->clause_count;
    result->model_declaration_count = model->declaration_count;
    result->model_clause_count = model->clause_count;
    result->first_transition_source_index = first_transition_source_index(model);
    result->no_effect = model->no_effect;
    result->execution_allowed = model->execution_allowed;
    result->mutation_allowed = model->mutation_allowed;
    result->network_allowed = model->network_allowed;
}

static int model_no_effect_ok(const latticra_lat_model_t *model) {
    return model != 0 &&
           model->no_effect == 1 &&
           model->execution_allowed == 0 &&
           model->mutation_allowed == 0 &&
           model->server_allowed == 0 &&
           model->network_allowed == 0 &&
           model->recovery_allowed == 0 &&
           model->hardware_allowed == 0;
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

static latticra_lir_node_kind_t clause_node_kind(latticra_lat_model_clause_role_t role) {
    switch (role) {
    case LATTICRA_LAT_MODEL_CLAUSE_FIELD: return LATTICRA_LIR_NODE_FIELD;
    case LATTICRA_LAT_MODEL_CLAUSE_REQUIRE: return LATTICRA_LIR_NODE_LAT_REQUIREMENT;
    case LATTICRA_LAT_MODEL_CLAUSE_ENSURE: return LATTICRA_LIR_NODE_LAT_REQUIREMENT;
    case LATTICRA_LAT_MODEL_CLAUSE_EFFECT: return LATTICRA_LIR_NODE_EFFECT;
    case LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN:
    default: return LATTICRA_LIR_NODE_UNKNOWN;
    }
}

static void set_node(
    latticra_lir_node_t *node,
    latticra_lir_node_kind_t kind,
    const char *name,
    const char *value,
    const char *operator_text,
    const char *binding,
    latticra_lat_source_span_t span,
    size_t parent_index,
    size_t first_child_index,
    size_t child_count) {
    if (node == 0) return;
    node->kind = kind;
    copy_text(node->name, sizeof(node->name), name);
    copy_text(node->value, sizeof(node->value), value);
    copy_text(node->operator_text, sizeof(node->operator_text), operator_text);
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

static size_t model_clause_node_index(const latticra_lat_model_t *model, size_t clause_index) {
    return LATTICRA_LAT_TO_LIR_FIRST_DECL_INDEX + model->declaration_count + clause_index;
}

static void copy_first_declaration_summary(
    const latticra_lat_model_t *model,
    latticra_lat_to_lir_result_t *result) {
    const latticra_lat_model_declaration_t *declaration;
    if (model == 0 || result == 0 || model->declaration_count == 0u) return;
    declaration = &model->declarations[0];
    result->first_declaration_node_index = declaration_node_index(0u);
    result->first_declaration_kind = declaration->kind;
    copy_text(result->first_declaration_name, sizeof(result->first_declaration_name), declaration->name);
    copy_text(result->first_declaration_source, sizeof(result->first_declaration_source), declaration->source_name);
    result->first_declaration_parse_index = declaration->parse_declaration_index;
    result->first_declaration_first_clause_index = declaration->first_clause_index;
    result->first_declaration_clause_count = declaration->clause_count;
    result->first_declaration_source_index = declaration->source_declaration_index;
}

static void copy_first_clause_summary(
    const latticra_lat_model_t *model,
    latticra_lat_to_lir_result_t *result) {
    const latticra_lat_model_clause_t *clause;
    if (model == 0 || result == 0 || model->clause_count == 0u) return;
    clause = &model->clauses[0];
    result->first_clause_node_index = model_clause_node_index(model, 0u);
    result->first_clause_role = clause->role;
    result->first_clause_effect = clause->effect;
    copy_text(result->first_clause_name, sizeof(result->first_clause_name), clause->name);
    copy_text(result->first_clause_operator, sizeof(result->first_clause_operator), clause->operator_text);
    copy_text(result->first_clause_value, sizeof(result->first_clause_value), clause->value);
}

static latticra_lat_to_lir_error_t lowering_error_from_model_error(latticra_lat_model_error_t error) {
    switch (error) {
    case LATTICRA_LAT_MODEL_OK: return LATTICRA_LAT_TO_LIR_OK;
    case LATTICRA_LAT_MODEL_PARSE_NOT_OK: return LATTICRA_LAT_TO_LIR_PARSE_NOT_OK;
    case LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK: return LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK;
    case LATTICRA_LAT_MODEL_SEMANTIC_NOT_VALID: return LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID;
    case LATTICRA_LAT_MODEL_NO_EFFECT_VIOLATION: return LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION;
    case LATTICRA_LAT_MODEL_CAPACITY_EXCEEDED: return LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED;
    case LATTICRA_LAT_MODEL_NULL_ARGUMENT:
    case LATTICRA_LAT_MODEL_UNSUPPORTED_DECLARATION:
    case LATTICRA_LAT_MODEL_UNSUPPORTED_CLAUSE:
    case LATTICRA_LAT_MODEL_INTERNAL_ERROR:
    default: return LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
    }
}

static latticra_lir_error_t lir_error_from_lowering_error(latticra_lat_to_lir_error_t error) {
    switch (error) {
    case LATTICRA_LAT_TO_LIR_OK: return LATTICRA_LIR_OK;
    case LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED: return LATTICRA_LIR_CAPACITY_EXCEEDED;
    case LATTICRA_LAT_TO_LIR_UNSUPPORTED_EFFECT: return LATTICRA_LIR_UNSUPPORTED_EFFECT;
    case LATTICRA_LAT_TO_LIR_NULL_ARGUMENT: return LATTICRA_LIR_NULL_ARGUMENT;
    case LATTICRA_LAT_TO_LIR_MODEL_NOT_OK: return LATTICRA_LIR_UNSUPPORTED_NODE_KIND;
    case LATTICRA_LAT_TO_LIR_PARSE_NOT_OK:
    case LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK:
    case LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID:
    case LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION:
    case LATTICRA_LAT_TO_LIR_INTERNAL_ERROR:
    default: return LATTICRA_LIR_SEMANTIC_FAILED;
    }
}

latticra_status_t latticra_lir_lower_lat_model(
    const latticra_lat_model_t *model,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *result) {
    size_t index;
    size_t required_nodes;
    size_t required_edges;

    if (model == 0 || module == 0 || result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    result_default(result);
    module_default(module);
    copy_model_summary(model, result);

    if (model->status != LATTICRA_STATUS_OK && model->error == LATTICRA_LAT_MODEL_OK) {
        result->error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
        module->error = LATTICRA_LIR_SEMANTIC_FAILED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }
    if (model->error != LATTICRA_LAT_MODEL_OK) {
        result->error = lowering_error_from_model_error(model->error);
        module->error = lir_error_from_lowering_error(result->error);
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }
    if (!model_no_effect_ok(model)) {
        result->error = LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION;
        module->error = LATTICRA_LIR_SEMANTIC_FAILED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }

    if (model->declaration_count > LATTICRA_LAT_DECLARATION_MAX || model->clause_count > LATTICRA_LAT_CLAUSE_MAX) {
        result->error = LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED;
        module->error = LATTICRA_LIR_CAPACITY_EXCEEDED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return LATTICRA_STATUS_OK;
    }
    required_nodes = 1u + model->declaration_count + model->clause_count;
    required_edges = model->declaration_count + model->clause_count + model->transition_count;
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
    copy_text(module->module_name, sizeof(module->module_name), model->module_name);
    copy_text(module->card_name, sizeof(module->card_name), "");
    copy_text(module->effect, sizeof(module->effect), "none");
    copy_text(module->boundary, sizeof(module->boundary), "lat_semantic_only");
    module->source_span = convert_span(model->span);
    module->node_count = required_nodes;
    module->binding_count = 0u;
    module->text_count = 0u;
    module->no_effect = model->no_effect;
    module->execution_allowed = model->execution_allowed;
    module->mutation_allowed = model->mutation_allowed;
    module->server_allowed = model->server_allowed;
    module->network_allowed = model->network_allowed;
    module->recovery_allowed = model->recovery_allowed;
    module->hardware_allowed = model->hardware_allowed;

    set_node(&module->nodes[LATTICRA_LAT_TO_LIR_MODULE_INDEX], LATTICRA_LIR_NODE_MODULE, model->module_name, "lat_module", "", "", model->span, LATTICRA_LAT_TO_LIR_ROOT_PARENT, LATTICRA_LAT_TO_LIR_FIRST_DECL_INDEX, model->declaration_count);

    for (index = 0u; index < model->declaration_count; index++) {
        const latticra_lat_model_declaration_t *declaration = &model->declarations[index];
        size_t node_index = declaration_node_index(index);
        const char *kind_label = latticra_lat_declaration_kind_label(declaration->kind);
        size_t first_child_index = 0u;
        if (declaration_node_kind(declaration->kind) == LATTICRA_LIR_NODE_UNKNOWN) {
            result->error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
            module->error = LATTICRA_LIR_UNSUPPORTED_NODE_KIND;
            finalize_lir_report_refinement(module);
            return LATTICRA_STATUS_OK;
        }
        if (declaration->clause_count > 0u) {
            if (declaration->first_clause_index == LATTICRA_LAT_MODEL_NO_INDEX ||
                declaration->first_clause_index > model->clause_count ||
                declaration->clause_count > model->clause_count - declaration->first_clause_index) {
                result->error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
                module->error = LATTICRA_LIR_SEMANTIC_FAILED;
                finalize_lir_report_refinement(module);
                return LATTICRA_STATUS_OK;
            }
            first_child_index = model_clause_node_index(model, declaration->first_clause_index);
        }
        set_node(&module->nodes[node_index], declaration_node_kind(declaration->kind), declaration->name, kind_label, "", declaration->source_name, declaration->span, LATTICRA_LAT_TO_LIR_MODULE_INDEX, first_child_index, declaration->clause_count);
        if (!append_edge(module, LATTICRA_LAT_TO_LIR_MODULE_INDEX, node_index, LATTICRA_LIR_EDGE_CONTAINS, declaration->span)) goto capacity_failed;
    }

    for (index = 0u; index < model->clause_count; index++) {
        const latticra_lat_model_clause_t *clause = &model->clauses[index];
        size_t owner = clause->owner_declaration_index;
        latticra_lir_node_kind_t kind = clause_node_kind(clause->role);
        size_t node_index = model_clause_node_index(model, index);
        if (kind == LATTICRA_LIR_NODE_UNKNOWN) {
            result->error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
            module->error = LATTICRA_LIR_UNSUPPORTED_NODE_KIND;
            finalize_lir_report_refinement(module);
            return LATTICRA_STATUS_OK;
        }
        if (owner == LATTICRA_LAT_MODEL_NO_INDEX || owner >= model->declaration_count) {
            result->error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
            module->error = LATTICRA_LIR_SEMANTIC_FAILED;
            finalize_lir_report_refinement(module);
            return LATTICRA_STATUS_OK;
        }
        set_node(&module->nodes[node_index], kind, clause->name, clause->value, clause->operator_text, latticra_lat_model_clause_role_label(clause->role), clause->span, declaration_node_index(owner), 0u, 0u);
        if (!append_edge(module, declaration_node_index(owner), node_index, LATTICRA_LIR_EDGE_CONTAINS, clause->span)) goto capacity_failed;
    }

    for (index = 0u; index < model->declaration_count; index++) {
        const latticra_lat_model_declaration_t *declaration = &model->declarations[index];
        if (declaration->kind == LATTICRA_LAT_DECLARATION_TRANSITION) {
            size_t state_index = declaration->source_declaration_index;
            if (state_index == LATTICRA_LAT_MODEL_NO_INDEX ||
                state_index >= model->declaration_count ||
                model->declarations[state_index].kind != LATTICRA_LAT_DECLARATION_STATE) {
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
    copy_first_declaration_summary(model, result);
    copy_first_clause_summary(model, result);
    result->no_effect = model->no_effect;
    result->execution_allowed = model->execution_allowed;
    result->mutation_allowed = model->mutation_allowed;
    result->network_allowed = model->network_allowed;
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

latticra_status_t latticra_lir_lower_lat_module(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *result) {
    latticra_lat_model_t model;
    latticra_status_t model_status;

    if (parse_result == 0 || semantic_result == 0 || module == 0 || result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    model_status = latticra_lat_model_normalize_module(parse_result, semantic_result, &model);
    if (model_status != LATTICRA_STATUS_OK) {
        result_default(result);
        module_default(module);
        result->status = model_status;
        result->error = LATTICRA_LAT_TO_LIR_MODEL_NOT_OK;
        module->status = model_status;
        module->error = LATTICRA_LIR_SEMANTIC_FAILED;
        module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE;
        finalize_lir_report_refinement(module);
        return model_status;
    }

    return latticra_lir_lower_lat_model(&model, module, result);
}

latticra_status_t latticra_lat_to_lir_report(
    const latticra_lat_to_lir_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    char module_name_escaped[LATTICRA_LAT_TO_LIR_ESCAPED_NAME_MAX];
    char first_declaration_name_escaped[LATTICRA_LAT_TO_LIR_ESCAPED_NAME_MAX];
    char first_declaration_source_escaped[LATTICRA_LAT_TO_LIR_ESCAPED_NAME_MAX];
    char first_clause_name_escaped[LATTICRA_LAT_TO_LIR_ESCAPED_NAME_MAX];
    char first_clause_operator_escaped[LATTICRA_LAT_TO_LIR_ESCAPED_NAME_MAX];
    char first_clause_value_escaped[LATTICRA_LAT_TO_LIR_ESCAPED_VALUE_MAX];
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;

    if (escape_report_string(result->module_name, module_name_escaped, sizeof(module_name_escaped)) != LATTICRA_STATUS_OK ||
        escape_report_string(result->first_declaration_name, first_declaration_name_escaped, sizeof(first_declaration_name_escaped)) != LATTICRA_STATUS_OK ||
        escape_report_string(result->first_declaration_source, first_declaration_source_escaped, sizeof(first_declaration_source_escaped)) != LATTICRA_STATUS_OK ||
        escape_report_string(result->first_clause_name, first_clause_name_escaped, sizeof(first_clause_name_escaped)) != LATTICRA_STATUS_OK ||
        escape_report_string(result->first_clause_operator, first_clause_operator_escaped, sizeof(first_clause_operator_escaped)) != LATTICRA_STATUS_OK ||
        escape_report_string(result->first_clause_value, first_clause_value_escaped, sizeof(first_clause_value_escaped)) != LATTICRA_STATUS_OK) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    written = snprintf(
        buffer,
        buffer_len,
        "LAT TO LIR LOWERING REPORT\n"
        "status=%d\n"
        "error=%s\n"
        "model_error=%s\n"
        "module=%s\n"
        "declaration_count=%zu\n"
        "clause_count=%zu\n"
        "model_declaration_count=%zu\n"
        "model_clause_count=%zu\n"
        "first_declaration_node_index=%zu\n"
        "first_declaration_kind=%s\n"
        "first_declaration_name=%s\n"
        "first_declaration_source=%s\n"
        "first_declaration_parse_index=%zu\n"
        "first_declaration_first_clause_index=%zu\n"
        "first_declaration_clause_count=%zu\n"
        "first_declaration_source_index=%zu\n"
        "first_transition_source_index=%zu\n"
        "first_clause_node_index=%zu\n"
        "first_clause_role=%s\n"
        "first_clause_effect=%s\n"
        "first_clause_name=%s\n"
        "first_clause_operator=%s\n"
        "first_clause_value=%s\n"
        "node_count=%zu\n"
        "edge_count=%zu\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "network_allowed=%d\n"
        "span_start_offset=%zu\n"
        "span_end_offset=%zu\n"
        "span_start_line=%zu\n"
        "span_start_column=%zu\n"
        "span_end_line=%zu\n"
        "span_end_column=%zu\n",
        (int)result->status,
        latticra_lat_to_lir_error_label(result->error),
        latticra_lat_model_error_label(result->model_error),
        module_name_escaped,
        result->declaration_count,
        result->clause_count,
        result->model_declaration_count,
        result->model_clause_count,
        result->first_declaration_node_index,
        latticra_lat_declaration_kind_label(result->first_declaration_kind),
        first_declaration_name_escaped,
        first_declaration_source_escaped,
        result->first_declaration_parse_index,
        result->first_declaration_first_clause_index,
        result->first_declaration_clause_count,
        result->first_declaration_source_index,
        result->first_transition_source_index,
        result->first_clause_node_index,
        latticra_lat_model_clause_role_label(result->first_clause_role),
        latticra_lat_effect_label(result->first_clause_effect),
        first_clause_name_escaped,
        first_clause_operator_escaped,
        first_clause_value_escaped,
        result->node_count,
        result->edge_count,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->network_allowed,
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

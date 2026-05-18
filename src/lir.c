#include "latticra/lir.h"

#include <stdio.h>
#include <string.h>

#define LATTICRA_LIR_ROOT_PARENT 0u
#define LATTICRA_LIR_MODULE_NODE_INDEX 0u
#define LATTICRA_LIR_CARD_NODE_INDEX 1u
#define LATTICRA_LIR_FIRST_RAIL_NODE_INDEX 2u
#define LATTICRA_LIR_FIRST_FIELD_NODE_INDEX 11u
#define LATTICRA_LIR_FIRST_TEXT_NODE_INDEX 34u
#define LATTICRA_LIR_FIRST_BINDING_NODE_INDEX 36u
#define LATTICRA_LIR_EFFECT_NODE_INDEX 59u
#define LATTICRA_LIR_BOUNDARY_NODE_INDEX 60u
#define LATTICRA_LIR_EXPECTED_NODE_COUNT 61u
#define LATTICRA_LIR_EXPECTED_FIELD_COUNT 23u
#define LATTICRA_LIR_EXPECTED_TEXT_COUNT 2u

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination == 0 || destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source == 0 ? "" : source);
}

static void copy_bytes_compat(char *destination, size_t destination_len, const char *source, size_t source_len) {
    if (destination == 0 || destination_len == 0u) return;
    destination[0] = '\0';
    if (source == 0) return;
    if (source_len >= destination_len) return;
    (void)memcpy(destination, source, source_len);
    destination[source_len] = '\0';
}

static void span_default(latticra_l_ui_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static void module_default(latticra_lir_module_t *module) {
    size_t index;
    if (module == 0) return;
    module->status = LATTICRA_STATUS_OK;
    module->error = LATTICRA_LIR_OK;
    module->source_kind = LATTICRA_LIR_SOURCE_UNKNOWN;
    module->module_name[0] = '\0';
    module->card_name[0] = '\0';
    module->effect[0] = '\0';
    module->boundary[0] = '\0';
    span_default(&module->source_span);
    module->node_count = 0u;
    module->edge_count = 0u;
    module->binding_count = 0u;
    module->text_count = 0u;
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
        span_default(&module->nodes[index].source_span);
        module->nodes[index].parent_index = 0u;
        module->nodes[index].first_child_index = 0u;
        module->nodes[index].child_count = 0u;
        module->nodes[index].flags = 0u;
    }
    for (index = 0u; index < LATTICRA_LIR_EDGE_MAX; index++) {
        module->edges[index].from_index = 0u;
        module->edges[index].to_index = 0u;
        module->edges[index].edge_kind = LATTICRA_LIR_EDGE_UNKNOWN;
        span_default(&module->edges[index].source_span);
    }
    for (index = 0u; index < LATTICRA_LIR_BINDING_REF_MAX; index++) {
        module->bindings[index].field_node_index = 0u;
        module->bindings[index].binding_target[0] = '\0';
        module->bindings[index].binding_prefix[0] = '\0';
        span_default(&module->bindings[index].source_span);
        module->bindings[index].resolved_kind = LATTICRA_LIR_BINDING_UNSUPPORTED;
    }
    for (index = 0u; index < LATTICRA_LIR_TEXT_MAX; index++) {
        module->texts[index].text_node_index = 0u;
        module->texts[index].value[0] = '\0';
        module->texts[index].value_len = 0u;
        module->texts[index].escaped_value[0] = '\0';
        span_default(&module->texts[index].source_span);
    }
}

const char *latticra_lir_error_label(latticra_lir_error_t error) {
    switch (error) {
    case LATTICRA_LIR_OK: return "ok";
    case LATTICRA_LIR_NULL_ARGUMENT: return "null_argument";
    case LATTICRA_LIR_SEMANTIC_FAILED: return "semantic_failed";
    case LATTICRA_LIR_CAPACITY_EXCEEDED: return "capacity_exceeded";
    case LATTICRA_LIR_UNSUPPORTED_SOURCE_KIND: return "unsupported_source_kind";
    case LATTICRA_LIR_UNSUPPORTED_NODE_KIND: return "unsupported_node_kind";
    case LATTICRA_LIR_UNSUPPORTED_EFFECT: return "unsupported_effect";
    case LATTICRA_LIR_UNSUPPORTED_BOUNDARY: return "unsupported_boundary";
    case LATTICRA_LIR_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

const char *latticra_lir_source_kind_label(latticra_lir_source_kind_t kind) {
    switch (kind) {
    case LATTICRA_LIR_SOURCE_UNKNOWN: return "unknown";
    case LATTICRA_LIR_SOURCE_L_UI_CARD: return "l_ui_card";
    case LATTICRA_LIR_SOURCE_LAT_MODULE: return "lat_module";
    case LATTICRA_LIR_SOURCE_INTERNAL_FIXTURE: return "internal_fixture";
    default: return "unknown";
    }
}

const char *latticra_lir_node_kind_label(latticra_lir_node_kind_t kind) {
    switch (kind) {
    case LATTICRA_LIR_NODE_MODULE: return "module";
    case LATTICRA_LIR_NODE_CARD: return "card";
    case LATTICRA_LIR_NODE_RAIL: return "rail";
    case LATTICRA_LIR_NODE_FIELD: return "field";
    case LATTICRA_LIR_NODE_TEXT: return "text";
    case LATTICRA_LIR_NODE_BINDING: return "binding";
    case LATTICRA_LIR_NODE_EFFECT: return "effect";
    case LATTICRA_LIR_NODE_BOUNDARY: return "boundary";
    case LATTICRA_LIR_NODE_LAT_STATE: return "lat_state";
    case LATTICRA_LIR_NODE_LAT_POLICY: return "lat_policy";
    case LATTICRA_LIR_NODE_LAT_TRANSITION: return "lat_transition";
    case LATTICRA_LIR_NODE_LAT_ASSERTION: return "lat_assertion";
    case LATTICRA_LIR_NODE_LAT_REQUIREMENT: return "lat_requirement";
    case LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION: return "lat_effect_declaration";
    case LATTICRA_LIR_NODE_UNKNOWN:
    default: return "unknown";
    }
}

const char *latticra_lir_edge_kind_label(latticra_lir_edge_kind_t kind) {
    switch (kind) {
    case LATTICRA_LIR_EDGE_CONTAINS: return "contains";
    case LATTICRA_LIR_EDGE_BINDS: return "binds";
    case LATTICRA_LIR_EDGE_ANNOTATES: return "annotates";
    case LATTICRA_LIR_EDGE_ORDERS_BEFORE: return "orders_before";
    case LATTICRA_LIR_EDGE_TRANSITIONS_FROM: return "transitions_from";
    case LATTICRA_LIR_EDGE_UNKNOWN:
    default: return "unknown";
    }
}

const char *latticra_lir_resolved_binding_kind_label(latticra_lir_resolved_binding_kind_t kind) {
    switch (kind) {
    case LATTICRA_LIR_BINDING_STATE_VALUE: return "state_value";
    case LATTICRA_LIR_BINDING_PREVIEW_VALUE: return "preview_value";
    case LATTICRA_LIR_BINDING_UNSUPPORTED:
    default: return "unsupported";
    }
}

static int prerequisite_ok(
    const latticra_l_ui_ast_result_t *ast,
    const latticra_l_ui_semantic_result_t *semantic) {
    return ast != 0 && semantic != 0 &&
           ast->parse_result.error == LATTICRA_L_UI_PARSE_OK &&
           semantic->error == LATTICRA_L_UI_SEMANTIC_OK &&
           semantic->parser_error == LATTICRA_L_UI_PARSE_OK &&
           semantic->no_effect == 1 &&
           semantic->execution_allowed == 0 &&
           semantic->mutation_allowed == 0 &&
           semantic->server_allowed == 0 &&
           semantic->recovery_allowed == 0 &&
           semantic->hardware_allowed == 0;
}

static latticra_lir_resolved_binding_kind_t resolved_binding_kind(const char *binding) {
    if (binding == 0) return LATTICRA_LIR_BINDING_UNSUPPORTED;
    if (strncmp(binding, "state.", strlen("state.")) == 0) return LATTICRA_LIR_BINDING_STATE_VALUE;
    if (strncmp(binding, "preview.", strlen("preview.")) == 0) return LATTICRA_LIR_BINDING_PREVIEW_VALUE;
    return LATTICRA_LIR_BINDING_UNSUPPORTED;
}

static void copy_binding_prefix(char *destination, size_t destination_len, const char *binding) {
    const char *dot;
    size_t len;
    if (destination == 0 || destination_len == 0u) return;
    destination[0] = '\0';
    if (binding == 0) return;
    dot = strchr(binding, '.');
    len = dot == 0 ? strlen(binding) : (size_t)(dot - binding);
    if (len >= destination_len) len = destination_len - 1u;
    (void)memcpy(destination, binding, len);
    destination[len] = '\0';
}

static int append_escaped_byte(char *destination, size_t destination_len, size_t *used, const char *text) {
    int written;
    if (destination == 0 || used == 0 || text == 0 || *used >= destination_len) return 0;
    written = snprintf(destination + *used, destination_len - *used, "%s", text);
    if (written < 0 || (size_t)written >= destination_len - *used) return 0;
    *used += (size_t)written;
    return 1;
}

static void escape_bytes(char *destination, size_t destination_len, const char *source, size_t source_len) {
    size_t index;
    size_t used = 0u;
    if (destination == 0 || destination_len == 0u) return;
    destination[0] = '\0';
    if (source == 0) return;
    for (index = 0u; index < source_len; index++) {
        unsigned char byte = (unsigned char)source[index];
        char hex[5];
        if (byte == (unsigned char)'\\') {
            if (!append_escaped_byte(destination, destination_len, &used, "\\\\")) break;
        } else if (byte == (unsigned char)'"') {
            if (!append_escaped_byte(destination, destination_len, &used, "\\\"")) break;
        } else if (byte == (unsigned char)'\n') {
            if (!append_escaped_byte(destination, destination_len, &used, "\\n")) break;
        } else if (byte == (unsigned char)'\r') {
            if (!append_escaped_byte(destination, destination_len, &used, "\\r")) break;
        } else if (byte == (unsigned char)'\t') {
            if (!append_escaped_byte(destination, destination_len, &used, "\\t")) break;
        } else if (byte == 0u) {
            if (!append_escaped_byte(destination, destination_len, &used, "\\x00")) break;
        } else {
            hex[0] = (char)byte;
            hex[1] = '\0';
            if (!append_escaped_byte(destination, destination_len, &used, hex)) break;
        }
    }
}

static size_t rail_parent_for_field(const latticra_l_ui_ast_result_t *ast, size_t field_index) {
    size_t rail;
    if (ast == 0) return LATTICRA_LIR_CARD_NODE_INDEX;
    for (rail = 0u; rail < ast->rail_count; rail++) {
        size_t first = ast->rails[rail].first_field_index;
        size_t last = first + ast->rails[rail].field_count;
        if (field_index >= first && field_index < last) return LATTICRA_LIR_FIRST_RAIL_NODE_INDEX + rail;
    }
    return LATTICRA_LIR_CARD_NODE_INDEX;
}

static size_t rail_parent_for_text(const latticra_l_ui_ast_result_t *ast, size_t text_index) {
    size_t rail;
    if (ast == 0) return LATTICRA_LIR_CARD_NODE_INDEX;
    for (rail = 0u; rail < ast->rail_count; rail++) {
        size_t first = ast->rails[rail].first_text_index;
        size_t last = first + ast->rails[rail].text_count;
        if (text_index >= first && text_index < last) return LATTICRA_LIR_FIRST_RAIL_NODE_INDEX + rail;
    }
    return LATTICRA_LIR_CARD_NODE_INDEX;
}

static void set_node(
    latticra_lir_node_t *node,
    latticra_lir_node_kind_t kind,
    const char *name,
    const char *value,
    const char *binding,
    const latticra_l_ui_source_span_t *span,
    size_t parent_index,
    size_t first_child_index,
    size_t child_count) {
    if (node == 0) return;
    node->kind = kind;
    copy_literal(node->name, sizeof(node->name), name);
    copy_literal(node->value, sizeof(node->value), value);
    copy_literal(node->binding, sizeof(node->binding), binding);
    if (span != 0) node->source_span = *span;
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
    const latticra_l_ui_source_span_t *span) {
    if (module == 0 || module->edge_count >= LATTICRA_LIR_EDGE_MAX) return 0;
    module->edges[module->edge_count].from_index = from_index;
    module->edges[module->edge_count].to_index = to_index;
    module->edges[module->edge_count].edge_kind = kind;
    if (span != 0) module->edges[module->edge_count].source_span = *span;
    module->edge_count += 1u;
    return 1;
}

static void mark_semantic_failed(latticra_lir_module_t *module) {
    module->status = LATTICRA_STATUS_OK;
    module->error = LATTICRA_LIR_SEMANTIC_FAILED;
    module->source_kind = LATTICRA_LIR_SOURCE_L_UI_CARD;
    module->node_count = 0u;
    module->edge_count = 0u;
    module->binding_count = 0u;
    module->text_count = 0u;
}

latticra_status_t latticra_lir_lower_l_ui_ast(
    const latticra_l_ui_ast_result_t *ast,
    const latticra_l_ui_semantic_result_t *semantic,
    latticra_lir_module_t *module) {
    size_t index;

    if (ast == 0 || semantic == 0 || module == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    module_default(module);
    if (!prerequisite_ok(ast, semantic)) {
        mark_semantic_failed(module);
        return LATTICRA_STATUS_OK;
    }

    module->status = LATTICRA_STATUS_OK;
    module->error = LATTICRA_LIR_OK;
    module->source_kind = LATTICRA_LIR_SOURCE_L_UI_CARD;
    copy_literal(module->module_name, sizeof(module->module_name), "l_ui_card_module");
    copy_literal(module->card_name, sizeof(module->card_name), ast->card.name);
    copy_literal(module->effect, sizeof(module->effect), ast->card.effect);
    copy_literal(module->boundary, sizeof(module->boundary), ast->card.boundary);
    module->source_span = ast->card.span;
    module->no_effect = ast->no_effect;
    module->execution_allowed = ast->execution_allowed;
    module->mutation_allowed = ast->mutation_allowed;
    module->server_allowed = ast->server_allowed;
    module->recovery_allowed = ast->recovery_allowed;
    module->hardware_allowed = ast->hardware_allowed;

    set_node(&module->nodes[LATTICRA_LIR_MODULE_NODE_INDEX], LATTICRA_LIR_NODE_MODULE, module->module_name, "", "", &ast->card.span, LATTICRA_LIR_ROOT_PARENT, LATTICRA_LIR_CARD_NODE_INDEX, 1u);
    set_node(&module->nodes[LATTICRA_LIR_CARD_NODE_INDEX], LATTICRA_LIR_NODE_CARD, ast->card.name, ast->card.purpose, "", &ast->card.span, LATTICRA_LIR_MODULE_NODE_INDEX, LATTICRA_LIR_FIRST_RAIL_NODE_INDEX, 11u);

    for (index = 0u; index < ast->rail_count && index < 9u; index++) {
        size_t node_index = LATTICRA_LIR_FIRST_RAIL_NODE_INDEX + index;
        size_t first_child = ast->rails[index].field_count > 0u
            ? LATTICRA_LIR_FIRST_FIELD_NODE_INDEX + ast->rails[index].first_field_index
            : LATTICRA_LIR_FIRST_TEXT_NODE_INDEX + ast->rails[index].first_text_index;
        set_node(&module->nodes[node_index], LATTICRA_LIR_NODE_RAIL, ast->rails[index].name, "", "", &ast->rails[index].span, LATTICRA_LIR_CARD_NODE_INDEX, first_child, ast->rails[index].field_count + ast->rails[index].text_count);
    }

    for (index = 0u; index < ast->field_count && index < LATTICRA_LIR_EXPECTED_FIELD_COUNT; index++) {
        size_t node_index = LATTICRA_LIR_FIRST_FIELD_NODE_INDEX + index;
        size_t binding_node = LATTICRA_LIR_FIRST_BINDING_NODE_INDEX + index;
        set_node(&module->nodes[node_index], LATTICRA_LIR_NODE_FIELD, ast->fields[index].name, "", ast->fields[index].binding, &ast->fields[index].span, rail_parent_for_field(ast, index), binding_node, 1u);
    }

    for (index = 0u; index < ast->text_count && index < LATTICRA_LIR_EXPECTED_TEXT_COUNT; index++) {
        size_t node_index = LATTICRA_LIR_FIRST_TEXT_NODE_INDEX + index;
        set_node(&module->nodes[node_index], LATTICRA_LIR_NODE_TEXT, "text", ast->texts[index].value, "", &ast->texts[index].span, rail_parent_for_text(ast, index), 0u, 0u);
        module->texts[index].text_node_index = node_index;
        copy_bytes_compat(module->texts[index].value, sizeof(module->texts[index].value), ast->texts[index].value, ast->texts[index].value_len);
        module->texts[index].value_len = ast->texts[index].value_len;
        escape_bytes(module->texts[index].escaped_value, sizeof(module->texts[index].escaped_value), ast->texts[index].value, ast->texts[index].value_len);
        module->texts[index].source_span = ast->texts[index].span;
        module->text_count += 1u;
    }

    for (index = 0u; index < ast->field_count && index < LATTICRA_LIR_EXPECTED_FIELD_COUNT; index++) {
        size_t node_index = LATTICRA_LIR_FIRST_BINDING_NODE_INDEX + index;
        set_node(&module->nodes[node_index], LATTICRA_LIR_NODE_BINDING, "binding", ast->fields[index].binding, ast->fields[index].binding, &ast->fields[index].binding_span, LATTICRA_LIR_FIRST_FIELD_NODE_INDEX + index, 0u, 0u);
        module->bindings[index].field_node_index = LATTICRA_LIR_FIRST_FIELD_NODE_INDEX + index;
        copy_literal(module->bindings[index].binding_target, sizeof(module->bindings[index].binding_target), ast->fields[index].binding);
        copy_binding_prefix(module->bindings[index].binding_prefix, sizeof(module->bindings[index].binding_prefix), ast->fields[index].binding);
        module->bindings[index].source_span = ast->fields[index].binding_span;
        module->bindings[index].resolved_kind = resolved_binding_kind(ast->fields[index].binding);
        module->binding_count += 1u;
    }

    set_node(&module->nodes[LATTICRA_LIR_EFFECT_NODE_INDEX], LATTICRA_LIR_NODE_EFFECT, "effect", ast->card.effect, "", &ast->card.span, LATTICRA_LIR_CARD_NODE_INDEX, 0u, 0u);
    set_node(&module->nodes[LATTICRA_LIR_BOUNDARY_NODE_INDEX], LATTICRA_LIR_NODE_BOUNDARY, "boundary", ast->card.boundary, "", &ast->card.span, LATTICRA_LIR_CARD_NODE_INDEX, 0u, 0u);
    module->node_count = LATTICRA_LIR_EXPECTED_NODE_COUNT;

    if (!append_edge(module, LATTICRA_LIR_MODULE_NODE_INDEX, LATTICRA_LIR_CARD_NODE_INDEX, LATTICRA_LIR_EDGE_CONTAINS, &ast->card.span)) goto capacity_failed;
    for (index = 0u; index < ast->rail_count && index < 9u; index++) {
        if (!append_edge(module, LATTICRA_LIR_CARD_NODE_INDEX, LATTICRA_LIR_FIRST_RAIL_NODE_INDEX + index, LATTICRA_LIR_EDGE_CONTAINS, &ast->rails[index].span)) goto capacity_failed;
    }
    for (index = 0u; index < ast->field_count && index < LATTICRA_LIR_EXPECTED_FIELD_COUNT; index++) {
        if (!append_edge(module, rail_parent_for_field(ast, index), LATTICRA_LIR_FIRST_FIELD_NODE_INDEX + index, LATTICRA_LIR_EDGE_CONTAINS, &ast->fields[index].span)) goto capacity_failed;
    }
    for (index = 0u; index < ast->text_count && index < LATTICRA_LIR_EXPECTED_TEXT_COUNT; index++) {
        if (!append_edge(module, rail_parent_for_text(ast, index), LATTICRA_LIR_FIRST_TEXT_NODE_INDEX + index, LATTICRA_LIR_EDGE_CONTAINS, &ast->texts[index].span)) goto capacity_failed;
    }
    for (index = 0u; index < ast->field_count && index < LATTICRA_LIR_EXPECTED_FIELD_COUNT; index++) {
        if (!append_edge(module, LATTICRA_LIR_FIRST_FIELD_NODE_INDEX + index, LATTICRA_LIR_FIRST_BINDING_NODE_INDEX + index, LATTICRA_LIR_EDGE_BINDS, &ast->fields[index].binding_span)) goto capacity_failed;
    }
    if (!append_edge(module, LATTICRA_LIR_CARD_NODE_INDEX, LATTICRA_LIR_EFFECT_NODE_INDEX, LATTICRA_LIR_EDGE_ANNOTATES, &ast->card.span)) goto capacity_failed;
    if (!append_edge(module, LATTICRA_LIR_CARD_NODE_INDEX, LATTICRA_LIR_BOUNDARY_NODE_INDEX, LATTICRA_LIR_EDGE_ANNOTATES, &ast->card.span)) goto capacity_failed;

    return LATTICRA_STATUS_OK;

capacity_failed:
    module_default(module);
    module->status = LATTICRA_STATUS_OK;
    module->error = LATTICRA_LIR_CAPACITY_EXCEEDED;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lir_report(
    const latticra_lir_module_t *module,
    char *buffer,
    size_t buffer_len) {
    int written;
    if (module == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA LIR REPORT\n"
        "status=%d\n"
        "error=%s\n"
        "source_kind=%s\n"
        "module=%s\n"
        "card=%s\n"
        "effect=%s\n"
        "boundary=%s\n"
        "node_count=%zu\n"
        "edge_count=%zu\n"
        "binding_count=%zu\n"
        "text_count=%zu\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "server_allowed=%d\n"
        "recovery_allowed=%d\n"
        "hardware_allowed=%d\n"
        "span_start_offset=%zu\n"
        "span_end_offset=%zu\n"
        "span_start_line=%zu\n"
        "span_start_column=%zu\n"
        "span_end_line=%zu\n"
        "span_end_column=%zu\n",
        (int)module->status,
        latticra_lir_error_label(module->error),
        latticra_lir_source_kind_label(module->source_kind),
        module->module_name,
        module->card_name,
        module->effect,
        module->boundary,
        module->node_count,
        module->edge_count,
        module->binding_count,
        module->text_count,
        module->no_effect,
        module->execution_allowed,
        module->mutation_allowed,
        module->server_allowed,
        module->recovery_allowed,
        module->hardware_allowed,
        module->source_span.start_offset,
        module->source_span.end_offset,
        module->source_span.start_line,
        module->source_span.start_column,
        module->source_span.end_line,
        module->source_span.end_column);
    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}

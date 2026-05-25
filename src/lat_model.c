#include "latticra/lat_model.h"

#include <stdio.h>
#include <string.h>

static void copy_text(char *destination, size_t destination_len, const char *source) {
    if (destination == 0 || destination_len == 0u) return;
    (void)snprintf(destination, destination_len, "%s", source == 0 ? "" : source);
}

static void span_default(latticra_lat_source_span_t *span) {
    if (span == 0) return;
    span->start_offset = 0u;
    span->end_offset = 0u;
    span->start_line = 1u;
    span->start_column = 1u;
    span->end_line = 1u;
    span->end_column = 1u;
}

static void declaration_default(latticra_lat_model_declaration_t *declaration) {
    if (declaration == 0) return;
    declaration->kind = LATTICRA_LAT_DECLARATION_UNKNOWN;
    declaration->name[0] = '\0';
    declaration->source_name[0] = '\0';
    declaration->parse_declaration_index = LATTICRA_LAT_MODEL_NO_INDEX;
    declaration->first_clause_index = LATTICRA_LAT_MODEL_NO_INDEX;
    declaration->clause_count = 0u;
    declaration->source_declaration_index = LATTICRA_LAT_MODEL_NO_INDEX;
    span_default(&declaration->span);
}

static void clause_default(latticra_lat_model_clause_t *clause) {
    if (clause == 0) return;
    clause->role = LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN;
    clause->owner_kind = LATTICRA_LAT_DECLARATION_UNKNOWN;
    clause->owner_declaration_index = LATTICRA_LAT_MODEL_NO_INDEX;
    clause->name[0] = '\0';
    clause->operator_text[0] = '\0';
    clause->value[0] = '\0';
    clause->effect = LATTICRA_LAT_EFFECT_UNKNOWN;
    span_default(&clause->span);
}

static void model_default(latticra_lat_model_t *model) {
    size_t index;
    if (model == 0) return;
    model->status = LATTICRA_STATUS_OK;
    model->error = LATTICRA_LAT_MODEL_OK;
    span_default(&model->span);
    model->module_name[0] = '\0';
    for (index = 0u; index < LATTICRA_LAT_DECLARATION_MAX; index++) {
        declaration_default(&model->declarations[index]);
        model->state_indices[index] = LATTICRA_LAT_MODEL_NO_INDEX;
        model->policy_indices[index] = LATTICRA_LAT_MODEL_NO_INDEX;
        model->transition_indices[index] = LATTICRA_LAT_MODEL_NO_INDEX;
        model->assertion_indices[index] = LATTICRA_LAT_MODEL_NO_INDEX;
        model->effect_indices[index] = LATTICRA_LAT_MODEL_NO_INDEX;
    }
    for (index = 0u; index < LATTICRA_LAT_CLAUSE_MAX; index++) {
        clause_default(&model->clauses[index]);
    }
    model->declaration_count = 0u;
    model->clause_count = 0u;
    model->state_count = 0u;
    model->policy_count = 0u;
    model->transition_count = 0u;
    model->assertion_count = 0u;
    model->effect_count = 0u;
    model->first_state_index = LATTICRA_LAT_MODEL_NO_INDEX;
    model->first_policy_index = LATTICRA_LAT_MODEL_NO_INDEX;
    model->first_transition_index = LATTICRA_LAT_MODEL_NO_INDEX;
    model->first_assertion_index = LATTICRA_LAT_MODEL_NO_INDEX;
    model->first_effect_index = LATTICRA_LAT_MODEL_NO_INDEX;
    model->no_effect = 1;
    model->execution_allowed = 0;
    model->mutation_allowed = 0;
    model->server_allowed = 0;
    model->recovery_allowed = 0;
    model->hardware_allowed = 0;
}

const char *latticra_lat_model_error_label(latticra_lat_model_error_t error) {
    switch (error) {
    case LATTICRA_LAT_MODEL_OK: return "ok";
    case LATTICRA_LAT_MODEL_NULL_ARGUMENT: return "null_argument";
    case LATTICRA_LAT_MODEL_PARSE_NOT_OK: return "parse_not_ok";
    case LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK: return "semantic_not_ok";
    case LATTICRA_LAT_MODEL_SEMANTIC_NOT_VALID: return "semantic_not_valid";
    case LATTICRA_LAT_MODEL_NO_EFFECT_VIOLATION: return "no_effect_violation";
    case LATTICRA_LAT_MODEL_CAPACITY_EXCEEDED: return "capacity_exceeded";
    case LATTICRA_LAT_MODEL_UNSUPPORTED_DECLARATION: return "unsupported_declaration";
    case LATTICRA_LAT_MODEL_UNSUPPORTED_CLAUSE: return "unsupported_clause";
    case LATTICRA_LAT_MODEL_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

const char *latticra_lat_model_clause_role_label(latticra_lat_model_clause_role_t role) {
    switch (role) {
    case LATTICRA_LAT_MODEL_CLAUSE_FIELD: return "field";
    case LATTICRA_LAT_MODEL_CLAUSE_REQUIRE: return "require";
    case LATTICRA_LAT_MODEL_CLAUSE_ENSURE: return "ensure";
    case LATTICRA_LAT_MODEL_CLAUSE_EFFECT: return "effect";
    case LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN:
    default: return "unknown";
    }
}

static latticra_lat_model_clause_role_t role_from_keyword(const char *keyword) {
    if (keyword == 0) return LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN;
    if (strcmp(keyword, "field") == 0) return LATTICRA_LAT_MODEL_CLAUSE_FIELD;
    if (strcmp(keyword, "require") == 0) return LATTICRA_LAT_MODEL_CLAUSE_REQUIRE;
    if (strcmp(keyword, "ensure") == 0) return LATTICRA_LAT_MODEL_CLAUSE_ENSURE;
    if (strcmp(keyword, "effect") == 0) return LATTICRA_LAT_MODEL_CLAUSE_EFFECT;
    return LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN;
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

static void copy_summary(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_model_t *model) {
    if (parse_result == 0 || model == 0) return;
    model->span = parse_result->module.span;
    copy_text(model->module_name, sizeof(model->module_name), parse_result->module.module_name);
    model->declaration_count = parse_result->declaration_count;
    model->clause_count = parse_result->clause_count;
    model->no_effect = parse_result->no_effect;
    model->execution_allowed = parse_result->execution_allowed;
    model->mutation_allowed = parse_result->mutation_allowed;
    model->server_allowed = parse_result->server_allowed;
    model->recovery_allowed = parse_result->recovery_allowed;
    model->hardware_allowed = parse_result->hardware_allowed;
}

static size_t find_state_declaration_index(
    const latticra_lat_parse_result_t *parse_result,
    const char *name) {
    size_t index;
    if (parse_result == 0 || name == 0) return LATTICRA_LAT_MODEL_NO_INDEX;
    for (index = 0u; index < parse_result->declaration_count; index++) {
        const latticra_lat_ast_declaration_t *declaration = &parse_result->declarations[index];
        if (declaration->kind == LATTICRA_LAT_DECLARATION_STATE && strcmp(declaration->name, name) == 0) return index;
    }
    return LATTICRA_LAT_MODEL_NO_INDEX;
}

static size_t find_clause_owner(
    const latticra_lat_parse_result_t *parse_result,
    size_t clause_index) {
    size_t index;
    if (parse_result == 0) return LATTICRA_LAT_MODEL_NO_INDEX;
    for (index = 0u; index < parse_result->declaration_count; index++) {
        size_t first = parse_result->declarations[index].first_clause_index;
        size_t last = first + parse_result->declarations[index].clause_count;
        if (clause_index >= first && clause_index < last) return index;
    }
    return LATTICRA_LAT_MODEL_NO_INDEX;
}

static int remember_declaration_index(latticra_lat_model_t *model, size_t index) {
    latticra_lat_model_declaration_t *declaration;
    if (model == 0 || index >= LATTICRA_LAT_DECLARATION_MAX) return 0;
    declaration = &model->declarations[index];
    switch (declaration->kind) {
    case LATTICRA_LAT_DECLARATION_STATE:
        if (model->state_count >= LATTICRA_LAT_DECLARATION_MAX) return 0;
        if (model->first_state_index == LATTICRA_LAT_MODEL_NO_INDEX) model->first_state_index = index;
        model->state_indices[model->state_count] = index;
        model->state_count += 1u;
        return 1;
    case LATTICRA_LAT_DECLARATION_POLICY:
        if (model->policy_count >= LATTICRA_LAT_DECLARATION_MAX) return 0;
        if (model->first_policy_index == LATTICRA_LAT_MODEL_NO_INDEX) model->first_policy_index = index;
        model->policy_indices[model->policy_count] = index;
        model->policy_count += 1u;
        return 1;
    case LATTICRA_LAT_DECLARATION_TRANSITION:
        if (model->transition_count >= LATTICRA_LAT_DECLARATION_MAX) return 0;
        if (model->first_transition_index == LATTICRA_LAT_MODEL_NO_INDEX) model->first_transition_index = index;
        model->transition_indices[model->transition_count] = index;
        model->transition_count += 1u;
        return 1;
    case LATTICRA_LAT_DECLARATION_ASSERTION:
        if (model->assertion_count >= LATTICRA_LAT_DECLARATION_MAX) return 0;
        if (model->first_assertion_index == LATTICRA_LAT_MODEL_NO_INDEX) model->first_assertion_index = index;
        model->assertion_indices[model->assertion_count] = index;
        model->assertion_count += 1u;
        return 1;
    case LATTICRA_LAT_DECLARATION_EFFECT:
        if (model->effect_count >= LATTICRA_LAT_DECLARATION_MAX) return 0;
        if (model->first_effect_index == LATTICRA_LAT_MODEL_NO_INDEX) model->first_effect_index = index;
        model->effect_indices[model->effect_count] = index;
        model->effect_count += 1u;
        return 1;
    case LATTICRA_LAT_DECLARATION_UNKNOWN:
    default:
        return 0;
    }
}

latticra_status_t latticra_lat_model_normalize_module(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lat_model_t *model) {
    size_t index;

    if (model == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    model_default(model);
    if (parse_result == 0 || semantic_result == 0) {
        model->status = LATTICRA_STATUS_NULL_ARGUMENT;
        model->error = LATTICRA_LAT_MODEL_NULL_ARGUMENT;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    copy_summary(parse_result, model);

    if (parse_result->error != LATTICRA_LAT_PARSE_OK) {
        model->error = LATTICRA_LAT_MODEL_PARSE_NOT_OK;
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->error != LATTICRA_LAT_SEMANTIC_OK) {
        model->error = LATTICRA_LAT_MODEL_SEMANTIC_NOT_OK;
        return LATTICRA_STATUS_OK;
    }
    if (semantic_result->semantic_valid != 1) {
        model->error = LATTICRA_LAT_MODEL_SEMANTIC_NOT_VALID;
        return LATTICRA_STATUS_OK;
    }
    if (!no_effect_ok(parse_result, semantic_result)) {
        model->error = LATTICRA_LAT_MODEL_NO_EFFECT_VIOLATION;
        return LATTICRA_STATUS_OK;
    }
    if (parse_result->declaration_count > LATTICRA_LAT_DECLARATION_MAX ||
        parse_result->clause_count > LATTICRA_LAT_CLAUSE_MAX) {
        model->error = LATTICRA_LAT_MODEL_CAPACITY_EXCEEDED;
        return LATTICRA_STATUS_OK;
    }

    for (index = 0u; index < parse_result->declaration_count; index++) {
        const latticra_lat_ast_declaration_t *source = &parse_result->declarations[index];
        latticra_lat_model_declaration_t *destination = &model->declarations[index];

        destination->kind = source->kind;
        copy_text(destination->name, sizeof(destination->name), source->name);
        copy_text(destination->source_name, sizeof(destination->source_name), source->source_name);
        destination->parse_declaration_index = index;
        destination->first_clause_index = source->first_clause_index;
        destination->clause_count = source->clause_count;
        destination->source_declaration_index = LATTICRA_LAT_MODEL_NO_INDEX;
        destination->span = source->span;

        if (source->kind == LATTICRA_LAT_DECLARATION_TRANSITION) {
            destination->source_declaration_index = find_state_declaration_index(parse_result, source->source_name);
            if (destination->source_declaration_index == LATTICRA_LAT_MODEL_NO_INDEX) {
                model->error = LATTICRA_LAT_MODEL_SEMANTIC_NOT_VALID;
                return LATTICRA_STATUS_OK;
            }
        }

        if (!remember_declaration_index(model, index)) {
            model->error = LATTICRA_LAT_MODEL_UNSUPPORTED_DECLARATION;
            return LATTICRA_STATUS_OK;
        }
    }

    for (index = 0u; index < parse_result->clause_count; index++) {
        const latticra_lat_ast_clause_t *source = &parse_result->clauses[index];
        latticra_lat_model_clause_t *destination = &model->clauses[index];
        size_t owner = find_clause_owner(parse_result, index);

        if (owner == LATTICRA_LAT_MODEL_NO_INDEX) {
            model->error = LATTICRA_LAT_MODEL_INTERNAL_ERROR;
            return LATTICRA_STATUS_OK;
        }

        destination->role = role_from_keyword(source->keyword);
        if (destination->role == LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN) {
            model->error = LATTICRA_LAT_MODEL_UNSUPPORTED_CLAUSE;
            return LATTICRA_STATUS_OK;
        }
        destination->owner_declaration_index = owner;
        destination->owner_kind = parse_result->declarations[owner].kind;
        copy_text(destination->name, sizeof(destination->name), source->left);
        copy_text(destination->operator_text, sizeof(destination->operator_text), source->operator_text);
        copy_text(destination->value, sizeof(destination->value), source->right);
        destination->effect = source->effect;
        destination->span = source->span;
    }

    model->error = LATTICRA_LAT_MODEL_OK;
    model->no_effect = 1;
    model->execution_allowed = 0;
    model->mutation_allowed = 0;
    model->server_allowed = 0;
    model->recovery_allowed = 0;
    model->hardware_allowed = 0;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lat_model_report(
    const latticra_lat_model_t *model,
    char *buffer,
    size_t buffer_len) {
    int written;
    size_t first_transition_source;
    size_t first_clause_index;
    latticra_lat_model_clause_role_t first_clause_role;
    latticra_lat_effect_t first_clause_effect;
    const char *first_clause_name;
    const char *first_clause_operator;
    const char *first_clause_value;
    if (model == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    first_transition_source = model->first_transition_index == LATTICRA_LAT_MODEL_NO_INDEX ?
        LATTICRA_LAT_MODEL_NO_INDEX :
        model->declarations[model->first_transition_index].source_declaration_index;
    first_clause_index = LATTICRA_LAT_MODEL_NO_INDEX;
    first_clause_role = LATTICRA_LAT_MODEL_CLAUSE_UNKNOWN;
    first_clause_effect = LATTICRA_LAT_EFFECT_UNKNOWN;
    first_clause_name = "";
    first_clause_operator = "";
    first_clause_value = "";
    if (model->error == LATTICRA_LAT_MODEL_OK && model->clause_count > 0u) {
        const latticra_lat_model_clause_t *clause = &model->clauses[0];
        first_clause_index = 0u;
        first_clause_role = clause->role;
        first_clause_effect = clause->effect;
        first_clause_name = clause->name;
        first_clause_operator = clause->operator_text;
        first_clause_value = clause->value;
    }
    written = snprintf(
        buffer,
        buffer_len,
        "LAT MODEL NORMALIZATION REPORT\n"
        "status=%d\n"
        "error=%s\n"
        "module=%s\n"
        "declaration_count=%zu\n"
        "state_count=%zu\n"
        "policy_count=%zu\n"
        "transition_count=%zu\n"
        "assertion_count=%zu\n"
        "effect_count=%zu\n"
        "clause_count=%zu\n"
        "first_state_index=%zu\n"
        "first_policy_index=%zu\n"
        "first_transition_index=%zu\n"
        "first_transition_source_index=%zu\n"
        "first_clause_index=%zu\n"
        "first_clause_role=%s\n"
        "first_clause_effect=%s\n"
        "first_clause_name=%s\n"
        "first_clause_operator=%s\n"
        "first_clause_value=%s\n"
        "first_assertion_index=%zu\n"
        "first_effect_index=%zu\n"
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
        (int)model->status,
        latticra_lat_model_error_label(model->error),
        model->module_name,
        model->declaration_count,
        model->state_count,
        model->policy_count,
        model->transition_count,
        model->assertion_count,
        model->effect_count,
        model->clause_count,
        model->first_state_index,
        model->first_policy_index,
        model->first_transition_index,
        first_transition_source,
        first_clause_index,
        latticra_lat_model_clause_role_label(first_clause_role),
        latticra_lat_effect_label(first_clause_effect),
        first_clause_name,
        first_clause_operator,
        first_clause_value,
        model->first_assertion_index,
        model->first_effect_index,
        model->no_effect,
        model->execution_allowed,
        model->mutation_allowed,
        model->server_allowed,
        model->recovery_allowed,
        model->hardware_allowed,
        model->span.start_offset,
        model->span.end_offset,
        model->span.start_line,
        model->span.start_column,
        model->span.end_line,
        model->span.end_column);
    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) buffer[0] = '\0';
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    return LATTICRA_STATUS_OK;
}

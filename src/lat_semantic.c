#include "latticra/lat_semantic.h"

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

static void diagnostic_default(latticra_lat_semantic_diagnostic_t *diagnostic) {
    if (diagnostic == 0) return;
    diagnostic->error = LATTICRA_LAT_SEMANTIC_OK;
    span_default(&diagnostic->span);
    diagnostic->declaration_index = 0u;
    diagnostic->clause_index = 0u;
    diagnostic->name[0] = '\0';
    diagnostic->detail[0] = '\0';
}

static void result_default(latticra_lat_semantic_result_t *result) {
    size_t index;
    if (result == 0) return;
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_LAT_SEMANTIC_OK;
    span_default(&result->span);
    result->module_name[0] = '\0';
    result->semantic_valid = 0;
    result->diagnostic_count = 0u;
    result->diagnostic_class = LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID;
    result->parse_diagnostic_count = 0u;
    result->declaration_diagnostic_count = 0u;
    result->reference_diagnostic_count = 0u;
    result->requirement_diagnostic_count = 0u;
    result->effect_diagnostic_count = 0u;
    result->no_effect_diagnostic_count = 0u;
    result->internal_diagnostic_count = 0u;
    result->first_diagnostic_declaration_index = 0u;
    result->first_diagnostic_clause_index = 0u;
    for (index = 0u; index < LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_MAX; index++) {
        diagnostic_default(&result->diagnostics[index]);
    }
    result->declaration_count = 0u;
    result->state_count = 0u;
    result->policy_count = 0u;
    result->transition_count = 0u;
    result->assertion_count = 0u;
    result->effect_count = 0u;
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->network_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

const char *latticra_lat_semantic_error_label(latticra_lat_semantic_error_t error) {
    switch (error) {
    case LATTICRA_LAT_SEMANTIC_OK: return "ok";
    case LATTICRA_LAT_SEMANTIC_NULL_ARGUMENT: return "null_argument";
    case LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK: return "parse_not_ok";
    case LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION: return "duplicate_declaration";
    case LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE: return "unknown_transition_source";
    case LATTICRA_LAT_SEMANTIC_INVALID_STATE_FIELD: return "invalid_state_field";
    case LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT: return "invalid_require_left";
    case LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET: return "invalid_effect_target";
    case LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_VALUE: return "invalid_effect_value";
    case LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE: return "effect_requires_gate";
    case LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION: return "invalid_clause_for_declaration";
    case LATTICRA_LAT_SEMANTIC_EMPTY_DECLARATION: return "empty_declaration";
    case LATTICRA_LAT_SEMANTIC_NO_EFFECT_VIOLATION: return "no_effect_violation";
    case LATTICRA_LAT_SEMANTIC_CAPACITY_EXCEEDED: return "capacity_exceeded";
    case LATTICRA_LAT_SEMANTIC_INTERNAL_ERROR:
    default: return "internal_error";
    }
}

const char *latticra_lat_semantic_diagnostic_class_label(latticra_lat_semantic_diagnostic_class_t diagnostic_class) {
    switch (diagnostic_class) {
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID: return "valid";
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_PARSE: return "parse";
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_DECLARATION: return "declaration";
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REFERENCE: return "reference";
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REQUIREMENT: return "requirement";
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_EFFECT: return "effect";
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_NO_EFFECT: return "no-effect";
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_INTERNAL:
    default: return "internal";
    }
}

static latticra_lat_semantic_diagnostic_class_t diagnostic_class_for_error(latticra_lat_semantic_error_t error) {
    switch (error) {
    case LATTICRA_LAT_SEMANTIC_OK: return LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID;
    case LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK: return LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_PARSE;
    case LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION:
    case LATTICRA_LAT_SEMANTIC_INVALID_STATE_FIELD:
    case LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION:
    case LATTICRA_LAT_SEMANTIC_EMPTY_DECLARATION:
        return LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_DECLARATION;
    case LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE:
        return LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REFERENCE;
    case LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT:
        return LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REQUIREMENT;
    case LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET:
    case LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_VALUE:
    case LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE:
        return LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_EFFECT;
    case LATTICRA_LAT_SEMANTIC_NO_EFFECT_VIOLATION:
        return LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_NO_EFFECT;
    case LATTICRA_LAT_SEMANTIC_NULL_ARGUMENT:
    case LATTICRA_LAT_SEMANTIC_CAPACITY_EXCEEDED:
    case LATTICRA_LAT_SEMANTIC_INTERNAL_ERROR:
    default:
        return LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_INTERNAL;
    }
}

static void count_diagnostic_class(latticra_lat_semantic_result_t *result, latticra_lat_semantic_diagnostic_class_t diagnostic_class) {
    if (result == 0) return;
    switch (diagnostic_class) {
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_PARSE:
        result->parse_diagnostic_count += 1u;
        break;
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_DECLARATION:
        result->declaration_diagnostic_count += 1u;
        break;
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REFERENCE:
        result->reference_diagnostic_count += 1u;
        break;
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_REQUIREMENT:
        result->requirement_diagnostic_count += 1u;
        break;
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_EFFECT:
        result->effect_diagnostic_count += 1u;
        break;
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_NO_EFFECT:
        result->no_effect_diagnostic_count += 1u;
        break;
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_INTERNAL:
        result->internal_diagnostic_count += 1u;
        break;
    case LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID:
    default:
        break;
    }
}

static int add_diagnostic(
    latticra_lat_semantic_result_t *result,
    latticra_lat_semantic_error_t error,
    const latticra_lat_source_span_t *span,
    size_t declaration_index,
    size_t clause_index,
    const char *name,
    const char *detail) {
    latticra_lat_semantic_diagnostic_t *diagnostic;
    latticra_lat_semantic_diagnostic_class_t diagnostic_class;
    if (result == 0) return 0;
    result->semantic_valid = 0;
    diagnostic_class = diagnostic_class_for_error(error);
    if (result->diagnostic_count >= LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_MAX) {
        if (result->error == LATTICRA_LAT_SEMANTIC_OK) {
            result->error = LATTICRA_LAT_SEMANTIC_CAPACITY_EXCEEDED;
            result->diagnostic_class = LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_INTERNAL;
            result->internal_diagnostic_count += 1u;
        }
        return 0;
    }
    diagnostic = &result->diagnostics[result->diagnostic_count];
    diagnostic->error = error;
    if (span != 0) diagnostic->span = *span;
    diagnostic->declaration_index = declaration_index;
    diagnostic->clause_index = clause_index;
    copy_text(diagnostic->name, sizeof(diagnostic->name), name);
    copy_text(diagnostic->detail, sizeof(diagnostic->detail), detail);
    if (result->diagnostic_count == 0u) {
        result->first_diagnostic_declaration_index = declaration_index;
        result->first_diagnostic_clause_index = clause_index;
    }
    count_diagnostic_class(result, diagnostic_class);
    if (result->error == LATTICRA_LAT_SEMANTIC_OK) {
        result->error = error;
        result->diagnostic_class = diagnostic_class;
        result->span = diagnostic->span;
    }
    result->diagnostic_count += 1u;
    return 1;
}

static int text_eq(const char *left, const char *right) {
    if (left == 0 || right == 0) return 0;
    return strcmp(left, right) == 0;
}

static int is_state_field(const char *field) {
    static const char *fields[] = {
        "origin",
        "route",
        "axis",
        "path",
        "breadcrumb",
        "trace",
        "safe_portal",
        "rollback",
        "health",
        "risk",
        "lock",
        "dark_phase",
        "host_effect",
        "external_effect"
    };
    size_t index;
    for (index = 0u; index < sizeof(fields) / sizeof(fields[0]); index++) {
        if (text_eq(field, fields[index])) return 1;
    }
    return 0;
}

static int is_effect_state_field(const char *field) {
    return text_eq(field, "host_effect") || text_eq(field, "external_effect");
}

static int is_requirement_left(const char *left) {
    if (is_state_field(left)) return 1;
    if (text_eq(left, "host")) return 1;
    if (text_eq(left, "external")) return 1;
    if (text_eq(left, "local")) return 1;
    if (text_eq(left, "network")) return 1;
    if (text_eq(left, "hardware")) return 1;
    if (text_eq(left, "boot")) return 1;
    if (text_eq(left, "recovery")) return 1;
    return 0;
}

static int is_transition_effect_target(const char *target) {
    return text_eq(target, "host") || text_eq(target, "external");
}

static int is_effect_declaration_target(const char *target) {
    if (text_eq(target, "host")) return 1;
    if (text_eq(target, "external")) return 1;
    if (text_eq(target, "local")) return 1;
    if (text_eq(target, "network")) return 1;
    if (text_eq(target, "hardware")) return 1;
    if (text_eq(target, "boot")) return 1;
    if (text_eq(target, "recovery")) return 1;
    return 0;
}

static int is_known_effect_value(latticra_lat_effect_t effect) {
    return effect != LATTICRA_LAT_EFFECT_UNKNOWN;
}

static int find_state_name(const latticra_lat_parse_result_t *parse_result, const char *name) {
    size_t index;
    if (parse_result == 0 || name == 0) return 0;
    for (index = 0u; index < parse_result->declaration_count; index++) {
        const latticra_lat_ast_declaration_t *declaration = &parse_result->declarations[index];
        if (declaration->kind == LATTICRA_LAT_DECLARATION_STATE && text_eq(declaration->name, name)) return 1;
    }
    return 0;
}

static void copy_counts_from_parse(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *result) {
    if (parse_result == 0 || result == 0) return;
    copy_text(result->module_name, sizeof(result->module_name), parse_result->module.module_name);
    result->span = parse_result->span;
    result->declaration_count = parse_result->declaration_count;
    result->state_count = parse_result->module.state_count;
    result->policy_count = parse_result->module.policy_count;
    result->transition_count = parse_result->module.transition_count;
    result->assertion_count = parse_result->module.assertion_count;
    result->effect_count = parse_result->module.effect_count;
    result->no_effect = parse_result->no_effect;
    result->execution_allowed = parse_result->execution_allowed;
    result->mutation_allowed = parse_result->mutation_allowed;
    result->server_allowed = parse_result->server_allowed;
    result->network_allowed = parse_result->network_allowed;
    result->recovery_allowed = parse_result->recovery_allowed;
    result->hardware_allowed = parse_result->hardware_allowed;
}

static void validate_declared_effect_value(
    latticra_lat_semantic_result_t *result,
    const latticra_lat_ast_clause_t *clause,
    size_t declaration_index,
    size_t clause_index) {
    if (clause == 0) return;
    if (!is_known_effect_value(clause->effect)) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_VALUE,
            &clause->span,
            declaration_index,
            clause_index,
            clause->left,
            clause->right);
        return;
    }
    if (clause->effect != LATTICRA_LAT_EFFECT_NONE) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE,
            &clause->span,
            declaration_index,
            clause_index,
            clause->left,
            clause->right);
    }
}

static void validate_duplicate_declarations(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *result) {
    size_t left;
    if (parse_result == 0 || result == 0) return;
    for (left = 0u; left < parse_result->declaration_count; left++) {
        size_t right;
        for (right = left + 1u; right < parse_result->declaration_count; right++) {
            if (text_eq(parse_result->declarations[left].name, parse_result->declarations[right].name)) {
                (void)add_diagnostic(
                    result,
                    LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION,
                    &parse_result->declarations[right].span,
                    right,
                    0u,
                    parse_result->declarations[right].name,
                    parse_result->declarations[left].name);
            }
        }
    }
}

static void validate_no_effect_flags(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *result) {
    if (parse_result == 0 || result == 0) return;
    if (parse_result->no_effect != 1 ||
        parse_result->execution_allowed != 0 ||
        parse_result->mutation_allowed != 0 ||
        parse_result->server_allowed != 0 ||
        parse_result->network_allowed != 0 ||
        parse_result->recovery_allowed != 0 ||
        parse_result->hardware_allowed != 0) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_NO_EFFECT_VIOLATION,
            &parse_result->span,
            0u,
            0u,
            parse_result->module.module_name,
            "no_effect_flags");
    }
}

static void validate_state_declaration(
    latticra_lat_semantic_result_t *result,
    const latticra_lat_ast_declaration_t *declaration,
    const latticra_lat_ast_clause_t *clause,
    size_t declaration_index,
    size_t clause_index) {
    if (result == 0 || declaration == 0 || clause == 0) return;
    if (!text_eq(clause->keyword, "field")) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION,
            &clause->span,
            declaration_index,
            clause_index,
            declaration->name,
            clause->keyword);
        return;
    }
    if (!is_state_field(clause->left)) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_INVALID_STATE_FIELD,
            &clause->span,
            declaration_index,
            clause_index,
            clause->left,
            declaration->name);
        return;
    }
    if (is_effect_state_field(clause->left)) {
        validate_declared_effect_value(result, clause, declaration_index, clause_index);
    }
}

static void validate_requirement_clause(
    latticra_lat_semantic_result_t *result,
    const latticra_lat_ast_declaration_t *declaration,
    const latticra_lat_ast_clause_t *clause,
    size_t declaration_index,
    size_t clause_index) {
    if (result == 0 || declaration == 0 || clause == 0) return;
    if (!(text_eq(clause->keyword, "require") || text_eq(clause->keyword, "ensure"))) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION,
            &clause->span,
            declaration_index,
            clause_index,
            declaration->name,
            clause->keyword);
        return;
    }
    if (!is_requirement_left(clause->left)) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT,
            &clause->span,
            declaration_index,
            clause_index,
            clause->left,
            declaration->name);
    }
}

static void validate_transition_declaration(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *result,
    const latticra_lat_ast_declaration_t *declaration,
    const latticra_lat_ast_clause_t *clause,
    size_t declaration_index,
    size_t clause_index) {
    if (parse_result == 0 || result == 0 || declaration == 0 || clause == 0) return;
    if (!find_state_name(parse_result, declaration->source_name)) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE,
            &declaration->span,
            declaration_index,
            0u,
            declaration->source_name,
            declaration->name);
        return;
    }
    if (text_eq(clause->keyword, "require")) {
        if (!is_requirement_left(clause->left)) {
            (void)add_diagnostic(
                result,
                LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT,
                &clause->span,
                declaration_index,
                clause_index,
                clause->left,
                declaration->name);
        }
        return;
    }
    if (text_eq(clause->keyword, "effect")) {
        if (!is_transition_effect_target(clause->left)) {
            (void)add_diagnostic(
                result,
                LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET,
                &clause->span,
                declaration_index,
                clause_index,
                clause->left,
                declaration->name);
            return;
        }
        validate_declared_effect_value(result, clause, declaration_index, clause_index);
        return;
    }
    (void)add_diagnostic(
        result,
        LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION,
        &clause->span,
        declaration_index,
        clause_index,
        declaration->name,
        clause->keyword);
}

static void validate_effect_declaration(
    latticra_lat_semantic_result_t *result,
    const latticra_lat_ast_declaration_t *declaration,
    const latticra_lat_ast_clause_t *clause,
    size_t declaration_index,
    size_t clause_index) {
    if (result == 0 || declaration == 0 || clause == 0) return;
    if (!text_eq(clause->keyword, "field")) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION,
            &clause->span,
            declaration_index,
            clause_index,
            declaration->name,
            clause->keyword);
        return;
    }
    if (!is_effect_declaration_target(clause->left)) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET,
            &clause->span,
            declaration_index,
            clause_index,
            clause->left,
            declaration->name);
        return;
    }
    validate_declared_effect_value(result, clause, declaration_index, clause_index);
}

static void validate_declaration(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *result,
    const latticra_lat_ast_declaration_t *declaration,
    size_t declaration_index) {
    size_t local_index;
    if (parse_result == 0 || result == 0 || declaration == 0) return;
    if (declaration->clause_count == 0u) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_EMPTY_DECLARATION,
            &declaration->span,
            declaration_index,
            0u,
            declaration->name,
            latticra_lat_declaration_kind_label(declaration->kind));
        return;
    }
    if (declaration->first_clause_index + declaration->clause_count > parse_result->clause_count) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_INTERNAL_ERROR,
            &declaration->span,
            declaration_index,
            0u,
            declaration->name,
            "clause_range");
        return;
    }
    for (local_index = 0u; local_index < declaration->clause_count; local_index++) {
        size_t clause_index = declaration->first_clause_index + local_index;
        const latticra_lat_ast_clause_t *clause = &parse_result->clauses[clause_index];
        if (declaration->kind == LATTICRA_LAT_DECLARATION_STATE) {
            validate_state_declaration(result, declaration, clause, declaration_index, clause_index);
        } else if (declaration->kind == LATTICRA_LAT_DECLARATION_POLICY ||
                   declaration->kind == LATTICRA_LAT_DECLARATION_ASSERTION) {
            validate_requirement_clause(result, declaration, clause, declaration_index, clause_index);
        } else if (declaration->kind == LATTICRA_LAT_DECLARATION_TRANSITION) {
            validate_transition_declaration(parse_result, result, declaration, clause, declaration_index, clause_index);
        } else if (declaration->kind == LATTICRA_LAT_DECLARATION_EFFECT) {
            validate_effect_declaration(result, declaration, clause, declaration_index, clause_index);
        } else {
            (void)add_diagnostic(
                result,
                LATTICRA_LAT_SEMANTIC_INTERNAL_ERROR,
                &declaration->span,
                declaration_index,
                clause_index,
                declaration->name,
                "unknown_declaration_kind");
        }
    }
}

latticra_status_t latticra_lat_validate_module(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *result) {
    size_t declaration_index;
    if (result == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    result_default(result);
    if (parse_result == 0) {
        result->status = LATTICRA_STATUS_NULL_ARGUMENT;
        result->error = LATTICRA_LAT_SEMANTIC_NULL_ARGUMENT;
        result->diagnostic_class = LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_INTERNAL;
        result->internal_diagnostic_count = 1u;
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    copy_counts_from_parse(parse_result, result);
    if (parse_result->error != LATTICRA_LAT_PARSE_OK) {
        (void)add_diagnostic(
            result,
            LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK,
            &parse_result->span,
            0u,
            0u,
            parse_result->module.module_name,
            latticra_lat_parse_error_label(parse_result->error));
        return LATTICRA_STATUS_OK;
    }
    validate_no_effect_flags(parse_result, result);
    validate_duplicate_declarations(parse_result, result);
    for (declaration_index = 0u; declaration_index < parse_result->declaration_count; declaration_index++) {
        validate_declaration(parse_result, result, &parse_result->declarations[declaration_index], declaration_index);
    }
    if (result->diagnostic_count == 0u) {
        result->error = LATTICRA_LAT_SEMANTIC_OK;
        result->diagnostic_class = LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_CLASS_VALID;
        result->semantic_valid = 1;
    }
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_lat_semantic_report(
    const latticra_lat_semantic_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;
    const latticra_lat_semantic_diagnostic_t *first;
    if (result == 0 || buffer == 0) return LATTICRA_STATUS_NULL_ARGUMENT;
    first = result->diagnostic_count == 0u ? 0 : &result->diagnostics[0];
    written = snprintf(
        buffer,
        buffer_len,
        "LAT SEMANTIC REPORT\n"
        "status=%d\n"
        "error=%s\n"
        "diagnostic_class=%s\n"
        "semantic_valid=%d\n"
        "module=%s\n"
        "declaration_count=%zu\n"
        "state_count=%zu\n"
        "policy_count=%zu\n"
        "transition_count=%zu\n"
        "assertion_count=%zu\n"
        "effect_count=%zu\n"
        "diagnostic_count=%zu\n"
        "parse_diagnostic_count=%zu\n"
        "declaration_diagnostic_count=%zu\n"
        "reference_diagnostic_count=%zu\n"
        "requirement_diagnostic_count=%zu\n"
        "effect_diagnostic_count=%zu\n"
        "no_effect_diagnostic_count=%zu\n"
        "internal_diagnostic_count=%zu\n"
        "first_diagnostic_declaration_index=%zu\n"
        "first_diagnostic_clause_index=%zu\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "server_allowed=%d\n"
        "network_allowed=%d\n"
        "recovery_allowed=%d\n"
        "hardware_allowed=%d\n"
        "first_diagnostic_error=%s\n"
        "first_diagnostic_name=%s\n"
        "first_diagnostic_detail=%s\n"
        "span_start_offset=%zu\n"
        "span_end_offset=%zu\n"
        "span_start_line=%zu\n"
        "span_start_column=%zu\n"
        "span_end_line=%zu\n"
        "span_end_column=%zu\n",
        (int)result->status,
        latticra_lat_semantic_error_label(result->error),
        latticra_lat_semantic_diagnostic_class_label(result->diagnostic_class),
        result->semantic_valid,
        result->module_name,
        result->declaration_count,
        result->state_count,
        result->policy_count,
        result->transition_count,
        result->assertion_count,
        result->effect_count,
        result->diagnostic_count,
        result->parse_diagnostic_count,
        result->declaration_diagnostic_count,
        result->reference_diagnostic_count,
        result->requirement_diagnostic_count,
        result->effect_diagnostic_count,
        result->no_effect_diagnostic_count,
        result->internal_diagnostic_count,
        result->first_diagnostic_declaration_index,
        result->first_diagnostic_clause_index,
        result->no_effect,
        result->execution_allowed,
        result->mutation_allowed,
        result->server_allowed,
        result->network_allowed,
        result->recovery_allowed,
        result->hardware_allowed,
        first == 0 ? "ok" : latticra_lat_semantic_error_label(first->error),
        first == 0 ? "" : first->name,
        first == 0 ? "" : first->detail,
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

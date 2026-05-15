#include "latticra/l_ui_parser.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source);
}

static void set_safe_defaults(latticra_l_ui_parse_result_t *result) {
    result->status = LATTICRA_STATUS_OK;
    result->error = LATTICRA_L_UI_PARSE_OK;
    result->line = 1u;
    result->column = 1u;
    result->card_name[0] = '\0';
    result->rail_count = 0u;
    result->field_count = 0u;
    copy_literal(result->effect, sizeof(result->effect), "none");
    copy_literal(result->boundary, sizeof(result->boundary), "preview_only");
    result->no_effect = 1;
    result->execution_allowed = 0;
    result->mutation_allowed = 0;
    result->server_allowed = 0;
    result->recovery_allowed = 0;
    result->hardware_allowed = 0;
}

static latticra_status_t set_error(
    latticra_l_ui_parse_result_t *result,
    latticra_l_ui_parse_error_t error) {
    set_safe_defaults(result);
    result->error = error;
    return LATTICRA_STATUS_OK;
}

static int contains_slice(const char *source, size_t source_len, const char *needle) {
    size_t needle_len = strlen(needle);
    size_t index;

    if (needle_len == 0u) {
        return 1;
    }
    if (source_len < needle_len) {
        return 0;
    }

    for (index = 0u; index <= source_len - needle_len; index++) {
        if (memcmp(source + index, needle, needle_len) == 0) {
            return 1;
        }
    }

    return 0;
}

static int braces_are_balanced(const char *source, size_t source_len) {
    size_t index;
    int depth = 0;

    for (index = 0u; index < source_len; index++) {
        if (source[index] == '{') {
            depth++;
        } else if (source[index] == '}') {
            depth--;
            if (depth < 0) {
                return 0;
            }
        }
    }

    return depth == 0;
}

static int strings_are_terminated(const char *source, size_t source_len) {
    size_t index;
    int in_string = 0;
    int escaped = 0;

    for (index = 0u; index < source_len; index++) {
        char ch = source[index];
        if (escaped) {
            escaped = 0;
            continue;
        }
        if (ch == '\\') {
            escaped = 1;
            continue;
        }
        if (ch == '"') {
            in_string = !in_string;
        }
    }

    return !in_string;
}

static int has_unsupported_effect(const char *source, size_t source_len) {
    const char *effects[] = {
        "effect read",
        "effect local_mutation",
        "effect host_mutation",
        "effect network",
        "effect hardware",
        "effect boot",
        "effect recovery",
        "effect external"
    };
    size_t index;

    for (index = 0u; index < sizeof(effects) / sizeof(effects[0]); index++) {
        if (contains_slice(source, source_len, effects[index])) {
            return 1;
        }
    }

    return 0;
}

static int has_forbidden_marker(const char *source, size_t source_len) {
    const char *markers[] = {
        "execute ",
        "host_mutation",
        "effect network",
        "effect hardware",
        "effect boot",
        "effect recovery",
        "self_update",
        "server call",
        "server_interaction {"
    };
    size_t index;

    for (index = 0u; index < sizeof(markers) / sizeof(markers[0]); index++) {
        if (contains_slice(source, source_len, markers[index])) {
            return 1;
        }
    }

    return 0;
}

static latticra_l_ui_parse_error_t validate_required_rails(const char *source, size_t source_len) {
    const char *rails[] = {
        "rail top {",
        "rail state {",
        "rail trace {",
        "rail safety {",
        "rail gates {",
        "rail effects {",
        "rail policy {",
        "rail execution {",
        "rail bottom {"
    };
    size_t index;

    for (index = 0u; index < sizeof(rails) / sizeof(rails[0]); index++) {
        if (!contains_slice(source, source_len, rails[index])) {
            return LATTICRA_L_UI_PARSE_MISSING_RAIL;
        }
    }

    return LATTICRA_L_UI_PARSE_OK;
}

static latticra_l_ui_parse_error_t validate_required_bindings(const char *source, size_t source_len) {
    const char *bindings[] = {
        "field origin bind state.origin",
        "field route bind state.route",
        "field axis bind state.axis",
        "field path bind state.path",
        "field breadcrumb bind state.breadcrumb",
        "field trace bind state.trace",
        "field health bind state.health",
        "field risk bind state.risk",
        "field lock bind state.lock",
        "field dark_phase bind state.dark_phase",
        "field safe_portal bind state.safe_portal",
        "field rollback bind state.rollback",
        "field host bind state.host_effect",
        "field external bind state.external_effect",
        "field requested bind preview.requested_effect",
        "field request bind preview.request",
        "field policy bind preview.policy",
        "field reason bind preview.reason",
        "field executed bind preview.executed",
        "field mutation bind preview.mutation_allowed",
        "field server bind preview.server_interaction_allowed",
        "field recovery bind preview.recovery_allowed",
        "field hardware bind preview.hardware_allowed"
    };
    size_t index;

    for (index = 0u; index < sizeof(bindings) / sizeof(bindings[0]); index++) {
        if (!contains_slice(source, source_len, bindings[index])) {
            return LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING;
        }
    }

    return LATTICRA_L_UI_PARSE_OK;
}

static int has_unknown_binding_prefix(const char *source, size_t source_len) {
    if (contains_slice(source, source_len, " bind host.")) {
        return 1;
    }
    if (contains_slice(source, source_len, " bind network.")) {
        return 1;
    }
    if (contains_slice(source, source_len, " bind hardware.")) {
        return 1;
    }
    if (contains_slice(source, source_len, " bind server.")) {
        return 1;
    }
    return 0;
}

const char *latticra_l_ui_parse_error_label(latticra_l_ui_parse_error_t error) {
    switch (error) {
    case LATTICRA_L_UI_PARSE_OK:
        return "ok";
    case LATTICRA_L_UI_PARSE_NULL_ARGUMENT:
        return "null_argument";
    case LATTICRA_L_UI_PARSE_EMPTY_SOURCE:
        return "empty_source";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION:
        return "unsupported_version";
    case LATTICRA_L_UI_PARSE_MISSING_CARD:
        return "missing_card";
    case LATTICRA_L_UI_PARSE_MISSING_PURPOSE:
        return "missing_purpose";
    case LATTICRA_L_UI_PARSE_MISSING_EFFECT:
        return "missing_effect";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT:
        return "unsupported_effect";
    case LATTICRA_L_UI_PARSE_MISSING_BOUNDARY:
        return "missing_boundary";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY:
        return "unsupported_boundary";
    case LATTICRA_L_UI_PARSE_MISSING_RAIL:
        return "missing_rail";
    case LATTICRA_L_UI_PARSE_UNKNOWN_RAIL:
        return "unknown_rail";
    case LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX:
        return "unknown_binding_prefix";
    case LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING:
        return "missing_required_binding";
    case LATTICRA_L_UI_PARSE_UNTERMINATED_STRING:
        return "unterminated_string";
    case LATTICRA_L_UI_PARSE_UNBALANCED_BRACE:
        return "unbalanced_brace";
    case LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER:
        return "forbidden_behavior_marker";
    case LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE:
        return "source_too_large";
    case LATTICRA_L_UI_PARSE_INTERNAL_ERROR:
    default:
        return "internal_error";
    }
}

latticra_status_t latticra_l_ui_parse_source(
    const char *source,
    size_t source_len,
    latticra_l_ui_parse_result_t *result) {
    latticra_l_ui_parse_error_t rail_error;
    latticra_l_ui_parse_error_t binding_error;

    if (source == 0 || result == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    set_safe_defaults(result);

    if (source_len == 0u) {
        return set_error(result, LATTICRA_L_UI_PARSE_EMPTY_SOURCE);
    }

    if (source_len > LATTICRA_L_UI_SOURCE_MAX) {
        return set_error(result, LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE);
    }

    if (!strings_are_terminated(source, source_len)) {
        return set_error(result, LATTICRA_L_UI_PARSE_UNTERMINATED_STRING);
    }

    if (!braces_are_balanced(source, source_len)) {
        return set_error(result, LATTICRA_L_UI_PARSE_UNBALANCED_BRACE);
    }

    if (!contains_slice(source, source_len, "lui 0.1")) {
        return set_error(result, LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION);
    }

    if (!contains_slice(source, source_len, "card NucleusPreview {")) {
        return set_error(result, LATTICRA_L_UI_PARSE_MISSING_CARD);
    }

    if (!contains_slice(source, source_len, "purpose ")) {
        return set_error(result, LATTICRA_L_UI_PARSE_MISSING_PURPOSE);
    }

    if (!contains_slice(source, source_len, "effect ")) {
        return set_error(result, LATTICRA_L_UI_PARSE_MISSING_EFFECT);
    }

    if (has_unsupported_effect(source, source_len) || !contains_slice(source, source_len, "effect none")) {
        return set_error(result, LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT);
    }

    if (!contains_slice(source, source_len, "boundary ")) {
        return set_error(result, LATTICRA_L_UI_PARSE_MISSING_BOUNDARY);
    }

    if (!contains_slice(source, source_len, "boundary preview_only")) {
        return set_error(result, LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY);
    }

    if (has_forbidden_marker(source, source_len)) {
        return set_error(result, LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER);
    }

    rail_error = validate_required_rails(source, source_len);
    if (rail_error != LATTICRA_L_UI_PARSE_OK) {
        return set_error(result, rail_error);
    }

    if (has_unknown_binding_prefix(source, source_len)) {
        return set_error(result, LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX);
    }

    binding_error = validate_required_bindings(source, source_len);
    if (binding_error != LATTICRA_L_UI_PARSE_OK) {
        return set_error(result, binding_error);
    }

    copy_literal(result->card_name, sizeof(result->card_name), "NucleusPreview");
    copy_literal(result->effect, sizeof(result->effect), "none");
    copy_literal(result->boundary, sizeof(result->boundary), "preview_only");
    result->rail_count = 9u;
    result->field_count = 23u;
    result->error = LATTICRA_L_UI_PARSE_OK;

    return LATTICRA_STATUS_OK;
}

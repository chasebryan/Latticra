#include "latticra/l_ui_parser.h"

#include <stdio.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source);
}

const char *latticra_l_ui_diagnostic_severity_label(
    latticra_l_ui_diagnostic_severity_t severity) {
    switch (severity) {
    case LATTICRA_L_UI_DIAGNOSTIC_OK:
        return "ok";
    case LATTICRA_L_UI_DIAGNOSTIC_ERROR:
        return "error";
    case LATTICRA_L_UI_DIAGNOSTIC_INTERNAL:
        return "internal";
    default:
        return "internal";
    }
}

static const char *diagnostic_code_for_error(latticra_l_ui_parse_error_t error) {
    switch (error) {
    case LATTICRA_L_UI_PARSE_OK:
        return "LUI0000";
    case LATTICRA_L_UI_PARSE_NULL_ARGUMENT:
        return "LUI0001";
    case LATTICRA_L_UI_PARSE_EMPTY_SOURCE:
        return "LUI0002";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION:
        return "LUI0003";
    case LATTICRA_L_UI_PARSE_MISSING_CARD:
        return "LUI0004";
    case LATTICRA_L_UI_PARSE_MISSING_PURPOSE:
        return "LUI0005";
    case LATTICRA_L_UI_PARSE_MISSING_EFFECT:
        return "LUI0006";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT:
        return "LUI0007";
    case LATTICRA_L_UI_PARSE_MISSING_BOUNDARY:
        return "LUI0008";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY:
        return "LUI0009";
    case LATTICRA_L_UI_PARSE_MISSING_RAIL:
        return "LUI0010";
    case LATTICRA_L_UI_PARSE_UNKNOWN_RAIL:
        return "LUI0011";
    case LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX:
        return "LUI0012";
    case LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING:
        return "LUI0013";
    case LATTICRA_L_UI_PARSE_UNTERMINATED_STRING:
        return "LUI0014";
    case LATTICRA_L_UI_PARSE_UNBALANCED_BRACE:
        return "LUI0015";
    case LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER:
        return "LUI0016";
    case LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE:
        return "LUI0017";
    case LATTICRA_L_UI_PARSE_INTERNAL_ERROR:
    default:
        return "LUI0018";
    }
}

static const char *diagnostic_message_for_error(latticra_l_ui_parse_error_t error) {
    switch (error) {
    case LATTICRA_L_UI_PARSE_OK:
        return "Parse completed successfully.";
    case LATTICRA_L_UI_PARSE_NULL_ARGUMENT:
        return "Parser received a null argument.";
    case LATTICRA_L_UI_PARSE_EMPTY_SOURCE:
        return "L-UI source is empty.";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION:
        return "L-UI version is not supported.";
    case LATTICRA_L_UI_PARSE_MISSING_CARD:
        return "Required card declaration is missing.";
    case LATTICRA_L_UI_PARSE_MISSING_PURPOSE:
        return "Required purpose clause is missing.";
    case LATTICRA_L_UI_PARSE_MISSING_EFFECT:
        return "Required effect clause is missing.";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT:
        return "Effect declaration is not supported.";
    case LATTICRA_L_UI_PARSE_MISSING_BOUNDARY:
        return "Required boundary clause is missing.";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY:
        return "Boundary declaration is not supported.";
    case LATTICRA_L_UI_PARSE_MISSING_RAIL:
        return "Required rail is missing.";
    case LATTICRA_L_UI_PARSE_UNKNOWN_RAIL:
        return "Rail name is not supported.";
    case LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX:
        return "Binding prefix is not supported.";
    case LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING:
        return "Required binding is missing.";
    case LATTICRA_L_UI_PARSE_UNTERMINATED_STRING:
        return "String literal is not terminated.";
    case LATTICRA_L_UI_PARSE_UNBALANCED_BRACE:
        return "Braces are not balanced.";
    case LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER:
        return "Source contains a forbidden behavior marker.";
    case LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE:
        return "Source exceeds the supported size limit.";
    case LATTICRA_L_UI_PARSE_INTERNAL_ERROR:
    default:
        return "Parser reached an internal error.";
    }
}

static const char *diagnostic_hint_for_error(latticra_l_ui_parse_error_t error) {
    switch (error) {
    case LATTICRA_L_UI_PARSE_OK:
        return "";
    case LATTICRA_L_UI_PARSE_NULL_ARGUMENT:
        return "Provide non-null source and result pointers.";
    case LATTICRA_L_UI_PARSE_EMPTY_SOURCE:
        return "Provide L-UI source beginning with: lui 0.1";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_VERSION:
        return "Use version header: lui 0.1";
    case LATTICRA_L_UI_PARSE_MISSING_CARD:
        return "Add card NucleusPreview { ... }";
    case LATTICRA_L_UI_PARSE_MISSING_PURPOSE:
        return "Add a purpose string.";
    case LATTICRA_L_UI_PARSE_MISSING_EFFECT:
        return "Add effect none.";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT:
        return "Use only effect none.";
    case LATTICRA_L_UI_PARSE_MISSING_BOUNDARY:
        return "Add boundary preview_only.";
    case LATTICRA_L_UI_PARSE_UNSUPPORTED_BOUNDARY:
        return "Use only boundary preview_only.";
    case LATTICRA_L_UI_PARSE_MISSING_RAIL:
        return "Add the required NucleusPreview rails.";
    case LATTICRA_L_UI_PARSE_UNKNOWN_RAIL:
        return "Use only documented rail names.";
    case LATTICRA_L_UI_PARSE_UNKNOWN_BINDING_PREFIX:
        return "Use only state. or preview. binding prefixes.";
    case LATTICRA_L_UI_PARSE_MISSING_REQUIRED_BINDING:
        return "Add all required NucleusPreview bindings.";
    case LATTICRA_L_UI_PARSE_UNTERMINATED_STRING:
        return "Close the string literal.";
    case LATTICRA_L_UI_PARSE_UNBALANCED_BRACE:
        return "Balance opening and closing braces.";
    case LATTICRA_L_UI_PARSE_FORBIDDEN_BEHAVIOR_MARKER:
        return "Remove behavior markers outside the static report grammar.";
    case LATTICRA_L_UI_PARSE_SOURCE_TOO_LARGE:
        return "Keep L-UI source at or below LATTICRA_L_UI_SOURCE_MAX.";
    case LATTICRA_L_UI_PARSE_INTERNAL_ERROR:
    default:
        return "Report the internal parser error.";
    }
}

static latticra_l_ui_diagnostic_severity_t diagnostic_severity_for_error(
    latticra_l_ui_parse_error_t error) {
    if (error == LATTICRA_L_UI_PARSE_OK) {
        return LATTICRA_L_UI_DIAGNOSTIC_OK;
    }
    if (error == LATTICRA_L_UI_PARSE_INTERNAL_ERROR) {
        return LATTICRA_L_UI_DIAGNOSTIC_INTERNAL;
    }
    return LATTICRA_L_UI_DIAGNOSTIC_ERROR;
}

latticra_status_t latticra_l_ui_diagnostic_from_parse_result(
    const latticra_l_ui_parse_result_t *parse_result,
    latticra_l_ui_diagnostic_t *diagnostic) {
    if (parse_result == 0 || diagnostic == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    diagnostic->severity = diagnostic_severity_for_error(parse_result->error);
    copy_literal(diagnostic->code, sizeof(diagnostic->code), diagnostic_code_for_error(parse_result->error));
    copy_literal(
        diagnostic->message,
        sizeof(diagnostic->message),
        diagnostic_message_for_error(parse_result->error));
    copy_literal(diagnostic->hint, sizeof(diagnostic->hint), diagnostic_hint_for_error(parse_result->error));
    diagnostic->line = parse_result->line;
    diagnostic->column = parse_result->column;
    diagnostic->no_effect = parse_result->no_effect;
    diagnostic->execution_allowed = parse_result->execution_allowed;
    diagnostic->mutation_allowed = parse_result->mutation_allowed;
    diagnostic->server_allowed = parse_result->server_allowed;
    diagnostic->recovery_allowed = parse_result->recovery_allowed;
    diagnostic->hardware_allowed = parse_result->hardware_allowed;

    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_l_ui_diagnostic_report(
    const latticra_l_ui_diagnostic_t *diagnostic,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (diagnostic == 0 || buffer == 0) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "L-UI PARSE DIAGNOSTIC\n"
        "severity=%s\n"
        "code=%s\n"
        "message=%s\n"
        "line=%zu\n"
        "column=%zu\n"
        "hint=%s\n"
        "no_effect=%d\n"
        "execution_allowed=%d\n"
        "mutation_allowed=%d\n"
        "server_allowed=%d\n"
        "recovery_allowed=%d\n"
        "hardware_allowed=%d\n",
        latticra_l_ui_diagnostic_severity_label(diagnostic->severity),
        diagnostic->code,
        diagnostic->message,
        diagnostic->line,
        diagnostic->column,
        diagnostic->hint,
        diagnostic->no_effect,
        diagnostic->execution_allowed,
        diagnostic->mutation_allowed,
        diagnostic->server_allowed,
        diagnostic->recovery_allowed,
        diagnostic->hardware_allowed);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}

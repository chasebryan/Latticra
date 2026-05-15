#include "latticra/l_ui_parser.h"

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

#define EXPECT_MEM_EQ(actual, expected, len, message) \
    do { \
        if (memcmp((actual), (expected), (len)) != 0) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static const char SOURCE_PREFIX[] =
    "lui 0.1\n"
    "card NucleusPreview {\n"
    "  purpose \"";

static const char SOURCE_MIDDLE[] =
    "\"\n"
    "  effect none\n"
    "  boundary preview_only\n"
    "  rail top { text \"";

static const char SOURCE_AFTER_TOP_TEXT[] =
    "\" }\n"
    "  rail state {\n"
    "    field origin bind state.origin\n"
    "    field route bind state.route\n"
    "    field axis bind state.axis\n"
    "    field path bind state.path\n"
    "  }\n"
    "  rail trace {\n"
    "    field breadcrumb bind state.breadcrumb\n"
    "    field trace bind state.trace\n"
    "  }\n"
    "  rail safety {\n"
    "    field health bind state.health\n"
    "    field risk bind state.risk\n"
    "    field lock bind state.lock\n"
    "    field dark_phase bind state.dark_phase\n"
    "  }\n"
    "  rail gates {\n"
    "    field safe_portal bind state.safe_portal\n"
    "    field rollback bind state.rollback\n"
    "  }\n"
    "  rail effects {\n"
    "    field host bind state.host_effect\n"
    "    field external bind state.external_effect\n"
    "    field requested bind preview.requested_effect\n"
    "  }\n"
    "  rail policy {\n"
    "    field request bind preview.request\n"
    "    field policy bind preview.policy\n"
    "    field reason bind preview.reason\n"
    "  }\n"
    "  rail execution {\n"
    "    field executed bind preview.executed\n"
    "    field mutation bind preview.mutation_allowed\n"
    "    field server bind preview.server_interaction_allowed\n"
    "    field recovery bind preview.recovery_allowed\n"
    "    field hardware bind preview.hardware_allowed\n"
    "  }\n"
    "  rail bottom { text \"";

static const char SOURCE_SUFFIX[] =
    "\" }\n"
    "}\n";

static int append_bytes(char *buffer, size_t buffer_len, size_t *used, const char *bytes, size_t bytes_len) {
    if (buffer == 0 || used == 0 || bytes == 0 || *used > buffer_len || bytes_len > buffer_len - *used) {
        return 0;
    }
    memcpy(buffer + *used, bytes, bytes_len);
    *used += bytes_len;
    return 1;
}

static int make_source_binary(
    char *buffer,
    size_t buffer_len,
    const char *purpose,
    size_t purpose_len,
    const char *top_text,
    size_t top_text_len,
    const char *bottom_text,
    size_t bottom_text_len,
    size_t *source_len) {
    size_t used = 0u;
    if (!append_bytes(buffer, buffer_len, &used, SOURCE_PREFIX, sizeof(SOURCE_PREFIX) - 1u)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, purpose, purpose_len)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, SOURCE_MIDDLE, sizeof(SOURCE_MIDDLE) - 1u)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, top_text, top_text_len)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, SOURCE_AFTER_TOP_TEXT, sizeof(SOURCE_AFTER_TOP_TEXT) - 1u)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, bottom_text, bottom_text_len)) return 0;
    if (!append_bytes(buffer, buffer_len, &used, SOURCE_SUFFIX, sizeof(SOURCE_SUFFIX) - 1u)) return 0;
    if (used >= buffer_len) return 0;
    buffer[used] = '\0';
    if (source_len != 0) {
        *source_len = used;
    }
    return 1;
}

static int make_source(
    char *buffer,
    size_t buffer_len,
    const char *purpose,
    const char *top_text,
    const char *bottom_text,
    size_t *source_len) {
    return make_source_binary(
        buffer,
        buffer_len,
        purpose,
        strlen(purpose),
        top_text,
        strlen(top_text),
        bottom_text,
        strlen(bottom_text),
        source_len);
}

static int parse_values(
    const char *purpose,
    const char *top_text,
    const char *bottom_text,
    latticra_l_ui_ast_result_t *ast,
    char *source,
    size_t source_len_limit,
    size_t *source_len) {
    size_t len;
    if (!make_source(source, source_len_limit, purpose, top_text, bottom_text, &len)) {
        return 0;
    }
    if (source_len != 0) {
        *source_len = len;
    }
    return latticra_l_ui_parse_ast(source, len, ast) == LATTICRA_STATUS_OK &&
           ast->parse_result.error == LATTICRA_L_UI_PARSE_OK;
}

static int expect_internal_for_purpose(const char *purpose, const char *message) {
    char source[8192];
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source(source, sizeof(source), purpose, "top", "bottom", &source_len), "invalid source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, message);
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_INTERNAL_ERROR, "invalid escape classified internal");
    EXPECT_TRUE(ast.rail_count == 0u && ast.field_count == 0u && ast.text_count == 0u, "invalid escape no partial AST");
    EXPECT_TRUE(ast.card.rail_count == 0u && ast.card.field_count == 0u && ast.card.text_count == 0u, "invalid escape no partial card counts");
    return 0;
}

static int string_escape_decodes_backslash(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("path\\\\root", "top", "bottom", &ast, source, sizeof(source), &source_len), "backslash source parses");
    EXPECT_STR_EQ(ast.card.purpose, "path\\root", "backslash decoded");
    (void)source_len;
    return 0;
}

static int string_escape_decodes_quote(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("purpose", "say \\\"yes\\\"", "bottom", &ast, source, sizeof(source), &source_len), "quote source parses");
    EXPECT_STR_EQ(ast.texts[0].value, "say \"yes\"", "quote decoded");
    (void)source_len;
    return 0;
}

static int string_escape_decodes_newline(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("line\\nnext", "top", "bottom", &ast, source, sizeof(source), &source_len), "newline source parses");
    EXPECT_STR_EQ(ast.card.purpose, "line\nnext", "newline decoded");
    (void)source_len;
    return 0;
}

static int string_escape_decodes_carriage_return(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("purpose", "row\\rnext", "bottom", &ast, source, sizeof(source), &source_len), "carriage return source parses");
    EXPECT_STR_EQ(ast.texts[0].value, "row\rnext", "carriage return decoded");
    (void)source_len;
    return 0;
}

static int string_escape_decodes_tab(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("purpose", "top", "col\\tvalue", &ast, source, sizeof(source), &source_len), "tab source parses");
    EXPECT_STR_EQ(ast.texts[1].value, "col\tvalue", "tab decoded");
    (void)source_len;
    return 0;
}

static int string_escape_decodes_uppercase_hex(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("hex\\x41value", "top", "bottom", &ast, source, sizeof(source), &source_len), "uppercase hex source parses");
    EXPECT_STR_EQ(ast.card.purpose, "hexAvalue", "uppercase hex decoded");
    (void)source_len;
    return 0;
}

static int string_escape_decodes_high_byte_hex(void) {
    char source[4096];
    static const char expected[] = { 'h', 'i', (char)0x80, (char)0xFF, '\0' };
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("hi\\x80\\xFF", "top", "bottom", &ast, source, sizeof(source), &source_len), "high byte source parses");
    EXPECT_TRUE(strlen(ast.card.purpose) == 4u, "high byte decoded length");
    EXPECT_MEM_EQ(ast.card.purpose, expected, sizeof(expected), "high byte decoded bytes");
    (void)source_len;
    return 0;
}

static int string_escape_rejects_lowercase_hex(void) {
    return expect_internal_for_purpose("bad\\x0a", "lowercase hex AST status");
}

static int string_escape_rejects_short_hex(void) {
    return expect_internal_for_purpose("bad\\x0", "short hex AST status");
}

static int string_escape_rejects_invalid_hex(void) {
    return expect_internal_for_purpose("bad\\xGG", "invalid hex AST status");
}

static int string_escape_rejects_unknown_escape(void) {
    return expect_internal_for_purpose("bad\\a", "unknown escape AST status");
}

static int string_escape_rejects_unterminated_escape(void) {
    return expect_internal_for_purpose("bad\\x", "unterminated escape AST status");
}

static int string_escape_rejects_decoded_nul_until_length_storage_exists(void) {
    return expect_internal_for_purpose("bad\\x00", "decoded NUL AST status");
}

static int string_escape_rejects_literal_nul_until_length_storage_exists(void) {
    char source[8192];
    static const char purpose[] = { 'b', 'a', 'd', '\0', 'n', 'u', 'l' };
    size_t source_len;
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(make_source_binary(
                    source,
                    sizeof(source),
                    purpose,
                    sizeof(purpose),
                    "top",
                    strlen("top"),
                    "bottom",
                    strlen("bottom"),
                    &source_len),
                "literal NUL source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast) == LATTICRA_STATUS_OK, "literal NUL AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_INTERNAL_ERROR, "literal NUL classified internal");
    EXPECT_TRUE(ast.rail_count == 0u && ast.field_count == 0u && ast.text_count == 0u, "literal NUL no partial AST");
    return 0;
}

static int fill_repeated(char *buffer, size_t len, char value) {
    size_t index;
    if (len == 0u) {
        return 0;
    }
    for (index = 0u; index + 1u < len; index++) {
        buffer[index] = value;
    }
    buffer[len - 1u] = '\0';
    return 1;
}

static int string_escape_rejects_oversized_decoded_output(void) {
    char long_value[LATTICRA_L_UI_AST_PURPOSE_MAX + 1u];
    EXPECT_TRUE(fill_repeated(long_value, sizeof(long_value), 'x'), "long decoded value builds");
    return expect_internal_for_purpose(long_value, "oversized decoded AST status");
}

static int string_escape_preserves_source_spans(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    static const char top_text[] = "a\\nBC";
    EXPECT_TRUE(parse_values("purpose", top_text, "bottom", &ast, source, sizeof(source), &source_len), "span source parses");
    EXPECT_TRUE(ast.texts[0].span.end_offset >= ast.texts[0].span.start_offset, "span range ordered");
    EXPECT_TRUE(ast.texts[0].span.end_offset - ast.texts[0].span.start_offset == strlen(top_text), "span uses source byte length");
    EXPECT_TRUE(strlen(ast.texts[0].value) == strlen("a\nBC"), "decoded value length differs from source escape length");
    (void)source_len;
    return 0;
}

static int string_escape_updates_detailed_report_escaped_fields(void) {
    char source[4096];
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("P\\nQ", "T\\tQ", "B\\x7F", &ast, source, sizeof(source), &source_len), "report escape source parses");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "detailed report status");
    EXPECT_TRUE(strstr(report, "purpose_escaped=P\\nQ\n") != 0, "purpose escaped report decoded newline safely");
    EXPECT_TRUE(strstr(report, "value_escaped=T\\tQ\n") != 0, "text escaped report decoded tab safely");
    EXPECT_TRUE(strstr(report, "value_escaped=B\\x7F\n") != 0, "text escaped report decoded DEL safely");
    (void)source_len;
    return 0;
}

static int string_escape_preserves_no_effect_flags(void) {
    char source[4096];
    latticra_l_ui_ast_result_t ast;
    size_t source_len;
    EXPECT_TRUE(parse_values("flag\\nsource", "top\\ttext", "bottom", &ast, source, sizeof(source), &source_len), "flag source parses");
    EXPECT_TRUE(ast.no_effect == 1, "no_effect preserved");
    EXPECT_TRUE(ast.execution_allowed == 0, "execution flag preserved");
    EXPECT_TRUE(ast.mutation_allowed == 0, "mutation flag preserved");
    EXPECT_TRUE(ast.server_allowed == 0, "server flag preserved");
    EXPECT_TRUE(ast.recovery_allowed == 0, "recovery flag preserved");
    EXPECT_TRUE(ast.hardware_allowed == 0, "hardware flag preserved");
    (void)source_len;
    return 0;
}

static int string_escape_does_not_change_parse_source_summary(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_parse_result_t result;
    EXPECT_TRUE(make_source(source, sizeof(source), "parse\\nsource", "top\\ttext", "bottom\\x41", &source_len), "parse source builds");
    EXPECT_TRUE(latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK, "parse source status");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_OK, "parse source remains structural OK");
    EXPECT_TRUE(result.rail_count == 9u, "parse source rail count unchanged");
    EXPECT_TRUE(result.field_count == 23u, "parse source field count unchanged");
    EXPECT_STR_EQ(result.effect, "none", "parse source effect unchanged");
    EXPECT_STR_EQ(result.boundary, "preview_only", "parse source boundary unchanged");
    return 0;
}

static int string_escape_does_not_change_failed_parse_report(void) {
    const char source[] = "lui 0.1\ncard NucleusPreview {\n  purpose \"bad\\n\"\n  effect network\n}\n";
    char report[LATTICRA_L_UI_AST_DETAILED_REPORT_MAX];
    latticra_l_ui_ast_result_t ast;
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, strlen(source), &ast) == LATTICRA_STATUS_OK, "failed parse AST status");
    EXPECT_TRUE(ast.parse_result.error == LATTICRA_L_UI_PARSE_UNSUPPORTED_EFFECT, "structural parse error preserved");
    EXPECT_TRUE(latticra_l_ui_ast_detailed_report(&ast, report, sizeof(report)) == LATTICRA_STATUS_OK, "failed parse report status");
    EXPECT_TRUE(strstr(report, "parse_error=unsupported_effect\n") != 0, "failed parse report unchanged");
    EXPECT_TRUE(strstr(report, "purpose=") == 0, "failed parse has no decoded purpose");
    EXPECT_TRUE(strstr(report, "value=") == 0, "failed parse has no decoded value");
    return 0;
}

static int string_escape_is_deterministic(void) {
    char source[4096];
    size_t source_len;
    latticra_l_ui_ast_result_t ast_one;
    latticra_l_ui_ast_result_t ast_two;
    EXPECT_TRUE(make_source(source, sizeof(source), "det\\nP", "det\\tT", "det\\x42", &source_len), "deterministic source builds");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast_one) == LATTICRA_STATUS_OK, "first deterministic parse");
    EXPECT_TRUE(latticra_l_ui_parse_ast(source, source_len, &ast_two) == LATTICRA_STATUS_OK, "second deterministic parse");
    EXPECT_TRUE(ast_one.parse_result.error == LATTICRA_L_UI_PARSE_OK, "first deterministic OK");
    EXPECT_TRUE(ast_two.parse_result.error == LATTICRA_L_UI_PARSE_OK, "second deterministic OK");
    EXPECT_STR_EQ(ast_one.card.purpose, ast_two.card.purpose, "deterministic purpose");
    EXPECT_STR_EQ(ast_one.texts[0].value, ast_two.texts[0].value, "deterministic top text");
    EXPECT_STR_EQ(ast_one.texts[1].value, ast_two.texts[1].value, "deterministic bottom text");
    return 0;
}

int main(void) {
    if (string_escape_decodes_backslash() != 0) return 1;
    if (string_escape_decodes_quote() != 0) return 1;
    if (string_escape_decodes_newline() != 0) return 1;
    if (string_escape_decodes_carriage_return() != 0) return 1;
    if (string_escape_decodes_tab() != 0) return 1;
    if (string_escape_decodes_uppercase_hex() != 0) return 1;
    if (string_escape_decodes_high_byte_hex() != 0) return 1;
    if (string_escape_rejects_lowercase_hex() != 0) return 1;
    if (string_escape_rejects_short_hex() != 0) return 1;
    if (string_escape_rejects_invalid_hex() != 0) return 1;
    if (string_escape_rejects_unknown_escape() != 0) return 1;
    if (string_escape_rejects_unterminated_escape() != 0) return 1;
    if (string_escape_rejects_decoded_nul_until_length_storage_exists() != 0) return 1;
    if (string_escape_rejects_literal_nul_until_length_storage_exists() != 0) return 1;
    if (string_escape_rejects_oversized_decoded_output() != 0) return 1;
    if (string_escape_preserves_source_spans() != 0) return 1;
    if (string_escape_updates_detailed_report_escaped_fields() != 0) return 1;
    if (string_escape_preserves_no_effect_flags() != 0) return 1;
    if (string_escape_does_not_change_parse_source_summary() != 0) return 1;
    if (string_escape_does_not_change_failed_parse_report() != 0) return 1;
    if (string_escape_is_deterministic() != 0) return 1;

    puts("l_ui_string_literal_escape_invariants: ok");
    return 0;
}

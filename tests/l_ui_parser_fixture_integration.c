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

static int read_fixture(const char *path, char *buffer, size_t buffer_len, size_t *out_len) {
    FILE *file;
    size_t read_len;

    if (path == 0 || buffer == 0 || out_len == 0 || buffer_len == 0u) {
        return 1;
    }

    file = fopen(path, "rb");
    if (file == 0) {
        return 1;
    }

    read_len = fread(buffer, 1u, buffer_len - 1u, file);
    if (ferror(file)) {
        (void)fclose(file);
        return 1;
    }

    if (fclose(file) != 0) {
        return 1;
    }

    buffer[read_len] = '\0';
    *out_len = read_len;
    return 0;
}

static int repository_fixture_parses_successfully(void) {
    char source[LATTICRA_L_UI_SOURCE_MAX];
    size_t source_len = 0u;
    latticra_l_ui_parse_result_t result;

    EXPECT_TRUE(
        read_fixture("examples/l-ui/nucleus-preview-card.lui", source, sizeof(source), &source_len) == 0,
        "repository L-UI fixture should be readable by test harness");
    EXPECT_TRUE(source_len > 0u, "repository L-UI fixture should not be empty");
    EXPECT_TRUE(
        latticra_l_ui_parse_source(source, source_len, &result) == LATTICRA_STATUS_OK,
        "repository L-UI fixture should return parser status ok");
    EXPECT_TRUE(result.error == LATTICRA_L_UI_PARSE_OK, "repository fixture parse error should be ok");
    EXPECT_STR_EQ(result.card_name, "NucleusPreview", "repository fixture card name");
    EXPECT_TRUE(result.rail_count == 9u, "repository fixture rail count");
    EXPECT_TRUE(result.field_count == 23u, "repository fixture field count");
    EXPECT_STR_EQ(result.effect, "none", "repository fixture effect");
    EXPECT_STR_EQ(result.boundary, "preview_only", "repository fixture boundary");
    EXPECT_TRUE(result.no_effect == 1, "repository fixture no_effect flag");
    EXPECT_TRUE(result.execution_allowed == 0, "repository fixture execution flag");
    EXPECT_TRUE(result.mutation_allowed == 0, "repository fixture mutation flag");
    EXPECT_TRUE(result.server_allowed == 0, "repository fixture server flag");
    EXPECT_TRUE(result.recovery_allowed == 0, "repository fixture recovery flag");
    EXPECT_TRUE(result.hardware_allowed == 0, "repository fixture hardware flag");

    return 0;
}

int main(void) {
    if (repository_fixture_parses_successfully() != 0) {
        return 1;
    }

    puts("l_ui_parser_fixture_integration: ok");
    return 0;
}

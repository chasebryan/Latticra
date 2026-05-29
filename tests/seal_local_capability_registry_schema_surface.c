#include "latticra/seal_local_capability_registry_schema.h"

#include <stdio.h>

int main(void) {
    latticra_seal_local_capability_registry_schema_t schema;
    char rendered[LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_REPORT_MAX];

    if (latticra_seal_local_capability_registry_schema_init(&schema) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to initialize Seal local capability registry schema\n");
        return 1;
    }
    if (latticra_seal_local_capability_registry_schema_add_default_entry(&schema) !=
        LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to add Seal local capability registry schema entry\n");
        return 1;
    }
    if (latticra_seal_local_capability_registry_schema_validate(&schema) !=
        LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to validate Seal local capability registry schema\n");
        return 1;
    }
    if (schema.last_error != LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK) {
        fprintf(stderr,
                "invalid Seal local capability registry schema: %s\n",
                latticra_seal_local_capability_registry_schema_error_label(schema.last_error));
        return 1;
    }
    if (latticra_seal_local_capability_registry_schema_is_report_only(&schema) != 1) {
        fprintf(stderr, "Seal local capability registry schema is not report-only\n");
        return 1;
    }
    if (latticra_seal_local_capability_registry_schema_render(&schema,
                                                              rendered,
                                                              sizeof(rendered)) !=
        LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal local capability registry schema\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}

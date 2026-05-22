#include "latticra/seal_capability_metadata.h"

#include <stdio.h>

int main(void) {
    latticra_seal_capability_metadata_result_t result;
    char rendered[LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_MAX];

    if (latticra_seal_capability_metadata_evaluate("seal.capability.report", &result) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to build Seal capability metadata\n");
        return 1;
    }

    if (result.error != LATTICRA_SEAL_CAPABILITY_METADATA_OK) {
        fprintf(stderr,
                "invalid Seal capability metadata: %s\n",
                latticra_seal_capability_metadata_error_label(result.error));
        return 1;
    }

    if (latticra_seal_capability_metadata_report(&result, rendered, sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal capability metadata report\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}

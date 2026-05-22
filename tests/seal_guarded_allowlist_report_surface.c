#include "latticra/seal_guarded_allowlist.h"

#include <stdio.h>

int main(void) {
    latticra_seal_guarded_allowlist_result_t result;
    char rendered[LATTICRA_SEAL_GUARDED_ALLOWLIST_REPORT_MAX];

    if (latticra_seal_guarded_allowlist_evaluate("latticra.seal.report", &result) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to build Seal guarded allowlist metadata\n");
        return 1;
    }

    if (result.error != LATTICRA_SEAL_GUARDED_ALLOWLIST_OK) {
        fprintf(stderr,
                "invalid Seal guarded allowlist metadata: %s\n",
                latticra_seal_guarded_allowlist_error_label(result.error));
        return 1;
    }

    if (latticra_seal_guarded_allowlist_report(&result, rendered, sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal guarded allowlist report\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}

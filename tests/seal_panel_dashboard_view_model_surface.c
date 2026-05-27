#include "latticra/seal_panel_dashboard_view_model.h"

#include <stdio.h>

static const char *source_report_fixture(void) {
    return "fixture_profile=latticra-seal-panel-dashboard-view-model-source/0.1\n"
           "mode=report-only\n"
           "report_only=1\n"
           "runtime_authority_granted=0\n"
           "effect_performed=0\n"
           "host_read_performed=0\n"
           "host_write_performed=0\n"
           "network_performed=0\n";
}

int main(void) {
    static const char *ids[] = {"seal.product.spine",
                                "seal.operator.receipt",
                                "seal.local.capability.registry.schema",
                                "seal.policy.decision",
                                "seal.signed.request",
                                "seal.request.freshness",
                                "seal.runtime.dry.run",
                                "seal.verification.receipt",
                                "seal.capability.gate",
                                "seal.effect.decision",
                                "seal.runtime.handoff",
                                "seal.status.rollup"};
    latticra_seal_panel_dashboard_view_model_t model;
    char rendered[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_REPORT_MAX];
    unsigned i;

    if (latticra_seal_panel_dashboard_view_model_init(&model) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to initialize Seal Panel dashboard view model\n");
        return 1;
    }
    for (i = 0u; i < sizeof(ids) / sizeof(ids[0]); ++i) {
        if (latticra_seal_panel_dashboard_view_model_add_source_report(
                &model,
                ids[i],
                ids[i],
                source_report_fixture()) != LATTICRA_STATUS_OK) {
            fprintf(stderr, "failed to add Seal Panel dashboard view-model source\n");
            return 1;
        }
    }
    if (latticra_seal_panel_dashboard_view_model_add_required_rows(&model) !=
        LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to add Seal Panel dashboard view-model rows\n");
        return 1;
    }
    if (latticra_seal_panel_dashboard_view_model_validate(&model) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to validate Seal Panel dashboard view model\n");
        return 1;
    }
    if (model.last_error != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK) {
        fprintf(stderr,
                "invalid Seal Panel dashboard view model: %s\n",
                latticra_seal_panel_dashboard_view_model_error_label(model.last_error));
        return 1;
    }
    if (latticra_seal_panel_dashboard_view_model_is_report_only(&model) != 1) {
        fprintf(stderr, "Seal Panel dashboard view model is not report-only\n");
        return 1;
    }
    if (latticra_seal_panel_dashboard_view_model_render(&model,
                                                        rendered,
                                                        sizeof(rendered)) !=
        LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal Panel dashboard view model\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}

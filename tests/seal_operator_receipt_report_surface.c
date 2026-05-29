#include "latticra/seal_operator_receipt_report.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static void fill_policy_decision(latticra_seal_policy_decision_t *policy_decision) {
    memset(policy_decision, 0, sizeof(*policy_decision));
    copy_literal(policy_decision->decision_state,
                 sizeof(policy_decision->decision_state),
                 "report-only");
    policy_decision->decision_denied = 1u;
    policy_decision->operator_review_required = 1u;
    policy_decision->unknown_tool_denied = 1u;
    policy_decision->unsigned_request_denied = 1u;
    policy_decision->invalid_schema_denied = 1u;
    policy_decision->stale_request_denied = 1u;
    policy_decision->replayed_request_denied = 1u;
    policy_decision->invalid_signature_denied = 1u;
    copy_literal(policy_decision->mode, sizeof(policy_decision->mode), "report-only");
    copy_literal(policy_decision->decision, sizeof(policy_decision->decision), "report-only");
    policy_decision->error = LATTICRA_SEAL_POLICY_DECISION_OK;
}

static void fill_request_freshness(latticra_seal_request_freshness_t *freshness) {
    memset(freshness, 0, sizeof(*freshness));
    copy_literal(freshness->mode, sizeof(freshness->mode), "report-only");
    copy_literal(freshness->decision, sizeof(freshness->decision), "report-only");
    freshness->error = LATTICRA_SEAL_REQUEST_FRESHNESS_OK;
}

static void fill_signed_request(latticra_seal_signed_request_t *signed_request) {
    memset(signed_request, 0, sizeof(*signed_request));
    copy_literal(signed_request->mode, sizeof(signed_request->mode), "report-only");
    copy_literal(signed_request->decision, sizeof(signed_request->decision), "report-only");
    signed_request->error = LATTICRA_SEAL_SIGNED_REQUEST_OK;
}

static void fill_runtime_dry_run(latticra_seal_runtime_dry_run_t *dry_run) {
    memset(dry_run, 0, sizeof(*dry_run));
    copy_literal(dry_run->request_class, sizeof(dry_run->request_class), "seal.capability.report");
    copy_literal(dry_run->policy_decision_state,
                 sizeof(dry_run->policy_decision_state),
                 "report-only");
    copy_literal(dry_run->runtime_gate_state,
                 sizeof(dry_run->runtime_gate_state),
                 "report-only");
    dry_run->dry_run_supported = 1u;
    dry_run->dry_run_performed = 1u;
    dry_run->input_policy_decision_present = 1u;
    dry_run->input_runtime_gate_present = 1u;
    dry_run->policy_decision_report_only = 1u;
    dry_run->runtime_gate_report_only = 1u;
    dry_run->default_action_deny = 1u;
    dry_run->would_deny = 1u;
    dry_run->would_require_operator_review = 1u;
    dry_run->unknown_tool_denied = 1u;
    dry_run->unsigned_request_denied = 1u;
    dry_run->invalid_schema_denied = 1u;
    dry_run->stale_request_denied = 1u;
    dry_run->replayed_request_denied = 1u;
    dry_run->invalid_signature_denied = 1u;
    dry_run->report_only = 1u;
    copy_literal(dry_run->mode, sizeof(dry_run->mode), "report-only");
    dry_run->error = LATTICRA_SEAL_RUNTIME_DRY_RUN_OK;
}

int main(void) {
    latticra_seal_capability_metadata_result_t capability_metadata;
    latticra_seal_policy_decision_t policy_decision;
    latticra_seal_request_freshness_t request_freshness;
    latticra_seal_signed_request_t signed_request;
    latticra_seal_runtime_dry_run_t runtime_dry_run;
    latticra_seal_operator_receipt_report_sources_t sources;
    latticra_seal_operator_receipt_report_t receipt;
    char rendered[LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_MAX];

    if (latticra_seal_capability_metadata_evaluate("seal.capability.report",
                                                   &capability_metadata) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to build Seal capability metadata\n");
        return 1;
    }

    fill_policy_decision(&policy_decision);
    fill_request_freshness(&request_freshness);
    fill_signed_request(&signed_request);
    fill_runtime_dry_run(&runtime_dry_run);

    sources.capability_metadata = &capability_metadata;
    sources.policy_decision = &policy_decision;
    sources.request_freshness = &request_freshness;
    sources.signed_request = &signed_request;
    sources.runtime_dry_run = &runtime_dry_run;

    if (latticra_seal_operator_receipt_report_from_sources(&sources, &receipt) !=
        LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to build Seal operator receipt report\n");
        return 1;
    }

    if (receipt.error != LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_OK) {
        fprintf(stderr,
                "invalid Seal operator receipt report: %s\n",
                latticra_seal_operator_receipt_report_error_label(receipt.error));
        return 1;
    }

    if (latticra_seal_operator_receipt_report_is_report_only(&receipt) != 1) {
        fprintf(stderr, "Seal operator receipt report is not report-only\n");
        return 1;
    }

    if (latticra_seal_operator_receipt_report_render(&receipt,
                                                     rendered,
                                                     sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal operator receipt report\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}

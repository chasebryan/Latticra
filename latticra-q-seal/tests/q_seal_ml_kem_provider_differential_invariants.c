#include "latticra/q_seal_ml_kem_provider_differential.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int provider_differential_is_comparison_only(void) {
    latticra_q_seal_ml_kem_provider_differential_t differential;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_PROVIDER_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_prepare(&differential) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        strcmp(
            differential.differential_profile,
            "latticra-q-seal-ml-kem-provider-differential/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(differential.formal_title, "Latticra Q-Seal ML-KEM Provider Differential") == 0,
        "title");
    EXPECT_TRUE(strcmp(differential.candidate_provider, "liboqs-comparison-only") == 0, "provider");
    EXPECT_TRUE(
        strcmp(differential.comparison_scope, "ML-KEM-FIPS203-keygen-encap-decap") == 0,
        "scope");
    EXPECT_TRUE(strcmp(differential.differential_state, "comparison-contract-only") == 0, "state");
    EXPECT_TRUE(differential.provider_differential_contract_present == 1u, "present");
    EXPECT_TRUE(differential.provider_candidate_recorded == 1u, "candidate");
    EXPECT_TRUE(differential.provider_comparison_only == 1u, "comparison only");
    EXPECT_TRUE(differential.provider_license_review_required == 1u, "license required");
    EXPECT_TRUE(differential.provider_license_review_recorded == 0u, "license recorded");
    EXPECT_TRUE(differential.provider_pinned_version_required == 1u, "version required");
    EXPECT_TRUE(differential.provider_pinned_version_recorded == 0u, "version recorded");
    EXPECT_TRUE(differential.provider_source_digest_required == 1u, "digest required");
    EXPECT_TRUE(differential.provider_source_digest_recorded == 0u, "digest recorded");
    EXPECT_TRUE(differential.provider_build_reproducibility_required == 1u, "build required");
    EXPECT_TRUE(differential.provider_build_reproducibility_recorded == 0u, "build recorded");
    EXPECT_TRUE(differential.provider_linking_enabled == 0u, "linking");
    EXPECT_TRUE(differential.provider_runtime_used == 0u, "runtime");
    EXPECT_TRUE(differential.parameter_sets_recorded == 1u, "parameters");
    EXPECT_TRUE(differential.ml_kem_512_comparison_required == 1u, "512");
    EXPECT_TRUE(differential.ml_kem_768_comparison_required == 1u, "768");
    EXPECT_TRUE(differential.ml_kem_1024_comparison_required == 1u, "1024");
    EXPECT_TRUE(differential.positive_vector_comparison_required == 1u, "positive required");
    EXPECT_TRUE(differential.positive_vector_comparison_recorded == 0u, "positive recorded");
    EXPECT_TRUE(differential.negative_vector_comparison_required == 1u, "negative required");
    EXPECT_TRUE(differential.negative_vector_comparison_recorded == 0u, "negative recorded");
    EXPECT_TRUE(differential.mismatch_triage_required == 1u, "triage required");
    EXPECT_TRUE(differential.mismatch_triage_recorded == 0u, "triage recorded");
    EXPECT_TRUE(differential.differential_keygen_enabled == 0u, "keygen");
    EXPECT_TRUE(differential.differential_encap_decap_enabled == 0u, "encap decap");
    EXPECT_TRUE(differential.operation_execution_allowed == 0u, "execution");
    EXPECT_TRUE(differential.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(differential.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(differential.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(differential.required_comparison_items_total == 10u, "total");
    EXPECT_TRUE(differential.required_comparison_items_satisfied == 3u, "satisfied");
    EXPECT_TRUE(
        differential.error == LATTICRA_Q_SEAL_ML_KEM_PROVIDER_DIFFERENTIAL_BLOCKED,
        "blocked");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_is_comparison_only(&differential) == 1,
        "comparison only helper");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_allows_provider_execution(&differential) == 0,
        "allows provider execution");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_report(
            &differential,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "LATTICRA Q-SEAL ML-KEM PROVIDER DIFFERENTIAL") != 0,
        "header");
    EXPECT_TRUE(strstr(rendered, "candidate_provider=liboqs-comparison-only") != 0, "provider");
    EXPECT_TRUE(strstr(rendered, "provider_linking_enabled=0") != 0, "linking");
    EXPECT_TRUE(strstr(rendered, "operation_execution_allowed=0") != 0, "execution");
    EXPECT_TRUE(
        strstr(rendered, "status=ml-kem-provider-differential-blocked") != 0,
        "status");
    return 0;
}

static int invalid_and_buffer_paths_fail_closed(void) {
    latticra_q_seal_ml_kem_provider_differential_t differential;
    char tiny[1];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_is_comparison_only(0) == 0,
        "null comparison");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_allows_provider_execution(0) == 0,
        "null execute");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_prepare(&differential) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_report(
            &differential,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    EXPECT_TRUE(tiny[0] == '\0', "small report clear");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_report(0, tiny, sizeof(tiny)) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report differential");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_provider_differential_report(
            &differential,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    return 0;
}

int main(void) {
    if (provider_differential_is_comparison_only() != 0) {
        return 1;
    }
    if (invalid_and_buffer_paths_fail_closed() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem provider differential invariants: ok\n");
    return 0;
}

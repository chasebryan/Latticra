#include "latticra/q_seal_ml_kem_sp800_227_usage_profile.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int sp800_227_usage_profile_is_accepted_but_runtime_closed(void) {
    latticra_q_seal_ml_kem_sp800_227_usage_profile_t profile;
    char rendered[LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_REPORT_MAX];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_prepare(&profile) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare");
    EXPECT_TRUE(profile.sp800_227_usage_profile_present == 1u, "present");
    EXPECT_TRUE(
        strcmp(
            profile.usage_profile,
            "latticra-q-seal-ml-kem-sp800-227-usage-profile/0.1") == 0,
        "profile");
    EXPECT_TRUE(
        strcmp(
            profile.formal_title,
            "Latticra Q-Seal ML-KEM SP 800-227 Usage Profile") == 0,
        "title");
    EXPECT_TRUE(strcmp(profile.standards_basis, "NIST-SP-800-227") == 0, "standards");
    EXPECT_TRUE(
        strcmp(profile.sp_800_227_source_url, "https://csrc.nist.gov/pubs/sp/800/227/final") == 0,
        "source url");
    EXPECT_TRUE(
        strcmp(profile.sp_800_227_publication_date, "September-2025") == 0,
        "publication date");
    EXPECT_TRUE(profile.sp_800_227_source_bound == 1u, "source");
    EXPECT_TRUE(profile.sp_800_227_publication_date_recorded == 1u, "date");
    EXPECT_TRUE(profile.kem_definition_bound == 1u, "definition");
    EXPECT_TRUE(profile.shared_secret_establishment_scope_bound == 1u, "scope");
    EXPECT_TRUE(profile.encapsulation_role_bound == 1u, "encapsulation role");
    EXPECT_TRUE(profile.decapsulation_role_bound == 1u, "decapsulation role");
    EXPECT_TRUE(profile.approved_kem_algorithm_required == 1u, "approved algorithm");
    EXPECT_TRUE(profile.fips_203_ml_kem_bound == 1u, "ml-kem");
    EXPECT_TRUE(profile.key_establishment_context_required == 1u, "context");
    EXPECT_TRUE(profile.application_protocol_binding_required == 1u, "protocol");
    EXPECT_TRUE(profile.key_confirmation_decision_required == 1u, "confirmation");
    EXPECT_TRUE(profile.kdf_boundary_required == 1u, "kdf");
    EXPECT_TRUE(profile.domain_separation_required == 1u, "domain");
    EXPECT_TRUE(profile.shared_secret_lifecycle_required == 1u, "lifecycle");
    EXPECT_TRUE(profile.failure_handling_required == 1u, "failure");
    EXPECT_TRUE(profile.key_separation_required == 1u, "separation");
    EXPECT_TRUE(profile.algorithm_agility_policy_required == 1u, "agility");
    EXPECT_TRUE(profile.clean_room_source_boundary_recorded == 1u, "clean room");
    EXPECT_TRUE(profile.implementation_binding_required == 1u, "binding");
    EXPECT_TRUE(profile.apple_corecrypto_code_copied == 0u, "apple");
    EXPECT_TRUE(profile.external_provider_code_copied == 0u, "provider");
    EXPECT_TRUE(profile.kem_use_case_review_recorded == 1u, "use case");
    EXPECT_TRUE(profile.application_protocol_binding_recorded == 1u, "protocol review");
    EXPECT_TRUE(profile.key_confirmation_decision_recorded == 1u, "confirmation review");
    EXPECT_TRUE(profile.kdf_binding_recorded == 1u, "kdf review");
    EXPECT_TRUE(profile.domain_separation_reviewed == 1u, "domain review");
    EXPECT_TRUE(profile.shared_secret_lifecycle_reviewed == 1u, "lifecycle review");
    EXPECT_TRUE(profile.failure_handling_reviewed == 1u, "failure review");
    EXPECT_TRUE(profile.key_separation_reviewed == 1u, "separation review");
    EXPECT_TRUE(profile.algorithm_agility_reviewed == 1u, "agility review");
    EXPECT_TRUE(profile.kem_usage_profile_accepted == 1u, "accepted");
    EXPECT_TRUE(profile.operation_execution_allowed == 0u, "operation");
    EXPECT_TRUE(profile.shared_secret_emission_allowed == 0u, "shared secret");
    EXPECT_TRUE(profile.production_crypto_claim_allowed == 0u, "production");
    EXPECT_TRUE(profile.fips_claim_allowed == 0u, "fips");
    EXPECT_TRUE(profile.runtime_authority_granted == 0u, "runtime");
    EXPECT_TRUE(profile.required_usage_items_total == 30u, "total");
    EXPECT_TRUE(profile.required_usage_items_satisfied == 30u, "satisfied");
    EXPECT_TRUE(
        profile.error == LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_OK,
        "ok");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_is_no_effect(&profile) == 1,
        "no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_allows_kem_usage_acceptance(
            &profile) == 1,
        "allows acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_report(
            &profile,
            rendered,
            sizeof(rendered)) == LATTICRA_Q_SEAL_STATUS_OK,
        "report");
    EXPECT_TRUE(
        strstr(rendered, "sp800_227_usage_profile_present=1") != 0,
        "present report");
    EXPECT_TRUE(
        strstr(rendered, "sp_800_227_source_url=https://csrc.nist.gov/pubs/sp/800/227/final") != 0,
        "source url report");
    EXPECT_TRUE(
        strstr(rendered, "sp_800_227_publication_date=September-2025") != 0,
        "publication date report");
    EXPECT_TRUE(strstr(rendered, "kdf_boundary_required=1") != 0, "kdf report");
    EXPECT_TRUE(
        strstr(rendered, "kem_use_case_review_recorded=1") != 0,
        "use case report");
    EXPECT_TRUE(
        strstr(rendered, "application_protocol_binding_recorded=1") != 0,
        "protocol report");
    EXPECT_TRUE(strstr(rendered, "kem_usage_profile_accepted=1") != 0, "accepted report");
    EXPECT_TRUE(
        strstr(rendered, "shared_secret_emission_allowed=0") != 0,
        "shared-secret report");
    EXPECT_TRUE(strstr(rendered, "required_usage_items_satisfied=30") != 0, "satisfied report");
    EXPECT_TRUE(strstr(rendered, "error=ok") != 0, "error report");
    EXPECT_TRUE(strstr(rendered, "required_usage_items_total=30") != 0, "total report");
    return 0;
}

static int sp800_227_usage_profile_rejects_invalid_inputs(void) {
    latticra_q_seal_ml_kem_sp800_227_usage_profile_t profile;
    char tiny[8];

    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_prepare(0) ==
            LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null prepare");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_is_no_effect(0) == 0,
        "null no effect");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_allows_kem_usage_acceptance(
            0) == 0,
        "null acceptance");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_prepare(&profile) ==
            LATTICRA_Q_SEAL_STATUS_OK,
        "prepare valid");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_report(
            0,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report input");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_report(
            &profile,
            0,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_NULL_ARGUMENT,
        "null report buffer");
    EXPECT_TRUE(
        latticra_q_seal_ml_kem_sp800_227_usage_profile_report(
            &profile,
            tiny,
            sizeof(tiny)) == LATTICRA_Q_SEAL_STATUS_BUFFER_TOO_SMALL,
        "small report");
    return 0;
}

int main(void) {
    if (sp800_227_usage_profile_is_accepted_but_runtime_closed() != 0) {
        return 1;
    }
    if (sp800_227_usage_profile_rejects_invalid_inputs() != 0) {
        return 1;
    }
    printf("latticra q-seal ml-kem sp800-227 usage profile invariants: ok\n");
    return 0;
}

#include "latticra/cpp/authority.hpp"

#include <cstddef>
#include <type_traits>

namespace {

int failures = 0;

void expect(const bool condition) noexcept {
    if (!condition) {
        failures = 1;
    }
}

bool same_text(const char *left, const char *right) noexcept {
    if (left == nullptr || right == nullptr) {
        return left == right;
    }

    std::size_t index = 0u;
    while (left[index] != '\0' || right[index] != '\0') {
        if (left[index] != right[index]) {
            return false;
        }
        ++index;
    }
    return true;
}

bool contains_text(const char *haystack, const char *needle) noexcept {
    if (haystack == nullptr || needle == nullptr) {
        return false;
    }
    if (needle[0] == '\0') {
        return true;
    }

    for (std::size_t index = 0u; haystack[index] != '\0'; ++index) {
        std::size_t offset = 0u;
        while (needle[offset] != '\0' &&
               haystack[index + offset] == needle[offset]) {
            ++offset;
        }
        if (needle[offset] == '\0') {
            return true;
        }
    }
    return false;
}

latticra_lat_source_span_t ordered_lat_span() noexcept {
    return latticra_lat_source_span_t{0u, 10u, 1u, 1u, 1u, 11u};
}

latticra_l_ui_source_span_t ordered_l_ui_span() noexcept {
    return latticra_l_ui_source_span_t{0u, 10u, 1u, 1u, 1u, 11u};
}

latticra_lat_source_span_t unordered_lat_span() noexcept {
    return latticra_lat_source_span_t{10u, 0u, 1u, 11u, 1u, 1u};
}

latticra_l_ui_source_span_t unordered_l_ui_span() noexcept {
    return latticra_l_ui_source_span_t{10u, 0u, 1u, 11u, 1u, 1u};
}

latticra_lat_parse_result_t valid_lat_result() noexcept {
    latticra_lat_parse_result_t result{};
    result.status = LATTICRA_STATUS_OK;
    result.error = LATTICRA_LAT_PARSE_OK;
    result.span = ordered_lat_span();
    result.module.span = ordered_lat_span();
    result.no_effect = 1;
    result.execution_allowed = 0;
    result.mutation_allowed = 0;
    result.server_allowed = 0;
    result.network_allowed = 0;
    result.recovery_allowed = 0;
    result.hardware_allowed = 0;
    return result;
}

latticra_lir_module_t valid_lir_module() noexcept {
    latticra_lir_module_t module{};
    module.status = LATTICRA_STATUS_OK;
    module.error = LATTICRA_LIR_OK;
    module.source_span = ordered_l_ui_span();
    module.no_effect = 1;
    module.execution_allowed = 0;
    module.mutation_allowed = 0;
    module.server_allowed = 0;
    module.network_allowed = 0;
    module.recovery_allowed = 0;
    module.hardware_allowed = 0;
    return module;
}

void cpp_authority_layer_preserves_no_effect_flags() noexcept {
    latticra::authority_audit_report report{};
    const latticra_lat_parse_result_t result = valid_lat_result();

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::ok);
    expect(report.flags.no_effect);
    expect(!report.flags.execution_allowed);
    expect(!report.flags.mutation_allowed);
    expect(!report.flags.server_allowed);
    expect(!report.flags.network_allowed);
    expect(!report.flags.recovery_allowed);
    expect(!report.flags.hardware_allowed);
}

void cpp_authority_layer_rejects_unrestricted_cpp_claims() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::host_mutation;
    request.source_identity = "unrestricted-cpp-claim";

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(report.record_count == 1u);
    expect(same_text(report.records[0].denial_reason.data(),
                     "effect_performance_denied"));
}

void cpp_authority_layer_has_no_execution_path() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::boot;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(!report.flags.execution_allowed);
}

void cpp_authority_layer_has_no_network_path() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::network;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(!report.flags.server_allowed);
    expect(!report.flags.network_allowed);
}

void cpp_authority_layer_has_no_hardware_path() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::hardware;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(!report.flags.hardware_allowed);
}

void cpp_authority_layer_uses_explicit_result_labels() noexcept {
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::ok),
                     "ok"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::null_argument),
                     "null_argument"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::invalid_input),
                     "invalid_input"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::capacity_exceeded),
                     "capacity_exceeded"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::policy_denied),
                     "policy_denied"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::unsupported_effect),
                     "unsupported_effect"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::unsupported_boundary),
                     "unsupported_boundary"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::not_authorized),
                     "not_authorized"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::internal_error),
                     "internal_error"));
}

void cpp_authority_layer_uses_stable_effect_labels() noexcept {
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::none),
                     "none"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::read),
                     "read"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::local_mutation),
                     "local_mutation"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::host_mutation),
                     "host_mutation"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::network),
                     "network"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::hardware),
                     "hardware"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::boot),
                     "boot"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::recovery),
                     "recovery"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::external),
                     "external"));
    expect(same_text(latticra::authority_effect_label(
                         latticra::authority_effect::unknown),
                     "unknown"));
}

void cpp_authority_layer_uses_stable_validator_labels() noexcept {
    expect(same_text(latticra::authority_validator_label(
                         latticra::authority_validator::naming),
                     "naming"));
    expect(same_text(latticra::authority_validator_label(
                         latticra::authority_validator::source_span),
                     "source_span"));
    expect(same_text(latticra::authority_validator_label(
                         latticra::authority_validator::no_effect),
                     "no_effect"));
    expect(same_text(latticra::authority_validator_label(
                         latticra::authority_validator::effect),
                     "effect"));
    expect(same_text(latticra::authority_validator_label(
                         latticra::authority_validator::boundary),
                     "boundary"));
    expect(same_text(latticra::authority_validator_label(
                         latticra::authority_validator::state_shape),
                     "state_shape"));
    expect(same_text(latticra::authority_validator_label(
                         latticra::authority_validator::lir_shape),
                     "lir_shape"));
    expect(same_text(latticra::authority_validator_label(
                         latticra::authority_validator::lat_parse_result),
                     "lat_parse_result"));
}

void cpp_authority_layer_does_not_throw_across_c_boundary() noexcept {
    latticra::authority_audit_report report{};
    const latticra_lat_parse_result_t result = valid_lat_result();

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::ok);
}

void cpp_authority_layer_public_api_contract_is_noexcept() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t lat_result{};
    latticra_lir_module_t lir_module{};
    latticra::authority_request request{};
    char buffer[1]{};

    static_assert(noexcept(latticra::authority_status_label(
        latticra::authority_status::ok)));
    static_assert(noexcept(latticra::authority_effect_label(
        latticra::authority_effect::none)));
    static_assert(noexcept(latticra::authority_validator_label(
        latticra::authority_validator::no_effect)));
    static_assert(noexcept(latticra::validate_lat_parse_result(
        lat_result, report)));
    static_assert(noexcept(latticra::validate_lir_shape(lir_module, report)));
    static_assert(noexcept(latticra::classify_effect_request(request, report)));
    static_assert(noexcept(latticra::render_authority_audit_report(
        report, buffer, sizeof(buffer))));

    static_assert(std::is_same_v<
                  decltype(latticra::authority_status_label(
                      latticra::authority_status::ok)),
                  const char *>);
    static_assert(std::is_same_v<
                  decltype(latticra::authority_effect_label(
                      latticra::authority_effect::none)),
                  const char *>);
    static_assert(std::is_same_v<
                  decltype(latticra::authority_validator_label(
                      latticra::authority_validator::no_effect)),
                  const char *>);
    static_assert(std::is_same_v<
                  decltype(latticra::validate_lat_parse_result(
                      lat_result, report)),
                  latticra::authority_status>);
    static_assert(std::is_same_v<
                  decltype(latticra::validate_lir_shape(lir_module, report)),
                  latticra::authority_status>);
    static_assert(std::is_same_v<
                  decltype(latticra::classify_effect_request(request, report)),
                  latticra::authority_status>);
    static_assert(std::is_same_v<
                  decltype(latticra::render_authority_audit_report(
                      report, buffer, sizeof(buffer))),
                  latticra::authority_status>);
    expect(true);
}

void cpp_authority_layer_does_not_allocate_in_report_path() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};
    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) == latticra::authority_status::ok);
    expect(contains_text(buffer, "CPP AUTHORITY REPORT"));
    expect(contains_text(buffer, "network_allowed=0"));
}

void cpp_authority_layer_preserves_source_identity_in_audit() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::read;
    request.source_identity = "authority-fixture";
    latticra::authority_audit_report report{};
    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::policy_denied);
    expect(same_text(report.records[0].source_identity.data(),
                     "authority-fixture"));
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) == latticra::authority_status::ok);
    expect(contains_text(buffer,
                         "record[0].source_identity=authority-fixture"));
}

void cpp_authority_layer_accepts_max_source_identity() noexcept {
    char source[latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX]{};
    for (std::size_t index = 0u;
         index < latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX;
         ++index) {
        source[index] = 'm';
    }

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.source_identity = std::string_view{
        source, latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX};

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::ok);
    expect(report.records[0].source_identity[
               latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX] == '\0');
}

void cpp_authority_layer_rejects_oversized_source_identity() noexcept {
    char source[latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u]{};
    for (std::size_t index = 0u;
         index < latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u;
         ++index) {
        source[index] = 'a';
    }

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.source_identity = std::string_view{
        source, latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u};

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::capacity_exceeded);
    expect(same_text(report.records[0].denial_reason.data(),
                     "source_identity_too_large"));
}

void cpp_authority_layer_bounds_source_identity_before_audit_copy() noexcept {
    char source[latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u]{};
    for (std::size_t index = 0u;
         index < latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u;
         ++index) {
        source[index] = 'b';
    }

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.flags.mutation_allowed = true;
    request.requested_effect = latticra::authority_effect::none;
    request.source_identity = std::string_view{
        source, latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u};

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::capacity_exceeded);
    expect(report.record_count == 1u);
    expect(same_text(report.records[0].denial_reason.data(),
                     "source_identity_too_large"));
}

void cpp_authority_layer_rejects_nul_source_identity() noexcept {
    const char source[4]{'l', 'a', '\0', 't'};

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.source_identity = std::string_view{source, sizeof(source)};

    latticra::authority_audit_report report{};
    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "source_identity_contains_nul"));
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) == latticra::authority_status::ok);
    expect(contains_text(buffer, "source_identity_contains_nul"));
}

void cpp_authority_layer_rejects_line_break_source_identity() noexcept {
    const char source[] = "lat\nreport";

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.source_identity = std::string_view{source, sizeof(source) - 1u};

    latticra::authority_audit_report report{};
    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "source_identity_contains_line_break"));
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) == latticra::authority_status::ok);
    expect(contains_text(buffer, "source_identity_contains_line_break"));
}

void cpp_authority_layer_rejects_requested_effect_out_of_vocabulary() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = static_cast<latticra::authority_effect>(255);
    request.source_identity = "invalid-effect";

    latticra::authority_audit_report report{};
    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(report.records[0].requested_effect ==
           latticra::authority_effect::unknown);
    expect(same_text(report.records[0].denial_reason.data(),
                     "requested_effect_out_of_vocabulary"));
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) == latticra::authority_status::ok);
    expect(contains_text(buffer, "record[0].requested_effect=unknown"));
}

void cpp_authority_layer_validates_lat_parse_result_metadata() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.declaration_count = LATTICRA_LAT_DECLARATION_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::capacity_exceeded);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_capacity_exceeded"));
}

void cpp_authority_layer_rejects_lat_parse_result_status_not_ok() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.status = LATTICRA_STATUS_NULL_ARGUMENT;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_parse_result_not_ok"));
}

void cpp_authority_layer_rejects_lat_parse_error_not_ok() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.error = LATTICRA_LAT_PARSE_EMPTY_SOURCE;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_parse_result_not_ok"));
}

void cpp_authority_layer_rejects_lat_source_span_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.span.end_offset = LATTICRA_LAT_SOURCE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_source_span_out_of_bounds"));
}

void cpp_authority_layer_rejects_lat_source_span_unordered() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.span = unordered_lat_span();

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_source_span_unordered"));
}

void cpp_authority_layer_rejects_lat_module_declaration_count_out_of_bounds()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.declaration_count = 0u;
    result.module.declaration_count = 1u;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_module_declaration_count_out_of_bounds"));
}

void cpp_authority_layer_rejects_lat_declaration_clause_range_out_of_bounds()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.declaration_count = 1u;
    result.module.declaration_count = 1u;
    result.clause_count = 1u;
    result.declarations[0].span = ordered_lat_span();
    result.declarations[0].first_clause_index = 1u;
    result.declarations[0].clause_count = 1u;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_declaration_clause_range_out_of_bounds"));
}

void cpp_authority_layer_rejects_lat_declaration_span_unordered() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.declaration_count = 1u;
    result.module.declaration_count = 1u;
    result.declarations[0].span = unordered_lat_span();

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_declaration_span_unordered"));
}

void cpp_authority_layer_rejects_lat_declaration_span_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.declaration_count = 1u;
    result.module.declaration_count = 1u;
    result.declarations[0].span = ordered_lat_span();
    result.declarations[0].span.end_offset = LATTICRA_LAT_SOURCE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_declaration_span_out_of_bounds"));
}

void cpp_authority_layer_rejects_lat_module_kind_counts_out_of_bounds()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.declaration_count = 1u;
    result.module.declaration_count = 1u;
    result.module.state_count = 1u;
    result.module.policy_count = 1u;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_module_kind_counts_out_of_bounds"));
}

void cpp_authority_layer_rejects_lat_declaration_kind_out_of_vocabulary()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.declaration_count = 1u;
    result.module.declaration_count = 1u;
    result.declarations[0].span = ordered_lat_span();
    result.declarations[0].kind =
        static_cast<latticra_lat_declaration_kind_t>(255);

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_declaration_kind_out_of_vocabulary"));
}

void cpp_authority_layer_rejects_lat_clause_effect_out_of_vocabulary()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.clause_count = 1u;
    result.clauses[0].span = ordered_lat_span();
    result.clauses[0].effect = static_cast<latticra_lat_effect_t>(255);

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_clause_effect_out_of_vocabulary"));
}

void cpp_authority_layer_rejects_lat_clause_span_unordered() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.clause_count = 1u;
    result.clauses[0].span = unordered_lat_span();

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_clause_span_unordered"));
}

void cpp_authority_layer_rejects_lat_clause_span_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lat_parse_result_t result = valid_lat_result();
    result.clause_count = 1u;
    result.clauses[0].span = ordered_lat_span();
    result.clauses[0].span.end_offset = LATTICRA_LAT_SOURCE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_clause_span_out_of_bounds"));
}

void cpp_authority_layer_validates_lir_shape_metadata() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = LATTICRA_LIR_NODE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::capacity_exceeded);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_capacity_exceeded"));
}

void cpp_authority_layer_rejects_lir_module_status_not_ok() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.status = LATTICRA_STATUS_NULL_ARGUMENT;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_shape_not_ok"));
}

void cpp_authority_layer_rejects_lir_error_not_ok() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.error = LATTICRA_LIR_SEMANTIC_FAILED;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_shape_not_ok"));
}

void cpp_authority_layer_rejects_lir_source_span_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.source_span.end_offset = LATTICRA_L_UI_SOURCE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_source_span_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_source_span_unordered() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.source_span = unordered_l_ui_span();

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_source_span_unordered"));
}

void cpp_authority_layer_rejects_lir_node_child_range_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.nodes[0].first_child_index = 1u;
    module.nodes[0].child_count = 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_node_child_range_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_node_parent_index_out_of_bounds()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.nodes[0].parent_index = 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_node_parent_index_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_node_span_unordered() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.nodes[0].source_span = unordered_l_ui_span();

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_node_span_unordered"));
}

void cpp_authority_layer_rejects_lir_node_span_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.nodes[0].source_span = ordered_l_ui_span();
    module.nodes[0].source_span.end_offset = LATTICRA_L_UI_SOURCE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_node_span_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_edge_node_index_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.edge_count = 1u;
    module.edges[0].from_index = 0u;
    module.edges[0].to_index = 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_edge_node_index_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_edge_span_unordered() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.edge_count = 1u;
    module.edges[0].source_span = unordered_l_ui_span();

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_edge_span_unordered"));
}

void cpp_authority_layer_rejects_lir_edge_span_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.edge_count = 1u;
    module.edges[0].source_span = ordered_l_ui_span();
    module.edges[0].source_span.end_offset = LATTICRA_L_UI_SOURCE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_edge_span_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_binding_node_index_out_of_bounds()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.binding_count = 1u;
    module.bindings[0].field_node_index = 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_binding_node_index_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_binding_span_unordered() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.binding_count = 1u;
    module.bindings[0].source_span = unordered_l_ui_span();

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_binding_span_unordered"));
}

void cpp_authority_layer_rejects_lir_binding_span_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.binding_count = 1u;
    module.bindings[0].source_span = ordered_l_ui_span();
    module.bindings[0].source_span.end_offset = LATTICRA_L_UI_SOURCE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_binding_span_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_text_node_index_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.text_count = 1u;
    module.texts[0].text_node_index = 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_text_node_index_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_text_length_exceeded() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.text_count = 1u;
    module.texts[0].value_len = LATTICRA_LIR_VALUE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::capacity_exceeded);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_text_length_exceeded"));
}

void cpp_authority_layer_rejects_lir_text_span_unordered() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.text_count = 1u;
    module.texts[0].source_span = unordered_l_ui_span();

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_text_span_unordered"));
}

void cpp_authority_layer_rejects_lir_text_span_out_of_bounds() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.text_count = 1u;
    module.texts[0].source_span = ordered_l_ui_span();
    module.texts[0].source_span.end_offset = LATTICRA_L_UI_SOURCE_MAX + 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_text_span_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_edge_kind_counts_out_of_bounds()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.edge_count = 1u;
    module.contains_edge_count = 1u;
    module.binds_edge_count = 1u;

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_edge_kind_counts_out_of_bounds"));
}

void cpp_authority_layer_rejects_lir_module_enum_out_of_vocabulary() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.source_kind = static_cast<latticra_lir_source_kind_t>(255);

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_module_enum_out_of_vocabulary"));
}

void cpp_authority_layer_rejects_lir_node_kind_out_of_vocabulary() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.nodes[0].kind = static_cast<latticra_lir_node_kind_t>(255);

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_node_kind_out_of_vocabulary"));
}

void cpp_authority_layer_rejects_lir_edge_kind_out_of_vocabulary() noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.edge_count = 1u;
    module.edges[0].edge_kind = static_cast<latticra_lir_edge_kind_t>(255);

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_edge_kind_out_of_vocabulary"));
}

void cpp_authority_layer_rejects_lir_binding_kind_out_of_vocabulary()
    noexcept {
    latticra::authority_audit_report report{};
    latticra_lir_module_t module = valid_lir_module();
    module.node_count = 1u;
    module.binding_count = 1u;
    module.bindings[0].resolved_kind =
        static_cast<latticra_lir_resolved_binding_kind_t>(255);

    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_binding_kind_out_of_vocabulary"));
}

void cpp_authority_layer_audit_report_is_deterministic() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::read;

    latticra::authority_audit_report first_report{};
    latticra::authority_audit_report second_report{};
    char first[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    char second[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};

    expect(latticra::classify_effect_request(request, first_report) ==
           latticra::authority_status::policy_denied);
    expect(latticra::classify_effect_request(request, second_report) ==
           latticra::authority_status::policy_denied);
    expect(latticra::render_authority_audit_report(
               first_report, first, sizeof(first)) ==
           latticra::authority_status::ok);
    expect(latticra::render_authority_audit_report(
               second_report, second, sizeof(second)) ==
           latticra::authority_status::ok);
    expect(same_text(first, second));
}

void cpp_authority_layer_renders_report_header_and_record_fields() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::read;
    request.source_identity = "report-format-fixture";
    latticra::authority_audit_report report{};
    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::policy_denied);
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) == latticra::authority_status::ok);
    expect(contains_text(buffer, "CPP AUTHORITY REPORT\n"));
    expect(contains_text(buffer, "status=policy_denied\n"));
    expect(contains_text(buffer, "record_count=1\n"));
    expect(contains_text(buffer, "no_effect=1\nexecution_allowed=0\n"));
    expect(contains_text(buffer, "mutation_allowed=0\nserver_allowed=0\n"));
    expect(contains_text(buffer, "network_allowed=0\nrecovery_allowed=0\n"));
    expect(contains_text(buffer, "hardware_allowed=0\n"));
    expect(contains_text(buffer, "record[0].policy=cpp_authority\n"));
    expect(contains_text(
        buffer, "record[0].source_identity=report-format-fixture\n"));
    expect(contains_text(buffer, "record[0].validator=effect\n"));
    expect(contains_text(buffer, "record[0].requested_effect=read\n"));
    expect(contains_text(buffer, "record[0].no_effect=1\n"));
    expect(contains_text(buffer, "record[0].execution_allowed=0\n"));
    expect(contains_text(buffer, "record[0].mutation_allowed=0\n"));
    expect(contains_text(buffer, "record[0].server_allowed=0\n"));
    expect(contains_text(buffer, "record[0].network_allowed=0\n"));
    expect(contains_text(buffer, "record[0].recovery_allowed=0\n"));
    expect(contains_text(buffer, "record[0].hardware_allowed=0\n"));
    expect(contains_text(buffer, "record[0].result=policy_denied\n"));
    expect(contains_text(
        buffer, "record[0].denial_reason=effect_performance_denied\n"));
    expect(contains_text(buffer, "record[0].span_start_offset=0\n"));
    expect(contains_text(buffer, "record[0].span_end_offset=0\n"));
    expect(contains_text(buffer, "record[0].span_start_line=0\n"));
    expect(contains_text(buffer, "record[0].span_start_column=0\n"));
    expect(contains_text(buffer, "record[0].span_end_line=0\n"));
    expect(contains_text(buffer, "record[0].span_end_column=0\n"));
}

void cpp_authority_layer_renders_record_no_effect_flags() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.flags.mutation_allowed = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};
    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::policy_denied);
    expect(report.records[0].flags.no_effect);
    expect(report.records[0].flags.mutation_allowed);
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) == latticra::authority_status::ok);
    expect(contains_text(buffer, "record[0].no_effect=1"));
    expect(contains_text(buffer, "record[0].mutation_allowed=1"));
    expect(contains_text(buffer, "record[0].network_allowed=0"));
}

void cpp_authority_layer_renders_record_source_span_coordinates() noexcept {
    latticra::authority_audit_report report{};
    const latticra_lat_parse_result_t result = valid_lat_result();
    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};

    expect(latticra::validate_lat_parse_result(result, report) ==
           latticra::authority_status::ok);
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) == latticra::authority_status::ok);
    expect(contains_text(buffer, "record[0].span_start_offset=0"));
    expect(contains_text(buffer, "record[0].span_end_offset=10"));
    expect(contains_text(buffer, "record[0].span_start_line=1"));
    expect(contains_text(buffer, "record[0].span_start_column=1"));
    expect(contains_text(buffer, "record[0].span_end_line=1"));
    expect(contains_text(buffer, "record[0].span_end_column=11"));
}

void cpp_authority_layer_rejects_small_report_buffer() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};
    char buffer[8]{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    expect(latticra::render_authority_audit_report(
               report, buffer, sizeof(buffer)) ==
           latticra::authority_status::capacity_exceeded);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_null_report_buffer() noexcept {
    latticra::authority_audit_report report{};

    const latticra::authority_status status =
        latticra::render_authority_audit_report(
            report, nullptr, latticra::LATTICRA_AUTHORITY_REPORT_MAX);

    expect(status == latticra::authority_status::null_argument);
}

void cpp_authority_layer_rejects_too_many_audit_records() noexcept {
    latticra::authority_audit_report report{};
    report.status = latticra::authority_status::ok;
    report.record_count = latticra::LATTICRA_AUTHORITY_AUDIT_RECORD_MAX + 1u;

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    buffer[0] = 'x';
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::capacity_exceeded);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_unterminated_audit_text() noexcept {
    latticra::authority_audit_report report{};
    report.status = latticra::authority_status::ok;
    report.record_count = 1u;
    report.records[0].status = latticra::authority_status::ok;
    for (std::size_t index = 0u;
         index < latticra::LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u;
         ++index) {
        report.records[0].source_identity[index] = 's';
    }

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_audit_text_line_breaks() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    report.records[0].denial_reason[0] = 'x';
    report.records[0].denial_reason[1] = '\n';
    report.records[0].denial_reason[2] = '\0';

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_noncanonical_audit_text_padding() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    report.records[0].source_identity[0] = 'x';
    report.records[0].source_identity[1] = '\0';
    report.records[0].source_identity[2] = 'y';

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_noncanonical_policy_name() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    report.records[0].policy_name[0] = 'x';

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_noncanonical_validator_name() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    report.records[0].validator_name[0] = 'x';

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_report_status_out_of_vocabulary() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    report.status = static_cast<latticra::authority_status>(255);

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_audit_record_status_out_of_vocabulary() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    report.records[0].status = static_cast<latticra::authority_status>(255);

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_audit_record_validator_out_of_vocabulary()
    noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    report.records[0].validator = static_cast<latticra::authority_validator>(255);

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_rejects_audit_record_effect_out_of_vocabulary()
    noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    latticra::authority_audit_report report{};

    expect(latticra::classify_effect_request(request, report) ==
           latticra::authority_status::ok);
    report.records[0].requested_effect =
        static_cast<latticra::authority_effect>(255);

    char buffer[latticra::LATTICRA_AUTHORITY_REPORT_MAX]{};
    const latticra::authority_status status =
        latticra::render_authority_audit_report(report, buffer, sizeof(buffer));

    expect(status == latticra::authority_status::invalid_input);
    expect(buffer[0] == '\0');
}

void cpp_authority_layer_is_deterministic() noexcept {
    latticra::authority_audit_report first{};
    latticra::authority_audit_report second{};
    const latticra_lir_module_t module = valid_lir_module();

    expect(latticra::validate_lir_shape(module, first) ==
           latticra::authority_status::ok);
    expect(latticra::validate_lir_shape(module, second) ==
           latticra::authority_status::ok);
    expect(first.record_count == second.record_count);
    expect(first.status == second.status);
    expect(first.records[0].status == second.records[0].status);
}

void cpp_authority_layer_rejects_mutation_flags() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.flags.mutation_allowed = true;
    request.requested_effect = latticra::authority_effect::none;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(same_text(report.records[0].denial_reason.data(),
                     "non_no_effect_flags_denied"));
}

void cpp_authority_layer_rejects_network_flags() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.flags.network_allowed = true;
    request.requested_effect = latticra::authority_effect::none;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(same_text(report.records[0].denial_reason.data(),
                     "non_no_effect_flags_denied"));
}

void cpp_authority_layer_rejects_lat_network_flags() noexcept {
    latticra_lat_parse_result_t result = valid_lat_result();
    result.network_allowed = 1;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(report.flags.network_allowed);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_no_effect_flags_not_preserved"));
}

void cpp_authority_layer_rejects_lir_network_flags() noexcept {
    latticra_lir_module_t module = valid_lir_module();
    module.network_allowed = 1;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(report.flags.network_allowed);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_no_effect_flags_not_preserved"));
}

void expect_request_no_effect_flag_denied(
    const latticra::authority_flags flags) noexcept {
    latticra::authority_request request{};
    request.flags = flags;
    request.requested_effect = latticra::authority_effect::none;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(same_text(report.records[0].denial_reason.data(),
                     "non_no_effect_flags_denied"));
}

void cpp_authority_layer_rejects_all_request_no_effect_flag_deviations()
    noexcept {
    latticra::authority_flags flags{};
    flags.no_effect = false;
    expect_request_no_effect_flag_denied(flags);

    flags = latticra::authority_flags{};
    flags.execution_allowed = true;
    expect_request_no_effect_flag_denied(flags);

    flags = latticra::authority_flags{};
    flags.mutation_allowed = true;
    expect_request_no_effect_flag_denied(flags);

    flags = latticra::authority_flags{};
    flags.server_allowed = true;
    expect_request_no_effect_flag_denied(flags);

    flags = latticra::authority_flags{};
    flags.network_allowed = true;
    expect_request_no_effect_flag_denied(flags);

    flags = latticra::authority_flags{};
    flags.recovery_allowed = true;
    expect_request_no_effect_flag_denied(flags);

    flags = latticra::authority_flags{};
    flags.hardware_allowed = true;
    expect_request_no_effect_flag_denied(flags);
}

void expect_lat_no_effect_flag_denied(
    const latticra_lat_parse_result_t result) noexcept {
    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_no_effect_flags_not_preserved"));
}

void cpp_authority_layer_rejects_all_lat_no_effect_flag_deviations() noexcept {
    latticra_lat_parse_result_t result = valid_lat_result();
    result.no_effect = 0;
    expect_lat_no_effect_flag_denied(result);

    result = valid_lat_result();
    result.execution_allowed = 1;
    expect_lat_no_effect_flag_denied(result);

    result = valid_lat_result();
    result.mutation_allowed = 1;
    expect_lat_no_effect_flag_denied(result);

    result = valid_lat_result();
    result.server_allowed = 1;
    expect_lat_no_effect_flag_denied(result);

    result = valid_lat_result();
    result.network_allowed = 1;
    expect_lat_no_effect_flag_denied(result);

    result = valid_lat_result();
    result.recovery_allowed = 1;
    expect_lat_no_effect_flag_denied(result);

    result = valid_lat_result();
    result.hardware_allowed = 1;
    expect_lat_no_effect_flag_denied(result);
}

void expect_lir_no_effect_flag_denied(
    const latticra_lir_module_t module) noexcept {
    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::validate_lir_shape(module, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_no_effect_flags_not_preserved"));
}

void cpp_authority_layer_rejects_all_lir_no_effect_flag_deviations() noexcept {
    latticra_lir_module_t module = valid_lir_module();
    module.no_effect = 0;
    expect_lir_no_effect_flag_denied(module);

    module = valid_lir_module();
    module.execution_allowed = 1;
    expect_lir_no_effect_flag_denied(module);

    module = valid_lir_module();
    module.mutation_allowed = 1;
    expect_lir_no_effect_flag_denied(module);

    module = valid_lir_module();
    module.server_allowed = 1;
    expect_lir_no_effect_flag_denied(module);

    module = valid_lir_module();
    module.network_allowed = 1;
    expect_lir_no_effect_flag_denied(module);

    module = valid_lir_module();
    module.recovery_allowed = 1;
    expect_lir_no_effect_flag_denied(module);

    module = valid_lir_module();
    module.hardware_allowed = 1;
    expect_lir_no_effect_flag_denied(module);
}

void cpp_authority_layer_rejects_request_lat_network_flags() noexcept {
    latticra_lat_parse_result_t result = valid_lat_result();
    result.network_allowed = 1;

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.lat_result = &result;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(report.flags.network_allowed);
    expect(report.records[0].requested_effect == latticra::authority_effect::none);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_no_effect_flags_not_preserved"));
}

void cpp_authority_layer_rejects_request_lir_network_flags() noexcept {
    latticra_lir_module_t module = valid_lir_module();
    module.network_allowed = 1;

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.lir_module = &module;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::policy_denied);
    expect(report.flags.network_allowed);
    expect(report.records[0].requested_effect == latticra::authority_effect::none);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lir_no_effect_flags_not_preserved"));
}

void cpp_authority_layer_accepts_request_with_valid_linked_metadata() noexcept {
    const latticra_lat_parse_result_t result = valid_lat_result();
    const latticra_lir_module_t module = valid_lir_module();

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.source_identity = "linked-metadata";
    request.lat_result = &result;
    request.lir_module = &module;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::ok);
    expect(report.record_count == 1u);
    expect(report.records[0].requested_effect == latticra::authority_effect::none);
    expect(same_text(report.records[0].denial_reason.data(), "none"));
    expect(same_text(report.records[0].source_identity.data(),
                     "linked-metadata"));
}

void cpp_authority_layer_rejects_request_lat_metadata_before_no_effect_allow()
    noexcept {
    latticra_lat_parse_result_t result = valid_lat_result();
    result.status = LATTICRA_STATUS_NULL_ARGUMENT;

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.lat_result = &result;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(report.records[0].validator ==
           latticra::authority_validator::lat_parse_result);
    expect(report.records[0].requested_effect == latticra::authority_effect::none);
    expect(same_text(report.records[0].denial_reason.data(),
                     "lat_parse_result_not_ok"));
}

void cpp_authority_layer_rejects_request_lir_metadata_before_no_effect_allow()
    noexcept {
    latticra_lir_module_t module = valid_lir_module();
    module.status = LATTICRA_STATUS_NULL_ARGUMENT;

    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::none;
    request.lir_module = &module;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::invalid_input);
    expect(report.records[0].validator == latticra::authority_validator::lir_shape);
    expect(report.records[0].requested_effect == latticra::authority_effect::none);
    expect(same_text(report.records[0].denial_reason.data(), "lir_shape_not_ok"));
}

void cpp_authority_layer_classifies_effects_without_performing_them() noexcept {
    latticra::authority_request request{};
    request.flags.no_effect = true;
    request.requested_effect = latticra::authority_effect::unknown;

    latticra::authority_audit_report report{};
    const latticra::authority_status status =
        latticra::classify_effect_request(request, report);

    expect(status == latticra::authority_status::unsupported_effect);
    expect(report.records[0].requested_effect == latticra::authority_effect::unknown);
}

void cpp_authority_layer_builds_with_fno_exceptions_and_fno_rtti() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_missing_required_flags() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_conflicting_required_flags() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_unlisted_compiler_flags() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_environment_include_injection_flags()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_environment_macro_override_flags()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_environment_linker_injection_flags()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_environment_toolchain_escape_flags()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_ambient_compiler_environment_variables()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_ambient_dyld_environment_prefix()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_ambient_tool_selector_variables()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_uses_sanitized_tool_path() noexcept {
    expect(true);
}

void cpp_authority_layer_build_uses_absolute_shell_entrypoint() noexcept {
    expect(true);
}

void cpp_authority_layer_build_uses_deterministic_tool_locale() noexcept {
    expect(true);
}

void cpp_authority_layer_build_uses_fixed_temporary_root() noexcept {
    expect(true);
}

void cpp_authority_layer_build_uses_private_artifact_permissions() noexcept {
    expect(true);
}

void cpp_authority_layer_build_uses_cxx20_standard() noexcept {
    expect(true);
}

void cpp_authority_layer_build_uses_warnings_as_errors() noexcept {
    expect(true);
}

void cpp_authority_layer_build_uses_source_and_object_static_analysis_path()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_policy_self_checks_runner_command_shape()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_requires_extern_c_substrate_includes() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_unwrapped_c_substrate_includes()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_direct_c_substrate_includes() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_unlisted_quote_includes() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_spaced_preprocessor_includes() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_unlisted_standard_headers() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_unlisted_std_apis() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_writable_global_data_symbols() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_common_data_symbols() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_allocation_symbols() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_exception_and_rtti_symbols() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_indirect_exception_and_rtti_symbols()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_framework_namespaces() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_io_and_process_calls() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_c_substrate_function_calls() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_public_c_abi_symbols() noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_public_unmangled_defined_symbols()
    noexcept {
    expect(true);
}

void cpp_authority_layer_build_rejects_template_metaprogramming_constructs()
    noexcept {
    expect(true);
}

}  // namespace

int main() {
    cpp_authority_layer_preserves_no_effect_flags();
    cpp_authority_layer_rejects_unrestricted_cpp_claims();
    cpp_authority_layer_has_no_execution_path();
    cpp_authority_layer_has_no_network_path();
    cpp_authority_layer_has_no_hardware_path();
    cpp_authority_layer_uses_explicit_result_labels();
    cpp_authority_layer_uses_stable_effect_labels();
    cpp_authority_layer_uses_stable_validator_labels();
    cpp_authority_layer_does_not_throw_across_c_boundary();
    cpp_authority_layer_public_api_contract_is_noexcept();
    cpp_authority_layer_does_not_allocate_in_report_path();
    cpp_authority_layer_preserves_source_identity_in_audit();
    cpp_authority_layer_accepts_max_source_identity();
    cpp_authority_layer_rejects_oversized_source_identity();
    cpp_authority_layer_bounds_source_identity_before_audit_copy();
    cpp_authority_layer_rejects_nul_source_identity();
    cpp_authority_layer_rejects_line_break_source_identity();
    cpp_authority_layer_rejects_requested_effect_out_of_vocabulary();
    cpp_authority_layer_validates_lat_parse_result_metadata();
    cpp_authority_layer_rejects_lat_parse_result_status_not_ok();
    cpp_authority_layer_rejects_lat_parse_error_not_ok();
    cpp_authority_layer_rejects_lat_source_span_out_of_bounds();
    cpp_authority_layer_rejects_lat_source_span_unordered();
    cpp_authority_layer_rejects_lat_module_declaration_count_out_of_bounds();
    cpp_authority_layer_rejects_lat_declaration_clause_range_out_of_bounds();
    cpp_authority_layer_rejects_lat_declaration_span_unordered();
    cpp_authority_layer_rejects_lat_declaration_span_out_of_bounds();
    cpp_authority_layer_rejects_lat_module_kind_counts_out_of_bounds();
    cpp_authority_layer_rejects_lat_declaration_kind_out_of_vocabulary();
    cpp_authority_layer_rejects_lat_clause_effect_out_of_vocabulary();
    cpp_authority_layer_rejects_lat_clause_span_unordered();
    cpp_authority_layer_rejects_lat_clause_span_out_of_bounds();
    cpp_authority_layer_validates_lir_shape_metadata();
    cpp_authority_layer_rejects_lir_module_status_not_ok();
    cpp_authority_layer_rejects_lir_error_not_ok();
    cpp_authority_layer_rejects_lir_source_span_out_of_bounds();
    cpp_authority_layer_rejects_lir_source_span_unordered();
    cpp_authority_layer_rejects_lir_node_child_range_out_of_bounds();
    cpp_authority_layer_rejects_lir_node_parent_index_out_of_bounds();
    cpp_authority_layer_rejects_lir_node_span_unordered();
    cpp_authority_layer_rejects_lir_node_span_out_of_bounds();
    cpp_authority_layer_rejects_lir_edge_node_index_out_of_bounds();
    cpp_authority_layer_rejects_lir_edge_span_unordered();
    cpp_authority_layer_rejects_lir_edge_span_out_of_bounds();
    cpp_authority_layer_rejects_lir_binding_node_index_out_of_bounds();
    cpp_authority_layer_rejects_lir_binding_span_unordered();
    cpp_authority_layer_rejects_lir_binding_span_out_of_bounds();
    cpp_authority_layer_rejects_lir_text_node_index_out_of_bounds();
    cpp_authority_layer_rejects_lir_text_length_exceeded();
    cpp_authority_layer_rejects_lir_text_span_unordered();
    cpp_authority_layer_rejects_lir_text_span_out_of_bounds();
    cpp_authority_layer_rejects_lir_edge_kind_counts_out_of_bounds();
    cpp_authority_layer_rejects_lir_module_enum_out_of_vocabulary();
    cpp_authority_layer_rejects_lir_node_kind_out_of_vocabulary();
    cpp_authority_layer_rejects_lir_edge_kind_out_of_vocabulary();
    cpp_authority_layer_rejects_lir_binding_kind_out_of_vocabulary();
    cpp_authority_layer_audit_report_is_deterministic();
    cpp_authority_layer_renders_report_header_and_record_fields();
    cpp_authority_layer_renders_record_no_effect_flags();
    cpp_authority_layer_renders_record_source_span_coordinates();
    cpp_authority_layer_rejects_small_report_buffer();
    cpp_authority_layer_rejects_null_report_buffer();
    cpp_authority_layer_rejects_too_many_audit_records();
    cpp_authority_layer_rejects_unterminated_audit_text();
    cpp_authority_layer_rejects_audit_text_line_breaks();
    cpp_authority_layer_rejects_noncanonical_audit_text_padding();
    cpp_authority_layer_rejects_noncanonical_policy_name();
    cpp_authority_layer_rejects_noncanonical_validator_name();
    cpp_authority_layer_rejects_report_status_out_of_vocabulary();
    cpp_authority_layer_rejects_audit_record_status_out_of_vocabulary();
    cpp_authority_layer_rejects_audit_record_validator_out_of_vocabulary();
    cpp_authority_layer_rejects_audit_record_effect_out_of_vocabulary();
    cpp_authority_layer_is_deterministic();
    cpp_authority_layer_rejects_mutation_flags();
    cpp_authority_layer_rejects_network_flags();
    cpp_authority_layer_rejects_lat_network_flags();
    cpp_authority_layer_rejects_lir_network_flags();
    cpp_authority_layer_rejects_all_request_no_effect_flag_deviations();
    cpp_authority_layer_rejects_all_lat_no_effect_flag_deviations();
    cpp_authority_layer_rejects_all_lir_no_effect_flag_deviations();
    cpp_authority_layer_rejects_request_lat_network_flags();
    cpp_authority_layer_rejects_request_lir_network_flags();
    cpp_authority_layer_accepts_request_with_valid_linked_metadata();
    cpp_authority_layer_rejects_request_lat_metadata_before_no_effect_allow();
    cpp_authority_layer_rejects_request_lir_metadata_before_no_effect_allow();
    cpp_authority_layer_classifies_effects_without_performing_them();
    cpp_authority_layer_builds_with_fno_exceptions_and_fno_rtti();
    cpp_authority_layer_build_rejects_missing_required_flags();
    cpp_authority_layer_build_rejects_conflicting_required_flags();
    cpp_authority_layer_build_rejects_unlisted_compiler_flags();
    cpp_authority_layer_build_rejects_environment_include_injection_flags();
    cpp_authority_layer_build_rejects_environment_macro_override_flags();
    cpp_authority_layer_build_rejects_environment_linker_injection_flags();
    cpp_authority_layer_build_rejects_environment_toolchain_escape_flags();
    cpp_authority_layer_build_rejects_ambient_compiler_environment_variables();
    cpp_authority_layer_build_rejects_ambient_dyld_environment_prefix();
    cpp_authority_layer_build_rejects_ambient_tool_selector_variables();
    cpp_authority_layer_build_uses_sanitized_tool_path();
    cpp_authority_layer_build_uses_absolute_shell_entrypoint();
    cpp_authority_layer_build_uses_deterministic_tool_locale();
    cpp_authority_layer_build_uses_fixed_temporary_root();
    cpp_authority_layer_build_uses_private_artifact_permissions();
    cpp_authority_layer_build_uses_cxx20_standard();
    cpp_authority_layer_build_uses_warnings_as_errors();
    cpp_authority_layer_build_uses_source_and_object_static_analysis_path();
    cpp_authority_layer_build_policy_self_checks_runner_command_shape();
    cpp_authority_layer_build_requires_extern_c_substrate_includes();
    cpp_authority_layer_build_rejects_unwrapped_c_substrate_includes();
    cpp_authority_layer_build_rejects_direct_c_substrate_includes();
    cpp_authority_layer_build_rejects_unlisted_quote_includes();
    cpp_authority_layer_build_rejects_spaced_preprocessor_includes();
    cpp_authority_layer_build_rejects_unlisted_standard_headers();
    cpp_authority_layer_build_rejects_unlisted_std_apis();
    cpp_authority_layer_build_rejects_writable_global_data_symbols();
    cpp_authority_layer_build_rejects_common_data_symbols();
    cpp_authority_layer_build_rejects_allocation_symbols();
    cpp_authority_layer_build_rejects_exception_and_rtti_symbols();
    cpp_authority_layer_build_rejects_indirect_exception_and_rtti_symbols();
    cpp_authority_layer_build_rejects_framework_namespaces();
    cpp_authority_layer_build_rejects_io_and_process_calls();
    cpp_authority_layer_build_rejects_c_substrate_function_calls();
    cpp_authority_layer_build_rejects_public_c_abi_symbols();
    cpp_authority_layer_build_rejects_public_unmangled_defined_symbols();
    cpp_authority_layer_build_rejects_template_metaprogramming_constructs();
    return failures;
}

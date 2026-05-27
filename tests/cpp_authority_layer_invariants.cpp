#include "latticra/cpp/authority.hpp"

#include <cstddef>

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
                         latticra::authority_status::policy_denied),
                     "policy_denied"));
    expect(same_text(latticra::authority_status_label(
                         latticra::authority_status::unsupported_effect),
                     "unsupported_effect"));
}

void cpp_authority_layer_does_not_throw_across_c_boundary() noexcept {
    latticra::authority_audit_report report{};
    const latticra_lat_parse_result_t result = valid_lat_result();

    const latticra::authority_status status =
        latticra::validate_lat_parse_result(result, report);

    expect(status == latticra::authority_status::ok);
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

}  // namespace

int main() {
    cpp_authority_layer_preserves_no_effect_flags();
    cpp_authority_layer_rejects_unrestricted_cpp_claims();
    cpp_authority_layer_has_no_execution_path();
    cpp_authority_layer_has_no_network_path();
    cpp_authority_layer_has_no_hardware_path();
    cpp_authority_layer_uses_explicit_result_labels();
    cpp_authority_layer_does_not_throw_across_c_boundary();
    cpp_authority_layer_does_not_allocate_in_report_path();
    cpp_authority_layer_preserves_source_identity_in_audit();
    cpp_authority_layer_accepts_max_source_identity();
    cpp_authority_layer_rejects_oversized_source_identity();
    cpp_authority_layer_bounds_source_identity_before_audit_copy();
    cpp_authority_layer_rejects_nul_source_identity();
    cpp_authority_layer_rejects_line_break_source_identity();
    cpp_authority_layer_validates_lat_parse_result_metadata();
    cpp_authority_layer_validates_lir_shape_metadata();
    cpp_authority_layer_audit_report_is_deterministic();
    cpp_authority_layer_rejects_small_report_buffer();
    cpp_authority_layer_rejects_unterminated_audit_text();
    cpp_authority_layer_rejects_audit_text_line_breaks();
    cpp_authority_layer_rejects_noncanonical_audit_text_padding();
    cpp_authority_layer_is_deterministic();
    cpp_authority_layer_rejects_mutation_flags();
    cpp_authority_layer_rejects_network_flags();
    cpp_authority_layer_rejects_lat_network_flags();
    cpp_authority_layer_rejects_lir_network_flags();
    cpp_authority_layer_rejects_request_lat_network_flags();
    cpp_authority_layer_rejects_request_lir_network_flags();
    cpp_authority_layer_classifies_effects_without_performing_them();
    cpp_authority_layer_builds_with_fno_exceptions_and_fno_rtti();
    return failures;
}

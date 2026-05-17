#include "latticra/cpp/authority.hpp"

namespace latticra {
namespace {

constexpr authority_flags no_effect_flags() noexcept {
    return authority_flags{};
}

constexpr bool flags_are_no_effect(const authority_flags flags) noexcept {
    return flags.no_effect && !flags.execution_allowed && !flags.mutation_allowed &&
           !flags.server_allowed && !flags.recovery_allowed &&
           !flags.hardware_allowed;
}

constexpr authority_flags flags_from_lat(
    const latticra_lat_parse_result_t &result) noexcept {
    return authority_flags{result.no_effect != 0,
                           result.execution_allowed != 0,
                           result.mutation_allowed != 0,
                           result.server_allowed != 0,
                           result.recovery_allowed != 0,
                           result.hardware_allowed != 0};
}

constexpr authority_flags flags_from_lir(
    const latticra_lir_module_t &module) noexcept {
    return authority_flags{module.no_effect != 0,
                           module.execution_allowed != 0,
                           module.mutation_allowed != 0,
                           module.server_allowed != 0,
                           module.recovery_allowed != 0,
                           module.hardware_allowed != 0};
}

constexpr authority_effect effect_from_lat(
    const latticra_lat_effect_t effect) noexcept {
    switch (effect) {
    case LATTICRA_LAT_EFFECT_NONE:
        return authority_effect::none;
    case LATTICRA_LAT_EFFECT_READ:
        return authority_effect::read;
    case LATTICRA_LAT_EFFECT_LOCAL_MUTATION:
        return authority_effect::local_mutation;
    case LATTICRA_LAT_EFFECT_HOST_MUTATION:
        return authority_effect::host_mutation;
    case LATTICRA_LAT_EFFECT_NETWORK:
        return authority_effect::network;
    case LATTICRA_LAT_EFFECT_HARDWARE:
        return authority_effect::hardware;
    case LATTICRA_LAT_EFFECT_BOOT:
        return authority_effect::boot;
    case LATTICRA_LAT_EFFECT_RECOVERY:
        return authority_effect::recovery;
    case LATTICRA_LAT_EFFECT_EXTERNAL:
        return authority_effect::external;
    case LATTICRA_LAT_EFFECT_UNKNOWN:
        return authority_effect::unknown;
    }
    return authority_effect::unknown;
}

constexpr authority_source_span span_from_lat(
    const latticra_lat_source_span_t span) noexcept {
    return authority_source_span{span.start_offset,
                                 span.end_offset,
                                 span.start_line,
                                 span.start_column,
                                 span.end_line,
                                 span.end_column};
}

constexpr authority_source_span span_from_l_ui(
    const latticra_l_ui_source_span_t span) noexcept {
    return authority_source_span{span.start_offset,
                                 span.end_offset,
                                 span.start_line,
                                 span.start_column,
                                 span.end_line,
                                 span.end_column};
}

constexpr bool span_is_ordered(const authority_source_span span) noexcept {
    if (span.start_offset > span.end_offset) {
        return false;
    }
    if (span.start_line > span.end_line) {
        return false;
    }
    if (span.start_line == span.end_line &&
        span.start_column > span.end_column) {
        return false;
    }
    return true;
}

template <std::size_t Size>
void clear_array(std::array<char, Size> &target) noexcept {
    for (std::size_t index = 0u; index < Size; ++index) {
        target[index] = '\0';
    }
}

template <std::size_t Size>
bool copy_c_string(std::array<char, Size> &target, const char *source) noexcept {
    clear_array(target);
    if (source == nullptr) {
        return true;
    }

    std::size_t index = 0u;
    while (source[index] != '\0') {
        if (index + 1u >= Size) {
            clear_array(target);
            return false;
        }
        target[index] = source[index];
        ++index;
    }
    return true;
}

void reset_report(authority_audit_report &report) noexcept {
    report = authority_audit_report{};
    report.status = authority_status::ok;
    report.flags = no_effect_flags();
    report.record_count = 0u;
}

authority_status add_record(authority_audit_report &report,
                            const authority_status status,
                            const authority_validator validator,
                            const authority_effect requested_effect,
                            const char *reason,
                            const authority_source_span span) noexcept {
    if (report.record_count >= LATTICRA_AUTHORITY_AUDIT_RECORD_MAX) {
        report.status = authority_status::capacity_exceeded;
        return authority_status::capacity_exceeded;
    }

    authority_audit_record &record = report.records[report.record_count];
    record = authority_audit_record{};
    record.status = status;
    record.validator = validator;
    record.requested_effect = requested_effect;
    record.flags = report.flags;
    record.span = span;

    if (!copy_c_string(record.policy_name, "cpp_authority")) {
        report.status = authority_status::capacity_exceeded;
        return authority_status::capacity_exceeded;
    }
    if (!copy_c_string(record.validator_name,
                       authority_validator_label(validator))) {
        report.status = authority_status::capacity_exceeded;
        return authority_status::capacity_exceeded;
    }
    if (!copy_c_string(record.denial_reason, reason)) {
        report.status = authority_status::capacity_exceeded;
        return authority_status::capacity_exceeded;
    }

    ++report.record_count;
    if (status != authority_status::ok) {
        report.status = status;
    }
    return status;
}

bool append_char(char *buffer,
                 const std::size_t buffer_len,
                 std::size_t &offset,
                 const char value) noexcept {
    if (buffer == nullptr || buffer_len == 0u || offset + 1u >= buffer_len) {
        return false;
    }
    buffer[offset] = value;
    ++offset;
    buffer[offset] = '\0';
    return true;
}

bool append_c_string(char *buffer,
                     const std::size_t buffer_len,
                     std::size_t &offset,
                     const char *value) noexcept {
    if (value == nullptr) {
        return true;
    }
    std::size_t index = 0u;
    while (value[index] != '\0') {
        if (!append_char(buffer, buffer_len, offset, value[index])) {
            return false;
        }
        ++index;
    }
    return true;
}

bool append_size(char *buffer,
                 const std::size_t buffer_len,
                 std::size_t &offset,
                 std::size_t value) noexcept {
    char digits[32]{};
    std::size_t digit_count = 0u;

    if (value == 0u) {
        digits[digit_count] = '0';
        ++digit_count;
    } else {
        while (value != 0u && digit_count < 32u) {
            const std::size_t digit = value % 10u;
            digits[digit_count] = static_cast<char>('0' + digit);
            value = value / 10u;
            ++digit_count;
        }
    }

    while (digit_count > 0u) {
        --digit_count;
        if (!append_char(buffer, buffer_len, offset, digits[digit_count])) {
            return false;
        }
    }
    return true;
}

bool append_bool(char *buffer,
                 const std::size_t buffer_len,
                 std::size_t &offset,
                 const bool value) noexcept {
    return append_char(buffer, buffer_len, offset, value ? '1' : '0');
}

bool append_record_line_prefix(char *buffer,
                               const std::size_t buffer_len,
                               std::size_t &offset,
                               const std::size_t record_index,
                               const char *field) noexcept {
    return append_c_string(buffer, buffer_len, offset, "record[") &&
           append_size(buffer, buffer_len, offset, record_index) &&
           append_c_string(buffer, buffer_len, offset, "].") &&
           append_c_string(buffer, buffer_len, offset, field) &&
           append_char(buffer, buffer_len, offset, '=');
}

void clear_output(char *buffer, const std::size_t buffer_len) noexcept {
    if (buffer != nullptr && buffer_len > 0u) {
        buffer[0] = '\0';
    }
}

}  // namespace

const char *authority_status_label(const authority_status status) noexcept {
    switch (status) {
    case authority_status::ok:
        return "ok";
    case authority_status::null_argument:
        return "null_argument";
    case authority_status::invalid_input:
        return "invalid_input";
    case authority_status::capacity_exceeded:
        return "capacity_exceeded";
    case authority_status::policy_denied:
        return "policy_denied";
    case authority_status::unsupported_effect:
        return "unsupported_effect";
    case authority_status::unsupported_boundary:
        return "unsupported_boundary";
    case authority_status::not_authorized:
        return "not_authorized";
    case authority_status::internal_error:
        return "internal_error";
    }
    return "internal_error";
}

const char *authority_effect_label(const authority_effect effect) noexcept {
    switch (effect) {
    case authority_effect::none:
        return "none";
    case authority_effect::read:
        return "read";
    case authority_effect::local_mutation:
        return "local_mutation";
    case authority_effect::host_mutation:
        return "host_mutation";
    case authority_effect::network:
        return "network";
    case authority_effect::hardware:
        return "hardware";
    case authority_effect::boot:
        return "boot";
    case authority_effect::recovery:
        return "recovery";
    case authority_effect::external:
        return "external";
    case authority_effect::unknown:
        return "unknown";
    }
    return "unknown";
}

const char *authority_validator_label(const authority_validator validator) noexcept {
    switch (validator) {
    case authority_validator::naming:
        return "naming";
    case authority_validator::source_span:
        return "source_span";
    case authority_validator::no_effect:
        return "no_effect";
    case authority_validator::effect:
        return "effect";
    case authority_validator::boundary:
        return "boundary";
    case authority_validator::state_shape:
        return "state_shape";
    case authority_validator::lir_shape:
        return "lir_shape";
    case authority_validator::lat_parse_result:
        return "lat_parse_result";
    }
    return "no_effect";
}

authority_status validate_lat_parse_result(
    const latticra_lat_parse_result_t &lat_result,
    authority_audit_report &report) noexcept {
    reset_report(report);
    report.flags = flags_from_lat(lat_result);

    if (lat_result.status != LATTICRA_STATUS_OK ||
        lat_result.error != LATTICRA_LAT_PARSE_OK) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::lat_parse_result,
                          authority_effect::none,
                          "lat_parse_result_not_ok",
                          span_from_lat(lat_result.span));
    }

    if (!flags_are_no_effect(report.flags)) {
        return add_record(report,
                          authority_status::policy_denied,
                          authority_validator::no_effect,
                          authority_effect::none,
                          "lat_no_effect_flags_not_preserved",
                          span_from_lat(lat_result.span));
    }

    if (lat_result.declaration_count > LATTICRA_LAT_DECLARATION_MAX ||
        lat_result.clause_count > LATTICRA_LAT_CLAUSE_MAX ||
        lat_result.module.declaration_count > LATTICRA_LAT_DECLARATION_MAX) {
        return add_record(report,
                          authority_status::capacity_exceeded,
                          authority_validator::lat_parse_result,
                          authority_effect::none,
                          "lat_capacity_exceeded",
                          span_from_lat(lat_result.span));
    }

    if (!span_is_ordered(span_from_lat(lat_result.span)) ||
        !span_is_ordered(span_from_lat(lat_result.module.span))) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::source_span,
                          authority_effect::none,
                          "lat_source_span_unordered",
                          span_from_lat(lat_result.span));
    }

    for (std::size_t index = 0u; index < lat_result.declaration_count; ++index) {
        if (!span_is_ordered(span_from_lat(lat_result.declarations[index].span))) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lat_declaration_span_unordered",
                              span_from_lat(lat_result.declarations[index].span));
        }
    }

    for (std::size_t index = 0u; index < lat_result.clause_count; ++index) {
        const authority_effect effect = effect_from_lat(lat_result.clauses[index].effect);
        if (!span_is_ordered(span_from_lat(lat_result.clauses[index].span))) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              effect,
                              "lat_clause_span_unordered",
                              span_from_lat(lat_result.clauses[index].span));
        }
    }

    return add_record(report,
                      authority_status::ok,
                      authority_validator::lat_parse_result,
                      authority_effect::none,
                      "none",
                      span_from_lat(lat_result.span));
}

authority_status validate_lir_shape(const latticra_lir_module_t &lir_module,
                                    authority_audit_report &report) noexcept {
    reset_report(report);
    report.flags = flags_from_lir(lir_module);

    if (lir_module.status != LATTICRA_STATUS_OK ||
        lir_module.error != LATTICRA_LIR_OK) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::lir_shape,
                          authority_effect::none,
                          "lir_shape_not_ok",
                          span_from_l_ui(lir_module.source_span));
    }

    if (!flags_are_no_effect(report.flags)) {
        return add_record(report,
                          authority_status::policy_denied,
                          authority_validator::no_effect,
                          authority_effect::none,
                          "lir_no_effect_flags_not_preserved",
                          span_from_l_ui(lir_module.source_span));
    }

    if (lir_module.node_count > LATTICRA_LIR_NODE_MAX ||
        lir_module.edge_count > LATTICRA_LIR_EDGE_MAX ||
        lir_module.binding_count > LATTICRA_LIR_BINDING_REF_MAX ||
        lir_module.text_count > LATTICRA_LIR_TEXT_MAX) {
        return add_record(report,
                          authority_status::capacity_exceeded,
                          authority_validator::lir_shape,
                          authority_effect::none,
                          "lir_capacity_exceeded",
                          span_from_l_ui(lir_module.source_span));
    }

    if (!span_is_ordered(span_from_l_ui(lir_module.source_span))) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::source_span,
                          authority_effect::none,
                          "lir_source_span_unordered",
                          span_from_l_ui(lir_module.source_span));
    }

    for (std::size_t index = 0u; index < lir_module.node_count; ++index) {
        if (!span_is_ordered(span_from_l_ui(lir_module.nodes[index].source_span))) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_node_span_unordered",
                              span_from_l_ui(lir_module.nodes[index].source_span));
        }
    }

    for (std::size_t index = 0u; index < lir_module.edge_count; ++index) {
        if (!span_is_ordered(span_from_l_ui(lir_module.edges[index].source_span))) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_edge_span_unordered",
                              span_from_l_ui(lir_module.edges[index].source_span));
        }
    }

    for (std::size_t index = 0u; index < lir_module.binding_count; ++index) {
        if (!span_is_ordered(span_from_l_ui(lir_module.bindings[index].source_span))) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_binding_span_unordered",
                              span_from_l_ui(lir_module.bindings[index].source_span));
        }
    }

    for (std::size_t index = 0u; index < lir_module.text_count; ++index) {
        if (lir_module.texts[index].value_len > LATTICRA_LIR_VALUE_MAX) {
            return add_record(report,
                              authority_status::capacity_exceeded,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_text_length_exceeded",
                              span_from_l_ui(lir_module.texts[index].source_span));
        }
        if (!span_is_ordered(span_from_l_ui(lir_module.texts[index].source_span))) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_text_span_unordered",
                              span_from_l_ui(lir_module.texts[index].source_span));
        }
    }

    return add_record(report,
                      authority_status::ok,
                      authority_validator::lir_shape,
                      authority_effect::none,
                      "none",
                      span_from_l_ui(lir_module.source_span));
}

authority_status classify_effect_request(const authority_request &request,
                                          authority_audit_report &report) noexcept {
    reset_report(report);
    report.flags = request.flags;

    if (!flags_are_no_effect(report.flags)) {
        return add_record(report,
                          authority_status::policy_denied,
                          authority_validator::no_effect,
                          request.requested_effect,
                          "non_no_effect_flags_denied",
                          authority_source_span{});
    }

    if (request.source_identity.size() > LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX) {
        return add_record(report,
                          authority_status::capacity_exceeded,
                          authority_validator::boundary,
                          request.requested_effect,
                          "source_identity_too_large",
                          authority_source_span{});
    }

    if (request.requested_effect == authority_effect::none) {
        return add_record(report,
                          authority_status::ok,
                          authority_validator::effect,
                          request.requested_effect,
                          "none",
                          authority_source_span{});
    }

    if (request.requested_effect == authority_effect::unknown) {
        return add_record(report,
                          authority_status::unsupported_effect,
                          authority_validator::effect,
                          request.requested_effect,
                          "unsupported_effect",
                          authority_source_span{});
    }

    return add_record(report,
                      authority_status::policy_denied,
                      authority_validator::effect,
                      request.requested_effect,
                      "effect_performance_denied",
                      authority_source_span{});
}

authority_status render_authority_audit_report(
    const authority_audit_report &report,
    char *buffer,
    const std::size_t buffer_len) noexcept {
    if (buffer == nullptr) {
        return authority_status::null_argument;
    }
    if (buffer_len == 0u) {
        return authority_status::capacity_exceeded;
    }

    clear_output(buffer, buffer_len);
    std::size_t offset = 0u;

    const bool ok =
        append_c_string(buffer, buffer_len, offset, "CPP AUTHORITY REPORT\n") &&
        append_c_string(buffer, buffer_len, offset, "status=") &&
        append_c_string(buffer, buffer_len, offset,
                        authority_status_label(report.status)) &&
        append_char(buffer, buffer_len, offset, '\n') &&
        append_c_string(buffer, buffer_len, offset, "record_count=") &&
        append_size(buffer, buffer_len, offset, report.record_count) &&
        append_char(buffer, buffer_len, offset, '\n') &&
        append_c_string(buffer, buffer_len, offset, "no_effect=") &&
        append_bool(buffer, buffer_len, offset, report.flags.no_effect) &&
        append_char(buffer, buffer_len, offset, '\n') &&
        append_c_string(buffer, buffer_len, offset, "execution_allowed=") &&
        append_bool(buffer, buffer_len, offset, report.flags.execution_allowed) &&
        append_char(buffer, buffer_len, offset, '\n') &&
        append_c_string(buffer, buffer_len, offset, "mutation_allowed=") &&
        append_bool(buffer, buffer_len, offset, report.flags.mutation_allowed) &&
        append_char(buffer, buffer_len, offset, '\n') &&
        append_c_string(buffer, buffer_len, offset, "server_allowed=") &&
        append_bool(buffer, buffer_len, offset, report.flags.server_allowed) &&
        append_char(buffer, buffer_len, offset, '\n') &&
        append_c_string(buffer, buffer_len, offset, "recovery_allowed=") &&
        append_bool(buffer, buffer_len, offset, report.flags.recovery_allowed) &&
        append_char(buffer, buffer_len, offset, '\n') &&
        append_c_string(buffer, buffer_len, offset, "hardware_allowed=") &&
        append_bool(buffer, buffer_len, offset, report.flags.hardware_allowed) &&
        append_char(buffer, buffer_len, offset, '\n');

    if (!ok) {
        clear_output(buffer, buffer_len);
        return authority_status::capacity_exceeded;
    }

    for (std::size_t index = 0u; index < report.record_count; ++index) {
        const authority_audit_record &record = report.records[index];
        const bool record_ok =
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "policy") &&
            append_c_string(buffer, buffer_len, offset,
                            record.policy_name.data()) &&
            append_char(buffer, buffer_len, offset, '\n') &&
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "validator") &&
            append_c_string(buffer, buffer_len, offset,
                            authority_validator_label(record.validator)) &&
            append_char(buffer, buffer_len, offset, '\n') &&
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "requested_effect") &&
            append_c_string(buffer, buffer_len, offset,
                            authority_effect_label(record.requested_effect)) &&
            append_char(buffer, buffer_len, offset, '\n') &&
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "result") &&
            append_c_string(buffer, buffer_len, offset,
                            authority_status_label(record.status)) &&
            append_char(buffer, buffer_len, offset, '\n') &&
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "denial_reason") &&
            append_c_string(buffer, buffer_len, offset,
                            record.denial_reason.data()) &&
            append_char(buffer, buffer_len, offset, '\n') &&
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "span_start_offset") &&
            append_size(buffer, buffer_len, offset, record.span.start_offset) &&
            append_char(buffer, buffer_len, offset, '\n') &&
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "span_end_offset") &&
            append_size(buffer, buffer_len, offset, record.span.end_offset) &&
            append_char(buffer, buffer_len, offset, '\n');

        if (!record_ok) {
            clear_output(buffer, buffer_len);
            return authority_status::capacity_exceeded;
        }
    }

    return authority_status::ok;
}

}  // namespace latticra

#include "latticra/cpp/authority.hpp"

namespace latticra {
namespace {

constexpr authority_flags no_effect_flags() noexcept {
    return authority_flags{};
}

constexpr bool flags_are_no_effect(const authority_flags flags) noexcept {
    return flags.no_effect && !flags.execution_allowed && !flags.mutation_allowed &&
           !flags.server_allowed && !flags.network_allowed && !flags.recovery_allowed &&
           !flags.hardware_allowed;
}

constexpr authority_flags flags_from_lat(
    const latticra_lat_parse_result_t &result) noexcept {
    return authority_flags{result.no_effect != 0,
                           result.execution_allowed != 0,
                           result.mutation_allowed != 0,
                           result.server_allowed != 0,
                           result.network_allowed != 0,
                           result.recovery_allowed != 0,
                           result.hardware_allowed != 0};
}

constexpr authority_flags flags_from_lir(
    const latticra_lir_module_t &module) noexcept {
    return authority_flags{module.no_effect != 0,
                           module.execution_allowed != 0,
                           module.mutation_allowed != 0,
                           module.server_allowed != 0,
                           module.network_allowed != 0,
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

constexpr bool authority_status_is_known(const authority_status status) noexcept {
    switch (status) {
    case authority_status::ok:
    case authority_status::null_argument:
    case authority_status::invalid_input:
    case authority_status::capacity_exceeded:
    case authority_status::policy_denied:
    case authority_status::unsupported_effect:
    case authority_status::unsupported_boundary:
    case authority_status::not_authorized:
    case authority_status::internal_error:
        return true;
    }
    return false;
}

constexpr bool authority_effect_is_known(const authority_effect effect) noexcept {
    switch (effect) {
    case authority_effect::none:
    case authority_effect::read:
    case authority_effect::local_mutation:
    case authority_effect::host_mutation:
    case authority_effect::network:
    case authority_effect::hardware:
    case authority_effect::boot:
    case authority_effect::recovery:
    case authority_effect::external:
    case authority_effect::unknown:
        return true;
    }
    return false;
}

constexpr authority_effect canonical_authority_effect(
    const authority_effect effect) noexcept {
    return authority_effect_is_known(effect) ? effect : authority_effect::unknown;
}

constexpr bool authority_validator_is_known(
    const authority_validator validator) noexcept {
    switch (validator) {
    case authority_validator::naming:
    case authority_validator::source_span:
    case authority_validator::no_effect:
    case authority_validator::effect:
    case authority_validator::boundary:
    case authority_validator::state_shape:
    case authority_validator::lir_shape:
    case authority_validator::lat_parse_result:
        return true;
    }
    return false;
}

constexpr bool lat_declaration_kind_is_known(
    const latticra_lat_declaration_kind_t kind) noexcept {
    switch (kind) {
    case LATTICRA_LAT_DECLARATION_STATE:
    case LATTICRA_LAT_DECLARATION_POLICY:
    case LATTICRA_LAT_DECLARATION_TRANSITION:
    case LATTICRA_LAT_DECLARATION_ASSERTION:
    case LATTICRA_LAT_DECLARATION_EFFECT:
    case LATTICRA_LAT_DECLARATION_UNKNOWN:
        return true;
    }
    return false;
}

constexpr bool lat_effect_is_known(const latticra_lat_effect_t effect) noexcept {
    switch (effect) {
    case LATTICRA_LAT_EFFECT_NONE:
    case LATTICRA_LAT_EFFECT_READ:
    case LATTICRA_LAT_EFFECT_LOCAL_MUTATION:
    case LATTICRA_LAT_EFFECT_HOST_MUTATION:
    case LATTICRA_LAT_EFFECT_NETWORK:
    case LATTICRA_LAT_EFFECT_HARDWARE:
    case LATTICRA_LAT_EFFECT_BOOT:
    case LATTICRA_LAT_EFFECT_RECOVERY:
    case LATTICRA_LAT_EFFECT_EXTERNAL:
    case LATTICRA_LAT_EFFECT_UNKNOWN:
        return true;
    }
    return false;
}

constexpr bool lir_source_kind_is_known(
    const latticra_lir_source_kind_t kind) noexcept {
    switch (kind) {
    case LATTICRA_LIR_SOURCE_UNKNOWN:
    case LATTICRA_LIR_SOURCE_L_UI_CARD:
    case LATTICRA_LIR_SOURCE_LAT_MODULE:
    case LATTICRA_LIR_SOURCE_INTERNAL_FIXTURE:
        return true;
    }
    return false;
}

constexpr bool lir_node_kind_is_known(
    const latticra_lir_node_kind_t kind) noexcept {
    switch (kind) {
    case LATTICRA_LIR_NODE_MODULE:
    case LATTICRA_LIR_NODE_CARD:
    case LATTICRA_LIR_NODE_RAIL:
    case LATTICRA_LIR_NODE_FIELD:
    case LATTICRA_LIR_NODE_TEXT:
    case LATTICRA_LIR_NODE_BINDING:
    case LATTICRA_LIR_NODE_EFFECT:
    case LATTICRA_LIR_NODE_BOUNDARY:
    case LATTICRA_LIR_NODE_UNKNOWN:
    case LATTICRA_LIR_NODE_LAT_STATE:
    case LATTICRA_LIR_NODE_LAT_POLICY:
    case LATTICRA_LIR_NODE_LAT_TRANSITION:
    case LATTICRA_LIR_NODE_LAT_ASSERTION:
    case LATTICRA_LIR_NODE_LAT_REQUIREMENT:
    case LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION:
        return true;
    }
    return false;
}

constexpr bool lir_edge_kind_is_known(
    const latticra_lir_edge_kind_t kind) noexcept {
    switch (kind) {
    case LATTICRA_LIR_EDGE_CONTAINS:
    case LATTICRA_LIR_EDGE_BINDS:
    case LATTICRA_LIR_EDGE_ANNOTATES:
    case LATTICRA_LIR_EDGE_ORDERS_BEFORE:
    case LATTICRA_LIR_EDGE_UNKNOWN:
    case LATTICRA_LIR_EDGE_TRANSITIONS_FROM:
        return true;
    }
    return false;
}

constexpr bool lir_binding_kind_is_known(
    const latticra_lir_resolved_binding_kind_t kind) noexcept {
    switch (kind) {
    case LATTICRA_LIR_BINDING_STATE_VALUE:
    case LATTICRA_LIR_BINDING_PREVIEW_VALUE:
    case LATTICRA_LIR_BINDING_UNSUPPORTED:
        return true;
    }
    return false;
}

constexpr bool lir_report_classification_is_known(
    const latticra_lir_report_classification_t classification) noexcept {
    switch (classification) {
    case LATTICRA_LIR_REPORT_EMPTY:
    case LATTICRA_LIR_REPORT_MATERIALIZED:
    case LATTICRA_LIR_REPORT_REJECTED:
    case LATTICRA_LIR_REPORT_INVALID:
        return true;
    }
    return false;
}

constexpr bool lir_shape_kind_is_known(
    const latticra_lir_shape_kind_t kind) noexcept {
    switch (kind) {
    case LATTICRA_LIR_SHAPE_UNKNOWN:
    case LATTICRA_LIR_SHAPE_L_UI_CARD_GRAPH:
    case LATTICRA_LIR_SHAPE_LAT_MODULE_GRAPH:
    case LATTICRA_LIR_SHAPE_INTERNAL_FIXTURE_GRAPH:
        return true;
    }
    return false;
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

constexpr bool span_offsets_are_bounded(const authority_source_span span,
                                        const std::size_t source_max) noexcept {
    return span.start_offset <= source_max && span.end_offset <= source_max;
}

constexpr bool index_is_bounded(const std::size_t index,
                                const std::size_t count) noexcept {
    return index < count;
}

constexpr bool range_is_bounded(const std::size_t first,
                                const std::size_t count,
                                const std::size_t total) noexcept {
    if (first > total) {
        return false;
    }
    if (count == 0u) {
        return true;
    }
    return count <= total - first;
}

constexpr bool sum_would_exceed(const std::size_t left,
                                const std::size_t right,
                                const std::size_t limit) noexcept {
    return left > limit || right > limit - left;
}

constexpr bool lat_module_kind_counts_are_bounded(
    const latticra_lat_ast_module_t &module,
    const std::size_t declaration_count) noexcept {
    std::size_t total = 0u;
    if (sum_would_exceed(total, module.state_count, declaration_count)) {
        return false;
    }
    total += module.state_count;
    if (sum_would_exceed(total, module.policy_count, declaration_count)) {
        return false;
    }
    total += module.policy_count;
    if (sum_would_exceed(total, module.transition_count, declaration_count)) {
        return false;
    }
    total += module.transition_count;
    if (sum_would_exceed(total, module.assertion_count, declaration_count)) {
        return false;
    }
    total += module.assertion_count;
    if (sum_would_exceed(total, module.effect_count, declaration_count)) {
        return false;
    }
    return true;
}

constexpr bool lir_edge_kind_counts_are_bounded(
    const latticra_lir_module_t &module) noexcept {
    std::size_t total = 0u;
    if (sum_would_exceed(total, module.contains_edge_count, module.edge_count)) {
        return false;
    }
    total += module.contains_edge_count;
    if (sum_would_exceed(total, module.binds_edge_count, module.edge_count)) {
        return false;
    }
    total += module.binds_edge_count;
    if (sum_would_exceed(total, module.annotates_edge_count, module.edge_count)) {
        return false;
    }
    total += module.annotates_edge_count;
    if (sum_would_exceed(total, module.orders_before_edge_count,
                         module.edge_count)) {
        return false;
    }
    total += module.orders_before_edge_count;
    if (sum_would_exceed(total, module.transitions_from_edge_count,
                         module.edge_count)) {
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

template <std::size_t Size>
bool copy_string_view(std::array<char, Size> &target,
                      const std::string_view source) noexcept {
    clear_array(target);
    if (source.size() >= Size) {
        return false;
    }

    for (std::size_t index = 0u; index < source.size(); ++index) {
        target[index] = source[index];
    }
    return true;
}

bool string_view_contains_nul(const std::string_view source) noexcept {
    for (std::size_t index = 0u; index < source.size(); ++index) {
        if (source[index] == '\0') {
            return true;
        }
    }
    return false;
}

bool string_view_contains_line_break(const std::string_view source) noexcept {
    for (std::size_t index = 0u; index < source.size(); ++index) {
        if (source[index] == '\n' || source[index] == '\r') {
            return true;
        }
    }
    return false;
}

template <std::size_t Size>
bool char_array_is_terminated(const std::array<char, Size> &source) noexcept {
    for (std::size_t index = 0u; index < Size; ++index) {
        if (source[index] == '\0') {
            return true;
        }
    }
    return false;
}

template <std::size_t Size>
bool char_array_has_line_break_before_terminator(
    const std::array<char, Size> &source) noexcept {
    for (std::size_t index = 0u; index < Size; ++index) {
        if (source[index] == '\0') {
            return false;
        }
        if (source[index] == '\n' || source[index] == '\r') {
            return true;
        }
    }
    return false;
}

bool record_text_fields_are_terminated(
    const authority_audit_record &record) noexcept {
    return char_array_is_terminated(record.policy_name) &&
           char_array_is_terminated(record.source_identity) &&
           char_array_is_terminated(record.validator_name) &&
           char_array_is_terminated(record.denial_reason);
}

template <std::size_t Size>
bool char_array_is_nul_padded(const std::array<char, Size> &source) noexcept {
    bool found_terminator = false;
    for (std::size_t index = 0u; index < Size; ++index) {
        if (found_terminator && source[index] != '\0') {
            return false;
        }
        if (source[index] == '\0') {
            found_terminator = true;
        }
    }
    return found_terminator;
}

template <std::size_t Size>
bool char_array_matches_c_string(const std::array<char, Size> &source,
                                 const char *expected) noexcept {
    if (expected == nullptr) {
        return false;
    }

    std::size_t index = 0u;
    while (expected[index] != '\0') {
        if (index >= Size || source[index] != expected[index]) {
            return false;
        }
        ++index;
    }
    return index < Size && source[index] == '\0';
}

bool record_text_fields_are_nul_padded(
    const authority_audit_record &record) noexcept {
    return char_array_is_nul_padded(record.policy_name) &&
           char_array_is_nul_padded(record.source_identity) &&
           char_array_is_nul_padded(record.validator_name) &&
           char_array_is_nul_padded(record.denial_reason);
}

bool record_text_fields_are_line_safe(
    const authority_audit_record &record) noexcept {
    return !char_array_has_line_break_before_terminator(record.policy_name) &&
           !char_array_has_line_break_before_terminator(record.source_identity) &&
           !char_array_has_line_break_before_terminator(record.validator_name) &&
           !char_array_has_line_break_before_terminator(record.denial_reason);
}

bool record_canonical_names_match(
    const authority_audit_record &record) noexcept {
    return char_array_matches_c_string(record.policy_name, "cpp_authority") &&
           char_array_matches_c_string(record.validator_name,
                                       authority_validator_label(record.validator));
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
                            const authority_source_span span,
                            const std::string_view source_identity = {}) noexcept {
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
    if (!copy_string_view(record.source_identity, source_identity)) {
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

bool append_record_bool_line(char *buffer,
                             const std::size_t buffer_len,
                             std::size_t &offset,
                             const std::size_t record_index,
                             const char *field,
                             const bool value) noexcept {
    return append_record_line_prefix(buffer, buffer_len, offset, record_index,
                                     field) &&
           append_bool(buffer, buffer_len, offset, value) &&
           append_char(buffer, buffer_len, offset, '\n');
}

bool append_record_size_line(char *buffer,
                             const std::size_t buffer_len,
                             std::size_t &offset,
                             const std::size_t record_index,
                             const char *field,
                             const std::size_t value) noexcept {
    return append_record_line_prefix(buffer, buffer_len, offset, record_index,
                                     field) &&
           append_size(buffer, buffer_len, offset, value) &&
           append_char(buffer, buffer_len, offset, '\n');
}

void clear_output(char *buffer, const std::size_t buffer_len) noexcept {
    if (buffer != nullptr && buffer_len > 0u) {
        buffer[0] = '\0';
    }
}

authority_status add_first_metadata_record(
    authority_audit_report &report,
    const authority_audit_report &metadata_report,
    const authority_effect requested_effect,
    const authority_validator fallback_validator,
    const char *fallback_reason,
    const std::string_view source_identity) noexcept {
    report.flags = metadata_report.flags;

    if (metadata_report.record_count == 0u) {
        return add_record(report,
                          metadata_report.status,
                          fallback_validator,
                          requested_effect,
                          fallback_reason,
                          authority_source_span{},
                          source_identity);
    }

    const authority_audit_record &record = metadata_report.records[0u];
    return add_record(report,
                      record.status,
                      record.validator,
                      requested_effect,
                      record.denial_reason.data(),
                      record.span,
                      source_identity);
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

    if (lat_result.module.declaration_count > lat_result.declaration_count) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::lat_parse_result,
                          authority_effect::none,
                          "lat_module_declaration_count_out_of_bounds",
                          span_from_lat(lat_result.module.span));
    }

    if (!lat_module_kind_counts_are_bounded(lat_result.module,
                                            lat_result.declaration_count)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::lat_parse_result,
                          authority_effect::none,
                          "lat_module_kind_counts_out_of_bounds",
                          span_from_lat(lat_result.module.span));
    }

    const authority_source_span result_span = span_from_lat(lat_result.span);
    const authority_source_span module_span = span_from_lat(lat_result.module.span);

    if (!span_is_ordered(result_span) || !span_is_ordered(module_span)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::source_span,
                          authority_effect::none,
                          "lat_source_span_unordered",
                          span_from_lat(lat_result.span));
    }

    if (!span_offsets_are_bounded(result_span, LATTICRA_LAT_SOURCE_MAX) ||
        !span_offsets_are_bounded(module_span, LATTICRA_LAT_SOURCE_MAX)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::source_span,
                          authority_effect::none,
                          "lat_source_span_out_of_bounds",
                          span_from_lat(lat_result.span));
    }

    for (std::size_t index = 0u; index < lat_result.declaration_count; ++index) {
        const authority_source_span declaration_span =
            span_from_lat(lat_result.declarations[index].span);
        if (!lat_declaration_kind_is_known(lat_result.declarations[index].kind)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lat_parse_result,
                              authority_effect::none,
                              "lat_declaration_kind_out_of_vocabulary",
                              declaration_span);
        }
        if (!span_is_ordered(declaration_span)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lat_declaration_span_unordered",
                              declaration_span);
        }
        if (!span_offsets_are_bounded(declaration_span, LATTICRA_LAT_SOURCE_MAX)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lat_declaration_span_out_of_bounds",
                              declaration_span);
        }
        if (!range_is_bounded(lat_result.declarations[index].first_clause_index,
                              lat_result.declarations[index].clause_count,
                              lat_result.clause_count)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lat_parse_result,
                              authority_effect::none,
                              "lat_declaration_clause_range_out_of_bounds",
                              declaration_span);
        }
    }

    for (std::size_t index = 0u; index < lat_result.clause_count; ++index) {
        const authority_source_span clause_span =
            span_from_lat(lat_result.clauses[index].span);
        if (!lat_effect_is_known(lat_result.clauses[index].effect)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lat_parse_result,
                              authority_effect::unknown,
                              "lat_clause_effect_out_of_vocabulary",
                              clause_span);
        }

        const authority_effect effect = effect_from_lat(lat_result.clauses[index].effect);
        if (!span_is_ordered(clause_span)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              effect,
                              "lat_clause_span_unordered",
                              clause_span);
        }
        if (!span_offsets_are_bounded(clause_span, LATTICRA_LAT_SOURCE_MAX)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              effect,
                              "lat_clause_span_out_of_bounds",
                              clause_span);
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

    if (!lir_source_kind_is_known(lir_module.source_kind) ||
        !lir_report_classification_is_known(lir_module.report_classification) ||
        !lir_shape_kind_is_known(lir_module.shape_kind)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::lir_shape,
                          authority_effect::none,
                          "lir_module_enum_out_of_vocabulary",
                          span_from_l_ui(lir_module.source_span));
    }

    if (!lir_edge_kind_counts_are_bounded(lir_module)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::lir_shape,
                          authority_effect::none,
                          "lir_edge_kind_counts_out_of_bounds",
                          span_from_l_ui(lir_module.source_span));
    }

    const authority_source_span module_span = span_from_l_ui(lir_module.source_span);

    if (!span_is_ordered(module_span)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::source_span,
                          authority_effect::none,
                          "lir_source_span_unordered",
                          module_span);
    }

    if (!span_offsets_are_bounded(module_span, LATTICRA_L_UI_SOURCE_MAX)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::source_span,
                          authority_effect::none,
                          "lir_source_span_out_of_bounds",
                          module_span);
    }

    for (std::size_t index = 0u; index < lir_module.node_count; ++index) {
        const authority_source_span node_span =
            span_from_l_ui(lir_module.nodes[index].source_span);
        if (!lir_node_kind_is_known(lir_module.nodes[index].kind)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_node_kind_out_of_vocabulary",
                              node_span);
        }
        if (!span_is_ordered(node_span)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_node_span_unordered",
                              node_span);
        }
        if (!span_offsets_are_bounded(node_span, LATTICRA_L_UI_SOURCE_MAX)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_node_span_out_of_bounds",
                              node_span);
        }
        if (!index_is_bounded(lir_module.nodes[index].parent_index,
                              lir_module.node_count)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_node_parent_index_out_of_bounds",
                              node_span);
        }
        if (!range_is_bounded(lir_module.nodes[index].first_child_index,
                              lir_module.nodes[index].child_count,
                              lir_module.node_count)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_node_child_range_out_of_bounds",
                              node_span);
        }
    }

    for (std::size_t index = 0u; index < lir_module.edge_count; ++index) {
        const authority_source_span edge_span =
            span_from_l_ui(lir_module.edges[index].source_span);
        if (!lir_edge_kind_is_known(lir_module.edges[index].edge_kind)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_edge_kind_out_of_vocabulary",
                              edge_span);
        }
        if (!span_is_ordered(edge_span)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_edge_span_unordered",
                              edge_span);
        }
        if (!span_offsets_are_bounded(edge_span, LATTICRA_L_UI_SOURCE_MAX)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_edge_span_out_of_bounds",
                              edge_span);
        }
        if (!index_is_bounded(lir_module.edges[index].from_index,
                              lir_module.node_count) ||
            !index_is_bounded(lir_module.edges[index].to_index,
                              lir_module.node_count)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_edge_node_index_out_of_bounds",
                              edge_span);
        }
    }

    for (std::size_t index = 0u; index < lir_module.binding_count; ++index) {
        const authority_source_span binding_span =
            span_from_l_ui(lir_module.bindings[index].source_span);
        if (!lir_binding_kind_is_known(lir_module.bindings[index].resolved_kind)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_binding_kind_out_of_vocabulary",
                              binding_span);
        }
        if (!span_is_ordered(binding_span)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_binding_span_unordered",
                              binding_span);
        }
        if (!span_offsets_are_bounded(binding_span, LATTICRA_L_UI_SOURCE_MAX)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_binding_span_out_of_bounds",
                              binding_span);
        }
        if (!index_is_bounded(lir_module.bindings[index].field_node_index,
                              lir_module.node_count)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_binding_node_index_out_of_bounds",
                              binding_span);
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
        const authority_source_span text_span =
            span_from_l_ui(lir_module.texts[index].source_span);
        if (!span_is_ordered(text_span)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_text_span_unordered",
                              text_span);
        }
        if (!span_offsets_are_bounded(text_span, LATTICRA_L_UI_SOURCE_MAX)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::source_span,
                              authority_effect::none,
                              "lir_text_span_out_of_bounds",
                              text_span);
        }
        if (!index_is_bounded(lir_module.texts[index].text_node_index,
                              lir_module.node_count)) {
            return add_record(report,
                              authority_status::invalid_input,
                              authority_validator::lir_shape,
                              authority_effect::none,
                              "lir_text_node_index_out_of_bounds",
                              text_span);
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

    if (request.source_identity.size() > LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX) {
        return add_record(report,
                          authority_status::capacity_exceeded,
                          authority_validator::boundary,
                          canonical_authority_effect(request.requested_effect),
                          "source_identity_too_large",
                          authority_source_span{});
    }

    if (string_view_contains_nul(request.source_identity)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::boundary,
                          canonical_authority_effect(request.requested_effect),
                          "source_identity_contains_nul",
                          authority_source_span{});
    }

    if (string_view_contains_line_break(request.source_identity)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::boundary,
                          canonical_authority_effect(request.requested_effect),
                          "source_identity_contains_line_break",
                          authority_source_span{});
    }

    if (!authority_effect_is_known(request.requested_effect)) {
        return add_record(report,
                          authority_status::invalid_input,
                          authority_validator::effect,
                          authority_effect::unknown,
                          "requested_effect_out_of_vocabulary",
                          authority_source_span{},
                          request.source_identity);
    }

    if (!flags_are_no_effect(report.flags)) {
        return add_record(report,
                          authority_status::policy_denied,
                          authority_validator::no_effect,
                          request.requested_effect,
                          "non_no_effect_flags_denied",
                          authority_source_span{},
                          request.source_identity);
    }

    if (request.lat_result != nullptr) {
        authority_audit_report metadata_report{};
        const authority_status metadata_status =
            validate_lat_parse_result(*request.lat_result, metadata_report);
        if (metadata_status != authority_status::ok) {
            return add_first_metadata_record(report,
                                             metadata_report,
                                             request.requested_effect,
                                             authority_validator::lat_parse_result,
                                             "lat_parse_result_not_ok",
                                             request.source_identity);
        }
    }

    if (request.lir_module != nullptr) {
        authority_audit_report metadata_report{};
        const authority_status metadata_status =
            validate_lir_shape(*request.lir_module, metadata_report);
        if (metadata_status != authority_status::ok) {
            return add_first_metadata_record(report,
                                             metadata_report,
                                             request.requested_effect,
                                             authority_validator::lir_shape,
                                             "lir_shape_not_ok",
                                             request.source_identity);
        }
    }

    if (request.requested_effect == authority_effect::none) {
        return add_record(report,
                          authority_status::ok,
                          authority_validator::effect,
                          request.requested_effect,
                          "none",
                          authority_source_span{},
                          request.source_identity);
    }

    if (request.requested_effect == authority_effect::unknown) {
        return add_record(report,
                          authority_status::unsupported_effect,
                          authority_validator::effect,
                          request.requested_effect,
                          "unsupported_effect",
                          authority_source_span{},
                          request.source_identity);
    }

    return add_record(report,
                      authority_status::policy_denied,
                      authority_validator::effect,
                      request.requested_effect,
                      "effect_performance_denied",
                      authority_source_span{},
                      request.source_identity);
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

    if (report.record_count > LATTICRA_AUTHORITY_AUDIT_RECORD_MAX) {
        return authority_status::capacity_exceeded;
    }

    if (!authority_status_is_known(report.status)) {
        return authority_status::invalid_input;
    }

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
        append_c_string(buffer, buffer_len, offset, "network_allowed=") &&
        append_bool(buffer, buffer_len, offset, report.flags.network_allowed) &&
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
        if (!authority_status_is_known(record.status) ||
            !authority_validator_is_known(record.validator) ||
            !authority_effect_is_known(record.requested_effect)) {
            clear_output(buffer, buffer_len);
            return authority_status::invalid_input;
        }

        if (!record_text_fields_are_terminated(record)) {
            clear_output(buffer, buffer_len);
            return authority_status::invalid_input;
        }

        if (!record_text_fields_are_nul_padded(record)) {
            clear_output(buffer, buffer_len);
            return authority_status::invalid_input;
        }

        if (!record_text_fields_are_line_safe(record)) {
            clear_output(buffer, buffer_len);
            return authority_status::invalid_input;
        }

        if (!record_canonical_names_match(record)) {
            clear_output(buffer, buffer_len);
            return authority_status::invalid_input;
        }

        const bool record_ok =
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "policy") &&
            append_c_string(buffer, buffer_len, offset,
                            record.policy_name.data()) &&
            append_char(buffer, buffer_len, offset, '\n') &&
            append_record_line_prefix(buffer, buffer_len, offset, index,
                                      "source_identity") &&
            append_c_string(buffer, buffer_len, offset,
                            record.source_identity.data()) &&
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
            append_record_bool_line(buffer, buffer_len, offset, index,
                                    "no_effect", record.flags.no_effect) &&
            append_record_bool_line(buffer, buffer_len, offset, index,
                                    "execution_allowed",
                                    record.flags.execution_allowed) &&
            append_record_bool_line(buffer, buffer_len, offset, index,
                                    "mutation_allowed",
                                    record.flags.mutation_allowed) &&
            append_record_bool_line(buffer, buffer_len, offset, index,
                                    "server_allowed",
                                    record.flags.server_allowed) &&
            append_record_bool_line(buffer, buffer_len, offset, index,
                                    "network_allowed",
                                    record.flags.network_allowed) &&
            append_record_bool_line(buffer, buffer_len, offset, index,
                                    "recovery_allowed",
                                    record.flags.recovery_allowed) &&
            append_record_bool_line(buffer, buffer_len, offset, index,
                                    "hardware_allowed",
                                    record.flags.hardware_allowed) &&
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
            append_record_size_line(buffer, buffer_len, offset, index,
                                    "span_start_offset",
                                    record.span.start_offset) &&
            append_record_size_line(buffer, buffer_len, offset, index,
                                    "span_end_offset", record.span.end_offset) &&
            append_record_size_line(buffer, buffer_len, offset, index,
                                    "span_start_line", record.span.start_line) &&
            append_record_size_line(buffer, buffer_len, offset, index,
                                    "span_start_column",
                                    record.span.start_column) &&
            append_record_size_line(buffer, buffer_len, offset, index,
                                    "span_end_line", record.span.end_line) &&
            append_record_size_line(buffer, buffer_len, offset, index,
                                    "span_end_column", record.span.end_column);

        if (!record_ok) {
            clear_output(buffer, buffer_len);
            return authority_status::capacity_exceeded;
        }
    }

    return authority_status::ok;
}

}  // namespace latticra

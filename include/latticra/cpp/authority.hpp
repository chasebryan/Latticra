#ifndef LATTICRA_CPP_AUTHORITY_HPP
#define LATTICRA_CPP_AUTHORITY_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>
#include <type_traits>

extern "C" {
#include "latticra/lat_parser.h"
#include "latticra/lir.h"
}

namespace latticra {

inline constexpr std::size_t LATTICRA_AUTHORITY_POLICY_NAME_MAX = 64u;
inline constexpr std::size_t LATTICRA_AUTHORITY_VALIDATOR_NAME_MAX = 64u;
inline constexpr std::size_t LATTICRA_AUTHORITY_DENIAL_REASON_MAX = 128u;
inline constexpr std::size_t LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX = 128u;
inline constexpr std::size_t LATTICRA_AUTHORITY_AUDIT_RECORD_MAX = 32u;
inline constexpr std::size_t LATTICRA_AUTHORITY_REPORT_MAX = 4096u;

enum class authority_status : std::uint8_t {
    ok = 0,
    null_argument = 1,
    invalid_input = 2,
    capacity_exceeded = 3,
    policy_denied = 4,
    unsupported_effect = 5,
    unsupported_boundary = 6,
    not_authorized = 7,
    internal_error = 8
};

enum class authority_effect : std::uint8_t {
    none = 0,
    read = 1,
    local_mutation = 2,
    host_mutation = 3,
    network = 4,
    hardware = 5,
    boot = 6,
    recovery = 7,
    external = 8,
    unknown = 9
};

enum class authority_validator : std::uint8_t {
    naming = 0,
    source_span = 1,
    no_effect = 2,
    effect = 3,
    boundary = 4,
    state_shape = 5,
    lir_shape = 6,
    lat_parse_result = 7
};

struct authority_flags {
    bool no_effect{true};
    bool execution_allowed{false};
    bool mutation_allowed{false};
    bool server_allowed{false};
    bool recovery_allowed{false};
    bool hardware_allowed{false};
};

struct authority_source_span {
    std::size_t start_offset{0u};
    std::size_t end_offset{0u};
    std::size_t start_line{0u};
    std::size_t start_column{0u};
    std::size_t end_line{0u};
    std::size_t end_column{0u};
};

struct authority_request {
    authority_effect requested_effect{authority_effect::none};
    authority_flags flags{};
    std::string_view source_identity{};
    const latticra_lat_parse_result_t *lat_result{nullptr};
    const latticra_lir_module_t *lir_module{nullptr};
};

struct authority_audit_record {
    authority_status status{authority_status::ok};
    authority_validator validator{authority_validator::no_effect};
    authority_effect requested_effect{authority_effect::none};
    authority_flags flags{};
    std::array<char, LATTICRA_AUTHORITY_POLICY_NAME_MAX> policy_name{};
    std::array<char, LATTICRA_AUTHORITY_VALIDATOR_NAME_MAX> validator_name{};
    std::array<char, LATTICRA_AUTHORITY_DENIAL_REASON_MAX> denial_reason{};
    authority_source_span span{};
};

struct authority_audit_report {
    authority_status status{authority_status::ok};
    authority_flags flags{};
    std::array<authority_audit_record, LATTICRA_AUTHORITY_AUDIT_RECORD_MAX> records{};
    std::size_t record_count{0u};
};

const char *authority_status_label(authority_status status) noexcept;
const char *authority_effect_label(authority_effect effect) noexcept;
const char *authority_validator_label(authority_validator validator) noexcept;

authority_status validate_lat_parse_result(
    const latticra_lat_parse_result_t &lat_result,
    authority_audit_report &report) noexcept;

authority_status validate_lir_shape(
    const latticra_lir_module_t &lir_module,
    authority_audit_report &report) noexcept;

authority_status classify_effect_request(
    const authority_request &request,
    authority_audit_report &report) noexcept;

authority_status render_authority_audit_report(
    const authority_audit_report &report,
    char *buffer,
    std::size_t buffer_len) noexcept;

}  // namespace latticra

#endif

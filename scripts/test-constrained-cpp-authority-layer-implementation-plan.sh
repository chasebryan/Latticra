#!/usr/bin/env sh
set -eu

doc="docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'constrained c++ authority layer implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'constrained c++ authority layer implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement C++ infrastructure' "$doc"
require_contains 'Direction checkpoint' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Implementation files' "$doc"
require_contains 'Public namespace' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Capacity constants' "$doc"
require_contains 'Authority status enum' "$doc"
require_contains 'Authority effect enum' "$doc"
require_contains 'Authority validator enum' "$doc"
require_contains 'Authority flags struct' "$doc"
require_contains 'Authority source span struct' "$doc"
require_contains 'Authority request struct' "$doc"
require_contains 'Authority audit record struct' "$doc"
require_contains 'Authority audit report struct' "$doc"
require_contains 'Ownership and lifetime rules' "$doc"
require_contains 'Allocation policy' "$doc"
require_contains 'Exception policy' "$doc"
require_contains 'RTTI and reflection policy' "$doc"
require_contains 'Template policy' "$doc"
require_contains 'Allowed standard library subset' "$doc"
require_contains 'C ABI boundary plan' "$doc"
require_contains 'Lat validation plan' "$doc"
require_contains 'LIR validation plan' "$doc"
require_contains 'Effect classification plan' "$doc"
require_contains 'Audit report format' "$doc"
require_contains 'Build policy' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation update plan' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/C_CPP_FOUNDATION_DIRECTION.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md \
  docs/LANGUAGE_STRATEGY.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/EFFECT_GATES.md \
  docs/STATE_LATTICE.md \
  docs/TRI_PLANE_TRANSITION.md \
  docs/NUCLEUS_PREVIEW.md \
  include/latticra/lat_parser.h \
  include/latticra/lir.h \
  include/latticra/state_lattice.h
do
  require_contains "$related" "$doc"
done

for direction in \
  'C is the metal.' \
  'C++ is the disciplined structure.' \
  'Latticra is the contract.' \
  'Lat / Latticra Language: contract and declaration layer' \
  'C++: governed authority layer' \
  'C: secure substrate' \
  'C++ must remain disciplined structure above the C substrate. It must not become unrestricted authority.'
do
  require_contains "$direction" "$doc"
done

for implementation_path in \
  include/latticra/cpp/authority.hpp \
  src/cpp/authority.cpp \
  tests/cpp_authority_layer_invariants.cpp \
  scripts/test-cpp-authority-layer.sh \
  .github/workflows/c.yml \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
do
  require_contains "$implementation_path" "$doc"
done

for api in \
  latticra::authority_status \
  latticra::authority_effect \
  latticra::authority_validator \
  latticra::authority_flags \
  latticra::authority_source_span \
  latticra::authority_request \
  latticra::authority_audit_record \
  latticra::authority_audit_report \
  latticra::authority_status_label \
  latticra::authority_effect_label \
  latticra::authority_validator_label \
  latticra::validate_lat_parse_result \
  latticra::validate_lir_shape \
  latticra::classify_effect_request \
  latticra::render_authority_audit_report
do
  require_contains "$api" "$doc"
done

for signature in \
  'const char *authority_status_label(authority_status status) noexcept;' \
  'const char *authority_effect_label(authority_effect effect) noexcept;' \
  'const char *authority_validator_label(authority_validator validator) noexcept;' \
  'authority_status validate_lat_parse_result(' \
  'authority_status validate_lir_shape(' \
  'authority_status classify_effect_request(' \
  'authority_status render_authority_audit_report('
do
  require_contains "$signature" "$doc"
done

for constant in \
  'LATTICRA_AUTHORITY_POLICY_NAME_MAX 64u' \
  'LATTICRA_AUTHORITY_VALIDATOR_NAME_MAX 64u' \
  'LATTICRA_AUTHORITY_DENIAL_REASON_MAX 128u' \
  'LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX 128u' \
  'LATTICRA_AUTHORITY_AUDIT_RECORD_MAX 32u' \
  'LATTICRA_AUTHORITY_REPORT_MAX 4096u' \
  'inline constexpr std::size_t LATTICRA_AUTHORITY_POLICY_NAME_MAX = 64u;'
do
  require_contains "$constant" "$doc"
done

for status in \
  'authority_status::ok' \
  'authority_status::null_argument' \
  'authority_status::invalid_input' \
  'authority_status::capacity_exceeded' \
  'authority_status::policy_denied' \
  'authority_status::unsupported_effect' \
  'authority_status::unsupported_boundary' \
  'authority_status::not_authorized' \
  'authority_status::internal_error'
do
  require_contains "$status" "$doc"
done

for effect in \
  'authority_effect::none' \
  'authority_effect::read' \
  'authority_effect::local_mutation' \
  'authority_effect::host_mutation' \
  'authority_effect::network' \
  'authority_effect::hardware' \
  'authority_effect::boot' \
  'authority_effect::recovery' \
  'authority_effect::external' \
  'authority_effect::unknown'
do
  require_contains "$effect" "$doc"
done

for validator in \
  'authority_validator::naming' \
  'authority_validator::source_span' \
  'authority_validator::no_effect' \
  'authority_validator::effect' \
  'authority_validator::boundary' \
  'authority_validator::state_shape' \
  'authority_validator::lir_shape' \
  'authority_validator::lat_parse_result'
do
  require_contains "$validator" "$doc"
done

for label in \
  ok \
  null_argument \
  invalid_input \
  capacity_exceeded \
  policy_denied \
  unsupported_effect \
  unsupported_boundary \
  not_authorized \
  internal_error \
  none \
  read \
  local_mutation \
  host_mutation \
  network \
  hardware \
  boot \
  recovery \
  external \
  unknown \
  naming \
  source_span \
  no_effect \
  effect \
  boundary \
  state_shape \
  lir_shape \
  lat_parse_result
do
  require_contains "$label" "$doc"
done

for field in \
  'bool no_effect;' \
  'bool execution_allowed;' \
  'bool mutation_allowed;' \
  'bool server_allowed;' \
  'bool recovery_allowed;' \
  'bool hardware_allowed;' \
  'std::size_t start_offset;' \
  'std::size_t end_offset;' \
  'std::size_t start_line;' \
  'std::size_t start_column;' \
  'std::size_t end_line;' \
  'std::size_t end_column;' \
  'authority_effect requested_effect;' \
  'authority_flags flags;' \
  'std::string_view source_identity;' \
  'const latticra_lat_parse_result_t *lat_result;' \
  'const latticra_lir_module_t *lir_module;' \
  'authority_status status;' \
  'authority_validator validator;' \
  'std::array<char, LATTICRA_AUTHORITY_POLICY_NAME_MAX> policy_name;' \
  'std::array<char, LATTICRA_AUTHORITY_VALIDATOR_NAME_MAX> validator_name;' \
  'std::array<char, LATTICRA_AUTHORITY_DENIAL_REASON_MAX> denial_reason;' \
  'std::array<authority_audit_record, LATTICRA_AUTHORITY_AUDIT_RECORD_MAX> records;' \
  'std::size_t record_count;'
do
  require_contains "$field" "$doc"
done

for flag in \
  'no_effect=1' \
  'execution_allowed=0' \
  'mutation_allowed=0' \
  'server_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0'
do
  require_contains "$flag" "$doc"
done

for ownership in \
  'value types' \
  'references for required non-owning inputs' \
  'std::span for bounded views when needed' \
  'std::string_view for non-owning text views' \
  'std::array for fixed storage' \
  'std::unique_ptr only if separately justified' \
  'raw owning pointers' \
  'raw new/delete' \
  'std::shared_ptr' \
  'hidden global mutable state' \
  'long-lived singletons' \
  'unbounded std::vector in authority paths' \
  'unbounded std::string in authority paths' \
  'stored references into caller-owned buffers' \
  'implicit lifetime extension'
do
  require_contains "$ownership" "$doc"
done

for allocation in \
  'fixed-capacity containers' \
  'caller-provided output buffers' \
  'no allocation in validators' \
  'no allocation in effect gates' \
  'no allocation in audit report rendering' \
  'no hidden allocation behind policy decisions'
do
  require_contains "$allocation" "$doc"
done

for exception_rule in \
  '-fno-exceptions' \
  'no throw expressions' \
  'no try/catch in authority paths' \
  'no exceptions across C ABI boundaries' \
  'no exceptions through effect gates' \
  'no exceptions through report generation' \
  'no exceptions for expected validation failures'
do
  require_contains "$exception_rule" "$doc"
done

for rtti_rule in \
  '-fno-rtti' \
  'no dynamic_cast in authority paths' \
  'no typeid-based authority decisions' \
  'no RTTI as policy architecture' \
  'no reflection-like dispatch'
do
  require_contains "$rtti_rule" "$doc"
done

for template_rule in \
  'small fixed-capacity helpers' \
  'strong type wrappers' \
  'constexpr constants' \
  'simple label helpers' \
  'std::array-based utility functions' \
  'template metaprogramming as policy engine' \
  'type-level authority decisions without readable reports' \
  'compile-time tricks that hide behavior' \
  'large framework-style abstractions' \
  'unreviewable generic dispatch'
do
  require_contains "$template_rule" "$doc"
done

for header in \
  '<array>' \
  '<cstddef>' \
  '<cstdint>' \
  '<span>' \
  '<string_view>' \
  '<type_traits>' \
  '<iostream>' \
  '<fstream>' \
  '<filesystem>' \
  '<thread>' \
  '<future>' \
  '<regex>' \
  '<exception>' \
  '<stdexcept>' \
  '<vector>' \
  '<string>' \
  '<map>' \
  '<unordered_map>'
do
  require_contains "$header" "$doc"
done

for abi in \
  'wrap C includes with extern "C" when included from C++' \
  'do not expose C++ object lifetimes to C callers' \
  'do not export raw C++ objects through a C ABI' \
  'do not let C++ exceptions cross C ABI boundaries' \
  'return explicit authority_status values for boundary failures' \
  'copy C metadata into fixed C++ report structures when needed'
do
  require_contains "$abi" "$doc"
done

for lat_check in \
  'Lat parse result status is successful before metadata validation succeeds' \
  'Lat no-effect flags are preserved' \
  'Lat execution_allowed is zero' \
  'Lat mutation_allowed is zero' \
  'Lat server_allowed is zero' \
  'Lat recovery_allowed is zero' \
  'Lat hardware_allowed is zero' \
  'Lat declaration and clause counts do not exceed declared capacity' \
  'Lat source spans are ordered and bounded' \
  'Lat effect metadata remains metadata only'
do
  require_contains "$lat_check" "$doc"
done

for lir_check in \
  'LIR module metadata is bounded' \
  'LIR node counts do not exceed declared capacity' \
  'LIR edge counts do not exceed declared capacity' \
  'LIR source spans are ordered and bounded' \
  'LIR binding metadata remains metadata only' \
  'LIR text references use explicit lengths' \
  'LIR report behavior remains no-effect'
do
  require_contains "$lir_check" "$doc"
done

for classification in \
  'none -> ok' \
  'read -> policy_denied' \
  'local_mutation -> policy_denied' \
  'host_mutation -> policy_denied' \
  'network -> policy_denied' \
  'hardware -> policy_denied' \
  'boot -> policy_denied' \
  'recovery -> policy_denied' \
  'external -> policy_denied' \
  'unknown -> unsupported_effect'
do
  require_contains "$classification" "$doc"
done

for report in \
  'CPP AUTHORITY REPORT' \
  'status=<authority-status-label>' \
  'record_count=<count>' \
  'record[0].policy=<policy-name>' \
  'record[0].validator=<validator-label>' \
  'record[0].requested_effect=<effect-label>' \
  'record[0].result=<authority-status-label>' \
  'record[0].denial_reason=<reason>' \
  'record[0].span_start_offset=<offset>' \
  'record[0].span_end_offset=<offset>'
do
  require_contains "$report" "$doc"
done

for build in \
  'CFLAGS="-std=c99 -Wall -Wextra -Werror -pedantic"' \
  'CXXFLAGS="-std=c++20 -Wall -Wextra -Werror -pedantic -fno-exceptions -fno-rtti"' \
  'compile C substrate objects with `cc`' \
  'compile authority C++ objects with `c++`' \
  'link with `c++`' \
  'cc $CFLAGS -Iinclude -c src/lat_parser.c' \
  'c++ $CXXFLAGS -Iinclude -c src/cpp/authority.cpp'
do
  require_contains "$build" "$doc"
done

for test_name in \
  cpp_authority_layer_preserves_no_effect_flags \
  cpp_authority_layer_rejects_unrestricted_cpp_claims \
  cpp_authority_layer_has_no_execution_path \
  cpp_authority_layer_has_no_network_path \
  cpp_authority_layer_has_no_hardware_path \
  cpp_authority_layer_uses_explicit_result_labels \
  cpp_authority_layer_does_not_throw_across_c_boundary \
  cpp_authority_layer_does_not_allocate_in_report_path \
  cpp_authority_layer_validates_lat_parse_result_metadata \
  cpp_authority_layer_validates_lir_shape_metadata \
  cpp_authority_layer_audit_report_is_deterministic \
  cpp_authority_layer_rejects_small_report_buffer \
  cpp_authority_layer_is_deterministic \
  cpp_authority_layer_rejects_mutation_flags \
  cpp_authority_layer_classifies_effects_without_performing_them \
  cpp_authority_layer_builds_with_fno_exceptions_and_fno_rtti
do
  require_contains "$test_name" "$doc"
done

for doc_path in \
  README.md \
  STATUS.md \
  docs/FOUNDATION_INDEX.md \
  docs/status/CURRENT_STATUS.md \
  docs/status/ANNOUNCEMENTS.md \
  docs/project_notes/CURRENT_DIRECTION.md \
  docs/project_notes/UPCOMING_WORK.md \
  docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md \
  scripts/test-project-strategy-status-framework.sh \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
do
  require_contains "$doc_path" "$doc"
done

for compat in \
  'C substrate behavior' \
  'Lat parser behavior' \
  'LIR shape behavior' \
  'L-UI parser behavior' \
  'L-UI semantic validation behavior' \
  'state lattice behavior' \
  'Nucleus preview behavior' \
  'C/C++ foundation direction' \
  'language naming policy' \
  'no-effect flags' \
  'Lat grammar reports' \
  'LIR shape reports'
do
  require_contains "$compat" "$doc"
done

for forbidden in \
  'become unrestricted C++' \
  'execute Lat' \
  'execute LIR' \
  'render L-UI' \
  'call Nucleus task execution' \
  'mutate state' \
  'read files' \
  'write files' \
  'open network connections' \
  'call server code' \
  'call update code' \
  'call recovery code' \
  'call hardware code' \
  'hide allocation in authority paths' \
  'throw exceptions across C ABI boundaries' \
  'use RTTI as policy architecture' \
  'use template metaprogramming as policy architecture' \
  'weaken C substrate boundaries' \
  'weaken no-effect flags' \
  'imply a sandbox, runtime, malware prevention, ransomware prevention, or operating-system surface'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-constrained-cpp-authority-layer-implementation-plan.sh' "$doc"
require_contains 'Constrained C++ authority-layer implementation code may be added only after this plan is merged.' "$doc"

printf 'constrained_cpp_authority_layer_implementation_plan: ok\n'

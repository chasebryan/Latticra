#!/usr/bin/env sh
set -eu

doc="docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION_PLAN.md"
runner="scripts/test-cpp-authority-layer.sh"
policy_runner="scripts/test-cpp-authority-layer-build-policy.sh"
test_file="tests/cpp_authority_layer_invariants.cpp"

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

if [ ! -f "$runner" ]; then
  printf 'constrained c++ authority layer implementation plan: missing runner: %s\n' "$runner" >&2
  exit 1
fi

if [ ! -f "$policy_runner" ]; then
  printf 'constrained c++ authority layer implementation plan: missing runner: %s\n' "$policy_runner" >&2
  exit 1
fi

if [ ! -f "$test_file" ]; then
  printf 'constrained c++ authority layer implementation plan: missing test file: %s\n' "$test_file" >&2
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
  scripts/test-cpp-authority-layer-build-policy.sh \
  scripts/test-constrained-cpp-authority-layer-implementation-plan.sh \
  .github/workflows/c.yml \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION_PLAN.md \
  docs/CPP_AUTHORITY_IMPLEMENTATION_REVIEW.md \
  docs/status/CPP_AUTHORITY_IMPLEMENTATION_REVIEW_STATUS.md
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

require_contains 'All public functions in the first implementation should be `noexcept`.' "$doc"
require_contains 'Validation, classification, and report-rendering functions should return' "$doc"
require_contains 'explicit `authority_status` values.' "$doc"

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
  'bool network_allowed;' \
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
  'std::array<char, LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u> source_identity;' \
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
  'network_allowed=0' \
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
  'malloc/calloc/realloc/free' \
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
  '<string_view>' \
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
  '<memory>' \
  '<map>' \
  '<unordered_map>'
do
  require_contains "$header" "$doc"
done

require_contains '`<type_traits>` is test-only for public API static assertions; it is not part of' "$doc"
require_contains 'the authority-path source subset. `std::span` remains a future bounded-view' "$doc"
require_contains 'candidate and requires an explicit guard update before authority-path use.' "$doc"

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
  'Lat parse error value is successful before metadata validation succeeds' \
  'Lat no-effect flags are preserved' \
  'Lat execution_allowed is zero' \
  'Lat mutation_allowed is zero' \
  'Lat server_allowed is zero' \
  'Lat network_allowed is zero' \
  'Lat recovery_allowed is zero' \
  'Lat hardware_allowed is zero' \
  'Lat declaration and clause counts do not exceed declared capacity' \
  'Lat module declaration count is bounded by materialized declarations' \
  'Lat module kind counts are bounded by materialized declarations' \
  'Lat declaration kinds stay inside the known Lat vocabulary' \
  'Lat declaration clause ranges are bounded' \
  'Lat clause effects stay inside the known Lat effect vocabulary' \
  'Lat source spans are ordered and bounded' \
  'Lat declaration source spans are bounded' \
  'Lat clause source spans are bounded' \
  'Lat effect metadata remains metadata only'
do
  require_contains "$lat_check" "$doc"
done

for lir_check in \
  'LIR module status is successful before metadata validation succeeds' \
  'LIR error value is successful before metadata validation succeeds' \
  'LIR module metadata is bounded' \
  'LIR module enums stay inside known LIR vocabularies' \
  'LIR node counts do not exceed declared capacity' \
  'LIR node kinds stay inside the known LIR vocabulary' \
  'LIR edge counts do not exceed declared capacity' \
  'LIR edge kinds stay inside the known LIR vocabulary' \
  'LIR edge kind counts are bounded by materialized edges' \
  'LIR binding kinds stay inside the known LIR vocabulary' \
  'LIR source spans are ordered and bounded' \
  'LIR node source spans are bounded' \
  'LIR edge source spans are bounded' \
  'LIR binding source spans are bounded' \
  'LIR text source spans are bounded' \
  'LIR node child ranges are bounded' \
  'LIR node parent indexes are bounded' \
  'LIR edge node indexes are bounded' \
  'LIR binding node indexes are bounded' \
  'LIR text node indexes are bounded' \
  'LIR execution_allowed is zero' \
  'LIR mutation_allowed is zero' \
  'LIR server_allowed is zero' \
  'LIR network_allowed is zero' \
  'LIR recovery_allowed is zero' \
  'LIR hardware_allowed is zero' \
  'LIR binding metadata remains metadata only' \
  'LIR text references use explicit lengths' \
  'LIR report behavior remains no-effect'
do
  require_contains "$lir_check" "$doc"
done

for classification in \
  'If request metadata includes Lat or LIR pointers, classification should' \
  'validate the linked metadata before allowing even a no-effect request.' \
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

require_contains 'Requested effects outside the authority effect vocabulary should return' "$doc"
require_contains 'values cannot silently pick a fallback report label.' "$doc"

for report in \
  'CPP AUTHORITY REPORT' \
  'status=<authority-status-label>' \
  'record_count=<count>' \
  'network_allowed=<0|1>' \
  'record[0].policy=<policy-name>' \
  'record[0].source_identity=<source-identity>' \
  'record[0].validator=<validator-label>' \
  'record[0].requested_effect=<effect-label>' \
  'record[0].no_effect=<0|1>' \
  'record[0].execution_allowed=<0|1>' \
  'record[0].mutation_allowed=<0|1>' \
  'record[0].server_allowed=<0|1>' \
  'record[0].network_allowed=<0|1>' \
  'record[0].recovery_allowed=<0|1>' \
  'record[0].hardware_allowed=<0|1>' \
  'record[0].result=<authority-status-label>' \
  'record[0].denial_reason=<reason>' \
  'record[0].span_start_offset=<offset>' \
  'record[0].span_end_offset=<offset>' \
  'record[0].span_start_line=<line>' \
  'record[0].span_start_column=<column>' \
  'record[0].span_end_line=<line>' \
  'record[0].span_end_column=<column>'
do
  require_contains "$report" "$doc"
done

require_contains 'Report status values and audit-record status, validator, and requested-effect' "$doc"
require_contains 'Audit-record policy and validator name text must match the canonical' "$doc"
require_contains 'authority policy name and validator enum label.' "$doc"
require_contains 'values outside their authority vocabularies should return' "$doc"

for build in \
  'CFLAGS="-std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow"' \
  'CXXFLAGS="-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti"' \
  'compile C substrate objects with `cc`' \
  'compile authority C++ objects with `c++`' \
  'link the C and C++ objects together with `c++`' \
  'tmpdir="$(mktemp -d "/tmp/cpp-authority-layer.XXXXXX")"' \
  'trap '\''rm -rf "$tmpdir"'\'' EXIT INT HUP TERM' \
  'TMPDIR="$tmpdir"' \
  'export TMPDIR' \
  'cc $CFLAGS -Iinclude -c src/lat_parser.c' \
  'c++ $CXXFLAGS -Iinclude -c src/cpp/authority.cpp' \
  '"$tmpdir/latticra-lat-parser.o"' \
  '"$tmpdir/latticra-lir.o"'
do
  require_contains "$build" "$doc"
done

for runner_build in \
  '#!/bin/sh' \
  'PATH=/usr/bin:/bin:/usr/sbin:/sbin' \
  'LC_ALL=C' \
  'LANG=C' \
  'umask 077' \
  ': "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow}"' \
  ': "${CXXFLAGS:=-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti}"' \
  'reject_unlisted_c_flag()' \
  'reject_unlisted_cxx_flag()' \
  'reject_linker_injection_flag()' \
  'reject_toolchain_escape_flag()' \
  'reject_set_environment_variable()' \
  'reject_prefixed_environment_variable()' \
  'require_private_path_permissions()' \
  'CPPFLAGS' \
  'CPLUS_INCLUDE_PATH' \
  'LIBRARY_PATH' \
  'SDKROOT' \
  'COMPILER_PATH' \
  'DEPENDENCIES_OUTPUT' \
  'CC \' \
  'CXX \' \
  'NM \' \
  'INSTALL_NAME_TOOL' \
  'reject_prefixed_environment_variable CCACHE_' \
  'reject_prefixed_environment_variable DISTCC_' \
  'reject_prefixed_environment_variable DYLD_' \
  'tmpdir="$(mktemp -d "/tmp/cpp-authority-layer.XXXXXX")"' \
  'TMPDIR="$tmpdir"' \
  'export TMPDIR' \
  'require_private_path_permissions "$tmpdir"' \
  'for artifact in "$lat_parser_o" "$lir_o" "$authority_o" "$authority_test"' \
  'require_private_path_permissions "$artifact"' \
  'private build artifact grants group/world access' \
  '^[[:space:]]*#[[:space:]]*include[[:space:]]*' \
  'cc $CFLAGS' \
  'c++ $CXXFLAGS' \
  'nm "$authority_o"' \
  'nm -g "$authority_o"'
do
  require_contains "$runner_build" "$runner"
done

require_contains 'The runner should reject environment-provided `CFLAGS` or `CXXFLAGS` that omit' "$doc"
require_contains 'the required flag fragments before compiling.' "$doc"
require_contains 'The negative missing-required-flag probes should cover every required C and C++' "$doc"
require_contains 'standard, warning, warnings-as-errors, no-exceptions, and no-RTTI flag fragment.' "$doc"
require_contains 'The runner should reject conflicting environment-provided flags that override' "$doc"
require_contains 'the required C99, C++20, no-exceptions, no-RTTI, or warnings-as-errors policy.' "$doc"
require_contains 'The negative flag-policy probes should cover conflicting C and C++ standards,' "$doc"
require_contains 'exception and RTTI re-enablement, and C/C++ warning-policy weakening.' "$doc"
require_contains 'The runner should reject any `CFLAGS` or `CXXFLAGS` fragment outside the' "$doc"
require_contains 'declared flag allowlists, so optimization, codegen, visibility, sanitizer,' "$doc"
require_contains 'dependency, or platform flags cannot alter authority objects or the authority' "$doc"
require_contains 'test binary.' "$doc"
require_contains 'The negative unlisted-flag probes should cover the C flag allowlist, the C++' "$doc"
require_contains 'flag allowlist, and optimization, codegen, visibility, sanitizer, dependency,' "$doc"
require_contains 'and platform flag classes.' "$doc"
require_contains 'It should reject environment-provided include path or forced-include flags such' "$doc"
require_contains 'as `-I`, `-isystem`, `-iquote`, `-idirafter`, `-include`, `-imacros`, `-F`,' "$doc"
require_contains 'and `-iframework` so caller flags cannot shadow or preinclude authority or C' "$doc"
require_contains 'substrate headers.' "$doc"
require_contains 'The negative include-flag probes should cover split and joined search-path' "$doc"
require_contains 'forms, split and joined forced-include/macro forms, GNU `--include` forms, and' "$doc"
require_contains 'split and joined framework forms.' "$doc"
require_contains 'It should reject environment-provided preprocessor macro override flags such' "$doc"
require_contains 'as `-D`, `-U`, `-Wp,*`, and `-Xpreprocessor` so caller flags cannot redefine' "$doc"
require_contains 'authority or C substrate contracts.' "$doc"
require_contains 'The negative preprocessor-override probes should cover joined and split' "$doc"
require_contains 'define/undef forms plus driver pass-through forms.' "$doc"
require_contains 'It should reject environment-provided linker injection flags in `CXXFLAGS`,' "$doc"
require_contains 'such as `-Wl,*`, `-Xlinker`, `-L`, `-l`, `-B`, `-fuse-ld=*`, `-shared`,' "$doc"
require_contains '`-static`, `-rdynamic`, `-nostdlib`, `-nodefaultlibs`, `-nostartfiles`,' "$doc"
require_contains '`-pie`, `-no-pie`, `-r`, `-pthread`, and `-stdlib=*`, so caller flags cannot' "$doc"
require_contains 'alter the final authority test link.' "$doc"
require_contains 'It should reject environment-provided toolchain escape flags such as' "$doc"
require_contains '`--sysroot`, `-isysroot`, `-resource-dir`, `-gcc-toolchain`, `-ccc-gcc-name`,' "$doc"
require_contains '`-fplugin=*`, `-fplugin-arg-*`, `-Xclang`, `-mllvm`, `-Xassembler`, and' "$doc"
require_contains '`-Wa,*` so caller flags cannot redirect the compiler resource/sysroot, inject' "$doc"
require_contains 'compiler plugins, or pass opaque options through the compiler driver.' "$doc"
require_contains 'It should reject ambient compiler and linker environment variables such as' "$doc"
require_contains '`CPPFLAGS`, `LDFLAGS`, `ASFLAGS`, `CPATH`, `C_INCLUDE_PATH`,' "$doc"
require_contains '`CPLUS_INCLUDE_PATH`, `LIBRARY_PATH`, `LD_LIBRARY_PATH`, `LD_PRELOAD`,' "$doc"
require_contains '`DYLD_*`, `SDKROOT`, `MACOSX_DEPLOYMENT_TARGET`, `DEVELOPER_DIR`,' "$doc"
require_contains '`TOOLCHAINS`, `GCC_EXEC_PREFIX`, `COMPILER_PATH`, `CCC_OVERRIDE_OPTIONS`,' "$doc"
require_contains 'and dependency-output variables so the build cannot be altered outside the' "$doc"
require_contains 'declared `CFLAGS` and `CXXFLAGS`.' "$doc"
require_contains 'The `DYLD_*` rejection should be prefix-wide, not limited to a fixed list of' "$doc"
require_contains 'known dynamic-loader variable names.' "$doc"
require_contains 'The negative prefix-helper fixture should prove prefix matching with a' "$doc"
require_contains 'non-DYLD surrogate prefix, while the runner self-check pins the real `DYLD_`' "$doc"
require_contains 'rejection call; this keeps the probe portable on platforms that strip' "$doc"
require_contains '`DYLD_*` before `/bin/sh` starts.' "$doc"
require_contains 'It should reject ambient tool-selector variables such as `CC`, `CXX`, `CPP`,' "$doc"
require_contains '`LD`, `NM`, `AR`, `RANLIB`, `STRIP`, `OBJDUMP`, `OBJCOPY`, `READELF`, `SIZE`,' "$doc"
require_contains '`LIBTOOL`, and `INSTALL_NAME_TOOL`, plus `CCACHE_*` and `DISTCC_*` prefixes, so' "$doc"
require_contains 'callers cannot imply alternate compiler, linker, or object-inspection tools.' "$doc"
require_contains 'It should reset `PATH` to `/usr/bin:/bin:/usr/sbin:/sbin` before resolving' "$doc"
require_contains 'the compiler, linker, shell utility, and object-inspection commands used by' "$doc"
require_contains 'the authority runner.' "$doc"
require_contains 'It should use an absolute `/bin/sh` shebang instead of `/usr/bin/env sh`, so' "$doc"
require_contains 'direct runner invocation does not resolve the shell through caller-controlled' "$doc"
require_contains '`PATH`.' "$doc"
require_contains 'It should force `LC_ALL=C` and `LANG=C` before source-token and object-symbol' "$doc"
require_contains 'analysis so shell tool matching is locale-stable.' "$doc"
require_contains 'It should ignore caller-provided `TMPDIR`, create a private authority build' "$doc"
require_contains 'directory under `/tmp` directly, export `TMPDIR` to that private directory for' "$doc"
require_contains 'compiler-driver temporaries, and set `umask 077` before creating authority' "$doc"
require_contains 'build artifacts so intermediate objects and test binaries are private to the' "$doc"
require_contains 'invoking user by default.' "$doc"
require_contains 'It should verify the private temporary directory, C substrate objects, C++' "$doc"
require_contains 'authority object, and authority test binary do not grant group or world' "$doc"
require_contains 'permissions before executing the authority test binary.' "$doc"
require_contains 'It should also reject `-Wno-*` flags that disable required warnings such as' "$doc"
require_contains '`-Wconversion` or `-Wshadow`.' "$doc"
require_contains 'The C++ standard version policy is constrained C++20, enforced through' "$doc"
require_contains '`-std=c++20` in `CXXFLAGS`.' "$doc"
require_contains 'The warnings-as-errors policy is mandatory for both C substrate objects and' "$doc"
require_contains 'C++ authority objects through `-Werror` in `CFLAGS` and `CXXFLAGS`.' "$doc"
require_contains 'The runner should require the C++ authority header to wrap the C substrate' "$doc"
require_contains 'includes with `extern "C"`.' "$doc"
require_contains 'The runner should reject any authority-header `latticra/lat_parser.h` or' "$doc"
require_contains '`latticra/lir.h` include that appears outside that `extern "C"` block.' "$doc"
require_contains 'The runner should reject direct C substrate includes from `src/cpp/authority.cpp`;' "$doc"
require_contains 'the public C++ authority header owns the C include boundary.' "$doc"
require_contains 'The runner should allowlist quoted includes in the authority path: the C++' "$doc"
require_contains 'authority header may include only `latticra/lat_parser.h` and `latticra/lir.h`,' "$doc"
require_contains 'and `src/cpp/authority.cpp` may include only `latticra/cpp/authority.hpp`.' "$doc"
require_contains 'The include guards should match normal preprocessor whitespace, including' "$doc"
require_contains 'leading spaces and `# include`, so directive formatting cannot bypass the' "$doc"
require_contains 'authority include allowlists or C substrate include boundary.' "$doc"
require_contains 'The include-boundary fixture probes should cover unwrapped' "$doc"
require_contains '`latticra/lat_parser.h` and `latticra/lir.h` authority-header includes, direct' "$doc"
require_contains '`latticra/lat_parser.h`, `latticra/lir.h`, and `latticra/state_lattice.h`' "$doc"
require_contains 'source includes, and both header/source quoted-include allowlists.' "$doc"
require_contains 'The build guard should allow only the declared standard library subset, reject' "$doc"
require_contains 'raw allocation constructs in authority-path source, and reject writable global' "$doc"
require_contains 'data symbols in the compiled authority object.' "$doc"
require_contains 'The companion build-policy test should run negative probes against the' "$doc"
require_contains 'authority runner for missing required flags, conflicting flags, warning' "$doc"
require_contains 'weakening, unlisted flags, include injection, macro override, linker injection,' "$doc"
require_contains 'toolchain escape, ambient compiler variables, ambient tool selectors, and' "$doc"
require_contains 'ambient tool prefixes. The flag probes should cover forced-include and search' "$doc"
require_contains 'path variants, macro undef/pass-through variants, linker library/selector/mode' "$doc"
require_contains 'variants, and sysroot/plugin/backend/assembler toolchain escape variants. It should also prove' "$doc"
require_contains 'ambient include-path, library-path, SDK, compiler-path, and dependency-output' "$doc"
require_contains 'variables are rejected before the authority build. They should also cover' "$doc"
require_contains 'assembler, C include path, Objective-C include path, loader path/preload,' "$doc"
require_contains 'deployment-target, developer-dir, toolchains, GCC exec-prefix, compiler' "$doc"
require_contains 'override/add-args, and SunPro dependency-output variables. The ambient' "$doc"
require_contains 'tool-selector probes should cover C/C++ compiler, preprocessor, linker,' "$doc"
require_contains 'archive/index, binary-inspection, libtool, and install-name selectors. It' "$doc"
require_contains 'should also prove caller' "$doc"
require_contains '`PATH` cannot steer tool' "$doc"
require_contains 'resolution and caller `TMPDIR` cannot steer the authority build root away from' "$doc"
require_contains 'the runner'\''s private `mktemp -d` authority workdir template. It should' "$doc"
require_contains 'self-check the authority runner command-shape' "$doc"
require_contains 'fragments so the C substrate object compile, authority C++ object compile, C++' "$doc"
require_contains 'test link, and `nm` object-inspection steps remain tied to the documented' "$doc"
require_contains 'authority runner paths and object variables. It should run mutated authority' "$doc"
require_contains 'source/header fixtures' "$doc"
require_contains 'through the runner to prove source-token guards reject unwrapped C substrate' "$doc"
require_contains 'includes, direct C substrate includes, unlisted quoted includes, spaced' "$doc"
require_contains 'preprocessor includes, unlisted standard headers, forbidden exception/RTTI' "$doc"
require_contains 'constructs, raw allocation constructs, forbidden C++ ownership/container' "$doc"
require_contains 'types, forbidden file/system standard headers, unlisted `std::` APIs,' "$doc"
require_contains 'framework namespaces, I/O or process calls, C substrate function calls, and' "$doc"
require_contains 'template metaprogramming constructs.' "$doc"
require_contains 'The ownership/container fixture probes should cover `std::vector`,' "$doc"
require_contains '`std::string`, `std::shared_ptr`, `std::unique_ptr`, `std::map`, and' "$doc"
require_contains '`std::unordered_map` authority-path tokens.' "$doc"
require_contains 'The forbidden standard-library header fixture probes should cover the named' "$doc"
require_contains 'file, system, exception, thread, regex, string, memory, map, and unordered-map' "$doc"
require_contains 'headers forbidden by the authority-path subset.' "$doc"
require_contains 'The exception, RTTI, and cast fixture probes should cover `throw`, `try`,' "$doc"
require_contains '`catch`, `dynamic_cast`, `typeid`, `reinterpret_cast`, and `const_cast`' "$doc"
require_contains 'authority-path tokens.' "$doc"
require_contains 'The raw and C allocation fixture probes should cover `new`, `delete`,' "$doc"
require_contains '`malloc`, `calloc`, `realloc`, and `free` authority-path tokens.' "$doc"
require_contains 'It should run mutated authority source fixtures that compile far enough to' "$doc"
require_contains 'prove object-symbol guards reject writable global data, common data symbols,' "$doc"
require_contains 'emitted `latticra_*` symbols, allocation symbols, exception/RTTI symbols,' "$doc"
require_contains 'indirect exception/RTTI symbols, public C ABI symbols, and public unmangled' "$doc"
require_contains 'defined symbols.' "$doc"
require_contains 'It should run a mutated runner fixture with weakened `umask` settings to prove' "$doc"
require_contains 'the private artifact-permission guard rejects group/world-readable build' "$doc"
require_contains 'artifacts.' "$doc"
require_contains 'The object-symbol guard should treat `nm` common symbols (`C`/`c`) as rejected' "$doc"
require_contains 'writable global data.' "$doc"
require_contains 'The first implementation static-analysis path is the source-token and object' "$doc"
require_contains 'symbol analysis embedded in `scripts/test-cpp-authority-layer.sh`; no separate' "$doc"
require_contains 'sanitizer runtime is required for this no-effect authority layer.' "$doc"
require_contains 'The runner should reject authority-path standard library headers outside the' "$doc"
require_contains 'declared subset.' "$doc"
require_contains 'The runner should reject authority-path `std::` API names outside the declared' "$doc"
require_contains 'subset.' "$doc"
require_contains 'It should also reject allocation symbols in the compiled authority object,' "$doc"
require_contains 'including `operator new`, `operator delete`, `malloc`, `calloc`, `realloc`,' "$doc"
require_contains 'and `free`.' "$doc"
require_contains 'The object allocation-symbol fixture probes should cover `operator new`,' "$doc"
require_contains '`operator delete`, `malloc`, `calloc`, `realloc`, and `free` emitted symbols.' "$doc"
require_contains 'It should reject exception-runtime and RTTI/typeinfo symbols in the compiled' "$doc"
require_contains 'authority object.' "$doc"
require_contains 'The object exception/RTTI fixture probes should cover `__gxx_personality`,' "$doc"
require_contains '`__cxa`, `__Unwind`, `_ZTI`, `_ZTS`, and `_ZTV` emitted symbol families.' "$doc"
require_contains 'The object-symbol guard should also reject indirect exception-runtime and' "$doc"
require_contains 'RTTI/typeinfo references such as `DW.ref.__gxx_personality_v0`.' "$doc"
require_contains 'It should reject framework-style namespaces such as `latticra::runtime`,' "$doc"
require_contains '`latticra::kernel`, `latticra::server`, and `latticra::recovery` in the' "$doc"
require_contains 'authority path.' "$doc"
require_contains 'The framework-namespace fixture probes should cover `latticra::runtime`,' "$doc"
require_contains '`latticra::kernel`, `latticra::server`, and `latticra::recovery` authority-path' "$doc"
require_contains 'namespace tokens.' "$doc"
require_contains 'It should reject obvious file I/O, network socket, and process-launch call' "$doc"
require_contains 'tokens in authority-path source.' "$doc"
require_contains 'The I/O, network, and process-call fixture probes should cover file calls' "$doc"
require_contains '`fopen`, `freopen`, `open`, `creat`, `read`, and `write`; socket calls' "$doc"
require_contains '`socket`, `connect`, `bind`, `listen`, `accept`, `send`, and `recv`; and' "$doc"
require_contains 'process calls `system`, `popen`, `fork`, `exec*`, and `posix_spawn`.' "$doc"
require_contains 'It should reject any authority-path `latticra_*` C substrate function call' "$doc"
require_contains 'expression and any emitted `latticra_*` C substrate symbol from the compiled' "$doc"
require_contains 'authority object; the layer may consume C structs and enums but must not call' "$doc"
require_contains 'C substrate behavior, report, or helper functions.' "$doc"
require_contains 'The C substrate call fixture probes should cover Lat helper, parse, and report' "$doc"
require_contains 'calls; LIR helper, lower, and report calls; and state-lattice default,' "$doc"
require_contains 'no-effect, and report calls.' "$doc"
require_contains 'It should reject public unmangled C ABI text symbols in the compiled authority' "$doc"
require_contains 'object.' "$doc"
require_contains 'It should reject any public unmangled defined symbol in the compiled authority' "$doc"
require_contains 'object, including non-text data symbols.' "$doc"
require_contains 'It should reject generic template metaprogramming constructs in authority-path' "$doc"
require_contains 'source while still allowing fixed-size helper templates.' "$doc"
require_contains 'The template-policy fixture probes should cover `template <typename>`,' "$doc"
require_contains '`template <class>`, template-template parameters, `requires`, `concept`,' "$doc"
require_contains '`std::enable_if`, `std::conditional`, `std::integral_constant`, `std::is_*`,' "$doc"
require_contains 'and `std::void_t` authority-path tokens.' "$doc"
require_contains 'The template-policy source-token check should run before the general unlisted' "$doc"
require_contains '`std::` API check so standard-library metaprogramming helpers receive the' "$doc"
require_contains 'template-policy denial.' "$doc"
require_contains 'Null output buffers should return `authority_status::null_argument`.' "$doc"
require_contains 'Audit report record counts larger than `LATTICRA_AUTHORITY_AUDIT_RECORD_MAX`' "$doc"
require_contains 'should return `authority_status::capacity_exceeded` and clear the buffer.' "$doc"

for test_name in \
  cpp_authority_layer_preserves_no_effect_flags \
  cpp_authority_layer_rejects_unrestricted_cpp_claims \
  cpp_authority_layer_has_no_execution_path \
  cpp_authority_layer_has_no_network_path \
  cpp_authority_layer_has_no_hardware_path \
  cpp_authority_layer_uses_explicit_result_labels \
  cpp_authority_layer_uses_stable_effect_labels \
  cpp_authority_layer_uses_stable_validator_labels \
  cpp_authority_layer_does_not_throw_across_c_boundary \
  cpp_authority_layer_public_api_contract_is_noexcept \
  cpp_authority_layer_does_not_allocate_in_report_path \
  cpp_authority_layer_preserves_source_identity_in_audit \
  cpp_authority_layer_accepts_max_source_identity \
  cpp_authority_layer_rejects_oversized_source_identity \
  cpp_authority_layer_bounds_source_identity_before_audit_copy \
  cpp_authority_layer_rejects_nul_source_identity \
  cpp_authority_layer_rejects_line_break_source_identity \
  cpp_authority_layer_rejects_requested_effect_out_of_vocabulary \
  cpp_authority_layer_validates_lat_parse_result_metadata \
  cpp_authority_layer_rejects_lat_parse_result_status_not_ok \
  cpp_authority_layer_rejects_lat_parse_error_not_ok \
  cpp_authority_layer_rejects_lat_source_span_out_of_bounds \
  cpp_authority_layer_rejects_lat_source_span_unordered \
  cpp_authority_layer_rejects_lat_module_declaration_count_out_of_bounds \
  cpp_authority_layer_rejects_lat_declaration_clause_range_out_of_bounds \
  cpp_authority_layer_rejects_lat_declaration_span_unordered \
  cpp_authority_layer_rejects_lat_declaration_span_out_of_bounds \
  cpp_authority_layer_rejects_lat_module_kind_counts_out_of_bounds \
  cpp_authority_layer_rejects_lat_declaration_kind_out_of_vocabulary \
  cpp_authority_layer_rejects_lat_clause_effect_out_of_vocabulary \
  cpp_authority_layer_rejects_lat_clause_span_unordered \
  cpp_authority_layer_rejects_lat_clause_span_out_of_bounds \
  cpp_authority_layer_validates_lir_shape_metadata \
  cpp_authority_layer_rejects_lir_module_status_not_ok \
  cpp_authority_layer_rejects_lir_error_not_ok \
  cpp_authority_layer_rejects_lir_source_span_out_of_bounds \
  cpp_authority_layer_rejects_lir_source_span_unordered \
  cpp_authority_layer_rejects_lir_node_child_range_out_of_bounds \
  cpp_authority_layer_rejects_lir_node_parent_index_out_of_bounds \
  cpp_authority_layer_rejects_lir_node_span_unordered \
  cpp_authority_layer_rejects_lir_node_span_out_of_bounds \
  cpp_authority_layer_rejects_lir_edge_node_index_out_of_bounds \
  cpp_authority_layer_rejects_lir_edge_span_unordered \
  cpp_authority_layer_rejects_lir_edge_span_out_of_bounds \
  cpp_authority_layer_rejects_lir_binding_node_index_out_of_bounds \
  cpp_authority_layer_rejects_lir_binding_span_unordered \
  cpp_authority_layer_rejects_lir_binding_span_out_of_bounds \
  cpp_authority_layer_rejects_lir_text_node_index_out_of_bounds \
  cpp_authority_layer_rejects_lir_text_length_exceeded \
  cpp_authority_layer_rejects_lir_text_span_unordered \
  cpp_authority_layer_rejects_lir_text_span_out_of_bounds \
  cpp_authority_layer_rejects_lir_edge_kind_counts_out_of_bounds \
  cpp_authority_layer_rejects_lir_module_enum_out_of_vocabulary \
  cpp_authority_layer_rejects_lir_node_kind_out_of_vocabulary \
  cpp_authority_layer_rejects_lir_edge_kind_out_of_vocabulary \
  cpp_authority_layer_rejects_lir_binding_kind_out_of_vocabulary \
  cpp_authority_layer_audit_report_is_deterministic \
  cpp_authority_layer_renders_report_header_and_record_fields \
  cpp_authority_layer_renders_record_no_effect_flags \
  cpp_authority_layer_renders_record_source_span_coordinates \
  cpp_authority_layer_rejects_small_report_buffer \
  cpp_authority_layer_rejects_null_report_buffer \
  cpp_authority_layer_rejects_too_many_audit_records \
  cpp_authority_layer_rejects_unterminated_audit_text \
  cpp_authority_layer_rejects_audit_text_line_breaks \
  cpp_authority_layer_rejects_noncanonical_audit_text_padding \
  cpp_authority_layer_rejects_noncanonical_policy_name \
  cpp_authority_layer_rejects_noncanonical_validator_name \
  cpp_authority_layer_rejects_report_status_out_of_vocabulary \
  cpp_authority_layer_rejects_audit_record_status_out_of_vocabulary \
  cpp_authority_layer_rejects_audit_record_validator_out_of_vocabulary \
  cpp_authority_layer_rejects_audit_record_effect_out_of_vocabulary \
  cpp_authority_layer_is_deterministic \
  cpp_authority_layer_rejects_mutation_flags \
  cpp_authority_layer_rejects_network_flags \
  cpp_authority_layer_rejects_lat_network_flags \
  cpp_authority_layer_rejects_lir_network_flags \
  cpp_authority_layer_rejects_all_request_no_effect_flag_deviations \
  cpp_authority_layer_rejects_all_lat_no_effect_flag_deviations \
  cpp_authority_layer_rejects_all_lir_no_effect_flag_deviations \
  cpp_authority_layer_rejects_request_lat_network_flags \
  cpp_authority_layer_rejects_request_lir_network_flags \
  cpp_authority_layer_accepts_request_with_valid_linked_metadata \
  cpp_authority_layer_rejects_request_lat_metadata_before_no_effect_allow \
  cpp_authority_layer_rejects_request_lir_metadata_before_no_effect_allow \
  cpp_authority_layer_classifies_effects_without_performing_them \
  cpp_authority_layer_builds_with_fno_exceptions_and_fno_rtti \
  cpp_authority_layer_build_rejects_missing_required_flags \
  cpp_authority_layer_build_rejects_conflicting_required_flags \
  cpp_authority_layer_build_rejects_unlisted_compiler_flags \
  cpp_authority_layer_build_rejects_environment_include_injection_flags \
  cpp_authority_layer_build_rejects_environment_macro_override_flags \
  cpp_authority_layer_build_rejects_environment_linker_injection_flags \
  cpp_authority_layer_build_rejects_environment_toolchain_escape_flags \
  cpp_authority_layer_build_rejects_ambient_compiler_environment_variables \
  cpp_authority_layer_build_rejects_ambient_dyld_environment_prefix \
  cpp_authority_layer_build_rejects_ambient_tool_selector_variables \
  cpp_authority_layer_build_uses_sanitized_tool_path \
  cpp_authority_layer_build_uses_absolute_shell_entrypoint \
  cpp_authority_layer_build_uses_deterministic_tool_locale \
  cpp_authority_layer_build_uses_fixed_temporary_root \
  cpp_authority_layer_build_uses_private_artifact_permissions \
  cpp_authority_layer_build_uses_cxx20_standard \
  cpp_authority_layer_build_uses_warnings_as_errors \
  cpp_authority_layer_build_uses_source_and_object_static_analysis_path \
  cpp_authority_layer_build_policy_self_checks_runner_command_shape \
  cpp_authority_layer_build_requires_extern_c_substrate_includes \
  cpp_authority_layer_build_rejects_unwrapped_c_substrate_includes \
  cpp_authority_layer_build_rejects_direct_c_substrate_includes \
  cpp_authority_layer_build_rejects_unlisted_quote_includes \
  cpp_authority_layer_build_rejects_spaced_preprocessor_includes \
  cpp_authority_layer_build_rejects_unlisted_standard_headers \
  cpp_authority_layer_build_rejects_unlisted_std_apis \
  cpp_authority_layer_build_rejects_writable_global_data_symbols \
  cpp_authority_layer_build_rejects_common_data_symbols \
  cpp_authority_layer_build_rejects_allocation_symbols \
  cpp_authority_layer_build_rejects_exception_and_rtti_symbols \
  cpp_authority_layer_build_rejects_indirect_exception_and_rtti_symbols \
  cpp_authority_layer_build_rejects_framework_namespaces \
  cpp_authority_layer_build_rejects_io_and_process_calls \
  cpp_authority_layer_build_rejects_c_substrate_function_calls \
  cpp_authority_layer_build_rejects_public_c_abi_symbols \
  cpp_authority_layer_build_rejects_public_unmangled_defined_symbols \
  cpp_authority_layer_build_rejects_template_metaprogramming_constructs
do
  require_contains "$test_name" "$doc"
  require_contains "$test_name" "$test_file"
done

for build_policy_probe in \
  'expect_runner_denies' \
  'expect_runner_fixture_denies' \
  'copy_authority_fixture' \
  'expect_fixture_denies' \
  'required_runner_pattern' \
  'runner missing required pattern' \
  'missing_cflags' \
  'missing_c_standard_flag' \
  'missing_c_wall_flag' \
  'missing_c_wextra_flag' \
  'missing_c_werror_flag' \
  'missing_c_pedantic_flag' \
  'missing_c_wconversion_flag' \
  'missing_cxxflags' \
  'missing_cxx_standard_flag' \
  'missing_cxx_wall_flag' \
  'missing_cxx_wextra_flag' \
  'missing_cxx_werror_flag' \
  'missing_cxx_pedantic_flag' \
  'missing_cxx_wconversion_flag' \
  'missing_cxx_wshadow_flag' \
  'missing_cxx_fno_exceptions_flag' \
  'conflicting_c_standard' \
  'conflicting_cpp_standard' \
  'conflicting_cpp_exception_policy' \
  'conflicting_cpp_rtti_policy' \
  'weakened_warning_policy' \
  'weakened_cxx_warning_policy' \
  'unlisted_c_flag' \
  'unlisted_cxx_flag' \
  'unlisted_codegen_flag' \
  'unlisted_visibility_flag' \
  'unlisted_sanitizer_flag' \
  'unlisted_dependency_flag' \
  'unlisted_platform_flag' \
  'include_injection_flag' \
  'include_split_search_flag' \
  'include_forced_include_flag' \
  'include_attached_forced_include_flag' \
  'include_gnu_forced_include_flag' \
  'include_gnu_forced_include_equals_flag' \
  'include_system_search_flag' \
  'include_system_split_search_flag' \
  'include_quote_search_flag' \
  'include_quote_split_search_flag' \
  'include_after_search_flag' \
  'include_after_split_search_flag' \
  'include_macros_flag' \
  'include_attached_macros_flag' \
  'include_framework_prefix_flag' \
  'include_framework_split_prefix_flag' \
  'include_framework_search_flag' \
  'include_framework_split_search_flag' \
  'preprocessor_override_flag' \
  'preprocessor_define_split_flag' \
  'preprocessor_undef_flag' \
  'preprocessor_undef_split_flag' \
  'preprocessor_passthrough_flag' \
  'preprocessor_driver_passthrough_flag' \
  'linker_injection_flag' \
  'linker_library_path_flag' \
  'linker_library_flag' \
  'linker_binary_prefix_flag' \
  'linker_fuse_ld_flag' \
  'linker_tool_selector_flag' \
  'linker_shared_flag' \
  'linker_static_flag' \
  'linker_rdynamic_flag' \
  'linker_nostdlib_flag' \
  'linker_nodefaultlibs_flag' \
  'linker_nostartfiles_flag' \
  'linker_pie_flag' \
  'linker_no_pie_flag' \
  'linker_relocatable_flag' \
  'linker_thread_flag' \
  'linker_stdlib_flag' \
  'toolchain_escape_flag' \
  'toolchain_sysroot_flag' \
  'toolchain_isysroot_flag' \
  'toolchain_resource_dir_flag' \
  'toolchain_gcc_toolchain_flag' \
  'toolchain_ccc_gcc_name_flag' \
  'toolchain_plugin_flag' \
  'toolchain_plugin_arg_flag' \
  'toolchain_backend_flag' \
  'toolchain_assembler_flag' \
  'toolchain_wa_flag' \
  'ambient_compiler_environment' \
  'ambient_assembler_environment' \
  'ambient_include_path_environment' \
  'ambient_c_include_path_environment' \
  'ambient_cxx_include_path_environment' \
  'ambient_objc_include_path_environment' \
  'ambient_objcxx_include_path_environment' \
  'ambient_linker_environment' \
  'ambient_library_path_environment' \
  'ambient_ld_library_path_environment' \
  'ambient_ld_preload_environment' \
  'ambient_sdk_environment' \
  'ambient_macos_deployment_environment' \
  'ambient_developer_dir_environment' \
  'ambient_toolchains_environment' \
  'ambient_gcc_exec_prefix_environment' \
  'ambient_compiler_path_environment' \
  'ambient_ccc_override_environment' \
  'ambient_ccc_add_args_environment' \
  'ambient_dependency_output_environment' \
  'ambient_sunpro_dependency_environment' \
  'ambient_tool_selector' \
  'ambient_cxx_tool_selector' \
  'ambient_cpp_tool_selector' \
  'ambient_linker_tool_selector' \
  'ambient_object_tool_selector' \
  'ambient_archive_tool_selector' \
  'ambient_ranlib_tool_selector' \
  'ambient_strip_tool_selector' \
  'ambient_objdump_tool_selector' \
  'ambient_objcopy_tool_selector' \
  'ambient_readelf_tool_selector' \
  'ambient_size_tool_selector' \
  'ambient_libtool_selector' \
  'ambient_install_name_tool_selector' \
  'ambient_tool_prefix' \
  'ambient_distcc_prefix' \
  'ambient_dyld_prefix_surrogate' \
  'runner did not sanitize caller PATH' \
  'runner did not ignore caller TMPDIR' \
  'runner missing private /tmp authority build root' \
  'tmpdir="$(mktemp -d "/tmp/cpp-authority-layer.XXXXXX")"' \
  'lat_parser_o="$tmpdir/lat-parser.o"' \
  'lir_o="$tmpdir/lir.o"' \
  'authority_o="$tmpdir/cpp-authority.o"' \
  'authority_test="$tmpdir/cpp-authority-layer-invariants"' \
  'cc $CFLAGS' \
  '-c src/lat_parser.c' \
  '-c src/lir.c' \
  'c++ $CXXFLAGS' \
  '-c src/cpp/authority.cpp' \
  'tests/cpp_authority_layer_invariants.cpp' \
  'nm "$authority_o"' \
  'nm -g "$authority_o"' \
  'unwrapped_c_substrate_include' \
  'unwrapped_lir_c_substrate_include' \
  'direct_c_substrate_include' \
  'direct_lir_c_substrate_include' \
  'direct_state_lattice_c_substrate_include' \
  'unlisted_header_quote_include' \
  'unlisted_quote_include' \
  'spaced_preprocessor_includes' \
  'unlisted_standard_header' \
  'forbidden_iostream_header' \
  'forbidden_fstream_header' \
  'forbidden_filesystem_header' \
  'forbidden_thread_header' \
  'forbidden_future_header' \
  'forbidden_regex_header' \
  'forbidden_exception_header' \
  'forbidden_stdexcept_header' \
  'forbidden_string_header' \
  'forbidden_memory_header' \
  'forbidden_map_header' \
  'forbidden_unordered_map_header' \
  'forbidden_exception_rtti_construct' \
  'forbidden_throw_construct' \
  'forbidden_try_catch_construct' \
  'forbidden_dynamic_cast_construct' \
  'forbidden_reinterpret_cast_construct' \
  'forbidden_const_cast_construct' \
  'forbidden_raw_allocation_construct' \
  'forbidden_delete_construct' \
  'forbidden_malloc_call' \
  'forbidden_calloc_call' \
  'forbidden_realloc_call' \
  'forbidden_free_call' \
  'forbidden_container_type' \
  'forbidden_string_type' \
  'forbidden_shared_ptr_type' \
  'forbidden_unique_ptr_type' \
  'forbidden_map_type' \
  'forbidden_unordered_map_type' \
  'unlisted_std_api' \
  'framework_namespace' \
  'framework_kernel_namespace' \
  'framework_server_namespace' \
  'framework_recovery_namespace' \
  'io_process_call' \
  'forbidden_fopen_call' \
  'forbidden_freopen_call' \
  'forbidden_open_call' \
  'forbidden_creat_call' \
  'forbidden_read_call' \
  'forbidden_write_call' \
  'forbidden_socket_call' \
  'forbidden_connect_call' \
  'forbidden_bind_call' \
  'forbidden_listen_call' \
  'forbidden_accept_call' \
  'forbidden_send_call' \
  'forbidden_recv_call' \
  'forbidden_popen_call' \
  'forbidden_fork_call' \
  'forbidden_exec_call' \
  'forbidden_posix_spawn_call' \
  'c_substrate_function_call' \
  'c_substrate_lat_parse_source_call' \
  'c_substrate_lat_parse_report_call' \
  'c_substrate_lir_label_call' \
  'c_substrate_lir_lower_call' \
  'c_substrate_lir_report_call' \
  'c_substrate_state_default_call' \
  'c_substrate_state_no_effect_call' \
  'c_substrate_state_report_call' \
  'template_metaprogramming_construct' \
  'template_class_parameter' \
  'template_template_parameter' \
  'template_requires_token' \
  'template_concept_token' \
  'template_enable_if_api' \
  'template_conditional_api' \
  'template_integral_constant_api' \
  'template_is_trait_api' \
  'template_void_t_api' \
  'object_writable_global_symbol' \
  'object_common_data_symbol' \
  'object_c_substrate_symbol' \
  'object_allocation_symbol' \
  'object_operator_new_symbol' \
  'object_operator_delete_symbol' \
  'object_calloc_symbol' \
  'object_realloc_symbol' \
  'object_free_symbol' \
  'object_exception_rtti_symbol' \
  'object_cxa_exception_symbol' \
  'object_unwind_exception_symbol' \
  'object_typeinfo_symbol' \
  'object_typeinfo_name_symbol' \
  'object_vtable_symbol' \
  'object_indirect_exception_rtti_symbol' \
  'object_public_c_abi_symbol' \
  'object_public_unmangled_defined_symbol' \
  'weak_artifact_permissions' \
  'writable global data symbol emitted' \
  'forbidden C substrate function symbol emitted' \
  'allocation symbol emitted' \
  'exception or RTTI symbol emitted' \
  'public C ABI symbol emitted' \
  'public unmangled defined symbol emitted' \
  'private build artifact grants group/world access' \
  'reject_prefixed_environment_variable DYLD_' \
  'cpp_authority_layer_build_policy: ok'
do
  require_contains "$build_policy_probe" "$policy_runner"
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
  docs/CPP_AUTHORITY_IMPLEMENTATION_REVIEW.md \
  docs/status/CPP_AUTHORITY_IMPLEMENTATION_REVIEW_STATUS.md \
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

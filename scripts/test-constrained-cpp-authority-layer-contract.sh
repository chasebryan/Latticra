#!/usr/bin/env sh
set -eu

doc="docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'constrained c++ authority layer contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'constrained c++ authority layer contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: constrained C++ authority layer contract' "$doc"
require_contains 'C is the metal.' "$doc"
require_contains 'C++ is the disciplined structure.' "$doc"
require_contains 'Latticra is the contract.' "$doc"
require_contains 'This document does not implement C++ infrastructure' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Layer placement' "$doc"
require_contains 'Allowed C++ responsibilities' "$doc"
require_contains 'Forbidden C++ posture' "$doc"
require_contains 'Initial C++ standard policy' "$doc"
require_contains 'Ownership policy' "$doc"
require_contains 'Allocation policy' "$doc"
require_contains 'Exception policy' "$doc"
require_contains 'RTTI and reflection policy' "$doc"
require_contains 'Template policy' "$doc"
require_contains 'C ABI boundary policy' "$doc"
require_contains 'Effect gate policy' "$doc"
require_contains 'Audit policy' "$doc"
require_contains 'Validator policy' "$doc"
require_contains 'Error/result policy' "$doc"
require_contains 'Namespace and file policy' "$doc"
require_contains 'Build policy' "$doc"
require_contains 'Relationship to Lat' "$doc"
require_contains 'Relationship to LIR' "$doc"
require_contains 'Relationship to Nucleus' "$doc"
require_contains 'No-effect rule' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Future implementation gate' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/C_CPP_FOUNDATION_DIRECTION.md \
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

for layer in \
  'Lat / Latticra Language: contract and declaration layer' \
  'C++: governed authority layer' \
  'C: secure substrate' \
  'C++ must not bypass the C substrate contracts.'
do
  require_contains "$layer" "$doc"
done

for allowed in \
  'policy logic' \
  validators \
  'effect gates' \
  'audit logic' \
  'bounded orchestration structures' \
  'operator-visible reports' \
  'higher-level state coordination' \
  'safe wrappers around C substrate APIs'
do
  require_contains "$allowed" "$doc"
done

for forbidden_posture in \
  'unrestricted C++' \
  'exception-heavy C++' \
  'reflection-heavy C++' \
  'template metaprogramming as architecture' \
  'hidden allocation by default' \
  'implicit authority' \
  'unchecked host execution'
do
  require_contains "$forbidden_posture" "$doc"
done

for ownership in \
  'value types' \
  'references for non-owning views' \
  'span-like bounded views' \
  'unique ownership only where necessary' \
  'RAII wrappers for explicit resources' \
  'shared ownership by default' \
  'raw owning pointers' \
  'unbounded containers in authority paths' \
  'long-lived global singletons'
do
  require_contains "$ownership" "$doc"
done

for allocation in \
  'fixed-capacity containers' \
  'caller-provided buffers' \
  'bounded vectors with explicit capacity' \
  'arena-like allocation only if separately contracted' \
  'unbounded allocation in validators' \
  'unbounded allocation in effect gates' \
  'allocation hidden behind policy decisions' \
  'allocation hidden in report generation'
do
  require_contains "$allocation" "$doc"
done

for exception_policy in \
  'no exceptions across C ABI boundaries' \
  'no exceptions through effect gates' \
  'no exceptions through report generation' \
  'no exceptions for expected validation failures' \
  '-fno-exceptions'
do
  require_contains "$exception_policy" "$doc"
done

for rtti in \
  'no dynamic_cast in authority paths' \
  'no typeid-based authority decisions' \
  'no reflection-like dispatch as policy architecture'
do
  require_contains "$rtti" "$doc"
done

for template_rule in \
  'small fixed-capacity helpers' \
  'strong type wrappers' \
  'bounded view utilities' \
  'template metaprogramming as policy engine' \
  'type-level authority decisions without readable reports'
do
  require_contains "$template_rule" "$doc"
done

for abi in \
  'no C++ exceptions crossing C ABI' \
  'no C++ ownership crossing C ABI without wrappers' \
  'no raw C++ object lifetime exposed to C callers' \
  'status/result returns for boundary failures'
do
  require_contains "$abi" "$doc"
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

for audit in \
  'input source identity if available' \
  'source spans if available' \
  'policy name' \
  'validator name' \
  'requested effect' \
  'allowed or denied result' \
  'denial reason' \
  'no-effect flags'
do
  require_contains "$audit" "$doc"
done

for validator in \
  'naming validators' \
  'source-span validators' \
  'no-effect validators' \
  'effect validators' \
  'boundary validators' \
  'state-shape validators' \
  'LIR-shape validators' \
  'Lat-parse-result validators'
do
  require_contains "$validator" "$doc"
done

for result_label in \
  ok \
  null_argument \
  invalid_input \
  capacity_exceeded \
  policy_denied \
  unsupported_effect \
  unsupported_boundary \
  not_authorized \
  internal_error
do
  require_contains "$result_label" "$doc"
done

for path in \
  include/latticra/cpp/authority.hpp \
  src/cpp/authority.cpp \
  tests/cpp_authority_layer_invariants.cpp \
  scripts/test-cpp-authority-layer.sh
do
  require_contains "$path" "$doc"
done

for build in \
  'compiler flags' \
  'C++ standard version' \
  'warnings-as-errors policy' \
  'exception policy' \
  'RTTI policy' \
  'allocation policy' \
  'sanitizer or static-analysis path if available' \
  'CI test runner'
do
  require_contains "$build" "$doc"
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
  'no-effect flags'
do
  require_contains "$compat" "$doc"
done

for gate in \
  'public API shape' \
  'namespace and file paths' \
  'C++ standard version' \
  'compiler flags' \
  'exception policy' \
  'RTTI policy' \
  'allocation policy' \
  'ownership/lifetime rules' \
  'result/error labels' \
  'C ABI boundary rules' \
  'validator categories' \
  'audit report format' \
  'exact tests' \
  'compatibility expectations' \
  'non-claims'
do
  require_contains "$gate" "$doc"
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
  cpp_authority_layer_preserves_source_identity_in_audit \
  cpp_authority_layer_accepts_max_source_identity \
  cpp_authority_layer_rejects_oversized_source_identity \
  cpp_authority_layer_bounds_source_identity_before_audit_copy \
  cpp_authority_layer_rejects_nul_source_identity \
  cpp_authority_layer_rejects_line_break_source_identity \
  cpp_authority_layer_validates_lat_parse_result_metadata \
  cpp_authority_layer_validates_lir_shape_metadata \
  cpp_authority_layer_audit_report_is_deterministic \
  cpp_authority_layer_rejects_small_report_buffer \
  cpp_authority_layer_rejects_unterminated_audit_text \
  cpp_authority_layer_rejects_audit_text_line_breaks \
  cpp_authority_layer_rejects_noncanonical_audit_text_padding \
  cpp_authority_layer_is_deterministic \
  cpp_authority_layer_rejects_mutation_flags \
  cpp_authority_layer_rejects_network_flags \
  cpp_authority_layer_rejects_lat_network_flags \
  cpp_authority_layer_rejects_lir_network_flags \
  cpp_authority_layer_rejects_request_lat_network_flags \
  cpp_authority_layer_rejects_request_lir_network_flags \
  cpp_authority_layer_classifies_effects_without_performing_them \
  cpp_authority_layer_builds_with_fno_exceptions_and_fno_rtti
do
  require_contains "$test_name" "$doc"
done

for forbidden in \
  'become unrestricted C++' \
  'add C++ implementation before an implementation plan' \
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

require_contains 'sh scripts/test-constrained-cpp-authority-layer-contract.sh' "$doc"

printf 'constrained_cpp_authority_layer_contract: ok\n'

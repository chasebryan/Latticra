# Latticra Constrained C++ Authority Layer Contract

Status: constrained C++ authority layer contract
Scope: governed C++ policy, validator, effect-gate, audit, ownership, lifetime, allocation, exception, boundary, and non-claim rules before any C++ authority-layer implementation.

## Purpose

This document defines the first contract for the constrained C++ authority layer in Latticra.

It preserves the active direction:

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

C++ is permitted only as a governed authority layer above the C substrate.

This document does not implement C++ infrastructure, policy code, validators, effect gates, audit logic, orchestration, LIR lowering, Lat execution, L-UI rendering, runtime behavior, operating-system behavior, sandboxing, malware prevention, ransomware prevention, or production security guarantees.

## Relationship to previous work

This contract depends on:

```text
docs/C_CPP_FOUNDATION_DIRECTION.md
docs/LANGUAGE_STRATEGY.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
docs/EFFECT_GATES.md
docs/STATE_LATTICE.md
docs/TRI_PLANE_TRANSITION.md
docs/NUCLEUS_PREVIEW.md
include/latticra/lat_parser.h
include/latticra/lir.h
include/latticra/state_lattice.h
```

Those files remain the source of truth for the C substrate, Lat metadata parsing, LIR shape, effect vocabulary, state-lattice vocabulary, no-effect flags, and preview boundaries.

## Layer placement

The C++ authority layer sits above the C substrate and below future operator/runtime orchestration.

Layer model:

```text
Lat / Latticra Language: contract and declaration layer
C++: governed authority layer
C: secure substrate
```

C++ must not bypass the C substrate contracts.

## Allowed C++ responsibilities

C++ may be used for:

```text
policy logic
validators
effect gates
audit logic
bounded orchestration structures
operator-visible reports
higher-level state coordination
safe wrappers around C substrate APIs
```

These are authority responsibilities, not unchecked execution rights.

## Forbidden C++ posture

The C++ authority layer must not become:

```text
unrestricted C++
exception-heavy C++
reflection-heavy C++
template metaprogramming as architecture
hidden allocation by default
implicit authority
unchecked host execution
```

## Initial C++ standard policy

The first C++ authority-layer implementation should target:

```text
C++20 or later only if the implementation plan justifies it
```

Required subset posture:

```text
explicit ownership
explicit lifetimes
no ambient authority
no hidden execution
no implicit network behavior
no implicit hardware behavior
no implicit file-system behavior
no global mutable authority
```

## Ownership policy

Ownership must be explicit.

Allowed default patterns:

```text
value types
references for non-owning views
span-like bounded views
unique ownership only where necessary
RAII wrappers for explicit resources
```

Restricted patterns:

```text
shared ownership by default
raw owning pointers
unbounded containers in authority paths
implicit lifetime extension
long-lived global singletons
```

Any future use of `std::shared_ptr`, raw owning pointers, or global singletons must be justified in an implementation plan and guarded by tests or review rules.

## Allocation policy

C++ authority-layer code should avoid hidden allocation in core paths.

Preferred patterns:

```text
fixed-capacity containers
caller-provided buffers
bounded vectors with explicit capacity
arena-like allocation only if separately contracted
no allocation in no-effect report paths unless justified
```

Forbidden by default:

```text
unbounded allocation in validators
unbounded allocation in effect gates
allocation hidden behind policy decisions
allocation hidden in report generation
allocation during no-effect validation without explicit contract
```

## Exception policy

The first authority layer should not use exceptions for control flow.

Default policy:

```text
no exceptions across C ABI boundaries
no exceptions through effect gates
no exceptions through report generation
no exceptions for expected validation failures
```

Expected failures should use explicit result/status types.

A future implementation plan must decide whether the C++ build uses:

```text
-fno-exceptions
```

or a documented restricted exception boundary.

## RTTI and reflection policy

RTTI and reflection-like behavior are forbidden by default in the authority layer.

Default policy:

```text
no dynamic_cast in authority paths
no typeid-based authority decisions
no reflection-like dispatch as policy architecture
```

A future implementation plan must justify any exception.

## Template policy

Templates may support small generic utilities but must not become architecture.

Allowed:

```text
small fixed-capacity helpers
strong type wrappers
bounded view utilities
compile-time constants
```

Forbidden by default:

```text
template metaprogramming as policy engine
type-level authority decisions without readable reports
compile-time tricks that hide behavior
large framework-style abstractions
```

## C ABI boundary policy

C++ code must interact with the C substrate through explicit C-compatible boundaries.

Rules:

```text
no C++ exceptions crossing C ABI
no C++ ownership crossing C ABI without wrappers
no raw C++ object lifetime exposed to C callers
no hidden allocation behind C ABI functions
status/result returns for boundary failures
```

## Effect gate policy

C++ effect gates must start as no-effect validators.

They may classify or deny effects but must not perform effects.

Initial preserved flags:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
network_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Any transition from classification to allowed behavior requires a separate execution/effect contract.

## Audit policy

Audit logic must be deterministic, bounded, and operator-visible.

Audit records should preserve:

```text
input source identity if available
source spans if available
policy name
validator name
requested effect
allowed or denied result
denial reason
no-effect flags
```

Audit reports must not leak secrets, read files, open network connections, or mutate state.

## Validator policy

Validators should be small and named.

Initial validator categories:

```text
naming validators
source-span validators
no-effect validators
effect validators
boundary validators
state-shape validators
LIR-shape validators
Lat-parse-result validators
```

Validators must return explicit result values and stable labels.

## Error/result policy

A future C++ implementation should define a small result type.

Recommended labels:

```text
ok
null_argument
invalid_input
capacity_exceeded
policy_denied
unsupported_effect
unsupported_boundary
not_authorized
internal_error
```

The implementation plan must define exact names before code.

## Namespace and file policy

Recommended namespace:

```text
latticra
```

Recommended future file roots:

```text
include/latticra/cpp/authority.hpp
src/cpp/authority.cpp
tests/cpp_authority_layer_invariants.cpp
scripts/test-cpp-authority-layer.sh
scripts/test-cpp-authority-layer-build-policy.sh
```

Exact paths must be named by a separate implementation plan.

## Build policy

The future implementation plan must define:

```text
compiler flags
C++ standard version
warnings-as-errors policy
exception policy
RTTI policy
environment linker-injection policy
environment toolchain escape policy
ambient compiler environment policy
sanitized tool path policy
deterministic shell-tool locale policy
fixed temporary artifact root policy
private build artifact permission policy
runner command-shape self-check policy
allocation policy
sanitizer or static-analysis path if available
CI test runner
```

No C++ source files should be added before that implementation plan exists.

## Relationship to Lat

The current Lat parser is metadata-only.

C++ authority-layer work may validate Lat parser results in the future but must not execute Lat, compile Lat, interpret Lat, or lower Lat to LIR without separate contracts.

## Relationship to LIR

The current LIR shape implementation is metadata-only.

C++ authority-layer work may validate LIR shape metadata in the future but must not execute LIR or convert LIR into behavior without separate contracts.

## Relationship to Nucleus

Nucleus preview work remains no-effect.

C++ authority-layer planning may define future Nucleus policy validation, but must not call task execution or alter runtime behavior without separate contracts.

## No-effect rule

The constrained C++ authority layer starts as policy metadata and validation planning only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility expectations

This contract must not change:

```text
C substrate behavior
Lat parser behavior
LIR shape behavior
L-UI parser behavior
L-UI semantic validation behavior
state lattice behavior
Nucleus preview behavior
C/C++ foundation direction
language naming policy
no-effect flags
```

## Future implementation gate

C++ authority-layer implementation must not begin until a separate implementation plan defines:

1. public API shape;
2. namespace and file paths;
3. C++ standard version;
4. compiler flags;
5. exception policy;
6. RTTI policy;
7. allocation policy;
8. ownership/lifetime rules;
9. result/error labels;
10. C ABI boundary rules;
11. validator categories;
12. audit report format;
13. exact tests;
14. compatibility expectations;
15. non-claims.

## Future test list

A future implementation plan should include tests for:

```text
cpp_authority_layer_preserves_no_effect_flags
cpp_authority_layer_rejects_unrestricted_cpp_claims
cpp_authority_layer_has_no_execution_path
cpp_authority_layer_has_no_network_path
cpp_authority_layer_has_no_hardware_path
cpp_authority_layer_uses_explicit_result_labels
cpp_authority_layer_uses_stable_effect_labels
cpp_authority_layer_uses_stable_validator_labels
cpp_authority_layer_does_not_throw_across_c_boundary
cpp_authority_layer_public_api_contract_is_noexcept
cpp_authority_layer_does_not_allocate_in_report_path
cpp_authority_layer_preserves_source_identity_in_audit
cpp_authority_layer_accepts_max_source_identity
cpp_authority_layer_rejects_oversized_source_identity
cpp_authority_layer_bounds_source_identity_before_audit_copy
cpp_authority_layer_rejects_nul_source_identity
cpp_authority_layer_rejects_line_break_source_identity
cpp_authority_layer_rejects_requested_effect_out_of_vocabulary
cpp_authority_layer_validates_lat_parse_result_metadata
cpp_authority_layer_rejects_lat_parse_result_status_not_ok
cpp_authority_layer_rejects_lat_parse_error_not_ok
cpp_authority_layer_rejects_lat_source_span_out_of_bounds
cpp_authority_layer_rejects_lat_source_span_unordered
cpp_authority_layer_rejects_lat_module_declaration_count_out_of_bounds
cpp_authority_layer_rejects_lat_declaration_clause_range_out_of_bounds
cpp_authority_layer_rejects_lat_declaration_span_unordered
cpp_authority_layer_rejects_lat_declaration_span_out_of_bounds
cpp_authority_layer_rejects_lat_module_kind_counts_out_of_bounds
cpp_authority_layer_rejects_lat_declaration_kind_out_of_vocabulary
cpp_authority_layer_rejects_lat_clause_effect_out_of_vocabulary
cpp_authority_layer_rejects_lat_clause_span_unordered
cpp_authority_layer_rejects_lat_clause_span_out_of_bounds
cpp_authority_layer_validates_lir_shape_metadata
cpp_authority_layer_rejects_lir_module_status_not_ok
cpp_authority_layer_rejects_lir_error_not_ok
cpp_authority_layer_rejects_lir_source_span_out_of_bounds
cpp_authority_layer_rejects_lir_source_span_unordered
cpp_authority_layer_rejects_lir_node_child_range_out_of_bounds
cpp_authority_layer_rejects_lir_node_parent_index_out_of_bounds
cpp_authority_layer_rejects_lir_node_span_unordered
cpp_authority_layer_rejects_lir_node_span_out_of_bounds
cpp_authority_layer_rejects_lir_edge_node_index_out_of_bounds
cpp_authority_layer_rejects_lir_edge_span_unordered
cpp_authority_layer_rejects_lir_edge_span_out_of_bounds
cpp_authority_layer_rejects_lir_binding_node_index_out_of_bounds
cpp_authority_layer_rejects_lir_binding_span_unordered
cpp_authority_layer_rejects_lir_binding_span_out_of_bounds
cpp_authority_layer_rejects_lir_text_node_index_out_of_bounds
cpp_authority_layer_rejects_lir_text_length_exceeded
cpp_authority_layer_rejects_lir_text_span_unordered
cpp_authority_layer_rejects_lir_text_span_out_of_bounds
cpp_authority_layer_rejects_lir_edge_kind_counts_out_of_bounds
cpp_authority_layer_rejects_lir_module_enum_out_of_vocabulary
cpp_authority_layer_rejects_lir_node_kind_out_of_vocabulary
cpp_authority_layer_rejects_lir_edge_kind_out_of_vocabulary
cpp_authority_layer_rejects_lir_binding_kind_out_of_vocabulary
cpp_authority_layer_audit_report_is_deterministic
cpp_authority_layer_renders_report_header_and_record_fields
cpp_authority_layer_renders_record_no_effect_flags
cpp_authority_layer_renders_record_source_span_coordinates
cpp_authority_layer_rejects_small_report_buffer
cpp_authority_layer_rejects_null_report_buffer
cpp_authority_layer_rejects_too_many_audit_records
cpp_authority_layer_rejects_unterminated_audit_text
cpp_authority_layer_rejects_audit_text_line_breaks
cpp_authority_layer_rejects_noncanonical_audit_text_padding
cpp_authority_layer_rejects_noncanonical_policy_name
cpp_authority_layer_rejects_noncanonical_validator_name
cpp_authority_layer_rejects_report_status_out_of_vocabulary
cpp_authority_layer_rejects_audit_record_status_out_of_vocabulary
cpp_authority_layer_rejects_audit_record_validator_out_of_vocabulary
cpp_authority_layer_rejects_audit_record_effect_out_of_vocabulary
cpp_authority_layer_is_deterministic
cpp_authority_layer_rejects_mutation_flags
cpp_authority_layer_rejects_network_flags
cpp_authority_layer_rejects_lat_network_flags
cpp_authority_layer_rejects_lir_network_flags
cpp_authority_layer_rejects_all_request_no_effect_flag_deviations
cpp_authority_layer_rejects_all_lat_no_effect_flag_deviations
cpp_authority_layer_rejects_all_lir_no_effect_flag_deviations
cpp_authority_layer_rejects_request_lat_network_flags
cpp_authority_layer_rejects_request_lir_network_flags
cpp_authority_layer_accepts_request_with_valid_linked_metadata
cpp_authority_layer_rejects_request_lat_metadata_before_no_effect_allow
cpp_authority_layer_rejects_request_lir_metadata_before_no_effect_allow
cpp_authority_layer_classifies_effects_without_performing_them
cpp_authority_layer_builds_with_fno_exceptions_and_fno_rtti
cpp_authority_layer_build_rejects_missing_required_flags
cpp_authority_layer_build_rejects_conflicting_required_flags
cpp_authority_layer_build_rejects_unlisted_compiler_flags
cpp_authority_layer_build_rejects_environment_include_injection_flags
cpp_authority_layer_build_rejects_environment_macro_override_flags
cpp_authority_layer_build_rejects_environment_linker_injection_flags
cpp_authority_layer_build_rejects_environment_toolchain_escape_flags
cpp_authority_layer_build_rejects_ambient_compiler_environment_variables
cpp_authority_layer_build_rejects_ambient_dyld_environment_prefix
cpp_authority_layer_build_rejects_ambient_tool_selector_variables
cpp_authority_layer_build_uses_sanitized_tool_path
cpp_authority_layer_build_uses_absolute_shell_entrypoint
cpp_authority_layer_build_uses_deterministic_tool_locale
cpp_authority_layer_build_uses_fixed_temporary_root
cpp_authority_layer_build_uses_private_artifact_permissions
cpp_authority_layer_build_uses_cxx20_standard
cpp_authority_layer_build_uses_warnings_as_errors
cpp_authority_layer_build_uses_source_and_object_static_analysis_path
cpp_authority_layer_build_policy_self_checks_runner_command_shape
cpp_authority_layer_build_requires_extern_c_substrate_includes
cpp_authority_layer_build_rejects_unwrapped_c_substrate_includes
cpp_authority_layer_build_rejects_direct_c_substrate_includes
cpp_authority_layer_build_rejects_unlisted_quote_includes
cpp_authority_layer_build_rejects_spaced_preprocessor_includes
cpp_authority_layer_build_rejects_unlisted_standard_headers
cpp_authority_layer_build_rejects_unlisted_std_apis
cpp_authority_layer_build_rejects_writable_global_data_symbols
cpp_authority_layer_build_rejects_common_data_symbols
cpp_authority_layer_build_rejects_allocation_symbols
cpp_authority_layer_build_rejects_exception_and_rtti_symbols
cpp_authority_layer_build_rejects_indirect_exception_and_rtti_symbols
cpp_authority_layer_build_rejects_framework_namespaces
cpp_authority_layer_build_rejects_io_and_process_calls
cpp_authority_layer_build_rejects_c_substrate_function_calls
cpp_authority_layer_build_rejects_public_c_abi_symbols
cpp_authority_layer_build_rejects_public_unmangled_defined_symbols
cpp_authority_layer_build_rejects_template_metaprogramming_constructs
```

## Forbidden behavior

The C++ authority layer must not:

- become unrestricted C++;
- add C++ implementation before an implementation plan;
- execute Lat;
- execute LIR;
- render L-UI;
- call Nucleus task execution;
- mutate state;
- read files;
- write files;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- hide allocation in authority paths;
- throw exceptions across C ABI boundaries;
- use RTTI as policy architecture;
- use template metaprogramming as policy architecture;
- weaken C substrate boundaries;
- weaken no-effect flags;
- imply a sandbox, runtime, malware prevention, ransomware prevention, or operating-system surface.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-constrained-cpp-authority-layer-contract.sh
```

The guard is static. It does not implement C++ authority-layer code.

## Non-claims

This document does not implement C++ infrastructure, policy code, validators, effect gates, audit logic, orchestration, Lat execution, Lat compilation, Lat interpretation, LIR execution, LIR lowering, L-UI rendering, command behavior, Nucleus task execution, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

# Latticra Constrained C++ Authority Layer Implementation Plan

Status: implementation planning contract
Scope: exact public API, namespace, file paths, C++ standard, compiler flags, exception policy, RTTI policy, allocation policy, ownership/lifetime rules, result labels, C ABI boundaries, validators, audit reports, tests, compatibility expectations, and non-claims before any C++ authority-layer code.

## Purpose

This document defines the implementation plan for the first constrained C++ authority layer in Latticra.

The constrained C++ authority-layer contract is already merged and guarded. This plan turns that contract into exact API, namespace, file path, build, exception, RTTI, allocation, ownership, C ABI, validator, audit report, and test expectations before implementation code is added.

This document does not implement C++ infrastructure, policy code, validators, effect gates, audit logic, orchestration, Lat execution, LIR execution, L-UI rendering, runtime behavior, operating-system behavior, sandboxing, malware prevention, ransomware prevention, or production security guarantees.

## Direction checkpoint

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

The implementation must preserve this relationship:

```text
Lat / Latticra Language: contract and declaration layer
C++: governed authority layer
C: secure substrate
```

C++ must remain disciplined structure above the C substrate. It must not become unrestricted authority.

## Relationship to previous work

This plan depends on:

```text
docs/C_CPP_FOUNDATION_DIRECTION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
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

Those files remain the source of truth for the C substrate, Lat metadata parsing, LIR shape, effect vocabulary, state-lattice vocabulary, transition vocabulary, Nucleus preview boundaries, no-effect flags, and current non-claims.

## Implementation language decision

The first authority-layer implementation should be implemented in constrained C++20.

Reason:

- `std::span` and `std::string_view` are C++20-era tools that fit explicit bounded views;
- constrained C++ gives RAII, value types, scoped ownership, `enum class`, and namespace hygiene;
- the existing C substrate remains the source of truth for parsed Lat and LIR metadata;
- the C++ layer should validate and report over C-owned metadata, not replace the C substrate;
- C++ implementation must remain no-effect and must not add execution, mutation, network, recovery, hardware, or server behavior.

This decision does not permit unrestricted C++.

## Implementation files

The implementation PR should add or modify:

```text
include/latticra/cpp/authority.hpp
src/cpp/authority.cpp
tests/cpp_authority_layer_invariants.cpp
scripts/test-cpp-authority-layer.sh
.github/workflows/c.yml
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
```

The implementation PR should not add Lat execution, LIR execution, L-UI rendering, Nucleus task execution, file I/O, network I/O, state mutation, recovery behavior, update behavior, server interaction, hardware behavior, or security guarantees.

## Public namespace

Use the namespace:

```text
latticra
```

The first implementation must not create nested framework-style namespaces such as:

```text
latticra::runtime
latticra::kernel
latticra::server
latticra::recovery
```

Those names imply capabilities that do not exist yet.

## Public API shape

Add public C++ API names:

```text
latticra::authority_status
latticra::authority_effect
latticra::authority_validator
latticra::authority_flags
latticra::authority_source_span
latticra::authority_request
latticra::authority_audit_record
latticra::authority_audit_report
latticra::authority_status_label
latticra::authority_effect_label
latticra::authority_validator_label
latticra::validate_lat_parse_result
latticra::validate_lir_shape
latticra::classify_effect_request
latticra::render_authority_audit_report
```

Recommended function signatures:

```text
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
```

All public functions in the first implementation should be `noexcept` and return explicit status values.

## Capacity constants

Add exact bounded constants:

```text
LATTICRA_AUTHORITY_POLICY_NAME_MAX 64u
LATTICRA_AUTHORITY_VALIDATOR_NAME_MAX 64u
LATTICRA_AUTHORITY_DENIAL_REASON_MAX 128u
LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX 128u
LATTICRA_AUTHORITY_AUDIT_RECORD_MAX 32u
LATTICRA_AUTHORITY_REPORT_MAX 4096u
```

Recommended declaration style:

```text
inline constexpr std::size_t LATTICRA_AUTHORITY_POLICY_NAME_MAX = 64u;
```

The first implementation should reject or truncate nothing silently. Capacity failures must return `capacity_exceeded` and preserve deterministic audit state.

## Authority status enum

Add status enum values:

```text
authority_status::ok
authority_status::null_argument
authority_status::invalid_input
authority_status::capacity_exceeded
authority_status::policy_denied
authority_status::unsupported_effect
authority_status::unsupported_boundary
authority_status::not_authorized
authority_status::internal_error
```

Stable labels:

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

## Authority effect enum

Add effect enum values:

```text
authority_effect::none
authority_effect::read
authority_effect::local_mutation
authority_effect::host_mutation
authority_effect::network
authority_effect::hardware
authority_effect::boot
authority_effect::recovery
authority_effect::external
authority_effect::unknown
```

Stable labels:

```text
none
read
local_mutation
host_mutation
network
hardware
boot
recovery
external
unknown
```

Effects remain metadata only. Classification must not perform effects.

## Authority validator enum

Add validator enum values:

```text
authority_validator::naming
authority_validator::source_span
authority_validator::no_effect
authority_validator::effect
authority_validator::boundary
authority_validator::state_shape
authority_validator::lir_shape
authority_validator::lat_parse_result
```

Stable labels:

```text
naming
source_span
no_effect
effect
boundary
state_shape
lir_shape
lat_parse_result
```

Validators should be small, named, deterministic, and report-visible.

## Authority flags struct

Add no-effect flag fields:

```text
bool no_effect;
bool execution_allowed;
bool mutation_allowed;
bool server_allowed;
bool network_allowed;
bool recovery_allowed;
bool hardware_allowed;
```

The default valid authority-layer state is:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
network_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Any deviation must be denied by the first implementation.

## Authority source span struct

Use a C++ source-span struct compatible with existing C source-span conventions:

```text
std::size_t start_offset;
std::size_t end_offset;
std::size_t start_line;
std::size_t start_column;
std::size_t end_line;
std::size_t end_column;
```

The implementation may copy spans from Lat or LIR metadata. It must not invent byte offsets.

## Authority request struct

Add request metadata fields:

```text
authority_effect requested_effect;
authority_flags flags;
std::string_view source_identity;
const latticra_lat_parse_result_t *lat_result;
const latticra_lir_module_t *lir_module;
```

The first implementation must treat `source_identity` as a non-owning bounded view and must not retain it after the call returns.
When present and within bounds, the implementation should copy it into fixed audit storage.
The bound check must run before any audit record copies caller-provided source identity.
Source identity containing an embedded NUL must be rejected before report rendering.

## Authority audit record struct

Add audit record fields:

```text
authority_status status;
authority_validator validator;
authority_effect requested_effect;
authority_flags flags;
std::array<char, LATTICRA_AUTHORITY_POLICY_NAME_MAX> policy_name;
std::array<char, LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX + 1u> source_identity;
std::array<char, LATTICRA_AUTHORITY_VALIDATOR_NAME_MAX> validator_name;
std::array<char, LATTICRA_AUTHORITY_DENIAL_REASON_MAX> denial_reason;
authority_source_span span;
```

Audit records must be deterministic and must not contain secrets, file contents, environment values, or host-specific data.

## Authority audit report struct

Add audit report fields:

```text
authority_status status;
authority_flags flags;
std::array<authority_audit_record, LATTICRA_AUTHORITY_AUDIT_RECORD_MAX> records;
std::size_t record_count;
```

The report must be fully initialized on success and failure.

## Ownership and lifetime rules

The first implementation should use:

```text
value types
references for required non-owning inputs
std::span for bounded views when needed
std::string_view for non-owning text views
std::array for fixed storage
std::unique_ptr only if separately justified
RAII wrappers only for explicit local resources
```

The first implementation must not use:

```text
raw owning pointers
raw new/delete
std::shared_ptr
hidden global mutable state
long-lived singletons
unbounded std::vector in authority paths
unbounded std::string in authority paths
stored references into caller-owned buffers
implicit lifetime extension
```

## Allocation policy

The first implementation should avoid heap allocation in authority paths.

Required posture:

```text
fixed-capacity containers
caller-provided output buffers
no allocation in validators
no allocation in effect gates
no allocation in audit report rendering
no hidden allocation behind policy decisions
```

A later arena or allocator policy requires a separate contract.

## Exception policy

The first implementation should build with:

```text
-fno-exceptions
```

Rules:

```text
no throw expressions
no try/catch in authority paths
no exceptions across C ABI boundaries
no exceptions through effect gates
no exceptions through report generation
no exceptions for expected validation failures
```

Expected failures must use `authority_status`.

## RTTI and reflection policy

The first implementation should build with:

```text
-fno-rtti
```

Rules:

```text
no dynamic_cast in authority paths
no typeid-based authority decisions
no RTTI as policy architecture
no reflection-like dispatch
```

## Template policy

Allowed:

```text
small fixed-capacity helpers
strong type wrappers
constexpr constants
simple label helpers
std::array-based utility functions
```

Forbidden by default:

```text
template metaprogramming as policy engine
type-level authority decisions without readable reports
compile-time tricks that hide behavior
large framework-style abstractions
unreviewable generic dispatch
```

## Allowed standard library subset

The first implementation may use:

```text
<array>
<cstddef>
<cstdint>
<span>
<string_view>
<type_traits>
```

The first implementation must not use in authority paths:

```text
<iostream>
<fstream>
<filesystem>
<thread>
<future>
<regex>
<exception>
<stdexcept>
<vector>
<string>
<map>
<unordered_map>
```

Any exception requires a later implementation note and guard update.

## C ABI boundary plan

The first implementation should consume existing C substrate structs through included C headers only.

Rules:

```text
wrap C includes with extern "C" when included from C++
do not expose C++ object lifetimes to C callers
do not export raw C++ objects through a C ABI
do not let C++ exceptions cross C ABI boundaries
return explicit authority_status values for boundary failures
copy C metadata into fixed C++ report structures when needed
```

The first implementation should not add a public C ABI wrapper unless a follow-up plan requires C callers to invoke the C++ authority layer directly.

## Lat validation plan

`validate_lat_parse_result` should validate metadata only.

Required checks:

```text
Lat parse result status is successful before metadata validation succeeds
Lat no-effect flags are preserved
Lat execution_allowed is zero
Lat mutation_allowed is zero
Lat server_allowed is zero
Lat network_allowed is zero
Lat recovery_allowed is zero
Lat hardware_allowed is zero
Lat declaration and clause counts do not exceed declared capacity
Lat source spans are ordered and bounded
Lat effect metadata remains metadata only
```

The function must not execute Lat, compile Lat, interpret Lat, lower Lat to LIR, read files, write files, open network connections, or mutate state.

## LIR validation plan

`validate_lir_shape` should validate metadata only.

Required checks:

```text
LIR module metadata is bounded
LIR node counts do not exceed declared capacity
LIR edge counts do not exceed declared capacity
LIR source spans are ordered and bounded
LIR network_allowed is zero
LIR binding metadata remains metadata only
LIR text references use explicit lengths
LIR report behavior remains no-effect
```

The function must not execute LIR, render L-UI, execute Lat, call Nucleus task execution, read files, write files, open network connections, or mutate state.

## Effect classification plan

`classify_effect_request` should classify requested effects but must not perform them.

Initial behavior:

```text
none -> ok
read -> policy_denied
local_mutation -> policy_denied
host_mutation -> policy_denied
network -> policy_denied
hardware -> policy_denied
boot -> policy_denied
recovery -> policy_denied
external -> policy_denied
unknown -> unsupported_effect
```

This preserves the no-effect authority-layer starting point.

## Audit report format

`render_authority_audit_report` should emit a deterministic bounded report:

```text
CPP AUTHORITY REPORT
status=<authority-status-label>
record_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
network_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
record[0].policy=<policy-name>
record[0].source_identity=<source-identity>
record[0].validator=<validator-label>
record[0].requested_effect=<effect-label>
record[0].result=<authority-status-label>
record[0].denial_reason=<reason>
record[0].span_start_offset=<offset>
record[0].span_end_offset=<offset>
```

Small output buffers should return `authority_status::capacity_exceeded` and clear the buffer.

## Build policy

The first implementation test runner should use:

```text
CFLAGS="-std=c99 -Wall -Wextra -Werror -pedantic"
CXXFLAGS="-std=c++20 -Wall -Wextra -Werror -pedantic -fno-exceptions -fno-rtti"
```

The script should compile C substrate objects with `cc`, compile authority C++ objects with `c++`, and link with `c++`.

Recommended command shape:

```sh
tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-cpp-authority.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
cc $CFLAGS -Iinclude -c src/lat_parser.c -o "$tmpdir/latticra-lat-parser.o"
cc $CFLAGS -Iinclude -c src/lir.c -o "$tmpdir/latticra-lir.o"
c++ $CXXFLAGS -Iinclude -c src/cpp/authority.cpp -o "$tmpdir/latticra-cpp-authority.o"
c++ $CXXFLAGS -Iinclude tests/cpp_authority_layer_invariants.cpp "$tmpdir/latticra-cpp-authority.o" ... -o "$tmpdir/latticra-cpp-authority-layer-invariants"
```

The exact object list may include L-UI parser and semantic objects if LIR validation requires them.

## Exact implementation test list

The implementation PR should include tests for:

```text
cpp_authority_layer_preserves_no_effect_flags
cpp_authority_layer_rejects_unrestricted_cpp_claims
cpp_authority_layer_has_no_execution_path
cpp_authority_layer_has_no_network_path
cpp_authority_layer_has_no_hardware_path
cpp_authority_layer_uses_explicit_result_labels
cpp_authority_layer_does_not_throw_across_c_boundary
cpp_authority_layer_does_not_allocate_in_report_path
cpp_authority_layer_preserves_source_identity_in_audit
cpp_authority_layer_rejects_oversized_source_identity
cpp_authority_layer_bounds_source_identity_before_audit_copy
cpp_authority_layer_rejects_nul_source_identity
cpp_authority_layer_validates_lat_parse_result_metadata
cpp_authority_layer_validates_lir_shape_metadata
cpp_authority_layer_audit_report_is_deterministic
cpp_authority_layer_rejects_small_report_buffer
cpp_authority_layer_is_deterministic
cpp_authority_layer_rejects_mutation_flags
cpp_authority_layer_rejects_network_flags
cpp_authority_layer_rejects_lat_network_flags
cpp_authority_layer_rejects_lir_network_flags
cpp_authority_layer_rejects_request_lat_network_flags
cpp_authority_layer_rejects_request_lir_network_flags
cpp_authority_layer_classifies_effects_without_performing_them
cpp_authority_layer_builds_with_fno_exceptions_and_fno_rtti
```

## Test file plan

Add:

```text
tests/cpp_authority_layer_invariants.cpp
scripts/test-cpp-authority-layer.sh
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-constrained-cpp-authority-layer-implementation-plan.sh
```

and before:

```text
sh scripts/test-lat-language-grammar-contract.sh
```

## Documentation update plan

The implementation PR should update:

```text
README.md
STATUS.md
docs/FOUNDATION_INDEX.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
scripts/test-project-strategy-status-framework.sh
```

and add:

```text
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
```

## Compatibility expectations

The implementation must not change:

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
Lat grammar reports
LIR shape reports
```

## Forbidden implementation behavior

The first C++ authority-layer implementation must not:

- become unrestricted C++;
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

This implementation plan is guarded by:

```sh
sh scripts/test-constrained-cpp-authority-layer-implementation-plan.sh
```

The guard is static. It does not implement C++ authority-layer code.

## Implementation gate

Constrained C++ authority-layer implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement C++ infrastructure, policy code, validators, effect gates, audit logic, orchestration, Lat execution, Lat compilation, Lat interpretation, LIR execution, LIR lowering, L-UI rendering, command behavior, Nucleus task execution, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

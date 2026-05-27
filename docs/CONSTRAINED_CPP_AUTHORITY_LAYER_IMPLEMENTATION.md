# Latticra Constrained C++ Authority Layer Implementation

Status: initial implementation contract
Scope: first no-effect constrained C++ authority-layer API, fixed-capacity audit structures, Lat metadata validation, LIR metadata validation, effect classification, deterministic report rendering, build policy, invariant tests, compatibility expectations, and non-claims.

## Purpose

This document records the first constrained C++ authority-layer implementation in Latticra.

It follows:

```text
docs/C_CPP_FOUNDATION_DIRECTION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION_PLAN.md
```

The implementation keeps the active direction:

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

## Implementation files

This slice adds:

```text
include/latticra/cpp/authority.hpp
src/cpp/authority.cpp
tests/cpp_authority_layer_invariants.cpp
scripts/test-cpp-authority-layer.sh
```

The implementation is intentionally small and no-effect.

## Public API

The public API is:

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

All public functions return explicit status values and are declared `noexcept`.

## Capacity constants

The implementation defines:

```text
LATTICRA_AUTHORITY_POLICY_NAME_MAX 64u
LATTICRA_AUTHORITY_VALIDATOR_NAME_MAX 64u
LATTICRA_AUTHORITY_DENIAL_REASON_MAX 128u
LATTICRA_AUTHORITY_SOURCE_IDENTITY_MAX 128u
LATTICRA_AUTHORITY_AUDIT_RECORD_MAX 32u
LATTICRA_AUTHORITY_REPORT_MAX 4096u
```

The authority layer uses fixed-capacity structures and caller-provided output buffers.

## Result labels

Stable authority status labels:

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

## Effect labels

Stable authority effect labels:

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

Effects are metadata only. Classification does not perform effects.

## Validator labels

Stable authority validator labels:

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

## No-effect flags

The authority layer preserves:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
network_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Any mutation, execution, server, network, recovery, or hardware flag is denied.

## Lat metadata validation

`latticra::validate_lat_parse_result` validates Lat parser metadata only.

It checks:

```text
Lat parse result status
Lat parse error value
Lat no-effect flags
Lat network_allowed flag denial
Lat declaration capacity
Lat clause capacity
Lat module declaration capacity
Lat source-span ordering
Lat declaration source-span ordering
Lat clause source-span ordering
```

It does not execute, compile, interpret, lower, read files, write files, open network connections, or mutate state.

## LIR metadata validation

`latticra::validate_lir_shape` validates LIR shape metadata only.

It checks:

```text
LIR module status
LIR error value
LIR no-effect flags
LIR network_allowed flag denial
LIR node capacity
LIR edge capacity
LIR binding capacity
LIR text capacity
LIR source-span ordering
LIR text length bounds
```

It does not execute LIR, render L-UI, execute Lat, call Nucleus task execution, read files, write files, open network connections, or mutate state.

## Effect classification

`latticra::classify_effect_request` classifies requested effects without performing them.
If a request carries linked Lat or LIR metadata, classification also validates
that linked metadata before allowing even a no-effect request.
Bounded request source identity is copied into fixed audit storage and rendered
in the report; oversized source identity is denied before any audit copy.
Source identity containing an embedded NUL is rejected so report text cannot
silently truncate the identity.
Source identity containing line breaks is rejected so report text cannot inject
additional report lines.

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

## Audit report format

`latticra::render_authority_audit_report` emits a deterministic bounded report:

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

Small output buffers return `capacity_exceeded` and clear the buffer.
Unterminated fixed audit text fields return `invalid_input` and clear the buffer.
Fixed audit text fields containing line breaks return `invalid_input` and clear the buffer.

## Build policy

The test runner uses:

```text
CFLAGS="-std=c99 -Wall -Wextra -Werror -pedantic"
CXXFLAGS="-std=c++20 -Wall -Wextra -Werror -pedantic -fno-exceptions -fno-rtti"
```

The guard rejects forbidden authority-path headers and constructs including:

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
<map>
<unordered_map>
throw
try
catch
dynamic_cast
typeid
std::vector
std::shared_ptr
```

## Validation

Run:

```sh
sh scripts/test-cpp-authority-layer.sh
```

The test suite covers:

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
cpp_authority_layer_accepts_max_source_identity
cpp_authority_layer_rejects_oversized_source_identity
cpp_authority_layer_bounds_source_identity_before_audit_copy
cpp_authority_layer_rejects_nul_source_identity
cpp_authority_layer_rejects_line_break_source_identity
cpp_authority_layer_validates_lat_parse_result_metadata
cpp_authority_layer_validates_lir_shape_metadata
cpp_authority_layer_audit_report_is_deterministic
cpp_authority_layer_rejects_small_report_buffer
cpp_authority_layer_rejects_unterminated_audit_text
cpp_authority_layer_rejects_audit_text_line_breaks
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

## Compatibility expectations

This implementation must not change:

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

## Current boundary

This implementation does not provide:

```text
unrestricted C++ authority
Lat execution
Lat compilation
Lat interpretation
LIR execution
LIR lowering
L-UI rendering
Nucleus task execution
file I/O
network I/O
state mutation
server interaction
self-update
recovery behavior
hardware behavior
sandboxing
malware prevention
ransomware prevention
operating-system completeness
```

## Non-claims

This document and implementation do not claim a finished operating system, hardened sandbox, production runtime, production security boundary, malware prevention, ransomware prevention, recovery system, update system, bootable image, or public release readiness.

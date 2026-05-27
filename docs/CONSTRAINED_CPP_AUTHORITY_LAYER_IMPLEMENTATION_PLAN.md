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

- `std::string_view` and fixed-capacity `std::array` fit explicit bounded views;
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
scripts/test-cpp-authority-layer-build-policy.sh
scripts/test-constrained-cpp-authority-layer-implementation-plan.sh
.github/workflows/c.yml
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION_PLAN.md
docs/CPP_AUTHORITY_IMPLEMENTATION_REVIEW.md
docs/status/CPP_AUTHORITY_IMPLEMENTATION_REVIEW_STATUS.md
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

All public functions in the first implementation should be `noexcept`.
Validation, classification, and report-rendering functions should return
explicit `authority_status` values.

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
Source identity containing line breaks must be rejected before report rendering.

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
malloc/calloc/realloc/free
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
<string_view>
```

`<type_traits>` is test-only for public API static assertions; it is not part of
the authority-path source subset. `std::span` remains a future bounded-view
candidate and requires an explicit guard update before authority-path use.

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
<memory>
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
Lat parse error value is successful before metadata validation succeeds
Lat no-effect flags are preserved
Lat execution_allowed is zero
Lat mutation_allowed is zero
Lat server_allowed is zero
Lat network_allowed is zero
Lat recovery_allowed is zero
Lat hardware_allowed is zero
Lat declaration and clause counts do not exceed declared capacity
Lat module declaration count is bounded by materialized declarations
Lat module kind counts are bounded by materialized declarations
Lat declaration kinds stay inside the known Lat vocabulary
Lat declaration clause ranges are bounded
Lat clause effects stay inside the known Lat effect vocabulary
Lat source spans are ordered and bounded
Lat declaration source spans are bounded
Lat clause source spans are bounded
Lat effect metadata remains metadata only
```

The function must not execute Lat, compile Lat, interpret Lat, lower Lat to LIR, read files, write files, open network connections, or mutate state.

## LIR validation plan

`validate_lir_shape` should validate metadata only.

Required checks:

```text
LIR module status is successful before metadata validation succeeds
LIR error value is successful before metadata validation succeeds
LIR module metadata is bounded
LIR module enums stay inside known LIR vocabularies
LIR node counts do not exceed declared capacity
LIR node kinds stay inside the known LIR vocabulary
LIR edge counts do not exceed declared capacity
LIR edge kinds stay inside the known LIR vocabulary
LIR edge kind counts are bounded by materialized edges
LIR binding kinds stay inside the known LIR vocabulary
LIR source spans are ordered and bounded
LIR node source spans are bounded
LIR edge source spans are bounded
LIR binding source spans are bounded
LIR text source spans are bounded
LIR node child ranges are bounded
LIR node parent indexes are bounded
LIR edge node indexes are bounded
LIR binding node indexes are bounded
LIR text node indexes are bounded
LIR execution_allowed is zero
LIR mutation_allowed is zero
LIR server_allowed is zero
LIR network_allowed is zero
LIR recovery_allowed is zero
LIR hardware_allowed is zero
LIR binding metadata remains metadata only
LIR text references use explicit lengths
LIR report behavior remains no-effect
```

The function must not execute LIR, render L-UI, execute Lat, call Nucleus task execution, read files, write files, open network connections, or mutate state.

## Effect classification plan

`classify_effect_request` should classify requested effects but must not perform them.
If request metadata includes Lat or LIR pointers, classification should
validate the linked metadata before allowing even a no-effect request.

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
Requested effects outside the authority effect vocabulary should return
`authority_status::invalid_input` and be recorded as `unknown` so invalid enum
values cannot silently pick a fallback report label.

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
record[0].no_effect=<0|1>
record[0].execution_allowed=<0|1>
record[0].mutation_allowed=<0|1>
record[0].server_allowed=<0|1>
record[0].network_allowed=<0|1>
record[0].recovery_allowed=<0|1>
record[0].hardware_allowed=<0|1>
record[0].result=<authority-status-label>
record[0].denial_reason=<reason>
record[0].span_start_offset=<offset>
record[0].span_end_offset=<offset>
record[0].span_start_line=<line>
record[0].span_start_column=<column>
record[0].span_end_line=<line>
record[0].span_end_column=<column>
```

Small output buffers should return `authority_status::capacity_exceeded` and clear the buffer.
Null output buffers should return `authority_status::null_argument`.
Audit report record counts larger than `LATTICRA_AUTHORITY_AUDIT_RECORD_MAX`
should return `authority_status::capacity_exceeded` and clear the buffer.
Unterminated fixed audit text fields should return `authority_status::invalid_input` and clear the buffer.
Fixed audit text fields containing line breaks should return `authority_status::invalid_input` and clear the buffer.
Fixed audit text fields with nonzero bytes after their first NUL terminator should return `authority_status::invalid_input` and clear the buffer.
Audit-record policy and validator name text must match the canonical
authority policy name and validator enum label.
Report status values and audit-record status, validator, and requested-effect
values outside their authority vocabularies should return
`authority_status::invalid_input` and clear the buffer.

## Build policy

The first implementation test runner should use:

```text
CFLAGS="-std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow"
CXXFLAGS="-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti"
```

The runner should reject environment-provided `CFLAGS` or `CXXFLAGS` that omit
the required flag fragments before compiling.
The negative missing-required-flag probes should cover every required C and C++
standard, warning, warnings-as-errors, no-exceptions, and no-RTTI flag fragment.
The runner should reject conflicting environment-provided flags that override
the required C99, C++20, no-exceptions, no-RTTI, or warnings-as-errors policy.
The negative flag-policy probes should cover conflicting C and C++ standards,
exception and RTTI re-enablement, and C/C++ warning-policy weakening.
The runner should reject any `CFLAGS` or `CXXFLAGS` fragment outside the
declared flag allowlists, so optimization, codegen, visibility, sanitizer,
dependency, or platform flags cannot alter authority objects or the authority
test binary.
The negative unlisted-flag probes should cover the C flag allowlist, the C++
flag allowlist, and optimization, codegen, visibility, sanitizer, dependency,
and platform flag classes.
It should reject environment-provided include path or forced-include flags such
as `-I`, `-isystem`, `-iquote`, `-idirafter`, `-include`, `-imacros`, `-F`,
and `-iframework` so caller flags cannot shadow or preinclude authority or C
substrate headers.
The negative include-flag probes should cover split and joined search-path
forms, split and joined forced-include/macro forms, GNU `--include` forms, and
split and joined framework forms.
It should reject environment-provided preprocessor macro override flags such
as `-D`, `-U`, `-Wp,*`, and `-Xpreprocessor` so caller flags cannot redefine
authority or C substrate contracts.
The negative preprocessor-override probes should cover joined and split
define/undef forms plus driver pass-through forms.
It should reject environment-provided linker injection flags in `CXXFLAGS`,
such as `-Wl,*`, `-Xlinker`, `-L`, `-l`, `-B`, `-fuse-ld=*`, `-shared`,
`-static`, `-rdynamic`, `-nostdlib`, `-nodefaultlibs`, `-nostartfiles`,
`-pie`, `-no-pie`, `-r`, `-pthread`, and `-stdlib=*`, so caller flags cannot
alter the final authority test link.
It should reject environment-provided toolchain escape flags such as
`--sysroot`, `-isysroot`, `-resource-dir`, `-gcc-toolchain`, `-ccc-gcc-name`,
`-fplugin=*`, `-fplugin-arg-*`, `-Xclang`, `-mllvm`, `-Xassembler`, and
`-Wa,*` so caller flags cannot redirect the compiler resource/sysroot, inject
compiler plugins, or pass opaque options through the compiler driver.
It should reject ambient compiler and linker environment variables such as
`CPPFLAGS`, `LDFLAGS`, `ASFLAGS`, `CPATH`, `C_INCLUDE_PATH`,
`CPLUS_INCLUDE_PATH`, `LIBRARY_PATH`, `LD_LIBRARY_PATH`, `LD_PRELOAD`,
`DYLD_*`, `SDKROOT`, `MACOSX_DEPLOYMENT_TARGET`, `DEVELOPER_DIR`,
`TOOLCHAINS`, `GCC_EXEC_PREFIX`, `COMPILER_PATH`, `CCC_OVERRIDE_OPTIONS`,
and dependency-output variables so the build cannot be altered outside the
declared `CFLAGS` and `CXXFLAGS`.
The `DYLD_*` rejection should be prefix-wide, not limited to a fixed list of
known dynamic-loader variable names.
The negative prefix-helper fixture should prove prefix matching with a
non-DYLD surrogate prefix, while the runner self-check pins the real `DYLD_`
rejection call; this keeps the probe portable on platforms that strip
`DYLD_*` before `/bin/sh` starts.
It should reject ambient tool-selector variables such as `CC`, `CXX`, `CPP`,
`LD`, `NM`, `AR`, `RANLIB`, `STRIP`, `OBJDUMP`, `OBJCOPY`, `READELF`, `SIZE`,
`LIBTOOL`, and `INSTALL_NAME_TOOL`, plus `CCACHE_*` and `DISTCC_*` prefixes, so
callers cannot imply alternate compiler, linker, or object-inspection tools.
It should reset `PATH` to `/usr/bin:/bin:/usr/sbin:/sbin` before resolving
the compiler, linker, shell utility, and object-inspection commands used by
the authority runner.
It should use an absolute `/bin/sh` shebang instead of `/usr/bin/env sh`, so
direct runner invocation does not resolve the shell through caller-controlled
`PATH`.
It should force `LC_ALL=C` and `LANG=C` before source-token and object-symbol
analysis so shell tool matching is locale-stable.
It should ignore caller-provided `TMPDIR`, create a private authority build
directory under `/tmp` directly, export `TMPDIR` to that private directory for
compiler-driver temporaries, and set `umask 077` before creating authority
build artifacts so intermediate objects and test binaries are private to the
invoking user by default.
It should verify the private temporary directory, C substrate objects, C++
authority object, and authority test binary do not grant group or world
permissions before executing the authority test binary.
It should also reject `-Wno-*` flags that disable required warnings such as
`-Wconversion` or `-Wshadow`.
The C++ standard version policy is constrained C++20, enforced through
`-std=c++20` in `CXXFLAGS`.
The warnings-as-errors policy is mandatory for both C substrate objects and
C++ authority objects through `-Werror` in `CFLAGS` and `CXXFLAGS`.

The runner should require the C++ authority header to wrap the C substrate
includes with `extern "C"`.
The runner should reject any authority-header `latticra/lat_parser.h` or
`latticra/lir.h` include that appears outside that `extern "C"` block.
The runner should reject direct C substrate includes from `src/cpp/authority.cpp`;
the public C++ authority header owns the C include boundary.
The runner should allowlist quoted includes in the authority path: the C++
authority header may include only `latticra/lat_parser.h` and `latticra/lir.h`,
and `src/cpp/authority.cpp` may include only `latticra/cpp/authority.hpp`.
The include guards should match normal preprocessor whitespace, including
leading spaces and `# include`, so directive formatting cannot bypass the
authority include allowlists or C substrate include boundary.
The include-boundary fixture probes should cover unwrapped
`latticra/lat_parser.h` and `latticra/lir.h` authority-header includes, direct
`latticra/lat_parser.h`, `latticra/lir.h`, and `latticra/state_lattice.h`
source includes, and both header/source quoted-include allowlists.

The script should compile C substrate objects with `cc`, compile authority C++ objects with `c++`, and link the C and C++ objects together with `c++`.

Recommended command shape:

```sh
tmpdir="$(mktemp -d "/tmp/cpp-authority-layer.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
TMPDIR="$tmpdir"
export TMPDIR
cc $CFLAGS -Iinclude -c src/lat_parser.c -o "$tmpdir/latticra-lat-parser.o"
cc $CFLAGS -Iinclude -c src/lir.c -o "$tmpdir/latticra-lir.o"
c++ $CXXFLAGS -Iinclude -c src/cpp/authority.cpp -o "$tmpdir/latticra-cpp-authority.o"
c++ $CXXFLAGS -Iinclude tests/cpp_authority_layer_invariants.cpp "$tmpdir/latticra-cpp-authority.o" "$tmpdir/latticra-lat-parser.o" "$tmpdir/latticra-lir.o" -o "$tmpdir/latticra-cpp-authority-layer-invariants"
```

The exact object list may include additional C substrate objects if later LIR validation requires them.

The build guard should allow only the declared standard library subset, reject
raw allocation constructs in authority-path source, and reject writable global
data symbols in the compiled authority object.
The companion build-policy test should run negative probes against the
authority runner for missing required flags, conflicting flags, warning
weakening, unlisted flags, include injection, macro override, linker injection,
toolchain escape, ambient compiler variables, ambient tool selectors, and
ambient tool prefixes. The flag probes should cover forced-include and search
path variants, macro undef/pass-through variants, linker library/selector/mode
variants, and sysroot/plugin/backend/assembler toolchain escape variants. It should also prove
ambient include-path, library-path, SDK, compiler-path, and dependency-output
variables are rejected before the authority build. They should also cover
assembler, C include path, Objective-C include path, loader path/preload,
deployment-target, developer-dir, toolchains, GCC exec-prefix, compiler
override/add-args, and SunPro dependency-output variables. The ambient
tool-selector probes should cover C/C++ compiler, preprocessor, linker,
archive/index, binary-inspection, libtool, and install-name selectors. It
should also prove caller
`PATH` cannot steer tool
resolution and caller `TMPDIR` cannot steer the authority build root away from
the runner's private `mktemp -d` authority workdir template. It should
self-check the authority runner command-shape
fragments so the C substrate object compile, authority C++ object compile, C++
test link, and `nm` object-inspection steps remain tied to the documented
authority runner paths and object variables. It should run mutated authority
source/header fixtures
through the runner to prove source-token guards reject unwrapped C substrate
includes, direct C substrate includes, unlisted quoted includes, spaced
preprocessor includes, unlisted standard headers, forbidden exception/RTTI
constructs, raw allocation constructs, forbidden C++ ownership/container
types, forbidden file/system standard headers, unlisted `std::` APIs,
framework namespaces, I/O or process calls, C substrate function calls, and
template metaprogramming constructs.
The ownership/container fixture probes should cover `std::vector`,
`std::string`, `std::shared_ptr`, `std::unique_ptr`, `std::map`, and
`std::unordered_map` authority-path tokens.
The forbidden standard-library header fixture probes should cover the named
file, system, exception, thread, regex, string, memory, map, and unordered-map
headers forbidden by the authority-path subset.
The exception, RTTI, and cast fixture probes should cover `throw`, `try`,
`catch`, `dynamic_cast`, `typeid`, `reinterpret_cast`, and `const_cast`
authority-path tokens.
The raw and C allocation fixture probes should cover `new`, `delete`,
`malloc`, `calloc`, `realloc`, and `free` authority-path tokens.
It should run mutated authority source fixtures that compile far enough to
prove object-symbol guards reject writable global data, common data symbols,
emitted `latticra_*` symbols, allocation symbols, exception/RTTI symbols,
indirect exception/RTTI symbols, public C ABI symbols, and public unmangled
defined symbols.
It should run a mutated runner fixture with weakened `umask` settings to prove
the private artifact-permission guard rejects group/world-readable build
artifacts.
The object-symbol guard should treat `nm` common symbols (`C`/`c`) as rejected
writable global data.
The first implementation static-analysis path is the source-token and object
symbol analysis embedded in `scripts/test-cpp-authority-layer.sh`; no separate
sanitizer runtime is required for this no-effect authority layer.
The runner should reject authority-path standard library headers outside the
declared subset.
The runner should reject authority-path `std::` API names outside the declared
subset.
It should also reject allocation symbols in the compiled authority object,
including `operator new`, `operator delete`, `malloc`, `calloc`, `realloc`,
and `free`.
The object allocation-symbol fixture probes should cover `operator new`,
`operator delete`, `malloc`, `calloc`, `realloc`, and `free` emitted symbols.
It should reject exception-runtime and RTTI/typeinfo symbols in the compiled
authority object.
The object exception/RTTI fixture probes should cover `__gxx_personality`,
`__cxa`, `__Unwind`, `_ZTI`, `_ZTS`, and `_ZTV` emitted symbol families.
The object-symbol guard should also reject indirect exception-runtime and
RTTI/typeinfo references such as `DW.ref.__gxx_personality_v0`.
It should reject framework-style namespaces such as `latticra::runtime`,
`latticra::kernel`, `latticra::server`, and `latticra::recovery` in the
authority path.
The framework-namespace fixture probes should cover `latticra::runtime`,
`latticra::kernel`, `latticra::server`, and `latticra::recovery` authority-path
namespace tokens.
It should reject obvious file I/O, network socket, and process-launch call
tokens in authority-path source.
The I/O, network, and process-call fixture probes should cover file calls
`fopen`, `freopen`, `open`, `creat`, `read`, and `write`; socket calls
`socket`, `connect`, `bind`, `listen`, `accept`, `send`, and `recv`; and
process calls `system`, `popen`, `fork`, `exec*`, and `posix_spawn`.
It should reject any authority-path `latticra_*` C substrate function call
expression and any emitted `latticra_*` C substrate symbol from the compiled
authority object; the layer may consume C structs and enums but must not call
C substrate behavior, report, or helper functions.
The C substrate call fixture probes should cover Lat helper, parse, and report
calls; LIR helper, lower, and report calls; and state-lattice default,
no-effect, and report calls.
It should reject public unmangled C ABI text symbols in the compiled authority
object.
It should reject any public unmangled defined symbol in the compiled authority
object, including non-text data symbols.
It should reject generic template metaprogramming constructs in authority-path
source while still allowing fixed-size helper templates.
The template-policy fixture probes should cover `template <typename>`,
`template <class>`, template-template parameters, `requires`, `concept`,
`std::enable_if`, `std::conditional`, `std::integral_constant`, `std::is_*`,
and `std::void_t` authority-path tokens.
The template-policy source-token check should run before the general unlisted
`std::` API check so standard-library metaprogramming helpers receive the
template-policy denial.

## Exact implementation test list

The implementation PR should include tests for:

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

## Test file plan

Add:

```text
tests/cpp_authority_layer_invariants.cpp
scripts/test-cpp-authority-layer.sh
scripts/test-cpp-authority-layer-build-policy.sh
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
docs/CPP_AUTHORITY_IMPLEMENTATION_REVIEW.md
docs/status/CPP_AUTHORITY_IMPLEMENTATION_REVIEW_STATUS.md
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

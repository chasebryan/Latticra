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
scripts/test-cpp-authority-layer-build-policy.sh
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

All public functions are declared `noexcept`.
Validation, classification, and report-rendering functions return explicit
`authority_status` values.

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
Lat execution_allowed flag denial
Lat mutation_allowed flag denial
Lat server_allowed flag denial
Lat network_allowed flag denial
Lat recovery_allowed flag denial
Lat hardware_allowed flag denial
Lat declaration capacity
Lat clause capacity
Lat module declaration capacity
Lat module declaration count bounds
Lat module kind count bounds
Lat declaration kind vocabulary
Lat declaration clause range bounds
Lat clause effect vocabulary
Lat source-span ordering
Lat source-span source bounds
Lat declaration source-span ordering
Lat declaration source-span source bounds
Lat clause source-span ordering
Lat clause source-span source bounds
```

It does not execute, compile, interpret, lower, read files, write files, open network connections, or mutate state.

## LIR metadata validation

`latticra::validate_lir_shape` validates LIR shape metadata only.

It checks:

```text
LIR module status
LIR error value
LIR module enum vocabulary
LIR no-effect flags
LIR execution_allowed flag denial
LIR mutation_allowed flag denial
LIR server_allowed flag denial
LIR network_allowed flag denial
LIR recovery_allowed flag denial
LIR hardware_allowed flag denial
LIR node capacity
LIR node kind vocabulary
LIR edge capacity
LIR edge kind vocabulary
LIR edge kind count bounds
LIR binding capacity
LIR binding kind vocabulary
LIR text capacity
LIR source-span ordering
LIR source-span source bounds
LIR node source-span source bounds
LIR edge source-span source bounds
LIR binding source-span source bounds
LIR text source-span source bounds
LIR node child range bounds
LIR node parent index bounds
LIR edge node index bounds
LIR binding node index bounds
LIR text node index bounds
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
Requested effects outside the authority effect vocabulary are rejected and
recorded as `unknown` so invalid enum values cannot silently pick a fallback
report label.

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

Small output buffers return `capacity_exceeded` and clear the buffer.
Null output buffers return `null_argument`.
Audit report record counts larger than `LATTICRA_AUTHORITY_AUDIT_RECORD_MAX`
return `capacity_exceeded` and clear the buffer.
Unterminated fixed audit text fields return `invalid_input` and clear the buffer.
Fixed audit text fields containing line breaks return `invalid_input` and clear the buffer.
Fixed audit text fields with nonzero bytes after their first NUL terminator return `invalid_input` and clear the buffer.
Audit-record policy and validator name text must match the canonical
authority policy name and validator enum label.
Report status values and audit-record status, validator, and requested-effect
values outside their authority vocabularies return `invalid_input` and clear
the buffer.

## Build policy

The test runner uses:

```text
CFLAGS="-std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow"
CXXFLAGS="-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti"
```

The runner rejects environment-provided `CFLAGS` or `CXXFLAGS` that omit the
required flag fragments before compiling.
The negative missing-required-flag probes cover every required C and C++
standard, warning, warnings-as-errors, no-exceptions, and no-RTTI flag fragment.
It rejects conflicting environment-provided flags that override the required
C99, C++20, no-exceptions, no-RTTI, or warnings-as-errors policy.
The negative flag-policy probes cover conflicting C and C++ standards,
exception and RTTI re-enablement, and C/C++ warning-policy weakening.
It rejects any `CFLAGS` or `CXXFLAGS` fragment outside the declared flag
allowlists, so optimization, codegen, visibility, sanitizer, dependency, or
platform flags cannot alter authority objects or the authority test binary.
The negative unlisted-flag probes cover the C flag allowlist, the C++ flag
allowlist, and optimization, codegen, visibility, sanitizer, dependency, and
platform flag classes.
It rejects environment-provided include path or forced-include flags such as
`-I`, `-isystem`, `-iquote`, `-idirafter`, `-include`, `-imacros`, `-F`, and
`-iframework` so caller flags cannot shadow or preinclude authority or C
substrate headers.
The negative include-flag probes cover split and joined search-path forms,
split and joined forced-include/macro forms, GNU `--include` forms, and split
and joined framework forms.
It rejects environment-provided preprocessor macro override flags such as
`-D`, `-U`, `-Wp,*`, and `-Xpreprocessor` so caller flags cannot redefine
authority or C substrate contracts.
The negative preprocessor-override probes cover joined and split define/undef
forms plus driver pass-through forms.
It rejects environment-provided linker injection flags in `CXXFLAGS`, such as
`-Wl,*`, `-Xlinker`, `-L`, `-l`, `-B`, `-fuse-ld=*`, `-shared`, `-static`,
`-rdynamic`, `-nostdlib`, `-nodefaultlibs`, `-nostartfiles`, `-pie`,
`-no-pie`, `-r`, `-pthread`, and `-stdlib=*`, so caller flags cannot alter
the final authority test link.
It rejects environment-provided toolchain escape flags such as `--sysroot`,
`-isysroot`, `-resource-dir`, `-gcc-toolchain`, `-ccc-gcc-name`, `-fplugin=*`,
`-fplugin-arg-*`, `-Xclang`, `-mllvm`, `-Xassembler`, and `-Wa,*` so caller
flags cannot redirect the compiler resource/sysroot, inject compiler plugins,
or pass opaque options through the compiler driver.
It rejects ambient compiler and linker environment variables such as
`CPPFLAGS`, `LDFLAGS`, `ASFLAGS`, `CPATH`, `C_INCLUDE_PATH`,
`CPLUS_INCLUDE_PATH`, `LIBRARY_PATH`, `LD_LIBRARY_PATH`, `LD_PRELOAD`,
`DYLD_*`, `SDKROOT`, `MACOSX_DEPLOYMENT_TARGET`, `DEVELOPER_DIR`,
`TOOLCHAINS`, `GCC_EXEC_PREFIX`, `COMPILER_PATH`, `CCC_OVERRIDE_OPTIONS`,
and dependency-output variables so the build cannot be altered outside the
declared `CFLAGS` and `CXXFLAGS`.
The `DYLD_*` rejection is prefix-wide, not limited to a fixed list of known
dynamic-loader variable names.
The negative prefix-helper fixture proves prefix matching with a non-DYLD
surrogate prefix, while the runner self-check pins the real `DYLD_` rejection
call; this keeps the probe portable on platforms that strip `DYLD_*` before
`/bin/sh` starts.
It rejects ambient tool-selector variables such as `CC`, `CXX`, `CPP`, `LD`,
`NM`, `AR`, `RANLIB`, `STRIP`, `OBJDUMP`, `OBJCOPY`, `READELF`, `SIZE`,
`LIBTOOL`, and `INSTALL_NAME_TOOL`, plus `CCACHE_*` and `DISTCC_*` prefixes, so
callers cannot imply alternate compiler, linker, or object-inspection tools.
It resets `PATH` to `/usr/bin:/bin:/usr/sbin:/sbin` before resolving the
compiler, linker, shell utility, and object-inspection commands used by the
authority runner.
It uses an absolute `/bin/sh` shebang instead of `/usr/bin/env sh`, so direct
runner invocation does not resolve the shell through caller-controlled `PATH`.
It forces `LC_ALL=C` and `LANG=C` before source-token and object-symbol
analysis so shell tool matching is locale-stable.
It ignores caller-provided `TMPDIR`, creates a private authority build directory
under `/tmp` directly, exports `TMPDIR` to that private directory for
compiler-driver temporaries, and sets `umask 077` before creating authority
build artifacts so intermediate objects and test binaries are private to the
invoking user by default.
It verifies the private temporary directory, C substrate objects, C++
authority object, and authority test binary do not grant group or world
permissions before executing the authority test binary.
It also rejects `-Wno-*` flags that disable required warnings such as
`-Wconversion` or `-Wshadow`.
The C++ standard version policy is constrained C++20, enforced through
`-std=c++20` in `CXXFLAGS`.
The warnings-as-errors policy is mandatory for both C substrate objects and
C++ authority objects through `-Werror` in `CFLAGS` and `CXXFLAGS`.
It requires the C++ authority header to wrap the C substrate includes with
`extern "C"`.
It rejects any authority-header `latticra/lat_parser.h` or `latticra/lir.h`
include that appears outside that `extern "C"` block.
It rejects direct C substrate includes from `src/cpp/authority.cpp`; the public
C++ authority header owns the C include boundary.
It allowlists quoted includes in the authority path: the C++ authority header
may include only `latticra/lat_parser.h` and `latticra/lir.h`, and
`src/cpp/authority.cpp` may include only `latticra/cpp/authority.hpp`.
The include guards match normal preprocessor whitespace, including leading
spaces and `# include`, so directive formatting cannot bypass the authority
include allowlists or C substrate include boundary.
The include-boundary fixture probes cover unwrapped `latticra/lat_parser.h`
and `latticra/lir.h` authority-header includes, direct
`latticra/lat_parser.h`, `latticra/lir.h`, and `latticra/state_lattice.h`
source includes, and both header/source quoted-include allowlists.
It rejects authority-path `std::` API names outside the declared subset.

It compiles the Lat parser and LIR C substrate objects with `cc`, compiles
the authority layer with `c++`, and links those C and C++ objects together with
`c++`.

The guard enforces the authority-path standard library and construct policy.
Its static-analysis path is the source-token and object-symbol analysis in
`scripts/test-cpp-authority-layer.sh`; this no-effect authority layer does not
require a separate sanitizer runtime.
`scripts/test-cpp-authority-layer-build-policy.sh` runs negative build-policy
probes against the authority runner for missing required flags, conflicting
flags, warning weakening, unlisted flags, include injection, macro override,
linker injection, toolchain escape, ambient compiler variables, ambient tool
selectors, and ambient tool prefixes. The flag probes cover forced-include and
search path variants, macro undef/pass-through variants, linker library/selector/mode
variants, and sysroot/plugin/backend/assembler toolchain escape variants. They also prove
ambient include-path, library-path, SDK, compiler-path, and dependency-output
variables are rejected before the authority build. They also cover assembler,
C include path, Objective-C include path, loader path/preload,
deployment-target, developer-dir, toolchains, GCC exec-prefix, compiler
override/add-args, and SunPro dependency-output variables. The ambient
tool-selector probes cover C/C++ compiler, preprocessor, linker, archive/index,
binary-inspection, libtool, and install-name selectors. It also proves caller
`PATH` cannot steer tool resolution and caller `TMPDIR` cannot steer the authority build root
away from the runner's private `mktemp -d` authority workdir template. It
self-checks the authority runner command-shape
fragments so the C substrate object compile, authority C++ object compile, C++
test link, and `nm` object-inspection steps remain tied to the documented
authority runner paths and object variables. It runs mutated authority
source/header fixtures
through the runner to prove source-token guards reject unwrapped C substrate
includes, direct C substrate includes, unlisted quoted includes, spaced
preprocessor includes, unlisted standard headers, forbidden exception/RTTI
constructs, raw allocation constructs, forbidden C++ ownership/container
types, forbidden file/system standard headers, unlisted `std::` APIs,
framework namespaces, I/O or process calls, C substrate function calls, and
template metaprogramming constructs.
The ownership/container fixture probes cover `std::vector`, `std::string`,
`std::shared_ptr`, `std::unique_ptr`, `std::map`, and `std::unordered_map`
authority-path tokens.
The forbidden standard-library header fixture probes cover the named file,
system, exception, thread, regex, string, memory, map, and unordered-map
headers forbidden by the authority-path subset.
The exception, RTTI, and cast fixture probes cover `throw`, `try`, `catch`,
`dynamic_cast`, `typeid`, `reinterpret_cast`, and `const_cast` authority-path
tokens.
The raw and C allocation fixture probes cover `new`, `delete`, `malloc`,
`calloc`, `realloc`, and `free` authority-path tokens.
It runs mutated authority source fixtures that compile far enough to prove
object-symbol guards reject writable global data, common data symbols, emitted
`latticra_*` symbols, allocation symbols, exception/RTTI symbols, indirect
exception/RTTI symbols, public C ABI symbols, and public unmangled defined
symbols.
It runs a mutated runner fixture with weakened `umask` settings to prove the
private artifact-permission guard rejects group/world-readable build artifacts.
It allows only the declared standard library subset:

```text
<array>
<cstddef>
<cstdint>
<string_view>
```

`<type_traits>` is used only by the C++ authority invariant test for static
assertions. It is not part of the authority-path source subset.

The guard also rejects forbidden authority-path constructs including:

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
throw
try
catch
dynamic_cast
typeid
reinterpret_cast
const_cast
new
delete
malloc
calloc
realloc
free
std::vector
std::string
std::shared_ptr
std::unique_ptr
std::map
std::unordered_map
```

After compiling the authority object, the guard rejects writable global data
symbols so the hidden-global-mutable-state rule is checked at object level.
It treats `nm` common symbols (`C`/`c`) as rejected writable global data.
It also rejects allocation symbols in the compiled authority object, including
`operator new`, `operator delete`, `malloc`, `calloc`, `realloc`, and `free`.
The object allocation-symbol fixture probes cover `operator new`,
`operator delete`, `malloc`, `calloc`, `realloc`, and `free` emitted symbols.
It rejects exception-runtime and RTTI/typeinfo symbols in the compiled
authority object.
The object exception/RTTI fixture probes cover `__gxx_personality`, `__cxa`,
`__Unwind`, `_ZTI`, `_ZTS`, and `_ZTV` emitted symbol families.
The object-symbol guard also rejects indirect exception-runtime and
RTTI/typeinfo references such as `DW.ref.__gxx_personality_v0`.
It rejects framework-style namespaces such as `latticra::runtime`,
`latticra::kernel`, `latticra::server`, and `latticra::recovery` in the
authority path.
The framework-namespace fixture probes cover `latticra::runtime`,
`latticra::kernel`, `latticra::server`, and `latticra::recovery`
authority-path namespace tokens.
It rejects obvious file I/O, network socket, and process-launch call tokens
in authority-path source.
The I/O, network, and process-call fixture probes cover file calls `fopen`,
`freopen`, `open`, `creat`, `read`, and `write`; socket calls `socket`,
`connect`, `bind`, `listen`, `accept`, `send`, and `recv`; and process calls
`system`, `popen`, `fork`, `exec*`, and `posix_spawn`.
It rejects any authority-path `latticra_*` C substrate function call expression
and any emitted `latticra_*` C substrate symbol from the compiled authority
object; the layer consumes C structs and enums but does not call C substrate
behavior, report, or helper functions.
The C substrate call fixture probes cover Lat helper, parse, and report calls;
LIR helper, lower, and report calls; and state-lattice default, no-effect, and
report calls.
It rejects public unmangled C ABI text symbols in the compiled authority object.
It rejects any public unmangled defined symbol in the compiled authority
object, including non-text data symbols.
It rejects generic template metaprogramming constructs in authority-path
source while still allowing fixed-size helper templates.
The template-policy fixture probes cover `template <typename>`,
`template <class>`, template-template parameters, `requires`, `concept`,
`std::enable_if`, `std::conditional`, `std::integral_constant`, `std::is_*`,
and `std::void_t` authority-path tokens.
The template-policy source-token check runs before the general unlisted
`std::` API check so standard-library metaprogramming helpers receive the
template-policy denial.
It rejects authority-path standard library headers and `std::` API names
outside the declared subset.

## Validation

Run:

```sh
sh scripts/test-cpp-authority-layer.sh
sh scripts/test-cpp-authority-layer-build-policy.sh
```

The test suite covers:

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

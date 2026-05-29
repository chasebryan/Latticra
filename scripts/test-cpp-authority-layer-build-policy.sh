#!/bin/sh
set -eu

PATH=/usr/bin:/bin:/usr/sbin:/sbin
export PATH
LC_ALL=C
LANG=C
export LC_ALL LANG

runner="scripts/test-cpp-authority-layer.sh"
default_cflags="-std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow"
default_cxxflags="-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti"

tmpdir="$(mktemp -d "/tmp/cpp-authority-build-policy.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

fail() {
  printf 'cpp authority layer build policy: %s\n' "$1" >&2
  exit 1
}

require_runner_contains() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$runner"; then
    fail "runner missing required pattern: $pattern"
  fi
}

copy_authority_fixture() {
  label="$1"
  fixture="$tmpdir/$label.fixture"

  mkdir -p \
    "$fixture/src/cpp" \
    "$fixture/tests" \
    "$fixture/scripts"
  cp -R include "$fixture/include"
  cp src/lat_parser.c "$fixture/src/lat_parser.c"
  cp src/lir.c "$fixture/src/lir.c"
  cp src/cpp/authority.cpp "$fixture/src/cpp/authority.cpp"
  cp tests/cpp_authority_layer_invariants.cpp \
    "$fixture/tests/cpp_authority_layer_invariants.cpp"
  cp "$runner" "$fixture/$runner"
}

expect_fixture_denies() {
  label="$1"
  pattern="$2"
  fixture="$tmpdir/$label.fixture"
  stdout="$tmpdir/$label.out"
  stderr="$tmpdir/$label.err"

  : >"$stdout"
  : >"$stderr"

  if (cd "$fixture" && env -i /bin/sh "$runner") >"$stdout" 2>"$stderr"; then
    fail "runner accepted forbidden authority source fixture: $label"
  fi

  if ! grep -Fq -- "$pattern" "$stderr"; then
    printf 'cpp authority layer build policy: missing source denial for %s: %s\n' \
      "$label" "$pattern" >&2
    if [ -f "$stderr" ]; then
      sed -n '1,20p' "$stderr" >&2
    else
      printf 'cpp authority layer build policy: missing stderr capture for %s\n' "$label" >&2
    fi
    exit 1
  fi
}

expect_runner_denies() {
  label="$1"
  pattern="$2"
  shift 2

  stdout="$tmpdir/$label.out"
  stderr="$tmpdir/$label.err"

  : >"$stdout"
  : >"$stderr"

  if env -i "$@" /bin/sh "$runner" >"$stdout" 2>"$stderr"; then
    fail "runner accepted forbidden build input: $label"
  fi

  if ! grep -Fq -- "$pattern" "$stderr"; then
    printf 'cpp authority layer build policy: missing denial for %s: %s\n' \
      "$label" "$pattern" >&2
    if [ -f "$stderr" ]; then
      sed -n '1,20p' "$stderr" >&2
    else
      printf 'cpp authority layer build policy: missing stderr capture for %s\n' "$label" >&2
    fi
    exit 1
  fi
}

expect_runner_fixture_denies() {
  label="$1"
  pattern="$2"
  fixture="$tmpdir/$label.runner"
  stdout="$tmpdir/$label.out"
  stderr="$tmpdir/$label.err"

  : >"$stdout"
  : >"$stderr"

  cp "$runner" "$fixture"

  if [ "$label" = "weak_artifact_permissions" ]; then
    awk '
      $0 == "umask 077" {
        print "umask 022"
        next
      }
      { print }
    ' "$fixture" >"$fixture.next"
    mv "$fixture.next" "$fixture"
  fi

  if [ "$label" = "ambient_dyld_prefix_surrogate" ]; then
    awk '
      $0 == "reject_prefixed_environment_variable DYLD_" {
        print "reject_prefixed_environment_variable LATTICRA_DYLD_"
        next
      }
      { print }
    ' "$fixture" >"$fixture.next"
    mv "$fixture.next" "$fixture"

    if env -i LATTICRA_DYLD_PRINT_LIBRARIES=1 /bin/sh "$fixture" \
      >"$stdout" 2>"$stderr"; then
      fail "runner accepted forbidden runner fixture: $label"
    fi

    if ! grep -Fq -- "$pattern" "$stderr"; then
      printf 'cpp authority layer build policy: missing runner fixture denial for %s: %s\n' \
        "$label" "$pattern" >&2
      if [ -f "$stderr" ]; then
        sed -n '1,20p' "$stderr" >&2
      else
        printf 'cpp authority layer build policy: missing stderr capture for %s\n' "$label" >&2
      fi
      exit 1
    fi

    return
  fi

  if env -i /bin/sh "$fixture" >"$stdout" 2>"$stderr"; then
    fail "runner accepted forbidden runner fixture: $label"
  fi

  if ! grep -Fq -- "$pattern" "$stderr"; then
    printf 'cpp authority layer build policy: missing runner fixture denial for %s: %s\n' \
      "$label" "$pattern" >&2
    if [ -f "$stderr" ]; then
      sed -n '1,20p' "$stderr" >&2
    else
      printf 'cpp authority layer build policy: missing stderr capture for %s\n' "$label" >&2
    fi
    exit 1
  fi
}

for required_runner_pattern in \
  'lat_parser_o="$tmpdir/lat-parser.o"' \
  'lir_o="$tmpdir/lir.o"' \
  'authority_o="$tmpdir/cpp-authority.o"' \
  'authority_test="$tmpdir/cpp-authority-layer-invariants"' \
  'cc $CFLAGS' \
  '-Iinclude' \
  '-c src/lat_parser.c' \
  '-o "$lat_parser_o"' \
  '-c src/lir.c' \
  '-o "$lir_o"' \
  'c++ $CXXFLAGS' \
  '-c src/cpp/authority.cpp' \
  '-o "$authority_o"' \
  'nm "$authority_o"' \
  'nm -g "$authority_o"' \
  'tests/cpp_authority_layer_invariants.cpp' \
  '"$authority_o"' \
  '"$lat_parser_o"' \
  '"$lir_o"' \
  '-o "$authority_test"'
do
  require_runner_contains "$required_runner_pattern"
done

expect_runner_denies \
  missing_cflags \
  'CFLAGS missing required flag: -Wshadow' \
  "CFLAGS=-std=c99 -Wall -Wextra -Werror -pedantic -Wconversion"

expect_runner_denies \
  missing_c_standard_flag \
  'CFLAGS missing required flag: -std=c99' \
  "CFLAGS=-Wall -Wextra -Werror -pedantic -Wconversion -Wshadow"

expect_runner_denies \
  missing_c_wall_flag \
  'CFLAGS missing required flag: -Wall' \
  "CFLAGS=-std=c99 -Wextra -Werror -pedantic -Wconversion -Wshadow"

expect_runner_denies \
  missing_c_wextra_flag \
  'CFLAGS missing required flag: -Wextra' \
  "CFLAGS=-std=c99 -Wall -Werror -pedantic -Wconversion -Wshadow"

expect_runner_denies \
  missing_c_werror_flag \
  'CFLAGS missing required flag: -Werror' \
  "CFLAGS=-std=c99 -Wall -Wextra -pedantic -Wconversion -Wshadow"

expect_runner_denies \
  missing_c_pedantic_flag \
  'CFLAGS missing required flag: -pedantic' \
  "CFLAGS=-std=c99 -Wall -Wextra -Werror -Wconversion -Wshadow"

expect_runner_denies \
  missing_c_wconversion_flag \
  'CFLAGS missing required flag: -Wconversion' \
  "CFLAGS=-std=c99 -Wall -Wextra -Werror -pedantic -Wshadow"

expect_runner_denies \
  missing_cxxflags \
  'CXXFLAGS missing required flag: -fno-rtti' \
  "CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions"

expect_runner_denies \
  missing_cxx_standard_flag \
  'CXXFLAGS missing required flag: -std=c++20' \
  "CXXFLAGS=-Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti"

expect_runner_denies \
  missing_cxx_wall_flag \
  'CXXFLAGS missing required flag: -Wall' \
  "CXXFLAGS=-std=c++20 -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti"

expect_runner_denies \
  missing_cxx_wextra_flag \
  'CXXFLAGS missing required flag: -Wextra' \
  "CXXFLAGS=-std=c++20 -Wall -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti"

expect_runner_denies \
  missing_cxx_werror_flag \
  'CXXFLAGS missing required flag: -Werror' \
  "CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti"

expect_runner_denies \
  missing_cxx_pedantic_flag \
  'CXXFLAGS missing required flag: -pedantic' \
  "CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -Wconversion -Wshadow -fno-exceptions -fno-rtti"

expect_runner_denies \
  missing_cxx_wconversion_flag \
  'CXXFLAGS missing required flag: -Wconversion' \
  "CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -Wshadow -fno-exceptions -fno-rtti"

expect_runner_denies \
  missing_cxx_wshadow_flag \
  'CXXFLAGS missing required flag: -Wshadow' \
  "CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -fno-exceptions -fno-rtti"

expect_runner_denies \
  missing_cxx_fno_exceptions_flag \
  'CXXFLAGS missing required flag: -fno-exceptions' \
  "CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-rtti"

expect_runner_denies \
  conflicting_c_standard \
  'CFLAGS conflicting C standard flag: -std=c11' \
  "CFLAGS=$default_cflags -std=c11"

expect_runner_denies \
  conflicting_cpp_standard \
  'CXXFLAGS conflicting C++ standard flag: -std=c++17' \
  "CXXFLAGS=$default_cxxflags -std=c++17"

expect_runner_denies \
  conflicting_cpp_exception_policy \
  'CXXFLAGS conflicts with no-exceptions/no-RTTI policy: -fexceptions' \
  "CXXFLAGS=$default_cxxflags -fexceptions"

expect_runner_denies \
  conflicting_cpp_rtti_policy \
  'CXXFLAGS conflicts with no-exceptions/no-RTTI policy: -frtti' \
  "CXXFLAGS=$default_cxxflags -frtti"

expect_runner_denies \
  weakened_warning_policy \
  'CFLAGS weakens required warning policy: -Wno-shadow' \
  "CFLAGS=$default_cflags -Wno-shadow"

expect_runner_denies \
  weakened_cxx_warning_policy \
  'CXXFLAGS weakens required warning policy: -Wno-conversion' \
  "CXXFLAGS=$default_cxxflags -Wno-conversion"

expect_runner_denies \
  unlisted_c_flag \
  'CFLAGS uses flag outside constrained allowlist: -O2' \
  "CFLAGS=$default_cflags -O2"

expect_runner_denies \
  unlisted_cxx_flag \
  'CXXFLAGS uses flag outside constrained allowlist: -O2' \
  "CXXFLAGS=$default_cxxflags -O2"

expect_runner_denies \
  unlisted_codegen_flag \
  'CXXFLAGS uses flag outside constrained allowlist: -fPIC' \
  "CXXFLAGS=$default_cxxflags -fPIC"

expect_runner_denies \
  unlisted_visibility_flag \
  'CXXFLAGS uses flag outside constrained allowlist: -fvisibility=hidden' \
  "CXXFLAGS=$default_cxxflags -fvisibility=hidden"

expect_runner_denies \
  unlisted_sanitizer_flag \
  'CXXFLAGS uses flag outside constrained allowlist: -fsanitize=address' \
  "CXXFLAGS=$default_cxxflags -fsanitize=address"

expect_runner_denies \
  unlisted_dependency_flag \
  'CXXFLAGS uses flag outside constrained allowlist: -MMD' \
  "CXXFLAGS=$default_cxxflags -MMD"

expect_runner_denies \
  unlisted_platform_flag \
  'CXXFLAGS uses flag outside constrained allowlist: -mmacosx-version-min=13.0' \
  "CXXFLAGS=$default_cxxflags -mmacosx-version-min=13.0"

expect_runner_denies \
  include_injection_flag \
  'CFLAGS injects include path or forced include: -Iinclude' \
  "CFLAGS=$default_cflags -Iinclude"

expect_runner_denies \
  include_split_search_flag \
  'CFLAGS injects include path or forced include: -I' \
  "CFLAGS=$default_cflags -I include"

expect_runner_denies \
  include_forced_include_flag \
  'CFLAGS injects include path or forced include: -include' \
  "CFLAGS=$default_cflags -include include/latticra/cpp/authority.hpp"

expect_runner_denies \
  include_attached_forced_include_flag \
  'CFLAGS injects include path or forced include: -includeinclude/latticra/cpp/authority.hpp' \
  "CFLAGS=$default_cflags -includeinclude/latticra/cpp/authority.hpp"

expect_runner_denies \
  include_gnu_forced_include_flag \
  'CFLAGS injects include path or forced include: --include' \
  "CFLAGS=$default_cflags --include include/latticra/cpp/authority.hpp"

expect_runner_denies \
  include_gnu_forced_include_equals_flag \
  'CFLAGS injects include path or forced include: --include=include/latticra/cpp/authority.hpp' \
  "CFLAGS=$default_cflags --include=include/latticra/cpp/authority.hpp"

expect_runner_denies \
  include_system_search_flag \
  'CFLAGS injects include path or forced include: -isysteminclude' \
  "CFLAGS=$default_cflags -isysteminclude"

expect_runner_denies \
  include_system_split_search_flag \
  'CFLAGS injects include path or forced include: -isystem' \
  "CFLAGS=$default_cflags -isystem include"

expect_runner_denies \
  include_quote_search_flag \
  'CFLAGS injects include path or forced include: -iquoteinclude' \
  "CFLAGS=$default_cflags -iquoteinclude"

expect_runner_denies \
  include_quote_split_search_flag \
  'CFLAGS injects include path or forced include: -iquote' \
  "CFLAGS=$default_cflags -iquote include"

expect_runner_denies \
  include_after_search_flag \
  'CFLAGS injects include path or forced include: -idirafterinclude' \
  "CFLAGS=$default_cflags -idirafterinclude"

expect_runner_denies \
  include_after_split_search_flag \
  'CFLAGS injects include path or forced include: -idirafter' \
  "CFLAGS=$default_cflags -idirafter include"

expect_runner_denies \
  include_macros_flag \
  'CFLAGS injects include path or forced include: -imacros' \
  "CFLAGS=$default_cflags -imacros include/latticra/cpp/authority.hpp"

expect_runner_denies \
  include_attached_macros_flag \
  'CFLAGS injects include path or forced include: -imacrosinclude/latticra/cpp/authority.hpp' \
  "CFLAGS=$default_cflags -imacrosinclude/latticra/cpp/authority.hpp"

expect_runner_denies \
  include_framework_prefix_flag \
  'CXXFLAGS injects include path or forced include: -F/System' \
  "CXXFLAGS=$default_cxxflags -F/System"

expect_runner_denies \
  include_framework_split_prefix_flag \
  'CXXFLAGS injects include path or forced include: -F' \
  "CXXFLAGS=$default_cxxflags -F /System"

expect_runner_denies \
  include_framework_search_flag \
  'CXXFLAGS injects include path or forced include: -iframework/System' \
  "CXXFLAGS=$default_cxxflags -iframework/System"

expect_runner_denies \
  include_framework_split_search_flag \
  'CXXFLAGS injects include path or forced include: -iframework' \
  "CXXFLAGS=$default_cxxflags -iframework /System"

expect_runner_denies \
  preprocessor_override_flag \
  'CXXFLAGS injects preprocessor macro or option: -DLATTICRA_OVERRIDE=1' \
  "CXXFLAGS=$default_cxxflags -DLATTICRA_OVERRIDE=1"

expect_runner_denies \
  preprocessor_define_split_flag \
  'CXXFLAGS injects preprocessor macro or option: -D' \
  "CXXFLAGS=$default_cxxflags -D LATTICRA_OVERRIDE=1"

expect_runner_denies \
  preprocessor_undef_flag \
  'CXXFLAGS injects preprocessor macro or option: -ULATTICRA_OVERRIDE' \
  "CXXFLAGS=$default_cxxflags -ULATTICRA_OVERRIDE"

expect_runner_denies \
  preprocessor_undef_split_flag \
  'CXXFLAGS injects preprocessor macro or option: -U' \
  "CXXFLAGS=$default_cxxflags -U LATTICRA_OVERRIDE"

expect_runner_denies \
  preprocessor_passthrough_flag \
  'CXXFLAGS injects preprocessor macro or option: -Wp,-DNOPE=1' \
  "CXXFLAGS=$default_cxxflags -Wp,-DNOPE=1"

expect_runner_denies \
  preprocessor_driver_passthrough_flag \
  'CXXFLAGS injects preprocessor macro or option: -Xpreprocessor' \
  "CXXFLAGS=$default_cxxflags -Xpreprocessor -DNOPE=1"

expect_runner_denies \
  linker_injection_flag \
  'CXXFLAGS injects linker behavior: -Wl,-rpath,/tmp' \
  "CXXFLAGS=$default_cxxflags -Wl,-rpath,/tmp"

expect_runner_denies \
  linker_library_path_flag \
  'CXXFLAGS injects linker behavior: -L/tmp' \
  "CXXFLAGS=$default_cxxflags -L/tmp"

expect_runner_denies \
  linker_library_flag \
  'CXXFLAGS injects linker behavior: -lnotreal' \
  "CXXFLAGS=$default_cxxflags -lnotreal"

expect_runner_denies \
  linker_binary_prefix_flag \
  'CXXFLAGS injects linker behavior: -B/tmp' \
  "CXXFLAGS=$default_cxxflags -B/tmp"

expect_runner_denies \
  linker_fuse_ld_flag \
  'CXXFLAGS injects linker behavior: -fuse-ld=lld' \
  "CXXFLAGS=$default_cxxflags -fuse-ld=lld"

expect_runner_denies \
  linker_tool_selector_flag \
  'CXXFLAGS injects linker behavior: -Xlinker' \
  "CXXFLAGS=$default_cxxflags -Xlinker -rpath"

expect_runner_denies \
  linker_shared_flag \
  'CXXFLAGS injects linker behavior: -shared' \
  "CXXFLAGS=$default_cxxflags -shared"

expect_runner_denies \
  linker_static_flag \
  'CXXFLAGS injects linker behavior: -static' \
  "CXXFLAGS=$default_cxxflags -static"

expect_runner_denies \
  linker_rdynamic_flag \
  'CXXFLAGS injects linker behavior: -rdynamic' \
  "CXXFLAGS=$default_cxxflags -rdynamic"

expect_runner_denies \
  linker_nostdlib_flag \
  'CXXFLAGS injects linker behavior: -nostdlib' \
  "CXXFLAGS=$default_cxxflags -nostdlib"

expect_runner_denies \
  linker_nodefaultlibs_flag \
  'CXXFLAGS injects linker behavior: -nodefaultlibs' \
  "CXXFLAGS=$default_cxxflags -nodefaultlibs"

expect_runner_denies \
  linker_nostartfiles_flag \
  'CXXFLAGS injects linker behavior: -nostartfiles' \
  "CXXFLAGS=$default_cxxflags -nostartfiles"

expect_runner_denies \
  linker_pie_flag \
  'CXXFLAGS injects linker behavior: -pie' \
  "CXXFLAGS=$default_cxxflags -pie"

expect_runner_denies \
  linker_no_pie_flag \
  'CXXFLAGS injects linker behavior: -no-pie' \
  "CXXFLAGS=$default_cxxflags -no-pie"

expect_runner_denies \
  linker_relocatable_flag \
  'CXXFLAGS injects linker behavior: -r' \
  "CXXFLAGS=$default_cxxflags -r"

expect_runner_denies \
  linker_thread_flag \
  'CXXFLAGS injects linker behavior: -pthread' \
  "CXXFLAGS=$default_cxxflags -pthread"

expect_runner_denies \
  linker_stdlib_flag \
  'CXXFLAGS injects linker behavior: -stdlib=libc++' \
  "CXXFLAGS=$default_cxxflags -stdlib=libc++"

expect_runner_denies \
  toolchain_escape_flag \
  'CFLAGS escapes the constrained compiler driver: -Xclang' \
  "CFLAGS=$default_cflags -Xclang"

expect_runner_denies \
  toolchain_sysroot_flag \
  'CFLAGS escapes the constrained compiler driver: --sysroot=/tmp/nope' \
  "CFLAGS=$default_cflags --sysroot=/tmp/nope"

expect_runner_denies \
  toolchain_isysroot_flag \
  'CFLAGS escapes the constrained compiler driver: -isysroot/tmp/nope' \
  "CFLAGS=$default_cflags -isysroot/tmp/nope"

expect_runner_denies \
  toolchain_resource_dir_flag \
  'CFLAGS escapes the constrained compiler driver: -resource-dir=/tmp/nope' \
  "CFLAGS=$default_cflags -resource-dir=/tmp/nope"

expect_runner_denies \
  toolchain_gcc_toolchain_flag \
  'CFLAGS escapes the constrained compiler driver: -gcc-toolchain=/tmp/nope' \
  "CFLAGS=$default_cflags -gcc-toolchain=/tmp/nope"

expect_runner_denies \
  toolchain_ccc_gcc_name_flag \
  'CFLAGS escapes the constrained compiler driver: -ccc-gcc-name=gcc' \
  "CFLAGS=$default_cflags -ccc-gcc-name=gcc"

expect_runner_denies \
  toolchain_plugin_flag \
  'CXXFLAGS escapes the constrained compiler driver: -fplugin=/tmp/nope.so' \
  "CXXFLAGS=$default_cxxflags -fplugin=/tmp/nope.so"

expect_runner_denies \
  toolchain_plugin_arg_flag \
  'CXXFLAGS escapes the constrained compiler driver: -fplugin-arg-nope=value' \
  "CXXFLAGS=$default_cxxflags -fplugin-arg-nope=value"

expect_runner_denies \
  toolchain_backend_flag \
  'CXXFLAGS escapes the constrained compiler driver: -mllvm' \
  "CXXFLAGS=$default_cxxflags -mllvm"

expect_runner_denies \
  toolchain_assembler_flag \
  'CXXFLAGS escapes the constrained compiler driver: -Xassembler' \
  "CXXFLAGS=$default_cxxflags -Xassembler"

expect_runner_denies \
  toolchain_wa_flag \
  'CXXFLAGS escapes the constrained compiler driver: -Wa,-DNOPE=1' \
  "CXXFLAGS=$default_cxxflags -Wa,-DNOPE=1"

expect_runner_denies \
  ambient_compiler_environment \
  'ambient compiler environment variable is not allowed: CPPFLAGS' \
  "CPPFLAGS=-Iinclude"

expect_runner_denies \
  ambient_assembler_environment \
  'ambient compiler environment variable is not allowed: ASFLAGS' \
  "ASFLAGS=-Iinclude"

expect_runner_denies \
  ambient_include_path_environment \
  'ambient compiler environment variable is not allowed: CPATH' \
  "CPATH=include"

expect_runner_denies \
  ambient_c_include_path_environment \
  'ambient compiler environment variable is not allowed: C_INCLUDE_PATH' \
  "C_INCLUDE_PATH=include"

expect_runner_denies \
  ambient_cxx_include_path_environment \
  'ambient compiler environment variable is not allowed: CPLUS_INCLUDE_PATH' \
  "CPLUS_INCLUDE_PATH=include"

expect_runner_denies \
  ambient_objc_include_path_environment \
  'ambient compiler environment variable is not allowed: OBJC_INCLUDE_PATH' \
  "OBJC_INCLUDE_PATH=include"

expect_runner_denies \
  ambient_objcxx_include_path_environment \
  'ambient compiler environment variable is not allowed: OBJCPLUS_INCLUDE_PATH' \
  "OBJCPLUS_INCLUDE_PATH=include"

expect_runner_denies \
  ambient_linker_environment \
  'ambient compiler environment variable is not allowed: LDFLAGS' \
  "LDFLAGS=-L/tmp"

expect_runner_denies \
  ambient_library_path_environment \
  'ambient compiler environment variable is not allowed: LIBRARY_PATH' \
  "LIBRARY_PATH=/tmp"

expect_runner_denies \
  ambient_ld_library_path_environment \
  'ambient compiler environment variable is not allowed: LD_LIBRARY_PATH' \
  "LD_LIBRARY_PATH=/tmp"

expect_runner_denies \
  ambient_ld_preload_environment \
  'ambient compiler environment variable is not allowed: LD_PRELOAD' \
  "LD_PRELOAD=/tmp/not-a-library"

expect_runner_denies \
  ambient_sdk_environment \
  'ambient compiler environment variable is not allowed: SDKROOT' \
  "SDKROOT=/tmp"

expect_runner_denies \
  ambient_macos_deployment_environment \
  'ambient compiler environment variable is not allowed: MACOSX_DEPLOYMENT_TARGET' \
  "MACOSX_DEPLOYMENT_TARGET=99.0"

expect_runner_denies \
  ambient_developer_dir_environment \
  'ambient compiler environment variable is not allowed: DEVELOPER_DIR' \
  "DEVELOPER_DIR=/tmp"

expect_runner_denies \
  ambient_toolchains_environment \
  'ambient compiler environment variable is not allowed: TOOLCHAINS' \
  "TOOLCHAINS=com.example.toolchain"

expect_runner_denies \
  ambient_gcc_exec_prefix_environment \
  'ambient compiler environment variable is not allowed: GCC_EXEC_PREFIX' \
  "GCC_EXEC_PREFIX=/tmp"

expect_runner_denies \
  ambient_compiler_path_environment \
  'ambient compiler environment variable is not allowed: COMPILER_PATH' \
  "COMPILER_PATH=/tmp"

expect_runner_denies \
  ambient_ccc_override_environment \
  'ambient compiler environment variable is not allowed: CCC_OVERRIDE_OPTIONS' \
  "CCC_OVERRIDE_OPTIONS=+-I/tmp"

expect_runner_denies \
  ambient_ccc_add_args_environment \
  'ambient compiler environment variable is not allowed: CCC_ADD_ARGS' \
  "CCC_ADD_ARGS=-I/tmp"

expect_runner_denies \
  ambient_dependency_output_environment \
  'ambient compiler environment variable is not allowed: DEPENDENCIES_OUTPUT' \
  "DEPENDENCIES_OUTPUT=$tmpdir/deps"

expect_runner_denies \
  ambient_sunpro_dependency_environment \
  'ambient compiler environment variable is not allowed: SUNPRO_DEPENDENCIES' \
  "SUNPRO_DEPENDENCIES=$tmpdir/deps"

expect_runner_denies \
  ambient_tool_selector \
  'ambient compiler environment variable is not allowed: CC' \
  "CC=clang"

expect_runner_denies \
  ambient_cxx_tool_selector \
  'ambient compiler environment variable is not allowed: CXX' \
  "CXX=clang++"

expect_runner_denies \
  ambient_cpp_tool_selector \
  'ambient compiler environment variable is not allowed: CPP' \
  "CPP=cpp"

expect_runner_denies \
  ambient_linker_tool_selector \
  'ambient compiler environment variable is not allowed: LD' \
  "LD=ld"

expect_runner_denies \
  ambient_object_tool_selector \
  'ambient compiler environment variable is not allowed: NM' \
  "NM=llvm-nm"

expect_runner_denies \
  ambient_archive_tool_selector \
  'ambient compiler environment variable is not allowed: AR' \
  "AR=ar"

expect_runner_denies \
  ambient_ranlib_tool_selector \
  'ambient compiler environment variable is not allowed: RANLIB' \
  "RANLIB=ranlib"

expect_runner_denies \
  ambient_strip_tool_selector \
  'ambient compiler environment variable is not allowed: STRIP' \
  "STRIP=strip"

expect_runner_denies \
  ambient_objdump_tool_selector \
  'ambient compiler environment variable is not allowed: OBJDUMP' \
  "OBJDUMP=objdump"

expect_runner_denies \
  ambient_objcopy_tool_selector \
  'ambient compiler environment variable is not allowed: OBJCOPY' \
  "OBJCOPY=objcopy"

expect_runner_denies \
  ambient_readelf_tool_selector \
  'ambient compiler environment variable is not allowed: READELF' \
  "READELF=readelf"

expect_runner_denies \
  ambient_size_tool_selector \
  'ambient compiler environment variable is not allowed: SIZE' \
  "SIZE=size"

expect_runner_denies \
  ambient_libtool_selector \
  'ambient compiler environment variable is not allowed: LIBTOOL' \
  "LIBTOOL=libtool"

expect_runner_denies \
  ambient_install_name_tool_selector \
  'ambient compiler environment variable is not allowed: INSTALL_NAME_TOOL' \
  "INSTALL_NAME_TOOL=install_name_tool"

expect_runner_denies \
  ambient_tool_prefix \
  'ambient compiler environment variable prefix is not allowed: CCACHE_' \
  "CCACHE_DIR=$tmpdir/ccache"

expect_runner_denies \
  ambient_distcc_prefix \
  'ambient compiler environment variable prefix is not allowed: DISTCC_' \
  "DISTCC_HOSTS=localhost"

if ! env -i "PATH=$tmpdir/forbidden-path" /bin/sh "$runner" \
  >"$tmpdir/sanitized_path.out" 2>"$tmpdir/sanitized_path.err"; then
  printf 'cpp authority layer build policy: runner did not sanitize caller PATH\n' >&2
  sed -n '1,20p' "$tmpdir/sanitized_path.err" >&2
  exit 1
fi

if ! env -i "TMPDIR=$tmpdir/forbidden-tmp" /bin/sh "$runner" \
  >"$tmpdir/ignored_tmpdir.out" 2>"$tmpdir/ignored_tmpdir.err"; then
  printf 'cpp authority layer build policy: runner did not ignore caller TMPDIR\n' >&2
  sed -n '1,20p' "$tmpdir/ignored_tmpdir.err" >&2
  exit 1
fi

if ! grep -Fq -- 'tmpdir="$(mktemp -d "/tmp/cpp-authority-layer.XXXXXX")"' \
  "$runner"; then
  fail 'runner missing private /tmp authority build root'
fi

copy_authority_fixture unwrapped_c_substrate_include
awk 'BEGIN { print "# include \"latticra/lat_parser.h\"" } { print }' \
  "$tmpdir/unwrapped_c_substrate_include.fixture/include/latticra/cpp/authority.hpp" \
  >"$tmpdir/unwrapped_c_substrate_include.fixture/include/latticra/cpp/authority.hpp.next"
mv "$tmpdir/unwrapped_c_substrate_include.fixture/include/latticra/cpp/authority.hpp.next" \
  "$tmpdir/unwrapped_c_substrate_include.fixture/include/latticra/cpp/authority.hpp"
expect_fixture_denies \
  unwrapped_c_substrate_include \
  'C substrate includes not wrapped with extern "C"'

copy_authority_fixture unwrapped_lir_c_substrate_include
awk 'BEGIN { print "# include \"latticra/lir.h\"" } { print }' \
  "$tmpdir/unwrapped_lir_c_substrate_include.fixture/include/latticra/cpp/authority.hpp" \
  >"$tmpdir/unwrapped_lir_c_substrate_include.fixture/include/latticra/cpp/authority.hpp.next"
mv "$tmpdir/unwrapped_lir_c_substrate_include.fixture/include/latticra/cpp/authority.hpp.next" \
  "$tmpdir/unwrapped_lir_c_substrate_include.fixture/include/latticra/cpp/authority.hpp"
expect_fixture_denies \
  unwrapped_lir_c_substrate_include \
  'C substrate includes not wrapped with extern "C"'

copy_authority_fixture direct_c_substrate_include
printf '\n# include "latticra/lat_parser.h"\n' \
  >>"$tmpdir/direct_c_substrate_include.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  direct_c_substrate_include \
  'direct C substrate include outside authority header'

for direct_c_substrate_probe in \
  'direct_lir_c_substrate_include latticra/lir.h' \
  'direct_state_lattice_c_substrate_include latticra/state_lattice.h'
do
  set -- $direct_c_substrate_probe
  direct_c_substrate_label="$1"
  direct_c_substrate_header="$2"

  copy_authority_fixture "$direct_c_substrate_label"
  printf '\n# include "%s"\n' "$direct_c_substrate_header" \
    >>"$tmpdir/$direct_c_substrate_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$direct_c_substrate_label" \
    'direct C substrate include outside authority header'
done

copy_authority_fixture unlisted_header_quote_include
printf '\n# include "latticra/cpp/not_authorized.hpp"\n' \
  >>"$tmpdir/unlisted_header_quote_include.fixture/include/latticra/cpp/authority.hpp"
expect_fixture_denies \
  unlisted_header_quote_include \
  'quoted include outside authority header allowlist'

copy_authority_fixture unlisted_quote_include
printf '\n# include "latticra/cpp/not_authorized.hpp"\n' \
  >>"$tmpdir/unlisted_quote_include.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  unlisted_quote_include \
  'quoted include outside authority source allowlist'

copy_authority_fixture spaced_preprocessor_includes
printf '\n  # include <vector>\n' \
  >>"$tmpdir/spaced_preprocessor_includes.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  spaced_preprocessor_includes \
  'standard library header outside allowed subset used'

copy_authority_fixture unlisted_standard_header
printf '\n# include <vector>\n' \
  >>"$tmpdir/unlisted_standard_header.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  unlisted_standard_header \
  'standard library header outside allowed subset used'

for forbidden_header_probe in \
  'forbidden_iostream_header iostream' \
  'forbidden_fstream_header fstream' \
  'forbidden_filesystem_header filesystem' \
  'forbidden_thread_header thread' \
  'forbidden_future_header future' \
  'forbidden_regex_header regex' \
  'forbidden_exception_header exception' \
  'forbidden_stdexcept_header stdexcept' \
  'forbidden_string_header string' \
  'forbidden_memory_header memory' \
  'forbidden_map_header map' \
  'forbidden_unordered_map_header unordered_map'
do
  set -- $forbidden_header_probe
  forbidden_header_label="$1"
  forbidden_header="$2"

  copy_authority_fixture "$forbidden_header_label"
  printf '\n# include <%s>\n' "$forbidden_header" \
    >>"$tmpdir/$forbidden_header_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_header_label" \
    'standard library header outside allowed subset used'
done

copy_authority_fixture forbidden_exception_rtti_construct
printf '\nvoid cpp_authority_probe_rtti() { (void)typeid(int); }\n' \
  >>"$tmpdir/forbidden_exception_rtti_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_exception_rtti_construct \
  'forbidden exception, cast, or RTTI construct used'

copy_authority_fixture forbidden_throw_construct
printf '\nvoid cpp_authority_probe_throw() { throw 1; }\n' \
  >>"$tmpdir/forbidden_throw_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_throw_construct \
  'forbidden exception, cast, or RTTI construct used'

copy_authority_fixture forbidden_try_catch_construct
printf '\nvoid cpp_authority_probe_try_catch() { try { } catch (...) { } }\n' \
  >>"$tmpdir/forbidden_try_catch_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_try_catch_construct \
  'forbidden exception, cast, or RTTI construct used'

copy_authority_fixture forbidden_dynamic_cast_construct
printf '\nvoid cpp_authority_probe_dynamic_cast(void *value) { (void)dynamic_cast<int *>(value); }\n' \
  >>"$tmpdir/forbidden_dynamic_cast_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_dynamic_cast_construct \
  'forbidden exception, cast, or RTTI construct used'

copy_authority_fixture forbidden_reinterpret_cast_construct
printf '\nvoid cpp_authority_probe_reinterpret_cast(int *value) { (void)reinterpret_cast<unsigned long>(value); }\n' \
  >>"$tmpdir/forbidden_reinterpret_cast_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_reinterpret_cast_construct \
  'forbidden exception, cast, or RTTI construct used'

copy_authority_fixture forbidden_const_cast_construct
printf '\nvoid cpp_authority_probe_const_cast(const int *value) { (void)const_cast<int *>(value); }\n' \
  >>"$tmpdir/forbidden_const_cast_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_const_cast_construct \
  'forbidden exception, cast, or RTTI construct used'

copy_authority_fixture forbidden_raw_allocation_construct
printf '\nint *cpp_authority_probe_new() { return new int; }\n' \
  >>"$tmpdir/forbidden_raw_allocation_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_raw_allocation_construct \
  'forbidden raw allocation construct used'

copy_authority_fixture forbidden_delete_construct
printf '\nvoid cpp_authority_probe_delete(int *value) { delete value; }\n' \
  >>"$tmpdir/forbidden_delete_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_delete_construct \
  'forbidden raw allocation construct used'

for forbidden_c_allocation_probe in \
  'forbidden_malloc_call malloc(1u)' \
  'forbidden_calloc_call calloc(1u,1u)' \
  'forbidden_realloc_call realloc(nullptr,1u)' \
  'forbidden_free_call free(nullptr)'
do
  set -- $forbidden_c_allocation_probe
  forbidden_c_allocation_label="$1"
  forbidden_c_allocation_call="$2"

  copy_authority_fixture "$forbidden_c_allocation_label"
  printf '\nvoid cpp_authority_probe_c_allocation() { (void)%s; }\n' \
    "$forbidden_c_allocation_call" \
    >>"$tmpdir/$forbidden_c_allocation_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_c_allocation_label" \
    'forbidden C allocation function used'
done

copy_authority_fixture forbidden_container_type
printf '\nvoid cpp_authority_probe_vector() { std::vector<int> value; }\n' \
  >>"$tmpdir/forbidden_container_type.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  forbidden_container_type \
  'forbidden authority-path container or ownership type used'

for forbidden_ownership_probe in \
  'forbidden_string_type std::string' \
  'forbidden_shared_ptr_type std::shared_ptr<int>' \
  'forbidden_unique_ptr_type std::unique_ptr<int>' \
  'forbidden_map_type std::map<int,int>' \
  'forbidden_unordered_map_type std::unordered_map<int,int>'
do
  set -- $forbidden_ownership_probe
  forbidden_ownership_label="$1"
  forbidden_ownership_type="$2"

  copy_authority_fixture "$forbidden_ownership_label"
  printf '\nvoid cpp_authority_probe_ownership_type() { %s value; }\n' \
    "$forbidden_ownership_type" \
    >>"$tmpdir/$forbidden_ownership_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_ownership_label" \
    'forbidden authority-path container or ownership type used'
done

copy_authority_fixture unlisted_std_api
printf '\nvoid cpp_authority_probe_std_api() { (void)std::move; }\n' \
  >>"$tmpdir/unlisted_std_api.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  unlisted_std_api \
  'std api outside allowed subset used'

copy_authority_fixture framework_namespace
printf '\nnamespace latticra::runtime {}\n' \
  >>"$tmpdir/framework_namespace.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  framework_namespace \
  'forbidden framework namespace used'

for forbidden_framework_namespace_probe in \
  'framework_kernel_namespace latticra::kernel' \
  'framework_server_namespace latticra::server' \
  'framework_recovery_namespace latticra::recovery'
do
  set -- $forbidden_framework_namespace_probe
  forbidden_framework_namespace_label="$1"
  forbidden_framework_namespace="$2"

  copy_authority_fixture "$forbidden_framework_namespace_label"
  printf '\nnamespace %s {}\n' "$forbidden_framework_namespace" \
    >>"$tmpdir/$forbidden_framework_namespace_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_framework_namespace_label" \
    'forbidden framework namespace used'
done

copy_authority_fixture io_process_call
printf '\nvoid cpp_authority_probe_system() { system("true"); }\n' \
  >>"$tmpdir/io_process_call.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  io_process_call \
  'forbidden I/O or process call used'

for forbidden_io_process_probe in \
  'forbidden_fopen_call fopen()' \
  'forbidden_freopen_call freopen()' \
  'forbidden_open_call open()' \
  'forbidden_creat_call creat()' \
  'forbidden_read_call read()' \
  'forbidden_write_call write()' \
  'forbidden_socket_call socket()' \
  'forbidden_connect_call connect()' \
  'forbidden_bind_call bind()' \
  'forbidden_listen_call listen()' \
  'forbidden_accept_call accept()' \
  'forbidden_send_call send()' \
  'forbidden_recv_call recv()' \
  'forbidden_popen_call popen()' \
  'forbidden_fork_call fork()' \
  'forbidden_exec_call execv()' \
  'forbidden_posix_spawn_call posix_spawn()'
do
  set -- $forbidden_io_process_probe
  forbidden_io_process_label="$1"
  forbidden_io_process_call="$2"

  copy_authority_fixture "$forbidden_io_process_label"
  printf '\nvoid cpp_authority_probe_io_process() { (void)%s; }\n' \
    "$forbidden_io_process_call" \
    >>"$tmpdir/$forbidden_io_process_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_io_process_label" \
    'forbidden I/O or process call used'
done

copy_authority_fixture c_substrate_function_call
printf '\nvoid cpp_authority_probe_c_call() { (void)latticra_lat_parse_error_label(LATTICRA_LAT_PARSE_OK); }\n' \
  >>"$tmpdir/c_substrate_function_call.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  c_substrate_function_call \
  'forbidden C substrate function call used'

for forbidden_c_substrate_call_probe in \
  'c_substrate_lat_parse_source_call latticra_lat_parse_source()' \
  'c_substrate_lat_parse_report_call latticra_lat_parse_report()' \
  'c_substrate_lir_label_call latticra_lir_node_kind_label()' \
  'c_substrate_lir_lower_call latticra_lir_lower_l_ui_ast()' \
  'c_substrate_lir_report_call latticra_lir_report()' \
  'c_substrate_state_default_call latticra_state_lattice_default()' \
  'c_substrate_state_no_effect_call latticra_state_lattice_is_no_effect()' \
  'c_substrate_state_report_call latticra_state_lattice_report()'
do
  set -- $forbidden_c_substrate_call_probe
  forbidden_c_substrate_call_label="$1"
  forbidden_c_substrate_call="$2"

  copy_authority_fixture "$forbidden_c_substrate_call_label"
  printf '\nvoid cpp_authority_probe_c_substrate_call() { (void)%s; }\n' \
    "$forbidden_c_substrate_call" \
    >>"$tmpdir/$forbidden_c_substrate_call_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_c_substrate_call_label" \
    'forbidden C substrate function call used'
done

copy_authority_fixture template_metaprogramming_construct
printf '\ntemplate <typename T> struct cpp_authority_probe_template {};\n' \
  >>"$tmpdir/template_metaprogramming_construct.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  template_metaprogramming_construct \
  'forbidden template metaprogramming construct used'

for forbidden_template_probe in \
  'template_class_parameter template <class T> struct cpp_authority_probe_class_template {};' \
  'template_template_parameter template <template <typename> class T> struct cpp_authority_probe_template_template {};' \
  'template_requires_token void cpp_authority_probe_requires() { requires; }' \
  'template_concept_token concept cpp_authority_probe_concept = true;' \
  'template_enable_if_api void cpp_authority_probe_enable_if() { (void)sizeof(std::enable_if<true,int>); }' \
  'template_conditional_api void cpp_authority_probe_conditional() { (void)sizeof(std::conditional<true,int,int>); }' \
  'template_integral_constant_api void cpp_authority_probe_integral_constant() { (void)sizeof(std::integral_constant<int,1>); }' \
  'template_is_trait_api void cpp_authority_probe_is_trait() { (void)sizeof(std::is_same<int,int>); }' \
  'template_void_t_api void cpp_authority_probe_void_t() { (void)sizeof(std::void_t<int>); }'
do
  forbidden_template_label="${forbidden_template_probe%% *}"
  forbidden_template_source="${forbidden_template_probe#* }"

  copy_authority_fixture "$forbidden_template_label"
  printf '\n%s\n' "$forbidden_template_source" \
    >>"$tmpdir/$forbidden_template_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_template_label" \
    'forbidden template metaprogramming construct used'
done

copy_authority_fixture object_writable_global_symbol
printf '\nint cpp_authority_probe_global_symbol = 1;\n' \
  >>"$tmpdir/object_writable_global_symbol.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  object_writable_global_symbol \
  'writable global data symbol emitted'

copy_authority_fixture object_common_data_symbol
printf '\nasm(".comm cpp_authority_probe_common_symbol,4,2");\n' \
  >>"$tmpdir/object_common_data_symbol.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  object_common_data_symbol \
  'writable global data symbol emitted'

copy_authority_fixture object_c_substrate_symbol
printf '\nextern "C" int cpp_authority_probe_c_symbol() asm("latticra_probe_emitted_symbol");\nextern "C" int cpp_authority_probe_c_symbol() { return 0; }\n' \
  >>"$tmpdir/object_c_substrate_symbol.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  object_c_substrate_symbol \
  'forbidden C substrate function symbol emitted'

copy_authority_fixture object_allocation_symbol
printf '\nextern "C" void *cpp_authority_probe_alloc_symbol(unsigned long) asm("malloc");\nvoid *cpp_authority_probe_allocation_symbol() { return cpp_authority_probe_alloc_symbol(1u); }\n' \
  >>"$tmpdir/object_allocation_symbol.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  object_allocation_symbol \
  'allocation symbol emitted'

for forbidden_object_allocation_probe in \
  'object_operator_new_symbol extern "C" void *cpp_authority_probe_object_operator_new_symbol(unsigned long) asm("_Znwm"); void *cpp_authority_probe_object_operator_new_ref() { return cpp_authority_probe_object_operator_new_symbol(1u); }' \
  'object_operator_delete_symbol extern "C" void cpp_authority_probe_object_operator_delete_symbol(void *) asm("_ZdlPv"); void cpp_authority_probe_object_operator_delete_ref(void *value) { cpp_authority_probe_object_operator_delete_symbol(value); }' \
  'object_calloc_symbol extern "C" void *cpp_authority_probe_object_calloc_symbol(unsigned long,unsigned long) asm("calloc"); void *cpp_authority_probe_object_calloc_ref() { return cpp_authority_probe_object_calloc_symbol(1u,1u); }' \
  'object_realloc_symbol extern "C" void *cpp_authority_probe_object_realloc_symbol(void *,unsigned long) asm("realloc"); void *cpp_authority_probe_object_realloc_ref(void *value) { return cpp_authority_probe_object_realloc_symbol(value,1u); }' \
  'object_free_symbol extern "C" void cpp_authority_probe_object_free_symbol(void *) asm("free"); void cpp_authority_probe_object_free_ref(void *value) { cpp_authority_probe_object_free_symbol(value); }'
do
  forbidden_object_allocation_label="${forbidden_object_allocation_probe%% *}"
  forbidden_object_allocation_source="${forbidden_object_allocation_probe#* }"

  copy_authority_fixture "$forbidden_object_allocation_label"
  printf '\n%s\n' "$forbidden_object_allocation_source" \
    >>"$tmpdir/$forbidden_object_allocation_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_object_allocation_label" \
    'allocation symbol emitted'
done

copy_authority_fixture object_exception_rtti_symbol
printf '\nextern "C" void cpp_authority_probe_exception_symbol() asm("__gxx_personality_v0");\nvoid cpp_authority_probe_exception_ref() { cpp_authority_probe_exception_symbol(); }\n' \
  >>"$tmpdir/object_exception_rtti_symbol.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  object_exception_rtti_symbol \
  'exception or RTTI symbol emitted'

for forbidden_exception_rtti_symbol_probe in \
  'object_cxa_exception_symbol extern "C" void cpp_authority_probe_cxa_exception_symbol() asm("__cxa_throw"); void cpp_authority_probe_cxa_exception_ref() { cpp_authority_probe_cxa_exception_symbol(); }' \
  'object_unwind_exception_symbol extern "C" void cpp_authority_probe_unwind_exception_symbol() asm("__Unwind_RaiseException"); void cpp_authority_probe_unwind_exception_ref() { cpp_authority_probe_unwind_exception_symbol(); }' \
  'object_typeinfo_symbol extern "C" void cpp_authority_probe_typeinfo_symbol() asm("_ZTIi"); void cpp_authority_probe_typeinfo_ref() { cpp_authority_probe_typeinfo_symbol(); }' \
  'object_typeinfo_name_symbol extern "C" void cpp_authority_probe_typeinfo_name_symbol() asm("_ZTSi"); void cpp_authority_probe_typeinfo_name_ref() { cpp_authority_probe_typeinfo_name_symbol(); }' \
  'object_vtable_symbol extern "C" void cpp_authority_probe_vtable_symbol() asm("_ZTVN8latticra20cpp_authority_probeE"); void cpp_authority_probe_vtable_ref() { cpp_authority_probe_vtable_symbol(); }'
do
  forbidden_exception_rtti_symbol_label="${forbidden_exception_rtti_symbol_probe%% *}"
  forbidden_exception_rtti_symbol_source="${forbidden_exception_rtti_symbol_probe#* }"

  copy_authority_fixture "$forbidden_exception_rtti_symbol_label"
  printf '\n%s\n' "$forbidden_exception_rtti_symbol_source" \
    >>"$tmpdir/$forbidden_exception_rtti_symbol_label.fixture/src/cpp/authority.cpp"
  expect_fixture_denies \
    "$forbidden_exception_rtti_symbol_label" \
    'exception or RTTI symbol emitted'
done

copy_authority_fixture object_indirect_exception_rtti_symbol
printf '\nextern "C" void cpp_authority_probe_indirect_exception_symbol() asm("DW.ref.__gxx_personality_v0");\nvoid cpp_authority_probe_indirect_exception_ref() { cpp_authority_probe_indirect_exception_symbol(); }\n' \
  >>"$tmpdir/object_indirect_exception_rtti_symbol.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  object_indirect_exception_rtti_symbol \
  'exception or RTTI symbol emitted'

copy_authority_fixture object_public_c_abi_symbol
printf '\nextern "C" int cpp_authority_probe_public_c_abi() { return 0; }\n' \
  >>"$tmpdir/object_public_c_abi_symbol.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  object_public_c_abi_symbol \
  'public C ABI symbol emitted'

copy_authority_fixture object_public_unmangled_defined_symbol
printf '\nextern "C" const int cpp_authority_probe_public_unmangled_data = 1;\n' \
  >>"$tmpdir/object_public_unmangled_defined_symbol.fixture/src/cpp/authority.cpp"
expect_fixture_denies \
  object_public_unmangled_defined_symbol \
  'public unmangled defined symbol emitted'

expect_runner_fixture_denies \
  weak_artifact_permissions \
  'private build artifact grants group/world access'

expect_runner_fixture_denies \
  ambient_dyld_prefix_surrogate \
  'ambient compiler environment variable prefix is not allowed: LATTICRA_DYLD_'

require_runner_contains 'reject_prefixed_environment_variable DYLD_'

printf 'cpp_authority_layer_build_policy: ok\n'

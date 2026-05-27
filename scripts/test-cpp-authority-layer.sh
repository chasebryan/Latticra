#!/bin/sh
set -eu

PATH=/usr/bin:/bin:/usr/sbin:/sbin
export PATH
LC_ALL=C
LANG=C
export LC_ALL LANG
umask 077

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow}"
: "${CXXFLAGS:=-std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti}"

require_flag() {
  flags="$1"
  required="$2"
  label="$3"
  case " $flags " in
    *" $required "*) ;;
    *)
      printf 'cpp authority layer: %s missing required flag: %s\n' "$label" "$required" >&2
      exit 1
      ;;
  esac
}

reject_include_injection_flag() {
  flag="$1"
  label="$2"
  case "$flag" in
    -I|-I*|-isystem|-isystem*|-iquote|-iquote*|-idirafter|-idirafter*|-include|-include*|--include|--include=*|-imacros|-imacros*|-F|-F*|-iframework|-iframework*)
      printf 'cpp authority layer: %s injects include path or forced include: %s\n' "$label" "$flag" >&2
      exit 1
      ;;
  esac
}

reject_preprocessor_override_flag() {
  flag="$1"
  label="$2"
  case "$flag" in
    -D|-D*|-U|-U*|-Wp,*|-Xpreprocessor)
      printf 'cpp authority layer: %s injects preprocessor macro or option: %s\n' "$label" "$flag" >&2
      exit 1
      ;;
  esac
}

reject_linker_injection_flag() {
  flag="$1"
  label="$2"
  case "$flag" in
    -Wl,*|-Xlinker|-Xlinker=*|-L|-L*|-l|-l*|-B|-B*|-fuse-ld=*|\
    -shared|-shared-*|-static|-static-*|-rdynamic|\
    -nostdlib|-nodefaultlibs|-nostartfiles|-pie|-no-pie|-r|\
    -pthread|-pthreads|-stdlib=*)
      printf 'cpp authority layer: %s injects linker behavior: %s\n' "$label" "$flag" >&2
      exit 1
      ;;
  esac
}

reject_toolchain_escape_flag() {
  flag="$1"
  label="$2"
  case "$flag" in
    --sysroot|--sysroot=*|-isysroot|-isysroot*|-resource-dir|-resource-dir=*|\
    -gcc-toolchain|-gcc-toolchain=*|-ccc-gcc-name|-ccc-gcc-name=*|\
    -fplugin=*|-fplugin-arg-*|-Xclang|-mllvm|-Xassembler|-Wa,*)
      printf 'cpp authority layer: %s escapes the constrained compiler driver: %s\n' "$label" "$flag" >&2
      exit 1
      ;;
  esac
}

reject_set_environment_variable() {
  variable="$1"
  if env | awk -v name="$variable" '
    BEGIN { prefix = name "=" }
    index($0, prefix) == 1 { found = 1 }
    END { exit found ? 0 : 1 }
  '; then
    printf 'cpp authority layer: ambient compiler environment variable is not allowed: %s\n' "$variable" >&2
    exit 1
  fi
}

reject_prefixed_environment_variable() {
  prefix="$1"
  if env | awk -v prefix="$prefix" '
    index($0, prefix) == 1 { found = 1 }
    END { exit found ? 0 : 1 }
  '; then
    printf 'cpp authority layer: ambient compiler environment variable prefix is not allowed: %s\n' "$prefix" >&2
    exit 1
  fi
}

require_private_path_permissions() {
  path="$1"
  if ! ls -ld "$path" 2>/dev/null | awk '
    {
      seen = 1
      if (length($1) < 10 || substr($1, 5, 6) != "------") {
        bad = 1
      }
    }
    END { exit seen && !bad ? 0 : 1 }
  '; then
    printf 'cpp authority layer: private build artifact grants group/world access: %s\n' "$path" >&2
    exit 1
  fi
}

reject_unlisted_c_flag() {
  flag="$1"
  case "$flag" in
    -std=c99|-Wall|-Wextra|-Werror|-pedantic|-Wconversion|-Wshadow)
      return 0
      ;;
  esac

  printf 'cpp authority layer: CFLAGS uses flag outside constrained allowlist: %s\n' "$flag" >&2
  exit 1
}

reject_unlisted_cxx_flag() {
  flag="$1"
  case "$flag" in
    -std=c++20|-Wall|-Wextra|-Werror|-pedantic|-Wconversion|-Wshadow|-fno-exceptions|-fno-rtti)
      return 0
      ;;
  esac

  printf 'cpp authority layer: CXXFLAGS uses flag outside constrained allowlist: %s\n' "$flag" >&2
  exit 1
}

reject_conflicting_c_flags() {
  for flag in $CFLAGS
  do
    reject_include_injection_flag "$flag" CFLAGS
    reject_preprocessor_override_flag "$flag" CFLAGS
    reject_toolchain_escape_flag "$flag" CFLAGS
    case "$flag" in
      -std=*)
        if [ "$flag" != "-std=c99" ]; then
          printf 'cpp authority layer: CFLAGS conflicting C standard flag: %s\n' "$flag" >&2
          exit 1
        fi
        ;;
      -Wno-error|-Wno-error=*|-Wno-*|-w)
        printf 'cpp authority layer: CFLAGS weakens required warning policy: %s\n' "$flag" >&2
        exit 1
        ;;
    esac
    reject_unlisted_c_flag "$flag"
  done
}

reject_conflicting_cxx_flags() {
  for flag in $CXXFLAGS
  do
    reject_include_injection_flag "$flag" CXXFLAGS
    reject_preprocessor_override_flag "$flag" CXXFLAGS
    reject_linker_injection_flag "$flag" CXXFLAGS
    reject_toolchain_escape_flag "$flag" CXXFLAGS
    case "$flag" in
      -std=*)
        if [ "$flag" != "-std=c++20" ]; then
          printf 'cpp authority layer: CXXFLAGS conflicting C++ standard flag: %s\n' "$flag" >&2
          exit 1
        fi
        ;;
      -fexceptions|-frtti)
        printf 'cpp authority layer: CXXFLAGS conflicts with no-exceptions/no-RTTI policy: %s\n' "$flag" >&2
        exit 1
        ;;
      -Wno-error|-Wno-error=*|-Wno-*|-w)
        printf 'cpp authority layer: CXXFLAGS weakens required warning policy: %s\n' "$flag" >&2
        exit 1
        ;;
    esac
    reject_unlisted_cxx_flag "$flag"
  done
}

for flag in -std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow
do
  require_flag "$CFLAGS" "$flag" CFLAGS
done

for flag in -std=c++20 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti
do
  require_flag "$CXXFLAGS" "$flag" CXXFLAGS
done

reject_conflicting_c_flags
reject_conflicting_cxx_flags

for variable in \
  CPPFLAGS \
  LDFLAGS \
  ASFLAGS \
  CPATH \
  C_INCLUDE_PATH \
  CPLUS_INCLUDE_PATH \
  OBJC_INCLUDE_PATH \
  OBJCPLUS_INCLUDE_PATH \
  LIBRARY_PATH \
  LD_LIBRARY_PATH \
  LD_PRELOAD \
  DYLD_LIBRARY_PATH \
  DYLD_FALLBACK_LIBRARY_PATH \
  DYLD_INSERT_LIBRARIES \
  DYLD_FRAMEWORK_PATH \
  DYLD_FALLBACK_FRAMEWORK_PATH \
  DYLD_ROOT_PATH \
  SDKROOT \
  MACOSX_DEPLOYMENT_TARGET \
  DEVELOPER_DIR \
  TOOLCHAINS \
  GCC_EXEC_PREFIX \
  COMPILER_PATH \
  CCC_OVERRIDE_OPTIONS \
  CCC_ADD_ARGS \
  DEPENDENCIES_OUTPUT \
  SUNPRO_DEPENDENCIES
do
  reject_set_environment_variable "$variable"
done
for variable in \
  CC \
  CXX \
  CPP \
  LD \
  NM \
  AR \
  RANLIB \
  STRIP \
  OBJDUMP \
  OBJCOPY \
  READELF \
  SIZE \
  LIBTOOL \
  INSTALL_NAME_TOOL
do
  reject_set_environment_variable "$variable"
done
reject_prefixed_environment_variable CCACHE_
reject_prefixed_environment_variable DISTCC_
reject_prefixed_environment_variable DYLD_

tmpdir="$(mktemp -d "/tmp/cpp-authority-layer.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
TMPDIR="$tmpdir"
export TMPDIR
require_private_path_permissions "$tmpdir"

lat_parser_o="$tmpdir/lat-parser.o"
lir_o="$tmpdir/lir.o"
authority_o="$tmpdir/cpp-authority.o"
authority_test="$tmpdir/cpp-authority-layer-invariants"

if ! awk '
  /extern "C"[[:space:]]*\{/ { inside = 1 }
  /^[[:space:]]*#[[:space:]]*include[[:space:]]*"latticra\/lat_parser.h"/ {
    if (inside) {
      lat = 1
    } else {
      outside = 1
    }
  }
  /^[[:space:]]*#[[:space:]]*include[[:space:]]*"latticra\/lir.h"/ {
    if (inside) {
      lir = 1
    } else {
      outside = 1
    }
  }
  inside && /^\}/ { inside = 0 }
  END { exit(lat && lir && !outside ? 0 : 1) }
' include/latticra/cpp/authority.hpp; then
  printf 'cpp authority layer: C substrate includes not wrapped with extern "C"\n' >&2
  exit 1
fi

if grep -E '^[[:space:]]*#[[:space:]]*include[[:space:]]*"latticra/(lat_parser|lir|state_lattice)\.h"' \
  src/cpp/authority.cpp; then
  printf 'cpp authority layer: direct C substrate include outside authority header\n' >&2
  exit 1
fi

if grep -E '^[[:space:]]*#[[:space:]]*include[[:space:]]*"[^"]+"' include/latticra/cpp/authority.hpp |
  grep -Ev '^[[:space:]]*#[[:space:]]*include[[:space:]]*"latticra/(lat_parser|lir)\.h"[[:space:]]*$'; then
  printf 'cpp authority layer: quoted include outside authority header allowlist\n' >&2
  exit 1
fi

if grep -E '^[[:space:]]*#[[:space:]]*include[[:space:]]*"[^"]+"' src/cpp/authority.cpp |
  grep -Ev '^[[:space:]]*#[[:space:]]*include[[:space:]]*"latticra/cpp/authority\.hpp"[[:space:]]*$'; then
  printf 'cpp authority layer: quoted include outside authority source allowlist\n' >&2
  exit 1
fi

if grep -E '^[[:space:]]*#[[:space:]]*include[[:space:]]*<[^>]+>' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp |
  grep -Ev '^[^:]+:[[:space:]]*#[[:space:]]*include[[:space:]]*<(array|cstddef|cstdint|string_view)>[[:space:]]*$'; then
  printf 'cpp authority layer: standard library header outside allowed subset used\n' >&2
  exit 1
fi

if grep -E '(^|[^[:alnum:]_])(throw|try|catch|dynamic_cast|typeid|reinterpret_cast|const_cast)([^[:alnum:]_]|$)' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden exception, cast, or RTTI construct used\n' >&2
  exit 1
fi

if grep -E '(^|[^[:alnum:]_])(new|delete)([^[:alnum:]_]|$)' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden raw allocation construct used\n' >&2
  exit 1
fi

if grep -E '(^|[^[:alnum:]_])(malloc|calloc|realloc|free)[[:space:]]*\(' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden C allocation function used\n' >&2
  exit 1
fi

if grep -E 'std::(vector|shared_ptr|unique_ptr|map|unordered_map)([^[:alnum:]_]|$)|std::string([^_[:alnum:]]|$)' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden authority-path container or ownership type used\n' >&2
  exit 1
fi

if grep -E 'template[[:space:]]*<[[:space:]]*(class|typename|template)|(^|[^[:alnum:]_:])(requires|concept)([^[:alnum:]_]|$)|std::(enable_if|conditional|integral_constant|is_[[:alnum:]_]+|void_t)' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden template metaprogramming construct used\n' >&2
  exit 1
fi

if grep -Eo 'std::[[:alnum:]_]+' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp |
  grep -Ev 'std::(array|size_t|uint8_t|string_view)$'; then
  printf 'cpp authority layer: std api outside allowed subset used\n' >&2
  exit 1
fi

if grep -E 'namespace[[:space:]]+latticra::(runtime|kernel|server|recovery)([^[:alnum:]_]|$)|namespace[[:space:]]+(runtime|kernel|server|recovery)([^[:alnum:]_]|$)' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden framework namespace used\n' >&2
  exit 1
fi

if grep -E '(^|[^[:alnum:]_])(fopen|freopen|open|creat|read|write|socket|connect|bind|listen|accept|send|recv|system|popen|fork|exec[[:alnum:]_]*|posix_spawn)[[:space:]]*\(' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden I/O or process call used\n' >&2
  exit 1
fi

if grep -E '(^|[^[:alnum:]_])(latticra_[[:alnum:]_]*)[[:space:]]*\(' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden C substrate function call used\n' >&2
  exit 1
fi

cc $CFLAGS \
  -Iinclude \
  -c src/lat_parser.c \
  -o "$lat_parser_o"

cc $CFLAGS \
  -Iinclude \
  -c src/lir.c \
  -o "$lir_o"

c++ $CXXFLAGS \
  -Iinclude \
  -c src/cpp/authority.cpp \
  -o "$authority_o"

if nm "$authority_o" |
  awk '$2 ~ /^[BbCcDdGg]$/ { print; found = 1 } END { exit found ? 0 : 1 }'; then
  printf 'cpp authority layer: writable global data symbol emitted\n' >&2
  exit 1
fi

if nm "$authority_o" |
  awk '{
    symbol = $NF
    if (symbol ~ /^_?(malloc|calloc|realloc|free)$/ ||
        symbol ~ /^_*_Z(nw|na|dl|da)/) {
      print
      found = 1
    }
  } END { exit found ? 0 : 1 }'; then
  printf 'cpp authority layer: allocation symbol emitted\n' >&2
  exit 1
fi

if nm "$authority_o" |
  awk '{
    symbol = $NF
    if (symbol ~ /__(cxa|gxx_personality)/ ||
        symbol ~ /__Unwind/ ||
        symbol ~ /_ZT[ISV]/) {
      print
      found = 1
    }
  } END { exit found ? 0 : 1 }'; then
  printf 'cpp authority layer: exception or RTTI symbol emitted\n' >&2
  exit 1
fi

if nm "$authority_o" |
  awk '{
    symbol = $NF
    if (symbol ~ /^_?latticra_/) {
      print
      found = 1
    }
  } END { exit found ? 0 : 1 }'; then
  printf 'cpp authority layer: forbidden C substrate function symbol emitted\n' >&2
  exit 1
fi

if nm -g "$authority_o" |
  awk '$2 == "T" {
    symbol = $NF
    if (symbol !~ /^_?_Z/) {
      print
      found = 1
    }
  } END { exit found ? 0 : 1 }'; then
  printf 'cpp authority layer: public C ABI symbol emitted\n' >&2
  exit 1
fi

if nm -g "$authority_o" |
  awk '$2 ~ /^[[:upper:]]$/ && $2 != "T" && $2 != "U" {
    symbol = $NF
    if (symbol !~ /^_?_Z/) {
      print
      found = 1
    }
  } END { exit found ? 0 : 1 }'; then
  printf 'cpp authority layer: public unmangled defined symbol emitted\n' >&2
  exit 1
fi

c++ $CXXFLAGS \
  -Iinclude \
  tests/cpp_authority_layer_invariants.cpp \
  "$authority_o" \
  "$lat_parser_o" \
  "$lir_o" \
  -o "$authority_test"

for artifact in "$lat_parser_o" "$lir_o" "$authority_o" "$authority_test"
do
  require_private_path_permissions "$artifact"
done

"$authority_test"

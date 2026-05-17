#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"
: "${CXXFLAGS:=-std=c++20 -Wall -Wextra -Werror -pedantic -fno-exceptions -fno-rtti}"

if grep -E '#include <(iostream|fstream|filesystem|thread|future|regex|exception|stdexcept|vector|map|unordered_map)>' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden standard library header used\n' >&2
  exit 1
fi

if grep -E '(^|[^[:alnum:]_])(throw|try|catch|dynamic_cast|typeid)([^[:alnum:]_]|$)' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden exception or RTTI construct used\n' >&2
  exit 1
fi

if grep -E 'std::(vector|shared_ptr|map|unordered_map)' \
  include/latticra/cpp/authority.hpp src/cpp/authority.cpp; then
  printf 'cpp authority layer: forbidden authority-path container or ownership type used\n' >&2
  exit 1
fi

cc $CFLAGS \
  -Iinclude \
  -c src/lat_parser.c \
  -o /tmp/latticra-lat-parser.o

cc $CFLAGS \
  -Iinclude \
  -c src/lir.c \
  -o /tmp/latticra-lir.o

c++ $CXXFLAGS \
  -Iinclude \
  -c src/cpp/authority.cpp \
  -o /tmp/latticra-cpp-authority.o

c++ $CXXFLAGS \
  -Iinclude \
  tests/cpp_authority_layer_invariants.cpp \
  /tmp/latticra-cpp-authority.o \
  -o /tmp/latticra-cpp-authority-layer-invariants

/tmp/latticra-cpp-authority-layer-invariants

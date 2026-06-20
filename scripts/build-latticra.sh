#!/bin/sh
# scripts/build-latticra.sh
# Builds the Latticra CLI + C++ authority demo binary.
# Replicates the constrained compile steps from test-cpp-authority-layer.sh
# Usage: ./scripts/build-latticra.sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow}"
default_cxx_flag=""
for flag in -std=c++20 -std=c++2a; do
  if printf 'int main(void){return 0;}\n' | c++ "$flag" -x c++ -fsyntax-only - >/dev/null 2>&1; then
    default_cxx_flag="$flag"
    break
  fi
done
: "${CXXFLAGS:=${default_cxx_flag:- -std=c++20} -Wall -Wextra -Werror -pedantic -Wconversion -Wshadow -fno-exceptions -fno-rtti}"

CFLAGS_CLI="$CFLAGS -Wno-unused-function"

mkdir -p build/bin artifacts/receipts

tmpdir="$(mktemp -d "/tmp/latticra-cli-build.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

lat_o="$tmpdir/lat_parser.o"
lir_o="$tmpdir/lir.o"
auth_o="$tmpdir/authority.o"
cli_o="$tmpdir/latticra_cli.o"
drv_o="$tmpdir/latticra.o"

cc $CFLAGS -Iinclude -c src/lat_parser.c -o "$lat_o"
cc $CFLAGS -Iinclude -c src/lir.c -o "$lir_o"
c++ $CXXFLAGS -Iinclude -c src/cpp/authority.cpp -o "$auth_o"
cc $CFLAGS_CLI -DUSE_LATTICRA_CPP_MAIN -Iinclude -c src/latticra_cli.c -o "$cli_o"
c++ $CXXFLAGS -Iinclude -c src/cpp/latticra.cpp -o "$drv_o"

c++ $CXXFLAGS -Iinclude \
  "$drv_o" "$cli_o" "$lat_o" "$lir_o" "$auth_o" \
  -o build/bin/latticra

echo "built: build/bin/latticra"
ls -l build/bin/latticra

# Run the MVP smoke immediately after build (no-effect authority + receipt)
if [ -x "./scripts/test-latticra-authority-mvp.sh" ]; then
  ./scripts/test-latticra-authority-mvp.sh
fi

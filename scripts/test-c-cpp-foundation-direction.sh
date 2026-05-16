#!/usr/bin/env sh
set -eu

doc="docs/C_CPP_FOUNDATION_DIRECTION.md"
strategy="docs/LANGUAGE_STRATEGY.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'c/c++ foundation direction: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'c/c++ foundation direction: missing doc: %s\n' "$doc" >&2
  exit 1
fi

if [ ! -f "$strategy" ]; then
  printf 'c/c++ foundation direction: missing strategy doc: %s\n' "$strategy" >&2
  exit 1
fi

require_contains 'Status: active language direction' "$doc"
require_contains 'C is the metal.' "$doc"
require_contains 'C++ is the disciplined structure.' "$doc"
require_contains 'Latticra is the contract.' "$doc"
require_contains 'A constrained C/C++ foundation for a security-conscious system.' "$doc"
require_contains 'Lat / Latticra Language: contract layer' "$doc"
require_contains 'C++: governed authority layer' "$doc"
require_contains 'C: secure substrate' "$doc"
require_contains 'C secure substrate' "$doc"
require_contains 'boot paths' "$doc"
require_contains 'ABI boundaries' "$doc"
require_contains 'platform shims' "$doc"
require_contains 'C++ governed authority layer' "$doc"
require_contains 'policy logic' "$doc"
require_contains 'validators' "$doc"
require_contains 'effect gates' "$doc"
require_contains 'audit logic' "$doc"
require_contains 'Not unrestricted C++' "$doc"
require_contains 'unrestricted C++' "$doc"
require_contains 'explicit trust boundaries' "$doc"
require_contains 'evidence-bound validation' "$doc"
require_contains 'source-aware diagnostics' "$doc"
require_contains 'contract before capability' "$doc"
require_contains 'Rust is not the current public foundation direction for Latticra.' "$doc"
require_contains 'Approved public wording' "$doc"
require_contains 'Implementation ordering' "$doc"
require_contains 'Current validation command' "$doc"
require_contains 'sh scripts/test-c-cpp-foundation-direction.sh' "$doc"
require_contains 'Non-claims' "$doc"

require_contains 'Scope: C, constrained C++, Lat, L-UI, LIR, and implementation ordering.' "$strategy"
require_contains 'C is the metal.' "$strategy"
require_contains 'C++ is the disciplined structure.' "$strategy"
require_contains 'Latticra is the contract.' "$strategy"
require_contains 'This does not mean unrestricted C++.' "$strategy"
require_contains 'C secure substrate' "$strategy"
require_contains 'C++ governed authority layer' "$strategy"
require_contains 'Rust is not the current public foundation direction for Latticra.' "$strategy"
require_contains 'C and constrained C++ implementations' "$strategy"

printf 'c_cpp_foundation_direction: ok\n'

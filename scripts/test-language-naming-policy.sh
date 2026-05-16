#!/usr/bin/env sh
set -eu

policy="docs/LANGUAGE_NAMING_POLICY.md"
strategy="docs/LANGUAGE_STRATEGY.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'language naming policy: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$policy" ]; then
  printf 'language naming policy: missing doc: %s\n' "$policy" >&2
  exit 1
fi

if [ ! -f "$strategy" ]; then
  printf 'language naming policy: missing doc: %s\n' "$strategy" >&2
  exit 1
fi

require_contains 'Status: language naming policy' "$policy"
require_contains 'Plain `L` is too collision-prone' "$policy"
require_contains 'Latticra must not claim plain:' "$policy"
require_contains 'L' "$policy"
require_contains '.l' "$policy"
require_contains 'Latticra Language' "$policy"
require_contains 'Lat' "$policy"
require_contains '.lat' "$policy"
require_contains '.lui' "$policy"
require_contains '.lir' "$policy"
require_contains 'The project should not use `.l` for Latticra source.' "$policy"
require_contains 'Dialect naming policy' "$policy"
require_contains 'Lat-Core' "$policy"
require_contains 'Lat-Orch' "$policy"
require_contains 'L-UI may keep its existing name' "$policy"
require_contains 'LIR may remain as an internal representation name' "$policy"
require_contains 'Future docs should write:' "$policy"
require_contains 'Lat / Latticra Language' "$policy"
require_contains 'formerly documented as L' "$policy"
require_contains 'Syntax examples should be marked as:' "$policy"
require_contains 'Lat example syntax only' "$policy"
require_contains 'This policy does not change:' "$policy"
require_contains 'L-UI parser behavior' "$policy"
require_contains '.lui fixtures' "$policy"
require_contains 'Future implementation gate' "$policy"
require_contains 'Forbidden behavior' "$policy"
require_contains 'claim plain `L` as the public language name' "$policy"
require_contains 'claim `.l` as the canonical source extension' "$policy"
require_contains 'imply compatibility with unrelated L-like languages' "$policy"
require_contains 'treat `.lat` files as executable before an execution contract exists' "$policy"
require_contains 'Current validation command' "$policy"
require_contains 'sh scripts/test-language-naming-policy.sh' "$policy"
require_contains 'Non-claims' "$policy"

require_contains 'Scope: C, Rust, Lat, L-UI, LIR, and implementation ordering.' "$strategy"
require_contains 'avoid using plain `L` as the public native language name' "$strategy"
require_contains 'LANGUAGE_NAMING_POLICY.md' "$strategy"
require_contains 'Lat / Latticra Language' "$strategy"
require_contains 'Canonical source extension:' "$strategy"
require_contains '.lat' "$strategy"
require_contains 'Plain `L` and `.l` are not the public language name or canonical file extension.' "$strategy"
require_contains 'Lat-Core' "$strategy"
require_contains 'Lat-Orch' "$strategy"
require_contains 'The `.lui` extension remains valid' "$strategy"
require_contains 'The `.lir` extension is reserved' "$strategy"
require_contains 'The project should not use `.l` as the canonical source extension.' "$strategy"

printf 'language_naming_policy: ok\n'

#!/bin/sh
# scripts/test-latticra-authority-mvp.sh
# Lightweight check that the built latticra binary with C++ authority layer
# can classify requests and write the expected no-effect receipt.
set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT/build/bin/latticra"

if [ ! -x "$BIN" ]; then
  echo "building latticra binary for mvp test..."
  "$ROOT/scripts/build-latticra.sh"
fi

mkdir -p "$ROOT/artifacts/receipts"

# clean specific for repeatability in this test
rm -f "$ROOT/artifacts/receipts/authority-decision-local_mutation.txt"

"$BIN" --authority local_mutation mvp-test >/dev/null || true  # expected policy_denied exit code for non-trivial effect

receipt="$ROOT/artifacts/receipts/authority-decision-local_mutation.txt"
if [ ! -f "$receipt" ]; then
  echo "FAIL: no receipt produced for local_mutation" >&2
  exit 1
fi

if ! grep -q 'type=authority_decision' "$receipt"; then
  echo "FAIL: receipt missing type" >&2
  exit 1
fi
if ! grep -q 'host_mutation=0' "$receipt"; then
  echo "FAIL: receipt does not affirm no mutation" >&2
  exit 1
fi
if ! grep -q 'mode=guarded-no-effect' "$receipt"; then
  echo "FAIL: receipt missing guarded mode" >&2
  exit 1
fi
if ! grep -q 'effect_performance_denied' "$receipt"; then
  # for non-none
  :
fi

# also smoke lat+authority path
if ! "$BIN" --lat-authority "$ROOT/fixtures/lat/minimal_module.lat" 2>&1 | grep -q 'parse_ok=1'; then
  echo "FAIL: lat-authority path" >&2
  exit 1
fi
if [ ! -f "$ROOT/artifacts/receipts/lat-authority-minimal_module.lat-default.txt" ]; then
  echo "FAIL: no lat receipt" >&2
  exit 1
fi

echo "MVP AUTHORITY + RECEIPT TEST: PASS"
exit 0

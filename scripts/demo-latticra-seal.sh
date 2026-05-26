#!/usr/bin/env bash
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
cd "$ROOT"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/demo-latticra-seal.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

echo "== Latticra Seal Demo =="
echo

echo "== Build =="
make seal-cli
echo

echo "== Version =="
./build/latticra-seal version
echo

echo "== Manifest Summary =="
./build/latticra-seal manifest
echo

echo "== Check =="
./build/latticra-seal check
echo

echo "== Verify Against Saved Baseline =="
./build/latticra-seal verify
echo

echo "== Hash Preview =="
./build/latticra-seal hashes > "$tmpdir/latticra-seal-demo-hashes.txt"
head -20 "$tmpdir/latticra-seal-demo-hashes.txt"
echo

echo "== Latest Report =="
./build/latticra-seal report

#!/usr/bin/env sh
set -eu

required_docs="
docs/latticra-seal/README.md
docs/latticra-seal/STATUS.md
docs/latticra-seal/ARCHITECTURE.md
docs/latticra-seal/USAGE.md
docs/latticra-seal/POLICY.md
docs/latticra-seal/REPORTS.md
docs/latticra-seal/BOUNDARIES.md
docs/latticra-seal/ROADMAP.md
"

for doc in $required_docs; do
  test -s "$doc" || {
    echo "missing or empty: $doc"
    exit 1
  }
done

grep -q "production security product" docs/latticra-seal/BOUNDARIES.md
grep -q "network_authority=0" docs/latticra-seal/STATUS.md
grep -q "runtime_enforcement_authority=0" docs/latticra-seal/STATUS.md
grep -q "make seal-policy-denials" docs/latticra-seal/POLICY.md
grep -q "report-only" docs/latticra-seal/REPORTS.md

echo "latticra_seal_docs: ok"

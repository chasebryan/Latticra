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
docs/latticra-seal/PRODUCT.md
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
grep -q "next_generation_security_product_target=1" docs/latticra-seal/STATUS.md
grep -q "product_spine_present=1" docs/latticra-seal/STATUS.md
grep -q "product_spine_status_present=1" docs/latticra-seal/STATUS.md
grep -q "make seal-policy-denials" docs/latticra-seal/POLICY.md
grep -q "report-only" docs/latticra-seal/REPORTS.md
grep -q "production_security_product=0" docs/latticra-seal/PRODUCT.md
grep -q "runtime_authority_granted=0" docs/latticra-seal/PRODUCT.md
grep -q "seal_capability_metadata_report=1" docs/latticra-seal/PRODUCT.md
grep -q "seal_product_spine_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "product_spine_changes_authority=0" docs/latticra-seal/PRODUCT.md
grep -q "operator_receipt_report_contract_present=1" docs/latticra-seal/PRODUCT.md
grep -q "operator_receipt_report_implementation_plan_present=1" docs/latticra-seal/PRODUCT.md
grep -q "operator_receipt_report_implementation_present=1" docs/latticra-seal/PRODUCT.md
grep -q "operator_receipt_report_surface_present=1" docs/latticra-seal/PRODUCT.md
grep -q "operator_receipt_report_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "local_capability_registry_schema_contract_present=1" docs/latticra-seal/PRODUCT.md
grep -q "local_capability_registry_schema_implementation_plan_present=1" docs/latticra-seal/PRODUCT.md
grep -q "local_capability_registry_schema_implementation_present=1" docs/latticra-seal/PRODUCT.md
grep -q "seal_operator_receipt_report=1" docs/latticra-seal/REPORTS.md

echo "latticra_seal_docs: ok"

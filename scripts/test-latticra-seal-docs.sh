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
grep -q "policy.required_files" docs/latticra-seal/POLICY.md
grep -q "policy.deny_filenames" docs/latticra-seal/POLICY.md
grep -q "policy.deny_contents" docs/latticra-seal/POLICY.md
grep -q "\\[paths\\].include" docs/latticra-seal/POLICY.md
grep -q "\\[paths\\].exclude" docs/latticra-seal/POLICY.md
grep -q "make seal-check" docs/latticra-seal/USAGE.md
grep -q "make seal-smoke" docs/latticra-seal/USAGE.md
grep -q "report-only" docs/latticra-seal/REPORTS.md
grep -q "reports/latticra-seal-cli-report.txt" docs/latticra-seal/REPORTS.md
grep -q "reports/latticra-seal-cli-hashes.txt" docs/latticra-seal/REPORTS.md
grep -q "\\[report\\]" docs/latticra-seal/REPORTS.md
grep -q "group/world-writable report directories" docs/latticra-seal/REPORTS.md
grep -q "temporary report file" docs/latticra-seal/REPORTS.md
grep -q "path sort order" docs/latticra-seal/REPORTS.md
grep -q "reports/latticra-seal-cli-report.txt" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "reports/latticra-seal-report.txt" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "\\[report\\].default_output" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "seal configuration fields must fail closed" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "unsorted baseline entries" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "atomic promotion" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "policy.required_files" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "pattern_parts" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "policy.deny_filenames" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "\\[paths\\].include" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "directory patterns ending in" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "fail closed" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "pattern_parts" latticra.seal
grep -Fq '".venv*/"' latticra.seal
grep -q 'default_output = "reports/latticra-seal-cli-report.txt"' latticra.seal
grep -q 'hash_list_output = "reports/latticra-seal-cli-hashes.txt"' latticra.seal
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
grep -q "local_capability_registry_schema_surface_present=1" docs/latticra-seal/PRODUCT.md
grep -q "local_capability_registry_schema_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_planning_checkpoint_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_planning_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_view_model_contract_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_view_model_contract_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_view_model_implementation_plan_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_view_model_implementation_plan_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_view_model_implementation_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_view_model_surface_present=1" docs/latticra-seal/PRODUCT.md
grep -q "panel_dashboard_view_model_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "seal_panel_dashboard=view-model-report-surface" docs/latticra-seal/PRODUCT.md
grep -q "seal_panel_dashboard_view_model=report-surface" docs/latticra-seal/PRODUCT.md
grep -q "seal_operator_receipt_report=1" docs/latticra-seal/REPORTS.md

echo "latticra_seal_docs: ok"

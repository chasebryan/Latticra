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
grep -q "Quoted array tokens must not use backslash escapes" docs/latticra-seal/POLICY.md
grep -q "Nested content marker parts must be non-empty" docs/latticra-seal/POLICY.md
grep -q "does not enforce large-binary denial" docs/latticra-seal/POLICY.md
grep -q "large-binary policy declarations must fail closed" docs/latticra-seal/POLICY.md
grep -q "make seal-check" docs/latticra-seal/USAGE.md
grep -q "make seal-smoke" docs/latticra-seal/USAGE.md
grep -q "latticra-seal check" docs/latticra-seal/USAGE.md
grep -q "latticra-seal manifest" docs/latticra-seal/USAGE.md
grep -q "latticra-seal verify" docs/latticra-seal/USAGE.md
grep -q "required root, project" docs/latticra-seal/USAGE.md
grep -q "quoted unsupported" docs/latticra-seal/USAGE.md
grep -q "report artifact is missing" docs/latticra-seal/USAGE.md
grep -q "latticra-seal hashes" docs/latticra-seal/USAGE.md
grep -q "empty, unreadable, malformed" docs/latticra-seal/USAGE.md
grep -q "malformed, embedded-NUL" docs/latticra-seal/USAGE.md
grep -q "CRLF/non-LF-terminated" docs/latticra-seal/USAGE.md
grep -q "parses the accepted hash-list descriptor" docs/latticra-seal/USAGE.md
grep -q "Hash-list descriptor parsing and streaming require size-stable" docs/latticra-seal/USAGE.md
grep -q "latticra-seal version" docs/latticra-seal/USAGE.md
grep -q "latticra-seal help" docs/latticra-seal/USAGE.md
grep -q "latticra-seal hybrid" docs/latticra-seal/USAGE.md
grep -q "latticra-seal hybrid-provider-self-test" docs/latticra-seal/USAGE.md
grep -q "AES-256-GCM seal/open self-check" docs/latticra-seal/USAGE.md
grep -q "provider-backed" docs/latticra-seal/USAGE.md
grep -q "ECDH-P-256" docs/latticra-seal/USAGE.md
grep -q "ML-KEM-512" docs/latticra-seal/USAGE.md
grep -q "runtime_authority_granted=0" docs/latticra-seal/USAGE.md
grep -q "Quoted summary fields that contain backslash escapes" docs/latticra-seal/USAGE.md
grep -q "clears stale native hash-list artifacts before manifest parsing" docs/latticra-seal/USAGE.md
grep -q "prevent temporary hash-list creation" docs/latticra-seal/USAGE.md
grep -q "artifact setup failures remove the created temp path" docs/latticra-seal/USAGE.md
grep -q "identity metadata must be present" docs/latticra-seal/USAGE.md
grep -q "reserved proof metadata checks pass" docs/latticra-seal/USAGE.md
grep -q "large-binary policy" docs/latticra-seal/USAGE.md
grep -q "refuses symlinked, hard-linked, or embedded-NUL manifests" docs/latticra-seal/USAGE.md
grep -q "size-stable descriptor read" docs/latticra-seal/USAGE.md
grep -q "substrate generates salt and nonce" docs/latticra-seal/USAGE.md
grep -q "attached self-check record" docs/latticra-seal/USAGE.md
grep -q "protected record header is bound" docs/latticra-seal/USAGE.md
grep -q "sealed record" docs/latticra-seal/USAGE.md
grep -q "cleanses its self-check record and recovered-plaintext buffers" docs/latticra-seal/USAGE.md
grep -q "stdout cannot be written" docs/latticra-seal/USAGE.md
grep -q "Manifest-declared required files must remain inside" docs/latticra-seal/USAGE.md
grep -q "generated Seal artifacts are suppressed" docs/latticra-seal/USAGE.md
grep -q "canonical native hash-list paths" docs/latticra-seal/USAGE.md
grep -q "directories must still match their observed" docs/latticra-seal/USAGE.md
grep -q "descriptor size after the read" docs/latticra-seal/USAGE.md
grep -q "Directory read or close failures make traversal incomplete" docs/latticra-seal/USAGE.md
grep -q "dynamic capacity growth would overflow" docs/latticra-seal/USAGE.md
grep -q "marker overlap" docs/latticra-seal/USAGE.md
grep -q "report-only" docs/latticra-seal/REPORTS.md
grep -q "reports/latticra-seal-cli-report.txt" docs/latticra-seal/REPORTS.md
grep -q "reports/latticra-seal-cli-hashes.txt" docs/latticra-seal/REPORTS.md
grep -q "\\[report\\]" docs/latticra-seal/REPORTS.md
grep -q "group/world-writable report directories" docs/latticra-seal/REPORTS.md
grep -q "refuse symlinked or group/world-writable report directories" docs/latticra-seal/REPORTS.md
grep -q "hard-linked, or non-regular final and temporary report paths" docs/latticra-seal/REPORTS.md
grep -q "Manifest reads and manifest hashing require" docs/latticra-seal/REPORTS.md
grep -q "identity metadata must also be present" docs/latticra-seal/REPORTS.md
grep -q "quoted unsupported" docs/latticra-seal/REPORTS.md
grep -q "without embedded NUL bytes" docs/latticra-seal/REPORTS.md
grep -q "size-stable descriptor read" docs/latticra-seal/REPORTS.md
grep -q "computed from the parsed manifest" docs/latticra-seal/REPORTS.md
grep -q "clear stale native hash-list artifacts" docs/latticra-seal/REPORTS.md
grep -q "prevent temporary hash-list creation" docs/latticra-seal/REPORTS.md
grep -q "removes the created temporary artifact" docs/latticra-seal/REPORTS.md
grep -q "reserved proof metadata checks pass" docs/latticra-seal/REPORTS.md
grep -q "hard-linked, or non-regular lock paths" docs/latticra-seal/REPORTS.md
grep -q "create-new semantics" docs/latticra-seal/REPORTS.md
grep -q "temporary report file" docs/latticra-seal/REPORTS.md
grep -q "temporary hash-list" docs/latticra-seal/REPORTS.md
grep -q "artifact cannot be read, is empty, is hard-linked" docs/latticra-seal/REPORTS.md
grep -q "refuses empty, malformed, embedded-NUL, CRLF" docs/latticra-seal/REPORTS.md
grep -q "baseline comparison require" docs/latticra-seal/REPORTS.md
grep -q "embedded-NUL-free" docs/latticra-seal/REPORTS.md
grep -q "LF-terminated" docs/latticra-seal/REPORTS.md
grep -q "CR-free" docs/latticra-seal/REPORTS.md
grep -q "are refused before comparison" docs/latticra-seal/REPORTS.md
grep -q "truncated output" docs/latticra-seal/REPORTS.md
grep -q "sort order" docs/latticra-seal/REPORTS.md
grep -q "Required files declared by the manifest must also stay inside" docs/latticra-seal/REPORTS.md
grep -q "missing, hard-linked, or excluded required file" docs/latticra-seal/REPORTS.md
grep -q "built-in exclusions from" docs/latticra-seal/REPORTS.md
grep -q "backslash-free" docs/latticra-seal/REPORTS.md
grep -q "Recursed directories must still" docs/latticra-seal/REPORTS.md
grep -q "descriptor size after the read" docs/latticra-seal/REPORTS.md
grep -q "Directory read or close failures make traversal incomplete" docs/latticra-seal/REPORTS.md
grep -q "dynamic capacity growth would overflow" docs/latticra-seal/REPORTS.md
grep -q "marker overlap" docs/latticra-seal/REPORTS.md
grep -q "reports/latticra-seal-cli-report.txt" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "reports/latticra-seal-report.txt" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "\\[report\\].default_output" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "require core project identity metadata" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "manifest summary requires \`name\`, \`id\`" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "including quoted table" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "seal configuration fields must fail closed" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "manifest summary command is read-only" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Quoted summary fields that contain backslash escapes" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "including \`manifest\`, \`report\`, \`hashes\`, \`version\`" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "must refuse empty report artifacts" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "before streaming artifact contents" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "empty, malformed, embedded-NUL, CRLF" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Native manifest readers and manifest hashing must treat" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Embedded NUL bytes must fail" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "size-stable descriptor read" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Embedded NUL bytes," docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "carriage returns, and non-LF-terminated entries" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "computed from the parsed manifest bytes" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "must clear stale" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "regular hash-list artifacts before manifest or baseline gates" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "reserved proof metadata shape checks" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "prevent temporary native hash-list creation" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Post-open setup failures" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "does not enforce large-binary denial" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "max_file_size_mb" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "single-link regular files" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "canonical native hash-list paths" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Report-streaming commands, including \`check\` and \`verify\`" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "unsorted baseline entries" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "verification must reject empty" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "malformed, unsafe, duplicate" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "baseline comparison must require size-stable" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "temporary hash-list paths" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "temporary lockfile" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "hard-linked lockfiles before comparing hashes" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "accepted baseline descriptor" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "accepted lockfile descriptor" docs/latticra-seal/REPORTS.md
grep -q "hard-linked, or non-regular final and temporary report paths" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "generated Seal artifacts" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "do not truncate an existing" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "atomic promotion" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "policy.required_files" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Required files must also remain inside the effective digest scope" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "single-link regular file" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "required file is missing, hard-linked, or excluded" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "traversal must open directories" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "descriptor size after the read" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Directory read or close failures must make traversal incomplete" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "does not verify proof hashes or signatures" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "any reserved" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "malformed proof claims must fail closed" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "pattern_parts" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "policy.deny_filenames" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "\\[paths\\].include" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "Quoted array tokens must not use backslash escapes" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "capacity growth would overflow an allocation size" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "marker overlap would overflow" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
grep -q "content marker part must be non-empty" docs/specs/LATTICRA_SEAL_MANIFEST_v0_1.md
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
grep -q "signed_receipt_proof_path_implementation_present=1" docs/latticra-seal/PRODUCT.md
grep -q "signed_receipt_proof_path_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "signed_receipt_proof_path_surface_present=1" docs/latticra-seal/PRODUCT.md
grep -q "signed_receipt_proof_path_surface_status_present=1" docs/latticra-seal/PRODUCT.md
grep -q "seal_panel_dashboard=view-model-report-surface" docs/latticra-seal/PRODUCT.md
grep -q "seal_panel_dashboard_view_model=report-surface" docs/latticra-seal/PRODUCT.md
grep -q "seal_signed_receipt_proof_path=verification-only-report-surface" docs/latticra-seal/PRODUCT.md
grep -q "seal_operator_receipt_report=1" docs/latticra-seal/REPORTS.md

echo "latticra_seal_docs: ok"

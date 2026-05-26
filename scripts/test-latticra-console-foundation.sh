#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-console-foundation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

foundation_bin="$tmpdir/latticra-console-foundation"
report_bin="$tmpdir/latticra-console-report"
report_txt="$tmpdir/latticra-console-report.txt"
help_txt="$tmpdir/latticra-console-help.txt"
man_txt="$tmpdir/latticra-console-man.txt"
boundary_txt="$tmpdir/latticra-console-boundary.txt"
host_contract_txt="$tmpdir/latticra-console-host-contract.txt"
host_inventory_txt="$tmpdir/latticra-console-host-inventory.txt"
host_adapter_txt="$tmpdir/latticra-console-host-adapter.txt"
receipt_request_txt="$tmpdir/latticra-console-receipt-request.txt"
receipt_payload_txt="$tmpdir/latticra-console-receipt-payload.txt"
receipt_artifact_txt="$tmpdir/latticra-console-receipt-artifact.txt"
receipt_artifact_review_txt="$tmpdir/latticra-console-receipt-artifact-review.txt"
receipt_materialization_plan_txt="$tmpdir/latticra-console-receipt-materialization-plan.txt"
signature_request_txt="$tmpdir/latticra-console-signature-request.txt"
receipts_txt="$tmpdir/latticra-console-receipts.txt"
os_contract_txt="$tmpdir/latticra-console-os-contract.txt"
vm_evidence_txt="$tmpdir/latticra-console-vm-evidence.txt"
status_file="docs/status/LATTICRA_CONSOLE_FOUNDATION_STATUS.md"
status_index="docs/status/README.md"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/lat_parser.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/latticra_console.c \
  tests/latticra_console_foundation.c \
  -o "$foundation_bin"

"$foundation_bin"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/lat_parser.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/latticra_console.c \
  tools/latticra_console_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"
"$report_bin" help > "$help_txt"
"$report_bin" man > "$man_txt"
"$report_bin" boundary > "$boundary_txt"
"$report_bin" host-contract > "$host_contract_txt"
"$report_bin" host-inventory > "$host_inventory_txt"
"$report_bin" host-adapter > "$host_adapter_txt"
"$report_bin" receipt-request > "$receipt_request_txt"
"$report_bin" receipt-payload > "$receipt_payload_txt"
"$report_bin" receipt-artifact > "$receipt_artifact_txt"
"$report_bin" receipt-artifact-review > "$receipt_artifact_review_txt"
"$report_bin" receipt-materialization-plan > "$receipt_materialization_plan_txt"
"$report_bin" signature-request > "$signature_request_txt"
"$report_bin" receipts > "$receipts_txt"
"$report_bin" os-contract > "$os_contract_txt"
"$report_bin" vm-evidence > "$vm_evidence_txt"

grep -Fq 'LATTICRA CONSOLE REPORT' "$report_txt"
grep -Fq 'console_id=latticra-console' "$report_txt"
grep -Fq 'short_name=LC' "$report_txt"
grep -Fq 'component_key=latticra_console' "$report_txt"
grep -Fq 'console_status=ready-report-only' "$report_txt"
grep -Fq 'command_registry_status=seed-registry-ready' "$report_txt"
grep -Fq 'command_registry_source=c-static-table' "$report_txt"
grep -Fq 'command_registry_no_effect=1' "$report_txt"
grep -Fq 'runtime_boundary_bound=1' "$report_txt"
grep -Fq 'seal_capability_labels_bound=1' "$report_txt"
grep -Fq 'LATTICRA CONSOLE COMMAND REGISTRY' "$report_txt"
grep -Fq 'command=lc install-config' "$report_txt"
grep -Fq 'capability=lc.install.config' "$report_txt"
grep -Fq 'command=lc profiles' "$report_txt"
grep -Fq 'capability=lc.core.profiles' "$report_txt"
grep -Fq 'command=lc host-contract' "$report_txt"
grep -Fq 'capability=lc.host.contract' "$report_txt"
grep -Fq 'command=lc host-inventory' "$report_txt"
grep -Fq 'capability=lc.host.inventory' "$report_txt"
grep -Fq 'command=lc host-adapter' "$report_txt"
grep -Fq 'capability=lc.host.adapter' "$report_txt"
grep -Fq 'command=lc receipt-request' "$report_txt"
grep -Fq 'capability=lc.receipt.request' "$report_txt"
grep -Fq 'command=lc receipt-payload' "$report_txt"
grep -Fq 'capability=lc.receipt.payload' "$report_txt"
grep -Fq 'command=lc receipt-artifact' "$report_txt"
grep -Fq 'capability=lc.receipt.artifact' "$report_txt"
grep -Fq 'command=lc receipt-artifact-review' "$report_txt"
grep -Fq 'capability=lc.receipt.artifact.review' "$report_txt"
grep -Fq 'command=lc receipt-materialization-plan' "$report_txt"
grep -Fq 'capability=lc.receipt.materialization.plan' "$report_txt"
grep -Fq 'command=lc signature-request' "$report_txt"
grep -Fq 'capability=lc.signature.request' "$report_txt"
grep -Fq 'command=lc receipts' "$report_txt"
grep -Fq 'capability=lc.receipts.inspect' "$report_txt"
grep -Fq 'command=lc os-contract' "$report_txt"
grep -Fq 'capability=lc.os.contract' "$report_txt"
grep -Fq 'command=lc vm-evidence' "$report_txt"
grep -Fq 'capability=lc.vm.evidence' "$report_txt"
grep -Fq 'command=lc substrate' "$report_txt"
grep -Fq 'capability=lc.substrate.inspect' "$report_txt"
grep -Fq 'launches_host_process=0' "$report_txt"
grep -Fq 'substrate_bridge_status=metadata-bound-ready' "$report_txt"
grep -Fq 'host_embedding_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'host_embedding_contract_present=1' "$report_txt"
grep -Fq 'host_inventory_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'host_inventory_contract_present=1' "$report_txt"
grep -Fq 'host_adapter_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'host_adapter_contract_present=1' "$report_txt"
grep -Fq 'receipt_request_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'receipt_request_contract_present=1' "$report_txt"
grep -Fq 'receipt_payload_schema_status=metadata-only-schema-ready' "$report_txt"
grep -Fq 'receipt_payload_schema_present=1' "$report_txt"
grep -Fq 'receipt_payload_artifact_draft_status=metadata-only-draft-ready' "$report_txt"
grep -Fq 'receipt_payload_artifact_draft_present=1' "$report_txt"
grep -Fq 'receipt_payload_artifact_review_status=metadata-only-review-gate-ready' "$report_txt"
grep -Fq 'receipt_payload_artifact_review_present=1' "$report_txt"
grep -Fq 'receipt_payload_materialization_plan_status=metadata-only-plan-ready' "$report_txt"
grep -Fq 'receipt_payload_materialization_plan_present=1' "$report_txt"
grep -Fq 'signature_request_binding_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'signature_request_binding_present=1' "$report_txt"
grep -Fq 'receipt_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'receipt_contract_present=1' "$report_txt"
grep -Fq 'os_base_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'os_base_contract_present=1' "$report_txt"
grep -Fq 'vm_evidence_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'vm_evidence_contract_present=1' "$report_txt"
grep -Fq 'panel_installable=1' "$report_txt"
grep -Fq 'future_os_base_claim=planned_not_claimed' "$report_txt"
grep -Fq 'execution_allowed=0' "$report_txt"
grep -Fq 'network_allowed=0' "$report_txt"
grep -Fq 'boot_allowed=0' "$report_txt"
grep -Fq 'os_base_enabled=0' "$report_txt"
grep -Fq 'production_os_claim=0' "$report_txt"
grep -Fq 'LATTICRA CONSOLE HELP' "$help_txt"
grep -Fq 'registry_source=c-static-table' "$help_txt"
grep -Fq 'lc install-config' "$help_txt"
grep -Fq 'lc profiles' "$help_txt"
grep -Fq 'lc receipts' "$help_txt"
grep -Fq 'lc host-contract' "$help_txt"
grep -Fq 'lc host-inventory' "$help_txt"
grep -Fq 'lc host-adapter' "$help_txt"
grep -Fq 'lc receipt-request' "$help_txt"
grep -Fq 'lc receipt-payload' "$help_txt"
grep -Fq 'lc receipt-artifact' "$help_txt"
grep -Fq 'lc receipt-artifact-review' "$help_txt"
grep -Fq 'lc receipt-materialization-plan' "$help_txt"
grep -Fq 'lc signature-request' "$help_txt"
grep -Fq 'lc os-contract' "$help_txt"
grep -Fq 'lc vm-evidence' "$help_txt"
grep -Fq 'lc substrate' "$help_txt"
grep -Fq 'capability=lc.substrate.inspect' "$help_txt"
grep -Fq 'host_process_launch_allowed=0' "$help_txt"
grep -Fq 'LATTICRA-CONSOLE(1)' "$man_txt"
grep -Fq 'COMMANDS' "$man_txt"
grep -Fq 'latticra-lc install-config' "$man_txt"
grep -Fq 'latticra-lc host-contract' "$man_txt"
grep -Fq 'latticra-lc host-inventory' "$man_txt"
grep -Fq 'latticra-lc host-adapter' "$man_txt"
grep -Fq 'latticra-lc receipt-request' "$man_txt"
grep -Fq 'latticra-lc receipt-payload' "$man_txt"
grep -Fq 'latticra-lc receipt-artifact' "$man_txt"
grep -Fq 'latticra-lc receipt-artifact-review' "$man_txt"
grep -Fq 'latticra-lc receipt-materialization-plan' "$man_txt"
grep -Fq 'latticra-lc signature-request' "$man_txt"
grep -Fq 'latticra-lc receipts' "$man_txt"
grep -Fq 'latticra-lc os-contract' "$man_txt"
grep -Fq 'latticra-lc vm-evidence' "$man_txt"
grep -Fq 'production_os_claim=0' "$man_txt"
grep -Fq 'LATTICRA CONSOLE COMMAND BOUNDARY REPORT' "$boundary_txt"
grep -Fq 'runtime_boundary_bound=1' "$boundary_txt"
grep -Fq 'seal_capability_labels_bound=1' "$boundary_txt"
grep -Fq 'command=lc install-config' "$boundary_txt"
grep -Fq 'command=lc substrate' "$boundary_txt"
grep -Fq 'command=lc host-contract' "$boundary_txt"
grep -Fq 'command=lc host-inventory' "$boundary_txt"
grep -Fq 'command=lc host-adapter' "$boundary_txt"
grep -Fq 'command=lc receipt-request' "$boundary_txt"
grep -Fq 'command=lc receipt-payload' "$boundary_txt"
grep -Fq 'command=lc receipt-artifact' "$boundary_txt"
grep -Fq 'command=lc receipt-artifact-review' "$boundary_txt"
grep -Fq 'command=lc receipt-materialization-plan' "$boundary_txt"
grep -Fq 'command=lc signature-request' "$boundary_txt"
grep -Fq 'command=lc receipts' "$boundary_txt"
grep -Fq 'runtime_request=authority-check' "$boundary_txt"
grep -Fq 'command=lc os-contract' "$boundary_txt"
grep -Fq 'command=lc vm-evidence' "$boundary_txt"
grep -Fq 'command=lc os' "$boundary_txt"
grep -Fq 'policy_matrix_cell=future-gated-operation' "$boundary_txt"
grep -Fq 'seal_capability=seal.capability.inspect' "$boundary_txt"
grep -Fq 'boot_allowed=0' "$boundary_txt"
grep -Fq 'LATTICRA CONSOLE HOST EMBEDDING CONTRACT' "$host_contract_txt"
grep -Fq 'contract_profile=lc-host-embedding-v0' "$host_contract_txt"
grep -Fq 'host_process_launch_allowed=0' "$host_contract_txt"
grep -Fq 'host_file_read_allowed=0' "$host_contract_txt"
grep -Fq 'promotion_gate=contract_receipt_and_read_only_host_inventory' "$host_contract_txt"
grep -Fq 'LATTICRA CONSOLE READ-ONLY HOST INVENTORY CONTRACT' "$host_inventory_txt"
grep -Fq 'contract_profile=lc-host-inventory-v0' "$host_inventory_txt"
grep -Fq 'inventory_performed=0' "$host_inventory_txt"
grep -Fq 'host_probe_allowed=0' "$host_inventory_txt"
grep -Fq 'host_file_read_allowed=0' "$host_inventory_txt"
grep -Fq 'promotion_gate=host_inventory_contract_receipt_before_host_adapter' "$host_inventory_txt"
grep -Fq 'LATTICRA CONSOLE HOST ADAPTER CONTRACT' "$host_adapter_txt"
grep -Fq 'contract_profile=lc-host-adapter-v0' "$host_adapter_txt"
grep -Fq 'host_adapter_enabled=0' "$host_adapter_txt"
grep -Fq 'host_process_launch_allowed=0' "$host_adapter_txt"
grep -Fq 'host_file_read_allowed=0' "$host_adapter_txt"
grep -Fq 'promotion_gate=host_adapter_contract_receipts_and_inventory' "$host_adapter_txt"
grep -Fq 'LATTICRA CONSOLE SEAL RECEIPT REQUEST CONTRACT' "$receipt_request_txt"
grep -Fq 'request_profile=lc-receipt-request-v0' "$receipt_request_txt"
grep -Fq 'receipt_payload_schema_profile=lc-receipt-payload-schema-v0' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_draft_command=lc receipt-artifact' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_review_command=lc receipt-artifact-review' "$receipt_request_txt"
grep -Fq 'receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$receipt_request_txt"
grep -Fq 'receipt_payload_materialization_plan_command=lc receipt-materialization-plan' "$receipt_request_txt"
grep -Fq 'draft_review_receipt_present=0' "$receipt_request_txt"
grep -Fq 'materialization_preconditions_met=0' "$receipt_request_txt"
grep -Fq 'materialization_allowed=0' "$receipt_request_txt"
grep -Fq 'payload_artifact_present=0' "$receipt_request_txt"
grep -Fq 'signature_request_binding_profile=lc-signature-request-binding-v0' "$receipt_request_txt"
grep -Fq 'signature_request_profile=latticra-seal-signature-request/0.1' "$receipt_request_txt"
grep -Fq 'requested_receipt_profile=latticra-seal-verified-receipt/0.1' "$receipt_request_txt"
grep -Fq 'seal_signature_request_present=0' "$receipt_request_txt"
grep -Fq 'receipt_write_allowed=0' "$receipt_request_txt"
grep -Fq 'promotion_gate=lc_receipt_request_review_before_signing' "$receipt_request_txt"
grep -Fq 'LATTICRA CONSOLE RECEIPT PAYLOAD SCHEMA' "$receipt_payload_txt"
grep -Fq 'schema_profile=lc-receipt-payload-schema-v0' "$receipt_payload_txt"
grep -Fq 'payload_fields=console_id,profile,command_registry' "$receipt_payload_txt"
grep -Fq 'payload_artifact_present=0' "$receipt_payload_txt"
grep -Fq 'receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0' "$receipt_payload_txt"
grep -Fq 'receipt_payload_artifact_draft_command=lc receipt-artifact' "$receipt_payload_txt"
grep -Fq 'receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0' "$receipt_payload_txt"
grep -Fq 'receipt_payload_artifact_review_command=lc receipt-artifact-review' "$receipt_payload_txt"
grep -Fq 'receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$receipt_payload_txt"
grep -Fq 'receipt_payload_materialization_plan_command=lc receipt-materialization-plan' "$receipt_payload_txt"
grep -Fq 'materialization_preconditions_met=0' "$receipt_payload_txt"
grep -Fq 'materialization_allowed=0' "$receipt_payload_txt"
grep -Fq 'signature_request_binding_allowed=0' "$receipt_payload_txt"
grep -Fq 'signature_request_binding_contract_present=1' "$receipt_payload_txt"
grep -Fq 'receipt_write_allowed=0' "$receipt_payload_txt"
grep -Fq 'promotion_gate=lc_receipt_payload_schema_before_signature_request_binding' "$receipt_payload_txt"
grep -Fq 'LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT DRAFT' "$receipt_artifact_txt"
grep -Fq 'draft_profile=lc-receipt-payload-artifact-draft-v0' "$receipt_artifact_txt"
grep -Fq 'draft_contract_present=1' "$receipt_artifact_txt"
grep -Fq 'receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0' "$receipt_artifact_txt"
grep -Fq 'related_review_command=lc receipt-artifact-review' "$receipt_artifact_txt"
grep -Fq 'receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$receipt_artifact_txt"
grep -Fq 'related_materialization_plan_command=lc receipt-materialization-plan' "$receipt_artifact_txt"
grep -Fq 'draft_review_receipt_present=0' "$receipt_artifact_txt"
grep -Fq 'materialization_preconditions_met=0' "$receipt_artifact_txt"
grep -Fq 'materialization_allowed=0' "$receipt_artifact_txt"
grep -Fq 'payload_artifact_present=0' "$receipt_artifact_txt"
grep -Fq 'payload_write_allowed=0' "$receipt_artifact_txt"
grep -Fq 'payload_hash_computed=0' "$receipt_artifact_txt"
grep -Fq 'payload_path_recorded=0' "$receipt_artifact_txt"
grep -Fq 'signature_request_binding_allowed=0' "$receipt_artifact_txt"
grep -Fq 'seal_signature_request_ready=0' "$receipt_artifact_txt"
grep -Fq 'receipt_write_allowed=0' "$receipt_artifact_txt"
grep -Fq 'command_surface=lc receipt-artifact' "$receipt_artifact_txt"
grep -Fq 'promotion_gate=lc_receipt_payload_artifact_draft_before_materialization_and_signature_request' "$receipt_artifact_txt"
grep -Fq 'LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT REVIEW GATE' "$receipt_artifact_review_txt"
grep -Fq 'review_profile=lc-receipt-payload-artifact-review-v0' "$receipt_artifact_review_txt"
grep -Fq 'receipt_payload_artifact_draft_present=1' "$receipt_artifact_review_txt"
grep -Fq 'receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$receipt_artifact_review_txt"
grep -Fq 'receipt_payload_materialization_plan_command=lc receipt-materialization-plan' "$receipt_artifact_review_txt"
grep -Fq 'draft_review_present=0' "$receipt_artifact_review_txt"
grep -Fq 'draft_review_receipt_present=0' "$receipt_artifact_review_txt"
grep -Fq 'materialization_preconditions_met=0' "$receipt_artifact_review_txt"
grep -Fq 'materialization_allowed=0' "$receipt_artifact_review_txt"
grep -Fq 'payload_artifact_present=0' "$receipt_artifact_review_txt"
grep -Fq 'payload_write_allowed=0' "$receipt_artifact_review_txt"
grep -Fq 'signature_request_binding_allowed=0' "$receipt_artifact_review_txt"
grep -Fq 'seal_signature_request_ready=0' "$receipt_artifact_review_txt"
grep -Fq 'receipt_write_allowed=0' "$receipt_artifact_review_txt"
grep -Fq 'command_surface=lc receipt-artifact-review' "$receipt_artifact_review_txt"
grep -Fq 'promotion_gate=lc_receipt_payload_artifact_review_before_materialization' "$receipt_artifact_review_txt"
grep -Fq 'LATTICRA CONSOLE RECEIPT PAYLOAD MATERIALIZATION PLAN' "$receipt_materialization_plan_txt"
grep -Fq 'materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$receipt_materialization_plan_txt"
grep -Fq 'draft_review_receipt_present=0' "$receipt_materialization_plan_txt"
grep -Fq 'materialization_preconditions_met=0' "$receipt_materialization_plan_txt"
grep -Fq 'materialization_allowed=0' "$receipt_materialization_plan_txt"
grep -Fq 'payload_artifact_present=0' "$receipt_materialization_plan_txt"
grep -Fq 'payload_write_allowed=0' "$receipt_materialization_plan_txt"
grep -Fq 'payload_file_open_allowed=0' "$receipt_materialization_plan_txt"
grep -Fq 'signature_request_binding_allowed=0' "$receipt_materialization_plan_txt"
grep -Fq 'receipt_write_allowed=0' "$receipt_materialization_plan_txt"
grep -Fq 'command_surface=lc receipt-materialization-plan' "$receipt_materialization_plan_txt"
grep -Fq 'promotion_gate=lc_receipt_payload_materialization_plan_after_review_receipt' "$receipt_materialization_plan_txt"
grep -Fq 'LATTICRA CONSOLE SIGNATURE REQUEST BINDING CONTRACT' "$signature_request_txt"
grep -Fq 'binding_profile=lc-signature-request-binding-v0' "$signature_request_txt"
grep -Fq 'receipt_payload_schema_profile=lc-receipt-payload-schema-v0' "$signature_request_txt"
grep -Fq 'receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0' "$signature_request_txt"
grep -Fq 'receipt_payload_artifact_draft_present=1' "$signature_request_txt"
grep -Fq 'receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0' "$signature_request_txt"
grep -Fq 'receipt_payload_artifact_review_present=1' "$signature_request_txt"
grep -Fq 'receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$signature_request_txt"
grep -Fq 'receipt_payload_materialization_plan_present=1' "$signature_request_txt"
grep -Fq 'materialization_preconditions_met=0' "$signature_request_txt"
grep -Fq 'materialization_allowed=0' "$signature_request_txt"
grep -Fq 'signing_authorization_profile=latticra-seal-signing-authorization/0.1' "$signature_request_txt"
grep -Fq 'signature_request_binding_artifact_present=0' "$signature_request_txt"
grep -Fq 'seal_signature_request_ready=0' "$signature_request_txt"
grep -Fq 'seal_signing_authority_present=0' "$signature_request_txt"
grep -Fq 'receipt_write_allowed=0' "$signature_request_txt"
grep -Fq 'promotion_gate=lc_signature_request_binding_after_payload_artifact_and_signing_authority' "$signature_request_txt"
grep -Fq 'LATTICRA CONSOLE RECEIPT CONTRACT' "$receipts_txt"
grep -Fq 'receipt_profile=lc-receipts-v0' "$receipts_txt"
grep -Fq 'host_inventory_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'host_adapter_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'receipt_request_contract_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_schema_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_artifact_draft_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_artifact_review_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_materialization_plan_required=1' "$receipts_txt"
grep -Fq 'signature_request_binding_required=1' "$receipts_txt"
grep -Fq 'signature_request_profile=latticra-seal-signature-request/0.1' "$receipts_txt"
grep -Fq 'seal_signature_present=0' "$receipts_txt"
grep -Fq 'receipt_signed=0' "$receipts_txt"
grep -Fq 'promotion_gate=lc_receipts_before_host_adapter_or_os_base' "$receipts_txt"
grep -Fq 'LATTICRA CONSOLE OS-BASE PLANNING CONTRACT' "$os_contract_txt"
grep -Fq 'contract_profile=lc-os-base-v0' "$os_contract_txt"
grep -Fq 'boot_authority_present=0' "$os_contract_txt"
grep -Fq 'kernel_change_allowed=0' "$os_contract_txt"
grep -Fq 'vm_evidence_contract_required=1' "$os_contract_txt"
grep -Fq 'vm_evidence_required=1' "$os_contract_txt"
grep -Fq 'promotion_gate=os_base_contract_receipt_and_vm_evidence' "$os_contract_txt"
grep -Fq 'LATTICRA CONSOLE VM EVIDENCE CONTRACT' "$vm_evidence_txt"
grep -Fq 'contract_profile=lc-vm-evidence-v0' "$vm_evidence_txt"
grep -Fq 'vm_launch_allowed=0' "$vm_evidence_txt"
grep -Fq 'hypervisor_access_allowed=0' "$vm_evidence_txt"
grep -Fq 'disk_image_write_allowed=0' "$vm_evidence_txt"
grep -Fq 'promotion_gate=vm_evidence_contract_before_boot_adjacency' "$vm_evidence_txt"

grep -Fq '[components.latticra_console]' installer/manifests/components.toml
grep -Fq 'bin/<lc.install.command_wrapper>' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/install/config.toml' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/host-inventory' installer/manifests/components.toml
grep -Fq 'LC install metadata records config/share paths and the command wrapper' installer/manifests/components.toml
grep -Fq 'latticra_console = true' installer/configs/default.installer.toml
grep -Fq 'latticra_console = true' installer/configs/local-prefix-example.installer.toml
grep -Fq 'pub latticra_console: bool' installer/latticra-installer/src/config.rs
grep -Fq 'pub struct LatticraConsoleConfig' installer/latticra-installer/src/config.rs
grep -Fq 'LatticraConsoleProfile::PanelEmbedded' installer/latticra-installer/src/config.rs
grep -Fq 'Latticra Console (LC)' installer/latticra-installer/src/ui.rs
grep -Fq 'WorkspaceTab::Console' installer/latticra-installer/src/ui.rs
grep -Fq 'profile = "panel_embedded"' installer/configs/default.installer.toml
grep -Fq '[lc.install]' installer/configs/default.installer.toml
grep -Fq 'install_profile = "lc-panel-install-v0"' installer/configs/default.installer.toml
grep -Fq 'allow_external_host_commands = false' installer/configs/default.installer.toml
grep -Fq 'command_registry_profile = "c-static-table"' installer/configs/default.installer.toml
grep -Fq 'host_embedding_contract_profile = "lc-host-embedding-v0"' installer/configs/default.installer.toml
grep -Fq 'host_inventory_contract_profile = "lc-host-inventory-v0"' installer/configs/default.installer.toml
grep -Fq 'host_adapter_contract_profile = "lc-host-adapter-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_request_contract_profile = "lc-receipt-request-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_schema_profile = "lc-receipt-payload-schema-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_artifact_draft_profile = "lc-receipt-payload-artifact-draft-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_artifact_review_profile = "lc-receipt-payload-artifact-review-v0"' installer/configs/default.installer.toml
grep -Fq 'require_receipt_payload_artifact_review = true' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_materialization_plan_profile = "lc-receipt-payload-materialization-plan-v0"' installer/configs/default.installer.toml
grep -Fq 'require_receipt_payload_materialization_plan = true' installer/configs/default.installer.toml
grep -Fq 'signature_request_binding_profile = "lc-signature-request-binding-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_contract_profile = "lc-receipts-v0"' installer/configs/default.installer.toml
grep -Fq 'os_base_contract_profile = "lc-os-base-v0"' installer/configs/default.installer.toml
grep -Fq 'vm_evidence_contract_profile = "lc-vm-evidence-v0"' installer/configs/default.installer.toml
grep -Fq 'LATTICRA_CONSOLE=$(cfg latticra_console true)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_PROFILE=$(cfg_section lc profile panel_embedded)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_INSTALL_PROFILE=$(cfg_section lc.install install_profile lc-panel-install-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_INSTALL_ALLOW_EXTERNAL_HOST_COMMANDS=$(cfg_section lc.install allow_external_host_commands false)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_HOST_EMBEDDING_CONTRACT_PROFILE=$(cfg_section lc host_embedding_contract_profile lc-host-embedding-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_HOST_INVENTORY_CONTRACT_PROFILE=$(cfg_section lc host_inventory_contract_profile lc-host-inventory-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_HOST_ADAPTER_CONTRACT_PROFILE=$(cfg_section lc host_adapter_contract_profile lc-host-adapter-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_REQUEST_CONTRACT_PROFILE=$(cfg_section lc receipt_request_contract_profile lc-receipt-request-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_SCHEMA_PROFILE=$(cfg_section lc receipt_payload_schema_profile lc-receipt-payload-schema-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_ARTIFACT_DRAFT_PROFILE=$(cfg_section lc receipt_payload_artifact_draft_profile lc-receipt-payload-artifact-draft-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_PROFILE=$(cfg_section lc receipt_payload_artifact_review_profile lc-receipt-payload-artifact-review-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_MATERIALIZATION_PLAN_PROFILE=$(cfg_section lc receipt_payload_materialization_plan_profile lc-receipt-payload-materialization-plan-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SIGNATURE_REQUEST_BINDING_PROFILE=$(cfg_section lc signature_request_binding_profile lc-signature-request-binding-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_CONTRACT_PROFILE=$(cfg_section lc receipt_contract_profile lc-receipts-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_OS_BASE_CONTRACT_PROFILE=$(cfg_section lc os_base_contract_profile lc-os-base-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_VM_EVIDENCE_CONTRACT_PROFILE=$(cfg_section lc vm_evidence_contract_profile lc-vm-evidence-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'profiles/hosted-reference.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'host-embedding/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'host-inventory/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'host-adapter/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-schema.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-artifact-draft.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-artifact-review.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-materialization-plan.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/signature-request-binding.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipts/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'os-base/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'vm-evidence/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'latticra-lc' installer/scripts/latticra-installer-apply.sh
grep -Fq 'lc install-config' installer/scripts/latticra-installer-apply.sh
grep -Fq 'render_lc_help()' installer/scripts/latticra-installer-apply.sh
grep -Fq 'render_lc_man()' installer/scripts/latticra-installer-apply.sh
grep -Fq 'render_lc_boundary()' installer/scripts/latticra-installer-apply.sh
grep -Fq 'Latticra Console Foundation' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Panel Profile Presets' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'share/latticra/lc/install/config.toml' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'lc.install.command_wrapper' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Host Embedding Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Read-Only Host Inventory Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Host Adapter Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Seal Receipt Request Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Receipt Payload Schema' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Signature Request Binding Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Receipt Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'OS-Base Planning Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'VM Evidence Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Help And Manpage Rendering' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Runtime Boundary Binding' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Status: active Stage-0 foundation' "$status_file"
grep -Fq 'latticra_console_report_surface_present=1' "$status_file"
grep -Fq 'host_adapter_contract_present=1' "$status_file"
grep -Fq 'receipt_payload_schema_present=1' "$status_file"
grep -Fq 'receipt_payload_artifact_draft_present=1' "$status_file"
grep -Fq 'receipt_payload_artifact_review_present=1' "$status_file"
grep -Fq 'receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0' "$status_file"
grep -Fq 'receipt_payload_artifact_review_status=metadata-only-review-gate' "$status_file"
grep -Fq 'receipt_payload_artifact_review_command=lc receipt-artifact-review' "$status_file"
grep -Fq 'receipt_payload_materialization_plan_present=1' "$status_file"
grep -Fq 'receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$status_file"
grep -Fq 'receipt_payload_materialization_plan_status=metadata-only-plan' "$status_file"
grep -Fq 'receipt_payload_materialization_plan_command=lc receipt-materialization-plan' "$status_file"
grep -Fq 'draft_review_receipt_present=0' "$status_file"
grep -Fq 'materialization_preconditions_met=0' "$status_file"
grep -Fq 'materialization_allowed=0' "$status_file"
grep -Fq 'signature_request_binding_present=1' "$status_file"
grep -Fq 'os_base_contract_present=1' "$status_file"
grep -Fq 'vm_evidence_contract_present=1' "$status_file"
grep -Fq 'production_os_claim=0' "$status_file"
grep -Fq 'LATTICRA_CONSOLE_FOUNDATION_STATUS.md' "$status_index"
grep -Fq 'Latticra Console foundation status' "$status_index"

printf 'latticra_console_foundation: ok\n'

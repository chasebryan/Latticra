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
standalone_txt="$tmpdir/latticra-console-standalone.txt"
session_txt="$tmpdir/latticra-console-session.txt"
workspace_txt="$tmpdir/latticra-console-workspace.txt"
namespace_txt="$tmpdir/latticra-console-namespace.txt"
rootfs_txt="$tmpdir/latticra-console-rootfs.txt"
packages_txt="$tmpdir/latticra-console-packages.txt"
init_txt="$tmpdir/latticra-console-init.txt"
services_txt="$tmpdir/latticra-console-services.txt"
service_schema_txt="$tmpdir/latticra-console-service-schema.txt"
service_definitions_txt="$tmpdir/latticra-console-service-definitions.txt"
service_plan_txt="$tmpdir/latticra-console-service-plan.txt"
service_runtime_txt="$tmpdir/latticra-console-service-runtime.txt"
processes_txt="$tmpdir/latticra-console-processes.txt"
host_contract_txt="$tmpdir/latticra-console-host-contract.txt"
host_inventory_txt="$tmpdir/latticra-console-host-inventory.txt"
host_adapter_txt="$tmpdir/latticra-console-host-adapter.txt"
receipt_request_txt="$tmpdir/latticra-console-receipt-request.txt"
receipt_payload_txt="$tmpdir/latticra-console-receipt-payload.txt"
receipt_artifact_txt="$tmpdir/latticra-console-receipt-artifact.txt"
receipt_artifact_review_txt="$tmpdir/latticra-console-receipt-artifact-review.txt"
receipt_review_receipt_txt="$tmpdir/latticra-console-receipt-review-receipt.txt"
receipt_review_draft_txt="$tmpdir/latticra-console-receipt-review-draft.txt"
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
"$report_bin" standalone > "$standalone_txt"
"$report_bin" session > "$session_txt"
"$report_bin" workspace > "$workspace_txt"
"$report_bin" namespace > "$namespace_txt"
"$report_bin" rootfs > "$rootfs_txt"
"$report_bin" packages > "$packages_txt"
"$report_bin" init > "$init_txt"
"$report_bin" services > "$services_txt"
"$report_bin" service-schema > "$service_schema_txt"
"$report_bin" service-definitions > "$service_definitions_txt"
"$report_bin" service-plan > "$service_plan_txt"
"$report_bin" service-runtime > "$service_runtime_txt"
"$report_bin" processes > "$processes_txt"
"$report_bin" host-contract > "$host_contract_txt"
"$report_bin" host-inventory > "$host_inventory_txt"
"$report_bin" host-adapter > "$host_adapter_txt"
"$report_bin" receipt-request > "$receipt_request_txt"
"$report_bin" receipt-payload > "$receipt_payload_txt"
"$report_bin" receipt-artifact > "$receipt_artifact_txt"
"$report_bin" receipt-artifact-review > "$receipt_artifact_review_txt"
"$report_bin" receipt-review-receipt > "$receipt_review_receipt_txt"
"$report_bin" receipt-review-draft > "$receipt_review_draft_txt"
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
grep -Fq 'command=lc standalone' "$report_txt"
grep -Fq 'capability=lc.standalone.inspect' "$report_txt"
grep -Fq 'command=lc session' "$report_txt"
grep -Fq 'capability=lc.session.contract' "$report_txt"
grep -Fq 'command=lc workspace' "$report_txt"
grep -Fq 'capability=lc.workspace.contract' "$report_txt"
grep -Fq 'command=lc namespace' "$report_txt"
grep -Fq 'capability=lc.namespace.contract' "$report_txt"
grep -Fq 'command=lc rootfs' "$report_txt"
grep -Fq 'capability=lc.rootfs.contract' "$report_txt"
grep -Fq 'command=lc packages' "$report_txt"
grep -Fq 'capability=lc.packages.contract' "$report_txt"
grep -Fq 'command=lc init' "$report_txt"
grep -Fq 'capability=lc.init.contract' "$report_txt"
grep -Fq 'command=lc services' "$report_txt"
grep -Fq 'capability=lc.services.contract' "$report_txt"
grep -Fq 'command=lc service-schema' "$report_txt"
grep -Fq 'capability=lc.service.schema.contract' "$report_txt"
grep -Fq 'command=lc service-definitions' "$report_txt"
grep -Fq 'capability=lc.service.definitions.contract' "$report_txt"
grep -Fq 'command=lc service-plan' "$report_txt"
grep -Fq 'capability=lc.service.plan.contract' "$report_txt"
grep -Fq 'command=lc service-runtime' "$report_txt"
grep -Fq 'capability=lc.service.runtime.contract' "$report_txt"
grep -Fq 'command=lc processes' "$report_txt"
grep -Fq 'capability=lc.processes.contract' "$report_txt"
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
grep -Fq 'command=lc receipt-review-receipt' "$report_txt"
grep -Fq 'capability=lc.receipt.review.receipt' "$report_txt"
grep -Fq 'command=lc receipt-review-draft' "$report_txt"
grep -Fq 'capability=lc.receipt.review.receipt.draft' "$report_txt"
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
grep -Fq 'receipt_payload_artifact_review_receipt_status=metadata-only-receipt-contract-ready' "$report_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$report_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_status=metadata-only-review-receipt-draft-ready' "$report_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_present=1' "$report_txt"
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
grep -Fq 'standalone_installable=1' "$report_txt"
grep -Fq 'standalone_requires_panel=0' "$report_txt"
grep -Fq 'standalone_command_wrapper=latticra-lc' "$report_txt"
grep -Fq 'standalone_console_status=metadata-only-standalone-contract-ready' "$report_txt"
grep -Fq 'standalone_contract_present=1' "$report_txt"
grep -Fq 'session_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'session_contract_present=1' "$report_txt"
grep -Fq 'workspace_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'workspace_contract_present=1' "$report_txt"
grep -Fq 'namespace_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'namespace_contract_present=1' "$report_txt"
grep -Fq 'rootfs_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'rootfs_contract_present=1' "$report_txt"
grep -Fq 'packages_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'packages_contract_present=1' "$report_txt"
grep -Fq 'init_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'init_contract_present=1' "$report_txt"
grep -Fq 'services_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'services_contract_present=1' "$report_txt"
grep -Fq 'service_schema_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'service_schema_contract_present=1' "$report_txt"
grep -Fq 'service_definitions_contract_status=metadata-only-contract-ready' "$report_txt"
grep -Fq 'service_definitions_contract_present=1' "$report_txt"
grep -Fq 'future_os_base_claim=planned_not_claimed' "$report_txt"
grep -Fq 'execution_allowed=0' "$report_txt"
grep -Fq 'network_allowed=0' "$report_txt"
grep -Fq 'boot_allowed=0' "$report_txt"
grep -Fq 'os_base_enabled=0' "$report_txt"
grep -Fq 'production_os_claim=0' "$report_txt"
grep -Fq 'LATTICRA CONSOLE HELP' "$help_txt"
grep -Fq 'registry_source=c-static-table' "$help_txt"
grep -Fq 'lc install-config' "$help_txt"
grep -Fq 'lc standalone' "$help_txt"
grep -Fq 'lc session' "$help_txt"
grep -Fq 'lc workspace' "$help_txt"
grep -Fq 'lc namespace' "$help_txt"
grep -Fq 'lc rootfs' "$help_txt"
grep -Fq 'lc packages' "$help_txt"
grep -Fq 'lc init' "$help_txt"
grep -Fq 'lc services' "$help_txt"
grep -Fq 'lc service-schema' "$help_txt"
grep -Fq 'lc service-definitions' "$help_txt"
grep -Fq 'lc service-plan' "$help_txt"
grep -Fq 'lc service-runtime' "$help_txt"
grep -Fq 'lc processes' "$help_txt"
grep -Fq 'lc profiles' "$help_txt"
grep -Fq 'lc receipts' "$help_txt"
grep -Fq 'lc host-contract' "$help_txt"
grep -Fq 'lc host-inventory' "$help_txt"
grep -Fq 'lc host-adapter' "$help_txt"
grep -Fq 'lc receipt-request' "$help_txt"
grep -Fq 'lc receipt-payload' "$help_txt"
grep -Fq 'lc receipt-artifact' "$help_txt"
grep -Fq 'lc receipt-artifact-review' "$help_txt"
grep -Fq 'lc receipt-review-receipt' "$help_txt"
grep -Fq 'lc receipt-review-draft' "$help_txt"
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
grep -Fq 'latticra-lc standalone' "$man_txt"
grep -Fq 'latticra-lc session' "$man_txt"
grep -Fq 'latticra-lc workspace' "$man_txt"
grep -Fq 'latticra-lc namespace' "$man_txt"
grep -Fq 'latticra-lc rootfs' "$man_txt"
grep -Fq 'latticra-lc packages' "$man_txt"
grep -Fq 'latticra-lc init' "$man_txt"
grep -Fq 'latticra-lc services' "$man_txt"
grep -Fq 'latticra-lc service-schema' "$man_txt"
grep -Fq 'latticra-lc service-definitions' "$man_txt"
grep -Fq 'latticra-lc service-plan' "$man_txt"
grep -Fq 'latticra-lc service-runtime' "$man_txt"
grep -Fq 'latticra-lc processes' "$man_txt"
grep -Fq 'latticra-lc host-contract' "$man_txt"
grep -Fq 'latticra-lc host-inventory' "$man_txt"
grep -Fq 'latticra-lc host-adapter' "$man_txt"
grep -Fq 'latticra-lc receipt-request' "$man_txt"
grep -Fq 'latticra-lc receipt-payload' "$man_txt"
grep -Fq 'latticra-lc receipt-artifact' "$man_txt"
grep -Fq 'latticra-lc receipt-artifact-review' "$man_txt"
grep -Fq 'latticra-lc receipt-review-receipt' "$man_txt"
grep -Fq 'latticra-lc receipt-review-draft' "$man_txt"
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
grep -Fq 'command=lc standalone' "$boundary_txt"
grep -Fq 'command=lc session' "$boundary_txt"
grep -Fq 'command=lc workspace' "$boundary_txt"
grep -Fq 'command=lc namespace' "$boundary_txt"
grep -Fq 'command=lc rootfs' "$boundary_txt"
grep -Fq 'command=lc packages' "$boundary_txt"
grep -Fq 'command=lc init' "$boundary_txt"
grep -Fq 'command=lc services' "$boundary_txt"
grep -Fq 'command=lc service-schema' "$boundary_txt"
grep -Fq 'command=lc service-definitions' "$boundary_txt"
grep -Fq 'command=lc service-plan' "$boundary_txt"
grep -Fq 'command=lc service-runtime' "$boundary_txt"
grep -Fq 'command=lc processes' "$boundary_txt"
grep -Fq 'command=lc substrate' "$boundary_txt"
grep -Fq 'command=lc host-contract' "$boundary_txt"
grep -Fq 'command=lc host-inventory' "$boundary_txt"
grep -Fq 'command=lc host-adapter' "$boundary_txt"
grep -Fq 'command=lc receipt-request' "$boundary_txt"
grep -Fq 'command=lc receipt-payload' "$boundary_txt"
grep -Fq 'command=lc receipt-artifact' "$boundary_txt"
grep -Fq 'command=lc receipt-artifact-review' "$boundary_txt"
grep -Fq 'command=lc receipt-review-receipt' "$boundary_txt"
grep -Fq 'command=lc receipt-review-draft' "$boundary_txt"
grep -Fq 'command=lc receipt-materialization-plan' "$boundary_txt"
grep -Fq 'command=lc signature-request' "$boundary_txt"
grep -Fq 'command=lc receipts' "$boundary_txt"
grep -Fq 'runtime_request=authority-check' "$boundary_txt"
grep -Fq 'command=lc os-contract' "$boundary_txt"
grep -Fq 'command=lc vm-evidence' "$boundary_txt"
grep -Fq 'command=lc os' "$boundary_txt"
grep -Fq 'policy_matrix_cell=future-gated-operation' "$boundary_txt"
grep -Fq 'seal_capability=seal.capability.inspect' "$boundary_txt"
grep -Fq 'network_allowed=0' "$boundary_txt"
grep -Fq 'runtime_enforcement_allowed=0' "$boundary_txt"
grep -Fq 'boot_allowed=0' "$boundary_txt"
grep -Fq 'LATTICRA CONSOLE STANDALONE CONTRACT' "$standalone_txt"
grep -Fq 'standalone_console_profile=lc-standalone-console-v0' "$standalone_txt"
grep -Fq 'standalone_contract_present=1' "$standalone_txt"
grep -Fq 'standalone_requires_panel=0' "$standalone_txt"
grep -Fq 'command_surface=lc standalone' "$standalone_txt"
grep -Fq 'host_process_launch_allowed=0' "$standalone_txt"
grep -Fq 'production_os_claim=0' "$standalone_txt"
grep -Fq 'LATTICRA CONSOLE SESSION CONTRACT' "$session_txt"
grep -Fq 'session_profile=lc-session-v0' "$session_txt"
grep -Fq 'session_contract_present=1' "$session_txt"
grep -Fq 'runtime_session_created=0' "$session_txt"
grep -Fq 'runtime_process_spawn_allowed=0' "$session_txt"
grep -Fq 'command_surface=lc session' "$session_txt"
grep -Fq 'host_process_launch_allowed=0' "$session_txt"
grep -Fq 'production_os_claim=0' "$session_txt"
grep -Fq 'LATTICRA CONSOLE WORKSPACE CONTRACT' "$workspace_txt"
grep -Fq 'workspace_profile=lc-workspace-v0' "$workspace_txt"
grep -Fq 'workspace_contract_present=1' "$workspace_txt"
grep -Fq 'workspace_mount_allowed=0' "$workspace_txt"
grep -Fq 'workspace_file_write_allowed=0' "$workspace_txt"
grep -Fq 'command_surface=lc workspace' "$workspace_txt"
grep -Fq 'host_process_launch_allowed=0' "$workspace_txt"
grep -Fq 'production_os_claim=0' "$workspace_txt"
grep -Fq 'LATTICRA CONSOLE NAMESPACE CONTRACT' "$namespace_txt"
grep -Fq 'namespace_profile=lc-namespace-v0' "$namespace_txt"
grep -Fq 'namespace_contract_present=1' "$namespace_txt"
grep -Fq 'namespace_mount_allowed=0' "$namespace_txt"
grep -Fq 'rootfs_mount_allowed=0' "$namespace_txt"
grep -Fq 'command_surface=lc namespace' "$namespace_txt"
grep -Fq 'host_process_launch_allowed=0' "$namespace_txt"
grep -Fq 'production_os_claim=0' "$namespace_txt"
grep -Fq 'LATTICRA CONSOLE ROOTFS CONTRACT' "$rootfs_txt"
grep -Fq 'rootfs_profile=lc-rootfs-v0' "$rootfs_txt"
grep -Fq 'rootfs_contract_present=1' "$rootfs_txt"
grep -Fq 'rootfs_image_create_allowed=0' "$rootfs_txt"
grep -Fq 'rootfs_mount_allowed=0' "$rootfs_txt"
grep -Fq 'rootfs_package_install_allowed=0' "$rootfs_txt"
grep -Fq 'command_surface=lc rootfs' "$rootfs_txt"
grep -Fq 'host_process_launch_allowed=0' "$rootfs_txt"
grep -Fq 'LATTICRA CONSOLE PACKAGES CONTRACT' "$packages_txt"
grep -Fq 'packages_profile=lc-packages-v0' "$packages_txt"
grep -Fq 'packages_contract_present=1' "$packages_txt"
grep -Fq 'package_manifest_write_allowed=0' "$packages_txt"
grep -Fq 'package_catalog_read_allowed=0' "$packages_txt"
grep -Fq 'package_download_allowed=0' "$packages_txt"
grep -Fq 'package_manager_execution_allowed=0' "$packages_txt"
grep -Fq 'rootfs_package_install_allowed=0' "$packages_txt"
grep -Fq 'command_surface=lc packages' "$packages_txt"
grep -Fq 'host_process_launch_allowed=0' "$packages_txt"
grep -Fq 'production_os_claim=0' "$packages_txt"
grep -Fq 'LATTICRA CONSOLE INIT CONTRACT' "$init_txt"
grep -Fq 'init_profile=lc-init-v0' "$init_txt"
grep -Fq 'init_contract_present=1' "$init_txt"
grep -Fq 'pid1_claim_allowed=0' "$init_txt"
grep -Fq 'service_start_allowed=0' "$init_txt"
grep -Fq 'process_supervision_allowed=0' "$init_txt"
grep -Fq 'services_contract_required=1' "$init_txt"
grep -Fq 'related_services_command=lc services' "$init_txt"
grep -Fq 'command_surface=lc init' "$init_txt"
grep -Fq 'host_process_launch_allowed=0' "$init_txt"
grep -Fq 'production_os_claim=0' "$init_txt"
grep -Fq 'LATTICRA CONSOLE SERVICES CONTRACT' "$services_txt"
grep -Fq 'services_profile=lc-services-v0' "$services_txt"
grep -Fq 'services_contract_present=1' "$services_txt"
grep -Fq 'service_registry_write_allowed=0' "$services_txt"
grep -Fq 'service_start_allowed=0' "$services_txt"
grep -Fq 'service_enable_allowed=0' "$services_txt"
grep -Fq 'process_supervision_allowed=0' "$services_txt"
grep -Fq 'init_contract_required=1' "$services_txt"
grep -Fq 'service_schema_contract_required=1' "$services_txt"
grep -Fq 'service_definitions_contract_required=1' "$services_txt"
grep -Fq 'service_plan_contract_required=1' "$services_txt"
grep -Fq 'service_runtime_contract_required=1' "$services_txt"
grep -Fq 'command_surface=lc services' "$services_txt"
grep -Fq 'related_service_schema_command=lc service-schema' "$services_txt"
grep -Fq 'related_service_definitions_command=lc service-definitions' "$services_txt"
grep -Fq 'related_service_plan_command=lc service-plan' "$services_txt"
grep -Fq 'related_service_runtime_command=lc service-runtime' "$services_txt"
grep -Fq 'host_process_launch_allowed=0' "$services_txt"
grep -Fq 'production_os_claim=0' "$services_txt"
grep -Fq 'LATTICRA CONSOLE SERVICE SCHEMA CONTRACT' "$service_schema_txt"
grep -Fq 'service_schema_profile=lc-service-schema-v0' "$service_schema_txt"
grep -Fq 'service_schema_contract_present=1' "$service_schema_txt"
grep -Fq 'service_schema_file=definition-schema.toml' "$service_schema_txt"
grep -Fq 'service_definition_write_allowed=0' "$service_schema_txt"
grep -Fq 'service_definition_validation_allowed=0' "$service_schema_txt"
grep -Fq 'service_start_allowed=0' "$service_schema_txt"
grep -Fq 'service_definitions_contract_required=1' "$service_schema_txt"
grep -Fq 'command_surface=lc service-schema' "$service_schema_txt"
grep -Fq 'related_service_definitions_command=lc service-definitions' "$service_schema_txt"
grep -Fq 'host_process_launch_allowed=0' "$service_schema_txt"
grep -Fq 'production_os_claim=0' "$service_schema_txt"
grep -Fq 'LATTICRA CONSOLE SERVICE DEFINITIONS CONTRACT' "$service_definitions_txt"
grep -Fq 'service_definitions_profile=lc-service-definitions-v0' "$service_definitions_txt"
grep -Fq 'service_definitions_contract_present=1' "$service_definitions_txt"
grep -Fq 'service_definitions_file=definitions.toml' "$service_definitions_txt"
grep -Fq 'service_definition_stub_count=0' "$service_definitions_txt"
grep -Fq 'service_definition_stub_write_allowed=0' "$service_definitions_txt"
grep -Fq 'service_definition_validation_allowed=0' "$service_definitions_txt"
grep -Fq 'service_start_allowed=0' "$service_definitions_txt"
grep -Fq 'service_schema_contract_required=1' "$service_definitions_txt"
grep -Fq 'command_surface=lc service-definitions' "$service_definitions_txt"
grep -Fq 'related_service_plan_command=lc service-plan' "$service_definitions_txt"
grep -Fq 'related_service_runtime_command=lc service-runtime' "$service_definitions_txt"
grep -Fq 'host_process_launch_allowed=0' "$service_definitions_txt"
grep -Fq 'production_os_claim=0' "$service_definitions_txt"
grep -Fq 'LATTICRA CONSOLE SERVICE PLAN CONTRACT' "$service_plan_txt"
grep -Fq 'service_plan_profile=lc-service-plan-v0' "$service_plan_txt"
grep -Fq 'service_plan_contract_present=1' "$service_plan_txt"
grep -Fq 'service_plan_file=plan.toml' "$service_plan_txt"
grep -Fq 'service_plan_created=0' "$service_plan_txt"
grep -Fq 'service_plan_materialization_allowed=0' "$service_plan_txt"
grep -Fq 'service_dependency_resolution_allowed=0' "$service_plan_txt"
grep -Fq 'service_activation_allowed=0' "$service_plan_txt"
grep -Fq 'service_start_allowed=0' "$service_plan_txt"
grep -Fq 'service_definitions_contract_required=1' "$service_plan_txt"
grep -Fq 'related_service_runtime_command=lc service-runtime' "$service_plan_txt"
grep -Fq 'command_surface=lc service-plan' "$service_plan_txt"
grep -Fq 'host_process_launch_allowed=0' "$service_plan_txt"
grep -Fq 'production_os_claim=0' "$service_plan_txt"
grep -Fq 'LATTICRA CONSOLE SERVICE RUNTIME CONTRACT' "$service_runtime_txt"
grep -Fq 'service_runtime_profile=lc-service-runtime-v0' "$service_runtime_txt"
grep -Fq 'service_runtime_contract_present=1' "$service_runtime_txt"
grep -Fq 'service_runtime_file=runtime.toml' "$service_runtime_txt"
grep -Fq 'service_runtime_created=0' "$service_runtime_txt"
grep -Fq 'service_runtime_materialization_allowed=0' "$service_runtime_txt"
grep -Fq 'service_runtime_handoff_allowed=0' "$service_runtime_txt"
grep -Fq 'service_executor_allowed=0' "$service_runtime_txt"
grep -Fq 'service_process_launch_allowed=0' "$service_runtime_txt"
grep -Fq 'service_supervision_allowed=0' "$service_runtime_txt"
grep -Fq 'service_plan_contract_required=1' "$service_runtime_txt"
grep -Fq 'command_surface=lc service-runtime' "$service_runtime_txt"
grep -Fq 'host_process_launch_allowed=0' "$service_runtime_txt"
grep -Fq 'production_os_claim=0' "$service_runtime_txt"
grep -Fq 'LATTICRA CONSOLE PROCESSES CONTRACT' "$processes_txt"
grep -Fq 'processes_profile=lc-processes-v0' "$processes_txt"
grep -Fq 'processes_contract_present=1' "$processes_txt"
grep -Fq 'processes_file=contract.toml' "$processes_txt"
grep -Fq 'process_table_present=0' "$processes_txt"
grep -Fq 'process_spawn_allowed=0' "$processes_txt"
grep -Fq 'process_exec_allowed=0' "$processes_txt"
grep -Fq 'process_signal_allowed=0' "$processes_txt"
grep -Fq 'process_supervision_allowed=0' "$processes_txt"
grep -Fq 'host_process_inspection_allowed=0' "$processes_txt"
grep -Fq 'host_process_launch_allowed=0' "$processes_txt"
grep -Fq 'service_runtime_contract_required=1' "$processes_txt"
grep -Fq 'command_surface=lc processes' "$processes_txt"
grep -Fq 'production_os_claim=0' "$processes_txt"
grep -Fq 'production_os_claim=0' "$rootfs_txt"
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
grep -Fq 'receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_required=1' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_present=1' "$receipt_request_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_command=lc receipt-review-draft' "$receipt_request_txt"
grep -Fq 'receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$receipt_request_txt"
grep -Fq 'receipt_payload_materialization_plan_command=lc receipt-materialization-plan' "$receipt_request_txt"
grep -Fq 'draft_review_receipt_present=0' "$receipt_request_txt"
grep -Fq 'materialization_preconditions_met=0' "$receipt_request_txt"
grep -Fq 'materialization_allowed=0' "$receipt_request_txt"
grep -Fq 'payload_artifact_present=0' "$receipt_request_txt"
grep -Fq 'signature_request_binding_profile=lc-signature-request-binding-v0' "$receipt_request_txt"
grep -Fq 'signature_request_profile=latticra-seal-signature-request/0.1' "$receipt_request_txt"
grep -Fq 'requested_receipt_profile=latticra-seal-verified-receipt/0.1' "$receipt_request_txt"
grep -Fq 'requested_surfaces=profile,session,workspace,namespace,rootfs,packages,init,services,service-schema,service-definitions,service-plan,service-runtime,processes,host-contract,host-inventory,host-adapter,runtime-boundary' "$receipt_request_txt"
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
grep -Fq 'receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0' "$receipt_payload_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$receipt_payload_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt' "$receipt_payload_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_present=1' "$receipt_payload_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_command=lc receipt-review-draft' "$receipt_payload_txt"
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
grep -Fq 'receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0' "$receipt_artifact_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$receipt_artifact_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt' "$receipt_artifact_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_present=1' "$receipt_artifact_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_command=lc receipt-review-draft' "$receipt_artifact_txt"
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
grep -Fq 'receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0' "$receipt_artifact_review_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_required=1' "$receipt_artifact_review_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$receipt_artifact_review_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt' "$receipt_artifact_review_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_present=1' "$receipt_artifact_review_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_command=lc receipt-review-draft' "$receipt_artifact_review_txt"
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
grep -Fq 'LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT REVIEW RECEIPT CONTRACT' "$receipt_review_receipt_txt"
grep -Fq 'review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0' "$receipt_review_receipt_txt"
grep -Fq 'draft_review_receipt_present=0' "$receipt_review_receipt_txt"
grep -Fq 'draft_review_receipt_artifact_present=0' "$receipt_review_receipt_txt"
grep -Fq 'draft_review_receipt_write_allowed=0' "$receipt_review_receipt_txt"
grep -Fq 'draft_review_receipt_signed=0' "$receipt_review_receipt_txt"
grep -Fq 'materialization_preconditions_met=0' "$receipt_review_receipt_txt"
grep -Fq 'materialization_allowed=0' "$receipt_review_receipt_txt"
grep -Fq 'payload_write_allowed=0' "$receipt_review_receipt_txt"
grep -Fq 'signature_request_binding_allowed=0' "$receipt_review_receipt_txt"
grep -Fq 'receipt_write_allowed=0' "$receipt_review_receipt_txt"
grep -Fq 'command_surface=lc receipt-review-receipt' "$receipt_review_receipt_txt"
grep -Fq 'promotion_gate=lc_receipt_payload_artifact_review_receipt_before_materialization_preconditions' "$receipt_review_receipt_txt"
grep -Fq 'related_review_receipt_draft_command=lc receipt-review-draft' "$receipt_review_receipt_txt"
grep -Fq 'LATTICRA CONSOLE RECEIPT PAYLOAD ARTIFACT REVIEW RECEIPT DRAFT CONTRACT' "$receipt_review_draft_txt"
grep -Fq 'review_receipt_draft_profile=lc-receipt-payload-artifact-review-receipt-draft-v0' "$receipt_review_draft_txt"
grep -Fq 'draft_review_receipt_write_allowed=0' "$receipt_review_draft_txt"
grep -Fq 'review_receipt_materialization_allowed=0' "$receipt_review_draft_txt"
grep -Fq 'command_surface=lc receipt-review-draft' "$receipt_review_draft_txt"
grep -Fq 'promotion_gate=lc_receipt_payload_artifact_review_receipt_draft_before_review_receipt_creation' "$receipt_review_draft_txt"
grep -Fq 'LATTICRA CONSOLE RECEIPT PAYLOAD MATERIALIZATION PLAN' "$receipt_materialization_plan_txt"
grep -Fq 'materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$receipt_materialization_plan_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0' "$receipt_materialization_plan_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_required=1' "$receipt_materialization_plan_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$receipt_materialization_plan_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt' "$receipt_materialization_plan_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_present=1' "$receipt_materialization_plan_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_command=lc receipt-review-draft' "$receipt_materialization_plan_txt"
grep -Fq 'draft_review_receipt_required=1' "$receipt_materialization_plan_txt"
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
grep -Fq 'receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0' "$signature_request_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_required=1' "$signature_request_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$signature_request_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt' "$signature_request_txt"
grep -Fq 'receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0' "$signature_request_txt"
grep -Fq 'receipt_payload_materialization_plan_present=1' "$signature_request_txt"
grep -Fq 'draft_review_receipt_present=0' "$signature_request_txt"
grep -Fq 'materialization_preconditions_met=0' "$signature_request_txt"
grep -Fq 'materialization_allowed=0' "$signature_request_txt"
grep -Fq 'signing_authorization_profile=latticra-seal-signing-authorization/0.1' "$signature_request_txt"
grep -Fq 'signature_request_binding_artifact_present=0' "$signature_request_txt"
grep -Fq 'seal_signature_request_ready=0' "$signature_request_txt"
grep -Fq 'seal_signing_authority_present=0' "$signature_request_txt"
grep -Fq 'receipt_write_allowed=0' "$signature_request_txt"
grep -Fq 'required_surfaces=receipt-request,receipt-payload-schema,receipt-payload-artifact-draft,receipt-payload-artifact-review,receipt-payload-artifact-review-receipt,receipt-payload-artifact-review-receipt-draft,receipt-payload-materialization-plan,receipt-contract,runtime-boundary,seal-capability-labels' "$signature_request_txt"
grep -Fq 'promotion_gate=lc_signature_request_binding_after_payload_artifact_and_signing_authority' "$signature_request_txt"
grep -Fq 'LATTICRA CONSOLE RECEIPT CONTRACT' "$receipts_txt"
grep -Fq 'receipt_profile=lc-receipts-v0' "$receipts_txt"
grep -Fq 'host_inventory_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'host_adapter_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'session_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'session_contract_command=lc session' "$receipts_txt"
grep -Fq 'workspace_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'workspace_contract_command=lc workspace' "$receipts_txt"
grep -Fq 'namespace_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'namespace_contract_command=lc namespace' "$receipts_txt"
grep -Fq 'rootfs_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'rootfs_contract_command=lc rootfs' "$receipts_txt"
grep -Fq 'packages_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'packages_contract_command=lc packages' "$receipts_txt"
grep -Fq 'init_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'init_contract_command=lc init' "$receipts_txt"
grep -Fq 'services_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'services_contract_command=lc services' "$receipts_txt"
grep -Fq 'service_schema_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'service_schema_contract_command=lc service-schema' "$receipts_txt"
grep -Fq 'service_definitions_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'service_definitions_contract_command=lc service-definitions' "$receipts_txt"
grep -Fq 'service_plan_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'service_plan_contract_command=lc service-plan' "$receipts_txt"
grep -Fq 'service_runtime_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'service_runtime_contract_present=1' "$receipts_txt"
grep -Fq 'service_runtime_contract_command=lc service-runtime' "$receipts_txt"
grep -Fq 'processes_contract_receipt_required=1' "$receipts_txt"
grep -Fq 'processes_contract_present=1' "$receipts_txt"
grep -Fq 'processes_contract_command=lc processes' "$receipts_txt"
grep -Fq 'receipt_surfaces=profile,session,workspace,namespace,rootfs,packages,init,services,service-schema,service-definitions,service-plan,service-runtime,processes,host-contract,host-inventory,host-adapter,runtime-boundary' "$receipts_txt"
grep -Fq 'receipt_request_contract_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_schema_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_artifact_draft_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_artifact_review_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_required=1' "$receipts_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$receipts_txt"
grep -Fq 'receipt_payload_materialization_plan_required=1' "$receipts_txt"
grep -Fq 'signature_request_binding_required=1' "$receipts_txt"
grep -Fq 'signature_request_profile=latticra-seal-signature-request/0.1' "$receipts_txt"
grep -Fq 'seal_signature_present=0' "$receipts_txt"
grep -Fq 'receipt_signed=0' "$receipts_txt"
grep -Fq 'receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt' "$receipts_txt"
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
grep -Fq 'share/latticra/lc/standalone' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/session' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/workspace' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/namespace' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/rootfs' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/packages' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/init' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/services' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/services/definitions.toml' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/services/plan.toml' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/services/runtime.toml' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/processes/contract.toml' installer/manifests/components.toml
grep -Fq 'share/latticra/lc/host-inventory' installer/manifests/components.toml
grep -Fq 'LC install metadata records config/share paths and the standalone command wrapper' installer/manifests/components.toml
grep -Fq 'latticra_console = true' installer/configs/default.installer.toml
grep -Fq 'latticra_console = true' installer/configs/local-prefix-example.installer.toml
grep -Fq 'profile = "lc_standalone"' installer/configs/lc-standalone.installer.toml
grep -Fq 'latticra_console = true' installer/configs/lc-standalone.installer.toml
grep -Fq 'lat_tooling = false' installer/configs/lc-standalone.installer.toml
grep -Fq 'profile = "lc_standalone"' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'dry_run = false' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'allow_host_mutation = true' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'pub latticra_console: bool' installer/latticra-installer/src/config.rs
grep -Fq 'pub struct LatticraConsoleConfig' installer/latticra-installer/src/config.rs
grep -Fq 'pub session_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub workspace_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub namespace_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub rootfs_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub packages_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub init_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub services_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub service_schema_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub service_definitions_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub service_plan_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub service_runtime_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'pub processes_contract_profile: String' installer/latticra-installer/src/config.rs
grep -Fq 'LatticraConsoleProfile::PanelEmbedded' installer/latticra-installer/src/config.rs
grep -Fq 'Self::Standalone => "standalone"' installer/latticra-installer/src/config.rs
grep -Fq 'InstallProfile::LcStandalone' installer/latticra-installer/src/config.rs
grep -Fq 'Latticra Console (LC)' installer/latticra-installer/src/ui.rs
grep -Fq 'WorkspaceTab::Console' installer/latticra-installer/src/ui.rs
grep -Fq 'profile = "panel_embedded"' installer/configs/default.installer.toml
grep -Fq 'standalone_console = true' installer/configs/default.installer.toml
grep -Fq '[lc.install]' installer/configs/default.installer.toml
grep -Fq 'install_profile = "lc-panel-install-v0"' installer/configs/default.installer.toml
grep -Fq 'allow_external_host_commands = false' installer/configs/default.installer.toml
grep -Fq 'command_registry_profile = "c-static-table"' installer/configs/default.installer.toml
grep -Fq 'host_embedding_contract_profile = "lc-host-embedding-v0"' installer/configs/default.installer.toml
grep -Fq 'host_inventory_contract_profile = "lc-host-inventory-v0"' installer/configs/default.installer.toml
grep -Fq 'host_adapter_contract_profile = "lc-host-adapter-v0"' installer/configs/default.installer.toml
grep -Fq 'session_contract_profile = "lc-session-v0"' installer/configs/default.installer.toml
grep -Fq 'require_session_contract = true' installer/configs/default.installer.toml
grep -Fq 'workspace_contract_profile = "lc-workspace-v0"' installer/configs/default.installer.toml
grep -Fq 'require_workspace_contract = true' installer/configs/default.installer.toml
grep -Fq 'namespace_contract_profile = "lc-namespace-v0"' installer/configs/default.installer.toml
grep -Fq 'require_namespace_contract = true' installer/configs/default.installer.toml
grep -Fq 'rootfs_contract_profile = "lc-rootfs-v0"' installer/configs/default.installer.toml
grep -Fq 'require_rootfs_contract = true' installer/configs/default.installer.toml
grep -Fq 'packages_contract_profile = "lc-packages-v0"' installer/configs/default.installer.toml
grep -Fq 'require_packages_contract = true' installer/configs/default.installer.toml
grep -Fq 'init_contract_profile = "lc-init-v0"' installer/configs/default.installer.toml
grep -Fq 'require_init_contract = true' installer/configs/default.installer.toml
grep -Fq 'services_contract_profile = "lc-services-v0"' installer/configs/default.installer.toml
grep -Fq 'require_services_contract = true' installer/configs/default.installer.toml
grep -Fq 'service_schema_contract_profile = "lc-service-schema-v0"' installer/configs/default.installer.toml
grep -Fq 'require_service_schema_contract = true' installer/configs/default.installer.toml
grep -Fq 'service_definitions_contract_profile = "lc-service-definitions-v0"' installer/configs/default.installer.toml
grep -Fq 'require_service_definitions_contract = true' installer/configs/default.installer.toml
grep -Fq 'service_plan_contract_profile = "lc-service-plan-v0"' installer/configs/default.installer.toml
grep -Fq 'require_service_plan_contract = true' installer/configs/default.installer.toml
grep -Fq 'service_runtime_contract_profile = "lc-service-runtime-v0"' installer/configs/default.installer.toml
grep -Fq 'require_service_runtime_contract = true' installer/configs/default.installer.toml
grep -Fq 'processes_contract_profile = "lc-processes-v0"' installer/configs/default.installer.toml
grep -Fq 'require_processes_contract = true' installer/configs/default.installer.toml
grep -Fq 'receipt_request_contract_profile = "lc-receipt-request-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_schema_profile = "lc-receipt-payload-schema-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_artifact_draft_profile = "lc-receipt-payload-artifact-draft-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_artifact_review_profile = "lc-receipt-payload-artifact-review-v0"' installer/configs/default.installer.toml
grep -Fq 'require_receipt_payload_artifact_review = true' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_artifact_review_receipt_profile = "lc-receipt-payload-artifact-review-receipt-v0"' installer/configs/default.installer.toml
grep -Fq 'require_receipt_payload_artifact_review_receipt = true' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_artifact_review_receipt_draft_profile = "lc-receipt-payload-artifact-review-receipt-draft-v0"' installer/configs/default.installer.toml
grep -Fq 'require_receipt_payload_artifact_review_receipt_draft = true' installer/configs/default.installer.toml
grep -Fq 'receipt_payload_materialization_plan_profile = "lc-receipt-payload-materialization-plan-v0"' installer/configs/default.installer.toml
grep -Fq 'require_receipt_payload_materialization_plan = true' installer/configs/default.installer.toml
grep -Fq 'signature_request_binding_profile = "lc-signature-request-binding-v0"' installer/configs/default.installer.toml
grep -Fq 'receipt_contract_profile = "lc-receipts-v0"' installer/configs/default.installer.toml
grep -Fq 'os_base_contract_profile = "lc-os-base-v0"' installer/configs/default.installer.toml
grep -Fq 'vm_evidence_contract_profile = "lc-vm-evidence-v0"' installer/configs/default.installer.toml
grep -Fq 'profile = "standalone"' installer/configs/lc-standalone.installer.toml
grep -Fq 'install_profile = "lc-standalone-install-v0"' installer/configs/lc-standalone.installer.toml
grep -Fq 'install_mode = "metadata-only-standalone-console"' installer/configs/lc-standalone.installer.toml
grep -Fq 'panel_embedded_console = false' installer/configs/lc-standalone.installer.toml
grep -Fq 'build_gui_installer = false' installer/configs/lc-standalone.installer.toml
grep -Fq 'install_desktop_entry = false' installer/configs/lc-standalone.installer.toml
grep -Fq 'install_profile = "lc-standalone-install-v0"' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'install_mode = "metadata-only-standalone-console"' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'panel_embedded_console = false' installer/configs/lc-standalone-local.installer.toml
grep -Fq 'LATTICRA_CONSOLE=$(cfg latticra_console true)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_PROFILE=$(cfg_section lc profile panel_embedded)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_INSTALL_STANDALONE_CONSOLE=$(cfg_section lc.install standalone_console true)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_INSTALL_PROFILE=$(cfg_section lc.install install_profile lc-panel-install-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_INSTALL_ALLOW_EXTERNAL_HOST_COMMANDS=$(cfg_section lc.install allow_external_host_commands false)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_HOST_EMBEDDING_CONTRACT_PROFILE=$(cfg_section lc host_embedding_contract_profile lc-host-embedding-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_HOST_INVENTORY_CONTRACT_PROFILE=$(cfg_section lc host_inventory_contract_profile lc-host-inventory-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_HOST_ADAPTER_CONTRACT_PROFILE=$(cfg_section lc host_adapter_contract_profile lc-host-adapter-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SESSION_CONTRACT_PROFILE=$(cfg_section lc session_contract_profile lc-session-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_WORKSPACE_CONTRACT_PROFILE=$(cfg_section lc workspace_contract_profile lc-workspace-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_NAMESPACE_CONTRACT_PROFILE=$(cfg_section lc namespace_contract_profile lc-namespace-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_ROOTFS_CONTRACT_PROFILE=$(cfg_section lc rootfs_contract_profile lc-rootfs-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_PACKAGES_CONTRACT_PROFILE=$(cfg_section lc packages_contract_profile lc-packages-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_INIT_CONTRACT_PROFILE=$(cfg_section lc init_contract_profile lc-init-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICES_CONTRACT_PROFILE=$(cfg_section lc services_contract_profile lc-services-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICE_SCHEMA_CONTRACT_PROFILE=$(cfg_section lc service_schema_contract_profile lc-service-schema-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICE_DEFINITIONS_CONTRACT_PROFILE=$(cfg_section lc service_definitions_contract_profile lc-service-definitions-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICE_PLAN_CONTRACT_PROFILE=$(cfg_section lc service_plan_contract_profile lc-service-plan-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SERVICE_RUNTIME_CONTRACT_PROFILE=$(cfg_section lc service_runtime_contract_profile lc-service-runtime-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_PROCESSES_CONTRACT_PROFILE=$(cfg_section lc processes_contract_profile lc-processes-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc session category=core effect=none capability=lc.session.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'session/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc workspace category=core effect=none capability=lc.workspace.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc service-runtime category=core effect=none capability=lc.service.runtime.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'services/runtime.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc processes category=core effect=none capability=lc.processes.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'processes/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'workspace/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc namespace category=core effect=none capability=lc.namespace.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'namespace/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc rootfs category=core effect=none capability=lc.rootfs.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'rootfs/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc packages category=core effect=none capability=lc.packages.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'packages/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc init category=core effect=none capability=lc.init.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'init/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc services category=core effect=none capability=lc.services.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'services/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc service-schema category=core effect=none capability=lc.service.schema.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'services/definition-schema.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc service-definitions category=core effect=none capability=lc.service.definitions.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'services/definitions.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'name=lc service-plan category=core effect=none capability=lc.service.plan.contract' installer/scripts/latticra-installer-apply.sh
grep -Fq 'services/plan.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_REQUEST_CONTRACT_PROFILE=$(cfg_section lc receipt_request_contract_profile lc-receipt-request-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_SCHEMA_PROFILE=$(cfg_section lc receipt_payload_schema_profile lc-receipt-payload-schema-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_ARTIFACT_DRAFT_PROFILE=$(cfg_section lc receipt_payload_artifact_draft_profile lc-receipt-payload-artifact-draft-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_PROFILE=$(cfg_section lc receipt_payload_artifact_review_profile lc-receipt-payload-artifact-review-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_RECEIPT_PROFILE=$(cfg_section lc receipt_payload_artifact_review_receipt_profile lc-receipt-payload-artifact-review-receipt-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_ARTIFACT_REVIEW_RECEIPT_DRAFT_PROFILE=$(cfg_section lc receipt_payload_artifact_review_receipt_draft_profile lc-receipt-payload-artifact-review-receipt-draft-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_PAYLOAD_MATERIALIZATION_PLAN_PROFILE=$(cfg_section lc receipt_payload_materialization_plan_profile lc-receipt-payload-materialization-plan-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_SIGNATURE_REQUEST_BINDING_PROFILE=$(cfg_section lc signature_request_binding_profile lc-signature-request-binding-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_RECEIPT_CONTRACT_PROFILE=$(cfg_section lc receipt_contract_profile lc-receipts-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_OS_BASE_CONTRACT_PROFILE=$(cfg_section lc os_base_contract_profile lc-os-base-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'LC_VM_EVIDENCE_CONTRACT_PROFILE=$(cfg_section lc vm_evidence_contract_profile lc-vm-evidence-v0)' installer/scripts/latticra-installer-apply.sh
grep -Fq 'profiles/hosted-reference.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'profiles/standalone-console.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'standalone/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'host-embedding/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'host-inventory/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'host-adapter/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/contract.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-schema.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-artifact-draft.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-artifact-review.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-artifact-review-receipt.toml' installer/scripts/latticra-installer-apply.sh
grep -Fq 'receipt-request/payload-artifact-review-receipt-draft.toml' installer/scripts/latticra-installer-apply.sh
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
grep -Fq 'installer/configs/lc-standalone.installer.toml' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'installer/configs/lc-standalone-local.installer.toml' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'share/latticra/lc/install/config.toml' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'lc.install.command_wrapper' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'panel_embedded -> default Panel-installed LC operator surface' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'host_embedded_planning -> future host-embedding plan with zero host mutation authority' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'os_base_planning -> future OS-base plan with zero boot, kernel, or runtime enforcement authority' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'The default user-local wrapper is:' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Panel installs can rename that direct wrapper with `lc.install.command_wrapper`' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Standalone Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Workspace Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Namespace Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Rootfs Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Packages Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Init Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Host Embedding Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Read-Only Host Inventory Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Host Adapter Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Seal Receipt Request Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Receipt Payload Schema' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Receipt Payload Artifact Review Receipt Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Signature Request Binding Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Receipt Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'OS-Base Planning Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'VM Evidence Contract' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Help And Manpage Rendering' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Runtime Boundary Binding' docs/LATTICRA_CONSOLE_FOUNDATION.md
grep -Fq 'Status: active Stage-0 foundation' "$status_file"
grep -Fq 'latticra_console_report_surface_present=1' "$status_file"
grep -Fq 'standalone_contract_present=1' "$status_file"
grep -Fq 'standalone_contract_command=lc standalone' "$status_file"
grep -Fq 'workspace_contract_present=1' "$status_file"
grep -Fq 'workspace_contract_command=lc workspace' "$status_file"
grep -Fq 'namespace_contract_present=1' "$status_file"
grep -Fq 'namespace_contract_command=lc namespace' "$status_file"
grep -Fq 'rootfs_contract_present=1' "$status_file"
grep -Fq 'rootfs_contract_command=lc rootfs' "$status_file"
grep -Fq 'packages_contract_present=1' "$status_file"
grep -Fq 'packages_contract_command=lc packages' "$status_file"
grep -Fq 'init_contract_present=1' "$status_file"
grep -Fq 'init_contract_command=lc init' "$status_file"
grep -Fq 'services_contract_present=1' "$status_file"
grep -Fq 'services_contract_command=lc services' "$status_file"
grep -Fq 'service_schema_contract_present=1' "$status_file"
grep -Fq 'service_schema_contract_command=lc service-schema' "$status_file"
grep -Fq 'service_definitions_contract_status=metadata-only-contract' "$status_file"
grep -Fq 'service_definitions_contract_present=1' "$status_file"
grep -Fq 'service_definitions_contract_command=lc service-definitions' "$status_file"
grep -Fq 'service_definitions_contract_profile=lc-service-definitions-v0' "$status_file"
grep -Fq 'service_definitions_file=definitions.toml' "$status_file"
grep -Fq 'service_definition_stub_count=0' "$status_file"
grep -Fq 'service_plan_contract_status=metadata-only-contract' "$status_file"
grep -Fq 'service_plan_contract_present=1' "$status_file"
grep -Fq 'service_plan_contract_command=lc service-plan' "$status_file"
grep -Fq 'service_plan_contract_profile=lc-service-plan-v0' "$status_file"
grep -Fq 'service_plan_file=plan.toml' "$status_file"
grep -Fq 'service_plan_created=0' "$status_file"
grep -Fq 'service_runtime_contract_status=metadata-only-contract' "$status_file"
grep -Fq 'service_runtime_contract_present=1' "$status_file"
grep -Fq 'service_runtime_contract_command=lc service-runtime' "$status_file"
grep -Fq 'service_runtime_contract_profile=lc-service-runtime-v0' "$status_file"
grep -Fq 'service_runtime_file=runtime.toml' "$status_file"
grep -Fq 'service_runtime_created=0' "$status_file"
grep -Fq 'processes_contract_status=metadata-only-contract' "$status_file"
grep -Fq 'processes_contract_present=1' "$status_file"
grep -Fq 'processes_contract_command=lc processes' "$status_file"
grep -Fq 'processes_contract_profile=lc-processes-v0' "$status_file"
grep -Fq 'process_table_present=0' "$status_file"
grep -Fq 'process_spawn_allowed=0' "$status_file"
grep -Fq 'host_adapter_contract_present=1' "$status_file"
grep -Fq 'receipt_payload_schema_present=1' "$status_file"
grep -Fq 'receipt_payload_artifact_draft_present=1' "$status_file"
grep -Fq 'receipt_payload_artifact_review_present=1' "$status_file"
grep -Fq 'receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0' "$status_file"
grep -Fq 'receipt_payload_artifact_review_status=metadata-only-review-gate' "$status_file"
grep -Fq 'receipt_payload_artifact_review_command=lc receipt-artifact-review' "$status_file"
grep -Fq 'receipt_payload_artifact_review_receipt_present=1' "$status_file"
grep -Fq 'receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0' "$status_file"
grep -Fq 'receipt_payload_artifact_review_receipt_status=metadata-only-receipt-contract' "$status_file"
grep -Fq 'receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt' "$status_file"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_present=1' "$status_file"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_profile=lc-receipt-payload-artifact-review-receipt-draft-v0' "$status_file"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_status=metadata-only-review-receipt-draft' "$status_file"
grep -Fq 'receipt_payload_artifact_review_receipt_draft_command=lc receipt-review-draft' "$status_file"
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

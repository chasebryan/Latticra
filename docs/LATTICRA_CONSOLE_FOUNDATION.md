# Latticra Console Foundation

Status: Stage-0 foundation
Scope: LC identity, Panel installability, configurable metadata, substrate bridge, host-embedding plan, host-adapter contract, Seal receipt-request contract, receipt payload schema, signature-request binding contract, OS-base planning contract, VM evidence contract, and future OS-base direction.

## Purpose

Latticra Console, shortened to LC, is the planned main operator base for Latticra.

LC should become the primary interaction surface for the Latticra substrate and the surrounding system. It is designed to be configurable and installable through Latticra Panel, embeddable inside a host environment, and eventually capable of growing into an OS-like user environment after explicit evidence gates.

This Stage-0 slice makes LC real without overclaiming authority.

## Phase1 Lessons Retained

The Phase1 reference is useful as a learning source, not as code to copy. Its relevant lessons are:

- a command registry should be the source of truth for help, command discovery, and future capability metadata;
- operator consoles need a guarded host boundary from the first implementation slice;
- OS-track language should stay staged and evidence-bound;
- help, status, and inspection commands should exist before effectful commands.

LC applies those lessons to Latticra's own architecture: Lat, LIR, Nucleus, Runtime Boundary, Latticra Seal, Panel, Nadia, and the System Substrate.

## Installed Identity

```text
console_name=Latticra Console
short_name=LC
component_key=latticra_console
panel_installable=1
configurable=1
profile=panel_embedded
panel_console_bridge=panel-aware
command_registry_profile=c-static-table
substrate_bridge_profile=metadata-bound
host_embedding_profile=panel-contained
host_embedding_contract_profile=lc-host-embedding-v0
host_inventory_contract_profile=lc-host-inventory-v0
host_adapter_contract_profile=lc-host-adapter-v0
receipt_request_contract_profile=lc-receipt-request-v0
receipt_payload_schema_profile=lc-receipt-payload-schema-v0
signature_request_binding_profile=lc-signature-request-binding-v0
receipt_contract_profile=lc-receipts-v0
os_base_contract_profile=lc-os-base-v0
vm_evidence_contract_profile=lc-vm-evidence-v0
os_base_profile=planned-no-boot-authority
report_only=true
host_embedding_contract_required=true
read_only_host_inventory_contract_required=true
profile_receipt_required=true
host_contract_receipt_required=true
host_inventory_receipt_required=true
host_adapter_contract_required=true
receipt_request_contract_required=true
receipt_payload_schema_required=true
signature_request_binding_required=true
os_base_contract_required=true
vm_evidence_contract_required=true
runtime_boundary_binding_required=true
seal_capability_labels_required=true
```

The Panel component creates:

```text
etc/latticra/lc.toml
share/latticra/lc/README.md
share/latticra/lc/commands/seed-registry.txt
share/latticra/lc/profiles/hosted-reference.toml
share/latticra/lc/profiles/panel-embedded.toml
share/latticra/lc/profiles/host-embedded-planning.toml
share/latticra/lc/profiles/os-base-planning.toml
share/latticra/lc/substrate
share/latticra/lc/host-embedding/contract.toml
share/latticra/lc/host-inventory/contract.toml
share/latticra/lc/host-adapter/contract.toml
share/latticra/lc/receipt-request/contract.toml
share/latticra/lc/receipt-request/payload-schema.toml
share/latticra/lc/receipt-request/signature-request-binding.toml
share/latticra/lc/receipts/contract.toml
share/latticra/lc/os-base/contract.toml
share/latticra/lc/vm-evidence/contract.toml
share/latticra/components/latticra-console.installed
```

The user-local wrapper is:

```text
latticra-lc
```

The umbrella wrapper routes:

```text
latticra lc status
```

## Stage-0 Commands

```text
help
status
plan
save
dry-run
reset
uninstall
clear
lc status
lc commands
lc profiles
lc receipts
lc receipt-request
lc receipt-payload
lc signature-request
lc substrate
lc host
lc host-contract
lc host-inventory
lc host-adapter
lc os-contract
lc vm-evidence
lc os
pwd
cd
```

These commands are registry-backed in the C foundation. Each command carries:

```text
name
usage
category
effect
capability_label
no_effect
panel_visible
launches_host_process
requires_future_gate
```

The Stage-0 registry is still metadata-only. It reports identity, seed command metadata, substrate bridge, host-embedding plan, and future OS-base posture. It does not launch host commands.

## Panel Profile Presets

Latticra Panel now carries LC profile presets as a first-class installer configuration block:

```toml
[lc]
profile = "panel_embedded"
command_registry_profile = "c-static-table"
substrate_bridge_profile = "metadata-bound"
host_embedding_profile = "panel-contained"
host_embedding_contract_profile = "lc-host-embedding-v0"
host_inventory_contract_profile = "lc-host-inventory-v0"
host_adapter_contract_profile = "lc-host-adapter-v0"
receipt_request_contract_profile = "lc-receipt-request-v0"
receipt_payload_schema_profile = "lc-receipt-payload-schema-v0"
signature_request_binding_profile = "lc-signature-request-binding-v0"
receipt_contract_profile = "lc-receipts-v0"
os_base_contract_profile = "lc-os-base-v0"
vm_evidence_contract_profile = "lc-vm-evidence-v0"
os_base_profile = "planned-no-boot-authority"
panel_bridge = "panel-aware"
report_only = true
require_host_embedding_contract = true
require_read_only_host_inventory_contract = true
require_profile_receipt = true
require_host_contract_receipt = true
require_host_inventory_receipt = true
require_host_adapter_contract = true
require_receipt_request_contract = true
require_receipt_payload_schema = true
require_signature_request_binding = true
require_os_base_contract = true
require_vm_evidence_contract = true
require_runtime_boundary_binding = true
require_seal_capability_labels = true
```

The current presets are:

```text
hosted_reference -> hosted reference metadata without embedded-host claims
panel_embedded -> default Panel-installed LC operator surface
host_embedded_planning -> future host-embedding plan with zero host mutation authority
os_base_planning -> future OS-base plan with zero boot, kernel, or runtime enforcement authority
custom -> manual metadata fields under the same no-effect authority floor
```

Panel exposes the presets in a Latticra Console workspace tab and in the embedded console:

```text
lc profiles
lc profile hosted
lc profile panel
lc profile host
lc profile os
lc profile custom
```

The install engine writes the selected profile into `etc/latticra/lc.toml` and installs the preset files under `share/latticra/lc/profiles/`. These profiles remain configuration metadata only.

## Host Embedding Contract

LC now installs and reports a host-embedding contract before any host integration behavior exists:

```text
contract_profile=lc-host-embedding-v0
contract_status=metadata-only
host_adapter_required=1
panel_install_required=1
runtime_boundary_required=1
seal_capability_labels_required=1
operator_consent_required=1
read_only_host_inventory_required_before_embedding=1
receipt_required_before_embedding=1
promotion_gate=contract_receipt_and_read_only_host_inventory
```

The source and installed command surfaces are:

```sh
latticra_console_report host-contract
latticra-lc host-contract
```

The contract explicitly denies host authority:

```text
host_embedded_now=0
host_process_launch_allowed=0
host_file_read_allowed=0
host_file_write_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
```

`lc host-contract` is an inspectable contract command. `lc host` remains the future-gated embedding lane.

## Read-Only Host Inventory Contract

LC also installs and reports a read-only host inventory contract before any host adapter exists:

```text
contract_profile=lc-host-inventory-v0
contract_status=metadata-only
required_before_host_embedding=1
host_adapter_present=0
inventory_schema_status=planned
inventory_performed=0
inventory_artifact_present=0
inventory_receipt_required=1
operator_consent_required=1
runtime_boundary_required=1
seal_capability_labels_required=1
promotion_gate=host_inventory_contract_receipt_before_host_adapter
```

The intended future inventory scope is narrow and reviewable:

```text
allowed_future_scope=os_family,kernel_version,cpu_arch,memory_class,filesystem_roots,user_scope,prefix_scope
excluded_future_scope=secrets,private_files,network_scan,process_launch,kernel_change,system_mutation
```

The current command surfaces are:

```sh
latticra_console_report host-inventory
latticra-lc host-inventory
```

This command does not inventory the host. It reports the contract and denial posture:

```text
inventory_performed=0
host_probe_allowed=0
host_process_launch_allowed=0
host_file_read_allowed=0
host_file_write_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
```

## Host Adapter Contract

LC now installs and reports a host-adapter contract before any Host embedding adapter exists:

```text
contract_profile=lc-host-adapter-v0
contract_status=metadata-only
contract_present=1
host_adapter_enabled=0
host_adapter_present=0
host_adapter_loaded=0
adapter_api_status=planned
adapter_abi_status=planned
host_embedding_contract_required=1
read_only_host_inventory_contract_required=1
host_embedding_contract_receipt_required=1
host_inventory_contract_receipt_required=1
operator_consent_required=1
runtime_boundary_required=1
seal_capability_labels_required=1
receipt_required_before_host_adapter=1
promotion_gate=host_adapter_contract_receipts_and_inventory
```

The source and installed command surfaces are:

```sh
latticra_console_report host-adapter
latticra-lc host-adapter
```

The contract explicitly denies adapter and host authority:

```text
host_embedded_now=0
host_process_launch_allowed=0
host_probe_allowed=0
host_file_read_allowed=0
host_file_write_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
```

`lc host-adapter` is an inspectable contract command. `lc host` remains the future-gated embedding lane.

## Receipt Contract

LC now installs and reports a receipt contract for its profile and host-side planning metadata:

```text
receipt_profile=lc-receipts-v0
receipt_contract_status=metadata-only
profile_receipt_required=1
host_embedding_contract_receipt_required=1
host_inventory_contract_receipt_required=1
host_adapter_contract_receipt_required=1
receipt_request_contract_required=1
receipt_request_contract_present=1
receipt_payload_schema_required=1
receipt_payload_schema_present=1
signature_request_binding_required=1
signature_request_binding_contract_present=1
runtime_boundary_receipt_required=1
seal_capability_labels_required=1
signature_request_profile=latticra-seal-signature-request/0.1
receipt_request_command=lc receipt-request
receipt_payload_schema_command=lc receipt-payload
signature_request_binding_command=lc signature-request
receipt_surfaces=profile,host-contract,host-inventory,host-adapter,runtime-boundary
promotion_gate=lc_receipts_before_host_adapter_or_os_base
```

The source and installed command surfaces are:

```sh
latticra_console_report receipts
latticra-lc receipts
```

The contract reserves a future Seal-signed receipt path without claiming signing authority now:

```text
seal_signature_planned=1
seal_signature_present=0
seal_signing_authority_present=0
receipt_written=0
receipt_signed=0
receipt_hash_recorded=0
receipt_path_recorded=0
file_write_allowed=0
```

## Seal Receipt Request Contract

LC now installs and reports a metadata-only request contract for the future Seal-signed LC receipt path:

```text
request_profile=lc-receipt-request-v0
request_contract_status=metadata-only
request_contract_present=1
receipt_contract_profile=lc-receipts-v0
signature_request_profile=latticra-seal-signature-request/0.1
requested_receipt_profile=latticra-seal-verified-receipt/0.1
requested_capability=verified-receipt-report
requested_surfaces=profile,host-contract,host-inventory,host-adapter,runtime-boundary
receipt_payload_schema_profile=lc-receipt-payload-schema-v0
receipt_payload_schema_required=1
receipt_payload_schema_present=1
receipt_payload_schema_command=lc receipt-payload
signature_request_binding_profile=lc-signature-request-binding-v0
signature_request_binding_required=1
signature_request_binding_contract_present=1
signature_request_binding_command=lc signature-request
receipt_payload_profile=lc-receipts-v0
receipt_payload_hash_recorded=0
receipt_payload_path_recorded=0
promotion_gate=lc_receipt_request_review_before_signing
```

The source and installed command surfaces are:

```sh
latticra_console_report receipt-request
latticra-lc receipt-request
```

The request contract is a bridge to Seal metadata only. It explicitly denies signing and file authority:

```text
seal_signature_planned=1
seal_signature_request_ready=0
seal_signature_request_present=0
seal_signing_authority_present=0
seal_signer_handoff_allowed=0
seal_signing_operation_allowed=0
receipt_write_allowed=0
receipt_signed=0
receipt_verification_allowed=0
file_write_allowed=0
host_process_launch_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
```

## Receipt Payload Schema

LC now installs and reports the metadata-only payload schema that a future Seal signature-request artifact would consume:

```text
schema_profile=lc-receipt-payload-schema-v0
schema_status=metadata-only
schema_present=1
receipt_request_profile=lc-receipt-request-v0
receipt_contract_profile=lc-receipts-v0
signature_request_profile=latticra-seal-signature-request/0.1
requested_receipt_profile=latticra-seal-verified-receipt/0.1
requested_capability=verified-receipt-report
payload_fields=console_id,profile,command_registry,host_contract,host_inventory,host_adapter,runtime_boundary,seal_capability_labels,authority_denials
required_authority_fields=no_effect,execution_allowed,host_mutation_allowed,network_allowed,runtime_enforcement_allowed,boot_allowed
payload_artifact_present=0
payload_hash_computed=0
payload_path_recorded=0
signature_request_binding_present=0
signature_request_binding_allowed=0
signature_request_binding_contract_present=1
signature_request_binding_command=lc signature-request
promotion_gate=lc_receipt_payload_schema_before_signature_request_binding
```

The source and installed command surfaces are:

```sh
latticra_console_report receipt-payload
latticra-lc receipt-payload
```

This schema does not create a payload, hash a payload, write a payload path, bind a signature request, or grant signing authority.

## Signature Request Binding Contract

LC now installs and reports a metadata-only binding contract for a future Seal signature-request artifact:

```text
binding_profile=lc-signature-request-binding-v0
binding_status=metadata-only
binding_contract_present=1
receipt_request_profile=lc-receipt-request-v0
receipt_payload_schema_profile=lc-receipt-payload-schema-v0
receipt_contract_profile=lc-receipts-v0
signature_request_profile=latticra-seal-signature-request/0.1
signing_authorization_profile=latticra-seal-signing-authorization/0.1
requested_signature=Ed25519-development
requested_signing_authorization=metadata-only
signature_request_binding_allowed=0
signature_request_binding_artifact_present=0
seal_signature_request_ready=0
seal_signature_request_present=0
seal_signing_authority_present=0
receipt_write_allowed=0
receipt_signed=0
promotion_gate=lc_signature_request_binding_after_payload_artifact_and_signing_authority
```

The source and installed command surfaces are:

```sh
latticra_console_report signature-request
latticra-lc signature-request
```

This contract does not create a signature-request artifact, write a binding path, hash a binding, grant signing authority, invoke a signer, write a receipt, or sign anything.

## OS-Base Planning Contract

LC now installs and reports an OS-base planning contract before any boot-adjacent behavior exists:

```text
contract_profile=lc-os-base-v0
contract_status=metadata-only
contract_present=1
os_base_enabled=0
production_os_claim=0
read_only_host_inventory_receipt_required=1
vm_evidence_contract_required=1
vm_evidence_required=1
operator_consent_required=1
runtime_boundary_required=1
seal_capability_labels_required=1
receipt_required_before_os_base=1
promotion_gate=os_base_contract_receipt_and_vm_evidence
```

The source and installed command surfaces are:

```sh
latticra_console_report os-contract
latticra-lc os-contract
```

The contract explicitly denies OS, kernel, hardware, and host authority:

```text
boot_allowed=0
boot_authority_present=0
kernel_change_allowed=0
kernel_enforcement_allowed=0
hardware_access_allowed=0
bootloader_write_allowed=0
partition_mutation_allowed=0
driver_load_allowed=0
service_install_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
```

`lc os-contract` is an inspectable contract command. `lc os` remains the future-gated boot-action planning lane.

## VM Evidence Contract

LC now installs and reports a VM evidence contract before any boot-adjacent evidence capture exists:

```text
contract_profile=lc-vm-evidence-v0
contract_status=metadata-only
contract_present=1
vm_evidence_required=1
vm_evidence_capture_enabled=0
vm_evidence_artifact_present=0
os_base_contract_required=1
read_only_host_inventory_receipt_required=1
operator_consent_required=1
runtime_boundary_required=1
seal_capability_labels_required=1
receipt_required_before_vm_evidence=1
promotion_gate=vm_evidence_contract_before_boot_adjacency
```

The source and installed command surfaces are:

```sh
latticra_console_report vm-evidence
latticra-lc vm-evidence
```

The contract explicitly denies VM, hypervisor, disk-image, guest, host, and boot authority:

```text
vm_launcher_present=0
vm_launch_allowed=0
hypervisor_access_allowed=0
disk_image_open_allowed=0
disk_image_write_allowed=0
snapshot_capture_allowed=0
guest_agent_allowed=0
guest_network_allowed=0
host_probe_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
production_os_claim=0
```

`lc vm-evidence` is an inspectable evidence-contract command. It does not start a VM or inspect a host.

## Help And Manpage Rendering

LC now has registry-backed renderers for:

```text
LATTICRA CONSOLE HELP
LATTICRA-CONSOLE(1)
```

The source runner can emit them directly:

```sh
tools/latticra_console_report.c -> help
tools/latticra_console_report.c -> man
```

Installed local-prefix wrappers expose the same operator shapes:

```sh
latticra-lc help
latticra-lc man
```

The installed wrapper reads `share/latticra/lc/commands/seed-registry.txt` for help rows, keeping command names, categories, effects, and capability labels attached to the component metadata.

## Runtime Boundary Binding

LC command metadata is now bound to Runtime Boundary classification and Seal capability labels:

```text
runtime_boundary_bound=1
seal_capability_labels_bound=1
```

Stage-0 command bindings use these rules:

```text
core, panel, and substrate inspection -> authority-check / validation-only
lc receipts -> authority-check / validation-only
lc receipt-request -> authority-check / validation-only
lc receipt-payload -> authority-check / validation-only
lc signature-request -> authority-check / validation-only
lc host-contract -> authority-check / validation-only
lc host-inventory -> authority-check / validation-only
lc host-adapter -> authority-check / validation-only
lc os-contract -> authority-check / validation-only
lc vm-evidence -> authority-check / validation-only
lc host -> future-gated command-execute planning
lc os -> future-gated boot-action planning
```

The boundary report keeps all authority outputs denied:

```text
no_effect=1
execution_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
seal_capability_grants_authority=0
```

Source and installed surfaces expose:

```sh
latticra_console_report boundary
latticra-lc boundary
```

## C Foundation

The C foundation is intentionally deterministic:

```text
include/latticra/latticra_console.h
src/latticra_console.c
tools/latticra_console_report.c
tests/latticra_console_foundation.c
scripts/test-latticra-console-foundation.sh
```

The report surface emits:

```text
LATTICRA CONSOLE REPORT
component_key=latticra_console
console_status=ready-report-only
command_registry_status=seed-registry-ready
command_registry_source=c-static-table
command_registry_no_effect=1
command_registry_host_process_launch_allowed=0
runtime_boundary_bound=1
seal_capability_labels_bound=1
substrate_bridge_status=metadata-bound-ready
panel_installable=1
host_adapter_contract_status=metadata-only-contract-ready
host_adapter_contract_present=1
receipt_request_contract_status=metadata-only-contract-ready
receipt_request_contract_present=1
receipt_payload_schema_status=metadata-only-schema-ready
receipt_payload_schema_present=1
signature_request_binding_status=metadata-only-contract-ready
signature_request_binding_present=1
os_base_contract_status=metadata-only-contract-ready
os_base_contract_present=1
vm_evidence_contract_status=metadata-only-contract-ready
vm_evidence_contract_present=1
os_base_enabled=0
production_os_claim=0
future_os_base_claim=planned_not_claimed
execution_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
```

## Authority Baseline

LC Stage-0 does not:

- execute shell commands;
- launch external host processes;
- read arbitrary host files;
- write arbitrary host files;
- mutate the host;
- use the network;
- enforce runtime policy;
- boot hardware;
- claim to be a production OS;
- replace Linux, Fedora, macOS, Windows, or any other host OS.

## Next Slices

1. Add a no-write LC receipt payload artifact draft only after the schema, binding contract, and receipt request are reviewed.
2. Bind the LC receipt payload artifact to a Seal signature-request artifact only after signing authority is implemented and gated.
3. Add the first Seal-signed LC receipt path only after the receipt request is reviewed and receipted.
4. Add a host-adapter artifact schema only after the host-adapter contract is receipted.
5. Add a VM evidence artifact schema only after the VM evidence contract is receipted.

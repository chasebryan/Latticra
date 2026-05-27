# Latticra Console Foundation

Status: Stage-0 foundation
Scope: LC identity, standalone and Panel installability, configurable metadata, session contract, workspace contract, namespace contract, rootfs contract, packages contract, init contract, substrate bridge, host-embedding plan, host-adapter contract, Seal receipt-request contract, receipt payload schema, receipt payload artifact draft, receipt payload artifact review gate, receipt payload artifact review receipt contract, receipt payload artifact review receipt draft contract, receipt payload materialization plan, signature-request binding contract, OS-base planning contract, VM evidence contract, and future OS-base direction.

## Purpose

Latticra Console, shortened to LC, is the planned main operator base for Latticra.

LC should become the primary interaction surface for the Latticra substrate and the surrounding system. It is designed to be configurable, installable through Latticra Panel, available as a standalone user-local console, embeddable inside a host environment, and eventually capable of growing into an OS-like user environment after explicit evidence gates.

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
standalone_installable=1
standalone_requires_panel=0
standalone_command_wrapper=latticra-lc
configurable=1
profile=panel_embedded
panel_console_bridge=panel-aware
command_registry_profile=c-static-table
substrate_bridge_profile=metadata-bound
host_embedding_profile=panel-contained
host_embedding_contract_profile=lc-host-embedding-v0
host_inventory_contract_profile=lc-host-inventory-v0
host_adapter_contract_profile=lc-host-adapter-v0
session_contract_profile=lc-session-v0
workspace_contract_profile=lc-workspace-v0
namespace_contract_profile=lc-namespace-v0
rootfs_contract_profile=lc-rootfs-v0
packages_contract_profile=lc-packages-v0
init_contract_profile=lc-init-v0
receipt_request_contract_profile=lc-receipt-request-v0
receipt_payload_schema_profile=lc-receipt-payload-schema-v0
receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0
receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_draft_profile=lc-receipt-payload-artifact-review-receipt-draft-v0
receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0
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
session_contract_required=true
workspace_contract_required=true
namespace_contract_required=true
rootfs_contract_required=true
packages_contract_required=true
init_contract_required=true
receipt_request_contract_required=true
receipt_payload_schema_required=true
receipt_payload_artifact_draft_required=true
receipt_payload_artifact_review_required=true
receipt_payload_artifact_review_receipt_required=true
receipt_payload_artifact_review_receipt_draft_required=true
receipt_payload_materialization_plan_required=true
signature_request_binding_required=true
os_base_contract_required=true
vm_evidence_contract_required=true
runtime_boundary_binding_required=true
seal_capability_labels_required=true
```

The Panel component creates:

```text
etc/latticra/lc.toml
share/latticra/lc/install/config.toml
share/latticra/lc/README.md
share/latticra/lc/commands/seed-registry.txt
share/latticra/lc/profiles/hosted-reference.toml
share/latticra/lc/profiles/standalone-console.toml
share/latticra/lc/profiles/panel-embedded.toml
share/latticra/lc/profiles/host-embedded-planning.toml
share/latticra/lc/profiles/os-base-planning.toml
share/latticra/lc/standalone/contract.toml
share/latticra/lc/session/contract.toml
share/latticra/lc/workspace/contract.toml
share/latticra/lc/namespace/contract.toml
share/latticra/lc/rootfs/contract.toml
share/latticra/lc/packages/contract.toml
share/latticra/lc/init/contract.toml
share/latticra/lc/substrate
share/latticra/lc/host-embedding/contract.toml
share/latticra/lc/host-inventory/contract.toml
share/latticra/lc/host-adapter/contract.toml
share/latticra/lc/receipt-request/contract.toml
share/latticra/lc/receipt-request/payload-schema.toml
share/latticra/lc/receipt-request/payload-artifact-draft.toml
share/latticra/lc/receipt-request/payload-artifact-review.toml
share/latticra/lc/receipt-request/payload-artifact-review-receipt.toml
share/latticra/lc/receipt-request/payload-artifact-review-receipt-draft.toml
share/latticra/lc/receipt-request/payload-materialization-plan.toml
share/latticra/lc/receipt-request/signature-request-binding.toml
share/latticra/lc/receipts/contract.toml
share/latticra/lc/os-base/contract.toml
share/latticra/lc/vm-evidence/contract.toml
share/latticra/components/latticra-console.installed
```

The default user-local wrapper is:

```text
latticra-lc
```

Panel installs can rename that direct wrapper with `lc.install.command_wrapper`; the wrapper also serves as the standalone LC entrypoint and does not require Panel at runtime. The umbrella route remains `latticra lc ...`.

The standalone installer presets are:

```text
installer/configs/lc-standalone.installer.toml
installer/configs/lc-standalone-local.installer.toml
```

They set `profile = "lc_standalone"`, `lc.profile = "standalone"`, `lc.install.install_profile = "lc-standalone-install-v0"`, `lc.install.install_mode = "metadata-only-standalone-console"`, `lc.install.panel_embedded_console = false`, and leave external host commands disabled. The `lc-standalone-local` preset is the guarded local-write companion for the dry-run standalone preset.

LC can also be installed as a standalone local console:

```text
installer/configs/lc-standalone.installer.toml
installer/configs/lc-standalone-local.installer.toml
installer/scripts/latticra-installer-verify-lc-standalone.sh
```

The standalone lane uses `lc-standalone-install-v0`, writes `share/latticra/lc/standalone/contract.toml`, keeps `standalone_requires_panel = false`, disables Panel embedding, and preserves the same no-effect host/network/runtime/boot authority floor.

The LC session lane writes `share/latticra/lc/session/contract.toml` and exposes `lc session`. It defines the future operator-base session envelope for standalone, Panel-embedded, and Host-embedded LC while keeping runtime session creation, shell launch, host process launch, host mutation, network, runtime enforcement, boot, and production OS authority denied.

The LC workspace lane writes `share/latticra/lc/workspace/contract.toml` and exposes `lc workspace`. It names the future operator-root workspace envelope while keeping workspace mounts, manifest writes, file reads, file writes, host workspace binding, host mutation, network, runtime enforcement, boot, and production OS authority denied.

The LC namespace lane writes `share/latticra/lc/namespace/contract.toml` and exposes `lc namespace`. It names the future internal OS-style namespace envelope while keeping namespace mounts, rootfs projection, path resolution, file reads, file writes, host path projection, host mutation, network, runtime enforcement, boot, and production OS authority denied.

The LC rootfs lane writes `share/latticra/lc/rootfs/contract.toml` and exposes `lc rootfs`. It names the future internal root filesystem envelope while keeping rootfs image creation, image opening, mounts, package installs, file reads, file writes, host mutation, network, runtime enforcement, boot, and production OS authority denied.

The LC packages lane writes `share/latticra/lc/packages/contract.toml` and exposes `lc packages`. It names the future rootfs package-manifest envelope while keeping package catalog reads, downloads, install-plan writes, package-manager execution, package-script execution, rootfs package installs, host mutation, network, runtime enforcement, boot, and production OS authority denied.

The LC init lane writes `share/latticra/lc/init/contract.toml` and exposes `lc init`. It names the future internal init and service envelope while keeping PID 1 claims, init process launch, service starts, service stops, process supervision, startup-order writes, host mutation, network, runtime enforcement, boot, and production OS authority denied.

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
lc standalone
lc session
lc workspace
lc namespace
lc rootfs
lc packages
lc init
lc profiles
lc receipts
lc receipt-request
lc receipt-payload
lc receipt-artifact
lc receipt-artifact-review
lc receipt-review-receipt
lc receipt-review-draft
lc receipt-materialization-plan
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
session_contract_profile = "lc-session-v0"
workspace_contract_profile = "lc-workspace-v0"
namespace_contract_profile = "lc-namespace-v0"
rootfs_contract_profile = "lc-rootfs-v0"
packages_contract_profile = "lc-packages-v0"
init_contract_profile = "lc-init-v0"
receipt_request_contract_profile = "lc-receipt-request-v0"
receipt_payload_schema_profile = "lc-receipt-payload-schema-v0"
receipt_payload_artifact_draft_profile = "lc-receipt-payload-artifact-draft-v0"
receipt_payload_artifact_review_profile = "lc-receipt-payload-artifact-review-v0"
receipt_payload_artifact_review_receipt_profile = "lc-receipt-payload-artifact-review-receipt-v0"
receipt_payload_artifact_review_receipt_draft_profile = "lc-receipt-payload-artifact-review-receipt-draft-v0"
receipt_payload_materialization_plan_profile = "lc-receipt-payload-materialization-plan-v0"
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
require_session_contract = true
require_workspace_contract = true
require_namespace_contract = true
require_rootfs_contract = true
require_packages_contract = true
require_init_contract = true
require_receipt_request_contract = true
require_receipt_payload_schema = true
require_receipt_payload_artifact_draft = true
require_receipt_payload_artifact_review = true
require_receipt_payload_artifact_review_receipt = true
require_receipt_payload_artifact_review_receipt_draft = true
require_receipt_payload_materialization_plan = true
require_signature_request_binding = true
require_os_base_contract = true
require_vm_evidence_contract = true
require_runtime_boundary_binding = true
require_seal_capability_labels = true

[lc.install]
install_profile = "lc-panel-install-v0"
install_mode = "metadata-only-console-foundation"
command_wrapper = "latticra-lc"
standalone_console = true
standalone_installable = true
standalone_requires_panel = false
panel_embedded_console = true
install_user_wrapper = true
allow_external_host_commands = false
```

The current presets are:

```text
hosted_reference -> hosted reference metadata without embedded-host claims
standalone -> standalone LC wrapper profile without requiring Panel at runtime
panel_embedded -> default Panel-installed LC operator surface
host_embedded_planning -> future host-embedding plan with zero host mutation authority
os_base_planning -> future OS-base plan with zero boot, kernel, or runtime enforcement authority
custom -> manual metadata fields under the same no-effect authority floor
```

Panel exposes the presets in a Latticra Console workspace tab and in the embedded console:

```text
lc profiles
lc profile hosted
lc profile standalone
lc profile panel
lc profile host
lc profile os
lc profile custom
```

The install engine writes the selected profile into `etc/latticra/lc.toml`, writes install metadata into `share/latticra/lc/install/config.toml`, and installs the preset files under `share/latticra/lc/profiles/`. The command wrapper comes from `lc.install.command_wrapper` and defaults to `latticra-lc`. That wrapper is the standalone LC entrypoint when `lc.install.standalone_console = true`; it remains metadata-only and does not require Panel at runtime. These profiles and install records remain configuration metadata only, and external host commands stay disabled from both Panel and standalone LC.

## Standalone Contract

LC now installs and reports a standalone console contract before standalone use can gain any effectful host or OS authority:

```text
standalone_console_profile=lc-standalone-console-v0
standalone_console_status=metadata-only-contract
standalone_contract_present=1
standalone_console=1
standalone_installable=1
standalone_requires_panel=0
standalone_command_wrapper=latticra-lc
standalone_profile_file=profiles/standalone-console.toml
panel_embedded_console=1
panel_required_for_runtime=0
config_path=etc/latticra/lc.toml
share_path=share/latticra/lc
command_registry_required=1
runtime_boundary_required=1
seal_capability_labels_required=1
profile_receipt_required=1
promotion_gate=lc_standalone_console_before_effectful_host_or_os_authority
command_surface=lc standalone
related_install_config_command=lc install-config
related_profile_command=lc profiles
no_effect=1
shell_execution_allowed=0
host_process_launch_allowed=0
host_file_read_allowed=0
host_file_write_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
production_os_claim=0
```

The source and installed command surfaces are:

```sh
latticra_console_report standalone
latticra-lc standalone
```

The standalone contract does not launch a shell, launch host processes, read or write host files, mutate the host, use the network, enforce runtime policy, boot hardware, or claim production OS status.

## Session Contract

LC now installs and reports a session contract before the Console can claim any runtime-session or host-adapter behavior:

```text
session_profile=lc-session-v0
session_status=metadata-only-contract
session_contract_present=1
session_kind=operator-base
standalone_compatible=1
panel_embedded_compatible=1
host_embedded_planned=1
session_manifest_present=0
session_manifest_write_allowed=0
runtime_session_created=0
runtime_process_spawn_allowed=0
runtime_invocation_allowed=0
interactive_shell_allowed=0
promotion_gate=lc_session_contract_before_runtime_or_host_embedding
command_surface=lc session
host_process_launch_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
production_os_claim=0
```

The source and installed command surfaces are:

```sh
latticra_console_report session
latticra-lc session
```

The session contract is an operator-base envelope only. It does not create a runtime session, launch an interactive shell, spawn host processes, invoke runtimes, write session manifests, mutate the host, use the network, enforce runtime policy, boot hardware, or claim production OS status.

## Workspace Contract

LC now installs and reports a workspace contract before the Console can claim any mounted workspace, manifest, or OS-base workspace behavior:

```text
workspace_profile=lc-workspace-v0
workspace_status=metadata-only-contract
workspace_contract_present=1
workspace_kind=operator-root
workspace_root=share/latticra/lc/workspace
workspace_mount_present=0
workspace_mount_allowed=0
host_workspace_bind_allowed=0
workspace_manifest_present=0
workspace_manifest_write_allowed=0
workspace_file_read_allowed=0
workspace_file_write_allowed=0
workspace_mutation_allowed=0
runtime_session_required_before_workspace_runtime=1
session_contract_required=1
host_adapter_contract_required=1
os_base_contract_required=1
promotion_gate=lc_workspace_contract_before_host_mount_or_os_workspace
command_surface=lc workspace
host_process_launch_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
production_os_claim=0
```

The source and installed command surfaces are:

```sh
latticra_console_report workspace
latticra-lc workspace
```

The workspace contract is an operator-root envelope only. It does not mount a workspace, bind Host workspace paths, read or write files, write manifests, mutate the host, use the network, enforce runtime policy, boot hardware, or claim production OS status.

## Namespace Contract

LC now installs and reports a namespace contract before the Console can claim any internal OS-style namespace, rootfs, mount, or host path projection behavior:

```text
namespace_profile=lc-namespace-v0
namespace_status=metadata-only-contract
namespace_contract_present=1
namespace_kind=lc-internal-os-namespace
namespace_root=share/latticra/lc/namespace
namespace_manifest_present=0
namespace_manifest_write_allowed=0
namespace_mount_present=0
namespace_mount_allowed=0
rootfs_present=0
rootfs_mount_allowed=0
path_resolver_present=0
path_resolution_allowed=0
host_path_projection_allowed=0
workspace_namespace_bind_allowed=0
namespace_file_read_allowed=0
namespace_file_write_allowed=0
namespace_mutation_allowed=0
workspace_contract_required=1
session_contract_required=1
runtime_boundary_required=1
promotion_gate=lc_namespace_contract_before_rootfs_or_path_projection
command_surface=lc namespace
host_process_launch_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
production_os_claim=0
```

The source and installed command surfaces are:

```sh
latticra_console_report namespace
latticra-lc namespace
```

The namespace contract is an internal OS-layout envelope only. It does not mount namespaces, create a rootfs, resolve host paths, project host paths, bind workspaces into a namespace, read or write files, mutate the host, use the network, enforce runtime policy, boot hardware, or claim production OS status.

## Rootfs Contract

LC now installs and reports a rootfs contract before the Console can claim image creation, mounts, package writes, boot adjacency, or OS-base filesystem behavior:

```text
rootfs_profile=lc-rootfs-v0
rootfs_status=metadata-only-contract
rootfs_contract_present=1
rootfs_kind=lc-internal-root-filesystem
rootfs_root=share/latticra/lc/rootfs
rootfs_state_source=metadata-only
rootfs_manifest_present=0
rootfs_manifest_write_allowed=0
rootfs_image_present=0
rootfs_image_create_allowed=0
rootfs_image_open_allowed=0
rootfs_mount_present=0
rootfs_mount_allowed=0
rootfs_package_manifest_present=0
rootfs_package_install_allowed=0
rootfs_file_read_allowed=0
rootfs_file_write_allowed=0
rootfs_mutation_allowed=0
namespace_contract_required=1
workspace_contract_required=1
session_contract_required=1
runtime_boundary_required=1
receipt_required_before_rootfs_materialization=1
command_surface=lc rootfs
host_process_launch_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
production_os_claim=0
promotion_gate=lc_rootfs_contract_before_image_mount_or_package_write
```

The source and installed command surfaces are:

```sh
latticra_console_report rootfs
latticra-lc rootfs
```

The rootfs contract is metadata only. It does not create or open a rootfs image, mount a filesystem, install packages, read or write rootfs files, mutate the host, use the network, enforce runtime policy, boot hardware, or claim production OS status.

## Packages Contract

LC now installs and reports a packages contract before the Console can claim package catalogs, package downloads, package-manager execution, package-script execution, install plans, package manifests, or rootfs package writes:

```text
packages_profile=lc-packages-v0
packages_status=metadata-only-contract
packages_contract_present=1
packages_kind=lc-rootfs-package-manifest-envelope
packages_root=share/latticra/lc/packages
packages_state_source=metadata-only
package_manifest_present=0
package_manifest_write_allowed=0
package_catalog_present=0
package_catalog_read_allowed=0
package_catalog_write_allowed=0
package_download_allowed=0
package_install_plan_present=0
package_install_plan_write_allowed=0
package_manager_present=0
package_manager_execution_allowed=0
package_script_execution_allowed=0
rootfs_package_manifest_present=0
rootfs_package_install_allowed=0
rootfs_file_write_allowed=0
rootfs_contract_required=1
namespace_contract_required=1
workspace_contract_required=1
session_contract_required=1
os_base_contract_required=1
runtime_boundary_required=1
receipt_required_before_package_materialization=1
command_surface=lc packages
host_process_launch_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
production_os_claim=0
promotion_gate=lc_packages_contract_before_catalog_install_or_rootfs_write
```

The source and installed command surfaces are:

```sh
latticra_console_report packages
latticra-lc packages
```

The packages contract is metadata only. It does not read package catalogs, download packages, write manifests or install plans, run package managers or package scripts, install packages into rootfs, mutate the host, use the network, enforce runtime policy, boot hardware, or claim production OS status.

## Init Contract

LC now installs and reports an init contract before the Console can claim PID 1, an init process, service supervision, startup ordering, boot adjacency, or OS-base init behavior:

```text
init_profile=lc-init-v0
init_status=metadata-only-contract
init_contract_present=1
init_kind=lc-internal-init-and-service-envelope
init_root=share/latticra/lc/init
init_state_source=metadata-only
init_manifest_present=0
init_manifest_write_allowed=0
pid1_claim_allowed=0
init_process_present=0
init_process_launch_allowed=0
service_registry_present=0
service_registry_write_allowed=0
service_start_allowed=0
service_stop_allowed=0
service_restart_allowed=0
process_supervision_allowed=0
startup_order_present=0
startup_order_write_allowed=0
rootfs_contract_required=1
packages_contract_required=1
namespace_contract_required=1
workspace_contract_required=1
session_contract_required=1
os_base_contract_required=1
runtime_boundary_required=1
receipt_required_before_init_runtime=1
command_surface=lc init
host_process_launch_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
production_os_claim=0
promotion_gate=lc_init_contract_before_pid1_service_supervision_or_boot
```

The source and installed command surfaces are:

```sh
latticra_console_report init
latticra-lc init
```

The init contract is metadata only. It does not claim PID 1, launch an init process, start or stop services, supervise processes, write startup order, mutate the host, use the network, enforce runtime policy, boot hardware, or claim production OS status.

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
session_contract_receipt_required=1
session_contract_present=1
workspace_contract_receipt_required=1
workspace_contract_present=1
namespace_contract_receipt_required=1
namespace_contract_present=1
rootfs_contract_receipt_required=1
rootfs_contract_present=1
packages_contract_receipt_required=1
packages_contract_present=1
init_contract_receipt_required=1
init_contract_present=1
receipt_request_contract_required=1
receipt_request_contract_present=1
receipt_payload_schema_required=1
receipt_payload_schema_present=1
receipt_payload_artifact_draft_required=1
receipt_payload_artifact_draft_present=1
receipt_payload_artifact_review_required=1
receipt_payload_artifact_review_present=1
receipt_payload_artifact_review_receipt_required=1
receipt_payload_artifact_review_receipt_present=1
receipt_payload_materialization_plan_required=1
receipt_payload_materialization_plan_present=1
signature_request_binding_required=1
signature_request_binding_contract_present=1
runtime_boundary_receipt_required=1
seal_capability_labels_required=1
signature_request_profile=latticra-seal-signature-request/0.1
receipt_request_command=lc receipt-request
receipt_payload_schema_command=lc receipt-payload
receipt_payload_artifact_draft_command=lc receipt-artifact
receipt_payload_artifact_review_command=lc receipt-artifact-review
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
receipt_payload_materialization_plan_command=lc receipt-materialization-plan
signature_request_binding_command=lc signature-request
session_contract_command=lc session
workspace_contract_command=lc workspace
namespace_contract_command=lc namespace
rootfs_contract_command=lc rootfs
packages_contract_command=lc packages
init_contract_command=lc init
receipt_surfaces=profile,session,workspace,namespace,rootfs,packages,init,host-contract,host-inventory,host-adapter,runtime-boundary
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
requested_surfaces=profile,session,workspace,namespace,rootfs,packages,init,host-contract,host-inventory,host-adapter,runtime-boundary
receipt_payload_schema_profile=lc-receipt-payload-schema-v0
receipt_payload_schema_required=1
receipt_payload_schema_present=1
receipt_payload_schema_command=lc receipt-payload
receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0
receipt_payload_artifact_draft_required=1
receipt_payload_artifact_draft_present=1
receipt_payload_artifact_draft_command=lc receipt-artifact
receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0
receipt_payload_artifact_review_required=1
receipt_payload_artifact_review_present=1
receipt_payload_artifact_review_command=lc receipt-artifact-review
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_required=1
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0
receipt_payload_materialization_plan_required=1
receipt_payload_materialization_plan_present=1
receipt_payload_materialization_plan_command=lc receipt-materialization-plan
draft_review_receipt_present=0
materialization_preconditions_met=0
materialization_allowed=0
payload_artifact_present=0
payload_materialized=0
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
receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0
receipt_payload_artifact_draft_present=1
receipt_payload_artifact_draft_command=lc receipt-artifact
receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0
receipt_payload_artifact_review_present=1
receipt_payload_artifact_review_command=lc receipt-artifact-review
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0
receipt_payload_materialization_plan_present=1
receipt_payload_materialization_plan_command=lc receipt-materialization-plan
materialization_preconditions_met=0
materialization_allowed=0
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

## Receipt Payload Artifact Draft

LC now installs and reports a no-write draft contract for the future receipt payload artifact:

```text
draft_profile=lc-receipt-payload-artifact-draft-v0
draft_status=metadata-only
draft_contract_present=1
receipt_request_profile=lc-receipt-request-v0
receipt_payload_schema_profile=lc-receipt-payload-schema-v0
receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0
receipt_payload_artifact_review_present=1
receipt_payload_artifact_review_command=lc receipt-artifact-review
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0
receipt_payload_materialization_plan_present=1
receipt_payload_materialization_plan_command=lc receipt-materialization-plan
signature_request_binding_profile=lc-signature-request-binding-v0
receipt_contract_profile=lc-receipts-v0
signature_request_profile=latticra-seal-signature-request/0.1
signing_authorization_profile=latticra-seal-signing-authorization/0.1
canonicalization_profile=lc-receipt-payload-canonical-text-v0
artifact_fields=console_id,profile,command_registry,host_contract,host_inventory,host_adapter,runtime_boundary,seal_capability_labels,authority_denials
required_prior_contracts=receipt-request,receipt-payload-schema,signature-request-binding,receipt-contract
receipt_payload_artifact_draft_present=1
draft_review_required=1
draft_review_present=0
draft_review_receipt_required=1
draft_review_receipt_present=0
draft_review_approval_recorded=0
materialization_preconditions_met=0
materialization_allowed=0
payload_artifact_present=0
payload_materialized=0
payload_write_allowed=0
payload_hash_computed=0
payload_hash_recorded=0
payload_path_recorded=0
signature_request_binding_artifact_present=0
signature_request_binding_allowed=0
seal_signature_request_ready=0
receipt_write_allowed=0
receipt_signed=0
promotion_gate=lc_receipt_payload_artifact_draft_before_materialization_and_signature_request
related_materialization_plan_command=lc receipt-materialization-plan
```

The source and installed command surfaces are:

```sh
latticra_console_report receipt-artifact
latticra-lc receipt-artifact
```

This draft does not create or write a payload artifact, compute or record a payload hash, record a payload path, bind a Seal signature request, invoke signing, or write a receipt.

## Receipt Payload Artifact Review Gate

LC now installs and reports a metadata-only review gate between the payload artifact draft and any future payload materialization:

```text
review_profile=lc-receipt-payload-artifact-review-v0
review_status=metadata-only
review_gate_present=1
receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0
receipt_payload_artifact_draft_required=1
receipt_payload_artifact_draft_present=1
receipt_payload_artifact_draft_command=lc receipt-artifact
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_required=1
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0
receipt_payload_materialization_plan_present=1
receipt_payload_materialization_plan_command=lc receipt-materialization-plan
draft_review_required=1
draft_review_present=0
draft_review_receipt_required=1
draft_review_receipt_present=0
draft_review_approval_recorded=0
draft_reviewer_identity_recorded=0
draft_review_timestamp_recorded=0
materialization_plan_required=1
materialization_plan_present=1
materialization_preconditions_met=0
materialization_allowed=0
payload_artifact_present=0
payload_materialized=0
payload_write_allowed=0
payload_hash_computed=0
payload_hash_recorded=0
payload_path_recorded=0
signature_request_binding_allowed=0
signature_request_binding_artifact_present=0
seal_signature_request_ready=0
seal_signature_request_present=0
seal_signing_authority_present=0
receipt_write_allowed=0
receipt_signed=0
promotion_gate=lc_receipt_payload_artifact_review_before_materialization
command_surface=lc receipt-artifact-review
related_materialization_plan_command=lc receipt-materialization-plan
```

The source and installed command surfaces are:

```sh
latticra_console_report receipt-artifact-review
latticra-lc receipt-artifact-review
```

This gate records that the draft still needs review and a review receipt. It does not materialize the payload artifact, write payload bytes, compute or record a payload hash, record a payload path, bind a Seal signature request, invoke signing, or write a receipt.

## Receipt Payload Artifact Review Receipt Contract

LC now installs and reports the metadata-only receipt contract for the payload artifact review gate before materialization can become possible:

```text
review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
review_receipt_status=metadata-only-contract
review_receipt_contract_present=1
review_receipt_draft_profile=lc-receipt-payload-artifact-review-receipt-draft-v0
review_receipt_draft_required=1
review_receipt_draft_contract_present=1
review_receipt_draft_command=lc receipt-review-draft
receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0
receipt_payload_artifact_review_required=1
receipt_payload_artifact_review_present=1
receipt_payload_artifact_review_command=lc receipt-artifact-review
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_required=1
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0
receipt_payload_materialization_plan_required=1
receipt_payload_materialization_plan_present=1
receipt_payload_materialization_plan_command=lc receipt-materialization-plan
draft_review_required=1
draft_review_present=0
draft_review_receipt_required=1
draft_review_receipt_present=0
draft_review_receipt_artifact_present=0
draft_review_receipt_write_allowed=0
draft_review_receipt_signed=0
draft_review_receipt_hash_recorded=0
draft_review_receipt_path_recorded=0
draft_review_approval_recorded=0
draft_reviewer_identity_recorded=0
draft_review_timestamp_recorded=0
materialization_preconditions_met=0
materialization_allowed=0
payload_artifact_present=0
payload_materialized=0
payload_write_allowed=0
signature_request_binding_allowed=0
receipt_write_allowed=0
receipt_signed=0
promotion_gate=lc_receipt_payload_artifact_review_receipt_before_materialization_preconditions
command_surface=lc receipt-review-receipt
related_review_receipt_draft_command=lc receipt-review-draft
```

The source and installed command surfaces are:

```sh
latticra_console_report receipt-review-receipt
latticra-lc receipt-review-receipt
```

This contract does not create a review receipt, record review approval, record reviewer identity, hash or path a review receipt, materialize payload bytes, bind a Seal signature request, invoke signing, or write a receipt.

## Receipt Payload Artifact Review Receipt Draft Contract

LC now installs and reports a metadata-only draft contract for the future review receipt artifact:

```text
review_receipt_draft_profile=lc-receipt-payload-artifact-review-receipt-draft-v0
review_receipt_draft_status=metadata-only-draft-contract
review_receipt_draft_contract_present=1
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_required=1
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
draft_review_receipt_required=1
draft_review_receipt_present=0
draft_review_receipt_artifact_present=0
draft_review_receipt_write_allowed=0
draft_review_receipt_signed=0
draft_review_receipt_hash_recorded=0
draft_review_receipt_path_recorded=0
review_receipt_materialization_allowed=0
review_receipt_signing_allowed=0
materialization_preconditions_met=0
materialization_allowed=0
payload_artifact_present=0
payload_materialized=0
payload_write_allowed=0
signature_request_binding_allowed=0
receipt_write_allowed=0
receipt_signed=0
promotion_gate=lc_receipt_payload_artifact_review_receipt_draft_before_review_receipt_creation
command_surface=lc receipt-review-draft
```

The source and installed command surfaces are:

```sh
latticra_console_report receipt-review-draft
latticra-lc receipt-review-draft
```

This draft contract does not create a review receipt draft, write receipt bytes, compute or record a hash, record a path, sign anything, materialize payload bytes, bind a Seal signature request, or write a receipt.

## Receipt Payload Materialization Plan

LC now installs and reports a metadata-only materialization plan for the future payload artifact:

```text
materialization_plan_profile=lc-receipt-payload-materialization-plan-v0
materialization_plan_status=metadata-only
materialization_plan_present=1
receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0
receipt_payload_artifact_review_required=1
receipt_payload_artifact_review_present=1
receipt_payload_artifact_review_command=lc receipt-artifact-review
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_required=1
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
receipt_payload_artifact_review_receipt_draft_profile=lc-receipt-payload-artifact-review-receipt-draft-v0
receipt_payload_artifact_review_receipt_draft_required=1
receipt_payload_artifact_review_receipt_draft_present=1
receipt_payload_artifact_review_receipt_draft_command=lc receipt-review-draft
draft_review_receipt_required=1
draft_review_receipt_present=0
draft_review_approval_recorded=0
materialization_preconditions_met=0
materialization_allowed=0
materialization_execution_planned=0
payload_artifact_present=0
payload_materialized=0
payload_write_allowed=0
payload_file_open_allowed=0
payload_hash_computed=0
payload_hash_recorded=0
payload_path_recorded=0
signature_request_binding_allowed=0
signature_request_binding_artifact_present=0
seal_signature_request_ready=0
receipt_write_allowed=0
receipt_signed=0
promotion_gate=lc_receipt_payload_materialization_plan_after_review_receipt
command_surface=lc receipt-materialization-plan
```

The source and installed command surfaces are:

```sh
latticra_console_report receipt-materialization-plan
latticra-lc receipt-materialization-plan
```

This plan names the preconditions for a future payload artifact. It does not open a payload file, write payload bytes, materialize the payload, compute or record a hash, record a path, bind a Seal signature request, invoke signing, or write a receipt.

## Signature Request Binding Contract

LC now installs and reports a metadata-only binding contract for a future Seal signature-request artifact:

```text
binding_profile=lc-signature-request-binding-v0
binding_status=metadata-only
binding_contract_present=1
receipt_request_profile=lc-receipt-request-v0
receipt_payload_schema_profile=lc-receipt-payload-schema-v0
receipt_payload_artifact_draft_profile=lc-receipt-payload-artifact-draft-v0
receipt_payload_artifact_draft_required=1
receipt_payload_artifact_draft_present=1
receipt_payload_artifact_draft_command=lc receipt-artifact
receipt_payload_artifact_review_profile=lc-receipt-payload-artifact-review-v0
receipt_payload_artifact_review_required=1
receipt_payload_artifact_review_present=1
receipt_payload_artifact_review_command=lc receipt-artifact-review
receipt_payload_artifact_review_receipt_profile=lc-receipt-payload-artifact-review-receipt-v0
receipt_payload_artifact_review_receipt_required=1
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_command=lc receipt-review-receipt
receipt_payload_materialization_plan_profile=lc-receipt-payload-materialization-plan-v0
receipt_payload_materialization_plan_required=1
receipt_payload_materialization_plan_present=1
receipt_payload_materialization_plan_command=lc receipt-materialization-plan
draft_review_receipt_present=0
materialization_preconditions_met=0
materialization_allowed=0
receipt_contract_profile=lc-receipts-v0
signature_request_profile=latticra-seal-signature-request/0.1
signing_authorization_profile=latticra-seal-signing-authorization/0.1
requested_signature=Ed25519-development
requested_signing_authorization=metadata-only
required_surfaces=receipt-request,receipt-payload-schema,receipt-payload-artifact-draft,receipt-payload-artifact-review,receipt-payload-artifact-review-receipt,receipt-payload-artifact-review-receipt-draft,receipt-payload-materialization-plan,receipt-contract,runtime-boundary,seal-capability-labels
payload_artifact_present=0
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
lc standalone -> authority-check / validation-only
lc session -> authority-check / validation-only
lc workspace -> authority-check / validation-only
lc namespace -> authority-check / validation-only
lc rootfs -> authority-check / validation-only
lc packages -> authority-check / validation-only
lc receipts -> authority-check / validation-only
lc receipt-request -> authority-check / validation-only
lc receipt-payload -> authority-check / validation-only
lc receipt-artifact -> authority-check / validation-only
lc receipt-artifact-review -> authority-check / validation-only
lc receipt-review-receipt -> authority-check / validation-only
lc receipt-review-draft -> authority-check / validation-only
lc receipt-materialization-plan -> authority-check / validation-only
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
standalone_console_status=metadata-only-standalone-contract-ready
standalone_contract_present=1
session_contract_status=metadata-only-contract-ready
session_contract_present=1
standalone_installable=1
standalone_requires_panel=0
substrate_bridge_status=metadata-bound-ready
panel_installable=1
standalone_installable=1
standalone_requires_panel=0
standalone_command_wrapper=latticra-lc
host_adapter_contract_status=metadata-only-contract-ready
host_adapter_contract_present=1
receipt_request_contract_status=metadata-only-contract-ready
receipt_request_contract_present=1
receipt_payload_schema_status=metadata-only-schema-ready
receipt_payload_schema_present=1
receipt_payload_artifact_draft_status=metadata-only-draft-ready
receipt_payload_artifact_draft_present=1
receipt_payload_artifact_review_status=metadata-only-review-gate-ready
receipt_payload_artifact_review_present=1
receipt_payload_artifact_review_receipt_status=metadata-only-receipt-contract-ready
receipt_payload_artifact_review_receipt_present=1
receipt_payload_artifact_review_receipt_draft_status=metadata-only-review-receipt-draft-ready
receipt_payload_artifact_review_receipt_draft_present=1
receipt_payload_materialization_plan_status=metadata-only-plan-ready
receipt_payload_materialization_plan_present=1
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

1. Materialize the LC receipt payload artifact only after the actual review receipt draft and actual review receipt exist.
2. Bind the LC receipt payload artifact to a Seal signature-request artifact only after signing authority is implemented and gated.
3. Add the first Seal-signed LC receipt path only after the receipt request is reviewed and receipted.
4. Add a host-adapter artifact schema only after the host-adapter contract is receipted.
5. Add a VM evidence artifact schema only after the VM evidence contract is receipted.

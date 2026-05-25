# Latticra Console Foundation

Status: Stage-0 foundation
Scope: LC identity, Panel installability, configurable metadata, substrate bridge, host-embedding plan, and future OS-base direction.

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
os_base_profile=planned-no-boot-authority
report_only=true
host_embedding_contract_required=true
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
lc substrate
lc host
lc host-contract
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
os_base_profile = "planned-no-boot-authority"
panel_bridge = "panel-aware"
report_only = true
require_host_embedding_contract = true
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
lc host-contract -> authority-check / validation-only
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

1. Add read-only host inventory contracts before any host adapter exists.
2. Add boot-adjacent planning only after read-only host and VM evidence exists.
3. Add LC profile and host-contract receipts so Panel saves selections as signed evidence when Seal signing authority exists.

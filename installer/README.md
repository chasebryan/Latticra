# Latticra Panel

Graphical installer and first-run control panel for Latticra, Lat, LIR, Latticra Seal, and the Nadia offline AI foundation.

The panel is designed as the main first impression for Latticra. It opens as a maximized, resizable GUI workbench with guided defaults, visible authority boundaries, component configuration, delivery controls, plan/evidence review, and an embedded Latticra Console for panel-aware commands.

## Prerequisites

Fedora:

```sh
sudo dnf install -y rust cargo make gcc pkgconf-pkg-config \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel mesa-libGL-devel wayland-devel desktop-file-utils gtk3
```

User-local command path:

```sh
export PATH="$HOME/.local/bin:$PATH"
```

## Run from source

```sh
make -C installer gui
```

Equivalent direct command:

```sh
cd installer/latticra-installer
LATTICRA_INSTALLER_ROOT="$PWD/.." cargo run
```

## First-run flow

1. Open **Guided Workbench**.
2. Keep dry-run mode enabled.
3. Generate and inspect the plan.
4. Run Dry-Install to validate and write a receipt.
5. Review the embedded console, plan, and engine log.
6. Enable guarded local-prefix writes only after the dry-run evidence looks correct.

## Embedded Latticra Console

The console in the upper-right of the panel is not a shell. It is a panel-aware operator console for common actions and local navigation only:

```text
help
status
plan
save
dry-run
nadia status
nadia context
nadia runtime
nadia plan
nadia mode
nadia ledger
nadia safety
nadia tool
nadia prompt-contract
nadia model-registry
nadia inference-readiness
nadia runtime-invocation
nadia model-load
profile guided
profile seal
profile fedora
mode dry
mode local
pwd
cd <path>
clear
```

External host processes are not launched from the embedded console. Installation and dry-run behavior must use dedicated panel commands or buttons such as `plan`, `save`, `dry-run`, `mode dry`, and `mode local`.

## Dry-run

```sh
make -C installer dry-run
```

## Install locally

```sh
make -C installer local-example
```

## Verify

```sh
make -C installer verify-local
```

## Open after install

```sh
latticra-panel
```

Or from the desktop app grid, open **Latticra Panel**.

## Installed paths

```text
~/.local/bin/latticra
~/.local/bin/lat
~/.local/bin/latticra-seal
~/.local/bin/latticra-nadia (when enabled)
~/.local/bin/latticra-panel
~/.local/share/applications/latticra-panel.desktop
~/.local/share/icons/hicolor/256x256/apps/latticra-panel.png
~/.local/share/latticra
```

## Nadia offline AI foundation

Nadia is Latticra's planned offline AI companion for software development, systems engineering, and AI development work. The name honors Nobel Peace Prize laureate Nadia Murad and keeps human dignity, survivor-witness respect, community awareness, harm-aware development, and an absolute non-sexual-use boundary visible in the system direction. Documentation and code identify the versioned implementation as Nadiav0.0.1 while the human-facing interactive name remains Nadia.

In the current installer lane, Nadia includes Stage-12 model-load contract metadata, Stage-11 runtime-invocation contract metadata, Stage-10 inference-readiness contract metadata, Stage-9 local model-registry contract metadata, Stage-8 prompt-evaluation contract metadata, Stage-7 report-only tool-preflight metadata, Stage-6 protective-safety metadata, Stage-5 productivity-ledger metadata, Stage-4 systems-engineering mode validation, Stage-3 prompt-plan metadata, Stage-2 runtime-profile metadata, Stage-1 local context-pack generation, Stage-0 identity, config, Console status, component marker, and productivity-ledger space. No sexual user functionality, prompt materialization, inference, prompt evaluation, tool execution, model installation, training, distillation, source mutation, or network authority are installed. Model-load metadata does not grant model file opening, weight mapping, weight verification, weight loading, runtime process spawning, runtime binary execution, runtime session creation, token generation, model selection, model weight inspection, benchmarking, or inference authority.

After a guarded local install with Nadia enabled:

```sh
latticra-nadia context-pack
latticra-nadia runtime-profile
latticra-nadia prompt-plan
latticra-nadia mode-validate
latticra-nadia productivity-ledger
latticra-nadia protective-safety
latticra-nadia tool-preflight
latticra-nadia prompt-contract
latticra-nadia model-registry
latticra-nadia inference-readiness
latticra-nadia runtime-invocation
latticra-nadia model-load
```

## Uninstall managed local install

```sh
make -C installer uninstall-local
```

## Safety baseline

```text
no root
no kernel mutation
no systemd mutation
no SELinux mutation
no network authority
user-local prefix only
```

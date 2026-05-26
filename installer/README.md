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
lc status
lc commands
lc substrate
lc host
lc os
plan
save
dry-run
updater status
updater dry-run
updater apply
reset
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
nadia prompt-receipt
nadia prompt-materialization
nadia awareness-dialogue
nadia prompt-evaluation-handoff
nadia tokenization-boundary
nadia tokenizer-specification
nadia tokenizer-manifest
nadia tokenizer-artifact-inventory
nadia tokenizer-artifact-measurement
nadia tokenizer-artifact-verification
nadia tokenizer-artifact-binding
nadia tokenizer-runtime-attachment
nadia prompt-tokenization
nadia prompt-token-sequence
nadia context-window-assembly
nadia prompt-evaluation-input
nadia prompt-evaluation-runtime-handoff
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

## Update from the Panel

Use the **Updater** workspace in Latticra Panel to preview and apply managed user-local updates from the current reviewed source checkout. The updater reuses the guarded installer engine, keeps network fetch authority disabled, and requires a successful updater dry-run before guarded apply by default.

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
~/.local/bin/latticra-lc
~/.local/bin/lat
~/.local/bin/latticra-seal
~/.local/bin/latticra-nadia (when enabled)
~/.local/bin/latticra-panel
~/.local/bin/latticra-installer (compatibility)
~/.local/share/applications/latticra-panel.desktop
~/.local/share/icons/hicolor/256x256/apps/latticra-panel.png
~/.local/share/latticra
```

## Latticra Console (LC)

LC is installed as the configurable operator base for Latticra substrate, Panel, and future host-embedded workflows. In this first slice it is metadata-only:

```sh
latticra lc status
latticra-lc commands
latticra-lc substrate
latticra-lc host
latticra-lc os
```

LC does not launch external host commands, mutate host files, use the network, grant runtime enforcement authority, boot hardware, or claim to be a production operating system.

## Nadia offline AI foundation

Nadia is Latticra's planned offline AI companion for software development, systems engineering, and AI development work. The name honors Nobel Peace Prize laureate Nadia Murad and keeps human dignity, survivor-witness respect, community awareness, harm-aware development, and an absolute non-sexual-use boundary visible in the system direction. Documentation and code identify the solemn implementation identity as Nadia Witness Foundation while the human-facing interactive name remains Nadia.

In the current installer lane, Nadia includes Stage-29 prompt-evaluation runtime handoff contract metadata, Stage-28 prompt-evaluation-input contract metadata, Stage-27 context-window-assembly contract metadata, Stage-26 prompt-token-sequence contract metadata, Stage-25 prompt-tokenization contract metadata, Stage-24 tokenizer-runtime-attachment contract metadata, Stage-23 tokenizer-artifact-binding contract metadata, Stage-22 tokenizer-artifact-verification contract metadata, Stage-21 tokenizer-artifact-measurement contract metadata, Stage-20 tokenizer-artifact-inventory contract metadata, Stage-19 tokenizer-manifest contract metadata, Stage-18 tokenizer-specification contract metadata, Stage-17 tokenization-boundary contract metadata, Stage-16 prompt-evaluation handoff contract metadata, Stage-15 awareness-dialogue contract metadata, Stage-14 prompt-materialization contract metadata, Stage-13 prompt-receipt contract metadata, Stage-12 model-load contract metadata, Stage-11 runtime-invocation contract metadata, Stage-10 inference-readiness contract metadata, Stage-9 local model-registry contract metadata, Stage-8 prompt-evaluation contract metadata, Stage-7 report-only tool-preflight metadata, Stage-6 protective-safety metadata, Stage-5 productivity-ledger metadata, Stage-4 systems-engineering mode validation, Stage-3 prompt-plan metadata, Stage-2 runtime-profile metadata, Stage-1 local context-pack generation, Stage-0 identity, config, Console status, component marker, and productivity-ledger space. No sexual user functionality, dialogue generation, prompt text receipt, prompt text reading, prompt source reading, prompt buffer allocation, prompt tokenization, prompt token creation, prompt token sequence recording, prompt token ID recording, prompt token order recording, prompt token offset recording, context window assembly, prompt evaluation input creation, prompt evaluation runtime handoff, prompt materialization, tokenizer artifact path resolution, tokenizer artifact opening, tokenizer artifact reading, tokenizer artifact scanning, tokenizer artifact hashing, tokenizer artifact measurement, tokenizer artifact digest recording, tokenizer artifact size recording, tokenizer artifact verification, tokenizer artifact digest comparison, tokenizer artifact size comparison, tokenizer artifact binding, tokenizer runtime attachment, runtime session creation, tokenizer manifest loading, tokenizer manifest parsing, tokenizer file access, tokenizer vocabulary loading, inference, prompt evaluation, tool execution, model installation, training, distillation, source mutation, or network authority are installed. Awareness-dialogue metadata defines future survivor-centered Q&A scope for official Nadia Initiative awareness topics, prompt-evaluation handoff metadata packages that evidence, tokenization-boundary metadata keeps prompt tokenization blocked, tokenizer-specification metadata records future review requirements, tokenizer-manifest metadata records future manifest review requirements, tokenizer-artifact-inventory metadata records future artifact measurement requirements, tokenizer-artifact-measurement metadata records future artifact verification requirements, tokenizer-artifact-verification metadata records future artifact binding requirements, tokenizer-artifact-binding metadata records future runtime attachment requirements, tokenizer-runtime-attachment metadata records future prompt tokenization requirements, prompt-tokenization metadata records future prompt token sequence requirements, prompt-token-sequence metadata records future context window assembly requirements, context-window-assembly metadata records future prompt evaluation input requirements, prompt-evaluation-input metadata records future prompt evaluation runtime handoff requirements, and prompt-evaluation runtime handoff metadata records future prompt evaluation invocation requirements; none grants dialogue generation, live web lookup, prompt evaluation, token generation, inference, or tool execution authority.

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
latticra-nadia prompt-receipt
latticra-nadia prompt-materialization
latticra-nadia awareness-dialogue
latticra-nadia prompt-evaluation-handoff
latticra-nadia tokenization-boundary
latticra-nadia tokenizer-specification
latticra-nadia tokenizer-manifest
latticra-nadia tokenizer-artifact-inventory
latticra-nadia tokenizer-artifact-measurement
latticra-nadia tokenizer-artifact-verification
latticra-nadia tokenizer-artifact-binding
latticra-nadia tokenizer-runtime-attachment
latticra-nadia prompt-tokenization
latticra-nadia prompt-token-sequence
latticra-nadia context-window-assembly
latticra-nadia prompt-evaluation-input
latticra-nadia prompt-evaluation-runtime-handoff
```

## Uninstall managed local install

```sh
make -C installer reset-dry-run
make -C installer reset-local
make -C installer uninstall-dry-run
make -C installer uninstall-local
latticra reset --dry-run
latticra reset
latticra uninstall --dry-run
latticra uninstall
```

Reset and uninstall remove the same managed artifacts: command wrappers, the Panel desktop entry, known Panel icons, and the selected local prefix. Use reset when the intent is to reinstall from new Panel specifications; use uninstall when the intent is to remove the local install. Unmanaged files in `~/.local/bin` are preserved.

## Clean full user-local uninstall

Use this only when normal reset/uninstall cannot clean up an old or broken user-local install. The commands below are intentionally scoped to Latticra user-local paths.

```sh
LATTICRA_PREFIX="${LATTICRA_PREFIX:-$HOME/.local/share/latticra}"

rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/latticra-lc" \
  "$HOME/.local/bin/lat" \
  "$HOME/.local/bin/latticra-seal" \
  "$HOME/.local/bin/latticra-nadia" \
  "$HOME/.local/bin/latticra-panel" \
  "$HOME/.local/bin/latticra-installer" \
  "$HOME/.local/share/applications/latticra-panel.desktop" \
  "$HOME/.local/share/applications/latticra-installer.desktop" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-panel.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-installer.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-seal.png"
```

If those exact paths are root-owned because an earlier command was run with `sudo`, repeat the same exact cleanup with `sudo`:

```sh
LATTICRA_PREFIX="${LATTICRA_PREFIX:-$HOME/.local/share/latticra}"

sudo rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

sudo rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/latticra-lc" \
  "$HOME/.local/bin/lat" \
  "$HOME/.local/bin/latticra-seal" \
  "$HOME/.local/bin/latticra-nadia" \
  "$HOME/.local/bin/latticra-panel" \
  "$HOME/.local/bin/latticra-installer" \
  "$HOME/.local/share/applications/latticra-panel.desktop" \
  "$HOME/.local/share/applications/latticra-installer.desktop" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-panel.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-installer.png" \
  "$HOME/.local/share/icons/hicolor/256x256/apps/latticra-seal.png"
```

Do not run `sudo rm -rf` against broad paths such as `~/.local`, `/usr`, `/`, or unreviewed wildcards.

## Safety baseline

```text
no root
no kernel mutation
no systemd mutation
no SELinux mutation
no network authority
user-local prefix only
```

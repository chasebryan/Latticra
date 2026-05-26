# Latticra Panel

Graphical installer and first-run control panel for Latticra, Lat, LIR, Latticra Seal, and the Nadia offline AI foundation.

The panel is designed as the main first impression for Latticra. It opens as a maximized, resizable GUI workbench with guided defaults, visible authority boundaries, component configuration, delivery controls, plan/evidence review, and an embedded Latticra Console for panel-aware commands.

## Prerequisites

Ubuntu:

```sh
sudo apt-get update
sudo apt-get install -y rustc cargo make gcc pkg-config \
  libx11-dev libxcb1-dev libxcursor-dev libxrandr-dev libxi-dev \
  libxkbcommon-dev libgl1-mesa-dev libwayland-dev desktop-file-utils \
  libgtk-3-bin
```

Fedora:

```sh
sudo dnf install -y rust cargo make gcc pkgconf-pkg-config \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel mesa-libGL-devel wayland-devel desktop-file-utils gtk3
```

openSUSE:

```sh
sudo zypper refresh
sudo zypper install -y rust cargo make gcc pkgconf \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel Mesa-libGL-devel wayland-devel desktop-file-utils \
  gtk3-tools
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

## SeaBIOS and GRUB compatibility boundary

The current Panel installer is compatible with SeaBIOS and GRUB hosts by staying out of the boot path. It installs only to a guarded user-local prefix and does not write firmware, partitions, boot sectors, EFI variables, GRUB configuration, kernel images, initramfs files, services, or drivers.

The guarded SeaBIOS and GRUB compatibility contract is [`../docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md`](../docs/SEABIOS_GRUB_COMPATIBILITY_CONTRACT.md).

The SeaBIOS and GRUB boot-preview evidence contract is [`../docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md`](../docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CONTRACT.md). Its fixture manifest is [`manifests/seabios-grub-boot-preview.toml`](manifests/seabios-grub-boot-preview.toml) and preserves a non-booted preview lane for future QEMU, serial-console, checksum, and recovery-path evidence.

The SeaBIOS and GRUB boot-preview preflight is [`../docs/SEABIOS_GRUB_BOOT_PREVIEW_PREFLIGHT.md`](../docs/SEABIOS_GRUB_BOOT_PREVIEW_PREFLIGHT.md). It is available as `sh scripts/seabios-grub-boot-preview-preflight.sh` and emits a no-effect tool-visibility and manifest-validity report.

The SeaBIOS and GRUB boot-preview evidence capture template is [`../docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CAPTURE_TEMPLATE.md`](../docs/SEABIOS_GRUB_BOOT_PREVIEW_EVIDENCE_CAPTURE_TEMPLATE.md). It is available as `sh scripts/seabios-grub-boot-preview-evidence-template.sh` and emits the future evidence bundle shape without running a VM.

The SeaBIOS and GRUB boot-preview QEMU argv template is [`../docs/SEABIOS_GRUB_BOOT_PREVIEW_QEMU_ARGV_TEMPLATE.md`](../docs/SEABIOS_GRUB_BOOT_PREVIEW_QEMU_ARGV_TEMPLATE.md). It is available as `sh scripts/seabios-grub-boot-preview-qemu-argv-template.sh` and emits future profile-specific QEMU argv record placeholders without running QEMU.

```text
installer_ready_for_user_local_panel=1
installer_boot_safe_by_absence=1
boot_preview_manifest_fixture_present=1
seabios_grub_boot_preview_preflight_present=1
seabios_grub_boot_preview_evidence_capture_template_present=1
seabios_grub_boot_preview_qemu_argv_template_present=1
firmware_mutation_allowed=0
bootloader_write_allowed=0
partition_mutation_allowed=0
grub_install_allowed=0
efibootmgr_allowed=0
qemu_execution_allowed_by_guard=0
qemu_boot_execution_attempted=0
qemu_argv_record_ready=0
boot_evidence_record_ready=0
bootable_os_ready=0
production_installer_ready=0
```

Future OS-base work must add QEMU/VM evidence for SeaBIOS, GRUB 2 BIOS, and GRUB 2 UEFI paths before any bootable image claim changes.

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
nadia commands
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
nadia prompt-evaluation-invocation
nadia prompt-evaluation-result
nadia prompt-evaluation-result-review
nadia prompt-evaluation-result-disposition
nadia prompt-evaluation-result-release
nadia prompt-evaluation-result-release-receipt
nadia prompt-evaluation-result-release-receipt-review
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

The installed umbrella command can report the Panel-owned updater policy without launching the GUI:

```sh
latticra updater status
```

## Dry-run

```sh
make -C installer dry-run
```

## Standalone LC dry-run

```sh
make -C installer lc-standalone-dry-run
```

## Standalone LC local install

```sh
make -C installer lc-standalone-local
make -C installer verify-lc-standalone
```

The standalone LC lane installs the direct `latticra-lc` wrapper, standalone profile, seed registry, and standalone contract without installing Panel desktop integration.

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
~/.local/bin/<lc.install.command_wrapper> (default: latticra-lc; when LC wrapper enabled)
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

The default direct wrapper is `latticra-lc`; custom Panel installs use `lc.install.command_wrapper`. The umbrella `latticra lc ...` route stays stable across wrapper names.

```sh
latticra lc status
latticra lc install-config
latticra-lc commands
latticra-lc install-config
latticra-lc substrate
latticra-lc host
latticra-lc os
```

The Panel LC workspace includes LC install configuration for the local config path, share path, wrapper command, profile presets, command registry, contract files, and embedded Panel bridge. External host command launch remains disabled.

LC does not launch external host commands, mutate host files, use the network, grant runtime enforcement authority, boot hardware, or claim to be a production operating system.

## Nadia offline AI foundation

Nadia is Latticra's planned offline AI companion for software development, systems engineering, and AI development work. The name honors Nobel Peace Prize laureate Nadia Murad and keeps human dignity, survivor-witness respect, community awareness, harm-aware development, and an absolute non-sexual-use boundary visible in the system direction. Documentation and code identify the solemn implementation identity as Nadia Witness Foundation while the human-facing interactive name remains Nadia.

In the current installer lane, Nadia includes Stage-37 prompt-evaluation result release receipt review disposition contract metadata, Stage-36 prompt-evaluation result release receipt review contract metadata, Stage-35 prompt-evaluation result release receipt contract metadata, Stage-34 prompt-evaluation result release contract metadata, Stage-33 prompt-evaluation result disposition contract metadata, Stage-32 prompt-evaluation result review contract metadata, Stage-31 prompt-evaluation result contract metadata, Stage-30 prompt-evaluation invocation contract metadata, Stage-29 prompt-evaluation runtime handoff contract metadata, Stage-28 prompt-evaluation-input contract metadata, Stage-27 context-window-assembly contract metadata, Stage-26 prompt-token-sequence contract metadata, Stage-25 prompt-tokenization contract metadata, Stage-24 tokenizer-runtime-attachment contract metadata, Stage-23 tokenizer-artifact-binding contract metadata, Stage-22 tokenizer-artifact-verification contract metadata, Stage-21 tokenizer-artifact-measurement contract metadata, Stage-20 tokenizer-artifact-inventory contract metadata, Stage-19 tokenizer-manifest contract metadata, Stage-18 tokenizer-specification contract metadata, Stage-17 tokenization-boundary contract metadata, Stage-16 prompt-evaluation handoff contract metadata, Stage-15 awareness-dialogue contract metadata, Stage-14 prompt-materialization contract metadata, Stage-13 prompt-receipt contract metadata, Stage-12 model-load contract metadata, Stage-11 runtime-invocation contract metadata, Stage-10 inference-readiness contract metadata, Stage-9 local model-registry contract metadata, Stage-8 prompt-evaluation contract metadata, Stage-7 report-only tool-preflight metadata, Stage-6 protective-safety metadata, Stage-5 productivity-ledger metadata, Stage-4 systems-engineering mode validation, Stage-3 prompt-plan metadata, Stage-2 runtime-profile metadata, Stage-1 local context-pack generation, Stage-0 identity, config, Console status, component marker, and productivity-ledger space. No sexual user functionality, dialogue generation, prompt text receipt, prompt text reading, prompt source reading, prompt buffer allocation, prompt tokenization, prompt token creation, prompt token sequence recording, prompt token ID recording, prompt token order recording, prompt token offset recording, context window assembly, prompt evaluation input creation, prompt evaluation runtime handoff, prompt-evaluation invocation request creation, prompt-evaluation result recording, prompt-evaluation result review recording, prompt-evaluation result disposition recording, disposition decision recording, prompt-evaluation result release recording, release decision recording, release publication, release packaging, release receipt creation, prompt-evaluation result release receipt recording, prompt-evaluation result release receipt review recording, prompt-evaluation result release receipt review disposition recording, review decision recording, review findings recording, receipt signing, receipt publication, model-output recording, prompt materialization, tokenizer artifact path resolution, tokenizer artifact opening, tokenizer artifact reading, tokenizer artifact scanning, tokenizer artifact hashing, tokenizer artifact measurement, tokenizer artifact digest recording, tokenizer artifact size recording, tokenizer artifact verification, tokenizer artifact digest comparison, tokenizer artifact size comparison, tokenizer artifact binding, tokenizer runtime attachment, runtime session creation, tokenizer manifest loading, tokenizer manifest parsing, tokenizer file access, tokenizer vocabulary loading, inference, prompt evaluation, tool execution, model installation, training, distillation, source mutation, or network authority are installed. Awareness-dialogue metadata defines future survivor-centered Q&A scope for official Nadia Initiative awareness topics, prompt-evaluation handoff metadata packages that evidence, tokenization-boundary metadata keeps prompt tokenization blocked, tokenizer-specification metadata records future review requirements, tokenizer-manifest metadata records future manifest review requirements, tokenizer-artifact-inventory metadata records future artifact measurement requirements, tokenizer-artifact-measurement metadata records future artifact verification requirements, tokenizer-artifact-verification metadata records future artifact binding requirements, tokenizer-artifact-binding metadata records future runtime attachment requirements, tokenizer-runtime-attachment metadata records future prompt tokenization requirements, prompt-tokenization metadata records future prompt token sequence requirements, prompt-token-sequence metadata records future context window assembly requirements, context-window-assembly metadata records future prompt evaluation input requirements, prompt-evaluation-input metadata records future prompt evaluation runtime handoff requirements, prompt-evaluation-runtime-handoff metadata records future prompt evaluation invocation requirements, prompt-evaluation-invocation metadata records future prompt evaluation result requirements, prompt-evaluation-result metadata records future prompt evaluation result review requirements, prompt-evaluation-result-review metadata records future prompt evaluation result disposition requirements, prompt-evaluation-result-disposition metadata records future prompt evaluation result release requirements, prompt-evaluation-result-release metadata records future prompt evaluation result release receipt requirements, prompt-evaluation-result-release-receipt metadata records future prompt evaluation result release receipt review requirements, prompt-evaluation-result-release-receipt-review metadata records future prompt evaluation result release receipt review disposition requirements, and prompt-evaluation-result-release-receipt-review-disposition metadata records future prompt evaluation result release receipt review disposition release requirements; none grants dialogue generation, live web lookup, prompt evaluation, token generation, inference, or tool execution authority.

Historical guard compatibility: No sexual user functionality, dialogue generation, prompt text receipt, prompt text reading, prompt source reading, prompt buffer allocation, prompt tokenization, prompt token creation, prompt token sequence recording, prompt token ID recording, prompt token order recording, prompt token offset recording, context window assembly, prompt evaluation input creation, prompt evaluation runtime handoff, prompt-evaluation invocation request creation, prompt-evaluation result recording, prompt-evaluation result review recording, prompt-evaluation result disposition recording, disposition decision recording, prompt-evaluation result release recording, release decision recording, release publication, release packaging, release receipt creation, prompt-evaluation result release receipt recording, prompt-evaluation result release receipt review recording, review decision recording, review findings recording, receipt signing, receipt publication, model-output recording, prompt materialization, tokenizer artifact path resolution, tokenizer artifact opening, tokenizer artifact reading, tokenizer artifact scanning, tokenizer artifact hashing, tokenizer artifact measurement, tokenizer artifact digest recording, tokenizer artifact size recording, tokenizer artifact verification, tokenizer artifact digest comparison, tokenizer artifact size comparison, tokenizer artifact binding, tokenizer runtime attachment, runtime session creation, tokenizer manifest loading, tokenizer manifest parsing, tokenizer file access, tokenizer vocabulary loading, inference, prompt evaluation, tool execution, model installation, training, distillation, source mutation, or network authority are installed.

Stage-37 adds `latticra-nadia prompt-evaluation-result-release-receipt-review-disposition` as prompt-evaluation result release receipt review disposition metadata only. prompt-evaluation result release receipt review disposition recording remains blocked metadata only.

After a guarded local install with Nadia enabled:

```sh
latticra-nadia commands
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
latticra-nadia prompt-evaluation-invocation
latticra-nadia prompt-evaluation-result
latticra-nadia prompt-evaluation-result-review
latticra-nadia prompt-evaluation-result-disposition
latticra-nadia prompt-evaluation-result-release
latticra-nadia prompt-evaluation-result-release-receipt
latticra-nadia prompt-evaluation-result-release-receipt-review
latticra-nadia prompt-evaluation-result-release-receipt-review-disposition
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

If LC was installed with a custom `lc.install.command_wrapper`, set `LC_WRAPPER` to that command name; the default is `latticra-lc`.

```sh
LATTICRA_PREFIX="${LATTICRA_PREFIX:-$HOME/.local/share/latticra}"
LC_WRAPPER="${LC_WRAPPER:-latticra-lc}"

rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/$LC_WRAPPER" \
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
LC_WRAPPER="${LC_WRAPPER:-latticra-lc}"

sudo rm -rf -- \
  "$LATTICRA_PREFIX" \
  "$HOME/.local/share/latticra-validation" \
  "$HOME/.local/share/latticra-reset-receipts"

sudo rm -f -- \
  "$HOME/.local/bin/latticra" \
  "$HOME/.local/bin/$LC_WRAPPER" \
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

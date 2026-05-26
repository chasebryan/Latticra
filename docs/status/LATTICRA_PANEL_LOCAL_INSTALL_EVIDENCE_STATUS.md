# Latticra Panel Local Install Evidence Status

Status: evidence status alignment
Date: 2026-05-22
Scope: Fedora Workstation user-local Latticra Panel install verification after the merged Panel installer, README, CI, and self-copy fix work.

## Summary

A Fedora Workstation user-local Latticra Panel install verification completed successfully.

The operator verified that the installed command wrappers resolve from `~/.local/bin`, that the Latticra local prefix exists, that the installed payload tree exists, that receipts are present, that the desktop entry and desktop icon are present, that the Latticra Panel launcher is available, and that Latticra Seal can generate a report-only local report.

This is Fedora user-local Latticra Panel install evidence.

It is not production installer readiness, root installer readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, kernel integration, systemd integration, SELinux integration, network authority, runtime enforcement authority, or a production security-product claim.

## Evidence source

```text
source=operator Fedora Workstation transcript
host_os=Fedora Linux 44 (Workstation Edition)
kernel=Linux 7.0.9-205.fc44.x86_64 x86_64 GNU/Linux
repo_path=/home/ckbryan/Latticra
install_prefix=/home/ckbryan/.local/share/latticra
user_bin=/home/ckbryan/.local/bin
```

## Command wrapper evidence

```text
which_latticra=/home/ckbryan/.local/bin/latticra
which_lat=/home/ckbryan/.local/bin/lat
which_latticra_seal=/home/ckbryan/.local/bin/latticra-seal
which_latticra_panel=/home/ckbryan/.local/bin/latticra-panel
```

## Installed status output

```text
Latticra is installed.
prefix=/home/ckbryan/.local/share/latticra
payload=/home/ckbryan/.local/share/latticra/lib/latticra
receipts=/home/ckbryan/.local/share/latticra/share/latticra/receipts
```

## Verification report recorded

```text
ok: prefix -> /home/ckbryan/.local/share/latticra
ok: payload tree -> /home/ckbryan/.local/share/latticra/lib/latticra
ok: config -> /home/ckbryan/.local/share/latticra/etc/latticra/installer-config.toml
ok: receipts -> /home/ckbryan/.local/share/latticra/share/latticra/receipts
ok: latticra command -> /home/ckbryan/.local/bin/latticra
ok: lat command -> /home/ckbryan/.local/bin/lat
ok: latticra-seal command -> /home/ckbryan/.local/bin/latticra-seal
ok: latticra-panel command -> /home/ckbryan/.local/bin/latticra-panel
ok: desktop entry -> /home/ckbryan/.local/share/applications/latticra-panel.desktop
ok: desktop icon -> /home/ckbryan/.local/share/icons/hicolor/256x256/apps/latticra-panel.png
ok: latticra-seal report generated
ok: Latticra Panel launcher is available
Latticra local install verification: ok
```

## Current updater policy alignment

The current verifier additionally requires the Panel-owned updater policy and non-launching updater status report:

```text
ok: updater config
ok: updater policy
ok: updater status report
ok: updater status dry-run command
ok: updater status apply command
ok: updater status network fetch authority disabled
ok: updater status apply mode
```

The updater remains a guarded local-checkout Panel lane:

```text
updater_panel_owned=1
updater_policy_present=1
updater_status_report_present=1
updater_preview_command=updater dry-run
updater_apply_command=updater apply
updater_apply_mode=guarded-local-prefix-reinstall
updater_network_fetch_authority=0
updater_root_authority=0
updater_system_mutation_authority=0
```

## Seal report evidence

```text
LATTICRA SEAL REPORT

timestamp_utc=20260522T172638Z
mode=report-only
prefix=/home/ckbryan/.local/share/latticra
kernel=Linux 7.0.9-205.fc44.x86_64 x86_64 GNU/Linux
os=Fedora Linux 44 (Workstation Edition)
network_authority=0
runtime_enforcement_authority=0
```

Installed component markers:

```text
developer-cli-helpers.installed
docs-and-examples.installed
latticra-seal.installed
lat-tooling.installed
lir-contracts.installed
```

## Current readiness classification

```text
latticra_panel_installer_present=1
latticra_panel_user_local_install_verified=1
latticra_panel_command_wrapper_present=1
latticra_panel_desktop_entry_present=1
latticra_panel_desktop_icon_present=1
latticra_panel_launcher_available=1
latticra_local_prefix_present=1
latticra_payload_tree_present=1
latticra_receipts_present=1
latticra_seal_report_generated=1
updater_policy_present=1
updater_status_report_present=1
updater_network_fetch_authority=0
updater_apply_mode=guarded-local-prefix-reinstall
seal_report_only_mode=1
network_authority=0
runtime_enforcement_authority=0
root_authority=0
kernel_modification_performed=0
systemd_modification_performed=0
selinux_modification_performed=0
production_installer_ready=0
root_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Boundary statement

This evidence is limited to a Fedora Workstation user-local Latticra Panel installation path.

The verified install path is under:

```text
/home/ckbryan/.local/share/latticra
/home/ckbryan/.local/bin
/home/ckbryan/.local/share/applications
/home/ckbryan/.local/share/icons
```

This evidence does not validate:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
/usr/lib/modules
/boot/latticra
kernel modification
systemd modification
SELinux modification
network operation
runtime enforcement
production host installation
```

## Guard validation

The evidence status alignment is guarded by:

```sh
sh scripts/test-latticra-panel-local-install-evidence-status.sh
```

Expected output:

```text
latticra_panel_local_install_evidence_status: ok
```

## Next recommended Latticra Panel lane

```text
Add public README/status wording limited to Fedora user-local Latticra Panel installation evidence
```

That wording must remain narrow and should not claim production installer readiness, root installation readiness, Fedora approval, Fedora distribution readiness, immutable Fedora readiness, daily-driver readiness, runtime enforcement, kernel integration, systemd integration, SELinux integration, or production security-product status.

## Non-claims

This status record is not production installer readiness, root installer readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, update safety, rollback safety, malware prevention, ransomware prevention, sandboxing, runtime enforcement, kernel integration, systemd integration, SELinux integration, or a production security-product claim.

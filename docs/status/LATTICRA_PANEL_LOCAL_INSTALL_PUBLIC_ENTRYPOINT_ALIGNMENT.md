# Latticra Panel Local Install Public Entrypoint Alignment

Status: public entrypoint alignment
Date: 2026-05-22
Scope: public README/status alignment after the successful Fedora Workstation user-local Latticra Panel install evidence milestone.

## Summary

The public Latticra entrypoint now has a safe Latticra Panel installer section, and the repository now has a dedicated evidence record for the successful Fedora Workstation user-local Panel verification.

This alignment records the narrow public meaning of that milestone:

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
seal_report_only_mode=1
network_authority=0
runtime_enforcement_authority=0
root_authority=0
production_installer_ready=0
root_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Public entrypoint wording

The root README identifies Latticra Panel as the graphical local installer and control panel for Latticra, Lat, LIR, and Latticra Seal.

It documents the guarded user-local install path:

```sh
make -C installer local-example
make -C installer verify-local
```

It also states the critical boundary:

```text
This installer is user-local only. It does not use root, modify the kernel, modify systemd, change SELinux, or use network authority.
```

That wording remains valid after the local-install evidence milestone.

## Evidence record

The local-install evidence milestone is recorded in:

```text
docs/status/LATTICRA_PANEL_LOCAL_INSTALL_EVIDENCE_STATUS.md
```

The recorded evidence includes:

```text
which_latticra=/home/ckbryan/.local/bin/latticra
which_lat=/home/ckbryan/.local/bin/lat
which_latticra_seal=/home/ckbryan/.local/bin/latticra-seal
which_latticra_panel=/home/ckbryan/.local/bin/latticra-panel
Latticra local install verification: ok
ok: desktop entry -> /home/ckbryan/.local/share/applications/latticra-panel.desktop
ok: desktop icon -> /home/ckbryan/.local/share/icons/hicolor/256x256/apps/latticra-panel.png
ok: latticra-seal report generated
ok: Latticra Panel launcher is available
network_authority=0
runtime_enforcement_authority=0
```

## Safe public claim

A careful public claim is:

```text
Latticra Panel now has Fedora Workstation user-local install evidence covering command wrappers, local prefix layout, payload tree, receipts, desktop metadata, Panel launcher availability, and Latticra Seal report-only output.
```

That is intentionally limited.

## Non-claims

This public entrypoint alignment does not mean Latticra Panel is a production installer, root installer, Fedora-approved package, Fedora distribution-ready package, daily-driver installer, immutable Fedora installer, runtime enforcement system, kernel integration layer, systemd integration layer, SELinux integration layer, malware prevention system, ransomware prevention system, sandbox, or production security product.

It does not validate:

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

This alignment is guarded by:

```sh
sh scripts/test-latticra-panel-local-install-public-entrypoint-alignment.sh
```

Expected output:

```text
latticra_panel_local_install_public_entrypoint_alignment: ok
```

## Next recommended Latticra Panel lane

```text
Add status-index integration for Latticra Panel local-install evidence and public-entrypoint alignment
```

That follow-up should preserve the same non-claims and should not expand the installer beyond the verified user-local evidence boundary.

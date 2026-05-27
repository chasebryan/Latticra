# Latticra Installer Documentation

Status: active installer documentation map
Last updated: 2026-05-26 CDT
Scope: Latticra Panel installer authority, UI configuration, install-button execution, receipts, evidence, and readiness boundaries.

## Purpose

This folder records the installer-specific contracts that sit below the public Panel guide in [`../README.md`](../README.md). These documents are about the guarded user-local installer path, not a production installer or system package manager integration.

## Documents

| Document | Purpose |
| --- | --- |
| [`INSTALLER_READINESS_CONTRACT.md`](INSTALLER_READINESS_CONTRACT.md) | Defines current installer authority, allowed behavior, forbidden behavior, and promotion requirements. |
| [`UI_CONFIGURATION_MODEL.md`](UI_CONFIGURATION_MODEL.md) | Defines the Panel configuration model and how UI choices map to installer planning. |
| [`INSTALL_BUTTON_EXECUTION_MODEL.md`](INSTALL_BUTTON_EXECUTION_MODEL.md) | Defines the execution path behind installer UI actions. |
| [`RECEIPTS_AND_EVIDENCE.md`](RECEIPTS_AND_EVIDENCE.md) | Defines installer receipts, evidence expectations, and review surfaces. |

## Reader Route

1. Start with [`../README.md`](../README.md) for the public Panel workflow.
2. Read [`INSTALLER_READINESS_CONTRACT.md`](INSTALLER_READINESS_CONTRACT.md) before interpreting any installer behavior.
3. Use [`UI_CONFIGURATION_MODEL.md`](UI_CONFIGURATION_MODEL.md) and [`INSTALL_BUTTON_EXECUTION_MODEL.md`](INSTALL_BUTTON_EXECUTION_MODEL.md) when changing or reviewing Panel controls.
4. Use [`RECEIPTS_AND_EVIDENCE.md`](RECEIPTS_AND_EVIDENCE.md) when changing install, dry-run, verify, reset, uninstall, or evidence wording.

## Current Boundary

```text
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0
user_local_prefix_allowed=1
dry_run_first_posture=1
```

The installer documentation must stay aligned with the root public README at [`../../README.md`](../../README.md), the documentation hub at [`../../docs/README.md`](../../docs/README.md), the root status shortcut at [`../../STATUS.md`](../../STATUS.md), and the detailed current status record at [`../../docs/status/CURRENT_STATUS.md`](../../docs/status/CURRENT_STATUS.md).

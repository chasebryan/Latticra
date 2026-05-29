# Latticra Effect Status Surface Status

Status: current local status surface
Last updated: 2026-05-29 CDT
Evidence level: 6 local implementation guard
Scope: `latticra --effect-status` report for the v0.3.0edge working checkpoint.

## Summary

Latticra now has bounded local operator effects in adjacent guarded lanes, including user-local install, local copy, receipt-writing, and operator-bundle staging surfaces.

The CLI effect-status command makes that posture visible without performing effects itself.

```text
LATTICRA EFFECT STATUS REPORT
latticra_effect_status_surface_present=1
edge_checkpoint=v0.3.0edge
effect_surface_version=1
cli_effect_status_command_present=1
cli_effect_performed=0
local_operator_effects_present=1
user_local_install_effect_present=1
user_local_copy_effect_present=1
receipt_write_effect_present=1
operator_bundle_write_effect_present=1
effect_boundary=bounded-user-local-or-requested-output-dir
effect_gate=scripted-guarded-path
effect_authority=bounded-local-visible
host_mutation_allowed=0
root_authority_allowed=0
network_allowed=0
kernel_operation_allowed=0
service_operation_allowed=0
package_manager_operation_allowed=0
boot_operation_allowed=0
usb_write_allowed=0
qemu_run_allowed=0
production_readiness_claim=0
```

## Evidence

```text
src/latticra_cli.c
docs/LATTICRA_NO_EFFECT_CLI_PAYLOAD_CONTRACT.md
docs/LATTICRA_NO_EFFECT_CLI_STATUS_SURFACE_IMPLEMENTATION.md
scripts/test-latticra-no-effect-cli-status-surface.sh
scripts/test-latticra-effect-status-surface.sh
.github/workflows/latticra-effect-status-surface.yml
```

## Non-Claims

This status record does not claim production readiness, root install authority, network authority, package-manager authority, USB write authority, QEMU execution readiness, kernel authority, service authority, distribution approval, or a standard release tag.

The v0.3.0edge marker here is a working edge checkpoint posture. Cutting or pushing a Git tag remains a separate release-management action.

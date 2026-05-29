# macOS Dry-Run Plan Adapter

Status: no-effect macOS dry-run plan adapter
Date: 2026-05-25 CDT
Scope: render user-local macOS installation intent after the build/platform probe without writing artifacts.

## Purpose

This lane adapts the current Latticra user-local installer model to macOS as a dry-run plan only.

It renders the intended Application Support prefix, app bundle layout, CLI wrapper paths, receipt paths, logs/caches paths, and verification command. It does not create those paths, write an app bundle, install wrappers, mutate shell profiles, use launchd, access Keychain, request TCC permissions, use Endpoint Security, use System Extensions, use Network Extensions, open the network, or grant runtime authority.

## Adapter Command

```sh
sh scripts/macos-dry-run-plan-adapter.sh
```

Optional report file:

```sh
sh scripts/macos-dry-run-plan-adapter.sh --output reports/macos-dry-run-plan.txt
```

The default command writes the plan to stdout. The optional `--output` path writes only where the operator explicitly asks.

## Default Planned Layout

```text
application_support_prefix=$HOME/Library/Application Support/Latticra
app_bundle=$HOME/Applications/Latticra Panel.app
cli_bin=$HOME/.local/bin
receipts_dir=$HOME/Library/Application Support/Latticra/receipts
logs_dir=$HOME/Library/Logs/Latticra
caches_dir=$HOME/Library/Caches/Latticra
```

The app bundle plan is:

```text
Latticra Panel.app/
  Contents/
    Info.plist
    MacOS/latticra-panel
    Resources/latticra-panel.icns
```

The planned wrapper paths are:

```text
planned_latticra_wrapper=$HOME/.local/bin/latticra
planned_lat_wrapper=$HOME/.local/bin/lat
planned_latticra_seal_wrapper=$HOME/.local/bin/latticra-seal
planned_latticra_nadia_wrapper=$HOME/.local/bin/latticra-nadia
planned_latticra_panel_wrapper=$HOME/.local/bin/latticra-panel
```

## Path Guard

The dry-run adapter classifies the default layout as:

```text
path_guard_status=allowed-user-local-dry-run
dry_run_allowed=1
```

If a caller supplies paths outside the supported user-local macOS layout, the plan reports:

```text
path_guard_status=blocked-unsafe-user-local-path
dry_run_allowed=0
```

Blocking a path still must not trigger a fallback write, privileged helper, package installer, network lookup, or shell-profile mutation.

## Authority Boundary

The plan must preserve:

```text
application_support_write_performed=0
payload_write_performed=0
config_write_performed=0
receipt_write_performed=0
app_bundle_write_performed=0
info_plist_write_performed=0
app_executable_write_performed=0
app_icon_write_performed=0
cli_wrapper_write_performed=0
shell_profile_mutation_performed=0
installer_write_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
production_installer_ready=0
```

## Validation

This lane is guarded by:

```sh
sh scripts/test-macos-dry-run-plan-adapter.sh
```

Expected output:

```text
macos_dry_run_plan_adapter: ok
```

## Non-Claims

This adapter is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, or Apple platform approval.

## Next Recommended Lane

```text
Add a macOS user-local app bundle implementation plan that remains no-effect and defines writer phases, failure behavior, reset/uninstall sequencing, verification commands, and guard tests before implementation.
```

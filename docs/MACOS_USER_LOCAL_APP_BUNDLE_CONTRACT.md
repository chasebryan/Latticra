# macOS User-Local App Bundle Contract

Status: macOS user-local app bundle contract
Date: 2026-05-25 CDT
Scope: exact app bundle, managed marker, reset/uninstall, and verification transcript requirements before any macOS app bundle writer exists.

## Purpose

This contract defines the minimum shape a future macOS user-local Latticra Panel app bundle writer must satisfy.

It follows the macOS dry-run plan adapter and remains contract-only. It does not create an app bundle, write files, install wrappers, mutate shell profiles, use launchd, access Keychain, request TCC permissions, use Endpoint Security, use System Extensions, use Network Extensions, open the network, or grant runtime authority.

## Required User-Local Roots

The only supported first writer roots are:

```text
application_support_prefix=$HOME/Library/Application Support/Latticra
app_bundle=$HOME/Applications/Latticra Panel.app
cli_bin=$HOME/.local/bin
logs_dir=$HOME/Library/Logs/Latticra
caches_dir=$HOME/Library/Caches/Latticra
reset_receipts_dir=$HOME/Library/Application Support/Latticra Reset Receipts
```

The writer must refuse:

```text
/Applications
/Library
/System
/usr/local
/opt/homebrew
LaunchDaemons
system LaunchAgents
kernel extension paths
system extension paths
network extension paths
privileged helper paths
```

## Exact App Bundle Files

A future writer may create only this managed app bundle shape:

```text
$HOME/Applications/Latticra Panel.app/
  Contents/
    Info.plist
    MacOS/
      latticra-panel
    Resources/
      latticra-panel.icns
      latticra/
        MANAGED_BY_LATTICRA
        bundle-manifest.txt
```

Required bundle file meanings:

| File | Requirement |
| --- | --- |
| `Contents/Info.plist` | Property-list metadata for the local app bundle only. |
| `Contents/MacOS/latticra-panel` | Future copied Panel executable; must be executable. |
| `Contents/Resources/latticra-panel.icns` | Future icon asset; may be generated or converted in a separate lane. |
| `Contents/Resources/latticra/MANAGED_BY_LATTICRA` | Managed marker proving the bundle is removable by Latticra. |
| `Contents/Resources/latticra/bundle-manifest.txt` | Deterministic bundle file list and measurements. |

## Info.plist Requirements

The future `Info.plist` must include:

```text
CFBundleName=Latticra Panel
CFBundleDisplayName=Latticra Panel
CFBundleIdentifier=systems.latticra.panel
CFBundleExecutable=latticra-panel
CFBundlePackageType=APPL
CFBundleShortVersionString=<panel-version>
CFBundleVersion=<build-or-date-version>
LSMinimumSystemVersion=<supported-version>
NSHighResolutionCapable=true
```

The first writer must not request privacy-sensitive usage strings unless a separate TCC contract exists. It must not include LaunchAgent, login item, background item, privileged helper, network extension, system extension, or Endpoint Security activation behavior.

## Application Support Files

A future writer may create only this managed Application Support shape:

```text
$HOME/Library/Application Support/Latticra/
  MANAGED_BY_LATTICRA
  etc/
    latticra/
      installer-config.toml
      macos-plan.txt
  lib/
    latticra/
      payload-manifest.txt
  receipts/
    latest-receipt.txt
    macos-app-bundle-install-receipt-<timestamp>.txt
    manifest-<timestamp>.sha256
```

The Application Support marker must include:

```text
LATTICRA_INSTALLER_MANAGED=1
LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1
root_authority=0
network_authority=0
runtime_enforcement_authority=0
```

## CLI Wrapper Contract

Future wrapper files may be created only under:

```text
$HOME/.local/bin/latticra
$HOME/.local/bin/lat
$HOME/.local/bin/latticra-seal
$HOME/.local/bin/latticra-nadia
$HOME/.local/bin/latticra-panel
```

Each wrapper must include:

```text
# LATTICRA_INSTALLER_MANAGED=1
# LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1
```

The first writer must not mutate `.zshrc`, `.zprofile`, `.bashrc`, `.bash_profile`, fish config, shell profile files, PATH settings, Homebrew prefixes, `/usr/local`, or `/opt/homebrew`.

## Receipt Requirements

The future install receipt must record:

```text
receipt_kind=macos-user-local-app-bundle-install
application_support_prefix=<path>
app_bundle=<path>
cli_bin=<path>
bundle_manifest=<path>
payload_manifest=<path>
root_authority=0
network_authority=0
runtime_enforcement_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
production_installer_ready=0
```

Receipts for reset or uninstall must be written outside any prefix being removed:

```text
reset_receipts_dir=$HOME/Library/Application Support/Latticra Reset Receipts
```

## Reset And Uninstall Contract

Reset/uninstall may remove only managed artifacts:

```text
$HOME/Applications/Latticra Panel.app
$HOME/Library/Application Support/Latticra
$HOME/.local/bin/latticra
$HOME/.local/bin/lat
$HOME/.local/bin/latticra-seal
$HOME/.local/bin/latticra-nadia
$HOME/.local/bin/latticra-panel
```

Removal is allowed only when the target contains a managed marker:

```text
LATTICRA_INSTALLER_MANAGED=1
LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1
```

If a marker is missing, the remover must preserve the target and report:

```text
preserved_unmanaged_target=1
```

Reset/uninstall must not remove user logs, user caches, shell profiles, Keychain items, LaunchAgents, Login Items, application support outside the Latticra prefix, Homebrew files, `/Applications`, `/Library`, `/System`, `/usr/local`, or `/opt/homebrew`.

## Verification Transcript

Before claiming macOS user-local app bundle install evidence, a transcript must record:

```text
ok: app bundle -> $HOME/Applications/Latticra Panel.app
ok: Info.plist -> $HOME/Applications/Latticra Panel.app/Contents/Info.plist
ok: app executable -> $HOME/Applications/Latticra Panel.app/Contents/MacOS/latticra-panel
ok: app resources -> $HOME/Applications/Latticra Panel.app/Contents/Resources
ok: app managed marker -> $HOME/Applications/Latticra Panel.app/Contents/Resources/latticra/MANAGED_BY_LATTICRA
ok: application support prefix -> $HOME/Library/Application Support/Latticra
ok: application support marker -> $HOME/Library/Application Support/Latticra/MANAGED_BY_LATTICRA
ok: receipts -> $HOME/Library/Application Support/Latticra/receipts
ok: latticra-panel wrapper -> $HOME/.local/bin/latticra-panel
ok: reset dry-run preserves unmanaged targets
ok: unsafe path blocked
```

The transcript must also record:

```text
app_bundle_created=1
host_mutation_scope=user-local-managed
root_authority=0
network_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
production_installer_ready=0
```

This transcript requirement does not mean such evidence exists today.

## Current Contract Status

```text
macos_user_local_app_bundle_contract_present=1
macos_app_bundle_writer_present=0
macos_app_bundle_created=0
macos_install_verified=0
macos_reset_uninstall_implemented=0
macos_verification_transcript_present=0
host_mutation_performed=0
network_performed=0
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-macos-user-local-app-bundle-contract.sh
```

Expected output:

```text
macos_user_local_app_bundle_contract: ok
```

## Non-Claims

This contract is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, or Apple platform approval.

## Next Recommended Lane

```text
Add a no-effect macOS app bundle writer dry-run prototype that emits the planned phase report, validates unsafe paths, and keeps commit_user_local_managed_artifacts=0.
```

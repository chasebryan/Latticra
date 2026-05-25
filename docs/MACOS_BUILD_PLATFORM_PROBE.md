# macOS Build Platform Probe

Status: no-effect macOS build/platform probe
Date: 2026-05-25 CDT
Scope: bounded platform and build-readiness probe after the macOS integration transferability map.

## Purpose

This lane records whether the current checkout has enough local toolchain and source evidence to consider later macOS Panel and C test build work.

It is intentionally not an installer lane. It does not create an app bundle, build a package, install wrappers, mutate shell profiles, use launchd, access Keychain, request TCC permissions, use Endpoint Security, use System Extensions, use Network Extensions, open the network, or grant runtime authority.

## Probe Command

```sh
sh scripts/macos-build-platform-probe.sh
```

Optional report file:

```sh
sh scripts/macos-build-platform-probe.sh --output reports/macos-build-platform-probe.txt
```

The default command writes the report to stdout. The optional `--output` path writes only where the operator explicitly asks.

## Report Fields

The report records:

```text
MACOS BUILD PLATFORM PROBE
probe_status=ok
host_kernel_name=Darwin
host_arch=<architecture>
macos_host_detected=<0-or-1>
sw_vers_recorded=<0-or-1>
clang_probe_recorded=<0-or-1>
rust_probe_recorded=1
architecture_recorded=1
panel_build_probe_recorded=1
panel_build_performed=0
panel_build_ready=<0-or-1>
c_test_build_probe_recorded=1
c_test_build_performed=0
c_test_build_ready=<0-or-1>
app_bundle_created=0
installer_write_performed=0
host_mutation_performed=0
network_performed=0
```

The probe records build readiness. It does not run `cargo build`, compile C tests, create an app bundle, or install artifacts.

## Read-Only Inputs

The probe may read:

```text
uname
sw_vers
clang --version
rustc --version
cargo --version
make availability
installer/latticra-installer/Cargo.toml
installer/latticra-installer/Cargo.lock
installer/latticra-installer/src/ui.rs
tests/lat_language_grammar_invariants.c
src/lat_parser.c
include/latticra
```

On non-macOS hosts, the script still emits a deterministic report with:

```text
macos_host_detected=0
```

That allows CI to validate the contract without pretending it has macOS install evidence.

## Authority Boundary

The probe must preserve:

```text
app_bundle_created=0
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
sh scripts/test-macos-build-platform-probe.sh
```

Expected output:

```text
macos_build_platform_probe: ok
```

## Non-Claims

This probe is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, or Apple platform approval.

## Next Recommended Lane

```text
Add a macOS user-local app bundle contract that defines the exact files, managed markers, rollback/reset behavior, and verification transcript required before any app bundle writer exists.
```

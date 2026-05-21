# Latticra No-Effect CLI Status Surface Implementation

Status: implementation record
Evidence level: 6 local implementation guard
Scope: first no-effect `latticra` CLI status surface implementation.

## Summary

This slice implements the first local no-effect Latticra CLI status surface as a small C executable source file.

The implementation is intentionally narrow.

It provides deterministic report-only output for:

```text
latticra --status
latticra --version
latticra --report
```

It does not update the Fedora RPM spec.

It does not install `/usr/bin/latticra`.

It does not add the CLI to the RPM payload.

It does not run disposable Fedora VM validation.

It does not claim host install readiness for the CLI payload.

## Files

```text
src/latticra_cli.c
scripts/test-latticra-no-effect-cli-status-surface.sh
.github/workflows/latticra-no-effect-cli-status-surface.yml
```

## CLI surface

The CLI accepts only the three report-only commands defined by the contract:

```text
latticra --status
latticra --version
latticra --report
```

Invalid commands emit usage text to stderr and return exit code 2.

## Deterministic status output

The `--status` and `--report` commands emit the same fixed report:

```text
LATTICRA STATUS REPORT
project=latticra
mode=no-effect
runtime_behavior=disabled
host_mutation=0
network=0
kernel_operation=0
service_operation=0
package_manager_operation=0
boot_operation=0
selinux_policy_operation=0
effect_authority=denied
```

The `--version` command emits:

```text
latticra 0.0.0
mode=no-effect
runtime_behavior=disabled
```

## No-effect implementation constraints

The implementation uses only standard C string comparison and output calls.

The guard rejects forbidden implementation patterns including:

```text
system(
popen(
fork(
exec
socket(
connect(
open(
fopen(
freopen(
remove(
rename(
unlink(
mkdir(
rmdir(
chmod(
chown(
mount(
setuid(
setgid(
```

## Current readiness classification

```text
cli_payload_contract_present=1
cli_status_surface_implemented=1
cli_local_guard_present=1
cli_local_guard_pass_expected=1
cli_rpm_payload_validated=0
disposable_vm_cli_validation_completed=0
host_install_ready_for_cli_payload=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Validation

```sh
sh scripts/test-latticra-no-effect-cli-status-surface.sh
```

Expected output:

```text
latticra_no_effect_cli_status_surface: ok
```

## Next recommended lane

```text
Add no-effect CLI payload packaging contract alignment
```

That future lane should still avoid claiming Fedora package validation for `/usr/bin/latticra` until a real disposable Fedora VM RPM validation transcript exists for the expanded payload.

## Non-claims

This implementation record is not RPM payload expansion.

It is not installation evidence for `/usr/bin/latticra`.

It is not disposable Fedora VM validation of the CLI payload.

It is not production readiness, Fedora approval, Fedora distribution readiness, daily-driver safety, immutable Fedora readiness, runtime behavior, Lat execution, LIR execution, service management, kernel integration, update safety, recovery safety, malware prevention, ransomware prevention, sandboxing, or a production installer claim.

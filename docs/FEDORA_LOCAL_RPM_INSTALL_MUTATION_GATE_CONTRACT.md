# Fedora Local RPM Install Mutation Gate Contract

Status: contract record
Scope: define the hard gate before any Fedora local RPM install mutation can be represented or implemented.
Evidence level: 4 target, contract only

## Purpose

Latticra now has a Fedora host install preflight classifier, a no-effect snapshot capture path, and a live read-only adapter.

This contract defines the next boundary: when a future Fedora local RPM install mutation may be considered.

This is intentionally not an installer implementation.

The purpose is to prevent accidental host mutation by requiring every install precondition to be explicit, reported, and testable before any code is allowed to execute a package install action.

## Required gate inputs

A future install mutation gate must consume an explicit record containing at least:

```text
fedora_host
mutable_fedora_host
immutable_host
local_rpm_present
local_rpm_path
root_or_sudo_available
network_required
operator_install_confirmation
dry_run_passed
rollback_or_remove_plan_present
preflight_classification
preflight_denial
snapshot_capture_status
live_probe_performed
```

The gate must fail closed when any required field is missing, false, unknown, or contradictory.

## Required allow conditions

A future local RPM install mutation may only be represented as allowed when all conditions are true:

```text
fedora_host=1
mutable_fedora_host=1
immutable_host=0
local_rpm_present=1
root_or_sudo_available=1
network_required=0
operator_install_confirmation=1
dry_run_passed=1
rollback_or_remove_plan_present=1
preflight_classification=ready-local-rpm
preflight_denial=none
live_probe_performed=1
```

Every other combination must deny the install mutation.

## Required denial reasons

The gate must report deterministic denial reasons such as:

```text
not-fedora-host
immutable-fedora-host
local-rpm-missing
privilege-missing
network-required
operator-confirmation-missing
dry-run-missing
rollback-plan-missing
preflight-not-ready
preflight-denied
live-probe-missing
invalid-gate-input
```

## Mutation status fields

The first gate implementation must remain a classifier. It must not execute install commands.

It should report fields such as:

```text
FEDORA LOCAL RPM INSTALL MUTATION GATE
install_gate_status=allowed
install_mutation_allowed=1
install_mutation_performed=0
host_mutation_performed=0
network_allowed=0
operator_install_confirmation=1
dry_run_passed=1
rollback_or_remove_plan_present=1
evidence_level=4
```

For denied cases, it should report:

```text
install_gate_status=denied
install_mutation_allowed=0
install_mutation_performed=0
host_mutation_performed=0
```

## Command boundary

This contract does not authorize any command execution.

The first implementation after this contract should be a pure gate classifier. It must not run package installation commands, privilege commands, package build commands, network commands, service commands, boot commands, or kernel module commands.

## Future install execution boundary

A later execution lane may be considered only after the mutation gate classifier exists and passes focused tests.

That later lane must use a separate contract and should require:

```text
explicit operator invocation
local RPM path
preflight report
live read-only adapter report
mutation gate report
rollback/removal plan
post-install verification plan
clear command transcript boundary
```

## Removal and rollback requirement

No install execution lane should be added until Latticra has a documented removal or rollback path.

At minimum, the future removal plan should define:

```text
how the installed package is identified
how package ownership is verified
how uninstall is requested
how post-removal absence is verified
how failure is reported without hiding partial state
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-local-rpm-install-mutation-gate-contract.sh
```

Expected output:

```text
fedora_local_rpm_install_mutation_gate_contract: ok
```

## Non-claims

This contract does not implement installation.

It does not install Latticra, mutate the host, validate sudo, run package tools, build packages, open the network, start services, change boot entries, load kernel modules, claim Fedora approval, or claim production installer readiness.

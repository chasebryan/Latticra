# Fedora Host Install Preflight Plan

Status: planning record
Scope: define a non-installing preflight classifier for deciding whether a Fedora host is eligible for direct host-level Latticra RPM install testing.

## Purpose

This plan turns the Fedora host install decision gate into a future preflight check.

The goal is conservative: classify the current host without building, installing, removing, or modifying packages.

The preflight should answer one question:

```text
Is this host eligible for direct host-level install testing, or should testing remain container-only?
```

## Current default

The safe default remains:

```text
Use Fedora containers or disposable Fedora CI for install-smoke testing.
```

Host install testing is exceptional and must be explicitly allowed by evidence and operator intent.

## Current package truth

The current local RPM is documentation-only.

Expected installed payload:

```text
/usr/share/doc/latticra/README.md
```

Expected absent installed surfaces:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
kernel modules
bootloader files
SELinux policy files
runtime configuration
```

## Future preflight checks

A future preflight script should collect and classify:

```text
Fedora marker present
bootc command availability
bootc status/read-only classification
rpm database accessibility
rpm package already installed state
git working tree cleanliness
required lane scripts present
container evidence requirements documented
operator consent requirement documented
host eligibility classification
```

## Non-installing command shape

The preflight may run non-installing commands like:

```sh
test -r /etc/fedora-release
command -v bootc >/dev/null 2>&1 || true
bootc status >/dev/null 2>&1 || true
rpm -q latticra || true
git status --short
ls scripts/test-fedora-local-install-smoke-lane.sh
ls scripts/test-fedora-installed-state-report-lane.sh
```

The preflight must not run:

```sh
dnf install
rpm -Uvh
rpm -e
rpmbuild
mock
```

## Classification labels

The preflight should emit one of these labels:

```text
host_install_eligible
container_only_bootc_or_read_only
container_only_dirty_worktree
container_only_missing_evidence
container_only_existing_latticra_package
container_only_unconfirmed_operator_consent
```

## Hard stop classifications

The preflight must classify as container-only if:

```text
bootc/read-only host is detected
worktree has local modifications
required scripts are missing
latticra is already installed
container evidence has not been recorded
operator consent has not been recorded
```

## Required evidence before eligibility

The host can be classified as host-install eligible only if:

```text
host is Fedora
host is mutable, not bootc/read-only
worktree is clean
latticra is not already installed
source archive fixture lane passed
local binary RPM build lane passed
RPM payload inspection report lane passed
local install smoke lane passed in disposable Fedora
installed-state report lane passed in disposable Fedora
operator explicitly accepts temporary RPM database modification
```

## Expected future output

A future preflight script may print a deterministic summary like:

```text
fedora_host_install_preflight: classification=container_only_bootc_or_read_only
fedora_host_install_preflight: ok
```

or:

```text
fedora_host_install_preflight: classification=host_install_eligible
fedora_host_install_preflight: ok
```

## bootc/read-only guidance

If a bootc/read-only system is detected, the preflight must recommend container testing.

It must not recommend forcing host package installation.

## Boundary

This plan does not run `rpmbuild`.

It does not run `mock`.

It does not create RPM artifacts.

It does not install Latticra.

It does not remove Latticra.

It does not modify the host RPM database.

It does not publish package artifacts.

It does not upload release artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora host install preflight classifier
```

That future slice should implement the non-installing host classification script.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-host-install-preflight-plan.sh
```

Expected output:

```text
fedora_host_install_preflight_plan: ok
```
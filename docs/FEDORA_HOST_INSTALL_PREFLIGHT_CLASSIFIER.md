# Fedora Host Install Preflight Classifier

Status: implementation record
Scope: no-effect Fedora host install preflight classification before any host install lane performs mutation.
Evidence level: 1

## Purpose

The Fedora host install preflight classifier determines whether a captured Fedora host snapshot is eligible to be considered for a separate local RPM install lane.

The classifier is intentionally conservative. It converts host facts into a deterministic report, but it does not inspect the live host itself and does not install Latticra.

This slice exists because the Fedora install verification path is moving toward installed-state proof, while the current package posture remains local-only and guarded by non-claims.

## Effect boundary

This classifier is no-effect.

It does not:

```text
install the RPM
run dnf
run rpm
run rpmbuild
run rpmlint
read /etc/os-release
write files
open the network
mutate the host
start services
create boot entries
load kernel modules
change SELinux policy
claim runtime readiness
```

The classifier only consumes an already-captured snapshot and returns labels.

## Snapshot fields

The caller provides facts such as:

```text
os_id
os_id_like
host_install_requested
immutable_host
rpm_available
dnf_available
rpmbuild_available
rpmlint_available
local_rpm_present
root_or_sudo_available
network_required
package_is_doc_only
command_entrypoint_expected
```

`rpm_available`, `dnf_available`, `local_rpm_present`, and `root_or_sudo_available` are required before a mutable Fedora host can become a host-install candidate.

`rpmbuild_available` and `rpmlint_available` are reported, but they are not required for the host-install candidate classification because build and lint validation belong to earlier Fedora lanes.

## Classifications

The public classifier labels are:

```text
LATTICRA_FEDORA_PREFLIGHT_REPORT_ONLY
LATTICRA_FEDORA_PREFLIGHT_READY_LOCAL_RPM
LATTICRA_FEDORA_PREFLIGHT_BLOCKED
LATTICRA_FEDORA_PREFLIGHT_FUTURE_GATED
LATTICRA_FEDORA_PREFLIGHT_INVALID
```

`ready-local-rpm` means the snapshot is eligible to be considered by a later local RPM install lane. It does not mean this classifier performed installation.

`future-gated` is used for immutable Fedora-style hosts where rpm-ostree or image-based handling must be designed separately.

`blocked` is used for non-Fedora hosts, network-requiring paths, missing required tooling, missing local RPMs, missing operator privilege, or premature runtime command expectations.

## Denial classes

The public denial labels are:

```text
host-install-not-requested
non-fedora-host
immutable-host
network-required
required-tooling-missing
local-rpm-missing
privilege-missing
runtime-entrypoint-not-present
invalid-snapshot
```

These labels are intended to make failed preflight reports auditable without adding host mutation.

## Deterministic report surface

The report begins with:

```text
FEDORA HOST INSTALL PREFLIGHT
```

Required report fields include:

```text
classification=ready-local-rpm
denial=none
host_classification=mutable-fedora-host
install_lane=local-doc-rpm
preflight_passed=1
host_install_candidate=1
host_install_performed=0
host_mutation_performed=0
network_allowed=0
local_only=1
fedora_host=1
mutable_fedora_host=1
immutable_host=0
rpm_available=1
dnf_available=1
local_rpm_present=1
no_effect=1
evidence_level=1
```

The no-effect fields are deliberate. A passing preflight report still records:

```text
host_install_performed=0
host_mutation_performed=0
network_allowed=0
```

## Current package boundary

For the current documentation-only package posture, a valid host preflight may classify a local doc RPM as a candidate. It must block any expectation that `/usr/bin/latticra`, a service, a kernel module, a boot entry, or an active runtime surface already exists.

If `package_is_doc_only=1` and `command_entrypoint_expected=1`, the classifier reports:

```text
classification=blocked
denial=runtime-entrypoint-not-present
install_lane=blocked-doc-only-package-runtime-command
```

## Validation

This implementation is guarded by:

```sh
sh scripts/test-fedora-host-install-preflight.sh
```

Expected output:

```text
fedora_host_install_preflight: ok
```

The documentation guard is:

```sh
sh scripts/test-fedora-host-install-preflight-docs.sh
```

Expected output:

```text
fedora_host_install_preflight_docs: ok
```

## Non-claims

This classifier does not install Latticra, does not prove Fedora package approval, does not create RPM artifacts, does not submit to Fedora, does not claim Fedora endorsement, does not provide a production installer, and does not prove operating-system readiness.

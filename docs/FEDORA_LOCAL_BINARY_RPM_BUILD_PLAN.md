# Fedora Local Binary RPM Build Plan

Status: planning record
Scope: define the first local binary RPM build path for Latticra without producing artifacts in this slice.

## Purpose

This plan advances Latticra from a local Fedora spec draft toward a local binary RPM build lane.

The goal is conservative: define exactly how a future Fedora lane will create a source archive, run a binary RPM build, and preserve audit evidence while keeping the package local-only.

This plan does not make Latticra a Fedora package. It does not submit Latticra to Fedora. It does not install Latticra on a host.

## Current package shape

The current local spec remains a local-only draft.

Current install payload:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

The executable payload is the no-effect CLI built from `src/latticra_cli.c`.

No service, kernel module, boot entry, SELinux policy, privileged helper, network authority, host-mutation hook, or runtime configuration is installed at this stage.

## Required build inputs

A future binary RPM build lane should define these inputs before it runs `rpmbuild`:

```text
package name: latticra
version source: packaging/fedora/latticra.spec Version field
release source: packaging/fedora/latticra.spec Release field
source archive name: latticra-<version>.tar.gz
source archive root directory: latticra-<version>/
spec path: packaging/fedora/latticra.spec
build root: temporary CI workspace only
artifact retention: audit-only unless a later release gate permits publishing
```

## Source archive plan

The local binary build lane should create a temporary source archive from the checked-out repository.

Required archive properties:

```text
archive name matches Source0
archive root directory matches %autosetup -n %{name}-%{version}
archive excludes .git
archive excludes CI-only temporary output
archive includes README.md
archive includes src/latticra_cli.c
archive includes scripts required by %build
archive includes docs needed by current package metadata
```

The archive should be created in a temporary RPM topdir, not committed to the repository.

## Binary build command plan

A future implementation lane may run a Fedora-container command shaped like:

```sh
rpmbuild -bb packaging/fedora/latticra.spec \
  --define "_topdir ${PWD}/.rpmwork" \
  --define "_sourcedir ${PWD}/.rpmwork/SOURCES" \
  --define "_rpmdir ${PWD}/.rpmwork/RPMS" \
  --define "_builddir ${PWD}/.rpmwork/BUILD" \
  --define "_buildrootdir ${PWD}/.rpmwork/BUILDROOT"
```

The first build lane should run only inside Fedora CI or an explicitly disposable Fedora environment.

## Expected local output

A successful future binary build lane should produce a local RPM under a temporary path like:

```text
.rpmwork/RPMS/*/latticra-*.rpm
```

The lane should record:

```text
rpmbuild exit status
RPM path
RPM filename
RPM package metadata summary
RPM payload file list
RPM verification plan handoff
```

## Post-build checks before install

Before any install smoke lane, the future binary build lane should inspect the generated RPM without installing it:

```sh
rpm -qpi .rpmwork/RPMS/*/latticra-*.rpm
rpm -qpl .rpmwork/RPMS/*/latticra-*.rpm
```

Expected payload at the current stage:

```text
/usr/bin/latticra
/usr/share/doc/latticra/README.md
```

Unexpected payload at the current stage:

```text
/etc/latticra
/usr/lib/systemd/system/latticra.service
kernel modules
bootloader files
privileged helper files
network authority files
host-mutation hooks
SELinux policy files
```

## Relationship to install verification

This plan comes before the install-verification lane.

The correct order is:

```text
1. binary RPM build plan
2. temporary source archive lane
3. local binary RPM build lane
4. RPM payload inspection lane
5. fresh Fedora install smoke lane
6. command/runtime smoke checks only after payload inspection accepts the no-effect entrypoint
```

## Boundary

This plan does not run `rpmbuild`.

It does not run `mock`.

It does not create source archives.

It does not create binary RPM artifacts.

It does not install Latticra.

It does not publish package artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora source archive fixture lane
```

That future slice should create and inspect the temporary source archive only, without running the binary RPM build yet.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-local-binary-rpm-build-plan.sh
```

Expected output:

```text
fedora_local_binary_rpm_build_plan: ok
```

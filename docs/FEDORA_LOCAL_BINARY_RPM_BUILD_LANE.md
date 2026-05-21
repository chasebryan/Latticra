# Fedora Local Binary RPM Build Lane

Status: active local build lane
Scope: build and inspect a local-only Fedora binary RPM inside Fedora CI without installing or publishing it.

## Purpose

This lane advances the Fedora integration path from source archive fixture inspection to a local binary RPM build.

The goal is conservative: prove that the current local spec, temporary source archive, and Fedora build environment can produce a local RPM package and that the resulting payload matches the current documentation-only package posture.

This lane does not install the RPM. It does not publish the RPM. It does not submit Latticra to Fedora.

## Current package truth

The current Fedora spec remains a local-only draft.

The current expected package payload is:

```text
/usr/share/doc/latticra/README.md
```

The current expected package payload does not include:

```text
/usr/bin/latticra
/etc/latticra
/usr/lib/systemd/system/latticra.service
kernel modules
bootloader files
SELinux policy files
runtime configuration
```

Because the current package is documentation-only and does not install compiled ELF payloads, this local build lane disables debug package generation for the lane with:

```text
debug_package %{nil}
```

That is a local build-lane constraint, not a permanent Fedora packaging decision. Debug/source package behavior should be revisited once Latticra installs compiled payloads.

## Build inputs

The lane uses:

```text
packaging/fedora/latticra.spec
Source0: %{name}-%{version}.tar.gz
%autosetup -n %{name}-%{version}
```

The lane reads the current `Name` and `Version` fields from the spec and creates a temporary source archive matching those fields.

## Fedora build environment

The lane should run in a Fedora container or explicitly disposable Fedora environment.

Required tools:

```text
rpm-build
gcc
make
tar
gzip
```

## Build procedure

The lane creates a temporary RPM work tree:

```text
.rpmwork/BUILD
.rpmwork/BUILDROOT
.rpmwork/RPMS
.rpmwork/SOURCES
.rpmwork/SPECS
.rpmwork/SRPMS
```

Then it runs a local binary RPM build shaped like:

```sh
rpmbuild -bb packaging/fedora/latticra.spec \
  --define "_topdir <temporary-rpm-workdir>" \
  --define "_sourcedir <temporary-rpm-workdir>/SOURCES" \
  --define "_rpmdir <temporary-rpm-workdir>/RPMS" \
  --define "_builddir <temporary-rpm-workdir>/BUILD" \
  --define "_buildrootdir <temporary-rpm-workdir>/BUILDROOT" \
  --define "debug_package %{nil}"
```

## RPM inspection

After the local build succeeds, the lane inspects the generated RPM without installing it:

```sh
rpm -qpi <generated-rpm>
rpm -qpl <generated-rpm>
```

The lane verifies the current expected documentation payload and rejects premature runtime/service/boot/policy payloads.

## Pass conditions

This lane passes only if:

```text
Fedora environment is present
rpm-build is available
source archive fixture can be formed
debug package generation is disabled for the current doc-only payload
rpmbuild produces one local latticra RPM
rpm -qpi can read package metadata
rpm -qpl can list payload files
README documentation is present in the RPM payload
no command, service, kernel, boot, SELinux, or runtime config payload appears by accident
all temporary RPM work output is removed at the end of the guard
```

## Boundary

This lane runs a local binary RPM build in CI.

It does not run `mock`.

It does not install Latticra.

It does not publish package artifacts.

It does not upload release artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora RPM payload inspection report
```

That future slice should preserve the package metadata and payload list as a deterministic report without installing the RPM.

## Validation

This lane is guarded by:

```sh
sh scripts/test-fedora-local-binary-rpm-build-lane.sh
```

Expected output:

```text
fedora_local_binary_rpm_build_lane: ok
```
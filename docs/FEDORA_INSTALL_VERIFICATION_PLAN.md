# Fedora Install Verification Plan

Status: planning record
Scope: define how Latticra integrates with Fedora Linux through the local RPM path and how installed-state checks will prove the result.

## Purpose

Latticra should integrate with Fedora as Fedora currently expects software to integrate: through RPM-shaped packaging, installed-file ownership, package queryability, package verification, and isolated Fedora validation lanes.

This plan keeps that integration conservative.

The current package path is local-only. It is not a Fedora submission, not a Fedora package approval request, not a Fedora spin/remix, and not an operating-system replacement claim.

## Current repository state

The current local Fedora spec is a documentation-only package draft.

It installs:

```text
%doc %{_docdir}/%{name}/README.md
```

It does not currently install:

```text
/usr/bin/latticra
/usr/libexec/latticra/*
/etc/latticra/*
/usr/lib/systemd/system/*.service
kernel modules
bootloader entries
SELinux policy
active runtime services
```

That means the first valid installed-state proof is a doc/package-shape proof, not a runnable product proof.

## Fedora integration model

Latticra should advance through these Fedora-facing stages:

```text
1. Local RPM spec remains explicit and local-only.
2. Source archive policy is defined.
3. Source RPM dry-run is introduced.
4. Binary RPM build lane is introduced inside Fedora.
5. Fresh Fedora install smoke lane installs the RPM.
6. Installed package checks prove file ownership and verification.
7. CLI/runtime smoke checks are added only after a real entrypoint exists.
8. COPR, Koji, or Fedora submission paths remain future work and require separate approval gates.
```

## Installed-state checks

Once a local binary RPM exists, the install lane should run checks like:

```sh
rpm -q latticra
rpm -ql latticra
rpm -V latticra
test -r /usr/share/doc/latticra/README.md
```

For the current doc-only package, the install lane should also prove the absence of premature runtime surfaces:

```sh
test ! -e /usr/bin/latticra
test ! -d /etc/latticra
test ! -e /usr/lib/systemd/system/latticra.service
```

Those absence checks are intentional. They protect the project from accidentally claiming runtime behavior before it exists.

## Future command checks

After Latticra exposes a real Fedora-installed command, the install lane may add command smoke checks such as:

```sh
command -v latticra
latticra --version
latticra check
```

Those checks must not be added until the package actually installs a stable command entrypoint.

## Future install smoke lane outline

A future implementation lane may run inside a Fedora container and perform:

```text
install build tools
create source archive
run rpmbuild
install generated RPM into a fresh Fedora environment
query package with rpm -q
list package files with rpm -ql
verify package files with rpm -V
probe expected documentation files
probe absence of premature runtime files
uninstall package
confirm package removal
```

## Pass conditions

The first successful Fedora install-verification lane should prove:

```text
package can be built locally
package can be installed locally
rpm database knows the package
installed files are owned by the package
rpm verification succeeds or has classified expected findings
README documentation is present
no runtime command is claimed before it exists
no service, kernel, boot, or policy surface is installed by accident
```

## Boundary

This plan does not run `rpmbuild`.

It does not run `mock`.

It does not create RPM artifacts.

It does not install Latticra on the host.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Next slice

Recommended next slice:

```text
Add Fedora local binary RPM build plan
```

That future slice should define the temporary source archive and binary build rules without installing artifacts yet.

## Validation

This plan is guarded by:

```sh
sh scripts/test-fedora-install-verification-plan.sh
```

Expected output:

```text
fedora_install_verification_plan: ok
```
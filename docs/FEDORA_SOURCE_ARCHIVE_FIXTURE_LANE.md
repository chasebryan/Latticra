# Fedora Source Archive Fixture Lane

Status: active fixture lane
Scope: create and inspect a temporary Fedora source archive fixture without running RPM builds or installing artifacts.

## Purpose

This lane advances the local Fedora packaging path from planning into a concrete source archive shape check.

The goal is conservative: prove that Latticra can form a temporary source archive matching the current `Source0` and `%autosetup` expectations in `packaging/fedora/latticra.spec`.

This lane does not build a source RPM or binary RPM. It only creates a disposable archive fixture and inspects its contents.

## Current spec relationship

The current spec expects:

```text
Source0: %{name}-%{version}.tar.gz
%autosetup -n %{name}-%{version}
```

For the current local draft, that resolves to:

```text
latticra-0.0.0.tar.gz
latticra-0.0.0/
```

## Fixture rules

The archive fixture must:

```text
use the Name field from packaging/fedora/latticra.spec
use the Version field from packaging/fedora/latticra.spec
create a root directory named latticra-<version>/
create an archive named latticra-<version>.tar.gz
use Git's tracked and unignored source view
include README.md
include packaging/fedora/latticra.spec
include scripts used by the current %build section
exclude .git
exclude temporary RPM work directories
exclude transient .tmp files
exclude RPM artifacts
exclude nested source archive artifacts
refuse symlink entries
normalize tar metadata
remain temporary and uncommitted
```

## Inspection checks

The lane should inspect the archive with `tar -tzf` and verify:

```text
latticra-<version>/README.md
latticra-<version>/packaging/fedora/latticra.spec
latticra-<version>/scripts/test-state-lattice.sh
latticra-<version>/scripts/test-system-bootstrap.sh
latticra-<version>/scripts/test-kernel.sh
latticra-<version>/scripts/test-kernel-lifecycle.sh
```

The lane should also fail if the archive contains:

```text
.git/
.rpmwork/
*.tmp
*.rpm
nested latticra-*.tar.gz
```

## Relationship to later RPM work

This fixture lane comes before RPM build execution.

The intended order is:

```text
1. source archive fixture lane
2. source archive reproducibility contract
3. source archive transcript review validator
4. source archive handoff to temporary RPM topdir
5. local binary RPM build lane
6. RPM payload inspection lane
7. fresh Fedora install smoke lane
```

## Boundary

This lane does not run `rpmbuild`.

It does not run `mock`.

It does not create source RPM artifacts.

It does not create binary RPM artifacts.

It does not install Latticra.

It does not publish package artifacts.

It does not submit Latticra to Fedora.

It does not claim Fedora package approval, Fedora endorsement, Fedora spin/remix status, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, SELinux policy readiness, or security-hardening completion.

## Completed Follow-On Lane

Completed follow-on source archive reproducibility contract:

```text
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
scripts/test-fedora-source-archive-reproducibility-contract.sh
.github/workflows/fedora-source-archive-reproducibility-contract.yml
```

This contract keeps source archive acceptance closed until reviewed transcript evidence exists.

## Next slice

Recommended next slice:

```text
Add a Fedora source archive transcript review validator before source archive evidence can be accepted for mock build or package review.
```

## Validation

This lane is guarded by:

```sh
sh scripts/test-fedora-source-archive-fixture-lane.sh
```

Expected output:

```text
fedora_source_archive_fixture_lane: ok
```

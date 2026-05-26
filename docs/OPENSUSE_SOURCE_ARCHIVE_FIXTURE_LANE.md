# openSUSE Source Archive Fixture Lane

Status: active fixture lane
Scope: create and inspect a temporary openSUSE source archive fixture without running package builds, installing artifacts, or publishing to Open Build Service.

## Purpose

This lane advances the openSUSE packaging path from a reproducibility contract into a concrete source archive shape check.

The goal is conservative: prove that Latticra can form a temporary source archive matching the current `Source0` and `%autosetup` expectations in `packaging/opensuse/latticra.spec`, generate it twice, and confirm the repeated SHA-256 value matches.

This lane does not build a source RPM or binary RPM. It only creates disposable archive fixtures and inspects their contents.

## Current Spec Relationship

The current local-only openSUSE spec expects:

```text
Source0:        %{name}-%{version}.tar.gz
%autosetup -n %{name}-%{version}
```

For the current local draft, that resolves to:

```text
latticra-0.0.0.tar.gz
latticra-0.0.0/
```

## Fixture Rules

The archive fixture must:

```text
use the Name field from packaging/opensuse/latticra.spec
use the Version field from packaging/opensuse/latticra.spec
create a root directory named latticra-<version>/
create an archive named latticra-<version>.tar.gz
generate the archive fixture twice
record matching SHA-256 values for both fixture archives
include README.md
include packaging/opensuse/latticra.spec
include packaging/opensuse/latticra.changes
include scripts used by the current %build section
include src/latticra_cli.c
exclude .git
exclude temporary RPM work directories
exclude build outputs
exclude RPM artifacts
exclude nested source archive artifacts
reject symlink entries before archiving
remain temporary and uncommitted
```

## Inspection Checks

The lane inspects the archive with `tar -tzf` and verifies:

```text
latticra-<version>/README.md
latticra-<version>/packaging/opensuse/latticra.spec
latticra-<version>/packaging/opensuse/latticra.changes
latticra-<version>/scripts/test-state-lattice.sh
latticra-<version>/scripts/test-system-bootstrap.sh
latticra-<version>/scripts/test-kernel.sh
latticra-<version>/scripts/test-kernel-lifecycle.sh
latticra-<version>/scripts/test-latticra-no-effect-cli-status-surface.sh
latticra-<version>/src/latticra_cli.c
```

The lane also fails if the archive contains:

```text
.git/
.rpmwork/
build/
target/
*.rpm
nested latticra-*.tar.gz
symlink entries
```

## Current Evidence

```text
opensuse_source_archive_fixture_lane_present=1
opensuse_source_archive_reproducibility_contract_present=1
source_archive_transcript_present=1
source_archive_created=1
source_archive_sha256_recorded=1
source_archive_reproducible=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
source_archive_contains_spec=1
source_archive_contains_changes=1
source_archive_contains_readme=1
source_archive_excludes_git_dir=1
source_archive_excludes_nested_archives=1
source_archive_excludes_build_outputs=1
source_archive_excludes_rpm_artifacts=1
source_archive_symlink_policy_checked=1
source_archive_path_safety_checked=1
source_archive_accepted_for_build=0
rpmbuild_run=0
osc_build_run=0
rpm_artifact_created=0
obs_publication_claimed=0
package_readiness_claimed=0
```

The source archive evidence is a temporary fixture transcript only. It does not promote the archive to an accepted package-build input.

## Relationship To Later RPM Work

This fixture lane comes before RPM build execution.

The intended order is:

```text
1. source archive reproducibility contract
2. source archive fixture lane
3. temporary RPM topdir handoff lane
4. local openSUSE RPM build lane
5. RPM payload inspection lane
6. install/remove behavior transcript lane
7. Open Build Service review and publication evidence
```

## Boundary

This lane does not run `rpmbuild`.

It does not run `osc build`.

It does not run `rpmlint`.

It does not run `spec-cleaner`.

It does not create source RPM artifacts.

It does not create binary RPM artifacts.

It does not install Latticra.

It does not publish package artifacts.

It does not create an Open Build Service project.

It does not submit Latticra to openSUSE.

It does not claim official openSUSE package status, SUSE endorsement, Open Build Service publication, product readiness, operating-system readiness, runtime authority, kernel authority, boot authority, service authority, policy readiness, or security-hardening completion.

## Next Slice

Recommended next slice:

```text
Add openSUSE temporary RPM topdir handoff lane that stages the verified source archive without running rpmbuild or osc build.
```

That future lane should prove the temporary source archive can be staged into RPM build input paths while package build and publication claims remain blocked.

## Validation

Run:

```sh
sh scripts/test-opensuse-source-archive-fixture-lane.sh
```

Expected output:

```text
opensuse_source_archive_fixture_lane: ok
```

# openSUSE Developer Workflow

Status: developer workflow record
Scope: local openSUSE Linux commands for productive Latticra development, user-local Panel work, and openSUSE maintenance records.

## Purpose

This note gives a repeatable local workflow for working on Latticra from openSUSE Linux.

The goal is simple:

```text
install the small zypper toolchain
install the Panel desktop prerequisites
run the same guards as the Fedora and Ubuntu tracks
maintain local-only openSUSE RPM metadata separately from the Fedora draft
avoid Open Build Service, official package, or SUSE endorsement claims until evidence exists
```

## Install Local Tools

On an openSUSE workstation or openSUSE container, install the basic guard toolchain:

```sh
sudo zypper refresh
sudo zypper install -y git gcc make coreutils findutils diffutils grep pkgconf
```

In a root container, omit `sudo`:

```sh
zypper refresh
zypper install -y git gcc make coreutils findutils diffutils grep pkgconf
```

## Install Panel Prerequisites

For the Rust/egui Latticra Panel and desktop metadata refresh path, install:

```sh
sudo zypper refresh
sudo zypper install -y rust cargo make gcc pkgconf \
  libX11-devel libxcb-devel libXcursor-devel libXrandr-devel libXi-devel \
  libxkbcommon-devel Mesa-libGL-devel wayland-devel desktop-file-utils \
  gtk3-tools
```

If the distro Rust toolchain is unavailable or too old for the locked Cargo dependency graph, use a current stable Rust toolchain through the operator's approved toolchain source before running Panel commands. The repository does not grant network authority or install Rust by itself.

## Fast Local Guard Loop

For a quick sanity check while editing C/kernel files, run:

```sh
sh scripts/test-state-lattice.sh
sh scripts/test-system-bootstrap.sh
sh scripts/test-kernel.sh
sh scripts/test-kernel-lifecycle.sh
sh scripts/test-latticra-no-effect-cli-status-surface.sh
```

## openSUSE Lane Guards

Before merging openSUSE-facing work, run:

```sh
sh scripts/test-opensuse-developer-workflow.sh
sh scripts/test-opensuse-local-rpm-static-validation.sh
sh scripts/test-opensuse-rpmlint-findings-classification.sh
sh scripts/test-opensuse-source-archive-reproducibility-contract.sh
sh scripts/test-opensuse-source-archive-fixture-lane.sh
sh scripts/test-opensuse-rpm-topdir-handoff-lane.sh
sh scripts/test-opensuse-local-rpm-build-gate-contract.sh
sh scripts/test-opensuse-local-rpm-build-environment-contract.sh
sh scripts/test-opensuse-rpm-artifact-naming-contract.sh
sh scripts/test-opensuse-rpm-payload-inspection-contract.sh
sh scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
sh scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
sh scripts/test-opensuse-rpm-validation-promotion-blocker-matrix-contract.sh
sh scripts/test-opensuse-rpm-build-evidence-intake-denial-contract.sh
```

Expected output:

```text
opensuse_developer_workflow: ok
opensuse_local_rpm_static_validation: ok
opensuse_rpmlint_findings_classification: ok
opensuse_source_archive_reproducibility_contract: ok
opensuse_source_archive_fixture_lane: ok
opensuse_rpm_topdir_handoff_lane: ok
opensuse_local_rpm_build_gate_contract: ok
opensuse_local_rpm_build_environment_contract: ok
opensuse_rpm_artifact_naming_contract: ok
opensuse_rpm_payload_inspection_contract: ok
opensuse_rpm_install_remove_transcript_contract: ok
opensuse_obs_publication_non_claim_review_contract: ok
opensuse_rpm_validation_promotion_blocker_matrix_contract: ok
opensuse_rpm_build_evidence_intake_denial_contract: ok
```

## Panel From Source

After the prerequisites are present:

```sh
export PATH="$HOME/.local/bin:$PATH"
make -C installer gui
```

The guarded user-local install remains the same on openSUSE:

```sh
make -C installer dry-run
make -C installer local-example
make -C installer verify-local
```

## Maintenance Rhythm

Use this loop for productive openSUSE maintenance:

```text
1. Create a small branch.
2. Make one bounded openSUSE-facing change.
3. Run the fast local guard loop.
4. Run the openSUSE lane guards when the branch touches packaging, installer, prerequisites, or openSUSE docs.
5. Keep package language local-only until real lint/build/install and Open Build Service evidence exists.
```

## Current Boundary

This workflow is for local developer productivity, user-local Panel work, and local-only openSUSE package maintenance. It does not publish an RPM, create an Open Build Service project, submit to openSUSE, claim official package readiness, claim SUSE endorsement, install a root service, modify systemd, modify the kernel, or claim production readiness.

## Validation

This workflow note is guarded by:

```sh
sh scripts/test-opensuse-developer-workflow.sh
```

Expected output:

```text
opensuse_developer_workflow: ok
```

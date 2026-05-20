# Fedora Developer Workflow

Status: developer workflow record
Scope: local Fedora Linux commands for productive Latticra development.

## Purpose

This note gives a repeatable local workflow for working on Latticra from Fedora Linux after the Fedora build lane was added.

The goal is simple:

```text
install the small toolchain
run the same guards as CI
keep kernel evidence work fast and repeatable
avoid packaging work until the build lane stays green
```

## Install local tools

On a Fedora workstation or Fedora container, install the basic tools:

```sh
sudo dnf -y install git gcc make coreutils findutils diffutils grep
```

In a root container, omit `sudo`:

```sh
dnf -y install git gcc make coreutils findutils diffutils grep
```

## Fast local guard loop

For a quick sanity check while editing C/kernel files, run:

```sh
sh scripts/test-state-lattice.sh
sh scripts/test-system-bootstrap.sh
sh scripts/test-kernel.sh
sh scripts/test-kernel-lifecycle.sh
```

## Kernel evidence guard loop

Before opening a kernel evidence PR, run:

```sh
sh scripts/test-kernel-lifecycle.sh
sh scripts/test-kernel-lifecycle-report-runner.sh
sh scripts/test-kernel-lifecycle-subsystem-summary.sh
sh scripts/test-kernel-lifecycle-subsystem-summary-report-runner.sh
sh scripts/test-kernel-lifecycle-rollback-plan.sh
```

## Fedora lane guard

Before merging Fedora-facing work, run:

```sh
sh scripts/test-fedora-build-lane.sh
```

Expected output:

```text
fedora_build_lane: ok
```

## Suggested work rhythm

Use this loop for productive development:

```text
1. Create a small branch.
2. Make one bounded change.
3. Run the fast local guard loop.
4. Run the Fedora lane guard when the branch touches build, kernel, or Fedora-facing files.
5. Open a focused PR with clear non-claims.
```

## Current boundary

This workflow is for local developer productivity. It does not add package metadata or change Latticra capability claims.

## Next recommended lane

After this workflow note, the next Fedora-facing slice should be:

```text
Fedora package metadata plan
```

That should be a planning slice before any spec file is added.

## Validation

This workflow note is guarded by:

```sh
sh scripts/test-fedora-developer-workflow.sh
```

Expected output:

```text
fedora_developer_workflow: ok
```

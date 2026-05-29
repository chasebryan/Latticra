# Ubuntu Developer Workflow

Status: developer workflow record
Scope: local Ubuntu Linux commands for productive Latticra development and user-local Panel work.

## Purpose

This note gives a repeatable local workflow for working on Latticra from Ubuntu Linux after the Ubuntu build lane was added.

The goal is simple:

```text
install the small toolchain
install the Panel desktop prerequisites
run the same guards as CI
keep local validation fast and repeatable
avoid archive or PPA claims until the deb lane has real evidence
```

## Install Local Tools

On an Ubuntu workstation or Ubuntu container, install the basic guard toolchain:

```sh
sudo apt-get update
sudo apt-get install -y git build-essential make gcc pkg-config coreutils findutils diffutils grep
```

In a root container, omit `sudo`:

```sh
apt-get update
apt-get install -y git build-essential make gcc pkg-config coreutils findutils diffutils grep
```

## Install Panel Prerequisites

For the Rust/egui Latticra Panel and desktop metadata refresh path, install:

```sh
sudo apt-get update
sudo apt-get install -y rustc cargo make gcc pkg-config \
  libx11-dev libxcb1-dev libxcursor-dev libxrandr-dev libxi-dev \
  libxkbcommon-dev libgl1-mesa-dev libwayland-dev desktop-file-utils \
  libgtk-3-bin
```

If the distro Rust toolchain is too old for the locked Cargo dependency graph, use a current stable Rust toolchain through the operator's approved toolchain source before running Panel commands. The repository does not grant network authority or install Rust by itself.

## Fast Local Guard Loop

For a quick sanity check while editing C/kernel files, run:

```sh
sh scripts/test-state-lattice.sh
sh scripts/test-system-bootstrap.sh
sh scripts/test-kernel.sh
sh scripts/test-kernel-lifecycle.sh
sh scripts/test-latticra-no-effect-cli-status-surface.sh
```

## Ubuntu Lane Guard

Before merging Ubuntu-facing work, run this on Ubuntu:

```sh
sh scripts/test-ubuntu-build-lane.sh
```

Expected output:

```text
ubuntu_build_lane: ok
```

## Panel From Source

After the prerequisites are present:

```sh
export PATH="$HOME/.local/bin:$PATH"
make -C installer gui
```

The guarded user-local install remains the same on Ubuntu:

```sh
make -C installer dry-run
make -C installer local-example
make -C installer verify-local
```

## Suggested Work Rhythm

Use this loop for productive development:

```text
1. Create a small branch.
2. Make one bounded change.
3. Run the fast local guard loop.
4. Run the Ubuntu lane guard when the branch touches build, installer, packaging, or Ubuntu-facing docs.
5. Keep package language local-only until real lint/build/install evidence exists.
```

## Current Boundary

This workflow is for local developer productivity and user-local Panel work. It does not publish a deb, create a PPA, submit to Ubuntu, claim Ubuntu archive readiness, install a root service, modify systemd, modify the kernel, or claim production readiness.

## Validation

This workflow note is guarded by:

```sh
sh scripts/test-ubuntu-developer-workflow.sh
```

Expected output:

```text
ubuntu_developer_workflow: ok
```

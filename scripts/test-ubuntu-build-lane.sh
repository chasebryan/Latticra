#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

if [ ! -r /etc/os-release ] || ! grep -Eq '^(ID=ubuntu|ID_LIKE=.*ubuntu)' /etc/os-release; then
  printf 'ubuntu build lane: expected Ubuntu environment\n' >&2
  exit 1
fi

apt_install() {
  if ! command -v apt-get >/dev/null 2>&1; then
    return 0
  fi

  if [ "$(id -u)" -eq 0 ]; then
    apt-get update
    env DEBIAN_FRONTEND=noninteractive apt-get install -y "$@"
  elif command -v sudo >/dev/null 2>&1; then
    sudo apt-get update
    sudo env DEBIAN_FRONTEND=noninteractive apt-get install -y "$@"
  fi
}

apt_install git build-essential make gcc pkg-config coreutils findutils diffutils grep

command -v cc >/dev/null 2>&1
command -v grep >/dev/null 2>&1

sh scripts/test-state-lattice.sh
sh scripts/test-system-bootstrap.sh
sh scripts/test-kernel.sh
sh scripts/test-kernel-lifecycle.sh
sh scripts/test-kernel-lifecycle-report-runner.sh
sh scripts/test-kernel-lifecycle-subsystem-summary.sh
sh scripts/test-kernel-lifecycle-subsystem-summary-report-runner.sh
sh scripts/test-latticra-no-effect-cli-status-surface.sh
sh scripts/test-ubuntu-developer-workflow.sh
sh scripts/test-ubuntu-local-deb-static-validation.sh

printf 'ubuntu_build_lane: ok\n'

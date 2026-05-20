#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

if [ ! -r /etc/fedora-release ]; then
  printf 'fedora build lane: expected Fedora environment\n' >&2
  exit 1
fi

if command -v dnf >/dev/null 2>&1; then
  dnf -y install gcc make git coreutils findutils diffutils grep
fi

command -v cc >/dev/null 2>&1
command -v grep >/dev/null 2>&1

sh scripts/test-state-lattice.sh
sh scripts/test-system-bootstrap.sh
sh scripts/test-kernel.sh
sh scripts/test-kernel-lifecycle.sh
sh scripts/test-kernel-lifecycle-report-runner.sh
sh scripts/test-kernel-lifecycle-subsystem-summary.sh
sh scripts/test-kernel-lifecycle-subsystem-summary-report-runner.sh
sh scripts/test-kernel-lifecycle-rollback-plan.sh
sh scripts/test-kernel-lifecycle-status-alignment.sh
sh scripts/test-fedora-readiness-plan.sh

printf 'fedora_build_lane: ok\n'

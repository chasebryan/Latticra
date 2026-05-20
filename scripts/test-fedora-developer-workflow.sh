#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora developer workflow: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora developer workflow: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_DEVELOPER_WORKFLOW.md
require_file docs/FEDORA_READINESS_PLAN.md
require_file scripts/test-fedora-build-lane.sh
require_file .github/workflows/compat-linux.yml

require_contains 'Status: developer workflow record' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'local Fedora Linux commands for productive Latticra development' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'sudo dnf -y install git gcc make coreutils findutils diffutils grep' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'dnf -y install git gcc make coreutils findutils diffutils grep' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'Fast local guard loop' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'Kernel evidence guard loop' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'sh scripts/test-fedora-build-lane.sh' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'fedora_build_lane: ok' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'Fedora package metadata plan' docs/FEDORA_DEVELOPER_WORKFLOW.md
require_contains 'fedora_developer_workflow: ok' docs/FEDORA_DEVELOPER_WORKFLOW.md

printf 'fedora_developer_workflow: ok\n'

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora installroot rpm mutation lane docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora installroot rpm mutation lane docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_file scripts/test-fedora-installroot-rpm-mutation-lane.sh
require_file packaging/fedora/latticra.spec

require_contains 'Status: active execution lane' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_contains 'Evidence level: 6' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_contains 'installroot_filesystem_mutated=1' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_contains 'installroot_rpmdb_mutated=1' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_contains 'live_container_rpmdb_mutated=0' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_contains 'developer_host_mutation_performed=0' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_contains 'post_removal_absence_verified=1' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_contains 'fedora_installroot_rpm_mutation_lane: ok' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_contains 'fedora_installroot_rpm_mutation_lane_docs: ok' docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md

printf 'fedora_installroot_rpm_mutation_lane_docs: ok\n'

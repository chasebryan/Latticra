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

doc='docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md'
runner='scripts/test-fedora-installroot-rpm-mutation-lane.sh'
workflow='.github/workflows/fedora-installroot-rpm-mutation-lane-docs.yml'

require_file "$doc"
require_file "$runner"
require_file "$workflow"
require_file packaging/fedora/latticra.spec
require_file docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
require_file docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_file docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER.md

require_contains '# Fedora Installroot RPM Mutation Lane' "$doc"
require_contains 'Status: active execution lane' "$doc"
require_contains 'Evidence level: 6' "$doc"
require_contains 'LATTICRA_ALLOW_INSTALLROOT_RPM_MUTATION=1' "$doc"
require_contains 'ID=fedora' "$doc"
require_contains 'GITHUB_ACTIONS=true' "$doc"
require_contains 'rpmbuild_present=1' "$doc"
require_contains 'rpm_present=1' "$doc"
require_contains 'FEDORA INSTALLROOT RPM MUTATION LANE' "$doc"
require_contains 'execution_status=ok' "$doc"
require_contains 'install_mutation_allowed=1' "$doc"
require_contains 'install_mutation_performed=1' "$doc"
require_contains 'removal_mutation_allowed=1' "$doc"
require_contains 'removal_mutation_performed=1' "$doc"
require_contains 'installroot_filesystem_mutated=1' "$doc"
require_contains 'installroot_rpmdb_mutated=1' "$doc"
require_contains 'live_container_rpmdb_mutated=0' "$doc"
require_contains 'developer_host_mutation_performed=0' "$doc"
require_contains 'post_removal_absence_verified=1' "$doc"
require_contains 'rollback_planned=1' "$doc"
require_contains 'partial_failure_report_required=1' "$doc"
require_contains '/usr/share/doc/latticra/README.md' "$doc"
require_contains '/usr/bin/latticra' "$doc"
require_contains '/etc/latticra' "$doc"
require_contains '/usr/lib/systemd/system/latticra.service' "$doc"
require_contains '/usr/lib/modules' "$doc"
require_contains '/boot/latticra' "$doc"
require_contains 'sh scripts/test-fedora-installroot-rpm-mutation-lane-docs.sh' "$doc"
require_contains 'fedora_installroot_rpm_mutation_lane_docs: ok' "$doc"
require_contains 'does not install Latticra on a developer host' "$doc"
require_contains 'does not publish artifacts' "$doc"
require_contains 'does not mutate a developer workstation' "$doc"

require_contains 'LATTICRA_ALLOW_INSTALLROOT_RPM_MUTATION' "$runner"
require_contains 'GITHUB_ACTIONS' "$runner"
require_contains '[ "${ID:-}" = "fedora" ]' "$runner"
require_contains 'rpm --root "$installroot"' "$runner"
require_contains 'live_container_rpmdb_mutated=0' "$runner"
require_contains 'developer_host_mutation_performed=0' "$runner"
require_contains 'installroot_rpmdb_mutated=1' "$runner"
require_contains 'post_removal_absence_verified=1' "$runner"
require_contains 'fedora_installroot_rpm_mutation_lane: ok' "$runner"

require_contains 'name: Fedora Installroot RPM Mutation Lane Docs' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'sh scripts/test-fedora-installroot-rpm-mutation-lane-docs.sh' "$workflow"
if grep -Fq 'LATTICRA_ALLOW_INSTALLROOT_RPM_MUTATION=1 sh scripts/test-fedora-installroot-rpm-mutation-lane.sh' "$workflow"; then
  printf 'fedora installroot rpm mutation lane docs: workflow must not run mutating installroot lane\n' >&2
  exit 1
fi

printf 'fedora_installroot_rpm_mutation_lane_docs: ok\n'

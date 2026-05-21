#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora host install preflight plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora host install preflight plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_file docs/FEDORA_HOST_INSTALL_DECISION_GATE.md
require_file docs/FEDORA_LOCAL_TESTING_GUIDE.md
require_file docs/FEDORA_INSTALLED_STATE_REPORT_LANE.md
require_file packaging/fedora/latticra.spec

require_contains 'Status: planning record' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'non-installing preflight classifier' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'Is this host eligible for direct host-level install testing' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'Use Fedora containers or disposable Fedora CI for install-smoke testing' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'Fedora marker present' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'bootc command availability' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'bootc status/read-only classification' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'rpm database accessibility' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'git working tree cleanliness' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'test -r /etc/fedora-release' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'command -v bootc >/dev/null 2>&1 || true' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'bootc status >/dev/null 2>&1 || true' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'rpm -q latticra || true' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'git status --short' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'dnf install' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'rpm -Uvh' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'rpm -e' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'host_install_eligible' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'container_only_bootc_or_read_only' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'container_only_dirty_worktree' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'container_only_missing_evidence' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'container_only_existing_latticra_package' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'container_only_unconfirmed_operator_consent' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'operator explicitly accepts temporary RPM database modification' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'fedora_host_install_preflight: classification=container_only_bootc_or_read_only' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'fedora_host_install_preflight: classification=host_install_eligible' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'does not run `rpmbuild`' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'does not run `mock`' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'does not create RPM artifacts' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'does not install Latticra' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'does not remove Latticra' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'does not modify the host RPM database' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'Add Fedora host install preflight classifier' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md
require_contains 'fedora_host_install_preflight_plan: ok' docs/FEDORA_HOST_INSTALL_PREFLIGHT_PLAN.md

require_contains '%doc %{_docdir}/%{name}/README.md' packaging/fedora/latticra.spec

printf 'fedora_host_install_preflight_plan: ok\n'
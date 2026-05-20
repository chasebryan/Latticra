#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora package metadata plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora package metadata plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_file docs/FEDORA_READINESS_PLAN.md
require_file docs/FEDORA_DEVELOPER_WORKFLOW.md
require_file docs/LICENSE_MIGRATION_PLAN.md
require_file docs/OPEN_ECOSYSTEM_POLICY.md
require_file scripts/test-fedora-build-lane.sh

require_contains 'Status: planning record' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'metadata required before a Fedora-oriented package draft exists' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'build lane first' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'local developer workflow second' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'metadata plan third' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'spec draft later' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'package_name' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'source_archive_policy' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'license_expression' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'build_requires' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'runtime_requires' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'installed_binaries' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'installed_docs' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'package_name=latticra' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'source_archive_policy=tagged upstream source archive only' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'license_expression=to-be-confirmed-before-spec' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'build_requires=gcc, make' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'This plan does not add a spec file.' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'Fedora build lane is green' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'license expression is decided' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'Add local RPM spec draft plan' docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_contains 'fedora_package_metadata_plan: ok' docs/FEDORA_PACKAGE_METADATA_PLAN.md

printf 'fedora_package_metadata_plan: ok\n'

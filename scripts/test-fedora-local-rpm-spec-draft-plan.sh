#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora local rpm spec draft plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora local rpm spec draft plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_file docs/FEDORA_READINESS_PLAN.md
require_file docs/FEDORA_DEVELOPER_WORKFLOW.md
require_file docs/FEDORA_PACKAGE_METADATA_PLAN.md
require_file scripts/test-fedora-build-lane.sh

require_contains 'Status: planning record' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'local-only RPM spec draft preparation before adding a spec file' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'local RPM spec draft plan' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'local spec draft later' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'packaging/fedora/latticra.spec' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'Do not add that file in this planning slice.' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'Name' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'Version' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'Release' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'Summary' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'License' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'Source0' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'BuildRequires' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains '%description' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains '%build' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains '%install' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains '%files' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'development and evidence tooling only' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'Do not write the spec License field until the license expression is reviewed.' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'local-only until lint and local build validation are added' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'Add local RPM spec draft skeleton' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md
require_contains 'fedora_local_rpm_spec_draft_plan: ok' docs/FEDORA_LOCAL_RPM_SPEC_DRAFT_PLAN.md

printf 'fedora_local_rpm_spec_draft_plan: ok\n'

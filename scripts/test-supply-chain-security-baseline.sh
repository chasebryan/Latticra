#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'supply chain security baseline: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

baseline='docs/SUPPLY_CHAIN_SECURITY_BASELINE.md'
status='docs/status/SUPPLY_CHAIN_SECURITY_BASELINE_STATUS.md'
security='SECURITY.md'
foundation_index='docs/FOUNDATION_INDEX.md'
status_index='docs/status/README.md'
security_page='docs/security.html'
quality_guard='scripts/test-quality-safety-guards.sh'
archive_guard='scripts/test-fedora-source-archive-fixture-lane.sh'
archive_doc='docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md'
makefile='Makefile'
workflow='.github/workflows/supply-chain-security-baseline.yml'

for file in \
  "$baseline" \
  "$status" \
  "$security" \
  "$foundation_index" \
  "$status_index" \
  "$security_page" \
  "$quality_guard" \
  "$archive_guard" \
  "$archive_doc" \
  "$makefile" \
  "$workflow"
do
  require_file "$file"
done

require_contains 'Status: supply-chain security baseline' "$baseline"
require_contains 'workflow_triggers_limited_to_push_and_pull_request=1' "$baseline"
require_contains 'out_of_band_workflow_triggers_require_dedicated_review=1' "$baseline"
require_contains 'deployment_environment_use_requires_dedicated_review=1' "$baseline"
require_contains 'github_expression_interpolation_requires_dedicated_review=1' "$baseline"
require_contains 'external_actions_must_be_commit_pinned=1' "$baseline"
require_contains 'checkout_persist_credentials_false_required=1' "$baseline"
require_contains 'workflow_token_permissions_read_only=1' "$baseline"
require_contains 'workflow_secrets_disallowed_without_dedicated_review=1' "$baseline"
require_contains 'implicit_github_token_surfaces_disallowed_without_dedicated_review=1' "$baseline"
require_contains 'remote_pipe_to_shell_disallowed=1' "$baseline"
require_contains 'package_manager_commands_allowlisted=1' "$baseline"
require_contains 'source_archive_fixture_requires_reviewed_symlink_guard=1' "$baseline"
require_contains 'reproducible_source_archive_metadata_required=1' "$baseline"
require_contains 'complete supply-chain security' "$baseline"

require_contains 'Status: status record for repository supply-chain security baseline' "$status"
require_contains 'supply_chain_security_baseline_present=1' "$status"
require_contains 'quality_security_standards_in_quality_aggregate=1' "$status"
require_contains 'source_archive_fixture_requires_reviewed_symlink_guard=1' "$status"
require_contains 'complete_supply_chain_security_claimed=0' "$status"

require_contains 'docs/SUPPLY_CHAIN_SECURITY_BASELINE.md' "$security"
require_contains 'SUPPLY_CHAIN_SECURITY_BASELINE.md' "$foundation_index"
require_contains 'SUPPLY_CHAIN_SECURITY_BASELINE_STATUS.md' "$status_index"
require_contains 'Supply-chain baseline' "$security_page"

require_contains 'quality-security-standards:' "$makefile"
require_contains 'quality-safety-guards quality-security-standards' "$makefile"
require_contains 'sh ./scripts/test-supply-chain-security-baseline.sh' "$makefile"

require_contains 'out-of-band workflow triggers without a dedicated review guard' "$quality_guard"
require_contains 'deployment environments without a dedicated review guard' "$quality_guard"
require_contains 'GitHub expression interpolation without a dedicated review guard' "$quality_guard"
require_contains 'workflow_dispatch' "$quality_guard"
require_contains 'repository_dispatch' "$quality_guard"
require_contains 'workflow_run' "$quality_guard"
require_contains 'workflow_call' "$quality_guard"
require_contains 'schedule' "$quality_guard"
require_contains 'quality-security-standards' "$quality_guard"

require_contains 'COPYFILE_DISABLE=1' "$archive_guard"
require_contains 'gzip.GzipFile' "$archive_guard"
require_contains 'mtime=0' "$archive_guard"
require_contains 'info.uid = 0' "$archive_guard"
require_contains 'info.gid = 0' "$archive_guard"
require_contains 'refusing symlink entry in source archive fixture' "$archive_guard"
require_contains 'git", "ls-files"' "$archive_guard"
require_contains 'exclude .git' "$archive_doc"
require_contains 'refuse symlink entries' "$archive_doc"
require_contains 'normalize tar metadata' "$archive_doc"

require_contains 'name: Supply Chain Security Baseline' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-supply-chain-security-baseline.sh' "$workflow"

printf 'supply_chain_security_baseline: ok\n'

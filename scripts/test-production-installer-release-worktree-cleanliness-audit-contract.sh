#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer release worktree cleanliness audit contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

require_not_matching() {
  pattern="$1"
  file="$2"
  if grep -Eq -- "$pattern" "$file"; then
    fail "unexpected executable pattern in $file: $pattern"
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

doc='docs/PRODUCTION_INSTALLER_RELEASE_WORKTREE_CLEANLINESS_AUDIT_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_RELEASE_WORKTREE_CLEANLINESS_AUDIT_STATUS.md'
script='scripts/production-installer-release-worktree-cleanliness-audit.sh'
test_script='scripts/test-production-installer-release-worktree-cleanliness-audit-contract.sh'
preflight_script='scripts/production-installer-release-artifact-candidate-preflight.sh'
preflight_contract='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
installer_page='docs/installer.html'
workflow='.github/workflows/production-installer-release-worktree-cleanliness-audit.yml'

for file in "$doc" "$status" "$script" "$test_script" "$preflight_script" \
  "$preflight_contract" "$readiness" "$ledger" "$index" "$installer_page" \
  "$workflow" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect release worktree cleanliness audit contract' "$doc"
require_contains 'release_worktree_cleanliness_audit_present=1' "$doc"
require_contains 'release_worktree_cleanliness_audit_mode=no-effect-tracked-status-report' "$doc"
require_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$doc"
require_contains 'release_worktree_cleanliness_audit_passed=0' "$doc"
require_contains 'release_worktree_tracked_worktree_clean=0' "$doc"
require_contains 'release_worktree_tracked_dirty_count=<observed>' "$doc"
require_contains 'release_worktree_staged_change_count=<observed>' "$doc"
require_contains 'release_worktree_unstaged_change_count=<observed>' "$doc"
require_contains 'release_worktree_untracked_ignored_for_release_cleanliness=1' "$doc"
require_contains 'release_worktree_dirty_inventory_present=1' "$doc"
require_contains 'release_worktree_dirty_inventory_mode=stdout-only-tracked-status-list' "$doc"
require_contains 'release_worktree_dirty_inventory_complete=<observed>' "$doc"
require_contains 'release_worktree_dirty_inventory_count=<observed>' "$doc"
require_contains 'release_worktree_dirty_inventory_written=0' "$doc"
require_contains 'release_worktree_dirty_inventory_accepted=0' "$doc"
require_contains 'release_worktree_cleanliness_remediation_required=<observed>' "$doc"
require_contains '[tracked_dirty_inventory]' "$doc"
require_contains 'tracked_status_entry=<git-porcelain-status-and-path-or-none>' "$doc"
require_contains 'release_artifact_candidate_tracked_dirty_count=<observed>' "$doc"
require_contains 'release_artifact_candidate_inputs_satisfied=0' "$doc"
require_contains 'package_manager_invoked=0' "$doc"
require_contains 'network_allowed=0' "$doc"
require_contains 'git_add_performed=0' "$doc"
require_contains 'git_commit_performed=0' "$doc"
require_contains 'git_checkout_performed=0' "$doc"
require_contains 'git_reset_performed=0' "$doc"
require_contains 'git_clean_performed=0' "$doc"
require_contains 'tracked_file_reverted=0' "$doc"
require_contains 'git_add_invoked=0' "$doc"
require_contains 'git_commit_invoked=0' "$doc"
require_contains 'git_checkout_invoked=0' "$doc"
require_contains 'git_clean_invoked=0' "$doc"
require_contains 'git_reset_invoked=0' "$doc"
require_contains 'git_revert_invoked=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-release-worktree-cleanliness-audit.sh' "$doc"

require_contains 'Status: worktree-audit/status alignment' "$status"
require_contains 'release_worktree_cleanliness_audit_present=1' "$status"
require_contains 'release_worktree_cleanliness_audit_passed=0' "$status"
require_contains 'release_worktree_tracked_worktree_clean=0' "$status"
require_contains 'release_worktree_tracked_dirty_count=<observed>' "$status"
require_contains 'release_worktree_dirty_inventory_present=1' "$status"
require_contains 'release_worktree_dirty_inventory_mode=stdout-only-tracked-status-list' "$status"
require_contains 'release_worktree_dirty_inventory_count=<observed>' "$status"
require_contains 'release_worktree_dirty_inventory_written=0' "$status"
require_contains 'release_worktree_dirty_inventory_accepted=0' "$status"
require_contains 'release_worktree_cleanliness_remediation_required=<observed>' "$status"
require_contains 'release_artifact_candidate_tracked_dirty_count=<observed>' "$status"
require_contains 'git_add_performed=0' "$status"
require_contains 'git_commit_performed=0' "$status"
require_contains 'git_checkout_performed=0' "$status"
require_contains 'git_reset_performed=0' "$status"
require_contains 'git_clean_performed=0' "$status"
require_contains 'tracked_file_reverted=0' "$status"
require_contains 'git_add_invoked=0' "$status"
require_contains 'git_reset_invoked=0' "$status"

require_contains 'release_worktree_cleanliness_audit_present=1' "$readiness"
require_contains 'release_worktree_cleanliness_audit_mode=no-effect-tracked-status-report' "$readiness"
require_contains 'release_worktree_cleanliness_audit_passed=0' "$readiness"
require_contains 'release_worktree_tracked_worktree_clean=0' "$readiness"
require_contains 'release_worktree_tracked_dirty_count=<observed>' "$readiness"
require_contains 'release_worktree_dirty_inventory_present=1' "$readiness"
require_contains 'release_worktree_dirty_inventory_mode=stdout-only-tracked-status-list' "$readiness"
require_contains 'release_worktree_dirty_inventory_count=<observed>' "$readiness"
require_contains 'release_worktree_dirty_inventory_written=0' "$readiness"
require_contains 'release_worktree_dirty_inventory_accepted=0' "$readiness"
require_contains 'release_worktree_cleanliness_remediation_required=<observed>' "$readiness"
require_contains 'release_artifact_candidate_tracked_dirty_count=<observed>' "$readiness"
require_contains 'package_manager_invoked=0' "$readiness"
require_contains 'network_allowed=0' "$readiness"
require_contains 'git_add_performed=0' "$readiness"
require_contains 'git_commit_performed=0' "$readiness"
require_contains 'git_checkout_performed=0' "$readiness"
require_contains 'git_reset_performed=0' "$readiness"
require_contains 'git_clean_performed=0' "$readiness"
require_contains 'tracked_file_reverted=0' "$readiness"
require_contains 'git_add_invoked=0' "$readiness"
require_contains 'git_commit_invoked=0' "$readiness"
require_contains 'git_clean_invoked=0' "$readiness"
require_contains 'git_reset_invoked=0' "$readiness"
require_contains 'git_revert_invoked=0' "$readiness"

require_contains '## Installer Release Worktree Cleanliness Audit' "$ledger"
require_contains 'release_worktree_cleanliness_audit_present=1' "$ledger"
require_contains 'release_worktree_cleanliness_audit_passed=0' "$ledger"
require_contains 'release_worktree_tracked_worktree_clean=0' "$ledger"
require_contains 'release_worktree_tracked_dirty_count=<observed>' "$ledger"
require_contains 'release_worktree_dirty_inventory_present=1' "$ledger"
require_contains 'release_worktree_dirty_inventory_mode=stdout-only-tracked-status-list' "$ledger"
require_contains 'release_worktree_dirty_inventory_count=<observed>' "$ledger"
require_contains 'release_worktree_dirty_inventory_written=0' "$ledger"
require_contains 'release_worktree_dirty_inventory_accepted=0' "$ledger"
require_contains 'release_worktree_cleanliness_remediation_required=<observed>' "$ledger"
require_contains 'tracked_file_reverted=0' "$ledger"
require_contains 'This closes the worktree-cleanliness-audit and stdout-only dirty-inventory presence gaps only.' "$ledger"
require_contains 'release_worktree_cleanliness_audit_present=1' README.md
require_contains 'release_worktree_dirty_inventory_present=1' README.md
require_contains 'release_worktree_dirty_inventory_written=0' README.md
require_contains 'docs/PRODUCTION_INSTALLER_RELEASE_WORKTREE_CLEANLINESS_AUDIT_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_RELEASE_WORKTREE_CLEANLINESS_AUDIT_STATUS.md' README.md
require_contains 'stdout-only dirty inventory' "$installer_page"
require_contains 'PRODUCTION_INSTALLER_RELEASE_WORKTREE_CLEANLINESS_AUDIT_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_RELEASE_WORKTREE_CLEANLINESS_AUDIT_STATUS.md' "$index"

require_contains 'release_worktree_cleanliness_audit_present=1' "$preflight_contract"
require_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$preflight_contract"
require_contains 'release_worktree_cleanliness_audit_present=1' "$preflight_script"
require_contains 'release_worktree_dirty_inventory_present=1' "$script"
require_contains 'release_worktree_dirty_inventory_mode=stdout-only-tracked-status-list' "$script"
require_contains 'release_worktree_dirty_inventory_complete=$DIRTY_INVENTORY_COMPLETE' "$script"
require_contains 'release_worktree_dirty_inventory_count=$TRACKED_DIRTY_COUNT' "$script"
require_contains 'release_worktree_dirty_inventory_written=0' "$script"
require_contains 'release_worktree_dirty_inventory_accepted=0' "$script"
require_contains 'release_worktree_cleanliness_remediation_required=$RELEASE_WORKTREE_CLEANLINESS_REMEDIATION_REQUIRED' "$script"
require_contains '[tracked_dirty_inventory]' "$script"
require_contains 'tracked_status_entry=' "$script"
require_contains 'production-installer-release-worktree-cleanliness-audit-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-release-worktree-cleanliness-audit-contract.sh' Makefile
require_contains 'name: Production Installer Release Worktree Cleanliness Audit' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-release-worktree-cleanliness-audit-contract.sh' "$workflow"

require_absent 'git add ' "$script"
require_absent 'git commit' "$script"
require_absent 'git checkout' "$script"
require_absent 'git clean' "$script"
require_absent 'git reset' "$script"
require_absent 'git revert' "$script"
require_not_matching '^[[:space:]]*rm[[:space:]]' "$script"
require_not_matching '^[[:space:]]*sudo[[:space:]]' "$script"

output="$(sh "$script" --tag v0.2.0edge)"
require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER RELEASE WORKTREE CLEANLINESS AUDIT'
require_output_contains "$output" 'worktree_audit_status=ok'
require_output_contains "$output" 'release_worktree_cleanliness_audit_present=1'
require_output_contains "$output" 'release_worktree_cleanliness_audit_mode=no-effect-tracked-status-report'
require_output_contains "$output" 'release_worktree_cleanliness_required_for_release_candidate=1'
require_output_contains "$output" 'release_worktree_cleanliness_audit_passed='
require_output_contains "$output" 'release_worktree_tracked_worktree_clean='
require_output_contains "$output" 'release_worktree_tracked_dirty_count='
require_output_contains "$output" 'release_worktree_staged_change_count='
require_output_contains "$output" 'release_worktree_unstaged_change_count='
require_output_contains "$output" 'release_worktree_dirty_inventory_present=1'
require_output_contains "$output" 'release_worktree_dirty_inventory_mode=stdout-only-tracked-status-list'
require_output_contains "$output" 'release_worktree_dirty_inventory_complete='
require_output_contains "$output" 'release_worktree_dirty_inventory_count='
require_output_contains "$output" 'release_worktree_dirty_inventory_written=0'
require_output_contains "$output" 'release_worktree_dirty_inventory_accepted=0'
require_output_contains "$output" 'release_worktree_cleanliness_remediation_required='
require_output_contains "$output" 'current_branch='
require_output_contains "$output" 'current_head_commit='
require_output_contains "$output" 'release_candidate_tag=v0.2.0edge'
require_output_contains "$output" 'release_artifact_candidate_tracked_dirty_count='
require_output_contains "$output" 'release_artifact_candidate_inputs_satisfied=0'
require_output_contains "$output" 'package_manager_invoked=0'
require_output_contains "$output" 'network_allowed=0'
require_output_contains "$output" 'git_add_performed=0'
require_output_contains "$output" 'git_commit_performed=0'
require_output_contains "$output" 'git_checkout_performed=0'
require_output_contains "$output" 'git_reset_performed=0'
require_output_contains "$output" 'git_clean_performed=0'
require_output_contains "$output" 'tracked_file_reverted=0'
require_output_contains "$output" 'git_add_invoked=0'
require_output_contains "$output" 'git_commit_invoked=0'
require_output_contains "$output" 'git_clean_invoked=0'
require_output_contains "$output" 'git_reset_invoked=0'
require_output_contains "$output" 'git_revert_invoked=0'
require_output_contains "$output" '[tracked_dirty_inventory]'
require_output_contains "$output" 'tracked_status_entry='
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'host_mutation_performed=0'

missing_tag_output="$(sh "$script" --tag latticra-nonexistent-worktree-audit-tag)"
require_output_contains "$missing_tag_output" 'release_candidate_tag=latticra-nonexistent-worktree-audit-tag'
require_output_contains "$missing_tag_output" 'release_candidate_tag_exists=0'
require_output_contains "$missing_tag_output" 'release_worktree_cleanliness_audit_present=1'

if sh "$script" --unknown >/dev/null 2>&1; then
  fail 'unknown argument unexpectedly succeeded'
fi

printf 'production_installer_release_worktree_cleanliness_audit_contract: ok\n'

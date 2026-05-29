#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-release-worktree-cleanliness-audit.sh [--tag <tag>]

Reports tracked worktree cleanliness for a future production-installer release
artifact candidate. It does not stage, commit, clean, reset, revert, delete,
write release evidence, invoke build tools, or mutate the host.
USAGE
}

fail() {
  printf 'production installer release worktree cleanliness audit: %s\n' "$1" >&2
  exit "${2:-1}"
}

tool_available() {
  if command -v "$1" >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

tool_path() {
  if command -v "$1" >/dev/null 2>&1; then
    command -v "$1"
  else
    printf 'missing\n'
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern" 65
}

TAG='v0.2.0edge'

while [ "$#" -gt 0 ]; do
  case "$1" in
    --tag)
      [ "$#" -ge 2 ] || fail 'missing value for --tag' 64
      TAG="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_candidate_preflight_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_candidate_tracked_worktree_clean=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_candidate_tracked_worktree_clean=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md
require_contains 'release_artifact_candidate_tracked_worktree_clean=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

GIT_AVAILABLE="$(tool_available git)"
BRANCH='detached'
HEAD_COMMIT='missing'
TAG_EXISTS=0
TAG_COMMIT='missing'
TRACKED_STATUS=''

if [ "$GIT_AVAILABLE" = "1" ]; then
  BRANCH="$(git symbolic-ref --short HEAD 2>/dev/null || printf 'detached\n')"
  HEAD_COMMIT="$(git rev-parse HEAD 2>/dev/null || printf 'missing\n')"
  if git rev-list -n 1 "$TAG" >/dev/null 2>&1; then
    TAG_EXISTS=1
    TAG_COMMIT="$(git rev-list -n 1 "$TAG")"
  fi
  TRACKED_STATUS="$(git status --porcelain --untracked-files=no)"
fi

if [ -n "$TRACKED_STATUS" ]; then
  TRACKED_DIRTY_COUNT="$(printf '%s\n' "$TRACKED_STATUS" | sed '/^$/d' | wc -l | tr -d ' ')"
else
  TRACKED_DIRTY_COUNT=0
fi

TRACKED_WORKTREE_CLEAN=0
if [ "$GIT_AVAILABLE" = "1" ] && [ "$TRACKED_DIRTY_COUNT" = "0" ]; then
  TRACKED_WORKTREE_CLEAN=1
fi

DIRTY_INVENTORY_COMPLETE=0
if [ "$GIT_AVAILABLE" = "1" ]; then
  DIRTY_INVENTORY_COMPLETE=1
fi

RELEASE_WORKTREE_CLEANLINESS_REMEDIATION_REQUIRED=1
if [ "$TRACKED_WORKTREE_CLEAN" = "1" ]; then
  RELEASE_WORKTREE_CLEANLINESS_REMEDIATION_REQUIRED=0
fi

STAGED_CHANGE_COUNT=0
UNSTAGED_CHANGE_COUNT=0
UNMERGED_CHANGE_COUNT=0
DELETED_CHANGE_COUNT=0
RENAMED_CHANGE_COUNT=0
if [ -n "$TRACKED_STATUS" ]; then
  STAGED_CHANGE_COUNT="$(printf '%s\n' "$TRACKED_STATUS" | awk 'substr($0,1,1)!=" " { count++ } END { print count + 0 }')"
  UNSTAGED_CHANGE_COUNT="$(printf '%s\n' "$TRACKED_STATUS" | awk 'substr($0,2,1)!=" " { count++ } END { print count + 0 }')"
  UNMERGED_CHANGE_COUNT="$(printf '%s\n' "$TRACKED_STATUS" | awk 'substr($0,1,2) ~ /U/ || substr($0,1,2) ~ /AA|DD/ { count++ } END { print count + 0 }')"
  DELETED_CHANGE_COUNT="$(printf '%s\n' "$TRACKED_STATUS" | awk 'substr($0,1,2) ~ /D/ { count++ } END { print count + 0 }')"
  RENAMED_CHANGE_COUNT="$(printf '%s\n' "$TRACKED_STATUS" | awk 'substr($0,1,2) ~ /R/ { count++ } END { print count + 0 }')"
fi

cat <<REPORT
LATTICRA PRODUCTION INSTALLER RELEASE WORKTREE CLEANLINESS AUDIT
worktree_audit_status=ok
release_worktree_cleanliness_audit_present=1
release_worktree_cleanliness_audit_mode=no-effect-tracked-status-report
release_worktree_cleanliness_required_for_release_candidate=1
release_worktree_cleanliness_audit_passed=$TRACKED_WORKTREE_CLEAN
release_worktree_tracked_worktree_clean=$TRACKED_WORKTREE_CLEAN
release_worktree_tracked_dirty_count=$TRACKED_DIRTY_COUNT
release_worktree_staged_change_count=$STAGED_CHANGE_COUNT
release_worktree_unstaged_change_count=$UNSTAGED_CHANGE_COUNT
release_worktree_unmerged_change_count=$UNMERGED_CHANGE_COUNT
release_worktree_deleted_change_count=$DELETED_CHANGE_COUNT
release_worktree_renamed_change_count=$RENAMED_CHANGE_COUNT
release_worktree_untracked_ignored_for_release_cleanliness=1
release_worktree_dirty_inventory_present=1
release_worktree_dirty_inventory_mode=stdout-only-tracked-status-list
release_worktree_dirty_inventory_complete=$DIRTY_INVENTORY_COMPLETE
release_worktree_dirty_inventory_count=$TRACKED_DIRTY_COUNT
release_worktree_dirty_inventory_written=0
release_worktree_dirty_inventory_accepted=0
release_worktree_cleanliness_remediation_required=$RELEASE_WORKTREE_CLEANLINESS_REMEDIATION_REQUIRED
release_candidate_tag=$TAG
release_candidate_tag_exists=$TAG_EXISTS
release_candidate_tag_commit=$TAG_COMMIT
current_branch=$BRANCH
current_head_commit=$HEAD_COMMIT
release_candidate_head_branch=$BRANCH
release_candidate_head_commit=$HEAD_COMMIT
git_available=$GIT_AVAILABLE
git_path=$(tool_path git)
release_artifact_candidate_preflight_present=1
release_artifact_candidate_tracked_worktree_clean=$TRACKED_WORKTREE_CLEAN
release_artifact_candidate_tracked_dirty_count=$TRACKED_DIRTY_COUNT
release_artifact_candidate_preflight_passed=0
release_artifact_candidate_inputs_satisfied=0
release_artifact_promotion_gate_passed=0
release_artifact_created=0
release_artifact_evidence_written=0
release_artifact_evidence_accepted=0
production_installer_ready=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
git_add_performed=0
git_commit_performed=0
git_checkout_performed=0
git_reset_performed=0
git_clean_performed=0
tracked_file_reverted=0

[non_effects]
git_add_invoked=0
git_commit_invoked=0
git_checkout_invoked=0
git_clean_invoked=0
git_reset_invoked=0
git_revert_invoked=0
file_delete_performed=0
release_evidence_written=0
release_worktree_dirty_inventory_written=0
release_worktree_dirty_inventory_accepted=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
git_add_performed=0
git_commit_performed=0
git_checkout_performed=0
git_reset_performed=0
git_clean_performed=0
tracked_file_reverted=0
REPORT

printf '\n[tracked_dirty_inventory]\n'
if [ -n "$TRACKED_STATUS" ]; then
  printf '%s\n' "$TRACKED_STATUS" | sed 's/^/tracked_status_entry=/'
else
  printf 'tracked_status_entry=none\n'
fi

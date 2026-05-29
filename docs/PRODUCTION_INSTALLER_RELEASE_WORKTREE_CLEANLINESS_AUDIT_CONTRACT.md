# Production Installer Release Worktree Cleanliness Audit Contract

Status: no-effect release worktree cleanliness audit contract
Evidence level: 10 target, tracked worktree audit only
Scope: report tracked worktree cleanliness for a future production-installer release artifact candidate without staging, committing, cleaning, resetting, reverting, deleting files, writing release evidence, invoking build tools, or mutating the host.

## Purpose

The release-artifact candidate preflight requires the tracked worktree to be clean before a future release artifact candidate can pass.

This contract records a no-effect audit for that blocker. It measures tracked Git status only and keeps untracked files out of the release-cleanliness decision to match the current preflight boundary.

The audit also prints a stdout-only tracked dirty inventory so each blocking path can be reviewed before any separate staging, carry-forward, or cleanup decision. The inventory is not written to disk and is not accepted as release evidence by the audit.

It does not clean the worktree or alter any tracked change.

## Command

```sh
sh scripts/production-installer-release-worktree-cleanliness-audit.sh --tag v0.2.0edge
```

## Current classification

```text
release_worktree_cleanliness_audit_present=1
release_worktree_cleanliness_audit_mode=no-effect-tracked-status-report
release_worktree_cleanliness_required_for_release_candidate=1
release_worktree_cleanliness_audit_passed=0
release_worktree_tracked_worktree_clean=0
release_worktree_tracked_dirty_count=<observed>
release_worktree_staged_change_count=<observed>
release_worktree_unstaged_change_count=<observed>
release_worktree_unmerged_change_count=<observed>
release_worktree_deleted_change_count=<observed>
release_worktree_renamed_change_count=<observed>
release_worktree_untracked_ignored_for_release_cleanliness=1
release_worktree_dirty_inventory_present=1
release_worktree_dirty_inventory_mode=stdout-only-tracked-status-list
release_worktree_dirty_inventory_complete=<observed>
release_worktree_dirty_inventory_count=<observed>
release_worktree_dirty_inventory_written=0
release_worktree_dirty_inventory_accepted=0
release_worktree_cleanliness_remediation_required=<observed>
release_artifact_candidate_preflight_present=1
release_artifact_candidate_tracked_worktree_clean=0
release_artifact_candidate_tracked_dirty_count=<observed>
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
git_add_invoked=0
git_commit_invoked=0
git_checkout_invoked=0
git_clean_invoked=0
git_reset_invoked=0
git_revert_invoked=0
release_worktree_dirty_inventory_written=0
release_worktree_dirty_inventory_accepted=0
```

The stdout inventory section uses this shape:

```text
[tracked_dirty_inventory]
tracked_status_entry=<git-porcelain-status-and-path-or-none>
```

## Required source records

The audit binds the current release-candidate posture:

```text
production_installer_ready=0
release_artifact_candidate_preflight_present=1
release_artifact_candidate_tracked_worktree_clean=0
release_artifact_promotion_gate_passed=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-release-worktree-cleanliness-audit-contract.sh
```

Expected output:

```text
production_installer_release_worktree_cleanliness_audit_contract: ok
```

## Next implementation lane

```text
Resolve or intentionally carry every tracked worktree change listed in the stdout-only dirty inventory before running the release-artifact candidate preflight for promotion evidence.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This audit is not a clean worktree.

It is not a release artifact, not a commit, not a staging operation, not a reset, not a revert, not a deletion, not artifact signing, not signature verification, not release evidence acceptance, not artifact promotion, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not recovery validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not host mutation, and not production installer readiness.

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-v1-release-readiness-gate.sh [--version v1.0.0]

Reports the current no-effect v1 release readiness decision. The gate
aggregates the existing production installer, release artifact, SBOM,
transcript, lifecycle, recovery, multi-VM, Fedora, Nadia, Q-Seal, and runtime
authority blocker records. It does not create artifacts, accept evidence, sign
anything, publish anything, install anything, or mutate the host.
USAGE
}

fail() {
  printf 'latticra v1 release readiness gate: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern" 65
}

tool_available() {
  if command -v "$1" >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

normalize_fingerprint() {
  printf '%s\n' "$1" | tr -d '[:space:]' | tr 'a-f' 'A-F'
}

fingerprint_format_valid() {
  fingerprint="$(normalize_fingerprint "$1")"
  case "$fingerprint" in
    ''|none|NONE|None)
      printf '0\n'
      return
      ;;
  esac
  if printf '%s\n' "$fingerprint" | grep -Eq '^[0-9A-F]{40}$|^[0-9A-F]{64}$'; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

output_value() {
  key="$1"
  output="$2"
  printf '%s\n' "$output" | awk -F= -v key="$key" '$1 == key { print substr($0, length(key) + 2); exit }'
}

RELEASE_VERSION='v1.0.0'

while [ "$#" -gt 0 ]; do
  case "$1" in
    --version)
      [ "$#" -ge 2 ] || fail 'missing value for --version' 64
      RELEASE_VERSION="$2"
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

require_contains 'Edge edition checkpoint: `v0.3.0edge`' README.md
require_contains 'Next main edge line: `v0.4.0edge`' README.md
require_contains 'It is not a production platform' README.md
require_contains 'Production quality blocker ledger' README.md
require_contains 'production_platform_claim_allowed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'production_installer_ready=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'production_cryptography_claimed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'production_enforcement_claimed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_present=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_signature_verified=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_candidate_preflight_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md
require_contains 'sbom_evidence_candidate_valid=0' docs/status/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'transcript_evidence_candidate_valid=0' docs/status/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'lifecycle_evidence_candidate_valid=0' docs/status/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'recovery_evidence_candidate_valid=0' docs/status/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'multi_vm_evidence_candidate_valid=0' docs/status/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'fedora_production_readiness_evidence_complete=0' docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md
require_contains 'production_nadia_ready=0' docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md
require_contains 'runtime_crypto_ready=0' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'production_crypto_claim_allowed=0' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'runtime_authority_granted=0' latticra-q-seal/evidence/Q_SEAL_READINESS.md

GIT_AVAILABLE="$(tool_available git)"
TRACKED_DIRTY_COUNT='unknown'
TRACKED_WORKTREE_CLEAN=0
UNTRACKED_COUNT='unknown'
UNTRACKED_WORKTREE_CLEAN=0
V1_TAG_EXISTS=0
V1_TAG_COMMIT='missing'
if [ "$GIT_AVAILABLE" = "1" ]; then
  TRACKED_DIRTY_COUNT="$(git status --porcelain --untracked-files=no | wc -l | tr -d ' ')"
  UNTRACKED_COUNT="$(git ls-files -o --exclude-standard | wc -l | tr -d ' ')"
  if [ "$TRACKED_DIRTY_COUNT" = "0" ]; then
    TRACKED_WORKTREE_CLEAN=1
  fi
  if [ "$UNTRACKED_COUNT" = "0" ]; then
    UNTRACKED_WORKTREE_CLEAN=1
  fi
  if git rev-list -n 1 "$RELEASE_VERSION" >/dev/null 2>&1; then
    V1_TAG_EXISTS=1
    V1_TAG_COMMIT="$(git rev-list -n 1 "$RELEASE_VERSION")"
  fi
fi

RPMBUILD_AVAILABLE="$(tool_available rpmbuild)"
RPM_AVAILABLE="$(tool_available rpm)"
SIGNING_KEY_FINGERPRINT="${LATTICRA_RELEASE_SIGNING_KEY_FINGERPRINT:-none}"
SIGNING_IDENTITY_REFERENCE_FORMAT_VALID="$(fingerprint_format_valid "$SIGNING_KEY_FINGERPRINT")"
SIGNING_IDENTITY_REFERENCE_PRESENT=0
case "$SIGNING_KEY_FINGERPRINT" in
  ''|none|NONE|None)
    SIGNING_KEY_FINGERPRINT='none'
    ;;
  *)
    SIGNING_KEY_FINGERPRINT="$(normalize_fingerprint "$SIGNING_KEY_FINGERPRINT")"
    if [ "$SIGNING_IDENTITY_REFERENCE_FORMAT_VALID" = "1" ]; then
      SIGNING_IDENTITY_REFERENCE_PRESENT=1
    fi
    ;;
esac

ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT="$(
  sh scripts/production-installer-release-artifact-candidate-preflight.sh \
    --tag "$RELEASE_VERSION" \
    --signing-key-fingerprint "$SIGNING_KEY_FINGERPRINT"
)"
ARTIFACT_CANDIDATE_PREFLIGHT_PRESENT="$(output_value release_artifact_candidate_preflight_present "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_PREFLIGHT_PASSED="$(output_value release_artifact_candidate_preflight_passed "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_INPUTS_SATISFIED="$(output_value release_artifact_candidate_inputs_satisfied "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_BLOCKER_COUNT="$(output_value release_artifact_candidate_blocker_count "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_BLOCKERS="$(output_value release_artifact_candidate_blockers "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_TAG="$(output_value release_artifact_candidate_tag "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_TAG_EXISTS="$(output_value release_artifact_candidate_tag_exists "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_TAG_BLOCKED="$(output_value release_artifact_candidate_tag_blocked "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_TOOLCHAIN_BLOCKED="$(output_value release_artifact_candidate_toolchain_blocked "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_TRACKED_WORKTREE_BLOCKED="$(output_value release_artifact_candidate_tracked_worktree_blocked "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"
ARTIFACT_CANDIDATE_SIGNING_IDENTITY_REFERENCE_BLOCKED="$(output_value release_artifact_candidate_signing_identity_reference_blocked "$ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT")"

BLOCKER_COUNT=0
BLOCKERS='none'
WORKSPACE_RESOLVABLE_BLOCKER_COUNT=0
RELEASE_DECISION_BLOCKER_COUNT=0
EXTERNAL_PREREQUISITE_BLOCKER_COUNT=0
EVIDENCE_BLOCKER_COUNT=0
PRODUCT_COMPLETION_BLOCKER_COUNT=0
add_blocker() {
  blocker="$1"
  if [ "$BLOCKERS" = "none" ]; then
    BLOCKERS="$blocker"
  else
    BLOCKERS="$BLOCKERS,$blocker"
  fi
  BLOCKER_COUNT=$((BLOCKER_COUNT + 1))
}

if [ "$V1_TAG_EXISTS" != "1" ]; then
  RELEASE_DECISION_BLOCKER_COUNT=$((RELEASE_DECISION_BLOCKER_COUNT + 1))
  add_blocker 'v1_release_tag_missing_or_not_approved'
fi
PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
add_blocker 'current_edge_checkpoint_not_v1'
PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
add_blocker 'v040edge_not_current_release'
PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
add_blocker 'production_platform_claim_closed'
PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
add_blocker 'production_installer_not_ready'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'release_artifact_not_promoted'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'release_artifact_missing'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'release_artifact_signature_not_verified'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'sbom_evidence_not_accepted'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'transcript_evidence_not_accepted'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'lifecycle_evidence_not_accepted'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'recovery_evidence_not_accepted'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'multi_vm_evidence_not_accepted'
PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
add_blocker 'fedora_production_readiness_incomplete'
PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
add_blocker 'nadia_production_readiness_blocked'
PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
add_blocker 'q_seal_runtime_crypto_blocked'
PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
add_blocker 'runtime_authority_closed'

if [ "$RPMBUILD_AVAILABLE" != "1" ]; then
  EXTERNAL_PREREQUISITE_BLOCKER_COUNT=$((EXTERNAL_PREREQUISITE_BLOCKER_COUNT + 1))
  add_blocker 'rpmbuild_toolchain_missing'
fi
if [ "$RPM_AVAILABLE" != "1" ]; then
  EXTERNAL_PREREQUISITE_BLOCKER_COUNT=$((EXTERNAL_PREREQUISITE_BLOCKER_COUNT + 1))
  add_blocker 'rpm_toolchain_missing'
fi
if [ "$SIGNING_IDENTITY_REFERENCE_PRESENT" != "1" ] ||
   [ "$SIGNING_IDENTITY_REFERENCE_FORMAT_VALID" != "1" ]; then
  EXTERNAL_PREREQUISITE_BLOCKER_COUNT=$((EXTERNAL_PREREQUISITE_BLOCKER_COUNT + 1))
  add_blocker 'release_signing_identity_reference_missing_or_invalid'
fi
if [ "$TRACKED_WORKTREE_CLEAN" != "1" ]; then
  WORKSPACE_RESOLVABLE_BLOCKER_COUNT=$((WORKSPACE_RESOLVABLE_BLOCKER_COUNT + 1))
  add_blocker 'tracked_worktree_dirty_or_unknown'
fi
if [ "$UNTRACKED_WORKTREE_CLEAN" != "1" ]; then
  WORKSPACE_RESOLVABLE_BLOCKER_COUNT=$((WORKSPACE_RESOLVABLE_BLOCKER_COUNT + 1))
  add_blocker 'untracked_worktree_dirty_or_unknown'
fi

RELEASE_NEXT_WORKSPACE_ACTION='none-current-workspace-cleanliness-gate-clear'
if [ "$WORKSPACE_RESOLVABLE_BLOCKER_COUNT" != "0" ]; then
  RELEASE_NEXT_WORKSPACE_ACTION='review-stage-commit-current-release-readiness-work'
fi

REQUIRED_GATE_COUNT=22
SATISFIED_GATE_COUNT=$((REQUIRED_GATE_COUNT - BLOCKER_COUNT))
if [ "$SATISFIED_GATE_COUNT" -lt 0 ]; then
  SATISFIED_GATE_COUNT=0
fi

cat <<REPORT
LATTICRA V1 RELEASE READINESS GATE
v1_release_readiness_gate_status=ok
v1_release_readiness_gate_present=1
v1_release_readiness_gate_mode=no-effect-release-readiness-aggregation
v1_release_readiness_gate_version=$RELEASE_VERSION
v1_release_readiness_gate_passed=0
v1_release_readiness_blocked=1
v1_release_readiness_decision=blocked-existing-production-evidence-gates-open
v1_release_required_gate_count=$REQUIRED_GATE_COUNT
v1_release_satisfied_gate_count=$SATISFIED_GATE_COUNT
v1_release_blocker_count=$BLOCKER_COUNT
v1_release_blockers=$BLOCKERS
v1_release_workspace_resolvable_blocker_count=$WORKSPACE_RESOLVABLE_BLOCKER_COUNT
v1_release_release_decision_blocker_count=$RELEASE_DECISION_BLOCKER_COUNT
v1_release_external_prerequisite_blocker_count=$EXTERNAL_PREREQUISITE_BLOCKER_COUNT
v1_release_evidence_blocker_count=$EVIDENCE_BLOCKER_COUNT
v1_release_product_completion_blocker_count=$PRODUCT_COMPLETION_BLOCKER_COUNT
v1_release_next_workspace_action=$RELEASE_NEXT_WORKSPACE_ACTION
current_edge_checkpoint=v0.3.0edge
next_main_edge_line=v0.4.0edge
v1_tag=$RELEASE_VERSION
v1_tag_exists=$V1_TAG_EXISTS
v1_tag_commit=$V1_TAG_COMMIT
v1_release_candidate_declared=0
v1_public_release_allowed=0
production_platform_claim_allowed=0
production_release_ready=0
production_installer_ready=0
production_ai_claimed=0
production_cryptography_claimed=0
production_enforcement_claimed=0
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_passed=$ARTIFACT_CANDIDATE_PREFLIGHT_PASSED
release_artifact_candidate_inputs_satisfied=$ARTIFACT_CANDIDATE_INPUTS_SATISFIED
release_artifact_candidate_blocker_count=$ARTIFACT_CANDIDATE_BLOCKER_COUNT
release_artifact_candidate_blockers=$ARTIFACT_CANDIDATE_BLOCKERS
release_artifact_candidate_tag=$ARTIFACT_CANDIDATE_TAG
release_artifact_candidate_tag_exists=$ARTIFACT_CANDIDATE_TAG_EXISTS
release_artifact_candidate_tag_blocked=$ARTIFACT_CANDIDATE_TAG_BLOCKED
release_artifact_candidate_toolchain_blocked=$ARTIFACT_CANDIDATE_TOOLCHAIN_BLOCKED
release_artifact_candidate_tracked_worktree_blocked=$ARTIFACT_CANDIDATE_TRACKED_WORKTREE_BLOCKED
release_artifact_candidate_signing_identity_reference_blocked=$ARTIFACT_CANDIDATE_SIGNING_IDENTITY_REFERENCE_BLOCKED
release_artifact_promotion_gate_present=1
release_artifact_promotion_gate_passed=0
release_artifact_present=0
release_artifact_built_from_tag=0
release_artifact_reproducible=0
release_artifact_sha256_recorded=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
rpmbuild_available=$RPMBUILD_AVAILABLE
rpm_available=$RPM_AVAILABLE
release_signing_identity_reference_present=$SIGNING_IDENTITY_REFERENCE_PRESENT
release_signing_identity_reference_format_valid=$SIGNING_IDENTITY_REFERENCE_FORMAT_VALID
release_artifact_evidence_accepted=0
sbom_evidence_candidate_valid=0
sbom_evidence_accepted_by_intake_validator=0
transcript_evidence_candidate_valid=0
transcript_evidence_accepted_by_intake_validator=0
lifecycle_evidence_candidate_valid=0
lifecycle_evidence_accepted_by_intake_validator=0
recovery_evidence_candidate_valid=0
recovery_evidence_accepted_by_intake_validator=0
multi_vm_evidence_candidate_valid=0
multi_vm_evidence_accepted_by_intake_validator=0
fedora_production_readiness_evidence_complete=0
fedora_production_readiness_promotion_allowed=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
production_nadia_ready=0
nadia_public_release_allowed=0
q_seal_readiness_profile_present=1
q_seal_runtime_crypto_ready=0
q_seal_production_crypto_claim_allowed=0
runtime_authority_granted=0
git_available=$GIT_AVAILABLE
tracked_worktree_clean=$TRACKED_WORKTREE_CLEAN
tracked_worktree_dirty_count=$TRACKED_DIRTY_COUNT
untracked_worktree_clean=$UNTRACKED_WORKTREE_CLEAN
untracked_worktree_dirty_count=$UNTRACKED_COUNT

[non_effects]
release_artifact_created=0
source_archive_created=0
signature_created=0
artifact_signed=0
signature_verified=0
sbom_generated=0
evidence_written=0
evidence_accepted=0
install_performed=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
git_add_performed=0
git_commit_performed=0
git_tag_performed=0
git_push_performed=0
REPORT

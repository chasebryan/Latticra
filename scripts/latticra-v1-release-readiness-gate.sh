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

status_value() {
  key="$1"
  file="$2"
  value="$(awk -F= -v key="$key" '$1 == key { print substr($0, length(key) + 2); exit }' "$file")"
  [ -n "$value" ] || fail "missing status value in $file: $key" 65
  printf '%s\n' "$value"
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
require_contains 'production_platform_claim_allowed=' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'production_installer_ready=' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'production_cryptography_claimed=' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'production_enforcement_claimed=' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_present=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_signature_verified=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_candidate_preflight_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md
require_contains 'v1_product_completion_blocker_audit_present=1' docs/LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_CONTRACT.md
require_contains 'v1_product_completion_blocker_audit_present=1' docs/status/LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_STATUS.md
require_contains 'release_artifact_evidence_intake_validator_present=1' docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'sbom_evidence_intake_validator_present=1' docs/status/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'transcript_evidence_intake_validator_present=1' docs/status/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'lifecycle_evidence_intake_validator_present=1' docs/status/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'recovery_evidence_intake_validator_present=1' docs/status/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'multi_vm_evidence_intake_validator_present=1' docs/status/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
require_contains 'fedora_production_readiness_evidence_complete=' docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md
require_contains 'production_nadia_ready=' docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md
require_contains 'runtime_crypto_ready=' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'production_crypto_claim_allowed=' latticra-q-seal/evidence/Q_SEAL_READINESS.md
require_contains 'runtime_authority_granted=' latticra-q-seal/evidence/Q_SEAL_READINESS.md

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

PRODUCT_BLOCKER_AUDIT_OUTPUT="$(
  sh scripts/latticra-v1-product-completion-blocker-audit.sh
)"
PRODUCT_BLOCKER_AUDIT_PRESENT="$(output_value v1_product_completion_blocker_audit_present "$PRODUCT_BLOCKER_AUDIT_OUTPUT")"
PRODUCT_BLOCKER_AUDIT_PASSED="$(output_value v1_product_completion_blocker_audit_passed "$PRODUCT_BLOCKER_AUDIT_OUTPUT")"
PRODUCT_BLOCKER_DETAIL_COUNT="$(output_value v1_product_completion_detail_blocker_count "$PRODUCT_BLOCKER_AUDIT_OUTPUT")"
PRODUCT_BLOCKER_DETAILS="$(output_value v1_product_completion_detail_blockers "$PRODUCT_BLOCKER_AUDIT_OUTPUT")"

RELEASE_ARTIFACT_CANDIDATE_VALID="$(status_value release_artifact_candidate_valid docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
RELEASE_ARTIFACT_EVIDENCE_ACCEPTED="$(status_value release_artifact_evidence_accepted_by_intake_validator docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
SBOM_EVIDENCE_CANDIDATE_VALID="$(status_value sbom_evidence_candidate_valid docs/status/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
SBOM_EVIDENCE_ACCEPTED="$(status_value sbom_evidence_accepted_by_intake_validator docs/status/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
TRANSCRIPT_EVIDENCE_CANDIDATE_VALID="$(status_value transcript_evidence_candidate_valid docs/status/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
TRANSCRIPT_EVIDENCE_ACCEPTED="$(status_value transcript_evidence_accepted_by_intake_validator docs/status/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
LIFECYCLE_EVIDENCE_CANDIDATE_VALID="$(status_value lifecycle_evidence_candidate_valid docs/status/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
LIFECYCLE_EVIDENCE_ACCEPTED="$(status_value lifecycle_evidence_accepted_by_intake_validator docs/status/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
RECOVERY_EVIDENCE_CANDIDATE_VALID="$(status_value recovery_evidence_candidate_valid docs/status/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
RECOVERY_EVIDENCE_ACCEPTED="$(status_value recovery_evidence_accepted_by_intake_validator docs/status/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
MULTI_VM_EVIDENCE_CANDIDATE_VALID="$(status_value multi_vm_evidence_candidate_valid docs/status/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
MULTI_VM_EVIDENCE_ACCEPTED="$(status_value multi_vm_evidence_accepted_by_intake_validator docs/status/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md)"
PRODUCTION_PLATFORM_CLAIM_ALLOWED="$(status_value production_platform_claim_allowed docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md)"
PRODUCTION_RELEASE_READY=0
PRODUCTION_INSTALLER_READY="$(status_value production_installer_ready docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md)"
PRODUCTION_AI_CLAIMED="$(status_value production_ai_claimed docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md)"
PRODUCTION_CRYPTOGRAPHY_CLAIMED="$(status_value production_cryptography_claimed docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md)"
PRODUCTION_ENFORCEMENT_CLAIMED="$(status_value production_enforcement_claimed docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md)"
FEDORA_PRODUCTION_READINESS_EVIDENCE_COMPLETE="$(status_value fedora_production_readiness_evidence_complete docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md)"
FEDORA_PRODUCTION_READINESS_PROMOTION_ALLOWED="$(status_value fedora_production_readiness_promotion_allowed docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md)"
FEDORA_DISTRIBUTION_READY="$(status_value fedora_distribution_ready docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md)"
FEDORA_APPROVAL_CLAIMED="$(status_value fedora_approval_claimed docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md)"
DAILY_DRIVER_INSTALL_READY="$(status_value daily_driver_install_ready docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md)"
IMMUTABLE_FEDORA_READY="$(status_value immutable_fedora_ready docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md)"
PRODUCTION_NADIA_READY="$(status_value production_nadia_ready docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md)"
NADIA_PUBLIC_RELEASE_ALLOWED="$(status_value public_release_allowed docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md)"
Q_SEAL_READINESS_PROFILE_PRESENT="$(status_value q_seal_readiness_profile_present latticra-q-seal/evidence/Q_SEAL_READINESS.md)"
Q_SEAL_RUNTIME_CRYPTO_READY="$(status_value runtime_crypto_ready latticra-q-seal/evidence/Q_SEAL_READINESS.md)"
Q_SEAL_PRODUCTION_CRYPTO_CLAIM_ALLOWED="$(status_value production_crypto_claim_allowed latticra-q-seal/evidence/Q_SEAL_READINESS.md)"
RUNTIME_AUTHORITY_GRANTED="$(status_value runtime_authority_granted latticra-q-seal/evidence/Q_SEAL_READINESS.md)"

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
if [ "$PRODUCTION_PLATFORM_CLAIM_ALLOWED" != "1" ]; then
  PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
  add_blocker 'production_platform_claim_closed'
fi
if [ "$PRODUCTION_INSTALLER_READY" != "1" ]; then
  PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
  add_blocker 'production_installer_not_ready'
fi
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'release_artifact_not_promoted'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'release_artifact_missing'
EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
add_blocker 'release_artifact_signature_not_verified'
if [ "$RELEASE_ARTIFACT_EVIDENCE_ACCEPTED" != "1" ]; then
  EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
  add_blocker 'release_artifact_evidence_not_accepted'
fi
if [ "$SBOM_EVIDENCE_ACCEPTED" != "1" ]; then
  EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
  add_blocker 'sbom_evidence_not_accepted'
fi
if [ "$TRANSCRIPT_EVIDENCE_ACCEPTED" != "1" ]; then
  EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
  add_blocker 'transcript_evidence_not_accepted'
fi
if [ "$LIFECYCLE_EVIDENCE_ACCEPTED" != "1" ]; then
  EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
  add_blocker 'lifecycle_evidence_not_accepted'
fi
if [ "$RECOVERY_EVIDENCE_ACCEPTED" != "1" ]; then
  EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
  add_blocker 'recovery_evidence_not_accepted'
fi
if [ "$MULTI_VM_EVIDENCE_ACCEPTED" != "1" ]; then
  EVIDENCE_BLOCKER_COUNT=$((EVIDENCE_BLOCKER_COUNT + 1))
  add_blocker 'multi_vm_evidence_not_accepted'
fi
if [ "$FEDORA_PRODUCTION_READINESS_EVIDENCE_COMPLETE" != "1" ] ||
   [ "$FEDORA_PRODUCTION_READINESS_PROMOTION_ALLOWED" != "1" ] ||
   [ "$FEDORA_DISTRIBUTION_READY" != "1" ]; then
  PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
  add_blocker 'fedora_production_readiness_incomplete'
fi
if [ "$PRODUCTION_NADIA_READY" != "1" ] ||
   [ "$NADIA_PUBLIC_RELEASE_ALLOWED" != "1" ]; then
  PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
  add_blocker 'nadia_production_readiness_blocked'
fi
if [ "$Q_SEAL_RUNTIME_CRYPTO_READY" != "1" ] ||
   [ "$Q_SEAL_PRODUCTION_CRYPTO_CLAIM_ALLOWED" != "1" ]; then
  PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
  add_blocker 'q_seal_runtime_crypto_blocked'
fi
if [ "$RUNTIME_AUTHORITY_GRANTED" != "1" ]; then
  PRODUCT_COMPLETION_BLOCKER_COUNT=$((PRODUCT_COMPLETION_BLOCKER_COUNT + 1))
  add_blocker 'runtime_authority_closed'
fi

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

REQUIRED_GATE_COUNT=23
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
v1_product_completion_blocker_audit_present=$PRODUCT_BLOCKER_AUDIT_PRESENT
v1_product_completion_blocker_audit_passed=$PRODUCT_BLOCKER_AUDIT_PASSED
v1_product_completion_detail_blocker_count=$PRODUCT_BLOCKER_DETAIL_COUNT
v1_product_completion_detail_blockers=$PRODUCT_BLOCKER_DETAILS
current_edge_checkpoint=v0.3.0edge
next_main_edge_line=v0.4.0edge
v1_tag=$RELEASE_VERSION
v1_tag_exists=$V1_TAG_EXISTS
v1_tag_commit=$V1_TAG_COMMIT
v1_release_candidate_declared=0
v1_public_release_allowed=0
production_platform_claim_allowed=$PRODUCTION_PLATFORM_CLAIM_ALLOWED
production_release_ready=$PRODUCTION_RELEASE_READY
production_installer_ready=$PRODUCTION_INSTALLER_READY
production_ai_claimed=$PRODUCTION_AI_CLAIMED
production_cryptography_claimed=$PRODUCTION_CRYPTOGRAPHY_CLAIMED
production_enforcement_claimed=$PRODUCTION_ENFORCEMENT_CLAIMED
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
release_artifact_candidate_valid=$RELEASE_ARTIFACT_CANDIDATE_VALID
release_artifact_evidence_accepted=$RELEASE_ARTIFACT_EVIDENCE_ACCEPTED
release_artifact_evidence_accepted_by_intake_validator=$RELEASE_ARTIFACT_EVIDENCE_ACCEPTED
sbom_evidence_candidate_valid=$SBOM_EVIDENCE_CANDIDATE_VALID
sbom_evidence_accepted_by_intake_validator=$SBOM_EVIDENCE_ACCEPTED
transcript_evidence_candidate_valid=$TRANSCRIPT_EVIDENCE_CANDIDATE_VALID
transcript_evidence_accepted_by_intake_validator=$TRANSCRIPT_EVIDENCE_ACCEPTED
lifecycle_evidence_candidate_valid=$LIFECYCLE_EVIDENCE_CANDIDATE_VALID
lifecycle_evidence_accepted_by_intake_validator=$LIFECYCLE_EVIDENCE_ACCEPTED
recovery_evidence_candidate_valid=$RECOVERY_EVIDENCE_CANDIDATE_VALID
recovery_evidence_accepted_by_intake_validator=$RECOVERY_EVIDENCE_ACCEPTED
multi_vm_evidence_candidate_valid=$MULTI_VM_EVIDENCE_CANDIDATE_VALID
multi_vm_evidence_accepted_by_intake_validator=$MULTI_VM_EVIDENCE_ACCEPTED
fedora_production_readiness_evidence_complete=$FEDORA_PRODUCTION_READINESS_EVIDENCE_COMPLETE
fedora_production_readiness_promotion_allowed=$FEDORA_PRODUCTION_READINESS_PROMOTION_ALLOWED
fedora_distribution_ready=$FEDORA_DISTRIBUTION_READY
fedora_approval_claimed=$FEDORA_APPROVAL_CLAIMED
daily_driver_install_ready=$DAILY_DRIVER_INSTALL_READY
immutable_fedora_ready=$IMMUTABLE_FEDORA_READY
production_nadia_ready=$PRODUCTION_NADIA_READY
nadia_public_release_allowed=$NADIA_PUBLIC_RELEASE_ALLOWED
q_seal_readiness_profile_present=$Q_SEAL_READINESS_PROFILE_PRESENT
q_seal_runtime_crypto_ready=$Q_SEAL_RUNTIME_CRYPTO_READY
q_seal_production_crypto_claim_allowed=$Q_SEAL_PRODUCTION_CRYPTO_CLAIM_ALLOWED
runtime_authority_granted=$RUNTIME_AUTHORITY_GRANTED
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

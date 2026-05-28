#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-release-artifact-candidate-preflight.sh \
    [--tag <tag>] \
    [--artifact-path <path>] \
    [--artifact <path>] \
    [--signing-key-fingerprint <fingerprint-or-none>]

Reports local readiness for creating a future tagged production-installer
release artifact candidate. It checks tag visibility, tracked worktree
cleanliness, local build/signing/checksum tool visibility, and whether an
explicit signing identity reference was supplied. It does not build, sign,
verify, publish, install, invoke a package manager, or mutate the host.
USAGE
}

fail() {
  printf 'production installer release artifact candidate preflight: %s\n' "$1" >&2
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

sha256_tool_available() {
  if command -v sha256sum >/dev/null 2>&1 || command -v shasum >/dev/null 2>&1; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

sha256_tool_path() {
  if command -v sha256sum >/dev/null 2>&1; then
    command -v sha256sum
  elif command -v shasum >/dev/null 2>&1; then
    command -v shasum
  else
    printf 'missing\n'
  fi
}

artifact_parent_path() {
  case "$1" in
    */*)
      parent="${1%/*}"
      if [ -n "$parent" ]; then
        printf '%s\n' "$parent"
      else
        printf '/\n'
      fi
      ;;
    *)
      printf '.\n'
      ;;
  esac
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern" 65
}

TAG='v0.2.0edge'
ARTIFACT_PATH='artifacts/release/latticra-production-installer.rpm'
SIGNING_KEY_FINGERPRINT="${LATTICRA_RELEASE_SIGNING_KEY_FINGERPRINT:-none}"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --tag)
      [ "$#" -ge 2 ] || fail 'missing value for --tag' 64
      TAG="$2"
      shift 2
      ;;
    --artifact-path)
      [ "$#" -ge 2 ] || fail 'missing value for --artifact-path' 64
      ARTIFACT_PATH="$2"
      shift 2
      ;;
    --artifact)
      [ "$#" -ge 2 ] || fail 'missing value for --artifact' 64
      ARTIFACT_PATH="$2"
      shift 2
      ;;
    --signing-key-fingerprint)
      [ "$#" -ge 2 ] || fail 'missing value for --signing-key-fingerprint' 64
      SIGNING_KEY_FINGERPRINT="$2"
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
require_contains 'release_artifact_promotion_gate_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_built_from_tag=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_signature_verified=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'Status: no-effect release-artifact promotion gate contract' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_contains 'Status: no-effect release-artifact evidence intake validator contract' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'Production quality blocker ledger' README.md

GIT_AVAILABLE="$(tool_available git)"
TAR_AVAILABLE="$(tool_available tar)"
GZIP_AVAILABLE="$(tool_available gzip)"
RPMBUILD_AVAILABLE="$(tool_available rpmbuild)"
RPM_AVAILABLE="$(tool_available rpm)"
GPG_AVAILABLE="$(tool_available gpg)"
SHA256_TOOL_AVAILABLE="$(sha256_tool_available)"
ARTIFACT_PARENT_DIR="$(artifact_parent_path "$ARTIFACT_PATH")"
ARTIFACT_PARENT_DIR_EXISTS=0
if [ -d "$ARTIFACT_PARENT_DIR" ]; then
  ARTIFACT_PARENT_DIR_EXISTS=1
fi

TAG_EXISTS=0
TAG_COMMIT='missing'
if [ "$GIT_AVAILABLE" = "1" ] && git rev-list -n 1 "$TAG" >/dev/null 2>&1; then
  TAG_EXISTS=1
  TAG_COMMIT="$(git rev-list -n 1 "$TAG")"
fi

TRACKED_DIRTY_COUNT=0
TRACKED_WORKTREE_CLEAN=0
if [ "$GIT_AVAILABLE" = "1" ]; then
  TRACKED_DIRTY_COUNT="$(git status --porcelain --untracked-files=no | wc -l | tr -d ' ')"
  if [ "$TRACKED_DIRTY_COUNT" = "0" ]; then
    TRACKED_WORKTREE_CLEAN=1
  fi
fi

SIGNING_IDENTITY_REFERENCE_PRESENT=0
case "$SIGNING_KEY_FINGERPRINT" in
  ''|none|NONE|None)
    SIGNING_KEY_FINGERPRINT='none'
    ;;
  *)
    SIGNING_IDENTITY_REFERENCE_PRESENT=1
    ;;
esac

RELEASE_ARTIFACT_CANDIDATE_INPUTS_SATISFIED=0
if [ "$TAG_EXISTS" = "1" ] &&
   [ "$TRACKED_WORKTREE_CLEAN" = "1" ] &&
   [ "$GIT_AVAILABLE" = "1" ] &&
   [ "$TAR_AVAILABLE" = "1" ] &&
   [ "$GZIP_AVAILABLE" = "1" ] &&
   [ "$RPMBUILD_AVAILABLE" = "1" ] &&
   [ "$RPM_AVAILABLE" = "1" ] &&
   [ "$GPG_AVAILABLE" = "1" ] &&
   [ "$SHA256_TOOL_AVAILABLE" = "1" ] &&
   [ "$SIGNING_IDENTITY_REFERENCE_PRESENT" = "1" ]; then
  RELEASE_ARTIFACT_CANDIDATE_INPUTS_SATISFIED=1
fi

cat <<REPORT
LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT CANDIDATE PREFLIGHT
preflight_status=ok
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness
release_artifact_candidate_preflight_no_effect=1
release_artifact_candidate_preflight_passed=$RELEASE_ARTIFACT_CANDIDATE_INPUTS_SATISFIED
release_artifact_candidate_inputs_satisfied=$RELEASE_ARTIFACT_CANDIDATE_INPUTS_SATISFIED
release_artifact_candidate_tag=$TAG
release_artifact_candidate_tag_exists=$TAG_EXISTS
release_artifact_candidate_tag_available=$TAG_EXISTS
release_artifact_candidate_tag_commit=$TAG_COMMIT
release_artifact_candidate_path=$ARTIFACT_PATH
release_artifact_candidate_artifact_path=$ARTIFACT_PATH
release_artifact_candidate_parent_dir=$ARTIFACT_PARENT_DIR
release_artifact_candidate_parent_dir_exists=$ARTIFACT_PARENT_DIR_EXISTS
release_artifact_candidate_tracked_worktree_clean=$TRACKED_WORKTREE_CLEAN
release_artifact_candidate_tracked_dirty_count=$TRACKED_DIRTY_COUNT
tracked_worktree_clean=$TRACKED_WORKTREE_CLEAN
tracked_worktree_dirty_count=$TRACKED_DIRTY_COUNT
git_available=$GIT_AVAILABLE
git_path=$(tool_path git)
tar_available=$TAR_AVAILABLE
tar_path=$(tool_path tar)
gzip_available=$GZIP_AVAILABLE
gzip_path=$(tool_path gzip)
rpmbuild_available=$RPMBUILD_AVAILABLE
rpmbuild_path=$(tool_path rpmbuild)
release_artifact_build_tool_available=$RPMBUILD_AVAILABLE
rpm_available=$RPM_AVAILABLE
rpm_path=$(tool_path rpm)
release_artifact_query_tool_available=$RPM_AVAILABLE
gpg_available=$GPG_AVAILABLE
gpg_path=$(tool_path gpg)
sha256_tool_available=$SHA256_TOOL_AVAILABLE
sha256_tool_path=$(sha256_tool_path)
signing_identity_reference_present=$SIGNING_IDENTITY_REFERENCE_PRESENT
signing_identity_reference=$SIGNING_KEY_FINGERPRINT
release_artifact_present=0
release_artifact_built_from_tag=0
release_artifact_reproducible=0
release_artifact_sha256_recorded=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
release_public_key_documented=0
signature_verification_documented=0
artifact_integrity_reviewed=0
checksum_recorded=0
release_artifact_evidence_intake_validator_present=1
release_artifact_evidence_accepted=0
release_artifact_evidence_written=0
release_artifact_evidence_accepted_by_intake_validator=0
release_artifact_evidence_written_by_intake_validator=0
release_artifact_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0

[non_effects]
source_archive_created=0
release_artifact_created=0
rpm_build_invoked=0
rpmbuild_invoked=0
rpm_invoked=0
signature_created=0
artifact_signed=0
signature_verified=0
artifact_published=0
install_performed=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT

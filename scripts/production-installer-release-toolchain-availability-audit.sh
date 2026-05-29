#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-release-toolchain-availability-audit.sh [--tag <tag>]

Reports visible command availability for a future production-installer release
artifact candidate. It does not install tools, build artifacts, sign artifacts,
verify signatures, publish, invoke package managers, use network access, or
mutate the host.
USAGE
}

fail() {
  printf 'production installer release toolchain availability audit: %s\n' "$1" >&2
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
require_contains 'release_artifact_build_tool_available=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_query_tool_available=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'rpmbuild_available=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md
require_contains 'rpm_available=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md
require_contains 'release_artifact_build_tool_available=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'release_artifact_query_tool_available=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

GIT_AVAILABLE="$(tool_available git)"
TAR_AVAILABLE="$(tool_available tar)"
GZIP_AVAILABLE="$(tool_available gzip)"
RPMBUILD_AVAILABLE="$(tool_available rpmbuild)"
RPM_AVAILABLE="$(tool_available rpm)"
GPG_AVAILABLE="$(tool_available gpg)"
SHA256_TOOL_AVAILABLE="$(sha256_tool_available)"

TAG_EXISTS=0
TAG_COMMIT='missing'
if [ "$GIT_AVAILABLE" = "1" ] && git rev-list -n 1 "$TAG" >/dev/null 2>&1; then
  TAG_EXISTS=1
  TAG_COMMIT="$(git rev-list -n 1 "$TAG")"
fi

RELEASE_TOOLCHAIN_READY=0
if [ "$GIT_AVAILABLE" = "1" ] &&
   [ "$TAR_AVAILABLE" = "1" ] &&
   [ "$GZIP_AVAILABLE" = "1" ] &&
   [ "$RPMBUILD_AVAILABLE" = "1" ] &&
   [ "$RPM_AVAILABLE" = "1" ] &&
   [ "$GPG_AVAILABLE" = "1" ] &&
   [ "$SHA256_TOOL_AVAILABLE" = "1" ]; then
  RELEASE_TOOLCHAIN_READY=1
fi

cat <<REPORT
LATTICRA PRODUCTION INSTALLER RELEASE TOOLCHAIN AVAILABILITY AUDIT
toolchain_audit_status=ok
release_toolchain_availability_audit_present=1
release_toolchain_availability_audit_mode=no-effect-command-visibility-report
release_toolchain_required_for_release_candidate=1
release_toolchain_availability_audit_passed=$RELEASE_TOOLCHAIN_READY
release_toolchain_ready=$RELEASE_TOOLCHAIN_READY
release_candidate_tag=$TAG
release_candidate_tag_exists=$TAG_EXISTS
release_candidate_tag_commit=$TAG_COMMIT
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
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_passed=0
release_artifact_candidate_inputs_satisfied=0
release_artifact_promotion_gate_passed=0
release_artifact_created=0
release_artifact_evidence_written=0
release_artifact_evidence_accepted=0
production_installer_ready=0
host_mutation_performed=0

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
REPORT

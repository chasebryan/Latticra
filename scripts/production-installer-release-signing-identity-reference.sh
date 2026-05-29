#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-release-signing-identity-reference.sh \
    [--fingerprint <40-or-64-hex-or-none>] \
    [--identity-label <label-or-none>] \
    [--public-key-path <path-or-none>]

Validates the shape of a future release signing identity reference without
listing secret keys, reading key material, signing artifacts, creating
signatures, verifying signatures, publishing artifacts, or mutating the host.
USAGE
}

fail() {
  printf 'production installer release signing identity reference: %s\n' "$1" >&2
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

reference_present() {
  fingerprint="$1"
  if [ "$(fingerprint_format_valid "$fingerprint")" = "1" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

label_present() {
  case "$1" in
    ''|none|NONE|None)
      printf '0\n'
      ;;
    *)
      printf '1\n'
      ;;
  esac
}

public_key_path_recorded() {
  case "$1" in
    ''|none|NONE|None)
      printf '0\n'
      ;;
    *)
      printf '1\n'
      ;;
  esac
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern" 65
}

FINGERPRINT="${LATTICRA_RELEASE_SIGNING_KEY_FINGERPRINT:-none}"
IDENTITY_LABEL="${LATTICRA_RELEASE_SIGNING_IDENTITY_LABEL:-none}"
PUBLIC_KEY_PATH="${LATTICRA_RELEASE_PUBLIC_KEY_PATH:-none}"

while [ "$#" -gt 0 ]; do
  case "$1" in
    --fingerprint)
      [ "$#" -ge 2 ] || fail 'missing value for --fingerprint' 64
      FINGERPRINT="$2"
      shift 2
      ;;
    --identity-label)
      [ "$#" -ge 2 ] || fail 'missing value for --identity-label' 64
      IDENTITY_LABEL="$2"
      shift 2
      ;;
    --public-key-path)
      [ "$#" -ge 2 ] || fail 'missing value for --public-key-path' 64
      PUBLIC_KEY_PATH="$2"
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
require_contains 'release_artifact_signing_identity_reference_present=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_candidate_preflight_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_staging_directory_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

NORMALIZED_FINGERPRINT="$(normalize_fingerprint "$FINGERPRINT")"
FINGERPRINT_FORMAT_VALID="$(fingerprint_format_valid "$FINGERPRINT")"
REFERENCE_PRESENT="$(reference_present "$FINGERPRINT")"
LABEL_PRESENT="$(label_present "$IDENTITY_LABEL")"
PUBLIC_KEY_PATH_RECORDED="$(public_key_path_recorded "$PUBLIC_KEY_PATH")"
GPG_AVAILABLE="$(tool_available gpg)"

cat <<REPORT
LATTICRA PRODUCTION INSTALLER RELEASE SIGNING IDENTITY REFERENCE
signing_identity_reference_status=ok
release_signing_identity_reference_validator_present=1
release_signing_identity_reference_mode=no-secret-inspection-reference-validation
release_signing_identity_reference_no_effect=1
release_signing_identity_reference_valid=$REFERENCE_PRESENT
release_signing_identity_reference_present=$REFERENCE_PRESENT
release_signing_identity_reference_fingerprint=$NORMALIZED_FINGERPRINT
release_signing_identity_reference_fingerprint_format_valid=$FINGERPRINT_FORMAT_VALID
release_signing_identity_reference_label_present=$LABEL_PRESENT
release_signing_identity_reference_public_key_path_recorded=$PUBLIC_KEY_PATH_RECORDED
gpg_available=$GPG_AVAILABLE
gpg_path=$(tool_path gpg)
secret_key_inspection_performed=0
secret_key_material_read=0
secret_key_material_written=0
release_artifact_signing_identity_reference_present=$REFERENCE_PRESENT
release_artifact_signing_identity_reference_format_valid=$FINGERPRINT_FORMAT_VALID
signing_performed=0
signature_created=0
signature_verified=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
release_artifact_evidence_written=0
release_artifact_evidence_accepted=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
REPORT

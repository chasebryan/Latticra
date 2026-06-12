#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer release artifact candidate preflight contract: %s\n' "$1" >&2
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
  pattern="$1"
  output="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

doc='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_STATUS.md'
script='scripts/production-installer-release-artifact-candidate-preflight.sh'
test_script='scripts/test-production-installer-release-artifact-candidate-preflight-contract.sh'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
staging_contract='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_CONTRACT.md'
worktree_audit='docs/PRODUCTION_INSTALLER_RELEASE_WORKTREE_CLEANLINESS_AUDIT_CONTRACT.md'
toolchain_audit='docs/PRODUCTION_INSTALLER_RELEASE_TOOLCHAIN_AVAILABILITY_AUDIT_CONTRACT.md'
staging_readme='artifacts/release/README.md'
promotion_gate='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md'
evidence_intake='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
workflow='.github/workflows/production-installer-release-artifact-candidate-preflight.yml'

for file in "$doc" "$status" "$script" "$test_script" "$readiness" \
  "$staging_contract" "$worktree_audit" "$toolchain_audit" "$staging_readme" "$promotion_gate" "$evidence_intake" \
  "$ledger" "$workflow" Makefile
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect release-artifact candidate preflight contract' "$doc"
require_contains 'Evidence level: 10 target, preflight evidence only' "$doc"
require_contains 'release_artifact_candidate_preflight_present=1' "$doc"
require_contains 'release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness' "$doc"
require_contains 'release_artifact_candidate_preflight_no_effect=1' "$doc"
require_contains 'release_artifact_candidate_preflight_passed=0' "$doc"
require_contains 'release_artifact_candidate_inputs_satisfied=0' "$doc"
require_contains 'release_artifact_candidate_blocker_count=<observed>' "$doc"
require_contains 'release_artifact_candidate_blockers=<observed-or-none>' "$doc"
require_contains 'release_artifact_candidate_tracked_worktree_blocked=<observed>' "$doc"
require_contains 'release_artifact_candidate_toolchain_blocked=<observed>' "$doc"
require_contains 'release_artifact_candidate_rpmbuild_blocked=<observed>' "$doc"
require_contains 'release_artifact_candidate_rpm_blocked=<observed>' "$doc"
require_contains 'release_artifact_candidate_signing_identity_reference_blocked=<observed>' "$doc"
require_contains 'release_artifact_candidate_blocker_count=0' "$doc"
require_contains 'release_artifact_candidate_blockers=none' "$doc"
require_contains 'release_artifact_candidate_tag_exists=<observed>' "$doc"
require_contains 'release_worktree_cleanliness_audit_present=1' "$doc"
require_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$doc"
require_contains 'release_artifact_candidate_tracked_worktree_clean=<observed>' "$doc"
require_contains 'release_worktree_tracked_worktree_clean=<observed>' "$doc"
require_contains 'release_worktree_tracked_dirty_count=<observed>' "$doc"
require_contains 'release_toolchain_availability_audit_present=1' "$doc"
require_contains 'release_toolchain_required_for_release_candidate=1' "$doc"
require_contains 'release_toolchain_ready=<observed>' "$doc"
require_contains 'release_artifact_build_tool_available=<observed>' "$doc"
require_contains 'release_artifact_query_tool_available=<observed>' "$doc"
require_contains 'release_artifact_candidate_parent_dir_exists=1' "$doc"
require_contains 'release_signing_identity_reference_validator_present=1' "$doc"
require_contains 'signing_identity_reference_format_valid=0' "$doc"
require_contains 'release_artifact_signing_identity_reference_format_valid=0' "$doc"
require_contains 'release_artifact_evidence_accepted=0' "$doc"
require_contains 'release_artifact_evidence_written=0' "$doc"
require_contains 'release_artifact_present=0' "$doc"
require_contains 'release_artifact_built_from_tag=0' "$doc"
require_contains 'release_artifact_signature_verified=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-release-artifact-candidate-preflight.sh \' "$doc"
require_contains 'sh scripts/test-production-installer-release-artifact-candidate-preflight-contract.sh' "$doc"

require_contains 'Status: preflight/status alignment' "$status"
require_contains 'release_artifact_candidate_preflight_present=1' "$status"
require_contains 'release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness' "$status"
require_contains 'release_artifact_candidate_preflight_no_effect=1' "$status"
require_contains 'release_artifact_candidate_preflight_passed=0' "$status"
require_contains 'release_artifact_candidate_inputs_satisfied=0' "$status"
require_contains 'release_artifact_candidate_blocker_count=<observed>' "$status"
require_contains 'release_artifact_candidate_blockers=<observed-or-none>' "$status"
require_contains 'release_artifact_candidate_tracked_worktree_blocked=<observed>' "$status"
require_contains 'release_artifact_candidate_toolchain_blocked=<observed>' "$status"
require_contains 'release_artifact_candidate_rpmbuild_blocked=<observed>' "$status"
require_contains 'release_artifact_candidate_rpm_blocked=<observed>' "$status"
require_contains 'release_artifact_candidate_signing_identity_reference_blocked=<observed>' "$status"
require_contains 'release_artifact_candidate_tag_exists=<observed>' "$status"
require_contains 'release_artifact_candidate_parent_dir_exists=1' "$status"
require_contains 'release_worktree_cleanliness_audit_present=1' "$status"
require_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$status"
require_contains 'release_artifact_candidate_tracked_worktree_clean=<observed>' "$status"
require_contains 'release_worktree_tracked_worktree_clean=<observed>' "$status"
require_contains 'release_worktree_tracked_dirty_count=<observed>' "$status"
require_contains 'release_toolchain_availability_audit_present=1' "$status"
require_contains 'release_toolchain_required_for_release_candidate=1' "$status"
require_contains 'release_toolchain_ready=<observed>' "$status"
require_contains 'release_artifact_build_tool_available=<observed>' "$status"
require_contains 'release_artifact_query_tool_available=<observed>' "$status"
require_contains 'signing_identity_reference_present=0' "$status"
require_contains 'signing_identity_reference_format_valid=0' "$status"
require_contains 'release_signing_identity_reference_validator_present=1' "$status"
require_contains 'release_artifact_signing_identity_reference_format_valid=0' "$status"
require_contains 'source_archive_created=0' "$status"
require_contains 'release_artifact_created=0' "$status"
require_contains 'rpm_build_invoked=0' "$status"
require_contains 'rpmbuild_invoked=0' "$status"
require_contains 'rpm_invoked=0' "$status"
require_contains 'signature_created=0' "$status"
require_contains 'artifact_signed=0' "$status"
require_contains 'signature_verified=0' "$status"
require_contains 'artifact_published=0' "$status"
require_contains 'package_manager_invoked=0' "$status"
require_contains 'network_allowed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"

require_contains 'production_installer_ready=0' "$readiness"
require_contains 'release_artifact_promotion_gate_present=1' "$readiness"
require_contains 'release_artifact_promotion_gate_passed=0' "$readiness"
require_contains 'release_artifact_candidate_preflight_present=1' "$readiness"
require_contains 'release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness' "$readiness"
require_contains 'release_artifact_candidate_preflight_passed=0' "$readiness"
require_contains 'release_artifact_candidate_inputs_satisfied=0' "$readiness"
require_contains 'release_artifact_candidate_parent_dir_exists=1' "$readiness"
require_contains 'release_worktree_cleanliness_audit_present=1' "$readiness"
require_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$readiness"
require_contains 'release_artifact_candidate_tracked_worktree_clean=0' "$readiness"
require_contains 'release_worktree_tracked_worktree_clean=0' "$readiness"
require_contains 'release_worktree_tracked_dirty_count=<observed>' "$readiness"
require_contains 'release_toolchain_availability_audit_present=1' "$readiness"
require_contains 'release_toolchain_required_for_release_candidate=1' "$readiness"
require_contains 'release_toolchain_ready=<observed>' "$readiness"
require_contains 'release_artifact_build_tool_available=<observed>' "$readiness"
require_contains 'release_artifact_query_tool_available=<observed>' "$readiness"
require_contains 'release_signing_identity_reference_validator_present=1' "$readiness"
require_contains 'release_signing_identity_reference_valid=0' "$readiness"
require_contains 'release_signing_identity_reference_fingerprint_format_valid=0' "$readiness"
require_contains 'release_artifact_signing_identity_reference_present=0' "$readiness"
require_contains 'release_artifact_signing_identity_reference_format_valid=0' "$readiness"
require_contains 'release_artifact_staging_directory_present=1' "$staging_contract"
require_contains 'release_worktree_cleanliness_audit_present=1' "$worktree_audit"
require_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$worktree_audit"
require_contains 'release_toolchain_availability_audit_present=1' "$toolchain_audit"
require_contains 'release_toolchain_required_for_release_candidate=1' "$toolchain_audit"
require_contains 'release_artifact_candidate_parent_dir_exists=1' "$staging_readme"
require_contains 'release_artifact_evidence_intake_validator_present=1' "$readiness"
require_contains 'release_artifact_present=0' "$readiness"
require_contains 'release_artifact_built_from_tag=0' "$readiness"
require_contains 'release_artifact_signature_verified=0' "$readiness"
require_contains 'Status: no-effect release-artifact promotion gate contract' "$promotion_gate"
require_contains 'Status: no-effect release-artifact evidence intake validator contract' "$evidence_intake"
require_contains '## Installer Release Artifact Candidate Preflight' "$ledger"
require_contains 'release_artifact_candidate_preflight_present=1' "$ledger"
require_contains 'release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness' "$ledger"
require_contains 'release_artifact_candidate_preflight_passed=0' "$ledger"
require_contains 'release_artifact_candidate_inputs_satisfied=0' "$ledger"
require_contains 'release_artifact_candidate_blocker_count=<observed>' "$ledger"
require_contains 'release_artifact_candidate_blockers=<observed-or-none>' "$ledger"
require_contains 'release_artifact_candidate_tracked_worktree_blocked=<observed>' "$ledger"
require_contains 'release_artifact_candidate_toolchain_blocked=<observed>' "$ledger"
require_contains 'release_artifact_candidate_rpmbuild_blocked=<observed>' "$ledger"
require_contains 'release_artifact_candidate_rpm_blocked=<observed>' "$ledger"
require_contains 'release_artifact_candidate_signing_identity_reference_blocked=<observed>' "$ledger"
require_contains 'release_artifact_candidate_parent_dir_exists=1' "$ledger"
require_contains 'release_worktree_cleanliness_audit_present=1' "$ledger"
require_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$ledger"
require_contains 'release_toolchain_availability_audit_present=1' "$ledger"
require_contains 'release_toolchain_required_for_release_candidate=1' "$ledger"
require_contains 'release_artifact_signing_identity_reference_present=0' "$ledger"
require_contains 'release_artifact_signing_identity_reference_format_valid=0' "$ledger"
require_contains 'release_artifact_promotion_gate_passed=0' "$ledger"

require_contains 'LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT CANDIDATE PREFLIGHT' "$script"
require_contains 'release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness' "$script"
require_contains 'release_artifact_candidate_preflight_no_effect=1' "$script"
require_contains 'release_artifact_candidate_preflight_passed=$RELEASE_ARTIFACT_CANDIDATE_INPUTS_SATISFIED' "$script"
require_contains 'release_artifact_candidate_inputs_satisfied=$RELEASE_ARTIFACT_CANDIDATE_INPUTS_SATISFIED' "$script"
require_contains 'release_artifact_candidate_blocker_count=$BLOCKER_COUNT' "$script"
require_contains 'release_artifact_candidate_blockers=$BLOCKERS' "$script"
require_contains 'release_artifact_candidate_tracked_worktree_blocked=$TRACKED_WORKTREE_BLOCKED' "$script"
require_contains 'release_artifact_candidate_toolchain_blocked=$RELEASE_TOOLCHAIN_BLOCKED' "$script"
require_contains 'release_artifact_candidate_rpmbuild_blocked=$RPMBUILD_BLOCKED' "$script"
require_contains 'release_artifact_candidate_rpm_blocked=$RPM_BLOCKED' "$script"
require_contains 'release_artifact_candidate_signing_identity_reference_blocked=$SIGNING_IDENTITY_REFERENCE_BLOCKED' "$script"
require_contains "add_blocker 'rpmbuild_missing'" "$script"
require_contains "add_blocker 'rpm_missing'" "$script"
require_contains "add_blocker 'signing_identity_reference_missing_or_invalid'" "$script"
require_contains 'release_artifact_candidate_tag_exists=$TAG_EXISTS' "$script"
require_contains 'release_artifact_candidate_path=$ARTIFACT_PATH' "$script"
require_contains 'release_artifact_candidate_parent_dir=$ARTIFACT_PARENT_DIR' "$script"
require_contains 'release_artifact_candidate_parent_dir_exists=$ARTIFACT_PARENT_DIR_EXISTS' "$script"
require_contains 'release_worktree_cleanliness_audit_present=1' "$script"
require_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$script"
require_contains 'release_artifact_candidate_tracked_worktree_clean=$TRACKED_WORKTREE_CLEAN' "$script"
require_contains 'release_artifact_candidate_tracked_dirty_count=$TRACKED_DIRTY_COUNT' "$script"
require_contains 'release_worktree_tracked_worktree_clean=$TRACKED_WORKTREE_CLEAN' "$script"
require_contains 'release_worktree_tracked_dirty_count=$TRACKED_DIRTY_COUNT' "$script"
require_contains 'release_toolchain_availability_audit_present=1' "$script"
require_contains 'release_toolchain_required_for_release_candidate=1' "$script"
require_contains 'release_toolchain_ready=$RELEASE_TOOLCHAIN_READY' "$script"
require_contains 'release_artifact_build_tool_available=$RPMBUILD_AVAILABLE' "$script"
require_contains 'release_artifact_query_tool_available=$RPM_AVAILABLE' "$script"
require_contains 'signing_identity_reference_format_valid=$SIGNING_IDENTITY_REFERENCE_FORMAT_VALID' "$script"
require_contains 'checksum_recorded=0' "$script"
require_contains 'release_artifact_evidence_accepted=0' "$script"
require_contains 'release_artifact_evidence_written=0' "$script"
require_contains 'release_artifact_present=0' "$script"
require_contains 'release_artifact_built_from_tag=0' "$script"
require_contains 'release_artifact_signature_verified=0' "$script"
require_contains 'release_artifact_promotion_gate_passed=0' "$script"
require_contains 'production_installer_ready=0' "$script"
require_contains 'source_archive_created=0' "$script"
require_contains 'release_artifact_created=0' "$script"
require_contains 'rpm_build_invoked=0' "$script"
require_contains 'rpmbuild_invoked=0' "$script"
require_contains 'rpm_invoked=0' "$script"
require_contains 'signature_created=0' "$script"
require_contains 'artifact_signed=0' "$script"
require_contains 'signature_verified=0' "$script"
require_contains 'artifact_published=0' "$script"
require_contains 'package_manager_invoked=0' "$script"
require_contains 'network_allowed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"
require_not_matching '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_matching '^[[:space:]]*dnf[[:space:]]' "$script"
require_not_matching '^[[:space:]]*rpm[[:space:]]' "$script"
require_not_matching '^[[:space:]]*rpmbuild[[:space:]]' "$script"
require_not_matching '^[[:space:]]*gpg[[:space:]]' "$script"
require_not_matching '^[[:space:]]*curl[[:space:]]' "$script"
require_not_matching '^[[:space:]]*wget[[:space:]]' "$script"

require_contains 'production-installer-release-artifact-candidate-preflight-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-release-artifact-candidate-preflight-contract.sh' Makefile
require_contains 'name: Production Installer Release Artifact Candidate Preflight' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-release-artifact-candidate-preflight-contract.sh' "$workflow"
require_absent 'sh scripts/production-installer-release-artifact-candidate-preflight.sh' "$workflow"

output="$(sh "$script" \
  --tag v0.2.0edge \
  --artifact-path artifacts/release/latticra-production-installer.rpm \
  --signing-key-fingerprint none)"
require_output_contains 'LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT CANDIDATE PREFLIGHT' "$output"
require_output_contains 'preflight_status=ok' "$output"
require_output_contains 'release_artifact_candidate_preflight_present=1' "$output"
require_output_contains 'release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness' "$output"
require_output_contains 'release_artifact_candidate_preflight_no_effect=1' "$output"
require_output_contains 'release_artifact_candidate_preflight_passed=0' "$output"
require_output_contains 'release_artifact_candidate_inputs_satisfied=0' "$output"
require_output_contains 'release_artifact_candidate_blocker_count=' "$output"
require_output_contains 'release_artifact_candidate_blockers=' "$output"
require_output_contains 'release_artifact_candidate_tracked_worktree_blocked=' "$output"
require_output_contains 'release_artifact_candidate_toolchain_blocked=' "$output"
require_output_contains 'release_artifact_candidate_rpmbuild_blocked=' "$output"
require_output_contains 'release_artifact_candidate_rpm_blocked=' "$output"
require_output_contains 'release_artifact_candidate_signing_identity_reference_blocked=1' "$output"
require_output_contains 'signing_identity_reference_missing_or_invalid' "$output"
require_output_contains 'release_artifact_candidate_tag=v0.2.0edge' "$output"
require_output_contains 'release_artifact_candidate_tag_exists=' "$output"
require_output_contains 'release_artifact_candidate_tag_commit=' "$output"
require_output_contains 'release_artifact_candidate_path=artifacts/release/latticra-production-installer.rpm' "$output"
require_output_contains 'release_artifact_candidate_artifact_path=artifacts/release/latticra-production-installer.rpm' "$output"
require_output_contains 'release_artifact_candidate_parent_dir=artifacts/release' "$output"
require_output_contains 'release_artifact_candidate_parent_dir_exists=1' "$output"
require_output_contains 'release_worktree_cleanliness_audit_present=1' "$output"
require_output_contains 'release_worktree_cleanliness_required_for_release_candidate=1' "$output"
require_output_contains 'release_artifact_candidate_tracked_worktree_clean=' "$output"
require_output_contains 'release_artifact_candidate_tracked_dirty_count=' "$output"
require_output_contains 'release_worktree_tracked_worktree_clean=' "$output"
require_output_contains 'release_worktree_tracked_dirty_count=' "$output"
require_output_contains 'release_toolchain_availability_audit_present=1' "$output"
require_output_contains 'release_toolchain_required_for_release_candidate=1' "$output"
require_output_contains 'release_toolchain_ready=' "$output"
require_output_contains 'release_artifact_build_tool_available=' "$output"
require_output_contains 'release_artifact_query_tool_available=' "$output"
require_output_contains 'release_signing_identity_reference_validator_present=1' "$output"
require_output_contains 'signing_identity_reference_present=0' "$output"
require_output_contains 'signing_identity_reference_format_valid=0' "$output"
require_output_contains 'signing_identity_reference=none' "$output"
require_output_contains 'release_artifact_present=0' "$output"
require_output_contains 'release_artifact_built_from_tag=0' "$output"
require_output_contains 'release_artifact_signature_verified=0' "$output"
require_output_contains 'release_artifact_promotion_gate_passed=0' "$output"
require_output_contains 'production_installer_ready=0' "$output"
require_output_contains 'source_archive_created=0' "$output"
require_output_contains 'release_artifact_created=0' "$output"
require_output_contains 'rpmbuild_invoked=0' "$output"
require_output_contains 'rpm_invoked=0' "$output"
require_output_contains 'artifact_signed=0' "$output"
require_output_contains 'signature_verified=0' "$output"
require_output_contains 'artifact_published=0' "$output"
require_output_contains 'install_performed=0' "$output"
require_output_contains 'package_manager_invoked=0' "$output"
require_output_contains 'network_allowed=0' "$output"
require_output_contains 'host_mutation_performed=0' "$output"

missing_tag_output="$(sh "$script" \
  --tag latticra-nonexistent-test-tag \
  --artifact artifacts/release/latticra-production-installer.rpm \
  --signing-key-fingerprint none)"
require_output_contains 'release_artifact_candidate_tag=latticra-nonexistent-test-tag' "$missing_tag_output"
require_output_contains 'release_artifact_candidate_tag_exists=0' "$missing_tag_output"
require_output_contains 'release_artifact_candidate_preflight_passed=0' "$missing_tag_output"
require_output_contains 'release_artifact_candidate_tag_blocked=1' "$missing_tag_output"
require_output_contains 'tag_missing' "$missing_tag_output"

if sh "$script" --definitely-not-a-real-option >/dev/null 2>&1; then
  fail 'unknown argument unexpectedly succeeded'
fi

printf 'production_installer_release_artifact_candidate_preflight_contract: ok\n'

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer release toolchain availability audit contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_RELEASE_TOOLCHAIN_AVAILABILITY_AUDIT_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_RELEASE_TOOLCHAIN_AVAILABILITY_AUDIT_STATUS.md'
script='scripts/production-installer-release-toolchain-availability-audit.sh'
test_script='scripts/test-production-installer-release-toolchain-availability-audit-contract.sh'
preflight_script='scripts/production-installer-release-artifact-candidate-preflight.sh'
preflight_contract='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
installer_page='docs/installer.html'
workflow='.github/workflows/production-installer-release-toolchain-availability-audit.yml'

for file in "$doc" "$status" "$script" "$test_script" "$preflight_script" \
  "$preflight_contract" "$readiness" "$ledger" "$index" "$installer_page" \
  "$workflow" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect release toolchain availability audit contract' "$doc"
require_contains 'release_toolchain_availability_audit_present=1' "$doc"
require_contains 'release_toolchain_availability_audit_mode=no-effect-command-visibility-report' "$doc"
require_contains 'release_toolchain_required_for_release_candidate=1' "$doc"
require_contains 'release_toolchain_availability_audit_passed=<observed>' "$doc"
require_contains 'release_toolchain_ready=<observed>' "$doc"
require_contains 'rpmbuild_available=<observed>' "$doc"
require_contains 'release_artifact_build_tool_available=<observed>' "$doc"
require_contains 'rpm_available=<observed>' "$doc"
require_contains 'release_artifact_query_tool_available=<observed>' "$doc"
require_contains 'gpg_available=<observed>' "$doc"
require_contains 'sha256_tool_available=<observed>' "$doc"
require_contains 'source_archive_created=0' "$doc"
require_contains 'release_artifact_created=0' "$doc"
require_contains 'rpmbuild_invoked=0' "$doc"
require_contains 'rpm_invoked=0' "$doc"
require_contains 'package_manager_invoked=0' "$doc"
require_contains 'network_allowed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-release-toolchain-availability-audit.sh' "$doc"

require_contains 'Status: toolchain-audit/status alignment' "$status"
require_contains 'release_toolchain_availability_audit_present=1' "$status"
require_contains 'release_toolchain_availability_audit_passed=<observed>' "$status"
require_contains 'release_toolchain_ready=<observed>' "$status"
require_contains 'rpmbuild_available=<observed>' "$status"
require_contains 'rpm_available=<observed>' "$status"
require_contains 'package_manager_invoked=0' "$status"
require_contains 'network_allowed=0' "$status"

require_contains 'release_toolchain_availability_audit_present=1' "$readiness"
require_contains 'release_toolchain_availability_audit_mode=no-effect-command-visibility-report' "$readiness"
require_contains 'release_toolchain_required_for_release_candidate=1' "$readiness"
require_contains 'release_toolchain_availability_audit_passed=<observed>' "$readiness"
require_contains 'release_toolchain_ready=<observed>' "$readiness"
require_contains 'rpmbuild_available=<observed>' "$readiness"
require_contains 'rpm_available=<observed>' "$readiness"
require_contains 'release_artifact_build_tool_available=<observed>' "$readiness"
require_contains 'release_artifact_query_tool_available=<observed>' "$readiness"

require_contains '## Installer Release Toolchain Availability Audit' "$ledger"
require_contains 'release_toolchain_availability_audit_present=1' "$ledger"
require_contains 'release_toolchain_availability_audit_passed=<observed>' "$ledger"
require_contains 'release_toolchain_ready=<observed>' "$ledger"
require_contains 'rpmbuild_available=<observed>' "$ledger"
require_contains 'rpm_available=<observed>' "$ledger"
require_contains 'This closes the release-toolchain-availability-audit presence gap only.' "$ledger"
require_contains 'release_toolchain_availability_audit_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_RELEASE_TOOLCHAIN_AVAILABILITY_AUDIT_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_RELEASE_TOOLCHAIN_AVAILABILITY_AUDIT_STATUS.md' README.md
require_contains 'release toolchain availability audit' "$installer_page"
require_contains 'PRODUCTION_INSTALLER_RELEASE_TOOLCHAIN_AVAILABILITY_AUDIT_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_RELEASE_TOOLCHAIN_AVAILABILITY_AUDIT_STATUS.md' "$index"

require_contains 'release_toolchain_availability_audit_present=1' "$preflight_contract"
require_contains 'release_toolchain_required_for_release_candidate=1' "$preflight_contract"
require_contains 'release_toolchain_availability_audit_present=1' "$preflight_script"
require_contains 'release_toolchain_ready=$RELEASE_TOOLCHAIN_READY' "$preflight_script"
require_contains 'production-installer-release-toolchain-availability-audit-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-release-toolchain-availability-audit-contract.sh' Makefile
require_contains 'name: Production Installer Release Toolchain Availability Audit' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-release-toolchain-availability-audit-contract.sh' "$workflow"

require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'brew ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"
require_not_matching '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_matching '^[[:space:]]*dnf[[:space:]]' "$script"
require_not_matching '^[[:space:]]*brew[[:space:]]' "$script"
require_not_matching '^[[:space:]]*rpm[[:space:]]' "$script"
require_not_matching '^[[:space:]]*rpmbuild[[:space:]]' "$script"
require_not_matching '^[[:space:]]*gpg[[:space:]]' "$script"
require_not_matching '^[[:space:]]*curl[[:space:]]' "$script"
require_not_matching '^[[:space:]]*wget[[:space:]]' "$script"

output="$(sh "$script" --tag v0.2.0edge)"
require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER RELEASE TOOLCHAIN AVAILABILITY AUDIT'
require_output_contains "$output" 'toolchain_audit_status=ok'
require_output_contains "$output" 'release_toolchain_availability_audit_present=1'
require_output_contains "$output" 'release_toolchain_availability_audit_mode=no-effect-command-visibility-report'
require_output_contains "$output" 'release_toolchain_required_for_release_candidate=1'
require_output_contains "$output" 'release_toolchain_availability_audit_passed='
require_output_contains "$output" 'release_toolchain_ready='
require_output_contains "$output" 'release_candidate_tag=v0.2.0edge'
require_output_contains "$output" 'git_available='
require_output_contains "$output" 'tar_available='
require_output_contains "$output" 'gzip_available='
require_output_contains "$output" 'rpmbuild_available='
require_output_contains "$output" 'rpm_available='
require_output_contains "$output" 'gpg_available='
require_output_contains "$output" 'sha256_tool_available='
require_output_contains "$output" 'release_artifact_build_tool_available='
require_output_contains "$output" 'release_artifact_query_tool_available='
require_output_contains "$output" 'release_artifact_candidate_preflight_present=1'
require_output_contains "$output" 'release_artifact_candidate_preflight_passed=0'
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'rpmbuild_invoked=0'
require_output_contains "$output" 'rpm_invoked=0'
require_output_contains "$output" 'package_manager_invoked=0'
require_output_contains "$output" 'network_allowed=0'
require_output_contains "$output" 'host_mutation_performed=0'

missing_tag_output="$(sh "$script" --tag latticra-nonexistent-toolchain-audit-tag)"
require_output_contains "$missing_tag_output" 'release_candidate_tag=latticra-nonexistent-toolchain-audit-tag'
require_output_contains "$missing_tag_output" 'release_candidate_tag_exists=0'
require_output_contains "$missing_tag_output" 'release_toolchain_availability_audit_present=1'

if sh "$script" --unknown >/dev/null 2>&1; then
  fail 'unknown argument unexpectedly succeeded'
fi

printf 'production_installer_release_toolchain_availability_audit_contract: ok\n'

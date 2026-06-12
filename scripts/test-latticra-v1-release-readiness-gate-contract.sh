#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra v1 release readiness gate contract: %s\n' "$1" >&2
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

require_output_contains() {
  pattern="$1"
  output="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

doc='docs/LATTICRA_V1_0_0_RELEASE_READINESS_GATE_CONTRACT.md'
status='docs/status/LATTICRA_V1_0_0_RELEASE_READINESS_GATE_STATUS.md'
gate='scripts/latticra-v1-release-readiness-gate.sh'
test_script='scripts/test-latticra-v1-release-readiness-gate-contract.sh'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
workflow='.github/workflows/latticra-v1-release-readiness-gate.yml'
nadia_status='docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md'
q_seal='latticra-q-seal/evidence/Q_SEAL_READINESS.md'
product_audit='scripts/latticra-v1-product-completion-blocker-audit.sh'
product_audit_test='scripts/test-latticra-v1-product-completion-blocker-audit-contract.sh'
product_audit_doc='docs/LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_CONTRACT.md'
product_audit_status='docs/status/LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_STATUS.md'

for file in "$doc" "$status" "$gate" "$test_script" "$ledger" "$status_index" \
  "$docs_hub" "$workflow" "$nadia_status" "$q_seal" "$product_audit" \
  "$product_audit_test" "$product_audit_doc" "$product_audit_status" README.md STATUS.md \
  docs/status/CURRENT_STATUS.md docs/project_notes/CURRENT_DIRECTION.md \
  docs/project_notes/UPCOMING_WORK.md Makefile
do
  require_file "$file"
done

sh -n "$gate"
sh -n "$test_script"
sh -n "$product_audit"

require_contains 'Status: no-effect v1.0.0 release readiness gate contract' "$doc"
require_contains 'Evidence level: release-blocker aggregation only' "$doc"
require_contains 'v1_release_readiness_gate_present=1' "$doc"
require_contains 'v1_release_readiness_gate_mode=no-effect-release-readiness-aggregation' "$doc"
require_contains 'v1_release_readiness_gate_version=v1.0.0' "$doc"
require_contains 'v1_release_readiness_gate_passed=0' "$doc"
require_contains 'v1_release_readiness_blocked=1' "$doc"
require_contains 'v1_release_readiness_decision=blocked-existing-production-evidence-gates-open' "$doc"
require_contains 'v1_release_required_gate_count=23' "$doc"
require_contains 'v1_release_blocker_count=<observed>' "$doc"
require_contains 'v1_release_tag_missing_or_not_approved' "$doc"
require_contains 'rpmbuild_toolchain_missing' "$doc"
require_contains 'rpm_toolchain_missing' "$doc"
require_contains 'release_signing_identity_reference_missing_or_invalid' "$doc"
require_contains 'v1_release_workspace_resolvable_blocker_count=<observed>' "$doc"
require_contains 'v1_release_release_decision_blocker_count=<observed>' "$doc"
require_contains 'v1_release_external_prerequisite_blocker_count=<observed>' "$doc"
require_contains 'v1_release_evidence_blocker_count=<observed>' "$doc"
require_contains 'v1_release_product_completion_blocker_count=<observed>' "$doc"
require_contains 'v1_release_next_workspace_action=<observed>' "$doc"
require_contains 'v1_product_completion_blocker_audit_present=1' "$doc"
require_contains 'v1_product_completion_blocker_audit_passed=<observed>' "$doc"
require_contains 'v1_product_completion_detail_blocker_count=<observed>' "$doc"
require_contains 'v1_product_completion_detail_blockers=<observed>' "$doc"
require_contains 'current_edge_checkpoint=v0.3.0edge' "$doc"
require_contains 'next_main_edge_line=v0.4.0edge' "$doc"
require_contains 'v1_tag=v1.0.0' "$doc"
require_contains 'v1_tag_commit=missing' "$doc"
require_contains 'production_release_ready=0' "$doc"
require_contains 'release_artifact_candidate_preflight_present=1' "$doc"
require_contains 'release_artifact_candidate_preflight_passed=<observed>' "$doc"
require_contains 'release_artifact_candidate_inputs_satisfied=<observed>' "$doc"
require_contains 'release_artifact_candidate_blocker_count=<observed>' "$doc"
require_contains 'release_artifact_candidate_blockers=<observed>' "$doc"
require_contains 'release_artifact_candidate_tag=v1.0.0' "$doc"
require_contains 'release_artifact_candidate_tag_exists=<observed>' "$doc"
require_contains 'release_artifact_candidate_tag_blocked=<observed>' "$doc"
require_contains 'release_artifact_candidate_toolchain_blocked=<observed>' "$doc"
require_contains 'release_artifact_candidate_tracked_worktree_blocked=<observed>' "$doc"
require_contains 'release_artifact_candidate_signing_identity_reference_blocked=<observed>' "$doc"
require_contains 'rpmbuild_available=<observed>' "$doc"
require_contains 'rpm_available=<observed>' "$doc"
require_contains 'release_signing_identity_reference_present=<observed>' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'release_artifact_candidate_valid=<observed>' "$doc"
require_contains 'release_artifact_evidence_accepted_by_intake_validator=<observed>' "$doc"
require_contains 'sbom_evidence_candidate_valid=<observed>' "$doc"
require_contains 'transcript_evidence_candidate_valid=<observed>' "$doc"
require_contains 'lifecycle_evidence_candidate_valid=<observed>' "$doc"
require_contains 'recovery_evidence_candidate_valid=<observed>' "$doc"
require_contains 'multi_vm_evidence_candidate_valid=<observed>' "$doc"
require_contains 'fedora_production_readiness_evidence_complete=<observed>' "$doc"
require_contains 'production_nadia_ready=<observed>' "$doc"
require_contains 'q_seal_runtime_crypto_ready=<observed>' "$doc"
require_contains 'runtime_authority_granted=<observed>' "$doc"
require_contains 'sh scripts/latticra-v1-release-readiness-gate.sh --version v1.0.0' "$doc"
require_contains 'sh scripts/test-latticra-v1-release-readiness-gate-contract.sh' "$doc"

require_contains 'Status: v1.0.0 release readiness gate/status alignment' "$status"
require_contains 'v1_release_readiness_gate_present=1' "$status"
require_contains 'v1_release_readiness_gate_passed=0' "$status"
require_contains 'v1_release_readiness_blocked=1' "$status"
require_contains 'v1_release_blocker_count=<observed>' "$status"
require_contains 'v1_release_workspace_resolvable_blocker_count=<observed>' "$status"
require_contains 'v1_release_external_prerequisite_blocker_count=<observed>' "$status"
require_contains 'v1_release_evidence_blocker_count=<observed>' "$status"
require_contains 'v1_release_product_completion_blocker_count=<observed>' "$status"
require_contains 'v1_release_next_workspace_action=<observed>' "$status"
require_contains 'v1_product_completion_blocker_audit_present=1' "$status"
require_contains 'v1_product_completion_blocker_audit_passed=<observed>' "$status"
require_contains 'v1_product_completion_detail_blocker_count=<observed>' "$status"
require_contains 'v1_product_completion_detail_blockers=<observed>' "$status"
require_contains 'v1_tag_exists=0' "$status"
require_contains 'production_release_ready=0' "$status"
require_contains 'release_artifact_candidate_preflight_present=1' "$status"
require_contains 'release_artifact_candidate_preflight_passed=<observed>' "$status"
require_contains 'release_artifact_candidate_blocker_count=<observed>' "$status"
require_contains 'release_artifact_candidate_blockers=<observed>' "$status"
require_contains 'release_artifact_candidate_tag=v1.0.0' "$status"
require_contains 'release_artifact_candidate_tag_exists=<observed>' "$status"
require_contains 'release_artifact_candidate_tag_blocked=<observed>' "$status"
require_contains 'release_artifact_candidate_signing_identity_reference_blocked=<observed>' "$status"
require_contains 'release_artifact_promotion_gate_passed=0' "$status"
require_contains 'rpmbuild_available=<observed>' "$status"
require_contains 'rpm_available=<observed>' "$status"
require_contains 'release_signing_identity_reference_present=<observed>' "$status"
require_contains 'release_artifact_candidate_valid=<observed>' "$status"
require_contains 'release_artifact_evidence_accepted_by_intake_validator=<observed>' "$status"
require_contains 'sbom_evidence_candidate_valid=<observed>' "$status"
require_contains 'sbom_evidence_accepted_by_intake_validator=<observed>' "$status"
require_contains 'transcript_evidence_accepted_by_intake_validator=<observed>' "$status"
require_contains 'lifecycle_evidence_accepted_by_intake_validator=<observed>' "$status"
require_contains 'recovery_evidence_accepted_by_intake_validator=<observed>' "$status"
require_contains 'multi_vm_evidence_accepted_by_intake_validator=<observed>' "$status"
require_contains 'multi_vm_evidence_candidate_valid=<observed>' "$status"
require_contains 'production_nadia_ready=<observed>' "$status"
require_contains 'q_seal_runtime_crypto_ready=<observed>' "$status"

require_contains 'LATTICRA V1 RELEASE READINESS GATE' "$gate"
require_contains 'v1_release_readiness_gate_mode=no-effect-release-readiness-aggregation' "$gate"
require_contains 'v1_release_readiness_gate_passed=0' "$gate"
require_contains 'v1_release_readiness_blocked=1' "$gate"
require_contains 'PRODUCTION_RELEASE_READY=0' "$gate"
require_contains 'production_release_ready=$PRODUCTION_RELEASE_READY' "$gate"
require_contains 'ARTIFACT_CANDIDATE_PREFLIGHT_OUTPUT="$(' "$gate"
require_contains '--tag "$RELEASE_VERSION"' "$gate"
require_contains 'release_artifact_candidate_preflight_passed=$ARTIFACT_CANDIDATE_PREFLIGHT_PASSED' "$gate"
require_contains 'release_artifact_candidate_blocker_count=$ARTIFACT_CANDIDATE_BLOCKER_COUNT' "$gate"
require_contains 'release_artifact_candidate_tag=$ARTIFACT_CANDIDATE_TAG' "$gate"
require_contains 'release_artifact_candidate_signing_identity_reference_blocked=$ARTIFACT_CANDIDATE_SIGNING_IDENTITY_REFERENCE_BLOCKED' "$gate"
require_contains 'PRODUCT_BLOCKER_AUDIT_OUTPUT="$(' "$gate"
require_contains 'scripts/latticra-v1-product-completion-blocker-audit.sh' "$gate"
require_contains 'v1_product_completion_blocker_audit_present=$PRODUCT_BLOCKER_AUDIT_PRESENT' "$gate"
require_contains 'v1_product_completion_detail_blocker_count=$PRODUCT_BLOCKER_DETAIL_COUNT' "$gate"
require_contains 'v1_product_completion_detail_blockers=$PRODUCT_BLOCKER_DETAILS' "$gate"
require_contains 'status_value()' "$gate"
require_contains 'RELEASE_ARTIFACT_EVIDENCE_ACCEPTED="$(status_value release_artifact_evidence_accepted_by_intake_validator' "$gate"
require_contains 'PRODUCTION_INSTALLER_READY="$(status_value production_installer_ready' "$gate"
require_contains 'FEDORA_PRODUCTION_READINESS_EVIDENCE_COMPLETE="$(status_value fedora_production_readiness_evidence_complete' "$gate"
require_contains 'Q_SEAL_RUNTIME_CRYPTO_READY="$(status_value runtime_crypto_ready' "$gate"
require_contains 'if [ "$PRODUCTION_INSTALLER_READY" != "1" ]; then' "$gate"
require_contains "add_blocker 'v1_release_tag_missing_or_not_approved'" "$gate"
require_contains "add_blocker 'release_artifact_not_promoted'" "$gate"
require_contains "add_blocker 'release_artifact_evidence_not_accepted'" "$gate"
require_contains "add_blocker 'sbom_evidence_not_accepted'" "$gate"
require_contains "add_blocker 'multi_vm_evidence_not_accepted'" "$gate"
require_contains "add_blocker 'nadia_production_readiness_blocked'" "$gate"
require_contains "add_blocker 'q_seal_runtime_crypto_blocked'" "$gate"
require_contains "add_blocker 'rpmbuild_toolchain_missing'" "$gate"
require_contains "add_blocker 'rpm_toolchain_missing'" "$gate"
require_contains "add_blocker 'release_signing_identity_reference_missing_or_invalid'" "$gate"
require_contains 'release_artifact_created=0' "$gate"
require_contains 'artifact_signed=0' "$gate"
require_contains 'sbom_generated=0' "$gate"
require_contains 'evidence_accepted=0' "$gate"
require_contains 'install_performed=0' "$gate"
require_contains 'package_manager_invoked=0' "$gate"
require_contains 'host_mutation_performed=0' "$gate"
require_contains 'git_tag_performed=0' "$gate"
require_contains 'git_push_performed=0' "$gate"

require_contains '## v1.0.0 Release Readiness Gate' "$ledger"
require_contains 'v1_release_readiness_gate_present=1' "$ledger"
require_contains 'v1_release_readiness_gate_passed=0' "$ledger"
require_contains 'v1_release_readiness_blocked=1' "$ledger"
require_contains 'v1_release_blocker_count=<observed>' "$ledger"
require_contains 'v1_release_workspace_resolvable_blocker_count=<observed>' "$ledger"
require_contains 'v1_release_external_prerequisite_blocker_count=<observed>' "$ledger"
require_contains 'v1_product_completion_blocker_audit_present=1' "$ledger"
require_contains 'v1_product_completion_detail_blocker_count=<observed>' "$ledger"
require_contains 'production_release_ready=0' "$ledger"
require_contains 'release_artifact_candidate_preflight_present=1' "$ledger"
require_contains 'release_artifact_candidate_blocker_count=<observed>' "$ledger"
require_contains 'release_artifact_candidate_tag=v1.0.0' "$ledger"
require_contains 'release_artifact_candidate_tag_blocked=<observed>' "$ledger"
require_contains 'release_artifact_candidate_signing_identity_reference_blocked=<observed>' "$ledger"
require_contains 'release_artifact_evidence_accepted_by_intake_validator=<observed>' "$ledger"
require_contains 'sbom_evidence_accepted_by_intake_validator=<observed>' "$ledger"
require_contains 'multi_vm_evidence_accepted_by_intake_validator=<observed>' "$ledger"
require_contains 'dynamic blocker classification counts' README.md
require_contains 'v1 tag-specific release artifact candidate preflight report' README.md
require_contains 'dynamic evidence-status aggregation' README.md
require_contains 'product-completion detail blocker audit' README.md
require_contains 'docs/LATTICRA_V1_0_0_RELEASE_READINESS_GATE_CONTRACT.md' README.md
require_contains 'docs/status/LATTICRA_V1_0_0_RELEASE_READINESS_GATE_STATUS.md' README.md
require_contains 'v1_release_blocker_count=<observed>' docs/status/CURRENT_STATUS.md
require_contains 'release_artifact_candidate_tag=v1.0.0' docs/status/CURRENT_STATUS.md
require_contains 'v1_product_completion_detail_blocker_count=<observed>' docs/status/CURRENT_STATUS.md
require_contains 'multi_vm_evidence_accepted_by_intake_validator=<observed>' docs/status/CURRENT_STATUS.md
require_contains 'release artifact candidate preflight against the requested v1 tag' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'evidence status records dynamically' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'product-completion blocker audit' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'dynamic blocker classification counts' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'v1 tag-specific release artifact candidate preflight report' docs/project_notes/UPCOMING_WORK.md
require_contains 'dynamic evidence-status aggregation' docs/project_notes/UPCOMING_WORK.md
require_contains 'product-completion detail blocker audit' docs/project_notes/UPCOMING_WORK.md
require_contains 'dynamic blocker classification counts' docs/project_notes/UPCOMING_WORK.md
require_contains 'LATTICRA_V1_0_0_RELEASE_READINESS_GATE_STATUS.md' "$status_index"
require_contains 'LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_STATUS.md' "$status_index"
require_contains 'LATTICRA_V1_0_0_RELEASE_READINESS_GATE_CONTRACT.md' "$docs_hub"
require_contains 'LATTICRA_V1_0_0_PRODUCT_COMPLETION_BLOCKER_AUDIT_CONTRACT.md' "$docs_hub"
require_contains 'Latest Latticra v1.0.0 release readiness gate note: 2026-06-12 CDT' STATUS.md
require_contains 'Latest Latticra v1.0.0 product blocker audit note: 2026-06-12 CDT' STATUS.md
require_contains 'Latest Latticra v1.0.0 release readiness gate note: 2026-06-12 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latest Latticra v1.0.0 product blocker audit note: 2026-06-12 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latest Latticra v1.0.0 release readiness gate note: 2026-06-12 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latest Latticra v1.0.0 product blocker audit note: 2026-06-12 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latest Latticra v1.0.0 release readiness gate note: 2026-06-12 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'Latest Latticra v1.0.0 product blocker audit note: 2026-06-12 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'latticra-v1-release-readiness-gate:' Makefile
require_contains 'latticra-v1-product-completion-blocker-audit:' Makefile
require_contains 'sh ./scripts/test-latticra-v1-release-readiness-gate-contract.sh' Makefile
require_contains 'sh ./scripts/test-latticra-v1-product-completion-blocker-audit-contract.sh' Makefile
require_contains 'scripts/test-latticra-v1-release-readiness-gate-contract.sh' "$workflow"
require_contains 'scripts/test-latticra-v1-product-completion-blocker-audit-contract.sh' "$workflow"

output="$(sh "$gate" --version v1.0.0)"
require_output_contains 'LATTICRA V1 RELEASE READINESS GATE' "$output"
require_output_contains 'v1_release_readiness_gate_present=1' "$output"
require_output_contains 'v1_release_readiness_gate_mode=no-effect-release-readiness-aggregation' "$output"
require_output_contains 'v1_release_readiness_gate_version=v1.0.0' "$output"
require_output_contains 'v1_release_readiness_gate_passed=0' "$output"
require_output_contains 'v1_release_readiness_blocked=1' "$output"
require_output_contains 'v1_release_readiness_decision=blocked-existing-production-evidence-gates-open' "$output"
require_output_contains 'v1_release_required_gate_count=23' "$output"
require_output_contains 'v1_release_blocker_count=' "$output"
require_output_contains 'v1_release_tag_missing_or_not_approved' "$output"
require_output_contains 'release_artifact_not_promoted' "$output"
require_output_contains 'release_artifact_evidence_not_accepted' "$output"
require_output_contains 'sbom_evidence_not_accepted' "$output"
require_output_contains 'multi_vm_evidence_not_accepted' "$output"
require_output_contains 'nadia_production_readiness_blocked' "$output"
require_output_contains 'q_seal_runtime_crypto_blocked' "$output"
require_output_contains 'release_signing_identity_reference_missing_or_invalid' "$output"
require_output_contains 'v1_release_workspace_resolvable_blocker_count=' "$output"
require_output_contains 'v1_release_release_decision_blocker_count=' "$output"
require_output_contains 'v1_release_external_prerequisite_blocker_count=' "$output"
require_output_contains 'v1_release_evidence_blocker_count=' "$output"
require_output_contains 'v1_release_product_completion_blocker_count=' "$output"
require_output_contains 'v1_release_next_workspace_action=' "$output"
require_output_contains 'v1_product_completion_blocker_audit_present=1' "$output"
require_output_contains 'v1_product_completion_blocker_audit_passed=0' "$output"
require_output_contains 'v1_product_completion_detail_blocker_count=' "$output"
require_output_contains 'v1_product_completion_detail_blockers=' "$output"
require_output_contains 'v1_tag_exists=0' "$output"
require_output_contains 'production_release_ready=0' "$output"
require_output_contains 'release_artifact_candidate_preflight_present=1' "$output"
require_output_contains 'release_artifact_candidate_preflight_passed=' "$output"
require_output_contains 'release_artifact_candidate_inputs_satisfied=' "$output"
require_output_contains 'release_artifact_candidate_blocker_count=' "$output"
require_output_contains 'release_artifact_candidate_blockers=' "$output"
require_output_contains 'release_artifact_candidate_tag=v1.0.0' "$output"
require_output_contains 'release_artifact_candidate_tag_exists=' "$output"
require_output_contains 'release_artifact_candidate_tag_blocked=' "$output"
require_output_contains 'release_artifact_candidate_toolchain_blocked=' "$output"
require_output_contains 'release_artifact_candidate_tracked_worktree_blocked=' "$output"
require_output_contains 'release_artifact_candidate_signing_identity_reference_blocked=' "$output"
require_output_contains 'release_artifact_promotion_gate_passed=0' "$output"
require_output_contains 'rpmbuild_available=' "$output"
require_output_contains 'rpm_available=' "$output"
require_output_contains 'release_signing_identity_reference_present=' "$output"
require_output_contains 'release_artifact_candidate_valid=' "$output"
require_output_contains 'release_artifact_evidence_accepted_by_intake_validator=' "$output"
require_output_contains 'sbom_evidence_candidate_valid=' "$output"
require_output_contains 'sbom_evidence_accepted_by_intake_validator=' "$output"
require_output_contains 'transcript_evidence_candidate_valid=' "$output"
require_output_contains 'transcript_evidence_accepted_by_intake_validator=' "$output"
require_output_contains 'lifecycle_evidence_candidate_valid=' "$output"
require_output_contains 'lifecycle_evidence_accepted_by_intake_validator=' "$output"
require_output_contains 'recovery_evidence_candidate_valid=' "$output"
require_output_contains 'recovery_evidence_accepted_by_intake_validator=' "$output"
require_output_contains 'multi_vm_evidence_candidate_valid=' "$output"
require_output_contains 'multi_vm_evidence_accepted_by_intake_validator=' "$output"
require_output_contains 'fedora_production_readiness_evidence_complete=' "$output"
require_output_contains 'production_nadia_ready=' "$output"
require_output_contains 'q_seal_runtime_crypto_ready=' "$output"
require_output_contains 'runtime_authority_granted=' "$output"
require_output_contains 'host_mutation_performed=0' "$output"
require_output_contains 'git_tag_performed=0' "$output"
require_output_contains 'git_push_performed=0' "$output"

printf 'latticra_v1_release_readiness_gate_contract: ok\n'

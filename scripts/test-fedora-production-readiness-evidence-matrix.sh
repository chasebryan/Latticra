#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora production readiness evidence matrix: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-production-readiness-evidence-matrix.sh'
test_script='scripts/test-fedora-production-readiness-evidence-matrix.sh'
readiness='docs/FEDORA_READINESS_PLAN.md'
promotion_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE.md'
promotion_gate_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE_STATUS.md'
promotion_gate_script='scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
source_archive_contract='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
source_archive_transcript_validator='docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md'
source_archive_acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md'
source_archive_accepted_status_template='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md'
source_archive_accepted_status_review_validator='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
source_archive_accepted_evidence_acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md'
source_archive_mock_build_input_handoff_contract='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
fedora_local_mock_build_gate_contract='docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md'
fedora_local_mock_build_environment_contract='docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md'
fedora_rpm_artifact_naming_contract='docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md'
fedora_rpm_payload_inspection_contract='docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
fedora_rpm_install_remove_transcript_contract='docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
fedora_package_review_non_claim_contract='docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md'
fedora_package_validation_promotion_blocker_matrix_contract='docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_review_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_disposition_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_disposition_closeout_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md'
spec='packaging/fedora/latticra.spec'
static_validation='scripts/test-fedora-local-rpm-static-validation.sh'
workflow='.github/workflows/fedora-production-readiness-evidence-matrix.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$readiness" \
  "$promotion_gate" \
  "$promotion_gate_status" \
  "$promotion_gate_script" \
  "$rpmlint_classification" \
  "$source_archive_contract" \
  "$source_archive_transcript_validator" \
  "$source_archive_acceptance_gate" \
  "$source_archive_accepted_status_template" \
  "$source_archive_accepted_status_review_validator" \
  "$source_archive_accepted_evidence_acceptance_gate" \
  "$source_archive_mock_build_input_handoff_contract" \
  "$fedora_local_mock_build_gate_contract" \
  "$fedora_local_mock_build_environment_contract" \
  "$fedora_rpm_artifact_naming_contract" \
  "$fedora_rpm_payload_inspection_contract" \
  "$fedora_rpm_install_remove_transcript_contract" \
  "$fedora_package_review_non_claim_contract" \
  "$fedora_package_validation_promotion_blocker_matrix_contract" \
  "$fedora_rpm_build_evidence_intake_denial_contract" \
  "$fedora_rpm_build_evidence_intake_denial_review_contract" \
  "$fedora_rpm_build_evidence_intake_denial_disposition_contract" \
  "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_contract" \
  "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract" \
  "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract" \
  "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract" \
  "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract" \
  "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract" \
  "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract" \
  "$spec" \
  "$static_validation" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect production-readiness evidence matrix' "$doc"
require_contains 'fedora_production_readiness_evidence_matrix_present=1' "$doc"
require_contains 'fedora_production_readiness_matrix_mode=no-effect-matrix' "$doc"
require_contains 'fedora_production_readiness_evidence_complete=0' "$doc"
require_contains 'fedora_production_readiness_promotion_allowed=0' "$doc"
require_contains 'sh scripts/fedora-production-readiness-evidence-matrix.sh' "$doc"
require_contains 'sh scripts/test-fedora-production-readiness-evidence-matrix.sh' "$doc"

require_contains 'FEDORA PRODUCTION READINESS EVIDENCE MATRIX' "$script"
require_contains 'matrix_status=blocked' "$script"
require_contains 'fedora_production_readiness_evidence_complete=0' "$script"
require_contains 'fedora_production_readiness_promotion_allowed=0' "$script"
require_contains 'fedora_mock_build_evidence_present=0' "$script"
require_contains 'fedora_rpmlint_evidence_present=0' "$script"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$script"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$script"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$script"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$script"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$script"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$script"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$script"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$script"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$script"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$script"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$script"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$script"
require_contains 'fedora_rpm_install_remove_transcript_contract_present=1' "$script"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$script"
require_contains 'fedora_package_validation_promotion_blocker_matrix_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_review_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1' "$script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$script"
require_contains 'source_archive_reproducible=0' "$script"
require_contains 'fedora_package_review_ready=0' "$script"
require_contains 'fedora_multi_vm_validation_evidence_present=0' "$script"
require_contains 'fedora_update_safety_evidence_present=0' "$script"
require_contains 'fedora_recovery_safety_evidence_present=0' "$script"
require_contains 'production_installer_ready=0' "$script"
require_contains 'fedora_distribution_ready=0' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_production_readiness_evidence_matrix_present=1' \
  'fedora_production_readiness_matrix_mode=no-effect-matrix' \
  'fedora_production_readiness_evidence_complete=0' \
  'fedora_production_readiness_promotion_allowed=0' \
  'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_promotion_gate_present=1' \
  'fedora_cli_payload_repeatability_prerequisite_complete=0' \
  'fedora_packaging_metadata_static_lane_present=1' \
  'fedora_local_rpm_static_validation_present=1' \
  'fedora_mock_build_evidence_present=0' \
  'fedora_rpmlint_evidence_present=0' \
  'fedora_rpmlint_findings_classification_present=1' \
  'fedora_source_archive_reproducibility_contract_present=1' \
  'fedora_source_archive_transcript_review_validator_present=1' \
  'fedora_source_archive_acceptance_gate_present=1' \
  'fedora_source_archive_accepted_evidence_status_template_present=1' \
  'fedora_source_archive_accepted_evidence_status_review_validator_present=1' \
  'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' \
  'fedora_source_archive_mock_build_input_handoff_contract_present=1' \
  'fedora_local_mock_build_gate_contract_present=1' \
  'fedora_local_mock_build_environment_contract_present=1' \
  'fedora_rpm_artifact_naming_contract_present=1' \
  'fedora_rpm_payload_inspection_contract_present=1' \
  'fedora_rpm_install_remove_transcript_contract_present=1' \
  'fedora_package_review_non_claim_contract_present=1' \
  'fedora_package_validation_promotion_blocker_matrix_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_review_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' \
  'source_archive_transcript_present=0' \
  'source_archive_transcript_candidate_valid=0' \
  'source_archive_transcript_reviewed=0' \
  'source_archive_transcript_review_report_valid=0' \
  'source_archive_accepted_by_transcript_validator=0' \
  'source_archive_accepted_for_build_by_transcript_validator_alone=0' \
  'source_archive_acceptance_gate_mode=no-effect-gate' \
  'source_archive_acceptance_requested=0' \
  'source_archive_accepted_by_acceptance_gate=0' \
  'source_archive_accepted_for_build_by_acceptance_gate_alone=0' \
  'source_archive_accepted_evidence_status_template_mode=no-effect-template' \
  'source_archive_accepted_evidence_status_template_decision=blocked-template-only-no-status-write' \
  'source_archive_accepted_evidence_status_template_complete=0' \
  'source_archive_accepted_evidence_status_review_mode=no-effect-validation' \
  'source_archive_accepted_evidence_status_candidate_valid=0' \
  'source_archive_accepted_evidence_status_reviewed=0' \
  'source_archive_accepted_evidence_status_accepted_by_validator=0' \
  'source_archive_accepted_evidence_status_written_by_validator=0' \
  'source_archive_accepted_for_build_by_status_validator_alone=0' \
  'fedora_mock_build_input_opened_by_status_validator_alone=0' \
  'source_archive_accepted_evidence_acceptance_gate_mode=no-effect-gate' \
  'source_archive_accepted_evidence_status_review_report_valid=0' \
  'source_archive_accepted_evidence_acceptance_requested=0' \
  'source_archive_accepted_by_accepted_evidence_acceptance_gate=0' \
  'source_archive_accepted_evidence_status_written_by_acceptance_gate=0' \
  'source_archive_accepted_for_build_by_acceptance_gate_alone=0' \
  'fedora_mock_build_input_opened_by_acceptance_gate_alone=0' \
  'source_archive_mock_build_input_handoff_contract_state=closed-no-effect' \
  'mock_build_input_handoff_allowed=0' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'fedora_mock_build_gate_open=0' \
  'fedora_mock_build_gate_opened_by_contract=0' \
  'fedora_mock_build_environment_contract_state=specified-no-effect' \
  'fedora_rpm_artifact_naming_contract_state=specified-no-effect' \
  'fedora_rpm_payload_inspection_contract_state=specified-no-effect' \
  'fedora_rpm_install_remove_transcript_contract_state=specified-no-effect' \
  'fedora_package_review_non_claim_contract_state=specified-no-effect' \
  'payload_inspection_contract_state=specified-no-effect' \
  'install_remove_transcript_contract_state=specified-no-effect' \
  'package_review_non_claim_state=specified-no-effect' \
  'fedora_clean_build_environment_documented=1' \
  'fedora_mock_target_documented=1' \
  'fedora_target_distribution_documented=1' \
  'fedora_build_environment_provisioned=0' \
  'fedora_mock_build_environment_provisioned=0' \
  'explicit_operator_build_authorization=0' \
  'disposable_validation_environment_required=1' \
  'disposable_validation_environment_provisioned=0' \
  'environment_transcript_present=0' \
  'toolchain_version_capture_required=1' \
  'rpm_input_digest_binding_required=1' \
  'mock_chroot_lifecycle_documented=1' \
  'mock_network_policy_documented=1' \
  'mock_result_directory_documented=1' \
  'source_rpm_output_path_documented=1' \
  'binary_rpm_output_path_documented=1' \
  'transcript_retention_path_documented=1' \
  'rpm_artifact_naming_contract_present=1' \
  'rpm_artifact_output_directory_required_under_disposable_environment=1' \
  'rpm_artifact_output_directory_created=0' \
  'repository_rpm_artifact_write_allowed=0' \
  'root_workspace_rpm_artifact_write_allowed=0' \
  'publication_directory_write_allowed=0' \
  'rpm_source_artifact_name_pattern_recorded=1' \
  'rpm_binary_artifact_name_pattern_recorded=1' \
  'rpm_dist_tag_token_required=1' \
  'rpm_binary_arch_token_required=1' \
  'rpm_payload_inspection_contract_present=1' \
  'payload_inspection_contract_present=1' \
  'rpm_payload_cli_path_required=1' \
  'rpm_payload_doc_readme_required=1' \
  'rpm_payload_service_files_allowed=0' \
  'rpm_payload_systemd_units_allowed=0' \
  'rpm_payload_init_files_allowed=0' \
  'rpm_payload_kernel_files_allowed=0' \
  'rpm_payload_privileged_helper_allowed=0' \
  'rpm_payload_network_authority_allowed=0' \
  'rpm_payload_host_mutation_hooks_allowed=0' \
  'rpm_install_remove_transcript_contract_present=1' \
  'install_remove_transcript_contract_present=1' \
  'rpm_install_remove_disposable_environment_required=1' \
  'rpm_install_remove_transcript_present=0' \
  'rpm_package_install_run=0' \
  'rpm_package_remove_run=0' \
  'rpm_dnf_install_run=0' \
  'rpm_dnf_remove_run=0' \
  'rpm_cli_install_run=0' \
  'rpm_cli_remove_run=0' \
  'host_install_allowed=0' \
  'host_remove_allowed=0' \
  'host_mutation_allowed=0' \
  'service_state_change_allowed=0' \
  'rpm_validation_result_promoted=0' \
  'package_review_non_claim_contract_present=1' \
  'package_review_non_claim_present=1' \
  'fedora_package_review_non_claim_present=1' \
  'package_validation_promotion_blocker_matrix_contract_present=1' \
  'package_validation_promotion_blocker_matrix_present=1' \
  'validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'package_validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'rpm_build_evidence_intake_denial_contract_present=1' \
  'rpm_build_evidence_intake_denial_review_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' \
  'build_evidence_intake_denial_state=denied-no-effect' \
  'build_evidence_intake_denial_review_state=reviewed-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_state=closed-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_state=closed-out-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' \
  'denial_review_required_before_re_request=1' \
  'denial_disposition_closeout_present=1' \
  'denial_disposition_closeout_decision=closeout-upheld-denial' \
  'denial_disposition_present=1' \
  'denial_disposition_decision=close-upheld-denial' \
  'denial_closed=1' \
  'denial_archived=0' \
  'denial_archive_allowed=0' \
  'denial_archive_gate_present=1' \
  'denial_archive_gate_state=closed-no-effect' \
  'denial_archive_gate_decision=deny-archive-and-re-request' \
  'denial_archive_gate_review_present=1' \
  'denial_archive_gate_review_state=reviewed-upheld-no-effect' \
  'denial_archive_gate_review_decision=uphold-closed-archive-gate' \
  'denial_archive_gate_review_disposition_present=1' \
  'denial_archive_gate_review_disposition_state=disposed-upheld-no-effect' \
  'denial_archive_gate_review_disposition_decision=dispose-upheld-closed-archive-gate-review' \
  'denial_archive_gate_review_disposition_closeout_present=1' \
  'denial_archive_gate_review_disposition_closeout_state=closed-out-upheld-no-effect' \
  'denial_archive_gate_review_disposition_closeout_decision=closeout-upheld-archive-gate-review-disposition' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_present=1' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_decision=deny-archive-and-re-request' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_present=1' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_decision=uphold-closed-archive-gate' \
  'denial_archive_record_write_allowed=0' \
  'denial_archive_record_written=0' \
  'denial_review_present=1' \
  'denial_review_decision=uphold-denial' \
  'denial_re_request_allowed=0' \
  'fedora_denial_archive_allowed=0' \
  'fedora_denial_archive_record_write_allowed=0' \
  'fedora_denial_archive_record_written=0' \
  'fedora_denial_re_request_allowed=0' \
  'fedora_build_evidence_intake_allowed=0' \
  'fedora_build_evidence_intake_requested=0' \
  'fedora_build_evidence_intake_denied=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_closed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' \
  'fedora_build_evidence_intake_denial_disposition_closeout_present=1' \
  'fedora_build_evidence_intake_denial_closed_out=1' \
  'fedora_build_evidence_intake_denial_disposition_present=1' \
  'fedora_build_evidence_intake_denial_closed=1' \
  'fedora_build_evidence_intake_denial_review_present=1' \
  'fedora_build_evidence_intake_denial_upheld=1' \
  'fedora_build_evidence_intake_denial_archived=0' \
  'fedora_build_evidence_intake_denial_archive_gate_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_closed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_reviewed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closed_out=1' \
  'build_transcript_intake_accepted=0' \
  'rpm_build_transcript_intake_accepted=0' \
  'fedora_build_transcript_intake_accepted=0' \
  'rpmbuild_evidence_accepted=0' \
  'mock_build_evidence_accepted=0' \
  'mock_buildsrpm_evidence_accepted=0' \
  'rpmlint_evidence_accepted=0' \
  'source_rpm_evidence_accepted=0' \
  'binary_rpm_evidence_accepted=0' \
  'fedora_rpmbuild_evidence_accepted=0' \
  'fedora_mock_build_evidence_accepted=0' \
  'fedora_mock_buildsrpm_evidence_accepted=0' \
  'fedora_rpmlint_evidence_accepted=0' \
  'fedora_source_rpm_evidence_accepted=0' \
  'fedora_binary_rpm_evidence_accepted=0' \
  'rpm_build_lane_opened=0' \
  'fedora_single_platform_build_lane_opened=0' \
  'fedora_package_review_bug_created=0' \
  'fedora_bugzilla_review_ticket_created=0' \
  'fedora_package_review_request_created=0' \
  'fedora_package_review_approved=0' \
  'fedora_scm_request_created=0' \
  'fedora_dist_git_repo_created=0' \
  'fedora_koji_build_run=0' \
  'fedora_bodhi_update_created=0' \
  'fedora_rawhide_submission_claimed=0' \
  'fedora_rawhide_acceptance_claimed=0' \
  'fedora_official_package_claimed=0' \
  'fedora_packager_sponsor_claimed=0' \
  'fedora_endorsement_claimed=0' \
  'fedora_platform_build_evidence_accepted=0' \
  'fedora_package_validation_result_promoted=0' \
  'package_validation_result_promoted=0' \
  'package_readiness_claimed=0' \
  'source_archive_accepted_evidence_acceptance_gate_report_valid=0' \
  'source_archive_accepted_evidence_acceptance_gate_reviewed=0' \
  'source_archive_accepted_for_build_candidate_valid=0' \
  'source_archive_handoff_to_rpmbuild_allowed=0' \
  'source_archive_handoff_to_mock_allowed=0' \
  'source_archive_handoff_written_by_contract=0' \
  'fedora_rpm_input_layout_documented=1' \
  'fedora_rpmbuild_sources_archive_staged=0' \
  'fedora_rpmbuild_specs_spec_staged=0' \
  'fedora_mock_build_input_opened_by_handoff_contract=0' \
  'fedora_mock_config_written=0' \
  'fedora_mock_chroot_initialized=0' \
  'fedora_mock_chroot_mutated=0' \
  'rpmbuild_allowed=0' \
  'rpmbuild_bs_allowed=0' \
  'rpmbuild_ba_allowed=0' \
  'rpmbuild_bb_allowed=0' \
  'rpmbuild_command_allowed=0' \
  'mock_build_allowed=0' \
  'mock_build_command_allowed=0' \
  'mock_buildsrpm_allowed=0' \
  'dnf_builddep_command_allowed=0' \
  'dnf_builddep_allowed=0' \
  'source_archive_accepted_evidence_status_written=0' \
  'source_archive_accepted_evidence_present=0' \
  'source_archive_accepted=0' \
  'source_archive_reproducible=0' \
  'source_archive_accepted_for_build=0' \
  'fedora_mock_build_input_opened=0' \
  'source_rpm_artifact_created=0' \
  'binary_rpm_artifact_created=0' \
  'rpm_artifact_sha256_recorded=0' \
  'rpm_artifact_published=0' \
  'rpm_payload_inspection_run=0' \
  'source_rpm_payload_inspection_run=0' \
  'binary_rpm_payload_inspection_run=0' \
  'rpm_payload_accepted=0' \
  'rpm_payload_listing_sha256_recorded=0' \
  'source_rpm_payload_listing_sha256_recorded=0' \
  'binary_rpm_payload_listing_sha256_recorded=0' \
  'rpm_installed_on_host=0' \
  'rpm_removed_from_host=0' \
  'rpm_install_remove_transcript_present=0' \
  'rpm_package_install_run=0' \
  'rpm_package_remove_run=0' \
  'rpm_dnf_install_run=0' \
  'rpm_dnf_remove_run=0' \
  'rpm_cli_install_run=0' \
  'rpm_cli_remove_run=0' \
  'host_install_allowed=0' \
  'host_remove_allowed=0' \
  'host_mutation_allowed=0' \
  'service_state_change_allowed=0' \
  'rpm_validation_result_promoted=0' \
  'fedora_package_review_bug_created=0' \
  'fedora_bugzilla_review_ticket_created=0' \
  'fedora_package_review_request_created=0' \
  'fedora_package_review_approved=0' \
  'fedora_scm_request_created=0' \
  'fedora_dist_git_repo_created=0' \
  'fedora_koji_build_run=0' \
  'fedora_bodhi_update_created=0' \
  'fedora_rawhide_submission_claimed=0' \
  'fedora_rawhide_acceptance_claimed=0' \
  'fedora_official_package_claimed=0' \
  'fedora_packager_sponsor_claimed=0' \
  'fedora_endorsement_claimed=0' \
  'fedora_package_review_ready=0' \
  'fedora_multi_vm_validation_evidence_present=0' \
  'fedora_update_safety_evidence_present=0' \
  'fedora_recovery_safety_evidence_present=0' \
  'fedora_immutable_host_evidence_present=0' \
  'fedora_daily_driver_evidence_present=0' \
  'fedora_security_hardening_evidence_present=0' \
  'production_installer_promotion_allowed=0' \
  'fedora_distribution_promotion_allowed=0' \
  'host_install_ready_for_cli_payload=1' \
  'production_installer_ready=0' \
  'root_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
done

for future_field in \
  'fedora_cli_payload_repeatability_prerequisite_complete=1' \
  'fedora_mock_build_evidence_present=1' \
  'fedora_rpmlint_evidence_present=1' \
  'source_archive_reproducible=1' \
  'source_archive_accepted_for_build=1' \
  'fedora_package_review_ready=1' \
  'fedora_multi_vm_validation_evidence_present=1' \
  'fedora_update_safety_evidence_present=1' \
  'fedora_recovery_safety_evidence_present=1' \
  'fedora_immutable_host_evidence_present=1' \
  'fedora_daily_driver_evidence_present=1' \
  'fedora_security_hardening_evidence_present=1'
do
  require_contains "$future_field" "$doc"
done

require_contains 'Status: matrix/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not run Fedora VM validation' "$status"
require_contains 'does not claim production installer readiness or Fedora distribution readiness' "$status"
require_contains 'Add a no-effect Fedora production-readiness evidence intake validator' "$status"

require_contains 'FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md' "$index"
require_contains 'Current Fedora production readiness evidence matrix checkpoint' "$index"
require_contains 'Fedora production-readiness evidence matrix is present but remains blocked' "$index"

require_contains 'docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md' "$readme"
require_contains 'docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md' "$readme"
require_contains 'The Fedora production-readiness evidence matrix is present' "$readme"
require_contains 'keeps Fedora production readiness blocked' "$readme"

require_contains 'not a production operating system' "$readiness"
require_contains 'promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0' "$promotion_gate"
require_contains 'production_installer_promotion_allowed=0' "$promotion_gate_status"
require_contains 'fedora_distribution_promotion_allowed=0' "$promotion_gate_script"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$rpmlint_classification"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$source_archive_contract"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$source_archive_transcript_validator"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$source_archive_acceptance_gate"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$source_archive_accepted_status_template"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$source_archive_accepted_status_review_validator"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$source_archive_accepted_evidence_acceptance_gate"
require_contains 'fedora_source_archive_mock_build_input_handoff_contract_present=1' "$source_archive_mock_build_input_handoff_contract"
require_contains 'fedora_local_mock_build_gate_contract_present=1' "$fedora_local_mock_build_gate_contract"
require_contains 'fedora_local_mock_build_environment_contract_present=1' "$fedora_local_mock_build_environment_contract"
require_contains 'fedora_rpm_artifact_naming_contract_present=1' "$fedora_rpm_artifact_naming_contract"
require_contains 'fedora_rpm_payload_inspection_contract_present=1' "$fedora_rpm_payload_inspection_contract"
require_contains 'fedora_rpm_install_remove_transcript_contract_present=1' "$fedora_rpm_install_remove_transcript_contract"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$fedora_package_review_non_claim_contract"
require_contains 'fedora_package_validation_promotion_blocker_matrix_contract_present=1' "$fedora_package_validation_promotion_blocker_matrix_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_review_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_review_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_disposition_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract"
require_contains 'Name:           latticra' "$spec"
require_contains 'fedora_local_rpm_static_validation: ok' "$static_validation"

require_contains 'name: Fedora Production Readiness Evidence Matrix' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-production-readiness-evidence-matrix.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-production-readiness-evidence-matrix.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-production-readiness-evidence-matrix.sh' 'Makefile'
require_contains 'fedora-production-readiness-evidence-matrix:' 'Makefile'

output=$(sh "$script")
require_output_contains "$output" 'FEDORA PRODUCTION READINESS EVIDENCE MATRIX'
require_output_contains "$output" 'matrix_status=blocked'
require_output_contains "$output" 'fedora_production_readiness_evidence_matrix_present=1'
require_output_contains "$output" 'fedora_production_readiness_evidence_complete=0'
require_output_contains "$output" 'fedora_production_readiness_promotion_allowed=0'
require_output_contains "$output" 'fedora_cli_payload_repeatability_prerequisite_complete=0'
require_output_contains "$output" 'fedora_mock_build_evidence_present=0'
require_output_contains "$output" 'fedora_rpmlint_evidence_present=0'
require_output_contains "$output" 'fedora_rpmlint_findings_classification_present=1'
require_output_contains "$output" 'fedora_source_archive_reproducibility_contract_present=1'
require_output_contains "$output" 'fedora_source_archive_transcript_review_validator_present=1'
require_output_contains "$output" 'fedora_source_archive_acceptance_gate_present=1'
require_output_contains "$output" 'fedora_source_archive_accepted_evidence_status_template_present=1'
require_output_contains "$output" 'fedora_source_archive_accepted_evidence_status_review_validator_present=1'
require_output_contains "$output" 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1'
require_output_contains "$output" 'fedora_source_archive_mock_build_input_handoff_contract_present=1'
require_output_contains "$output" 'fedora_local_mock_build_gate_contract_present=1'
require_output_contains "$output" 'fedora_local_mock_build_environment_contract_present=1'
require_output_contains "$output" 'fedora_rpm_artifact_naming_contract_present=1'
require_output_contains "$output" 'fedora_rpm_payload_inspection_contract_present=1'
require_output_contains "$output" 'fedora_rpm_install_remove_transcript_contract_present=1'
require_output_contains "$output" 'fedora_package_review_non_claim_contract_present=1'
require_output_contains "$output" 'fedora_package_validation_promotion_blocker_matrix_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_review_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_disposition_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1'
require_output_contains "$output" 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1'
require_output_contains "$output" 'source_archive_transcript_review_report_valid=0'
require_output_contains "$output" 'source_archive_accepted_by_acceptance_gate=0'
require_output_contains "$output" 'source_archive_accepted_evidence_status_written=0'
require_output_contains "$output" 'source_archive_accepted_evidence_status_accepted_by_validator=0'
require_output_contains "$output" 'source_archive_accepted_by_accepted_evidence_acceptance_gate=0'
require_output_contains "$output" 'source_archive_accepted_for_build_by_acceptance_gate_alone=0'
require_output_contains "$output" 'source_archive_handoff_to_rpmbuild_allowed=0'
require_output_contains "$output" 'source_archive_handoff_to_mock_allowed=0'
require_output_contains "$output" 'fedora_mock_build_input_opened_by_handoff_contract=0'
require_output_contains "$output" 'fedora_mock_build_gate_state=closed-no-effect'
require_output_contains "$output" 'fedora_mock_build_gate_open=0'
require_output_contains "$output" 'fedora_mock_build_environment_contract_state=specified-no-effect'
require_output_contains "$output" 'fedora_rpm_artifact_naming_contract_state=specified-no-effect'
require_output_contains "$output" 'fedora_rpm_payload_inspection_contract_state=specified-no-effect'
require_output_contains "$output" 'fedora_rpm_install_remove_transcript_contract_state=specified-no-effect'
require_output_contains "$output" 'fedora_package_review_non_claim_contract_state=specified-no-effect'
require_output_contains "$output" 'environment_transcript_present=0'
require_output_contains "$output" 'fedora_mock_build_environment_provisioned=0'
require_output_contains "$output" 'rpm_artifact_output_directory_created=0'
require_output_contains "$output" 'repository_rpm_artifact_write_allowed=0'
require_output_contains "$output" 'rpm_payload_inspection_run=0'
require_output_contains "$output" 'rpm_payload_accepted=0'
require_output_contains "$output" 'rpm_installed_on_host=0'
require_output_contains "$output" 'rpm_removed_from_host=0'
require_output_contains "$output" 'rpm_install_remove_transcript_present=0'
require_output_contains "$output" 'rpm_package_install_run=0'
require_output_contains "$output" 'rpm_package_remove_run=0'
require_output_contains "$output" 'host_mutation_allowed=0'
require_output_contains "$output" 'rpm_validation_result_promoted=0'
require_output_contains "$output" 'package_validation_promotion_blocker_matrix_contract_present=1'
require_output_contains "$output" 'validation_promotion_blocker_matrix_state=blocked-no-effect'
require_output_contains "$output" 'fedora_platform_build_evidence_accepted=0'
require_output_contains "$output" 'fedora_package_validation_result_promoted=0'
require_output_contains "$output" 'package_validation_result_promoted=0'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_review_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_disposition_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_contract_present=1'
require_output_contains "$output" 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1'
require_output_contains "$output" 'build_evidence_intake_denial_state=denied-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_review_state=reviewed-upheld-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_disposition_state=closed-upheld-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_state=closed-out-upheld-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect'
require_output_contains "$output" 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect'
require_output_contains "$output" 'denial_review_required_before_re_request=1'
require_output_contains "$output" 'denial_disposition_closeout_present=1'
require_output_contains "$output" 'denial_disposition_closeout_decision=closeout-upheld-denial'
require_output_contains "$output" 'denial_disposition_present=1'
require_output_contains "$output" 'denial_disposition_decision=close-upheld-denial'
require_output_contains "$output" 'denial_closed=1'
require_output_contains "$output" 'denial_archived=0'
require_output_contains "$output" 'denial_archive_allowed=0'
require_output_contains "$output" 'denial_archive_gate_present=1'
require_output_contains "$output" 'denial_archive_gate_state=closed-no-effect'
require_output_contains "$output" 'denial_archive_gate_decision=deny-archive-and-re-request'
require_output_contains "$output" 'denial_archive_gate_review_present=1'
require_output_contains "$output" 'denial_archive_gate_review_state=reviewed-upheld-no-effect'
require_output_contains "$output" 'denial_archive_gate_review_decision=uphold-closed-archive-gate'
require_output_contains "$output" 'denial_archive_gate_review_disposition_present=1'
require_output_contains "$output" 'denial_archive_gate_review_disposition_state=disposed-upheld-no-effect'
require_output_contains "$output" 'denial_archive_gate_review_disposition_decision=dispose-upheld-closed-archive-gate-review'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_present=1'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_state=closed-out-upheld-no-effect'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_decision=closeout-upheld-archive-gate-review-disposition'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_archive_gate_present=1'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_archive_gate_decision=deny-archive-and-re-request'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_archive_gate_review_present=1'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect'
require_output_contains "$output" 'denial_archive_gate_review_disposition_closeout_archive_gate_review_decision=uphold-closed-archive-gate'
require_output_contains "$output" 'denial_archive_record_write_allowed=0'
require_output_contains "$output" 'denial_archive_record_written=0'
require_output_contains "$output" 'denial_review_present=1'
require_output_contains "$output" 'denial_review_decision=uphold-denial'
require_output_contains "$output" 'denial_re_request_allowed=0'
require_output_contains "$output" 'fedora_denial_archive_allowed=0'
require_output_contains "$output" 'fedora_denial_archive_record_write_allowed=0'
require_output_contains "$output" 'fedora_denial_archive_record_written=0'
require_output_contains "$output" 'fedora_build_evidence_intake_allowed=0'
require_output_contains "$output" 'fedora_build_evidence_intake_denied=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_closed=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_reviewed=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_disposition_closeout_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_closed_out=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_disposition_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_closed=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_review_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_upheld=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archived=0'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_closed=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_reviewed=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_disposed=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_present=1'
require_output_contains "$output" 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closed_out=1'
require_output_contains "$output" 'build_transcript_intake_accepted=0'
require_output_contains "$output" 'rpm_build_transcript_intake_accepted=0'
require_output_contains "$output" 'rpmbuild_evidence_accepted=0'
require_output_contains "$output" 'mock_build_evidence_accepted=0'
require_output_contains "$output" 'rpmlint_evidence_accepted=0'
require_output_contains "$output" 'source_rpm_evidence_accepted=0'
require_output_contains "$output" 'binary_rpm_evidence_accepted=0'
require_output_contains "$output" 'rpm_build_lane_opened=0'
require_output_contains "$output" 'fedora_package_review_bug_created=0'
require_output_contains "$output" 'fedora_package_review_request_created=0'
require_output_contains "$output" 'fedora_dist_git_repo_created=0'
require_output_contains "$output" 'fedora_koji_build_run=0'
require_output_contains "$output" 'fedora_bodhi_update_created=0'
require_output_contains "$output" 'fedora_official_package_claimed=0'
require_output_contains "$output" 'rpmbuild_allowed=0'
require_output_contains "$output" 'rpmbuild_bs_allowed=0'
require_output_contains "$output" 'mock_build_allowed=0'
require_output_contains "$output" 'mock_buildsrpm_allowed=0'
require_output_contains "$output" 'dnf_builddep_allowed=0'
require_output_contains "$output" 'source_archive_reproducible=0'
require_output_contains "$output" 'fedora_package_review_ready=0'
require_output_contains "$output" 'production_installer_promotion_allowed=0'
require_output_contains "$output" 'fedora_distribution_promotion_allowed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'root_installer_ready=0'
require_output_contains "$output" 'fedora_distribution_ready=0'

printf 'fedora_production_readiness_evidence_matrix: ok\n'

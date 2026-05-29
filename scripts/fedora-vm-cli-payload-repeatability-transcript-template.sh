#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-transcript-template.sh

Emits a no-effect Fedora VM CLI payload repeatability transcript capture
template. It validates local records and prints required future transcript
fields. It does not run the repeatability runner, build an RPM, install an RPM,
remove an RPM, or mutate the host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability transcript template: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file" 66
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern"
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
require_file scripts/run-fedora-vm-cli-payload-repeatability-lane.sh

require_contains 'transcript_kind=disposable-vm-cli-payload-repeatability' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_contains 'source_tree_revision_recorded=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md
require_contains 'repeatability_transcript_accepted=0' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY LANE' scripts/run-fedora-vm-cli-payload-repeatability-lane.sh

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT CAPTURE TEMPLATE

template_status=ok
fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1
repeatability_transcript_template_mode=no-effect-template
repeatability_transcript_template_decision=blocked-template-only-no-vm-execution
repeatability_transcript_template_complete=0
repeatability_runner_executed=0
rpm_build_performed=0
rpm_install_performed=0
rpm_removal_performed=0
host_mutation_performed=0
repeatability_transcript_attached=0
repeatability_transcript_reviewed=0
repeatability_transcript_accepted=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0

[operator_context]
target_required=disposable-fedora-vm
operator_review_required=1
clean_snapshot_required=1
recovery_path_required=1
prior_cli_payload_evidence_required=1
runner_path=scripts/run-fedora-vm-cli-payload-repeatability-lane.sh

[required_environment]
LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1
LATTICRA_ALLOW_CLI_PAYLOAD_REPEATABILITY_VALIDATION=1
LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1
LATTICRA_TARGET_IS_DAILY_DRIVER=0
LATTICRA_TARGET_IS_PRODUCTION_HOST=0
LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0
LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1
LATTICRA_TARGET_HAS_RECOVERY_PATH=1
LATTICRA_OPERATOR_CONSENT_RECORDED=1

[transcript_header]
FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT
transcript_kind=disposable-vm-cli-payload-repeatability
transcript_version=1
operator_review_required=1
repeatability_transcript_recorded_after_real_run=1
prior_cli_payload_evidence_recorded=1

[prior_evidence]
prior_validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm
prior_validated_payload=/usr/bin/latticra
prior_validated_payload=/usr/share/doc/latticra/README.md
prior_disposable_vm_cli_validation_completed=1
prior_host_install_ready_for_cli_payload=1
prior_evidence_level=9

[runner_report_required_fields]
FEDORA VM CLI PAYLOAD REPEATABILITY LANE
validation_status=ok
repeatability_validation_status=ok
source_tree_revision_recorded=1
source_tree_revision=<required-from-real-run>
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
fedora_kernel_version=<required-from-real-run>
spec_checksum_recorded=1
spec_checksum=<required-from-real-run>
source_archive_checksum_recorded=1
source_archive_checksum=<required-from-real-run>
rpm_nevra_recorded=1
rpm_nevra=<required-from-real-run>
package_name=latticra
package_version=0.0.0
rpm_payload_listing_recorded=1
rpm_payload_matches_expected_cli_surfaces=1
unexpected_runtime_surface_absent=1
cli_status_output_recorded=1
cli_version_output_recorded=1
cli_report_output_recorded=1
cli_invalid_command_exit_recorded=1
validated_cli_mode_still_no_effect=1
validated_runtime_behavior_still_disabled=1
validated_non_claims_preserved=1
rpm_verify_completed=1
removal_validation_performed=1
post_removal_absence_verified=1
second_disposable_vm_cli_validation_completed=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
fedora_vm_cli_payload_repeatability_lane: ok

[review_gate]
repeatability_transcript_review_required=1
repeatability_transcript_attached=0
repeatability_transcript_reviewed=0
repeatability_transcript_accepted=0
promotion_allowed_before_review=0

[non_claims]
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
security_hardening_claimed=0
update_safety_claimed=0
recovery_safety_claimed=0
os_replacement_ready=0
REPORT

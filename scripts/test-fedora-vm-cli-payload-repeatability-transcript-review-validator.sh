#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability transcript review validator: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-transcript-review-validator.sh'
template='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md'
template_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE_STATUS.md'
review_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md'
review_gate_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE_STATUS.md'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-transcript-review-validator.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$template" \
  "$template_status" \
  "$review_gate" \
  "$review_gate_status" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect transcript review validator' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$doc"
require_contains 'repeatability_transcript_review_mode=no-effect-validation' "$doc"
require_contains 'repeatability_transcript_candidate_valid=0' "$doc"
require_contains 'repeatability_transcript_accepted=0' "$doc"
require_contains 'evidence_status_written=0' "$doc"
require_contains 'promotion_allowed_by_validator_alone=0' "$doc"
require_contains 'sh scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh --transcript <path>' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-review-validator.sh' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT REVIEW' "$script"
require_contains 'repeatability_transcript_candidate_valid=1' "$script"
require_contains 'repeatability_transcript_placeholder_values_absent=1' "$script"
require_contains 'repeatability_transcript_required_markers_present=1' "$script"
require_contains 'repeatability_transcript_value_fields_validated=1' "$script"
require_contains 'repeatability_transcript_accepted=0' "$script"
require_contains 'evidence_status_written=0' "$script"
require_contains 'promotion_allowed_by_validator_alone=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

require_contains 'Status: validator/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$status"
require_contains 'repeatability_transcript_candidate_valid=0' "$status"
require_contains 'repeatability_transcript_accepted=0' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-review-validator.sh' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability transcript review validator checkpoint' "$index"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$index"
require_contains 'promotion_allowed_by_validator_alone=0' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md' "$readme"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$readme"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md' "$template"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh' "$template"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$template_status"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md' "$review_gate"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh' "$review_gate"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$review_gate_status"

require_contains 'name: Fedora VM CLI Payload Repeatability Transcript Review Validator' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-review-validator.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-repeatability-review.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.transcript"
placeholder="$tmp/placeholder.transcript"

cat >"$valid" <<'VALID_TRANSCRIPT'
FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT
transcript_kind=disposable-vm-cli-payload-repeatability
transcript_version=1
operator_review_required=1
repeatability_transcript_recorded_after_real_run=1
prior_cli_payload_evidence_recorded=1
prior_validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm
prior_validated_payload=/usr/bin/latticra
prior_validated_payload=/usr/share/doc/latticra/README.md
prior_disposable_vm_cli_validation_completed=1
prior_host_install_ready_for_cli_payload=1
prior_evidence_level=9
FEDORA VM CLI PAYLOAD REPEATABILITY LANE
validation_status=ok
repeatability_validation_status=ok
source_tree_revision_recorded=1
source_tree_revision=0123456789abcdef0123456789abcdef01234567
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
fedora_kernel_version=6.19.10-300.fc44.x86_64
spec_checksum_recorded=1
spec_checksum=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
source_archive_checksum_recorded=1
source_archive_checksum=bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
rpm_nevra_recorded=1
rpm_nevra=latticra-0.0.0-0.1.local.fc44.x86_64
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
VALID_TRANSCRIPT

cat >"$placeholder" <<'PLACEHOLDER_TRANSCRIPT'
FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT
transcript_kind=disposable-vm-cli-payload-repeatability
transcript_version=1
operator_review_required=1
repeatability_transcript_recorded_after_real_run=1
prior_cli_payload_evidence_recorded=1
prior_validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm
prior_validated_payload=/usr/bin/latticra
prior_validated_payload=/usr/share/doc/latticra/README.md
prior_disposable_vm_cli_validation_completed=1
prior_host_install_ready_for_cli_payload=1
prior_evidence_level=9
FEDORA VM CLI PAYLOAD REPEATABILITY LANE
validation_status=ok
repeatability_validation_status=ok
source_tree_revision_recorded=1
source_tree_revision=<required-from-real-run>
fedora_os_release_recorded=1
fedora_kernel_version_recorded=1
fedora_kernel_version=<required-from-real-run>
spec_checksum_recorded=1
spec_checksum=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
source_archive_checksum_recorded=1
source_archive_checksum=bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
rpm_nevra_recorded=1
rpm_nevra=latticra-0.0.0-0.1.local.fc44.x86_64
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
PLACEHOLDER_TRANSCRIPT

output=$(sh "$script" --transcript "$valid")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT REVIEW'
require_output_contains "$output" 'review_status=ok'
require_output_contains "$output" 'repeatability_transcript_candidate_valid=1'
require_output_contains "$output" 'repeatability_transcript_placeholder_values_absent=1'
require_output_contains "$output" 'repeatability_transcript_accepted=0'
require_output_contains "$output" 'evidence_status_written=0'
require_output_contains "$output" 'promotion_allowed_by_validator_alone=0'
require_output_contains "$output" 'cli_payload_repeatability_evidence_present=0'

if sh "$script" --transcript "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder transcript unexpectedly passed review'
fi

printf 'fedora_vm_cli_payload_repeatability_transcript_review_validator: ok\n'

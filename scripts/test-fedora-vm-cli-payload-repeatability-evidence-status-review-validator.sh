#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability evidence status review validator: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-evidence-status-review-validator.sh'
template='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md'
template_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE_STATUS.md'
template_script='scripts/fedora-vm-cli-payload-repeatability-evidence-status-template.sh'
acceptance='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md'
transcript_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md'
transcript_review='scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-evidence-status-review-validator.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$template" \
  "$template_status" \
  "$template_script" \
  "$acceptance" \
  "$transcript_validator" \
  "$transcript_review" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect evidence status review validator' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_evidence_status_review_validator_present=1' "$doc"
require_contains 'repeatability_evidence_status_review_mode=no-effect-validation' "$doc"
require_contains 'repeatability_evidence_status_candidate_valid=0' "$doc"
require_contains 'repeatability_evidence_status_accepted_by_validator=0' "$doc"
require_contains 'evidence_status_written_by_validator=0' "$doc"
require_contains 'promotion_allowed_by_status_validator_alone=0' "$doc"
require_contains 'sh scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh --status <path>' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-status-review-validator.sh' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS REVIEW' "$script"
require_contains 'repeatability_evidence_status_candidate_valid=1' "$script"
require_contains 'repeatability_evidence_status_placeholder_values_absent=1' "$script"
require_contains 'repeatability_evidence_status_required_markers_present=1' "$script"
require_contains 'repeatability_evidence_status_value_fields_validated=1' "$script"
require_contains 'repeatability_evidence_status_accepted_by_validator=0' "$script"
require_contains 'evidence_status_written_by_validator=0' "$script"
require_contains 'promotion_allowed_by_status_validator_alone=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_vm_cli_payload_repeatability_evidence_status_template_present=1' \
  'fedora_vm_cli_payload_repeatability_evidence_status_review_validator_present=1' \
  'repeatability_evidence_status_review_mode=no-effect-validation' \
  'repeatability_evidence_status_candidate_valid=0' \
  'repeatability_evidence_status_reviewed=0' \
  'repeatability_evidence_status_accepted_by_validator=0' \
  'evidence_status_written_by_validator=0' \
  'promotion_allowed_by_status_validator_alone=0' \
  'repeatability_transcript_accepted=0' \
  'evidence_status_written=0' \
  'second_disposable_vm_cli_validation_completed=0' \
  'cli_payload_repeatability_evidence_present=0' \
  'host_install_ready_for_cli_payload=1' \
  'production_installer_ready=0' \
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

require_contains 'Status: validator/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'does not write evidence status' "$status"
require_contains 'does not mark repeatability evidence present' "$status"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript candidate, fill evidence status template, and review the evidence status candidate' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability evidence status review validator checkpoint' "$index"
require_contains 'evidence status review validator is present but does not write or accept repeatability evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md' "$readme"
require_contains 'The repeatability evidence status review validator is present' "$readme"
require_contains 'does not write or promote evidence' "$readme"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS' "$template"
require_contains 'fedora_vm_cli_payload_repeatability_evidence_status_template_present=1' "$template_status"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS TEMPLATE' "$template_script"
require_contains 'The acceptance contract alone cannot promote evidence.' "$acceptance"
require_contains 'repeatability_transcript_accepted=0' "$transcript_validator"
require_contains 'evidence_status_written=0' "$transcript_review"

require_contains 'name: Fedora VM CLI Payload Repeatability Evidence Status Review Validator' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-status-review-validator.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-evidence-status-review-validator.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-evidence-status-review-validator:' 'Makefile'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-repeatability-status-review.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.status"
placeholder="$tmp/placeholder.status"

cat >"$valid" <<'VALID_STATUS'
FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS
Status: evidence status alignment
Date: 2026-05-26
source=operator disposable Fedora VM repeatability transcript
transcript_kind=disposable-vm-cli-payload-repeatability
transcript_path=docs/status/evidence/fedora-repeatability-transcript-2026-05-26.txt
transcript_checksum=cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
repeatability_transcript_reviewed=1
repeatability_transcript_accepted=1
repeatability_transcript_candidate_valid=1
repeatability_transcript_placeholder_values_absent=1
repeatability_transcript_required_markers_present=1
repeatability_transcript_value_fields_validated=1
source_tree_revision_recorded=1
source_tree_revision=0123456789abcdef0123456789abcdef01234567
fedora_os_release_recorded=1
fedora_os_release=Fedora Linux 44
fedora_kernel_version_recorded=1
fedora_kernel_version=6.19.10-300.fc44.x86_64
spec_checksum_recorded=1
spec_checksum=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
source_archive_checksum_recorded=1
source_archive_checksum=bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
rpm_nevra_recorded=1
rpm_nevra=latticra-0.0.0-0.1.local.fc44.x86_64
rpm_payload_matches_expected_cli_surfaces=1
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
evidence_status_written=1
VALID_STATUS

cat >"$placeholder" <<'PLACEHOLDER_STATUS'
FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS
Status: evidence status alignment
Date: <required-from-accepted-review-date>
source=operator disposable Fedora VM repeatability transcript
transcript_kind=disposable-vm-cli-payload-repeatability
transcript_path=<required-from-operator-attachment>
transcript_checksum=cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
repeatability_transcript_reviewed=1
repeatability_transcript_accepted=1
repeatability_transcript_candidate_valid=1
repeatability_transcript_placeholder_values_absent=1
repeatability_transcript_required_markers_present=1
repeatability_transcript_value_fields_validated=1
source_tree_revision_recorded=1
source_tree_revision=<required-from-real-run>
fedora_os_release_recorded=1
fedora_os_release=<required-from-real-run>
fedora_kernel_version_recorded=1
fedora_kernel_version=6.19.10-300.fc44.x86_64
spec_checksum_recorded=1
spec_checksum=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
source_archive_checksum_recorded=1
source_archive_checksum=bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
rpm_nevra_recorded=1
rpm_nevra=latticra-0.0.0-0.1.local.fc44.x86_64
rpm_payload_matches_expected_cli_surfaces=1
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
evidence_status_written=1
PLACEHOLDER_STATUS

output=$(sh "$script" --status "$valid")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS REVIEW'
require_output_contains "$output" 'review_status=ok'
require_output_contains "$output" 'repeatability_evidence_status_candidate_valid=1'
require_output_contains "$output" 'repeatability_evidence_status_placeholder_values_absent=1'
require_output_contains "$output" 'repeatability_evidence_status_accepted_by_validator=0'
require_output_contains "$output" 'evidence_status_written_by_validator=0'
require_output_contains "$output" 'promotion_allowed_by_status_validator_alone=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" --status "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder evidence status unexpectedly passed review'
fi

printf 'fedora_vm_cli_payload_repeatability_evidence_status_review_validator: ok\n'

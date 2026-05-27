#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability publication review validator: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-publication-review.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-publication-review-validator.sh'
template='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE.md'
template_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE_STATUS.md'
template_script='scripts/fedora-vm-cli-payload-repeatability-publication-review-template.sh'
publication_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md'
evidence_status_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
evidence_status_review='scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-publication-review-validator.yml'

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
  "$publication_gate" \
  "$evidence_status_validator" \
  "$evidence_status_review" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect publication review validator' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_publication_review_validator_present=1' "$doc"
require_contains 'publication_review_validation_mode=no-effect-validation' "$doc"
require_contains 'publication_review_candidate_valid=0' "$doc"
require_contains 'publication_review_approved_by_validator=0' "$doc"
require_contains 'evidence_status_written_by_validator=0' "$doc"
require_contains 'repeatability_evidence_published_by_validator=0' "$doc"
require_contains 'promotion_allowed_by_publication_review_validator_alone=0' "$doc"
require_contains 'sh scripts/fedora-vm-cli-payload-repeatability-publication-review.sh --review <path>' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-review-validator.sh' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW VALIDATION' "$script"
require_contains 'publication_review_candidate_valid=1' "$script"
require_contains 'publication_review_placeholder_values_absent=1' "$script"
require_contains 'publication_review_required_markers_present=1' "$script"
require_contains 'publication_review_value_fields_validated=1' "$script"
require_contains 'publication_review_approved_by_validator=0' "$script"
require_contains 'evidence_status_written_by_validator=0' "$script"
require_contains 'repeatability_evidence_published_by_validator=0' "$script"
require_contains 'promotion_allowed_by_publication_review_validator_alone=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_vm_cli_payload_repeatability_publication_review_template_present=1' \
  'fedora_vm_cli_payload_repeatability_publication_review_validator_present=1' \
  'publication_review_validation_mode=no-effect-validation' \
  'publication_review_candidate_valid=0' \
  'publication_review_reviewed=0' \
  'publication_review_approved_by_validator=0' \
  'evidence_status_written_by_validator=0' \
  'repeatability_evidence_published_by_validator=0' \
  'promotion_allowed_by_publication_review_validator_alone=0' \
  'operator_publication_review_completed=0' \
  'repeatability_evidence_publication_approved=0' \
  'repeatability_evidence_status_published=0' \
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
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not approve publication by itself' "$status"
require_contains 'does not publish repeatability evidence' "$status"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, then validate the filled publication review candidate' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability publication review validator checkpoint' "$index"
require_contains 'publication review validator is present but does not approve or publish repeatability evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR_STATUS.md' "$readme"
require_contains 'The repeatability publication review validator is present' "$readme"
require_contains 'does not approve or publish evidence' "$readme"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW' "$template"
require_contains 'fedora_vm_cli_payload_repeatability_publication_review_template_present=1' "$template_status"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW TEMPLATE' "$template_script"
require_contains 'operator_publication_review_completed=1' "$publication_gate"
require_contains 'repeatability_evidence_status_accepted_by_validator=0' "$evidence_status_validator"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS REVIEW' "$evidence_status_review"

require_contains 'name: Fedora VM CLI Payload Repeatability Publication Review Validator' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-review-validator.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-vm-cli-payload-repeatability-publication-review.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-publication-review-validator.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-publication-review-validator:' 'Makefile'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-repeatability-publication-review.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.review"
placeholder="$tmp/placeholder.review"

cat >"$valid" <<'VALID_REVIEW'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW
publication_review_status=approved-for-publication
publication_review_date=2026-05-27
operator_reviewer=release-operator
transcript_review_output_attached=1
evidence_status_review_output_attached=1
transcript_checksum_matches_status=1
source_revision_matches_status=1
status_candidate_validator_passed=1
publication_gate_reviewed=1
non_claims_reviewed=1
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
published_status_path=docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS.md
repeatability_evidence_status_published=1
evidence_status_written=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
VALID_REVIEW

cat >"$placeholder" <<'PLACEHOLDER_REVIEW'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW
publication_review_status=approved-for-publication
publication_review_date=<required-after-operator-review>
operator_reviewer=<required-after-operator-review>
transcript_review_output_attached=1
evidence_status_review_output_attached=1
transcript_checksum_matches_status=1
source_revision_matches_status=1
status_candidate_validator_passed=1
publication_gate_reviewed=1
non_claims_reviewed=1
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
published_status_path=<required-after-status-write>
repeatability_evidence_status_published=1
evidence_status_written=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
PLACEHOLDER_REVIEW

output=$(sh "$script" --review "$valid")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW VALIDATION'
require_output_contains "$output" 'review_validation_status=ok'
require_output_contains "$output" 'publication_review_candidate_valid=1'
require_output_contains "$output" 'publication_review_placeholder_values_absent=1'
require_output_contains "$output" 'publication_review_approved_by_validator=0'
require_output_contains "$output" 'evidence_status_written_by_validator=0'
require_output_contains "$output" 'repeatability_evidence_published_by_validator=0'
require_output_contains "$output" 'promotion_allowed_by_publication_review_validator_alone=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" --review "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder publication review unexpectedly passed validation'
fi

printf 'fedora_vm_cli_payload_repeatability_publication_review_validator: ok\n'

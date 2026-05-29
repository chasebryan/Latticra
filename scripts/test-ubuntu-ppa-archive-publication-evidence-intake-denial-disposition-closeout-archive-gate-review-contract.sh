#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu ppa/archive publication evidence intake denial disposition closeout archive gate review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu ppa/archive publication evidence intake denial disposition closeout archive gate review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_no_ubuntu_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.deb' -o -name '*.dsc' -o -name '*.changes' -o -name '*.build' -o -name '*.buildinfo' \) -print | grep -q .; then
    printf 'ubuntu ppa/archive publication evidence intake denial disposition closeout archive gate review contract: unexpected Ubuntu package artifact under %s\n' "$dir" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md'
archive_gate_review_disposition_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md'
archive_gate_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
closeout_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md'
disposition_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md'
review_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md'
denial_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
matrix_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
publication_gate='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
workflow='.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-review-contract.yml'
archive_gate_review_disposition_workflow='.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.yml'

require_file "$contract"
require_file "$archive_gate_review_disposition_contract"
require_file "$archive_gate_contract"
require_file "$closeout_contract"
require_file "$disposition_contract"
require_file "$review_contract"
require_file "$denial_contract"
require_file "$matrix_contract"
require_file "$publication_gate"
require_file "$static_validation"
require_file "$readiness"
require_file "$status"
require_file "$workflow"
require_file "$archive_gate_review_disposition_workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md

require_contains 'Status: no-effect publication evidence intake denial disposition closeout archive gate review contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' "$contract"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'ubuntu_ppa_archive_publication_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_present=1' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_decision=uphold-closed-archive-gate' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_present=1' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_state=disposed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_decision=dispose-upheld-closed-archive-gate-review' "$contract"
require_contains 'publication_evidence_denial_archive_gate_present=1' "$contract"
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$contract"
require_contains 'publication_evidence_denial_disposition_closeout_present=1' "$contract"
require_contains 'publication_evidence_denial_disposition_closeout_decision=closeout-upheld-denial' "$contract"
require_contains 'publication_evidence_denial_closed=1' "$contract"
require_contains 'publication_evidence_denial_archived=0' "$contract"
require_contains 'publication_evidence_denial_archive_allowed=0' "$contract"
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$contract"
require_contains 'publication_evidence_denial_archive_record_written=0' "$contract"
require_contains 'publication_evidence_denial_re_request_allowed=0' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denied=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_closed=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_closed_out=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archived=0' "$contract"
require_contains 'ubuntu_platform_publication_evidence_accepted=0' "$contract"
require_contains 'publication_transcript_intake_accepted=0' "$contract"
require_contains 'ppa_creation_evidence_accepted=0' "$contract"
require_contains 'launchpad_publication_evidence_accepted=0' "$contract"
require_contains 'ubuntu_archive_submission_evidence_accepted=0' "$contract"
require_contains 'publication_result_evidence_accepted=0' "$contract"
require_contains 'publication_result_promoted=0' "$contract"
require_contains 'ubuntu_publication_result_promoted=0' "$contract"
require_contains 'ubuntu_publication_ready=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'publication_evidence_denial_archive_gate_review_identifier' "$contract"
require_contains 'publication_evidence_denial_archive_gate_reference' "$contract"
require_contains 'denial_disposition_closeout_reference' "$contract"
require_contains 'denial_disposition_reference' "$contract"
require_contains 'denial_review_reference' "$contract"
require_contains 'publication_evidence_denial_reference' "$contract"
require_contains 'publication_evidence_intake_request_identifier' "$contract"
require_contains 'ubuntu_target_series' "$contract"
require_contains 'requested_publication_evidence_kind' "$contract"
require_contains 'requested_publication_action' "$contract"
require_contains 'submitted_publication_transcript_reference' "$contract"
require_contains 'publication_promotion_blocker_matrix_reference' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_decision' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_reason' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_reviewer' "$contract"
require_contains 'archive_record_write_authorization_reference' "$contract"
require_contains 'uphold-closed-archive-gate' "$contract"

require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_reviewed=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_disposition_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_disposed=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_closed=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_closed_out=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archived=0' "$contract"
require_contains 'ubuntu_publication_denial_archive_allowed=0' "$contract"
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' "$contract"
require_contains 'ubuntu_publication_denial_archive_record_written=0' "$contract"
require_contains 'ubuntu_publication_denial_re_request_allowed=0' "$contract"
require_contains 'ubuntu_publication_transcript_intake_accepted=0' "$contract"
require_contains 'ubuntu_ppa_creation_evidence_accepted=0' "$contract"
require_contains 'ubuntu_launchpad_publication_evidence_accepted=0' "$contract"
require_contains 'ubuntu_archive_submission_evidence_accepted=0' "$contract"
require_contains 'ubuntu_publication_result_evidence_accepted=0' "$contract"
require_contains 'debsign_run=0' "$contract"
require_contains 'dput_run=0' "$contract"
require_contains 'launchpad_upload_run=0' "$contract"
require_contains 'ppa_created=0' "$contract"
require_contains 'ppa_claimed=0' "$contract"
require_contains 'ubuntu_archive_submission_claimed=0' "$contract"

require_contains 'archive denied publication evidence' "$contract"
require_contains 'write archive records' "$contract"
require_contains 're-request publication evidence' "$contract"
require_contains 'accept publication evidence' "$contract"
require_contains "$archive_gate_review_disposition_contract" "$contract"
require_contains "$archive_gate_contract" "$contract"
require_contains 'Add an Ubuntu publication evidence intake denial disposition closeout archive gate review disposition contract' "$contract"
require_contains 'Add an Ubuntu publication evidence intake denial disposition closeout archive gate review disposition closeout archive gate contract' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_contract: ok' "$contract"

for file in \
  "$archive_gate_contract" \
  "$closeout_contract" \
  "$disposition_contract" \
  "$review_contract" \
  "$denial_contract" \
  "$matrix_contract" \
  "$publication_gate" \
  "$static_validation" \
  "$readiness" \
  "$status" \
  packaging/ubuntu/README.md \
  README.md
do
  require_contains "$contract" "$file"
done

for file in "$status" packaging/ubuntu/README.md README.md
do
  require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' "$file"
  require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' "$file"
  require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$file"
  require_contains 'publication_evidence_denial_archive_gate_review_present=1' "$file"
  require_contains 'publication_evidence_denial_archive_gate_review_state=reviewed-upheld-no-effect' "$file"
  require_contains 'publication_evidence_denial_archive_gate_review_decision=uphold-closed-archive-gate' "$file"
  require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' "$file"
  require_contains 'publication_evidence_denial_archive_allowed=0' "$file"
  require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$file"
  require_contains 'publication_evidence_denial_archive_record_written=0' "$file"
done

require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_present=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_reviewed=1' "$status"
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_reviewed=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' packaging/ubuntu/README.md

require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-review-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'Ubuntu PPA Evidence Intake Denial Archive Gate Review Contract' "$workflow"
require_contains 'Run Ubuntu PPA archive publication evidence intake denial disposition closeout archive gate review guard' "$workflow"
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-review-contract.sh' "$workflow"
require_contains 'Ubuntu PPA Evidence Intake Denial Archive Gate Review Disposition Contract' "$archive_gate_review_disposition_workflow"
require_contains 'Run Ubuntu PPA archive publication evidence intake denial disposition closeout archive gate review disposition guard' "$archive_gate_review_disposition_workflow"
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.sh' "$archive_gate_review_disposition_workflow"

require_no_ubuntu_artifacts packaging/ubuntu

printf 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_contract: ok\n'

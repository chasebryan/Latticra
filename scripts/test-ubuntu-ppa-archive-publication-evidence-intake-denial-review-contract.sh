#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'ubuntu ppa/archive publication evidence intake denial review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'ubuntu ppa/archive publication evidence intake denial review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_no_ubuntu_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.deb' -o -name '*.dsc' -o -name '*.changes' -o -name '*.build' -o -name '*.buildinfo' \) -print | grep -q .; then
    printf 'ubuntu ppa/archive publication evidence intake denial review contract: unexpected Ubuntu package artifact under %s\n' "$dir" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md'
disposition_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md'
closeout_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md'
archive_gate_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
denial_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
matrix_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
publication_gate='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
workflow='.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.yml'
disposition_workflow='.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.yml'
closeout_workflow='.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.yml'
archive_gate_workflow='.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.yml'

require_file "$contract"
require_file "$disposition_contract"
require_file "$closeout_contract"
require_file "$archive_gate_contract"
require_file "$denial_contract"
require_file "$matrix_contract"
require_file "$publication_gate"
require_file "$static_validation"
require_file "$readiness"
require_file "$status"
require_file "$workflow"
require_file "$disposition_workflow"
require_file "$closeout_workflow"
require_file "$archive_gate_workflow"
require_file README.md
require_file docs/QUICK_START_CHEATSHEET.md
require_file packaging/ubuntu/README.md

require_contains 'Status: no-effect publication evidence intake denial review contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_review_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_state=denied-no-effect' "$contract"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'ubuntu_ppa_archive_publication_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_present=1' "$contract"
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$contract"
require_contains 'publication_evidence_denial_disposition_present=1' "$contract"
require_contains 'publication_evidence_denial_disposition_decision=close-upheld-denial' "$contract"
require_contains 'publication_evidence_denial_disposition_closeout_present=1' "$contract"
require_contains 'publication_evidence_denial_disposition_closeout_decision=closeout-upheld-denial' "$contract"
require_contains 'publication_evidence_denial_closed=1' "$contract"
require_contains 'publication_evidence_denial_archived=0' "$contract"
require_contains 'publication_evidence_denial_archive_allowed=0' "$contract"
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$contract"
require_contains 'publication_evidence_denial_archive_record_written=0' "$contract"
require_contains 'denial_review_required_before_re_request=1' "$contract"
require_contains 'publication_evidence_denial_review_present=1' "$contract"
require_contains 'publication_evidence_denial_review_decision=uphold-denial' "$contract"
require_contains 'publication_evidence_denial_re_request_allowed=0' "$contract"
require_contains 'ubuntu_publication_evidence_intake_allowed=0' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denied=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' "$contract"
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

require_contains 'publication_evidence_denial_reference' "$contract"
require_contains 'denial_review_identifier' "$contract"
require_contains 'ubuntu_target_series' "$contract"
require_contains 'requested_publication_evidence_kind' "$contract"
require_contains 'requested_publication_action' "$contract"
require_contains 'submitted_publication_transcript_reference' "$contract"
require_contains 'publication_promotion_blocker_matrix_reference' "$contract"
require_contains 'denial_review_decision' "$contract"
require_contains 'denial_review_reason' "$contract"
require_contains 'denial_review_reviewer' "$contract"
require_contains 'uphold-denial' "$contract"

require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_closed=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_review_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_closed=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_closed_out=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' "$contract"
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

require_contains 're-request publication evidence' "$contract"
require_contains 'accept publication evidence' "$contract"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' "$contract"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' "$contract"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.sh' "$contract"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.yml' "$contract"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md' "$contract"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.sh' "$contract"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.yml' "$contract"
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md' "$contract"
require_contains 'scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh' "$contract"
require_contains '.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.yml' "$contract"
require_contains 'Add an Ubuntu publication evidence intake denial disposition closeout archive gate review disposition closeout archive gate contract' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract: ok' "$contract"

require_contains "$contract" "$disposition_contract"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$disposition_contract"
require_contains 'publication_evidence_denial_disposition_decision=close-upheld-denial' "$disposition_contract"
require_contains "$contract" "$closeout_contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$closeout_contract"
require_contains 'publication_evidence_denial_disposition_closeout_decision=closeout-upheld-denial' "$closeout_contract"
require_contains "$contract" "$archive_gate_contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$archive_gate_contract"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$archive_gate_contract"
require_contains "$contract" "$denial_contract"
require_contains "$contract" "$matrix_contract"
require_contains "$contract" "$publication_gate"
require_contains "$contract" "$static_validation"
require_contains "$contract" "$readiness"
require_contains "$contract" "$status"
require_contains "$contract" packaging/ubuntu/README.md
require_contains "$contract" README.md
require_contains "$disposition_contract" "$denial_contract"
require_contains "$disposition_contract" "$matrix_contract"
require_contains "$disposition_contract" "$publication_gate"
require_contains "$disposition_contract" "$static_validation"
require_contains "$disposition_contract" "$readiness"
require_contains "$disposition_contract" "$status"
require_contains "$disposition_contract" packaging/ubuntu/README.md
require_contains "$disposition_contract" README.md
require_contains "$closeout_contract" "$denial_contract"
require_contains "$closeout_contract" "$matrix_contract"
require_contains "$closeout_contract" "$publication_gate"
require_contains "$closeout_contract" "$static_validation"
require_contains "$closeout_contract" "$readiness"
require_contains "$closeout_contract" "$status"
require_contains "$closeout_contract" packaging/ubuntu/README.md
require_contains "$closeout_contract" README.md
require_contains "$archive_gate_contract" "$denial_contract"
require_contains "$archive_gate_contract" "$matrix_contract"
require_contains "$archive_gate_contract" "$publication_gate"
require_contains "$archive_gate_contract" "$static_validation"
require_contains "$archive_gate_contract" "$readiness"
require_contains "$archive_gate_contract" "$status"
require_contains "$archive_gate_contract" packaging/ubuntu/README.md
require_contains "$archive_gate_contract" README.md

require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_review_contract_present=1' "$status"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_contract_present=1' "$status"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_contract_present=1' "$status"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' "$status"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$status"
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' "$status"
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$status"
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$status"
require_contains 'publication_evidence_denial_closed=1' "$status"
require_contains 'publication_evidence_denial_archive_gate_present=1' "$status"
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' "$status"
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' "$status"
require_contains 'publication_evidence_denial_review_present=1' "$status"
require_contains 'publication_evidence_denial_review_decision=uphold-denial' "$status"
require_contains 'publication_evidence_denial_re_request_allowed=0' "$status"
require_contains 'publication_evidence_denial_archived=0' "$status"
require_contains 'publication_evidence_denial_archive_allowed=0' "$status"
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$status"
require_contains 'publication_evidence_denial_archive_record_written=0' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_present=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_closed=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' "$status"
require_contains 'ubuntu_publication_evidence_intake_denial_closed_out=1' "$status"
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' "$status"
require_contains 'ubuntu_publication_denial_archive_record_written=0' "$status"

require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_review_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_closed=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_gate_present=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_review_present=1' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_review_decision=uphold-denial' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_re_request_allowed=0' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archived=0' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_allowed=0' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' packaging/ubuntu/README.md
require_contains 'publication_evidence_denial_archive_record_written=0' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_present=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_closed=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_upheld=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_evidence_intake_denial_closed_out=1' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' packaging/ubuntu/README.md
require_contains 'ubuntu_publication_denial_archive_record_written=0' packaging/ubuntu/README.md

require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1' README.md
require_contains 'ubuntu_publication_evidence_intake_denial_review_contract_present=1' README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_contract_present=1' README.md
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_contract_present=1' README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_contract_present=1' README.md
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_contract_present=1' README.md
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' README.md
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' README.md
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' README.md
require_contains 'publication_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' README.md
require_contains 'publication_evidence_intake_denial_disposition_state=closed-upheld-no-effect' README.md
require_contains 'publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect' README.md
require_contains 'publication_evidence_denial_closed=1' README.md
require_contains 'publication_evidence_denial_archive_gate_present=1' README.md
require_contains 'publication_evidence_denial_archive_gate_state=closed-no-effect' README.md
require_contains 'publication_evidence_denial_archive_gate_decision=deny-archive-and-re-request' README.md
require_contains 'publication_evidence_denial_review_present=1' README.md
require_contains 'publication_evidence_denial_review_decision=uphold-denial' README.md
require_contains 'publication_evidence_denial_re_request_allowed=0' README.md
require_contains 'publication_evidence_denial_archived=0' README.md
require_contains 'publication_evidence_denial_archive_allowed=0' README.md
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' README.md
require_contains 'publication_evidence_denial_archive_record_written=0' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md' README.md
require_contains 'docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md' README.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'Ubuntu PPA Archive Publication Evidence Intake Denial Review Contract' "$workflow"
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.sh' "$workflow"
require_contains 'Ubuntu PPA Archive Publication Evidence Intake Denial Disposition Contract' "$disposition_workflow"
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-contract.sh' "$disposition_workflow"
require_contains 'Ubuntu PPA Archive Publication Evidence Intake Denial Disposition Closeout Contract' "$closeout_workflow"
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-contract.sh' "$closeout_workflow"
require_contains 'Ubuntu PPA Archive Publication Evidence Intake Denial Disposition Closeout Archive Gate Contract' "$archive_gate_workflow"
require_contains 'sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh' "$archive_gate_workflow"

require_no_ubuntu_artifacts packaging/ubuntu

printf 'ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract: ok\n'

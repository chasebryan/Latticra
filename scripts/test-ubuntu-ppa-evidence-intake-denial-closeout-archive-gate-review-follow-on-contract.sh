#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

label='ubuntu ppa evidence intake denial closeout archive gate review follow-on contract'

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf '%s: missing file: %s\n' "$label" "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf '%s: missing required pattern in %s: %s\n' "$label" "$file" "$pattern" >&2
    exit 1
  fi
}

require_no_ubuntu_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.deb' -o -name '*.dsc' -o -name '*.changes' -o -name '*.build' -o -name '*.buildinfo' \) -print | grep -q .; then
    printf '%s: unexpected Ubuntu package artifact under %s\n' "$label" "$dir" >&2
    exit 1
  fi
}

contract='docs/UBUNTU_PPA_EVIDENCE_INTAKE_DENIAL_CLOSEOUT_ARCHIVE_GATE_REVIEW_FOLLOW_ON_CONTRACT.md'
predecessor_contract='docs/UBUNTU_PPA_EVIDENCE_INTAKE_DENIAL_CLOSEOUT_ARCHIVE_GATE_FOLLOW_ON_CONTRACT.md'
predecessor_closeout_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md'
matrix_contract='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
publication_gate='docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md'
static_validation='docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md'
readiness='docs/UBUNTU_READINESS_PLAN.md'
status='docs/status/UBUNTU_ECOSYSTEM_INTEGRATION_STATUS.md'
workflow='.github/workflows/ubuntu-ppa-evidence-closeout-archive-gate-review-follow-on.yml'
script='scripts/test-ubuntu-ppa-evidence-intake-denial-closeout-archive-gate-review-follow-on-contract.sh'

for file in \
  "$contract" \
  "$predecessor_contract" \
  "$predecessor_closeout_contract" \
  "$matrix_contract" \
  "$publication_gate" \
  "$static_validation" \
  "$readiness" \
  "$status" \
  "$workflow" \
  README.md \
  docs/README.md \
  docs/status/README.md \
  docs/QUICK_START_CHEATSHEET.md \
  packaging/ubuntu/README.md
do
  require_file "$file"
done

require_contains 'Status: no-effect publication evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract' "$contract"
require_contains 'physical filename is intentionally shortened' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'ubuntu_ppa_evidence_intake_denial_closeout_archive_gate_review_follow_on_contract_present=1' "$contract"
require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'publication_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'ubuntu_ppa_archive_publication_gate_state=closed-no-effect' "$contract"

require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_decision=uphold-closed-archive-gate' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'publication_evidence_denial_archived=0' "$contract"
require_contains 'publication_evidence_denial_archive_allowed=0' "$contract"
require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$contract"
require_contains 'publication_evidence_denial_archive_record_written=0' "$contract"
require_contains 'publication_evidence_denial_re_request_allowed=0' "$contract"
require_contains 'ubuntu_platform_publication_evidence_accepted=0' "$contract"
require_contains 'ubuntu_publication_result_promoted=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_identifier' "$contract"
require_contains 'publication_evidence_denial_reference' "$contract"
require_contains 'publication_evidence_intake_request_identifier' "$contract"
require_contains 'ubuntu_target_series' "$contract"
require_contains 'requested_publication_evidence_kind' "$contract"
require_contains 'publication_promotion_blocker_matrix_reference' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_decision' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_reason' "$contract"
require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_reviewer' "$contract"
require_contains 'uphold-closed-archive-gate' "$contract"

require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_present=1' "$contract"
require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_closed=1' "$contract"
require_contains 'ubuntu_publication_denial_archive_allowed=0' "$contract"
require_contains 'ubuntu_publication_denial_archive_record_write_allowed=0' "$contract"
require_contains 'ubuntu_publication_denial_archive_record_written=0' "$contract"
require_contains 'ubuntu_publication_denial_re_request_allowed=0' "$contract"
require_contains 'ubuntu_publication_transcript_intake_accepted=0' "$contract"
require_contains 'ubuntu_ppa_creation_evidence_accepted=0' "$contract"
require_contains 'ubuntu_launchpad_publication_evidence_accepted=0' "$contract"
require_contains 'ubuntu_archive_submission_evidence_accepted=0' "$contract"
require_contains 'debsign_run=0' "$contract"
require_contains 'dput_run=0' "$contract"
require_contains 'launchpad_upload_run=0' "$contract"

require_contains 'archive denied publication evidence' "$contract"
require_contains 'write archive records' "$contract"
require_contains 're-request publication evidence' "$contract"
require_contains 'accept publication evidence' "$contract"
require_contains "$predecessor_contract" "$contract"
require_contains 'Add an Ubuntu publication evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate can be relaxed or re-requested.' "$contract"
require_contains 'Add an Ubuntu publication evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review can be relaxed or re-requested.' "$contract"
require_contains 'ubuntu_ppa_evidence_intake_denial_closeout_archive_gate_review_follow_on_contract: ok' "$contract"

for file in \
  "$predecessor_contract" \
  "$predecessor_closeout_contract" \
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

require_contains 'UBUNTU_PPA_EVIDENCE_INTAKE_DENIAL_CLOSEOUT_ARCHIVE_GATE_REVIEW_FOLLOW_ON_CONTRACT.md' docs/README.md
require_contains 'UBUNTU_PPA_EVIDENCE_INTAKE_DENIAL_CLOSEOUT_ARCHIVE_GATE_REVIEW_FOLLOW_ON_CONTRACT.md' docs/status/README.md
require_contains 'UBUNTU_PPA_EVIDENCE_INTAKE_DENIAL_CLOSEOUT_ARCHIVE_GATE_REVIEW_FOLLOW_ON_CONTRACT.md' "$readiness"

for file in "$status" packaging/ubuntu/README.md README.md
do
  require_contains 'ubuntu_ppa_evidence_intake_denial_closeout_archive_gate_review_follow_on_contract_present=1' "$file"
  require_contains 'ubuntu_ppa_archive_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$file"
  require_contains 'ubuntu_publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$file"
  require_contains 'publication_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$file"
  require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' "$file"
  require_contains 'publication_evidence_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$file"
  require_contains 'publication_evidence_denial_archive_allowed=0' "$file"
  require_contains 'publication_evidence_denial_archive_record_write_allowed=0' "$file"
  require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' "$file"
  require_contains 'ubuntu_publication_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' "$file"
done

require_contains "sh $script" docs/QUICK_START_CHEATSHEET.md
require_contains "$script" "$readiness"
require_contains "sh $script" README.md
require_contains 'Ubuntu PPA Evidence Closeout Archive Gate Review Follow-On' "$workflow"
require_contains 'Run Ubuntu PPA evidence intake denial closeout archive gate review follow-on guard' "$workflow"
require_contains "sh $script" "$workflow"

require_no_ubuntu_artifacts packaging/ubuntu

sh -n "$0"

printf 'ubuntu_ppa_evidence_intake_denial_closeout_archive_gate_review_follow_on_contract: ok\n'

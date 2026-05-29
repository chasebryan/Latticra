#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

label='opensuse rpm evidence intake denial repeat closeout archive gate review contract'

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

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    printf '%s: unexpected RPM artifact under %s\n' "$label" "$dir" >&2
    exit 1
  fi
}

contract='docs/OPENSUSE_RPM_EVIDENCE_INTAKE_DENIAL_REPEAT_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md'
predecessor_contract='docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
predecessor_closeout_contract='docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md'
matrix_contract='docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
workflow='.github/workflows/opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review.yml'
next_disposition_contract='docs/OPENSUSE_RPM_EVIDENCE_INTAKE_DENIAL_REPEAT_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md'
next_disposition_script='scripts/test-opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-disposition-contract.sh'
next_disposition_workflow='.github/workflows/opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-disposition.yml'

for file in \
  "$contract" \
  "$predecessor_contract" \
  "$predecessor_closeout_contract" \
  "$matrix_contract" \
  docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md \
  docs/README.md \
  docs/status/README.md \
  docs/OPENSUSE_DEVELOPER_WORKFLOW.md \
  docs/OPENSUSE_READINESS_PLAN.md \
  docs/QUICK_START_CHEATSHEET.md \
  docs/packaging.html \
  packaging/opensuse/README.md \
  packaging/opensuse/latticra.spec \
  packaging/opensuse/latticra.changes \
  README.md \
  Makefile \
  "$workflow" \
  "$next_disposition_contract" \
  "$next_disposition_script" \
  "$next_disposition_workflow"
do
  require_file "$file"
done

require_contains 'Status: active RPM build-evidence intake denial repeat closeout archive gate review contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'fully expanded filename exceeds common filesystem filename limits' "$contract"
require_contains 'opensuse_rpm_evidence_intake_denial_repeat_closeout_archive_gate_review_contract_present=1' "$contract"
require_contains 'opensuse_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$contract"
require_contains 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$contract"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'validation_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'opensuse_rpm_build_gate_state=closed-no-effect' "$contract"

require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_decision=uphold-closed-archive-gate' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' "$contract"
require_contains 'denial_archived=0' "$contract"
require_contains 'denial_archive_allowed=0' "$contract"
require_contains 'denial_archive_record_write_allowed=0' "$contract"
require_contains 'denial_archive_record_written=0' "$contract"
require_contains 'denial_re_request_allowed=0' "$contract"
require_contains 'opensuse_build_evidence_intake_allowed=0' "$contract"
require_contains 'opensuse_build_evidence_intake_denied=1' "$contract"
require_contains 'opensuse_platform_build_evidence_accepted=0' "$contract"
require_contains 'source_archive_accepted_for_build=0' "$contract"
require_contains 'accepted_rpmlint_transcript_present=0' "$contract"
require_contains 'environment_transcript_present=0' "$contract"
require_contains 'explicit_operator_build_authorization=0' "$contract"
require_contains 'rpm_artifact_created=0' "$contract"
require_contains 'rpm_payload_accepted=0' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains 'opensuse_rpm_validation_result_promoted=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_identifier' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_reference' "$contract"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_reference' "$contract"
require_contains 'validation_promotion_blocker_matrix_reference' "$contract"
require_contains 'archive_record_write_authorization_reference' "$contract"
require_contains 'uphold-closed-archive-gate' "$contract"

require_contains 'opensuse_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' "$contract"
require_contains 'opensuse_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' "$contract"
require_contains 'opensuse_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_closed=1' "$contract"
require_contains 'opensuse_denial_archive_allowed=0' "$contract"
require_contains 'opensuse_denial_archive_record_write_allowed=0' "$contract"
require_contains 'opensuse_denial_archive_record_written=0' "$contract"
require_contains 'opensuse_denial_re_request_allowed=0' "$contract"
require_contains 'opensuse_rpmbuild_evidence_accepted=0' "$contract"
require_contains 'opensuse_osc_build_evidence_accepted=0' "$contract"
require_contains 'opensuse_rpmlint_evidence_accepted=0' "$contract"
require_contains 'rpmbuild_run=0' "$contract"
require_contains 'osc_build_run=0' "$contract"
require_contains 'rpmlint_run=0' "$contract"
require_contains 'osc_submitreq_run=0' "$contract"
require_contains 'opensuse_obs_publication_claimed=0' "$contract"

require_contains 'run rpmbuild' "$contract"
require_contains 'run osc build' "$contract"
require_contains 'request build evidence' "$contract"
require_contains 're-request build evidence' "$contract"
require_contains 'archive denied build evidence' "$contract"
require_contains 'write archive records' "$contract"
require_contains 'accept build evidence' "$contract"
require_contains 'claim package readiness' "$contract"

require_contains "$predecessor_contract" "$contract"
require_contains "$next_disposition_contract" "$contract"
require_contains "$contract" "$next_disposition_contract"
require_contains "$contract" "$next_disposition_script"
require_contains "$contract" "$next_disposition_workflow"
require_contains 'Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition contract' "$contract"
require_contains 'opensuse_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract: ok' "$contract"

for file in \
  "$predecessor_contract" \
  docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md \
  packaging/opensuse/README.md \
  README.md
do
  require_contains "$contract" "$file"
done

require_contains 'OPENSUSE_RPM_EVIDENCE_INTAKE_DENIAL_REPEAT_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_RPM_EVIDENCE_INTAKE_DENIAL_REPEAT_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_RPM_EVIDENCE_INTAKE_DENIAL_REPEAT_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'OPENSUSE_RPM_EVIDENCE_INTAKE_DENIAL_REPEAT_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md' docs/packaging.html

for file in \
  docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md \
  packaging/opensuse/README.md
do
  require_contains 'opensuse_rpm_evidence_intake_denial_repeat_closeout_archive_gate_review_contract_present=1' "$file"
  require_contains 'opensuse_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$file"
  require_contains 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$file"
  require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$file"
  require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' "$file"
  require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$file"
  require_contains 'denial_archive_allowed=0' "$file"
  require_contains 'denial_archive_record_write_allowed=0' "$file"
  require_contains 'denial_re_request_allowed=0' "$file"
  require_contains 'opensuse_platform_build_evidence_accepted=0' "$file"
  require_contains 'opensuse_rpm_validation_result_promoted=0' "$file"
done

require_contains 'opensuse_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' packaging/opensuse/README.md
require_contains 'opensuse_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' packaging/opensuse/README.md

require_contains 'sh scripts/test-opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-contract.sh' docs/OPENSUSE_DEVELOPER_WORKFLOW.md
require_contains 'sh scripts/test-opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-contract.sh' docs/OPENSUSE_READINESS_PLAN.md
require_contains 'sh scripts/test-opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-contract.sh' docs/QUICK_START_CHEATSHEET.md
require_contains 'sh scripts/test-opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-contract.sh' README.md

require_contains 'opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-contract:' Makefile
require_contains 'sh ./scripts/test-opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-contract.sh' Makefile

require_no_rpm_artifacts packaging/opensuse

require_contains 'Run openSUSE RPM build evidence intake denial repeat closeout archive gate review contract guard' "$workflow"
require_contains 'sh scripts/test-opensuse-rpm-evidence-intake-denial-repeat-closeout-archive-gate-review-contract.sh' "$workflow"

sh -n "$0"

printf 'opensuse_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract: ok\n'

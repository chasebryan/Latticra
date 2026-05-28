# openSUSE RPM Build-Evidence Intake Denial Contract

Status: active RPM build-evidence intake denial contract
Scope: define denial of openSUSE RPM build-evidence intake while the validation promotion blocker matrix is closed.

## Purpose

This contract records how openSUSE RPM build evidence must be refused until the validation promotion blocker matrix opens.

The goal is narrow: no `rpmbuild`, `osc build`, `rpmlint`, source RPM, binary RPM, payload, install/remove, or OBS evidence may be requested or accepted while the matrix remains blocked.

This contract is documentation-only and static. It does not run `rpmbuild`, run `osc`, run `rpmlint`, request build evidence, accept build evidence, create RPM artifacts, inspect RPM artifacts, install packages, remove packages, publish packages, submit Latticra to openSUSE, accept Open Build Service evidence, promote validation results, or claim package readiness.

## Current Intake Denial State

```text
opensuse_rpm_build_evidence_intake_denial_contract_present=1
rpm_build_evidence_intake_denial_contract_present=1
build_evidence_intake_denial_state=denied-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
opensuse_rpm_build_gate_state=closed-no-effect
opensuse_build_evidence_intake_allowed=0
opensuse_build_evidence_intake_requested=0
opensuse_build_evidence_intake_denied=1
opensuse_platform_build_evidence_accepted=0
build_transcript_intake_accepted=0
rpm_build_transcript_intake_accepted=0
rpmbuild_evidence_accepted=0
osc_build_evidence_accepted=0
rpmlint_evidence_accepted=0
source_rpm_evidence_accepted=0
binary_rpm_evidence_accepted=0
rpm_build_lane_opened=0
opensuse_single_platform_build_lane_opened=0
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
obs_publication_non_claim_review_present=1
rpm_validation_result_promoted=0
opensuse_rpm_validation_result_promoted=0
package_readiness_claimed=0
```

## Denial Reason Matrix

Current build-evidence intake denial is required because:

```text
build_evidence_denial_reason=validation-promotion-blocker-matrix-closed
source_archive_column_state=blocked
rpmlint_column_state=blocked
environment_column_state=blocked
artifact_column_state=blocked
payload_column_state=blocked
install_remove_column_state=blocked
promotion_column_state=blocked
obs_publication_non_claim_column_state=specified
denial_review_required_before_re_request=1
```

A future build-evidence intake request must record:

```text
build_evidence_intake_request_identifier
opensuse_target_distribution
requested_build_evidence_kind
requested_build_command
submitted_transcript_reference
source_archive_sha256
rpmlint_transcript_reference
environment_identifier
operator_authorization_reference
validation_promotion_blocker_matrix_reference
denial_decision
denial_reason
denial_reviewer
status_page_update_reference
```

The only current decision allowed by this contract is denial.

## openSUSE Intake Denial

Current openSUSE RPM build-evidence intake remains denied:

```text
opensuse_build_evidence_intake_allowed=0
opensuse_build_evidence_intake_requested=0
opensuse_build_evidence_intake_denied=1
opensuse_platform_build_evidence_accepted=0
opensuse_build_transcript_intake_accepted=0
opensuse_rpmbuild_evidence_accepted=0
opensuse_osc_build_evidence_accepted=0
opensuse_rpmlint_evidence_accepted=0
opensuse_source_rpm_evidence_accepted=0
opensuse_binary_rpm_evidence_accepted=0
rpmbuild_run=0
rpmbuild_ba_run=0
rpmbuild_bb_run=0
rpmbuild_bs_run=0
osc_build_run=0
rpmlint_run=0
osc_submitreq_run=0
obs_build_result_claimed=0
opensuse_obs_publication_claimed=0
opensuse_rpm_validation_result_promoted=0
opensuse_distribution_ready=0
```

openSUSE build, lint, artifact, payload, install/remove, OBS, submit-request, and official-package evidence may not be requested, received, accepted, summarized as successful, or used to open an openSUSE build lane while the blocker matrix is closed.

## Current Blockers

Build-evidence intake remains denied under this blocker state:

```text
validation_promotion_blocker_matrix_state=blocked-no-effect
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
opensuse_platform_build_evidence_accepted=0
rpm_validation_result_promoted=0
```

## Command Boundary

This contract does not:

```text
run rpmbuild
run osc build
run rpmlint
run osc branch
run osc commit
run osc submitreq
request build evidence
accept build evidence
create RPM artifacts
inspect RPM artifacts
install RPM packages
remove RPM packages
create an Open Build Service project
create an Open Build Service package
publish RPM artifacts
submit Latticra to openSUSE
promote openSUSE validation results
claim package readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
```

The local RPM build gate remains closed. This intake denial contract only records that build evidence cannot be requested or accepted until the validation promotion blocker matrix opens in a future lane.

## Next Slice

Completed follow-on RPM build-evidence intake denial review contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-review-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-review-contract.yml
```

That lane upholds the denied intake state while keeping build-evidence re-requests blocked.

Completed follow-on RPM build-evidence intake denial disposition contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-contract.yml
```

That lane closes the upheld denial without accepting openSUSE build evidence or opening RPM builds.

Completed follow-on RPM build-evidence intake denial disposition closeout contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-contract.yml
```

That lane closes out the no-effect disposition while keeping archive, re-request, build, and readiness blockers in place.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-contract.yml
```

That lane keeps the closed-out denial unarchived while archive, re-request, build, and readiness blockers stay in place.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review contract before any archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-contract.yml
```

That lane reviews and upholds the closed archive gate while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition contract before any reviewed archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.yml
```

That lane disposes the reviewed closed archive gate while preserving RPM build and readiness blockers.


Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout contract before any reviewed archive gate disposition can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-contract.yml
```

That lane closes out the reviewed archive gate disposition while preserving RPM build and readiness blockers.


Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate contract before any reviewed archive gate disposition closeout can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.yml
```

That lane keeps the reviewed archive gate disposition closeout unarchived while preserving RPM build and readiness blockers.


Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.yml
```

That lane reviews and upholds the reviewed archive gate disposition closeout archive gate while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.yml
```

That lane records the reviewed closeout archive gate as disposed while preserving RPM build and readiness blockers.


Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout contract before any reviewed archive gate disposition closeout archive gate review disposition can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-contract.yml
```

That lane closes out the reviewed closeout archive gate review disposition while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract before any reviewed archive gate disposition closeout archive gate review disposition closeout can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.yml
```

That lane keeps the reviewed closeout archive gate review disposition closeout unarchived while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.yml
```

That lane reviews and upholds the reviewed closeout archive gate review disposition closeout archive gate while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.yml
```

That lane records the reviewed closeout archive gate review disposition closeout archive gate review as disposed while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate review disposition can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-contract.yml
```

That lane closes out the reviewed closeout archive gate review disposition closeout archive gate review disposition while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate review disposition closeout can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.yml
```

That lane keeps the reviewed closeout archive gate review disposition closeout archive gate review disposition closeout unarchived while preserving RPM build and readiness blockers.

Recommended next slice:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate can be relaxed or re-requested.
```

That future lane should review the closed archive gate for the reviewed closeout archive gate review disposition closeout while preserving RPM build and readiness blockers.


Completed follow-on archive gate review record:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md
```

That follow-on review preserves the closed, no-effect archive gate posture and does not accept build evidence, create RPM artifacts, or claim package readiness.

## Validation

Run:

```sh
sh scripts/test-opensuse-rpm-build-evidence-intake-denial-contract.sh
```

Expected output:

```text
opensuse_rpm_build_evidence_intake_denial_contract: ok
```

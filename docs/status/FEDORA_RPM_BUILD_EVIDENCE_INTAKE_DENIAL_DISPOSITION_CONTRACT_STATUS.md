# Fedora RPM Build-Evidence Intake Denial Disposition Contract Status

Status: rpm-build-evidence-intake-denial-disposition/status alignment
Date: 2026-05-28
Scope: status record for the no-effect Fedora RPM build-evidence intake denial disposition contract.

## Summary

Latticra now has a no-effect Fedora RPM build-evidence intake denial disposition contract.

The disposition closes the upheld Fedora build-evidence intake denial while re-request authority remains closed.

It does not run `rpmbuild`, `mock`, `rpmlint`, `dnf`, `fedpkg`, `koji`, `bodhi`, or `copr-cli`.

It does not request build evidence, re-request denied evidence, accept build evidence, create RPM artifacts, inspect RPM artifacts, install packages, remove packages, create Bugzilla tickets, publish packages, submit to Fedora, promote validation results, or mutate a host.

## Current classification

```text
fedora_rpm_build_evidence_intake_denial_disposition_contract_present=1
fedora_rpm_build_evidence_intake_denial_review_contract_present=1
fedora_rpm_build_evidence_intake_denial_contract_present=1
fedora_package_validation_promotion_blocker_matrix_contract_present=1
rpm_build_evidence_intake_denial_disposition_contract_present=1
build_evidence_intake_denial_disposition_state=closed-upheld-no-effect
build_evidence_intake_denial_review_state=reviewed-upheld-no-effect
build_evidence_intake_denial_state=denied-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect
fedora_mock_build_gate_state=closed-no-effect
denial_disposition_present=1
denial_disposition_decision=close-upheld-denial
denial_review_present=1
denial_review_decision=uphold-denial
denial_closed=1
denial_re_request_allowed=0
fedora_denial_re_request_allowed=0
fedora_build_evidence_intake_allowed=0
fedora_build_evidence_intake_denied=1
fedora_platform_build_evidence_accepted=0
build_transcript_intake_accepted=0
rpm_build_transcript_intake_accepted=0
fedora_build_transcript_intake_accepted=0
rpm_build_lane_opened=0
fedora_single_platform_build_lane_opened=0
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
fedora_package_review_non_claim_present=1
fedora_package_validation_result_promoted=0
rpm_validation_result_promoted=0
package_validation_result_promoted=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
host_mutation_performed=0
```

## Guard validation

This status alignment is guarded by:

```sh
sh scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-contract.sh
```

Expected output:

```text
fedora_rpm_build_evidence_intake_denial_disposition_contract: ok
```

## Completed follow-on

```text
docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-contract.sh
.github/workflows/fedora-rpm-build-evidence-intake-denial-disposition-closeout-contract.yml
```

That lane closes out the disposed denial while keeping archive, re-request, build, package review, Fedora distribution, and production readiness blockers in place.

## Next recommended lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This status record is not Fedora build evidence, not `mock` evidence, not `rpmlint` evidence, not RPM artifact evidence, not Fedora package review evidence, not Bugzilla evidence, not reviewer approval, not dist-git evidence, not Koji evidence, not Bodhi evidence, not Rawhide evidence, not official package evidence, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.

# Fedora rpmlint Findings Classification

Status: active findings classification record
Scope: classify expected and unexpected `rpmlint` findings for the local-only Fedora spec draft without promoting package-readiness, production-installer, or Fedora distribution claims.

## Purpose

This record defines how `rpmlint` output from the Fedora static spec lane should be interpreted while `packaging/fedora/latticra.spec` remains a local-only draft.

The goal is to separate expected draft findings from findings that must block Fedora package promotion.

This record is classification only. It does not require a clean `rpmlint` result, run `rpmbuild`, run `mock`, create package artifacts, submit Latticra to Fedora, install Latticra, accept Fedora production-readiness evidence, or claim package readiness.

## Inputs

The classification applies to:

```text
packaging/fedora/latticra.spec
docs/FEDORA_RPMLINT_STATIC_SPEC_LANE.md
docs/FEDORA_RPMLINT_AVAILABILITY.md
docs/FEDORA_LOCAL_RPM_STATIC_VALIDATION.md
docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
scripts/test-fedora-rpmlint-static-spec-lane.sh
scripts/test-fedora-rpmlint-availability.sh
scripts/test-fedora-local-rpm-static-validation.sh
scripts/test-fedora-production-readiness-evidence-matrix.sh
```

## Expected Draft Finding Classes

These finding classes are expected while the package remains local-only:

```text
placeholder_version_or_release
local_only_release_marker
license_expression_review_pending
missing_real_source_archive
limited_payload_surface
draft_doc_payload_mapping
```

Expected draft findings do not unblock package readiness. They only explain why a local-only draft may produce `rpmlint` output before source archive, license, and maintenance evidence mature.

## Unexpected Finding Classes

These finding classes must be treated as blockers until separately reviewed:

```text
service_installation
systemd_mutation
kernel_module_payload
boot_path_payload
etc_path_payload
privileged_helper_payload
network_fetch_during_build
host_mutation_during_build
unreviewed_scriptlet
unowned_or_unsafe_file_path
license_claim_promotion
fedora_official_status_claim
fedora_distribution_claim
fedora_endorsement_claim
```

Unexpected findings do not automatically mean the package is unsafe; they mean the local-only draft has crossed a boundary that needs a separate review lane before promotion.

## Classification Output Shape

A future accepted `rpmlint` findings transcript should record:

```text
rpmlint_invocation
rpmlint_exit_status
rpmlint_output_present
expected_draft_findings_count
unexpected_findings_count
package_artifact_created
rpm_build_run
mock_build_run
fedora_package_review_ready
fedora_distribution_claimed
package_readiness_claimed
classification_decision
```

Current classification baseline:

```text
fedora_rpmlint_findings_classification_present=1
fedora_rpmlint_static_spec_lane_present=1
fedora_source_archive_reproducibility_contract_present=1
expected_draft_finding_classes_recorded=1
unexpected_finding_classes_recorded=1
accepted_rpmlint_transcript_present=0
expected_draft_findings_count_recorded=0
unexpected_findings_count_recorded=0
classification_decision=blocked-pending-reviewed-rpmlint-output
fedora_rpmlint_evidence_present=0
package_artifact_created=0
rpm_build_run=0
mock_build_run=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
```

## Promotion Rule

Package promotion remains blocked unless all of these are true:

```text
accepted_rpmlint_transcript_present=1
unexpected_findings_count=0
license_expression_reviewed=1
source_archive_reproducible=1
mock_build_transcript_present=1
install_remove_transcript_present=1
fedora_package_review_ready=1
fedora_distribution_claimed=0
fedora_official_package_claimed=0
fedora_endorsement_claimed=0
```

Until those conditions are met, `rpmlint` output is evidence for maintenance review only, not package readiness.

## Boundary

This record does not:

```text
run rpmlint
run rpmbuild
run mock
create package artifacts
submit Latticra to Fedora
install Latticra on a host
claim official Fedora package status
claim Fedora endorsement
claim Fedora distribution readiness
claim production installer readiness
claim production readiness
```

## Completed Follow-On Lane

Completed follow-on source archive reproducibility contract:

```text
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
scripts/test-fedora-source-archive-reproducibility-contract.sh
.github/workflows/fedora-source-archive-reproducibility-contract.yml
```

## Next Slice

Recommended next Fedora packaging evidence lane:

```text
Add a Fedora source archive transcript review validator before source archive evidence can be accepted for mock build or package review.
```

## Validation

This classification is guarded by:

```sh
sh scripts/test-fedora-rpmlint-findings-classification.sh
```

Expected output:

```text
fedora_rpmlint_findings_classification: ok
```

## Non-claims

This record is not `rpmlint` output, not a reviewed `rpmlint` transcript, not mock build evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.

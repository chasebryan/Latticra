# Fedora Source Archive Mock Build Input Handoff Contract

Status: no-effect mock-build input handoff contract
Scope: define the evidence required before accepted Fedora source archive evidence can become `rpmbuild` or `mock` input, without staging archives, running RPM builds, creating RPM artifacts, installing packages, or mutating a host.

## Purpose

This contract defines the boundary after the Fedora source archive accepted evidence acceptance gate.

It records the future RPM input layout and review evidence required before a Fedora source archive can be used by `rpmbuild` or `mock`.

It does not create a source archive.

It does not stage a source archive under `SOURCES/`.

It does not stage `packaging/fedora/latticra.spec` under `SPECS/`.

It does not write a `mock` configuration.

It does not run `rpmbuild`.

It does not run `mock`.

It does not run package managers.

It does not create source RPM or binary RPM artifacts.

It does not install packages.

It does not submit Latticra to Fedora.

It does not mutate a host.

```text
fedora_source_archive_mock_build_input_handoff_contract_present=1
fedora_source_archive_accepted_evidence_acceptance_gate_present=1
source_archive_mock_build_input_handoff_contract_state=closed-no-effect
mock_build_input_handoff_allowed=0
source_archive_accepted_evidence_acceptance_gate_report_valid=0
source_archive_accepted_evidence_acceptance_gate_reviewed=0
source_archive_accepted_for_build_candidate_valid=0
candidate_source_archive_accepted_for_build=0
candidate_fedora_mock_build_input_opened=0
source_archive_handoff_to_rpmbuild_allowed=0
source_archive_handoff_to_mock_allowed=0
source_archive_handoff_written_by_contract=0
fedora_rpm_input_layout_documented=1
fedora_rpmbuild_sources_archive_staged=0
fedora_rpmbuild_specs_spec_staged=0
fedora_mock_build_input_opened_by_handoff_contract=0
rpmbuild_allowed=0
mock_build_allowed=0
rpmbuild_run=0
mock_build_run=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
```

## Future RPM Input Layout

A future handoff may only stage inputs under a disposable validation workdir with this shape:

```text
fedora-rpm-input/BUILD/
fedora-rpm-input/BUILDROOT/
fedora-rpm-input/RPMS/
fedora-rpm-input/SOURCES/latticra-0.0.0.tar.gz
fedora-rpm-input/SPECS/latticra.spec
fedora-rpm-input/SRPMS/
```

The staged source archive name and root must match the Fedora spec:

```text
Source0:        %{name}-%{version}.tar.gz
%autosetup -n %{name}-%{version}
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
```

## Required Future Handoff Evidence

The handoff remains closed unless all of these have been reviewed and recorded:

```text
source_archive_accepted_evidence_acceptance_gate_report_valid=1
source_archive_accepted_evidence_acceptance_gate_reviewed=1
source_archive_accepted_evidence_status_written=1
source_archive_accepted_evidence_present=1
source_archive_accepted=1
source_archive_accepted_for_build=1
fedora_mock_build_input_opened=1
source_archive_sha256_recorded=1
source_archive_reproducible=1
source_archive_path_safety_checked=1
source_archive_symlink_policy_checked=1
fedora_rpmlint_findings_classification_present=1
accepted_rpmlint_transcript_present=1
license_expression_reviewed=1
package_notice_obligations_reviewed=1
fedora_rpm_input_layout_documented=1
disposable_validation_environment=1
explicit_operator_build_authorization=1
```

Those future values are prerequisites, not current claims.

## Current Gate Rule

The current handoff state is closed:

```text
source_archive_handoff_to_rpmbuild_allowed=0
source_archive_handoff_to_mock_allowed=0
rpmbuild_allowed=0
mock_build_allowed=0
```

The contract alone cannot turn an accepted evidence status review report into build input.

The contract alone cannot stage the source archive for `rpmbuild`.

The contract alone cannot stage the source archive for `mock`.

The contract alone cannot create source RPMs or binary RPMs.

The contract alone cannot claim package review readiness, Fedora distribution readiness, production installer readiness, or production readiness.

## Command Boundary

All Fedora package build commands remain blocked while the current handoff state is `closed-no-effect`.

Fedora build commands blocked by this contract:

```text
rpmbuild -bs
rpmbuild -ba
rpmbuild -bb
mock --buildsrpm
mock -r
dnf builddep
```

Fedora package and publication effect commands blocked by this contract:

```text
rpm install local RPM artifact
dnf install local RPM artifact
install package on host
remove package from host
publish package artifact
submit package review
claim official Fedora package status
claim Fedora endorsement
claim production readiness
```

## Required Source Records

This contract depends on:

```text
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md
docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE_STATUS.md
scripts/fedora-source-archive-accepted-evidence-acceptance-gate.sh
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
packaging/fedora/latticra.spec
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-source-archive-mock-build-input-handoff-contract.sh
```

Expected output:

```text
fedora_source_archive_mock_build_input_handoff_contract: ok
```

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This contract is not a source archive transcript, not source archive acceptance, not written evidence status, not mock build evidence, not source RPM evidence, not binary RPM evidence, not package-review approval, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.

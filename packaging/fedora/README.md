# Fedora Packaging Draft

Status: local-only packaging draft

This directory contains Fedora-oriented packaging experiments for Latticra.

The current spec is a local-only draft used by static guards. It is not a Fedora package submission, not Fedora approval evidence, not a Copr build record, not a mock build result, and not package-readiness evidence.

## Where this fits

- Documentation hub: [`../../docs/README.md`](../../docs/README.md)
- Fedora workflow: [`../../docs/FEDORA_DEVELOPER_WORKFLOW.md`](../../docs/FEDORA_DEVELOPER_WORKFLOW.md)
- Fedora readiness plan: [`../../docs/FEDORA_READINESS_PLAN.md`](../../docs/FEDORA_READINESS_PLAN.md)
- Current status: [`../../docs/status/CURRENT_STATUS.md`](../../docs/status/CURRENT_STATUS.md)

Current guarded files:

```text
packaging/fedora/latticra.spec
packaging/fedora/README.md
scripts/test-fedora-spec-static.sh
scripts/test-fedora-local-rpm-static-validation.sh
scripts/test-fedora-rpmlint-static-spec-lane.sh
scripts/test-fedora-local-mock-build-gate-contract.sh
scripts/test-fedora-local-mock-build-environment-contract.sh
scripts/test-fedora-rpm-artifact-naming-contract.sh
scripts/test-fedora-rpm-payload-inspection-contract.sh
docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md
docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md
docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md
.github/workflows/fedora-spec-static.yml
.github/workflows/fedora-local-rpm-static-validation.yml
.github/workflows/fedora-rpmlint-static-spec-lane.yml
.github/workflows/fedora-local-mock-build-gate-contract.yml
.github/workflows/fedora-local-mock-build-environment-contract.yml
.github/workflows/fedora-rpm-artifact-naming-contract.yml
.github/workflows/fedora-rpm-payload-inspection-contract.yml
```

The static lanes preserve:

```text
fedora_local_mock_build_gate_contract_present=1
fedora_local_mock_build_environment_contract_present=1
fedora_rpm_artifact_naming_contract_present=1
fedora_rpm_payload_inspection_contract_present=1
fedora_mock_build_gate_state=closed-no-effect
fedora_mock_build_environment_contract_state=specified-no-effect
fedora_rpm_artifact_naming_contract_state=specified-no-effect
fedora_rpm_payload_inspection_contract_state=specified-no-effect
fedora_build_environment_provisioned=0
fedora_mock_build_environment_provisioned=0
local_only_draft=1
package_artifact_created=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
repository_rpm_artifact_write_allowed=0
rpm_payload_inspection_run=0
rpm_payload_accepted=0
rpmbuild_run_required=0
rpmbuild_allowed=0
mock_build_allowed=0
dnf_builddep_allowed=0
mock_run_required=0
fedora_submission_claimed=0
fedora_approval_claimed=0
production_readiness_claimed=0
```

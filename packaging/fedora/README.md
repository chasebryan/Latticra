# Fedora Packaging Draft

Status: local-only packaging draft

This directory contains Fedora-oriented packaging experiments for Latticra.

The current spec is a local-only draft used by static guards. It is not a Fedora package submission, not Fedora approval evidence, not a Copr build record, not a mock build result, and not package-readiness evidence.

Current guarded files:

```text
packaging/fedora/latticra.spec
packaging/fedora/README.md
scripts/test-fedora-spec-static.sh
scripts/test-fedora-local-rpm-static-validation.sh
scripts/test-fedora-rpmlint-static-spec-lane.sh
.github/workflows/fedora-spec-static.yml
.github/workflows/fedora-local-rpm-static-validation.yml
.github/workflows/fedora-rpmlint-static-spec-lane.yml
```

The static lanes preserve:

```text
local_only_draft=1
package_artifact_created=0
rpmbuild_run_required=0
mock_run_required=0
fedora_submission_claimed=0
fedora_approval_claimed=0
production_readiness_claimed=0
```

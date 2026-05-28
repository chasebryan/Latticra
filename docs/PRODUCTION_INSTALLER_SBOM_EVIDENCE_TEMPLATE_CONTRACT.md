# Production Installer SBOM Evidence Template Contract

Status: no-effect SBOM evidence template contract
Evidence level: 10 target, template only
Scope: print the required future production-installer SBOM evidence bundle shape without generating an SBOM, calculating evidence hashes, writing evidence files, accepting evidence, attaching an SBOM, passing promotion, publishing, installing, invoking package managers, using network access, or mutating the host.

## Purpose

The SBOM evidence intake validator can validate a complete future SBOM evidence bundle, but the bundle still needs a stable, reviewable shape before a release operator can collect SBOM, dependency-review, vulnerability-review, license-review, and final-review evidence safely.

This contract records a no-effect stdout-only template for that future evidence bundle. It mirrors the validator's required fields and keeps placeholder digest values intentionally invalid until real SBOM and review files exist.

It does not write the evidence file and does not make a candidate valid.

## Command

```sh
sh scripts/production-installer-sbom-evidence-template.sh
```

## Current classification

```text
sbom_evidence_template_present=1
sbom_evidence_template_mode=no-effect-template
sbom_evidence_template_decision=blocked-template-only-no-evidence-write
sbom_evidence_template_complete=0
sbom_evidence_intake_validator_present=1
sbom_evidence_intake_validation_mode=no-effect-validation
sbom_artifact_file_present=<observed>
sbom_dependency_review_file_present=<observed>
sbom_vulnerability_review_file_present=<observed>
sbom_license_review_file_present=<observed>
sbom_review_file_present=<observed>
sbom_generated_by_template=0
sbom_evidence_written_by_template=0
sbom_evidence_accepted_by_template=0
sbom_evidence_accepted_by_intake_validator=0
sbom_evidence_written_by_intake_validator=0
installer_sbom_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_sbom_recorded=0
sbom_attached_to_release_artifact=0
release_artifact_created=0
source_archive_created=0
rpm_build_invoked=0
rpmbuild_invoked=0
rpm_invoked=0
artifact_published=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
production_installer_ready=0
```

## Required evidence fields

The template must print the same required field names that the intake validator expects:

```text
LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE
sbom_evidence_status=complete
sbom_artifact_present=1
sbom_format_declared=1
sbom_format=spdx-json
sbom_component_inventory_present=1
sbom_dependency_reviewed=1
sbom_vulnerability_reviewed=1
sbom_license_reviewed=1
sbom_reviewed=1
installer_sbom_recorded=1
sbom_artifact_sha256=<required-sbom-sha256>
sbom_dependency_review_sha256=<required-dependency-review-sha256>
sbom_vulnerability_review_sha256=<required-vulnerability-review-sha256>
sbom_license_review_sha256=<required-license-review-sha256>
sbom_review_sha256=<required-sbom-review-sha256>
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

The `sbom_format=spdx-json` line may be replaced with `sbom_format=cyclonedx-json` when the supplied SBOM file uses CycloneDX JSON markers. The placeholders above must be replaced with real SHA-256 values before the evidence intake validator can pass.

## Required source records

The template binds the current blocked SBOM posture:

```text
production_installer_ready=0
sbom_evidence_intake_validator_present=1
sbom_evidence_status=complete
release_artifact_promotion_gate_passed=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-sbom-evidence-template-contract.sh
```

Expected output:

```text
production_installer_sbom_evidence_template_contract: ok
```

## Next implementation lane

```text
Use the template after a tagged release artifact candidate exists, fill real SHA-256 values from the SBOM, dependency-review, vulnerability-review, license-review, and final SBOM-review files, then validate the completed evidence bundle with the SBOM evidence intake validator.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This template is not a generated SBOM, not SBOM review, not evidence acceptance, not evidence writing, not SBOM attachment, not artifact publication, not artifact promotion, not release artifact evidence, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not recovery validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not host mutation, and not production installer readiness.

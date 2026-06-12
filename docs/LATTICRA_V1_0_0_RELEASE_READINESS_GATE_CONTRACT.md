# Latticra v1.0.0 Release Readiness Gate Contract

Status: no-effect v1.0.0 release readiness gate contract
Evidence level: release-blocker aggregation only
Scope: aggregate the existing release, installer, SBOM, transcript, lifecycle, recovery, multi-VM, Fedora, Nadia, Q-Seal, and runtime-authority blockers before any v1.0.0 release claim.

## Purpose

The repository now has many local quality and production-readiness records. A green local quality run is useful, but it is not enough to claim that Latticra is ready for a `v1.0.0` release.

This gate gives the v1.0.0 release question one executable no-effect decision. It reports the current blocker set and keeps the release closed while the existing production evidence gates still report missing artifacts, missing evidence, or closed authority.

It does not create release artifacts, sign artifacts, generate an SBOM, accept evidence, write evidence, install packages, publish tags, push commits, or mutate the host.

## Command

```sh
sh scripts/latticra-v1-release-readiness-gate.sh --version v1.0.0
```

## Current classification

```text
v1_release_readiness_gate_present=1
v1_release_readiness_gate_mode=no-effect-release-readiness-aggregation
v1_release_readiness_gate_version=v1.0.0
v1_release_readiness_gate_passed=0
v1_release_readiness_blocked=1
v1_release_readiness_decision=blocked-existing-production-evidence-gates-open
v1_release_required_gate_count=22
v1_release_satisfied_gate_count=<observed>
v1_release_blocker_count=<observed>
v1_release_blockers=<observed>
v1_release_workspace_resolvable_blocker_count=<observed>
v1_release_release_decision_blocker_count=<observed>
v1_release_external_prerequisite_blocker_count=<observed>
v1_release_evidence_blocker_count=8
v1_release_product_completion_blocker_count=8
v1_release_next_workspace_action=<observed>
current_edge_checkpoint=v0.3.0edge
next_main_edge_line=v0.4.0edge
v1_tag=v1.0.0
v1_tag_exists=0
v1_tag_commit=missing
v1_release_candidate_declared=0
v1_public_release_allowed=0
production_platform_claim_allowed=0
production_release_ready=0
production_installer_ready=0
production_ai_claimed=0
production_cryptography_claimed=0
production_enforcement_claimed=0
release_artifact_promotion_gate_passed=0
release_artifact_present=0
release_artifact_built_from_tag=0
release_artifact_reproducible=0
release_artifact_sha256_recorded=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
rpmbuild_available=<observed>
rpm_available=<observed>
release_signing_identity_reference_present=<observed>
release_signing_identity_reference_format_valid=<observed>
release_artifact_evidence_accepted=0
sbom_evidence_candidate_valid=0
sbom_evidence_accepted_by_intake_validator=0
transcript_evidence_candidate_valid=0
transcript_evidence_accepted_by_intake_validator=0
lifecycle_evidence_candidate_valid=0
lifecycle_evidence_accepted_by_intake_validator=0
recovery_evidence_candidate_valid=0
recovery_evidence_accepted_by_intake_validator=0
multi_vm_evidence_candidate_valid=0
multi_vm_evidence_accepted_by_intake_validator=0
fedora_production_readiness_evidence_complete=0
fedora_production_readiness_promotion_allowed=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
production_nadia_ready=0
nadia_public_release_allowed=0
q_seal_runtime_crypto_ready=0
q_seal_production_crypto_claim_allowed=0
runtime_authority_granted=0
```

The current blocker vocabulary includes `v1_release_tag_missing_or_not_approved`, `rpmbuild_toolchain_missing`, `rpm_toolchain_missing`, `release_signing_identity_reference_missing_or_invalid`, `release_artifact_not_promoted`, `sbom_evidence_not_accepted`, `multi_vm_evidence_not_accepted`, `nadia_production_readiness_blocked`, and `q_seal_runtime_crypto_blocked`.

## Required source records

The gate binds these existing records:

```text
README.md
STATUS.md
docs/status/CURRENT_STATUS.md
docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
docs/status/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md
docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md
latticra-q-seal/evidence/Q_SEAL_READINESS.md
```

## Pass requirements

This gate may report `v1_release_readiness_gate_passed=1` only after a future reviewed record closes all of these blockers:

```text
v1_tag_exists=1
current_edge_checkpoint_not_v1=0
production_platform_claim_allowed=1
production_release_ready=1
production_installer_ready=1
rpmbuild_available=1
rpm_available=1
release_signing_identity_reference_present=1
release_signing_identity_reference_format_valid=1
release_artifact_promotion_gate_passed=1
release_artifact_present=1
release_artifact_built_from_tag=1
release_artifact_reproducible=1
release_artifact_sha256_recorded=1
release_artifact_signature_verified=1
release_artifact_evidence_accepted=1
sbom_evidence_accepted_by_intake_validator=1
transcript_evidence_accepted_by_intake_validator=1
lifecycle_evidence_accepted_by_intake_validator=1
recovery_evidence_accepted_by_intake_validator=1
multi_vm_evidence_accepted_by_intake_validator=1
fedora_production_readiness_evidence_complete=1
production_nadia_ready=1
q_seal_runtime_crypto_ready=1
runtime_authority_granted=<reviewed-release-authority>
tracked_worktree_clean=1
untracked_worktree_clean=1
```

Any pass record must preserve the relevant evidence, non-claim, and authority-review records; it must not infer readiness from the presence of templates or validators alone.

## Validation

```sh
sh scripts/test-latticra-v1-release-readiness-gate-contract.sh
```

## Non-claims

This contract is not a v1.0.0 release, not a release candidate, not a product-readiness claim, not installer readiness, not AI readiness, not runtime authority, not production cryptography, not Fedora approval, not a distribution claim, and not permission to publish a tag or artifact.

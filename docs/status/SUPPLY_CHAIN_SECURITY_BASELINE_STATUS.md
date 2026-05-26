# Latticra Supply-Chain Security Baseline Status

Status: status record for supply-chain security baseline
Date: 2026-05-26

## Scope

This record tracks the supply-chain security baseline for repository, CI, dependency, package, installer, artifact, SBOM, release, and update-lane posture.

It does not publish artifacts, release packages, add signing authority, claim SLSA level, claim NIST compliance, claim CISA CPG compliance, claim production readiness, or grant release authority.

## Current fields

```text
supply_chain_security_baseline_present=1
supply_chain_security_status_present=1
supply_chain_security_guard_present=1
high_assurance_security_baseline_present=1
ssdf_supply_chain_profile_present=1
cpg_supply_chain_profile_present=1
sbom_required_before_production_installer=1
kev_nvd_review_required_before_release=1
dependency_inventory_required=1
pinned_ci_actions_required=1
read_only_workflow_permissions_required=1
persist_credentials_false_required=1
pull_request_target_forbidden=1
repository_secret_use_requires_dedicated_review=1
implicit_github_token_use_requires_dedicated_review=1
repository_secret_filename_scan_required=1
repository_secret_content_marker_scan_required=1
sensitive_local_artifact_filename_guard_required=1
report_redaction_boundary_guard_required=1
whole_environment_report_dump_forbidden=1
installer_engine_log_redaction_required=1
locked_dependency_builds_required=1
offline_installer_builds_required=1
ad_hoc_network_client_commands_forbidden_without_guard=1
source_archive_fixture_tracked_unignored_source_view_required=1
source_archive_fixture_symlink_refusal_required=1
source_archive_fixture_reproducible_metadata_required=1
release_publishing_authority_granted=0
production_installer_claim_allowed=0
production_update_claim_allowed=0
compliance_claim_allowed=0
certification_claim_allowed=0
external_endorsement_claimed=0
```

## Validation

```sh
sh scripts/test-supply-chain-security-baseline.sh
sh scripts/test-secret-material-guard.sh
sh scripts/test-report-redaction-boundary.sh
```

Expected output:

```text
supply_chain_security_baseline: ok
```

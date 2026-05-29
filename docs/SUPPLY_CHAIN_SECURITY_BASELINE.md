# Latticra Supply-Chain Security Baseline

Status: supply-chain security baseline
Source refresh date: 2026-05-26
Scope: repository, CI, dependency, package, installer, artifact, SBOM, release, and update-lane security posture for current Latticra work.

This baseline turns the supply-chain requirements in `docs/HIGH_ASSURANCE_SECURITY_BASELINE.md` into a guarded local project contract.

It also carries forward the stricter update-lane, command-boundary, and integrity expectations implied by NIST SP 800-53 Release 5.2.0, CISA KEV practice, and the CISA secure-design alert on OS command injection.

It does not publish artifacts, release packages, add signing authority, claim SLSA level, claim NIST compliance, claim CISA CPG compliance, or make Latticra production-ready.

## Current Fields

```text
supply_chain_security_baseline_present=1
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
repository_source_symlink_refusal_required=1
repository_secret_filename_scan_required=1
repository_secret_content_marker_scan_required=1
sensitive_local_artifact_filename_guard_required=1
report_redaction_boundary_guard_required=1
whole_environment_report_dump_forbidden=1
installer_engine_log_redaction_required=1
installer_engine_log_sanitization_required=1
installer_engine_log_line_length_cap_required=1
installer_engine_event_boundary_sanitization_required=1
installer_engine_failure_event_sanitization_required=1
installer_ui_event_ingestion_sanitization_required=1
installer_ui_evidence_log_redaction_required=1
installer_ui_status_event_sanitization_required=1
installer_ui_status_boundary_required=1
installer_ui_direct_status_assignment_forbidden=1
installer_ui_blocked_plan_sanitization_required=1
installer_ui_blocked_plan_error_injection_guard_required=1
installer_config_authority_slug_allowlist_required=1
installer_command_wrapper_strict_name_required=1
installer_ui_artifact_authority_guard_required=1
installer_ui_artifact_write_validation_required=1
installer_console_output_authority_guard_required=1
installer_console_config_reflection_denial_required=1
installer_console_control_character_sanitization_required=1
installer_console_secret_redaction_required=1
installer_console_line_length_cap_required=1
installer_ui_console_navigation_root_boundary_required=1
installer_ui_console_navigation_path_reflection_denial_required=1
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

## Current Guarded Controls

| Surface | Current control | Evidence |
| --- | --- | --- |
| GitHub workflows | actions pinned to approved commit SHAs | `scripts/test-quality-safety-guards.sh` |
| GitHub token permissions | workflows require explicit read-only repository permissions | `scripts/test-quality-safety-guards.sh` |
| Checkout credentials | checkout steps require `persist-credentials: false` | `scripts/test-quality-safety-guards.sh` |
| Pull request trust boundary | `pull_request_target` is forbidden | `scripts/test-quality-safety-guards.sh` |
| Secrets and tokens | workflow secret and implicit token use are blocked without a dedicated guard | `scripts/test-quality-safety-guards.sh` |
| Repository source hygiene | source-scope symlinks, secret-bearing filenames, private-key blocks, and common live-token markers are blocked from source files | `scripts/test-secret-material-guard.sh` |
| Report and log redaction | whole-environment dumps, shell xtrace, and unredacted installer child logs are blocked | `scripts/test-report-redaction-boundary.sh` |
| Installer engine logs | child stdout/stderr lines are redacted, escaped, and length-bounded before entering evidence logs | `scripts/test-installer-engine-log-sanitization.sh` |
| Installer engine event boundary | internal log and failure events are redacted, escaped, and length-bounded through one engine send boundary | `scripts/test-installer-engine-event-boundary.sh` |
| Installer UI event ingestion | Panel status and evidence logs redact, escape, and length-bound engine event text before rendering | `scripts/test-installer-ui-event-ingestion-sanitization.sh` |
| Installer UI status boundary | Panel status updates are routed through one redacting, escaping, length-bounded setter | `scripts/test-installer-ui-status-boundary.sh` |
| Installer UI blocked plan | blocked plan validation errors are redacted, escaped, and length-bounded before record rendering | `scripts/test-installer-ui-blocked-plan-sanitization.sh` |
| Installer config authority labels | profile, strategy, channel, and command-wrapper values are constrained to reviewed ASCII slug/name allowlists before rendering or install | `scripts/test-installer-config-authority-allowlist.sh` |
| Installer UI artifacts | Panel save/plan paths validate and sanitize authority fields before writing config or plan artifacts | `scripts/test-installer-ui-artifact-authority.sh` |
| Installer console output | Panel console report commands validate authority fields before reflecting config-derived values | `scripts/test-installer-console-output-authority.sh` |
| Installer console display | Panel console lines are escaped, redacted, and length-bounded before rendering | `scripts/test-installer-console-display-sanitization.sh` |
| Installer console navigation | Panel `cd` navigation is constrained to the panel workspace root and rejects host-path reflection on failures | `scripts/test-installer-ui-console-navigation-boundary.sh` |
| Workflow network clients | ad hoc `curl`, `wget`, SSH, FTP, and netcat-style commands are blocked without a dedicated guard | `scripts/test-quality-safety-guards.sh` |
| Package-manager mutation | package-manager use is limited to reviewed workflow/script allowlists | `scripts/test-quality-safety-guards.sh` |
| Source archive fixtures | package source archives require tracked/unignored source selection, symlink refusal, and deterministic tar/gzip metadata | `scripts/test-quality-safety-guards.sh` |
| Rust installer dependency use | local quality uses `cargo check --locked` | `Makefile` |
| Live installer build path | installer apply script requires locked offline Cargo builds and keeps the process-launch boundary centralized | `installer/scripts/latticra-installer-apply.sh` |
| Local installer artifacts | SBOM path is explicit and currently `none` for non-production fixtures | `docs/LOCAL_INSTALLER_ARTIFACT_MANIFEST_CONTRACT.md` |
| Boot artifact manifest fixture | SBOM fields are required before real boot artifact acceptance | `docs/SEABIOS_GRUB_BOOT_PREVIEW_BOOT_ARTIFACT_MANIFEST_VALIDATION.md` |
| Ubuntu package readiness | third-party material, notice, license, generated-artifact, and trademark reviews remain blocked until formal review | `docs/UBUNTU_READINESS_PLAN.md` |

## Required Release Gate

No production package, production installer, internet-facing service, update lane, boot artifact, or release artifact may be described as production-ready until the following gate is complete:

```text
release_artifact_inventory_present=1
sbom_present=1
sbom_reviewed=1
dependency_inventory_reviewed=1
third_party_material_reviewed=1
license_notice_reviewed=1
kev_nvd_review_completed=1
known_exploited_vulnerability_mitigation_recorded=1
workflow_write_permission_reviewed=1
release_secret_boundary_reviewed=1
artifact_integrity_hashes_recorded=1
signing_authority_contract_present=1
update_payload_integrity_reviewed=1
update_authenticity_path_reviewed=1
update_rollback_evidence_present=1
command_boundary_reviewed=1
rollback_or_recovery_contract_present=1
vulnerability_disclosure_path_present=1
production_non_claim_review_completed=1
```

Until this gate is complete, the required posture is:

```text
sbom_present_for_production_release=0
release_artifact_published=0
release_signing_performed=0
release_secret_access_granted=0
release_write_token_granted=0
production_installer_claim_allowed=0
production_update_claim_allowed=0
production_security_claim_allowed=0
```

## Dependency Review Rules

Every new dependency, vendored artifact, generated artifact, or bundled binary requires:

- purpose and ownership;
- license and notice review;
- security history review where practical;
- transitive dependency review where practical;
- KEV/NVD check before release or documented offline exception;
- build reproducibility note where practical;
- update authenticity and integrity impact review where the dependency can affect installer, package, or update behavior;
- removal or replacement plan if the dependency becomes unsuitable.

## CI Authority Rules

CI changes must preserve:

- explicit workflow permissions;
- read-only default repository token posture;
- no `pull_request_target`;
- no repository secrets without dedicated review;
- no implicit `GITHUB_TOKEN`, `GH_TOKEN`, `ACTIONS_ID_TOKEN`, or runtime token use without dedicated review;
- no source-scope symlink entries that can bypass source or secret-material scans;
- no committed local secret files, private-key blocks, or common live-token markers in repository source;
- no whole-environment dumps, shell xtrace, or unredacted child-process output in report/log paths;
- no installer profile, update-channel, strategy, or command-wrapper string may cross into plans, config artifacts, or install scripts unless it passes the authority slug/name allowlist;
- no installer UI save or plan artifact may be written from an unvalidated or network-authority-enabled config;
- no ad hoc network client commands without dedicated review;
- no new command-construction or shell-interpolation path without a dedicated command-boundary review;
- no mutating update lane without integrity, authenticity, validation, and rollback evidence;
- no release publishing without an explicit release-authority contract.

## Validation

This baseline is guarded by:

```sh
sh scripts/test-supply-chain-security-baseline.sh
sh scripts/test-secret-material-guard.sh
sh scripts/test-report-redaction-boundary.sh
sh scripts/test-installer-engine-log-sanitization.sh
sh scripts/test-installer-engine-event-boundary.sh
sh scripts/test-installer-ui-event-ingestion-sanitization.sh
sh scripts/test-installer-ui-status-boundary.sh
sh scripts/test-installer-ui-blocked-plan-sanitization.sh
sh scripts/test-installer-config-authority-allowlist.sh
sh scripts/test-installer-ui-artifact-authority.sh
sh scripts/test-installer-console-output-authority.sh
sh scripts/test-installer-console-display-sanitization.sh
sh scripts/test-installer-ui-console-navigation-boundary.sh
```

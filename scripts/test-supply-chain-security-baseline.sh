#!/usr/bin/env sh
set -eu

doc="docs/SUPPLY_CHAIN_SECURITY_BASELINE.md"
status_doc="docs/status/SUPPLY_CHAIN_SECURITY_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'supply chain security baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'supply chain security baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/MEMORY_SAFETY_ROADMAP.md
require_file docs/LOCAL_INSTALLER_ARTIFACT_MANIFEST_CONTRACT.md
require_file docs/SEABIOS_GRUB_BOOT_PREVIEW_BOOT_ARTIFACT_MANIFEST_VALIDATION.md
require_file docs/UBUNTU_READINESS_PLAN.md
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh
require_file scripts/test-secret-material-guard.sh
require_file scripts/test-report-redaction-boundary.sh
require_file scripts/test-installer-engine-log-sanitization.sh
require_file scripts/test-installer-engine-event-boundary.sh
require_file scripts/test-installer-ui-event-ingestion-sanitization.sh
require_file scripts/test-installer-ui-status-boundary.sh
require_file scripts/test-installer-ui-blocked-plan-sanitization.sh
require_file scripts/test-installer-config-authority-allowlist.sh
require_file scripts/test-installer-ui-artifact-authority.sh
require_file scripts/test-installer-console-output-authority.sh
require_file scripts/test-installer-console-display-sanitization.sh
require_file scripts/test-installer-ui-console-navigation-boundary.sh
require_file installer/scripts/latticra-installer-apply.sh

require_contains 'Status: supply-chain security baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'NIST SP 800-53 Release 5.2.0' "$doc"
require_contains 'OS command injection' "$doc"
require_contains 'Current Guarded Controls' "$doc"
require_contains 'Required Release Gate' "$doc"
require_contains 'Dependency Review Rules' "$doc"
require_contains 'CI Authority Rules' "$doc"

for field in \
  'supply_chain_security_baseline_present=1' \
  'supply_chain_security_guard_present=1' \
  'high_assurance_security_baseline_present=1' \
  'ssdf_supply_chain_profile_present=1' \
  'cpg_supply_chain_profile_present=1' \
  'sbom_required_before_production_installer=1' \
  'kev_nvd_review_required_before_release=1' \
  'dependency_inventory_required=1' \
  'pinned_ci_actions_required=1' \
  'read_only_workflow_permissions_required=1' \
  'persist_credentials_false_required=1' \
  'pull_request_target_forbidden=1' \
  'repository_secret_use_requires_dedicated_review=1' \
  'implicit_github_token_use_requires_dedicated_review=1' \
  'repository_source_symlink_refusal_required=1' \
  'repository_secret_filename_scan_required=1' \
  'repository_secret_content_marker_scan_required=1' \
  'sensitive_local_artifact_filename_guard_required=1' \
  'report_redaction_boundary_guard_required=1' \
  'whole_environment_report_dump_forbidden=1' \
  'installer_engine_log_redaction_required=1' \
  'installer_engine_log_sanitization_required=1' \
  'installer_engine_log_line_length_cap_required=1' \
  'installer_engine_event_boundary_sanitization_required=1' \
  'installer_engine_failure_event_sanitization_required=1' \
  'installer_ui_event_ingestion_sanitization_required=1' \
  'installer_ui_evidence_log_redaction_required=1' \
  'installer_ui_status_event_sanitization_required=1' \
  'installer_ui_status_boundary_required=1' \
  'installer_ui_direct_status_assignment_forbidden=1' \
  'installer_ui_blocked_plan_sanitization_required=1' \
  'installer_ui_blocked_plan_error_injection_guard_required=1' \
  'installer_config_authority_slug_allowlist_required=1' \
  'installer_command_wrapper_strict_name_required=1' \
  'installer_ui_artifact_authority_guard_required=1' \
  'installer_ui_artifact_write_validation_required=1' \
  'installer_console_output_authority_guard_required=1' \
  'installer_console_config_reflection_denial_required=1' \
  'installer_console_control_character_sanitization_required=1' \
  'installer_console_secret_redaction_required=1' \
  'installer_console_line_length_cap_required=1' \
  'installer_ui_console_navigation_root_boundary_required=1' \
  'installer_ui_console_navigation_path_reflection_denial_required=1' \
  'locked_dependency_builds_required=1' \
  'offline_installer_builds_required=1' \
  'ad_hoc_network_client_commands_forbidden_without_guard=1' \
  'source_archive_fixture_tracked_unignored_source_view_required=1' \
  'source_archive_fixture_symlink_refusal_required=1' \
  'source_archive_fixture_reproducible_metadata_required=1' \
  'release_publishing_authority_granted=0' \
  'production_installer_claim_allowed=0' \
  'production_update_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'certification_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'supply_chain_security_status_present=1' "$status_doc"

for gate in \
  'release_artifact_inventory_present=1' \
  'sbom_present=1' \
  'sbom_reviewed=1' \
  'dependency_inventory_reviewed=1' \
  'third_party_material_reviewed=1' \
  'license_notice_reviewed=1' \
  'kev_nvd_review_completed=1' \
  'known_exploited_vulnerability_mitigation_recorded=1' \
  'workflow_write_permission_reviewed=1' \
  'release_secret_boundary_reviewed=1' \
  'artifact_integrity_hashes_recorded=1' \
  'signing_authority_contract_present=1' \
  'update_payload_integrity_reviewed=1' \
  'update_authenticity_path_reviewed=1' \
  'update_rollback_evidence_present=1' \
  'command_boundary_reviewed=1' \
  'rollback_or_recovery_contract_present=1' \
  'vulnerability_disclosure_path_present=1' \
  'production_non_claim_review_completed=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'sbom_present_for_production_release=0' \
  'release_artifact_published=0' \
  'release_signing_performed=0' \
  'release_secret_access_granted=0' \
  'release_write_token_granted=0' \
  'production_security_claim_allowed=0'
do
  require_contains "$closed" "$doc"
  require_contains "$closed" "$status_doc"
done

require_contains 'workflow must pin external action refs to a 40-character commit SHA' scripts/test-quality-safety-guards.sh
require_contains 'workflow must keep repository token permissions read-only' scripts/test-quality-safety-guards.sh
require_contains 'workflow must set persist-credentials: false in every checkout step' scripts/test-quality-safety-guards.sh
require_contains 'workflow must not use pull_request_target' scripts/test-quality-safety-guards.sh
require_contains 'workflow must not consume repository secrets without a dedicated review guard' scripts/test-quality-safety-guards.sh
require_contains 'workflow must not consume implicit GitHub token surfaces without a dedicated review guard' scripts/test-quality-safety-guards.sh
require_contains 'workflow must not add ad hoc network client commands without a dedicated review guard' scripts/test-quality-safety-guards.sh
require_contains 'possible source-scope symlinks found' scripts/test-secret-material-guard.sh
require_contains 'possible committed secret-bearing filenames found' scripts/test-secret-material-guard.sh
require_contains 'possible committed secret or private-key content markers found' scripts/test-secret-material-guard.sh
require_contains 'sh ./scripts/test-secret-material-guard.sh' Makefile
require_contains 'secret-material-guard:' Makefile
require_contains 'whole process environments' scripts/test-report-redaction-boundary.sh
require_contains 'sanitize child stdout before forwarding install logs' scripts/test-report-redaction-boundary.sh
require_contains 'sanitize_log_line(line.as_ref())' installer/latticra-installer/src/engine.rs
require_contains 'sh ./scripts/test-report-redaction-boundary.sh' Makefile
require_contains 'report-redaction-boundary:' Makefile
require_contains 'installer_engine_log_sanitization: ok' scripts/test-installer-engine-log-sanitization.sh
require_contains 'sanitize_log_line_escapes_control_characters' installer/latticra-installer/src/engine.rs
require_contains 'sh ./scripts/test-installer-engine-log-sanitization.sh' Makefile
require_contains 'installer-engine-log-sanitization:' Makefile
require_contains 'installer_engine_event_boundary: ok' scripts/test-installer-engine-event-boundary.sh
require_contains 'send_log_sanitizes_internal_engine_events' installer/latticra-installer/src/engine.rs
require_contains 'send_failure_sanitizes_engine_failure_events' installer/latticra-installer/src/engine.rs
require_contains 'sh ./scripts/test-installer-engine-event-boundary.sh' Makefile
require_contains 'installer-engine-event-boundary:' Makefile
require_contains 'installer_ui_event_ingestion_sanitization: ok' scripts/test-installer-ui-event-ingestion-sanitization.sh
require_contains 'engine_log_event_is_sanitized_before_evidence_and_status' installer/latticra-installer/src/ui.rs
require_contains 'engine_failure_event_is_sanitized_before_status_and_evidence' installer/latticra-installer/src/ui.rs
require_contains 'sh ./scripts/test-installer-ui-event-ingestion-sanitization.sh' Makefile
require_contains 'installer-ui-event-ingestion-sanitization:' Makefile
require_contains 'installer_ui_status_boundary: ok' scripts/test-installer-ui-status-boundary.sh
require_contains 'status_setter_redacts_and_escapes_direct_status_updates' installer/latticra-installer/src/ui.rs
require_contains 'sh ./scripts/test-installer-ui-status-boundary.sh' Makefile
require_contains 'installer-ui-status-boundary:' Makefile
require_contains 'installer_ui_blocked_plan_sanitization: ok' scripts/test-installer-ui-blocked-plan-sanitization.sh
require_contains 'blocked_ui_plan_sanitizes_error_record_value' installer/latticra-installer/src/ui.rs
require_contains 'blocked_ui_plan_truncates_oversized_error_value' installer/latticra-installer/src/ui.rs
require_contains 'sh ./scripts/test-installer-ui-blocked-plan-sanitization.sh' Makefile
require_contains 'installer-ui-blocked-plan-sanitization:' Makefile
require_contains 'installer_config_authority_allowlist: ok' scripts/test-installer-config-authority-allowlist.sh
require_contains 'validate_authority_slug("LC install profile"' installer/latticra-installer/src/config.rs
require_contains 'valid_authority_slug()' installer/scripts/latticra-installer-apply.sh
require_contains 'sh ./scripts/test-installer-config-authority-allowlist.sh' Makefile
require_contains 'installer-config-authority-allowlist:' Makefile
require_contains 'installer_ui_artifact_authority: ok' scripts/test-installer-ui-artifact-authority.sh
require_contains 'sanitized_ui_artifact_config' installer/latticra-installer/src/ui.rs
require_contains 'can_write_artifacts' installer/latticra-installer/src/config.rs
require_contains 'sh ./scripts/test-installer-ui-artifact-authority.sh' Makefile
require_contains 'installer-ui-artifact-authority:' Makefile
require_contains 'installer_console_output_authority: ok' scripts/test-installer-console-output-authority.sh
require_contains 'console_report_config' installer/latticra-installer/src/ui.rs
require_contains 'console_config_report_blocks_invalid_authority_without_reflection' installer/latticra-installer/src/ui.rs
require_contains 'sh ./scripts/test-installer-console-output-authority.sh' Makefile
require_contains 'installer-console-output-authority:' Makefile
require_contains 'installer_console_display_sanitization: ok' scripts/test-installer-console-display-sanitization.sh
require_contains 'sanitize_console_line' installer/latticra-installer/src/ui.rs
require_contains 'pub(crate) fn redact_log_line' installer/latticra-installer/src/engine.rs
require_contains 'sh ./scripts/test-installer-console-display-sanitization.sh' Makefile
require_contains 'installer-console-display-sanitization:' Makefile
require_contains 'installer_ui_console_navigation_boundary: ok' scripts/test-installer-ui-console-navigation-boundary.sh
require_contains 'terminal_root: String' installer/latticra-installer/src/ui.rs
require_contains 'console_navigation_denies_paths_outside_workspace_root_without_reflection' installer/latticra-installer/src/ui.rs
require_contains 'sh ./scripts/test-installer-ui-console-navigation-boundary.sh' Makefile
require_contains 'installer-ui-console-navigation-boundary:' Makefile
require_contains 'source archives must use deterministic tar/gzip metadata' scripts/test-quality-safety-guards.sh
require_contains 'cargo check --locked --manifest-path installer/latticra-installer/Cargo.toml' Makefile
require_contains 'cargo build --release --locked --offline' installer/scripts/latticra-installer-apply.sh
require_contains 'SBOM evidence for shipped artifacts' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'dependency inventory with license and security review' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'KEV/NVD review or documented offline exception before release' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'software update and patch integrity, authenticity, validation, and rollback evidence before any mutating update lane' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/SUPPLY_CHAIN_SECURITY_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-supply-chain-security-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/SUPPLY_CHAIN_SECURITY_BASELINE.md' SECURITY.md
require_contains 'supply_chain_security_baseline_present=1' README.md
require_contains 'supply_chain_security_baseline_present=1' STATUS.md
require_contains 'SUPPLY_CHAIN_SECURITY_BASELINE_STATUS.md' docs/status/README.md
require_contains 'supply_chain_security_baseline_present=1' docs/status/README.md
require_contains 'Latest supply-chain security baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'SUPPLY_CHAIN_SECURITY_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Supply-chain baseline' docs/security.html
require_contains 'SUPPLY_CHAIN_SECURITY_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-supply-chain-security-baseline.sh' Makefile
require_contains 'supply-chain-security-baseline:' Makefile
require_contains 'test-supply-chain-security-baseline.sh' scripts/test-quality-safety-guards.sh

for allocation in \
  'process-launch boundary centralized' \
  'update authenticity and integrity impact review' \
  'command-boundary review' \
  'integrity, authenticity, validation, and rollback evidence'
do
  require_contains "$allocation" "$doc"
done

printf 'supply_chain_security_baseline: ok\n'

#!/usr/bin/env sh
set -eu

doc="docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md"
status_doc="docs/status/BACKUP_RECOVERY_RESILIENCE_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'backup recovery resilience baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'backup recovery resilience baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
require_file docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
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

require_contains 'Status: backup, recovery, and cyber resilience baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Authoritative Recovery and Resilience Sources' "$doc"
require_contains 'CISA/FBI/NSA/MS-ISAC #StopRansomware Guide' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals' "$doc"
require_contains 'NIST SP 800-34 Rev. 1 Contingency Planning Guide for Federal Information Systems' "$doc"
require_contains 'NIST SP 800-184 Guide for Cybersecurity Event Recovery' "$doc"
require_contains 'NIST SP 800-160 Vol. 2 Rev. 1 Developing Cyber-Resilient Systems' "$doc"
require_contains 'NIST Cybersecurity Framework 2.0 Recover function' "$doc"
require_contains 'NIST SP 800-53 Rev. 5 Contingency Planning controls' "$doc"
require_contains 'https://www.cisa.gov/stopransomware/ransomware-guide' "$doc"
require_contains 'https://www.cisa.gov/resources-tools/resources/stopransomware-guide' "$doc"
require_contains 'https://www.cisa.gov/cross-sector-cybersecurity-performance-goals' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/34/r1/upd1/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/184/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/160/v2/r1/final' "$doc"
require_contains 'https://www.nist.gov/cyberframework/recover' "$doc"
require_contains 'https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final' "$doc"

for field in \
  'backup_recovery_resilience_baseline_present=1' \
  'backup_recovery_resilience_guard_present=1' \
  'stopransomware_recovery_guidance_tracked=1' \
  'cisa_cpg_backup_recovery_tracked=1' \
  'nist_sp_800_34_contingency_planning_tracked=1' \
  'nist_sp_800_184_event_recovery_tracked=1' \
  'nist_sp_800_160_cyber_resilience_tracked=1' \
  'nist_csf_recover_function_tracked=1' \
  'nist_sp_800_53_contingency_planning_tracked=1' \
  'backup_scope_inventory_required=1' \
  'critical_asset_restore_priority_required=1' \
  'rto_rpo_record_required=1' \
  'offline_encrypted_backup_plan_required=1' \
  'backup_integrity_test_required=1' \
  'restore_test_required=1' \
  'clean_recovery_environment_required=1' \
  'golden_image_or_iac_recovery_plan_required=1' \
  'rollback_plan_required_before_mutation=1' \
  'recovery_authorization_contract_required=1' \
  'recovery_communications_plan_required=1' \
  'lessons_learned_update_required=1' \
  'recovery_exception_owner_required=1' \
  'recovery_exception_expiration_required=1' \
  'implementation_behavior_changed=0' \
  'backup_creation_added=0' \
  'backup_storage_added=0' \
  'restore_execution_added=0' \
  'rollback_execution_added=0' \
  'failover_added=0' \
  'recovery_orchestration_added=0' \
  'disaster_recovery_service_added=0' \
  'ransomware_recovery_service_added=0' \
  'production_recovery_claim_allowed=0' \
  'hosted_service_recovery_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'backup_recovery_resilience_status_present=1' "$status_doc"

for gate in \
  'critical_asset_inventory_present=1' \
  'dependency_restore_order_recorded=1' \
  'business_impact_or_service_priority_recorded=1' \
  'rto_recorded=1' \
  'rpo_recorded=1' \
  'backup_scope_recorded=1' \
  'backup_owner_recorded=1' \
  'offline_or_immutable_backup_path_recorded=1' \
  'backup_encryption_and_access_control_recorded=1' \
  'backup_integrity_verification_recorded=1' \
  'restore_test_result_recorded=1' \
  'clean_recovery_environment_recorded=1' \
  'golden_image_or_iac_restore_path_recorded=1' \
  'rollback_plan_recorded=1' \
  'recovery_authorization_recorded=1' \
  'recovery_communications_path_recorded=1' \
  'incident_response_handoff_recorded=1' \
  'post_recovery_validation_recorded=1' \
  'lessons_learned_update_path_recorded=1' \
  'recovery_exception_owner_recorded=1' \
  'recovery_exception_expiration_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'production_recovery_allowed=0' \
  'restore_execution_allowed=0' \
  'rollback_execution_allowed=0' \
  'failover_allowed=0' \
  'backup_service_claim_allowed=0' \
  'disaster_recovery_claim_allowed=0' \
  'ransomware_recovery_claim_allowed=0' \
  'hosted_service_recovery_claim_allowed=0' \
  'production_update_recovery_claim_allowed=0' \
  'continuity_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for boundary_field in \
  'latticra_recovery_path_metadata_only=1' \
  'latticra_rollback_plan_metadata_only=1' \
  'latticra_install_validation_recovery_flag_metadata_only=1' \
  'latticra_backup_storage_added=0' \
  'latticra_restore_runtime_added=0' \
  'latticra_failover_runtime_added=0' \
  'latticra_recovery_authority_granted=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'evidence_preservation_required=1' docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
require_contains 'incident_handoff_path_required=1' docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_contains 'rollback_or_recovery_contract_present=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'define backup, restore, and recovery evidence' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'backup_recovery_resilience_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-backup-recovery-resilience-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md' SECURITY.md
require_contains 'backup_recovery_resilience_baseline_present=1' README.md
require_contains 'backup_recovery_resilience_baseline_present=1' STATUS.md
require_contains 'BACKUP_RECOVERY_RESILIENCE_BASELINE_STATUS.md' docs/status/README.md
require_contains 'backup_recovery_resilience_baseline_present=1' docs/status/README.md
require_contains 'Latest backup, recovery, and cyber resilience baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'BACKUP_RECOVERY_RESILIENCE_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Backup, recovery, and cyber resilience baseline' docs/security.html
require_contains 'BACKUP_RECOVERY_RESILIENCE_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-backup-recovery-resilience-baseline.sh' Makefile
require_contains 'backup-recovery-resilience-baseline:' Makefile
require_contains 'sh ./scripts/test-backup-recovery-resilience-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-backup-recovery-resilience-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'backup_recovery_resilience_baseline: ok\n'

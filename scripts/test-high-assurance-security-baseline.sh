#!/usr/bin/env sh
set -eu

doc="docs/HIGH_ASSURANCE_SECURITY_BASELINE.md"
status_doc="docs/status/HIGH_ASSURANCE_SECURITY_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'high assurance security baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'high assurance security baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/security.html
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
require_file docs/MEMORY_SAFETY_ROADMAP.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
require_file docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
require_file docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
require_file docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md
require_file docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_file docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md
require_file docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_file docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md
require_file docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md
require_file docs/AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md
require_file docs/security/C_CPP_SECURITY_PROFILE.md
require_file docs/security/C_ABI_BOUNDARY_POLICY.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file scripts/test-defensive-threat-model-validation.sh
require_file scripts/test-defensive-threat-model-validation-refinement.sh
require_file scripts/test-memory-safety-roadmap.sh
require_file scripts/test-supply-chain-security-baseline.sh
require_file scripts/test-cyber-incident-reporting-response-baseline.sh
require_file scripts/test-vulnerability-management-release-gate-baseline.sh
require_file scripts/test-cryptographic-assurance-key-management-baseline.sh
require_file scripts/test-identity-credential-access-management-baseline.sh
require_file scripts/test-security-logging-monitoring-baseline.sh
require_file scripts/test-backup-recovery-resilience-baseline.sh
require_file scripts/test-secure-configuration-change-management-baseline.sh
require_file scripts/test-network-exposure-remote-access-baseline.sh
require_file scripts/test-data-classification-protection-baseline.sh
require_file scripts/test-ai-agentic-automation-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: high-assurance security baseline checkpoint' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Date checked: 2026-05-26' "$doc"
require_contains 'Authoritative Source Inventory' "$doc"
require_contains 'NSA Zero Trust Implementation Guidelines, Primer, Discovery Phase, Phase One, and Phase Two' "$doc"
require_contains 'NSA Advancing Zero Trust Maturity Throughout the User Pillar' "$doc"
require_contains 'CISA and NSA Identity and Access Management: Recommended Best Practices for Administrators' "$doc"
require_contains 'NSA/CISA Memory Safe Languages CSI' "$doc"
require_contains 'CISA Secure by Design' "$doc"
require_contains 'CISA/FBI Product Security Bad Practices' "$doc"
require_contains 'NSA and CISA Red and Blue Teams Share Top Ten Cybersecurity Misconfigurations' "$doc"
require_contains 'CISA/NSA/FBI secure-by-design and secure-by-default principles' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals' "$doc"
require_contains 'CISA/FBI/NSA international Best Practices for Event Logging and Threat Detection' "$doc"
require_contains 'CISA Logging Made Easy and CISA logging guidance' "$doc"
require_contains 'CISA Zero Trust Maturity Model v2' "$doc"
require_contains 'NSA Zero Trust Data Pillar' "$doc"
require_contains 'NSA Zero Trust Network and Environment Pillar' "$doc"
require_contains 'NSA Network Infrastructure Security Guide' "$doc"
require_contains 'CISA/NSA/FBI Guide to Securing Remote Access Software' "$doc"
require_contains 'CISA/NSA/MS-ISAC Remote Monitoring and Management Software Advisory' "$doc"
require_contains 'NIST SP 800-63-4 Digital Identity Guidelines' "$doc"
require_contains 'CISA/NSA/FBI/MS-ISAC Phishing Guidance' "$doc"
require_contains 'CISA Known Exploited Vulnerabilities Catalog' "$doc"
require_contains 'NIST National Vulnerability Database and CVSS metrics' "$doc"
require_contains 'FBI Cyber' "$doc"
require_contains 'CISA/FBI/NSA/MS-ISAC #StopRansomware Guide' "$doc"
require_contains 'CISA/FBI/NSA/MS-ISAC #StopRansomware recovery guidance' "$doc"
require_contains 'NIST Cybersecurity Framework 2.0' "$doc"
require_contains 'NIST SP 800-34 Rev. 1 and SP 800-184' "$doc"
require_contains 'NIST SP 800-60 and SP 800-122' "$doc"
require_contains 'NIST Privacy Framework' "$doc"
require_contains 'NIST SP 800-128' "$doc"
require_contains 'NIST SP 800-70 Rev. 5' "$doc"
require_contains 'NIST SP 800-41 Rev. 1' "$doc"
require_contains 'NIST SP 800-207A' "$doc"
require_contains 'NIST SP 800-92 and SP 800-92 Rev. 1 draft' "$doc"
require_contains 'NIST SP 800-218 SSDF v1.1' "$doc"
require_contains 'NIST SP 800-53 Rev. 5, Release 5.2.0' "$doc"
require_contains 'NIST SP 800-160 Vol. 2 Rev. 1' "$doc"
require_contains 'NIST SP 800-207 Zero Trust Architecture' "$doc"
require_contains 'NSA/CISA/FBI and partners Deploying AI Systems Securely' "$doc"
require_contains 'CISA and NCSC Guidelines for Secure AI System Development' "$doc"
require_contains 'NSA AISC MCP Security Design Considerations for AI-Driven Automation' "$doc"
require_contains 'NSA/CISA and partners Careful Adoption of Agentic AI Services' "$doc"
require_contains 'NIST AI RMF 1.0 and NIST AI 600-1 Generative AI Profile' "$doc"
require_contains 'NIST SP 800-218A AI SSDF Community Profile' "$doc"
require_contains 'FIPS 140-3' "$doc"
require_contains 'NIST SP 800-57 Part 1 Rev. 5, SP 800-131A Rev. 2, and SP 800-90 series' "$doc"
require_contains 'NSA/CISA/NIST post-quantum guidance and NSA CNSA 2.0' "$doc"

for field in \
  'high_assurance_security_baseline_present=1' \
  'source_refresh_date=2026-05-26' \
  'official_source_inventory_present=1' \
  'memory_safety_roadmap_required=1' \
  'memory_safety_roadmap_present=1' \
  'zero_trust_runtime_boundary_required=1' \
  'ssdf_secure_development_required=1' \
  'cpg_operational_baseline_required=1' \
  'supply_chain_security_baseline_present=1' \
  'cyber_incident_reporting_response_baseline_present=1' \
  'vulnerability_management_release_gate_baseline_present=1' \
  'cryptographic_assurance_key_management_baseline_present=1' \
  'identity_credential_access_management_baseline_present=1' \
  'security_logging_monitoring_baseline_present=1' \
  'backup_recovery_resilience_baseline_present=1' \
  'secure_configuration_change_management_baseline_present=1' \
  'network_exposure_remote_access_baseline_present=1' \
  'data_classification_protection_baseline_present=1' \
  'ai_agentic_automation_security_baseline_present=1' \
  'kev_release_review_required=1' \
  'fips_crypto_boundary_required_before_production_crypto=1' \
  'phishing_resistant_mfa_required_before_remote_privileged_access=1' \
  'security_event_logging_required_before_hosted_service=1' \
  'backup_restore_recovery_evidence_required_before_hosted_service=1' \
  'secure_configuration_change_control_required_before_hosted_service=1' \
  'network_exposure_review_required_before_hosted_service=1' \
  'data_classification_review_required_before_hosted_service=1' \
  'ai_agentic_automation_security_required_before_model_or_tool_authority=1' \
  'sbom_required_before_production_installer=1' \
  'third_party_security_validation_required_before_security_release=1' \
  'incident_response_plan_required_before_production_service=1' \
  'recurring_source_review_required=1' \
  'implementation_behavior_changed=0' \
  'runtime_authority_granted=0' \
  'security_boundary_claimed=0' \
  'certification_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'external_endorsement_claimed=0' \
  'production_protection_claim_allowed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

for allocation in \
  'new network-facing code -> memory-safe language preferred' \
  'new cryptographic key-handling code -> memory-safe language preferred' \
  'new parser for untrusted external input -> memory-safe language preferred or restricted C profile with fuzzing and exception record' \
  'buffer overflow, format-string, off-by-one, use-after-free' \
  'strcpy' \
  'system()' \
  'operator_identity_known=1' \
  'workload_or_service_identity_known=1' \
  'device_or_host_integrity_context_known=1' \
  'tool_or_mcp_boundary_known=1' \
  'context_sharing_scope_known=1' \
  'request_kind_known=1' \
  'unknown_request_denied=1' \
  'future_gate_denied_until_contract=1' \
  'SBOM evidence for shipped artifacts' \
  'KEV/NVD review or documented offline exception before release' \
  'vulnerability-management release gate before production release or supported-version claims' \
  'software update and patch integrity, authenticity, validation, and rollback evidence before any mutating update lane' \
  'defined cryptographic module boundary' \
  'FIPS 140-3 applicability decision' \
  'cryptographic assurance and key-management baseline before production cryptography claims' \
  'phishing-resistant MFA path for privileged and remote access' \
  'prohibit shared administrative accounts and default credentials' \
  'security event source inventory and owner mapping' \
  'log redaction and secret-marker scanning' \
  'define log retention, integrity, time-source, triage, and incident-handoff evidence' \
  'critical asset inventory and dependency restore order' \
  'backup integrity verification and restore-test result' \
  'publish a backup, recovery, and cyber resilience baseline before any recovery-service or failover claim' \
  'configuration item inventory and owners' \
  'secure baseline configuration record' \
  'configuration checklist or equivalent verification artifact' \
  'secure default and default-credential absence review' \
  'approved change request and risk review' \
  'rollback plan before configuration mutation' \
  'drift-detection and unauthorized-change response plan' \
  'network asset inventory and owners' \
  'internet-exposed service inventory' \
  'inbound port, protocol, and owner record' \
  'outbound egress policy' \
  'firewall policy review' \
  'segmentation boundary record' \
  'remote access tool inventory and approved remote access path' \
  'approved RMM allowlist and unauthorized RMM detection plan' \
  'network log-source inventory and flow visibility plan' \
  'data inventory and owners' \
  'data classification and information type categorization' \
  'sensitive-data flow map' \
  'PII presence review and confidentiality impact record' \
  'data minimization and collection-purpose review' \
  'retention period and disposal process' \
  'log/report redaction and secret or PII scan evidence' \
  'assign a named cybersecurity owner' \
  'define secure configuration baseline and change-control evidence' \
  'define network exposure and remote-access evidence' \
  'define data classification and protection evidence' \
  'define AI system inventory, model provenance, prompt/context boundaries, and agentic tool-authority evidence' \
  'require AI adversarial testing, monitoring, rollback, human oversight, and incident handoff before model, MCP, tool, or autonomous-effect claims' \
  'publish a cyber incident reporting and response baseline before any incident-response feature' \
  'schedule table-top or third-party validation before security release'
do
  require_contains "$allocation" "$doc"
done

require_contains 'Memory-safety roadmap alignment' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'memory-safe implementation language for new high-risk components' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'CISA/FBI product-security bad-practice exclusions' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'FIPS 140-3' docs/security/C_CPP_SECURITY_PROFILE.md

require_contains 'High-assurance standards posture' SECURITY.md
require_contains 'docs/HIGH_ASSURANCE_SECURITY_BASELINE.md' SECURITY.md
require_contains 'docs/MEMORY_SAFETY_ROADMAP.md' SECURITY.md
require_contains 'docs/SUPPLY_CHAIN_SECURITY_BASELINE.md' SECURITY.md
require_contains 'docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md' SECURITY.md
require_contains 'docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md' SECURITY.md
require_contains 'docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md' SECURITY.md
require_contains 'docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md' SECURITY.md
require_contains 'docs/SECURITY_LOGGING_MONITORING_BASELINE.md' SECURITY.md
require_contains 'docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md' SECURITY.md
require_contains 'docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md' SECURITY.md
require_contains 'docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md' SECURITY.md
require_contains 'docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md' SECURITY.md
require_contains 'docs/AI_AGENTIC_AUTOMATION_SECURITY_BASELINE.md' SECURITY.md
require_contains 'high_assurance_security_baseline_present=1' README.md
require_contains 'memory_safety_roadmap_present=1' README.md
require_contains 'supply_chain_security_baseline_present=1' README.md
require_contains 'cyber_incident_reporting_response_baseline_present=1' README.md
require_contains 'vulnerability_management_release_gate_baseline_present=1' README.md
require_contains 'cryptographic_assurance_key_management_baseline_present=1' README.md
require_contains 'identity_credential_access_management_baseline_present=1' README.md
require_contains 'security_logging_monitoring_baseline_present=1' README.md
require_contains 'backup_recovery_resilience_baseline_present=1' README.md
require_contains 'secure_configuration_change_management_baseline_present=1' README.md
require_contains 'network_exposure_remote_access_baseline_present=1' README.md
require_contains 'data_classification_protection_baseline_present=1' README.md
require_contains 'ai_agentic_automation_security_baseline_present=1' README.md
require_contains 'source_refresh_date=2026-05-26' README.md
require_contains 'high_assurance_security_baseline_present=1' STATUS.md
require_contains 'memory_safety_roadmap_present=1' STATUS.md
require_contains 'supply_chain_security_baseline_present=1' STATUS.md
require_contains 'cyber_incident_reporting_response_baseline_present=1' STATUS.md
require_contains 'vulnerability_management_release_gate_baseline_present=1' STATUS.md
require_contains 'cryptographic_assurance_key_management_baseline_present=1' STATUS.md
require_contains 'identity_credential_access_management_baseline_present=1' STATUS.md
require_contains 'security_logging_monitoring_baseline_present=1' STATUS.md
require_contains 'backup_recovery_resilience_baseline_present=1' STATUS.md
require_contains 'secure_configuration_change_management_baseline_present=1' STATUS.md
require_contains 'network_exposure_remote_access_baseline_present=1' STATUS.md
require_contains 'data_classification_protection_baseline_present=1' STATUS.md
require_contains 'ai_agentic_automation_security_baseline_present=1' STATUS.md
require_contains 'High-assurance security baseline' docs/status/README.md
require_contains 'HIGH_ASSURANCE_SECURITY_BASELINE_STATUS.md' docs/status/README.md
require_contains 'Latest high-assurance security baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'High-assurance baseline' docs/security.html
require_contains 'HIGH_ASSURANCE_SECURITY_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-high-assurance-security-baseline.sh' Makefile
require_contains 'sh ./scripts/test-memory-safety-roadmap.sh' Makefile
require_contains 'sh ./scripts/test-supply-chain-security-baseline.sh' Makefile
require_contains 'sh ./scripts/test-cyber-incident-reporting-response-baseline.sh' Makefile
require_contains 'sh ./scripts/test-vulnerability-management-release-gate-baseline.sh' Makefile
require_contains 'sh ./scripts/test-cryptographic-assurance-key-management-baseline.sh' Makefile
require_contains 'sh ./scripts/test-identity-credential-access-management-baseline.sh' Makefile
require_contains 'sh ./scripts/test-security-logging-monitoring-baseline.sh' Makefile
require_contains 'sh ./scripts/test-backup-recovery-resilience-baseline.sh' Makefile
require_contains 'sh ./scripts/test-secure-configuration-change-management-baseline.sh' Makefile
require_contains 'sh ./scripts/test-network-exposure-remote-access-baseline.sh' Makefile
require_contains 'sh ./scripts/test-data-classification-protection-baseline.sh' Makefile
require_contains 'sh ./scripts/test-ai-agentic-automation-security-baseline.sh' Makefile
require_contains 'quality-security-standards:' Makefile
require_contains 'quality-security-standards' Makefile
require_contains 'test-high-assurance-security-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'high_assurance_security_baseline: ok\n'

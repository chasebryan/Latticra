#!/usr/bin/env sh
set -eu

doc="docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md"
status_doc="docs/status/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'network exposure remote access baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'network exposure remote access baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_file docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md
require_file docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_file docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file docs/security/C_CPP_SECURITY_PROFILE.md
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-zero-trust-runtime-authority-baseline.sh
require_file scripts/test-identity-credential-access-management-baseline.sh
require_file scripts/test-security-logging-monitoring-baseline.sh
require_file scripts/test-secure-configuration-change-management-baseline.sh
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: network exposure and remote access baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Authoritative Network and Remote Access Sources' "$doc"
require_contains 'NSA Zero Trust Network and Environment Pillar' "$doc"
require_contains 'NSA Network Infrastructure Security Guide' "$doc"
require_contains 'CISA/NSA/FBI Guide to Securing Remote Access Software' "$doc"
require_contains 'CISA/NSA/MS-ISAC Remote Monitoring and Management Software Advisory' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals' "$doc"
require_contains 'NIST SP 800-41 Rev. 1 Guidelines on Firewalls and Firewall Policy' "$doc"
require_contains 'NIST SP 800-207A Zero Trust Architecture Model for Access Control in Cloud-Native Applications in Multi-Location Environments' "$doc"
require_contains 'NIST SP 800-53 Rev. 5 Access Control and System and Communications Protection controls' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3527658/nsa-releases-repository-for-zero-trust-guidance/' "$doc"
require_contains 'https://media.defense.gov/2024/Mar/05/2003404587/-1/-1/0/CSI_Zero_Trust_Network_Environment_Pillar.PDF' "$doc"
require_contains 'https://media.defense.gov/2022/Jun/15/2003018261/-1/-1/0/CTR_NSA_NETWORK_INFRASTRUCTURE_SECURITY_GUIDE_20220615.PDF' "$doc"
require_contains 'https://www.cisa.gov/resources-tools/resources/guide-securing-remote-access-software' "$doc"
require_contains 'https://www.cisa.gov/news-events/cybersecurity-advisories/aa23-025a' "$doc"
require_contains 'https://www.cisa.gov/cybersecurity-performance-goals-cpgs' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/41/r1/final' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/207/a/final' "$doc"
require_contains 'https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final' "$doc"

for field in \
  'network_exposure_remote_access_baseline_present=1' \
  'network_exposure_remote_access_guard_present=1' \
  'nsa_zero_trust_network_environment_pillar_tracked=1' \
  'nsa_network_infrastructure_security_guide_tracked=1' \
  'cisa_nsa_fbi_remote_access_software_guide_tracked=1' \
  'cisa_nsa_msisac_rmm_advisory_tracked=1' \
  'cisa_cpg_network_security_tracked=1' \
  'nist_sp_800_41_firewall_policy_tracked=1' \
  'nist_sp_800_207a_zero_trust_access_tracked=1' \
  'nist_sp_800_53_network_controls_tracked=1' \
  'network_asset_inventory_required=1' \
  'internet_exposure_inventory_required=1' \
  'remote_access_inventory_required=1' \
  'ingress_policy_required=1' \
  'egress_policy_required=1' \
  'firewall_policy_required=1' \
  'network_segmentation_required=1' \
  'dns_tls_certificate_lifecycle_required=1' \
  'remote_access_mfa_and_device_posture_required=1' \
  'authorized_rmm_inventory_required=1' \
  'network_logging_and_flow_visibility_required=1' \
  'network_exception_owner_required=1' \
  'network_exception_expiration_required=1' \
  'implementation_behavior_changed=0' \
  'network_listener_added=0' \
  'network_client_added=0' \
  'remote_access_added=0' \
  'rmm_added=0' \
  'firewall_change_added=0' \
  'dns_tls_runtime_added=0' \
  'network_scanner_added=0' \
  'production_network_claim_allowed=0' \
  'internet_facing_service_claim_allowed=0' \
  'hosted_remote_access_claim_allowed=0' \
  'network_segmentation_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'network_exposure_remote_access_status_present=1' "$status_doc"

for gate in \
  'network_asset_inventory_present=1' \
  'network_data_flow_map_recorded=1' \
  'internet_exposed_service_inventory_present=1' \
  'inbound_port_protocol_owner_recorded=1' \
  'outbound_egress_policy_recorded=1' \
  'firewall_policy_review_recorded=1' \
  'segmentation_boundary_recorded=1' \
  'remote_access_tool_inventory_recorded=1' \
  'approved_remote_access_path_recorded=1' \
  'phishing_resistant_mfa_or_exception_recorded=1' \
  'device_posture_requirement_recorded=1' \
  'rmm_allowlist_recorded=1' \
  'unauthorized_rmm_detection_plan_recorded=1' \
  'dns_resolver_policy_recorded=1' \
  'tls_certificate_lifecycle_recorded=1' \
  'network_log_source_inventory_recorded=1' \
  'flow_visibility_plan_recorded=1' \
  'incident_handoff_recorded=1' \
  'exception_owner_recorded=1' \
  'exception_expiration_recorded=1' \
  'operator_visible_non_claims_recorded=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'network_listener_allowed=0' \
  'network_client_allowed=0' \
  'internet_facing_service_claim_allowed=0' \
  'remote_admin_claim_allowed=0' \
  'remote_access_software_claim_allowed=0' \
  'rmm_claim_allowed=0' \
  'firewall_policy_claim_allowed=0' \
  'network_segmentation_claim_allowed=0' \
  'egress_control_claim_allowed=0' \
  'dns_tls_service_claim_allowed=0' \
  'compliance_claim_allowed=0'
do
  require_contains "$closed" "$doc"
done

for boundary_field in \
  'latticra_network_metadata_only=1' \
  'latticra_runtime_network_authority_denied=1' \
  'latticra_installer_network_fetch_authority_denied=1' \
  'latticra_remote_admin_surface_added=0' \
  'latticra_service_listener_added=0' \
  'latticra_network_client_added=0' \
  'latticra_rmm_capability_added=0' \
  'latticra_firewall_mutation_added=0' \
  'latticra_dns_tls_runtime_added=0' \
  'latticra_network_authority_granted=0'
do
  require_contains "$boundary_field" "$doc"
done

require_contains 'network_open_allowed=0' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'mfa_required_for_remote_access=1' docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md
require_contains 'network_sensor_added=0' docs/SECURITY_LOGGING_MONITORING_BASELINE.md
require_contains 'network_behavior_changed=0' docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
require_contains 'ad_hoc_network_client_commands_forbidden_without_guard=1' docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_contains 'secure_configuration_change_management_baseline_present=1' docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
require_contains 'network-facing code' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'network exposure and remote-access evidence' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'network_exposure_remote_access_baseline_present=1' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-network-exposure-remote-access-baseline.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md' SECURITY.md
require_contains 'network_exposure_remote_access_baseline_present=1' README.md
require_contains 'network_exposure_remote_access_baseline_present=1' STATUS.md
require_contains 'NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE_STATUS.md' docs/status/README.md
require_contains 'network_exposure_remote_access_baseline_present=1' docs/status/README.md
require_contains 'Latest network exposure and remote access baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Network exposure and remote access baseline' docs/security.html
require_contains 'NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-network-exposure-remote-access-baseline.sh' Makefile
require_contains 'network-exposure-remote-access-baseline:' Makefile
require_contains 'sh ./scripts/test-network-exposure-remote-access-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-network-exposure-remote-access-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'network_exposure_remote_access_baseline: ok\n'

# Latticra Network Exposure and Remote Access Baseline

Status: network exposure and remote access baseline
Source refresh date: 2026-05-26
Scope: network asset inventory, internet exposure inventory, ingress and egress policy, firewall policy, segmentation, remote access, remote monitoring and management tooling, DNS and TLS lifecycle, network logging, flow visibility, exception ownership, and network non-claims before hosted services, internet-facing services, remote administration, infrastructure automation, or production network claims.

This baseline records network exposure and remote-access requirements only. It does not implement network access, service listeners, network clients, DNS, TLS, firewall changes, routing changes, remote access, remote monitoring and management tooling, segmentation, network scanning, compliance, or runtime authority.

## Authoritative Network and Remote Access Sources

Date checked: 2026-05-26

| Source | Latticra use |
| --- | --- |
| NSA Zero Trust Network and Environment Pillar | network segmentation, traffic visibility, policy enforcement, and network/environment zero-trust maturity vocabulary |
| NSA Network Infrastructure Security Guide | network device hardening, management-plane separation, secure administration, and routing/switching infrastructure hygiene vocabulary |
| CISA/NSA/FBI Guide to Securing Remote Access Software | remote access inventory, phishing-resistant MFA, identity/device posture, least privilege, logging, and remote-access hardening vocabulary |
| CISA/NSA/MS-ISAC Remote Monitoring and Management Software Advisory | RMM inventory, approved-tool allowlisting, unauthorized RMM detection, network indicators, and incident-handoff vocabulary |
| CISA Cross-Sector Cybersecurity Performance Goals | network asset inventory, external exposure, MFA for remote access, secure configuration, logging, and vulnerability reduction context |
| NIST SP 800-41 Rev. 1 Guidelines on Firewalls and Firewall Policy | firewall architecture, policy planning, rule review, ingress/egress filtering, and firewall lifecycle vocabulary |
| NIST SP 800-207A Zero Trust Architecture Model for Access Control in Cloud-Native Applications in Multi-Location Environments | policy decision, service identity, workload access, and distributed zero-trust access-control vocabulary |
| NIST SP 800-53 Rev. 5 Access Control and System and Communications Protection controls | AC and SC family vocabulary for remote access, least privilege, boundary protection, transmission confidentiality, and network controls |

Authoritative URLs:

```text
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/3527658/nsa-releases-repository-for-zero-trust-guidance/
https://media.defense.gov/2024/Mar/05/2003404587/-1/-1/0/CSI_Zero_Trust_Network_Environment_Pillar.PDF
https://media.defense.gov/2022/Jun/15/2003018261/-1/-1/0/CTR_NSA_NETWORK_INFRASTRUCTURE_SECURITY_GUIDE_20220615.PDF
https://www.cisa.gov/resources-tools/resources/guide-securing-remote-access-software
https://www.cisa.gov/news-events/cybersecurity-advisories/aa23-025a
https://www.cisa.gov/cross-sector-cybersecurity-performance-goals
https://csrc.nist.gov/pubs/sp/800/41/r1/final
https://csrc.nist.gov/pubs/sp/800/207/a/final
https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final
```

## Current Fields

```text
network_exposure_remote_access_baseline_present=1
network_exposure_remote_access_guard_present=1
nsa_zero_trust_network_environment_pillar_tracked=1
nsa_network_infrastructure_security_guide_tracked=1
cisa_nsa_fbi_remote_access_software_guide_tracked=1
cisa_nsa_msisac_rmm_advisory_tracked=1
cisa_cpg_network_security_tracked=1
nist_sp_800_41_firewall_policy_tracked=1
nist_sp_800_207a_zero_trust_access_tracked=1
nist_sp_800_53_network_controls_tracked=1
network_asset_inventory_required=1
internet_exposure_inventory_required=1
remote_access_inventory_required=1
ingress_policy_required=1
egress_policy_required=1
firewall_policy_required=1
network_segmentation_required=1
dns_tls_certificate_lifecycle_required=1
remote_access_mfa_and_device_posture_required=1
authorized_rmm_inventory_required=1
network_logging_and_flow_visibility_required=1
network_exception_owner_required=1
network_exception_expiration_required=1
implementation_behavior_changed=0
network_listener_added=0
network_client_added=0
remote_access_added=0
rmm_added=0
firewall_change_added=0
dns_tls_runtime_added=0
network_scanner_added=0
production_network_claim_allowed=0
internet_facing_service_claim_allowed=0
hosted_remote_access_claim_allowed=0
network_segmentation_claim_allowed=0
compliance_claim_allowed=0
external_endorsement_claimed=0
```

## Required Network Promotion Gate

No hosted service, internet-facing service, production runtime, production installer, production package, infrastructure automation lane, remote administration path, remote access software claim, RMM claim, service-listener claim, ingress/egress control claim, firewall policy claim, segmentation claim, DNS/TLS service claim, or production network claim may be promoted until this gate is complete:

```text
network_asset_inventory_present=1
network_data_flow_map_recorded=1
internet_exposed_service_inventory_present=1
inbound_port_protocol_owner_recorded=1
outbound_egress_policy_recorded=1
firewall_policy_review_recorded=1
segmentation_boundary_recorded=1
remote_access_tool_inventory_recorded=1
approved_remote_access_path_recorded=1
phishing_resistant_mfa_or_exception_recorded=1
device_posture_requirement_recorded=1
rmm_allowlist_recorded=1
unauthorized_rmm_detection_plan_recorded=1
dns_resolver_policy_recorded=1
tls_certificate_lifecycle_recorded=1
network_log_source_inventory_recorded=1
flow_visibility_plan_recorded=1
incident_handoff_recorded=1
exception_owner_recorded=1
exception_expiration_recorded=1
operator_visible_non_claims_recorded=1
```

Until this gate is complete:

```text
network_listener_allowed=0
network_client_allowed=0
internet_facing_service_claim_allowed=0
remote_admin_claim_allowed=0
remote_access_software_claim_allowed=0
rmm_claim_allowed=0
firewall_policy_claim_allowed=0
network_segmentation_claim_allowed=0
egress_control_claim_allowed=0
dns_tls_service_claim_allowed=0
compliance_claim_allowed=0
```

## Latticra Boundary

Current Latticra network-related records remain evidence and no-effect contract work.

```text
latticra_network_metadata_only=1
latticra_runtime_network_authority_denied=1
latticra_installer_network_fetch_authority_denied=1
latticra_remote_admin_surface_added=0
latticra_service_listener_added=0
latticra_network_client_added=0
latticra_rmm_capability_added=0
latticra_firewall_mutation_added=0
latticra_dns_tls_runtime_added=0
latticra_network_authority_granted=0
```

## Current Evidence

Current supporting evidence:

```text
docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md
docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md
docs/SECURITY_LOGGING_MONITORING_BASELINE.md
docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
docs/security/C_CPP_SECURITY_PROFILE.md
SECURITY.md
scripts/test-zero-trust-runtime-authority-baseline.sh
scripts/test-identity-credential-access-management-baseline.sh
scripts/test-security-logging-monitoring-baseline.sh
scripts/test-secure-configuration-change-management-baseline.sh
scripts/test-network-exposure-remote-access-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-network-exposure-remote-access-baseline.sh
```

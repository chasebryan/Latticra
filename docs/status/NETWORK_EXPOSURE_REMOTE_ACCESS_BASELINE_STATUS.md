# Latticra Network Exposure and Remote Access Baseline Status

Status: status record for network exposure and remote access baseline
Date: 2026-05-26

## Scope

This record tracks the network exposure and remote-access baseline for network asset inventory, internet exposure inventory, ingress and egress policy, firewall policy, segmentation, remote access, remote monitoring and management tooling, DNS and TLS lifecycle, network logging, flow visibility, exception ownership, and network non-claims.

It does not implement network access, service listeners, network clients, DNS, TLS, firewall changes, routing changes, remote access, remote monitoring and management tooling, segmentation, network scanning, compliance, or runtime authority.

## Current fields

```text
network_exposure_remote_access_baseline_present=1
network_exposure_remote_access_status_present=1
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

## Validation

```sh
sh scripts/test-network-exposure-remote-access-baseline.sh
```

Expected output:

```text
network_exposure_remote_access_baseline: ok
```

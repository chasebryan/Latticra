# Latticra High-Assurance Security Baseline

Status: high-assurance security baseline checkpoint
Source refresh date: 2026-05-26
Scope: NSA, CISA, FBI, and NIST security guidance alignment for current Latticra source, documentation, tests, packaging lanes, and future infrastructure posture.

This baseline allocates required security work for Latticra. It does not certify Latticra, accredit Latticra, make Latticra a production security boundary, or claim compliance with any external framework.

## Purpose

Latticra is an early-stage systems architecture and language implementation project. Because the project intentionally works near parsers, runtime boundaries, effect gates, cryptographic metadata, local installers, and future agentic automation surfaces, security work must track authoritative guidance before new authority is added.

This baseline records:

```text
current official source inventory
required project allocations
memory-safety roadmap requirements
zero-trust runtime-boundary requirements
supply-chain and dependency requirements
cryptographic assurance requirements
identity, credential, and access management requirements
security logging, monitoring, and detection requirements
backup, recovery, and cyber resilience requirements
secure configuration and change management requirements
network exposure and remote access requirements
data classification and protection requirements
incident-response and disclosure requirements
non-claims that remain closed
```

## Authoritative Source Inventory

Date checked: 2026-05-26

| Source | Current guidance used | Latticra allocation |
| --- | --- | --- |
| NSA Zero Trust Implementation Guidelines, Primer, Discovery Phase, Phase One, and Phase Two | Zero trust work begins with visibility over data, applications, assets, services, access, and authorization activity, then advances through phased activities, requirements, precursors, and successors toward target-level maturity. | Keep runtime authority denied until request identity, asset identity, authorization state, evidence level, prerequisites, successors, and audit output are visible. |
| NSA Advancing Zero Trust Maturity Throughout the User Pillar | ICAM capabilities are a core zero-trust maturity path for critical systems. | Require identity, credential, MFA, privileged-access, account-lifecycle, and identity-event evidence before hosted or privileged authority claims. |
| CISA and NSA Identity and Access Management: Recommended Best Practices for Administrators | Administrators should inventory assets and identities, understand security gaps, deploy and inventory MFA, collect SSO context, and monitor privileged behavior. | Keep identity and access management as a gated baseline before remote access, hosted administration, privileged sessions, or account-management claims. |
| NSA/CISA Memory Safe Languages CSI | Memory-safe language adoption should be considered, while existing code can be improved through interoperability and mitigations where migration is not practical. | Publish and guard a memory-safety roadmap for C/C++ substrate code; prefer memory-safe implementation for new high-risk infrastructure surfaces. |
| CISA Secure by Design | Manufacturers should take ownership of customer security outcomes, practice transparency/accountability, and lead from the top. | Require evidence-bound public claims, vulnerability reporting, no hidden security costs, deterministic reports, and leadership-owned security gates. |
| CISA/FBI Product Security Bad Practices | Avoid exceptionally risky practices, including absent memory-safety roadmaps, injection classes, known-insecure crypto, weak defaults, and unmanaged dependencies. | Guard against unsafe APIs, shell injection surfaces, default-secret patterns, unbounded buffers, path traversal, and production crypto claims without a module boundary. |
| NSA and CISA Red and Blue Teams Share Top Ten Cybersecurity Misconfigurations | Common enterprise compromise paths include default configurations, poor patch/configuration hygiene, weak controls, and visibility gaps. | Require secure configuration and change-management evidence before host, infrastructure, hardening, or production configuration claims. |
| CISA/NSA/FBI secure-by-design and secure-by-default principles | Secure products should ship with secure default baselines and should not shift avoidable hardening burden to customers. | Block secure-default and configuration-hardening claims until secure defaults, default-credential absence, checklist evidence, and exception ownership are recorded. |
| CISA Cross-Sector Cybersecurity Performance Goals | Establish baseline practices for asset inventory, vulnerability management, logging, account security, incident response, recovery, and third-party validation. | Maintain source and dependency inventory, KEV-aware release checks, explicit logs/reports, incident plan, recovery contracts before mutation, and third-party review before security release. |
| CISA/FBI/NSA international Best Practices for Event Logging and Threat Detection | Event logging supports continued operations and resilience through visibility, detection, and investigation across cloud, enterprise, mobile, and OT environments. | Require a security logging, monitoring, and detection baseline before hosted services, telemetry export, SIEM integration, or detection claims. |
| CISA Logging Made Easy and CISA logging guidance | Centralized log management, user activity visibility, alerting, and regular review improve threat detection. | Require event-source inventory, log centralization/export planning, redaction, triage ownership, and incident handoff before monitoring claims. |
| CISA Zero Trust Maturity Model v2 | Mature zero trust uses identity, devices, networks, applications/workloads, and data pillars with visibility, analytics, automation, orchestration, and governance. | Treat each Latticra request as a per-request policy decision; preserve deny-by-default behavior for network, host, recovery, boot, and tool authority. |
| NSA Zero Trust Data Pillar | Data security maturity includes inventory, tagging, labeling, encryption, access control, data-loss prevention, and data-at-rest/in-transit protection. | Require data classification and protection evidence before sensitive-data, PII, telemetry, analytics, or customer-data handling claims. |
| NSA Zero Trust Network and Environment Pillar | Network/environment zero trust requires segmentation, visibility, policy enforcement, and maturity planning for network flows and access. | Require network exposure and remote-access evidence before service-listener, remote administration, ingress/egress, segmentation, or hosted network claims. |
| NSA Network Infrastructure Security Guide | Network infrastructure should be hardened with secure management, inventory, management-plane separation, routing/switching hygiene, and monitored administration. | Keep network infrastructure work metadata-only until device, service, firewall, route, management, and exception evidence exists. |
| CISA/NSA/FBI Guide to Securing Remote Access Software | Remote access software needs inventory, MFA, device posture, least privilege, monitoring, and secure configuration. | Block remote access and remote administration claims until inventory, phishing-resistant MFA path, device posture, logs, and owner evidence are recorded. |
| CISA/NSA/MS-ISAC Remote Monitoring and Management Software Advisory | RMM tools are abused when unapproved, unmanaged, or insufficiently monitored. | Require approved RMM inventory, allowlisting, unauthorized RMM detection planning, and incident handoff before any RMM claim. |
| NIST SP 800-63-4 Digital Identity Guidelines | Current digital identity guidance covers identity proofing, authentication, authenticator management, federation, and assertions. | Use SP 800-63-4 vocabulary for future operator identity, account lifecycle, MFA, SSO/federation, and authentication non-claims. |
| CISA/NSA/FBI/MS-ISAC Phishing Guidance | Phishing-resistant MFA and social-engineering-resistant account processes reduce account-compromise risk. | Require phishing-resistant MFA planning and help-desk identity verification before privileged or remote access claims. |
| CISA Known Exploited Vulnerabilities Catalog | Internet-facing exploited vulnerabilities need timely mitigation or compensating controls. | Before any internet-facing asset exists, create a KEV review gate; current project has no internet-facing runtime authority. |
| NIST National Vulnerability Database and CVSS metrics | CVE and CVSS records provide vulnerability enrichment and severity context, while CVSS is not a complete risk score by itself. | Require KEV/NVD review, component inventory, mitigation or exception records, and public non-claim review before release. |
| FBI Cyber | The active threat environment includes ransomware, nation-state targeting, critical infrastructure risk, rapidly changing IOCs/TTPs, and reporting through FBI/IC3 paths. | Keep the threat model defensive, keep reports private, add incident-reporting paths, and avoid offensive payload, persistence, exfiltration, and evasion content. |
| CISA/FBI/NSA/MS-ISAC #StopRansomware Guide | Ransomware and data-extortion preparation, prevention, response, evidence preservation, out-of-band communications, and federal contact paths must be planned before incidents. | Keep incident-response authority denied, document reporting paths, preserve evidence requirements, and require operator/legal review before notification or reporting assistance. |
| CISA/FBI/NSA/MS-ISAC #StopRansomware recovery guidance | Offline encrypted backups, regular backup testing, restoration prioritization, clean recovery environments, and post-incident lessons learned reduce ransomware recovery risk. | Require a backup, recovery, and cyber resilience baseline before hosted-service recovery, disaster-recovery, failover, rollback, or ransomware-recovery claims. |
| NIST Cybersecurity Framework 2.0 | Govern, Identify, Protect, Detect, Respond, and Recover provide current cybersecurity risk-management functions. | Map future infrastructure readiness to CSF 2.0 functions before production claims. |
| NIST SP 800-34 Rev. 1 and SP 800-184 | Contingency planning and cybersecurity event recovery require business impact analysis, recovery strategy, playbooks, realistic testing, and continuous improvement. | Require recovery scope, RTO/RPO, restore testing, rollback, recovery authorization, and lessons-learned evidence before recoverability claims. |
| NIST SP 800-60 and SP 800-122 | Information categorization and PII confidentiality guidance define information type, security category, confidentiality impact, safeguards, and PII incident planning vocabulary. | Require data inventory, classification, PII review, confidentiality impact, data minimization, retention, disposal, and incident handoff before data-protection claims. |
| NIST Privacy Framework | Privacy risk management uses data processing inventory, governance, control, communication, and protection functions. | Use Privacy Framework vocabulary for future data processing, privacy engineering, and privacy non-claims without making a compliance claim. |
| NIST SP 800-128 | Security-focused configuration management uses baseline configuration, configuration control, monitoring, and SecCM practices to manage risk. | Require configuration item inventory, baseline configuration, owner, change record, testing, rollback, and drift-detection evidence before configuration claims. |
| NIST SP 800-70 Rev. 5 | Security configuration checklists help configure products to a risk posture, verify configuration, identify unauthorized change, and produce posture artifacts. | Require checklist evidence and unauthorized-change detection planning before secure configuration, hardening, or scanning claims. |
| NIST SP 800-41 Rev. 1 | Firewall policy requires planned architecture, rule review, ingress and egress filtering, lifecycle maintenance, and monitoring. | Require firewall policy, inbound owner, outbound egress, segmentation, and rule-review evidence before network control claims. |
| NIST SP 800-207A | Zero-trust access in multi-location environments uses policy decisions, service/workload identity, and distributed access control. | Keep service access and workload network authority denied until per-request policy evidence exists. |
| NIST SP 800-92 and SP 800-92 Rev. 1 draft | Log management requires planning for generation, transmission, storage, access, analysis, retention, and disposal. | Use SP 800-92 vocabulary for future audit-event selection, log lifecycle, retention, access, and disposal evidence. |
| NIST SP 800-218 SSDF v1.1 | Secure development should prepare the organization, protect software, produce well-secured software, and respond to vulnerabilities. | Keep tests, threat-model docs, protected source/build processes, vulnerability handling, and root-cause-driven fixes in the quality gate. |
| NIST SP 800-53 Rev. 5, Release 5.2.0 | Control families cover access, audit, configuration, identification, incident response, risk assessment, system acquisition, system integrity, and supply-chain risk management. | Use SP 800-53 as the high-assurance control vocabulary for future production profiles, not as a current compliance claim. |
| NIST SP 800-160 Vol. 2 Rev. 1 | Cyber-resilient systems should anticipate, withstand, recover from, and adapt to adverse conditions and attacks. | Keep rollback, recovery, degraded-mode, auditability, and no-hidden-effect requirements ahead of any mutating infrastructure behavior. |
| NIST SP 800-207 Zero Trust Architecture | Zero trust removes implicit trust and makes access decisions resource-focused and least-privilege. | Runtime and agentic automation authority must remain per-request, least-privilege, auditable, and denied unless prerequisites pass. |
| FIPS 140-3 | Federal cryptographic module security requirements define validated module expectations and security levels. | No production cryptography or FIPS claim is allowed until a cryptographic module boundary, validation path, key lifecycle, and dependency review exist. |
| NIST SP 800-57 Part 1 Rev. 5, SP 800-131A Rev. 2, and SP 800-90 series | Key management, algorithm transition, and random-bit generation guidance define required cryptographic planning vocabulary. | Require a cryptographic assurance and key-management baseline before signing authority, key storage, entropy use, FIPS, or production crypto claims. |
| NSA/CISA/NIST post-quantum guidance and NSA CNSA 2.0 | High-assurance systems should inventory cryptography and plan migration toward quantum-resistant algorithms without premature deployment claims. | Require post-quantum inventory and migration planning before long-lived confidentiality or national-security-oriented cryptographic claims. |

Authoritative URLs for this checkpoint are preserved in `docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md`.

Tracked follow-on guidance for this checkpoint:

- CISA/FBI Secure by Design Alert: Eliminating Buffer Overflow Vulnerabilities sharpens the retained-C/C++ posture toward buffer-overflow-class defect reduction, adversarial testing, and memory-safe implementation preference for new high-risk surfaces.
- CISA Secure by Design Alert: Eliminating OS Command Injection Vulnerabilities reinforces the existing `system()`/`popen()` exclusions and keeps shell authority centralized behind reviewed boundaries.
- CISA The Case for Memory Safe Roadmaps reinforces the requirement for a component-by-component migration or mitigation record instead of a generic memory-safety aspiration.
- NIST SP 800-207A and NIST SP 1800-35 provide secondary zero-trust implementation detail for future workload, service, and device-integrity-aware authority surfaces.

Follow-on source review performed: 2026-05-27

- NSA's May 20, 2026 guidance on security design considerations for AI-driven automation leveraging MCP is now relevant to Latticra's future server, MCP, tool, and agentic automation surfaces. It reinforces explicit tool-boundary contracts, dynamic tool invocation caution, context-sharing limits, and distrust of implicit cross-service trust.
- NSA and partners' April 30, 2026 guidance on careful adoption of agentic AI services reinforces that future agentic automation should be treated as a broader risk amplifier, not merely a wrapper around existing cybersecurity controls.

## Required Allocations

Current required allocation fields:

```text
high_assurance_security_baseline_present=1
source_refresh_date=2026-05-26
official_source_inventory_present=1
memory_safety_roadmap_required=1
memory_safety_roadmap_present=1
zero_trust_runtime_boundary_required=1
ssdf_secure_development_required=1
cpg_operational_baseline_required=1
supply_chain_security_baseline_present=1
cyber_incident_reporting_response_baseline_present=1
vulnerability_management_release_gate_baseline_present=1
cryptographic_assurance_key_management_baseline_present=1
identity_credential_access_management_baseline_present=1
security_logging_monitoring_baseline_present=1
backup_recovery_resilience_baseline_present=1
secure_configuration_change_management_baseline_present=1
network_exposure_remote_access_baseline_present=1
data_classification_protection_baseline_present=1
kev_release_review_required=1
fips_crypto_boundary_required_before_production_crypto=1
phishing_resistant_mfa_required_before_remote_privileged_access=1
security_event_logging_required_before_hosted_service=1
backup_restore_recovery_evidence_required_before_hosted_service=1
secure_configuration_change_control_required_before_hosted_service=1
network_exposure_review_required_before_hosted_service=1
data_classification_review_required_before_hosted_service=1
sbom_required_before_production_installer=1
third_party_security_validation_required_before_security_release=1
incident_response_plan_required_before_production_service=1
recurring_source_review_required=1
implementation_behavior_changed=0
runtime_authority_granted=0
security_boundary_claimed=0
certification_claim_allowed=0
compliance_claim_allowed=0
external_endorsement_claimed=0
production_protection_claim_allowed=0
```

## Memory-Safety Roadmap

Latticra currently contains C and restricted C++ code. That remains allowed only under `docs/security/C_CPP_SECURITY_PROFILE.md`.

Required memory-safety posture:

```text
new network-facing code -> memory-safe language preferred
new cryptographic key-handling code -> memory-safe language preferred
new parser for untrusted external input -> memory-safe language preferred or restricted C profile with fuzzing and exception record
new installer or host-mutation authority -> memory-safe language preferred
existing C/C++ substrate -> strict profile, bounded buffers, no unsafe string APIs, explicit review of buffer overflow, format-string, off-by-one, use-after-free, and lifetime hazards, sanitizer/static-analysis path
C/C++ unsafe exception -> documented exception with lifetime, buffer, failure, test, and reviewer fields
```

Short-term mitigations:

- keep `strcpy`, `strcat`, `sprintf`, `vsprintf`, `gets`, `tmpnam`, and `tempnam` forbidden;
- keep `system()` and `popen()` forbidden in source roots;
- keep shell authority centralized and guarded in installer code;
- keep pointer, buffer, lifetime, and ownership rules explicit at C ABI boundaries;
- keep parser and source-buffer invariants tested with malformed, boundary-length, truncation, and hostile-input cases;
- keep retained C/C++ high-risk paths covered by regression tests for buffer-overflow-class, format-string, off-by-one, and lifetime faults where practical;
- require fuzzing or a documented exception before any parser is promoted to a security boundary.

Long-term direction:

- prefer Rust or another memory-safe implementation language for new infrastructure-facing surfaces where practical;
- isolate C substrate code behind small ABI wrappers;
- keep C++ authority code narrow, RAII-based, and exception-free across C/security boundaries;
- publish component-by-component migration or mitigation notes before any production security claim.

## Zero-Trust Runtime Requirements

No future runtime, agentic automation, network, host I/O, update, recovery, boot, or hardware request may be promoted unless all fields below are available and tested:

```text
request_kind_known=1
requested_effect_known=1
caller_context_known=1
operator_identity_known=1
asset_or_resource_identity_known=1
workload_or_service_identity_known=1
device_or_host_integrity_context_known=1
tool_or_mcp_boundary_known=1
context_sharing_scope_known=1
mode_matches_request_family=1
authority_prerequisites_satisfied=1
operator_confirmation_is_metadata_only=1
policy_decision_reported=1
denial_reason_reported=1
audit_record_emitted=1
unknown_request_denied=1
unknown_effect_denied=1
future_gate_denied_until_contract=1
```

## Supply-Chain Requirements

Before a production installer, production package, internet-facing service, or production update lane can be claimed, Latticra requires:

- SBOM evidence for shipped artifacts;
- dependency inventory with license and security review;
- KEV/NVD review or documented offline exception before release;
- vulnerability-management release gate before production release or supported-version claims;
- pinned CI actions and read-only workflow permissions;
- locked dependency builds where the package manager supports it;
- no ad hoc network client commands in workflows without a dedicated review guard;
- software update and patch integrity, authenticity, validation, and rollback evidence before any mutating update lane;
- third-party component update plan for supported product lifetime;
- vulnerability disclosure route and triage process.

## Cryptographic Assurance Requirements

Current Seal cryptographic work is evidence and metadata oriented. It is not production cryptographic enforcement.

Production cryptography requires:

- defined cryptographic module boundary;
- approved algorithm and parameter inventory;
- key lifecycle and storage contract;
- randomness source contract;
- validation and self-test behavior;
- side-channel and sensitive-data handling review;
- FIPS 140-3 applicability decision;
- explicit non-FIPS disclosure if FIPS validation is not pursued;
- post-quantum inventory and migration planning before long-lived secrecy claims;
- cryptographic assurance and key-management baseline before production cryptography claims;
- authority-neutral crypto graduation gate before any verified receipt can influence future authority-bearing policy;
- test fixtures for malformed keys, unsupported algorithms, stale requests, replayed requests, and denied verification paths.

## Identity, Credential, and Access Management Requirements

No future hosted service, hosted administration surface, privileged operator role, remote access path, service-account runtime authority, SSO/federation claim, MFA claim, or identity-security claim may be promoted until Latticra has:

- human, service, machine, and local identity inventories;
- privileged role and role-to-effect mapping;
- phishing-resistant MFA path for privileged and remote access;
- account lifecycle and deprovisioning contract;
- break-glass access policy and monitoring;
- credential storage, recovery, rotation, and reuse review;
- help-desk identity verification process for access changes;
- identity event logging and privileged behavior review;
- owner and expiration for every access exception;
- operator-visible identity and access non-claims.

## Security Logging, Monitoring, and Detection Requirements

No future hosted service, production runtime, remote access path, privileged administration surface, SIEM integration, telemetry export, security monitoring claim, or detection-service claim may be promoted until Latticra has:

- security event source inventory and owner mapping;
- audit event selection and event schema contract;
- runtime policy decision and denial reason events;
- identity, access, privileged action, configuration change, and security error events;
- event severity taxonomy and time-source requirements;
- log redaction and secret-marker scanning;
- log integrity, access control, retention, and disposal policy;
- centralization or export path planning;
- alerting expectation for disabled critical log sources;
- detection triage owner and incident handoff path;
- operator-visible logging and monitoring non-claims.

## Backup, Recovery, and Cyber Resilience Requirements

No future hosted service, production runtime, production installer, production package, mutating update lane, rollback path, failover path, ransomware recovery feature, disaster-recovery claim, continuity claim, or production recoverability claim may be promoted until Latticra has:

- critical asset inventory and dependency restore order;
- business impact or service-priority record;
- RTO and RPO evidence;
- backup scope and owner;
- offline, immutable, or otherwise protected backup path;
- backup encryption and access-control review;
- backup integrity verification and restore-test result;
- clean recovery environment plan;
- golden-image or infrastructure-as-code restore path;
- rollback plan and recovery authorization;
- recovery communication and incident-response handoff path;
- post-recovery validation and lessons-learned update path;
- owner and expiration for recovery exceptions;
- operator-visible recovery non-claims.

## Secure Configuration and Change Management Requirements

No future hosted service, production runtime, production installer, production package, infrastructure automation lane, host mutation lane, configuration hardening claim, secure-default claim, configuration scanning claim, drift-detection claim, or compliance claim may be promoted until Latticra has:

- configuration item inventory and owners;
- secure baseline configuration record;
- configuration checklist or equivalent verification artifact;
- secure default and default-credential absence review;
- approved change request and risk review;
- change owner and test evidence;
- rollback plan before configuration mutation;
- drift-detection and unauthorized-change response plan;
- configuration secret review;
- configuration-change log event mapping;
- owner and expiration for configuration exceptions;
- operator-visible configuration non-claims.

## Network Exposure and Remote Access Requirements

No future hosted service, internet-facing service, production runtime, production installer, production package, infrastructure automation lane, remote administration path, remote access software claim, RMM claim, service-listener claim, ingress/egress control claim, firewall policy claim, segmentation claim, DNS/TLS service claim, or production network claim may be promoted until Latticra has:

- network asset inventory and owners;
- network data-flow map;
- internet-exposed service inventory;
- inbound port, protocol, and owner record;
- outbound egress policy;
- firewall policy review;
- segmentation boundary record;
- remote access tool inventory and approved remote access path;
- phishing-resistant MFA or exception record for remote access;
- device posture requirement;
- approved RMM allowlist and unauthorized RMM detection plan;
- DNS resolver policy and TLS certificate lifecycle record;
- network log-source inventory and flow visibility plan;
- incident handoff path;
- owner and expiration for network exceptions;
- operator-visible network non-claims.

## Data Classification and Protection Requirements

No future hosted service, production runtime, production installer, production package, telemetry export, analytics feature, data storage service, customer-data handling claim, PII processing claim, encryption-at-rest claim, DLP claim, data retention claim, data deletion claim, breach-notification claim, privacy claim, or production data-protection claim may be promoted until Latticra has:

- data inventory and owners;
- data classification and information type categorization;
- sensitive-data flow map;
- PII presence review and confidentiality impact record;
- data minimization and collection-purpose review;
- access-control and encryption-at-rest/in-transit decisions;
- retention period and disposal process;
- backup data protection evidence;
- log/report redaction and secret or PII scan evidence;
- data-loss prevention plan;
- incident-response handoff path;
- owner and expiration for data exceptions;
- operator-visible data non-claims.

## Operational Security Requirements

Before any production service, hosted system, or critical infrastructure deployment:

- assign a named cybersecurity owner;
- maintain asset inventory and data-flow inventory;
- define secure configuration baseline and change-control evidence;
- define network exposure and remote-access evidence;
- define data classification and protection evidence;
- require MFA/SSO for privileged accounts;
- require phishing-resistant MFA planning for remote and privileged access;
- prohibit shared administrative accounts and default credentials;
- collect security-relevant logs without leaking secrets;
- define log retention, integrity, time-source, triage, and incident-handoff evidence;
- define incident response and vulnerability disclosure procedures;
- publish a cyber incident reporting and response baseline before any incident-response feature;
- define backup, restore, and recovery evidence;
- publish a backup, recovery, and cyber resilience baseline before any recovery-service or failover claim;
- schedule table-top or third-party validation before security release;
- maintain recurring NSA/CISA/FBI/NIST source review.

## Current Evidence

Current supporting local evidence:

```text
SECURITY.md
docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md
docs/MEMORY_SAFETY_ROADMAP.md
docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md
docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md
docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md
docs/LATTICRA_SEAL_CRYPTO_GRADUATION_GATE_IMPLEMENTATION.md
docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md
docs/SECURITY_LOGGING_MONITORING_BASELINE.md
docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md
docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md
docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md
docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md
docs/security/C_CPP_SECURITY_PROFILE.md
docs/security/C_ABI_BOUNDARY_POLICY.md
scripts/test-quality-safety-guards.sh
scripts/test-defensive-threat-model-validation.sh
scripts/test-defensive-threat-model-validation-refinement.sh
scripts/test-high-assurance-security-baseline.sh
scripts/test-memory-safety-roadmap.sh
scripts/test-supply-chain-security-baseline.sh
scripts/test-cyber-incident-reporting-response-baseline.sh
scripts/test-vulnerability-management-release-gate-baseline.sh
scripts/test-cryptographic-assurance-key-management-baseline.sh
scripts/test-latticra-seal-crypto-graduation-gate.sh
scripts/test-identity-credential-access-management-baseline.sh
scripts/test-security-logging-monitoring-baseline.sh
scripts/test-backup-recovery-resilience-baseline.sh
scripts/test-secure-configuration-change-management-baseline.sh
scripts/test-network-exposure-remote-access-baseline.sh
scripts/test-data-classification-protection-baseline.sh
```

## Non-Claims

This baseline does not implement runtime execution, effect execution, capability enforcement, cryptographic verification, signing, host behavior, network behavior, MCP behavior, AI-agent execution, model execution, tool execution, shell execution, production protection, sandboxing, malware prevention, ransomware prevention, incident response, recovery behavior, certification, accreditation, compliance, external endorsement, or runtime authority.

It also does not claim that Latticra is a finished operating system, hardened sandbox, production security product, high-assurance certified product, or critical infrastructure platform.

## Validation

This baseline is guarded by:

```sh
sh scripts/test-high-assurance-security-baseline.sh
```

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
incident-response and disclosure requirements
non-claims that remain closed
```

## Authoritative Source Inventory

Date checked: 2026-05-26

| Source | Current guidance used | Latticra allocation |
| --- | --- | --- |
| NSA Zero Trust Implementation Guidelines, Primer, Discovery Phase, Phase One, and Phase Two | Zero trust work begins with visibility over data, applications, assets, services, access, and authorization activity, then advances through phased activities, requirements, precursors, and successors toward target-level maturity. | Keep runtime authority denied until request identity, asset identity, authorization state, evidence level, prerequisites, successors, and audit output are visible. |
| NSA/CISA Memory Safe Languages CSI | Memory-safe language adoption should be considered, while existing code can be improved through interoperability and mitigations where migration is not practical. | Publish and guard a memory-safety roadmap for C/C++ substrate code; prefer memory-safe implementation for new high-risk infrastructure surfaces. |
| CISA Secure by Design | Manufacturers should take ownership of customer security outcomes, practice transparency/accountability, and lead from the top. | Require evidence-bound public claims, vulnerability reporting, no hidden security costs, deterministic reports, and leadership-owned security gates. |
| CISA/FBI Product Security Bad Practices | Avoid exceptionally risky practices, including absent memory-safety roadmaps, injection classes, known-insecure crypto, weak defaults, and unmanaged dependencies. | Guard against unsafe APIs, shell injection surfaces, default-secret patterns, unbounded buffers, path traversal, and production crypto claims without a module boundary. |
| CISA Cross-Sector Cybersecurity Performance Goals | Establish baseline practices for asset inventory, vulnerability management, logging, account security, incident response, recovery, and third-party validation. | Maintain source and dependency inventory, KEV-aware release checks, explicit logs/reports, incident plan, recovery contracts before mutation, and third-party review before security release. |
| CISA Zero Trust Maturity Model v2 | Mature zero trust uses identity, devices, networks, applications/workloads, and data pillars with visibility, analytics, automation, orchestration, and governance. | Treat each Latticra request as a per-request policy decision; preserve deny-by-default behavior for network, host, recovery, boot, and tool authority. |
| CISA Known Exploited Vulnerabilities Catalog | Internet-facing exploited vulnerabilities need timely mitigation or compensating controls. | Before any internet-facing asset exists, create a KEV review gate; current project has no internet-facing runtime authority. |
| FBI Cyber | The active threat environment includes ransomware, nation-state targeting, critical infrastructure risk, rapidly changing IOCs/TTPs, and reporting through FBI/IC3 paths. | Keep the threat model defensive, keep reports private, add incident-reporting paths, and avoid offensive payload, persistence, exfiltration, and evasion content. |
| NIST Cybersecurity Framework 2.0 | Govern, Identify, Protect, Detect, Respond, and Recover provide current cybersecurity risk-management functions. | Map future infrastructure readiness to CSF 2.0 functions before production claims. |
| NIST SP 800-218 SSDF v1.1 | Secure development should prepare the organization, protect software, produce well-secured software, and respond to vulnerabilities. | Keep tests, threat-model docs, protected source/build processes, vulnerability handling, and root-cause-driven fixes in the quality gate. |
| NIST SP 800-53 Rev. 5, Release 5.2.0 | Control families cover access, audit, configuration, identification, incident response, risk assessment, system acquisition, system integrity, and supply-chain risk management. | Use SP 800-53 as the high-assurance control vocabulary for future production profiles, not as a current compliance claim. |
| NIST SP 800-160 Vol. 2 Rev. 1 | Cyber-resilient systems should anticipate, withstand, recover from, and adapt to adverse conditions and attacks. | Keep rollback, recovery, degraded-mode, auditability, and no-hidden-effect requirements ahead of any mutating infrastructure behavior. |
| NIST SP 800-207 Zero Trust Architecture | Zero trust removes implicit trust and makes access decisions resource-focused and least-privilege. | Runtime and agentic automation authority must remain per-request, least-privilege, auditable, and denied unless prerequisites pass. |
| FIPS 140-3 | Federal cryptographic module security requirements define validated module expectations and security levels. | No production cryptography or FIPS claim is allowed until a cryptographic module boundary, validation path, key lifecycle, and dependency review exist. |

Authoritative URLs for this checkpoint are preserved in `docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md`.

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
kev_release_review_required=1
fips_crypto_boundary_required_before_production_crypto=1
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
existing C/C++ substrate -> strict profile, bounded buffers, no unsafe string APIs, narrow ownership, sanitizer/static-analysis path
C/C++ unsafe exception -> documented exception with lifetime, buffer, failure, test, and reviewer fields
```

Short-term mitigations:

- keep `strcpy`, `strcat`, `sprintf`, `vsprintf`, `gets`, `tmpnam`, and `tempnam` forbidden;
- keep `system()` and `popen()` forbidden in source roots;
- keep shell authority centralized and guarded in installer code;
- keep pointer, buffer, lifetime, and ownership rules explicit at C ABI boundaries;
- keep parser and source-buffer invariants tested with malformed and boundary inputs;
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
asset_or_resource_identity_known=1
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
- pinned CI actions and read-only workflow permissions;
- locked dependency builds where the package manager supports it;
- no ad hoc network client commands in workflows without a dedicated review guard;
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
- test fixtures for malformed keys, unsupported algorithms, stale requests, replayed requests, and denied verification paths.

## Operational Security Requirements

Before any production service, hosted system, or critical infrastructure deployment:

- assign a named cybersecurity owner;
- maintain asset inventory and data-flow inventory;
- require MFA/SSO for privileged accounts;
- collect security-relevant logs without leaking secrets;
- define incident response and vulnerability disclosure procedures;
- define backup, restore, and recovery evidence;
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
docs/security/C_CPP_SECURITY_PROFILE.md
docs/security/C_ABI_BOUNDARY_POLICY.md
scripts/test-quality-safety-guards.sh
scripts/test-defensive-threat-model-validation.sh
scripts/test-defensive-threat-model-validation-refinement.sh
scripts/test-high-assurance-security-baseline.sh
scripts/test-memory-safety-roadmap.sh
scripts/test-supply-chain-security-baseline.sh
```

## Non-Claims

This baseline does not implement runtime execution, effect execution, capability enforcement, cryptographic verification, signing, host behavior, network behavior, MCP behavior, AI-agent execution, model execution, tool execution, shell execution, production protection, sandboxing, malware prevention, ransomware prevention, incident response, recovery behavior, certification, accreditation, compliance, external endorsement, or runtime authority.

It also does not claim that Latticra is a finished operating system, hardened sandbox, production security product, high-assurance certified product, or critical infrastructure platform.

## Validation

This baseline is guarded by:

```sh
sh scripts/test-high-assurance-security-baseline.sh
```

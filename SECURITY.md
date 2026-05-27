# Security Policy

## Project status

Latticra is an early-stage systems architecture and language implementation project.

It is not currently a finished operating system, hardened sandbox, production runtime, installer, recovery writer, hardware mutation tool, server agent, or security boundary.

Security-related work in this repository should remain evidence-bound:

```text
no claim without evidence
no execution before a contract
no mutation before visibility
no hardware effect before an explicit gate
no recovery behavior before rollback and failure behavior are documented
```

## Supported versions

Latticra does not currently publish stable production releases.

Security reports should target the current `main` branch unless a maintainer explicitly identifies another supported branch or release line.

| Version or branch | Supported |
| --- | --- |
| `main` | Best-effort security review |
| Active feature/design branches | Best-effort while active |
| Tags/releases | Not security-supported unless explicitly marked |

## Reporting a vulnerability

Please do not publish exploit details in a public issue, pull request, discussion, social post, or comment thread.

Preferred reporting path:

1. Use GitHub private vulnerability reporting or the repository security advisory flow if available.
2. If a private reporting path is not available, open a minimal public issue that says only that you need a private security contact path. Do not include exploit details, proof-of-concept payloads, secrets, or reproduction steps in that public issue.

A useful private report should include:

- affected file, component, or document;
- whether the issue is in code, tests, documentation, CI, or a claim boundary;
- clear reproduction steps, when safe to share privately;
- expected behavior;
- observed behavior;
- potential impact;
- whether the issue requires local access, malformed input, repository write access, CI access, network access, or hardware access;
- suggested fix, if known.

## Vulnerability scope

Reports are in scope when they involve:

- parser memory safety risk;
- unchecked buffer behavior;
- malformed L-UI source handling;
- source-span or diagnostic confusion that could hide rejected behavior;
- CI or test gaps that allow unsupported behavior to appear accepted;
- documentation that overstates security maturity;
- repository workflow behavior that could expose secrets or unsafe automation;
- future server, update, recovery, hardware, or execution code once such code exists.

Reports are also welcome when they identify a mismatch between an implementation and a merged contract.

## Currently out of scope

The following are usually out of scope unless they reveal a concrete security issue in this repository:

- requests for production hardening of unfinished features;
- claims that Latticra is not a complete operating system, because that is already a documented non-claim;
- issues in third-party tools not controlled by this repository;
- social engineering against maintainers or users;
- denial-of-service against GitHub, CI providers, package registries, or unrelated infrastructure;
- attacks against systems you do not own or have explicit permission to test.

## Safe testing rules

Security testing must be limited to code, files, and systems you own or have explicit permission to test.

Do not:

- run destructive tests against third-party systems;
- attempt unauthorized access;
- exfiltrate data;
- publish secrets;
- test against unrelated production services;
- submit payloads designed to damage a maintainer's system;
- use Latticra security reports to coordinate malware, ransomware, credential theft, botnets, persistence, evasion, or unauthorized exploitation.

For parser and source-handling reports, prefer minimal local fixtures and deterministic reproduction steps.

## Disclosure expectations

Maintainers will make a best-effort attempt to:

1. acknowledge private reports;
2. assess whether the report is security-relevant;
3. create or update a contract when the security boundary is unclear;
4. add tests before or alongside fixes;
5. avoid overstating the maturity of the fix;
6. credit reporters when appropriate and requested.

No response-time SLA is promised at this stage.

## Security boundaries and non-claims

Latticra currently does not claim to provide:

- kernel isolation;
- hardened sandboxing;
- privilege separation;
- malware containment;
- ransomware prevention;
- secure boot;
- secure update delivery;
- hardware recovery safety;
- production-ready cryptography;
- production server security;
- operating-system completeness.

If future work introduces any of these areas, it should first receive a contract, tests, documentation, and explicit non-claims before being treated as security-relevant capability.

## Secrets and sensitive data

Do not include real secrets in issues, pull requests, tests, fixtures, screenshots, logs, or documentation.

Examples of secrets and sensitive data include:

- API keys;
- tokens;
- passwords;
- private keys;
- recovery phrases;
- session cookies;
- personal identifying information;
- private infrastructure details;
- exploit details for unpatched third-party systems.

If a secret is accidentally committed, assume it is compromised and rotate it immediately.

## Security development principles

Security-relevant changes should prefer:

- small, reviewable diffs;
- explicit contracts before implementation;
- deterministic tests;
- no-effect defaults;
- fail-closed behavior;
- stable diagnostics;
- source-span clarity;
- explicit non-claims;
- clear rollback or failure behavior when mutation is ever introduced.

## High-assurance standards posture

The current high-assurance standards checkpoint is recorded in `docs/HIGH_ASSURANCE_SECURITY_BASELINE.md`.

That baseline tracks current NSA, CISA, FBI, and NIST security guidance as source input for Latticra security work. It requires memory-safety roadmap discipline, zero-trust runtime-boundary prerequisites, SSDF-style secure development evidence, CPG-inspired operational readiness gates, KEV-aware release review, SBOM evidence before production installer claims, a FIPS 140-3 cryptographic module boundary decision before any production cryptography claim, identity/access evidence before privileged or remote access claims, logging/detection evidence before hosted-service or monitoring claims, recovery evidence before backup, restore, rollback, failover, or continuity claims, secure configuration/change-control evidence before hosted-service or hardening claims, network exposure/remote-access evidence before internet-facing or remote-administration claims, and data classification/protection evidence before sensitive-data, PII, telemetry, analytics, or customer-data claims.

The component-level memory-safety roadmap is recorded in `docs/MEMORY_SAFETY_ROADMAP.md`.

The supply-chain security baseline is recorded in `docs/SUPPLY_CHAIN_SECURITY_BASELINE.md`.

The zero-trust runtime authority baseline is recorded in `docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md`.

It requires caller identity, resource identity, per-request authorization, least-privilege effect scope, policy decision visibility, denial reason visibility, and audit records before any future runtime authority is considered. Operator confirmation remains metadata-only and must not override denied effects.

The cyber incident reporting and response baseline is recorded in `docs/CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md`.

It documents CISA, FBI, IC3, and joint #StopRansomware reporting paths, evidence-preservation requirements, out-of-band communication expectations, and the future gates required before any incident-response or report-assistance feature exists. Latticra does not report incidents, notify customers, contact law enforcement, collect forensic evidence, or provide incident-response services.

The vulnerability management release gate baseline is recorded in `docs/VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md`.

It keeps release claims blocked until vulnerability source review, KEV/NVD review, disclosure path evidence, exception ownership, exception expiration, and non-exploitability evidence are recorded. Latticra does not publish security advisories, submit CVEs, generate SBOMs, claim vulnerability-free status, or authorize production releases.

The cryptographic assurance and key management baseline is recorded in `docs/CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md`.

It keeps cryptographic claims blocked until module boundaries, algorithm and parameter inventory, key lifecycle, key storage, key destruction, randomness, self-tests, sensitive-data handling, post-quantum migration planning, and FIPS/CMVP claim gates are recorded. Latticra does not implement production cryptography, signing authority, key storage, key generation, entropy collection, random-bit generation, FIPS validation, CMVP submission, CAVP testing, or post-quantum migration.

The identity, credential, and access management baseline is recorded in `docs/IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md`.

It keeps hosted service, remote access, privileged operator, SSO/federation, MFA, and identity-security claims blocked until human/service/machine identity inventory, phishing-resistant MFA planning, account lifecycle, privileged role mapping, break-glass policy, credential handling, identity logging, and access-exception evidence are recorded. Latticra does not implement an identity provider, MFA provider, remote login, account database, credential store, hosted administration surface, or privileged access authority.

The security logging, monitoring, and detection baseline is recorded in `docs/SECURITY_LOGGING_MONITORING_BASELINE.md`.

It keeps production monitoring, SIEM integration, telemetry export, log collection, hosted service, and detection-service claims blocked until event-source inventory, audit-event selection, log schema, runtime decision events, denial reason events, identity/access events, privileged-action events, redaction, integrity, retention, disposal, time-source, triage, and incident-handoff evidence are recorded. Latticra does not implement a log collector, SIEM, telemetry export, host sensor, network sensor, alerting service, detection rule, log storage service, or monitoring authority.

The backup, recovery, and cyber resilience baseline is recorded in `docs/BACKUP_RECOVERY_RESILIENCE_BASELINE.md`.

It keeps backup, restore, rollback, failover, disaster-recovery, ransomware-recovery, hosted-service recovery, and continuity claims blocked until critical asset inventory, restore ordering, RTO/RPO, backup scope, backup integrity verification, restore testing, clean recovery environment planning, recovery authorization, recovery communications, incident handoff, and lessons-learned evidence are recorded. Latticra does not implement backup creation, backup storage, restore execution, rollback execution, failover, disaster recovery, recovery orchestration, continuity operations, or recovery authority.

The secure configuration and change management baseline is recorded in `docs/SECURE_CONFIGURATION_CHANGE_MANAGEMENT_BASELINE.md`.

It keeps secure-default, configuration hardening, configuration scanning, drift-detection, infrastructure-as-code, hosted-service configuration, and production configuration claims blocked until configuration item inventory, secure baseline configuration, checklist evidence, default-credential absence review, approved change record, risk review, test evidence, rollback plan, drift-detection plan, secret review, configuration-change logging, and exception ownership are recorded. Latticra does not implement host configuration mutation, infrastructure configuration mutation, configuration enforcement, configuration scanning, drift detection, change approval workflow, rollback execution, or configuration authority.

The network exposure and remote access baseline is recorded in `docs/NETWORK_EXPOSURE_REMOTE_ACCESS_BASELINE.md`.

It keeps internet-facing service, remote administration, remote access software, RMM, service-listener, network client, firewall policy, segmentation, ingress/egress control, DNS/TLS service, and production network claims blocked until network asset inventory, internet exposure inventory, inbound owner records, egress policy, firewall policy review, segmentation boundaries, remote access tool inventory, MFA/device posture, RMM allowlisting, unauthorized RMM detection, DNS/TLS lifecycle, network log sources, flow visibility, incident handoff, and exception ownership are recorded. Latticra does not implement network access, service listeners, network clients, DNS, TLS, firewall changes, routing changes, remote access, RMM tooling, segmentation, scanning, or network authority.

The data classification and protection baseline is recorded in `docs/DATA_CLASSIFICATION_PROTECTION_BASELINE.md`.

It keeps sensitive-data collection, PII collection, telemetry export, data storage, analytics, encryption-at-rest, DLP, data retention, data deletion, breach-notification, privacy, customer-data handling, and production data-protection claims blocked until data inventory, data classification, information type categorization, sensitive-data flows, PII review, minimization, purpose, access controls, encryption decisions, retention, disposal, backup protection, report/log redaction, secret/PII scanning, DLP planning, incident handoff, and exception ownership are recorded. Latticra does not implement data collection, PII collection, telemetry export, data storage, analytics, encryption at rest, DLP, privacy engineering, data purge, retention enforcement, breach notification, or data authority.

This posture is an allocation of required work, not a compliance claim. It does not certify Latticra, accredit Latticra, make Latticra a production security product, or create a hardened runtime boundary.

## Contact and attribution

Use GitHub private vulnerability reporting or the repository security advisory flow when available.

If public contact is the only available path, open a minimal public issue requesting a private security contact and wait for maintainer direction before sharing details.

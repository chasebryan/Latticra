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

## Contact and attribution

Use GitHub private vulnerability reporting or the repository security advisory flow when available.

If public contact is the only available path, open a minimal public issue requesting a private security contact and wait for maintainer direction before sharing details.

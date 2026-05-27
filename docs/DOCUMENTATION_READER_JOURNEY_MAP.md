# Documentation Reader Journey Map

Status: active reader journey map
Last updated: 2026-05-26 CDT
Scope: user, operator, reviewer, contributor, packager, security reviewer, subsystem implementer, public-site reader, and handbook reader routes.

## Purpose

This map keeps Latticra documentation usable for different readers without weakening the evidence boundary.

Use it with [`README.md`](README.md), [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), and [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md).

The goal is simple: each reader should know where to start, what they can safely conclude, where to find proof, and which claims remain blocked.

## Journey Matrix

| Reader | Start | Continue to | Success criteria | Stop signals |
| --- | --- | --- | --- | --- |
| New local user | [`../README.md`](../README.md), [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md), [`start.html`](start.html) | [`../installer/README.md`](../installer/README.md), [`NON_CLAIMS.md`](NON_CLAIMS.md) | Reader can identify guarded user-local paths and cleanup/reset expectations. | Any expectation of root install, daily-driver install, production runtime, or broad host management. |
| Operator | [`../STATUS.md`](../STATUS.md), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`validation.html`](validation.html) | Relevant installer, platform, or subsystem source record | Operator can identify current posture, runnable checks, denied effects, and required evidence. | Any unclear effect boundary, missing reset path, or missing non-claim near a runnable path. |
| Reviewer | [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), [`NON_CLAIMS.md`](NON_CLAIMS.md) | [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md) | Reviewer can trace public wording to source evidence and blocked adjacent claims. | Public wording lacks a source record, validation path, or non-claim boundary. |
| Contributor | [`README.md`](README.md), [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md), [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md) | [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) | Contributor can change docs without broadening claims or breaking mirrors. | Change would require implementation evidence, guard changes, or stronger public wording. |
| Packager or platform reviewer | [`validation.html`](validation.html), platform README or workflow record | [`PRODUCTION_INSTALLER_READINESS_CONTRACT.md`](PRODUCTION_INSTALLER_READINESS_CONTRACT.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) | Reviewer can identify local-only package posture and platform-specific blockers. | Any implied Fedora approval, Ubuntu archive readiness, Debian archive readiness, FreeBSD official port, OpenBSD official port, openSUSE official package, or production installability. |
| Security reviewer | [`../SECURITY.md`](../SECURITY.md), [`security.html`](security.html), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) | [`DEFENSIVE_THREAT_MODEL_CONTRACT.md`](DEFENSIVE_THREAT_MODEL_CONTRACT.md), [`HIGH_ASSURANCE_SECURITY_BASELINE.md`](HIGH_ASSURANCE_SECURITY_BASELINE.md), [`ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md`](ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md) | Reviewer can separate defensive planning from security guarantees. | Any claim of malware prevention, ransomware prevention, hardened sandboxing, certification, or production protection. |
| Subsystem implementer | [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md) | Relevant contract, implementation plan, implementation record, status record, and guard | Implementer can find the exact boundary and validation path before editing. | Missing contract, missing guard, or implementation language that outruns status. |
| Public-site reader | [`index.html`](index.html), [`map.html`](map.html), [`status.html`](status.html) | Source Markdown records linked from the public page | Reader can scan posture quickly and reach exact source records. | Public HTML implies stronger claims than source Markdown. |
| Handbook reader | [`latticra-system-substrate/README.md`](latticra-system-substrate/README.md) | [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md), project notes, status records | Reader can connect long-form narrative to current status and source records. | Handbook narrative outruns current status or omits current non-claims. |

## Journey Rules

1. A fast route may be short, but it must not hide non-claims.
2. A product route may be readable, but it must not replace source records.
3. A reviewer route must reach source records, validation, and blocked adjacent claims.
4. A platform route must keep local-only or no-effect status visible until official evidence exists.
5. A security route must keep security non-claims visible near security-adjacent wording.
6. A contributor route must include validation and drift-response docs before public wording changes.

## Success Criteria

A reader journey is healthy when:

- the first page tells the reader what Latticra currently is and is not;
- the path to current status is visible;
- runnable commands have guarded or no-effect expectations;
- broad claims have source-record links;
- non-claims are near the claims they constrain;
- validation commands are named where evidence matters;
- the route does not require reading the full repository before making a narrow safe decision.

## Friction Signals

Treat these as documentation-product friction:

- a new reader cannot find the current status within two clicks or two source links;
- an operator sees commands before effect boundaries;
- a reviewer sees a claim before evidence;
- a packager sees package shape before local-only status;
- a security reader sees protection language before non-claims;
- a contributor sees mirrors before source-of-truth rules;
- a public site page has no route back to source Markdown.

## Boundary

This map optimizes documentation navigation only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.

# Product Documentation Cohesion

Status: active product-documentation cohesion guide
Last updated: 2026-05-26 CDT
Scope: public README, documentation hub, static site pages, installer docs, package docs, security docs, status records, subsystem maps, and reader routes.

## Purpose

This guide keeps Latticra's product-facing documentation coherent without implying that Latticra is already a production product.

In this file, "product documentation" means the reader-facing surface of the project: what a user, operator, reviewer, packager, or contributor sees before they understand the full evidence trail.

The product surface should always make four things easy to find:

1. what exists now;
2. what a reader can safely run or inspect;
3. what remains intentionally blocked;
4. what evidence would be required before the claim can become stronger.

## Cohesion Promise

All product-facing documentation should describe Latticra as:

```text
early-stage
evidence-bound
contract-first
local-first where runnable
no-effect or guarded by default
explicit about non-claims
```

Do not let a shorter product summary outgrow the evidence in status records, contracts, guard scripts, or the [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md).

## Product Surface Matrix

| Surface | Reader job | Must say | Must not imply |
| --- | --- | --- | --- |
| [`../README.md`](../README.md) | Understand identity, posture, quick start, and non-claims. | Early-stage, evidence-bound, current estimates, guarded local routes, and explicit non-claims. | Production platform, certified security, OS replacement, package approval, or broad installer readiness. |
| [`README.md`](README.md) | Choose the right documentation depth. | First reading paths, status sources, claim boundaries, platform lanes, and maintenance rules. | That every doc is equally authoritative or that public summaries override status records. |
| [`index.html`](index.html) | Scan the public site quickly. | Current posture, no-effect default, major records, and resource routes. | That GitHub Pages content is stronger than source Markdown records. |
| [`start.html`](start.html) and [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md) | Try safe local entry points. | Guarded user-local commands, reset/cleanup paths, and expected no-effect posture. | Root installation, daily-driver readiness, boot readiness, or broad host management. |
| [`validation.html`](validation.html) | Understand local evidence lanes. | Local-only validation, transcripts, static checks, and disposable/guarded boundaries. | Distribution approval, production installability, update safety, or recovery safety. |
| [`security.html`](security.html) and [`../SECURITY.md`](../SECURITY.md) | Report issues and understand security posture. | Safe testing, threat-model work, security non-claims, and evidence boundaries. | Malware prevention, ransomware prevention, certified security, or hardened sandboxing. |
| [`../installer/README.md`](../installer/README.md) | Use Panel and installer lanes. | User-local guarded behavior, configuration boundaries, and platform-specific prerequisites. | Root installer authority, unattended host mutation, production installer readiness, or OS-base installation. |
| Platform package docs | Review package shape and platform readiness. | Local-only drafts, static checks, prerequisites, and non-approval boundaries. | Fedora, Ubuntu, Debian, FreeBSD, OpenBSD, openSUSE, or vendor endorsement. |
| Subsystem maps | Enter a technical lane. | Contract, implementation, status, and guard path for the subsystem. | That subsystem progress changes overall product readiness automatically. |
| Status records | Verify current posture. | Current evidence, estimate posture, next blockers, and non-claims. | Release commitments, guarantees, or broad public claims. |

## Reader Routes

### New User

Use this route for someone trying Latticra locally:

1. [`../README.md`](../README.md)
2. [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md)
3. [`start.html`](start.html)
4. [`../installer/README.md`](../installer/README.md)
5. [`NON_CLAIMS.md`](NON_CLAIMS.md)

The route must stay practical and bounded. It should not require reading every architecture record before a guarded user-local check, but it must keep current non-claims visible.

### Reviewer

Use this route for posture or due-diligence review:

1. [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md)
2. [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md)
3. [`NON_CLAIMS.md`](NON_CLAIMS.md)
4. [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md)
5. [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md)

The route should make it easy to reject overbroad wording before it reaches public summaries.

### Contributor

Use this route for someone changing documentation or product posture:

1. [`README.md`](README.md)
2. [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md)
3. [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md)
4. The relevant subsystem contract and status record
5. The exact guard named by that record

The route should prevent documentation from getting ahead of implementation or validation evidence.

### Packager Or Platform Reviewer

Use this route for platform-specific work:

1. [`validation.html`](validation.html)
2. The platform workflow document or package README
3. [`PRODUCTION_INSTALLER_READINESS_CONTRACT.md`](PRODUCTION_INSTALLER_READINESS_CONTRACT.md)
4. [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md)
5. [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md)

The route should keep every package and platform lane local-only unless official publication or distribution evidence exists.

## Product Copy Rules

Use product copy that is specific, inspectable, and bounded.

Prefer:

```text
guarded user-local workbench
no-effect report surface
local-only package draft
static validation lane
contract-first runtime boundary
report-only Seal evidence
early-stage public status
```

Avoid:

```text
secure product
agent security platform
production installer
official package
Linux replacement
OS distribution
runtime enforcement
host protection
```

## Cross-Link Requirements

Every product-facing page that describes a capability should have a path to:

1. current status;
2. non-claims;
3. relevant contract or implementation record;
4. validation or guard evidence;
5. safe user route, if the capability can be run locally;
6. blocked-claim language, if adjacent unsupported claims are likely.

## Drift Review

Run this review when public wording changes:

1. Does the public wording match [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md)?
2. Does the route from `README.md` or `index.html` reach the exact source record?
3. Does the status record use the same posture words?
4. Does the page say what is blocked?
5. Does the validation path prove the narrow claim?
6. Does the change preserve the documentation-only boundary if no implementation changed?

## Maintenance Boundary

Use [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md) for update process, source-of-truth mirrors, estimate handling, and validation commands.

Use this file for product-facing coherence: audience route, product wording, surface responsibilities, and cross-link expectations.

# Documentation Status Record Standard

Status: active documentation status-record standard
Last updated: 2026-05-27 CDT
Scope: status records under `docs/status/`, root status mirrors, current-status summaries, estimate records, subsystem status records, platform status records, security baseline status records, public-entry alignment records, and status-index entries.

## Purpose

This standard defines how Latticra status records should be written, indexed, mirrored, and reviewed.

Status records are not ordinary notes. They anchor public posture, estimates, source-record alignment, validation state, and non-claims. A status record should make it easy to tell what is current, what evidence supports it, what remains blocked, and which public surfaces may need updates.

Use this standard with [`status/README.md`](status/README.md), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md), [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md), [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This standard does not promote claims. It keeps status records narrow enough to be useful as public posture evidence.

## Status Record Rule

Every status record should answer:

```text
What changed?
What is current now?
What evidence supports it?
What remains blocked?
Which public surfaces may need review?
Which validation proves only this narrow status?
```

If a status record cannot answer those questions, treat it as a draft or planning note until the missing evidence exists.

## Required Shape

Use this shape when practical:

```text
# [Milestone or Surface] Status

Status:
Last updated:
Scope:

## Purpose
## Current Posture
## Evidence
## Validation
## Public Mirrors
## Non-Claims
## Next Valid Work
## Boundary
```

Short status records may combine sections, but they should still preserve current posture, evidence, validation, non-claims, and boundary.

## Field Rules

| Field | Meaning | Rule |
| --- | --- | --- |
| `Status` | Lifecycle and posture label for the record. | Use concrete labels such as `public status record`, `active status index`, `status/public-entry alignment`, `local-only status`, `no-effect status`, or `blocked status`. |
| `Last updated` | Last substantive status review. | Use a concrete date. Use `CDT` when the record is tied to the project working context. |
| `Scope` | Surfaces and claims covered by the record. | Name the subsystem, source record, public mirror, estimate, platform lane, security baseline, or validation lane. |
| `Current Posture` | What is true now. | Keep it narrower than implementation, validation, non-claims, and source authority. |
| `Evidence` | Why the posture is supported. | Link source records, implementation records, reports, transcripts, guards, or review records. |
| `Validation` | How the status is checked. | Name exact guards when they exist. If validation is missing, mark the claim blocked. |
| `Public Mirrors` | Public files that may need alignment. | Name root `README.md`, `STATUS.md`, `docs/README.md`, `docs/status/CURRENT_STATUS.md`, static HTML, subsystem pages, or package README files when relevant. |
| `Non-Claims` | Adjacent blocked claims. | Keep risky boundaries near platform, installer, runtime, security, package, AI, crypto, or OS wording. |
| `Next Valid Work` | Work that can follow without overstating readiness. | Keep future work separate from current posture. |
| `Boundary` | What the status record cannot prove. | State that the record does not change behavior, authority, security posture, package approval, or readiness. |

## Status Index Entries

Every status record that should be discoverable from the status index should have one entry in [`status/README.md`](status/README.md).

Use this entry shape:

```text
- FILE_STATUS.md - short posture sentence with the current boundary and any critical field marker.
```

The index entry should be shorter than the status record. It should not introduce a stronger claim than the record.

If a status record is superseded or stale, keep the entry but add the current reader route or lifecycle boundary from [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md).

## Public Mirror Rules

When a status record changes public posture, review:

1. [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md);
2. [`../STATUS.md`](../STATUS.md);
3. [`../README.md`](../README.md);
4. [`README.md`](README.md);
5. static HTML pages that summarize the status;
6. subsystem landing pages or platform README files that name the status;
7. [`status/README.md`](status/README.md).

Do not update every public surface mechanically. Use [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md) to decide the radius.

## Estimate Status Records

Estimate records must keep planning language visible.

They should not imply:

```text
release promises
delivery dates
production readiness
capability guarantees
support commitments
```

When estimate values change, run the current estimate table source-alignment guard named in [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).

## Platform, Installer, Security, Runtime, And AI Status

Status records in risky lanes must preserve nearby non-claims.

Use local-only, no-effect, report-only, guarded, blocked, or planning wording unless the source record and validation evidence support a stronger claim.

Risky lanes include:

- platform and package posture;
- installer or updater authority;
- runtime authority;
- security protection, prevention, hardening, certification, or compliance;
- cryptographic signing, verification, key handling, or production crypto;
- AI model loading, prompt evaluation, inference, dialogue generation, tool execution, or agentic control;
- boot, OS image, root install, firmware, or host mutation.

## Validation

For status-record changes, choose validation by impact:

| Change | Checks |
| --- | --- |
| Local status wording only | `git diff --check`, trailing-whitespace check, local link check. |
| Status index entry changes | Local link check over [`status/README.md`](status/README.md). |
| Public status mirror changes | `sh scripts/test-project-strategy-status-framework.sh`. |
| Estimate values change | `sh scripts/test-current-estimate-table-source-alignment.sh`. |
| Seal status changes | `sh scripts/test-latticra-seal-docs.sh` plus exact Seal guard when applicable. |
| Platform, installer, security, runtime, or subsystem status changes | Exact guard named by the source record plus public-entry checks when public posture changes. |

## Boundary

This standard governs documentation status records only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.

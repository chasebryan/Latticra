# Documentation Source Authority Order

Status: active documentation source-authority order
Last updated: 2026-05-27 CDT
Scope: public README files, documentation hub, status records, status-index entries, estimate records, source records, subsystem records, platform records, public HTML mirrors, review packets, and documentation governance files.

## Purpose

This document defines which documentation record wins when Latticra documentation disagrees with itself.

Latticra documentation has many layers: public summaries, status mirrors, static HTML pages, subsystem records, package lanes, security baselines, review packets, and implementation records. Those layers are useful only if readers can tell which one is authoritative for a claim.

Use this order with [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md), [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md), [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md), [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md), [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This order does not promote claims. It tells reviewers which document to trust first.

## Authority Rule

When records disagree, use the narrowest current source record until the disagreement is resolved.

If a public summary is broader than its source, narrow the summary.

If a source record is broader than implementation, validation, status, or non-claims, demote the source record and then align mirrors.

If no source record exists, the claim stays blocked.

## Authority Order

| Rank | Record type | Wins for | Does not win for |
| --- | --- | --- | --- |
| 1 | Guard scripts, deterministic tests, generated reports, and implementation behavior | What the repository can actually validate or do. | Public meaning beyond the narrow validated behavior. |
| 2 | Current subsystem source records: contracts, implementation records, implementation plans, status records, and validation records | The narrow posture of a subsystem, package lane, installer lane, security baseline, runtime boundary, or report surface. | Overall product readiness unless a public status record also says so. |
| 3 | [`NON_CLAIMS.md`](NON_CLAIMS.md) and [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) | Blocked adjacent claims, allowed public wording, and claim-promotion boundaries. | Implementation evidence by themselves. |
| 4 | [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`../STATUS.md`](../STATUS.md), and status source records | Current public posture, current estimates, and next-step mirrors. | Subsystem implementation details not named by the status record. |
| 5 | Estimate source records under `docs/status/` | Estimate values and planning posture. | Release promises, readiness guarantees, or capability evidence. |
| 6 | [`REAL_SYSTEM_CONTRACT.md`](REAL_SYSTEM_CONTRACT.md), [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md), and foundation policy records | Project identity, evidence rules, and promotion requirements. | Current completion status unless mirrored by current status records. |
| 7 | [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md) and documentation maps | Discovery, routing, and exhaustive indexing. | Capability truth when a linked source record is narrower. |
| 8 | Documentation governance files such as maintenance, health, traceability, style, validation, drift response, source authority, subsystem standard, and public-site mirror standard | How documentation should be changed, reviewed, validated, and aligned. | Product capability or implementation evidence. |
| 9 | Public summaries such as [`../README.md`](../README.md), [`README.md`](README.md), static HTML pages, public maps, and public dashboards | Reader-friendly orientation and routing. | Claims broader than source records, non-claims, status, or validation. |
| 10 | Review packets, pull request text, announcements, and planning notes | Review decisions, dated context, and rationale. | Capability truth without a source record and validation path. Freshness and lifecycle boundaries govern stale, superseded, archived, and planning-only records. |

## Conflict Examples

| Conflict | Trust first | Action |
| --- | --- | --- |
| `index.html` says a feature is ready, but the source record says no-effect. | Source record and non-claims. | Narrow `index.html`. |
| `README.md` has an estimate that differs from `status/CURRENT_STATUS.md`. | Current status and estimate source records. | Align the README mirror and run estimate checks if values changed. |
| A platform README implies package approval, but the platform workflow says local-only. | Platform workflow and non-claims. | Restore local-only wording. |
| A subsystem landing page implies product readiness from subsystem progress. | Subsystem source record, status record, and [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md). | Add stop signals and narrow the landing page. |
| A review packet accepts wording that the claims ledger blocks. | [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) and [`NON_CLAIMS.md`](NON_CLAIMS.md). | Mark the packet outcome blocked or revise the wording. |
| A status record sounds broader than validation evidence. | Guard, implementation, and validation records. | Demote the status record and align mirrors. |

## Review Order

When a documentation conflict appears:

1. Identify the exact public claim or route.
2. Find the linked source record through [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md).
3. Check [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) and [`NON_CLAIMS.md`](NON_CLAIMS.md).
4. Check current status and estimate source records if posture or estimates are involved.
5. Check the exact guard or validation record named by the source.
6. Apply the authority order above.
7. Apply [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md) when stale, superseded, archived, planning, draft, local-only, no-effect, report-only, or blocked records are involved.
8. Use [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md) to decide which mirrors, source records, status records, validation paths, public HTML pages, or non-claims must be reviewed.
9. Use [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md) when status records, status-index entries, status mirrors, estimate records, or public-entry alignment status notes are involved.
10. Use [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md) to narrow, align, demote, or block the wording.
11. Update only mirrors whose reader-facing claim changed.
12. Run checks from [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).

## Do Not

Do not:

- let public HTML override source Markdown;
- let a review packet override non-claims;
- let the Foundation Index imply a capability just because it links a record;
- let an estimate mirror override the estimate source record;
- let a subsystem progress note imply overall product readiness;
- let documentation governance files become capability evidence;
- edit a guard script to make documentation wording pass.

## Boundary

This order governs documentation source precedence only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.

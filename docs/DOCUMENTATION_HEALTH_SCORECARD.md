# Documentation Health Scorecard

Status: active documentation health rubric
Last updated: 2026-05-27 CDT
Scope: public Markdown, static HTML pages, status records, installer docs, package docs, security docs, subsystem landing pages, reader routes, source-record links, validation paths, and non-claim placement.

## Purpose

This scorecard gives Latticra documentation a repeatable health check.

Use it before publishing broad documentation changes, after fixing drift, or during periodic documentation review. The scorecard turns "does this feel coherent?" into a concrete review of findability, claim safety, traceability, validation, reader routes, and public/source alignment.

Use it with [`DOCUMENTATION_READER_JOURNEY_MAP.md`](DOCUMENTATION_READER_JOURNEY_MAP.md), [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md), [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md), [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md), [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md), [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md), [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), and [`NON_CLAIMS.md`](NON_CLAIMS.md).

This rubric does not promote claims. It only checks whether documentation accurately reflects current evidence.

## Scorecard

| Dimension | Healthy | Watch | Failing | Evidence to check |
| --- | --- | --- | --- | --- |
| Findability | The reader can reach current status, source records, validation, and non-claims from the entry point. | The path exists but requires too many hops or ambiguous labels. | The reader cannot find status, evidence, or boundaries from the surface. | [`README.md`](README.md), [`map.html`](map.html), [`index.html`](index.html), [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md) |
| Current status visibility | Current posture appears before aspirational or roadmap language. | Current posture exists but appears after feature language. | A page describes goals without current status. | [`../STATUS.md`](../STATUS.md), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`status.html`](status.html) |
| Freshness and lifecycle | Status labels, `Last updated` dates, stale records, superseded records, and archive boundaries match current source authority. | Dates exist but the review scope or lifecycle state is unclear. | A stale, superseded, archived, or planning record drives public claims as if it were current. | [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md), [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md), current source record |
| Impact radius discipline | The review radius matches the change: local edits stay local, claim or posture changes expand to source records, mirrors, validation, public HTML, status, and non-claims. | Radius is plausible but reviewed or intentionally untouched surfaces are not named. | A claim-affecting change is reviewed only locally, or broad mechanical updates occur without source or mirror reason. | [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md), review packet, touched files |
| Status record quality | Status records separate current posture, evidence, validation, public mirrors, non-claims, next valid work, and boundary. | A status record is accurate but missing one useful section or index detail. | A status record implies current posture without evidence, validation, non-claims, mirror route, or boundary. | [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md), [`status/README.md`](status/README.md), changed status record |
| Claim safety | Public wording stays inside the allowed wording ledger and names blocked adjacent claims. | Wording is technically narrow but easy to overread. | Wording implies production, security, package approval, runtime authority, or OS replacement without evidence. | [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), [`NON_CLAIMS.md`](NON_CLAIMS.md), [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md) |
| Source traceability | Each public claim reaches a source record, validation path, and non-claim boundary. | A source exists, but the validation or non-claim route is indirect. | The public claim has no source record or review path. | [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) |
| Non-claim proximity | Non-claims appear near the claim they constrain. | Non-claims are present elsewhere but not near the risky wording. | A risky public surface omits the relevant non-claim. | [`NON_CLAIMS.md`](NON_CLAIMS.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) |
| Validation selection | The narrowest relevant documentation, public-entry, subsystem, or platform guard is named and runnable. | Validation is listed but too broad, too narrow, or missing an exact guard. | A claim depends on validation that is missing, unknown, or failing. | [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), changed source record |
| Drift response | Drift is narrowed, aligned, demoted, or blocked with a named response path. | Drift is noticed but not yet assigned to a response. | Drift remains in a public surface after review. | [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) |
| Reader journey fitness | The surface serves its intended reader and names stop signals. | The surface is usable but mixes reader roles or hides stop signals. | The reader can reasonably infer an unsupported capability. | [`DOCUMENTATION_READER_JOURNEY_MAP.md`](DOCUMENTATION_READER_JOURNEY_MAP.md), [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md) |
| Public/source consistency | Static HTML and public summaries match source Markdown. | HTML and Markdown are close but use different posture words. | Public HTML is stronger than source Markdown. | [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md), changed HTML page, source Markdown, [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) |
| Platform posture | Platform or package wording stays local-only, draft, or no-effect unless official evidence exists. | Local-only status is present but visually secondary. | A platform page implies approval, archive readiness, official package status, or production installability. | Platform README, workflow record, status record, [`NON_CLAIMS.md`](NON_CLAIMS.md) |
| Security posture | Security docs separate defensive planning from protection guarantees. | Non-claims exist but security wording still sounds stronger than evidence. | A page implies malware prevention, ransomware prevention, hardened sandboxing, certification, or production protection. | [`../SECURITY.md`](../SECURITY.md), [`security.html`](security.html), [`HIGH_ASSURANCE_SECURITY_BASELINE.md`](HIGH_ASSURANCE_SECURITY_BASELINE.md) |
| Estimate hygiene | Estimate mirrors match source records and remain planning posture. | Estimates match but release-promise language appears nearby. | Estimates disagree or imply commitments. | [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), estimate source records, [`roadmap.html`](roadmap.html) |
| Subsystem landing-page quality | Each subsystem route exposes contract, implementation, status, guard, and non-claim context. | One element exists only in the foundation index. | A subsystem landing page implies product readiness from subsystem progress. | [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md), subsystem record, status record, guard script, [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md) |

## How To Use

1. Choose the public surface or documentation set under review.
2. Score each dimension as `healthy`, `watch`, or `failing`.
3. For every `watch` or `failing` dimension, identify the source record or missing source record.
4. Use [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md) to choose narrowing, alignment, demotion, or blocking.
5. Use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) when public wording, mirrors, status, estimates, platform posture, security wording, non-claims, or reader routes change.
6. Run the checks selected with [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).

## Minimum Passing Posture

A documentation surface passes this scorecard only when:

- local links are valid;
- current status is reachable;
- lifecycle state, freshness, and date meaning are clear when a record is stale, superseded, archived, or planning-only;
- the documented impact radius matches the change and names intentionally untouched surfaces when relevant;
- status records expose current posture, evidence, validation, public mirrors, non-claims, next valid work, and boundary when they anchor public posture;
- public claims trace to source records;
- blocked adjacent claims remain visible;
- non-claims are near risky wording;
- validation commands are named for the changed claim;
- public HTML does not exceed source Markdown;
- platform and security wording remain within current evidence;
- no page implies product readiness from planning, subsystem progress, or local static validation alone.

## Stop Conditions

Stop and demote or block the wording when:

- public copy implies production readiness, security protection, package approval, runtime authority, host control, network protection, or OS replacement;
- a claim has no source record;
- validation is missing or failing;
- status records and public pages disagree;
- static HTML is stronger than source Markdown;
- estimates differ across public mirrors;
- a runnable path omits effect boundaries, reset expectations, or cleanup context;
- non-claims are absent near security, installer, package, runtime, or platform wording.

## Review Record Template

Use this short form in a review packet, pull request, or status note:

```text
documentation_health_scorecard:
  surface:
  review_date:
  reviewer:
  dimensions:
    findability:
    current_status_visibility:
    freshness_and_lifecycle:
    impact_radius_discipline:
    status_record_quality:
    claim_safety:
    source_traceability:
    non_claim_proximity:
    validation_selection:
    drift_response:
    reader_journey_fitness:
    public_source_consistency:
    platform_posture:
    security_posture:
    estimate_hygiene:
    subsystem_landing_page_quality:
  watch_items:
  failing_items:
  selected_drift_response:
  validation_commands:
  outcome:
```

## Boundary

This scorecard measures documentation health only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.

# Documentation Change Review Packet

Status: active documentation review template
Last updated: 2026-05-27 CDT
Scope: documentation-only changes that affect public wording, reader routes, product-facing pages, command examples, non-claims, status records, status mirrors, lifecycle states, stale records, superseded records, archive boundaries, impact radius, platform posture, installer posture, package posture, subsystem landing pages, or documentation navigation.

## Purpose

Use this packet before merging or publishing documentation changes that could change how readers understand Latticra.

The packet is intentionally lightweight. It exists to make sure a documentation change names its claim boundary, source records, mirrors, non-claims, validation, and rollback path before public wording drifts.

## When To Use

Use this packet when a change touches any of these:

- [`../README.md`](../README.md)
- [`README.md`](README.md)
- [`STATUS.md`](../STATUS.md)
- [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md)
- [`status/README.md`](status/README.md)
- public HTML pages such as [`index.html`](index.html), [`map.html`](map.html), [`status.html`](status.html), [`roadmap.html`](roadmap.html), [`validation.html`](validation.html), or [`security.html`](security.html)
- installer, platform, package, security, or subsystem landing pages
- public estimates, public claims, product copy, non-claim wording, or reader routes

Do not use this packet as evidence for a stronger capability. It reviews documentation posture only.

## Packet

Copy this section into the relevant review record, pull request, or status note.

```text
documentation_change_review_packet:
  change_id:
  reviewer:
  review_date:
  change_type:
    public_wording:
    command_example:
    reader_route:
    status_record:
    status_mirror:
    estimate_mirror:
    platform_posture:
    installer_posture:
    package_posture:
    subsystem_landing_page:
    security_wording:
    non_claim_wording:
    freshness_or_lifecycle:
  touched_surfaces:
  impact_radius:
  radius_reason:
  surfaces_reviewed:
  surfaces_intentionally_not_reviewed:
  source_records:
  current_claim:
  proposed_claim:
  evidence_level:
  implementation_changed: no
  behavior_changed: no
  authority_changed: no
  non_claims_preserved:
  public_claims_ledger_checked:
  product_documentation_cohesion_checked:
  documentation_source_authority_order_checked:
  documentation_freshness_lifecycle_policy_checked:
  documentation_change_impact_radius_guide_checked:
  documentation_status_record_standard_checked:
  documentation_command_example_standard_checked:
  documentation_health_scorecard_checked:
  subsystem_documentation_standard_checked:
  public_site_mirror_standard_checked:
  documentation_traceability_matrix_checked:
  documentation_validation_playbook_checked:
  documentation_drift_response_playbook_checked:
  documentation_style_guide_checked:
  documentation_maintenance_checked:
  mirrors_checked:
  validation_commands:
  blocked_adjacent_claims:
  rollback_or_demotion_path:
  outcome:
```

## Review Steps

1. Classify the change as wording-only, navigation-only, status mirror, estimate mirror, platform posture, installer posture, package posture, subsystem landing page, or security wording.
2. Identify the source records that make the wording true.
3. Compare the wording against [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md).
4. Compare the reader route against [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md).
5. Compare audience-specific paths against [`DOCUMENTATION_READER_JOURNEY_MAP.md`](DOCUMENTATION_READER_JOURNEY_MAP.md) when routes change.
6. Apply [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md) when source records, mirrors, public pages, review packets, or governance files disagree.
7. Apply [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md) when status labels, `Last updated` dates, stale records, superseded records, archive boundaries, or lifecycle states change.
8. Use [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md) to name the review radius and touched or intentionally untouched surfaces.
9. Apply [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md) when status records, status-index entries, status mirrors, estimate records, or public-entry alignment notes change.
10. Apply [`DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md`](DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md) when runnable commands, validation command lists, install/update/reset/uninstall snippets, platform prerequisites, or public HTML command examples change.
11. Score broad route, command example, public HTML, platform, security, estimate, freshness, lifecycle, status-record, or subsystem landing-page changes with [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md).
12. Compare subsystem landing-page changes against [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md).
13. Compare static HTML changes against [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md).
14. Compare source records, mirrors, validation, lifecycle state, status-record shape, command-example boundaries, and non-claim boundaries against [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md).
15. Select validation commands with [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).
16. Choose a drift-response, narrowing, or demotion path with [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md) when records disagree.
17. Compare terminology, headings, dates, and replacement wording against [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md).
18. Compare mirror requirements against [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md).
19. Confirm that adjacent non-claims remain visible.
20. Run the narrowest relevant validation commands.
21. Name how to demote or roll back the wording if the evidence changes.

## Claim Classification

| Classification | Meaning | Required handling |
| --- | --- | --- |
| Navigation-only | Links, entry points, or ordering changed without claim change. | Check local links and affected reader routes. |
| Wording-only | Existing evidence is described more clearly without capability change. | Check claims ledger, non-claims, and source records. |
| Command example | A runnable snippet, validation command list, install/update/reset/uninstall command, platform prerequisite, or public HTML command example changed. | Apply the command example standard and preserve effect boundary, expected output, cleanup route, and blocked adjacent claims. |
| Status record | A status record, status-index entry, current-status mirror, estimate source, or public-entry alignment status note changed. | Apply the status record standard and keep current posture, evidence, validation, public mirrors, non-claims, next valid work, and boundary clear. |
| Status mirror | Public status wording is mirrored from an existing status record. | Check `STATUS.md`, `docs/status/CURRENT_STATUS.md`, and status index alignment. |
| Estimate mirror | Planning estimate wording or displayed values changed. | Check estimate source alignment and static HTML mirrors. |
| Platform posture | Fedora, Ubuntu, Debian, FreeBSD, OpenBSD, openSUSE, macOS, installer, or package wording changed. | Preserve local-only or no-effect boundaries unless official evidence exists. |
| Security wording | Security, threat-model, runtime authority, sandbox, malware, or ransomware wording changed. | Preserve security non-claims and safe-testing boundaries. |
| Freshness or lifecycle | Status labels, dates, stale records, supersession blocks, archive boundaries, or lifecycle state changed. | Apply the freshness lifecycle policy and keep stale, superseded, archived, planning, draft, local-only, no-effect, report-only, or blocked records from driving current public claims. |
| Impact radius | The change may or may not require mirrors, source records, status records, validation paths, public HTML, or non-claims to move. | Apply the impact radius guide and name reviewed and intentionally untouched surfaces. |
| Claim promotion | A public claim becomes stronger. | Stop unless contract, implementation, validation, status, non-claim update, and public-entry alignment all exist. |

## Minimum Validation

For most documentation-only packets:

```sh
git diff --check
sh scripts/test-project-strategy-status-framework.sh
```

Add these when relevant:

```sh
sh scripts/test-current-estimate-table-source-alignment.sh
sh scripts/test-latticra-seal-docs.sh
sh scripts/test-fedora-developer-workflow.sh
sh scripts/test-ubuntu-developer-workflow.sh
sh scripts/test-opensuse-developer-workflow.sh
```

Add the exact subsystem or milestone guard named by the source record when a specialized status or public-entry alignment changes.

Use [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) for guard selection, local link checks, and failure handling.

## Outcome Language

Use one of these outcome labels:

```text
accepted_navigation_only
accepted_wording_only
accepted_status_mirror
accepted_estimate_mirror
accepted_local_only_platform_posture
accepted_freshness_lifecycle_update
blocked_claim_promotion
blocked_missing_source_record
blocked_missing_validation
blocked_non_claim_drift
blocked_public_entry_drift
blocked_stale_public_source
```

## Boundary

This packet does not change source behavior, installer authority, package authority, runtime authority, shell guard behavior, workflow permissions, security posture, or product readiness.

If the proposed wording requires implementation or validation to become true, the documentation change must stay blocked until that evidence exists.

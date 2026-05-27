# Documentation Maintenance

Status: active documentation maintenance guide
Last updated: 2026-05-27 CDT
Scope: public documentation entry points, status records, status mirrors, estimate sources, static HTML mirrors, platform guides, change-impact radius, and documentation-only validation.

## Purpose

This guide defines how Latticra documentation should stay cohesive as the project changes.

Use it when a change affects public wording, capability posture, estimates, platform readiness, security claims, installer authority, package claims, subsystem status, or reader navigation.

## Source Of Truth

| Subject | Source of truth | Mirrors that may need updates |
| --- | --- | --- |
| Project identity and broad non-claims | [`../README.md`](../README.md), [`REAL_SYSTEM_CONTRACT.md`](REAL_SYSTEM_CONTRACT.md), [`NON_CLAIMS.md`](NON_CLAIMS.md) | [`map.html`](map.html), [`latticra-system-substrate/README.md`](latticra-system-substrate/README.md), [`latticra/DOCUMENTATION_MAP.md`](latticra/DOCUMENTATION_MAP.md) |
| Current status and estimates | [`../STATUS.md`](../STATUS.md), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md`](status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md), [`status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md`](status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md) | [`../README.md`](../README.md), [`status.html`](status.html), [`roadmap.html`](roadmap.html), [`index.html`](index.html) |
| Documentation source authority | [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md) | Review packets, public summaries, static HTML pages, source records, and status mirrors |
| Documentation freshness and lifecycle | [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md) | Public summaries, status records, source records, superseded records, archive boundaries, review packets, and static HTML pages |
| Documentation change impact radius | [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md) | Review packets, public entry points, source records, status records, static HTML pages, validation paths, and non-claims |
| Documentation status records | [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md), [`status/README.md`](status/README.md) | [`../STATUS.md`](../STATUS.md), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), public summaries, static HTML pages, source records, and status-index entries |
| Documentation navigation | [`README.md`](README.md), [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md) | [`../README.md`](../README.md), [`map.html`](map.html), [`project_notes/README.md`](project_notes/README.md) |
| Public site mirrors | [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md) | Static HTML pages under `docs/`, source Markdown records, status records, estimate records |
| Documentation health | [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md) | [`README.md`](README.md), [`map.html`](map.html), [`index.html`](index.html), review packets |
| Subsystem landing-page standard | [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md) | Subsystem README files, subsystem public HTML pages, [`README.md`](README.md), [`map.html`](map.html), [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md) |
| Documentation traceability | [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) | [`README.md`](README.md), [`map.html`](map.html), [`index.html`](index.html), review packets |
| Documentation validation | [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) | Review packets, status records, platform docs, subsystem landing pages |
| Documentation drift response | [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md) | Public entry points, status mirrors, estimate mirrors, platform docs, security docs |
| Documentation style and terminology | [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) | [`../README.md`](../README.md), [`index.html`](index.html), [`map.html`](map.html), platform README files, subsystem landing pages |
| Security posture | [`../SECURITY.md`](../SECURITY.md), [`HIGH_ASSURANCE_SECURITY_BASELINE.md`](HIGH_ASSURANCE_SECURITY_BASELINE.md), [`DEFENSIVE_THREAT_MODEL_CONTRACT.md`](DEFENSIVE_THREAT_MODEL_CONTRACT.md) | [`security.html`](security.html), [`../README.md`](../README.md), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md) |
| Installer authority | [`../installer/README.md`](../installer/README.md), [`../installer/docs/README.md`](../installer/docs/README.md), [`PRODUCTION_INSTALLER_READINESS_CONTRACT.md`](PRODUCTION_INSTALLER_READINESS_CONTRACT.md) | [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md), [`validation.html`](validation.html), [`../README.md`](../README.md) |
| Platform and packaging posture | Platform workflow and package README files | [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md), [`validation.html`](validation.html), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`../README.md`](../README.md) |

## Public-Entry Checklist

When a milestone changes capability posture or public wording, review these files:

```text
README.md
STATUS.md
docs/README.md
docs/FOUNDATION_INDEX.md
docs/status/CURRENT_STATUS.md
docs/status/README.md
docs/project_notes/README.md
docs/map.html
docs/status.html
docs/roadmap.html
docs/index.html
```

Do not update every file mechanically. Update only the files whose reader-facing claim actually changes.

Use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) when a public-entry change needs an explicit record of touched surfaces, source records, claim classification, mirrors, validation commands, and rollback or demotion path.

Use [`DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md`](DOCUMENTATION_SOURCE_AUTHORITY_ORDER.md) when two documentation records disagree about the same claim, estimate, status, mirror, or non-claim boundary.

Use [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md) when status labels, `Last updated` dates, stale records, superseded records, archive boundaries, or lifecycle states change.

Use [`DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md`](DOCUMENTATION_CHANGE_IMPACT_RADIUS_GUIDE.md) before deciding that a change only needs local review or that it must expand to public entries, source records, status records, mirrors, validation paths, or non-claims.

Use [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md) before creating or updating a status record, status-index entry, status mirror, estimate record, or public-entry alignment status note.

Use [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) when a public-entry change needs a source-record, mirror, validation, or non-claim lookup.

Use [`PUBLIC_SITE_MIRROR_STANDARD.md`](PUBLIC_SITE_MIRROR_STANDARD.md) when static HTML pages under `docs/` change.

Use [`DOCUMENTATION_HEALTH_SCORECARD.md`](DOCUMENTATION_HEALTH_SCORECARD.md) when a broad public-entry change needs a repeatable health check for findability, claim safety, traceability, validation, reader routes, platform posture, security posture, estimate hygiene, or public/source consistency.

Use [`SUBSYSTEM_DOCUMENTATION_STANDARD.md`](SUBSYSTEM_DOCUMENTATION_STANDARD.md) when a subsystem landing page or subsystem public summary changes.

Use [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) when choosing hygiene, link, public-entry, estimate, platform, subsystem, or claim-promotion checks.

Use [`DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md`](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md) when public pages, source records, status mirrors, estimate tables, platform docs, security wording, or non-claims disagree.

Use [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md) when a public-entry change edits terminology, status labels, date style, heading shape, link style, platform names, or replacement wording.

## Estimate Rule

Planning estimates are posture markers, not release promises.

When an estimate changes:

1. Update the source record under `docs/status/`.
2. Mirror the current public table in `README.md`, `STATUS.md`, and `docs/status/CURRENT_STATUS.md`.
3. Update static HTML summary values in `docs/index.html`, `docs/status.html`, and `docs/roadmap.html` when those pages display the changed values.
4. Run the current estimate table source-alignment guard.

## Non-Claim Rule

Never promote these claims without implementation, tests, status records, and public-entry alignment:

```text
production runtime
host protection
hardened sandbox
malware prevention
ransomware prevention
kernel enforcement
root installer
network authority
package approval
official distribution readiness
OS replacement
certification
compliance
production cryptography
AI-agent execution control
```

Use narrower language when evidence is narrow. For example, a disposable VM transcript can support a bounded local validation claim without supporting daily-driver, production, security, update-safety, recovery-safety, or distribution-readiness claims.

## Platform Documentation Rule

Platform and package documentation must state the current authority boundary:

- Fedora: local-only unless Fedora approval evidence exists.
- Ubuntu: local-only unless Ubuntu archive or PPA evidence exists.
- Debian: local-only unless Debian archive evidence exists.
- openSUSE: local-only unless Open Build Service publication or official package evidence exists.
- FreeBSD and OpenBSD: local-only unless official port evidence exists.
- macOS: no-effect or user-local only unless app-bundle write, signing, notarization, install, verification, reset, and uninstall evidence exists.

## Validation

For documentation-only work, run the narrowest relevant guard set:

```sh
git diff --check
sh scripts/test-project-strategy-status-framework.sh
sh scripts/test-current-estimate-table-source-alignment.sh
sh scripts/test-latticra-seal-docs.sh
```

Add platform guards when platform docs move:

```sh
sh scripts/test-fedora-developer-workflow.sh
sh scripts/test-ubuntu-developer-workflow.sh
sh scripts/test-opensuse-developer-workflow.sh
```

Add the exact milestone guard named by the status record when changing a milestone-specific status or public-entry alignment.

For command selection and failure handling, use [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).

## Documentation-Only Boundary

Documentation-only changes should not change source behavior, installer authority, package authority, runtime authority, shell guard behavior, workflow permissions, or security posture. If a documentation update requires code or guard changes to become true, keep the documentation claim blocked until that implementation evidence exists.

# Latticra Documentation Hub

Status: active reader-facing documentation hub
Last updated: 2026-05-26 CDT
Scope: public orientation, status, foundation contracts, subsystem records, installer and packaging documentation, and documentation-maintenance rules.

## Purpose

This file is the short route through the Latticra documentation set.

Latticra keeps a deliberately dense record trail: public status, foundation contracts, implementation records, no-effect reports, package and installer notes, strategy records, and project notes. Use this hub to choose the right level before diving into the full index.

## Start Here

| Need | Read |
| --- | --- |
| Fast user-local install and cleanup commands | [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md) |
| Current public posture and estimates | [`../STATUS.md`](../STATUS.md), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md) |
| Product-facing wording and routes | [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) |
| Documentation style and terminology | [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md) |
| Documentation traceability | [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) |
| Documentation validation | [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) |
| Documentation change review packet | [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) |
| Full architecture and operations index | [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md) |
| Project-level handbook | [`latticra-system-substrate/README.md`](latticra-system-substrate/README.md) |
| GitHub Pages documentation map | [`map.html`](map.html) |
| Current direction and near-term queue | [`project_notes/README.md`](project_notes/README.md) |
| Announcements and status history | [`status/ANNOUNCEMENTS.md`](status/ANNOUNCEMENTS.md), [`status/README.md`](status/README.md) |
| Security reporting and non-claims | [`../SECURITY.md`](../SECURITY.md), [`HIGH_ASSURANCE_SECURITY_BASELINE.md`](HIGH_ASSURANCE_SECURITY_BASELINE.md) |
| Contribution rules | [`../CONTRIBUTING.md`](../CONTRIBUTING.md) |
| Documentation maintenance rules | [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md) |

## Documentation Levels

| Level | Role | Primary files |
| --- | --- | --- |
| Public orientation | Reader-facing project identity, quick start, and non-claims | [`../README.md`](../README.md), [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md), [`map.html`](map.html) |
| Product documentation cohesion | Reader routes, product-surface responsibilities, cross-link expectations, safe copy rules, traceability, validation, documentation style, and documentation-change review | [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md), [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md), [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md), [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) |
| Live status | Current posture, estimates, milestone status, and announcement records | [`../STATUS.md`](../STATUS.md), [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`status/README.md`](status/README.md) |
| Foundation rules | Evidence ladder, real-system contract, naming, authority, effect, and security rules | [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md), [`REAL_SYSTEM_CONTRACT.md`](REAL_SYSTEM_CONTRACT.md), [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md), [`NON_CLAIMS.md`](NON_CLAIMS.md) |
| Architecture and language | C/C++ direction, Lat, LIR, L-UI, Nucleus, Runtime Boundary, and Seal contracts | [`architecture/LATTICRA_LANGUAGE_FOUNDATION.md`](architecture/LATTICRA_LANGUAGE_FOUNDATION.md), [`LANGUAGE_STRATEGY.md`](LANGUAGE_STRATEGY.md), [`RUNTIME_BOUNDARY_CONTRACT.md`](RUNTIME_BOUNDARY_CONTRACT.md), [`LATTICRA_SEAL_CONTRACT.md`](LATTICRA_SEAL_CONTRACT.md) |
| Subsystem handbooks | Focused landing pages for durable subsystems | [`latticra-system-substrate/README.md`](latticra-system-substrate/README.md), [`latticra-seal/README.md`](latticra-seal/README.md), [`latticra/DOCUMENTATION_MAP.md`](latticra/DOCUMENTATION_MAP.md) |
| Installer and platform lanes | Panel, macOS, Fedora, Ubuntu, Debian, FreeBSD, OpenBSD, openSUSE, and local package records | [`../installer/README.md`](../installer/README.md), [`../installer/docs/README.md`](../installer/docs/README.md), [`FEDORA_DEVELOPER_WORKFLOW.md`](FEDORA_DEVELOPER_WORKFLOW.md), [`UBUNTU_DEVELOPER_WORKFLOW.md`](UBUNTU_DEVELOPER_WORKFLOW.md), [`DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md`](DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md), [`FREEBSD_PORT_STATIC_VALIDATION.md`](FREEBSD_PORT_STATIC_VALIDATION.md), [`OPENBSD_PORT_STATIC_VALIDATION.md`](OPENBSD_PORT_STATIC_VALIDATION.md), [`DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md`](DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md), [`DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md`](DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md), [`DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md`](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md), [`DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md`](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md), [`DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md`](DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md), [`DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md`](DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md), [`OPENSUSE_DEVELOPER_WORKFLOW.md`](OPENSUSE_DEVELOPER_WORKFLOW.md), [`OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md`](OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md), [`OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md`](OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md), [`OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md`](OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md) |
| Project notes and strategy | Short narrative direction, upcoming work, strategy templates, and dated strategy records | [`project_notes/README.md`](project_notes/README.md), [`strategy/README.md`](strategy/README.md) |

## Reader Routes

For a user or operator:

1. Read [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md).
2. Confirm current posture in [`../STATUS.md`](../STATUS.md).
3. Use [`../installer/README.md`](../installer/README.md) only for guarded user-local Panel work.

For an implementer:

1. Read [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md).
2. Find the relevant contract and implementation record.
3. Run the guard script named by that record before changing public claims.

For a reviewer:

1. Start with [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md).
2. Compare public claims against [`NON_CLAIMS.md`](NON_CLAIMS.md).
3. Check whether the relevant implementation, guard, and status record all agree.

For packaging or platform work:

1. Use the platform README or workflow document.
2. Keep local-only status explicit.
3. Do not treat static spec, lint, or transcript lanes as distribution approval.

## Maintenance Rules

- Use [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md) before changing public entry points, estimates, status mirrors, static HTML summaries, platform posture, or non-claim wording.
- Use [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md) before changing user-facing product copy, reader routes, public site resources, installer docs, package docs, or subsystem landing pages.
- Use [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md) to map public surfaces back to source records, validation, mirrors, and non-claim boundaries.
- Use [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) to choose documentation hygiene, link, public-entry, estimate, platform, subsystem, and claim-promotion checks.
- Use [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md) for canonical project terms, status labels, date style, heading shape, link style, and replacement wording.
- Use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) when a documentation change needs an explicit claim, mirror, validation, and rollback review.
- Keep `README.md`, `STATUS.md`, `docs/status/CURRENT_STATUS.md`, and this hub aligned when public posture changes.
- Keep `docs/status/README.md` and `docs/FOUNDATION_INDEX.md` as evidence-heavy indexes; keep this file as the reader route.
- Update `docs/map.html` and related HTML pages when reader-facing estimates or dates change.
- Do not promote production runtime, host protection, package approval, certification, or OS replacement claims without reproducible implementation, tests, status records, and public-entry alignment.
- Documentation-only work should not change source behavior, installer authority, packaging authority, runtime authority, or security claims.

## Current Non-Claim Reminder

Latticra is still early-stage and evidence-bound. It is not a production security product, hardened sandbox, operating-system replacement, Fedora-approved package, Ubuntu archive-ready package, Debian archive-ready package, FreeBSD official port, OpenBSD official port, openSUSE official package, root installer, network authority, or production runtime.

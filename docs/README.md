# Latticra Documentation Hub

Status: active reader-facing documentation hub

Last updated: 2026-05-27 CDT
Scope: public orientation, live status, foundation contracts, subsystem records, installer and packaging docs, security baselines, strategy notes, and documentation maintenance.

## Purpose

This file is the deeper map behind the root [README](../README.md).

Latticra keeps a large evidence trail on purpose: status records, contracts, implementation notes, guard scripts, package lanes, platform notes, reports, public site pages, and non-claim ledgers. This hub keeps that material reachable without asking a new reader to absorb everything at once.

## First Routes

| Reader | Start | Then read |
| --- | --- | --- |
| New user | [Quick Start Cheat Sheet](QUICK_START_CHEATSHEET.md) | [Installer README](../installer/README.md), [Status](../STATUS.md) |
| Reviewer | [Current Status](status/CURRENT_STATUS.md) | [Public Claims Ledger](PUBLIC_CLAIMS_LEDGER.md), [Non-Claims](NON_CLAIMS.md), [Evidence Ladder](EVIDENCE_LADDER.md) |
| Contributor | [Contributing](../CONTRIBUTING.md) | [Foundation Index](FOUNDATION_INDEX.md), [Documentation Maintenance](DOCUMENTATION_MAINTENANCE.md) |
| Packager | Platform README below | Platform workflow or validation lane below |
| Security reviewer | [Security Policy](../SECURITY.md) | [High-Assurance Security Baseline](HIGH_ASSURANCE_SECURITY_BASELINE.md), [Defensive Threat Model](DEFENSIVE_THREAT_MODEL_CONTRACT.md) |
| Reference reader | [Reference Manual](latticra-reference-manual/README.md) | [PDF edition](latticra-reference-manual/the-latticra-reference-manual-v0.1.0.pdf), [editable Markdown](latticra-reference-manual/the-latticra-reference-manual-v0.1.0.md), [source manifest](latticra-reference-manual/source-manifest.json) |
| Handbook reader | [System Substrate README](latticra-system-substrate/README.md) | [System Substrate PDF](latticra-system-substrate/the-latticra-system-substrate.pdf), [Foundation Index](FOUNDATION_INDEX.md) |

## Core Public Documents

| Document | Role |
| --- | --- |
| [Root README](../README.md) | Short public front door and documentation router |
| [Quick Start Cheat Sheet](QUICK_START_CHEATSHEET.md) | Shortest safe user-local install, run, update, reset, and cleanup route |
| [Status](../STATUS.md) | Public status shortcut and estimate mirror |
| [Current Status](status/CURRENT_STATUS.md) | Current progress, estimates, and next priorities |
| [Foundation Index](FOUNDATION_INDEX.md) | Exhaustive architecture, implementation, guard, status, and evidence index |
| [Reference Manual](latticra-reference-manual/README.md) | Generated v0.1.0 book assembled from the current documentation corpus |
| [System Substrate handbook landing page](latticra-system-substrate/README.md) | Project-level long-form technical handbook |
| [Documentation Reader Journey Map](DOCUMENTATION_READER_JOURNEY_MAP.md) | Audience-specific reading routes and stop signals |
| [Documentation Glossary](DOCUMENTATION_GLOSSARY.md) | Shared vocabulary for evidence, validation, posture, platform, and readiness terms |
| [Documentation Health Scorecard](DOCUMENTATION_HEALTH_SCORECARD.md) | Repeatable rubric for findability, claim safety, traceability, validation, reader routes, and public/source consistency |
| [Public Claims Ledger](PUBLIC_CLAIMS_LEDGER.md) | Current public claims and blocked adjacent claims |
| [Non-Claims](NON_CLAIMS.md) | Claims Latticra explicitly does not make |
| [Real System Contract](REAL_SYSTEM_CONTRACT.md) | Project identity, real-system boundary, evidence rules, and non-claims |
| [Evidence Ladder](EVIDENCE_LADDER.md) | Promotion path from concept to real-system capability |

## Subsystem Entry Points

| Subsystem | Entry points |
| --- | --- |
| Latticra Panel | [Panel README](../installer/README.md), [installer docs](../installer/docs/README.md), [installer readiness contract](../installer/docs/INSTALLER_READINESS_CONTRACT.md) |
| Latticra Console | [Console foundation](LATTICRA_CONSOLE_FOUNDATION.md), [UI terminal language](UI_TERMINAL_LANGUAGE.md), [self-update model](SELF_UPDATE_MODEL.md) |
| Latticra Seal | [Seal README](latticra-seal/README.md), [Seal status](latticra-seal/STATUS.md), [Seal architecture](latticra-seal/ARCHITECTURE.md), [Seal usage](latticra-seal/USAGE.md), [Seal boundaries](latticra-seal/BOUNDARIES.md), [Seal product spine](latticra-seal/PRODUCT.md) |
| Lat language | [Language strategy](LANGUAGE_STRATEGY.md), [language naming policy](LANGUAGE_NAMING_POLICY.md), [Lat pipeline contract](LAT_PIPELINE_CONTRACT.md), [Lat pipeline implementation](LAT_PIPELINE_IMPLEMENTATION.md), [Lat grammar contract](LAT_LANGUAGE_GRAMMAR_CONTRACT.md) |
| LIR | [LIR shape contract](LIR_SHAPE_CONTRACT.md), [Lat to LIR lowering contract](LAT_TO_LIR_LOWERING_CONTRACT.md), [Lat to LIR implementation](LAT_TO_LIR_LOWERING_IMPLEMENTATION.md), [LIR report refinement](LIR_REPORT_REFINEMENT.md) |
| L-UI | [L-UI parser](L_UI_PARSER.md), [source grammar](L_UI_SOURCE_GRAMMAR.md), [parser diagnostics](L_UI_PARSER_DIAGNOSTICS.md), [semantic validation contract](L_UI_SEMANTIC_VALIDATION_CONTRACT.md), [rendering contract](L_UI_RENDERING_CONTRACT.md) |
| Nucleus | [Supervisor architecture](SUPERVISOR_ARCHITECTURE.md), [task execution contract](NUCLEUS_TASK_EXECUTION_CONTRACT.md), [task execution implementation](NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md), [task report refinement](NUCLEUS_TASK_REPORT_REFINEMENT.md) |
| Runtime Boundary | [runtime boundary contract](RUNTIME_BOUNDARY_CONTRACT.md), [runtime boundary implementation](RUNTIME_BOUNDARY_IMPLEMENTATION.md), [runtime boundary refinement plan](RUNTIME_BOUNDARY_REFINEMENT_PLAN.md), [runtime boundary policy matrix](RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md) |
| Nadia offline AI | [Nadia foundation](NADIA_OFFLINE_AI_FOUNDATION.md), [local context engine](NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md), [runtime profile](NADIA_RUNTIME_PROFILE_STAGE_2.md), [guarded tool authority](NADIA_GUARDED_TOOL_AUTHORITY_STAGE_7.md), [current Nadia status records](status/README.md) |
| Kernel lifecycle research | [kernel lifecycle seed](KERNEL_LIFECYCLE_SEED.md), [kernel lifecycle subsystem summary](KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md), [kernel state machine](KERNEL_STATE_MACHINE.md), [kernel scheduler seed](KERNEL_SCHEDULER_SEED.md) |
| Visual theorem engines | [visual theorem engines](VISUAL_THEOREM_ENGINES.md), [demos](demos/LATTICRA_SEAL_DEMO_v0_1.md) |

## Platform and Packaging

All platform lanes are local-only or no-effect unless a source record explicitly says otherwise. None of these entries claim distribution approval, archive readiness, official package status, root install authority, or production installability.

| Platform | Reader entry | Validation and workflow records |
| --- | --- | --- |
| Fedora | [packaging/fedora README](../packaging/fedora/README.md) | [Fedora developer workflow](FEDORA_DEVELOPER_WORKFLOW.md), [Fedora readiness plan](FEDORA_READINESS_PLAN.md), [local RPM static validation](FEDORA_LOCAL_RPM_STATIC_VALIDATION.md), [VM CLI payload validation lane](FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md) |
| Ubuntu | [packaging/ubuntu README](../packaging/ubuntu/README.md) | [Ubuntu developer workflow](UBUNTU_DEVELOPER_WORKFLOW.md), [Ubuntu readiness plan](UBUNTU_READINESS_PLAN.md), [local deb static validation](UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md), [lintian static metadata contract](UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md) |
| Debian | [packaging/debian README](../packaging/debian/README.md) | [Debian local deb static validation](DEBIAN_LOCAL_DEB_STATIC_VALIDATION.md), [source archive contract](DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md), [package build gate](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md), [build-evidence intake denial](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md) |
| openSUSE | [packaging/opensuse README](../packaging/opensuse/README.md) | [openSUSE developer workflow](OPENSUSE_DEVELOPER_WORKFLOW.md), [openSUSE readiness plan](OPENSUSE_READINESS_PLAN.md), [local RPM static validation](OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md), [validation blocker matrix](OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md) |
| FreeBSD | [packaging/freebsd README](../packaging/freebsd/README.md) | [FreeBSD port static validation](FREEBSD_PORT_STATIC_VALIDATION.md), [source archive fixture lane](DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md), [build-evidence intake denial](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md) |
| OpenBSD | [packaging/openbsd README](../packaging/openbsd/README.md) | [OpenBSD port static validation](OPENBSD_PORT_STATIC_VALIDATION.md), [source archive fixture lane](DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md), [build-evidence intake denial](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md) |
| macOS | [macOS integration transferability plan](MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md) | [app bundle writer dry run](MACOS_APP_BUNDLE_WRITER_DRY_RUN.md), [commit gate contract](MACOS_COMMIT_GATE_CONTRACT.md), [reset/uninstall dry-run contract](MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT.md), [verification transcript contract](MACOS_VERIFICATION_TRANSCRIPT_CONTRACT.md) |

openSUSE RPM maintenance records:

- [OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md](OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md)
- [OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md](OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md)
- [OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md](OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md)
- [OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md](OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md)
- [OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md](OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md)
- [OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md](OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md)
- [OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md](OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md)

Shared Debian, FreeBSD, and OpenBSD package/port records:

- [DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md)
- [DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md](DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md)

## Security and Assurance

| Area | Entry points |
| --- | --- |
| Reporting policy | [Security Policy](../SECURITY.md) |
| Security baseline | [High-Assurance Security Baseline](HIGH_ASSURANCE_SECURITY_BASELINE.md), [Defensive Threat Model](DEFENSIVE_THREAT_MODEL_CONTRACT.md), [Defensive Threat Model Validation](DEFENSIVE_THREAT_MODEL_VALIDATION.md) |
| Memory safety | [Memory Safety Roadmap](MEMORY_SAFETY_ROADMAP.md), [C/C++ security profile](security/C_CPP_SECURITY_PROFILE.md), [C ABI boundary policy](security/C_ABI_BOUNDARY_POLICY.md) |
| Supply chain | [Supply Chain Security Baseline](SUPPLY_CHAIN_SECURITY_BASELINE.md), [Vulnerability Management Release Gate](VULNERABILITY_MANAGEMENT_RELEASE_GATE_BASELINE.md) |
| Runtime authority | [Zero Trust Runtime Authority Baseline](ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md), [Runtime Boundary Contract](RUNTIME_BOUNDARY_CONTRACT.md) |
| Crypto and keys | [Cryptographic Assurance and Key Management Baseline](CRYPTOGRAPHIC_ASSURANCE_KEY_MANAGEMENT_BASELINE.md), [Seal key material contract](LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md), [Seal verification policy contract](LATTICRA_SEAL_VERIFICATION_POLICY_CONTRACT.md) |
| Incident response and resilience | [Cyber Incident Reporting Response Baseline](CYBER_INCIDENT_REPORTING_RESPONSE_BASELINE.md), [Security Logging Monitoring Baseline](SECURITY_LOGGING_MONITORING_BASELINE.md), [Backup Recovery Resilience Baseline](BACKUP_RECOVERY_RESILIENCE_BASELINE.md) |
| Identity and access | [Identity Credential Access Management Baseline](IDENTITY_CREDENTIAL_ACCESS_MANAGEMENT_BASELINE.md) |

## Documentation Operations

Use these before changing public wording, navigation, claim posture, mirrored estimates, platform posture, or subsystem landing pages.

| Document | Use it for |
| --- | --- |
| [Product Documentation Cohesion](PRODUCT_DOCUMENTATION_COHESION.md) | Product-facing copy, reader routes, public site resources, and subsystem landing pages |
| [Documentation Maintenance](DOCUMENTATION_MAINTENANCE.md) | Public entry points, status mirrors, static HTML summaries, and documentation-only validation |
| [Documentation Style Guide](DOCUMENTATION_STYLE_GUIDE.md) | Canonical terms, date style, headings, link style, and claim wording |
| [Documentation Health Scorecard](DOCUMENTATION_HEALTH_SCORECARD.md) | Findability, current status, claim safety, traceability, validation, reader-route, platform, security, estimate, and subsystem landing-page checks |
| [Documentation Traceability Matrix](DOCUMENTATION_TRACEABILITY_MATRIX.md) | Mapping public surfaces to source records, validation, mirrors, and non-claims |
| [Documentation Validation Playbook](DOCUMENTATION_VALIDATION_PLAYBOOK.md) | Hygiene, link, public-entry, estimate, platform, subsystem, and claim-promotion checks |
| [Documentation Drift Response Playbook](DOCUMENTATION_DRIFT_RESPONSE_PLAYBOOK.md) | Mirror drift, stale evidence, non-claim drift, and claim demotion |
| [Documentation Change Review Packet](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) | Explicit claim, mirror, validation, and rollback review |

## Status and Strategy

| Area | Entry points |
| --- | --- |
| Current status | [status/CURRENT_STATUS.md](status/CURRENT_STATUS.md), [status index](status/README.md), [announcements](status/ANNOUNCEMENTS.md) |
| Current project direction | [project notes](project_notes/README.md), [current direction](project_notes/CURRENT_DIRECTION.md), [upcoming work](project_notes/UPCOMING_WORK.md) |
| Strategy records | [strategy index](strategy/README.md), [overall strategy priority map](strategy/2026-05-26-1702-cdt-overall-strategy-priority-map.md) |
| Public site status pages | [status.html](status.html), [validation.html](validation.html), [evidence.html](evidence.html), [architecture.html](architecture.html), [security.html](security.html), [packaging.html](packaging.html), [panel.html](panel.html), [kernel.html](kernel.html) |

## Maintenance Rules

- Keep the root [README](../README.md) short, navigable, and user-facing.
- Keep this hub as the route map for deeper docs.
- Keep [Foundation Index](FOUNDATION_INDEX.md) evidence-heavy and exhaustive.
- Keep [Status](../STATUS.md), [Current Status](status/CURRENT_STATUS.md), and status mirrors aligned when public posture changes.
- Use [Documentation Health Scorecard](DOCUMENTATION_HEALTH_SCORECARD.md) before broad public, route, platform, security, estimate, or subsystem landing-page changes.
- Keep non-claims near any security, packaging, installer, runtime, or OS-adjacent wording.
- Do not promote production runtime, host protection, package approval, certification, or OS replacement claims without implementation evidence, tests, status records, and public-entry alignment.

## Current Non-Claim Reminder

Latticra is early-stage and evidence-bound. It is not a production security product, hardened sandbox, operating-system replacement, root installer, network authority, production runtime, Fedora-approved package, Ubuntu archive-ready package, Debian archive-ready package, FreeBSD official port, OpenBSD official port, or openSUSE official package.

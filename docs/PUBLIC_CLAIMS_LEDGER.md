# Latticra Public Claims Ledger

Status: active documentation guard
Last updated: 2026-05-26
Scope: README surfaces, public site pages, status records, subsystem summaries, installer/package documentation, release notes, and external-facing project descriptions.

## Purpose

This ledger keeps public Latticra wording aligned with current evidence.

It does not promote any capability by itself. It translates the current status records, evidence ladder, non-claims, contracts, and implementation notes into safe wording that can be reused without implying production readiness, security guarantees, operating-system completeness, or distribution approval.

When two records disagree, use the narrowest current claim until a later contract, implementation record, validation record, status update, and public-entry alignment all support a stronger statement.

## Source of Truth Order

Use this order when public wording needs a decision:

1. [`STATUS.md`](../STATUS.md) and [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md)
2. [`NON_CLAIMS.md`](NON_CLAIMS.md)
3. [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md)
4. [`REAL_SYSTEM_CONTRACT.md`](REAL_SYSTEM_CONTRACT.md)
5. Specific subsystem contracts, implementation records, status records, and guard scripts
6. This ledger as the wording guide for public summaries

## Allowed Public Wording

| Area | Allowed wording | Required boundary |
| --- | --- | --- |
| Project identity | Latticra is an early-stage, evidence-bound systems architecture repository. | Do not call it a deployed product, production platform, daily-driver system, or operating-system replacement. |
| Documentation posture | Latticra uses contract-first documentation, status records, non-claims, and validation guards to keep claims evidence-bound. | Do not imply that documentation maturity equals implementation maturity. |
| Evidence model | Latticra has an evidence ladder for promoting concepts, fixtures, tested models, reports, guarded experiments, and later real-system capabilities. | Do not skip evidence levels or treat a lower-level record as a real-system claim. |
| Runtime Boundary | Latticra has denied-by-default runtime-boundary classification and report surfaces. | Do not claim runtime authority, live enforcement, process isolation, or effect-performing runtime behavior. |
| Nucleus | Nucleus task records and reports are report-only and denied by default. | Do not claim effect-performing task execution. |
| Latticra Seal | Latticra Seal has report-only dry-run, metadata, policy-denial, request-boundary, and negative-test evidence for AI-era tool-boundary planning. | Do not claim active AI-agent control, host protection, network blocking, hardened sandboxing, or production enforcement. |
| Lat, LIR, and L-UI | Lat, LIR, and L-UI have no-effect parse, validate, lower, metadata, and report paths. | Do not claim production language execution, LIR execution, or an interactive terminal-control renderer. |
| Panel and installer | Latticra Panel is a guarded local workbench and installer/control surface in active development. | Do not claim a daily-driver installer, root installer, distribution installer, or broad host-management product. |
| Fedora, Ubuntu, and openSUSE | The repo has local-only packaging drafts, workflow records, and validation lanes. | Do not claim Fedora approval, Ubuntu archive readiness, PPA availability, Open Build Service publication, or distribution support. |
| macOS lane | The macOS lane currently centers on no-effect probes, dry-run planning, app-bundle contracts, reset/uninstall contracts, and evidence gates. | Do not claim a signed, notarized, written, installed, or verified macOS app bundle unless later evidence says so. |
| Nadia offline AI | Nadia has staged offline AI foundation and prompt-evaluation planning contracts. | Do not claim model loading, inference, token generation, dialogue generation, prompt evaluation, or tool execution. |
| Security posture | Latticra documents defensive boundaries, safe-testing rules, and security non-claims. | Do not claim malware prevention, ransomware prevention, secure boot, verified boot, sandbox escape resistance, or certified security. |

## Blocked Public Wording

| Blocked wording | Safer replacement |
| --- | --- |
| production-ready | early-stage, evidence-bound, or planning-stage |
| secure platform | documented defensive boundary with explicit security non-claims |
| hardened sandbox | report-only or no-effect boundary, depending on the record |
| AI-agent security system | AI-era tool-boundary planning with report-only evidence |
| runtime enforcement | denied-by-default classification and reporting |
| cryptographic enforcement layer | metadata, signing, key, or verification planning record, unless a specific verified implementation record says otherwise |
| operating system | systems architecture repository or operating-system-universe direction |
| OS replacement | no-effect architecture and validation research |
| daily-driver installer | guarded local workbench or local-only installer lane |
| official Fedora package | local Fedora RPM draft or validation lane |
| Ubuntu archive-ready package | local Ubuntu deb draft or validation lane |
| openSUSE package | local openSUSE RPM draft, spec lane, or validation lane |
| malware prevention | defensive threat-model planning and non-claims |
| ransomware prevention | defensive threat-model planning and non-claims |
| active model runtime | offline AI foundation or prompt-evaluation contract lane |
| tool execution authority | report-only guarded tool-authority preflight |
| root authority | no root authority claimed |
| host protection | host-facing boundary planning with non-claims |

## Promotion Requirements

Any stronger public claim needs all of the following before the wording is promoted:

| Requirement | Minimum proof |
| --- | --- |
| Contract | A specific contract names the capability, effect boundary, failure behavior, operator boundary, and non-claims. |
| Implementation | A bounded implementation record names the exact files, behaviors, disabled paths, and report output. |
| Validation | Tests, guard scripts, transcripts, or reproducible reports prove the narrow behavior and denied behavior. |
| Status | Root and detailed status records describe the new posture without overstating it. |
| Public-entry alignment | README, public HTML pages, indexes, and subsystem summaries use the same wording. |
| Non-claim update | Unsupported adjacent claims remain explicit. |
| Rollback or demotion path | If evidence becomes stale, contradicted, or unsafe, the claim can be narrowed quickly. |

## Review Checklist

Before adding or changing public wording, confirm:

1. The wording names the exact evidence level or status surface.
2. The wording does not imply production, security, OS, installer, package, AI-runtime, network, host, root, or cryptographic authority beyond the evidence.
3. The linked source record exists and says the same thing.
4. Adjacent non-claims remain visible.
5. Denied effects are stated when the topic involves runtime, installer, package, AI, host, network, signing, or security behavior.
6. The public entry point and the detailed status record do not drift.
7. Source, mirror, validation, and non-claim traceability follows [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md).
8. Validation selection follows [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).
9. Terminology follows [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md).
10. Broad public wording changes have a [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) outcome.

## Primary References

- [`README.md`](../README.md)
- [`STATUS.md`](../STATUS.md)
- [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md)
- [`NON_CLAIMS.md`](NON_CLAIMS.md)
- [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md)
- [`REAL_SYSTEM_CONTRACT.md`](REAL_SYSTEM_CONTRACT.md)
- [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md)
- [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md)
- [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md)
- [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md)
- [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md)
- [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md)
- [`PRODUCTION_INSTALLER_READINESS_CONTRACT.md`](PRODUCTION_INSTALLER_READINESS_CONTRACT.md)
- [`ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md`](ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md)
- [`latticra-seal/README.md`](latticra-seal/README.md)
- [`LATTICRA_SEAL_CORE_EVIDENCE_REPORT.md`](LATTICRA_SEAL_CORE_EVIDENCE_REPORT.md)
- [`../installer/README.md`](../installer/README.md)
- [`../packaging/fedora/README.md`](../packaging/fedora/README.md)
- [`../packaging/ubuntu/README.md`](../packaging/ubuntu/README.md)
- [`../packaging/opensuse/README.md`](../packaging/opensuse/README.md)

# Documentation Traceability Matrix

Status: active documentation traceability matrix
Last updated: 2026-05-26 CDT
Scope: public entry points, source records, mirrors, validation guards, non-claims, product surfaces, installer docs, package docs, security docs, and subsystem maps.

## Purpose

This matrix maps reader-facing documentation surfaces back to their source records and validation checks.

Use it to answer:

1. where a public statement should be sourced;
2. which mirrors may need updates;
3. which validation commands are relevant;
4. which non-claims must remain visible;
5. where to look when a public page and a source record disagree.

This document does not promote claims. It makes documentation traceability visible.

## Traceability Rule

Every public-facing claim should have a path to:

```text
public surface -> source record -> validation or review record -> non-claim boundary
```

If that path is missing, keep the claim narrow or remove it until a source record exists.

## Matrix

| Topic | Public surfaces | Source records | Validation or review | Non-claim boundary |
| --- | --- | --- | --- | --- |
| Project identity | [`../README.md`](../README.md), [`index.html`](index.html), [`map.html`](map.html) | [`REAL_SYSTEM_CONTRACT.md`](REAL_SYSTEM_CONTRACT.md), [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md), [`README.md`](README.md) | [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md), `git diff --check` | [`NON_CLAIMS.md`](NON_CLAIMS.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) |
| Current status and estimates | [`../README.md`](../README.md), [`../STATUS.md`](../STATUS.md), [`status.html`](status.html), [`roadmap.html`](roadmap.html) | [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md), [`status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md`](status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md) | `sh scripts/test-current-estimate-table-source-alignment.sh` | Estimates are planning posture, not release promises. |
| Documentation navigation | [`README.md`](README.md), [`map.html`](map.html), [`index.html`](index.html) | [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md), [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md) | Local link check, `git diff --check` | Navigation must not imply capability promotion. |
| Product-facing wording | [`../README.md`](../README.md), [`index.html`](index.html), [`start.html`](start.html), [`validation.html`](validation.html) | [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md) | [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) | Product copy must stay evidence-bound and non-production. |
| Public claim language | All public Markdown and HTML summaries | [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md), [`NON_CLAIMS.md`](NON_CLAIMS.md) | Claim review packet outcome when wording changes | Unsupported adjacent claims stay blocked. |
| Security posture | [`../SECURITY.md`](../SECURITY.md), [`security.html`](security.html), [`../README.md`](../README.md) | [`DEFENSIVE_THREAT_MODEL_CONTRACT.md`](DEFENSIVE_THREAT_MODEL_CONTRACT.md), [`HIGH_ASSURANCE_SECURITY_BASELINE.md`](HIGH_ASSURANCE_SECURITY_BASELINE.md), [`ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md`](ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md) | Security-specific guard named by the changed source record | No malware prevention, ransomware prevention, hardened sandbox, certification, or production protection claim. |
| Installer and Panel posture | [`../installer/README.md`](../installer/README.md), [`../installer/docs/README.md`](../installer/docs/README.md), [`start.html`](start.html), [`validation.html`](validation.html) | [`PRODUCTION_INSTALLER_READINESS_CONTRACT.md`](PRODUCTION_INSTALLER_READINESS_CONTRACT.md), installer docs and status records | Installer or Panel guard named by the changed record | No root installer, daily-driver installer, production installer, or unattended host mutation claim. |
| Fedora lane | [`FEDORA_READINESS_PLAN.md`](FEDORA_READINESS_PLAN.md), [`FEDORA_DEVELOPER_WORKFLOW.md`](FEDORA_DEVELOPER_WORKFLOW.md), [`../packaging/fedora/README.md`](../packaging/fedora/README.md), [`validation.html`](validation.html) | Fedora package, workflow, and status records | `sh scripts/test-fedora-developer-workflow.sh` plus exact Fedora guard | Local-only unless Fedora approval evidence exists. |
| Ubuntu lane | [`UBUNTU_READINESS_PLAN.md`](UBUNTU_READINESS_PLAN.md), [`UBUNTU_DEVELOPER_WORKFLOW.md`](UBUNTU_DEVELOPER_WORKFLOW.md), [`../packaging/ubuntu/README.md`](../packaging/ubuntu/README.md), [`validation.html`](validation.html) | Ubuntu package, workflow, notice, license, and status records | `sh scripts/test-ubuntu-developer-workflow.sh` plus exact Ubuntu guard | Local-only unless Ubuntu archive or PPA evidence exists. |
| Debian, FreeBSD, and OpenBSD lanes | [`../packaging/debian/README.md`](../packaging/debian/README.md), [`../packaging/freebsd/README.md`](../packaging/freebsd/README.md), [`../packaging/openbsd/README.md`](../packaging/openbsd/README.md), [`validation.html`](validation.html) | Platform package draft and package-input/build-gate records | Exact platform guard named by the changed record | Local-only unless archive, ports-tree, or official publication evidence exists. |
| openSUSE lane | [`OPENSUSE_READINESS_PLAN.md`](OPENSUSE_READINESS_PLAN.md), [`OPENSUSE_DEVELOPER_WORKFLOW.md`](OPENSUSE_DEVELOPER_WORKFLOW.md), [`../packaging/opensuse/README.md`](../packaging/opensuse/README.md), [`validation.html`](validation.html) | openSUSE package, workflow, rpmlint, osc, and status records | `sh scripts/test-opensuse-developer-workflow.sh` plus exact openSUSE guard | Local-only unless Open Build Service or official package evidence exists. |
| Runtime Boundary and Nucleus | [`runtime.html`](runtime.html), [`../README.md`](../README.md), subsystem records | [`RUNTIME_BOUNDARY_CONTRACT.md`](RUNTIME_BOUNDARY_CONTRACT.md), [`RUNTIME_BOUNDARY_IMPLEMENTATION.md`](RUNTIME_BOUNDARY_IMPLEMENTATION.md), [`NUCLEUS_TASK_EXECUTION_CONTRACT.md`](NUCLEUS_TASK_EXECUTION_CONTRACT.md), [`NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md`](NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md) | Runtime or Nucleus guard named by the changed source record | No runtime authority, effect-performing execution, process isolation, or sandbox claim. |
| Latticra Seal | [`seal.html`](seal.html), [`latticra-seal/README.md`](latticra-seal/README.md), [`latticra-seal/STATUS.md`](latticra-seal/STATUS.md), [`../README.md`](../README.md) | [`LATTICRA_SEAL_CONTRACT.md`](LATTICRA_SEAL_CONTRACT.md), [`LATTICRA_SEAL_CORE_EVIDENCE_REPORT.md`](LATTICRA_SEAL_CORE_EVIDENCE_REPORT.md), Seal status records | `sh scripts/test-latticra-seal-docs.sh` plus exact Seal guard | No production enforcement, AI-agent control, host protection, network blocking, or cryptographic authority claim. |
| Lat, LIR, and L-UI | [`language.html`](language.html), [`examples.html`](examples.html), [`../README.md`](../README.md) | [`LANGUAGE_STRATEGY.md`](LANGUAGE_STRATEGY.md), [`LAT_PIPELINE_CONTRACT.md`](LAT_PIPELINE_CONTRACT.md), [`LIR_SHAPE_CONTRACT.md`](LIR_SHAPE_CONTRACT.md), [`L_UI_PARSER.md`](L_UI_PARSER.md) | Language or parser guard named by the changed source record | No production language runtime, LIR execution, or terminal-control renderer claim. |
| Nadia offline AI | [`nadia.html`](nadia.html), [`../README.md`](../README.md), Nadia status records | [`NADIA_OFFLINE_AI_FOUNDATION.md`](NADIA_OFFLINE_AI_FOUNDATION.md) and staged Nadia contracts | Exact Nadia guard named by the changed source record | No model loading, inference, token generation, dialogue generation, prompt evaluation, or tool execution claim. |
| Boot and OS-base preview | [`boot.html`](boot.html), [`../README.md`](../README.md), installer records | SeaBIOS/GRUB boot-preview contracts, templates, preflight, and validation records | Exact SeaBIOS/GRUB guard named by the changed source record | No bootable OS image, OS replacement, GRUB installer, firmware mutation, or hardware boot success claim. |
| Handbook and long-form docs | [`latticra-system-substrate/README.md`](latticra-system-substrate/README.md), generated handbook artifacts | [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md), project notes, status records, subsystem contracts | Documentation change review packet and local link check | Handbook summaries must not outrun current status. |

## Drift Indicators

Treat these as documentation drift:

- a public page names a capability without a source record;
- a status record and public page use different posture words;
- a platform README omits local-only or no-effect boundaries;
- a security page uses "secure", "safe", "hardened", "protection", or "prevention" without a supporting source record;
- an estimate appears in public HTML but not in the current estimate source records;
- a subsystem landing page implies product readiness from subsystem progress alone;
- a quick-start path omits reset, cleanup, or non-claim context for a runnable local path.

## Review Flow

When drift is found:

1. Identify the topic row in this matrix.
2. Read the source records before editing public wording.
3. Check [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) and [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md).
4. Use [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md) to choose the narrowest relevant validation commands.
5. Use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) when wording, mirrors, estimates, status, platform posture, or non-claims change.
6. Run the selected validation commands.
7. Update only the public surfaces whose reader-facing claim actually changed.

## Boundary

This matrix is documentation traceability only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.

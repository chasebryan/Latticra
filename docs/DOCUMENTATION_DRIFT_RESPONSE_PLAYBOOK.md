# Documentation Drift Response Playbook

Status: active documentation drift-response playbook
Last updated: 2026-05-26 CDT
Scope: public wording drift, status mirror drift, estimate drift, non-claim drift, link drift, platform posture drift, security wording drift, stale evidence, and claim demotion.

## Purpose

This playbook defines what to do when Latticra documentation disagrees with itself.

Use it when a public page, source record, status mirror, estimate table, package README, installer guide, security page, or subsystem landing page appears to overstate, understate, or contradict the current evidence.

This playbook does not promote claims. It narrows or aligns documentation until the evidence supports stronger wording.

## Drift Types

| Drift type | Signal | First response |
| --- | --- | --- |
| Link drift | A local link is broken or points to the wrong record. | Fix the link or remove it if no source exists. |
| Source-record drift | A public statement has no source record. | Narrow or remove the statement until a source record exists. |
| Status mirror drift | `README.md`, `STATUS.md`, `docs/status/CURRENT_STATUS.md`, or public HTML pages disagree. | Use the narrowest current status wording and align mirrors. |
| Estimate drift | Estimate values differ across public tables or static pages. | Treat the current estimate source record as authoritative and run the estimate alignment guard. |
| Non-claim drift | A public page drops a required non-claim or weakens blocked language. | Restore the non-claim near the claim it constrains. |
| Product-copy drift | Product-facing wording implies production, approval, security, or runtime authority. | Replace it with wording from the claims ledger and style guide. |
| Platform drift | Package or platform docs imply official approval, archive readiness, or production installability. | Restore local-only or no-effect posture. |
| Security drift | Security docs imply protection, prevention, sandboxing, certification, or hardening without evidence. | Restore security non-claims and source-tracked wording. |
| Validation drift | A guard fails because the docs and expected public posture disagree. | Fix the docs or mirrors; do not edit the guard for convenience. |
| Stale evidence | A record relies on older evidence contradicted by newer status. | Demote the public wording to the latest supported status. |

## Response Order

When drift appears:

1. Read the public surface that contains the questionable wording.
2. Find the source record through [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md).
3. Check allowed and blocked wording in [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md).
4. Check terminology in [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md).
5. Select validation commands with [`DOCUMENTATION_VALIDATION_PLAYBOOK.md`](DOCUMENTATION_VALIDATION_PLAYBOOK.md).
6. Use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) if public wording, mirrors, estimates, platform posture, security wording, or non-claims change.
7. Update only the surfaces whose reader-facing claim changed.
8. Run the selected validation checks.

## Demotion Rule

Demotion is required when a public statement is stronger than the evidence.

Use this pattern:

```text
strong claim -> current evidence-bound claim -> explicit blocked adjacent claim
```

Examples:

| Strong claim | Demoted wording | Blocked adjacent claim |
| --- | --- | --- |
| Latticra is secure. | Latticra documents defensive boundaries and security non-claims. | No production security guarantee. |
| The installer is ready. | The Panel path is guarded and user-local for the documented workflow. | No root installer or daily-driver installer claim. |
| Fedora support is ready. | The Fedora lane has local-only package and validation records. | No Fedora approval or distribution-readiness claim. |
| Seal protects AI agents. | Latticra Seal records report-only AI-era tool-boundary evidence. | No active AI-agent control or host protection claim. |
| Runtime enforcement exists. | Runtime Boundary classification and reports are denied by default. | No runtime authority or effect-performing execution claim. |

## Alignment Actions

| Situation | Action | Validation |
| --- | --- | --- |
| Public page is broader than status. | Narrow the public page to the status record. | Public-entry guard and link check. |
| Status record is broader than implementation evidence. | Narrow the status record and public mirrors. | Exact source guard plus public-entry guard. |
| Estimate mirror differs. | Update mirror from the estimate source record. | Estimate source-alignment guard. |
| Platform docs omit local-only status. | Add local-only and no-approval wording. | Platform workflow guard plus exact platform guard. |
| Security docs overpromise. | Restore non-claims and source-tracked wording. | Exact security or threat-model guard. |
| Source record is missing. | Remove or block the claim until the source record exists. | Link check and review packet outcome. |
| Validation command is missing. | Mark the claim blocked for missing validation. | Review packet outcome `blocked_missing_validation`. |

## Do Not

Do not:

- broaden a public claim to make a product page sound better;
- edit a guard script only to make documentation pass;
- hide non-claims in deep source files when a public page implies the adjacent claim;
- treat subsystem progress as overall product readiness;
- treat local static validation as platform approval;
- treat report-only evidence as runtime enforcement;
- treat planning estimates as release promises;
- claim security, safety, hardening, prevention, approval, or certification without explicit source evidence.

## Review Packet Outcomes

Use these outcomes from [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md) when drift is found:

```text
blocked_claim_promotion
blocked_missing_source_record
blocked_missing_validation
blocked_non_claim_drift
blocked_public_entry_drift
accepted_wording_only
accepted_status_mirror
accepted_local_only_platform_posture
```

## Boundary

This playbook changes documentation posture only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.

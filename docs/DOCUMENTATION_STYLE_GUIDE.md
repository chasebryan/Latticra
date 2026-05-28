# Documentation Style Guide

Status: active documentation style guide
Last updated: 2026-05-27 CDT
Scope: public Markdown, public HTML copy, status records, installer docs, package docs, subsystem landing pages, strategy records, and review packets.

## Purpose

This guide keeps Latticra documentation consistent at the wording level.

Use it with [`DOCUMENTATION_GLOSSARY.md`](DOCUMENTATION_GLOSSARY.md), [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md), [`DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md`](DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md), [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), [`DOCUMENTATION_MAINTENANCE.md`](DOCUMENTATION_MAINTENANCE.md), and [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md).

This guide does not decide whether a claim is true. It decides how true claims should be written once the source records support them.

Use [`DOCUMENTATION_GLOSSARY.md`](DOCUMENTATION_GLOSSARY.md) for definitions of shared posture, validation, platform, and reader terms.

## Core Voice

Latticra documentation should be:

```text
specific
evidence-bound
plainspoken
operator-visible
careful about claims
clear about blocked effects
```

Prefer short, concrete sentences over broad promise language.

## Canonical Project Description

Use this shape when a short project description is needed:

```text
Latticra is an early-stage, evidence-bound systems architecture repository for contract-first authority, no-effect reporting, guarded local validation, and AI-era tool-boundary planning.
```

Do not shorten this into "security product", "AI security platform", "operating system", "installer", or "runtime enforcement system".

## Canonical Terms

| Use | Avoid |
| --- | --- |
| Latticra | Lattice OS, Latticra OS, Latticra Linux |
| Latticra Panel | the installer, the app, the product |
| Latticra Seal | Seal security platform, Seal enforcement layer |
| Lat | L, .l, LatticraScript |
| LIR | execution IR, runtime IR |
| L-UI | terminal UI runtime, shell UI |
| Runtime Boundary | runtime enforcement, sandbox runtime |
| Nucleus | task executor, agent runner |
| no-effect | harmless, safe, guaranteed safe |
| report-only | enforcement, protection |
| guarded user-local | production install, root install |
| local-only package draft | official package, distribution package |
| public status | release status, readiness guarantee |

## Platform Names

Use the official spelling in public docs:

```text
Fedora
Ubuntu
Debian
FreeBSD
OpenBSD
openSUSE
macOS
GitHub Pages
Open Build Service
```

Use "local-only" for package lanes unless official publication evidence exists.

## Status And Date Style

Markdown records should use this header shape when practical:

```text
Status: active documentation guide
Last updated: 2026-05-26 CDT
Scope: public documentation entry points and related records.
```

Use concrete dates for review snapshots and status records. Use `CDT` for current local documentation timestamps when the record is tied to the project working context.

Use [`DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md`](DOCUMENTATION_FRESHNESS_LIFECYCLE_POLICY.md) before changing status labels, `Last updated` dates, stale wording, superseded wording, archive wording, or lifecycle boundaries.

Use [`DOCUMENTATION_STATUS_RECORD_STANDARD.md`](DOCUMENTATION_STATUS_RECORD_STANDARD.md) before changing status-record fields, status-index entries, public status mirrors, estimate records, or public-entry alignment status notes.

Do not use vague status labels such as:

```text
soon
almost ready
basically done
ship-ready
production-ish
```

## Claim Wording

Prefer:

```text
current posture
current evidence
validated by local guard
report-only metadata
denied-by-default classification
local-only draft
guarded user-local workflow
blocked until later evidence exists
```

Avoid:

```text
secure
safe
complete
production-ready
approved
certified
official
hardened
unbreakable
fully supported
```

If a sentence contains a strong word such as "secure", "safe", "ready", "approved", "official", or "enforced", check [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) before keeping it.

## Headings

Use predictable headings for source records:

```text
Purpose
Scope
Current Posture
Evidence
Validation
Non-Claims
Boundary
Next Valid Work
```

Do not create dramatic or marketing-style headings for technical source records.

## Link Style

Use relative Markdown links for repository files.

Prefer linking to source records instead of repeating long claims. A public summary should point to:

1. status record;
2. contract or implementation record;
3. validation guard or transcript;
4. non-claims;
5. review packet when public wording changed.

## Tables And Lists

Use tables for comparison surfaces:

- source of truth and mirrors;
- allowed and blocked wording;
- product surface responsibilities;
- platform posture;
- validation commands.

Use numbered lists for ordered review or validation steps.

Use bullets for unordered examples.

## Code Blocks

Use fenced code blocks for commands, status key/value output, guard output, packet templates, and exact labels.

Use `text` fences for non-command labels and `sh` fences for shell commands.

Use [`DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md`](DOCUMENTATION_COMMAND_EXAMPLE_STANDARD.md) before adding or changing runnable commands, especially commands that write files, use `sudo`, fetch from the network, validate platform posture, or install, update, reset, or uninstall user-local state.

## Non-Claim Placement

Put non-claims near the claim they constrain.

For public product pages, do not hide non-claims only in a deep source file. The page should either state the relevant boundary directly or link to [`NON_CLAIMS.md`](NON_CLAIMS.md) and [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md).

## Replacement Examples

| Replace | With |
| --- | --- |
| Latticra is secure. | Latticra documents defensive boundaries and security non-claims. |
| Seal protects AI agents. | Latticra Seal records report-only AI-era tool-boundary evidence. |
| The installer is ready. | The Panel workflow is guarded and user-local for the documented path. |
| Fedora support is ready. | The Fedora lane has local-only package and validation records. |
| Runtime enforcement exists. | Runtime Boundary classification and reports are denied by default. |
| Nadia runs offline AI. | Nadia has staged offline AI foundation and prompt-evaluation planning contracts. |

## Boundary

Style changes should not change source behavior, installer authority, package authority, runtime authority, workflow permissions, status estimates, security posture, or product readiness.

When a style change would make a claim stronger, stop and use [`DOCUMENTATION_CHANGE_REVIEW_PACKET.md`](DOCUMENTATION_CHANGE_REVIEW_PACKET.md).

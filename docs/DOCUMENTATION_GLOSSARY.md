# Documentation Glossary

Status: active documentation glossary
Last updated: 2026-05-26 CDT
Scope: public documentation terms, claim posture, evidence wording, validation wording, package posture, installer posture, runtime posture, and reader-route terminology.

## Purpose

This glossary defines common documentation terms used across Latticra public and source records.

Use it with [`DOCUMENTATION_STYLE_GUIDE.md`](DOCUMENTATION_STYLE_GUIDE.md), [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md), [`PRODUCT_DOCUMENTATION_COHESION.md`](PRODUCT_DOCUMENTATION_COHESION.md), and [`DOCUMENTATION_TRACEABILITY_MATRIX.md`](DOCUMENTATION_TRACEABILITY_MATRIX.md).

This glossary is not a source of capability. It defines wording only.

## Core Terms

| Term | Meaning | Do not imply |
| --- | --- | --- |
| evidence-bound | A claim is limited by source records, tests, validation, status, and non-claims. | Production readiness or safety guarantees. |
| contract-first | A boundary, behavior, failure mode, and non-claim are documented before implementation expands. | That the implementation already exists. |
| source record | The contract, implementation note, status record, transcript, or guard-backed document that supports a public statement. | That a public summary is authoritative by itself. |
| public surface | A reader-facing file or page such as README, public HTML, docs hub, package README, installer README, or subsystem landing page. | That public wording can outrun source records. |
| mirror | A second location repeating source posture for reader convenience. | That duplicate wording can become a new source of truth. |
| public-entry alignment | Updating public entry points so they match current source records and status. | Capability promotion. |
| traceability | A visible path from public wording to source record, validation, mirror, and non-claim boundary. | Proof of runtime behavior by itself. |
| validation | A check, test, guard, transcript, or review that supports a narrow claim. | General correctness, safety, or release readiness. |
| guard script | A deterministic local script that checks a narrow documentation, status, package, source, or behavior expectation. | Broad security or product certification. |
| review packet | A structured review record for documentation wording, mirrors, validation, non-claims, and rollback or demotion path. | Implementation evidence. |

## Capability Posture

| Term | Meaning | Do not imply |
| --- | --- | --- |
| no-effect | The path is intended to report, classify, validate, or model without performing host, network, runtime, package, installer, or security effects. | Harmlessness, safety guarantee, or production approval. |
| report-only | The path produces metadata or reports without enforcing policy, granting authority, or performing effects. | Enforcement, protection, containment, or runtime authority. |
| denied by default | The current classification blocks behavior unless later evidence and gates explicitly allow a narrow path. | A production sandbox or full policy engine. |
| guarded | A path has explicit checks, prerequisites, or review gates before a narrow operation can proceed. | Broad permission or unattended operation. |
| guarded user-local | A user-scoped path with documented boundaries and no broad root/system authority claim. | Root install, daily-driver install, production install, or host-management product. |
| local-only | A package, validation, or workflow lane is limited to local records and checks. | Official distribution, archive, store, or vendor approval. |
| static validation | A check of files, metadata, shape, wording, or configuration without proving full build/install/runtime behavior. | Publication readiness or install safety. |
| disposable validation | Validation intended for a throwaway VM or controlled environment. | Daily-driver safety or broad host compatibility. |
| runtime authority | Permission or capability to execute effects at runtime. | Present capability unless a source record explicitly proves it. |
| host behavior | Reading, writing, mutating, installing, deleting, managing, or otherwise affecting the host. | Allowed behavior unless explicitly proven and gated. |
| network behavior | Network access, server interaction, update fetching, remote trust lookup, or internet-facing behavior. | Present capability unless explicitly proven and bounded. |

## Product And Status Terms

| Term | Meaning | Do not imply |
| --- | --- | --- |
| public status | Reader-facing current posture, estimates, and next blockers. | Release status, readiness guarantee, or support commitment. |
| planning estimate | A rough posture marker for project planning. | Release promise, completion guarantee, or product-readiness metric. |
| product readiness | A future state requiring implementation, validation, support boundaries, non-claims, and public-entry alignment. | Current Latticra status. |
| current posture | The narrowest currently supported description of a topic. | Future ambition or roadmap completion. |
| next valid work | The next work that can proceed without overclaiming or skipping evidence. | A commitment to ship or release. |
| blocked adjacent claim | A tempting broader claim that must remain explicitly unsupported. | Hidden future capability. |
| demotion | Narrowing public wording when evidence is stale, contradicted, missing, or too weak. | Failure of the project; it is claim hygiene. |
| drift | A disagreement between public pages, source records, status mirrors, estimates, validation, or non-claims. | An implementation change by itself. |

## Platform Terms

| Term | Meaning | Do not imply |
| --- | --- | --- |
| Fedora lane | Fedora-specific local package, workflow, transcript, or validation work. | Fedora approval or distribution readiness. |
| Ubuntu lane | Ubuntu-specific local deb, workflow, package, notice, or validation work. | Ubuntu archive readiness, PPA readiness, or Canonical endorsement. |
| Debian lane | Debian-specific local package or archive-preparation work. | Debian archive upload, sponsorship, or official package status. |
| FreeBSD lane | FreeBSD-specific local port-shape or validation work. | FreeBSD ports-tree readiness or official port status. |
| OpenBSD lane | OpenBSD-specific local port-shape or validation work. | OpenBSD ports-tree readiness or official package status. |
| openSUSE lane | openSUSE-specific local RPM, rpmlint, osc, spec, or validation work. | Open Build Service publication, official package status, or SUSE endorsement. |
| macOS lane | macOS-specific no-effect or user-local planning, probing, dry-run, app-bundle, reset/uninstall, or verification work. | Signed app, notarized app, production installer, privileged helper, or broad host authority. |

## Reader Terms

| Term | Meaning | Do not imply |
| --- | --- | --- |
| new local user | A reader trying the guarded local path or understanding basic commands. | Production operator. |
| operator | A reader evaluating runnable paths, local checks, denied effects, and evidence requirements. | Someone granted hidden authority. |
| reviewer | A reader checking public claims against source evidence and non-claims. | Product approver. |
| contributor | A reader changing docs or source records under existing guardrails. | Someone authorized to broaden public claims without evidence. |
| packager | A reader reviewing platform package shape, static validation, and local-only boundaries. | Distribution maintainer approval. |
| security reviewer | A reader checking defensive posture, threat-model records, safe-testing rules, and security non-claims. | Certification authority. |

## Replacement Rule

When a term could be read as a stronger claim, replace it with the narrowest glossary term.

Examples:

| Replace | With |
| --- | --- |
| safe | no-effect, guarded, or validated by local guard |
| ready | current posture or local-only draft |
| secure | documented defensive boundary with security non-claims |
| official | local-only unless official evidence exists |
| enforcement | report-only or denied-by-default classification |
| installer | guarded user-local Panel path unless production installer evidence exists |

## Boundary

This glossary standardizes documentation wording only.

It does not change implementation behavior, installer authority, package authority, runtime authority, workflow permissions, security posture, public estimates, or product readiness.

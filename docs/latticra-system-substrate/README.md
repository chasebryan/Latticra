# The Latticra System Substrate

**Title:** *The Latticra System Substrate: An Effect at Modern Security*<br>
**Edition:** Working Draft 0.13 — 2026-05-26<br>
**Role:** Project-level technical handbook for Latticra, Latticra Seal trust-boundary metadata, authority-neutral Ed25519 verification evidence, metadata-only capability/effect/handoff/report/envelope/signature-request/signing-operation classification and status guards, Latticra Console host/receipt/signature/OS/VM contract surfaces, Runtime Boundary Lat/LIR provenance records, Nucleus, Nadia offline AI contracts, Panel, platform install validation lanes, Lat/LIR contract surfaces, receipts, reports, and future runtime-boundary research.

This handbook supersedes the former standalone **Latticra Seal Documentation Handbook** as the main reader-facing book for the project.

The Seal handbook was useful as a subsystem reference. This new handbook expands the scope into a computer-science-oriented project book: Latticra as an evidence-bound system substrate for local integrity, authority boundaries, reproducible reports, receipts, policy semantics, and future runtime-handoff research.

## Downloads

- [PDF edition](the-latticra-system-substrate.pdf)
- [Editable DOCX edition](the-latticra-system-substrate.docx)
- [Public repository folder](https://github.com/Bryforge/Latticra/tree/main/docs/latticra-system-substrate)

## Living handbook cadence

Treat this handbook as a live project artifact, not a finished release.

As Latticra work progresses, material decisions, capability changes, boundary refinements, validation lanes, public wording, and evidence updates should be folded back into the handbook alongside the nearer-term project notes and status records.

Handbook updates should stay evidence-bound: describe what is implemented, tested, measured, planned, or explicitly out of scope, and avoid promoting future runtime, enforcement, host-protection, packaging, or production claims ahead of reproducible evidence.

## Correct interpretation

Latticra should be understood as early, evidence-bound systems architecture work.

It is not currently:

- a production security product
- a host-protection system
- a hardened sandbox
- a malware prevention system
- a ransomware prevention system
- a kernel enforcement layer
- a systemd enforcement layer
- an SELinux authority
- a root installer
- a network authority
- a production runtime authority
- an operating-system replacement

The handbook's core claim is narrower and more useful: Latticra is a substrate for making security-relevant effects visible, typed, reviewable, reproducible, and eventually governable.

## Relationship to Latticra Seal

Latticra Seal remains the verification, reporting, manifest/hash baseline, and policy-boundary lane inside the Latticra ecosystem.

Working Draft 0.13 carries the Seal trust/crypto ladder forward, keeps the current Latticra Console contract bundle, preserves Runtime Boundary Lat/LIR provenance records, and folds in signing-operation status guard/predecessor alignment for the Seal signing path. Seal documents signed request metadata, request freshness metadata, verification receipts, crypto verify backend metadata, local Ed25519 verify-only results, verified receipt promotion metadata, verified capability gate metadata, verified effect decision metadata, runtime handoff evaluation metadata, runtime handoff report metadata, report envelope metadata, signature request metadata, signing authorization metadata, signer handoff metadata, signer invocation metadata, signing-operation readiness metadata, effect decisions, runtime handoff boundaries, and report envelopes. Latticra Console documents metadata-only host-adapter, receipt-request, receipt-payload, payload-artifact-draft, signature-request-binding, OS-base, and VM-evidence contract surfaces. Runtime Boundary carries Lat pipeline first-clause evidence as provenance metadata. These surfaces do not claim host embedding, language execution, operator evaluation, payload materialization, receipt writing, signing, signer invocation, signature verification, private-key handling, key generation, trust-store behavior, revocation checks, object sealing, capability enforcement, effect execution, VM launch, boot behavior, host effects, network authority, runtime authority, runtime handoff execution, production OS status, or production cryptography.

The new System Substrate handbook places Seal in the full project architecture alongside:

- Latticra Panel
- Latticra Console
- Nucleus report-only task boundaries
- Nadia offline AI contract metadata
- macOS and Fedora platform validation lanes
- guarded local-prefix installation
- receipts and reports
- command contracts
- Lat and LIR contract surfaces
- runtime-boundary metadata
- validation lanes
- research artifacts and visual theorem engines

## Canonical public wording

Use language like:

> Latticra is an early, evidence-bound system substrate for describing, measuring, and presenting local project state under explicit authority constraints.

Avoid language that claims production protection, runtime enforcement, malware prevention, ransomware prevention, kernel enforcement, root authority, or certification unless those claims are implemented, tested, and documented with reproducible evidence.

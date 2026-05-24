# The Latticra System Substrate

**Title:** *The Latticra System Substrate: An Effect at Modern Security*  
**Edition:** Working Draft 0.1 — 2026-05-24  
**Role:** Project-level technical handbook for Latticra, Latticra Seal, Panel, Lat/LIR contract surfaces, receipts, reports, and future runtime-boundary research.

This handbook supersedes the former standalone **Latticra Seal Documentation Handbook** as the main reader-facing book for the project.

The Seal handbook was useful as a subsystem reference. This new handbook expands the scope into a computer-science-oriented project book: Latticra as an evidence-bound system substrate for local integrity, authority boundaries, reproducible reports, receipts, policy semantics, and future runtime-handoff research.

## Downloads

- [PDF edition](the-latticra-system-substrate.pdf)
- [Editable DOCX edition](the-latticra-system-substrate.docx)

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

The new System Substrate handbook places Seal in the full project architecture alongside:

- Latticra Panel
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

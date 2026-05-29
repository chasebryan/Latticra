# Latticra Effect Substrate Transition Plan

**Status:** Draft (v0.3.0edge → real effect capability)
**Date:** 2026-05-29
**Owner:** Chase Bryan (with Grok assistance)

## Goal

Move Latticra from a pure evidence/report-only foundation to a genuine, useful substrate architecture that can safely perform real, bounded system modifications on host systems (starting with Linux user-space, expanding to full host complement layers).

## Core Principles (Non-Negotiable)

- Contract-first (no effect without explicit contract + identity)
- Evidence-bound (every effect must produce auditable evidence)
- Denied-by-default authority
- Substrate model (complements hosts, does not claim to replace them)
- Clear, reviewable boundaries at every layer
- Progressive disclosure of capability (start narrow, expand with evidence)

## Current State (v0.3.0edge)

- Excellent isolated Development Platform
- Rich contract, preview, report, and boundary modeling
- Almost everything is deliberately "no-effect" or "requires future gate"
- Packaging is planning-only

## Proposed Transition Phases

### Phase 1: User-Space Effect Foundation (Next 3-6 months target)

**Scope:**
- User-space only (no kernel, no privileged daemons initially)
- Narrow, high-value effects with strong contracts
- Full evidence capture for every effect

**Initial Effect Classes to Implement (in order):**

1. **Guarded Local File Operations** (within user-controlled paths)
2. **Guarded Command Execution** (with full parameter + environment evidence)
3. **Guarded Configuration Management** (templated, auditable writes)
4. **Guarded Service/User Unit Control** (systemd user units, launchd agents where applicable)

**Key Deliverables:**
- Effect Execution Layer (new `src/effect/` or `src/substrate/effect/`)
- Effect Gate (runtime enforcement of contracts + boundaries)
- Evidence Recorder (structured, signed or hash-chained evidence)
- Updated Nucleus + Runtime Boundary to actually dispatch real effects when policy allows
- Packaging that produces real, installable user-local tools

### Phase 2: Host Complement Layer

- Optional privileged components (with extremely narrow authority)
- Better integration with host package managers, init systems, etc.
- Architecture-specific backends behind clear interfaces

### Phase 3: Cross-Architecture Maturity

- Real support for x86_64 and aarch64 hosted profiles
- QEMU and real-device validation pipelines
- Proper multi-distro packaging (deb, rpm, pkg, ports, etc.)

## Build System Evolution

The current `build-separate/` platform is excellent for development.

We need to evolve toward:

- Profile-aware builds (`--profile=hosted-x86_64`, `--profile=report-only`, etc.)
- Real artifact production for target hosts
- Cross-compilation support
- Integration with packaging directories (`packaging/fedora/`, etc.)

## Risk Management

- Start extremely narrow (user-controlled paths only)
- Heavy use of the existing Seal + Nucleus + Runtime Boundary machinery for gating
- Mandatory evidence for every effect
- Progressive rollout with strong non-claims

## Success Criteria for Phase 1

- A user can install a Latticra user-space agent
- Define a contract for a file operation or command
- Execute it through Latticra
- Get rich, auditable evidence that the effect happened (or was denied)
- The system remains denied-by-default and contract-first

---

This document should be treated as a living transition plan. All effect capability must still go through the existing contract, preview, and boundary systems.

## Work Started in v0.3.0edge → v0.4 Transition

As of late May 2026, initial scaffolding has begun:

- Created `src/substrate/effect/` directory and basic `effect_dispatcher.c` skeleton.
- Created public header `include/latticra/substrate/effect.h`.
- Added `BUILD_PROFILE` support to the Development Platform (`build-separate.sh`).
- New Makefile targets: `build-separate-platform-effect` and `build-separate-effect-tools`.
- Effect dispatcher currently returns "effects disabled" unless explicitly built in effect-enabled profile.

This is the beginning of the shift from pure report-only to gated real effects.

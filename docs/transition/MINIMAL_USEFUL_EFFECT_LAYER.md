# Minimal Useful Effect Layer (Phase 1 Target)

**Goal:** The smallest possible set of real, gated effects that would make Latticra genuinely useful as a substrate on Linux (and eventually other hosts) while staying true to the project's principles.

## Proposed Minimal Scope (User-Space Only)

### 1. Guarded Command Execution
- Execute a command with explicitly declared arguments and environment.
- Full pre- and post-execution evidence (including stdout/stderr capture with size limits).
- Policy can require operator confirmation, cryptographic approval (via Seal), or be fully automated under contract.

### 2. Guarded File Operations (within declared safe paths)
- Read / write / delete files only within paths the contract has explicitly authorized.
- Atomic operations where possible.
- Full before/after hashes and change evidence.

### 3. Guarded Environment / Configuration Management
- Apply configuration from a declared source (with validation).
- Rollback capability with evidence.

## Non-Goals for Phase 1
- Kernel modifications
- Privileged system services (initially)
- Network effects (except under very narrow contracts)
- Boot / firmware changes

## Key New Components Needed

- `src/substrate/effect/` — Effect dispatcher and executor
- `src/substrate/evidence/` — Structured evidence recorder (with optional signing)
- Updates to Nucleus Task Execution to actually call into the effect layer when policy allows
- Effect Gate (runtime enforcement)
- Simple user-space agent / CLI that can perform these effects when authorized

## Success Metric
A user can write a contract, get it approved (or auto-approved under policy), execute a real file operation or command through Latticra, and receive rich, tamper-evident evidence that it happened — all while the system remains denied-by-default for anything not explicitly contracted.

This would be the first time Latticra does something *useful* in the real world rather than just describing what it would do.

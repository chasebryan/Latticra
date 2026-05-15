# Latticra Foundation Index

Status: initial planning index
Scope: foundation documents required before implementation code begins.

## Purpose

This index collects the first architecture documents for Latticra.

Latticra should refine its language model, supervisor model, effect gates, server model, update model, target architectures, and Phase1 concept translations before real implementation work begins.

## Foundation documents

- [`REAL_SYSTEM_CONTRACT.md`](REAL_SYSTEM_CONTRACT.md) — project identity, real-system boundary, and relationship to Phase1, Base1, and Fyr.
- [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md) — promotion levels from concept to real-system capability.
- [`PHASE1_IMPORT_RULE.md`](PHASE1_IMPORT_RULE.md) — rules for importing proven Phase1 concepts into Latticra.
- [`NON_CLAIMS.md`](NON_CLAIMS.md) — claims Latticra does not currently make.
- [`ARCHITECTURE_SEED.md`](ARCHITECTURE_SEED.md) — initial state-lattice and software-universe vocabulary.
- [`NAMING_SYSTEM.md`](NAMING_SYSTEM.md) — formal naming rules for translating Phase1-era concepts into professional Latticra terms.
- [`LANGUAGE_STRATEGY.md`](LANGUAGE_STRATEGY.md) — role of C, Rust, L, L-UI, and future LIR.
- [`SUPERVISOR_ARCHITECTURE.md`](SUPERVISOR_ARCHITECTURE.md) — Nucleus supervisor model and orchestration responsibilities.
- [`FEATURE_TRANSLATION_LEDGER.md`](FEATURE_TRANSLATION_LEDGER.md) — Phase1-to-Latticra feature rename and promotion ledger.
- [`EFFECT_GATES.md`](EFFECT_GATES.md) — effect categories, gating rules, and visibility requirements.
- [`UI_TERMINAL_LANGUAGE.md`](UI_TERMINAL_LANGUAGE.md) — L-UI terminal/operator interface language direction.
- [`SERVER_INTERACTION_MODEL.md`](SERVER_INTERACTION_MODEL.md) — signed, optional, inspectable server interaction model.
- [`SELF_UPDATE_MODEL.md`](SELF_UPDATE_MODEL.md) — staged signed update and rollback design.
- [`HOST_ARCHITECTURE_TARGETS.md`](HOST_ARCHITECTURE_TARGETS.md) — x86_64 and ARM64 target policy.
- [`ROADMAP.md`](ROADMAP.md) — design-first roadmap before implementation.
- [`LICENSE_POLICY.md`](LICENSE_POLICY.md) — Apache-2.0 project licensing, contributions, branding, and future notice rules.

## Initial implementation and design documents

- [`STATE_LATTICE.md`](STATE_LATTICE.md) — first C state lattice fixture, invariant tests, report surface, and no-effect boundary.
- [`TRI_PLANE_TRANSITION.md`](TRI_PLANE_TRANSITION.md) — pure preview transition model, denial reasons, and no-effect invariants.
- [`NUCLEUS_PREVIEW.md`](NUCLEUS_PREVIEW.md) — Nucleus request/effect classification, report surface, and no-execution invariants.
- [`L_UI_STATIC_REPORT.md`](L_UI_STATIC_REPORT.md) — terminal-facing L-UI static report fixture for Nucleus/state rails.
- [`L_UI_SOURCE_GRAMMAR.md`](L_UI_SOURCE_GRAMMAR.md) — L-UI source grammar draft and `.lui` fixture guardrails.
- [`L_UI_PARSER_DESIGN.md`](L_UI_PARSER_DESIGN.md) — parser design contract, error categories, no-effect constraints, and implementation gate.
- [`L_UI_PARSER_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_IMPLEMENTATION_PLAN.md) — parser implementation language, module shape, API, source-size limit, and exact test list before parser code.
- [`L_UI_PARSER.md`](L_UI_PARSER.md) — initial no-effect C parser, summary result, error labels, and parser invariants.

## Implementation rule

No implementation code should be added until the relevant contract document exists and names:

1. purpose;
2. evidence level;
3. effect boundary;
4. failure behavior;
5. non-claims;
6. tests or validation path.

## Current priority

Implemented/guarded foundation units:

```text
state lattice fixture + invariant tests
tri-plane transition model + invariant tests
Nucleus preview request classification + report invariants
L-UI static report fixture + rail invariants
L-UI source grammar draft + fixture guardrails
L-UI parser design contract + guardrails
L-UI parser implementation plan + guardrails
L-UI parser implementation + invariants
```

The next implementation target should be:

```text
L-UI parser fixture integration
```

That target should make repository fixture validation part of parser testing while keeping parser code in-memory only and no-effect.

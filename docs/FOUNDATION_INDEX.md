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
- [`L_UI_PARSER_FIXTURE_INTEGRATION.md`](L_UI_PARSER_FIXTURE_INTEGRATION.md) — repository `.lui` fixture validation through controlled parser test input.
- [`L_UI_PARSER_RESULT_REPORT.md`](L_UI_PARSER_RESULT_REPORT.md) — deterministic parser result summaries for valid and error parse states.
- [`L_UI_PARSER_DIAGNOSTICS.md`](L_UI_PARSER_DIAGNOSTICS.md) — parser diagnostic codes, stable messages, line/column rules, and future diagnostics gate.
- [`L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION_PLAN.md) — diagnostics API shape, exact tests, and report extension rules before diagnostic code.
- [`L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md`](L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md) — diagnostic structs, mapping functions, report surface, and invariants.
- [`L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_CONTRACT.md`](L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_CONTRACT.md) — parser-level invalid string escape diagnostics, diagnostic codes, source spans, messages, hints, and compatibility rules.
- [`L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md) — parser enum additions, diagnostic mapping updates, validation helpers, source-span behavior, exact tests, and compatibility expectations before parser-level string escape diagnostics code.
- [`L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md`](L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md) — parser-level diagnostics for invalid L-UI string-literal escape sequences.
- [`L_UI_PARSER_LINE_COLUMN_PRECISION_PLAN.md`](L_UI_PARSER_LINE_COLUMN_PRECISION_PLAN.md) — line/column precision rules, newline policy, byte-column behavior, and future tests.
- [`L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION_PLAN.md) — helper shapes, parser touch points, implementation tests, and boundaries before precise location code.
- [`L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION.md`](L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION.md) — private location helpers, parser touch-point updates, and location invariants.
- [`L_UI_PARSER_SOURCE_SPAN_CONTRACT.md`](L_UI_PARSER_SOURCE_SPAN_CONTRACT.md) — future source ranges, span rules, byte offsets, line/column ranges, and no-effect boundaries.
- [`L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION_PLAN.md) — source-span public API changes, report extensions, exact tests, and compatibility expectations before span code.
- [`L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md`](L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md) — public source-span metadata, parse-result spans, diagnostic spans, report extensions, and invariants.
- [`L_UI_PARSER_AST_CONTRACT.md`](L_UI_PARSER_AST_CONTRACT.md) — future AST shape, node ownership, source-span usage, capacity rules, diagnostics relationship, and no-effect boundaries.
- [`L_UI_PARSER_AST_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_AST_IMPLEMENTATION_PLAN.md) — AST public API changes, struct placement, capacity constants, ownership/lifetime rules, source-span integration, exact tests, and compatibility expectations.
- [`L_UI_PARSER_AST_IMPLEMENTATION.md`](L_UI_PARSER_AST_IMPLEMENTATION.md) — fixed-size AST metadata, source-span-aware nodes, deterministic report, and no-effect invariants.
- [`L_UI_AST_DETAILED_REPORT_CONTRACT.md`](L_UI_AST_DETAILED_REPORT_CONTRACT.md) — deterministic rail, field, text, and source-span reporting rules before detailed AST report implementation.
- [`L_UI_AST_DETAILED_REPORT_IMPLEMENTATION_PLAN.md`](L_UI_AST_DETAILED_REPORT_IMPLEMENTATION_PLAN.md) — detailed AST report public API addition, capacity, section order, failed-parse behavior, escaping policy, exact tests, and compatibility expectations.
- [`L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md`](L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md) — bounded detailed AST report for card, rail, field, text, source-span, and no-effect metadata.
- [`L_UI_AST_ESCAPED_STRING_REPORT_CONTRACT.md`](L_UI_AST_ESCAPED_STRING_REPORT_CONTRACT.md) — stable escaped string report rules for broader L-UI text values before implementation.
- [`L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION_PLAN.md`](L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION_PLAN.md) — escaped string report helper shape, escaped fields, destination sizes, too-small behavior, exact tests, and compatibility expectations.
- [`L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md`](L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md) — byte-oriented escaped string fields for detailed AST report metadata.
- [`L_UI_AST_SOURCE_BACKED_TEXT_CONTRACT.md`](L_UI_AST_SOURCE_BACKED_TEXT_CONTRACT.md) — source-backed extraction rules for AST purpose and text values before implementation.
- [`L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION_PLAN.md`](L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION_PLAN.md) — source-backed extraction helpers, quote handling, capacity behavior, span decisions, exact tests, and compatibility expectations.
- [`L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md`](L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md) — source-backed extraction of AST purpose and text values from validated L-UI source.
- [`L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md`](L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md) — decoding rules for quoted L-UI source string escapes.
- [`L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md`](L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md) — parser-level validation decision, AST decoding helper shape, NUL/capacity/span/report behavior, exact tests, and compatibility expectations before string-literal escape decoding.
- [`L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md`](L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md) — byte-oriented string-literal escape decoding for source-backed L-UI AST purpose and text values.

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
L-UI parser fixture integration + repository fixture validation
L-UI parser result report + invariants
L-UI parser diagnostics contract + guardrails
L-UI parser diagnostics implementation plan + guardrails
L-UI parser diagnostics implementation + invariants
L-UI parser string escape diagnostics contract + guardrails
L-UI parser string escape diagnostics implementation plan + guardrails
L-UI parser string escape diagnostics implementation + invariants
L-UI parser line-column precision plan + guardrails
L-UI parser line-column precision implementation plan + guardrails
L-UI parser line-column precision implementation + invariants
L-UI parser source-span contract + guardrails
L-UI parser source-span implementation plan + guardrails
L-UI parser source-span implementation + invariants
L-UI parser AST contract + guardrails
L-UI parser AST implementation plan + guardrails
L-UI parser AST implementation + invariants
L-UI AST detailed report contract + guardrails
L-UI AST detailed report implementation plan + guardrails
L-UI AST detailed report implementation + invariants
L-UI AST escaped string report contract + guardrails
L-UI AST escaped string report implementation plan + guardrails
L-UI AST escaped string report implementation + invariants
L-UI AST source-backed text contract + guardrails
L-UI AST source-backed text implementation plan + guardrails
L-UI AST source-backed text extraction implementation + invariants
L-UI string-literal escape contract + guardrails
L-UI string-literal escape implementation plan + guardrails
L-UI string-literal escape decoding implementation + invariants
```

The next implementation target should be:

```text
L-UI length-carrying AST string storage contract
```

That target should define explicit decoded string lengths before decoded NUL bytes can ever be accepted.

# Latticra

Status: real-system implementation seed
Scope: formal implementation track for the Base1 / Phase1 / Fyr architecture.

Latticra is the real-system implementation track for the Base1 / Phase1 / Fyr architecture.

It is not the simulation lab. It is not a game. It is not a claim that a finished operating system exists today.

Latticra exists to turn proven Phase1 concepts into a disciplined real-world system architecture through contracts, tests, evidence, formal state models, hardware profiles, and carefully gated implementation work.

## Relationship to Phase1

Phase1 remains the simulation, prototype, and evidence environment.

Latticra is the implementation track that imports only what Phase1 has proven enough to promote.

```text
Phase1   -> explores, simulates, models, tests, and evaluates possibility
Latticra -> formalizes, implements, validates, and promotes real-system capability
```

## Core idea

Latticra treats computing as structured software universes built from explicit state lattices, grid-like execution domains, formal movement rules, safety gates, and evidence-backed promotion levels.

The system direction includes:

- Phase-derived operator movement and state models;
- Base1-derived boot, recovery, and hardware evidence paths;
- Fyr-derived native language and control surfaces;
- Optics-derived state visibility and operator awareness;
- lattice/grid/matrix-style state spaces for real embedded software universes.

## First principles

1. No real-world claim without evidence.
2. No mutation before read-only visibility.
3. No execution before a contract.
4. No hardware effect before an explicit gate.
5. No recovery action before rollback and failure behavior are documented.
6. No concept promotion before tests and review.
7. No confusion between simulation and implementation.

## Initial documentation

Start with [`docs/FOUNDATION_INDEX.md`](docs/FOUNDATION_INDEX.md) for the full foundation map.

Core seed documents:

- [`docs/REAL_SYSTEM_CONTRACT.md`](docs/REAL_SYSTEM_CONTRACT.md) — real-system scope, rules, and non-confusion boundary.
- [`docs/EVIDENCE_LADDER.md`](docs/EVIDENCE_LADDER.md) — promotion path from concept to real-system capability.
- [`docs/PHASE1_IMPORT_RULE.md`](docs/PHASE1_IMPORT_RULE.md) — how Phase1 concepts may enter Latticra.
- [`docs/NON_CLAIMS.md`](docs/NON_CLAIMS.md) — claims Latticra does not make yet.
- [`docs/ARCHITECTURE_SEED.md`](docs/ARCHITECTURE_SEED.md) — initial architecture vocabulary and direction.
- [`docs/LANGUAGE_NAMING_POLICY.md`](docs/LANGUAGE_NAMING_POLICY.md) — Lat / Latticra Language naming and extension policy.
- [`docs/LANGUAGE_STRATEGY.md`](docs/LANGUAGE_STRATEGY.md) — C, Rust, Lat, L-UI, and LIR roles.
- [`docs/SUPERVISOR_ARCHITECTURE.md`](docs/SUPERVISOR_ARCHITECTURE.md) — Nucleus supervisor and orchestration architecture.
- [`docs/ROADMAP.md`](docs/ROADMAP.md) — design-first implementation sequence.

## Initial implementation and design units

- [`docs/STATE_LATTICE.md`](docs/STATE_LATTICE.md) — first C state lattice fixture, invariant tests, and no-effect boundary.
- [`docs/TRI_PLANE_TRANSITION.md`](docs/TRI_PLANE_TRANSITION.md) — pure preview transition model, denial reasons, and no-effect invariants.
- [`docs/NUCLEUS_PREVIEW.md`](docs/NUCLEUS_PREVIEW.md) — Nucleus request/effect classification, report surface, and no-execution invariants.
- [`docs/L_UI_STATIC_REPORT.md`](docs/L_UI_STATIC_REPORT.md) — terminal-facing L-UI static report fixture for Nucleus/state rails.
- [`docs/L_UI_SOURCE_GRAMMAR.md`](docs/L_UI_SOURCE_GRAMMAR.md) — L-UI source grammar draft and `.lui` fixture guardrails.
- [`docs/L_UI_PARSER_DESIGN.md`](docs/L_UI_PARSER_DESIGN.md) — parser design contract, error categories, no-effect constraints, and implementation gate.
- [`docs/L_UI_PARSER_IMPLEMENTATION_PLAN.md`](docs/L_UI_PARSER_IMPLEMENTATION_PLAN.md) — parser implementation language, module shape, API, source-size limit, and exact test list before parser code.
- [`docs/L_UI_PARSER.md`](docs/L_UI_PARSER.md) — initial no-effect C parser, summary result, error labels, and parser invariants.
- [`docs/L_UI_PARSER_FIXTURE_INTEGRATION.md`](docs/L_UI_PARSER_FIXTURE_INTEGRATION.md) — repository `.lui` fixture validation through controlled parser test input.
- [`docs/L_UI_PARSER_RESULT_REPORT.md`](docs/L_UI_PARSER_RESULT_REPORT.md) — deterministic parser result summaries for valid and error parse states.
- [`docs/L_UI_PARSER_DIAGNOSTICS.md`](docs/L_UI_PARSER_DIAGNOSTICS.md) — parser diagnostic codes, stable messages, line/column rules, and future diagnostics gate.
- [`docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION_PLAN.md`](docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION_PLAN.md) — diagnostics API shape, exact tests, and report extension rules before diagnostic code.
- [`docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md`](docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md) — diagnostic structs, mapping functions, report surface, and invariants.
- [`docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_CONTRACT.md`](docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_CONTRACT.md) — parser-level invalid string escape diagnostics, diagnostic codes, source spans, messages, hints, and compatibility rules.
- [`docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md`](docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md) — parser enum additions, diagnostic mapping updates, validation helpers, source-span behavior, exact tests, and compatibility expectations before parser-level string escape diagnostics code.
- [`docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md`](docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md) — parser-level diagnostics for invalid L-UI string-literal escape sequences.
- [`docs/L_UI_PARSER_LINE_COLUMN_PRECISION_PLAN.md`](docs/L_UI_PARSER_LINE_COLUMN_PRECISION_PLAN.md) — line/column precision rules, newline policy, byte-column behavior, and future tests.
- [`docs/L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION_PLAN.md`](docs/L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION_PLAN.md) — helper shapes, parser touch points, implementation tests, and boundaries before precise location code.
- [`docs/L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION.md`](docs/L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION.md) — private location helpers, parser touch-point updates, and location invariants.
- [`docs/L_UI_PARSER_SOURCE_SPAN_CONTRACT.md`](docs/L_UI_PARSER_SOURCE_SPAN_CONTRACT.md) — future source ranges, span rules, byte offsets, line/column ranges, and no-effect boundaries.
- [`docs/L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION_PLAN.md`](docs/L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION_PLAN.md) — source-span public API changes, report extensions, exact tests, and compatibility expectations before span code.
- [`docs/L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md`](docs/L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md) — public source-span metadata, parse-result spans, diagnostic spans, report extensions, and invariants.
- [`docs/L_UI_PARSER_AST_CONTRACT.md`](docs/L_UI_PARSER_AST_CONTRACT.md) — future AST shape, node ownership, source-span usage, capacity rules, diagnostics relationship, and no-effect boundaries.
- [`docs/L_UI_PARSER_AST_IMPLEMENTATION_PLAN.md`](docs/L_UI_PARSER_AST_IMPLEMENTATION_PLAN.md) — AST public API changes, struct placement, capacity constants, ownership/lifetime rules, source-span integration, exact tests, and compatibility expectations.
- [`docs/L_UI_PARSER_AST_IMPLEMENTATION.md`](docs/L_UI_PARSER_AST_IMPLEMENTATION.md) — fixed-size AST metadata, source-span-aware nodes, deterministic report, and no-effect invariants.
- [`docs/L_UI_AST_DETAILED_REPORT_CONTRACT.md`](docs/L_UI_AST_DETAILED_REPORT_CONTRACT.md) — deterministic rail, field, text, and source-span reporting rules before detailed AST report implementation.
- [`docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION_PLAN.md`](docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION_PLAN.md) — detailed AST report public API addition, capacity, section order, failed-parse behavior, escaping policy, exact tests, and compatibility expectations.
- [`docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md`](docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md) — bounded detailed AST report for card, rail, field, text, source-span, and no-effect metadata.
- [`docs/L_UI_AST_ESCAPED_STRING_REPORT_CONTRACT.md`](docs/L_UI_AST_ESCAPED_STRING_REPORT_CONTRACT.md) — stable escaped string report rules for broader L-UI text values before implementation.
- [`docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION_PLAN.md`](docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION_PLAN.md) — escaped string report helper shape, escaped fields, destination sizes, too-small behavior, exact tests, and compatibility expectations.
- [`docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md`](docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md) — byte-oriented escaped string fields for detailed AST report metadata.
- [`docs/L_UI_AST_SOURCE_BACKED_TEXT_CONTRACT.md`](docs/L_UI_AST_SOURCE_BACKED_TEXT_CONTRACT.md) — source-backed extraction rules for AST purpose and text values before implementation.
- [`docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION_PLAN.md`](docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION_PLAN.md) — source-backed extraction helpers, quote handling, capacity behavior, span decisions, exact tests, and compatibility expectations.
- [`docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md`](docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md) — source-backed extraction of AST purpose and text values from validated L-UI source.
- [`docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_CONTRACT.md`](docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_CONTRACT.md) — explicit decoded byte lengths for L-UI AST purpose and text values.
- [`docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md`](docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md) — public struct field placement, initialization rules, decode length assignment, report fields, length-aware escaping, and exact tests before storage code changes.
- [`docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md`](docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md) — explicit decoded byte lengths for L-UI AST purpose and text values.
- [`docs/L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md`](docs/L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md) — future escaped decoded NUL acceptance rules after length-carrying AST string storage.
- [`docs/L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md`](docs/L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md) — decoding rules for quoted L-UI source string escapes.
- [`docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md`](docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md) — parser-level validation decision, AST decoding helper shape, NUL/capacity/span/report behavior, exact tests, and compatibility expectations before string-literal escape decoding.
- [`docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md`](docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md) — byte-oriented string-literal escape decoding for source-backed L-UI AST purpose and text values.

Run the current implementation checks with:

```sh
sh scripts/test-language-naming-policy.sh
sh scripts/test-state-lattice.sh
sh scripts/test-tri-plane-transition.sh
sh scripts/test-nucleus-preview.sh
sh scripts/test-l-ui-static-report.sh
sh scripts/test-l-ui-grammar-fixtures.sh
sh scripts/test-l-ui-parser-design.sh
sh scripts/test-l-ui-parser-implementation-plan.sh
sh scripts/test-l-ui-parser.sh
sh scripts/test-l-ui-parser-fixture-integration.sh
sh scripts/test-l-ui-parser-result-report.sh
sh scripts/test-l-ui-parser-diagnostics-contract.sh
sh scripts/test-l-ui-parser-diagnostics-implementation-plan.sh
sh scripts/test-l-ui-parser-diagnostics.sh
sh scripts/test-l-ui-parser-string-escape-diagnostics-contract.sh
sh scripts/test-l-ui-parser-string-escape-diagnostics-implementation-plan.sh
sh scripts/test-l-ui-parser-string-escape-diagnostics.sh
sh scripts/test-l-ui-parser-line-column-precision-plan.sh
sh scripts/test-l-ui-parser-line-column-precision-implementation-plan.sh
sh scripts/test-l-ui-parser-location.sh
sh scripts/test-l-ui-parser-source-span-contract.sh
sh scripts/test-l-ui-parser-source-span-implementation-plan.sh
sh scripts/test-l-ui-parser-source-span.sh
sh scripts/test-l-ui-parser-ast-contract.sh
sh scripts/test-l-ui-parser-ast-implementation-plan.sh
sh scripts/test-l-ui-parser-ast.sh
sh scripts/test-l-ui-ast-detailed-report-contract.sh
sh scripts/test-l-ui-ast-detailed-report-implementation-plan.sh
sh scripts/test-l-ui-ast-detailed-report.sh
sh scripts/test-l-ui-ast-escaped-string-report-contract.sh
sh scripts/test-l-ui-ast-escaped-string-report-implementation-plan.sh
sh scripts/test-l-ui-ast-escaped-string-report.sh
sh scripts/test-l-ui-ast-source-backed-text-contract.sh
sh scripts/test-l-ui-ast-source-backed-text-implementation-plan.sh
sh scripts/test-l-ui-ast-source-backed-text.sh
sh scripts/test-l-ui-ast-length-carrying-string-storage-contract.sh
sh scripts/test-l-ui-ast-length-carrying-string-storage-implementation-plan.sh
sh scripts/test-l-ui-ast-length-carrying-string-storage.sh
sh scripts/test-l-ui-decoded-nul-acceptance-contract.sh
sh scripts/test-l-ui-string-literal-escape-contract.sh
sh scripts/test-l-ui-string-literal-escape-implementation-plan.sh
sh scripts/test-l-ui-string-literal-escape.sh
```

## Current boundary

Latticra currently contains foundation contracts, a language naming policy, an initial no-effect state lattice fixture, a pure preview tri-plane transition model, Nucleus preview request classification with operator-visible reporting, a static L-UI report fixture, an L-UI source grammar draft with static fixtures, an L-UI parser design contract, an L-UI parser implementation plan, an initial no-effect L-UI parser, repository fixture parser integration, parser result reporting, a parser diagnostics contract, a parser diagnostics implementation plan, parser diagnostics implementation, a parser string escape diagnostics contract, a parser string escape diagnostics implementation plan, a parser string escape diagnostics implementation, a line/column precision plan, a line/column precision implementation plan, line/column precision implementation, a source-span contract, a source-span implementation plan, source-span implementation, an AST contract, an AST implementation plan, an AST implementation, an AST detailed report contract, an AST detailed report implementation plan, an AST detailed report implementation, an AST escaped string report contract, an AST escaped string report implementation plan, an AST escaped string report implementation, an AST source-backed text contract, an AST source-backed text implementation plan, an AST source-backed text extraction implementation, an AST length-carrying string storage contract, an AST length-carrying string storage implementation plan, an AST length-carrying string storage implementation, a decoded-NUL acceptance contract, a string-literal escape contract, a string-literal escape implementation plan, and a string-literal escape decoding implementation.

It does not yet provide a kernel, bootable image, installer, recovery writer, hardware mutation tool, production language runtime, hardened sandbox, network interaction, self-update execution, Nucleus task execution, L-UI rendering, decoded NUL acceptance implementation, live movement, or operating system replacement.

## License

Latticra uses Apache-2.0. See [`LICENSE`](LICENSE) and [`docs/LICENSE_POLICY.md`](docs/LICENSE_POLICY.md).

## North star

Latticra is the path from tested simulation to real implementation: a professional, evidence-bound software universe architecture built from Phase1, Base1, and Fyr concepts only after they prove themselves.
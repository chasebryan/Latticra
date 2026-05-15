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
- [`docs/LANGUAGE_STRATEGY.md`](docs/LANGUAGE_STRATEGY.md) — C, Rust, L, L-UI, and LIR roles.
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

Run the current implementation checks with:

```sh
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
```

## Current boundary

Latticra currently contains foundation contracts, an initial no-effect state lattice fixture, a pure preview tri-plane transition model, Nucleus preview request classification with operator-visible reporting, a static L-UI report fixture, an L-UI source grammar draft with static fixtures, an L-UI parser design contract, an L-UI parser implementation plan, an initial no-effect L-UI parser, repository fixture parser integration, parser result reporting, and a parser diagnostics contract.

It does not yet provide a kernel, bootable image, installer, recovery writer, hardware mutation tool, production language runtime, hardened sandbox, network interaction, self-update execution, Nucleus task execution, L-UI rendering, richer parser diagnostics, live movement, or operating system replacement.

## License

Latticra uses Apache-2.0. See [`LICENSE`](LICENSE) and [`docs/LICENSE_POLICY.md`](docs/LICENSE_POLICY.md).

## North star

Latticra is the path from tested simulation to real implementation: a professional, evidence-bound software universe architecture built from Phase1, Base1, and Fyr concepts only after they prove themselves.

# Latticra Documentation Hub

Status: public documentation orientation
Last updated: 2026-05-26
Scope: first reading paths, claim boundaries, subsystem maps, and documentation update rules.

## Purpose

This hub gives Markdown readers a stable entry point into the documentation tree.

The public site pages in this folder are useful for browsing, while the Markdown records are the durable source documents for status, claims, contracts, implementation boundaries, validation, and non-claims.

## First Reading Path

Start here when reviewing the project from a fresh checkout:

1. [`../README.md`](../README.md)
2. [`../STATUS.md`](../STATUS.md)
3. [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md)
4. [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md)
5. [`NON_CLAIMS.md`](NON_CLAIMS.md)
6. [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md)
7. [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md)
8. [`map.html`](map.html)

## Public Claim and Status Records

- [`PUBLIC_CLAIMS_LEDGER.md`](PUBLIC_CLAIMS_LEDGER.md) - allowed wording, blocked wording, promotion requirements, and review checklist.
- [`NON_CLAIMS.md`](NON_CLAIMS.md) - claims Latticra explicitly does not currently make.
- [`EVIDENCE_LADDER.md`](EVIDENCE_LADDER.md) - evidence levels for concept, fixture, tested model, report surface, guarded experiment, and later real-system capability.
- [`REAL_SYSTEM_CONTRACT.md`](REAL_SYSTEM_CONTRACT.md) - repository identity, real-system boundary, and evidence rules.
- [`status/README.md`](status/README.md) - status index and update rules.
- [`status/CURRENT_STATUS.md`](status/CURRENT_STATUS.md) - current detailed project posture and estimates.

## System Foundation

- [`FOUNDATION_INDEX.md`](FOUNDATION_INDEX.md) - broad index of foundation, project operations, implementation, guard, and current-priority records.
- [`ARCHITECTURE_SEED.md`](ARCHITECTURE_SEED.md) - initial state-lattice and software-universe vocabulary.
- [`C_CPP_FOUNDATION_DIRECTION.md`](C_CPP_FOUNDATION_DIRECTION.md) - C, constrained C++, and contract roles.
- [`CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md`](CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md) - future governed C++ authority boundary.
- [`DEFENSIVE_THREAT_MODEL_CONTRACT.md`](DEFENSIVE_THREAT_MODEL_CONTRACT.md) - defensive threat-model boundary and evidence expectations.
- [`ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md`](ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md) - runtime-authority baseline and promotion rules.

## Runtime and Language Lanes

- [`LANGUAGE_STRATEGY.md`](LANGUAGE_STRATEGY.md) - roles for C, constrained C++, Lat, L-UI, and LIR.
- [`LAT_PIPELINE_CONTRACT.md`](LAT_PIPELINE_CONTRACT.md) - no-effect Lat parse, validate, diagnose, and lower boundary.
- [`LIR_SHAPE_CONTRACT.md`](LIR_SHAPE_CONTRACT.md) - bounded intermediate-representation shape boundary.
- [`L_UI_PARSER.md`](L_UI_PARSER.md) - L-UI parser design and current report posture.
- [`NUCLEUS_TASK_EXECUTION_CONTRACT.md`](NUCLEUS_TASK_EXECUTION_CONTRACT.md) - task-boundary prerequisites and non-claims.
- [`RUNTIME_BOUNDARY_CONTRACT.md`](RUNTIME_BOUNDARY_CONTRACT.md) - disabled-by-default runtime boundary.

## Product Surface and Validation Lanes

- [`QUICK_START_CHEATSHEET.md`](QUICK_START_CHEATSHEET.md) - short command-oriented user path.
- [`../installer/README.md`](../installer/README.md) - Panel and installer workflow orientation.
- [`PRODUCTION_INSTALLER_READINESS_CONTRACT.md`](PRODUCTION_INSTALLER_READINESS_CONTRACT.md) - readiness boundary before production installer claims.
- [`FEDORA_READINESS_PLAN.md`](FEDORA_READINESS_PLAN.md) - Fedora readiness path and non-claims.
- [`UBUNTU_READINESS_PLAN.md`](UBUNTU_READINESS_PLAN.md) - Ubuntu readiness path and non-claims.
- [`OPENSUSE_READINESS_PLAN.md`](OPENSUSE_READINESS_PLAN.md) - openSUSE readiness path and non-claims.
- [`DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md`](DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md) - Debian, FreeBSD, and OpenBSD temporary package-input handoff lane.
- [`../packaging/fedora/README.md`](../packaging/fedora/README.md) - local Fedora packaging records.
- [`../packaging/ubuntu/README.md`](../packaging/ubuntu/README.md) - local Ubuntu packaging records.
- [`../packaging/debian/README.md`](../packaging/debian/README.md) - local Debian packaging records.
- [`../packaging/freebsd/README.md`](../packaging/freebsd/README.md) - local FreeBSD port records.
- [`../packaging/openbsd/README.md`](../packaging/openbsd/README.md) - local OpenBSD port records.
- [`../packaging/opensuse/README.md`](../packaging/opensuse/README.md) - local openSUSE packaging records.

## Subsystem Maps

- [`latticra-seal/README.md`](latticra-seal/README.md) - Latticra Seal documentation map.
- [`latticra-system-substrate/README.md`](latticra-system-substrate/README.md) - handbook source and generated artifacts.
- [`project_notes/README.md`](project_notes/README.md) - current direction and upcoming work notes.
- [`strategy/README.md`](strategy/README.md) - strategy record index and rules.

## Update Rule

Documentation changes that alter public meaning should update the relevant source record and entry point together.

Use this minimum check:

1. The claim appears in only the narrowest justified form.
2. The status record, non-claims, and public claims ledger agree.
3. The linked contract or implementation record exists.
4. The validation or guard path is named when the claim depends on evidence.
5. Public HTML pages and Markdown indexes do not point readers at stale wording.

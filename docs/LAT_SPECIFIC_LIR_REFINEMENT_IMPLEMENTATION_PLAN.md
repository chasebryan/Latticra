# Latticra Lat-Specific LIR Refinement Implementation Plan

Status: implementation planning contract
Scope: exact enum additions, lowering mappings, labels, tests, workflow, compatibility expectations, and non-claims before Lat-specific LIR refinement implementation.

## Purpose

This plan defines the implementation of the first Lat-specific LIR refinement.

The goal is to make Lat declaration semantics more visible in LIR without changing the no-effect boundary or adding execution behavior.

## Implementation files

Update:

```text
include/latticra/lir.h
src/lir.c
src/lat_to_lir.c
tests/lat_to_lir_lowering_invariants.c
README.md
STATUS.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/FOUNDATION_INDEX.md
```

Add:

```text
tests/lat_specific_lir_refinement_invariants.c
scripts/test-lat-specific-lir-refinement.sh
.github/workflows/lat-specific-lir-refinement.yml
docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md
```

## Public enum additions

Append Lat-specific node kinds without renumbering existing values:

```text
LATTICRA_LIR_NODE_LAT_STATE
LATTICRA_LIR_NODE_LAT_POLICY
LATTICRA_LIR_NODE_LAT_TRANSITION
LATTICRA_LIR_NODE_LAT_ASSERTION
LATTICRA_LIR_NODE_LAT_REQUIREMENT
LATTICRA_LIR_NODE_LAT_EFFECT_DECLARATION
```

Append the transition-source edge kind:

```text
LATTICRA_LIR_EDGE_TRANSITIONS_FROM
```

## Label additions

Add deterministic labels:

```text
lat_state
lat_policy
lat_transition
lat_assertion
lat_requirement
lat_effect_declaration
transitions_from
```

## Lowering changes

`latticra_lir_lower_lat_module` should emit Lat-specific declaration node kinds while preserving the existing LIR shape and counts.

The transition source relationship should use `transitions_from` rather than the generic `binds` edge.

## Test command

```sh
sh scripts/test-lat-specific-lir-refinement.sh
```

## Compatibility expectations

This implementation must not change L-UI lowering, existing generic LIR node kinds, existing generic LIR edge kinds, Lat parser behavior, Lat semantic validation behavior, Lat pipeline behavior, C++ authority behavior, Nucleus behavior, or runtime boundary behavior.

## Non-claims

This implementation plan does not implement Lat execution, LIR execution, runtime behavior, command behavior, mutation, file I/O, network I/O, recovery behavior, hardware behavior, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

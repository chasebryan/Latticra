# Latticra Lat-to-LIR Lowering Contract

Status: Lat-to-LIR lowering contract
Scope: first contract for lowering semantically valid Lat / Latticra Language metadata into LIR shape metadata before implementation code, execution, runtime behavior, or operating-system behavior.

## Purpose

This document defines the first contract for:

```text
Lat-to-LIR lowering
```

The goal is to define how a semantically valid Lat module may be represented as Latticra Intermediate Representation metadata in a future implementation slice.

This is contract-only work. It does not implement lowering code.

The current Lat lane now has:

```text
Lat source -> bounded grammar parser -> Lat semantic validation -> future Lat-to-LIR lowering
```

The current LIR lane already has a bounded representation shape and reserves `lat_module` as a source kind. This contract defines the first Lat-specific lowering boundary for that reserved source kind.

## Relationship to previous work

This contract depends on:

```text
docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
docs/LAT_SEMANTIC_VALIDATION_CONTRACT.md
docs/LAT_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md
docs/LAT_LANGUAGE_FOUNDATION_ANALYSIS.md
docs/LIR_SHAPE_CONTRACT.md
docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md
docs/LIR_SHAPE_IMPLEMENTATION.md
include/latticra/lat_parser.h
include/latticra/lat_semantic.h
include/latticra/lir.h
```

Those files remain the source of truth for Lat grammar parsing, Lat semantic validation, existing LIR shape, no-effect metadata, report behavior, and current implementation boundaries.

## First lowering target

The first target is:

```text
Lat-Core semantic module -> LIR module metadata
```

Lat-Core currently includes:

```text
state
policy
transition
assertion
effect
```

Lat-Orch remains future work.

## Input prerequisite

A future lowering function must accept only parser and semantic results that satisfy:

```text
parser_error=ok
semantic_error=ok
semantic_valid=1
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

If semantic validation failed, lowering must not produce a partial LIR module.

## Output target

The output target should be the existing LIR module shape:

```text
latticra_lir_module_t
```

The source kind should be:

```text
lat_module
```

The future implementation should reuse the existing LIR no-effect flags and report model instead of creating a separate executable representation.

## Proposed public API boundary

A future implementation plan should define exact C API names. The expected shape is:

```text
latticra_status_t latticra_lir_lower_lat_module(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module);
```

This contract does not add the function.

## Node mapping rules

A future Lat-to-LIR lowering implementation should map Lat declarations into deterministic LIR node records.

Suggested mapping:

```text
Lat module      -> LIR module node
state           -> LIR node kind field or module child node with declaration role metadata
policy          -> LIR node kind field or module child node with declaration role metadata
transition      -> LIR node kind field or module child node with source-state metadata
assertion       -> LIR node kind field or module child node with assertion metadata
effect          -> LIR effect node
require clause  -> LIR binding or metadata node
ensure clause   -> LIR binding or metadata node
effect clause   -> LIR effect metadata
field assignment -> LIR field metadata
```

Because the current LIR node enum was first shaped for L-UI, the implementation plan must either reuse existing node kinds conservatively or add exact Lat-oriented node kinds through a separate plan before code is added.

## Edge mapping rules

A future lowering implementation should use deterministic edges for relationships.

Suggested edge mapping:

```text
module contains declaration
declaration contains clause
transition references source state
policy annotates requirement metadata
assertion annotates checked metadata
effect annotates effect boundary metadata
```

If the existing edge enum is not expressive enough, the implementation plan must name any new edge kind before implementation code is added.

## Source-span preservation

Every LIR record derived from Lat must carry the source span from parser metadata.

Rules:

- module span comes from the Lat module span;
- declaration span comes from the Lat declaration span;
- clause span comes from the Lat clause span;
- transition source-state metadata should preserve the transition declaration span until a more specific reference span exists;
- effect metadata should preserve the effect clause or effect declaration span;
- lowering must not invent byte offsets.

## Effect preservation

Lat semantic validation currently accepts only `none` effect declarations in this slice.

Lat-to-LIR lowering must preserve:

```text
effect=none
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

A future implementation must reject or report unsupported effect values rather than widening behavior.

## Report model

A future Lat-to-LIR lowering report should remain deterministic and bounded.

Suggested report fields:

```text
LAT TO LIR LOWERING REPORT
status=<status>
source_kind=lat_module
module=<module-name>
declaration_count=<count>
state_count=<count>
policy_count=<count>
transition_count=<count>
assertion_count=<count>
effect_count=<count>
node_count=<count>
edge_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
```

The future implementation may use `latticra_lir_report` directly if it can represent all required fields without losing Lat-specific context.

## Error model

A future implementation plan should define stable error labels.

Expected labels:

```text
ok
null_argument
parse_not_ok
semantic_not_ok
semantic_not_valid
capacity_exceeded
unsupported_declaration_kind
unsupported_clause_kind
unsupported_effect
unsupported_lir_shape
internal_error
```

## Capacity policy

The implementation plan must name exact capacity behavior before code is added.

At minimum, it must define how many LIR nodes and edges are required per:

```text
module
declaration
clause
transition source reference
effect metadata record
```

If the existing `LATTICRA_LIR_NODE_MAX` or `LATTICRA_LIR_EDGE_MAX` is not sufficient, the plan must justify any increase before implementation code is added.

## Compatibility expectations

Lat-to-LIR lowering work must not change:

```text
Lat parser behavior
Lat semantic validation behavior
L-UI parser behavior
L-UI semantic validation behavior
existing LIR lowering from L-UI
state lattice behavior
source-span behavior
no-effect flags
```

## Future implementation gate

Lowering implementation must not begin until a separate implementation plan defines:

1. public API shape;
2. exact error enum labels;
3. exact node mapping;
4. exact edge mapping;
5. exact capacity accounting;
6. source-span mapping;
7. report format;
8. semantic prerequisite behavior;
9. compatibility expectations;
10. exact tests;
11. non-claims.

That next slice should be:

```text
LAT_TO_LIR_LOWERING_IMPLEMENTATION_PLAN.md
```

## Future test list

The implementation plan should include tests for:

```text
lat_to_lir_rejects_parse_error
lat_to_lir_rejects_semantic_error
lat_to_lir_accepts_foundation_model
lat_to_lir_sets_source_kind_lat_module
lat_to_lir_preserves_module_name
lat_to_lir_preserves_declaration_counts
lat_to_lir_preserves_transition_source_metadata
lat_to_lir_preserves_effect_none
lat_to_lir_preserves_source_spans
lat_to_lir_preserves_no_effect_flags
lat_to_lir_report_is_deterministic
lat_to_lir_report_rejects_small_buffer
lat_to_lir_does_not_execute_lat
lat_to_lir_does_not_mutate_state
lat_to_lir_is_deterministic
```

## Forbidden behavior

Lat-to-LIR lowering work must not:

- lower parser-failed input;
- lower semantic-failed input;
- execute Lat declarations;
- interpret transition behavior;
- mutate state;
- render L-UI;
- call Nucleus task execution;
- evaluate host state;
- write files;
- read files;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- broaden accepted Lat syntax;
- weaken Lat semantic validation;
- weaken existing LIR shape behavior;
- invent source byte offsets;
- imply a compiler, interpreter, runtime, package manager, or operating-system surface.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-lat-to-lir-lowering-contract.sh
```

The guard is static. It does not implement Lat-to-LIR lowering.

## Non-claims

This document does not implement Lat-to-LIR lowering, Lat execution, Lat compilation, Lat interpretation, LIR execution, command behavior, Nucleus task handling, state mutation, runtime behavior, recovery behavior, server interaction, self-update, hardware support, boot readiness, or operating-system completeness.

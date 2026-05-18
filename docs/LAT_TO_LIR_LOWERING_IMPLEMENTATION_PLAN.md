# Latticra Lat-to-LIR Lowering Implementation Plan

Status: implementation planning contract
Scope: exact public API, files, structs, errors, capacity accounting, node mapping, edge mapping, source-span mapping, report format, tests, compatibility expectations, and non-claims before Lat-to-LIR lowering code.

## Purpose

This document defines the implementation plan for the first Lat-to-LIR lowering slice.

The existing Lat lane now has a bounded grammar parser and a bounded no-effect semantic validator. The next implementation step must not jump directly into execution or runtime behavior. It must first define the exact lowering API and deterministic mapping from semantically valid Lat metadata into the existing LIR module shape.

This document is plan-only. It does not implement Lat-to-LIR lowering.

## Relationship to previous work

This plan depends on:

```text
docs/LAT_TO_LIR_LOWERING_CONTRACT.md
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
fixtures/lat/foundation_model.lat
```

Those files remain the source of truth for parser metadata, semantic validation, LIR shape, no-effect flags, fixture behavior, and current report boundaries.

## Implementation language decision

The first Lat-to-LIR lowering implementation should be written in C.

Reason:

- the existing Lat parser is C;
- the existing Lat semantic validator is C;
- the existing LIR shape is C;
- the lowering layer should remain bounded, deterministic, caller-buffer based, and no-effect;
- constrained C++ authority layers should consume stable C substrate data rather than define the first lowering surface.

## Implementation files

The future implementation slice should add:

```text
include/latticra/lat_to_lir.h
src/lat_to_lir.c
tests/lat_to_lir_lowering_invariants.c
scripts/test-lat-to-lir-lowering.sh
docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md
```

The implementation should reuse:

```text
include/latticra/lat_parser.h
include/latticra/lat_semantic.h
include/latticra/lir.h
fixtures/lat/foundation_model.lat
```

The implementation should not add runtime execution, command behavior, file I/O, network I/O, host mutation, recovery behavior, hardware behavior, or a package/runtime surface.

## Public API shape

Add public API names:

```text
latticra_lat_to_lir_error_t
latticra_lat_to_lir_result_t
latticra_lat_to_lir_error_label
latticra_lir_lower_lat_module
latticra_lat_to_lir_report
```

Recommended function signatures:

```text
const char *latticra_lat_to_lir_error_label(latticra_lat_to_lir_error_t error);

latticra_status_t latticra_lir_lower_lat_module(
    const latticra_lat_parse_result_t *parse_result,
    const latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *result);

latticra_status_t latticra_lat_to_lir_report(
    const latticra_lat_to_lir_result_t *result,
    char *buffer,
    size_t buffer_len);
```

The lowering function should fill both the target `latticra_lir_module_t` and a smaller Lat-to-LIR summary result. The summary result exists so tests can assert lowering-specific counts and errors without parsing the generic LIR report.

## Capacity constants

Add exact bounded constants:

```text
LATTICRA_LAT_TO_LIR_REPORT_MAX 4096u
LATTICRA_LAT_TO_LIR_MODULE_NODE_COST 1u
LATTICRA_LAT_TO_LIR_DECLARATION_NODE_COST 1u
LATTICRA_LAT_TO_LIR_CLAUSE_NODE_COST 1u
LATTICRA_LAT_TO_LIR_DECLARATION_EDGE_COST 1u
LATTICRA_LAT_TO_LIR_CLAUSE_EDGE_COST 1u
LATTICRA_LAT_TO_LIR_TRANSITION_SOURCE_EDGE_COST 1u
```

Capacity accounting must be deterministic.

Required nodes:

```text
1 + declaration_count + clause_count
```

Required edges:

```text
declaration_count + clause_count + transition_count
```

If required nodes exceed `LATTICRA_LIR_NODE_MAX`, return `capacity_exceeded`.

If required edges exceed `LATTICRA_LIR_EDGE_MAX`, return `capacity_exceeded`.

## Error enum

Add error enum values:

```text
LATTICRA_LAT_TO_LIR_OK
LATTICRA_LAT_TO_LIR_NULL_ARGUMENT
LATTICRA_LAT_TO_LIR_PARSE_NOT_OK
LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_OK
LATTICRA_LAT_TO_LIR_SEMANTIC_NOT_VALID
LATTICRA_LAT_TO_LIR_NO_EFFECT_VIOLATION
LATTICRA_LAT_TO_LIR_CAPACITY_EXCEEDED
LATTICRA_LAT_TO_LIR_UNSUPPORTED_DECLARATION_KIND
LATTICRA_LAT_TO_LIR_UNSUPPORTED_CLAUSE_KIND
LATTICRA_LAT_TO_LIR_UNSUPPORTED_EFFECT
LATTICRA_LAT_TO_LIR_UNSUPPORTED_LIR_SHAPE
LATTICRA_LAT_TO_LIR_INTERNAL_ERROR
```

Stable labels:

```text
ok
null_argument
parse_not_ok
semantic_not_ok
semantic_not_valid
no_effect_violation
capacity_exceeded
unsupported_declaration_kind
unsupported_clause_kind
unsupported_effect
unsupported_lir_shape
internal_error
```

## Result struct

Add a bounded summary result:

```text
latticra_status_t status;
latticra_lat_to_lir_error_t error;
latticra_lat_source_span_t span;
char module_name[LATTICRA_LAT_NAME_MAX];
size_t declaration_count;
size_t state_count;
size_t policy_count;
size_t transition_count;
size_t assertion_count;
size_t effect_count;
size_t clause_count;
size_t node_count;
size_t edge_count;
size_t binding_count;
size_t text_count;
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

The result must be fully initialized on success and failure.

## Semantic prerequisite behavior

The lowering function must reject null arguments with `LATTICRA_STATUS_NULL_ARGUMENT`.

The lowering function must reject parser failure when:

```text
parse_result->error != LATTICRA_LAT_PARSE_OK
```

The lowering function must reject semantic failure when:

```text
semantic_result->error != LATTICRA_LAT_SEMANTIC_OK
semantic_result->semantic_valid != 1
```

The lowering function must reject no-effect flag violations when any of these differ from the no-effect boundary:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

No partial successful LIR module should be reported for failed prerequisites.

## LIR module metadata mapping

On success, the future implementation should set:

```text
module->status = LATTICRA_STATUS_OK
module->error = LATTICRA_LIR_OK
module->source_kind = LATTICRA_LIR_SOURCE_LAT_MODULE
module->module_name = parse_result->module.module_name
module->card_name = ""
module->effect = "none"
module->boundary = "lat_semantic_only"
module->source_span = parse_result->module.span converted to the LIR source-span shape
module->no_effect = 1
module->execution_allowed = 0
module->mutation_allowed = 0
module->server_allowed = 0
module->recovery_allowed = 0
module->hardware_allowed = 0
```

The implementation plan should not require `card_name` for Lat modules.

## Source-span conversion

The current Lat source span and L-UI source span have compatible fields:

```text
start_offset
end_offset
start_line
start_column
end_line
end_column
```

The implementation should use a private conversion helper from `latticra_lat_source_span_t` to the LIR span type used by `latticra_lir_module_t`.

The conversion must copy fields exactly and must not invent byte offsets.

## Node mapping

The first implementation should not add new LIR node enum values.

Use the existing node kinds conservatively:

```text
Lat module declaration -> LATTICRA_LIR_NODE_MODULE
state declaration      -> LATTICRA_LIR_NODE_FIELD with value="state"
policy declaration     -> LATTICRA_LIR_NODE_FIELD with value="policy"
transition declaration -> LATTICRA_LIR_NODE_FIELD with value="transition"
assertion declaration  -> LATTICRA_LIR_NODE_FIELD with value="assertion"
effect declaration     -> LATTICRA_LIR_NODE_EFFECT with value="effect"
field clause           -> LATTICRA_LIR_NODE_FIELD
require clause         -> LATTICRA_LIR_NODE_BINDING with value="require"
ensure clause          -> LATTICRA_LIR_NODE_BINDING with value="ensure"
effect clause          -> LATTICRA_LIR_NODE_EFFECT
```

Declaration node fields:

```text
name = declaration.name
value = declaration kind label
binding = declaration.source_name for transition declarations, otherwise empty
source_span = declaration.span
parent_index = module node index
```

Clause node fields:

```text
name = clause.left
value = clause.right
binding = clause.keyword
source_span = clause.span
parent_index = declaration node index
```

## Edge mapping

The first implementation should use existing edge kinds:

```text
module contains declaration -> LATTICRA_LIR_EDGE_CONTAINS
declaration contains clause -> LATTICRA_LIR_EDGE_CONTAINS
transition references source state -> LATTICRA_LIR_EDGE_BINDS
```

Transition source-reference edges should connect the transition declaration node to the referenced state declaration node when that state exists. Semantic validation is the prerequisite that guarantees the referenced state exists.

Policy and assertion clauses may remain contained child nodes in the first implementation. Additional `annotates` edges may wait for a later refinement.

## Binding and text counts

The first Lat-to-LIR lowering implementation should not populate the LIR text table.

```text
text_count=0
```

The first implementation may set `binding_count` equal to the number of `require` and `ensure` clause nodes, or it may keep `binding_count=0` if binding references are reserved for L-UI only.

This plan chooses:

```text
binding_count=0
```

Reason: Lat requirement and ensure clauses are metadata nodes in this first slice, not resolved L-UI binding references.

## Effect handling

The first implementation accepts only semantic output that preserves effect `none`.

If any Lat effect value maps to `LATTICRA_LAT_EFFECT_UNKNOWN` or any non-`none` value reaches lowering, return:

```text
unsupported_effect
```

This should be unreachable after successful semantic validation, but the lowering layer must still defend its own boundary.

## Report format

`latticra_lat_to_lir_report` should emit:

```text
LAT TO LIR LOWERING REPORT
status=<integer-status>
error=<error-label>
module=<module-name>
declaration_count=<count>
state_count=<count>
policy_count=<count>
transition_count=<count>
assertion_count=<count>
effect_count=<count>
clause_count=<count>
node_count=<count>
edge_count=<count>
binding_count=<count>
text_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
span_start_offset=<offset>
span_end_offset=<offset>
span_start_line=<line>
span_start_column=<column>
span_end_line=<line>
span_end_column=<column>
```

Small buffers must return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the output buffer when possible.

## Exact test list

The implementation slice should add tests for:

```text
lat_to_lir_rejects_null_arguments
lat_to_lir_rejects_parse_error
lat_to_lir_rejects_semantic_error
lat_to_lir_rejects_semantic_not_valid
lat_to_lir_accepts_foundation_model
lat_to_lir_sets_source_kind_lat_module
lat_to_lir_preserves_module_name
lat_to_lir_preserves_declaration_counts
lat_to_lir_preserves_transition_source_metadata
lat_to_lir_preserves_effect_none
lat_to_lir_preserves_source_spans
lat_to_lir_preserves_no_effect_flags
lat_to_lir_counts_nodes_and_edges_deterministically
lat_to_lir_report_is_deterministic
lat_to_lir_report_rejects_small_buffer
lat_to_lir_error_labels_are_stable
lat_to_lir_does_not_execute_lat
lat_to_lir_does_not_mutate_state
lat_to_lir_is_deterministic
```

## Test command

The implementation slice should add:

```sh
sh scripts/test-lat-to-lir-lowering.sh
```

The test should compile with:

```text
-std=c99 -Wall -Wextra -Werror -pedantic
```

and include:

```text
src/lat_parser.c
src/lat_semantic.c
src/lat_to_lir.c
src/lir.c
tests/lat_to_lir_lowering_invariants.c
```

## Documentation update plan

The implementation slice should update:

```text
README.md
STATUS.md
docs/FOUNDATION_INDEX.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
```

and add:

```text
docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md
```

## Compatibility expectations

The implementation must not change:

```text
Lat grammar parser behavior
Lat semantic validation behavior
L-UI parser behavior
L-UI semantic validation behavior
existing LIR lowering from L-UI
state lattice behavior
source-span behavior
no-effect flags
```

## Implementation boundary

The implementation must not:

- execute Lat declarations;
- interpret transition behavior;
- mutate state;
- render L-UI;
- call Nucleus task execution;
- evaluate host state;
- write files;
- read files;
- open network connections;
- call update code;
- call recovery code;
- call hardware code;
- broaden accepted Lat syntax;
- weaken Lat semantic validation;
- weaken existing LIR shape behavior;
- invent source byte offsets;
- imply a compiler, interpreter, runtime, package manager, or operating-system surface.

## Current validation command

This implementation plan is guarded by:

```sh
sh scripts/test-lat-to-lir-lowering-implementation-plan.sh
```

The guard is static. It does not implement Lat-to-LIR lowering.

## Implementation gate

Lat-to-LIR lowering implementation code may be added only after this plan is merged and guarded.

## Non-claims

This document does not implement Lat-to-LIR lowering, Lat execution, Lat compilation, Lat interpretation, LIR execution, command behavior, Nucleus task handling, state mutation, runtime behavior, recovery behavior, server interaction, self-update, hardware support, boot readiness, or operating-system completeness.

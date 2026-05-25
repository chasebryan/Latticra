# Latticra Lat-to-LIR Lowering Implementation

Status: model-aware implementation record
Scope: bounded no-effect Lat-to-LIR lowering implementation, normalized model entry point, compatibility wrapper, public API, test runner, workflow, report surface, fixture path, and invariants.

## Purpose

This implementation adds the bounded Lat-to-LIR lowering surface for semantically valid Lat / Latticra Language metadata.

The primary lowering implementation consumes:

```text
latticra_lat_model_t
```

and fills:

```text
latticra_lir_module_t
latticra_lat_to_lir_result_t
```

The compatibility wrapper `latticra_lir_lower_lat_module` still accepts parser and semantic results, normalizes a local Lat model, and delegates to the model-aware lowerer.

The lowering surface is metadata-only. It does not execute Lat, interpret transitions, mutate state, render L-UI, invoke Nucleus behavior, perform runtime behavior, write files, read files, open network connections, call update code, call recovery code, touch hardware, or provide an operating-system surface.

## Implementation files

```text
include/latticra/lat_to_lir.h
src/lat_to_lir.c
tests/lat_to_lir_lowering_invariants.c
scripts/test-lat-to-lir-lowering.sh
.github/workflows/lat-to-lir-lowering.yml
```

Related contract and plan files:

```text
docs/LAT_TO_LIR_LOWERING_CONTRACT.md
docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION_PLAN.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
docs/LAT_SEMANTIC_VALIDATION_CONTRACT.md
docs/LIR_SHAPE_IMPLEMENTATION.md
```

## Public API

The public API adds:

```text
latticra_lat_to_lir_error_t
latticra_lat_to_lir_result_t
latticra_lat_to_lir_error_label
latticra_lir_lower_lat_model
latticra_lir_lower_lat_module
latticra_lat_to_lir_report
```

The model-aware lowering function accepts normalized Lat model metadata, writes a LIR module, and writes a lowering-specific summary result. The wrapper accepts parser and semantic metadata for existing callers.

## Accepted input

The lowering implementation accepts only input that satisfies:

```text
parse_result->error == LATTICRA_LAT_PARSE_OK
semantic_result->error == LATTICRA_LAT_SEMANTIC_OK
semantic_result->semantic_valid == 1
model->error == LATTICRA_LAT_MODEL_OK
no_effect == 1
execution_allowed == 0
mutation_allowed == 0
```

The implementation also preserves server, recovery, and hardware denial flags in the generated LIR module.

## LIR output shape

On success, the LIR module records:

```text
source_kind=lat_module
module=<Lat module name>
card=
effect=none
boundary=lat_semantic_only
node_count=1 + declaration_count + clause_count
edge_count=declaration_count + clause_count + transition_count
binding_count=0
text_count=0
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

The implementation uses the Lat-specific LIR declaration node kinds and transition source edge kind while preserving the same no-effect metadata boundary.

## Mapping summary

```text
Lat module      -> LIR module node
state           -> LIR lat_state node
policy          -> LIR lat_policy node
transition      -> LIR lat_transition node with source-state metadata
assertion       -> LIR lat_assertion node
effect          -> LIR lat_effect_declaration node
field clause    -> LIR field node
require clause  -> LIR lat_requirement node metadata
ensure clause   -> LIR lat_requirement node metadata
effect clause   -> LIR effect node metadata
```

Edges use:

```text
module contains declaration
declaration contains clause
transition transitions_from source state
```

## Source-span behavior

Lat source spans are copied into the compatible LIR source-span shape:

```text
start_offset
end_offset
start_line
start_column
end_line
end_column
```

The implementation does not invent byte offsets.

## Report surface

`latticra_lat_to_lir_report` emits a deterministic bounded report beginning with:

```text
LAT TO LIR LOWERING REPORT
```

The report records status, lowering error label, model error label, module name, declaration counts, model counts, clause counts, first transition source index, node count, edge count, no-effect flags, and source-span fields.

Small output buffers return:

```text
LATTICRA_STATUS_BUFFER_TOO_SMALL
```

and clear the buffer when possible.

## Validation

Run:

```sh
sh scripts/test-lat-to-lir-lowering.sh
```

The runner compiles with:

```text
-std=c99 -Wall -Wextra -Werror -pedantic
```

and includes:

```text
src/lat_parser.c
src/lat_semantic.c
src/lat_model.c
src/lir.c
src/lat_to_lir.c
tests/lat_to_lir_lowering_invariants.c
```

## Invariants covered

The invariant suite checks:

```text
foundation model lowers successfully
normalized model lowers through the model-aware entry point
source kind is lat_module
declaration and clause counts are preserved
model counts and first transition source index are preserved
node and edge counts are deterministic
module metadata is preserved
transition source metadata is preserved
parse failures are rejected
semantic failures are rejected
no-effect flags are preserved
lowering reports are deterministic
small report buffers are rejected and cleared
error labels are stable
```

## Current evidence level

This is an L2 implementation slice:

```text
contract + implementation plan + C implementation + invariant tests + workflow coverage
```

It is not a compiler, interpreter, runtime, package system, command surface, or operating-system surface.

## Next implementation candidate

The next candidate is:

```text
Lat model-driven lowering diagnostics and status integration
```

After this model-driven lowering integration, a later refinement may broaden clause operator/value metadata or add focused diagnostics only through a separate bounded contract or plan.

## Non-claims

This implementation does not execute Lat, compile Lat, interpret Lat, execute LIR, perform runtime behavior, mutate state, render L-UI, invoke Nucleus behavior, perform recovery behavior, interact with servers, perform self-update, touch hardware, provide boot readiness, or provide operating-system completeness.

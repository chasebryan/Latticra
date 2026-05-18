# Latticra Lat-to-LIR Lowering Implementation

Status: initial implementation record
Scope: first bounded no-effect Lat-to-LIR lowering implementation, public API, test runner, workflow, report surface, fixture path, and invariants.

## Purpose

This implementation adds the first Lat-to-LIR lowering surface for semantically valid Lat / Latticra Language metadata.

The implementation consumes:

```text
latticra_lat_parse_result_t
latticra_lat_semantic_result_t
```

and fills:

```text
latticra_lir_module_t
latticra_lat_to_lir_result_t
```

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
latticra_lir_lower_lat_module
latticra_lat_to_lir_report
```

The lowering function accepts parser and semantic metadata, writes a LIR module, and writes a lowering-specific summary result.

## Accepted input

The lowering implementation accepts only input that satisfies:

```text
parse_result->error == LATTICRA_LAT_PARSE_OK
semantic_result->error == LATTICRA_LAT_SEMANTIC_OK
semantic_result->semantic_valid == 1
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

The first implementation reuses existing LIR node and edge kinds rather than adding new enum variants.

## Mapping summary

```text
Lat module      -> LIR module node
state           -> LIR field node with declaration role metadata
policy          -> LIR field node with declaration role metadata
transition      -> LIR field node with source-state metadata
assertion       -> LIR field node with assertion role metadata
effect          -> LIR effect node
field clause    -> LIR field node
require clause  -> LIR binding node metadata
ensure clause   -> LIR binding node metadata
effect clause   -> LIR effect node metadata
```

Edges use:

```text
module contains declaration
declaration contains clause
transition binds source state
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

The report records status, error label, module name, declaration count, clause count, node count, edge count, no-effect flags, and source-span fields.

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
src/lir.c
src/lat_to_lir.c
tests/lat_to_lir_lowering_invariants.c
```

## Invariants covered

The invariant suite checks:

```text
foundation model lowers successfully
source kind is lat_module
declaration and clause counts are preserved
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
Lat-to-LIR lowering implementation documentation and status integration
```

After status integration, a later refinement may broaden Lat-specific LIR node kinds only through a separate contract or plan.

## Non-claims

This implementation does not execute Lat, compile Lat, interpret Lat, execute LIR, perform runtime behavior, mutate state, render L-UI, invoke Nucleus behavior, perform recovery behavior, interact with servers, perform self-update, touch hardware, provide boot readiness, or provide operating-system completeness.

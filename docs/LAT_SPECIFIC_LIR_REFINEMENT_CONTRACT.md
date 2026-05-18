# Latticra Lat-Specific LIR Refinement Contract

Status: Lat-specific LIR refinement contract
Scope: explicit Lat declaration and transition metadata in LIR after grammar parsing, semantic validation, Lat-to-LIR lowering, and Lat pipeline composition.

## Purpose

This contract defines the first Lat-specific refinement of the Latticra Intermediate Representation.

The existing Lat-to-LIR lowering path materializes a `lat_module` LIR shape. This refinement makes the Lat origin of key nodes and transition-source edges explicit instead of relying only on generic field, binding, and effect node kinds.

## Refinement target

The refinement introduces explicit LIR node kinds for Lat declarations:

```text
lat_state
lat_policy
lat_transition
lat_assertion
lat_requirement
lat_effect_declaration
```

and an explicit edge kind for transition source relationships:

```text
transitions_from
```

## Compatibility policy

The refinement must preserve existing numeric values for already-published LIR enum members.

The generic node kinds and edge kinds remain available for L-UI lowering and existing LIR users.

## Required behavior

Lat-to-LIR lowering must map:

```text
state declaration      -> lat_state
policy declaration     -> lat_policy
transition declaration -> lat_transition
assertion declaration  -> lat_assertion
effect declaration     -> lat_effect_declaration
require / ensure       -> lat_requirement
transition source edge -> transitions_from
```

The implementation must preserve:

```text
source spans
module/declaration/clause counts
node and edge counts
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Forbidden behavior

This refinement must not execute Lat, execute LIR, interpret transitions, mutate state, perform effects, perform file I/O, perform network I/O, call server code, call recovery code, touch hardware, or provide runtime behavior.

## Validation

The implementation must add focused invariants for:

```text
lat_specific_lir_labels_are_stable
lat_specific_lir_uses_lat_declaration_node_kinds
lat_specific_lir_uses_lat_requirement_node_kind
lat_specific_lir_uses_transition_source_edge_kind
lat_specific_lir_preserves_counts_and_no_effect_flags
```

## Non-claims

This contract does not implement Lat execution, Lat compilation, Lat interpretation, LIR execution, runtime behavior, command behavior, Nucleus task execution, mutation, file I/O, network I/O, recovery behavior, hardware behavior, sandboxing, malware prevention, ransomware prevention, certification, accreditation, or operating-system completeness.

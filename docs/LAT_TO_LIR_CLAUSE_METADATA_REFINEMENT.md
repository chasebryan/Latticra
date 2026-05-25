# Lat-to-LIR Clause Metadata Refinement

Status: initial no-effect implementation

Scope: preserve Lat clause operator metadata in LIR nodes and expose first-clause lowering metadata in deterministic Lat-to-LIR reports.

## Purpose

This slice makes lowered Lat clause metadata more inspectable without changing Lat parsing, semantic validation, normalization, lowering classification, or execution behavior.

Before this refinement, clause nodes preserved clause name, value, role, source span, owner relationship, and node kind. This slice adds a dedicated LIR node `operator_text` field and records the first lowered clause in the Lat-to-LIR result/report surface.

## Added Metadata

LIR nodes now carry:

```text
operator_text
```

Lat-to-LIR lowering writes clause operators into that field for:

```text
field clauses
require clauses
ensure clauses
effect clauses
```

The Lat-to-LIR result/report now also records:

```text
first_clause_node_index
first_clause_role
first_clause_effect
first_clause_name
first_clause_operator
first_clause_value
```

## Behavior

The refinement preserves existing mapping behavior:

```text
Lat clause name  -> LIR node name
Lat clause value -> LIR node value
Lat clause role  -> LIR node binding
Lat operator     -> LIR node operator_text
```

For example:

```text
require risk != "high"
```

lowers into a Lat requirement node with:

```text
name=risk
operator_text=!=
value=high
binding=require
```

## Validation

Run:

```sh
sh scripts/test-lat-to-lir-clause-metadata-refinement.sh
sh scripts/test-lat-to-lir-lowering.sh
```

The focused guard verifies field, requirement, and effect clause operator metadata plus first-clause report fields.

The Lat-to-LIR diagnostic refinement also copies these first-clause fields into its diagnostic result/report so operator metadata remains visible from the diagnostic layer.

## Boundary

This is metadata-only. It does not execute Lat, interpret requirements, evaluate operators, execute LIR, perform effects, mutate state, perform file I/O, perform network I/O, call runtime behavior, or grant authority.

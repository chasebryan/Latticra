# Latticra LIR Report Refinement

Status: initial LIR report refinement implementation
Scope: deterministic LIR report classification, graph shape labeling, edge-kind summary counts, no-effect-chain reporting, evidence-level reporting, invariant tests, guard coverage, and workflow coverage.

## Purpose

This document records the LIR report refinement after the Lat semantic diagnostics refinement.

The goal is to make LIR reports easier to audit by stating whether a graph was materialized, rejected, invalid, or empty, which graph shape is present, and how edge kinds are distributed.

This refinement does not execute LIR, compile Lat, interpret Lat, mutate state, perform I/O, or provide runtime behavior.

## Added LIR report metadata

The LIR module now records:

```text
report_classification
shape_kind
contains_edge_count
binds_edge_count
annotates_edge_count
orders_before_edge_count
transitions_from_edge_count
no_effect_chain_ok
evidence_level
```

The deterministic `LATTICRA LIR REPORT` now emits those fields.

## Report classifications

Initial report classifications:

```text
empty
materialized
rejected
invalid
```

## Shape kinds

Initial shape kinds:

```text
unknown
l-ui-card-graph
lat-module-graph
internal-fixture-graph
```

## Edge summary counts

The LIR report now records counts by edge kind:

```text
contains_edge_count
binds_edge_count
annotates_edge_count
orders_before_edge_count
transitions_from_edge_count
```

These counts are derived from the existing edge array; they do not change the graph.

## Evidence level

The LIR report uses a small deterministic evidence label:

```text
0 -> invalid or empty report evidence
1 -> rejected report evidence or materialized graph with no-effect-chain concern
2 -> materialized no-effect graph evidence
```

This is a project-internal evidence label, not a certification, production-readiness claim, or security guarantee.

## Validation

Run:

```sh
sh scripts/test-lir-report-refinement.sh
sh scripts/test-lir-shape.sh
```

The focused invariant tests verify:

```text
lir_report_refinement_labels_are_stable
lir_report_refinement_reports_materialized_l_ui_shape
lir_report_refinement_reports_semantic_rejection
lir_report_refinement_report_is_deterministic
```

## Compatibility

This refinement preserves existing LIR behavior for:

```text
L-UI AST lowering
Lat-to-LIR lowering
node counts
edge counts
binding counts
text counts
binding resolution
source spans
no-effect flags
small-buffer behavior
semantic-failure behavior
```

## Non-claims

This report refinement does not provide:

```text
LIR execution
Lat execution
Lat compilation
Lat interpretation
runtime behavior
command execution
state mutation
file I/O
network I/O
server interaction
hardware behavior
terminal control
security isolation
sandboxing
malware prevention
ransomware prevention
certification
accreditation
operating-system completeness
```

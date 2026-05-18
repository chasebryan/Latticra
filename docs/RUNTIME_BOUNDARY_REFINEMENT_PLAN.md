# Latticra Runtime Boundary Refinement Plan

Status: refinement planning contract
Scope: planning-only refinement for integrating Lat pipeline and Lat-specific LIR metadata into the no-effect runtime boundary classification/report surface.

## Purpose

This document defines the next runtime boundary refinement before any new runtime behavior is added.

The current runtime boundary already classifies no-effect report, validation, and classification requests while preserving disabled-by-default operational behavior. The next refinement should make the boundary aware of the newer Lat pipeline and Lat-specific LIR metadata surfaces without promoting execution, mutation, command behavior, file I/O, network I/O, recovery, hardware, boot, or operating-system claims.

## Relationship to current work

This plan depends on:

```text
docs/RUNTIME_BOUNDARY_CONTRACT.md
docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md
docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
docs/LAT_PIPELINE_CONTRACT.md
docs/LAT_PIPELINE_IMPLEMENTATION_PLAN.md
docs/LAT_PIPELINE_IMPLEMENTATION.md
docs/LAT_SPECIFIC_LIR_REFINEMENT_CONTRACT.md
docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION_PLAN.md
docs/LAT_SPECIFIC_LIR_REFINEMENT_IMPLEMENTATION.md
include/latticra/runtime_boundary.h
include/latticra/lat_pipeline.h
include/latticra/lat_to_lir.h
include/latticra/lir.h
```

## Refinement goal

The refinement should let runtime-boundary records and reports summarize the newer Lat pipeline chain:

```text
Lat parser metadata
Lat semantic metadata
Lat-to-LIR lowering metadata
Lat-specific LIR metadata
Lat pipeline aggregate metadata
```

The runtime boundary should remain a classifier and reporter, not an executor.

## Planned metadata additions

A future implementation slice may add report fields for:

```text
lat_pipeline_status
lat_pipeline_error
lat_pipeline_semantic_valid
lat_pipeline_source_len
lat_pipeline_node_count
lat_pipeline_edge_count
lat_lir_source_kind
lat_lir_module_node_count
lat_lir_transition_edge_count
lat_lir_has_lat_state_nodes
lat_lir_has_lat_transition_nodes
lat_lir_has_transition_source_edges
```

The exact names may be adjusted during implementation, but the implementation must stay deterministic, bounded, and no-effect.

## Planned request handling

The next implementation slice may add or refine no-effect request classification for:

```text
Lat pipeline report validation
Lat-specific LIR metadata validation
Runtime boundary report over Lat pipeline evidence
```

Any operational request remains denied or future-gated.

## Planned tests

The implementation slice should add focused tests for:

```text
runtime_boundary_reports_lat_pipeline_status
runtime_boundary_denies_failed_lat_pipeline_metadata
runtime_boundary_allows_valid_lat_pipeline_metadata_in_report_mode
runtime_boundary_reports_lat_specific_lir_node_evidence
runtime_boundary_reports_transition_source_edge_evidence
runtime_boundary_preserves_no_effect_for_lat_pipeline_evidence
runtime_boundary_keeps_lat_and_lir_execute_future_gated
runtime_boundary_refinement_report_is_deterministic
runtime_boundary_refinement_rejects_small_buffer
```

## Compatibility expectations

The refinement must not change existing behavior for:

```text
unknown request denial
unknown effect denial
operator confirmation non-override behavior
future-gated operational requests
existing Lat validation prerequisites
existing LIR validation prerequisites
existing render report prerequisites
existing Nucleus task report prerequisites
existing runtime report fields
existing small-buffer behavior
```

## Status and evidence rule

This plan is not implementation evidence by itself. It permits the next implementation slice to add bounded API/report fields and focused tests. Status percentages may only increase modestly from this planning milestone and should increase more substantially only after implementation and CI evidence merge.

## Non-claims

This plan does not implement runtime behavior, command execution, Lat execution, LIR execution, task effect execution, live movement, state mutation, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware support, boot behavior, terminal control, security isolation, sandboxing, malware prevention, ransomware prevention, certification, accreditation, or operating-system completeness.

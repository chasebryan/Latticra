# Lat Model Normalization Implementation

Status: initial no-effect implementation

Scope: bounded Lat / Latticra Language model normalization after grammar parsing and semantic validation, before LIR lowering, execution, runtime behavior, or operating-system behavior.

## Purpose

This slice adds a normalized Lat module model between semantic validation and Lat-to-LIR lowering.

The model consumes only bounded parser and semantic metadata. It builds deterministic declaration and clause tables for states, policies, transitions, assertions, and effect declarations while preserving source spans and no-effect flags.

It does not read source bytes, execute Lat, interpret transitions, lower to LIR, execute LIR, mutate state, perform file I/O, perform network I/O, call recovery behavior, touch hardware, or grant runtime authority.

## Implementation Files

```text
include/latticra/lat_model.h
src/lat_model.c
tests/lat_model_normalization_invariants.c
scripts/test-lat-model-normalization.sh
.github/workflows/lat-model-normalization.yml
```

## Public API

The public API adds:

```text
latticra_lat_model_error_t
latticra_lat_model_clause_role_t
latticra_lat_model_declaration_t
latticra_lat_model_clause_t
latticra_lat_model_t
latticra_lat_model_error_label
latticra_lat_model_clause_role_label
latticra_lat_model_normalize_module
latticra_lat_model_report
```

## Normalized Tables

The model preserves the parser declaration order and adds typed index tables:

```text
state_indices
policy_indices
transition_indices
assertion_indices
effect_indices
```

Transition declarations also carry a resolved source-state declaration index.

Clauses are normalized into stable roles:

```text
field
require
ensure
effect
```

Each clause records its owner declaration index, owner declaration kind, name, operator text, value, effect metadata, and source span.

## Report Format

`latticra_lat_model_report` emits a deterministic bounded report beginning with:

```text
LAT MODEL NORMALIZATION REPORT
```

and including:

```text
status
error
module
declaration_count
state_count
policy_count
transition_count
assertion_count
effect_count
clause_count
first_state_index
first_policy_index
first_transition_index
first_transition_source_index
first_assertion_index
first_effect_index
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
source span fields
```

Small output buffers return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the output buffer when possible.

## Validation

Run:

```sh
sh scripts/test-lat-model-normalization.sh
sh scripts/test-lat-pipeline.sh
```

The invariants verify:

```text
lat_model_labels_are_stable
lat_model_normalizes_foundation_counts
lat_model_builds_typed_declaration_indices
lat_model_builds_clause_roles_and_owners
lat_model_rejects_parse_failure
lat_model_rejects_semantic_failure
lat_model_preserves_no_effect_flags
lat_model_report_is_deterministic
lat_model_report_rejects_small_buffer
```

The Lat pipeline now also calls `latticra_lat_model_normalize_module` internally. Callers that need the normalized model can use `latticra_lat_pipeline_run_source_with_model`; existing callers can continue using `latticra_lat_pipeline_run_source`.

Lat-to-LIR lowering now has a model-aware entry point, `latticra_lir_lower_lat_model`, that consumes this normalized model directly. The older `latticra_lir_lower_lat_module` entry point remains available and normalizes a local model before lowering.

## Non-Claims

This implementation does not provide Lat execution, Lat compilation, Lat interpretation, LIR execution, runtime behavior, command execution, mutation, file I/O, network I/O, recovery behavior, hardware behavior, sandboxing, malware prevention, ransomware prevention, certification, accreditation, or operating-system completeness.

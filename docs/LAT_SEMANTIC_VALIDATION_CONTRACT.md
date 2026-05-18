# Latticra Lat Semantic Validation Contract

Status: semantic validation contract proposal
Scope: semantic validation after bounded Lat grammar parsing and before Lat-to-LIR lowering, execution, runtime behavior, or operating-system behavior.

## Purpose

This contract defines the first semantic validation layer for Lat / Latticra Language.

The layer consumes a successful `latticra_lat_parse_result_t` and validates declaration identity, cross-declaration references, state-field vocabulary, effect metadata, clause shapes, no-effect preservation, and deterministic report behavior.

This contract does not execute Lat, compile Lat, interpret Lat, lower Lat to LIR, render L-UI, call Nucleus, mutate state, read files, write files, open network connections, call server code, call update code, call recovery code, or touch hardware.

## Relationship to previous work

This contract depends on:

```text
docs/LAT_LANGUAGE_GRAMMAR_CONTRACT.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION_PLAN.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
docs/LANGUAGE_NAMING_POLICY.md
docs/LANGUAGE_STRATEGY.md
docs/EFFECT_GATES.md
docs/STATE_LATTICE.md
include/latticra/lat_parser.h
include/latticra/state_lattice.h
```

Those files remain the source of truth for naming, parser API, effect vocabulary, state-lattice vocabulary, and no-effect posture.

## Semantic validation target

The first target is:

```text
Lat-Core semantic validation
```

Lat-Core remains a declaration subset for state, policy, assertion, transition, and effect metadata.

Lat-Orch remains future work.

## Input contract

The validator accepts:

```text
const latticra_lat_parse_result_t *parse_result
```

The validator must reject or report semantic failure when:

```text
parse_result == NULL
parse_result->error != LATTICRA_LAT_PARSE_OK
```

The validator must not read source bytes directly. It trusts only bounded parser metadata and source spans already produced by the parser.

## Output contract

The validator produces:

```text
latticra_lat_semantic_result_t
```

The result records:

- status;
- summary semantic error;
- module name;
- semantic validity flag;
- diagnostic count;
- bounded diagnostics;
- declaration counts;
- no-effect flags.

## Stable semantic error labels

The first semantic error labels are:

```text
ok
null_argument
parse_not_ok
duplicate_declaration
unknown_transition_source
invalid_state_field
invalid_require_left
invalid_effect_target
invalid_effect_value
effect_requires_gate
invalid_clause_for_declaration
empty_declaration
no_effect_violation
capacity_exceeded
internal_error
```

## Declaration identity rule

Declaration names must be globally unique inside one Lat module for this slice.

This prevents ambiguity before namespace, import, or qualified-name contracts exist.

## State semantic rule

A `state` declaration may contain only field assignment clauses.

Allowed state fields:

```text
origin
route
axis
path
breadcrumb
trace
safe_portal
rollback
health
risk
lock
dark_phase
host_effect
external_effect
```

The fields `host_effect` and `external_effect` must use known Lat effect values. This first semantic validation slice accepts only:

```text
none
```

as a declared effect value.

## Policy semantic rule

A `policy` declaration may contain only:

```text
require
ensure
```

clauses.

A policy must not assign fields or declare direct effects in this slice.

## Transition semantic rule

A `transition` declaration must resolve its `from <StateName>` reference to a declared `state`.

Transition clauses may be:

```text
require left operator right
effect host = none
effect external = none
```

Unknown effect targets are rejected.

Any non-`none` declared effect value is rejected until a later effect-gate contract promotes it.

## Assertion semantic rule

An `assertion` declaration may contain only:

```text
require
ensure
```

clauses.

Assertions are metadata checks only.

## Effect declaration semantic rule

An `effect` declaration may assign known effect targets:

```text
host
external
local
network
hardware
boot
recovery
```

Values must be known Lat effect labels. This first slice accepts only `none` as a declared effect value.

## No-effect preservation

The semantic validator must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

If the input parse result violates these flags, semantic validation must report `no_effect_violation`.

## Report format

`latticra_lat_semantic_report` emits a deterministic bounded report beginning with:

```text
LAT SEMANTIC REPORT
```

The report includes:

```text
status
error
semantic_valid
module
declaration_count
state_count
policy_count
transition_count
assertion_count
effect_count
diagnostic_count
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
first_diagnostic_error
first_diagnostic_name
first_diagnostic_detail
span_start_offset
span_end_offset
span_start_line
span_start_column
span_end_line
span_end_column
```

Small output buffers must return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the buffer when possible.

## Exact implementation files

The implementation slice should add:

```text
include/latticra/lat_semantic.h
src/lat_semantic.c
tests/lat_semantic_validation_invariants.c
scripts/test-lat-semantic-validation.sh
fixtures/lat/foundation_model.lat
docs/LAT_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md
```

and update the C workflow to run the semantic validation test after grammar parser tests.

## Required tests

The implementation must include tests for:

```text
lat_semantic_accepts_foundation_model
lat_semantic_rejects_parse_error
lat_semantic_rejects_duplicate_declaration
lat_semantic_rejects_unknown_transition_source
lat_semantic_rejects_invalid_state_field
lat_semantic_rejects_invalid_policy_field_assignment
lat_semantic_rejects_invalid_effect_target
lat_semantic_rejects_invalid_effect_value
lat_semantic_rejects_effect_requiring_gate
lat_semantic_preserves_no_effect_flags
lat_semantic_reports_are_deterministic
lat_semantic_report_rejects_small_buffer
lat_semantic_error_labels_are_stable
lat_semantic_is_deterministic
```

## Forbidden behavior

Lat semantic validation must not:

- claim plain `L` as the public language name;
- claim `.l` as the canonical source extension;
- parse source text directly;
- execute declarations;
- mutate state;
- lower to LIR;
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
- imply a compiler, interpreter, runtime, package manager, sandbox, or operating-system surface.

## Non-claims

This contract does not implement Lat execution, Lat compilation, Lat interpretation, LIR lowering, L-UI rendering, command behavior, Nucleus task handling, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

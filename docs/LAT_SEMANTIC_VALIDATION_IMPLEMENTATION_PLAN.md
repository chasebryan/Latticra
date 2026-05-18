# Latticra Lat Semantic Validation Implementation Plan

Status: implementation planning contract proposal
Scope: exact public API, result structs, diagnostics, validation rules, report surface, fixture, tests, compatibility expectations, and non-claims before semantic validation code.

## Purpose

This document defines the implementation plan for the first Lat / Latticra Language semantic validation layer.

The existing Lat grammar parser records bounded module, declaration, clause, effect, source-span, and no-effect metadata. The semantic validator will consume that parser result and validate module coherence without executing Lat or lowering it to LIR.

## Implementation language decision

The first Lat semantic validator should be implemented in C.

Reason:

- current parser and state-lattice foundations are C;
- validation must remain bounded, deterministic, and no-effect;
- this layer should be usable before constrained C++ authority code grows around it;
- tests and runners already use C and POSIX shell.

## Implementation files

Add:

```text
include/latticra/lat_semantic.h
src/lat_semantic.c
tests/lat_semantic_validation_invariants.c
scripts/test-lat-semantic-validation.sh
fixtures/lat/foundation_model.lat
```

Update:

```text
.github/workflows/c.yml
docs/FOUNDATION_INDEX.md
README.md
STATUS.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
```

## Public API shape

Add public API names:

```text
latticra_lat_semantic_error_t
latticra_lat_semantic_diagnostic_t
latticra_lat_semantic_result_t
latticra_lat_semantic_error_label
latticra_lat_validate_module
latticra_lat_semantic_report
```

Recommended function signatures:

```text
const char *latticra_lat_semantic_error_label(latticra_lat_semantic_error_t error);

latticra_status_t latticra_lat_validate_module(
    const latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *result);

latticra_status_t latticra_lat_semantic_report(
    const latticra_lat_semantic_result_t *result,
    char *buffer,
    size_t buffer_len);
```

## Capacity constants

Add bounded constants:

```text
LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_MAX 32u
LATTICRA_LAT_SEMANTIC_REPORT_MAX 4096u
```

## Semantic error enum

Add semantic error enum values:

```text
LATTICRA_LAT_SEMANTIC_OK
LATTICRA_LAT_SEMANTIC_NULL_ARGUMENT
LATTICRA_LAT_SEMANTIC_PARSE_NOT_OK
LATTICRA_LAT_SEMANTIC_DUPLICATE_DECLARATION
LATTICRA_LAT_SEMANTIC_UNKNOWN_TRANSITION_SOURCE
LATTICRA_LAT_SEMANTIC_INVALID_STATE_FIELD
LATTICRA_LAT_SEMANTIC_INVALID_REQUIRE_LEFT
LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_TARGET
LATTICRA_LAT_SEMANTIC_INVALID_EFFECT_VALUE
LATTICRA_LAT_SEMANTIC_EFFECT_REQUIRES_GATE
LATTICRA_LAT_SEMANTIC_INVALID_CLAUSE_FOR_DECLARATION
LATTICRA_LAT_SEMANTIC_EMPTY_DECLARATION
LATTICRA_LAT_SEMANTIC_NO_EFFECT_VIOLATION
LATTICRA_LAT_SEMANTIC_CAPACITY_EXCEEDED
LATTICRA_LAT_SEMANTIC_INTERNAL_ERROR
```

Stable labels:

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

## Diagnostic struct

Add diagnostic metadata fields:

```text
latticra_lat_semantic_error_t error;
latticra_lat_source_span_t span;
size_t declaration_index;
size_t clause_index;
char name[LATTICRA_LAT_NAME_MAX];
char detail[LATTICRA_LAT_VALUE_MAX];
```

## Result struct

Add result metadata fields:

```text
latticra_status_t status;
latticra_lat_semantic_error_t error;
latticra_lat_source_span_t span;
char module_name[LATTICRA_LAT_NAME_MAX];
int semantic_valid;
size_t diagnostic_count;
latticra_lat_semantic_diagnostic_t diagnostics[LATTICRA_LAT_SEMANTIC_DIAGNOSTIC_MAX];
size_t declaration_count;
size_t state_count;
size_t policy_count;
size_t transition_count;
size_t assertion_count;
size_t effect_count;
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

## Validation algorithm

1. Initialize output deterministically.
2. Reject null arguments with `LATTICRA_STATUS_NULL_ARGUMENT`.
3. Copy module and count metadata from the parser result when available.
4. If parser error is not `ok`, record `parse_not_ok` and stop.
5. Verify no-effect flags.
6. Detect duplicate declaration names.
7. For each declaration:
   - reject empty declarations;
   - validate declaration-specific clause forms;
   - validate known state fields;
   - validate known effect targets;
   - validate known effect values;
   - reject non-`none` declared effects in this first slice;
   - resolve transition source state names.
8. Set `semantic_valid=1` only when no diagnostics exist.
9. Emit deterministic bounded reports.

## Fixture

Add:

```text
fixtures/lat/foundation_model.lat
```

Recommended content:

```text
lat module FoundationModule {
  state RootCell {
    origin = "0/0"
    route = "ROOT"
    axis = "ROOT"
    path = "/"
    health = "ok"
    risk = "low"
    lock = "open"
    host_effect = none
    external_effect = none
  }

  effect PreviewOnly {
    host = none
    external = none
    network = none
    hardware = none
  }

  policy SafePreview {
    require risk != "high"
    require lock == "open"
    ensure host_effect == none
    ensure external_effect == none
  }

  transition MoveRight from RootCell {
    require lock == "open"
    effect host = none
    effect external = none
  }

  assertion RootCellIsSafe {
    require health == "ok"
    require host_effect == none
    require external_effect == none
  }
}
```

## Exact test list

Add invariant tests for:

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

## Test command

Add:

```sh
sh scripts/test-lat-semantic-validation.sh
```

Compile with:

```text
-std=c99 -Wall -Wextra -Werror -pedantic
```

and include:

```text
src/lat_parser.c
src/lat_semantic.c
tests/lat_semantic_validation_invariants.c
```

## Compatibility expectations

This implementation must not change:

```text
language naming policy
.lat canonical extension
C/C++ foundation direction
Lat grammar parser behavior
L-UI parser behavior
L-UI semantic validation behavior
LIR shape behavior
state lattice behavior
Nucleus preview behavior
literal source-buffer NUL rejection
no-effect flags
```

## Non-claims

This implementation plan does not implement Lat execution, Lat compilation, Lat interpretation, LIR lowering, L-UI rendering, command behavior, Nucleus task handling, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

# Latticra L-UI Rendering Contract

Status: L-UI rendering contract
Scope: first operator-visible L-UI rendering boundary before renderer implementation, terminal UI behavior, interactive UI behavior, command behavior, execution, mutation, networking, recovery, hardware behavior, or production UI claims.

## Purpose

This document defines the first contract for L-UI rendering in Latticra.

L-UI rendering means turning already validated L-UI/LIR metadata into deterministic operator-visible text output.

This document does not implement L-UI rendering.

The future implementation plan should be recorded in:

```text
L_UI_RENDERING_IMPLEMENTATION_PLAN.md
```

## Relationship to previous work

This contract depends on:

```text
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md
docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md
docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md
docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md
docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
include/latticra/lir.h
include/latticra/cpp/authority.hpp
src/l_ui_parser_ast.c
src/l_ui_parser_semantic.c
src/lir.c
src/cpp/authority.cpp
```

Those files remain the source of truth for L-UI AST shape, source-backed text, length-carrying strings, escaped decoded NUL handling, literal source-buffer NUL rejection, semantic validation, LIR shape, constrained C++ authority validation, and no-effect boundaries.

## Rendering role

L-UI rendering should be a deterministic presentation layer over validated metadata.

Recommended future pipeline:

```text
source bytes
  -> structural parser
  -> AST construction
  -> semantic validation
  -> LIR lowering
  -> constrained authority validation
  -> L-UI rendering
  -> operator-visible text output
```

Rendering must not bypass parser, semantic validation, LIR shape, or authority-layer checks.

## First rendering unit

The first renderer should render one validated L-UI card or one validated LIR module.

Suggested future root object:

```text
latticra_l_ui_render_result_t
```

Suggested future input object:

```text
latticra_l_ui_render_request_t
```

Initial rendered unit labels:

```text
card
rail
field
text
binding
effect
boundary
source_span
authority
```

## Input prerequisites

Rendering may only operate after the input metadata is valid:

```text
parser_error=ok
semantic_error=ok
lir_error=ok
authority_status=ok
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

If parsing, semantic validation, LIR lowering, or authority validation failed, rendering should return a bounded failure report instead of rendering a partial operator surface.

## Render modes

Initial render modes should be explicit and bounded.

Suggested render modes:

```text
summary
detailed
diagnostics_only
authority_only
```

The first implementation plan must choose exact enum names.

Render modes must not imply interactive UI, live terminal control, command execution, or event handling.

## Output target

The first renderer should write into caller-provided buffers only.

Suggested output behavior:

```text
caller-provided char buffer
explicit buffer length
NUL-terminated on success
cleared on too-small failure
no heap allocation
no file output
no terminal escape control by default
```

The first renderer should not write directly to stdout, stderr, files, terminals, sockets, servers, logs, or devices.

## Rendered report model

A future rendered report should be deterministic and bounded.

Suggested report header:

```text
LATTICRA L-UI RENDER REPORT
status=<status-label>
mode=<render-mode-label>
card=<card-name>
effect=<effect-label>
boundary=<boundary-label>
rail_count=<count>
field_count=<count>
text_count=<count>
binding_count=<count>
node_count=<count>
edge_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
```

Detailed output may include rail, field, text, binding, LIR node, and authority sections, but only as text metadata.

## Suggested section order

Detailed rendering should use stable section order:

```text
HEADER
CARD
AUTHORITY
RAILS
FIELDS
TEXT
BINDINGS
LIR
SOURCE_SPANS
NO_EFFECT_FLAGS
```

The order must be deterministic across repeated runs.

## Rail rendering

Rail rendering should preserve validated rail order from AST/LIR metadata.

Rail output should include:

```text
rail index
rail name
field count
text count
source span
```

The renderer must not invent rails or reorder them unless a future contract explicitly defines a display sort mode.

## Field and binding rendering

Field rendering should preserve validated field metadata.

Field output should include:

```text
field index
field name
binding target
binding prefix
source span
binding source span
```

Bindings remain symbolic. Rendering must not evaluate state, preview values, host state, or runtime state.

## Text rendering

Text rendering must respect length-carrying storage.

Rules:

```text
value_len is authoritative
escaped output is used for operator-visible text
escaped decoded NUL through \x00 remains representable
literal source-buffer NUL remains rejected before rendering
raw C-string fields are not authoritative for embedded NUL values
```

Rendering must not drop embedded NUL metadata or silently truncate text.

## Source-span rendering

Source spans should be operator-visible where useful.

Suggested source-span fields:

```text
start_offset
end_offset
start_line
start_column
end_line
end_column
```

Rendering must not invent byte positions, line numbers, or column numbers.

## LIR rendering

LIR rendering should display LIR metadata only.

LIR output may include:

```text
source_kind
module_name
card_name
node_count
edge_count
binding_count
text_count
node kinds
edge kinds
binding refs
text refs
```

Rendering must not execute LIR, lower LIR into behavior, evaluate bindings, render an interactive UI, or call Nucleus task execution.

## Authority rendering

Authority rendering should display constrained C++ authority-layer report metadata only.

Authority output may include:

```text
authority status
authority validator
authority requested effect
authority denial reason
authority no-effect flags
```

Rendering authority metadata must not broaden authority, perform effects, or alter authority-layer state.

## Error model

Rendering should have a separate error space.

Recommended future labels:

```text
ok
null_argument
invalid_input
parser_failed
semantic_failed
lir_failed
authority_failed
capacity_exceeded
unsupported_render_mode
unsupported_effect
unsupported_boundary
internal_error
```

Exact enum names must be defined by a future implementation plan.

## Capacity policy

The first implementation should use fixed capacities and caller-owned buffers.

Suggested constants:

```text
LATTICRA_L_UI_RENDER_REPORT_MAX
LATTICRA_L_UI_RENDER_LINE_MAX
LATTICRA_L_UI_RENDER_SECTION_MAX
```

The implementation plan must name exact capacities before code is added.

Small output buffers should return a stable capacity error and clear the output buffer.

## No-effect rule

L-UI rendering is presentation-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Rendering must not execute commands, mutate state, evaluate host state, call Nucleus task execution, write files, read files, open network connections, call server code, call update code, call recovery code, or touch hardware.

## Compatibility expectations

L-UI rendering work must not change:

```text
existing parser behavior
existing parser diagnostic codes
existing AST construction behavior
existing detailed AST report behavior
existing escaped string report behavior
existing source-backed text behavior
existing length-carrying string behavior
existing decoded NUL acceptance
existing literal source-buffer NUL rejection
existing semantic validation behavior
existing LIR shape behavior
existing constrained C++ authority behavior
source-span byte offset behavior
no-effect flags
current accepted fixture counts
```

The first accepted fixture should still preserve:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Future implementation gate

L-UI rendering implementation must not begin until a separate implementation plan defines:

1. implementation language;
2. public API shape;
3. public header path;
4. source file path;
5. render request struct;
6. render result struct;
7. render mode enum;
8. render error enum;
9. capacity constants;
10. output buffer rules;
11. section order;
12. source-span rendering rules;
13. embedded NUL rendering rules;
14. authority metadata rendering rules;
15. exact tests;
16. compatibility expectations;
17. non-claims.

That plan should be recorded in:

```text
L_UI_RENDERING_IMPLEMENTATION_PLAN.md
```

## Future file policy

Recommended future files:

```text
include/latticra/l_ui_renderer.h
src/l_ui_renderer.c
tests/l_ui_rendering_invariants.c
scripts/test-l-ui-rendering.sh
docs/L_UI_RENDERING_IMPLEMENTATION_PLAN.md
docs/L_UI_RENDERING_IMPLEMENTATION.md
```

The implementation plan must confirm exact paths before renderer code is added.

## Future test list

A future implementation plan should include tests for:

```text
l_ui_rendering_accepts_semantically_valid_l_ui_fixture
l_ui_rendering_requires_semantic_success
l_ui_rendering_requires_lir_success
l_ui_rendering_requires_authority_success
l_ui_rendering_preserves_card_metadata
l_ui_rendering_preserves_rail_order
l_ui_rendering_preserves_field_bindings
l_ui_rendering_preserves_text_lengths
l_ui_rendering_preserves_escaped_x00_visibility
l_ui_rendering_preserves_source_spans
l_ui_rendering_preserves_no_effect_flags
l_ui_rendering_report_is_deterministic
l_ui_rendering_report_rejects_small_buffer
l_ui_rendering_does_not_change_ast_report
l_ui_rendering_does_not_change_lir_report
l_ui_rendering_does_not_execute_bindings
l_ui_rendering_does_not_call_nucleus_execution
l_ui_rendering_is_deterministic
```

## Forbidden behavior

L-UI rendering work must not:

- render parser-failed input as a valid surface;
- render semantic-failed input as a valid surface;
- render LIR-failed input as a valid surface;
- bypass constrained authority validation;
- execute bindings;
- evaluate host state;
- evaluate runtime state;
- call Nucleus task execution;
- execute Lat;
- execute LIR;
- mutate state;
- write files;
- read files;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- emit terminal escape control by default;
- create an interactive UI loop;
- broaden accepted syntax;
- weaken parser diagnostics;
- weaken semantic validation;
- weaken LIR validation;
- weaken constrained C++ authority validation;
- accept literal source-buffer NUL;
- remove escaped decoded NUL support;
- make raw C-string fields authoritative for embedded NUL values;
- imply a production UI, runtime, sandbox, malware prevention, ransomware prevention, or operating-system surface.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-rendering-contract.sh
```

The guard is static. It does not implement L-UI rendering.

## Non-claims

This document does not implement L-UI rendering, interactive UI behavior, terminal control, command behavior, Lat execution, LIR execution, Nucleus task execution, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

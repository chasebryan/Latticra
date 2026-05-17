# Latticra L-UI Rendering Implementation Plan

Status: implementation planning contract
Scope: exact public API, renderer files, render request/result structs, render mode enum, render error enum, capacity constants, output-buffer behavior, section order, source-span rendering, embedded-NUL rendering, authority metadata rendering, tests, compatibility expectations, and non-claims before L-UI renderer code.

## Purpose

This document defines the implementation plan for the first L-UI renderer.

The L-UI rendering contract is already merged and guarded. This plan turns that contract into exact public API, file paths, data structures, capacity constants, render modes, error labels, report format, output-buffer rules, authority metadata handling, tests, compatibility expectations, and non-claims required before renderer code is added.

This document does not implement L-UI rendering.

## Relationship to previous work

This plan depends on:

```text
docs/L_UI_RENDERING_CONTRACT.md
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

Those files remain the source of truth for parser behavior, AST shape, source-backed text, length-carrying strings, escaped decoded NUL handling, literal source-buffer NUL rejection, semantic validation, LIR shape, constrained C++ authority validation, and no-effect boundaries.

## Implementation language decision

The first L-UI renderer should be implemented in C.

Reason:

- L-UI parser, AST, semantic validation, detailed reports, and LIR shape are C;
- C remains the secure substrate;
- renderer output should be deterministic and bounded;
- renderer code should use caller-provided buffers and avoid heap allocation;
- the C++ authority layer remains a validation/report dependency, not the rendering substrate.

The renderer may consume authority metadata through a small C-compatible authority summary struct or a pre-rendered authority report snapshot. It should not include or require C++ object lifetime in the public C renderer API.

## Implementation files

The implementation PR should add or modify:

```text
include/latticra/l_ui_renderer.h
src/l_ui_renderer.c
tests/l_ui_rendering_invariants.c
scripts/test-l-ui-rendering.sh
.github/workflows/c.yml
docs/L_UI_RENDERING_IMPLEMENTATION.md
```

The implementation PR should not add interactive UI behavior, terminal control, command behavior, Lat execution, LIR execution, Nucleus task execution, file I/O, network I/O, state mutation, recovery behavior, update behavior, server interaction, hardware behavior, or security guarantees.

## Public API shape

Add public API names:

```text
latticra_l_ui_render_error_t
latticra_l_ui_render_mode_t
latticra_l_ui_render_authority_summary_t
latticra_l_ui_render_request_t
latticra_l_ui_render_result_t
latticra_l_ui_render_error_label
latticra_l_ui_render_mode_label
latticra_l_ui_render
latticra_l_ui_render_report
```

Recommended function signatures:

```text
const char *latticra_l_ui_render_error_label(latticra_l_ui_render_error_t error);
const char *latticra_l_ui_render_mode_label(latticra_l_ui_render_mode_t mode);

latticra_status_t latticra_l_ui_render(
    const latticra_l_ui_render_request_t *request,
    latticra_l_ui_render_result_t *result);

latticra_status_t latticra_l_ui_render_report(
    const latticra_l_ui_render_result_t *result,
    char *buffer,
    size_t buffer_len);
```

The first renderer should generate metadata reports only.

## Capacity constants

Add exact bounded constants:

```text
LATTICRA_L_UI_RENDER_LABEL_MAX 64u
LATTICRA_L_UI_RENDER_REASON_MAX 128u
LATTICRA_L_UI_RENDER_REPORT_MAX 16384u
LATTICRA_L_UI_RENDER_LINE_MAX 512u
LATTICRA_L_UI_RENDER_SECTION_MAX 16u
LATTICRA_L_UI_RENDER_AUTHORITY_REPORT_MAX 4096u
```

The first implementation must reject or report capacity failures deterministically. It must not silently truncate semantically meaningful fields.

## Render error enum

Add render error enum values:

```text
LATTICRA_L_UI_RENDER_OK
LATTICRA_L_UI_RENDER_NULL_ARGUMENT
LATTICRA_L_UI_RENDER_INVALID_INPUT
LATTICRA_L_UI_RENDER_PARSER_FAILED
LATTICRA_L_UI_RENDER_SEMANTIC_FAILED
LATTICRA_L_UI_RENDER_LIR_FAILED
LATTICRA_L_UI_RENDER_AUTHORITY_FAILED
LATTICRA_L_UI_RENDER_CAPACITY_EXCEEDED
LATTICRA_L_UI_RENDER_UNSUPPORTED_RENDER_MODE
LATTICRA_L_UI_RENDER_UNSUPPORTED_EFFECT
LATTICRA_L_UI_RENDER_UNSUPPORTED_BOUNDARY
LATTICRA_L_UI_RENDER_INTERNAL_ERROR
```

Stable labels:

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

## Render mode enum

Add render mode enum values:

```text
LATTICRA_L_UI_RENDER_MODE_SUMMARY
LATTICRA_L_UI_RENDER_MODE_DETAILED
LATTICRA_L_UI_RENDER_MODE_DIAGNOSTICS_ONLY
LATTICRA_L_UI_RENDER_MODE_AUTHORITY_ONLY
```

Stable labels:

```text
summary
detailed
diagnostics_only
authority_only
```

Render modes are presentation choices only. They must not imply interaction, command execution, live terminal control, or event handling.

## Authority summary struct

Add a C-compatible authority summary struct:

```text
latticra_status_t status;
char status_label[LATTICRA_L_UI_RENDER_LABEL_MAX];
char validator_label[LATTICRA_L_UI_RENDER_LABEL_MAX];
char requested_effect_label[LATTICRA_L_UI_RENDER_LABEL_MAX];
char denial_reason[LATTICRA_L_UI_RENDER_REASON_MAX];
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

This struct lets the C renderer display authority metadata without owning C++ objects or exposing C++ object lifetimes through a C ABI.

The first implementation may use a helper in tests to populate this struct from known good authority metadata, but renderer code must remain C.

## Render request struct

Add request fields:

```text
latticra_l_ui_render_mode_t mode;
const latticra_l_ui_ast_result_t *ast;
const latticra_l_ui_semantic_result_t *semantic;
const latticra_lir_module_t *lir;
const latticra_l_ui_render_authority_summary_t *authority;
```

The renderer must not retain pointers from the request after the call returns.

## Render result struct

Add result fields:

```text
latticra_status_t status;
latticra_l_ui_render_error_t error;
latticra_l_ui_render_mode_t mode;
char card_name[LATTICRA_L_UI_RENDER_LABEL_MAX];
char effect[LATTICRA_L_UI_RENDER_LABEL_MAX];
char boundary[LATTICRA_L_UI_RENDER_LABEL_MAX];
size_t rail_count;
size_t field_count;
size_t text_count;
size_t binding_count;
size_t node_count;
size_t edge_count;
size_t section_count;
latticra_l_ui_source_span_t span;
latticra_l_ui_render_authority_summary_t authority;
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

The result must be fully initialized on success and failure.

## Input prerequisite behavior

Rendering may succeed only when:

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

Failure behavior:

```text
parser failure -> LATTICRA_L_UI_RENDER_PARSER_FAILED
semantic failure -> LATTICRA_L_UI_RENDER_SEMANTIC_FAILED
LIR failure -> LATTICRA_L_UI_RENDER_LIR_FAILED
authority failure -> LATTICRA_L_UI_RENDER_AUTHORITY_FAILED
non-no-effect flags -> LATTICRA_L_UI_RENDER_AUTHORITY_FAILED
unsupported mode -> LATTICRA_L_UI_RENDER_UNSUPPORTED_RENDER_MODE
unsupported effect -> LATTICRA_L_UI_RENDER_UNSUPPORTED_EFFECT
unsupported boundary -> LATTICRA_L_UI_RENDER_UNSUPPORTED_BOUNDARY
```

The renderer must not produce a valid surface from invalid inputs.

## Output buffer rules

`latticra_l_ui_render_report` should:

```text
write only to caller-provided buffers
require explicit buffer length
NUL-terminate on success
clear the buffer on too-small failure
return LATTICRA_STATUS_BUFFER_TOO_SMALL for small buffers
avoid heap allocation
avoid file output
avoid stdout
avoid stderr
avoid terminal escape control
```

The renderer must not write directly to files, terminals, sockets, servers, logs, or devices.

## Report format

`latticra_l_ui_render_report` should emit:

```text
LATTICRA L-UI RENDER REPORT
status=<integer-status>
error=<render-error-label>
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
section_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
authority_status=<authority-status-label>
authority_validator=<authority-validator-label>
authority_requested_effect=<authority-effect-label>
authority_denial_reason=<authority-denial-reason>
span_start_offset=<offset>
span_end_offset=<offset>
span_start_line=<line>
span_start_column=<column>
span_end_line=<line>
span_end_column=<column>
```

Summary mode may stop at the metadata header.

Detailed mode should add deterministic sections in the section order below.

## Section order

Detailed rendering must use this section order:

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

The renderer must produce deterministic section order across repeated runs.

## Rail rendering rules

Rail rendering should preserve validated rail order.

Detailed output should include:

```text
rail[<index>].name=<rail-name>
rail[<index>].field_count=<count>
rail[<index>].text_count=<count>
rail[<index>].span_start_offset=<offset>
rail[<index>].span_end_offset=<offset>
```

The renderer must not invent rails or reorder rails.

## Field and binding rendering rules

Field output should preserve validated field metadata:

```text
field[<index>].name=<field-name>
field[<index>].binding=<binding-target>
field[<index>].binding_prefix=<binding-prefix>
field[<index>].span_start_offset=<offset>
field[<index>].binding_span_start_offset=<offset>
```

Bindings remain symbolic. Rendering must not evaluate state, preview values, host state, runtime state, or environment state.

## Text rendering rules

Text rendering must respect length-carrying storage.

Rules:

```text
value_len is authoritative
escaped output is used for operator-visible text
escaped decoded NUL through \x00 remains visible
literal source-buffer NUL remains rejected before rendering
raw C-string fields are not authoritative for embedded NUL values
```

Detailed output should include:

```text
text[<index>].value_len=<length>
text[<index>].escaped_value=<escaped-text>
text[<index>].span_start_offset=<offset>
text[<index>].span_end_offset=<offset>
```

Rendering must not silently drop or truncate embedded NUL metadata.

## Source-span rendering rules

Source-span output should use existing parser/AST/LIR spans.

Required fields:

```text
start_offset
end_offset
start_line
start_column
end_line
end_column
```

Rendering must not invent byte offsets, line numbers, or column numbers.

## LIR rendering rules

LIR rendering should display LIR metadata only.

Detailed LIR output may include:

```text
source_kind
module_name
card_name
node_count
edge_count
binding_count
text_count
node kind labels
edge kind labels
binding refs
text refs
```

Rendering must not execute LIR, lower LIR into behavior, evaluate bindings, render an interactive UI, or call Nucleus task execution.

## Authority metadata rendering rules

Authority rendering should display the C-compatible authority summary only.

Authority output may include:

```text
authority_status
authority_validator
authority_requested_effect
authority_denial_reason
authority no-effect flags
```

Rendering authority metadata must not broaden authority, perform effects, or alter authority-layer state.

## No-effect preservation

The renderer is presentation-only.

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

## Exact implementation test list

The implementation PR should include tests for:

```text
l_ui_rendering_accepts_semantically_valid_l_ui_fixture
l_ui_rendering_requires_semantic_success
l_ui_rendering_requires_lir_success
l_ui_rendering_requires_authority_success
l_ui_rendering_rejects_non_no_effect_flags
l_ui_rendering_preserves_card_metadata
l_ui_rendering_preserves_rail_order
l_ui_rendering_preserves_field_bindings
l_ui_rendering_preserves_text_lengths
l_ui_rendering_preserves_escaped_x00_visibility
l_ui_rendering_preserves_source_spans
l_ui_rendering_preserves_no_effect_flags
l_ui_rendering_report_is_deterministic
l_ui_rendering_report_rejects_small_buffer
l_ui_rendering_rejects_unsupported_mode
l_ui_rendering_does_not_change_ast_report
l_ui_rendering_does_not_change_lir_report
l_ui_rendering_does_not_execute_bindings
l_ui_rendering_does_not_call_nucleus_execution
l_ui_rendering_is_deterministic
```

## Test file plan

Add:

```text
tests/l_ui_rendering_invariants.c
scripts/test-l-ui-rendering.sh
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-l-ui-rendering-implementation-plan.sh
```

and before:

```text
sh scripts/test-l-ui-string-literal-escape-contract.sh
```

## Documentation update plan

The implementation PR should update:

```text
README.md
STATUS.md
docs/FOUNDATION_INDEX.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
docs/L_UI_RENDERING_CONTRACT.md
scripts/test-project-strategy-status-framework.sh
```

and add:

```text
docs/L_UI_RENDERING_IMPLEMENTATION.md
```

## Compatibility expectations

The implementation must not change:

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

## Forbidden implementation behavior

The first L-UI renderer implementation must not:

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

This implementation plan is guarded by:

```sh
sh scripts/test-l-ui-rendering-implementation-plan.sh
```

The guard is static. It does not implement L-UI rendering.

## Implementation gate

L-UI renderer implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement L-UI rendering, interactive UI behavior, terminal control, command behavior, Lat execution, LIR execution, Nucleus task execution, live movement, state mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

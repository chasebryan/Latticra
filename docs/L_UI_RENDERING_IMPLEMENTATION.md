# Latticra L-UI Rendering Implementation

Status: initial implementation contract
Scope: first no-effect C L-UI renderer API, bounded render result metadata, deterministic report output, semantic/LIR/authority prerequisites, source-span rendering, length-aware text rendering, compatibility expectations, validation, and non-claims.

## Purpose

This document records the first L-UI rendering implementation.

The implementation follows:

```text
docs/L_UI_RENDERING_CONTRACT.md
docs/L_UI_RENDERING_IMPLEMENTATION_PLAN.md
```

The renderer turns already validated L-UI/LIR metadata into deterministic operator-visible text output.

It is presentation-only.

## Implementation files

This slice adds:

```text
include/latticra/l_ui_renderer.h
src/l_ui_renderer.c
tests/l_ui_rendering_invariants.c
scripts/test-l-ui-rendering.sh
```

It also wires the renderer test into:

```text
.github/workflows/c.yml
```

## Public API

The public API is:

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

The API is C and uses caller-owned input/output structures.

## Capacity constants

The renderer defines:

```text
LATTICRA_L_UI_RENDER_LABEL_MAX 64u
LATTICRA_L_UI_RENDER_REASON_MAX 128u
LATTICRA_L_UI_RENDER_REPORT_MAX 16384u
LATTICRA_L_UI_RENDER_LINE_MAX 512u
LATTICRA_L_UI_RENDER_SECTION_MAX 16u
LATTICRA_L_UI_RENDER_AUTHORITY_REPORT_MAX 4096u
```

The renderer uses fixed-capacity fields and caller-provided report buffers.

## Render errors

Stable render error labels:

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

## Render modes

Supported render modes:

```text
summary
detailed
diagnostics_only
authority_only
```

Render modes are presentation choices only. They do not imply interactive UI behavior, command execution, live terminal control, or event handling.

## Input prerequisites

Rendering succeeds only when:

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

The renderer rejects parser-failed, semantic-failed, LIR-failed, authority-failed, non-no-effect, unsupported-effect, unsupported-boundary, and unsupported-mode inputs.

## Render result metadata

The render result records:

```text
card name
effect
boundary
rail count
field count
text count
binding count
node count
edge count
section count
card source span
authority summary
no-effect flags
bounded rail snapshots
bounded field snapshots
bounded binding-prefix snapshots
bounded text length and escaped-value snapshots
bounded source-span snapshots
```

The renderer does not retain request pointers after `latticra_l_ui_render` returns.

## Report output

`latticra_l_ui_render_report` writes a deterministic report into a caller-provided buffer.

Header fields include:

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

Small output buffers return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the buffer.

## Detailed report sections

Detailed mode emits sections in this order:

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

The order is deterministic across repeated runs.

## Text and embedded NUL behavior

The renderer respects length-carrying text metadata.

Rules:

```text
value_len is authoritative
escaped output is used for operator-visible text
escaped decoded NUL through \x00 remains visible
literal source-buffer NUL remains rejected before rendering
raw C-string fields are not authoritative for embedded NUL values
```

## Authority metadata behavior

The renderer consumes a C-compatible authority summary.

It displays authority metadata but does not broaden authority, perform effects, call C++ authority APIs directly, or expose C++ object lifetimes through the renderer API.

## No-effect behavior

Rendering preserves:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Rendering does not execute commands, mutate state, evaluate host state, call Nucleus task execution, write files, read files, open network connections, call server code, call update code, call recovery code, or touch hardware.

## Validation

Run:

```sh
sh scripts/test-l-ui-rendering.sh
```

The test suite covers:

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

## Compatibility expectations

This implementation must not change:

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

The first accepted fixture still preserves:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Current boundary

This implementation does not provide:

```text
interactive UI behavior
terminal control
command behavior
Lat execution
LIR execution
Nucleus task execution
file I/O
network I/O
state mutation
server interaction
self-update
recovery behavior
hardware behavior
sandboxing
malware prevention
ransomware prevention
operating-system completeness
```

## Non-claims

This document and implementation do not claim a finished operating system, hardened sandbox, production runtime, production security boundary, malware prevention, ransomware prevention, recovery system, update system, bootable image, public UI product, terminal UI product, or public release readiness.

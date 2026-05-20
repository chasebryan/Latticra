# Latticra L-UI Rendering Detailed Report Refinement

Status: implementation refinement
Scope: deterministic detailed-report metadata for the no-effect L-UI renderer.

## Purpose

This refinement makes the existing L-UI detailed rendering surface easier to audit by adding explicit metadata fields for report classification, detail level, detailed-report availability, detailed section count, deterministic section sequence, no-effect-chain status, and evidence level.

The renderer remains presentation-only.

## Implementation files

This slice updates:

```text
include/latticra/l_ui_renderer.h
src/l_ui_renderer.c
tests/l_ui_rendering_detailed_report_refinement.c
scripts/test-l-ui-rendering-detailed-report-refinement.sh
.github/workflows/l-ui-rendering-detailed-report-refinement.yml
.github/workflows/c.yml
```

## Added metadata

The render result now exposes:

```text
report_classification
detail_level
section_sequence
no_effect_chain
evidence_level
detailed_report_available
detailed_section_count
```

Detailed mode reports:

```text
report_classification=detailed_report
detail_level=detailed
detailed_report_available=1
detailed_section_count=10
section_sequence=HEADER,CARD,AUTHORITY,RAILS,FIELDS,TEXT,BINDINGS,LIR,SOURCE_SPANS,NO_EFFECT_FLAGS
no_effect_chain=preserved
evidence_level=metadata
```

Summary mode remains a header-only report:

```text
report_classification=summary_report
detail_level=summary
detailed_report_available=0
detailed_section_count=0
section_sequence=HEADER
```

## Boundary

This refinement does not add:

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

## Validation

Run:

```sh
sh scripts/test-l-ui-rendering-detailed-report-refinement.sh
sh scripts/test-l-ui-rendering.sh
```

The focused test verifies:

```text
detailed mode sets explicit report metadata
detailed report emits explicit metadata
summary mode remains single-header reporting
no-effect flags remain preserved
```

## Compatibility expectations

This refinement preserves:

```text
existing parser behavior
existing semantic validation behavior
existing LIR shape behavior
existing authority behavior
existing render modes
existing no-effect flags
existing detailed report section order
existing summary report behavior
```

## Non-claims

This document and implementation do not claim a finished operating system, hardened sandbox, production runtime, production security boundary, malware prevention, ransomware prevention, recovery system, update system, bootable image, public UI product, terminal UI product, or public release readiness.

# Latticra Lat Semantic Diagnostics Refinement

Status: initial Lat semantic diagnostics refinement implementation
Scope: deterministic semantic diagnostic classes, category counters, first-diagnostic indices, report fields, invariant tests, guard coverage, and workflow coverage.

## Purpose

This document records the Lat semantic diagnostics refinement after the Nucleus task report refinement.

The goal is to make Lat semantic reports easier to audit by classifying diagnostics into stable categories, counting diagnostics by category, and exposing deterministic first-diagnostic indices.

This refinement does not execute Lat, execute LIR, compile Lat, interpret Lat, mutate state, perform I/O, or provide runtime behavior.

## Added semantic metadata

The Lat semantic result now records:

```text
diagnostic_class
parse_diagnostic_count
declaration_diagnostic_count
reference_diagnostic_count
requirement_diagnostic_count
effect_diagnostic_count
no_effect_diagnostic_count
internal_diagnostic_count
first_diagnostic_declaration_index
first_diagnostic_clause_index
```

The deterministic `LAT SEMANTIC REPORT` now emits those fields.

## Diagnostic classes

Initial diagnostic classes:

```text
valid
parse
declaration
reference
requirement
effect
no-effect
internal
```

## Class mapping

Initial class mapping:

```text
ok -> valid
parse_not_ok -> parse
duplicate_declaration -> declaration
invalid_state_field -> declaration
invalid_clause_for_declaration -> declaration
empty_declaration -> declaration
unknown_transition_source -> reference
invalid_require_left -> requirement
invalid_effect_target -> effect
invalid_effect_value -> effect
effect_requires_gate -> effect
no_effect_violation -> no-effect
null_argument -> internal
capacity_exceeded -> internal
internal_error -> internal
```

## First diagnostic indices

When diagnostics are present, the semantic result records the declaration and clause indices of the first emitted diagnostic:

```text
first_diagnostic_declaration_index
first_diagnostic_clause_index
```

When the semantic result is valid or has no diagnostic record, both remain zero.

## Validation

Run:

```sh
sh scripts/test-lat-semantic-diagnostics-refinement.sh
sh scripts/test-lat-semantic-validation.sh
```

The focused invariant tests verify:

```text
lat_semantic_diagnostic_class_labels_are_stable
lat_semantic_diagnostics_refinement_reports_valid_class
lat_semantic_diagnostics_refinement_reports_parse_class
lat_semantic_diagnostics_refinement_reports_declaration_class
lat_semantic_diagnostics_refinement_reports_reference_class
lat_semantic_diagnostics_refinement_reports_requirement_class
lat_semantic_diagnostics_refinement_reports_effect_class
lat_semantic_diagnostics_refinement_reports_internal_null_argument
```

## Compatibility

This refinement preserves existing Lat semantic behavior for:

```text
semantic validation outcomes
semantic error labels
diagnostic record content
declaration/state/policy/transition/assertion/effect counts
no-effect flags
small-buffer behavior
null-argument behavior
```

## Non-claims

This diagnostics refinement does not provide:

```text
Lat execution
Lat compilation
Lat interpretation
LIR execution
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

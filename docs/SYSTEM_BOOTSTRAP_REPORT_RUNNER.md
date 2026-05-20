# System Bootstrap Report Runner

Status: operator-facing report runner
Scope: compile and run a small command-line program that prints the deterministic system bootstrap report.

## Purpose

This slice adds a tiny report runner for the system bootstrap surface.

The runner builds a default bootstrap request, runs the existing no-effect bootstrap API, renders the bootstrap report, and prints it to standard output.

## Files

```text
tools/system_bootstrap_report.c
scripts/test-system-bootstrap-report-runner.sh
.github/workflows/system-bootstrap-report-runner.yml
docs/SYSTEM_BOOTSTRAP_REPORT_RUNNER.md
```

## Validation

Run:

```sh
sh scripts/test-system-bootstrap-report-runner.sh
```

The guard compiles the runner, executes it, captures its output, and checks for stable report fields:

```text
LATTICRA SYSTEM BOOTSTRAP REPORT
bootstrap_id=latticra-system-bootstrap
system_status=startup-report-ready
effect_boundary=no-effect
runtime_entry_status=not-entered
no_effect=1
```

## Boundary

This runner is report-only. It prints the deterministic bootstrap report and does not expand the bootstrap effect boundary or add runtime entry behavior.
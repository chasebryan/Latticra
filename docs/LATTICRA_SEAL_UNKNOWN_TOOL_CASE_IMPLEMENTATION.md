# Latticra Seal Unknown Tool Case Implementation

Status: initial unknown tool case test fixture
Scope: first negative-test evidence slice after the runtime gate contract. This slice does not implement runtime enforcement, allow/deny outcomes, runtime authority, tool execution, shell execution, network behavior, host behavior, cryptographic validation, or effect execution.

## Purpose

This document records the unknown-tool test fixture for the Seal runtime gate.

It uses report-only runtime gate metadata and ensures the unknown tool case remains blocked by default.

## Added files

```text
tests/seal_unknown_tool_case.c
scripts/test-latticra-seal-unknown-tool-case.sh
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-unknown-tool-case.sh
```

Expected output:

```text
seal unknown tool case: ok
```

## Claim gate

This test fixture alone does not justify a public claim that Latticra secures AI agents.

The accurate public claim remains:

```text
Latticra Seal is building a report-only trust boundary for AI-era automation.
```

Stronger claims require additional blocked-request tests (unsigned, stale, replayed) and validated runtime-enforcement behavior.

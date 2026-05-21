# Latticra Seal Replayed Request Case Implementation

Status: initial replayed request case fixture
Scope: local deterministic case fixture after the replayed request case contract.

## Purpose

This record documents the replayed-request case fixture for the Seal runtime gate metadata path.

The fixture keeps the gate in report-only state and verifies that no authority, host operation, network operation, or effect is reported.

## Added files

```text
tests/seal_replayed_request_case.c
scripts/test-latticra-seal-replayed-request-case.sh
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-replayed-request-case.sh
```

Expected output:

```text
seal replayed request case: ok
```

## Boundary

This slice is a local deterministic fixture only.

It does not add runtime behavior, tool behavior, host behavior, network behavior, effect behavior, or authority grants.

## Claim boundary

This fixture does not by itself justify a stronger public claim.

The accurate public claim remains:

```text
Latticra Seal is building a report-only trust boundary for AI-era automation.
```

## Next valid slice

The next valid slice is status/index alignment for the completed core blocked-request case set.

# Latticra Seal Unsigned Request Case Implementation

Status: initial unsigned request case fixture
Scope: local deterministic case fixture after the unsigned request case contract.

## Purpose

This record documents the unsigned-request case fixture for the Seal runtime gate metadata path.

The fixture keeps the gate in report-only state and verifies that no authority, host operation, network operation, or effect is reported.

## Added files

```text
tests/seal_unsigned_request_case.c
scripts/test-latticra-seal-unsigned-request-case.sh
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-unsigned-request-case.sh
```

Expected output:

```text
seal unsigned request case: ok
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

The next valid slice is the stale request case contract.

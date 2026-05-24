# Latticra Seal Usage

This document describes the intended user-facing shape of Latticra Seal commands.

Some commands may be planned, experimental, or partially implemented. Treat the local repository and current tests as the source of truth.

## Check local command availability

```sh
which latticra-seal
```

## Generate a local report

```sh
latticra-seal report
```

Expected report behavior:

- report-only
- no network authority
- no runtime enforcement authority
- no root authority
- local evidence only

## Run the Seal smoke lane

```sh
make seal
```

## Run policy-denial regression checks

```sh
make seal-policy-denials
```

## Inspect Seal lock material

```sh
head -40 latticra.seal.lock
```

## Recommended local verification sequence

```sh
make seal
make seal-policy-denials
latticra-seal report
```

## Expected documentation posture

Every command should be documented with:

- what it reads
- what it writes
- what it refuses to do
- whether it is report-only
- whether it requires root
- whether it uses the network
- what counts as PASS
- what counts as FAIL

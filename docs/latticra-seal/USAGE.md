# Latticra Seal Usage

This document describes the intended user-facing shape of Latticra Seal commands.

Some commands may be planned, experimental, or partially implemented. Treat the local repository and current tests as the source of truth.

## Check local command availability

```sh
which latticra-seal
```

## Generate a local CLI report

```sh
make seal
```

`make seal` builds the native `latticra-seal` CLI and runs the local integrity check.
It writes the current CLI report and hash list under `reports/`.
The native `latticra-seal check` command exits nonzero if its report stream
cannot be written to stdout. Digest and policy traversal refuses symlinks,
hard-linked regular files, and other non-regular paths inside the included
project scope before writing a new hash list. Recursed directories must still
match their observed device/inode identity when opened for traversal, and files
collected for policy scanning and hashing must still match their collected
device/inode identity when they are read.
Manifest-declared required files must remain inside that effective digest
scope; a missing required file or one excluded through `[paths].exclude` fails
the check and prevents a fresh hash list from being promoted.

## Print the latest local CLI report

```sh
latticra-seal report
```

`latticra-seal report` exits nonzero when the report artifact is missing,
unreadable, hard-linked, the report directory is symlinked or
group/world-writable, or stdout cannot be written. The command validates and
opens `reports/` before reading the artifact by descriptor-relative name; it
does not create `reports/` for a read-only missing-artifact hint.

Expected report behavior:

- report-only
- no network authority
- no runtime enforcement authority
- no root authority
- local evidence only

## Run the legacy smoke lane

```sh
make seal-smoke
```

The smoke lane is retained as a compatibility route for the original shell report.

## Run the native Seal check directly

```sh
make seal-check
```

## Inspect the manifest summary

```sh
latticra-seal manifest
```

The manifest summary is read-only and exits nonzero when required summary
fields are missing, duplicate, malformed, empty, or unsupported for the native
v0.1 CLI. It also exits nonzero when stdout cannot be written.

## Print the latest local CLI hash list

```sh
latticra-seal hashes
```

`latticra-seal hashes` exits nonzero when the hash-list artifact is missing,
unreadable, hard-linked, the report directory is symlinked or
group/world-writable, or stdout cannot be written. The command validates and
opens `reports/` before reading the artifact by descriptor-relative name; it
does not create `reports/` for a read-only missing-artifact hint.

The read-only `latticra-seal version` and `latticra-seal help` commands also
exit nonzero when stdout cannot be written.

## Run the hybrid envelope self-check

```sh
latticra-seal hybrid
```

`latticra-seal hybrid` runs a local AES-256-GCM seal/open self-check over the C
substrate hybrid envelope. The substrate generates salt and nonce material for
the attached self-check record, and the protected record header is bound as
AES-GCM associated data. The command prints metadata only and redacts secret
material, salt, nonce, ciphertext, tags, plaintext, and the sealed record.

## Run the hybrid provider self-test

```sh
latticra-seal hybrid-provider-self-test
```

`latticra-seal hybrid-provider-self-test` runs the read-only provider-backed
hybrid self-test over local `ECDH-P-256` plus `ML-KEM-512`, `ML-KEM-768`, and
`ML-KEM-1024` parameter sets, then feeds those derived secrets into the
attached-record hybrid envelope path. The command emits a report-only status
surface, binds transcript AAD to provider algorithm and public-key evidence,
redacts secret material and plaintext, and preserves `runtime_authority_granted=0`.

## Create a local hash baseline

```sh
latticra-seal baseline
```

The native CLI writes `latticra.seal.lock` only after a passing check. Baseline
promotion retains the generated hash-list descriptor from that prerequisite
check, copies that descriptor into a temporary lockfile, and refuses symlinked,
hard-linked, or non-regular lock paths. The temporary lockfile is flushed and
fsynced before promotion, and the project-root directory is synced after the
rename when supported.
The baseline command exits nonzero when its prerequisite check output or final
success line cannot be written to stdout.

## Verify a local hash baseline

```sh
latticra-seal verify
```

`latticra-seal verify` compares current hashes against `latticra.seal.lock` and
exits nonzero when its report stream cannot be written to stdout.

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
latticra-seal hybrid
latticra-seal hybrid-provider-self-test
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

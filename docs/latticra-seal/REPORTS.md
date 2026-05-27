# Latticra Seal Reports

Latticra Seal reports are evidence records.

A report should be readable by a human and stable enough for future tooling.

## Report goals

A Seal report should answer:

- what was checked
- when it was checked
- where it was checked
- what mode was used
- what passed
- what failed
- what changed
- what authority was not used

## Required report fields

Recommended fields:

```text
timestamp_utc=
mode=
prefix=
kernel=
os=
network_authority=
runtime_enforcement_authority=
root_authority=
manifest_present=
lock_present=
hashes_checked=
hashes_changed=
warnings=
failures=
status=
```

## Current Seal report surfaces

Current report-only Seal surfaces include:

```text
seal_capability_metadata_report=1
seal_policy_decision_report=1
seal_runtime_dry_run_report=1
seal_operator_receipt_report=1
```

The operator receipt report is a bundled denied metadata receipt. It does not grant authority, execute tools, read or write host data, use the network, or perform effects.

## Local integrity report files

The default `make seal` path uses the native CLI and writes:

```text
reports/latticra-seal-cli-report.txt
reports/latticra-seal-cli-hashes.txt
```

The native CLI validates that the `[report]` output declarations in
`latticra.seal` match these generated artifact paths before it returns PASS.
It refuses symlinked, non-directory, or group/world-writable report directories
before writing evidence artifacts.
The native CLI writes the latest report through a temporary report file and
promotes it only after the report is complete. Symlinked final or temporary
report paths are refused.

`latticra-seal baseline` promotes the generated hash list into
`latticra.seal.lock` through a temporary lockfile, and refuses symlinked or
non-regular lock paths.
`latticra-seal verify` treats the lockfile as canonical: entries must use the
native two-space hash/path separator, project-relative safe paths, and strict
path sort order.

The legacy shell smoke lane remains available through `make seal-smoke` and writes:

```text
reports/latticra-seal-report.txt
reports/latticra-seal-file-hashes.txt
```

## Report modes

### report-only

The default safe mode.

Report-only mode may inspect and describe local state, but should not enforce runtime behavior or mutate system state.

### verification

Verification mode compares current state against declared expectations.

Verification may fail when files are missing, changed, malformed, or outside policy.

### future enforcement

Future enforcement must not be claimed until implemented and tested.

## PASS meaning

PASS means the checked evidence matched the declared local expectations for that command.

PASS does not mean the host is secure.

## FAIL meaning

FAIL means the checked evidence did not match expectations, policy denied the state, or Seal could not safely complete the check.

FAIL should include a reason.

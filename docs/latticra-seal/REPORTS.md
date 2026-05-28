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
Core `[project]` identity metadata must also be present, quoted, non-empty,
escape-free, control-free, unique, and supported before native digest evidence
is promoted.
Malformed, quoted unsupported, or otherwise unsupported manifest section
headers fail closed before report or digest evidence is promoted.
Manifest reads and manifest hashing require `latticra.seal` to be a single-link
regular file without embedded NUL bytes, so symlinked, hard-linked, or
truncated-parse manifests fail closed before a passing report or digest can be
produced. Manifest reads also require a size-stable descriptor read, so
size-changing concurrent manifest updates fail closed. The reported
`manifest_sha256` is computed from the parsed manifest bytes instead of
reopening the path after validation.
It refuses symlinked, non-directory, or group/world-writable report directories
before writing evidence artifacts.
Generated report artifacts are then opened, unlinked, read, and promoted
relative to the checked report-directory descriptor so a later path swap cannot
redirect report or hash-list evidence.
The native `check` and `verify` commands clear stale native hash-list artifacts
before manifest or baseline gates, which prevents early failures from leaving an
older hash list in the advertised output location.
A fresh native hash list is promoted only after manifest, policy, report, and
reserved proof metadata checks pass with no prior failures. Policy denial hits or policy inspection failures prevent temporary hash-list creation and fresh hash-list promotion.
The native CLI writes the latest report through a temporary report file and
promotes it only after the report is complete.
Symlinked, hard-linked, or non-regular final and temporary report paths are refused.
Temporary artifact creation uses create-new semantics after clearing only safe
single-link stale temp files. Report and hash-list temporary files are flushed
and fsynced before promotion, and the report directory is synced after the
promotion when the platform supports directory fsync.
The native hash list follows the same artifact safety rule: stale regular hash
lists may be cleared, but symlinked, hard-linked, or non-regular final and
temporary hash-list paths are refused.
Digest and policy traversal also refuses symlinks, hard-linked regular files,
and other non-regular paths inside the included project scope before writing a
new hash list. In-scope path names must also be representable as canonical
native hash-list paths: project-relative, control-free, backslash-free, and
without `.` or `..` segments. Recursed directories must still match their
observed device/inode identity when opened for traversal. Regular files
collected for policy scanning and hashing retain their device/inode identity,
and later reads must still match that identity. Policy scan and hash reads
snapshot the opened descriptor's observed size and require the descriptor size after the read to match.
Directory read or close failures make traversal incomplete and prevent fresh
native hash-list promotion.
Regular generated Seal artifacts are treated as built-in exclusions from
native policy and digest evidence even when a custom manifest omits the default
report, hash-list, or lockfile exclude patterns.
Required files declared by the manifest must also stay inside the effective
digest scope. A missing, hard-linked, or excluded required file fails the report
and prevents a fresh native hash list from being promoted.
Read-only streaming commands for report and hash-list artifacts fail closed when
the artifact cannot be read, is empty, is hard-linked, or stdout cannot be
written, so automation does not mistake redirected or truncated output for a
successful export.
The read-only hash-list stream also parses the accepted hash-list descriptor and
refuses empty, malformed, embedded-NUL, CRLF, or non-LF-terminated hash-list
artifacts before emitting bytes to stdout. Report and hash-list artifact
streaming, hash-list parsing, baseline copying, and baseline comparison require
size-stable descriptor reads.
These read-only commands refuse symlinked or group/world-writable report directories
before streaming artifact contents, and they do not create `reports/` while
serving a missing-artifact hint.

`latticra-seal baseline` promotes the generated hash list into
`latticra.seal.lock` through a temporary lockfile.
It retains the hash-list descriptor produced by its prerequisite passing check
and copies that descriptor into the lockfile, then refuses symlinked,
hard-linked, or non-regular lock paths. The temporary lockfile is flushed and
fsynced before promotion, and the project-root directory is synced after the
rename when supported.
`latticra-seal verify` treats the lockfile as canonical: entries must be
non-empty, LF-terminated, embedded-NUL-free, CR-free, and use the native
two-space hash/path separator, project-relative safe paths, and strict path
sort order. Hard-linked lockfiles are refused before comparison. The
accepted lockfile descriptor is retained for baseline comparison so a later path
replacement cannot change which saved baseline is being compared.

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

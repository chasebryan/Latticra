# Latticra Seal Manifest v0.1

latticra.seal is the root trust manifest for a Latticra project.

It is a human-readable, TOML-compatible manifest used to describe local project integrity rules, protected paths, policy checks, and proof-report metadata.

The .seal extension marks the file as a Latticra trust artifact while keeping it simple enough to parse from C, C++, Rust, Python, or shell tooling.

## Purpose

The v0.1 manifest defines:

- project identity
- local trust boundary
- hash algorithm
- protected paths
- excluded paths
- required files
- basic policy checks
- report output locations
- reserved proof fields for future signing

## Current Security Status

v0.1 is an unsigned local-integrity manifest.

It can support local scanning, policy checking, and digest reporting, but it should not yet be described as a complete cryptographic attestation system.

## Required Root Fields

Required root fields:

    schema = "latticra.seal/v0.1"
    format = "toml"
    kind = "local-integrity-manifest"

These fields identify the manifest version, parser expectation, and trust-artifact type.

## Project Section

The project section describes the project being sealed.

Expected fields:

    name = "Latticra"
    id = "latticra"
    version = "0.1.0"
    repository = "https://github.com/Bryforge/Latticra"
    license = "SEE LICENSE"

## Seal Section

The seal section describes the active trust mode.

For v0.1:

    mode = "local-integrity"
    status = "unsigned"
    algorithm = "sha256"
    digest_encoding = "hex"
    trust_boundary = "project-root"

The native Seal CLI validates the declared mode, unsigned status, digest
algorithm, digest encoding, canonicalization string, and trust boundary before
emitting a passing report. seal configuration fields must fail closed when
missing, duplicate, malformed, or unsupported.
The native manifest summary command is read-only, but it must also fail closed:
required summary fields must not be missing, duplicate, malformed, empty, or
unsupported when `latticra-seal manifest` exits successfully.
Read-only output commands, including `manifest`, `report`, `hashes`, `version`,
and `help`, must exit nonzero when stdout cannot be written.
The `report` and `hashes` commands must also refuse symlinked or
group/world-writable report directories before streaming artifact contents.
Generated report and hash-list artifacts must be single-link regular files
before read-only streaming commands can export them. Native report artifacts
must be opened, unlinked, read, and promoted relative to a checked `reports/`
directory descriptor; read-only streaming commands must not create `reports/`
while serving missing-artifact hints.
Report-streaming commands, including `check` and `verify`, must also exit
nonzero when stdout cannot be written after their generated report artifacts are
finalized. `baseline` must refuse promotion when its prerequisite check stream
cannot be written and must exit nonzero if its final success line cannot be
written.

## Paths Section

The paths section defines what the scanner should include and exclude.

The v0.1 default includes the project root and excludes generated directories, dependency directories, temporary files, and generated reports.

The native Seal CLI reads `[paths].include` and `[paths].exclude` before
policy and digest scans. The supported v0.1 include scope is the project root
(`"."`). Exclude entries may be exact filenames, exact relative paths, simple
`*` wildcard prefix/suffix patterns, or directory patterns ending in `/`.
Missing, duplicate, malformed, or unsupported path scope must fail closed.
String arrays must use explicit comma separators; missing or doubled separators
are malformed.
Exclude entries must stay relative to the project root and must not contain
absolute paths, `.` or `..` path segments, control characters, backslashes, or
multiple wildcards.
Digest and policy traversal must fail closed on symlinks, hard-linked regular
files, and other non-regular paths inside the included project scope before any
new native hash list is promoted. Directory traversal must open directories
without following symlinks and verify that recursed directories still match the
previously observed device/inode identity before reading entries. File reads
performed after traversal must verify that the opened file still matches the
collected device/inode identity.

## Policy Section

The policy section defines local project checks.

Initial policy checks include:

- requiring a README
- requiring a LICENSE
- denying obvious private-key filenames
- denying .env files
- denying obvious committed token markers
- optionally warning about oversized files

The native Seal CLI reads required file paths from
`[policy.required_files].paths`. Missing, duplicate, or malformed required-file
arrays must fail closed, and every declared required file must exist as a
regular file. Required-file paths must be project-relative regular-file paths;
absolute paths, directory paths, wildcards, `.` or `..` segments, control
characters, and backslashes are malformed.
Required files must also remain inside the effective digest scope. If a
required file is missing or excluded by a file or parent-directory exclude
pattern, the check must fail closed and no new native hash list may be
promoted.

Content-denial marker examples should be represented as split `pattern_parts`
metadata in the manifest so the manifest does not itself contain a complete
denied marker string.

The native Seal CLI reads deny filename patterns from
`[policy.deny_filenames].patterns` and deny content markers from
`[policy.deny_contents].pattern_parts`. Missing, duplicate, or malformed deny
policy arrays must fail closed.
Nested content marker arrays must also use explicit comma separators.
Filename deny patterns must be filename patterns, not path patterns; `/`,
backslashes, control characters, bare `*`, and multiple wildcards are
malformed.

## Report Section

The report section defines where generated Seal reports should be written.

Default native CLI outputs:

    reports/latticra-seal-cli-report.txt
    reports/latticra-seal-cli-hashes.txt

Native hash lists and `latticra.seal.lock` baselines are canonical artifacts:
each entry uses lowercase SHA-256 hex, two spaces, and a project-relative safe
path. Baseline entries must already be sorted by path; verification must reject
malformed, unsafe, duplicate, or unsorted baseline entries instead of
normalizing them.
Native hash-list promotion must refuse symlinked, hard-linked, or non-regular
final and temporary hash-list paths, and promotion must occur relative to the
checked report-directory descriptor. Native report and hash-list temporary
files must be flushed and fsynced before promotion, and the report directory
must be synced after promotion when directory fsync is supported.
Baseline promotion must apply the same symlink, hard-link, and non-regular path
refusal to `latticra.seal.lock` and its temporary lockfile. Baseline promotion
must copy from the generated hash-list descriptor retained by its prerequisite
passing check, not by reopening the hash-list artifact after the check returns.
The temporary baseline lockfile must be flushed and fsynced before promotion,
and the project-root directory must be synced after promotion when directory
fsync is supported.
Baseline verification must refuse hard-linked lockfiles before comparing hashes.

Legacy smoke-lane outputs retained for compatibility:

    reports/latticra-seal-report.txt
    reports/latticra-seal-file-hashes.txt

The native Seal CLI validates `[report].default_output`,
`[report].hash_list_output`, `[report].legacy_smoke_output`,
`[report].legacy_smoke_hash_list_output`, and the report inclusion booleans
before returning PASS. These declarations must match the actual CLI report
surface so manifest metadata cannot drift away from generated artifacts.
Native report writes should use a temporary report file and atomic promotion so
the public latest-report path is not left partially written.
Symlinked, hard-linked, or non-regular final and temporary report paths must be refused.
Temporary artifact creation must use create-new semantics after clearing only
safe single-link stale temp files, so temp writers do not truncate an existing
path before validating it.

## Proof Section

The proof section is reserved for future cryptographic fields.

In v0.1, these fields are intentionally empty:

    manifest_hash = ""
    root_hash = ""
    signature_algorithm = ""
    signature = ""
    public_key = ""

## Roadmap

- v0.1: local manifest, smoke verification, digest report
- v0.2: signed manifests and public-key verification
- v0.3: Merkle-style root hash and reproducible proof bundles
- v0.4: Latticra Panel integration
- v1.0: stable Seal CLI with documented guarantees and limits

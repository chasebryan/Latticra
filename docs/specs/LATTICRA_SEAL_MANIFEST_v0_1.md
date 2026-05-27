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

Legacy smoke-lane outputs retained for compatibility:

    reports/latticra-seal-report.txt
    reports/latticra-seal-file-hashes.txt

The native Seal CLI validates `[report].default_output`,
`[report].hash_list_output`, `[report].legacy_smoke_output`,
`[report].legacy_smoke_hash_list_output`, and the report inclusion booleans
before returning PASS. These declarations must match the actual CLI report
surface so manifest metadata cannot drift away from generated artifacts.

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

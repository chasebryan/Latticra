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

## Paths Section

The paths section defines what the scanner should include and exclude.

The v0.1 default includes the project root and excludes generated directories, dependency directories, temporary files, and generated reports.

## Policy Section

The policy section defines local project checks.

Initial policy checks include:

- requiring a README
- requiring a LICENSE
- denying obvious private-key filenames
- denying .env files
- denying obvious committed token markers
- optionally warning about oversized files

## Report Section

The report section defines where generated Seal reports should be written.

Default outputs:

    reports/latticra-seal-report.txt
    reports/latticra-seal-file-hashes.txt

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

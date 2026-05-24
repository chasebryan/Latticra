# Latticra Seal Demo v0.1

This demo shows the first working trust loop for Latticra Seal.

Latticra Seal currently supports:

- reading the root latticra.seal manifest
- checking manifest shape
- checking required project files
- generating SHA-256 file digests
- writing a saved baseline to latticra.seal.lock
- verifying the current project state against that saved baseline
- reporting added, removed, or modified files

## Demo Commands

Build the Seal CLI:

    make seal-cli

Print the version:

    ./build/latticra-seal version

Inspect the manifest:

    ./build/latticra-seal manifest

Run a full check:

    ./build/latticra-seal check

Create or refresh the trusted baseline:

    ./build/latticra-seal baseline

Verify the current project state:

    ./build/latticra-seal verify

Run the demo script:

    ./scripts/demo-latticra-seal.sh

## What the baseline means

The saved baseline does not prove the project is perfect or externally certified.

It means the current project files match the file-state previously recorded in latticra.seal.lock.

A precise public statement is:

Latticra Seal verifies that the current project state matches a previously recorded trusted baseline.

## Current Status

This is an early local-integrity prototype.

It is not yet a full cryptographic attestation system. Future versions should add signed manifests, public-key verification, stronger proof bundles, and Latticra Panel integration.

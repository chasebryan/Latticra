# Latticra Seal Roadmap

Latticra Seal should grow in disciplined layers.

## Phase 1: Documentation baseline

Goal: make Seal understandable.

Tasks:

- create documentation handbook
- define status
- define architecture
- define command usage
- define policy behavior
- define report behavior
- define non-claims

## Phase 2: CLI clarity

Goal: make commands predictable.

Tasks:

- document every command
- document read/write behavior
- document exit codes
- document report schema
- document policy-denial reasons

## Phase 3: Manifest and lock hardening

Goal: make local verification reproducible.

Tasks:

- stabilize manifest schema
- stabilize lock format
- define baseline update rules
- define ignored paths
- define changed-file output
- test malformed manifest behavior

## Phase 4: Report schema

Goal: make reports machine-readable and human-readable.

Tasks:

- define required fields
- define optional fields
- define status values
- define warning classes
- define failure classes
- preserve report-only authority limits

## Phase 5: Panel integration

Goal: make Seal visible in Latticra Panel.

Tasks:

- expose report-only scan
- expose policy-denial status
- expose report path
- expose manifest/lock status
- avoid runtime/root/network authority

## Phase 6: Cryptographic strengthening

Goal: move from hash baseline toward stronger signed evidence.

Tasks:

- define signing model
- define key handling
- define trust root boundaries
- define verification receipt format
- test invalid signature behavior
- test missing key behavior

## Phase 7: Runtime-boundary handoff

Goal: prepare metadata for future enforcement without claiming enforcement early.

Tasks:

- define runtime handoff metadata
- define capability gate contract
- define denial behavior
- define no-effect dry-run behavior
- test handoff reports

## Phase 8: Fedora/Linux integration research

Goal: explore host integration carefully.

Tasks:

- document user-local install evidence
- document no-root assumptions
- document future RPM boundaries
- document SELinux/systemd non-claims
- document what would be required before host-level trust claims

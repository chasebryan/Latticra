# Latticra Netplane Kaiju Static Adapter Evidence Intake

Status: no-effect Kaiju static adapter evidence intake
Date: 2026-06-19 CDT
Scope: first Kaiju follow-on lane after the Latticra Netplane central-hub intake.

## Purpose

This record defines the first Kaiju-to-Latticra Netplane adapter lane as static evidence only. It records Kaiju workspace metadata, license posture, schema markers, fixture boundaries, and digest fields that a future Latticra adapter can review before any source import, artifact copy, command execution, live network action, plugin runtime, mixed build, or runtime authority is accepted.

The intake is grounded in the local Kaiju checkout observed at `~/Documents/kaiju` on `main` revision `93995843381d`.

## Boundary Checkpoint

```text
latticra_netplane_kaiju_static_adapter_evidence_intake_present=1
kaiju_static_adapter_evidence_intake_guard_present=1
intake_id=latticra-netplane-kaiju-static-adapter-evidence-intake
intake_version=1
edge_checkpoint=v0.3.0edge
manifest_reference=fixtures/netplane/latticra-netplane-kaiju-static-adapter-evidence-manifest.json
kaiju_static_adapter_inventory_tool=tools/latticra_netplane_kaiju_static_adapter_inventory.py
central_hub_intake_reference=docs/LATTICRA_NETPLANE_CENTRAL_HUB_INTAKE.md
kaiju_lane_present=1
kaiju_github=chasebryan/kaiju
kaiju_local_checkout=~/Documents/kaiju
kaiju_source_revision=93995843381d
kaiju_source_dirty_state=clean
kaiju_license_posture=Apache-2.0
kaiju_crate_count=11
kaiju_documentation_file_count=12
kaiju_fixture_file_count=3
kaiju_snapshot_file_count=12
kaiju_evidence_reference_count=8
kaiju_schema_marker_count=5
static_adapter_evidence_intake=1
source_import_performed=0
artifact_copy_performed=0
kaiju_command_executed=0
kaiju_source_vendored=0
kaiju_binary_ingested=0
kaiju_package_accepted=0
pcap_import_performed=0
live_probe_performed=0
port_scan_performed=0
privileged_capture_performed=0
network_performed=0
host_mutation_performed=0
runtime_authority_granted=0
plugin_runtime_accepted=0
mixed_build_promotion_accepted=0
production_readiness_claim=0
```

## Static Evidence Accepted

The intake accepts only static metadata references and digests:

```text
workspace-package-metadata-digest
license-boundary-digest
project-snapshot-schema-marker
package-schema-marker
offline-network-evidence-schema-marker
synthetic-fixture-digest
deterministic-snapshot-digest
```

The fixture manifest records digest-bound references for:

```text
Cargo.toml
LICENSE
docs/project-format.md
docs/network-model.md
docs/threat-model.md
tests/fixtures/README.md
tests/fixtures/network-evidence.txt
tests/snapshots/raw-export.json
```

## Denied Behavior

This intake denies:

```text
source-vendoring
build-output-copy
binary-ingestion
package-acceptance
pcap-import
live-tcp-probe
port-scan
privileged-capture
plugin-runtime
mixed-build-promotion
network-authority
runtime-authority
```

## Adapter Meaning

The adapter meaning is narrow: Latticra can now name the Kaiju evidence shapes it would review, but it has not imported Kaiju source, copied Kaiju artifacts, run Kaiju commands, accepted `.kaiju` packages, imported pcap files, performed live probes or scans, enabled plugins, or granted a runtime bridge.

The next lane may define a Latticra receipt schema for Kaiju package metadata. That schema must still keep source import, package acceptance, command execution, and runtime authority closed until a later explicit review gate changes those fields.

## Validation

This intake is guarded by:

```sh
sh scripts/test-latticra-netplane-kaiju-static-adapter-evidence-intake.sh
```

Expected output:

```text
latticra_netplane_kaiju_static_adapter_evidence_intake: ok
```

## Non-Claims

This record is not source import, artifact import, source vendoring, build output acceptance, binary ingestion, `.kaiju` package acceptance, command execution, file mutation, pcap import, live probing, port scanning, privileged capture, plugin runtime, mixed-build promotion, network behavior, runtime authority, production readiness, distribution readiness, reverse-engineering completeness, or a claim that Kaiju is integrated into Latticra.

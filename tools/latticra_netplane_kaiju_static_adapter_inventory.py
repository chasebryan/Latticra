#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit the Latticra Netplane Kaiju static adapter evidence intake receipt."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
from typing import Any


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_MANIFEST = (
    REPO_ROOT / "fixtures/netplane/latticra-netplane-kaiju-static-adapter-evidence-manifest.json"
)
MANIFEST_REFERENCE = "fixtures/netplane/latticra-netplane-kaiju-static-adapter-evidence-manifest.json"
REQUIRED_EVIDENCE_ROLES = (
    "workspace-package-metadata",
    "license-boundary",
    "project-and-package-schema-boundary",
    "offline-network-evidence-and-live-probe-boundary",
    "defensive-parser-and-authority-boundary",
    "synthetic-fixture-boundary",
    "authorized-offline-network-evidence-fixture",
    "deterministic-project-snapshot-fixture",
)
REQUIRED_SCHEMA_MARKERS = (
    "kaiju.project.v1",
    "kaiju.network.v1",
    "kaiju.network.probe.v1",
    "kaiju.package.v1",
    "kaiju.annotations.v1",
)


def _load_manifest(path: Path) -> dict[str, Any]:
    with path.open("r", encoding="utf-8") as handle:
        loaded = json.load(handle)
    if not isinstance(loaded, dict):
        raise ValueError("manifest root must be an object")
    return loaded


def _canonical_sha256(document: dict[str, Any]) -> str:
    encoded = json.dumps(document, sort_keys=True, separators=(",", ":")).encode("utf-8")
    return "sha256:" + hashlib.sha256(encoded).hexdigest()


def _require_boundary_zeroes(boundary: dict[str, Any]) -> None:
    required_zeroes = (
        "source_import_performed",
        "artifact_copy_performed",
        "kaiju_command_executed",
        "kaiju_source_vendored",
        "kaiju_binary_ingested",
        "kaiju_package_accepted",
        "pcap_import_performed",
        "live_probe_performed",
        "port_scan_performed",
        "privileged_capture_performed",
        "network_performed",
        "host_mutation_performed",
        "file_mutation_performed",
        "runtime_authority_granted",
        "plugin_runtime_accepted",
        "mixed_build_promotion_accepted",
        "production_readiness_claim",
    )
    for key in required_zeroes:
        if boundary.get(key) != 0:
            raise ValueError(f"boundary must preserve {key}=0")


def _evidence_reference_map(source_lane: dict[str, Any]) -> dict[str, dict[str, Any]]:
    references = source_lane.get("evidence_references")
    if not isinstance(references, list):
        raise ValueError("evidence_references must be a list")

    mapped: dict[str, dict[str, Any]] = {}
    for reference in references:
        if not isinstance(reference, dict):
            raise ValueError("evidence_references entries must be objects")
        role = reference.get("evidence_role")
        path = reference.get("path")
        digest = reference.get("sha256")
        if not isinstance(role, str) or not role:
            raise ValueError("evidence references must include evidence_role")
        if not isinstance(path, str) or not path:
            raise ValueError("evidence references must include path")
        if not isinstance(digest, str) or not digest.startswith("sha256:"):
            raise ValueError(f"evidence reference {path} must include sha256 digest")
        mapped[role] = reference
    return mapped


def validate_manifest(manifest: dict[str, Any]) -> dict[str, Any]:
    if manifest.get("manifest_id") != "latticra-netplane-kaiju-static-adapter-evidence-intake":
        raise ValueError("unexpected manifest_id")
    if manifest.get("manifest_version") != 1:
        raise ValueError("unexpected manifest_version")

    source_lane = manifest.get("source_lane")
    if not isinstance(source_lane, dict):
        raise ValueError("source_lane must be an object")
    if source_lane.get("lane") != "kaiju":
        raise ValueError("source_lane must describe the kaiju lane")
    if source_lane.get("source_dirty_state") != "clean":
        raise ValueError("kaiju source_dirty_state must be clean for this observed intake")

    workspace_package = source_lane.get("workspace_package")
    if not isinstance(workspace_package, dict):
        raise ValueError("workspace_package must be an object")
    if workspace_package.get("license") != "Apache-2.0":
        raise ValueError("kaiju workspace license must remain Apache-2.0 for this intake")
    if workspace_package.get("crate_count") != 11:
        raise ValueError("kaiju crate_count must match observed static inventory")

    boundary = manifest.get("adapter_boundary")
    if not isinstance(boundary, dict):
        raise ValueError("adapter_boundary must be an object")
    if boundary.get("static_adapter_evidence_intake") != 1:
        raise ValueError("static adapter evidence intake must be present")
    _require_boundary_zeroes(boundary)

    references = _evidence_reference_map(source_lane)
    missing_roles = [role for role in REQUIRED_EVIDENCE_ROLES if role not in references]
    if missing_roles:
        raise ValueError(f"missing evidence roles: {', '.join(missing_roles)}")

    schema_markers = source_lane.get("schema_markers")
    if not isinstance(schema_markers, dict):
        raise ValueError("schema_markers must be an object")
    marker_values = set(schema_markers.values())
    missing_markers = [marker for marker in REQUIRED_SCHEMA_MARKERS if marker not in marker_values]
    if missing_markers:
        raise ValueError(f"missing schema markers: {', '.join(missing_markers)}")

    denied_shapes = manifest.get("denied_evidence_shapes")
    if not isinstance(denied_shapes, list):
        raise ValueError("denied_evidence_shapes must be a list")
    for denied in (
        "source-vendoring",
        "live-tcp-probe",
        "port-scan",
        "privileged-capture",
        "plugin-runtime",
        "network-authority",
        "runtime-authority",
    ):
        if denied not in denied_shapes:
            raise ValueError(f"denied evidence shape is required: {denied}")

    return {
        "evidence_reference_count": len(references),
        "schema_marker_count": len(marker_values),
        "denied_shape_count": len(denied_shapes),
    }


def build_receipt(manifest_path: Path = DEFAULT_MANIFEST) -> dict[str, Any]:
    manifest = _load_manifest(manifest_path)
    validation = validate_manifest(manifest)
    source_lane = manifest["source_lane"]
    workspace_package = source_lane["workspace_package"]
    local_inventory = source_lane["local_inventory"]
    boundary = manifest["adapter_boundary"]

    return {
        "latticra_netplane_kaiju_static_adapter_evidence_intake_present": 1,
        "kaiju_static_adapter_evidence_intake_guard_present": 1,
        "intake_id": "latticra-netplane-kaiju-static-adapter-evidence-intake",
        "intake_version": 1,
        "edge_checkpoint": boundary["edge_checkpoint"],
        "manifest_reference": MANIFEST_REFERENCE,
        "manifest_sha256": _canonical_sha256(manifest),
        "central_hub_intake_reference": manifest["central_hub_intake_reference"],
        "kaiju_lane_present": 1,
        "kaiju_github": source_lane["github"],
        "kaiju_local_checkout": source_lane["local_checkout"],
        "kaiju_source_revision": source_lane["local_revision"],
        "kaiju_source_dirty_state": source_lane["source_dirty_state"],
        "kaiju_license_posture": workspace_package["license"],
        "kaiju_crate_count": workspace_package["crate_count"],
        "kaiju_documentation_file_count": local_inventory["documentation_file_count"],
        "kaiju_fixture_file_count": local_inventory["fixture_file_count"],
        "kaiju_snapshot_file_count": local_inventory["snapshot_file_count"],
        "kaiju_evidence_reference_count": validation["evidence_reference_count"],
        "kaiju_schema_marker_count": validation["schema_marker_count"],
        "denied_shape_count": validation["denied_shape_count"],
        "static_adapter_evidence_intake": boundary["static_adapter_evidence_intake"],
        "source_import_performed": boundary["source_import_performed"],
        "artifact_copy_performed": boundary["artifact_copy_performed"],
        "kaiju_command_executed": boundary["kaiju_command_executed"],
        "kaiju_source_vendored": boundary["kaiju_source_vendored"],
        "kaiju_binary_ingested": boundary["kaiju_binary_ingested"],
        "kaiju_package_accepted": boundary["kaiju_package_accepted"],
        "pcap_import_performed": boundary["pcap_import_performed"],
        "live_probe_performed": boundary["live_probe_performed"],
        "port_scan_performed": boundary["port_scan_performed"],
        "privileged_capture_performed": boundary["privileged_capture_performed"],
        "network_performed": boundary["network_performed"],
        "host_mutation_performed": boundary["host_mutation_performed"],
        "runtime_authority_granted": boundary["runtime_authority_granted"],
        "plugin_runtime_accepted": boundary["plugin_runtime_accepted"],
        "mixed_build_promotion_accepted": boundary["mixed_build_promotion_accepted"],
        "production_readiness_claim": boundary["production_readiness_claim"],
        "next_recommended_lane": manifest["next_recommended_lane"],
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", default=str(DEFAULT_MANIFEST))
    args = parser.parse_args()

    receipt = build_receipt(Path(args.manifest))
    print(json.dumps(receipt, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()

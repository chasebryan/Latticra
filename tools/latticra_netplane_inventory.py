#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Emit the Latticra Netplane central-hub intake receipt."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
from typing import Any


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_MANIFEST = REPO_ROOT / "fixtures/netplane/latticra-netplane-central-hub-manifest.json"
MANIFEST_REFERENCE = "fixtures/netplane/latticra-netplane-central-hub-manifest.json"
REQUIRED_LANES = ("kaiju", "l2", "l3", "l4", "fyr", "rainbow", "netplane")


def _load_manifest(path: Path) -> dict[str, Any]:
    with path.open("r", encoding="utf-8") as handle:
        loaded = json.load(handle)
    if not isinstance(loaded, dict):
        raise ValueError("manifest root must be an object")
    return loaded


def _canonical_sha256(document: dict[str, Any]) -> str:
    encoded = json.dumps(document, sort_keys=True, separators=(",", ":")).encode("utf-8")
    return "sha256:" + hashlib.sha256(encoded).hexdigest()


def _lane_map(manifest: dict[str, Any]) -> dict[str, dict[str, Any]]:
    lanes = manifest.get("active_lanes")
    if not isinstance(lanes, list):
        raise ValueError("active_lanes must be a list")

    mapped: dict[str, dict[str, Any]] = {}
    for lane in lanes:
        if not isinstance(lane, dict):
            raise ValueError("active_lanes entries must be objects")
        name = lane.get("lane")
        if not isinstance(name, str) or not name:
            raise ValueError("active_lanes entries must include lane names")
        mapped[name] = lane
    return mapped


def _require_boundary_zeroes(boundary: dict[str, Any]) -> None:
    required_zeroes = (
        "source_import_performed",
        "artifact_copy_performed",
        "mixed_build_promotion_accepted",
        "effect_execution_performed",
        "command_execution_performed",
        "file_mutation_performed",
        "network_performed",
        "runtime_authority_granted",
        "production_readiness_claim",
    )
    for key in required_zeroes:
        if boundary.get(key) != 0:
            raise ValueError(f"boundary must preserve {key}=0")


def validate_manifest(manifest: dict[str, Any]) -> dict[str, Any]:
    if manifest.get("manifest_id") != "latticra-netplane-central-hub-intake":
        raise ValueError("unexpected manifest_id")
    if manifest.get("manifest_version") != 1:
        raise ValueError("unexpected manifest_version")

    boundary = manifest.get("boundary")
    if not isinstance(boundary, dict):
        raise ValueError("boundary must be an object")
    _require_boundary_zeroes(boundary)

    lanes = _lane_map(manifest)
    missing_lanes = [lane for lane in REQUIRED_LANES if lane not in lanes]
    if missing_lanes:
        raise ValueError(f"missing active lanes: {', '.join(missing_lanes)}")

    imported_lanes = [
        name
        for name, lane in lanes.items()
        if lane.get("import_decision") != "not-imported"
    ]
    if imported_lanes:
        raise ValueError(f"lanes must not be imported at intake: {', '.join(imported_lanes)}")

    separate_channels = manifest.get("separate_channels")
    if not isinstance(separate_channels, list):
        raise ValueError("separate_channels must be a list")
    warlock_separate = any(
        isinstance(channel, dict)
        and channel.get("lane") == "warlock-index"
        and channel.get("decision") == "separate-channel"
        for channel in separate_channels
    )
    if not warlock_separate:
        raise ValueError("warlock-index separate channel decision is required")

    fyr_lane = lanes["fyr"]
    rainbow_lane = lanes["rainbow"]
    fyr_checkout_gap = int(fyr_lane.get("local_checkout") == "not-present-as-fyr")
    rainbow_local_present = int(rainbow_lane.get("local_checkout") == "~/Documents/fyr")

    return {
        "active_lane_count": len(lanes),
        "required_lane_count": len(REQUIRED_LANES),
        "required_lanes_present": 1,
        "warlock_index_separate_channel": 1,
        "fyr_local_provenance_refresh_required": fyr_checkout_gap,
        "rainbow_local_checkout_present": rainbow_local_present,
    }


def build_receipt(manifest_path: Path = DEFAULT_MANIFEST) -> dict[str, Any]:
    manifest = _load_manifest(manifest_path)
    validation = validate_manifest(manifest)
    boundary = manifest["boundary"]

    return {
        "latticra_netplane_central_hub_intake_present": 1,
        "netplane_intake_id": "latticra-netplane-central-hub-intake",
        "netplane_intake_version": 1,
        "edge_checkpoint": boundary["edge_checkpoint"],
        "manifest_reference": MANIFEST_REFERENCE,
        "manifest_sha256": _canonical_sha256(manifest),
        "central_hub_declared": boundary["central_hub_declared"],
        "netplane_defined": boundary["netplane_defined"],
        "active_lanes": list(REQUIRED_LANES),
        "active_lane_count": validation["active_lane_count"],
        "required_lane_count": validation["required_lane_count"],
        "required_lanes_present": validation["required_lanes_present"],
        "kaiju_lane_present": 1,
        "l2_lane_present": 1,
        "l3_lane_present": 1,
        "l4_lane_present": 1,
        "fyr_lane_present": 1,
        "rainbow_lane_present": 1,
        "warlock_index_separate_channel": validation["warlock_index_separate_channel"],
        "fyr_local_provenance_refresh_required": validation[
            "fyr_local_provenance_refresh_required"
        ],
        "rainbow_local_checkout_present": validation["rainbow_local_checkout_present"],
        "source_import_performed": boundary["source_import_performed"],
        "artifact_copy_performed": boundary["artifact_copy_performed"],
        "mixed_build_promotion_accepted": boundary["mixed_build_promotion_accepted"],
        "effect_execution_performed": boundary["effect_execution_performed"],
        "command_execution_performed": boundary["command_execution_performed"],
        "file_mutation_performed": boundary["file_mutation_performed"],
        "network_performed": boundary["network_performed"],
        "runtime_authority_granted": boundary["runtime_authority_granted"],
        "production_readiness_claim": boundary["production_readiness_claim"],
        "next_recommended_lane": "kaiju-static-adapter-evidence-intake",
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", default=str(DEFAULT_MANIFEST))
    args = parser.parse_args()

    receipt = build_receipt(Path(args.manifest))
    print(json.dumps(receipt, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra netplane kaiju static adapter evidence intake: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing pattern in $file: $pattern"
}

doc='docs/LATTICRA_NETPLANE_KAIJU_STATIC_ADAPTER_EVIDENCE_INTAKE.md'
status='docs/status/LATTICRA_NETPLANE_KAIJU_STATIC_ADAPTER_EVIDENCE_INTAKE_STATUS.md'
manifest='fixtures/netplane/latticra-netplane-kaiju-static-adapter-evidence-manifest.json'
tool='tools/latticra_netplane_kaiju_static_adapter_inventory.py'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-netplane-kaiju-static-adapter-evidence-intake.yml'

for file in "$doc" "$status" "$manifest" "$tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_netplane_kaiju_static_adapter_evidence_intake_present=1' "$file"
  require_contains 'kaiju_static_adapter_evidence_intake_guard_present=1' "$file"
  require_contains 'intake_id=latticra-netplane-kaiju-static-adapter-evidence-intake' "$file"
  require_contains 'intake_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'manifest_reference=fixtures/netplane/latticra-netplane-kaiju-static-adapter-evidence-manifest.json' "$file"
  require_contains 'kaiju_static_adapter_inventory_tool=tools/latticra_netplane_kaiju_static_adapter_inventory.py' "$file"
  require_contains 'central_hub_intake_reference=docs/LATTICRA_NETPLANE_CENTRAL_HUB_INTAKE.md' "$file"
  require_contains 'kaiju_lane_present=1' "$file"
  require_contains 'kaiju_github=chasebryan/kaiju' "$file"
  require_contains 'kaiju_local_checkout=~/Documents/kaiju' "$file"
  require_contains 'kaiju_source_revision=93995843381d' "$file"
  require_contains 'kaiju_source_dirty_state=clean' "$file"
  require_contains 'kaiju_license_posture=Apache-2.0' "$file"
  require_contains 'kaiju_crate_count=11' "$file"
  require_contains 'kaiju_evidence_reference_count=8' "$file"
  require_contains 'kaiju_schema_marker_count=5' "$file"
  require_contains 'static_adapter_evidence_intake=1' "$file"
  require_contains 'source_import_performed=0' "$file"
  require_contains 'artifact_copy_performed=0' "$file"
  require_contains 'kaiju_command_executed=0' "$file"
  require_contains 'kaiju_source_vendored=0' "$file"
  require_contains 'kaiju_binary_ingested=0' "$file"
  require_contains 'kaiju_package_accepted=0' "$file"
  require_contains 'pcap_import_performed=0' "$file"
  require_contains 'live_probe_performed=0' "$file"
  require_contains 'port_scan_performed=0' "$file"
  require_contains 'privileged_capture_performed=0' "$file"
  require_contains 'network_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'plugin_runtime_accepted=0' "$file"
  require_contains 'mixed_build_promotion_accepted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'latticra_netplane_kaiju_static_adapter_evidence_intake: ok' "$file"
done

for pattern in \
  '"manifest_id": "latticra-netplane-kaiju-static-adapter-evidence-intake"' \
  '"lane": "kaiju"' \
  '"github": "chasebryan/kaiju"' \
  '"local_revision": "93995843381d"' \
  '"source_dirty_state": "clean"' \
  '"license": "Apache-2.0"' \
  '"crate_count": 11' \
  '"project_snapshot_schema": "kaiju.project.v1"' \
  '"network_snapshot_schema": "kaiju.network.v1"' \
  '"network_probe_schema": "kaiju.network.probe.v1"' \
  '"package_schema": "kaiju.package.v1"' \
  '"annotations_schema": "kaiju.annotations.v1"' \
  '"evidence_role": "workspace-package-metadata"' \
  '"evidence_role": "license-boundary"' \
  '"evidence_role": "authorized-offline-network-evidence-fixture"' \
  '"sha256:b5828da29e21e98c8fb7afeaa41c26f87ef12c375d2295a46d785b39aa7d3631"' \
  '"sha256:54d0f55de250d7704f583d3c930afec501357f0091eaa6a559be9c0b072f58b2"' \
  '"kaiju_command_executed": 0' \
  '"live_probe_performed": 0' \
  '"port_scan_performed": 0' \
  '"network_performed": 0' \
  '"runtime_authority_granted": 0' \
  '"plugin_runtime_accepted": 0'
do
  require_contains "$pattern" "$manifest"
done

python3 -m py_compile "$tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kaiju-static-adapter.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
tmp="$tmp_dir/kaiju-static-adapter.json"
python3 "$tool" > "$tmp"

for pattern in \
  '"latticra_netplane_kaiju_static_adapter_evidence_intake_present": 1' \
  '"kaiju_static_adapter_evidence_intake_guard_present": 1' \
  '"intake_id": "latticra-netplane-kaiju-static-adapter-evidence-intake"' \
  '"manifest_reference": "fixtures/netplane/latticra-netplane-kaiju-static-adapter-evidence-manifest.json"' \
  '"manifest_sha256": "sha256:' \
  '"kaiju_lane_present": 1' \
  '"kaiju_github": "chasebryan/kaiju"' \
  '"kaiju_source_revision": "93995843381d"' \
  '"kaiju_source_dirty_state": "clean"' \
  '"kaiju_license_posture": "Apache-2.0"' \
  '"kaiju_crate_count": 11' \
  '"kaiju_evidence_reference_count": 8' \
  '"kaiju_schema_marker_count": 5' \
  '"static_adapter_evidence_intake": 1' \
  '"source_import_performed": 0' \
  '"artifact_copy_performed": 0' \
  '"kaiju_command_executed": 0' \
  '"kaiju_source_vendored": 0' \
  '"kaiju_package_accepted": 0' \
  '"pcap_import_performed": 0' \
  '"live_probe_performed": 0' \
  '"port_scan_performed": 0' \
  '"privileged_capture_performed": 0' \
  '"network_performed": 0' \
  '"runtime_authority_granted": 0' \
  '"plugin_runtime_accepted": 0' \
  '"next_recommended_lane": "kaiju-package-metadata-receipt-schema"'
do
  require_contains "$pattern" "$tmp"
done

require_contains 'LATTICRA_NETPLANE_KAIJU_STATIC_ADAPTER_EVIDENCE_INTAKE_STATUS.md' "$status_index"
require_contains 'Latticra Netplane Kaiju Static Adapter Evidence Intake' "$docs_hub"
require_contains 'Kaiju static adapter evidence intake](docs/LATTICRA_NETPLANE_KAIJU_STATIC_ADAPTER_EVIDENCE_INTAKE.md)' "$root_readme"
require_contains 'Latest Latticra Netplane Kaiju static adapter evidence intake note: 2026-06-19 CDT' "$root_status"
require_contains 'Latest Latticra Netplane Kaiju static adapter evidence intake note: 2026-06-19 CDT' "$current_status"
require_contains 'Latest Latticra Netplane Kaiju static adapter evidence intake note: 2026-06-19 CDT' "$current_direction"
require_contains 'Latest Latticra Netplane Kaiju static adapter evidence intake note: 2026-06-19 CDT' "$upcoming_work"
require_contains 'latticra-netplane-kaiju-static-adapter-evidence-intake:' "$makefile"
require_contains 'sh ./scripts/test-latticra-netplane-kaiju-static-adapter-evidence-intake.sh' "$makefile"
require_contains 'latticra-netplane-kaiju-static-adapter-evidence-intake:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-netplane-kaiju-static-adapter-evidence-intake.sh' "$quality_guard"
require_contains 'Run Latticra Netplane Kaiju static adapter evidence intake guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-netplane-kaiju-static-adapter-evidence-intake.sh' "$workflow"

printf 'latticra_netplane_kaiju_static_adapter_evidence_intake: ok\n'

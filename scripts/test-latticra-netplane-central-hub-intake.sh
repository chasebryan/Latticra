#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra netplane central hub intake: %s\n' "$1" >&2
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

doc='docs/LATTICRA_NETPLANE_CENTRAL_HUB_INTAKE.md'
status='docs/status/LATTICRA_NETPLANE_CENTRAL_HUB_INTAKE_STATUS.md'
manifest='fixtures/netplane/latticra-netplane-central-hub-manifest.json'
tool='tools/latticra_netplane_inventory.py'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-netplane-central-hub-intake.yml'

for file in "$doc" "$status" "$manifest" "$tool" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_netplane_central_hub_intake_present=1' "$file"
  require_contains 'netplane_intake_id=latticra-netplane-central-hub-intake' "$file"
  require_contains 'netplane_intake_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'manifest_reference=fixtures/netplane/latticra-netplane-central-hub-manifest.json' "$file"
  require_contains 'netplane_inventory_tool=tools/latticra_netplane_inventory.py' "$file"
  require_contains 'central_hub_declared=1' "$file"
  require_contains 'netplane_defined=1' "$file"
  require_contains 'active_lane_count=7' "$file"
  require_contains 'required_lane_count=7' "$file"
  require_contains 'required_lanes_present=1' "$file"
  require_contains 'kaiju_lane_present=1' "$file"
  require_contains 'l2_lane_present=1' "$file"
  require_contains 'l3_lane_present=1' "$file"
  require_contains 'l4_lane_present=1' "$file"
  require_contains 'fyr_lane_present=1' "$file"
  require_contains 'rainbow_lane_present=1' "$file"
  require_contains 'warlock_index_separate_channel=1' "$file"
  require_contains 'fyr_local_provenance_refresh_required=1' "$file"
  require_contains 'rainbow_local_checkout_present=1' "$file"
  require_contains 'deny_by_default=1' "$file"
  require_contains 'source_import_performed=0' "$file"
  require_contains 'artifact_copy_performed=0' "$file"
  require_contains 'mixed_build_promotion_accepted=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed=0' "$file"
  require_contains 'network_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'Kaiju static adapter evidence intake.' "$file"
  require_contains 'latticra_netplane_central_hub_intake: ok' "$file"
done

for pattern in \
  '"lane": "kaiju"' \
  '"lane": "l2"' \
  '"lane": "l3"' \
  '"lane": "l4"' \
  '"lane": "fyr"' \
  '"lane": "rainbow"' \
  '"lane": "netplane"' \
  '"lane": "warlock-index"' \
  '"decision": "separate-channel"' \
  '"source_import_performed": 0' \
  '"network_performed": 0' \
  '"runtime_authority_granted": 0'
do
  require_contains "$pattern" "$manifest"
done

python3 -m py_compile "$tool"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-netplane-intake.XXXXXX")"
trap 'rm -rf "$tmp_dir"' EXIT INT HUP TERM
tmp="$tmp_dir/netplane.json"
python3 "$tool" > "$tmp"

for pattern in \
  '"latticra_netplane_central_hub_intake_present": 1' \
  '"netplane_intake_id": "latticra-netplane-central-hub-intake"' \
  '"manifest_reference": "fixtures/netplane/latticra-netplane-central-hub-manifest.json"' \
  '"manifest_sha256": "sha256:' \
  '"central_hub_declared": 1' \
  '"netplane_defined": 1' \
  '"active_lane_count": 7' \
  '"required_lanes_present": 1' \
  '"kaiju_lane_present": 1' \
  '"l2_lane_present": 1' \
  '"l3_lane_present": 1' \
  '"l4_lane_present": 1' \
  '"fyr_lane_present": 1' \
  '"rainbow_lane_present": 1' \
  '"warlock_index_separate_channel": 1' \
  '"fyr_local_provenance_refresh_required": 1' \
  '"source_import_performed": 0' \
  '"artifact_copy_performed": 0' \
  '"network_performed": 0' \
  '"runtime_authority_granted": 0' \
  '"next_recommended_lane": "kaiju-static-adapter-evidence-intake"'
do
  require_contains "$pattern" "$tmp"
done

require_contains 'LATTICRA_NETPLANE_CENTRAL_HUB_INTAKE_STATUS.md' "$status_index"
require_contains 'Latticra Netplane Central Hub Intake' "$docs_hub"
require_contains 'Netplane central hub intake](docs/LATTICRA_NETPLANE_CENTRAL_HUB_INTAKE.md)' "$root_readme"
require_contains 'Latest Latticra Netplane central hub intake note: 2026-06-19 CDT' "$root_status"
require_contains 'Latest Latticra Netplane central hub intake note: 2026-06-19 CDT' "$current_status"
require_contains 'Latest Latticra Netplane central hub intake note: 2026-06-19 CDT' "$current_direction"
require_contains 'Latest Latticra Netplane central hub intake note: 2026-06-19 CDT' "$upcoming_work"
require_contains 'latticra-netplane-central-hub-intake:' "$makefile"
require_contains 'sh ./scripts/test-latticra-netplane-central-hub-intake.sh' "$makefile"
require_contains 'latticra-netplane-central-hub-intake:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-netplane-central-hub-intake.sh' "$quality_guard"
require_contains 'Run Latticra Netplane central hub intake guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-netplane-central-hub-intake.sh' "$workflow"

printf 'latticra_netplane_central_hub_intake: ok\n'

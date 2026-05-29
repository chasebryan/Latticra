#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra identity replay model3 failure visual suite: %s\n' "$1" >&2
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

doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_FAILURE_VISUAL_SUITE.md'
status='docs/status/LATTICRA_IDENTITY_REPLAY_MODEL3_FAILURE_VISUAL_SUITE_STATUS.md'
one_page='docs/LATTICRA_HIGGS_CHALLENGE_ONE_PAGE.md'
rejection_doc='docs/LATTICRA_IDENTITY_REPLAY_MODEL3_REJECTION_ANALYSIS.md'
generator='tools/render_latticra_identity_replay_model3_failure_visuals.py'
asset_dir='docs/assets/identity-replay-model3-failure'
ratio_chart="$asset_dir/model3-failure-ratio-chart.svg"
ordering_chart="$asset_dir/model3-failure-ordering-chart.svg"
sector_chart="$asset_dir/model3-failure-sector-chart.svg"
manifest="$asset_dir/render-manifest.txt"
manifest_json="$asset_dir/render-manifest.json"
prediction_json="$asset_dir/model3-failure-prediction.json"
evaluation_json="$asset_dir/model3-failure-evaluation.json"
analysis_json="$asset_dir/model3-failure-rejection-analysis.json"
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
handbook='docs/latticra-system-substrate/README.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-identity-replay-model3-failure-visual-suite.yml'

for file in "$doc" "$status" "$one_page" "$rejection_doc" "$generator" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$handbook" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

python3 -m py_compile "$generator"
python3 "$generator" >/dev/null

for file in "$ratio_chart" "$ordering_chart" "$sector_chart" "$manifest" "$manifest_json" "$prediction_json" "$evaluation_json" "$analysis_json"
do
  require_file "$file"
done

for file in "$doc" "$status" "$manifest"
do
  require_contains 'latticra_identity_replay_model3_failure_visual_suite_rendered=1' "$file"
  require_contains 'visual_suite_id=latticra-identity-replay-model3-failure-visual-suite' "$file"
  require_contains 'visual_mode=static-svg-from-receipted-model3-rejection-analysis' "$file"
  require_contains 'ratio_chart=docs/assets/identity-replay-model3-failure/model3-failure-ratio-chart.svg' "$file"
  require_contains 'ordering_chart=docs/assets/identity-replay-model3-failure/model3-failure-ordering-chart.svg' "$file"
  require_contains 'sector_chart=docs/assets/identity-replay-model3-failure/model3-failure-sector-chart.svg' "$file"
  require_contains 'model3_prediction_law_rejected=1' "$file"
  require_contains 'dynamic_range_deficit_factor=5.4744404767584652275663280083338001338306169886721631882430541171586743908036395' "$file"
  require_contains 'single_global_amplifier_insufficient=1' "$file"
  require_contains 'required_refined_model3_property=target_blind_sector_resolved_topological_charge_with_family_monotonicity' "$file"
  require_contains 'mass_ratio_recovery_claimed=0' "$file"
  require_contains 'higgs_checkmate_claimed=0' "$file"
  require_contains 'simulation_proven=0' "$file"
  require_contains 'scientific_claim_promoted=0' "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_identity_replay_model3_failure_visual_suite_present=1' "$file"
  require_contains 'visual_generator=tools/render_latticra_identity_replay_model3_failure_visuals.py' "$file"
  require_contains 'ordering_mismatch_visualized=1' "$file"
  require_contains 'sector_placement_failure_visualized=1' "$file"
  require_contains 'low_electroweak_below_electron_targets=Higgs boson,Z boson' "$file"
  require_contains 'higgs_only_causal_closure_challenged=1' "$file"
  require_contains 'physics_bound_by_simulative_concepts_claimed=0' "$file"
done

require_contains 'Model-3 Failure: Predicted vs Target Mass Ratios' "$ratio_chart"
require_contains 'Model-3 Failure: Identity Ordering Mismatch' "$ordering_chart"
require_contains 'Model-3 Failure: Sector Placement' "$sector_chart"
require_contains '<svg xmlns="http://www.w3.org/2000/svg"' "$ratio_chart"
require_contains '<svg xmlns="http://www.w3.org/2000/svg"' "$ordering_chart"
require_contains '<svg xmlns="http://www.w3.org/2000/svg"' "$sector_chart"
require_contains '"latticra_identity_replay_model3_failure_visual_suite_rendered": 1' "$manifest_json"
require_contains '"model3_prediction_law_rejected": 1' "$analysis_json"
require_contains '"model3_prediction_receipt_hash": "sha256:' "$prediction_json"
require_contains '"model3_evaluation_receipt_hash": "sha256:' "$evaluation_json"

require_contains 'Model-3 Failure Visual Suite' "$one_page"
require_contains 'Model-3 Failure Visual Suite' "$rejection_doc"
require_contains 'LATTICRA_IDENTITY_REPLAY_MODEL3_FAILURE_VISUAL_SUITE_STATUS.md' "$status_index"
require_contains 'Model-3 Failure Visual Suite' "$docs_hub"
require_contains 'Model-3 Failure Visual Suite](docs/LATTICRA_IDENTITY_REPLAY_MODEL3_FAILURE_VISUAL_SUITE.md)' "$root_readme"
require_contains 'Latest Latticra identity-replay Model-3 failure visual suite note: 2026-05-29 CDT' "$root_status"
require_contains 'Latest Latticra identity-replay Model-3 failure visual suite note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest Latticra identity-replay Model-3 failure visual suite note: 2026-05-29 CDT' "$current_direction"
require_contains 'Latest Latticra identity-replay Model-3 failure visual suite note: 2026-05-29 CDT' "$upcoming_work"
require_contains 'Model-3 failure visual suite' "$handbook"
require_contains 'latticra-identity-replay-model3-failure-visual-suite:' "$makefile"
require_contains 'sh ./scripts/test-latticra-identity-replay-model3-failure-visual-suite.sh' "$makefile"
require_contains 'latticra-identity-replay-model3-failure-visual-suite:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-identity-replay-model3-failure-visual-suite.sh' "$quality_guard"
require_contains 'Run Latticra identity-replay Model-3 failure visual suite guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"

printf 'latticra_identity_replay_model3_failure_visual_suite: ok\n'

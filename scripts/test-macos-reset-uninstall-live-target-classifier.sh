#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos reset/uninstall live-target classifier: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-target classifier: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos reset/uninstall live-target classifier: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos reset/uninstall live-target classifier: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

write_marker() {
  marker="$1"
  {
    printf 'LATTICRA_INSTALLER_MANAGED=1\n'
    printf 'LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1\n'
  } > "$marker"
}

doc='docs/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER_STATUS.md'
script='scripts/macos-reset-uninstall-live-target-classifier.sh'
workflow='.github/workflows/macos-reset-uninstall-live-target-classifier.yml'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme='README.md'
reset_doc='docs/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT.md'
reset_status='docs/status/MACOS_RESET_UNINSTALL_DRY_RUN_CONTRACT_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$readme"
require_file "$reset_doc"
require_file "$reset_status"

require_contains 'Status: no-effect macOS reset/uninstall live-target classifier' "$doc"
require_contains 'sh scripts/macos-reset-uninstall-live-target-classifier.sh' "$doc"
require_contains 'macos_reset_uninstall_live_target_classifier_present=1' "$doc"
require_contains 'reset_uninstall_live_classifier_decision=blocked-unmanaged-targets-preserve' "$doc"
require_contains 'app_bundle_target_state=managed' "$doc"
require_contains 'app_bundle_target_state=unmanaged-preserve' "$doc"
require_contains 'file_delete_performed=0' "$doc"
require_contains 'directory_delete_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'macos_reset_uninstall_live_target_classifier: ok' "$doc"
require_contains 'Add a macOS reset/uninstall evidence-bundle contract' "$doc"

require_contains 'Status: no-effect reset/uninstall live-target classifier status' "$status"
require_contains 'macos_reset_uninstall_live_target_classifier_present=1' "$status"
require_contains 'macos_reset_uninstall_live_target_classifier_guard_present=1' "$status"
require_contains 'target_states_recorded=1' "$status"
require_contains 'managed_target_detected=report-runtime' "$status"
require_contains 'unmanaged_target_detected=report-runtime' "$status"
require_contains 'file_delete_performed=0' "$status"
require_contains 'directory_delete_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'network_performed=0' "$status"
require_contains 'not macOS reset evidence' "$status"

require_contains 'MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER_STATUS.md' "$index"
require_contains 'macOS reset/uninstall live-target classifier status' "$index"
require_contains 'stage_4_macos_reset_uninstall_live_target_classifier=present' "$transfer_plan"
require_contains 'docs/MACOS_RESET_UNINSTALL_LIVE_TARGET_CLASSIFIER.md' "$transfer_plan"
require_contains 'scripts/macos-reset-uninstall-live-target-classifier.sh' "$transfer_plan"
require_contains 'macos_reset_uninstall_live_target_classifier_present=1' "$transfer_status"
require_contains 'macos_reset_uninstall_live_target_classifier_present=1' "$readme"
require_contains 'sh scripts/macos-reset-uninstall-live-target-classifier.sh' "$readme"
require_contains 'macOS reset/uninstall live-target classifier' "$reset_doc"
require_contains 'macos_reset_uninstall_live_target_classifier_present=1' "$reset_status"

require_contains 'MACOS RESET UNINSTALL LIVE TARGET CLASSIFIER' "$script"
require_contains 'reset_uninstall_live_classifier_decision=$CLASSIFIER_DECISION' "$script"
require_contains 'app_bundle_target_state=$APP_BUNDLE_STATE' "$script"
require_contains 'cli_wrapper_target_state=$CLI_WRAPPER_STATE' "$script"
require_contains 'managed_target_detected=$MANAGED_TARGET_DETECTED' "$script"
require_contains 'unmanaged_target_detected=$UNMANAGED_TARGET_DETECTED' "$script"
require_contains 'file_delete_performed=0' "$script"
require_contains 'directory_delete_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'network_performed=0' "$script"
require_contains 'next_lane=macos-reset-uninstall-live-runner-acceptance-gate-contract' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'rmdir ' "$script"
require_not_contains 'sudo ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"

tmp_root=$(mktemp -d "${TMPDIR:-/tmp}/latticra-macos-live-target-classifier.XXXXXX")
cleanup() {
  rm -rf "$tmp_root"
}
trap cleanup EXIT

absent_home="$tmp_root/absent-home"
managed_home="$tmp_root/managed-home"
unmanaged_home="$tmp_root/unmanaged-home"
mkdir -p "$absent_home" "$managed_home" "$unmanaged_home"

absent_output=$(HOME="$absent_home" sh "$script")
require_output_contains "$absent_output" 'MACOS RESET UNINSTALL LIVE TARGET CLASSIFIER'
require_output_contains "$absent_output" 'reset_uninstall_live_target_classifier_status=ok'
require_output_contains "$absent_output" 'path_guard_status=allowed-user-local-classification'
require_output_contains "$absent_output" 'app_bundle_target_state=absent'
require_output_contains "$absent_output" 'app_support_prefix_target_state=absent'
require_output_contains "$absent_output" 'cli_wrapper_target_state=absent'
require_output_contains "$absent_output" 'reset_receipts_dir_target_state=absent'
require_output_contains "$absent_output" 'managed_target_detected=0'
require_output_contains "$absent_output" 'unmanaged_target_detected=0'
require_output_contains "$absent_output" 'absent_target_detected=1'
require_output_contains "$absent_output" 'reset_uninstall_live_classifier_decision=ready-no-targets-observed-no-effect'
require_output_contains "$absent_output" 'file_delete_performed=0'
require_output_contains "$absent_output" 'directory_delete_performed=0'
require_output_contains "$absent_output" 'next_lane=macos-reset-uninstall-live-runner-acceptance-gate-contract'

mkdir -p "$managed_home/Applications/Latticra Panel.app/Contents/Resources/latticra"
mkdir -p "$managed_home/Library/Application Support/Latticra"
mkdir -p "$managed_home/Library/Application Support/Latticra Reset Receipts"
mkdir -p "$managed_home/.local/bin"
write_marker "$managed_home/Applications/Latticra Panel.app/Contents/Resources/latticra/MANAGED_BY_LATTICRA"
write_marker "$managed_home/Library/Application Support/Latticra/MANAGED_BY_LATTICRA"
write_marker "$managed_home/Library/Application Support/Latticra Reset Receipts/MANAGED_BY_LATTICRA"
write_marker "$managed_home/.local/bin/latticra-panel"

managed_output=$(HOME="$managed_home" sh "$script")
require_output_contains "$managed_output" 'app_bundle_target_state=managed'
require_output_contains "$managed_output" 'app_support_prefix_target_state=managed'
require_output_contains "$managed_output" 'cli_wrapper_target_state=managed'
require_output_contains "$managed_output" 'reset_receipts_dir_target_state=managed'
require_output_contains "$managed_output" 'managed_target_detected=1'
require_output_contains "$managed_output" 'unmanaged_target_detected=0'
require_output_contains "$managed_output" 'reset_uninstall_live_classifier_decision=ready-managed-targets-observed-no-effect'
require_output_contains "$managed_output" 'managed_app_bundle_removal_performed=0'
require_output_contains "$managed_output" 'managed_application_support_removal_performed=0'

mkdir -p "$unmanaged_home/Applications/Latticra Panel.app"
mkdir -p "$unmanaged_home/.local/bin"
printf '#!/usr/bin/env sh\n' > "$unmanaged_home/.local/bin/latticra-panel"

unmanaged_output=$(HOME="$unmanaged_home" sh "$script")
require_output_contains "$unmanaged_output" 'app_bundle_target_state=unmanaged-preserve'
require_output_contains "$unmanaged_output" 'cli_wrapper_target_state=unmanaged-preserve'
require_output_contains "$unmanaged_output" 'unmanaged_target_detected=1'
require_output_contains "$unmanaged_output" 'classifier_phase_3_status=preserve-unmanaged-targets'
require_output_contains "$unmanaged_output" 'reset_uninstall_live_classifier_decision=blocked-unmanaged-targets-preserve'
require_output_contains "$unmanaged_output" 'file_delete_performed=0'
require_output_contains "$unmanaged_output" 'directory_delete_performed=0'

unsafe_output=$(HOME="$absent_home" sh "$script" --app-bundle /Applications/Latticra.app)
require_output_contains "$unsafe_output" 'path_guard_status=blocked-unsafe-user-local-path'
require_output_contains "$unsafe_output" 'unsafe_path_detected=1'
require_output_contains "$unsafe_output" 'app_bundle_target_state=not-classified-unsafe-path'
require_output_contains "$unsafe_output" 'classifier_phase_1_status=blocked-unsafe-path'
require_output_contains "$unsafe_output" 'reset_uninstall_live_classifier_decision=blocked-unsafe-path'
require_output_contains "$unsafe_output" 'host_mutation_performed=0'
require_output_contains "$unsafe_output" 'network_performed=0'

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'sh scripts/test-macos-reset-uninstall-live-target-classifier.sh' "$workflow"

printf 'macos_reset_uninstall_live_target_classifier: ok\n'

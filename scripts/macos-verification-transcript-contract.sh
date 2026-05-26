#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-verification-transcript-contract.sh

Emits the no-effect macOS verification transcript contract for a future
user-local app bundle install. It defines required post-write evidence, but it
does not verify an install, write transcripts, create app bundles, mutate host
state, or claim macOS installation.
USAGE
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "unknown argument: $1" >&2
      usage >&2
      exit 64
      ;;
  esac
done

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
UNAME_S=$(uname -s 2>/dev/null || printf 'unknown')
UNAME_M=$(uname -m 2>/dev/null || printf 'unknown')

cat <<REPORT
MACOS VERIFICATION TRANSCRIPT CONTRACT

verification_transcript_contract_status=ok
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
macos_verification_transcript_contract_present=1
verification_transcript_contract_state=defined-no-effect
verification_transcript_contract_decision=contract-defined-evidence-not-present
verification_transcript_required=1
verification_transcript_evidence_present=0
macos_install_verified=0
commit_user_local_managed_artifacts=0
managed_write_implementation_present=0
reset_uninstall_implementation_present=0
app_support_prefix_expected=$HOME/Library/Application Support/Latticra
app_bundle_expected=$HOME/Applications/Latticra Panel.app
cli_wrapper_expected=$HOME/.local/bin/latticra-panel
receipts_dir_expected=$HOME/Library/Application Support/Latticra/receipts
bundle_identifier_expected=systems.latticra.panel
bundle_executable_expected=latticra-panel
transcript_line_host_identity_required=1
transcript_line_architecture_required=1
transcript_line_app_bundle_path_required=1
transcript_line_info_plist_identifier_required=1
transcript_line_panel_executable_digest_required=1
transcript_line_icon_asset_digest_required=1
transcript_line_application_support_marker_required=1
transcript_line_cli_wrapper_marker_required=1
transcript_line_receipt_manifest_required=1
transcript_line_authority_denials_required=1
transcript_line_candidate_flow_required=1
transcript_line_commit_gate_required=1
transcript_line_reset_uninstall_dry_run_required=1
host_os_macos_recorded_required=1
architecture_recorded_required=1
managed_app_bundle_present_required=1
info_plist_present_required=1
info_plist_bundle_identifier_required=1
app_executable_present_required=1
app_executable_executable_required=1
app_executable_digest_required=1
icon_asset_present_required=1
icon_asset_digest_required=1
application_support_marker_required=1
cli_wrapper_present_required=1
cli_wrapper_marker_required=1
receipts_present_required=1
receipt_completeness_required=1
authority_denial_fields_required=1
candidate_integration_ready_required=1
commit_gate_closed_until_evidence_required=1
reset_uninstall_dry_run_required=1
macos_reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
reset_uninstall_dry_run_evidence_present=0
unmanaged_target_preservation_required=1
seal_report_only_output_required=1
lat_or_lir_no_effect_probe_required=1
verification_transcript_run_performed=0
verification_transcript_written=0
application_support_write_performed=0
payload_write_performed=0
config_write_performed=0
receipt_write_performed=0
app_bundle_write_performed=0
info_plist_write_performed=0
app_executable_write_performed=0
app_icon_write_performed=0
cli_wrapper_write_performed=0
shell_profile_mutation_performed=0
installer_write_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
runtime_authority_granted=0
production_installer_ready=0
next_lane=macos-reset-uninstall-absence-report-contract
REPORT

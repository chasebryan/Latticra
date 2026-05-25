#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia offline ai stage 0: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia offline ai stage 0: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status='docs/status/NADIA_OFFLINE_AI_STAGE_0_STATUS.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
manifest='installer/manifests/components.toml'
default_config='installer/configs/default.installer.toml'
local_config='installer/configs/local-prefix-example.installer.toml'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
apply_script='installer/scripts/latticra-installer-apply.sh'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'

require_file "$foundation"
require_file "$status"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$manifest"
require_file "$default_config"
require_file "$local_config"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$apply_script"
require_file "$installer_readme"
require_file "$ui_model"

require_contains 'public_name=Nadia' "$foundation"
require_contains 'interactive_name=Nadia' "$foundation"
require_contains 'implementation_name=Nadia Witness Foundation' "$foundation"
require_contains 'documentation_code_name=Nadia Witness Foundation' "$foundation"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$foundation"
require_contains 'command_name=latticra-nadia' "$foundation"
require_contains 'component_key=nadia_offline_ai' "$foundation"
require_contains 'Nobel Peace Prize laureate Nadia Murad' "$foundation"
require_contains 'community_awareness_posture=1' "$foundation"
require_contains 'Stage-0 makes Nadia visible and installable without claiming model capability.' "$foundation"
require_contains 'panel_install_surface_present=1' "$foundation"
require_contains 'console_interop_surface_present=1' "$foundation"
require_contains 'model_runtime_present=0' "$foundation"
require_contains 'model_weights_installed=0' "$foundation"
require_contains 'network_authority=0' "$foundation"
require_contains 'tool_execution_authority=0' "$foundation"
require_contains 'self_modification_authority=0' "$foundation"
require_contains 'productivity_ledger=operator-reviewed-local' "$foundation"
require_contains 'sh scripts/test-nadia-offline-ai-stage-0.sh' "$foundation"

require_contains 'Status: foundation status record' "$status"
require_contains 'nadia_name_selected=1' "$status"
require_contains 'nadia_namesake=Nadia Murad' "$status"
require_contains 'nadia_system_name=Latticra Nadia Witness Foundation' "$status"
require_contains 'implementation_name=Nadia Witness Foundation' "$status"
require_contains 'nadia_panel_component_present=1' "$status"
require_contains 'nadia_console_status_surface_present=1' "$status"
require_contains 'human_dignity_principle=1' "$status"
require_contains 'model_runtime_present=0' "$status"
require_contains 'weight_training=0' "$status"
require_contains 'production_ai_claimed=0' "$status"

require_contains 'NADIA_OFFLINE_AI_STAGE_0_STATUS.md' "$status_index"
require_contains 'NADIA_OFFLINE_AI_FOUNDATION.md' "$foundation_index"
require_contains 'Nadia offline AI Stage-0 foundation + guardrails' "$foundation_index"
require_contains 'Nadia Offline AI' "$readme"
require_contains 'nadia_offline_ai_stage_0_foundation_present=1' "$readme"
require_contains 'latticra-nadia' "$readme"
require_contains 'Nadia Murad' "$readme"
require_contains 'Latest Nadia offline AI Stage-0 foundation note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia offline AI Stage-0 foundation note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia offline AI Stage-0 foundation for Panel installability, Console interoperability, and awareness principles' "$current_status"

require_contains '[components.nadia_offline_ai]' "$manifest"
require_contains 'label = "Nadia offline AI foundation"' "$manifest"
require_contains 'default_enabled = false' "$manifest"
require_contains 'No sexual user functionality, dialogue generation, prompt text receipt, prompt source reading, prompt buffer allocation, prompt tokenization, prompt materialization, tokenizer artifact path resolution, tokenizer artifact opening, tokenizer artifact reading, tokenizer artifact scanning, tokenizer artifact hashing, tokenizer artifact measurement, tokenizer artifact digest recording, tokenizer artifact size recording, tokenizer artifact verification, tokenizer artifact digest comparison, tokenizer artifact size comparison, tokenizer artifact binding, tokenizer manifest loading, tokenizer manifest parsing, tokenizer file access, tokenizer vocabulary loading, prompt evaluation, inference, tool execution, model installation, training, distillation, source mutation, or network authority.' "$manifest"
require_contains 'nadia_offline_ai = false' "$default_config"
require_contains 'nadia_offline_ai = false' "$local_config"

require_contains 'pub nadia_offline_ai: bool' "$panel_config"
require_contains 'nadia_offline_ai: false' "$panel_config"
require_contains 'nadia_offline_ai={}' "$panel_config"
require_contains 'Nadia offline AI foundation' "$panel_ui"
require_contains 'nadia status' "$panel_ui"
require_contains 'name=Nadia' "$panel_ui"
require_contains 'implementation_name=Nadia Witness Foundation' "$panel_ui"
require_contains 'model_runtime_invoked=0 inference_performed=0' "$panel_ui"

require_contains 'NADIA_OFFLINE_AI=$(cfg nadia_offline_ai false)' "$apply_script"
require_contains 'nadia_offline_ai=$NADIA_OFFLINE_AI' "$apply_script"
require_contains 'component_selected=$NADIA_OFFLINE_AI' "$apply_script"
require_contains 'nadia-offline-ai.installed' "$apply_script"
require_contains 'latticra-nadia' "$apply_script"
require_contains 'human_dignity_principle=1' "$apply_script"
require_contains 'model_runtime_present = false' "$apply_script"
require_contains 'model_runtime_present=0' "$apply_script"
require_contains 'self_modification_authority=0' "$apply_script"

require_contains 'Nadia offline AI foundation' "$installer_readme"
require_contains 'nadia status' "$installer_readme"
require_contains 'Nadia Murad' "$installer_readme"
require_contains 'No sexual user functionality, dialogue generation, prompt text receipt, prompt source reading, prompt buffer allocation, prompt tokenization, prompt materialization, tokenizer artifact path resolution, tokenizer artifact opening, tokenizer artifact reading, tokenizer artifact scanning, tokenizer artifact hashing, tokenizer artifact measurement, tokenizer artifact digest recording, tokenizer artifact size recording, tokenizer artifact verification, tokenizer artifact digest comparison, tokenizer artifact size comparison, tokenizer artifact binding, tokenizer manifest loading, tokenizer manifest parsing, tokenizer file access, tokenizer vocabulary loading, inference, prompt evaluation, tool execution, model installation, training, distillation, source mutation, or network authority are installed.' "$installer_readme"
require_contains 'Nadia offline AI foundation' "$ui_model"
require_contains "Nadia's Stage-0, Stage-1, Stage-2, Stage-3, Stage-4, Stage-5, Stage-6, Stage-7, Stage-8, Stage-9, Stage-10, Stage-11, Stage-12, Stage-13, Stage-14, Stage-15, Stage-16, Stage-17, Stage-18, Stage-19, Stage-20, Stage-21, and Stage-22 console surfaces are metadata-only" "$ui_model"

printf 'nadia_offline_ai_stage_0: ok\n'

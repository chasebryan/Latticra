#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia runtime profile stage 2: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia runtime profile stage 2: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia runtime profile stage 2: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage2_doc='docs/NADIA_RUNTIME_PROFILE_STAGE_2.md'
stage2_status='docs/status/NADIA_RUNTIME_PROFILE_STAGE_2_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
runtime_script='scripts/nadia-runtime-profile.sh'
stage2_guard='scripts/test-nadia-runtime-profile-stage-2.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
makefile='Makefile'

require_file "$stage2_doc"
require_file "$stage2_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$runtime_script"
require_file "$stage2_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$makefile"

require_contains 'Status: Stage-2 implementation contract' "$stage2_doc"
require_contains 'nadia_stage_2_runtime_profile_present=1' "$stage2_doc"
require_contains 'runtime_profile_command=scripts/nadia-runtime-profile.sh' "$stage2_doc"
require_contains 'installed_runtime_profile_command=latticra-nadia runtime-profile' "$stage2_doc"
require_contains 'model_file_measurement=operator_provided_optional' "$stage2_doc"
require_contains 'model_runtime_invoked=0' "$stage2_doc"
require_contains 'inference_performed=0' "$stage2_doc"
require_contains 'prompt_evaluated=0' "$stage2_doc"
require_contains 'sh scripts/test-nadia-runtime-profile-stage-2.sh' "$stage2_doc"

require_contains 'Status: implementation status record' "$stage2_status"
require_contains 'nadia_runtime_profile_generator_present=1' "$stage2_status"
require_contains 'runtime_family=llama.cpp-compatible' "$stage2_status"
require_contains 'model_format=gguf' "$stage2_status"
require_contains 'model_weights_installed=0' "$stage2_status"

require_contains 'Stage-2: Offline Inference Runtime' "$foundation"
require_contains 'scripts/nadia-runtime-profile.sh' "$foundation"
require_contains 'NADIA_RUNTIME_PROFILE_STAGE_2.md' "$foundation_index"
require_contains 'NADIA_RUNTIME_PROFILE_STAGE_2_STATUS.md' "$status_index"
require_contains 'nadia_stage_2_runtime_profile_present=1' "$readme"
require_contains 'Latest Nadia runtime profile Stage-2 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia runtime profile Stage-2 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia runtime profile Stage-2' "$current_status"

require_contains 'NADIA RUNTIME PROFILE' "$runtime_script"
require_contains 'runtime_family=$RUNTIME_FAMILY' "$runtime_script"
require_contains 'model_runtime_invoked=0' "$runtime_script"
require_contains 'inference_performed=0' "$runtime_script"
require_contains 'prompt_evaluated=0' "$runtime_script"
require_contains 'model_file_copied=0' "$runtime_script"
require_not_contains 'curl ' "$runtime_script"
require_not_contains 'wget ' "$runtime_script"
require_not_contains 'ssh ' "$runtime_script"

require_contains 'runtime-profile' "$apply_script"
require_contains 'scripts/nadia-runtime-profile.sh' "$apply_script"
require_contains 'runtime_profile_stage=2-runtime-profile-boundary' "$panel_config"
require_contains 'nadia runtime' "$panel_ui"
require_contains 'latticra-nadia runtime-profile' "$installer_readme"
require_contains 'nadia-runtime' "$makefile"

out='/private/tmp/latticra-nadia-stage2-runtime-test'
model='/private/tmp/latticra-nadia-stage2-model.gguf'
rm -rf "$out"
mkdir -p "$out"
printf 'not a real model fixture\n' > "$model"
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage2-test sh "$runtime_script" --model "$model" --context-tokens 8192 --memory-mib 16384 --output "$out" >/tmp/latticra-nadia-stage2-runtime-test.out
profile="$out/nadia-runtime-profile-stage2-test.txt"

require_file "$profile"
require_file "$out/latest-runtime-profile.txt"
require_contains 'stage=2-runtime-profile-boundary' "$profile"
require_contains 'runtime_family=llama.cpp-compatible' "$profile"
require_contains 'model_format=gguf' "$profile"
require_contains 'model_file_present=1' "$profile"
require_contains 'model_file_copied=0' "$profile"
require_contains 'context_window_tokens=8192' "$profile"
require_contains 'memory_budget_mib=16384' "$profile"
require_contains 'network_authority=0' "$profile"
require_contains 'model_runtime_invoked=0' "$profile"
require_contains 'inference_performed=0' "$profile"
require_contains 'prompt_evaluated=0' "$profile"
require_contains 'source_mutation_authority=0' "$profile"
require_contains 'community_awareness_posture=1' "$profile"

printf 'nadia_runtime_profile_stage_2: ok\n'

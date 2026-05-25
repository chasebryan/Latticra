#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia local context engine stage 1: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia local context engine stage 1: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia local context engine stage 1: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage1_doc='docs/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md'
stage1_status='docs/status/NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
context_script='scripts/nadia-context-pack.sh'
stage0_guard='scripts/test-nadia-offline-ai-stage-0.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'

require_file "$stage1_doc"
require_file "$stage1_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$context_script"
require_file "$stage0_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"

require_contains 'Status: Stage-1 implementation contract' "$stage1_doc"
require_contains 'nadia_stage_1_local_context_engine_present=1' "$stage1_doc"
require_contains 'context_pack_command=scripts/nadia-context-pack.sh' "$stage1_doc"
require_contains 'installed_context_pack_command=latticra-nadia context-pack' "$stage1_doc"
require_contains 'network_authority=0' "$stage1_doc"
require_contains 'model_runtime_present=0' "$stage1_doc"
require_contains 'source_mutation_authority=0' "$stage1_doc"
require_contains 'sh scripts/test-nadia-local-context-engine-stage-1.sh' "$stage1_doc"

require_contains 'Status: implementation status record' "$stage1_status"
require_contains 'nadia_context_pack_generator_present=1' "$stage1_status"
require_contains 'local_file_read_for_indexing=operator_invoked' "$stage1_status"
require_contains 'training_performed=0' "$stage1_status"

require_contains 'Stage-1: Local Context Engine' "$foundation"
require_contains 'scripts/nadia-context-pack.sh' "$foundation"
require_contains 'NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1.md' "$foundation_index"
require_contains 'NADIA_LOCAL_CONTEXT_ENGINE_STAGE_1_STATUS.md' "$status_index"
require_contains 'nadia_stage_1_local_context_engine_present=1' "$readme"
require_contains 'Latest Nadia local context engine Stage-1 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia local context engine Stage-1 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia local context engine Stage-1' "$current_status"

require_contains 'NADIA LOCAL CONTEXT PACK' "$context_script"
require_contains 'network_authority=0' "$context_script"
require_contains 'model_runtime_present=0' "$context_script"
require_contains 'source_mutation_authority=0' "$context_script"
require_contains 'NADIA_CONTEXT_PACK=' "$context_script"
require_not_contains 'curl ' "$context_script"
require_not_contains 'wget ' "$context_script"
require_not_contains 'ssh ' "$context_script"

require_contains 'context-pack' "$apply_script"
require_contains 'scripts/nadia-context-pack.sh' "$apply_script"
require_contains 'context_engine_stage=1-local-context-engine' "$panel_config"
require_contains 'nadia context' "$panel_ui"
require_contains 'latticra-nadia context-pack' "$installer_readme"

out='/private/tmp/latticra-nadia-stage1-context-test'
rm -rf "$out"
mkdir -p "$out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage1-test sh "$context_script" --repo . --output "$out" >/tmp/latticra-nadia-stage1-context-test.out
pack="$out/nadia-context-pack-stage1-test.txt"
index="$out/nadia-context-file-index-stage1-test.tsv"

require_file "$pack"
require_file "$index"
require_file "$out/latest-context-pack.txt"
require_file "$out/latest-file-index.tsv"
require_contains 'stage=1-local-context-engine' "$pack"
require_contains 'network_authority=0' "$pack"
require_contains 'model_runtime_present=0' "$pack"
require_contains 'source_mutation_authority=0' "$pack"
require_contains 'community_awareness_posture=1' "$pack"
require_contains 'README.md' "$index"
require_contains 'docs/NADIA_OFFLINE_AI_FOUNDATION.md' "$index"
require_contains 'scripts/nadia-context-pack.sh' "$index"

printf 'nadia_local_context_engine_stage_1: ok\n'

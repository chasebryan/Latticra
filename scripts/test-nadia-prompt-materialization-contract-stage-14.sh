#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt materialization contract stage 14: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt materialization contract stage 14: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt materialization contract stage 14: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage14_doc='docs/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14.md'
stage14_status='docs/status/NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
prompt_materialization_script='scripts/nadia-prompt-materialization-contract.sh'
stage14_guard='scripts/test-nadia-prompt-materialization-contract-stage-14.sh'
stage13_guard='scripts/test-nadia-prompt-receipt-contract-stage-13.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage14_doc"
require_file "$stage14_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$prompt_materialization_script"
require_file "$stage14_guard"
require_file "$stage13_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-14 implementation contract' "$stage14_doc"
require_contains 'prompt_materialization_contract_command=scripts/nadia-prompt-materialization-contract.sh' "$stage14_doc"
require_contains 'installed_prompt_materialization_contract_command=latticra-nadia prompt-materialization' "$stage14_doc"
require_contains 'prompt_materialization_authority=0' "$stage14_doc"
require_contains 'prompt_materialization_allowed=0' "$stage14_doc"
require_contains 'prompt_materialized=0' "$stage14_doc"
require_contains 'prompt_buffer_allocated=0' "$stage14_doc"
require_contains 'prompt_tokenized=0' "$stage14_doc"
require_contains 'sh scripts/test-nadia-prompt-materialization-contract-stage-14.sh' "$stage14_doc"

require_contains 'Status: implementation status record' "$stage14_status"
require_contains 'nadia_prompt_materialization_contract_generator_present=1' "$stage14_status"
require_contains 'prompt_materialization_contract_status=contract_only' "$stage14_status"
require_contains 'prompt_materialization_promotion_allowed=0' "$stage14_status"

require_contains 'Stage-14: Prompt Materialization Contract' "$foundation"
require_contains 'scripts/nadia-prompt-materialization-contract.sh' "$foundation"
require_contains 'NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14.md' "$foundation_index"
require_contains 'NADIA_PROMPT_MATERIALIZATION_CONTRACT_STAGE_14_STATUS.md' "$status_index"
require_contains 'nadia_stage_14_prompt_materialization_contract_present=1' "$readme"
require_contains 'implementation_name=Nadia Witness Foundation' "$readme"
require_contains 'Latest Nadia prompt materialization contract Stage-14 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt materialization contract Stage-14 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia prompt materialization contract Stage-14' "$current_status"

require_contains 'NADIA PROMPT MATERIALIZATION CONTRACT' "$prompt_materialization_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$prompt_materialization_script"
require_contains 'public_name=Nadia' "$prompt_materialization_script"
require_contains 'prompt_materialization_authority=0' "$prompt_materialization_script"
require_contains 'prompt_materialization_allowed=0' "$prompt_materialization_script"
require_contains 'prompt_materialized=0' "$prompt_materialization_script"
require_contains 'prompt_buffer_allocation_authority=0' "$prompt_materialization_script"
require_contains 'prompt_buffer_write_authority=0' "$prompt_materialization_script"
require_contains 'prompt_tokenization_authority=0' "$prompt_materialization_script"
require_contains 'prompt_buffer_allocated=0' "$prompt_materialization_script"
require_contains 'prompt_tokenized=0' "$prompt_materialization_script"
require_contains 'prompt_evaluated=0' "$prompt_materialization_script"
require_contains 'token_generation_performed=0' "$prompt_materialization_script"
require_contains 'inference_performed=0' "$prompt_materialization_script"
require_contains 'sexual_request_refusal=always' "$prompt_materialization_script"
require_not_contains 'curl ' "$prompt_materialization_script"
require_not_contains 'wget ' "$prompt_materialization_script"
require_not_contains 'ssh ' "$prompt_materialization_script"

require_contains 'prompt-materialization' "$apply_script"
require_contains 'scripts/nadia-prompt-materialization-contract.sh' "$apply_script"
require_contains 'prompt_materialization_contract_stage=14-prompt-materialization-contract' "$panel_config"
require_contains 'nadia prompt-materialization' "$panel_ui"
require_contains 'latticra-nadia prompt-materialization' "$installer_readme"
require_contains 'nadia prompt-materialization' "$ui_model"
require_contains 'prompt-materialization' "$components_manifest"
require_contains 'nadia-prompt-materialization' "$makefile"

if [ -n "${NADIA_TEST_TMP_ROOT:-}" ]; then
  tmp_root="$NADIA_TEST_TMP_ROOT"
else
  tmp_base="${TMPDIR:-/tmp}"
  tmp_root=$(mktemp -d "$tmp_base/latticra-nadia-stage14-test.XXXXXX")
  trap 'rm -rf "$tmp_root"' EXIT INT HUP TERM
fi

log_out="$tmp_root/stage14/logs"
mkdir -p "$log_out"
NADIA_TEST_TMP_ROOT="$tmp_root" sh "$stage13_guard" >"$log_out/prereq-stage13.out"

out="$tmp_root/stage14/materialization"
receipt="$tmp_root/stage13/receipt/nadia-prompt-receipt-contract-stage13-test.txt"
rm -rf "$out"
mkdir -p "$out"

require_file "$receipt"

NADIA_PROMPT_MATERIALIZATION_TIMESTAMP=stage14-test sh "$prompt_materialization_script" \
  --prompt-receipt "$receipt" \
  --request-class software-development \
  --output "$out" >"$log_out/materialization.out"
materialization="$out/nadia-prompt-materialization-contract-stage14-test.txt"

require_file "$materialization"
require_file "$out/latest-prompt-materialization-contract.txt"
require_contains 'NADIA PROMPT MATERIALIZATION CONTRACT' "$materialization"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$materialization"
require_contains 'public_name=Nadia' "$materialization"
require_contains 'stage=14-prompt-materialization-contract' "$materialization"
require_contains 'request_class=software-development' "$materialization"
require_contains 'prompt_materialization_contract_status=contract_only' "$materialization"
require_contains 'prompt_materialization_stage=contract-only' "$materialization"
require_contains 'prompt_materialization_authority=0' "$materialization"
require_contains 'prompt_materialization_allowed=0' "$materialization"
require_contains 'prompt_materialized=0' "$materialization"
require_contains 'prompt_text_materialized=0' "$materialization"
require_contains 'prompt_receipt_stage=13-prompt-receipt-contract' "$materialization"
require_contains 'model_load_stage=12-model-load-contract' "$materialization"
require_contains 'model_registry_stage=9-local-model-registry-contract' "$materialization"
require_contains 'materialization_decision=blocked_contract_only' "$materialization"
require_contains 'requires_prompt_receipt_contract=1' "$materialization"
require_contains 'requires_future_prompt_evaluation_handoff_contract=1' "$materialization"
require_contains 'prompt_materialization_promotion_allowed=0' "$materialization"
require_contains 'prompt_source_open_authority=0' "$materialization"
require_contains 'prompt_source_read_authority=0' "$materialization"
require_contains 'prompt_text_materialization_authority=0' "$materialization"
require_contains 'prompt_buffer_allocation_authority=0' "$materialization"
require_contains 'prompt_buffer_write_authority=0' "$materialization"
require_contains 'prompt_tokenization_authority=0' "$materialization"
require_contains 'prompt_source_opened=0' "$materialization"
require_contains 'prompt_source_read=0' "$materialization"
require_contains 'prompt_bytes_read=0' "$materialization"
require_contains 'prompt_text_received=0' "$materialization"
require_contains 'prompt_materialization_performed=0' "$materialization"
require_contains 'prompt_buffer_allocated=0' "$materialization"
require_contains 'prompt_buffer_written=0' "$materialization"
require_contains 'prompt_bytes_materialized=0' "$materialization"
require_contains 'prompt_tokens_created=0' "$materialization"
require_contains 'prompt_tokenized=0' "$materialization"
require_contains 'prompt_content_stored=0' "$materialization"
require_contains 'prompt_hash_computed=0' "$materialization"
require_contains 'prompt_classified=0' "$materialization"
require_contains 'prompt_evaluation_authority=0' "$materialization"
require_contains 'prompt_evaluated=0' "$materialization"
require_contains 'model_loaded=0' "$materialization"
require_contains 'model_weights_loaded=0' "$materialization"
require_contains 'token_generation_authority=0' "$materialization"
require_contains 'token_generation_performed=0' "$materialization"
require_contains 'inference_authority=0' "$materialization"
require_contains 'inference_performed=0' "$materialization"
require_contains 'tool_execution_authority=0' "$materialization"
require_contains 'network_authority=0' "$materialization"
require_contains 'sexual_content_generation=0' "$materialization"
require_contains 'sexual_request_refusal=always' "$materialization"

if NADIA_PROMPT_MATERIALIZATION_TIMESTAMP=stage14-reject sh "$prompt_materialization_script" \
  --prompt-receipt "$receipt" \
  --request-class sexual \
  --output "$out" >"$log_out/reject.out" 2>"$log_out/reject.err"; then
  printf 'nadia prompt materialization contract stage 14: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-materialization boundary' "$log_out/reject.err"

printf 'nadia_prompt_materialization_contract_stage_14: ok\n'

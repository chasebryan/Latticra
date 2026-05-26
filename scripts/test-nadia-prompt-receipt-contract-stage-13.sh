#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt receipt contract stage 13: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt receipt contract stage 13: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt receipt contract stage 13: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage13_doc='docs/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13.md'
stage13_status='docs/status/NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
prompt_receipt_script='scripts/nadia-prompt-receipt-contract.sh'
stage13_guard='scripts/test-nadia-prompt-receipt-contract-stage-13.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage13_doc"
require_file "$stage13_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$prompt_receipt_script"
require_file "$stage13_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-13 implementation contract' "$stage13_doc"
require_contains 'prompt_receipt_contract_command=scripts/nadia-prompt-receipt-contract.sh' "$stage13_doc"
require_contains 'installed_prompt_receipt_contract_command=latticra-nadia prompt-receipt' "$stage13_doc"
require_contains 'prompt_receipt_authority=0' "$stage13_doc"
require_contains 'prompt_received=0' "$stage13_doc"
require_contains 'prompt_text_received=0' "$stage13_doc"
require_contains 'prompt_source_open_authority=0' "$stage13_doc"
require_contains 'prompt_text_materialized=0' "$stage13_doc"
require_contains 'sh scripts/test-nadia-prompt-receipt-contract-stage-13.sh' "$stage13_doc"

require_contains 'Status: implementation status record' "$stage13_status"
require_contains 'nadia_prompt_receipt_contract_generator_present=1' "$stage13_status"
require_contains 'prompt_receipt_contract_status=contract_only' "$stage13_status"
require_contains 'prompt_receipt_promotion_allowed=0' "$stage13_status"

require_contains 'Stage-13: Prompt Receipt Contract' "$foundation"
require_contains 'scripts/nadia-prompt-receipt-contract.sh' "$foundation"
require_contains 'NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13.md' "$foundation_index"
require_contains 'NADIA_PROMPT_RECEIPT_CONTRACT_STAGE_13_STATUS.md' "$status_index"
require_contains 'nadia_stage_13_prompt_receipt_contract_present=1' "$readme"
require_contains 'implementation_name=Nadia Witness Foundation' "$readme"
require_contains 'Latest Nadia prompt receipt contract Stage-13 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt receipt contract Stage-13 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia prompt receipt contract Stage-13' "$current_status"

require_contains 'NADIA PROMPT RECEIPT CONTRACT' "$prompt_receipt_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$prompt_receipt_script"
require_contains 'public_name=Nadia' "$prompt_receipt_script"
require_contains 'prompt_receipt_authority=0' "$prompt_receipt_script"
require_contains 'prompt_receipt_allowed=0' "$prompt_receipt_script"
require_contains 'prompt_received=0' "$prompt_receipt_script"
require_contains 'prompt_source_open_authority=0' "$prompt_receipt_script"
require_contains 'prompt_source_read_authority=0' "$prompt_receipt_script"
require_contains 'prompt_text_materialization_authority=0' "$prompt_receipt_script"
require_contains 'prompt_content_storage_authority=0' "$prompt_receipt_script"
require_contains 'prompt_hash_authority=0' "$prompt_receipt_script"
require_contains 'prompt_classification_authority=0' "$prompt_receipt_script"
require_contains 'prompt_text_received=0' "$prompt_receipt_script"
require_contains 'prompt_text_materialized=0' "$prompt_receipt_script"
require_contains 'prompt_evaluated=0' "$prompt_receipt_script"
require_contains 'token_generation_performed=0' "$prompt_receipt_script"
require_contains 'inference_performed=0' "$prompt_receipt_script"
require_contains 'sexual_request_refusal=always' "$prompt_receipt_script"
require_not_contains 'curl ' "$prompt_receipt_script"
require_not_contains 'wget ' "$prompt_receipt_script"
require_not_contains 'ssh ' "$prompt_receipt_script"

require_contains 'prompt-receipt' "$apply_script"
require_contains 'scripts/nadia-prompt-receipt-contract.sh' "$apply_script"
require_contains 'prompt_receipt_contract_stage=13-prompt-receipt-contract' "$panel_config"
require_contains 'nadia prompt-receipt' "$panel_ui"
require_contains 'latticra-nadia prompt-receipt' "$installer_readme"
require_contains 'nadia prompt-receipt' "$ui_model"
require_contains 'prompt-receipt' "$components_manifest"
require_contains 'nadia-prompt-receipt' "$makefile"

if [ -n "${NADIA_TEST_TMP_ROOT:-}" ]; then
  tmp_root="$NADIA_TEST_TMP_ROOT"
else
  tmp_base="${TMPDIR:-/tmp}"
  tmp_root=$(mktemp -d "$tmp_base/latticra-nadia-stage13-test.XXXXXX")
  trap 'rm -rf "$tmp_root"' EXIT INT HUP TERM
fi

out="$tmp_root/stage13/receipt"
context_out="$tmp_root/stage13/context"
runtime_out="$tmp_root/stage13/runtime"
plan_out="$tmp_root/stage13/plan"
mode_out="$tmp_root/stage13/mode"
ledger_out="$tmp_root/stage13/ledger"
safety_out="$tmp_root/stage13/safety"
tool_out="$tmp_root/stage13/tool"
contract_out="$tmp_root/stage13/contract"
registry_out="$tmp_root/stage13/registry"
readiness_out="$tmp_root/stage13/readiness"
invocation_out="$tmp_root/stage13/invocation"
load_out="$tmp_root/stage13/load"
log_out="$tmp_root/stage13/logs"
rm -rf "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out" "$registry_out" "$readiness_out" "$invocation_out" "$load_out" "$log_out"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out" "$registry_out" "$readiness_out" "$invocation_out" "$load_out" "$log_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage13-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >"$log_out/context.out"
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage13-test sh scripts/nadia-runtime-profile.sh \
  --context-tokens 8192 \
  --memory-mib 16384 \
  --output "$runtime_out" >"$log_out/runtime.out"
NADIA_PROMPT_PLAN_TIMESTAMP=stage13-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage13-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage13-test.txt" \
  --task "prompt receipt contract planning" \
  --output "$plan_out" >"$log_out/plan.out"
NADIA_MODE_VALIDATION_TIMESTAMP=stage13-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage13-test.txt" \
  --mode ai-development \
  --output "$mode_out" >"$log_out/mode.out"
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage13-test sh scripts/nadia-productivity-ledger.sh \
  --mode-validation "$mode_out/nadia-mode-validation-stage13-test.txt" \
  --outcome "accepted prompt receipt boundary" \
  --recommendation "keep prompt receipt contract-only" \
  --output "$ledger_out" >"$log_out/ledger.out"
NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage13-test sh scripts/nadia-protective-safety-boundary.sh \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage13-test.txt" \
  --request-class software-development \
  --output "$safety_out" >"$log_out/safety.out"
NADIA_TOOL_PREFLIGHT_TIMESTAMP=stage13-test sh scripts/nadia-tool-authority-preflight.sh \
  --protective-safety "$safety_out/nadia-protective-safety-stage13-test.txt" \
  --tool-class metadata-read \
  --action "prepare prompt receipt contract evidence" \
  --output "$tool_out" >"$log_out/tool.out"
NADIA_PROMPT_CONTRACT_TIMESTAMP=stage13-test sh scripts/nadia-prompt-evaluation-contract.sh \
  --tool-preflight "$tool_out/nadia-tool-preflight-stage13-test.txt" \
  --request-class software-development \
  --output "$contract_out" >"$log_out/contract.out"
NADIA_MODEL_REGISTRY_TIMESTAMP=stage13-test sh scripts/nadia-local-model-registry-contract.sh \
  --prompt-contract "$contract_out/nadia-prompt-contract-stage13-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage13-test.txt" \
  --model-id local-coding-assistant-candidate \
  --quantization q4_k_m \
  --source operator-provided-local \
  --license operator-review-required \
  --output "$registry_out" >"$log_out/registry.out"
NADIA_INFERENCE_READINESS_TIMESTAMP=stage13-test sh scripts/nadia-inference-readiness-contract.sh \
  --model-registry "$registry_out/nadia-model-registry-contract-stage13-test.txt" \
  --request-class software-development \
  --output "$readiness_out" >"$log_out/readiness.out"
NADIA_RUNTIME_INVOCATION_TIMESTAMP=stage13-test sh scripts/nadia-runtime-invocation-contract.sh \
  --inference-readiness "$readiness_out/nadia-inference-readiness-contract-stage13-test.txt" \
  --request-class software-development \
  --output "$invocation_out" >"$log_out/invocation.out"
NADIA_MODEL_LOAD_TIMESTAMP=stage13-test sh scripts/nadia-model-load-contract.sh \
  --runtime-invocation "$invocation_out/nadia-runtime-invocation-contract-stage13-test.txt" \
  --request-class software-development \
  --output "$load_out" >"$log_out/load.out"
NADIA_PROMPT_RECEIPT_TIMESTAMP=stage13-test sh "$prompt_receipt_script" \
  --model-load "$load_out/nadia-model-load-contract-stage13-test.txt" \
  --request-class software-development \
  --output "$out" >"$log_out/receipt.out"
receipt="$out/nadia-prompt-receipt-contract-stage13-test.txt"

require_file "$receipt"
require_file "$out/latest-prompt-receipt-contract.txt"
require_contains 'NADIA PROMPT RECEIPT CONTRACT' "$receipt"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$receipt"
require_contains 'public_name=Nadia' "$receipt"
require_contains 'stage=13-prompt-receipt-contract' "$receipt"
require_contains 'request_class=software-development' "$receipt"
require_contains 'prompt_receipt_contract_status=contract_only' "$receipt"
require_contains 'prompt_receipt_stage=contract-only' "$receipt"
require_contains 'prompt_receipt_authority=0' "$receipt"
require_contains 'prompt_receipt_allowed=0' "$receipt"
require_contains 'prompt_received=0' "$receipt"
require_contains 'model_load_stage=12-model-load-contract' "$receipt"
require_contains 'model_registry_stage=9-local-model-registry-contract' "$receipt"
require_contains 'receipt_decision=blocked_contract_only' "$receipt"
require_contains 'requires_model_load_contract=1' "$receipt"
require_contains 'requires_future_prompt_materialization_contract=1' "$receipt"
require_contains 'prompt_receipt_promotion_allowed=0' "$receipt"
require_contains 'prompt_source_open_authority=0' "$receipt"
require_contains 'prompt_source_read_authority=0' "$receipt"
require_contains 'prompt_text_materialization_authority=0' "$receipt"
require_contains 'prompt_content_storage_authority=0' "$receipt"
require_contains 'prompt_source_opened=0' "$receipt"
require_contains 'prompt_source_read=0' "$receipt"
require_contains 'prompt_bytes_read=0' "$receipt"
require_contains 'prompt_text_received=0' "$receipt"
require_contains 'prompt_text_materialized=0' "$receipt"
require_contains 'prompt_content_stored=0' "$receipt"
require_contains 'prompt_hash_computed=0' "$receipt"
require_contains 'prompt_classified=0' "$receipt"
require_contains 'prompt_materialized=0' "$receipt"
require_contains 'prompt_evaluation_authority=0' "$receipt"
require_contains 'prompt_evaluated=0' "$receipt"
require_contains 'model_loaded=0' "$receipt"
require_contains 'model_weights_loaded=0' "$receipt"
require_contains 'token_generation_authority=0' "$receipt"
require_contains 'token_generation_performed=0' "$receipt"
require_contains 'inference_authority=0' "$receipt"
require_contains 'inference_performed=0' "$receipt"
require_contains 'tool_execution_authority=0' "$receipt"
require_contains 'network_authority=0' "$receipt"
require_contains 'sexual_content_generation=0' "$receipt"
require_contains 'sexual_request_refusal=always' "$receipt"

if NADIA_PROMPT_RECEIPT_TIMESTAMP=stage13-reject sh "$prompt_receipt_script" \
  --model-load "$load_out/nadia-model-load-contract-stage13-test.txt" \
  --request-class sexual \
  --output "$out" >"$log_out/reject.out" 2>"$log_out/reject.err"; then
  printf 'nadia prompt receipt contract stage 13: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-receipt boundary' "$log_out/reject.err"

printf 'nadia_prompt_receipt_contract_stage_13: ok\n'

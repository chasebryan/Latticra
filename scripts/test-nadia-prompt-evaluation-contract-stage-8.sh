#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt evaluation contract stage 8: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation contract stage 8: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation contract stage 8: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage8_doc='docs/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8.md'
stage8_status='docs/status/NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
contract_script='scripts/nadia-prompt-evaluation-contract.sh'
stage8_guard='scripts/test-nadia-prompt-evaluation-contract-stage-8.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage8_doc"
require_file "$stage8_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$contract_script"
require_file "$stage8_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-8 implementation contract' "$stage8_doc"
require_contains 'nadia_stage_8_prompt_evaluation_contract_present=1' "$stage8_doc"
require_contains 'prompt_evaluation_contract_command=scripts/nadia-prompt-evaluation-contract.sh' "$stage8_doc"
require_contains 'installed_prompt_evaluation_contract_command=latticra-nadia prompt-contract' "$stage8_doc"
require_contains 'prompt_evaluation_authority=0' "$stage8_doc"
require_contains 'prompt_materialized=0' "$stage8_doc"
require_contains 'prompt_evaluated=0' "$stage8_doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-contract-stage-8.sh' "$stage8_doc"

require_contains 'Status: implementation status record' "$stage8_status"
require_contains 'nadia_prompt_evaluation_contract_generator_present=1' "$stage8_status"
require_contains 'prompt_contract_status=contract_only' "$stage8_status"
require_contains 'contract_promotion_allowed=0' "$stage8_status"

require_contains 'Stage-8: Prompt Evaluation Contract' "$foundation"
require_contains 'scripts/nadia-prompt-evaluation-contract.sh' "$foundation"
require_contains 'NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8.md' "$foundation_index"
require_contains 'NADIA_PROMPT_EVALUATION_CONTRACT_STAGE_8_STATUS.md' "$status_index"
require_contains 'nadia_stage_8_prompt_evaluation_contract_present=1' "$readme"
require_contains 'Latest Nadia prompt evaluation contract Stage-8 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt evaluation contract Stage-8 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia prompt evaluation contract Stage-8' "$current_status"

require_contains 'NADIA PROMPT EVALUATION CONTRACT' "$contract_script"
require_contains 'prompt_evaluation_authority=0' "$contract_script"
require_contains 'prompt_materialized=0' "$contract_script"
require_contains 'prompt_evaluated=0' "$contract_script"
require_contains 'model_runtime_invoked=0' "$contract_script"
require_contains 'inference_performed=0' "$contract_script"
require_contains 'tool_execution_authority=0' "$contract_script"
require_contains 'sexual_request_refusal=always' "$contract_script"
require_not_contains 'curl ' "$contract_script"
require_not_contains 'wget ' "$contract_script"
require_not_contains 'ssh ' "$contract_script"

require_contains 'prompt-contract' "$apply_script"
require_contains 'scripts/nadia-prompt-evaluation-contract.sh' "$apply_script"
require_contains 'prompt_evaluation_contract_stage=8-prompt-evaluation-contract' "$panel_config"
require_contains 'nadia prompt-contract' "$panel_ui"
require_contains 'latticra-nadia prompt-contract' "$installer_readme"
require_contains 'nadia prompt-contract' "$ui_model"
require_contains 'prompt-contracts' "$components_manifest"
require_contains 'nadia-prompt-contract' "$makefile"

out='/private/tmp/latticra-nadia-stage8-contract-test'
context_out='/private/tmp/latticra-nadia-stage8-context-test'
runtime_out='/private/tmp/latticra-nadia-stage8-runtime-test'
plan_out='/private/tmp/latticra-nadia-stage8-plan-test'
mode_out='/private/tmp/latticra-nadia-stage8-mode-test'
ledger_out='/private/tmp/latticra-nadia-stage8-ledger-test'
safety_out='/private/tmp/latticra-nadia-stage8-safety-test'
tool_out='/private/tmp/latticra-nadia-stage8-tool-test'
rm -rf "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage8-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >/tmp/latticra-nadia-stage8-context-test.out
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage8-test sh scripts/nadia-runtime-profile.sh --output "$runtime_out" >/tmp/latticra-nadia-stage8-runtime-test.out
NADIA_PROMPT_PLAN_TIMESTAMP=stage8-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage8-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage8-test.txt" \
  --task "prompt evaluation contract planning" \
  --output "$plan_out" >/tmp/latticra-nadia-stage8-plan-test.out
NADIA_MODE_VALIDATION_TIMESTAMP=stage8-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage8-test.txt" \
  --mode ai-development \
  --output "$mode_out" >/tmp/latticra-nadia-stage8-mode-test.out
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage8-test sh scripts/nadia-productivity-ledger.sh \
  --mode-validation "$mode_out/nadia-mode-validation-stage8-test.txt" \
  --outcome "accepted prompt contract boundary" \
  --recommendation "keep prompt evaluation contract-only" \
  --output "$ledger_out" >/tmp/latticra-nadia-stage8-ledger-test.out
NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage8-test sh scripts/nadia-protective-safety-boundary.sh \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage8-test.txt" \
  --request-class software-development \
  --output "$safety_out" >/tmp/latticra-nadia-stage8-safety-test.out
NADIA_TOOL_PREFLIGHT_TIMESTAMP=stage8-test sh scripts/nadia-tool-authority-preflight.sh \
  --protective-safety "$safety_out/nadia-protective-safety-stage8-test.txt" \
  --tool-class metadata-read \
  --action "prepare prompt contract evidence" \
  --output "$tool_out" >/tmp/latticra-nadia-stage8-tool-test.out
NADIA_PROMPT_CONTRACT_TIMESTAMP=stage8-test sh "$contract_script" \
  --tool-preflight "$tool_out/nadia-tool-preflight-stage8-test.txt" \
  --request-class software-development \
  --output "$out" >/tmp/latticra-nadia-stage8-contract-test.out
contract="$out/nadia-prompt-contract-stage8-test.txt"

require_file "$contract"
require_file "$out/latest-prompt-contract.txt"
require_contains 'NADIA PROMPT EVALUATION CONTRACT' "$contract"
require_contains 'stage=8-prompt-evaluation-contract' "$contract"
require_contains 'request_class=software-development' "$contract"
require_contains 'prompt_contract_status=contract_only' "$contract"
require_contains 'tool_preflight_stage=7-guarded-tool-authority-preflight' "$contract"
require_contains 'prompt_evaluation_stage=contract-only' "$contract"
require_contains 'prompt_materialized=0' "$contract"
require_contains 'prompt_text_materialized=0' "$contract"
require_contains 'prompt_evaluation_authority=0' "$contract"
require_contains 'prompt_evaluated=0' "$contract"
require_contains 'prompt_receipt_required=1' "$contract"
require_contains 'refusal_policy_required=1' "$contract"
require_contains 'protective_safety_required=1' "$contract"
require_contains 'tool_preflight_required=1' "$contract"
require_contains 'runtime_profile_required=1' "$contract"
require_contains 'model_registry_review_required=1' "$contract"
require_contains 'contract_promotion_allowed=0' "$contract"
require_contains 'sexual_content_generation=0' "$contract"
require_contains 'sexual_request_refusal=always' "$contract"
require_contains 'preflight_decision=report_only_no_execution' "$contract"
require_contains 'tool_execution_authority=0' "$contract"
require_contains 'tool_execution_performed=0' "$contract"
require_contains 'model_runtime_invoked=0' "$contract"
require_contains 'inference_performed=0' "$contract"

if NADIA_PROMPT_CONTRACT_TIMESTAMP=stage8-reject sh "$contract_script" \
  --tool-preflight "$tool_out/nadia-tool-preflight-stage8-test.txt" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage8-reject-test.out 2>/tmp/latticra-nadia-stage8-reject-test.err; then
  printf 'nadia prompt evaluation contract stage 8: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-evaluation contract boundary' /tmp/latticra-nadia-stage8-reject-test.err

printf 'nadia_prompt_evaluation_contract_stage_8: ok\n'

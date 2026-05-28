#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'nadia production readiness blocker status contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "forbidden pattern in $file: $pattern"
  fi
}

contract='docs/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS_CONTRACT.md'
status='docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md'
status_index='docs/status/README.md'
script='scripts/nadia-production-readiness-blocker-status.sh'
guard='scripts/test-nadia-production-readiness-blocker-status-contract.sh'
workflow='.github/workflows/nadia-production-readiness-blocker-status-contract.yml'
makefile='Makefile'

require_file "$contract"
require_file "$status"
require_file "$status_index"
require_file "$script"
require_file "$guard"
require_file "$workflow"
require_file "$makefile"
require_file docs/status/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6_STATUS.md
require_file docs/status/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15_STATUS.md
require_file docs/status/NADIA_PROMPT_EVALUATION_RESULT_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_REVIEW_DISPOSITION_RELEASE_RECEIPT_CONTRACT_STAGE_51_STATUS.md
require_file scripts/test-nadia-command-surface.sh

require_contains 'Status: no-effect Nadia production-readiness blocker status' "$contract"
require_contains 'scripts/nadia-production-readiness-blocker-status.sh' "$contract"
require_contains 'scripts/test-nadia-production-readiness-blocker-status-contract.sh' "$contract"
require_contains 'nadia_production_readiness_blocker_status_present=1' "$contract"
require_contains 'absolute_protective_boundary_required=1' "$contract"
require_contains 'sexual_content_generation=0' "$contract"
require_contains 'sexual_request_refusal=always' "$contract"
require_contains 'sexual_safety_runtime_enforcement_validated=0' "$contract"
require_contains 'sexual_safety_adversarial_eval_reviewed=0' "$contract"
require_contains 'manipulation_resistance_red_team_reviewed=0' "$contract"
require_contains 'survivor_sensitive_content_reviewed=0' "$contract"
require_contains 'nadia_initiative_source_snapshot_reviewed=0' "$contract"
require_contains 'source_citation_pack_reviewed=0' "$contract"
require_contains 'awareness_qa_dataset_reviewed=0' "$contract"
require_contains 'offline_model_artifact_present=0' "$contract"
require_contains 'offline_model_integrity_verified=0' "$contract"
require_contains 'inference_runtime_validated=0' "$contract"
require_contains 'runtime_sandbox_validated=0' "$contract"
require_contains 'tool_authority_runtime_enforced=0' "$contract"
require_contains 'console_interoperability_e2e_validated=0' "$contract"
require_contains 'panel_install_e2e_validated=0' "$contract"
require_contains 'production_nadia_ready=0' "$contract"
require_contains 'public_release_allowed=0' "$contract"
require_contains 'no_effect=1' "$contract"
require_contains 'not permission to generate sexual content' "$contract"

require_contains 'Status: production-blocked no-effect status record' "$status"
require_contains 'nadia_production_readiness_blocker_status_present=1' "$status"
require_contains 'production_nadia_ready=0' "$status"
require_contains 'not permission to generate sexual content' "$status"
require_contains 'NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md' "$status_index"
require_contains 'NADIA_PRODUCTION_READINESS_BLOCKER_STATUS_CONTRACT.md' "$status_index"

require_contains 'LATTICRA NADIA PRODUCTION READINESS BLOCKER STATUS' "$script"
require_contains 'require_file docs/status/NADIA_PROTECTIVE_SAFETY_BOUNDARY_STAGE_6_STATUS.md' "$script"
require_contains 'require_file docs/status/NADIA_AWARENESS_DIALOGUE_CONTRACT_STAGE_15_STATUS.md' "$script"
require_contains 'sexual_content_generation=0' "$script"
require_contains 'sexual_safety_runtime_enforcement_validated=0' "$script"
require_contains 'survivor_sensitive_content_reviewed=0' "$script"
require_contains 'production_nadia_ready=0' "$script"
require_contains 'model_runtime_invoked=0' "$script"
require_contains 'tool_execution_performed=0' "$script"
require_contains 'source_mutation_performed=0' "$script"
require_contains 'no_effect=1' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"
require_not_contains 'ssh ' "$script"

require_contains 'nadia-production-readiness-blocker-status-contract' "$makefile"
require_contains 'sh ./scripts/test-nadia-production-readiness-blocker-status-contract.sh' "$makefile"
require_contains 'Nadia Production Readiness Blocker Status' "$workflow"
require_contains 'sh scripts/test-nadia-production-readiness-blocker-status-contract.sh' "$workflow"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-production-readiness.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
out="$tmpdir/status.txt"
sh "$script" > "$out"

require_contains 'LATTICRA NADIA PRODUCTION READINESS BLOCKER STATUS' "$out"
require_contains 'nadia_production_readiness_blocker_status_present=1' "$out"
require_contains 'nadia_production_readiness_status_no_effect=1' "$out"
require_contains 'stage_6_protective_safety_boundary_status_present=1' "$out"
require_contains 'stage_15_awareness_dialogue_status_present=1' "$out"
require_contains 'stage_51_release_receipt_status_present=1' "$out"
require_contains 'sexual_content_generation=0' "$out"
require_contains 'sexual_request_refusal=always' "$out"
require_contains 'sexual_safety_runtime_enforcement_validated=0' "$out"
require_contains 'sexual_safety_adversarial_eval_reviewed=0' "$out"
require_contains 'manipulation_resistance_red_team_reviewed=0' "$out"
require_contains 'survivor_sensitive_content_reviewed=0' "$out"
require_contains 'human_rights_awareness_reviewed=0' "$out"
require_contains 'nadia_initiative_source_snapshot_reviewed=0' "$out"
require_contains 'source_citation_pack_reviewed=0' "$out"
require_contains 'awareness_qa_dataset_reviewed=0' "$out"
require_contains 'offline_model_artifact_present=0' "$out"
require_contains 'offline_model_license_reviewed=0' "$out"
require_contains 'offline_model_integrity_verified=0' "$out"
require_contains 'tokenizer_artifact_runtime_verified=0' "$out"
require_contains 'model_load_runtime_validated=0' "$out"
require_contains 'prompt_evaluation_runtime_validated=0' "$out"
require_contains 'inference_runtime_validated=0' "$out"
require_contains 'runtime_sandbox_validated=0' "$out"
require_contains 'tool_authority_runtime_enforced=0' "$out"
require_contains 'console_interoperability_e2e_validated=0' "$out"
require_contains 'panel_install_e2e_validated=0' "$out"
require_contains 'release_receipt_signed=0' "$out"
require_contains 'release_receipt_reviewed=0' "$out"
require_contains 'community_awareness_review_ready=0' "$out"
require_contains 'production_nadia_ready=0' "$out"
require_contains 'public_release_allowed=0' "$out"
require_contains 'network_allowed=0' "$out"
require_contains 'model_download_allowed=0' "$out"
require_contains 'prompt_evaluated=0' "$out"
require_contains 'inference_performed=0' "$out"
require_contains 'model_runtime_invoked=0' "$out"
require_contains 'tool_execution_performed=0' "$out"
require_contains 'source_mutation_performed=0' "$out"
require_contains 'training_performed=0' "$out"
require_contains 'distillation_performed=0' "$out"
require_contains 'host_mutation_performed=0' "$out"
require_contains 'no_effect=1' "$out"

printf 'nadia_production_readiness_blocker_status_contract: ok\n'

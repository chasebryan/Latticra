#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-evaluation-contract.sh [options]

Options:
  --tool-preflight <file>  Stage-7 Nadia tool-authority preflight report
  --request-class <label>  Operator request classification label
  --output <dir>           Output directory for prompt-evaluation contracts

Creates Nadia Stage-8 prompt-evaluation contract metadata only. It does not
materialize prompts, evaluate prompts, run a model, execute tools, mutate
source, train, distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt evaluation contract: %s\n' "$1" >&2
  exit "${2:-1}"
}

measure_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    cksum "$file" | awk '{ print "cksum:" $1 ":" $2 }'
  fi
}

field_or_unknown() {
  key="$1"
  file="$2"
  awk -F '=' -v key="$key" '
    $1 == key {
      val = $2
      for (i = 3; i <= NF; i++) val = val "=" $i
      print val
      found = 1
      exit
    }
    END {
      if (!found) print "unknown"
    }
  ' "$file"
}

TOOL_PREFLIGHT=""
REQUEST_CLASS="software-development"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --tool-preflight)
      [ "$#" -ge 2 ] || fail "missing value for --tool-preflight" 64
      TOOL_PREFLIGHT="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --output)
      [ "$#" -ge 2 ] || fail "missing value for --output" 64
      OUTPUT="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

if [ -z "$TOOL_PREFLIGHT" ] && [ -f "reports/nadia/tool-preflights/latest-tool-preflight.txt" ]; then
  TOOL_PREFLIGHT="reports/nadia/tool-preflights/latest-tool-preflight.txt"
fi

[ -n "$TOOL_PREFLIGHT" ] || fail "tool preflight report is required" 64
[ -f "$TOOL_PREFLIGHT" ] || fail "tool preflight report not found: $TOOL_PREFLIGHT" 66

REQUEST_CLASS_NORMALIZED=$(printf '%s\n' "$REQUEST_CLASS" | tr '[:upper:]' '[:lower:]')
case "$REQUEST_CLASS_NORMALIZED" in
  *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
    fail "request class is outside Nadia prompt-evaluation contract boundary" 65
    ;;
esac

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-contracts"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_CONTRACT_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-contract-$TS.txt"

TOOL_PREFLIGHT_ABS=$(cd "$(dirname -- "$TOOL_PREFLIGHT")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$TOOL_PREFLIGHT")")
TOOL_PREFLIGHT_MEASUREMENT=$(measure_file "$TOOL_PREFLIGHT_ABS")
TOOL_PREFLIGHT_STAGE=$(field_or_unknown stage "$TOOL_PREFLIGHT_ABS")
MODE=$(field_or_unknown mode "$TOOL_PREFLIGHT_ABS")
TASK=$(field_or_unknown task "$TOOL_PREFLIGHT_ABS")
PREFLIGHT_DECISION=$(field_or_unknown preflight_decision "$TOOL_PREFLIGHT_ABS")
TOOL_EXECUTION_AUTHORITY=$(field_or_unknown tool_execution_authority "$TOOL_PREFLIGHT_ABS")
TOOL_EXECUTION_PERFORMED=$(field_or_unknown tool_execution_performed "$TOOL_PREFLIGHT_ABS")
AUTHORITY_TRANSITION_ALLOWED=$(field_or_unknown authority_transition_allowed "$TOOL_PREFLIGHT_ABS")
SEXUAL_CONTENT_GENERATION=$(field_or_unknown sexual_content_generation "$TOOL_PREFLIGHT_ABS")
SEXUAL_REQUEST_REFUSAL=$(field_or_unknown sexual_request_refusal "$TOOL_PREFLIGHT_ABS")
MANIPULATION_RESISTANCE=$(field_or_unknown manipulation_resistance "$TOOL_PREFLIGHT_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$TOOL_PREFLIGHT_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$TOOL_PREFLIGHT_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$TOOL_PREFLIGHT_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$TOOL_PREFLIGHT_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$TOOL_PREFLIGHT_ABS")

[ "$TOOL_PREFLIGHT_STAGE" = "7-guarded-tool-authority-preflight" ] || fail "tool preflight stage must be 7-guarded-tool-authority-preflight" 65
[ "$PREFLIGHT_DECISION" = "report_only_no_execution" ] || fail "tool preflight must remain report-only" 65
[ "$TOOL_EXECUTION_AUTHORITY" = "0" ] || fail "tool preflight must not grant tool execution authority" 65
[ "$TOOL_EXECUTION_PERFORMED" = "0" ] || fail "tool preflight must not perform tool execution" 65
[ "$AUTHORITY_TRANSITION_ALLOWED" = "0" ] || fail "tool preflight must not allow authority transition" 65
[ "$SEXUAL_CONTENT_GENERATION" = "0" ] || fail "tool preflight must forbid sexual content generation" 65
[ "$SEXUAL_REQUEST_REFUSAL" = "always" ] || fail "tool preflight must always refuse sexual requests" 65
[ "$MANIPULATION_RESISTANCE" = "required" ] || fail "tool preflight must require manipulation resistance" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "tool preflight must not evaluate prompts" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "tool preflight must not include inference" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "tool preflight must not invoke a model runtime" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "tool preflight must not include source mutation authority" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "tool preflight must not include network authority" 65

cat > "$REPORT" <<REPORT
NADIA PROMPT EVALUATION CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=8-prompt-evaluation-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_contract_status=contract_only

[inputs]
tool_preflight=$TOOL_PREFLIGHT_ABS
tool_preflight_stage=$TOOL_PREFLIGHT_STAGE
tool_preflight_measurement=$TOOL_PREFLIGHT_MEASUREMENT
mode=$MODE
task=$TASK

[prompt_contract]
prompt_evaluation_stage=contract-only
prompt_materialized=0
prompt_text_materialized=0
prompt_evaluation_authority=0
prompt_evaluated=0
prompt_receipt_required=1
refusal_policy_required=1
protective_safety_required=1
tool_preflight_required=1
runtime_profile_required=1
model_registry_review_required=1
operator_review_required=1
contract_promotion_allowed=0

[protective_boundary]
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
prompt_injection_override_authority=0
policy_bypass_authority=0
namesake_cause_awareness=1

[tool_boundary]
preflight_decision=report_only_no_execution
tool_execution_authority=0
tool_execution_performed=0
source_mutation_authority=0
authority_transition_allowed=0

[authority]
offline_by_default=1
network_authority=0
training_performed=0
distillation_performed=0
self_modification_authority=0
model_runtime_invoked=0
inference_performed=0
model_weights_installed=0

[operator_review]
requires_operator_review=1
requires_prompt_contract_review=1
requires_refusal_policy_review=1
requires_future_prompt_evaluation_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-prompt-contract.txt"

printf 'NADIA_PROMPT_EVALUATION_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_EVALUATED=0\n'
printf 'NADIA_PROMPT_EVALUATION_AUTHORITY=0\n'

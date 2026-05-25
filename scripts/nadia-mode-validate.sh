#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-mode-validate.sh [options]

Options:
  --prompt-plan <file>  Stage-3 Nadia prompt plan
  --mode <mode>         Systems-engineering mode label
  --output <dir>        Output directory for mode-validation reports

Creates Nadia Stage-4 mode-validation metadata only. It does not evaluate
prompts, run a model, mutate source, execute tools, train, download, or use
network.
USAGE
}

fail() {
  printf 'nadia mode validate: %s\n' "$1" >&2
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

mode_detail() {
  MODE_ALLOWED=1
  case "$MODE" in
    systems-engineering)
      MODE_FOCUS="architecture-boundary-contracts"
      VALIDATOR_SET="contract-surface,evidence-surface,nonclaim-surface"
      ;;
    ai-development)
      MODE_FOCUS="offline-ai-runtime-retrieval-evaluation"
      VALIDATOR_SET="runtime-boundary,prompt-boundary,training-nonclaim"
      ;;
    c-substrate)
      MODE_FOCUS="c-foundation-memory-abi-diagnostics"
      VALIDATOR_SET="abi-contract,memory-boundary,diagnostic-evidence"
      ;;
    cpp-authority)
      MODE_FOCUS="constrained-cpp-authority-layer"
      VALIDATOR_SET="authority-boundary,no-effect-evidence,receipt-fields"
      ;;
    rust-panel)
      MODE_FOCUS="latticra-panel-installer-console"
      VALIDATOR_SET="panel-metadata,installer-plan,console-allowlist"
      ;;
    lat-lir-l-ui)
      MODE_FOCUS="language-ir-ui-contracts"
      VALIDATOR_SET="parser-contract,ir-shape,ui-render-evidence"
      ;;
    seal-boundary)
      MODE_FOCUS="latticra-seal-local-evidence"
      VALIDATOR_SET="receipt-boundary,key-nonclaim,crypto-profile"
      ;;
    runtime-boundary)
      MODE_FOCUS="host-runtime-policy-authority"
      VALIDATOR_SET="runtime-policy,no-network,no-host-mutation"
      ;;
    fedora-validation)
      MODE_FOCUS="fedora-linux-validation-packaging"
      VALIDATOR_SET="fedora-policy,local-prefix,safety-baseline"
      ;;
    awareness-safety)
      MODE_FOCUS="human-dignity-community-awareness"
      VALIDATOR_SET="human-dignity,survivor-witness-respect,harm-aware-development"
      ;;
    *)
      MODE_ALLOWED=0
      fail "unsupported mode: $MODE" 65
      ;;
  esac
}

PROMPT_PLAN=""
MODE="systems-engineering"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-plan)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-plan" 64
      PROMPT_PLAN="$2"
      shift 2
      ;;
    --mode)
      [ "$#" -ge 2 ] || fail "missing value for --mode" 64
      MODE="$2"
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

if [ -z "$PROMPT_PLAN" ] && [ -f "reports/nadia/prompt-plans/latest-prompt-plan.txt" ]; then
  PROMPT_PLAN="reports/nadia/prompt-plans/latest-prompt-plan.txt"
fi

[ -n "$PROMPT_PLAN" ] || fail "prompt plan is required" 64
[ -f "$PROMPT_PLAN" ] || fail "prompt plan not found: $PROMPT_PLAN" 66

mode_detail

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/mode-validations"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_MODE_VALIDATION_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-mode-validation-$TS.txt"

PROMPT_PLAN_ABS=$(cd "$(dirname -- "$PROMPT_PLAN")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_PLAN")")
PROMPT_PLAN_MEASUREMENT=$(measure_file "$PROMPT_PLAN_ABS")
PROMPT_PLAN_STAGE=$(field_or_unknown stage "$PROMPT_PLAN_ABS")
TASK=$(field_or_unknown task "$PROMPT_PLAN_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$PROMPT_PLAN_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$PROMPT_PLAN_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$PROMPT_PLAN_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$PROMPT_PLAN_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$PROMPT_PLAN_ABS")

[ "$PROMPT_PLAN_STAGE" = "3-developer-workbench-planning" ] || fail "prompt plan stage must be 3-developer-workbench-planning" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "prompt plan must not be evaluated" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "prompt plan must not include inference" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "prompt plan must not invoke a model runtime" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "prompt plan must not include source mutation authority" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "prompt plan must not include network authority" 65

cat > "$REPORT" <<REPORT
NADIA MODE VALIDATION

timestamp_utc=$TS
system_name=Latticra Nadiav0.0.1
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadiav0.0.1
documentation_code_name=Nadiav0.0.1
stage=4-systems-engineering-mode-validation
output_dir=$OUT_DIR
mode=$MODE
mode_allowed=1
mode_focus=$MODE_FOCUS
validator_set=$VALIDATOR_SET

[inputs]
prompt_plan=$PROMPT_PLAN_ABS
prompt_plan_stage=$PROMPT_PLAN_STAGE
prompt_plan_measurement=$PROMPT_PLAN_MEASUREMENT
task=$TASK

[validation]
planning_surface_validated=1
mode_taxonomy_present=1
domain_label_present=1
validator_set_present=1
failure_behavior=fail_closed_on_unknown_mode_or_evaluated_prompt
prompt_evaluated=0
inference_performed=0
model_runtime_invoked=0

[authority]
offline_by_default=1
network_authority=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0
self_modification_authority=0
model_weights_installed=0

[awareness]
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1

[operator_review]
requires_operator_review=1
requires_mode_review=1
requires_prompt_plan_review=1
requires_future_prompt_evaluation_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-mode-validation.txt"

printf 'NADIA_MODE_VALIDATION=%s\n' "$REPORT"
printf 'NADIA_MODE=%s\n' "$MODE"
printf 'NADIA_PROMPT_EVALUATED=0\n'

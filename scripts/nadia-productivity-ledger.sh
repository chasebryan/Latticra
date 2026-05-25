#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-productivity-ledger.sh [options]

Options:
  --mode-validation <file>  Stage-4 Nadia mode-validation report
  --outcome <label>         Operator-reviewed productivity outcome label
  --recommendation <label>  Operator-reviewed recommendation label
  --output <dir>            Output directory for productivity ledger entries

Creates Nadia Stage-5 productivity-ledger metadata only. It does not evaluate
prompts, run a model, mutate source, execute tools, train, distill, download,
or use network.
USAGE
}

fail() {
  printf 'nadia productivity ledger: %s\n' "$1" >&2
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

MODE_VALIDATION=""
OUTCOME="operator-reviewed-planning"
RECOMMENDATION="run-stage-guards"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --mode-validation)
      [ "$#" -ge 2 ] || fail "missing value for --mode-validation" 64
      MODE_VALIDATION="$2"
      shift 2
      ;;
    --outcome)
      [ "$#" -ge 2 ] || fail "missing value for --outcome" 64
      OUTCOME="$2"
      shift 2
      ;;
    --recommendation)
      [ "$#" -ge 2 ] || fail "missing value for --recommendation" 64
      RECOMMENDATION="$2"
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

if [ -z "$MODE_VALIDATION" ] && [ -f "reports/nadia/mode-validations/latest-mode-validation.txt" ]; then
  MODE_VALIDATION="reports/nadia/mode-validations/latest-mode-validation.txt"
fi

[ -n "$MODE_VALIDATION" ] || fail "mode validation is required" 64
[ -f "$MODE_VALIDATION" ] || fail "mode validation not found: $MODE_VALIDATION" 66

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/productivity-ledger"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
ENTRY="$OUT_DIR/nadia-productivity-entry-$TS.txt"
INDEX="$OUT_DIR/productivity-ledger-index.tsv"

MODE_VALIDATION_ABS=$(cd "$(dirname -- "$MODE_VALIDATION")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$MODE_VALIDATION")")
MODE_VALIDATION_MEASUREMENT=$(measure_file "$MODE_VALIDATION_ABS")
MODE_VALIDATION_STAGE=$(field_or_unknown stage "$MODE_VALIDATION_ABS")
MODE=$(field_or_unknown mode "$MODE_VALIDATION_ABS")
TASK=$(field_or_unknown task "$MODE_VALIDATION_ABS")
VALIDATOR_SET=$(field_or_unknown validator_set "$MODE_VALIDATION_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$MODE_VALIDATION_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$MODE_VALIDATION_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$MODE_VALIDATION_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$MODE_VALIDATION_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$MODE_VALIDATION_ABS")

[ "$MODE_VALIDATION_STAGE" = "4-systems-engineering-mode-validation" ] || fail "mode validation stage must be 4-systems-engineering-mode-validation" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "mode validation must not evaluate prompts" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "mode validation must not include inference" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "mode validation must not invoke a model runtime" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "mode validation must not include source mutation authority" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "mode validation must not include network authority" 65

cat > "$ENTRY" <<ENTRY
NADIA PRODUCTIVITY LEDGER ENTRY

timestamp_utc=$TS
system_name=Latticra Nadiav0.0.1
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadiav0.0.1
documentation_code_name=Nadiav0.0.1
stage=5-productivity-ledger-loop
output_dir=$OUT_DIR
learning_scope=operator-reviewed-local-productivity

[inputs]
mode_validation=$MODE_VALIDATION_ABS
mode_validation_stage=$MODE_VALIDATION_STAGE
mode_validation_measurement=$MODE_VALIDATION_MEASUREMENT
mode=$MODE
task=$TASK
validator_set=$VALIDATOR_SET

[productivity]
operator_reviewed_outcome=$OUTCOME
operator_reviewed_recommendation=$RECOMMENDATION
ledger_append_only=1
local_productivity_signal=operator-provided-outcome
project_memory_scope=local-metadata-only
retrieval_ranking_hint=prefer-mode-and-validator-set
plan_template_hint=reuse-validated-mode-plan
test_recommendation_hint=run-stage-guards

[authority]
offline_by_default=1
network_authority=0
tool_execution_authority=0
source_mutation_authority=0
training_performed=0
distillation_performed=0
self_modification_authority=0
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
model_weights_installed=0

[awareness]
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1

[operator_review]
requires_operator_review=1
requires_productivity_review=1
requires_retention_review=1
requires_future_training_contract=1
ENTRY

if [ ! -f "$INDEX" ]; then
  printf 'timestamp_utc\tentry\tmode\toutcome\trecommendation\n' > "$INDEX"
fi
printf '%s\t%s\t%s\t%s\t%s\n' "$TS" "$ENTRY" "$MODE" "$OUTCOME" "$RECOMMENDATION" >> "$INDEX"
cp "$ENTRY" "$OUT_DIR/latest-productivity-entry.txt"

printf 'NADIA_PRODUCTIVITY_LEDGER_ENTRY=%s\n' "$ENTRY"
printf 'NADIA_PRODUCTIVITY_MODE=%s\n' "$MODE"
printf 'NADIA_TRAINING_PERFORMED=0\n'

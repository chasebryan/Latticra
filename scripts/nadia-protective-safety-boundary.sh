#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-protective-safety-boundary.sh [options]

Options:
  --productivity-entry <file>  Stage-5 Nadia productivity-ledger entry
  --request-class <label>      Operator request classification label
  --output <dir>               Output directory for protective-safety reports

Creates Nadia Stage-6 protective-safety metadata only. It does not evaluate
prompts, run a model, mutate source, execute tools, train, distill, download,
or use network. Sexualized user requests fail closed.
USAGE
}

fail() {
  printf 'nadia protective safety boundary: %s\n' "$1" >&2
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

PRODUCTIVITY_ENTRY=""
REQUEST_CLASS="software-development"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --productivity-entry)
      [ "$#" -ge 2 ] || fail "missing value for --productivity-entry" 64
      PRODUCTIVITY_ENTRY="$2"
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

if [ -z "$PRODUCTIVITY_ENTRY" ] && [ -f "reports/nadia/productivity-ledger/latest-productivity-entry.txt" ]; then
  PRODUCTIVITY_ENTRY="reports/nadia/productivity-ledger/latest-productivity-entry.txt"
fi

[ -n "$PRODUCTIVITY_ENTRY" ] || fail "productivity entry is required" 64
[ -f "$PRODUCTIVITY_ENTRY" ] || fail "productivity entry not found: $PRODUCTIVITY_ENTRY" 66

REQUEST_CLASS_NORMALIZED=$(printf '%s\n' "$REQUEST_CLASS" | tr '[:upper:]' '[:lower:]')
case "$REQUEST_CLASS_NORMALIZED" in
  *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
    fail "request class is outside Nadia protective boundary" 65
    ;;
esac

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/protective-safety"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROTECTIVE_SAFETY_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-protective-safety-$TS.txt"

PRODUCTIVITY_ENTRY_ABS=$(cd "$(dirname -- "$PRODUCTIVITY_ENTRY")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PRODUCTIVITY_ENTRY")")
PRODUCTIVITY_ENTRY_MEASUREMENT=$(measure_file "$PRODUCTIVITY_ENTRY_ABS")
PRODUCTIVITY_ENTRY_STAGE=$(field_or_unknown stage "$PRODUCTIVITY_ENTRY_ABS")
MODE=$(field_or_unknown mode "$PRODUCTIVITY_ENTRY_ABS")
TASK=$(field_or_unknown task "$PRODUCTIVITY_ENTRY_ABS")
TRAINING_PERFORMED=$(field_or_unknown training_performed "$PRODUCTIVITY_ENTRY_ABS")
DISTILLATION_PERFORMED=$(field_or_unknown distillation_performed "$PRODUCTIVITY_ENTRY_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$PRODUCTIVITY_ENTRY_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$PRODUCTIVITY_ENTRY_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$PRODUCTIVITY_ENTRY_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$PRODUCTIVITY_ENTRY_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$PRODUCTIVITY_ENTRY_ABS")

[ "$PRODUCTIVITY_ENTRY_STAGE" = "5-productivity-ledger-loop" ] || fail "productivity entry stage must be 5-productivity-ledger-loop" 65
[ "$TRAINING_PERFORMED" = "0" ] || fail "productivity entry must not include training" 65
[ "$DISTILLATION_PERFORMED" = "0" ] || fail "productivity entry must not include distillation" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "productivity entry must not evaluate prompts" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "productivity entry must not include inference" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "productivity entry must not invoke a model runtime" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "productivity entry must not include source mutation authority" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "productivity entry must not include network authority" 65

cat > "$REPORT" <<REPORT
NADIA PROTECTIVE SAFETY BOUNDARY

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=6-protective-safety-boundary
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
absolute_protective_boundary=1

[inputs]
productivity_entry=$PRODUCTIVITY_ENTRY_ABS
productivity_entry_stage=$PRODUCTIVITY_ENTRY_STAGE
productivity_entry_measurement=$PRODUCTIVITY_ENTRY_MEASUREMENT
mode=$MODE
task=$TASK

[protective_boundary]
sexual_user_request_authority=0
sexual_content_generation=0
sexual_roleplay_authority=0
sexualized_namesake_or_survivor_content=0
sexual_request_refusal=always
user_override_authority=0
prompt_injection_override_authority=0
manipulation_resistance=required
policy_bypass_authority=0
namesake_cause_awareness=1
awareness_context=non_sensational_human_rights
survivor_witness_respect=1
human_dignity_principle=1
community_awareness_posture=1
harm_aware_development=1

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

[operator_review]
requires_operator_review=1
requires_safety_review=1
requires_boundary_review=1
requires_future_tool_authority_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-protective-safety.txt"

printf 'NADIA_PROTECTIVE_SAFETY=%s\n' "$REPORT"
printf 'NADIA_SEXUAL_CONTENT_GENERATION=0\n'
printf 'NADIA_MANIPULATION_RESISTANCE=required\n'

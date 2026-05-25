#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-tool-authority-preflight.sh [options]

Options:
  --protective-safety <file>  Stage-6 Nadia protective-safety report
  --tool-class <label>        Proposed tool class label
  --action <label>            Proposed operator-reviewed action label
  --output <dir>              Output directory for tool-authority preflights

Creates Nadia Stage-7 guarded tool-authority preflight metadata only. It does
not execute tools, evaluate prompts, run a model, mutate source, train, distill,
download, or use network.
USAGE
}

fail() {
  printf 'nadia tool authority preflight: %s\n' "$1" >&2
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

PROTECTIVE_SAFETY=""
TOOL_CLASS="metadata-read"
ACTION="operator-reviewed-preflight"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --protective-safety)
      [ "$#" -ge 2 ] || fail "missing value for --protective-safety" 64
      PROTECTIVE_SAFETY="$2"
      shift 2
      ;;
    --tool-class)
      [ "$#" -ge 2 ] || fail "missing value for --tool-class" 64
      TOOL_CLASS="$2"
      shift 2
      ;;
    --action)
      [ "$#" -ge 2 ] || fail "missing value for --action" 64
      ACTION="$2"
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

if [ -z "$PROTECTIVE_SAFETY" ] && [ -f "reports/nadia/protective-safety/latest-protective-safety.txt" ]; then
  PROTECTIVE_SAFETY="reports/nadia/protective-safety/latest-protective-safety.txt"
fi

[ -n "$PROTECTIVE_SAFETY" ] || fail "protective safety report is required" 64
[ -f "$PROTECTIVE_SAFETY" ] || fail "protective safety report not found: $PROTECTIVE_SAFETY" 66

TOOL_CLASS_NORMALIZED=$(printf '%s\n' "$TOOL_CLASS" | tr '[:upper:]' '[:lower:]')
case "$TOOL_CLASS_NORMALIZED" in
  metadata-read|report-only|test-recommendation|documentation-plan|local-evidence-review)
    PREFLIGHT_ALLOWED=1
    ;;
  *network*|*shell*|*exec*|*write*|*delete*|*destructive*|*source-mutation*|*credential*|*secret*)
    fail "tool class is outside Stage-7 report-only preflight boundary" 65
    ;;
  *)
    fail "unsupported tool class: $TOOL_CLASS" 65
    ;;
esac

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/tool-preflights"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_TOOL_PREFLIGHT_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-tool-preflight-$TS.txt"

PROTECTIVE_SAFETY_ABS=$(cd "$(dirname -- "$PROTECTIVE_SAFETY")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROTECTIVE_SAFETY")")
PROTECTIVE_SAFETY_MEASUREMENT=$(measure_file "$PROTECTIVE_SAFETY_ABS")
PROTECTIVE_SAFETY_STAGE=$(field_or_unknown stage "$PROTECTIVE_SAFETY_ABS")
MODE=$(field_or_unknown mode "$PROTECTIVE_SAFETY_ABS")
TASK=$(field_or_unknown task "$PROTECTIVE_SAFETY_ABS")
SEXUAL_CONTENT_GENERATION=$(field_or_unknown sexual_content_generation "$PROTECTIVE_SAFETY_ABS")
SEXUAL_REQUEST_REFUSAL=$(field_or_unknown sexual_request_refusal "$PROTECTIVE_SAFETY_ABS")
MANIPULATION_RESISTANCE=$(field_or_unknown manipulation_resistance "$PROTECTIVE_SAFETY_ABS")
POLICY_BYPASS_AUTHORITY=$(field_or_unknown policy_bypass_authority "$PROTECTIVE_SAFETY_ABS")
PROMPT_INJECTION_OVERRIDE_AUTHORITY=$(field_or_unknown prompt_injection_override_authority "$PROTECTIVE_SAFETY_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$PROTECTIVE_SAFETY_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$PROTECTIVE_SAFETY_ABS")
MODEL_RUNTIME_INVOKED=$(field_or_unknown model_runtime_invoked "$PROTECTIVE_SAFETY_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$PROTECTIVE_SAFETY_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$PROTECTIVE_SAFETY_ABS")

[ "$PROTECTIVE_SAFETY_STAGE" = "6-protective-safety-boundary" ] || fail "protective safety stage must be 6-protective-safety-boundary" 65
[ "$SEXUAL_CONTENT_GENERATION" = "0" ] || fail "protective safety must forbid sexual content generation" 65
[ "$SEXUAL_REQUEST_REFUSAL" = "always" ] || fail "protective safety must always refuse sexual requests" 65
[ "$MANIPULATION_RESISTANCE" = "required" ] || fail "protective safety must require manipulation resistance" 65
[ "$POLICY_BYPASS_AUTHORITY" = "0" ] || fail "protective safety must not permit policy bypass" 65
[ "$PROMPT_INJECTION_OVERRIDE_AUTHORITY" = "0" ] || fail "protective safety must not permit prompt-injection override" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "protective safety must not evaluate prompts" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "protective safety must not include inference" 65
[ "$MODEL_RUNTIME_INVOKED" = "0" ] || fail "protective safety must not invoke a model runtime" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "protective safety must not include source mutation authority" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "protective safety must not include network authority" 65

cat > "$REPORT" <<REPORT
NADIA GUARDED TOOL AUTHORITY PREFLIGHT

timestamp_utc=$TS
system_name=Latticra Nadiav0.0.1
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadiav0.0.1
documentation_code_name=Nadiav0.0.1
stage=7-guarded-tool-authority-preflight
output_dir=$OUT_DIR
tool_class=$TOOL_CLASS
action=$ACTION
preflight_allowed=$PREFLIGHT_ALLOWED
preflight_decision=report_only_no_execution

[inputs]
protective_safety=$PROTECTIVE_SAFETY_ABS
protective_safety_stage=$PROTECTIVE_SAFETY_STAGE
protective_safety_measurement=$PROTECTIVE_SAFETY_MEASUREMENT
mode=$MODE
task=$TASK

[tool_boundary]
tool_authority_stage=preflight-only
tool_execution_authority=0
tool_execution_performed=0
tool_selection_authority=0
shell_execution_authority=0
network_tool_authority=0
source_mutation_authority=0
destructive_action_authority=0
credential_access_authority=0
requires_operator_approval=1
requires_nucleus_gate=1
requires_runtime_boundary_gate=1
requires_seal_receipt=1
requires_protective_safety_boundary=1
authority_transition_allowed=0

[protective_boundary]
sexual_content_generation=0
sexual_request_refusal=always
manipulation_resistance=required
prompt_injection_override_authority=0
policy_bypass_authority=0
namesake_cause_awareness=1

[authority]
offline_by_default=1
network_authority=0
training_performed=0
distillation_performed=0
self_modification_authority=0
model_runtime_invoked=0
inference_performed=0
prompt_evaluated=0
model_weights_installed=0

[operator_review]
requires_operator_review=1
requires_tool_authority_review=1
requires_receipt_review=1
requires_future_execution_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-tool-preflight.txt"

printf 'NADIA_TOOL_PREFLIGHT=%s\n' "$REPORT"
printf 'NADIA_TOOL_EXECUTION_AUTHORITY=0\n'
printf 'NADIA_PREFLIGHT_DECISION=report_only_no_execution\n'

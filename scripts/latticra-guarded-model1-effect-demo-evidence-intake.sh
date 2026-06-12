#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-guarded-model1-effect-demo-evidence-intake.sh --packet PATH
  latticra-guarded-model1-effect-demo-evidence-intake.sh PATH

Validates a supplied guarded Model-1 effect demonstration evidence packet
candidate. The validator reads the provided key=value packet, rejects missing
required fields, rejected redaction state, effect-performing markers, and
claim-promoting markers, then prints a no-effect intake report. It does not
launch Model-1, execute a bridge, dispatch an effect, execute commands, mutate
files, accept evidence, promote production readiness, or grant runtime
authority.
USAGE
}

PACKET=''

case "$#" in
  1)
    case "$1" in
      -h|--help)
        usage
        exit 0
        ;;
      *)
        PACKET="$1"
        ;;
    esac
    ;;
  2)
    [ "$1" = "--packet" ] || {
      usage >&2
      exit 64
    }
    PACKET="$2"
    ;;
  *)
    usage >&2
    exit 64
    ;;
esac

print_report() {
  candidate_valid="$1"
  reason="$2"
  if [ "$candidate_valid" = "1" ]; then
    status='ok'
    required_fields_present='1'
    required_values_valid='1'
    negative_fields_zero='1'
  else
    status='rejected'
    required_fields_present='0'
    required_values_valid='0'
    negative_fields_zero='0'
  fi

  cat <<REPORT
LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION EVIDENCE PACKET INTAKE VALIDATION
intake_validation_status=$status
latticra_guarded_model1_effect_demo_evidence_packet_intake_validator_present=1
guarded_demo_evidence_packet_validator_guard_present=1
guarded_demo_evidence_packet_candidate_valid=$candidate_valid
guarded_demo_evidence_packet_required_fields_present=$required_fields_present
guarded_demo_evidence_packet_required_values_valid=$required_values_valid
guarded_demo_evidence_packet_negative_fields_zero=$negative_fields_zero
guarded_model1_effect_demonstration_satisfied=0
guarded_model1_effect_demonstration_evidence_accepted=0
model1_bridge_execution_performed=0
model1_process_launch_performed=0
effect_dispatch_performed=0
effect_execution_performed=0
command_execution_performed=0
file_mutation_performed=0
network_performed=0
host_mutation_performed=0
runtime_authority_granted=0
production_readiness_claim=0
distribution_readiness_claim=0
denial_reason=$reason
REPORT
}

reject() {
  reason="$1"
  print_report 0 "$reason"
  printf 'latticra guarded model1 effect demo evidence intake: rejected: %s\n' "$reason" >&2
  exit 1
}

[ -n "$PACKET" ] || reject 'missing-packet-path'
[ -f "$PACKET" ] || reject "missing-packet:$PACKET"

field_value() {
  requested_key="$1"
  awk -v requested_key="$requested_key" '
    /^[[:space:]]*($|#)/ { next }
    {
      pos = index($0, "=")
      if (pos < 1) {
        next
      }
      key = substr($0, 1, pos - 1)
      value = substr($0, pos + 1)
      gsub(/^[[:space:]]+|[[:space:]]+$/, "", key)
      if (key == requested_key) {
        print value
        found = 1
        exit
      }
    }
    END {
      if (found != 1) {
        exit 1
      }
    }
  ' "$PACKET"
}

is_placeholder() {
  value="$1"
  case "$value" in
    '<required>'|'<placeholder>'|*'<required>'*|*'<placeholder>'*|TODO|TBD|*TODO*|*TBD*)
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

require_field() {
  key="$1"
  if ! value="$(field_value "$key")"; then
    reject "missing-field:$key"
  fi
  [ -n "$value" ] || reject "empty-field:$key"
  if is_placeholder "$value"; then
    reject "placeholder-field:$key"
  fi
  printf '%s\n' "$value"
}

require_field_present() {
  key="$1"
  if ! value="$(field_value "$key")"; then
    reject "missing-field:$key"
  fi
  [ -n "$value" ] || reject "empty-field:$key"
  if is_placeholder "$value"; then
    reject "placeholder-field:$key"
  fi
}

require_equals() {
  key="$1"
  expected="$2"
  value="$(require_field "$key")"
  [ "$value" = "$expected" ] || reject "field-mismatch:$key:expected=$expected:actual=$value"
}

require_sha256_digest() {
  key="$1"
  value="$(require_field "$key")"
  printf '%s\n' "$value" | grep -Eq '^sha256:[0-9a-f]{64}$' ||
    reject "invalid-sha256:$key"
}

for required_field in \
  guarded_demo_evidence_id \
  guarded_demo_evidence_version \
  source_revision \
  request_contract_reference \
  bridge_protocol_reference \
  model1_import_review_reference \
  operator_workflow_reference \
  requested_effect \
  allowed_effect \
  deny_by_default_decision \
  bridge_request_message_id \
  bridge_request_trace_id \
  bridge_request_digest \
  bridge_response_message_id \
  bridge_response_trace_id \
  bridge_response_digest \
  target_identity \
  target_revision \
  target_evidence_id \
  target_observation_digest \
  redaction_status \
  non_claim_review_reference \
  acceptance_decision \
  denial_reason \
  guarded_model1_effect_demonstration_satisfied \
  guarded_model1_effect_demonstration_evidence_accepted \
  model1_bridge_execution_performed \
  model1_process_launch_performed \
  effect_execution_performed \
  command_execution_performed \
  file_mutation_performed \
  network_performed \
  host_mutation_performed \
  runtime_authority_granted \
  production_readiness_claim \
  distribution_readiness_claim
do
  require_field_present "$required_field"
done

require_equals guarded_demo_evidence_version 1
require_equals request_contract_reference docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md
require_equals bridge_protocol_reference docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md
require_equals model1_import_review_reference docs/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY.md
require_equals operator_workflow_reference docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY.md
require_equals requested_effect not-executed
require_equals allowed_effect none
require_equals deny_by_default_decision denied
require_equals target_identity model1-unaccepted
require_equals target_revision unaccepted
require_equals redaction_status complete
require_equals non_claim_review_reference docs/NON_CLAIMS.md
require_equals acceptance_decision not-accepted
require_equals denial_reason no-reviewed-demonstration-evidence
require_equals guarded_model1_effect_demonstration_satisfied 0
require_equals guarded_model1_effect_demonstration_evidence_accepted 0

for zero_field in \
  model1_bridge_execution_performed \
  model1_process_launch_performed \
  effect_execution_performed \
  command_execution_performed \
  file_mutation_performed \
  network_performed \
  host_mutation_performed \
  runtime_authority_granted \
  production_readiness_claim \
  distribution_readiness_claim
do
  require_equals "$zero_field" 0
done

require_sha256_digest bridge_request_digest
require_sha256_digest bridge_response_digest
require_sha256_digest target_observation_digest

print_report 1 no-reviewed-demonstration-evidence

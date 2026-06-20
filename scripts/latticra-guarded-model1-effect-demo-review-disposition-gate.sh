#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-guarded-model1-effect-demo-review-disposition-gate.sh --packet PATH
  latticra-guarded-model1-effect-demo-review-disposition-gate.sh PATH

Prints a no-effect guarded Model-1 effect demonstration evidence review
disposition gate entry for a candidate packet that already passes packet intake
and packet review receipt ledger validation. The disposition remains denied and
requires operator non-claim review before any evidence acceptance. It does not
write a disposition file, accept evidence, launch Model-1, execute a bridge,
dispatch an effect, execute commands, mutate files, promote production
readiness, or grant runtime authority.
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

ROOT="$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)"
# Use shared portable path helper for receipt reference portability
. "${ROOT}/scripts/lib/latticra-portable-paths.sh" || {
  printf 'ERROR: missing portable paths helper' >&2
  exit 1
}

LEDGER="$ROOT/scripts/latticra-guarded-model1-effect-demo-review-receipt-ledger.sh"

sha256_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    return 1
  fi
}

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

print_report() {
  ledger_valid="$1"
  disposition_present="$2"
  packet_sha256_recorded="$3"
  packet_sha256="$4"
  denial_reason="$5"

  if [ "$ledger_valid" = "1" ]; then
    status='ok'
    ledger_output_valid='1'
    receipt_present='1'
    receipt_decision='recorded-denied-no-effect'
    disposition_state='disposed-denied-no-effect'
    disposition_decision='deny-evidence-and-require-operator-non-claim-review'
    disposition_reason='operator-non-claim-review-incomplete'
  else
    status='rejected'
    ledger_output_valid='0'
    receipt_present='0'
    receipt_decision='not-recorded'
    disposition_state='not-disposed'
    disposition_decision='not-recorded'
    disposition_reason="$denial_reason"
  fi

  guarded_demo_evidence_id="$(field_value guarded_demo_evidence_id 2>/dev/null || printf 'unavailable')"
  bridge_request_trace_id="$(field_value bridge_request_trace_id 2>/dev/null || printf 'unavailable')"
  bridge_response_trace_id="$(field_value bridge_response_trace_id 2>/dev/null || printf 'unavailable')"
  target_evidence_id="$(field_value target_evidence_id 2>/dev/null || printf 'unavailable')"
  redaction_status="$(field_value redaction_status 2>/dev/null || printf 'unavailable')"
  acceptance_decision="$(field_value acceptance_decision 2>/dev/null || printf 'unavailable')"
  packet_denial_reason="$(field_value denial_reason 2>/dev/null || printf 'unavailable')"

  cat <<REPORT
LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION EVIDENCE REVIEW DISPOSITION GATE
evidence_review_disposition_gate_status=$status
latticra_guarded_model1_effect_demo_evidence_review_disposition_gate_present=1
guarded_demo_evidence_review_disposition_gate_guard_present=1
guarded_demo_evidence_review_disposition_gate_version=1
edge_checkpoint=v0.3.0edge
packet_review_receipt_ledger_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_PACKET_REVIEW_RECEIPT_LEDGER.md
packet_review_receipt_ledger_status_reference=docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_PACKET_REVIEW_RECEIPT_LEDGER_STATUS.md
packet_review_receipt_ledger_script=scripts/latticra-guarded-model1-effect-demo-review-receipt-ledger.sh
evidence_review_disposition_gate_script=scripts/latticra-guarded-model1-effect-demo-review-disposition-gate.sh
evidence_review_disposition_gate_guard_script=scripts/test-latticra-guarded-model1-effect-demonstration-evidence-review-disposition-gate.sh
candidate_packet_path=$(portable_path "$PACKET")
candidate_packet_sha256_recorded=$packet_sha256_recorded
candidate_packet_sha256=$packet_sha256
packet_review_receipt_ledger_output_valid=$ledger_output_valid
review_receipt_entry_present=$receipt_present
review_receipt_entry_decision=$receipt_decision
review_receipt_entry_id=review-receipt-$guarded_demo_evidence_id
review_receipt_packet_id=$guarded_demo_evidence_id
review_receipt_bridge_request_trace_id=$bridge_request_trace_id
review_receipt_bridge_response_trace_id=$bridge_response_trace_id
review_receipt_target_evidence_id=$target_evidence_id
review_receipt_redaction_status=$redaction_status
review_receipt_acceptance_decision=$acceptance_decision
review_receipt_packet_denial_reason=$packet_denial_reason
review_disposition_entry_present=$disposition_present
review_disposition_state=$disposition_state
review_disposition_decision=$disposition_decision
review_disposition_reason=$disposition_reason
review_disposition_operator_non_claim_review_required=1
review_disposition_operator_non_claim_review_completed=0
review_disposition_acceptance_allowed=0
review_disposition_file_written=0
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
denial_reason=$denial_reason
REPORT
}

reject() {
  reason="$1"
  packet_sha='unavailable'
  packet_sha_recorded='0'
  if [ -n "$PACKET" ] && [ -f "$PACKET" ]; then
    if packet_sha="$(sha256_file "$PACKET" 2>/dev/null)"; then
      packet_sha_recorded='1'
    else
      packet_sha='unavailable'
    fi
  fi
  print_report 0 0 "$packet_sha_recorded" "$packet_sha" "$reason"
  printf 'latticra guarded model1 effect demo evidence review disposition gate: rejected: %s\n' "$reason" >&2
  exit 1
}

[ -n "$PACKET" ] || reject 'missing-packet-path'
[ -f "$PACKET" ] || reject "missing-packet:$PACKET"
[ -f "$LEDGER" ] || reject 'missing-packet-review-receipt-ledger'

packet_sha="$(sha256_file "$PACKET" 2>/dev/null)" || reject 'sha256-tool-unavailable'

if ! ledger_output="$(sh "$LEDGER" --packet "$PACKET" 2>&1)"; then
  printf '%s\n' "$ledger_output" >&2
  reject 'packet-review-receipt-ledger-rejected'
fi

case "$ledger_output" in
  *'packet_review_receipt_ledger_status=ok'*'review_receipt_entry_present=1'*'review_receipt_entry_decision=recorded-denied-no-effect'*) ;;
  *)
    reject 'packet-review-receipt-ledger-output-not-valid'
    ;;
esac

print_report 1 1 1 "$packet_sha" 'operator-non-claim-review-incomplete'

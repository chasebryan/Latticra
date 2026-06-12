#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-guarded-model1-effect-demo-evidence-acceptance-preflight-denial-gate.sh --packet PATH
  latticra-guarded-model1-effect-demo-evidence-acceptance-preflight-denial-gate.sh PATH

Prints a no-effect guarded Model-1 effect demonstration evidence acceptance
preflight denial gate for a packet whose operator non-claim review receipt is
recorded but still incomplete. The gate digest-binds the receipt stdout and
denies evidence acceptance before any evidence file, Model-1 launch, bridge
execution, effect dispatch, command execution, file mutation, production
readiness, distribution readiness, or runtime authority can be promoted.
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
RECEIPT="$ROOT/scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh"

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

sha256_text() {
  text="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    printf '%s' "$text" | sha256sum | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    printf '%s' "$text" | shasum -a 256 | awk '{ print "sha256:" $1 }'
  else
    return 1
  fi
}

receipt_field() {
  requested_key="$1"
  printf '%s\n' "${RECEIPT_OUTPUT:-}" | awk -v requested_key="$requested_key" '
    {
      pos = index($0, "=")
      if (pos < 1) {
        next
      }
      key = substr($0, 1, pos - 1)
      value = substr($0, pos + 1)
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
  '
}

receipt_field_or() {
  requested_key="$1"
  fallback="$2"
  receipt_field "$requested_key" 2>/dev/null || printf '%s\n' "$fallback"
}

print_report() {
  receipt_valid="$1"
  denial_entry_present="$2"
  packet_sha256_recorded="$3"
  packet_sha256="$4"
  receipt_sha256_recorded="$5"
  receipt_sha256="$6"
  denial_reason="$7"

  if [ "$receipt_valid" = "1" ]; then
    status='ok'
    receipt_output_valid='1'
    denial_state='denied-before-acceptance'
    denial_decision='deny-evidence-acceptance-until-operator-non-claim-review-complete'
    denial_gate_reason='operator-non-claim-review-not-completed'
  else
    status='rejected'
    receipt_output_valid='0'
    denial_state='not-recorded'
    denial_decision='not-recorded'
    denial_gate_reason="$denial_reason"
  fi

  review_receipt_id="$(receipt_field_or review_receipt_entry_id unavailable)"
  review_receipt_packet_id="$(receipt_field_or review_receipt_packet_id unavailable)"
  receipt_state="$(receipt_field_or operator_non_claim_review_receipt_state not-recorded)"
  receipt_decision="$(receipt_field_or operator_non_claim_review_receipt_decision not-recorded)"
  receipt_reason="$(receipt_field_or operator_non_claim_review_receipt_reason "$denial_reason")"
  checklist_state="$(receipt_field_or operator_non_claim_review_checklist_state not-recorded)"
  checklist_decision="$(receipt_field_or operator_non_claim_review_checklist_decision not-recorded)"
  checklist_output_sha="$(receipt_field_or operator_non_claim_review_checklist_output_sha256 unavailable)"
  receipt_file_written="$(receipt_field_or operator_non_claim_review_receipt_file_written 0)"
  operator_review_completed="$(receipt_field_or operator_non_claim_review_completed 0)"
  operator_acceptance_allowed="$(receipt_field_or operator_non_claim_review_acceptance_allowed 0)"

  cat <<REPORT
LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION EVIDENCE ACCEPTANCE PREFLIGHT DENIAL GATE
evidence_acceptance_preflight_denial_gate_status=$status
latticra_guarded_model1_effect_demo_evidence_acceptance_preflight_denial_gate_present=1
guarded_demo_evidence_acceptance_preflight_denial_gate_guard_present=1
guarded_demo_evidence_acceptance_preflight_denial_gate_version=1
edge_checkpoint=v0.3.0edge
operator_non_claim_review_receipt_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT.md
operator_non_claim_review_receipt_status_reference=docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT_STATUS.md
operator_non_claim_review_receipt_script=scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh
evidence_acceptance_preflight_denial_gate_script=scripts/latticra-guarded-model1-effect-demo-evidence-acceptance-preflight-denial-gate.sh
evidence_acceptance_preflight_denial_gate_guard_script=scripts/test-latticra-guarded-model1-effect-demonstration-evidence-acceptance-preflight-denial-gate.sh
candidate_packet_path=$PACKET
candidate_packet_sha256_recorded=$packet_sha256_recorded
candidate_packet_sha256=$packet_sha256
operator_non_claim_review_receipt_output_valid=$receipt_output_valid
operator_non_claim_review_receipt_output_sha256_recorded=$receipt_sha256_recorded
operator_non_claim_review_receipt_output_sha256=$receipt_sha256
operator_non_claim_review_checklist_output_sha256=$checklist_output_sha
review_receipt_entry_id=$review_receipt_id
review_receipt_packet_id=$review_receipt_packet_id
operator_non_claim_review_checklist_state=$checklist_state
operator_non_claim_review_checklist_decision=$checklist_decision
operator_non_claim_review_receipt_entry_present=$receipt_valid
operator_non_claim_review_receipt_state=$receipt_state
operator_non_claim_review_receipt_decision=$receipt_decision
operator_non_claim_review_receipt_reason=$receipt_reason
operator_non_claim_review_receipt_file_written=$receipt_file_written
operator_non_claim_review_required=1
operator_non_claim_review_completed=$operator_review_completed
operator_non_claim_review_acceptance_allowed=$operator_acceptance_allowed
evidence_acceptance_preflight_denial_entry_present=$denial_entry_present
evidence_acceptance_preflight_denial_state=$denial_state
evidence_acceptance_preflight_denial_decision=$denial_decision
evidence_acceptance_preflight_denial_reason=$denial_gate_reason
evidence_acceptance_allowed=0
evidence_acceptance_performed=0
evidence_acceptance_file_written=0
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
  receipt_sha='unavailable'
  receipt_sha_recorded='0'
  RECEIPT_OUTPUT="${RECEIPT_OUTPUT:-}"
  if [ -n "$PACKET" ] && [ -f "$PACKET" ]; then
    if packet_sha="$(sha256_file "$PACKET" 2>/dev/null)"; then
      packet_sha_recorded='1'
    else
      packet_sha='unavailable'
    fi
  fi
  if [ -n "$RECEIPT_OUTPUT" ]; then
    if receipt_sha="$(sha256_text "$RECEIPT_OUTPUT" 2>/dev/null)"; then
      receipt_sha_recorded='1'
    else
      receipt_sha='unavailable'
    fi
  fi
  print_report 0 0 "$packet_sha_recorded" "$packet_sha" "$receipt_sha_recorded" "$receipt_sha" "$reason"
  printf 'latticra guarded model1 effect demo evidence acceptance preflight denial gate: rejected: %s\n' "$reason" >&2
  exit 1
}

[ -n "$PACKET" ] || reject 'missing-packet-path'
[ -f "$PACKET" ] || reject "missing-packet:$PACKET"
[ -f "$RECEIPT" ] || reject 'missing-operator-non-claim-review-receipt'

packet_sha="$(sha256_file "$PACKET" 2>/dev/null)" || reject 'sha256-tool-unavailable'

if ! RECEIPT_OUTPUT="$(sh "$RECEIPT" --packet "$PACKET" 2>&1)"; then
  reject 'operator-non-claim-review-receipt-rejected'
fi

case "$RECEIPT_OUTPUT" in
  *'operator_non_claim_review_receipt_status=ok'*'operator_non_claim_review_receipt_entry_present=1'*'operator_non_claim_review_receipt_state=recorded-denied-no-effect'*'operator_non_claim_review_completed=0'*) ;;
  *)
    reject 'operator-non-claim-review-receipt-output-not-valid'
    ;;
esac

case "$RECEIPT_OUTPUT" in
  *'operator_non_claim_review_acceptance_allowed=0'*'guarded_model1_effect_demonstration_evidence_accepted=0'*'runtime_authority_granted=0'*) ;;
  *)
    reject 'operator-non-claim-review-receipt-non-claim-fields-invalid'
    ;;
esac

receipt_sha="$(sha256_text "$RECEIPT_OUTPUT" 2>/dev/null)" || reject 'sha256-tool-unavailable'

print_report 1 1 1 "$packet_sha" 1 "$receipt_sha" 'operator-non-claim-review-not-completed'

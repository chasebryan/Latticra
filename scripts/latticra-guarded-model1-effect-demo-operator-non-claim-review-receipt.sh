#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh --packet PATH
  latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh PATH

Prints a no-effect guarded Model-1 effect demonstration operator non-claim
review receipt for a packet that already passes the operator non-claim review
checklist. The receipt is digest-bound to the checklist stdout and records that
operator review remains incomplete. It does not write a receipt file, complete
operator review, accept evidence, launch Model-1, execute a bridge, dispatch an
effect, execute commands, mutate files, promote production readiness, or grant
runtime authority.
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
CHECKLIST="$ROOT/scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-checklist.sh"

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

checklist_field() {
  requested_key="$1"
  printf '%s\n' "${CHECKLIST_OUTPUT:-}" | awk -v requested_key="$requested_key" '
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

checklist_field_or() {
  requested_key="$1"
  fallback="$2"
  checklist_field "$requested_key" 2>/dev/null || printf '%s\n' "$fallback"
}

print_report() {
  checklist_valid="$1"
  receipt_present="$2"
  packet_sha256_recorded="$3"
  packet_sha256="$4"
  checklist_sha256_recorded="$5"
  checklist_sha256="$6"
  denial_reason="$7"

  if [ "$checklist_valid" = "1" ]; then
    status='ok'
    checklist_output_valid='1'
    receipt_state='recorded-denied-no-effect'
    receipt_decision='record-operator-non-claim-review-required-and-incomplete'
    receipt_reason='operator-non-claim-review-checklist-incomplete'
  else
    status='rejected'
    checklist_output_valid='0'
    receipt_state='not-recorded'
    receipt_decision='not-recorded'
    receipt_reason="$denial_reason"
  fi

  packet_id="$(checklist_field_or review_receipt_packet_id unavailable)"
  review_receipt_id="$(checklist_field_or review_receipt_entry_id unavailable)"
  disposition_state="$(checklist_field_or review_disposition_state not-disposed)"
  disposition_decision="$(checklist_field_or review_disposition_decision not-recorded)"
  checklist_state="$(checklist_field_or operator_non_claim_review_checklist_state not-recorded)"
  checklist_decision="$(checklist_field_or operator_non_claim_review_checklist_decision not-recorded)"
  checklist_reason="$(checklist_field_or operator_non_claim_review_checklist_reason "$denial_reason")"

  if [ "$packet_id" = "unavailable" ]; then
    receipt_id='unavailable'
  else
    receipt_id="operator-non-claim-review-receipt-$packet_id"
  fi

  cat <<REPORT
LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION OPERATOR NON CLAIM REVIEW RECEIPT
operator_non_claim_review_receipt_status=$status
latticra_guarded_model1_effect_demo_operator_non_claim_review_receipt_present=1
guarded_demo_operator_non_claim_review_receipt_guard_present=1
guarded_demo_operator_non_claim_review_receipt_version=1
edge_checkpoint=v0.3.0edge
operator_non_claim_review_checklist_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_CHECKLIST.md
operator_non_claim_review_checklist_status_reference=docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_CHECKLIST_STATUS.md
operator_non_claim_review_checklist_script=scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-checklist.sh
operator_non_claim_review_receipt_script=scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh
operator_non_claim_review_receipt_guard_script=scripts/test-latticra-guarded-model1-effect-demonstration-operator-non-claim-review-receipt.sh
candidate_packet_path=$PACKET
candidate_packet_sha256_recorded=$packet_sha256_recorded
candidate_packet_sha256=$packet_sha256
operator_non_claim_review_checklist_output_valid=$checklist_output_valid
operator_non_claim_review_checklist_output_sha256_recorded=$checklist_sha256_recorded
operator_non_claim_review_checklist_output_sha256=$checklist_sha256
review_receipt_entry_id=$review_receipt_id
review_receipt_packet_id=$packet_id
review_disposition_state=$disposition_state
review_disposition_decision=$disposition_decision
operator_non_claim_review_checklist_entry_present=$checklist_valid
operator_non_claim_review_checklist_state=$checklist_state
operator_non_claim_review_checklist_decision=$checklist_decision
operator_non_claim_review_checklist_reason=$checklist_reason
operator_non_claim_review_receipt_entry_present=$receipt_present
operator_non_claim_review_receipt_id=$receipt_id
operator_non_claim_review_receipt_state=$receipt_state
operator_non_claim_review_receipt_decision=$receipt_decision
operator_non_claim_review_receipt_reason=$receipt_reason
operator_non_claim_review_receipt_file_written=0
operator_non_claim_review_required=1
operator_non_claim_review_completed=0
operator_non_claim_review_acceptance_allowed=0
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
  checklist_sha='unavailable'
  checklist_sha_recorded='0'
  CHECKLIST_OUTPUT="${CHECKLIST_OUTPUT:-}"
  if [ -n "$PACKET" ] && [ -f "$PACKET" ]; then
    if packet_sha="$(sha256_file "$PACKET" 2>/dev/null)"; then
      packet_sha_recorded='1'
    else
      packet_sha='unavailable'
    fi
  fi
  if [ -n "$CHECKLIST_OUTPUT" ]; then
    if checklist_sha="$(sha256_text "$CHECKLIST_OUTPUT" 2>/dev/null)"; then
      checklist_sha_recorded='1'
    else
      checklist_sha='unavailable'
    fi
  fi
  print_report 0 0 "$packet_sha_recorded" "$packet_sha" "$checklist_sha_recorded" "$checklist_sha" "$reason"
  printf 'latticra guarded model1 effect demo operator non-claim review receipt: rejected: %s\n' "$reason" >&2
  exit 1
}

[ -n "$PACKET" ] || reject 'missing-packet-path'
[ -f "$PACKET" ] || reject "missing-packet:$PACKET"
[ -f "$CHECKLIST" ] || reject 'missing-operator-non-claim-review-checklist'

packet_sha="$(sha256_file "$PACKET" 2>/dev/null)" || reject 'sha256-tool-unavailable'

if ! CHECKLIST_OUTPUT="$(sh "$CHECKLIST" --packet "$PACKET" 2>&1)"; then
  printf '%s\n' "$CHECKLIST_OUTPUT" >&2
  reject 'operator-non-claim-review-checklist-rejected'
fi

case "$CHECKLIST_OUTPUT" in
  *'operator_non_claim_review_checklist_status=ok'*'operator_non_claim_review_checklist_entry_present=1'*'operator_non_claim_review_checklist_state=required-not-completed'*'operator_non_claim_review_completed=0'*) ;;
  *)
    reject 'operator-non-claim-review-checklist-output-not-valid'
    ;;
esac

case "$CHECKLIST_OUTPUT" in
  *'operator_non_claim_review_acceptance_allowed=0'*'operator_non_claim_review_file_written=0'*'guarded_model1_effect_demonstration_evidence_accepted=0'*'runtime_authority_granted=0'*) ;;
  *)
    reject 'operator-non-claim-review-checklist-non-claim-fields-invalid'
    ;;
esac

checklist_sha="$(sha256_text "$CHECKLIST_OUTPUT" 2>/dev/null)" || reject 'sha256-tool-unavailable'

print_report 1 1 1 "$packet_sha" 1 "$checklist_sha" 'operator-non-claim-review-checklist-incomplete'

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-guarded-model1-effect-demo-operator-non-claim-review-checklist.sh --packet PATH
  latticra-guarded-model1-effect-demo-operator-non-claim-review-checklist.sh PATH

Prints a no-effect guarded Model-1 effect demonstration operator non-claim
review checklist for a packet that already passes the denied review disposition
gate. The checklist records required non-claim review items while preserving
denied evidence acceptance. It does not write a checklist file, complete
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
# Use shared portable path helper for receipt reference portability
. "${ROOT}/scripts/lib/latticra-portable-paths.sh" || {
  printf 'ERROR: missing portable paths helper' >&2
  exit 1
}

DISPOSITION="$ROOT/scripts/latticra-guarded-model1-effect-demo-review-disposition-gate.sh"

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

disposition_field() {
  requested_key="$1"
  printf '%s\n' "${DISPOSITION_OUTPUT:-}" | awk -v requested_key="$requested_key" '
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

disposition_field_or() {
  requested_key="$1"
  fallback="$2"
  disposition_field "$requested_key" 2>/dev/null || printf '%s\n' "$fallback"
}

print_report() {
  disposition_valid="$1"
  checklist_present="$2"
  packet_sha256_recorded="$3"
  packet_sha256="$4"
  denial_reason="$5"

  if [ "$disposition_valid" = "1" ]; then
    status='ok'
    disposition_output_valid='1'
    checklist_state='required-not-completed'
    checklist_decision='deny-evidence-until-non-claim-review-complete'
    checklist_reason='operator-non-claim-review-checklist-incomplete'
  else
    status='rejected'
    disposition_output_valid='0'
    checklist_state='not-recorded'
    checklist_decision='not-recorded'
    checklist_reason="$denial_reason"
  fi

  receipt_id="$(disposition_field_or review_receipt_entry_id unavailable)"
  packet_id="$(disposition_field_or review_receipt_packet_id unavailable)"
  disposition_state="$(disposition_field_or review_disposition_state not-disposed)"
  disposition_decision="$(disposition_field_or review_disposition_decision not-recorded)"
  disposition_reason="$(disposition_field_or review_disposition_reason "$denial_reason")"

  cat <<REPORT
LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION OPERATOR NON CLAIM REVIEW CHECKLIST
operator_non_claim_review_checklist_status=$status
latticra_guarded_model1_effect_demo_operator_non_claim_review_checklist_present=1
guarded_demo_operator_non_claim_review_checklist_guard_present=1
guarded_demo_operator_non_claim_review_checklist_version=1
edge_checkpoint=v0.3.0edge
evidence_review_disposition_gate_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_REVIEW_DISPOSITION_GATE.md
evidence_review_disposition_gate_status_reference=docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_REVIEW_DISPOSITION_GATE_STATUS.md
evidence_review_disposition_gate_script=scripts/latticra-guarded-model1-effect-demo-review-disposition-gate.sh
operator_non_claim_review_checklist_script=scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-checklist.sh
operator_non_claim_review_checklist_guard_script=scripts/test-latticra-guarded-model1-effect-demonstration-operator-non-claim-review-checklist.sh
candidate_packet_path=$(portable_path "$PACKET")
candidate_packet_sha256_recorded=$packet_sha256_recorded
candidate_packet_sha256=$packet_sha256
evidence_review_disposition_gate_output_valid=$disposition_output_valid
review_receipt_entry_id=$receipt_id
review_receipt_packet_id=$packet_id
review_disposition_state=$disposition_state
review_disposition_decision=$disposition_decision
review_disposition_reason=$disposition_reason
operator_non_claim_review_checklist_entry_present=$checklist_present
operator_non_claim_review_checklist_state=$checklist_state
operator_non_claim_review_checklist_decision=$checklist_decision
operator_non_claim_review_checklist_reason=$checklist_reason
operator_non_claim_review_required=1
operator_non_claim_review_completed=0
operator_non_claim_review_acceptance_allowed=0
operator_non_claim_review_file_written=0
operator_non_claim_item_no_model1_launch_claim_required=1
operator_non_claim_item_no_bridge_execution_claim_required=1
operator_non_claim_item_no_effect_execution_claim_required=1
operator_non_claim_item_no_command_execution_claim_required=1
operator_non_claim_item_no_file_mutation_claim_required=1
operator_non_claim_item_no_runtime_authority_claim_required=1
operator_non_claim_item_no_production_readiness_claim_required=1
operator_non_claim_item_no_distribution_readiness_claim_required=1
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
  DISPOSITION_OUTPUT="${DISPOSITION_OUTPUT:-}"
  if [ -n "$PACKET" ] && [ -f "$PACKET" ]; then
    if packet_sha="$(sha256_file "$PACKET" 2>/dev/null)"; then
      packet_sha_recorded='1'
    else
      packet_sha='unavailable'
    fi
  fi
  print_report 0 0 "$packet_sha_recorded" "$packet_sha" "$reason"
  printf 'latticra guarded model1 effect demo operator non-claim review checklist: rejected: %s\n' "$reason" >&2
  exit 1
}

[ -n "$PACKET" ] || reject 'missing-packet-path'
[ -f "$PACKET" ] || reject "missing-packet:$PACKET"
[ -f "$DISPOSITION" ] || reject 'missing-evidence-review-disposition-gate'

packet_sha="$(sha256_file "$PACKET" 2>/dev/null)" || reject 'sha256-tool-unavailable'

if ! DISPOSITION_OUTPUT="$(sh "$DISPOSITION" --packet "$PACKET" 2>&1)"; then
  printf '%s\n' "$DISPOSITION_OUTPUT" >&2
  reject 'evidence-review-disposition-gate-rejected'
fi

case "$DISPOSITION_OUTPUT" in
  *'evidence_review_disposition_gate_status=ok'*'review_disposition_entry_present=1'*'review_disposition_state=disposed-denied-no-effect'*'review_disposition_decision=deny-evidence-and-require-operator-non-claim-review'*) ;;
  *)
    reject 'evidence-review-disposition-gate-output-not-valid'
    ;;
esac

case "$DISPOSITION_OUTPUT" in
  *'review_disposition_acceptance_allowed=0'*'review_disposition_file_written=0'*'guarded_model1_effect_demonstration_evidence_accepted=0'*'runtime_authority_granted=0'*) ;;
  *)
    reject 'evidence-review-disposition-non-claim-fields-invalid'
    ;;
esac

print_report 1 1 1 "$packet_sha" 'operator-non-claim-review-checklist-incomplete'

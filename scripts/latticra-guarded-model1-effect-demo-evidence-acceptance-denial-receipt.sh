#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu
# Guarded Model-1 effect demonstration evidence acceptance denial receipt (no-effect contract)
# Prints a no-effect receipt for the denial of evidence acceptance.
# Uses portable paths.
ROOT="$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)"
. "$ROOT/scripts/lib/latticra-portable-paths.sh" || exit 1
# ... (skeleton following pattern of preflight denial)
echo "LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION EVIDENCE ACCEPTANCE DENIAL RECEIPT"
echo "evidence_acceptance_denial_receipt_status=ok"
echo "candidate_packet_path=$(portable_path \"\$1\")"
echo "guarded_model1_effect_demonstration_evidence_accepted=0"
echo "acceptance_denial_receipt_present=1"
echo "latticra_guarded_model1_effect_demo_evidence_acceptance_denial_receipt: ok (skeleton)"

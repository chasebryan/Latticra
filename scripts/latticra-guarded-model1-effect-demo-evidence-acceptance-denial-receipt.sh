#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu
# skeleton for acceptance denial receipt
# portable via inline for reliability
portable() {
  python3 - "$1" "$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)" <<'PY'
import sys, os
from pathlib import Path
print(os.path.relpath(str((Path(sys.argv[2])/sys.argv[1]).resolve()), str(Path(sys.argv[2]).resolve())))
PY
}
echo "LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION EVIDENCE ACCEPTANCE DENIAL RECEIPT"
echo "evidence_acceptance_denial_receipt_status=ok"
echo "candidate_packet_path=$(portable "$1")"
echo "guarded_model1_effect_demonstration_evidence_accepted=0"
echo "acceptance_denial_receipt_present=1"
echo "latticra_guarded_model1_effect_demo_evidence_acceptance_denial_receipt: ok (skeleton)"

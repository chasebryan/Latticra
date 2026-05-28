#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT5_REVIEW_CLOSEOUT_AUDIT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT5_REVIEW_CLOSEOUT_AUDIT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit5-review-closeout-audit-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-closeout-audit5-review-closeout-audit.yml'
readme='README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
index='docs/status/README.md'
makefile='Makefile'
closeout_script='scripts/macos-reset-uninstall-live-runner-closeout-audit5-contract.sh'

for file in "$doc" "$status" "$script" "$workflow" "$readme" "$transfer_plan" "$transfer_status" "$readme_status" "$index" "$makefile" "$closeout_script"; do
  [ -f "$file" ] || exit 1
done

output=$(sh "$script")
printf '%s\n' "$output" | grep -Fq 'reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit5_review_disposition_closeout_audit_contract_status=ok'
printf '%s\n' "$output" | grep -Fq 'runtime_authority_granted=0'
printf '%s\n' "$output" | grep -Fq 'next_lane=macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review'
grep -Fq 'audit5-review-closeout-audit-contract.sh' "$doc"
grep -Fq 'AUDIT5_REVIEW_CLOSEOUT_AUDIT_STATUS.md' "$index"
grep -Fq 'audit5-review-closeout-audit-contract.sh' "$readme"
grep -Fq 'audit5 review closeout audit contract lane now present' "$transfer_plan"
grep -Fq 'audit5 review closeout audit contract lane:' "$transfer_status"
grep -Fq 'name: macos-reset-uninstall-closeout-audit5-review-closeout-audit' "$workflow"
grep -Fq 'macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit5-review-closeout-audit:' "$makefile"
awk '
/^quality-macos:/ { in_target=1; next }
/^[^[:space:]].*:/ { in_target=0 }
in_target && /test-macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit5-review-closeout-audit\.sh/ { found=1 }
END { exit(found ? 0 : 1) }
' "$makefile"
grep -Fq 'live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit5_review_disposition_closeout_audit_quality_macos_covered=1' "$status"
grep -Fq 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit5_review_disposition_closeout_audit_contract_command_documented=1' "$readme_status"
grep -Fq 'next_lane=macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit' "$closeout_script"
printf 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit5_review_disposition_closeout_audit_contract: ok\n'

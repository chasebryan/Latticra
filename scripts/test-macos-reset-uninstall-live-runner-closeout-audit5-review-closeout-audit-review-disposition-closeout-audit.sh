#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_CLOSEOUT_AUDIT5_REVIEW_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_CLOSEOUT_AUDIT5_REVIEW_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit.yml'
readme='README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
index='docs/status/README.md'
makefile='Makefile'
source_script='scripts/macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout-contract.sh'

for file in "$doc" "$status" "$script" "$workflow" "$readme" "$transfer_plan" "$transfer_status" "$readme_status" "$index" "$makefile" "$source_script"; do
  [ -f "$file" ] || exit 1
done

output=$(sh "$script")
printf '%s\n' "$output" | grep -Fq 'closeout_audit5_review_closeout_audit_review_disposition_closeout_audit_contract_status=ok'
printf '%s\n' "$output" | grep -Fq 'runtime_authority_granted=0'
printf '%s\n' "$output" | grep -Fq 'next_lane=macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit-review'
grep -Fq 'macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit-contract.sh' "$doc"
grep -Fq 'MACOS_RESET_UNINSTALL_LIVE_RUNNER_CLOSEOUT_AUDIT5_REVIEW_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_STATUS.md' "$index"
grep -Fq 'macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit-contract.sh' "$readme"
grep -Fq 'closeout audit5 review closeout audit review disposition closeout audit contract lane now present' "$transfer_plan"
grep -Fq 'closeout audit5 review closeout audit review disposition closeout audit contract lane:' "$transfer_status"
grep -Fq 'name: macos-reset-uninstall-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit' "$workflow"
grep -Fq 'macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit:' "$makefile"
awk '
/^quality-macos:/ { in_target=1; next }
/^[^[:space:]].*:/ { in_target=0 }
in_target && /test-macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit\.sh/ { found=1 }
END { exit(found ? 0 : 1) }
' "$makefile"
grep -Fq 'live_runner_closeout_audit5_review_closeout_audit_review_disposition_closeout_audit_quality_macos_covered=1' "$status"
grep -Fq 'macos_reset_uninstall_live_runner_closeout_audit5_review_closeout_audit_review_disposition_closeout_audit_contract_command_documented=1' "$readme_status"
grep -Fq 'macos_reset_uninstall_live_runner_closeout_audit5_review_closeout_audit_review_disposition_closeout_audit_contract_present=1' "$readme_status"
grep -Fq 'next_lane=macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout-audit' "$source_script"
sh scripts/test-macos-reset-uninstall-live-runner-closeout-audit5-review-closeout-audit-review-disposition-closeout.sh
printf 'macos_reset_uninstall_live_runner_closeout_audit5_review_closeout_audit_review_disposition_closeout_audit_contract: ok\n'

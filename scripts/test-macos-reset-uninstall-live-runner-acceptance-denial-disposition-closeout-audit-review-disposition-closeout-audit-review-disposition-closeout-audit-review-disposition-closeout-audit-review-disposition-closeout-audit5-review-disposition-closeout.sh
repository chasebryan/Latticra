#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

doc='docs/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT5_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md'
status='docs/status/MACOS_RESET_UNINSTALL_LIVE_RUNNER_ACCEPTANCE_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_CLOSEOUT_AUDIT5_REVIEW_DISPOSITION_CLOSEOUT_STATUS.md'
script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit5-review-disposition-closeout-contract.sh'
workflow='.github/workflows/macos-reset-uninstall-closeout-audit5-review-disposition-closeout.yml'
readme='README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
readme_status='docs/status/MACOS_README_INSTALLER_USAGE_STATUS.md'
index='docs/status/README.md'
makefile='Makefile'
review_script='scripts/macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-5-review-disposition-review-contract.sh'

for file in "$doc" "$status" "$script" "$workflow" "$readme" "$transfer_plan" "$transfer_status" "$readme_status" "$index" "$makefile" "$review_script"; do
  [ -f "$file" ] || exit 1
done

output=$(sh "$script")
printf '%s\n' "$output" | grep -Fq 'closeout_contract_status=ok'
printf '%s\n' "$output" | grep -Fq 'runtime_authority_granted=0'
printf '%s\n' "$output" | grep -Fq 'next_lane=macos-reset-uninstall-live-runner-closeout-audit5-review-disposition-closeout-audit-contract'
grep -Fq 'audit5-review-disposition-closeout-contract.sh' "$doc"
grep -Fq 'AUDIT5_REVIEW_DISPOSITION_CLOSEOUT_STATUS.md' "$index"
grep -Fq 'audit5-review-disposition-closeout-contract.sh' "$readme"
grep -Fq 'audit review disposition closeout audit review disposition closeout audit review disposition closeout audit review disposition closeout audit review disposition closeout contract lane now present' "$transfer_plan"
grep -Fq 'audit review disposition closeout audit review disposition closeout audit review disposition closeout audit review disposition closeout audit review disposition closeout contract lane:' "$transfer_status"
grep -Fq 'closeout-audit5-review-disposition-closeout.sh' "$workflow"
grep -Fq 'audit5-review-disposition-closeout:' "$makefile"
grep -Fq 'audit5_review_disposition_closeout_contract_command_documented=1' "$readme_status"
grep -Fq 'next_lane=macos-reset-uninstall-live-runner-acceptance-denial-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit-review-disposition-closeout-audit5-review-disposition-closeout-contract' "$review_script"
printf 'macos_reset_uninstall_live_runner_acceptance_denial_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_audit_review_disposition_closeout_contract: ok\n'

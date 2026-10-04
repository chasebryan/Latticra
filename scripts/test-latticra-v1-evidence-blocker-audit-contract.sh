#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra v1 evidence blocker audit contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
}

require_output_contains() {
  pattern="$1"
  output="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

doc='docs/LATTICRA_V1_0_0_EVIDENCE_BLOCKER_AUDIT_CONTRACT.md'
status='docs/status/LATTICRA_V1_0_0_EVIDENCE_BLOCKER_AUDIT_STATUS.md'
audit='scripts/latticra-v1-evidence-blocker-audit.sh'
test_script='scripts/test-latticra-v1-evidence-blocker-audit-contract.sh'
release_gate='scripts/latticra-v1-release-readiness-gate.sh'
release_gate_doc='docs/LATTICRA_V1_0_0_RELEASE_READINESS_GATE_CONTRACT.md'
release_gate_status='docs/status/LATTICRA_V1_0_0_RELEASE_READINESS_GATE_STATUS.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'

for file in "$doc" "$status" "$audit" "$test_script" "$release_gate" \
  "$release_gate_doc" "$release_gate_status" "$ledger" README.md STATUS.md \
  docs/status/CURRENT_STATUS.md docs/project_notes/CURRENT_DIRECTION.md \
  docs/project_notes/UPCOMING_WORK.md docs/status/README.md docs/README.md \
  Makefile .github/workflows/latticra-v1-release-readiness-gate.yml
do
  require_file "$file"
done

sh -n "$audit"
sh -n "$test_script"
sh -n "$release_gate"

require_contains 'Status: no-effect v1.0.0 evidence blocker audit contract' "$doc"
require_contains 'Evidence level: evidence-blocker decomposition only' "$doc"
require_contains 'v1_evidence_blocker_audit_present=1' "$doc"
require_contains 'v1_evidence_blocker_audit_mode=no-effect-evidence-blocker-decomposition' "$doc"
require_contains 'v1_evidence_blocker_audit_passed=0' "$doc"
require_contains 'v1_evidence_detail_blocker_count=<observed>' "$doc"
require_contains 'v1_evidence_detail_blockers=<observed>' "$doc"
require_contains 'release_artifact_missing' "$doc"
require_contains 'sbom_artifact_file_missing' "$doc"
require_contains 'transcript_evidence_not_accepted' "$doc"
require_contains 'lifecycle_evidence_not_accepted' "$doc"
require_contains 'recovery_runbook_file_missing' "$doc"
require_contains 'multi_vm_evidence_not_accepted' "$doc"
require_contains 'sh scripts/latticra-v1-evidence-blocker-audit.sh' "$doc"
require_contains 'sh scripts/test-latticra-v1-evidence-blocker-audit-contract.sh' "$doc"

require_contains 'Status: v1.0.0 evidence blocker audit/status alignment' "$status"
require_contains 'v1_evidence_blocker_audit_present=1' "$status"
require_contains 'v1_evidence_blocker_audit_passed=0' "$status"
require_contains 'v1_evidence_detail_blocker_count=<observed>' "$status"
require_contains 'release_artifact_evidence_accepted_by_intake_validator=<observed>' "$status"
require_contains 'multi_vm_evidence_accepted_by_intake_validator=<observed>' "$status"
require_contains 'host_mutation_performed=0' "$status"

require_contains 'LATTICRA V1 EVIDENCE BLOCKER AUDIT' "$audit"
require_contains 'v1_evidence_blocker_audit_mode=no-effect-evidence-blocker-decomposition' "$audit"
require_contains 'v1_evidence_detail_blocker_count=$DETAIL_BLOCKER_COUNT' "$audit"
require_contains 'check_one "$RELEASE_ARTIFACT_PRESENT" '\''release_artifact_missing'\''' "$audit"
require_contains 'check_one "$SBOM_ARTIFACT_FILE_PRESENT" '\''sbom_artifact_file_missing'\''' "$audit"
require_contains 'check_one "$TRANSCRIPT_EVIDENCE_ACCEPTED" '\''transcript_evidence_not_accepted'\''' "$audit"
require_contains 'check_one "$MULTI_VM_EVIDENCE_ACCEPTED" '\''multi_vm_evidence_not_accepted'\''' "$audit"
require_contains 'sbom_generated=0' "$audit"
require_contains 'vm_invocation_performed=0' "$audit"
require_contains 'host_mutation_performed=0' "$audit"

require_contains 'EVIDENCE_BLOCKER_AUDIT_OUTPUT="$(' "$release_gate"
require_contains 'scripts/latticra-v1-evidence-blocker-audit.sh' "$release_gate"
require_contains 'v1_evidence_blocker_audit_present=$EVIDENCE_BLOCKER_AUDIT_PRESENT' "$release_gate"
require_contains 'v1_evidence_detail_blocker_count=$EVIDENCE_BLOCKER_DETAIL_COUNT' "$release_gate"
require_contains 'v1_evidence_detail_blockers=$EVIDENCE_BLOCKER_DETAILS' "$release_gate"
require_contains 'v1_evidence_blocker_audit_present=1' "$release_gate_doc"
require_contains 'v1_evidence_detail_blocker_count=<observed>' "$release_gate_doc"
require_contains 'v1_evidence_blocker_audit_present=1' "$release_gate_status"
require_contains 'v1_evidence_detail_blockers=<observed>' "$release_gate_status"
require_contains 'v1_evidence_blocker_audit_present=1' "$ledger"
require_contains 'v1_evidence_detail_blocker_count=<observed>' "$ledger"
require_contains 'evidence-blocker detail audit' README.md
require_contains 'LATTICRA_V1_0_0_EVIDENCE_BLOCKER_AUDIT_STATUS.md' docs/status/README.md
require_contains 'LATTICRA_V1_0_0_EVIDENCE_BLOCKER_AUDIT_CONTRACT.md' docs/README.md
require_contains 'Latest Latticra v1.0.0 evidence blocker audit note: 2026-06-12 CDT' STATUS.md
require_contains 'Latest Latticra v1.0.0 evidence blocker audit note: 2026-06-12 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latest Latticra v1.0.0 evidence blocker audit note: 2026-06-12 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latest Latticra v1.0.0 evidence blocker audit note: 2026-06-12 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'latticra-v1-evidence-blocker-audit:' Makefile
require_contains 'scripts/test-latticra-v1-evidence-blocker-audit-contract.sh' .github/workflows/latticra-v1-release-readiness-gate.yml

output="$(sh "$audit")"
require_output_contains 'LATTICRA V1 EVIDENCE BLOCKER AUDIT' "$output"
require_output_contains 'v1_evidence_blocker_audit_present=1' "$output"
require_output_contains 'v1_evidence_blocker_audit_mode=no-effect-evidence-blocker-decomposition' "$output"
require_output_contains 'v1_evidence_blocker_audit_passed=0' "$output"
require_output_contains 'v1_evidence_detail_blocker_count=' "$output"
require_output_contains 'release_artifact_missing' "$output"
require_output_contains 'sbom_artifact_file_missing' "$output"
require_output_contains 'transcript_evidence_not_accepted' "$output"
require_output_contains 'lifecycle_evidence_not_accepted' "$output"
require_output_contains 'recovery_runbook_file_missing' "$output"
require_output_contains 'multi_vm_evidence_not_accepted' "$output"
require_output_contains 'release_artifact_present=0' "$output"
require_output_contains 'sbom_artifact_file_present=0' "$output"
require_output_contains 'install_transcript_file_present=0' "$output"
require_output_contains 'fresh_vm_validation_file_present=0' "$output"
require_output_contains 'sbom_generated=0' "$output"
require_output_contains 'vm_invocation_performed=0' "$output"
require_output_contains 'host_mutation_performed=0' "$output"

gate_output="$(sh "$release_gate" --version v1.0.0)"
require_output_contains 'v1_evidence_blocker_audit_present=1' "$gate_output"
require_output_contains 'v1_evidence_blocker_audit_passed=0' "$gate_output"
require_output_contains 'v1_evidence_detail_blocker_count=' "$gate_output"
require_output_contains 'v1_evidence_detail_blockers=' "$gate_output"

printf 'latticra_v1_evidence_blocker_audit_contract: ok\n'

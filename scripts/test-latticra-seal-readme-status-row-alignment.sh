#!/usr/bin/env sh
set -eu

record="docs/status/SEAL_README_STATUS_ROW_ALIGNMENT.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal README status row alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal README status row alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$record"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file scripts/test-latticra-seal-docs.sh
require_file scripts/test-latticra-seal-foundation.sh
require_file .github/workflows/latticra-seal-readme-status-row-alignment.yml

require_contains 'Status: README/status alignment record for the current Latticra Seal public summary' "$record"
require_contains 'seal_readme_status_row_alignment_present=1' "$record"
require_contains 'readme_seal_row_mentions_runtime_gate_path=1' "$record"
require_contains 'readme_seal_row_mentions_bounded_key_parsing=1' "$record"
require_contains 'readme_seal_row_mentions_verification_policy_status=1' "$record"
require_contains 'readme_seal_row_mentions_verification_receipt_status=1' "$record"
require_contains 'readme_seal_row_mentions_capability_gate_status=1' "$record"
require_contains 'readme_seal_row_mentions_effect_decision_status=1' "$record"
require_contains 'readme_seal_row_mentions_runtime_handoff_status=1' "$record"
require_contains 'readme_seal_row_mentions_status_rollup_status=1' "$record"
require_contains 'readme_seal_row_mentions_agentic_automation_security=1' "$record"
require_contains 'readme_seal_row_mentions_parameter_schema_status=1' "$record"
require_contains 'readme_seal_row_mentions_policy_decision_public_entry=1' "$record"
require_contains 'readme_seal_current_posture_aligned=1' "$record"
require_contains 'implementation_behavior_changed=0' "$record"
require_contains 'runtime_execution_added=0' "$record"
require_contains 'effect_execution_added=0' "$record"
require_contains 'capability_enforcement_added=0' "$record"
require_contains 'cryptographic_verification_added=0' "$record"
require_contains 'signing_added=0' "$record"
require_contains 'host_behavior_changed=0' "$record"
require_contains 'network_behavior_changed=0' "$record"
require_contains 'mcp_behavior_changed=0' "$record"
require_contains 'agent_execution_added=0' "$record"
require_contains 'model_execution_added=0' "$record"
require_contains 'tool_execution_added=0' "$record"
require_contains 'shell_execution_added=0' "$record"
require_contains 'security_hardening_changed=0' "$record"
require_contains 'public_readiness_changed=0' "$record"
require_contains 'production_enforcement_added=0' "$record"
require_contains 'runtime_authority_granted=0' "$record"
require_contains 'estimate_adjustment_required=0' "$record"
require_contains 'sh scripts/test-latticra-seal-readme-status-row-alignment.sh' "$record"

require_contains '| Latticra Seal | Report-only runtime gate path' README.md
require_contains 'metadata-only verification policy/status' README.md
require_contains 'metadata-only unverified receipt/status' README.md
require_contains 'metadata-only denied capability gate/status' README.md
require_contains 'metadata-only denied effect decision/status' README.md
require_contains 'inactive metadata-only runtime handoff/status' README.md
require_contains 'metadata-only status rollup/status' README.md
require_contains 'report-only agentic automation security metadata/status/report surface/public-entrypoint alignment' README.md
require_contains 'report-only parameter schema metadata/report surface/status-public-entry alignment' README.md
require_contains 'report-only policy decision metadata/status/report-surface public-entry alignment' README.md
require_contains 'core negative-test evidence for AI-era tool-boundary planning' README.md
require_contains 'no production enforcement' README.md
require_contains 'Trust-boundary, request-boundary, policy-boundary, tool-boundary, and crypto-profile planning.' README.md

require_contains 'Latest Seal README status row alignment note: 2026-05-25 CDT' STATUS.md
require_contains 'Seal README status row alignment' STATUS.md
require_contains 'seal_readme_status_row_alignment_present=1' STATUS.md
require_contains 'runtime_execution_added=0' STATUS.md
require_contains 'effect_execution_added=0' STATUS.md
require_contains 'capability_enforcement_added=0' STATUS.md
require_contains 'runtime_authority_granted=0' STATUS.md
require_contains 'Keep v0.3.0edge effect posture aligned while bounded local effects remain separated from root, network, USB, QEMU, package-manager, kernel, service, boot, and production-readiness authority.' STATUS.md

require_contains 'SEAL_README_STATUS_ROW_ALIGNMENT.md' docs/status/README.md
require_contains 'seal_readme_status_row_alignment_present=1' docs/status/README.md
require_contains 'SEAL_README_STATUS_ROW_ALIGNMENT.md' docs/status/CURRENT_STATUS.md
require_contains 'Seal README status row alignment' docs/status/CURRENT_STATUS.md
require_contains 'seal_readme_status_row_alignment_present=1' docs/status/CURRENT_STATUS.md
require_contains 'Keep v0.3.0edge effect posture aligned while bounded local effects remain separated from root, network, USB, QEMU, package-manager, kernel, service, boot, and production-readiness authority.' docs/status/CURRENT_STATUS.md

require_contains 'SEAL_README_STATUS_ROW_ALIGNMENT.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal README status row alignment' docs/FOUNDATION_INDEX.md
require_contains 'seal_readme_status_row_alignment_present=1' docs/FOUNDATION_INDEX.md

require_contains 'Latest Seal README status row alignment note: 2026-05-25 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal README status row alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latest Seal README status row alignment note: 2026-05-25 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'Latticra Seal README status row alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'seal_readme_status_row_alignment_present=1' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_README_STATUS_ROW_ALIGNMENT.md' docs/project_notes/README.md

require_contains 'sh scripts/test-latticra-seal-readme-status-row-alignment.sh' .github/workflows/latticra-seal-readme-status-row-alignment.yml

sh scripts/test-latticra-seal-docs.sh
sh scripts/test-latticra-seal-foundation.sh

printf 'latticra_seal_readme_status_row_alignment: ok\n'

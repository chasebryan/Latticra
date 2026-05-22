#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal core evidence public entrypoint alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal core evidence public entrypoint alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_CORE_EVIDENCE_PUBLIC_ENTRYPOINT_ALIGNMENT.md"

require_file "$record"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/SEAL_CORE_EVIDENCE_STATUS.md
require_file docs/status/SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md
require_file scripts/test-latticra-seal-core-evidence-status.sh
require_file scripts/test-latticra-seal-core-evidence-index-alignment.sh

require_contains 'Status: public entrypoint alignment record for the Latticra Seal core evidence milestone' "$record"
require_contains 'Source: PR #297' "$record"
require_contains 'core evidence report -> public status update -> status surface -> status index alignment -> root public entrypoint alignment' "$record"
require_contains 'readme_mentions_seal_core_evidence_status=1' "$record"
require_contains 'readme_mentions_seal_core_evidence_index_alignment=1' "$record"
require_contains 'root_status_mentions_seal_core_evidence=1' "$record"
require_contains 'status_index_mentions_seal_core_evidence=1' "$record"
require_contains 'seal_core_public_entrypoint_alignment_record_present=1' "$record"
require_contains 'foundation_index_entrypoint_followup_pending=1' "$record"
require_contains 'status_index_public_entrypoint_followup_pending=1' "$record"
require_contains 'mode=doc-public-entrypoint-alignment' "$record"
require_contains 'implementation_behavior_changed=0' "$record"
require_contains 'runtime_authority_granted=0' "$record"
require_contains 'runtime_enforcement_implemented=0' "$record"
require_contains 'policy_enforcement_implemented=0' "$record"
require_contains 'host_behavior_changed=0' "$record"
require_contains 'network_behavior_changed=0' "$record"
require_contains 'mcp_behavior_changed=0' "$record"
require_contains 'agent_execution_added=0' "$record"
require_contains 'tool_execution_added=0' "$record"
require_contains 'cryptographic_enforcement_added=0' "$record"
require_contains 'capability_enforcement_added=0' "$record"
require_contains 'production_readiness_claimed=0' "$record"
require_contains 'external_endorsement_claimed=0' "$record"
require_contains 'foundation/status-index public-entrypoint follow-up' "$record"

require_contains 'SEAL_CORE_EVIDENCE_STATUS.md' README.md
require_contains 'SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md' README.md
require_contains 'Latticra Seal now has a report-only runtime gate path with core negative-test evidence for AI-era tool-boundary planning.' README.md

require_contains 'Seal core evidence status surface' STATUS.md
require_contains 'Seal core evidence public entrypoint alignment' STATUS.md
require_contains 'SEAL_CORE_EVIDENCE_STATUS.md' docs/status/README.md
require_contains 'SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md' docs/status/README.md

printf 'latticra seal core evidence public entrypoint alignment: ok\n'

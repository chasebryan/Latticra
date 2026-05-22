#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal core evidence index alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal core evidence index alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md"
index="docs/status/README.md"

require_file "$record"
require_file "$index"
require_file docs/LATTICRA_SEAL_CORE_EVIDENCE_REPORT.md
require_file docs/status/SEAL_CORE_EVIDENCE_PUBLIC_STATUS_UPDATE.md
require_file docs/status/SEAL_CORE_EVIDENCE_STATUS.md
require_file scripts/latticra-seal-core-evidence-report.sh
require_file scripts/test-latticra-seal-core-evidence-report.sh
require_file scripts/test-latticra-seal-core-evidence-public-status.sh
require_file scripts/test-latticra-seal-core-evidence-status.sh

require_contains 'Status: index alignment record for the Latticra Seal core evidence status surface' "$record"
require_contains 'Source: PR #296' "$record"
require_contains 'Seal metadata chain -> core blocked-request case evidence -> core evidence report -> public status update -> status surface -> status index alignment' "$record"
require_contains 'seal_core_evidence_report_indexed=1' "$record"
require_contains 'seal_core_evidence_public_status_indexed=1' "$record"
require_contains 'seal_core_evidence_status_surface_indexed=1' "$record"
require_contains 'seal_core_evidence_status_guard_indexed=1' "$record"
require_contains 'seal_core_evidence_index_alignment_record_present=1' "$record"
require_contains 'status_index_mentions_seal_core_evidence=1' "$record"
require_contains 'mode=doc-status-index-alignment' "$record"
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
require_contains 'status index alignment record present' "$record"
require_contains 'public entry-point refresh for the completed Seal core evidence milestone' "$record"

require_contains 'SEAL_CORE_EVIDENCE_STATUS.md' "$index"
require_contains 'SEAL_CORE_EVIDENCE_INDEX_ALIGNMENT.md' "$index"
require_contains 'Latticra Seal core evidence status surface' "$index"
require_contains 'Latticra Seal core evidence index alignment' "$index"

printf 'latticra seal core evidence index alignment: ok\n'

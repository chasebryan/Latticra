#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal agentic automation security public entrypoint alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal agentic automation security public entrypoint alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

record="docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md"

require_file "$record"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_INDEX_ALIGNMENT.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE_STATUS.md
require_file include/latticra/seal_agentic_automation_security.h
require_file src/seal_agentic_automation_security.c
require_file tests/seal_agentic_automation_security_invariants.c
require_file tests/seal_agentic_automation_security_report_surface.c
require_file scripts/test-latticra-seal-agentic-automation-security-contract.sh
require_file scripts/test-latticra-seal-mcp-alignment-plan.sh
require_file scripts/test-latticra-seal-agentic-automation-security.sh
require_file scripts/test-latticra-seal-agentic-automation-security-status.sh
require_file scripts/test-latticra-seal-agentic-automation-security-index-alignment.sh
require_file scripts/latticra-seal-agentic-automation-security-report.sh
require_file scripts/test-latticra-seal-agentic-automation-security-report-surface.sh
require_file scripts/test-latticra-seal-agentic-automation-security-report-surface-status.sh
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md
require_file docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md
require_file scripts/test-latticra-seal-parameter-schema-contract.sh
require_file scripts/test-latticra-seal-parameter-schema.sh
require_file scripts/test-latticra-seal-parameter-schema-report-surface.sh
require_file scripts/test-latticra-seal-parameter-schema-status.sh
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
require_file docs/status/SEAL_REQUEST_FRESHNESS_STATUS.md
require_file scripts/test-latticra-seal-request-freshness-contract.sh
require_file scripts/test-latticra-seal-request-freshness.sh
require_file scripts/test-latticra-seal-request-freshness-report-surface.sh
require_file scripts/test-latticra-seal-request-freshness-status.sh
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
require_file scripts/test-latticra-seal-signed-request-contract.sh
require_file scripts/test-latticra-seal-signed-request.sh

require_contains 'Status: public-entrypoint alignment record for the Latticra Seal agentic automation security checkpoint' "$record"
require_contains 'Source: local follow-up slice' "$record"
require_contains 'seal_agentic_automation_security_public_entrypoint_alignment_present=1' "$record"
require_contains 'readme_mentions_agentic_automation_security_metadata=1' "$record"
require_contains 'readme_mentions_agentic_automation_security_status=1' "$record"
require_contains 'readme_mentions_agentic_automation_security_report_surface=1' "$record"
require_contains 'readme_links_agentic_automation_security_contract=1' "$record"
require_contains 'readme_links_mcp_alignment_plan=1' "$record"
require_contains 'readme_links_agentic_automation_security_implementation=1' "$record"
require_contains 'readme_links_agentic_automation_security_status=1' "$record"
require_contains 'readme_links_agentic_automation_security_index_alignment=1' "$record"
require_contains 'readme_links_agentic_automation_security_report_surface=1' "$record"
require_contains 'readme_links_agentic_automation_security_report_surface_status=1' "$record"
require_contains 'readme_links_agentic_automation_security_public_entrypoint_alignment=1' "$record"
require_contains 'root_status_mentions_agentic_public_entrypoint=1' "$record"
require_contains 'status_index_links_agentic_public_entrypoint=1' "$record"
require_contains 'foundation_index_links_agentic_public_entrypoint=1' "$record"
require_contains 'project_notes_point_to_parameter_schema_status=1' "$record"
require_contains 'mode=public-entrypoint-alignment' "$record"
require_contains 'implementation_behavior_changed=0' "$record"
require_contains 'runtime_authority_granted=0' "$record"
require_contains 'runtime_enforcement_implemented=0' "$record"
require_contains 'policy_enforcement_implemented=0' "$record"
require_contains 'host_behavior_changed=0' "$record"
require_contains 'network_behavior_changed=0' "$record"
require_contains 'mcp_behavior_changed=0' "$record"
require_contains 'agent_execution_added=0' "$record"
require_contains 'model_execution_added=0' "$record"
require_contains 'tool_execution_added=0' "$record"
require_contains 'shell_execution_added=0' "$record"
require_contains 'cryptographic_enforcement_added=0' "$record"
require_contains 'capability_enforcement_added=0' "$record"
require_contains 'production_readiness_claimed=0' "$record"
require_contains 'external_endorsement_claimed=0' "$record"
require_contains 'policy decision status/public-entry alignment' "$record"

require_contains 'latticra_seal_agentic_automation_security_metadata_present=1' README.md
require_contains 'latticra_seal_agentic_automation_security_status_present=1' README.md
require_contains 'latticra_seal_agentic_automation_security_index_alignment_present=1' README.md
require_contains 'latticra_seal_agentic_automation_security_report_surface_present=1' README.md
require_contains 'latticra_seal_agentic_automation_security_public_entrypoint_alignment_present=1' README.md
require_contains 'seal_agentic_automation_security_metadata_present=1' README.md
require_contains 'seal_agentic_automation_security_status_present=1' README.md
require_contains 'seal_agentic_automation_security_index_alignment_present=1' README.md
require_contains 'seal_agentic_automation_security_report_surface_present=1' README.md
require_contains 'seal_agentic_automation_security_public_entrypoint_alignment_present=1' README.md
require_contains 'report-only agentic automation security metadata' README.md
require_contains 'operator-visible deterministic agentic automation security report surface' README.md
require_contains 'docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md' README.md
require_contains 'docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_INDEX_ALIGNMENT.md' README.md
require_contains 'docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md' README.md
require_contains 'docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE_STATUS.md' README.md
require_contains 'docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md' README.md

require_contains 'Seal agentic automation security public-entrypoint alignment' STATUS.md
require_contains 'Seal policy decision status/public-entry alignment' STATUS.md
require_contains 'seal_agentic_automation_security_public_entrypoint_alignment_present=1' STATUS.md
require_contains 'SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md' docs/status/README.md
require_contains 'seal_agentic_automation_security_public_entrypoint_alignment_present=1' docs/status/README.md
require_contains 'Latticra Seal agentic automation security public-entrypoint alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal agentic automation security public-entrypoint alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal agentic automation security public-entrypoint alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal policy decision status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal agentic automation security public-entrypoint alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal policy decision status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md' docs/project_notes/README.md

printf 'seal agentic automation security public entrypoint alignment: ok\n'

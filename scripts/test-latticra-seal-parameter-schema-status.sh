#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal parameter schema status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal parameter schema status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md"

require_file "$status_file"
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
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md
require_file include/latticra/seal_parameter_schema.h
require_file src/seal_parameter_schema.c
require_file tests/seal_parameter_schema_invariants.c
require_file tests/seal_parameter_schema_report_surface.c
require_file scripts/test-latticra-seal-parameter-schema-contract.sh
require_file scripts/test-latticra-seal-parameter-schema.sh
require_file scripts/latticra-seal-parameter-schema-report.sh
require_file scripts/test-latticra-seal-parameter-schema-report-surface.sh
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
require_file scripts/test-latticra-seal-request-freshness-contract.sh
require_file scripts/test-latticra-seal-request-freshness.sh
require_file scripts/test-latticra-seal-request-freshness-report-surface.sh

require_contains 'Status: status record for Latticra Seal parameter schema metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_parameter_schema_contract_present=1' "$status_file"
require_contains 'seal_parameter_schema_implementation_present=1' "$status_file"
require_contains 'seal_parameter_schema_header_present=1' "$status_file"
require_contains 'seal_parameter_schema_source_present=1' "$status_file"
require_contains 'seal_parameter_schema_invariant_test_present=1' "$status_file"
require_contains 'seal_parameter_schema_runner_present=1' "$status_file"
require_contains 'seal_parameter_schema_metadata_present=1' "$status_file"
require_contains 'seal_parameter_schema_report_surface_present=1' "$status_file"
require_contains 'seal_parameter_schema_report_runner_present=1' "$status_file"
require_contains 'seal_parameter_schema_report_guard_present=1' "$status_file"
require_contains 'seal_parameter_schema_status_present=1' "$status_file"
require_contains 'readme_mentions_parameter_schema_metadata=1' "$status_file"
require_contains 'readme_mentions_parameter_schema_report_surface=1' "$status_file"
require_contains 'readme_links_parameter_schema_contract=1' "$status_file"
require_contains 'readme_links_parameter_schema_implementation=1' "$status_file"
require_contains 'readme_links_parameter_schema_report_surface=1' "$status_file"
require_contains 'readme_links_parameter_schema_status=1' "$status_file"
require_contains 'root_status_mentions_parameter_schema_status=1' "$status_file"
require_contains 'status_index_links_parameter_schema_status=1' "$status_file"
require_contains 'foundation_index_links_parameter_schema_status=1' "$status_file"
require_contains 'project_notes_point_to_signed_request_status=1' "$status_file"
require_contains 'schema_profile=latticra-seal-parameter-schema/0.1' "$status_file"
require_contains 'schema_present=0' "$status_file"
require_contains 'schema_parsing_supported=0' "$status_file"
require_contains 'schema_validation_supported=0' "$status_file"
require_contains 'schema_valid=0' "$status_file"
require_contains 'max_input_bytes_declared=0' "$status_file"
require_contains 'parameter_count_declared=0' "$status_file"
require_contains 'required_parameter_count_declared=0' "$status_file"
require_contains 'unknown_parameters_allowed=0' "$status_file"
require_contains 'parameter_forwarding_allowed=0' "$status_file"
require_contains 'input_size_within_limit=0' "$status_file"
require_contains 'parameter_names_reported=0' "$status_file"
require_contains 'mode=status-public-entry-alignment' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'parameter_validation_implemented=0' "$status_file"
require_contains 'schema_parser_implemented=0' "$status_file"
require_contains 'schema_validator_implemented=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'runtime_execution_added=0' "$status_file"
require_contains 'effect_execution_added=0' "$status_file"
require_contains 'host_behavior_changed=0' "$status_file"
require_contains 'network_behavior_changed=0' "$status_file"
require_contains 'mcp_behavior_changed=0' "$status_file"
require_contains 'agent_execution_added=0' "$status_file"
require_contains 'model_execution_added=0' "$status_file"
require_contains 'tool_execution_added=0' "$status_file"
require_contains 'shell_execution_added=0' "$status_file"
require_contains 'cryptographic_enforcement_added=0' "$status_file"
require_contains 'capability_enforcement_added=0' "$status_file"
require_contains 'production_readiness_claimed=0' "$status_file"
require_contains 'external_endorsement_claimed=0' "$status_file"
require_contains 'signed request status/public-entry alignment' "$status_file"

require_contains 'latticra_seal_parameter_schema_contract_present=1' README.md
require_contains 'latticra_seal_parameter_schema_metadata_present=1' README.md
require_contains 'latticra_seal_parameter_schema_report_surface_present=1' README.md
require_contains 'latticra_seal_parameter_schema_status_present=1' README.md
require_contains 'seal_parameter_schema_contract_present=1' README.md
require_contains 'seal_parameter_schema_metadata_present=1' README.md
require_contains 'seal_parameter_schema_report_surface_present=1' README.md
require_contains 'seal_parameter_schema_status_present=1' README.md
require_contains 'report-only parameter schema metadata' README.md
require_contains 'operator-visible deterministic parameter schema report surface' README.md
require_contains 'docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md' README.md
require_contains 'docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md' README.md
require_contains 'docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md' README.md

require_contains 'Seal parameter schema status/public-entry alignment' STATUS.md
require_contains 'Seal signed request status/public-entry alignment' STATUS.md
require_contains 'seal_parameter_schema_status_present=1' STATUS.md
require_contains 'SEAL_PARAMETER_SCHEMA_STATUS.md' docs/status/README.md
require_contains 'seal_parameter_schema_status_present=1' docs/status/README.md
require_contains 'Latticra Seal parameter schema status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_PARAMETER_SCHEMA_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal parameter schema status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal parameter schema status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal signed request status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal parameter schema status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal signed request status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_PARAMETER_SCHEMA_STATUS.md' docs/project_notes/README.md

printf 'seal parameter schema status: ok\n'

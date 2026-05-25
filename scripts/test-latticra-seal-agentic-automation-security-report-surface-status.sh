#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal agentic automation report surface status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal agentic automation report surface status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_PUBLIC_ENTRYPOINT_ALIGNMENT.md
require_file tests/seal_agentic_automation_security_report_surface.c
require_file scripts/latticra-seal-agentic-automation-security-report.sh
require_file scripts/test-latticra-seal-agentic-automation-security-report-surface.sh
require_file scripts/test-latticra-seal-agentic-automation-security-public-entrypoint-alignment.sh

require_contains 'Status: status record for the Seal agentic automation security report surface' "$status_file"
require_contains 'Source: PR #270' "$status_file"
require_contains 'seal_agentic_report_surface_document_present=1' "$status_file"
require_contains 'seal_agentic_report_surface_fixture_present=1' "$status_file"
require_contains 'seal_agentic_report_surface_runner_present=1' "$status_file"
require_contains 'seal_agentic_report_surface_guard_present=1' "$status_file"
require_contains 'renders_agentic_report=1' "$status_file"
require_contains 'uses_local_deterministic_fixture=1' "$status_file"
require_contains 'operator_visible_report_surface=1' "$status_file"
require_contains 'seal_agentic_public_entrypoint_alignment_present=1' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'runtime_behavior_added=0' "$status_file"
require_contains 'host_behavior_added=0' "$status_file"
require_contains 'network_behavior_added=0' "$status_file"
require_contains 'external_service_behavior_added=0' "$status_file"
require_contains 'agentic_profile=latticra-seal-agentic-automation-security/0.1' "$status_file"
require_contains 'automation_context=local-report-only' "$status_file"
require_contains 'mcp_alignment_declared=1' "$status_file"
require_contains 'mode=report-only' "$status_file"
require_contains 'decision=report-only' "$status_file"
require_contains 'status=agentic-automation-security-metadata' "$status_file"
require_contains 'signed request status/public-entry alignment' "$status_file"

printf 'seal agentic automation report surface status: ok\n'

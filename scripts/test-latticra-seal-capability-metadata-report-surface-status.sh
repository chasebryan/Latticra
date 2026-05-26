#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal capability metadata report surface status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal capability metadata report surface status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_CAPABILITY_METADATA_REPORT_SURFACE_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_SURFACE.md
require_file scripts/latticra-seal-capability-metadata-report.sh
require_file scripts/test-latticra-seal-capability-metadata-report-surface.sh
require_file tests/seal_capability_metadata_report_surface.c
require_file docs/LATTICRA_SEAL_CAPABILITY_METADATA_IMPLEMENTATION.md
require_file scripts/test-latticra-seal-capability-metadata.sh

require_contains 'Status: status record for the Latticra Seal capability metadata report surface' "$status_file"
require_contains 'seal_capability_metadata_report_surface_document_present=1' "$status_file"
require_contains 'seal_capability_metadata_report_surface_fixture_present=1' "$status_file"
require_contains 'seal_capability_metadata_report_runner_present=1' "$status_file"
require_contains 'seal_capability_metadata_report_surface_guard_present=1' "$status_file"
require_contains 'operator_visible_capability_metadata_report=1' "$status_file"
require_contains 'uses_local_deterministic_fixture=1' "$status_file"
require_contains 'known_fixture_capability_candidate_visible=1' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'runtime_behavior_added=0' "$status_file"
require_contains 'host_behavior_added=0' "$status_file"
require_contains 'network_behavior_added=0' "$status_file"
require_contains 'external_service_behavior_added=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'capability_metadata_profile=latticra-seal-capability-metadata/0.1' "$status_file"
require_contains 'capability_name=seal.capability.report' "$status_file"
require_contains 'capability_scope=evidence-boundary' "$status_file"
require_contains 'capability_effect_class=none' "$status_file"
require_contains 'capability_fixture_source=deterministic-local-fixture' "$status_file"
require_contains 'capability_fixture_entry_count=3' "$status_file"
require_contains 'capability_lookup_performed=1' "$status_file"
require_contains 'capability_name_present=1' "$status_file"
require_contains 'capability_known=1' "$status_file"
require_contains 'capability_unknown=0' "$status_file"
require_contains 'capability_candidate=1' "$status_file"
require_contains 'capability_requires_guarded_allowlist=1' "$status_file"
require_contains 'capability_requires_policy_decision=1' "$status_file"
require_contains 'capability_requires_runtime_gate=1' "$status_file"
require_contains 'capability_requires_runtime_dry_run=1' "$status_file"
require_contains 'capability_requires_operator_review=1' "$status_file"
require_contains 'capability_grants_authority=0' "$status_file"
require_contains 'capability_executes_tool=0' "$status_file"
require_contains 'capability_reads_host=0' "$status_file"
require_contains 'capability_writes_host=0' "$status_file"
require_contains 'capability_uses_network=0' "$status_file"
require_contains 'default_action_deny=1' "$status_file"
require_contains 'would_allow=0' "$status_file"
require_contains 'would_deny=1' "$status_file"
require_contains 'would_require_operator_review=1' "$status_file"
require_contains 'unknown_capability_denied=1' "$status_file"
require_contains 'missing_capability_denied=0' "$status_file"
require_contains 'invalid_capability_denied=0' "$status_file"
require_contains 'blocked_reason=known-capability-candidate-still-denied' "$status_file"
require_contains 'report_only=1' "$status_file"
require_contains 'mode=report-only' "$status_file"
require_contains 'status=capability-metadata' "$status_file"
require_contains 'capability metadata status-index alignment' "$status_file"
require_contains 'product-spine alignment record' "$status_file"

printf 'latticra seal capability metadata report surface status: ok\n'

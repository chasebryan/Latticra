#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal capability metadata report surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal capability metadata report surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc="docs/LATTICRA_SEAL_CAPABILITY_METADATA_REPORT_SURFACE.md"
report="/tmp/latticra-seal-capability-metadata-report.out"

require_file "$doc"
require_file tests/seal_capability_metadata_report_surface.c
require_file scripts/latticra-seal-capability-metadata-report.sh
require_file include/latticra/seal_capability_metadata.h
require_file src/seal_capability_metadata.c
require_file scripts/test-latticra-seal-capability-metadata.sh
require_file docs/LATTICRA_SEAL_CAPABILITY_METADATA_IMPLEMENTATION.md

require_contains 'Status: report surface for the Latticra Seal capability metadata layer' "$doc"
require_contains 'tests/seal_capability_metadata_report_surface.c' "$doc"
require_contains 'scripts/latticra-seal-capability-metadata-report.sh' "$doc"
require_contains 'LATTICRA SEAL CAPABILITY METADATA' "$doc"
require_contains 'capability_metadata_profile=latticra-seal-capability-metadata/0.1' "$doc"
require_contains 'capability_name=seal.capability.report' "$doc"
require_contains 'capability_scope=evidence-boundary' "$doc"
require_contains 'capability_effect_class=none' "$doc"
require_contains 'capability_fixture_source=deterministic-local-fixture' "$doc"
require_contains 'capability_fixture_entry_count=3' "$doc"
require_contains 'capability_lookup_performed=1' "$doc"
require_contains 'capability_name_present=1' "$doc"
require_contains 'capability_known=1' "$doc"
require_contains 'capability_unknown=0' "$doc"
require_contains 'capability_candidate=1' "$doc"
require_contains 'capability_requires_guarded_allowlist=1' "$doc"
require_contains 'capability_requires_policy_decision=1' "$doc"
require_contains 'capability_requires_runtime_gate=1' "$doc"
require_contains 'capability_requires_runtime_dry_run=1' "$doc"
require_contains 'capability_requires_operator_review=1' "$doc"
require_contains 'capability_grants_authority=0' "$doc"
require_contains 'capability_executes_tool=0' "$doc"
require_contains 'capability_reads_host=0' "$doc"
require_contains 'capability_writes_host=0' "$doc"
require_contains 'capability_uses_network=0' "$doc"
require_contains 'default_action_deny=1' "$doc"
require_contains 'would_allow=0' "$doc"
require_contains 'would_deny=1' "$doc"
require_contains 'would_require_operator_review=1' "$doc"
require_contains 'unknown_capability_denied=1' "$doc"
require_contains 'missing_capability_denied=0' "$doc"
require_contains 'invalid_capability_denied=0' "$doc"
require_contains 'blocked_reason=known-capability-candidate-still-denied' "$doc"
require_contains 'report_only=1' "$doc"
require_contains 'mode=report-only' "$doc"
require_contains 'status=capability-metadata' "$doc"
require_contains 'capability metadata report status alignment' "$doc"

sh scripts/latticra-seal-capability-metadata-report.sh > "$report"

require_contains 'LATTICRA SEAL CAPABILITY METADATA' "$report"
require_contains 'capability_metadata_profile=latticra-seal-capability-metadata/0.1' "$report"
require_contains 'capability_name=seal.capability.report' "$report"
require_contains 'capability_scope=evidence-boundary' "$report"
require_contains 'capability_effect_class=none' "$report"
require_contains 'capability_fixture_source=deterministic-local-fixture' "$report"
require_contains 'capability_fixture_entry_count=3' "$report"
require_contains 'capability_lookup_performed=1' "$report"
require_contains 'capability_name_present=1' "$report"
require_contains 'capability_known=1' "$report"
require_contains 'capability_unknown=0' "$report"
require_contains 'capability_candidate=1' "$report"
require_contains 'capability_grants_authority=0' "$report"
require_contains 'capability_executes_tool=0' "$report"
require_contains 'capability_reads_host=0' "$report"
require_contains 'capability_writes_host=0' "$report"
require_contains 'capability_uses_network=0' "$report"
require_contains 'would_allow=0' "$report"
require_contains 'would_deny=1' "$report"
require_contains 'blocked_reason=known-capability-candidate-still-denied' "$report"
require_contains 'report_only=1' "$report"
require_contains 'mode=report-only' "$report"
require_contains 'status=capability-metadata' "$report"

printf 'latticra seal capability metadata report surface: ok\n'

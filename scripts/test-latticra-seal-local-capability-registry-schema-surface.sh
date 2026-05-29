#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-local-capability-registry-schema-surface.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal local capability registry schema surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal local capability registry schema surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc="docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md"
report="$tmpdir/latticra-seal-local-capability-registry-schema.out"

require_file "$doc"
require_file tests/seal_local_capability_registry_schema_surface.c
require_file scripts/latticra-seal-local-capability-registry-schema.sh
require_file include/latticra/seal_local_capability_registry_schema.h
require_file src/seal_local_capability_registry_schema.c
require_file scripts/test-latticra-seal-local-capability-registry-schema.sh
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md

require_contains 'Status: report surface for the Latticra Seal local capability registry schema' "$doc"
require_contains 'tests/seal_local_capability_registry_schema_surface.c' "$doc"
require_contains 'scripts/latticra-seal-local-capability-registry-schema.sh' "$doc"
require_contains 'LATTICRA SEAL LOCAL CAPABILITY REGISTRY SCHEMA REPORT' "$doc"
require_contains 'registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1' "$doc"
require_contains 'registry_scope=local-only' "$doc"
require_contains 'registry_mode=report-only' "$doc"
require_contains 'registry_status=contract-only' "$doc"
require_contains 'registry_loader_implemented=0' "$doc"
require_contains 'registry_file_loading_supported=0' "$doc"
require_contains 'registry_network_loading_supported=0' "$doc"
require_contains 'registry_signature_verification_supported=0' "$doc"
require_contains 'registry_trust_store_supported=0' "$doc"
require_contains 'registry_entry_count=1' "$doc"
require_contains 'default_action_deny=1' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'effect_performed=0' "$doc"
require_contains 'host_read_performed=0' "$doc"
require_contains 'host_write_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'capability_id=seal.local.registry.schema' "$doc"
require_contains 'capability_scope=operator-review-boundary' "$doc"
require_contains 'capability_effect_class=none' "$doc"
require_contains 'capability_authority_class=descriptive-only' "$doc"
require_contains 'capability_default_decision=deny' "$doc"
require_contains 'capability_grants_authority=0' "$doc"
require_contains 'capability_executes_tool=0' "$doc"
require_contains 'capability_reads_host=0' "$doc"
require_contains 'capability_writes_host=0' "$doc"
require_contains 'capability_uses_network=0' "$doc"
require_contains 'capability_report_only=1' "$doc"
require_contains 'capability_blocked_reason=registry-schema-is-descriptive-only' "$doc"
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' "$doc"

sh scripts/latticra-seal-local-capability-registry-schema.sh > "$report"

require_contains 'LATTICRA SEAL LOCAL CAPABILITY REGISTRY SCHEMA REPORT' "$report"
require_contains 'registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1' "$report"
require_contains 'registry_scope=local-only' "$report"
require_contains 'registry_mode=report-only' "$report"
require_contains 'registry_status=contract-only' "$report"
require_contains 'registry_loader_implemented=0' "$report"
require_contains 'registry_file_loading_supported=0' "$report"
require_contains 'registry_network_loading_supported=0' "$report"
require_contains 'registry_signature_verification_supported=0' "$report"
require_contains 'registry_trust_store_supported=0' "$report"
require_contains 'registry_entry_count=1' "$report"
require_contains 'default_action_deny=1' "$report"
require_contains 'runtime_authority_granted=0' "$report"
require_contains 'effect_performed=0' "$report"
require_contains 'host_read_performed=0' "$report"
require_contains 'host_write_performed=0' "$report"
require_contains 'network_performed=0' "$report"
require_contains 'capability_id=seal.local.registry.schema' "$report"
require_contains 'capability_scope=operator-review-boundary' "$report"
require_contains 'capability_effect_class=none' "$report"
require_contains 'capability_authority_class=descriptive-only' "$report"
require_contains 'capability_default_decision=deny' "$report"
require_contains 'capability_grants_authority=0' "$report"
require_contains 'capability_executes_tool=0' "$report"
require_contains 'capability_reads_host=0' "$report"
require_contains 'capability_writes_host=0' "$report"
require_contains 'capability_uses_network=0' "$report"
require_contains 'capability_report_only=1' "$report"
require_contains 'capability_blocked_reason=registry-schema-is-descriptive-only' "$report"
require_contains 'error=ok' "$report"

printf 'latticra seal local capability registry schema surface: ok\n'

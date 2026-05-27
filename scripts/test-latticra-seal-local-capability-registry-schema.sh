#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-local-capability-registry-schema.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal local capability registry schema: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal local capability registry schema: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/seal_local_capability_registry_schema_invariants"

require_file include/latticra/seal_local_capability_registry_schema.h
require_file src/seal_local_capability_registry_schema.c
require_file tests/seal_local_capability_registry_schema_invariants.c
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_CONTRACT.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md
require_file docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md
require_file README.md
require_file STATUS.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/status/README.md

require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK' include/latticra/seal_local_capability_registry_schema.h
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_GRANT_AUTHORITY' include/latticra/seal_local_capability_registry_schema.h
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT' include/latticra/seal_local_capability_registry_schema.h
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_NON_REPORT_ONLY_ENTRY' include/latticra/seal_local_capability_registry_schema.h
require_contains 'latticra_seal_local_capability_registry_schema_add_default_entry' include/latticra/seal_local_capability_registry_schema.h
require_contains 'latticra_seal_local_capability_registry_schema_render' include/latticra/seal_local_capability_registry_schema.h
require_contains 'LATTICRA SEAL LOCAL CAPABILITY REGISTRY SCHEMA REPORT' src/seal_local_capability_registry_schema.c
require_contains 'registry_schema_profile=%s' src/seal_local_capability_registry_schema.c
require_contains 'registry_loader_implemented=%u' src/seal_local_capability_registry_schema.c
require_contains 'capability_grants_authority=%u' src/seal_local_capability_registry_schema.c
require_contains 'entry-would-grant-authority' src/seal_local_capability_registry_schema.c
require_contains 'entry-would-perform-effect' src/seal_local_capability_registry_schema.c
require_contains 'non-report-only-entry' src/seal_local_capability_registry_schema.c
require_contains 'registry-schema-is-descriptive-only' tests/seal_local_capability_registry_schema_invariants.c
require_contains 'seal local capability registry schema invariants: ok' tests/seal_local_capability_registry_schema_invariants.c
require_contains 'registry_schema_profile=latticra-seal-local-capability-registry-schema/0.1' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'registry_loader_implemented=0' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'registry_file_loading_supported=0' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'registry_network_loading_supported=0' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'capability_id=seal.local.registry.schema' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'capability_grants_authority=0' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'capability_executes_tool=0' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'capability_reads_host=0' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'capability_writes_host=0' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'capability_uses_network=0' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'scripts/test-latticra-seal-local-capability-registry-schema.sh' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION_PLAN.md' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.' docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md
require_contains 'latticra_seal_local_capability_registry_schema_implementation_present=1' README.md
require_contains 'seal_local_capability_registry_schema_implementation_present=1' README.md
require_contains 'docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md' README.md
require_contains 'Latest Seal local capability registry schema implementation note: 2026-05-26 CDT' STATUS.md
require_contains 'Latest Seal local capability registry schema implementation note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_IMPLEMENTATION.md' docs/status/README.md

cc $CFLAGS \
  -Iinclude \
  src/seal_local_capability_registry_schema.c \
  tests/seal_local_capability_registry_schema_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra seal local capability registry schema: ok\n'

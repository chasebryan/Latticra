#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal foundation: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal foundation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/LATTICRA_SEAL_CONTRACT.md
require_file docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
require_file docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md

require_contains 'Status: Latticra Seal contract' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'This document does not implement cryptographic enforcement.' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'No contract without identity.' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'No authority without a capability.' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'No effect without a signed gate.' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'No promotion without verifiable evidence.' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'artifact measurement implemented' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'capability enforcement implemented' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'Latticra Seal does not invent cryptographic primitives.' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'artifact hashing allowed: not until exact measurement plan and tests exist' docs/LATTICRA_SEAL_CONTRACT.md
require_contains 'The first implementation target is report-only.' docs/LATTICRA_SEAL_CONTRACT.md

require_contains 'Status: Latticra Seal implementation planning contract' docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
require_contains 'This plan is intentionally narrow.' docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
require_contains 'artifact hashing' docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
require_contains 'signature generation' docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
require_contains 'encryption' docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
require_contains 'capability enforcement' docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
require_contains 'runtime_authority_granted=0' docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
require_contains 'Artifact measurement must not be added directly to the first report implementation.' docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md

require_contains 'Status: Latticra Seal foundation status record' docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md
require_contains 'seal_report_implementation_present=0' docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md
require_contains 'artifact_measurement_supported=0' docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md
require_contains 'signature_supported=0' docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md
require_contains 'capability_enforcement_supported=0' docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md
require_contains 'sealed_objects_supported=0' docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md
require_contains 'runtime_authority_granted=0' docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md
require_contains 'new_runtime_behavior=0' docs/status/LATTICRA_SEAL_FOUNDATION_STATUS.md

printf 'latticra seal foundation: ok\n'

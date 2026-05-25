#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal status rollup status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal status rollup status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_STATUS_ROLLUP_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_STATUS_ROLLUP_CONTRACT.md
require_file docs/LATTICRA_SEAL_STATUS_ROLLUP_IMPLEMENTATION.md
require_file include/latticra/seal_status_rollup.h
require_file src/seal_status_rollup.c
require_file tests/seal_status_rollup_invariants.c
require_file scripts/test-latticra-seal-status-rollup-contract.sh
require_file scripts/test-latticra-seal-status-rollup.sh
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_IMPLEMENTATION.md
require_file docs/status/SEAL_RUNTIME_HANDOFF_STATUS.md
require_file include/latticra/seal_runtime_handoff.h
require_file src/seal_runtime_handoff.c
require_file tests/seal_runtime_handoff_invariants.c
require_file scripts/test-latticra-seal-runtime-handoff-contract.sh
require_file scripts/test-latticra-seal-runtime-handoff.sh
require_file scripts/test-latticra-seal-runtime-handoff-status.sh
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md
require_file docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md
require_file scripts/test-latticra-seal-agentic-automation-security-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md

require_contains 'Status: status record for Latticra Seal status rollup metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_status_rollup_contract_present=1' "$status_file"
require_contains 'seal_status_rollup_implementation_present=1' "$status_file"
require_contains 'seal_status_rollup_header_present=1' "$status_file"
require_contains 'seal_status_rollup_source_present=1' "$status_file"
require_contains 'seal_status_rollup_invariant_test_present=1' "$status_file"
require_contains 'seal_status_rollup_runner_present=1' "$status_file"
require_contains 'seal_status_rollup_metadata_present=1' "$status_file"
require_contains 'seal_status_rollup_status_present=1' "$status_file"
require_contains 'seal_runtime_handoff_contract_present=1' "$status_file"
require_contains 'seal_runtime_handoff_implementation_present=1' "$status_file"
require_contains 'seal_runtime_handoff_status_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_contract_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_implementation_present=1' "$status_file"
require_contains 'seal_agentic_automation_security_status_present=1' "$status_file"
require_contains 'rollup_profile=latticra-seal-status-rollup/0.1' "$status_file"
require_contains 'report_present=1' "$status_file"
require_contains 'measurement_present=1' "$status_file"
require_contains 'manifest_present=1' "$status_file"
require_contains 'signature_policy_present=1' "$status_file"
require_contains 'signature_metadata_present=1' "$status_file"
require_contains 'verification_policy_present=1' "$status_file"
require_contains 'verification_receipt_present=1' "$status_file"
require_contains 'capability_gate_present=1' "$status_file"
require_contains 'effect_decision_present=1' "$status_file"
require_contains 'runtime_handoff_present=1' "$status_file"
require_contains 'cryptographic_verification_supported=0' "$status_file"
require_contains 'verified=0' "$status_file"
require_contains 'capability_gate_allowed=0' "$status_file"
require_contains 'effect_allowed=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'handoff_active=0' "$status_file"
require_contains 'runtime_boundary_state=disabled' "$status_file"
require_contains 'runtime_effect_performed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'capability_enforcement_performed=0' "$status_file"
require_contains 'cryptographic_verification_performed=0' "$status_file"
require_contains 'verification_performed=0' "$status_file"
require_contains 'public_key_material_handling=0' "$status_file"
require_contains 'key_material_loaded=0' "$status_file"
require_contains 'private_key_handling=0' "$status_file"
require_contains 'key_generation_performed=0' "$status_file"
require_contains 'hardware_key_used=0' "$status_file"
require_contains 'trust_store_loaded=0' "$status_file"
require_contains 'network_lookup_allowed=0' "$status_file"
require_contains 'revocation_lookup_allowed=0' "$status_file"
require_contains 'revocation_lookup_performed=0' "$status_file"
require_contains 'signature_performed=0' "$status_file"
require_contains 'signer_invoked=0' "$status_file"
require_contains 'mode=metadata-only' "$status_file"
require_contains 'rollup_state=metadata-only' "$status_file"
require_contains 'status=status-rollup-metadata' "$status_file"
require_contains 'error=ok' "$status_file"
require_contains 'seal status rollup contract: ok' "$status_file"
require_contains 'seal status rollup invariants: ok' "$status_file"
require_contains 'seal status rollup status: ok' "$status_file"
require_contains 'seal runtime handoff status: ok' "$status_file"
require_contains 'seal agentic automation security status: ok' "$status_file"
require_contains 'Seal agentic automation security public README/status/foundation entry-point refresh' "$status_file"

require_contains 'SEAL_STATUS_ROLLUP_STATUS.md' README.md
require_contains 'LATTICRA_SEAL_STATUS_ROLLUP_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_STATUS_ROLLUP_IMPLEMENTATION.md' README.md
require_contains 'latticra_seal_status_rollup_metadata_present=1' README.md
require_contains 'latticra_seal_status_rollup_status_present=1' README.md
require_contains 'seal_status_rollup_metadata_present=1' README.md
require_contains 'seal_status_rollup_status_present=1' README.md
require_contains 'Seal status rollup status/public-entry alignment' STATUS.md
require_contains 'seal_status_rollup_metadata_present=1' STATUS.md
require_contains 'seal_status_rollup_status_present=1' STATUS.md
require_contains 'SEAL_STATUS_ROLLUP_STATUS.md' docs/status/README.md
require_contains 'seal_status_rollup_metadata_present=1' docs/status/README.md
require_contains 'seal_status_rollup_status_present=1' docs/status/README.md
require_contains 'Latticra Seal status rollup status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_STATUS_ROLLUP_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_STATUS_ROLLUP_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal status rollup status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal agentic automation security public README/status/foundation entry-point refresh' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal status rollup status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal agentic automation security public README/status/foundation entry-point refresh' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_STATUS_ROLLUP_STATUS.md' docs/project_notes/README.md

printf 'seal status rollup status: ok\n'

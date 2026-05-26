#!/usr/bin/env sh
set -eu

doc="docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'runtime boundary policy expansion after threat model: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime boundary policy expansion after threat model: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
require_file docs/RUNTIME_BOUNDARY_CONTRACT.md
require_file docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md
require_file docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
require_file docs/RUNTIME_BOUNDARY_POLICY_MATRIX_REFINEMENT.md
require_file docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md
require_file docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REFINEMENT.md
require_file docs/RUNTIME_BOUNDARY_DOMAIN_MATRIX_REPORT_INTEGRATION.md
require_file scripts/test-defensive-threat-model-validation-refinement.sh
require_file scripts/test-runtime-boundary.sh
require_file scripts/test-runtime-boundary-policy-matrix-refinement.sh
require_file scripts/test-runtime-boundary-abuse-case-fixtures.sh
require_file scripts/test-runtime-boundary-domain-matrix-refinement.sh
require_file scripts/test-runtime-boundary-domain-matrix-report-integration.sh

require_contains 'Status: runtime boundary policy expansion after threat-model validation' "$doc"
require_contains 'Source: local follow-up slice' "$doc"
require_contains 'runtime boundary source needs fuller policy expansion after threat-model validation' "$doc"
require_contains 'runtime_boundary_policy_expansion_after_threat_model_present=1' "$doc"
require_contains 'runtime_boundary_policy_expansion_after_threat_model_guard_present=1' "$doc"
require_contains 'defensive_threat_model_validation_refinement_present=1' "$doc"
require_contains 'runtime_boundary_contract_present=1' "$doc"
require_contains 'runtime_boundary_implementation_plan_present=1' "$doc"
require_contains 'runtime_boundary_implementation_present=1' "$doc"
require_contains 'runtime_boundary_policy_matrix_present=1' "$doc"
require_contains 'runtime_boundary_domain_matrix_present=1' "$doc"
require_contains 'runtime_boundary_domain_matrix_report_present=1' "$doc"
require_contains 'request_family_policy_map_present=1' "$doc"
require_contains 'effect_policy_map_present=1' "$doc"
require_contains 'authority_prerequisite_map_present=1' "$doc"
require_contains 'future_gate_policy_map_present=1' "$doc"
require_contains 'abuse_case_runtime_policy_map_present=1' "$doc"
require_contains 'evidence_gap_map_present=1' "$doc"
require_contains 'mode=policy-expansion-after-threat-model' "$doc"
require_contains 'implementation_behavior_changed=0' "$doc"
require_contains 'runtime_execution_added=0' "$doc"
require_contains 'effect_execution_added=0' "$doc"
require_contains 'capability_enforcement_added=0' "$doc"
require_contains 'cryptographic_verification_added=0' "$doc"
require_contains 'signing_added=0' "$doc"
require_contains 'host_behavior_changed=0' "$doc"
require_contains 'network_behavior_changed=0' "$doc"
require_contains 'mcp_behavior_changed=0' "$doc"
require_contains 'agent_execution_added=0' "$doc"
require_contains 'model_execution_added=0' "$doc"
require_contains 'tool_execution_added=0' "$doc"
require_contains 'shell_execution_added=0' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'production_protection_claim_allowed=0' "$doc"
require_contains 'runtime_protection_claim_allowed=0' "$doc"
require_contains 'malware_prevention_claim_allowed=0' "$doc"
require_contains 'ransomware_prevention_claim_allowed=0' "$doc"
require_contains 'sandbox_claim_allowed=0' "$doc"
require_contains 'certification_claim_allowed=0' "$doc"
require_contains 'compliance_claim_allowed=0' "$doc"
require_contains 'external_endorsement_claimed=0' "$doc"
require_contains 'completion_estimate_review_required=0' "$doc"
require_contains 'Request-family policy map' "$doc"
require_contains 'Effect policy map' "$doc"
require_contains 'Authority prerequisite map' "$doc"
require_contains 'Future-gate policy map' "$doc"
require_contains 'Abuse-case runtime policy map' "$doc"
require_contains 'Evidence gap map' "$doc"
require_contains 'distinct operator identity, workload or service identity, and host or device integrity context' "$doc"
require_contains 'caller identity known' "$doc"
require_contains 'operator identity known when operator context exists' "$doc"
require_contains 'workload or service identity known when tool, MCP, model, runtime, updater, signer, or installer authority is requested' "$doc"
require_contains 'host or device integrity context known when host, network, update, recovery, boot, or hardware authority is requested' "$doc"
require_contains 'least-privilege scope recorded for the exact requested effect' "$doc"
require_contains 'unknown request is treated as allowed' "$doc"
require_contains 'unknown effect is treated as allowed' "$doc"
require_contains 'future-gated request is treated as executable' "$doc"
require_contains 'operator confirmation overrides policy' "$doc"
require_contains 'future workload or service authority lacks distinct workload identity' "$doc"
require_contains 'future host, network, update, recovery, boot, or hardware authority lacks host or device integrity context' "$doc"
require_contains 'future tool or command path reaches a shell boundary without dedicated command-boundary review' "$doc"
require_contains 'future workload-identity-aware authority contract' "$doc"
require_contains 'docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md' "$doc"
require_contains 'sh scripts/test-runtime-boundary-policy-expansion-after-threat-model.sh' "$doc"

require_contains 'runtime_boundary_policy_expansion_after_threat_model_present=1' README.md
require_contains 'docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md' README.md
require_contains 'Runtime boundary policy expansion after threat-model validation' STATUS.md
require_contains 'runtime_boundary_policy_expansion_after_threat_model_present=1' STATUS.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' STATUS.md
require_contains 'RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md' docs/status/README.md
require_contains 'runtime_boundary_policy_expansion_after_threat_model_present=1' docs/status/README.md
require_contains 'Runtime boundary policy expansion after threat-model validation' docs/status/CURRENT_STATUS.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' docs/status/CURRENT_STATUS.md
require_contains 'RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md' docs/FOUNDATION_INDEX.md
require_contains 'Runtime boundary policy expansion after threat-model validation' docs/FOUNDATION_INDEX.md
require_contains 'runtime_boundary_policy_expansion_after_threat_model_present=1' docs/FOUNDATION_INDEX.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' docs/FOUNDATION_INDEX.md
require_contains 'Runtime boundary policy expansion after threat-model validation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Runtime boundary policy expansion after threat-model validation' docs/project_notes/UPCOMING_WORK.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md' docs/project_notes/README.md

printf 'runtime_boundary_policy_expansion_after_threat_model: ok\n'

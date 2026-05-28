#!/usr/bin/env sh
set -eu

doc="docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md"
status_doc="docs/status/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'zero trust runtime authority baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'zero trust runtime authority baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
require_file docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md
require_file docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md
require_file docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-defensive-threat-model-validation-refinement.sh
require_file scripts/test-runtime-boundary-policy-expansion-after-threat-model.sh
require_file scripts/test-runtime-boundary-abuse-case-fixtures.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: zero-trust runtime authority baseline' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Authoritative Zero-Trust Sources' "$doc"
require_contains 'NSA Zero Trust Implementation Guidelines: Primer, Discovery Phase, Phase One, and Phase Two' "$doc"
require_contains 'CISA Zero Trust Maturity Model Version 2.0' "$doc"
require_contains 'NIST SP 800-207 Zero Trust Architecture' "$doc"
require_contains 'NIST SP 800-207A' "$doc"
require_contains 'NSA MCP security-design guidance' "$doc"
require_contains 'careful-adoption guidance' "$doc"
require_contains 'NIST'\''s May 18, 2026 summary analysis of AI-agent security RFI responses' "$doc"
require_contains 'identity and authority of software agents' "$doc"
require_contains 'Pillar Mapping' "$doc"
require_contains 'Required Runtime Authority Gate' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4393480/nsa-releases-phase-one-and-phase-two-of-the-zero-trust-implementation-guidelines/' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4378980/nsa-releases-first-in-series-of-zero-trust-implementation-guidelines/' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4496698/nsa-releases-security-design-considerations-for-ai-driven-automation-leveraging/' "$doc"
require_contains 'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4475134/nsa-joins-the-asds-acsc-and-others-to-release-guidance-on-agentic-artificial-in/' "$doc"
require_contains 'https://www.cisa.gov/resources-tools/resources/zero-trust-maturity-model' "$doc"
require_contains 'https://www.nist.gov/publications/zero-trust-architecture-0' "$doc"
require_contains 'https://csrc.nist.gov/pubs/sp/800/207/a/final' "$doc"

for field in \
  'zero_trust_runtime_authority_baseline_present=1' \
  'zero_trust_runtime_authority_guard_present=1' \
  'defensive_threat_model_validation_refinement_present=1' \
  'runtime_boundary_policy_expansion_after_threat_model_present=1' \
  'zero_trust_runtime_boundary_required=1' \
  'per_request_authorization_required=1' \
  'least_privilege_effect_scope_required=1' \
  'resource_identity_required=1' \
  'caller_identity_required=1' \
  'asset_inventory_required_before_authority=1' \
  'policy_decision_visibility_required=1' \
  'denial_reason_visibility_required=1' \
  'audit_record_required_before_authority=1' \
  'operator_confirmation_metadata_only_required=1' \
  'unknown_request_denial_required=1' \
  'unknown_effect_denial_required=1' \
  'future_gate_denial_required=1' \
  'runtime_execution_added=0' \
  'tool_execution_added=0' \
  'host_behavior_changed=0' \
  'network_behavior_changed=0' \
  'mcp_behavior_changed=0' \
  'runtime_authority_granted=0' \
  'production_protection_claim_allowed=0' \
  'zero_trust_certification_claim_allowed=0' \
  'external_endorsement_claimed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'zero_trust_runtime_authority_status_present=1' "$status_doc"

for gate in \
  'request_kind_known=1' \
  'requested_effect_known=1' \
  'caller_identity_known=1' \
  'operator_or_automation_context_known=1' \
  'software_agent_identity_known=1' \
  'resource_identity_known=1' \
  'resource_sensitivity_classified=1' \
  'execution_environment_known=1' \
  'tool_or_mcp_boundary_known=1' \
  'context_sharing_scope_known=1' \
  'mode_matches_request_family=1' \
  'authority_prerequisites_satisfied=1' \
  'least_privilege_scope_recorded=1' \
  'policy_decision_reported=1' \
  'denial_reason_reported=1' \
  'audit_record_emitted=1' \
  'evidence_level_recorded=1' \
  'operator_confirmation_recorded_as_metadata_only=1' \
  'operator_confirmation_non_override_test_present=1' \
  'unknown_request_denial_test_present=1' \
  'unknown_effect_denial_test_present=1' \
  'future_gate_denial_test_present=1' \
  'blocked_effect_denial_test_present=1' \
  'rollback_or_failure_behavior_defined_for_mutation=1' \
  'non_claim_review_completed=1'
do
  require_contains "$gate" "$doc"
done

for closed in \
  'runtime_execution_allowed=0' \
  'tool_execution_allowed=0' \
  'host_read_allowed=0' \
  'host_write_allowed=0' \
  'network_open_allowed=0' \
  'mcp_invocation_allowed=0' \
  'model_execution_allowed=0' \
  'signing_authority_allowed=0' \
  'update_authority_allowed=0' \
  'recovery_authority_allowed=0' \
  'boot_authority_allowed=0' \
  'hardware_authority_allowed=0' \
  'operator_confirmation_override_allowed=0'
do
  require_contains "$closed" "$doc"
done

require_contains 'runtime boundary source needs fuller policy expansion after threat-model validation' docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
require_contains 'runtime_boundary_policy_expansion_after_threat_model_present=1' docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md
require_contains 'operator confirmation cannot override policy' docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md
require_contains 'operator_confirmation_non_override_fixture_present=1' docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md
require_contains 'docs/ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md' SECURITY.md
require_contains 'zero_trust_runtime_authority_baseline_present=1' README.md
require_contains 'zero_trust_runtime_authority_baseline_present=1' STATUS.md
require_contains 'ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE_STATUS.md' docs/status/README.md
require_contains 'zero_trust_runtime_authority_baseline_present=1' docs/status/README.md
require_contains 'Latest zero-trust runtime authority baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md' docs/FOUNDATION_INDEX.md
require_contains 'Zero-trust runtime authority baseline' docs/security.html
require_contains 'ZERO_TRUST_RUNTIME_AUTHORITY_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-zero-trust-runtime-authority-baseline.sh' Makefile
require_contains 'zero-trust-runtime-authority-baseline:' Makefile
require_contains 'sh ./scripts/test-zero-trust-runtime-authority-baseline.sh' scripts/test-quality-safety-guards.sh
require_contains 'test-zero-trust-runtime-authority-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'zero_trust_runtime_authority_baseline: ok\n'

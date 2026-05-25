#!/usr/bin/env sh
set -eu

doc="docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md"
test_file="tests/runtime_boundary_abuse_case_fixtures.c"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'runtime boundary abuse-case fixtures: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime boundary abuse-case fixtures: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$test_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
require_file docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md
require_file include/latticra/runtime_boundary.h
require_file include/latticra/runtime_boundary_domain_matrix.h
require_file src/runtime_boundary.c
require_file src/runtime_boundary_domain_matrix_eval.c
require_file scripts/test-runtime-boundary-policy-expansion-after-threat-model.sh
require_file scripts/test-runtime-boundary.sh
require_file .github/workflows/runtime-boundary-abuse-case-fixtures.yml

require_contains 'Status: runtime boundary abuse-case fixture expansion after policy expansion' "$doc"
require_contains 'abuse-case mapping needs broader fixture coverage' "$doc"
require_contains 'runtime_boundary_abuse_case_fixture_expansion_present=1' "$doc"
require_contains 'runtime_boundary_abuse_case_fixture_guard_present=1' "$doc"
require_contains 'runtime_boundary_abuse_case_c_fixtures_present=1' "$doc"
require_contains 'runtime_boundary_abuse_case_fixture_count=8' "$doc"
require_contains 'runtime_boundary_policy_expansion_after_threat_model_present=1' "$doc"
require_contains 'unknown_request_abuse_fixture_present=1' "$doc"
require_contains 'unknown_effect_abuse_fixture_present=1' "$doc"
require_contains 'future_gated_execution_abuse_fixture_present=1' "$doc"
require_contains 'operator_confirmation_non_override_fixture_present=1' "$doc"
require_contains 'denial_reason_report_fixture_present=1' "$doc"
require_contains 'authority_failure_abuse_fixture_present=1' "$doc"
require_contains 'invalid_lir_prerequisite_fixture_present=1' "$doc"
require_contains 'blocked_effect_abuse_fixture_present=1' "$doc"
require_contains 'report_reason_assertions_present=1' "$doc"
require_contains 'policy_matrix_assertions_present=1' "$doc"
require_contains 'domain_matrix_assertions_present=1' "$doc"
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
require_contains 'completion_estimate_review_required=0' "$doc"
require_contains 'unknown-request-is-not-allowed' "$doc"
require_contains 'unknown-effect-is-not-allowed' "$doc"
require_contains 'future-gated-execution-is-not-executable' "$doc"
require_contains 'operator-confirmation-cannot-override-policy' "$doc"
require_contains 'denial-reason-stays-rendered' "$doc"
require_contains 'authority-failure-is-not-allowed' "$doc"
require_contains 'invalid-lir-prerequisite-stays-denied' "$doc"
require_contains 'blocked-effect-stays-blocked' "$doc"
require_contains 'sh scripts/test-runtime-boundary-abuse-case-fixtures.sh' "$doc"

require_contains 'runtime_boundary_abuse_case_fixture_table_covers_current_policy_map' "$test_file"
require_contains 'runtime_boundary_abuse_case_reports_include_denial_reasons' "$test_file"
require_contains 'runtime_boundary_abuse_case_domain_matrix_preserves_no_authority' "$test_file"
require_contains 'runtime_boundary_abuse_case_unknown_request_is_not_allowed' "$test_file"
require_contains 'runtime_boundary_abuse_case_unknown_effect_is_not_allowed' "$test_file"
require_contains 'runtime_boundary_abuse_case_future_gated_request_is_not_executable' "$test_file"
require_contains 'runtime_boundary_abuse_case_operator_confirmation_does_not_override' "$test_file"
require_contains 'runtime_boundary_abuse_case_render_report_preserves_lir_failure_reason' "$test_file"
require_contains 'runtime_boundary_abuse_case_failed_authority_metadata_is_not_allowed' "$test_file"
require_contains 'runtime_boundary_abuse_case_invalid_lir_does_not_reach_allowed_validation' "$test_file"
require_contains 'runtime_boundary_abuse_case_blocked_effect_stays_blocked' "$test_file"
require_contains 'runtime_boundary_abuse_case_fixtures: ok' "$test_file"

require_contains 'runtime_boundary_abuse_case_fixture_expansion_present=1' README.md
require_contains 'docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md' README.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' STATUS.md
require_contains 'runtime_boundary_abuse_case_fixture_expansion_present=1' STATUS.md
require_contains 'Completion estimate review only if capability posture changes' STATUS.md
require_contains 'RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md' docs/status/README.md
require_contains 'runtime_boundary_abuse_case_fixture_expansion_present=1' docs/status/README.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' docs/status/CURRENT_STATUS.md
require_contains 'runtime_boundary_abuse_case_fixture_expansion_present=1' docs/status/CURRENT_STATUS.md
require_contains 'Completion estimate review only if capability posture changes' docs/status/CURRENT_STATUS.md
require_contains 'RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md' docs/FOUNDATION_INDEX.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' docs/FOUNDATION_INDEX.md
require_contains 'runtime_boundary_abuse_case_fixture_expansion_present=1' docs/FOUNDATION_INDEX.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Completion estimate review only if capability posture changes' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' docs/project_notes/UPCOMING_WORK.md
require_contains 'Completion estimate review only if capability posture changes' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md' docs/project_notes/README.md
require_contains 'sh scripts/test-runtime-boundary-abuse-case-fixtures.sh' .github/workflows/runtime-boundary-abuse-case-fixtures.yml

sh scripts/test-runtime-boundary.sh

printf 'runtime_boundary_abuse_case_fixtures_guard: ok\n'

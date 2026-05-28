#!/usr/bin/env sh
set -eu

doc="docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'completion estimate review after runtime boundary abuse-case fixtures: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'completion estimate review after runtime boundary abuse-case fixtures: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
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
require_file docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md
require_file scripts/test-runtime-boundary-abuse-case-fixtures.sh
require_file .github/workflows/runtime-boundary-abuse-case-completion-estimate-review.yml

require_contains 'Status: planning-estimate review' "$doc"
require_contains 'Runtime boundary abuse-case fixture expansion after policy expansion' "$doc"
require_contains 'completion_estimate_after_runtime_boundary_abuse_case_fixtures_present=1' "$doc"
require_contains 'runtime_boundary_abuse_case_fixture_expansion_present=1' "$doc"
require_contains 'runtime_boundary_abuse_case_fixture_count=8' "$doc"
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
require_contains 'security_hardening_changed=0' "$doc"
require_contains 'public_readiness_changed=0' "$doc"
require_contains 'production_readiness_claimed=0' "$doc"
require_contains 'estimate_adjustment_required=0' "$doc"
require_contains 'completion_estimate_review_required=0' "$doc"
require_contains 'completion_estimate_changed=0' "$doc"
require_contains 'Overall Latticra system: 39%' "$doc"
require_contains 'Latticra Seal / local evidence layer: 34%' "$doc"
require_contains 'Runtime / operating-system-universe direction: 19%' "$doc"
require_contains 'Security-hardening implementation: 7%' "$doc"
require_contains 'Public product readiness: 8%' "$doc"
require_contains 'No estimate is raised' "$doc"
require_contains 'sh scripts/test-completion-estimate-review-after-runtime-boundary-abuse-case-fixtures.sh' "$doc"

require_contains 'Latest completion estimate review after runtime-boundary abuse-case fixtures note: 2026-05-25 CDT' STATUS.md
require_contains 'Completion estimate review after runtime-boundary abuse-case fixtures' STATUS.md
require_contains 'completion_estimate_after_runtime_boundary_abuse_case_fixtures_present=1' STATUS.md
require_contains 'estimate_adjustment_required=0' STATUS.md
require_contains 'Continue small guarded report/status alignment only when drift appears' STATUS.md
require_contains '| Overall Latticra system | 48% |' STATUS.md
require_contains '| Latticra Seal / local evidence layer | 45% |' STATUS.md
require_contains '| Security-hardening implementation | 14% |' STATUS.md
require_contains '| Public product readiness | 13% |' STATUS.md

require_contains 'COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md' docs/status/README.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_28.md' docs/status/README.md
require_contains 'completion_estimate_after_runtime_boundary_abuse_case_fixtures_present=1' docs/status/README.md
require_contains 'Completion estimate review after runtime-boundary abuse-case fixtures' docs/status/CURRENT_STATUS.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_28.md' docs/status/CURRENT_STATUS.md
require_contains 'completion_estimate_after_runtime_boundary_abuse_case_fixtures_present=1' docs/status/CURRENT_STATUS.md
require_contains 'estimate_adjustment_required=0' docs/status/CURRENT_STATUS.md
require_contains 'Continue small guarded report/status alignment only when drift appears' docs/status/CURRENT_STATUS.md
require_contains '| Overall Latticra system | 48% |' docs/status/CURRENT_STATUS.md
require_contains '| Public product readiness | 13% |' docs/status/CURRENT_STATUS.md

require_contains 'COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md' docs/FOUNDATION_INDEX.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_28.md' docs/FOUNDATION_INDEX.md
require_contains 'Completion estimate review after runtime-boundary abuse-case fixtures' docs/FOUNDATION_INDEX.md
require_contains 'completion_estimate_after_runtime_boundary_abuse_case_fixtures_present=1' docs/FOUNDATION_INDEX.md
require_contains 'Completion estimate review after runtime-boundary abuse-case fixtures' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Continue small guarded report/status alignment only when drift appears' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Completion estimate review after runtime-boundary abuse-case fixtures' docs/project_notes/UPCOMING_WORK.md
require_contains 'Continue small guarded report/status alignment only when drift appears' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md' docs/project_notes/README.md

require_contains 'Current public estimate | Roughly 48% overall system planning estimate' README.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_28.md' README.md
require_contains '| Product readiness | Early; no production platform claimed |' README.md
require_contains 'sh scripts/test-completion-estimate-review-after-runtime-boundary-abuse-case-fixtures.sh' .github/workflows/runtime-boundary-abuse-case-completion-estimate-review.yml

sh scripts/test-runtime-boundary-abuse-case-fixtures.sh

printf 'completion_estimate_review_after_runtime_boundary_abuse_case_fixtures: ok\n'

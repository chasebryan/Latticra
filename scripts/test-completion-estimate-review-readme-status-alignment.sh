#!/usr/bin/env sh
set -eu

doc="docs/status/COMPLETION_ESTIMATE_REVIEW_README_STATUS_ALIGNMENT.md"
review="docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'completion estimate review README/status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'completion estimate review README/status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$review"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file scripts/test-completion-estimate-review-after-runtime-boundary-abuse-case-fixtures.sh
require_file .github/workflows/completion-estimate-review-readme-status-alignment.yml

require_contains 'Status: README/status alignment' "$doc"
require_contains 'completion_estimate_review_readme_status_alignment_present=1' "$doc"
require_contains 'completion_estimate_after_runtime_boundary_abuse_case_fixtures_present=1' "$doc"
require_contains 'readme_links_latest_completion_estimate_review=1' "$doc"
require_contains 'status_index_links_alignment_record=1' "$doc"
require_contains 'foundation_index_links_alignment_record=1' "$doc"
require_contains 'project_notes_link_alignment_record=1' "$doc"
require_contains 'implementation_behavior_changed=0' "$doc"
require_contains 'runtime_execution_added=0' "$doc"
require_contains 'effect_execution_added=0' "$doc"
require_contains 'capability_enforcement_added=0' "$doc"
require_contains 'security_hardening_changed=0' "$doc"
require_contains 'public_readiness_changed=0' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'estimate_adjustment_required=0' "$doc"
require_contains 'completion_estimate_changed=0' "$doc"
require_contains 'Overall Latticra system: 39%' "$doc"
require_contains 'Latticra Seal / local evidence layer: 34%' "$doc"
require_contains 'Security-hardening implementation: 7%' "$doc"
require_contains 'Public product readiness: 8%' "$doc"
require_contains 'sh scripts/test-completion-estimate-review-readme-status-alignment.sh' "$doc"
require_contains 'small guarded report/status alignment only when drift appears' "$doc"

require_contains '[`docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md`](docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md)' README.md
require_contains '| Current public estimate | Roughly 45% overall system planning estimate |' README.md
require_contains '| Foundation documents and contracts | Mature relative to implementation; around 94% planning estimate |' README.md
require_contains '| Public documentation posture | Strong but still evolving; around 91% planning estimate |' README.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md' README.md
require_contains '| Latticra Seal | Report-only runtime gate path' README.md
require_contains '| Product readiness | Early; no production platform claimed |' README.md
require_contains 'Planning estimates are not release promises, product-readiness metrics, or security guarantees.' README.md

require_contains 'Latest completion estimate review README/status alignment note: 2026-05-25 CDT' STATUS.md
require_contains 'Completion estimate review README/status alignment' STATUS.md
require_contains 'completion_estimate_review_readme_status_alignment_present=1' STATUS.md
require_contains 'completion_estimate_after_runtime_boundary_abuse_case_fixtures_present=1' STATUS.md
require_contains 'estimate_adjustment_required=0' STATUS.md
require_contains 'implementation_behavior_changed=0' STATUS.md
require_contains 'runtime_execution_added=0' STATUS.md
require_contains 'effect_execution_added=0' STATUS.md
require_contains 'capability_enforcement_added=0' STATUS.md
require_contains 'security_hardening_changed=0' STATUS.md
require_contains 'public_readiness_changed=0' STATUS.md
require_contains 'runtime_authority_granted=0' STATUS.md
require_contains 'Continue small guarded report/status alignment only when drift appears' STATUS.md
require_contains '| Overall Latticra system | 45% |' STATUS.md
require_contains '| Latticra Seal / local evidence layer | 39% |' STATUS.md
require_contains '| Security-hardening implementation | 10% |' STATUS.md
require_contains '| Public product readiness | 10% |' STATUS.md

require_contains 'COMPLETION_ESTIMATE_REVIEW_README_STATUS_ALIGNMENT.md' docs/status/README.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md' docs/status/README.md
require_contains 'completion_estimate_review_readme_status_alignment_present=1' docs/status/README.md
require_contains 'COMPLETION_ESTIMATE_REVIEW_README_STATUS_ALIGNMENT.md' docs/status/CURRENT_STATUS.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md' docs/status/CURRENT_STATUS.md
require_contains 'Completion estimate review README/status alignment' docs/status/CURRENT_STATUS.md
require_contains 'completion_estimate_review_readme_status_alignment_present=1' docs/status/CURRENT_STATUS.md
require_contains 'estimate_adjustment_required=0' docs/status/CURRENT_STATUS.md
require_contains 'Continue small guarded report/status alignment only when drift appears' docs/status/CURRENT_STATUS.md
require_contains '| Overall Latticra system | 45% |' docs/status/CURRENT_STATUS.md
require_contains '| Public product readiness | 10% |' docs/status/CURRENT_STATUS.md

require_contains 'COMPLETION_ESTIMATE_REVIEW_README_STATUS_ALIGNMENT.md' docs/FOUNDATION_INDEX.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md' docs/FOUNDATION_INDEX.md
require_contains 'Completion estimate review README/status alignment' docs/FOUNDATION_INDEX.md
require_contains 'completion_estimate_review_readme_status_alignment_present=1' docs/FOUNDATION_INDEX.md
require_contains 'completion_estimate_after_runtime_boundary_abuse_case_fixtures_present=1' docs/FOUNDATION_INDEX.md

require_contains 'Latest completion estimate review README/status alignment note: 2026-05-25 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Completion estimate review README/status alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Continue small guarded report/status alignment only when drift appears' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latest completion estimate review README/status alignment note: 2026-05-25 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'Completion estimate review README/status alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'completion_estimate_review_readme_status_alignment_present=1' docs/project_notes/UPCOMING_WORK.md
require_contains 'Continue small guarded report/status alignment only when drift appears' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/COMPLETION_ESTIMATE_REVIEW_README_STATUS_ALIGNMENT.md' docs/project_notes/README.md

require_contains 'sh scripts/test-completion-estimate-review-readme-status-alignment.sh' .github/workflows/completion-estimate-review-readme-status-alignment.yml

sh scripts/test-completion-estimate-review-after-runtime-boundary-abuse-case-fixtures.sh

printf 'completion_estimate_review_readme_status_alignment: ok\n'

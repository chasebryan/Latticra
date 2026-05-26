#!/usr/bin/env sh
set -eu

record="docs/status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'current estimate table source alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'current estimate table source alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$record"
require_file README.md
require_file STATUS.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/status/README.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md
require_file docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md
require_file docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md
require_file scripts/test-completion-estimate-review-readme-status-alignment.sh
require_file .github/workflows/current-estimate-table-source-alignment.yml

require_contains 'Status: current estimate table source alignment' "$record"
require_contains 'current_estimate_table_source_alignment_present=1' "$record"
require_contains 'readme_estimate_source_row_present=1' "$record"
require_contains 'readme_current_public_estimate_table_present=1' "$record"
require_contains 'root_status_current_estimate_table_present=1' "$record"
require_contains 'current_status_current_estimate_table_present=1' "$record"
require_contains 'status_index_links_current_estimate_table_source_alignment=1' "$record"
require_contains 'foundation_index_links_current_estimate_table_source_alignment=1' "$record"
require_contains 'project_notes_link_current_estimate_table_source_alignment=1' "$record"
require_contains 'latest_estimate_refresh_record_linked=1' "$record"
require_contains 'latest_runtime_boundary_hold_review_linked=1' "$record"
require_contains 'latest_mathematical_rebase_record_linked=1' "$record"
require_contains 'source_alignment_estimate_changed=0' "$record"
require_contains 'mathematical_rebase_estimate_changed=1' "$record"
require_contains 'estimate_adjustment_required=0' "$record"
require_contains 'implementation_behavior_changed=0' "$record"
require_contains 'runtime_execution_added=0' "$record"
require_contains 'effect_execution_added=0' "$record"
require_contains 'capability_enforcement_added=0' "$record"
require_contains 'security_hardening_changed=0' "$record"
require_contains 'public_readiness_changed=0' "$record"
require_contains 'runtime_authority_granted=0' "$record"
require_contains 'Overall Latticra system: 45%' "$record"
require_contains 'Nadia offline AI foundation: 74%' "$record"
require_contains 'Public product readiness: 10%' "$record"
require_contains 'sh scripts/test-current-estimate-table-source-alignment.sh' "$record"
require_contains 'weighted_sum=4454' docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md
require_contains 'overall_estimate=round(4454 / 100)=45' docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md
require_contains '| Nadia offline AI foundation | 70% | 74% |' docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md
require_contains '| Runtime / operating-system-universe direction | 19% | 25% |' docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md

require_contains '| Estimate source | Current public estimate table below, mirrored from `STATUS.md` and `docs/status/CURRENT_STATUS.md` |' README.md
require_contains 'Current public estimate table, as summarized by [`STATUS.md`](STATUS.md) and [`docs/status/CURRENT_STATUS.md`](docs/status/CURRENT_STATUS.md):' README.md
require_contains 'The current estimate table source alignment is [`docs/status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md`](docs/status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md).' README.md
require_contains 'The latest mathematical estimate rebase is [`docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md`](docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md).' README.md
require_contains 'The latest estimate refresh record is [`docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md`](docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md).' README.md
require_contains 'The latest estimate hold review is [`docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md`](docs/status/COMPLETION_ESTIMATE_REVIEW_AFTER_RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES.md)' README.md

for file in README.md STATUS.md docs/status/CURRENT_STATUS.md; do
  require_contains '| Overall Latticra system | 45% |' "$file"
  require_contains '| Latticra Seal / local evidence layer | 39% |' "$file"
  require_contains '| Latticra Panel / local control surface | 31% |' "$file"
  require_contains '| Nadia offline AI foundation | 74% |' "$file"
  require_contains '| L-UI parser / AST / string foundation | 87% |' "$file"
  require_contains '| Foundation documents and contracts | 94% |' "$file"
  require_contains '| Public documentation posture | 91% |' "$file"
  require_contains '| Strategy/status/funding framework | 63% |' "$file"
  require_contains '| Lat / Latticra Programming Language | 27% |' "$file"
  require_contains '| LIR / Intermediate Representation | 24% |' "$file"
  require_contains '| C/C++ foundation direction | 22% |' "$file"
  require_contains '| Constrained C++ authority layer | 5% |' "$file"
  require_contains '| Nucleus real task execution | 12% |' "$file"
  require_contains '| Runtime / operating-system-universe direction | 25% |' "$file"
  require_contains '| Security-hardening implementation | 9% |' "$file"
  require_contains '| Public product readiness | 10% |' "$file"
done

require_contains 'Latest current estimate table source alignment note: 2026-05-26 CDT' STATUS.md
require_contains 'Latest current estimate mathematical rebase note: 2026-05-26 CDT' STATUS.md
require_contains 'Current estimate table source alignment' STATUS.md
require_contains 'Current estimate mathematical rebase' STATUS.md
require_contains 'current_estimate_table_source_alignment_present=1' STATUS.md
require_contains 'current_estimate_mathematical_rebase_present=1' STATUS.md
require_contains 'source_alignment_estimate_changed=0' STATUS.md
require_contains 'mathematical_rebase_estimate_changed=1' STATUS.md
require_contains 'estimate_adjustment_required=0' STATUS.md
require_contains 'runtime_authority_granted=0' STATUS.md

require_contains 'CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md' docs/status/README.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md' docs/status/README.md
require_contains 'current_estimate_table_source_alignment_present=1' docs/status/README.md
require_contains 'current_estimate_mathematical_rebase_present=1' docs/status/README.md
require_contains 'CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md' docs/status/CURRENT_STATUS.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md' docs/status/CURRENT_STATUS.md
require_contains 'Current estimate table source alignment' docs/status/CURRENT_STATUS.md
require_contains 'current estimate mathematical rebase' docs/status/CURRENT_STATUS.md
require_contains 'current_estimate_table_source_alignment_present=1' docs/status/CURRENT_STATUS.md
require_contains 'current_estimate_mathematical_rebase_present=1' docs/status/CURRENT_STATUS.md
require_contains 'source_alignment_estimate_changed=0' docs/status/CURRENT_STATUS.md
require_contains 'mathematical_rebase_estimate_changed=1' docs/status/CURRENT_STATUS.md
require_contains 'estimate_adjustment_required=0' docs/status/CURRENT_STATUS.md
require_contains 'Continue small guarded report/status alignment only when drift appears' docs/status/CURRENT_STATUS.md

require_contains 'CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md' docs/FOUNDATION_INDEX.md
require_contains 'CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md' docs/FOUNDATION_INDEX.md
require_contains 'Current estimate table source alignment' docs/FOUNDATION_INDEX.md
require_contains 'Current estimate mathematical rebase' docs/FOUNDATION_INDEX.md
require_contains 'current_estimate_table_source_alignment_present=1' docs/FOUNDATION_INDEX.md
require_contains 'current_estimate_mathematical_rebase_present=1' docs/FOUNDATION_INDEX.md

require_contains 'Latest current estimate table source alignment note: 2026-05-26 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latest current estimate mathematical rebase note: 2026-05-26 CDT' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Current estimate table source alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Current estimate mathematical rebase' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latest current estimate table source alignment note: 2026-05-26 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'Latest current estimate mathematical rebase note: 2026-05-26 CDT' docs/project_notes/UPCOMING_WORK.md
require_contains 'Current estimate table source alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'Current estimate mathematical rebase' docs/project_notes/UPCOMING_WORK.md
require_contains 'current_estimate_table_source_alignment_present=1' docs/project_notes/UPCOMING_WORK.md
require_contains 'current_estimate_mathematical_rebase_present=1' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/CURRENT_ESTIMATE_TABLE_SOURCE_ALIGNMENT.md' docs/project_notes/README.md
require_contains 'docs/status/CURRENT_ESTIMATE_MATHEMATICAL_REBASE_2026_05_26.md' docs/project_notes/README.md

require_contains 'sh scripts/test-current-estimate-table-source-alignment.sh' .github/workflows/current-estimate-table-source-alignment.yml

sh scripts/test-completion-estimate-review-readme-status-alignment.sh

printf 'current_estimate_table_source_alignment: ok\n'

#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'project strategy/status framework: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'project strategy/status framework: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file .github/FUNDING.yml
require_file STATUS.md
require_file docs/strategy/README.md
require_file docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/status/ANNOUNCEMENTS.md
require_file docs/project_notes/README.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md

require_contains 'buy_me_a_coffee: Bryforge' .github/FUNDING.yml
require_contains 'https://buymeacoffee.com/Bryforge' README.md
require_contains '## Motto' README.md
require_contains 'The simulacrum is never what hides the truth.' README.md
require_contains '## Mission' README.md
require_contains '## Status and strategy' README.md
require_contains '## Support' README.md
require_contains 'STATUS.md' README.md
require_contains 'docs/status/CURRENT_STATUS.md' README.md
require_contains 'docs/status/ANNOUNCEMENTS.md' README.md
require_contains 'docs/strategy/README.md' README.md
require_contains 'docs/project_notes/README.md' README.md

require_contains 'Status: public status shortcut' STATUS.md
require_contains 'Overall Latticra system' STATUS.md
require_contains 'L-UI source-buffer literal NUL policy implementation plan' STATUS.md
require_contains 'planning estimates only' STATUS.md

require_contains 'Status: active strategy index' docs/strategy/README.md
require_contains '2026-05-15-2249-cdt-national-security-open-system-strategy.md' docs/strategy/README.md
require_contains 'Strategic planning rules' docs/strategy/README.md
require_contains 'anti-malware and anti-ransomware goals as design targets' docs/strategy/README.md
require_contains 'Quality bar' docs/strategy/README.md

require_contains 'Status: active strategy record' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Jean Baudrillard' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'national-security-grade discipline' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'auditable' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'defensive' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Primary target users' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'government infrastructure stakeholders' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Latticra does not currently prevent malware or ransomware.' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
require_contains 'Buy Me a Coffee: Bryforge' docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md

require_contains 'Status: active status index' docs/status/README.md
require_contains 'CURRENT_STATUS.md' docs/status/README.md
require_contains 'ANNOUNCEMENTS.md' docs/status/README.md
require_contains 'completion percentages' docs/status/README.md

require_contains 'Status: public status record' docs/status/CURRENT_STATUS.md
require_contains 'Rough completion estimates' docs/status/CURRENT_STATUS.md
require_contains 'Overall Latticra system' docs/status/CURRENT_STATUS.md
require_contains '15%' docs/status/CURRENT_STATUS.md
require_contains 'L-UI parser / AST / string foundation' docs/status/CURRENT_STATUS.md
require_contains '80%' docs/status/CURRENT_STATUS.md
require_contains 'Current non-claims' docs/status/CURRENT_STATUS.md
require_contains 'Next recommended work' docs/status/CURRENT_STATUS.md

require_contains 'Status: public announcement log' docs/status/ANNOUNCEMENTS.md
require_contains '2026-05-15 22:49 CDT' docs/status/ANNOUNCEMENTS.md
require_contains 'Strategy, status, sponsorship, and planning framework' docs/status/ANNOUNCEMENTS.md
require_contains 'Non-claims' docs/status/ANNOUNCEMENTS.md

require_contains 'Status: active project notes index' docs/project_notes/README.md
require_contains 'CURRENT_DIRECTION.md' docs/project_notes/README.md
require_contains 'UPCOMING_WORK.md' docs/project_notes/README.md
require_contains 'Status: active project note' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Current direction' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Current technical lane' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Status: active project note' docs/project_notes/UPCOMING_WORK.md
require_contains 'Recommended next slice' docs/project_notes/UPCOMING_WORK.md
require_contains 'Near-term queue' docs/project_notes/UPCOMING_WORK.md

printf 'project_strategy_status_framework: ok\n'

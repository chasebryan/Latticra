#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'report redaction boundary: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-report-redaction.XXXXXX")"
cleanup() {
  rm -rf "$tmp_dir"
}
trap cleanup EXIT INT HUP TERM

shell_hits="$tmp_dir/shell-hits.txt"
workflow_hits="$tmp_dir/workflow-hits.txt"
source_hits="$tmp_dir/source-hits.txt"
: >"$shell_hits"
: >"$workflow_hits"
: >"$source_hits"

shell_dump_pattern='(^|[[:space:]])(set[[:space:]]+-x|set[[:space:]]+-o[[:space:]]+xtrace|sh[[:space:]]+-x|bash[[:space:]]+-x)([[:space:]]|$)|^[[:space:]]*(printenv|export[[:space:]]+-p|declare[[:space:]]+-p|typeset[[:space:]]+-p|compgen[[:space:]]+-e)([[:space:]]|$)|^[[:space:]]*(sudo[[:space:]]+)?env[[:space:]]*([|>]|$)|^[[:space:]]*set[[:space:]]*([|>]|$)|/proc/self/environ'

for script in scripts/*.sh installer/scripts/*.sh; do
  [ -f "$script" ] || continue
  [ "$script" != "scripts/test-report-redaction-boundary.sh" ] || continue

  grep -En "$shell_dump_pattern" "$script" >>"$shell_hits" 2>/dev/null || :
done

if [ -s "$shell_hits" ]; then
  sed -n '1,40p' "$shell_hits" >&2
  fail "shell scripts must not dump full environments or enable xtrace in report/log paths"
fi

for workflow in .github/workflows/*.yml .github/workflows/*.yaml; do
  [ -f "$workflow" ] || continue
  grep -En "$shell_dump_pattern" "$workflow" >>"$workflow_hits" 2>/dev/null || :
done

if [ -s "$workflow_hits" ]; then
  sed -n '1,40p' "$workflow_hits" >&2
  fail "workflows must not dump full environments or enable xtrace in report/log paths"
fi

source_dump_pattern='std::env::vars(_os)?[[:space:]]*\(|os[.]environ[.]items[[:space:]]*\(|os[.]environ[.]copy[[:space:]]*\(|dict[[:space:]]*\([[:space:]]*os[.]environ[[:space:]]*\)|print[[:space:]]*\([[:space:]]*os[.]environ[[:space:]]*\)|pprint[[:space:]]*\([[:space:]]*os[.]environ[[:space:]]*\)|extern[[:space:]]+char[[:space:]]+\*\*environ|environ[[:space:]]*\[|/proc/self/environ'

find src include tools tests installer/latticra-installer/src \
  -path '*/target/*' -prune -o \
  -type f \( -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' -o -name '*.rs' -o -name '*.py' \) -print |
  while IFS= read -r source; do
    grep -En "$source_dump_pattern" "$source" >>"$source_hits" 2>/dev/null || :
  done

if [ -s "$source_hits" ]; then
  sed -n '1,40p' "$source_hits" >&2
  fail "source code must not enumerate or print whole process environments"
fi

engine="installer/latticra-installer/src/engine.rs"
require_contains "sanitize_log_line(&line)" "$engine"
require_contains "SENSITIVE_ASSIGNMENT_KEYS" "$engine"
require_contains "PRIVATE_KEY_MARKER_REDACTION" "$engine"
require_contains "redact_log_line_masks_sensitive_assignments" "$engine"
require_contains "sanitize_log_line_escapes_control_characters" "$engine"

if grep -Fq "InstallEvent::Log(line)" "$engine"; then
  fail "$engine must sanitize child stdout before forwarding install logs"
fi
if grep -Fq 'stderr: {line}' "$engine"; then
  fail "$engine must sanitize child stderr before forwarding install logs"
fi

printf 'report_redaction_boundary: ok\n'

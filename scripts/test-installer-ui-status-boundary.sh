#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer ui status boundary: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

require_single_contains() {
  pattern="$1"
  file="$2"
  count="$( (grep -F -- "$pattern" "$file" || true) | wc -l | tr -d ' ')"

  [ "$count" = "1" ] ||
    fail "$file must contain exactly one status storage boundary matching: $pattern"
}

ui_rs="installer/latticra-installer/src/ui.rs"

require_contains "fn set_status" "$ui_rs"
require_contains "self.status = sanitize_status_line(&status)" "$ui_rs"
require_contains "fn sanitize_status_line" "$ui_rs"
require_contains "const STATUS_MAX_LINE_CHARS" "$ui_rs"
require_contains "status_setter_redacts_and_escapes_direct_status_updates" "$ui_rs"
require_contains "status_line_sanitizer_redacts_and_truncates_event_text" "$ui_rs"

require_single_contains "self.status =" "$ui_rs"

if grep -Fq "self.status = format!(" "$ui_rs"; then
  fail "$ui_rs must not assign formatted status text outside set_status"
fi

if grep -Fq "self.status = err.clone()" "$ui_rs"; then
  fail "$ui_rs must not assign raw error text to status"
fi

require_contains "sh ./scripts/test-installer-ui-status-boundary.sh" Makefile
require_contains "installer-ui-status-boundary:" Makefile

printf 'installer_ui_status_boundary: ok\n'

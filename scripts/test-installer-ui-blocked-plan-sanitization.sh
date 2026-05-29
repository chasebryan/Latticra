#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer ui blocked plan sanitization: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

ui_rs="installer/latticra-installer/src/ui.rs"

require_contains "fn blocked_ui_plan" "$ui_rs"
require_contains "let validation_error = sanitize_status_line(error)" "$ui_rs"
require_contains "validation_error={validation_error}" "$ui_rs"
require_contains "blocked_ui_plan_sanitizes_error_record_value" "$ui_rs"
require_contains "blocked_ui_plan_truncates_oversized_error_value" "$ui_rs"
require_contains "blocked_ui_plan_omits_invalid_authority_value" "$ui_rs"

if grep -Fq "validation_error={error}" "$ui_rs"; then
  fail "$ui_rs must not interpolate raw validation errors into blocked plans"
fi

require_contains "sh ./scripts/test-installer-ui-blocked-plan-sanitization.sh" Makefile
require_contains "installer-ui-blocked-plan-sanitization:" Makefile

printf 'installer_ui_blocked_plan_sanitization: ok\n'

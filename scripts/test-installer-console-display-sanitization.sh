#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer console display sanitization: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

ui_rs="installer/latticra-installer/src/ui.rs"
engine_rs="installer/latticra-installer/src/engine.rs"

require_contains "const CONSOLE_MAX_LINE_CHARS" "$ui_rs"
require_contains "fn sanitize_console_line" "$ui_rs"
require_contains "self.console_lines.push(sanitize_console_line(&line))" "$ui_rs"
require_contains "engine::redact_log_line(line)" "$ui_rs"
require_contains "pub(crate) fn redact_log_line" "$engine_rs"
require_contains "console_line_sanitizer_escapes_control_characters" "$ui_rs"
require_contains "console_line_sanitizer_redacts_secret_assignments" "$ui_rs"
require_contains "console_line_sanitizer_truncates_oversized_lines" "$ui_rs"
require_contains "console_command_echo_escapes_multiline_secret_input" "$ui_rs"

if grep -Fq "self.console_lines.push(line.into())" "$ui_rs"; then
  fail "$ui_rs must not append raw console lines"
fi

require_contains "sh ./scripts/test-installer-console-display-sanitization.sh" Makefile
require_contains "installer-console-display-sanitization:" Makefile

printf 'installer_console_display_sanitization: ok\n'

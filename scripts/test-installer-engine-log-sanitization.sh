#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer engine log sanitization: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

engine_rs="installer/latticra-installer/src/engine.rs"

require_contains "const MAX_INSTALLER_LOG_LINE_CHARS" "$engine_rs"
require_contains "fn sanitize_log_line" "$engine_rs"
require_contains "fn send_log" "$engine_rs"
require_contains "InstallEvent::Log(sanitize_log_line(line.as_ref()))" "$engine_rs"
require_contains "send_log(&tx, line)" "$engine_rs"
require_contains "pub(crate) fn redact_log_line" "$engine_rs"
require_contains "sanitize_log_line_escapes_control_characters" "$engine_rs"
require_contains "sanitize_log_line_redacts_before_display_sanitization" "$engine_rs"
require_contains "sanitize_log_line_truncates_oversized_lines" "$engine_rs"

if grep -Fq "InstallEvent::Log(redact_log_line(&line))" "$engine_rs"; then
  fail "$engine_rs must not forward raw redacted child stdout without display sanitization"
fi

if grep -Fq "redact_log_line(&line)" "$engine_rs"; then
  fail "$engine_rs must not call redact_log_line directly on child log forwarding paths"
fi

require_contains "sh ./scripts/test-installer-engine-log-sanitization.sh" Makefile
require_contains "installer-engine-log-sanitization:" Makefile

printf 'installer_engine_log_sanitization: ok\n'

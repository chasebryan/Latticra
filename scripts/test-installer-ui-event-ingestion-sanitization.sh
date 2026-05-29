#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer ui event ingestion sanitization: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

ui_rs="installer/latticra-installer/src/ui.rs"

require_contains "const EVIDENCE_MAX_LINE_CHARS" "$ui_rs"
require_contains "const STATUS_MAX_LINE_CHARS" "$ui_rs"
require_contains "fn set_status" "$ui_rs"
require_contains "self.status = sanitize_status_line(&status)" "$ui_rs"
require_contains "fn push_evidence_log" "$ui_rs"
require_contains "let sanitized_line = sanitize_evidence_line(&raw_line)" "$ui_rs"
require_contains "fn sanitize_evidence_line" "$ui_rs"
require_contains "fn sanitize_status_line" "$ui_rs"
require_contains "fn sanitize_display_line" "$ui_rs"
require_contains "sanitize_display_line(line, EVIDENCE_MAX_LINE_CHARS)" "$ui_rs"
require_contains "sanitize_display_line(line, STATUS_MAX_LINE_CHARS)" "$ui_rs"
require_contains "let line = self.push_evidence_log(line)" "$ui_rs"
require_contains "let status = sanitize_status_line(&err)" "$ui_rs"
require_contains "self.push_evidence_log(format!(\"ENGINE_FAILURE: {err}\"))" "$ui_rs"
require_contains "evidence_line_sanitizer_escapes_control_characters" "$ui_rs"
require_contains "status_line_sanitizer_redacts_and_truncates_event_text" "$ui_rs"
require_contains "engine_log_event_is_sanitized_before_evidence_and_status" "$ui_rs"
require_contains "engine_failure_event_is_sanitized_before_status_and_evidence" "$ui_rs"

if grep -Fq "self.logs.push(line.clone())" "$ui_rs"; then
  fail "$ui_rs must not store raw engine event log lines"
fi

if grep -Fq "self.logs.push(format!(\"ENGINE_FAILURE: {err}\"))" "$ui_rs"; then
  fail "$ui_rs must not store raw engine failure text"
fi

if grep -Fq "self.status = err.clone()" "$ui_rs"; then
  fail "$ui_rs must not assign raw error text to status"
fi

status_assignments="$(grep -F "self.status =" "$ui_rs" || true)"
if [ "$status_assignments" != "        self.status = sanitize_status_line(&status);" ]; then
  fail "$ui_rs must route status assignments through set_status"
fi

require_contains "sh ./scripts/test-installer-ui-event-ingestion-sanitization.sh" Makefile
require_contains "installer-ui-event-ingestion-sanitization:" Makefile

printf 'installer_ui_event_ingestion_sanitization: ok\n'

#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer engine event boundary: %s\n' "$1" >&2
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
    fail "$file must contain exactly one boundary send matching: $pattern"
}

engine_rs="installer/latticra-installer/src/engine.rs"

require_contains "fn send_log" "$engine_rs"
require_contains "fn send_failure" "$engine_rs"
require_contains "InstallEvent::Log(sanitize_log_line(line.as_ref()))" "$engine_rs"
require_contains "InstallEvent::Failed(sanitize_log_line(err.as_ref()))" "$engine_rs"
require_contains "send_failure(&tx, err)" "$engine_rs"
require_contains "send_log(&tx, line)" "$engine_rs"
require_contains "send_log(&tx, format!(\"stderr: {line}\"))" "$engine_rs"
require_contains "fn send_network_authority_evidence" "$engine_rs"
require_contains "ENGINE: network_authority=0" "$engine_rs"
require_contains "ENGINE: network_authority_denied={}" "$engine_rs"
require_contains "ENGINE: network_fetch_authority=0" "$engine_rs"
require_contains "ENGINE: network_fetch_authority_denied={}" "$engine_rs"
require_contains "send_log_sanitizes_internal_engine_events" "$engine_rs"
require_contains "send_failure_sanitizes_engine_failure_events" "$engine_rs"
require_contains "send_network_authority_evidence_reports_denied_floor" "$engine_rs"

require_single_contains "tx.send(InstallEvent::Log" "$engine_rs"
require_single_contains "tx.send(InstallEvent::Failed" "$engine_rs"

if grep -Fq "InstallEvent::Log(format!(" "$engine_rs"; then
  fail "$engine_rs must route formatted log events through send_log"
fi

if grep -Fq "tx.send(InstallEvent::Log(line))" "$engine_rs"; then
  fail "$engine_rs must route child stdout through send_log"
fi

if grep -Fq "InstallEvent::Failed(err)" "$engine_rs"; then
  fail "$engine_rs must route failure events through send_failure"
fi

require_contains "sh ./scripts/test-installer-engine-event-boundary.sh" Makefile
require_contains "installer-engine-event-boundary:" Makefile

printf 'installer_engine_event_boundary: ok\n'

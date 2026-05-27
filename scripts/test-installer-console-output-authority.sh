#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer console output authority: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

ui_rs="installer/latticra-installer/src/ui.rs"

require_contains "fn console_report_config(&mut self)" "$ui_rs"
require_contains "fn console_command_requires_authority_floor" "$ui_rs"
require_contains "console_command_requires_authority_floor(parts.as_slice())" "$ui_rs"
require_contains "sanitized_ui_artifact_config(&self.config)" "$ui_rs"
require_contains "blocked: console command requires valid authority fields" "$ui_rs"
require_contains '["lc", "profile", ..]' "$ui_rs"
require_contains '["lc", "profiles"]' "$ui_rs"
require_contains '["nadia", "commands"]' "$ui_rs"
require_contains "console_config_report_blocks_invalid_authority_without_reflection" "$ui_rs"
require_contains "console_updater_report_blocks_invalid_authority_without_reflection" "$ui_rs"
require_contains "console_profile_command_can_repair_invalid_authority" "$ui_rs"
require_contains "console_command_discovery_works_with_invalid_authority" "$ui_rs"

guard_line="$(grep -n 'console_command_requires_authority_floor(parts.as_slice())' "$ui_rs" | head -n 1 | cut -d: -f1)"
match_line="$(grep -n 'match parts.as_slice()' "$ui_rs" | head -n 1 | cut -d: -f1)"

[ "$guard_line" -lt "$match_line" ] ||
  fail "$ui_rs must validate console authority before matching report commands"

require_contains "sh ./scripts/test-installer-console-output-authority.sh" Makefile
require_contains "installer-console-output-authority:" Makefile

printf 'installer_console_output_authority: ok\n'

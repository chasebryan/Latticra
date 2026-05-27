#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer UI artifact authority: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

config_rs="installer/latticra-installer/src/config.rs"
ui_rs="installer/latticra-installer/src/ui.rs"

require_contains "pub fn can_write_artifacts(&self)" "$config_rs"
require_contains "self.can_write_artifacts()?" "$config_rs"

require_contains "fn enforce_ui_artifact_authority_floor" "$ui_rs"
require_contains "fn sanitized_ui_artifact_config" "$ui_rs"
require_contains "fn ui_config_toml_artifact" "$ui_rs"
require_contains "fn ui_plan_artifact" "$ui_rs"
require_contains "fn blocked_ui_plan" "$ui_rs"
require_contains "self.panel_can_write_artifacts()" "$ui_rs"
require_contains "Artifact writes locked" "$ui_rs"
require_contains "blocked config save" "$ui_rs"
require_contains "blocked plan write" "$ui_rs"
require_contains "ui_config_artifact_rejects_invalid_authority_slug" "$ui_rs"
require_contains "ui_plan_artifact_rejects_invalid_authority_slug" "$ui_rs"
require_contains "ui_artifact_config_forces_network_authority_off" "$ui_rs"
require_contains "blocked_ui_plan_omits_invalid_authority_value" "$ui_rs"

if grep -Fq "self.plan = render_plan(&self.config)" "$ui_rs"; then
  fail "$ui_rs must not render UI plan artifacts without authority validation"
fi

if grep -Fq "toml::to_string_pretty(&self.config)" "$ui_rs"; then
  fail "$ui_rs must not serialize UI config artifacts without authority validation"
fi

require_contains "sh ./scripts/test-installer-ui-artifact-authority.sh" Makefile
require_contains "installer-ui-artifact-authority:" Makefile

printf 'installer_ui_artifact_authority: ok\n'

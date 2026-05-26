#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra panel lc install config: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_output_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf '--- output: %s ---\n' "$file" >&2
    sed -n '1,160p' "$file" >&2
    fail "missing required output pattern: $pattern"
  fi
}

ui='installer/latticra-installer/src/ui.rs'
config='installer/latticra-installer/src/config.rs'
apply='installer/scripts/latticra-installer-apply.sh'
default_config='installer/configs/default.installer.toml'
local_config='installer/configs/local-prefix-example.installer.toml'
manifest='installer/manifests/components.toml'
foundation_doc='docs/LATTICRA_CONSOLE_FOUNDATION.md'
workflow='.github/workflows/latticra-panel-installer.yml'

for file in \
  "$ui" \
  "$config" \
  "$apply" \
  "$default_config" \
  "$local_config" \
  "$manifest" \
  "$foundation_doc" \
  "$workflow" \
  Makefile
do
  require_file "$file"
done

require_contains 'pub struct LatticraConsoleInstallConfig' "$config"
require_contains 'install: LatticraConsoleInstallConfig' "$config"
require_contains 'LC install configuration cannot enable external host commands from the Panel.' "$config"
require_contains 'LC command wrapper must be a single command name.' "$config"
require_contains 'must be a relative path under the install prefix.' "$config"
require_contains 'LC install configuration' "$ui"
require_contains 'Install Latticra Console' "$ui"
require_contains 'External host commands (future; disabled)' "$ui"
require_contains '[lc.install]' "$default_config"
require_contains 'install_profile = "lc-panel-install-v0"' "$default_config"
require_contains 'allow_external_host_commands = false' "$default_config"
require_contains '[lc.install]' "$local_config"
require_contains 'install_user_wrapper = true' "$local_config"
require_contains 'LC_INSTALL_PROFILE=$(cfg_section lc.install install_profile lc-panel-install-v0)' "$apply"
require_contains 'LC_INSTALL_ALLOW_EXTERNAL_HOST_COMMANDS=$(cfg_section lc.install allow_external_host_commands false)' "$apply"
require_contains 'fail "LC install configuration cannot enable external host commands from the Panel" 78' "$apply"
require_contains 'write_file "$PREFIX/share/latticra/lc/install/config.toml"' "$apply"
require_contains 'if bool_true "$LATTICRA_CONSOLE" && bool_true "$LC_INSTALL_USER_WRAPPER"; then' "$apply"
require_contains 'bin/<lc.install.command_wrapper>' "$manifest"
require_contains 'share/latticra/lc/install/config.toml' "$manifest"
require_contains 'LC install metadata records config/share paths and the command wrapper' "$manifest"
require_contains 'share/latticra/lc/install/config.toml' "$foundation_doc"
require_contains 'lc.install.command_wrapper' "$foundation_doc"
require_contains 'sh ./scripts/test-latticra-panel-lc-install-config.sh' Makefile
require_contains 'Validate Latticra Panel LC install configuration' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-panel-lc-install-config-test.XXXXXX")"
mkdir -p "$tmp/home" "$tmp/receipts"
trap 'rm -rf "$tmp"' EXIT HUP INT TERM

HOME="$tmp/home" sh "$apply" \
  --config "$default_config" \
  --plan "$tmp/plan.txt" \
  --receipt-dir "$tmp/receipts" > "$tmp/dry-run.out" 2>&1

require_output_contains '[dry-run] would install LC config profile lc-panel-install-v0' "$tmp/dry-run.out"
require_contains 'install_profile=lc-panel-install-v0' "$tmp/plan.txt"
require_contains 'install_mode=metadata-only-console-foundation' "$tmp/plan.txt"
require_contains 'command_wrapper=latticra-lc' "$tmp/plan.txt"
require_contains 'allow_external_host_commands=false' "$tmp/plan.txt"
require_contains 'lc_install_profile=lc-panel-install-v0' "$tmp/receipts/latest-receipt.txt"
require_contains 'lc_allow_external_host_commands=false' "$tmp/receipts/latest-receipt.txt"

awk '
  $0 == "allow_external_host_commands = false" {
    print "allow_external_host_commands = true"
    next
  }
  { print }
' "$default_config" > "$tmp/external-host-commands.installer.toml"

if HOME="$tmp/home" sh "$apply" \
  --config "$tmp/external-host-commands.installer.toml" \
  --plan "$tmp/bad-plan.txt" \
  --receipt-dir "$tmp/bad-receipts" > "$tmp/external-host-commands.out" 2>&1
then
  fail "LC external-host-command config unexpectedly succeeded"
fi

require_output_contains 'LC install configuration cannot enable external host commands from the Panel' "$tmp/external-host-commands.out"

printf 'latticra_panel_lc_install_config: ok\n'

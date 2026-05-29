#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer ui console navigation boundary: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

ui_rs="installer/latticra-installer/src/ui.rs"

require_contains "terminal_root: String" "$ui_rs"
require_contains "let terminal_root = terminal_cwd.clone()" "$ui_rs"
require_contains "fn change_terminal_dir" "$ui_rs"
require_contains "let root = root.canonicalize().unwrap_or(root)" "$ui_rs"
require_contains "if !resolved.starts_with(&root)" "$ui_rs"
require_contains "cd denied: path outside panel workspace root" "$ui_rs"
require_contains "cd failed: path unavailable" "$ui_rs"
require_contains "console_navigation_allows_paths_inside_workspace_root" "$ui_rs"
require_contains "console_navigation_denies_paths_outside_workspace_root_without_reflection" "$ui_rs"

if grep -Fq "cd failed: {err}" "$ui_rs"; then
  fail "$ui_rs must not reflect raw cd OS errors into the panel console"
fi

if grep -Fq "not a directory: {}" "$ui_rs"; then
  fail "$ui_rs must not reflect rejected cd target paths into the panel console"
fi

require_contains "sh ./scripts/test-installer-ui-console-navigation-boundary.sh" Makefile
require_contains "installer-ui-console-navigation-boundary:" Makefile

printf 'installer_ui_console_navigation_boundary: ok\n'

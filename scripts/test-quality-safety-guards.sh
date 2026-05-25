#!/usr/bin/env sh
set -eu

ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$ROOT"

fail() {
  printf 'FAIL: %s\n' "$1" >&2
  exit 1
}

pass() {
  printf 'PASS: %s\n' "$1"
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

require_line() {
  pattern="$1"
  file="$2"

  grep -Fxq "$pattern" "$file" ||
    fail "$file must contain line: $pattern"
}

check_workflow() {
  workflow="$1"

  grep -q '^name:' "$workflow" ||
    fail "$workflow must declare a workflow name"
  grep -q '^on:' "$workflow" ||
    fail "$workflow must declare triggers"
  grep -Eq '^[[:space:]]*pull_request:' "$workflow" ||
    fail "$workflow must run on pull_request"
  grep -Eq '^[[:space:]]*push:' "$workflow" ||
    fail "$workflow must run on push"
  grep -q '^permissions:' "$workflow" ||
    fail "$workflow must declare explicit permissions"
  grep -q '^  contents: read' "$workflow" ||
    fail "$workflow must keep repository token permissions read-only"

  if grep -Eq 'pull_request_target:' "$workflow"; then
    fail "$workflow must not use pull_request_target"
  fi

  if grep -Eq 'secrets\.' "$workflow"; then
    fail "$workflow must not consume repository secrets without a dedicated review guard"
  fi

  if grep -Eq 'curl[^|]*\|[[:space:]]*(sh|bash)|wget[^|]*\|[[:space:]]*(sh|bash)|bash[[:space:]]+<|sh[[:space:]]+<' "$workflow"; then
    fail "$workflow must not pipe remote content into a shell"
  fi

  if grep -Eq 'git[[:space:]]+reset[[:space:]]+--hard|chmod[[:space:]]+-R[[:space:]]+777|rm[[:space:]]+-rf[[:space:]]+/' "$workflow"; then
    fail "$workflow contains an unsafe broad mutation command"
  fi

  action_refs="$(sed -nE 's/^[[:space:]]*uses:[[:space:]]*([^[:space:]]+).*/\1/p' "$workflow")"
  for action_ref in $action_refs; do
    case "$action_ref" in
      *@*) ;;
      *) fail "$workflow uses an unpinned action reference: $action_ref" ;;
    esac

    case "$action_ref" in
      *@main | *@master)
        fail "$workflow uses a moving action branch: $action_ref"
        ;;
    esac
  done

  script_refs="$(grep -Eo '(scripts|installer/scripts)/[A-Za-z0-9._/-]+\.sh' "$workflow" || :)"
  for script_ref in $script_refs; do
    [ -f "$script_ref" ] ||
      fail "$workflow references missing guard script $script_ref"
  done
}

check_shell_script() {
  script="$1"

  sh -n "$script" ||
    fail "$script failed shell syntax validation"

  if ! sed -n '1,6p' "$script" | grep -Eq '^set -e'; then
    fail "$script must enable fail-fast shell behavior near the top"
  fi

  if grep -q 'CFLAGS:=' "$script"; then
    for flag in -Wall -Wextra -Werror; do
      grep -q -- "$flag" "$script" ||
        fail "$script CFLAGS must include $flag"
    done
  fi

  if grep -q 'CXXFLAGS:=' "$script"; then
    for flag in -Wall -Wextra -Werror; do
      grep -q -- "$flag" "$script" ||
        fail "$script CXXFLAGS must include $flag"
    done
  fi

  if [ "$script" = "installer/scripts/latticra-installer-apply.sh" ]; then
    bad_cargo_builds=$(grep -n 'cargo build' "$script" | grep -Ev -- '--locked.*--offline|--offline.*--locked' || :)
    [ -z "$bad_cargo_builds" ] ||
      fail "$script cargo builds must use locked offline dependencies"

    require_contains "path_has_parent_reference()" "$script"
    require_contains "refusing install prefix with parent-directory traversal" "$script"
    require_contains "refusing symlink install prefix" "$script"
  fi

  if [ "$script" = "installer/scripts/latticra-installer-uninstall.sh" ]; then
    require_contains "path_has_parent_reference()" "$script"
    require_contains "parent-directory traversal" "$script"
    require_contains "refusing to reset symlink prefix" "$script"
  fi
}

workflow_count=0
for workflow in .github/workflows/*.yml .github/workflows/*.yaml; do
  [ -f "$workflow" ] || continue
  workflow_count=$((workflow_count + 1))
  check_workflow "$workflow"
done

[ "$workflow_count" -gt 0 ] ||
  fail "no GitHub workflow files found"

require_contains "quality-safety-guards:" "Makefile"
require_contains "quality: quality-safety-guards quality-defensive-threat-model seal-policy-denials quality-rust-installer quality-panel-installer quality-c-foundation" "Makefile"
require_contains "sh ./scripts/test-quality-safety-guards.sh" "Makefile"
require_contains "sh ./scripts/test-defensive-threat-model-contract.sh" "Makefile"
require_contains "sh ./scripts/test-defensive-threat-model-implementation-plan.sh" "Makefile"
require_contains "sh ./scripts/test-defensive-threat-model-validation.sh" "Makefile"
require_contains "cargo fmt --manifest-path installer/latticra-installer/Cargo.toml -- --check" "Makefile"
require_contains "cargo check --locked --manifest-path installer/latticra-installer/Cargo.toml" "Makefile"
require_contains "python3 scripts/check_latticra_panel_ui_design.py" "Makefile"
require_contains "sh ./scripts/test-latticra-panel-local-install-evidence-status.sh" "Makefile"
require_contains "sh ./scripts/test-latticra-panel-local-install-public-entrypoint-alignment.sh" "Makefile"
require_contains "sh ./scripts/test-latticra-panel-local-uninstall-reset.sh" "Makefile"
require_contains "sh ./scripts/test-latticra-console-foundation.sh" "Makefile"
require_contains "sh ./scripts/test-cpp-authority-layer.sh" "Makefile"
require_contains "make quality" ".github/workflows/quality.yml"
require_contains 'gcc \' ".github/workflows/quality.yml"
require_contains 'g++ \' ".github/workflows/quality.yml"
require_contains "timeout-minutes: 20" ".github/workflows/quality.yml"
require_contains "make quality-safety-guards" ".github/workflows/quality-safety-guards.yml"
require_contains "timeout-minutes: 10" ".github/workflows/quality-safety-guards.yml"
require_contains "cargo check --locked --manifest-path installer/latticra-installer/Cargo.toml" ".github/workflows/latticra-panel-installer.yml"
require_line "make quality" "README.md"
require_line "make quality-safety-guards" "README.md"
require_line "make quality" "CONTRIBUTING.md"
require_line "make quality-safety-guards" "CONTRIBUTING.md"

script_count=0
for script in scripts/*.sh installer/scripts/*.sh; do
  [ -f "$script" ] || continue
  script_count=$((script_count + 1))
  check_shell_script "$script"
done

[ "$script_count" -gt 0 ] ||
  fail "no shell guard scripts found"

pass "quality safety guards validated workflows=$workflow_count scripts=$script_count"

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

  script_refs="$(grep -Eo 'scripts/[A-Za-z0-9._/-]+\.sh' "$workflow" || :)"
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
}

workflow_count=0
for workflow in .github/workflows/*.yml .github/workflows/*.yaml; do
  [ -f "$workflow" ] || continue
  workflow_count=$((workflow_count + 1))
  check_workflow "$workflow"
done

[ "$workflow_count" -gt 0 ] ||
  fail "no GitHub workflow files found"

script_count=0
for script in scripts/*.sh installer/scripts/*.sh; do
  [ -f "$script" ] || continue
  script_count=$((script_count + 1))
  check_shell_script "$script"
done

[ "$script_count" -gt 0 ] ||
  fail "no shell guard scripts found"

pass "quality safety guards validated workflows=$workflow_count scripts=$script_count"

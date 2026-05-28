#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-quality-worktree-stability.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

processes="$tmpdir/processes.txt"
offenders="$tmpdir/offenders.txt"
marker="$tmpdir/stability-marker"
changed="$tmpdir/changed-files.txt"

touch "$marker"
sleep "${LATTICRA_QUALITY_STABILITY_WINDOW_SECONDS:-3}"

find .github/workflows scripts docs latticra-q-seal Makefile -type f -newer "$marker" -print > "$changed"

if [ -s "$changed" ]; then
  printf 'FAIL: quality worktree changed during stability window; stop concurrent validators before make quality\n' >&2
  cat "$changed" >&2
  exit 1
fi

if ps -axo pid=,ppid=,command= > "$processes" 2>/dev/null ||
  ps -eo pid=,ppid=,args= > "$processes" 2>/dev/null; then
  awk '
    /test-quality-worktree-stability[.]sh/ {
      next
    }
    {
      pid = $1
      ppid = $2
      command = $0
      sub(/^[[:space:]]*[0-9]+[[:space:]]+[0-9]+[[:space:]]*/, "", command)

      if (command ~ /scripts\/test-quality-safety-guards[.]sh/ ||
          command ~ /sh -x [.]?\/?scripts\/test-/ ||
          command ~ /sh [.]?\/?scripts\/test-/ ||
          command ~ /make quality-(security-standards|packaging-static|macos|safety-guards|nadia|c-foundation|status|installer-readiness|panel-installer|rust-installer)/ ||
          command ~ /remote-debugging-port=9226/ ||
          command ~ /latticra-panel-test-ui-/ ||
          command ~ /http[.]server .*--directory docs/) {
        print "pid=" pid " ppid=" ppid " command=" command
      }
    }
  ' "$processes" > "$offenders"
else
  : > "$offenders"
fi

if [ -s "$offenders" ]; then
  printf 'FAIL: concurrent Latticra validators or UI test processes are running; stop them before make quality\n' >&2
  cat "$offenders" >&2
  exit 1
fi

printf 'quality_worktree_stability: ok\n'

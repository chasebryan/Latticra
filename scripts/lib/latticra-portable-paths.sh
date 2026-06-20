#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
# Shared portable path helper for Latticra evidence reports/ledgers.
# Always produces repo-root relative POSIX paths.

portable_path() {
  p="$1"
  if command -v git >/dev/null 2>&1; then
    _root=$(git rev-parse --show-toplevel 2>/dev/null || echo "")
  fi
  if [ -z "$_root" ]; then
    if [ -n "${ROOT:-}" ] && [ -d "$ROOT" ]; then
      _root="$ROOT"
    else
      _d="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
      _root="$_d"
      while [ ! -f "$_root/README.md" ] && [ "$_root" != "/" ]; do _root="$(dirname "$_root")"; done
    fi
  fi
  python3 - "$p" "$_root" <<'PY'
import sys, os
from pathlib import Path
p = Path(sys.argv[1])
root = Path(sys.argv[2])
try:
  if p.is_absolute():
    cand = p
  else:
    cand = (root / p).resolve()
  print(os.path.relpath(str(cand.resolve()), str(root.resolve())))
except Exception:
  print(p.as_posix() if hasattr(p,'as_posix') else str(p))
PY
}

if [ "${0##*/}" = "latticra-portable-paths.sh" ]; then
  echo "self-test rel:" $(portable_path README.md)
  echo "self-test abs:" $(portable_path "$PWD/fixtures/latticra-model1-demo-evidence/valid-denied.packet")
  echo "lib self-test done"
fi

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
# Shared portable path helper for Latticra evidence reports, ledgers, and receipts.
# Ensures references written to reports use repo-root-relative POSIX paths
# even when absolute paths are provided (for receipt reference portability).

portable_path() {
  p="$1"
  if [ -n "${ROOT:-}" ] && [ -d "$ROOT" ]; then
    _root="$ROOT"
  else
    _script_dir="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
    _root="$_script_dir"
    while [ ! -f "$_root/README.md" ] && [ "$_root" != "/" ]; do
      _root="$(dirname "$_root")"
    done
  fi
  python3 - "$p" "$_root" <<'PY'
import sys
import os
from pathlib import Path
p = Path(sys.argv[1])
root = Path(sys.argv[2])
try:
  if p.is_absolute():
    cand = p
  else:
    cand = (root / p).resolve()
  r_cand = cand.resolve()
  r_root = root.resolve()
  rel = os.path.relpath(str(r_cand), str(r_root))
  print(rel)
except Exception:
  try:
    print(p.as_posix())
  except Exception:
    print(str(p))
PY
}

if [ "${0##*/}" = "latticra-portable-paths.sh" ]; then
  echo 'latticra portable paths lib self-test'
  res=$(portable_path "README.md")
  [ "$res" = "README.md" ] || { echo 'FAIL relative'; exit 1; }
  echo '  relative ok'
  abs_repo="$PWD/README.md"
  res2=$(portable_path "$abs_repo")
  case "$res2" in
    README.md) : ;;
    /*) echo 'FAIL abs not normalized: '"$res2" ; exit 1 ;;
  esac
  echo '  abs normalized ok'
  echo 'self-test: ok'
fi

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
# Shared portable path helper for Latticra evidence reports, ledgers, and receipts.
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

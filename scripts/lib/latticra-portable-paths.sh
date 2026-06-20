#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
# Portable path helper for receipt references and model1 tests.

REPO_ROOT="${REPO_ROOT:-$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)}"

portable_path() {
  p="$1"
  if [ -z "$p" ]; then echo ""; return 0; fi
  if [ -d "$REPO_ROOT" ]; then
    case "$p" in
      /*) candidate="$p" ;;
      *) candidate="$REPO_ROOT/$p" ;;
    esac
    if [ -e "$candidate" ]; then
      (cd "$REPO_ROOT" && realpath --relative-to=. "$candidate" 2>/dev/null || echo "$p")
    else
      echo "$p"
    fi
  else
    echo "$p"
  fi
}

export REPO_ROOT

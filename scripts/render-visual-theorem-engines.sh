#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MODE="${1:-build}"
DURATION="${2:-96}"
CC_BIN="${CC:-gcc}"
OUT="$ROOT/build/visual-engines"

usage() {
  cat <<USAGE
Usage:
  scripts/render-visual-theorem-engines.sh build
  scripts/render-visual-theorem-engines.sh substrate [seconds]
  scripts/render-visual-theorem-engines.sh theorem [seconds]
  scripts/render-visual-theorem-engines.sh all [seconds]
USAGE
}

require_source() {
  local src="$1"
  if [ ! -f "$src" ]; then
    echo "Missing source file: $src" >&2
    exit 1
  fi
}

need_ffmpeg() {
  if ! command -v ffmpeg >/dev/null 2>&1; then
    echo "ffmpeg is required for MP4 rendering." >&2
    echo "On Fedora, install it with: sudo dnf install ffmpeg" >&2
    exit 1
  fi
}

build() {
  mkdir -p "$OUT"

  require_source "$ROOT/substrate-engine/latticra_substrate_engine_nofigure.c"
  require_source "$ROOT/visual-theorem-engine/latticra_theorem_engine.c"

  "$CC_BIN" -std=gnu99 -O2 -Wall -Wextra -Wno-unused-function \
    "$ROOT/substrate-engine/latticra_substrate_engine_nofigure.c" \
    -lm -o "$OUT/latticra_substrate_engine"

  "$CC_BIN" -std=gnu99 -O2 -Wall -Wextra -Wno-unused-function \
    "$ROOT/visual-theorem-engine/latticra_theorem_engine.c" \
    -lm -o "$OUT/latticra_theorem_engine"

  echo "Built visual engines into: $OUT"
}

case "$MODE" in
  build)
    build
    ;;

  substrate)
    need_ffmpeg
    build
    "$OUT/latticra_substrate_engine" \
      "$OUT/latticra-substrate-engine.mp4" \
      "$DURATION"
    echo "Rendered: $OUT/latticra-substrate-engine.mp4"
    ;;

  theorem)
    need_ffmpeg
    build
    "$OUT/latticra_theorem_engine" \
      "$OUT/latticra-theorem-engine.mp4" \
      "$DURATION"
    echo "Rendered: $OUT/latticra-theorem-engine.mp4"
    ;;

  all)
    need_ffmpeg
    build
    "$OUT/latticra_substrate_engine" \
      "$OUT/latticra-substrate-engine.mp4" \
      "$DURATION"

    "$OUT/latticra_theorem_engine" \
      "$OUT/latticra-theorem-engine.mp4" \
      "$DURATION"

    echo "Rendered both videos into: $OUT"
    ;;

  *)
    usage
    exit 1
    ;;
esac

#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUNDLED_PY="$HOME/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3"
CONFIG="$ROOT/presentations/latticra-motion/latticra_motion_presentation.toml"
OUT="$ROOT/build/presentation/latticra-motion"
DEFAULT_PIPER_BIN="$ROOT/.venv-piper/bin/piper"
DEFAULT_PIPER_MODEL="$ROOT/assets/piper-voices/en_US-lessac-medium.onnx"
DEFAULT_PIPER_CONFIG="$ROOT/assets/piper-voices/en_US-lessac-medium.onnx.json"

if [ "${PY_BIN:-}" ]; then
  PYTHON_BIN="$PY_BIN"
elif [ -x "$BUNDLED_PY" ]; then
  PYTHON_BIN="$BUNDLED_PY"
else
  PYTHON_BIN="${PYTHON:-python3}"
fi

PIPER_ARGS=()
if [ -z "${PIPER_BIN:-}" ] && [ -x "$DEFAULT_PIPER_BIN" ]; then
  PIPER_ARGS+=(--piper-bin "$DEFAULT_PIPER_BIN")
fi
if [ -z "${PIPER_MODEL:-}" ] && [ -f "$DEFAULT_PIPER_MODEL" ]; then
  PIPER_ARGS+=(--piper-model "$DEFAULT_PIPER_MODEL")
  if [ -f "$DEFAULT_PIPER_CONFIG" ]; then
    PIPER_ARGS+=(--piper-config "$DEFAULT_PIPER_CONFIG")
  fi
fi

exec "$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" \
  --config "$CONFIG" \
  --out "$OUT" \
  "${PIPER_ARGS[@]}" \
  "$@"

#!/usr/bin/env sh
set -eu

ROOT="$(CDPATH= cd -- "$(dirname "$0")/.." && pwd)"
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

use_default_piper_bin=0
use_default_piper_model=0
use_default_piper_config=0

if [ -z "${PIPER_BIN:-}" ] && [ -x "$DEFAULT_PIPER_BIN" ]; then
  use_default_piper_bin=1
fi
if [ -z "${PIPER_MODEL:-}" ] && [ -f "$DEFAULT_PIPER_MODEL" ]; then
  use_default_piper_model=1
  if [ -f "$DEFAULT_PIPER_CONFIG" ]; then
    use_default_piper_config=1
  fi
fi

if [ "$use_default_piper_bin" -eq 1 ] && [ "$use_default_piper_model" -eq 1 ] && [ "$use_default_piper_config" -eq 1 ]; then
  exec "$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" \
    --config "$CONFIG" \
    --out "$OUT" \
    --piper-bin "$DEFAULT_PIPER_BIN" \
    --piper-model "$DEFAULT_PIPER_MODEL" \
    --piper-config "$DEFAULT_PIPER_CONFIG" \
    "$@"
elif [ "$use_default_piper_bin" -eq 1 ] && [ "$use_default_piper_model" -eq 1 ]; then
  exec "$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" \
    --config "$CONFIG" \
    --out "$OUT" \
    --piper-bin "$DEFAULT_PIPER_BIN" \
    --piper-model "$DEFAULT_PIPER_MODEL" \
    "$@"
elif [ "$use_default_piper_model" -eq 1 ] && [ "$use_default_piper_config" -eq 1 ]; then
  exec "$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" \
    --config "$CONFIG" \
    --out "$OUT" \
    --piper-model "$DEFAULT_PIPER_MODEL" \
    --piper-config "$DEFAULT_PIPER_CONFIG" \
    "$@"
elif [ "$use_default_piper_bin" -eq 1 ]; then
  exec "$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" \
    --config "$CONFIG" \
    --out "$OUT" \
    --piper-bin "$DEFAULT_PIPER_BIN" \
    "$@"
elif [ "$use_default_piper_model" -eq 1 ]; then
  exec "$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" \
    --config "$CONFIG" \
    --out "$OUT" \
    --piper-model "$DEFAULT_PIPER_MODEL" \
    "$@"
else
  exec "$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" \
    --config "$CONFIG" \
    --out "$OUT" \
    "$@"
fi

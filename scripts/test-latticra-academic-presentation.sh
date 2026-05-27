#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUNDLED_PY="$HOME/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3"

if [ -x "$BUNDLED_PY" ]; then
  PYTHON_BIN="$BUNDLED_PY"
else
  PYTHON_BIN="${PYTHON:-python3}"
fi

OUT="$(mktemp -d "${TMPDIR:-/tmp}/latticra-academic-presentation.XXXXXX")"
trap 'rm -rf "$OUT"' EXIT INT HUP TERM

"$PYTHON_BIN" "$ROOT/tools/render_latticra_academic_presentation.py" storyboard --out "$OUT" >/dev/null
"$PYTHON_BIN" "$ROOT/tools/render_latticra_academic_presentation.py" preview --out "$OUT" --size 960x540 --fps 12 >/dev/null

test -s "$OUT/voiceover-script.txt"
test -s "$OUT/voiceover-cues.srt"
test -s "$OUT/storyboard.json"
test -s "$OUT/preview/contact-sheet.png"
test -s "$OUT/preview/scene-01.png"
test -s "$OUT/piper-scenes/scene-01.txt"

"$PYTHON_BIN" - "$OUT/storyboard.json" <<'PY'
import json
import sys
from pathlib import Path

path = Path(sys.argv[1])
data = json.loads(path.read_text(encoding="utf-8"))
assert data["total_seconds"] >= 720, data["total_seconds"]
assert data["scene_count"] == 12, data["scene_count"]
assert data["word_count"] >= 1400, data["word_count"]
for scene in data["scenes"]:
    assert scene["duration"] > 0, scene
    assert scene["narration_word_count"] >= 90, scene
    assert scene["terms"], scene
    assert scene["bullets"], scene
PY

printf 'latticra_academic_presentation: ok\n'

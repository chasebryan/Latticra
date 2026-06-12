#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUNDLED_PY="$HOME/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3"
CONFIG="$ROOT/presentations/latticra-motion/latticra_motion_presentation.toml"

if [ -x "$BUNDLED_PY" ]; then
  PYTHON_BIN="$BUNDLED_PY"
else
  PYTHON_BIN="${PYTHON:-python3}"
fi

require_contains() {
  needle="$1"
  file="$2"
  if ! grep -F -- "$needle" "$ROOT/$file" >/dev/null; then
    printf 'missing %s in %s\n' "$needle" "$file" >&2
    exit 1
  fi
}

OUT="$(mktemp -d "${TMPDIR:-/tmp}/latticra-motion-presentation.XXXXXX")"
trap 'rm -rf "$OUT"' EXIT INT HUP TERM

"$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" storyboard --config "$CONFIG" --out "$OUT" >/dev/null
"$PYTHON_BIN" "$ROOT/tools/render_latticra_motion_presentation.py" preview --config "$CONFIG" --out "$OUT" --size 1280x720 --fps 12 >/dev/null

test -s "$OUT/voiceover-script.txt"
test -s "$OUT/voiceover-cues.srt"
test -s "$OUT/storyboard.json"
test -s "$OUT/storyboard-manifest.json"
test -s "$OUT/preview-manifest.json"
test -s "$OUT/preview/contact-sheet.png"
test -s "$OUT/preview/scene-01-opening.png"
test -s "$OUT/piper-scenes/scene-01-opening.txt"
test ! -e "$OUT/render-manifest.json"

"$PYTHON_BIN" - "$OUT/storyboard.json" "$OUT/preview-manifest.json" <<'PY'
import json
import sys
from pathlib import Path

data = json.loads(Path(sys.argv[1]).read_text(encoding="utf-8"))
manifest = json.loads(Path(sys.argv[2]).read_text(encoding="utf-8"))
assert data["scene_count"] == 14, data["scene_count"]
assert data["planned_seconds"] >= 900, data["planned_seconds"]
assert data["word_count"] >= 1700, data["word_count"]
assert data["artifact_slug"] == "latticra-motion", data["artifact_slug"]
assert not data["phrase_audit"]["repeated_four_grams"], data["phrase_audit"]["repeated_four_grams"]
assert manifest["mode"] == "preview", manifest["mode"]
assert manifest["scene_count"] == data["scene_count"], manifest["scene_count"]
assert manifest["artifact_slug"] == data["artifact_slug"], manifest["artifact_slug"]
assert len(manifest["config_sha256"]) == 64, manifest["config_sha256"]
assert "video" not in manifest, manifest
for scene in data["scenes"]:
    assert scene["narration_word_count"] >= 90, scene
    assert len(scene["screen_title"]) <= 88, scene["screen_title"]
    assert len(scene["screen_line"]) <= 78, scene["screen_line"]
    assert scene["id"].replace("_", "").replace("-", "").isalnum(), scene["id"]
PY

root_motion_video='build/presentation/latticra-motion/video/latticra-motion-presentation.mp4'
docs_motion_video='../build/presentation/latticra-motion/video/latticra-motion-presentation.mp4'
require_contains 'latticra-motion-presentation-test:' Makefile
require_contains 'sh ./scripts/test-latticra-motion-presentation.sh' Makefile
require_contains "$root_motion_video" README.md
require_contains "$docs_motion_video" docs/README.md
require_contains "$docs_motion_video" docs/DOCUMENTATION_READER_JOURNEY_MAP.md
require_contains "$root_motion_video" docs/VISUAL_THEOREM_ENGINES.md
require_contains "$docs_motion_video" docs/index.html
require_contains "$docs_motion_video" docs/map.html

printf 'latticra_motion_presentation: ok\n'

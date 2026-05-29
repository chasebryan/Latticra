#!/usr/bin/env bash
# SPDX-License-Identifier: AGPL-3.0-or-later
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="$ROOT/build/visual-engines/computational-math-physics"
NARRATION="$ROOT/presentations/latticra-computational-math-physics/narration.txt"
PIPER_BIN="${PIPER_BIN:-$ROOT/.venv-piper/bin/piper}"
PIPER_MODEL="${PIPER_MODEL:-$ROOT/assets/piper-voices/en_US-lessac-medium.onnx}"
PIPER_CONFIG="${PIPER_CONFIG:-$ROOT/assets/piper-voices/en_US-lessac-medium.onnx.json}"
FFMPEG_BIN="${FFMPEG_BIN:-ffmpeg}"
FFPROBE_BIN="${FFPROBE_BIN:-ffprobe}"

fail() {
  printf 'latticra computational math physics demo render: %s\n' "$1" >&2
  exit 1
}

require_file() {
  local file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_exec() {
  local cmd="$1"
  if [ -x "$cmd" ]; then
    return 0
  fi
  command -v "$cmd" >/dev/null 2>&1 || fail "missing executable: $cmd"
}

timestamp() {
  awk -v seconds="$1" 'BEGIN {
    total_ms = int((seconds * 1000) + 0.5)
    ms = total_ms % 1000
    total_s = int(total_ms / 1000)
    s = total_s % 60
    m = int(total_s / 60) % 60
    h = int(total_s / 3600)
    printf "%02d:%02d:%02d,%03d", h, m, s, ms
  }'
}

write_captions() {
  local duration="$1"
  local srt="$2"
  local step
  step="$(awk -v d="$duration" 'BEGIN { printf "%.3f", d / 6.0 }')"
  : > "$srt"

  cue() {
    local index="$1"
    local start="$2"
    local end="$3"
    local text="$4"
    {
      printf '%s\n' "$index"
      printf '%s --> %s\n' "$(timestamp "$start")" "$(timestamp "$end")"
      printf '%s\n\n' "$text"
    } >> "$srt"
  }

  cue 1 0 "$step" "State space: variables, boundaries, initial conditions, and admissible transformations."
  cue 2 "$step" "$(awk -v s="$step" 'BEGIN { printf "%.3f", s * 2 }')" "Transition operator: replayable state movement with explicit failure conditions."
  cue 3 "$(awk -v s="$step" 'BEGIN { printf "%.3f", s * 2 }')" "$(awk -v s="$step" 'BEGIN { printf "%.3f", s * 3 }')" "Invariant surfaces: conservation, symmetry, scale, locality, and constraint boundaries."
  cue 4 "$(awk -v s="$step" 'BEGIN { printf "%.3f", s * 3 }')" "$(awk -v s="$step" 'BEGIN { printf "%.3f", s * 4 }')" "Observer projection: measurement limits, error terms, and alternative explanations."
  cue 5 "$(awk -v s="$step" 'BEGIN { printf "%.3f", s * 4 }')" "$(awk -v s="$step" 'BEGIN { printf "%.3f", s * 5 }')" "Physics coupling: units, scale, measurement protocol, noise model, and negative results."
  cue 6 "$(awk -v s="$step" 'BEGIN { printf "%.3f", s * 5 }')" "$duration" "Visual demonstration: explanation surface only, not proof or scientific claim promotion."
}

require_file "$NARRATION"
require_file "$PIPER_MODEL"
require_file "$PIPER_CONFIG"
require_exec "$PIPER_BIN"
require_exec "$FFMPEG_BIN"
require_exec "$FFPROBE_BIN"

mkdir -p "$OUT"

voiceover="$OUT/voiceover.wav"
script_copy="$OUT/voiceover-script.txt"
srt="$OUT/voiceover-cues.srt"
source_video="$ROOT/build/visual-engines/latticra-substrate-engine.mp4"
silent_video="$OUT/latticra-computational-math-physics-substrate-silent.mp4"
final_video="$OUT/latticra-computational-math-physics-demo.mp4"
manifest="$OUT/render-manifest.txt"

cp "$NARRATION" "$script_copy"

"$PIPER_BIN" \
  --model "$PIPER_MODEL" \
  --config "$PIPER_CONFIG" \
  --input-file "$NARRATION" \
  --output-file "$voiceover" \
  --sentence-silence 0.28

audio_duration="$("$FFPROBE_BIN" -v error -show_entries format=duration -of default=noprint_wrappers=1:nokey=1 "$voiceover")"
render_seconds="$(awk -v d="$audio_duration" 'BEGIN { seconds = int(d + 3.999); if (seconds < 60) seconds = 60; printf "%d", seconds }')"

"$ROOT/scripts/render-visual-theorem-engines.sh" substrate "$render_seconds"
cp "$source_video" "$silent_video"

write_captions "$audio_duration" "$srt"

"$FFMPEG_BIN" -y \
  -i "$silent_video" \
  -i "$voiceover" \
  -map 0:v:0 \
  -map 1:a:0 \
  -c:v copy \
  -c:a aac \
  -b:a 160k \
  -shortest \
  "$final_video"

{
  printf 'latticra_computational_math_physics_demo_rendered=1\n'
  printf 'render_mode=substrate-engine-with-piper-voiceover\n'
  printf 'source_video=%s\n' "$silent_video"
  printf 'voiceover=%s\n' "$voiceover"
  printf 'captions=%s\n' "$srt"
  printf 'final_video=%s\n' "$final_video"
  printf 'audio_duration_seconds=%s\n' "$audio_duration"
  printf 'render_seconds=%s\n' "$render_seconds"
  printf 'simulation_proven=0\n'
  printf 'scientific_claim_promoted=0\n'
} > "$manifest"

printf 'Rendered narrated computational math/physics demo:\n%s\n' "$final_video"

# Latticra Visual Theorem Engines

Latticra includes C-based visual theorem engines that render symbolic substrate models as MP4 video demonstrations.

These engines are not ordinary animations. They are visual field demonstrations of the Latticra idea: lattice nodes, matrix substrate behavior, recursive numeric order, modular expansion, abstraction containment, axiom fracture, particle-field unification, quantum deceleration, and regenesis from a null-state.

## Engines

### latt-field-engines/substrate-engine/

The figure-free Latticra Substrate Engine.

This version removes the human-like center figure and focuses entirely on the field itself. It renders the Latticra substrate as a moving 2D mathematical plane containing:

- Primordial substrate closure
- Matrix substrate structure
- Sigkokilla Modul expansion
- Abstraction-field containment
- Axiomatic fracture
- Particle unification
- Quantum deceleration
- Cosmic regenesis

### latt-field-engines/visual-theorem-engine/

The original cinematic theorem engine.

This version includes a central operator figure and demonstrates the earlier theorem-card aesthetic as a moving symbolic system.

## Build

From the repository root:

    scripts/render-visual-theorem-engines.sh build

## Render the substrate engine

    scripts/render-visual-theorem-engines.sh substrate 96

Output:

    build/visual-engines/latticra-substrate-engine.mp4

## Render the theorem engine

    scripts/render-visual-theorem-engines.sh theorem 60

Output:

    build/visual-engines/latticra-theorem-engine.mp4

## Render both

    scripts/render-visual-theorem-engines.sh all 96

## Academic presentation production engine

The university presentation path is separate from the older C-only theorem
videos. It keeps the symbolic field language, but moves slide typography,
voiceover timing, captions, and proof-object layout into a higher-level
production renderer:

    scripts/render-latticra-academic-presentation.sh preview

Preview output:

    build/presentation/latticra-academic/preview/contact-sheet.png
    build/presentation/latticra-academic/voiceover-script.txt
    build/presentation/latticra-academic/voiceover-cues.srt

The full 720 second script lives in:

    presentations/latticra-academic/latticra_academic_presentation.toml

The final render command is:

    scripts/render-latticra-academic-presentation.sh render

For Piper voiceover, provide a voice model if it is not already configured:

    PIPER_MODEL=/path/to/voice.onnx scripts/render-latticra-academic-presentation.sh render

Optional overrides:

    PIPER_BIN=/path/to/piper
    PIPER_PYTHON=/path/to/python-with-piper-tts
    PIPER_MODEL=/path/to/voice.onnx
    PIPER_CONFIG=/path/to/voice.onnx.json
    FFMPEG_BIN=/path/to/ffmpeg

If `PIPER_BIN` is not set and no standalone `piper` executable is on `PATH`,
the renderer falls back to the modern Python module form:

    "$PIPER_PYTHON" -m piper

The renderer pads shorter Piper scenes to their planned chapter timing and
extends any scene whose generated audio runs longer than its planned duration.
That keeps the voiceover integral to the video instead of appended after the
fact.

## Requirements

- gcc
- ffmpeg
- standard C math library, linked with -lm
- Python 3.11+ with Pillow for the academic presentation renderer
- Piper and a Piper voice model for generated narration

On Fedora:

    sudo dnf install gcc ffmpeg

## Theory summary

The visual theorem engines posit Latticra as a symbolic computation substrate where field structures can be represented as lattices, split into substructures, projected onto a 2D abstraction plane, decelerated toward coherence, unified into particle-field classes, and regenerated from a null-state through deterministic operators.

The project is best understood as a mathematical art-engine and speculative computation model: part visual proof sketch, part symbolic systems theory, and part Latticra identity piece.

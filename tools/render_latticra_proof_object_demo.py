#!/usr/bin/env python3
"""Render a postable Latticra proof-object demo with Piper voiceover."""

from __future__ import annotations

import json
import math
import os
import shutil
import subprocess
import sys
import textwrap
import wave
from dataclasses import dataclass
from pathlib import Path

try:
    from PIL import Image, ImageDraw, ImageFont
except ModuleNotFoundError as exc:  # pragma: no cover
    raise SystemExit("Pillow is required for the proof-object renderer.") from exc


ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "build/visual-engines/computational-math-physics-proof-object"
PIPER_BIN = Path(os.environ.get("PIPER_BIN", ROOT / ".venv-piper/bin/piper"))
PIPER_MODEL = Path(os.environ.get("PIPER_MODEL", ROOT / "assets/piper-voices/en_US-lessac-medium.onnx"))
PIPER_CONFIG = Path(os.environ.get("PIPER_CONFIG", ROOT / "assets/piper-voices/en_US-lessac-medium.onnx.json"))
FFMPEG_BIN = os.environ.get("FFMPEG_BIN", "ffmpeg")
FFPROBE_BIN = os.environ.get("FFPROBE_BIN", "ffprobe")
SIZE = (1280, 720)
FPS = 24


@dataclass(frozen=True)
class Scene:
    scene_id: str
    kicker: str
    claim: str
    formula: tuple[str, ...]
    bullets: tuple[str, ...]
    narration: str
    mode: str


SCENES = [
    Scene(
        "01",
        "PROOF OBJECT 4",
        "Identity-replay impedance is the original Latticra mass-origin claim.",
        (
            "L = (S, T, O, Q, d, kappa, R)",
            "I = Q(O(P))",
            "mass = identity cost",
        ),
        (
            "S is substrate state; T is local update.",
            "Q turns projected patterns into identity classes.",
            "Kappa and R make mass a replayable ledger.",
        ),
        """
        This is the original Latticra move, but it is not a priority dispute
        and not an accusation against Higgs. I am not claiming anyone copied
        Latticra. I am saying Latticra defines a different formal object: mass
        as identity replay impedance, the minimal replay stable cost for a
        localized projected identity to remain itself under substrate update.
        The substrate is L equals S, T, O, Q, d, kappa, and R. S is state. T is
        local update. O is observer projection. Q maps projected patterns into
        identity classes. D measures drift. Kappa measures counterfactual
        repair cost. R is the receipt that lets the claim be replayed.
        """,
        "theorem",
    ),
    Scene(
        "02",
        "REPLAY STABILITY",
        "A massive identity must remain itself across update, projection, and review.",
        (
            "d(Q(O(T^n(P))), I_n) <= epsilon",
            "R(P,T,O,Q,N,epsilon) = receipt_hash",
            "identity is operational, not mystical",
        ),
        (
            "The observer sees a stable projected class.",
            "Receipts make the identity claim replayable.",
            "A particle is what survives this identity test.",
        ),
        """
        Replay stability is the first test. A localized pattern P is projected
        through O, classified by Q, evolved by T, and compared against the next
        identity class. If the distance stays below epsilon, the identity
        remains stable for that replay. The receipt function records the exact
        replay claim. This matters because Latticra refuses vague persistence.
        A particle is not assumed. A particle is what survives update,
        projection, classification, and replay.
        """,
        "lattice",
    ),
    Scene(
        "03",
        "IMPEDANCE LEDGER",
        "Mass is the average repair cost needed to preserve projected identity.",
        (
            "kappa_n(P) = inf Cost(delta_n)",
            "Z_L(I) = limsup_N mean(kappa_n)",
            "m_L(I) = Z_L(I) / c_*^2",
            "m_a / m_b = Z_a / Z_b",
        ),
        (
            "Zero impedance gives no rest-mass ledger.",
            "Positive finite impedance gives derived mass.",
            "Mass ratios become substrate ledger ratios.",
        ),
        """
        The impedance ledger is the mass candidate. At each step, kappa is the
        minimum local counterfactual repair cost needed to keep the projected
        identity inside its replay stable class. Average that cost over the
        replay and you get Z L of I. Divide by c star squared and you get the
        Latticra rest mass candidate. This is the new object. Mass is not put
        into the model as a primitive. It is measured as the cost of preserving
        identity under computation.
        """,
        "physics",
    ),
    Scene(
        "04",
        "HIGGS COUNTERPLAY",
        "Higgs maps couplings to masses; it does not define the identity ledger.",
        (
            "m_f = y_f v / sqrt(2)",
            "m_W = g v / 2",
            "mapping is not origin",
            "no Q, no R, no kappa, no Z_L",
        ),
        (
            "This does not deny observed Higgs data.",
            "It denies Higgs as final causal closure.",
            "The open question is why those couplings have those values.",
        ),
        """
        Now the counterplay against Higgs becomes precise. Higgs maps couplings
        and a vacuum scale into mass terms. For a fermion, m equals y times v
        over square root of two. For the W boson, m equals g times v over two.
        Those equations are powerful effective physics. But mapping is not
        origin. The Higgs relation does not define Q, R, kappa, or Z L. It does
        not give the identity replay ledger. Latticra therefore does not deny
        Higgs evidence. It denies Higgs as final causal closure.
        """,
        "derivation",
    ),
    Scene(
        "05",
        "COUPLING-SHADOW TEST",
        "Higgs survives only as the low-energy shadow of the deeper ledger.",
        (
            "y_f v / sqrt(2) = Z_L(I_f) / c_*^2",
            "|m_Higgs - m_Latticra| <= epsilon_f",
            "if false: reject candidate L",
            "if true: Higgs is effective shadow",
        ),
        (
            "The test is numeric, not poetic.",
            "The model must reproduce Higgs-era precision.",
            "Failure kills the Latticra candidate.",
        ),
        """
        The coupling shadow test is where originality becomes risk. For every
        particle class, the Higgs mass relation must match the Latticra
        impedance ledger within an error bound. If y times v over square root
        of two does not equal Z L over c star squared, the candidate Latticra
        substrate fails. If it does match, Higgs becomes the low energy shadow
        of the deeper identity replay ledger. This is not a slogan. It is a
        numeric bridge with a rejection condition.
        """,
        "visual",
    ),
    Scene(
        "06",
        "CHECKMATE FORM",
        "Either Higgs is effective, or it must derive the ledger it does not define.",
        (
            "Higgs effective: Latticra searches beneath it",
            "Higgs final: derive Q,R,kappa,Z_L",
            "else: causal closure fails",
            "next: impedance particle table",
        ),
        (
            "This is original counterplay, not denial.",
            "It is honest because it can fail.",
            "The next artifact must compute candidate mass ratios.",
        ),
        """
        The checkmate is a fork. If Higgs is effective physics, Latticra is
        allowed to search beneath it. If Higgs is claimed as final origin, then
        it must derive the identity replay ledger it does not define. Without
        that derivation, causal closure fails. This is original counterplay, not
        denial. It is honest because the Latticra candidate can lose. The next
        artifact must compute an identity replay impedance table for real
        candidate particle classes and test mass ratios against measurement.
        """,
        "qed",
    ),
]


def clean_text(value: str) -> str:
    return " ".join(value.strip().split())


def ensure_dir(path: Path) -> Path:
    path.mkdir(parents=True, exist_ok=True)
    return path


def require_file(path: Path) -> None:
    if not path.exists():
        raise SystemExit(f"missing required file: {path}")


def require_executable(command: str | Path) -> str:
    value = str(command)
    if Path(value).is_file() and os.access(value, os.X_OK):
        return value
    resolved = shutil.which(value)
    if not resolved:
        raise SystemExit(f"missing executable: {value}")
    return resolved


def font(size: int, mono: bool = False) -> ImageFont.ImageFont:
    candidates = (
        ["/System/Library/Fonts/SFNSMono.ttf", "/System/Library/Fonts/Menlo.ttc"]
        if mono
        else [
            "/System/Library/Fonts/Avenir.ttc",
            "/System/Library/Fonts/HelveticaNeue.ttc",
            "/System/Library/Fonts/SFNS.ttf",
        ]
    )
    for candidate in candidates:
        if Path(candidate).exists():
            try:
                return ImageFont.truetype(candidate, size=size)
            except OSError:
                pass
    return ImageFont.load_default()


def wrap(draw: ImageDraw.ImageDraw, text: str, fnt: ImageFont.ImageFont, width: int) -> list[str]:
    words = text.split()
    lines: list[str] = []
    line = ""
    for word in words:
        trial = f"{line} {word}".strip()
        bbox = draw.textbbox((0, 0), trial, font=fnt)
        if bbox[2] - bbox[0] <= width or not line:
            line = trial
        else:
            lines.append(line)
            line = word
    if line:
        lines.append(line)
    return lines


def draw_wrapped(draw: ImageDraw.ImageDraw, text: str, xy: tuple[int, int], fnt: ImageFont.ImageFont, fill, width: int, line_gap: int = 8, max_lines: int | None = None) -> int:
    x, y = xy
    lines = wrap(draw, text, fnt, width)
    if max_lines is not None:
        lines = lines[:max_lines]
    line_height = fnt.size + line_gap if hasattr(fnt, "size") else 24
    for line in lines:
        draw.text((x, y), line, font=fnt, fill=fill)
        y += line_height
    return y


def scene_duration(path: Path) -> float:
    with wave.open(str(path), "rb") as wav:
        return wav.getnframes() / float(wav.getframerate())


def synthesize_voiceover(out: Path) -> list[dict]:
    piper = require_executable(PIPER_BIN)
    require_file(PIPER_MODEL)
    require_file(PIPER_CONFIG)
    voice_dir = ensure_dir(out / "voiceover")
    timings = []
    cursor = 0.0
    first_params = None
    combined = voice_dir / "latticra-proof-object-4-voiceover.wav"
    with wave.open(str(combined), "wb") as out_wav:
        for scene in SCENES:
            text_path = voice_dir / f"scene-{scene.scene_id}.txt"
            wav_path = voice_dir / f"scene-{scene.scene_id}.wav"
            text_path.write_text(clean_text(scene.narration) + "\n", encoding="utf-8")
            subprocess.run(
                [
                    piper,
                    "--model",
                    str(PIPER_MODEL),
                    "--config",
                    str(PIPER_CONFIG),
                    "--input-file",
                    str(text_path),
                    "--output-file",
                    str(wav_path),
                    "--sentence-silence",
                    "0.22",
                    "--length-scale",
                    "1.02",
                ],
                check=True,
            )
            with wave.open(str(wav_path), "rb") as in_wav:
                params = in_wav.getparams()
                frames = in_wav.readframes(in_wav.getnframes())
            if first_params is None:
                first_params = params
                out_wav.setparams(params)
            elif params[:3] != first_params[:3]:
                raise SystemExit("piper wave parameters changed across scenes")
            audio = scene_duration(wav_path)
            duration = max(24.0, audio + 1.5)
            out_wav.writeframes(frames)
            pad_frames = int(round((duration - audio) * params.framerate))
            if pad_frames > 0:
                out_wav.writeframes(b"\x00" * pad_frames * params.nchannels * params.sampwidth)
            timings.append({"id": scene.scene_id, "start": cursor, "duration": duration, "audio": audio})
            cursor += duration
    return timings


def srt_time(seconds: float) -> str:
    millis = int(round(seconds * 1000))
    ms = millis % 1000
    total = millis // 1000
    sec = total % 60
    minute = (total // 60) % 60
    hour = total // 3600
    return f"{hour:02d}:{minute:02d}:{sec:02d},{ms:03d}"


def write_story_artifacts(out: Path, timings: list[dict]) -> None:
    script = out / "voiceover-script.txt"
    srt = out / "voiceover-cues.srt"
    storyboard = out / "storyboard.json"
    script.write_text(
        "\n\n".join(
            [f"Latticra Proof Object 4: Identity-Replay Impedance and Higgs Counterplay"]
            + [f"{scene.kicker}: {clean_text(scene.narration)}" for scene in SCENES]
        )
        + "\n",
        encoding="utf-8",
    )
    srt_lines = []
    for index, (scene, timing) in enumerate(zip(SCENES, timings), start=1):
        srt_lines.extend(
            [
                str(index),
                f"{srt_time(timing['start'])} --> {srt_time(timing['start'] + timing['duration'])}",
                scene.claim,
                "",
            ]
        )
    srt.write_text("\n".join(srt_lines), encoding="utf-8")
    storyboard.write_text(
        json.dumps(
            {
                "title": "Latticra Proof Object 4",
                "claim": "Mass can be modeled as identity-replay impedance: the replay-stable cost for a projected localized identity to remain itself under substrate update.",
                "simulation_proven": 0,
                "scientific_claim_promoted": 0,
                "identity_replay_impedance_defined": 1,
                "higgs_existence_denied": 0,
                "higgs_final_causal_closure_refuted": 1,
                "scenes": [
                    {
                        "id": scene.scene_id,
                        "kicker": scene.kicker,
                        "claim": scene.claim,
                        "formula": list(scene.formula),
                        "bullets": list(scene.bullets),
                        "timing": timing,
                    }
                    for scene, timing in zip(SCENES, timings)
                ],
            },
            indent=2,
        ),
        encoding="utf-8",
    )


def background(scene: Scene, progress: float) -> Image.Image:
    w, h = SIZE
    image = Image.new("RGB", SIZE, (5, 8, 13))
    draw = ImageDraw.Draw(image)
    for y in range(h):
        t = y / h
        r = int(5 + 10 * t)
        g = int(8 + 16 * t)
        b = int(13 + 24 * t)
        draw.line((0, y, w, y), fill=(r, g, b))
    for i in range(140):
        x = int((math.sin(i * 12.989 + progress * 8.0) * 43758.5453 % 1) * w)
        y = int((math.sin(i * 78.233 + len(scene.claim)) * 24634.6345 % 1) * h)
        color = (60 + (i * 7) % 160, 180 + (i * 3) % 70, 170 + (i * 5) % 80)
        draw.ellipse((x - 1, y - 1, x + 1, y + 1), fill=color)
    return image


def draw_network(draw: ImageDraw.ImageDraw, scene: Scene, progress: float) -> None:
    cx, cy = 350, 385
    nodes = []
    for layer in range(4):
        count = layer + 2
        radius = 55 + layer * 52
        for index in range(count):
            angle = -math.pi / 2 + index * (math.tau / count) + layer * 0.28
            x = cx + math.cos(angle) * radius
            y = cy + math.sin(angle) * radius * 0.72
            nodes.append((x, y, layer, index))
    for a in nodes:
        for b in nodes:
            if b[2] == a[2] + 1 and (a[3] + b[3] + len(scene.mode)) % 2 == 0:
                draw.line((a[0], a[1], b[0], b[1]), fill=(75, 210, 190, 80), width=2)
    pulse = int(progress * len(nodes)) % max(1, len(nodes))
    for idx, (x, y, layer, _) in enumerate(nodes):
        r = 7 if idx == pulse else 5
        color = (244, 205, 93) if idx == pulse else (120, 230, 210)
        draw.ellipse((x - r, y - r, x + r, y + r), fill=color, outline=(255, 255, 255))
    if scene.mode in {"physics", "derivation"}:
        draw.arc((140, 190, 560, 570), 205, 337, fill=(245, 93, 93), width=4)
    if scene.mode == "qed":
        draw.rectangle((128, 604, 575, 635), outline=(183, 255, 106), width=3)
        draw.text((145, 602), "QED: proof shape established", font=font(25, mono=True), fill=(215, 255, 185))


def draw_scene(scene: Scene, local: float, elapsed: float, total: float) -> Image.Image:
    image = background(scene, elapsed / max(1.0, total))
    draw = ImageDraw.Draw(image, "RGBA")
    w, h = SIZE
    draw.rounded_rectangle((32, 32, w - 32, h - 32), radius=12, outline=(95, 225, 205, 120), width=2)
    draw.text((62, 58), scene.kicker, font=font(24), fill=(183, 255, 106, 255))
    draw_wrapped(draw, scene.claim, (62, 98), font(42), (245, 241, 230, 255), 1120, line_gap=6, max_lines=2)
    draw_network(draw, scene, local)

    formula_x, formula_y = 640, 245
    draw.rounded_rectangle((formula_x - 20, formula_y - 22, 1205, 420), radius=10, fill=(3, 6, 10, 175), outline=(119, 215, 255, 120), width=2)
    draw.text((formula_x, formula_y - 2), "formal surface", font=font(20), fill=(119, 215, 255, 235))
    y = formula_y + 38
    for item in scene.formula:
        draw.text((formula_x, y), item, font=font(22, mono=True), fill=(248, 213, 123, 255))
        y += 39

    bullet_x, bullet_y = 640, 455
    draw.text((bullet_x, bullet_y - 34), "proof obligations", font=font(20), fill=(183, 255, 106, 235))
    for bullet in scene.bullets:
        draw.ellipse((bullet_x, bullet_y + 9, bullet_x + 9, bullet_y + 18), fill=(183, 255, 106, 230))
        bullet_y = draw_wrapped(draw, bullet, (bullet_x + 24, bullet_y), font(23), (232, 239, 230, 245), 560, line_gap=5, max_lines=2) + 9

    bar_w = int((w - 124) * min(1.0, elapsed / total))
    draw.rectangle((62, h - 68, 62 + bar_w, h - 61), fill=(183, 255, 106, 230))
    draw.text((62, h - 51), "identity_replay_impedance=1  |  higgs_denied=0  |  simulation_proven=0", font=font(17, mono=True), fill=(180, 201, 207, 230))
    return image


def render_video(out: Path, timings: list[dict]) -> Path:
    ffmpeg = require_executable(FFMPEG_BIN)
    video_path = ensure_dir(out / "video") / "latticra-proof-object-4-identity-replay-impedance.mp4"
    voiceover = out / "voiceover/latticra-proof-object-4-voiceover.wav"
    total = sum(item["duration"] for item in timings)
    command = [
        ffmpeg,
        "-y",
        "-f",
        "rawvideo",
        "-pix_fmt",
        "rgb24",
        "-s",
        f"{SIZE[0]}x{SIZE[1]}",
        "-r",
        str(FPS),
        "-i",
        "-",
        "-i",
        str(voiceover),
        "-c:v",
        "libx264",
        "-profile:v",
        "high",
        "-level:v",
        "4.0",
        "-preset",
        "veryfast",
        "-crf",
        "18",
        "-pix_fmt",
        "yuv420p",
        "-c:a",
        "aac",
        "-b:a",
        "160k",
        "-shortest",
        "-movflags",
        "+faststart",
        str(video_path),
    ]
    proc = subprocess.Popen(command, stdin=subprocess.PIPE)
    assert proc.stdin is not None
    frame_cursor = 0
    try:
        for scene, timing in zip(SCENES, timings):
            frames = int(math.ceil(timing["duration"] * FPS))
            for frame_index in range(frames):
                local = frame_index / max(1, frames - 1)
                elapsed = frame_cursor / FPS
                frame = draw_scene(scene, local, elapsed, total)
                proc.stdin.write(frame.tobytes())
                frame_cursor += 1
                if frame_cursor % FPS == 0:
                    print(f"rendering {frame_cursor // FPS:03d}/{math.ceil(total)} seconds", file=sys.stderr)
        proc.stdin.close()
        rc = proc.wait()
    finally:
        if proc.stdin and not proc.stdin.closed:
            proc.stdin.close()
    if rc:
        raise SystemExit(f"ffmpeg exited with {rc}")
    return video_path


def main() -> int:
    require_executable(FFMPEG_BIN)
    require_executable(FFPROBE_BIN)
    ensure_dir(OUT)
    timings = synthesize_voiceover(OUT)
    write_story_artifacts(OUT, timings)
    video = render_video(OUT, timings)
    manifest = {
        "latticra_proof_object_4_rendered": 1,
        "video": str(video),
        "voiceover": str(OUT / "voiceover/latticra-proof-object-4-voiceover.wav"),
        "captions": str(OUT / "voiceover-cues.srt"),
        "duration_seconds": sum(item["duration"] for item in timings),
        "simulation_proven": 0,
        "scientific_claim_promoted": 0,
        "identity_replay_impedance_defined": 1,
        "higgs_existence_denied": 0,
        "higgs_final_causal_closure_refuted": 1,
        "postable_claim": "Latticra introduces identity-replay impedance: mass as replay-stable projected identity cost, with Higgs treated as effective physics that must pass a coupling-shadow test.",
    }
    (OUT / "render-manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    print(json.dumps(manifest, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

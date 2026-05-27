#!/usr/bin/env python3
"""Render the Latticra academic presentation from a timed storyboard.

The renderer deliberately separates production concerns:

* TOML carries the academic story, scene timing, and complete narration.
* Pillow renders readable 16:9 frames with real fonts and bounded text boxes.
* Piper, when configured, produces scene-level voiceover WAV files.
* ffmpeg, when available, receives raw RGB frames and the voiceover track.
"""

from __future__ import annotations

import argparse
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
from typing import Iterable

try:
    import tomllib
except ModuleNotFoundError:  # pragma: no cover - this script targets Python 3.11+.
    tomllib = None

try:
    from PIL import Image, ImageDraw, ImageFont
except ModuleNotFoundError as exc:  # pragma: no cover - handled for operator clarity.
    raise SystemExit(
        "Pillow is required. Use scripts/render-latticra-academic-presentation.sh "
        "or run with the bundled Codex Python runtime."
    ) from exc


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CONFIG = ROOT / "presentations/latticra-academic/latticra_academic_presentation.toml"
DEFAULT_OUT = ROOT / "build/presentation/latticra-academic"
DEFAULT_SIZE = (1920, 1080)
DEFAULT_FPS = 24


@dataclass(frozen=True)
class Scene:
    index: int
    scene_id: str
    kicker: str
    claim: str
    layout: str
    duration: float
    caption: str
    proof: str
    terms: tuple[str, ...]
    bullets: tuple[str, ...]
    narration: str
    start: float = 0.0


def clean_text(value: str) -> str:
    return " ".join(value.strip().split())


def word_count(value: str) -> int:
    return len([part for part in value.replace("/", " ").split() if part.strip()])


def load_storyboard(path: Path) -> tuple[dict, list[Scene]]:
    if tomllib is None:
        raise SystemExit("Python 3.11 or newer is required for TOML storyboard loading.")
    with path.open("rb") as fh:
        data = tomllib.load(fh)

    meta = dict(data.get("meta", {}))
    scenes: list[Scene] = []
    start = 0.0
    for idx, raw in enumerate(data.get("scene", []), start=1):
        duration = float(raw["duration"])
        scene = Scene(
            index=idx,
            scene_id=str(raw["id"]),
            kicker=str(raw["kicker"]),
            claim=str(raw["claim"]),
            layout=str(raw["layout"]),
            duration=duration,
            caption=clean_text(str(raw["caption"])),
            proof=clean_text(str(raw["proof"])),
            terms=tuple(str(term) for term in raw.get("terms", [])),
            bullets=tuple(clean_text(str(item)) for item in raw.get("bullets", [])),
            narration=clean_text(str(raw["narration"])),
            start=start,
        )
        scenes.append(scene)
        start += duration
    return meta, scenes


def validate_storyboard(meta: dict, scenes: list[Scene]) -> list[str]:
    errors: list[str] = []
    if not scenes:
        errors.append("storyboard has no scenes")
    target = float(meta.get("target_seconds", 720))
    total = sum(scene.duration for scene in scenes)
    if total < target:
        errors.append(f"scene duration total {total:.1f}s is below target {target:.1f}s")
    if len(scenes) < 8:
        errors.append("academic deck should have at least 8 scenes")
    total_words = sum(word_count(scene.narration) for scene in scenes)
    if total_words < 1400:
        errors.append(f"voiceover has only {total_words} words; expected a full 720s script")
    for scene in scenes:
        if word_count(scene.narration) < 90:
            errors.append(f"scene {scene.scene_id} narration is too thin")
        joined = " ".join([scene.claim, scene.caption, scene.proof, scene.narration])
        if "todo" in joined.lower() or "placeholder" in joined.lower():
            errors.append(f"scene {scene.scene_id} contains placeholder language")
        if not scene.bullets:
            errors.append(f"scene {scene.scene_id} has no visible bullet spine")
        if not scene.terms:
            errors.append(f"scene {scene.scene_id} has no technical term rail")
    return errors


def ensure_dir(path: Path) -> Path:
    path.mkdir(parents=True, exist_ok=True)
    return path


def srt_timestamp(seconds: float) -> str:
    millis = int(round(seconds * 1000))
    ms = millis % 1000
    total_seconds = millis // 1000
    sec = total_seconds % 60
    minutes = (total_seconds // 60) % 60
    hours = total_seconds // 3600
    return f"{hours:02d}:{minutes:02d}:{sec:02d},{ms:03d}"


def write_story_artifacts(meta: dict, scenes: list[Scene], out_dir: Path) -> dict:
    ensure_dir(out_dir)
    script_path = out_dir / "voiceover-script.txt"
    srt_path = out_dir / "voiceover-cues.srt"
    json_path = out_dir / "storyboard.json"
    piper_text_dir = ensure_dir(out_dir / "piper-scenes")

    script_lines = [
        str(meta.get("title", "Latticra academic presentation")),
        str(meta.get("subtitle", "")),
        "",
        f"Target duration: {sum(scene.duration for scene in scenes):.0f} seconds",
        f"Voice style: {meta.get('voice_style', 'measured technical narration')}",
        "",
    ]
    srt_lines: list[str] = []
    storyboard = {
        "title": meta.get("title"),
        "subtitle": meta.get("subtitle"),
        "target_seconds": meta.get("target_seconds"),
        "total_seconds": sum(scene.duration for scene in scenes),
        "scene_count": len(scenes),
        "word_count": sum(word_count(scene.narration) for scene in scenes),
        "scenes": [],
    }

    for cue_index, scene in enumerate(scenes, start=1):
        start = scene.start
        end = scene.start + scene.duration
        script_lines.extend(
            [
                f"Scene {scene.scene_id}: {scene.kicker}",
                f"Claim: {scene.claim}",
                f"Timing: {srt_timestamp(start)} --> {srt_timestamp(end)}",
                "",
                textwrap.fill(scene.narration, width=88),
                "",
            ]
        )
        srt_lines.extend(
            [
                str(cue_index),
                f"{srt_timestamp(start)} --> {srt_timestamp(end)}",
                textwrap.fill(scene.narration, width=72),
                "",
            ]
        )
        (piper_text_dir / f"scene-{scene.scene_id}.txt").write_text(scene.narration + "\n", encoding="utf-8")
        storyboard["scenes"].append(
            {
                "id": scene.scene_id,
                "index": scene.index,
                "kicker": scene.kicker,
                "claim": scene.claim,
                "layout": scene.layout,
                "start": start,
                "duration": scene.duration,
                "caption": scene.caption,
                "proof": scene.proof,
                "terms": list(scene.terms),
                "bullets": list(scene.bullets),
                "narration_word_count": word_count(scene.narration),
            }
        )

    script_path.write_text("\n".join(script_lines), encoding="utf-8")
    srt_path.write_text("\n".join(srt_lines), encoding="utf-8")
    json_path.write_text(json.dumps(storyboard, indent=2), encoding="utf-8")
    return {
        "script": str(script_path),
        "srt": str(srt_path),
        "storyboard": str(json_path),
        "piper_text_dir": str(piper_text_dir),
    }


class FontBook:
    def __init__(self) -> None:
        self.paths = {
            "display": self._first_existing(
                "/System/Library/Fonts/NewYork.ttf",
                "/System/Library/Fonts/Supplemental/Iowan Old Style.ttc",
                "/System/Library/Fonts/Supplemental/Georgia.ttf",
            ),
            "sans": self._first_existing(
                "/System/Library/Fonts/Avenir.ttc",
                "/System/Library/Fonts/SFNS.ttf",
                "/System/Library/Fonts/HelveticaNeue.ttc",
            ),
            "mono": self._first_existing(
                "/System/Library/Fonts/SFNSMono.ttf",
                "/System/Library/Fonts/Menlo.ttc",
                "/System/Library/Fonts/Supplemental/Courier New.ttf",
            ),
        }
        self._cache: dict[tuple[str, int], ImageFont.FreeTypeFont | ImageFont.ImageFont] = {}

    @staticmethod
    def _first_existing(*paths: str) -> str | None:
        for item in paths:
            if Path(item).exists():
                return item
        return None

    def get(self, family: str, size: int) -> ImageFont.FreeTypeFont | ImageFont.ImageFont:
        key = (family, size)
        if key in self._cache:
            return self._cache[key]
        path = self.paths.get(family) or self.paths.get("sans")
        if path:
            try:
                font = ImageFont.truetype(path, size=size)
            except OSError:
                font = ImageFont.load_default()
        else:
            font = ImageFont.load_default()
        self._cache[key] = font
        return font


def rgb(hex_value: str) -> tuple[int, int, int]:
    value = hex_value.strip().lstrip("#")
    return tuple(int(value[i : i + 2], 16) for i in (0, 2, 4))


def mix(a: tuple[int, int, int], b: tuple[int, int, int], t: float) -> tuple[int, int, int]:
    return tuple(int(a[i] + (b[i] - a[i]) * t) for i in range(3))


PALETTE = [
    ("#b7ff6a", "#24d6a3"),
    ("#f7c45d", "#f15c5c"),
    ("#77d7ff", "#7d88ff"),
    ("#f5a6ff", "#72f2d7"),
    ("#ffe38a", "#71d6ff"),
    ("#ff8f70", "#b8ff70"),
    ("#b9a8ff", "#66e6a3"),
    ("#ffd36a", "#a8d8ff"),
    ("#72f2d7", "#ff75a0"),
    ("#a8d8ff", "#f7c45d"),
    ("#e7e1d2", "#77d7ff"),
    ("#d2ff72", "#ff8f70"),
]


class ProductionRenderer:
    def __init__(self, width: int, height: int, fps: int) -> None:
        self.width = width
        self.height = height
        self.fps = fps
        self.fonts = FontBook()
        self.margin_x = max(72, int(width * 0.055))
        self.margin_y = max(48, int(height * 0.055))
        self.background_cache: dict[int, Image.Image] = {}
        self.static_cache: dict[tuple[int, str], Image.Image] = {}

    def scaled(self, value: int) -> int:
        return max(1, round(value * self.width / 1920))

    def font(self, family: str, size: int) -> ImageFont.FreeTypeFont | ImageFont.ImageFont:
        return self.fonts.get(family, self.scaled(size))

    def accent(self, scene: Scene) -> tuple[tuple[int, int, int], tuple[int, int, int]]:
        pair = PALETTE[(scene.index - 1) % len(PALETTE)]
        return rgb(pair[0]), rgb(pair[1])

    def base_background(self, scene: Scene) -> Image.Image:
        if scene.index in self.background_cache:
            return self.background_cache[scene.index]
        a, b = self.accent(scene)
        top = rgb("#07090d")
        bottom = mix(rgb("#10151d"), b, 0.10)
        image = Image.new("RGB", (self.width, self.height), top)
        draw = ImageDraw.Draw(image)
        for y in range(self.height):
            t = y / max(1, self.height - 1)
            col = mix(top, bottom, t)
            draw.line((0, y, self.width, y), fill=col)

        for i in range(220):
            x = int((math.sin(i * 12.9898 + scene.index) * 43758.5453 % 1.0) * self.width)
            y = int((math.sin(i * 78.233 + scene.index * 3.1) * 24634.6345 % 1.0) * self.height)
            alpha = 30 + (i * 17) % 70
            color = mix(a, rgb("#ffffff"), 0.45)
            draw.point((x, y), fill=tuple(min(255, c * alpha // 90) for c in color))

        mono = self.font("mono", 13)
        for col in range(0, self.scaled(78), self.scaled(18)):
            for row in range(0, self.height, self.scaled(24)):
                bit = "1" if ((row // max(1, self.scaled(24)) + col + scene.index) % 3 == 0) else "0"
                draw.text((self.scaled(10) + col, row), bit, font=mono, fill=(*mix(a, b, 0.3), 28))
        frame = (self.scaled(34), self.scaled(34), self.width - self.scaled(34), self.height - self.scaled(34))
        draw.rounded_rectangle(frame, radius=self.scaled(12), outline=(*mix(a, b, 0.45), 74), width=self.scaled(2))
        self.background_cache[scene.index] = image
        return image

    def render_frame(self, scene: Scene, local_progress: float, total_progress: float, elapsed: float, total: float) -> Image.Image:
        image = self.base_background(scene).copy().convert("RGBA")
        self.draw_lattice_field(image, scene, local_progress)
        key = (scene.index, f"{self.width}x{self.height}")
        if key not in self.static_cache:
            layer = Image.new("RGBA", (self.width, self.height), (0, 0, 0, 0))
            self.draw_static_scene(layer, scene)
            self.static_cache[key] = layer
        image.alpha_composite(self.static_cache[key])
        self.draw_scene_motion(image, scene, local_progress)
        self.draw_dynamic_footer(image, scene, local_progress, total_progress, elapsed, total)
        return image.convert("RGB")

    def draw_lattice_field(self, image: Image.Image, scene: Scene, p: float) -> None:
        draw = ImageDraw.Draw(image, "RGBA")
        a, b = self.accent(scene)
        nodes = []
        cols, rows = 9, 5
        x0, x1 = int(self.width * 0.08), int(self.width * 0.92)
        y0, y1 = int(self.height * 0.16), int(self.height * 0.82)
        for row in range(rows):
            for col in range(cols):
                base_x = x0 + (x1 - x0) * col / (cols - 1)
                base_y = y0 + (y1 - y0) * row / (rows - 1)
                phase = scene.index * 0.41 + row * 0.7 + col * 0.33
                x = base_x + math.sin(p * math.tau + phase) * self.scaled(10)
                y = base_y + math.cos(p * math.tau * 0.7 + phase) * self.scaled(7)
                nodes.append((x, y, row, col))
        for x, y, row, col in nodes:
            if col < cols - 1:
                target = next(n for n in nodes if n[2] == row and n[3] == col + 1)
                color = (*mix(a, b, (row + col) / (rows + cols)), 28)
                draw.line((x, y, target[0], target[1]), fill=color, width=self.scaled(1))
            if row < rows - 1 and (row + col + scene.index) % 2 == 0:
                target = next(n for n in nodes if n[2] == row + 1 and n[3] == col)
                draw.line((x, y, target[0], target[1]), fill=(*mix(b, a, 0.4), 20), width=self.scaled(1))
        pulse_index = int(p * len(nodes)) % len(nodes)
        for idx, (x, y, row, col) in enumerate(nodes):
            dist = min(abs(idx - pulse_index), len(nodes) - abs(idx - pulse_index))
            alpha = max(24, 115 - dist * 18)
            radius = self.scaled(2 + (1 if idx == pulse_index else 0))
            draw.ellipse((x - radius, y - radius, x + radius, y + radius), fill=(*mix(a, b, row / max(1, rows - 1)), alpha))

    def draw_scene_motion(self, image: Image.Image, scene: Scene, p: float) -> None:
        draw = ImageDraw.Draw(image, "RGBA")
        a, b = self.accent(scene)
        left = self.margin_x
        right = self.width - self.margin_x
        top = int(self.height * 0.23)
        bottom = int(self.height * 0.78)
        phase = (math.sin(p * math.tau) + 1.0) * 0.5
        col = mix(a, b, phase)

        if scene.layout in {"theorem_cover", "qed"}:
            cx = right - self.scaled(270) if scene.layout == "theorem_cover" else (left + right) // 2
            cy = top + self.scaled(245)
            for idx in range(4):
                r = self.scaled(54 + idx * 42) + int(math.sin(p * math.tau + idx) * self.scaled(5))
                draw.ellipse((cx - r, cy - r, cx + r, cy + r), outline=(*mix(a, b, idx / 3), 64), width=self.scaled(2))

        elif scene.layout in {"poset_lattice", "meet_join"}:
            points = [
                (left + self.scaled(390), top + self.scaled(480)),
                (left + self.scaled(290), top + self.scaled(315)),
                (left + self.scaled(390), top + self.scaled(250)),
                (left + self.scaled(490), top + self.scaled(315)),
                (left + self.scaled(390), top + self.scaled(75)),
            ]
            if scene.layout == "meet_join":
                mid = (left + right) // 2
                points = [(mid, top + self.scaled(455)), (mid - self.scaled(95), top + self.scaled(312)), (mid, top + self.scaled(250)), (mid + self.scaled(95), top + self.scaled(312)), (mid, top + self.scaled(45))]
            seg = min(len(points) - 2, int(p * (len(points) - 1)))
            local = p * (len(points) - 1) - seg
            x0, y0 = points[seg]
            x1, y1 = points[seg + 1]
            x = x0 + (x1 - x0) * local
            y = y0 + (y1 - y0) * local
            draw.ellipse((x - self.scaled(10), y - self.scaled(10), x + self.scaled(10), y + self.scaled(10)), fill=(*col, 210))

        elif scene.layout == "powerset_lattice":
            x0 = left + self.scaled(210)
            x1 = left + self.scaled(650)
            y = top + self.scaled(438 - 330 * p)
            draw.line((x0, y, x1, y), fill=(*col, 125), width=self.scaled(2))

        elif scene.layout == "effect_semiring":
            effects = 5
            y = top + self.scaled(214)
            x0 = left + self.scaled(40)
            gap = self.scaled(32)
            cell_w = (right - left - self.scaled(80) - gap * (effects - 1)) // effects
            idxf = p * (effects - 1)
            idx = int(idxf)
            local = idxf - idx
            x = x0 + idx * (cell_w + gap) + cell_w // 2 + local * (cell_w + gap)
            draw.ellipse((x - self.scaled(13), y - self.scaled(13), x + self.scaled(13), y + self.scaled(13)), outline=(*col, 230), width=self.scaled(3))

        elif scene.layout == "hyperlattice":
            origin_x = left + self.scaled(230)
            origin_y = bottom - self.scaled(130)
            x = origin_x + self.scaled(55 + 355 * p)
            y = origin_y - self.scaled(45 + 270 * p)
            draw.line((origin_x, origin_y, x, y), fill=(*col, 155), width=self.scaled(3))
            draw.ellipse((x - self.scaled(11), y - self.scaled(11), x + self.scaled(11), y + self.scaled(11)), fill=(*col, 210))

        elif scene.layout == "simulation_tick":
            y = top + self.scaled(241)
            x0 = left
            x1 = right
            x = x0 + (x1 - x0) * p
            draw.ellipse((x - self.scaled(12), y - self.scaled(12), x + self.scaled(12), y + self.scaled(12)), fill=(*col, 220))

        elif scene.layout == "chains":
            x0 = left + self.scaled(90)
            spacing = (right - left - self.scaled(180)) // 6
            x = x0 + spacing * 6 * p
            y = top + self.scaled(210)
            draw.ellipse((x - self.scaled(12), y - self.scaled(12), x + self.scaled(12), y + self.scaled(12)), fill=(*col, 220))

        elif scene.layout == "fixpoint":
            cx = left + self.scaled(455)
            cy = top + self.scaled(255)
            r = self.scaled(180 - 145 * p)
            angle = p * math.tau * 2.2
            x = cx + math.cos(angle) * r
            y = cy + math.sin(angle) * r
            draw.line((x, y, cx, cy), fill=(*col, 95), width=self.scaled(2))
            draw.ellipse((x - self.scaled(9), y - self.scaled(9), x + self.scaled(9), y + self.scaled(9)), fill=(*col, 220))

        elif scene.layout == "abstraction_tower":
            cx = left + self.scaled(360)
            y0 = bottom - self.scaled(120)
            y = y0 - self.scaled(300 * p)
            draw.line((cx + self.scaled(330), y0, cx + self.scaled(330), y), fill=(*col, 150), width=self.scaled(3))

        elif scene.layout == "trace_matrix":
            y0 = top + self.scaled(136)
            row_h = self.scaled(58)
            row = min(3, int(p * 4))
            y = y0 + (row + 1) * row_h
            draw.rectangle((left, y, right, y + row_h), outline=(*col, 220), width=self.scaled(3))

    def scene_formulas(self, scene: Scene) -> tuple[str, ...]:
        formulas: dict[str, tuple[str, ...]] = {
            "theorem_cover": (
                "Theorem: guarded monotone simulation",
                "h = (l, e, t)",
                "T(h) defined only under gate(e)",
                "Trace = ordered evidence, not decoration",
                "0_L <= l <= 1_L",
            ),
            "poset_lattice": (
                "x <= y means y contains x",
                "reflexive: x <= x",
                "antisymmetric: x <= y <= x => x = y",
                "transitive: x <= y <= z => x <= z",
                "cover relation = edge on the Hasse diagram",
            ),
            "meet_join": (
                "a meet b = glb(a,b)",
                "a join b = lub(a,b)",
                "meet removes unsupported excess",
                "join accumulates controlled evidence",
                "absorption: a join (a meet b) = a",
            ),
            "powerset_lattice": (
                "P(X) ordered by subset inclusion",
                "A meet B = A intersect B",
                "A join B = A union B",
                "evidence atoms: parse, span, LIR, gate",
                "bottom = empty evidence",
            ),
            "effect_semiring": (
                "0_E = no-effect report",
                "e_i + e_j = combined authority surface",
                "e_i * e_j = sequential effect",
                "requested <= admitted",
                "denial is still trace evidence",
            ),
            "hyperlattice": (
                "H = L x E x Tau",
                "(l,e,t) <= (l',e',t') componentwise",
                "representation, effect, time stay coupled",
                "projection_L(h) = l",
                "projection_E(h) = e",
            ),
            "simulation_tick": (
                "tick_i: h_i -> h_{i+1}",
                "valid iff h_i <= h_{i+1}",
                "gate(effect_i) = allow",
                "else Trace += refusal",
                "no hidden mutation path",
            ),
            "chains": (
                "h0 <= h1 <= h2 <= ...",
                "directed chain accumulates evidence",
                "lub chain = least containing state",
                "complete lattices admit limits",
                "limit != guess; limit = order-theoretic bound",
            ),
            "fixpoint": (
                "T(x*) = x*",
                "iterate: bottom, T(bottom), T^2(bottom), ...",
                "least fixed point when hypotheses hold",
                "stability = no new representation",
                "gate remains part of T",
            ),
            "abstraction_tower": (
                "pi_i : L_{i+1} -> L_i",
                "x <= y => pi_i(x) <= pi_i(y)",
                "abstraction is rule-bound loss",
                "authority must survive projection",
                "explanation is a monotone image",
            ),
            "trace_matrix": (
                "frame_i = projection(trace_i)",
                "delta_i records evidence change",
                "gate_i records authority outcome",
                "operation_i is read through state and effect",
                "simulation becomes reviewable",
            ),
            "qed": (
                "Latticra = (L, E, T, Trace)",
                "L supplies order and lattice operations",
                "E supplies explicit authority",
                "T supplies guarded dynamics",
                "Trace supplies inspectability",
            ),
        }
        return formulas.get(scene.layout, tuple(scene.terms))

    def draw_formula_cloud(self, image: Image.Image, scene: Scene) -> None:
        draw = ImageDraw.Draw(image, "RGBA")
        a, b = self.accent(scene)
        formulas = self.scene_formulas(scene)
        if not formulas:
            return

        font = self.font("mono", 18)
        small = self.font("mono", 14)
        left = self.scaled(92)
        right = self.width - self.scaled(92)
        top = int(self.height * 0.19)
        if scene.layout == "trace_matrix":
            positions = [
                (left, top),
                (right - self.scaled(470), top + self.scaled(12)),
                (left + self.scaled(560), self.scaled(652)),
            ]
            formulas = formulas[: len(positions)]
        elif scene.layout in {"theorem_cover", "poset_lattice"}:
            positions = [
                (left, top),
                (right - self.scaled(470), top + self.scaled(12)),
            ]
            formulas = formulas[: len(positions)]
        else:
            positions = [
                (left, top),
                (right - self.scaled(470), top + self.scaled(12)),
                (right - self.scaled(520), top + self.scaled(392)),
            ]
        for idx, formula in enumerate(formulas[: len(positions)]):
            x, y = positions[idx]
            col = mix(a, b, idx / max(1, len(positions) - 1))
            box_w = self.scaled(430 if idx % 2 == 0 else 480)
            box_h = self.scaled(38)
            draw.rounded_rectangle((x - self.scaled(12), y - self.scaled(8), x + box_w, y + box_h), radius=self.scaled(6), fill=(*rgb("#05090d"), 32), outline=(*col, 34), width=self.scaled(1))
            self.draw_fit_line(draw, formula, x, y, box_w - self.scaled(18), font if idx < 2 else small, (*mix(col, rgb("#ffffff"), 0.28), 64))

        proof_marks = ["meet", "join", "gate", "trace", "QED"]
        for idx, mark in enumerate(proof_marks):
            x = self.scaled(114 + idx * 185)
            y = self.height - self.scaled(100 + (idx % 2) * 22)
            col = mix(a, b, idx / max(1, len(proof_marks) - 1))
            draw.text((x, y), mark.upper(), font=small, fill=(*col, 30))

    def draw_static_scene(self, layer: Image.Image, scene: Scene) -> None:
        draw = ImageDraw.Draw(layer, "RGBA")
        a, b = self.accent(scene)
        ink = rgb("#f6f2e8")
        muted = rgb("#b7c0c5")
        self.draw_header(draw, scene, a, b, ink)

        left = self.margin_x
        top = int(self.height * 0.23)
        right = self.width - self.margin_x
        bottom = int(self.height * 0.78)
        layout = scene.layout
        if layout == "theorem_cover":
            self.layout_theorem_cover(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "poset_lattice":
            self.layout_poset_lattice(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "meet_join":
            self.layout_meet_join(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "powerset_lattice":
            self.layout_powerset_lattice(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "effect_semiring":
            self.layout_effect_semiring(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "hyperlattice":
            self.layout_hyperlattice(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "simulation_tick":
            self.layout_simulation_tick(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "chains":
            self.layout_chains(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "fixpoint":
            self.layout_fixpoint(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "abstraction_tower":
            self.layout_abstraction_tower(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "trace_matrix":
            self.layout_trace_matrix(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "qed":
            self.layout_qed(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "cover":
            self.layout_cover(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "problem":
            self.layout_problem(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "pipeline":
            self.layout_pipeline(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "lattice":
            self.layout_lattice(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "ui_report":
            self.layout_ui_report(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "authority":
            self.layout_authority(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "seal":
            self.layout_seal(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "kernel":
            self.layout_kernel(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "visual_engine":
            self.layout_visual_engine(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "delivery":
            self.layout_delivery(draw, scene, left, top, right, bottom, a, b, ink, muted)
        elif layout == "research":
            self.layout_research(draw, scene, left, top, right, bottom, a, b, ink, muted)
        else:
            self.layout_closing(draw, scene, left, top, right, bottom, a, b, ink, muted)

        self.draw_term_rail(draw, scene, left, int(self.height * 0.805), right, a, b, muted)

    def draw_header(self, draw: ImageDraw.ImageDraw, scene: Scene, a: tuple[int, int, int], b: tuple[int, int, int], ink: tuple[int, int, int]) -> None:
        x = self.margin_x
        y = self.margin_y
        marker = self.scaled(13)
        draw.rounded_rectangle((x, y + self.scaled(9), x + marker, y + self.scaled(22)), radius=self.scaled(3), fill=(*a, 220))
        draw.text((x + self.scaled(24), y), scene.kicker.upper(), font=self.font("sans", 18), fill=(*mix(a, ink, 0.35), 235))
        max_width = self.width - self.margin_x * 2
        self.draw_wrapped(
            draw,
            scene.claim,
            x,
            y + self.scaled(38),
            self.font("display", 48),
            (*ink, 245),
            max_width,
            line_gap=self.scaled(8),
            max_lines=2,
        )
        draw.line((x, y + self.scaled(150), self.width - self.margin_x, y + self.scaled(150)), fill=(*mix(a, b, 0.5), 110), width=self.scaled(1))

    def draw_term_rail(self, draw: ImageDraw.ImageDraw, scene: Scene, x0: int, y: int, x1: int, a: tuple[int, int, int], b: tuple[int, int, int], muted: tuple[int, int, int]) -> None:
        draw.text((x0, y), "NOTATION", font=self.font("sans", 15), fill=(*muted, 205))
        x = x0
        y += self.scaled(32)
        font = self.font("mono", 18)
        for idx, term in enumerate(scene.terms):
            label = term.upper()
            bbox = draw.textbbox((0, 0), label, font=font)
            w = bbox[2] - bbox[0] + self.scaled(28)
            if x + w > x1:
                break
            col = mix(a, b, idx / max(1, len(scene.terms) - 1))
            draw.rounded_rectangle((x, y, x + w, y + self.scaled(36)), radius=self.scaled(8), fill=(*rgb("#111820"), 210), outline=(*col, 160), width=self.scaled(1))
            draw.text((x + self.scaled(14), y + self.scaled(8)), label, font=font, fill=(*mix(col, rgb("#ffffff"), 0.35), 235))
            x += w + self.scaled(12)

    def draw_dynamic_footer(self, image: Image.Image, scene: Scene, p: float, total_p: float, elapsed: float, total: float) -> None:
        draw = ImageDraw.Draw(image, "RGBA")
        a, b = self.accent(scene)
        x0 = self.margin_x
        x1 = self.width - self.margin_x
        y = self.height - self.margin_y
        draw.line((x0, y, x1, y), fill=(*rgb("#51606b"), 90), width=self.scaled(2))
        draw.line((x0, y, x0 + int((x1 - x0) * total_p), y), fill=(*mix(a, b, 0.55), 210), width=self.scaled(3))
        label = f"Proof segment {scene.scene_id} / theorem board"
        time_label = f"{int(elapsed):03d}s / {int(total):03d}s"
        draw.text((x0, y + self.scaled(14)), label, font=self.font("sans", 16), fill=(*rgb("#d8dedc"), 210))
        tw = draw.textbbox((0, 0), time_label, font=self.font("mono", 16))[2]
        draw.text((x1 - tw, y + self.scaled(14)), time_label, font=self.font("mono", 16), fill=(*mix(a, rgb("#ffffff"), 0.5), 220))
        caption_y = y - self.scaled(44)
        draw.rounded_rectangle((x0, caption_y, x1, caption_y + self.scaled(31)), radius=self.scaled(8), fill=(*rgb("#080d12"), 180), outline=(*mix(a, b, 0.4), 80))
        self.draw_fit_line(draw, scene.caption, x0 + self.scaled(18), caption_y + self.scaled(7), x1 - x0 - self.scaled(36), self.font("sans", 18), (*rgb("#f6f2e8"), 225))

    def draw_fit_line(self, draw: ImageDraw.ImageDraw, text: str, x: int, y: int, max_width: int, font: ImageFont.ImageFont, fill: tuple[int, int, int, int]) -> None:
        candidate = text
        while candidate:
            bbox = draw.textbbox((0, 0), candidate, font=font)
            if bbox[2] - bbox[0] <= max_width:
                draw.text((x, y), candidate, font=font, fill=fill)
                return
            candidate = candidate[:-2].rstrip() + "."
        draw.text((x, y), text[:12], font=font, fill=fill)

    def draw_wrapped(
        self,
        draw: ImageDraw.ImageDraw,
        text: str,
        x: int,
        y: int,
        font: ImageFont.ImageFont,
        fill: tuple[int, int, int, int],
        max_width: int,
        line_gap: int = 6,
        max_lines: int | None = None,
    ) -> int:
        words = text.split()
        lines: list[str] = []
        current = ""
        for word in words:
            probe = f"{current} {word}".strip()
            bbox = draw.textbbox((0, 0), probe, font=font)
            if bbox[2] - bbox[0] <= max_width or not current:
                current = probe
            else:
                lines.append(current)
                current = word
        if current:
            lines.append(current)
        if max_lines is not None and len(lines) > max_lines:
            lines = lines[:max_lines]
            lines[-1] = lines[-1].rstrip(".") + "."
        cursor = y
        line_height = max(1, draw.textbbox((0, 0), "Hg", font=font)[3] - draw.textbbox((0, 0), "Hg", font=font)[1])
        for line in lines:
            draw.text((x, cursor), line, font=font, fill=fill)
            cursor += line_height + line_gap
        return cursor

    def bullet_stack(self, draw: ImageDraw.ImageDraw, scene: Scene, x: int, y: int, w: int, a: tuple[int, int, int], ink: tuple[int, int, int], muted: tuple[int, int, int]) -> None:
        draw.text((x, y), "ARGUMENT SPINE", font=self.font("sans", 16), fill=(*muted, 220))
        y += self.scaled(36)
        for idx, item in enumerate(scene.bullets):
            marker_y = y + self.scaled(5)
            draw.ellipse((x, marker_y, x + self.scaled(9), marker_y + self.scaled(9)), fill=(*mix(a, ink, 0.18), 230))
            y = self.draw_wrapped(draw, item, x + self.scaled(24), y, self.font("sans", 24), (*ink, 232), w - self.scaled(24), line_gap=self.scaled(6), max_lines=3)
            y += self.scaled(24 if idx < len(scene.bullets) - 1 else 0)

    def panel(self, draw: ImageDraw.ImageDraw, box: tuple[int, int, int, int], fill_alpha: int = 156, outline: tuple[int, int, int] | None = None) -> None:
        outline = outline or rgb("#5e6b78")
        draw.rounded_rectangle(box, radius=self.scaled(8), fill=(*rgb("#0d131a"), fill_alpha), outline=(*outline, 120), width=self.scaled(1))

    def math_box(self, draw: ImageDraw.ImageDraw, box: tuple[int, int, int, int], title: str, body: str, accent: tuple[int, int, int], ink: tuple[int, int, int], muted: tuple[int, int, int]) -> None:
        self.panel(draw, box, outline=accent)
        x0, y0, x1, _ = box
        draw.text((x0 + self.scaled(18), y0 + self.scaled(15)), title.upper(), font=self.font("mono", 16), fill=(*accent, 235))
        self.draw_wrapped(draw, body, x0 + self.scaled(18), y0 + self.scaled(48), self.font("mono", 20), (*ink, 230), x1 - x0 - self.scaled(36), line_gap=self.scaled(8), max_lines=5)

    def draw_order_lattice(self, draw: ImageDraw.ImageDraw, cx: int, cy: int, radius: int, a: tuple[int, int, int], b: tuple[int, int, int], ink: tuple[int, int, int], labels: tuple[str, ...] = ("0", "a", "b", "a meet b", "a join b", "1")) -> None:
        points = [
            (cx, cy + radius, labels[0]),
            (cx - int(radius * 0.46), cy + int(radius * 0.30), labels[1]),
            (cx + int(radius * 0.46), cy + int(radius * 0.30), labels[2]),
            (cx, cy + int(radius * 0.02), labels[3]),
            (cx, cy - int(radius * 0.34), labels[4]),
            (cx, cy - radius, labels[5]),
        ]
        edges = [(0, 1), (0, 2), (1, 3), (2, 3), (3, 4), (1, 4), (2, 4), (4, 5)]
        for i, j in edges:
            x0, y0, _ = points[i]
            x1, y1, _ = points[j]
            draw.line((x0, y0, x1, y1), fill=(*mix(a, b, (i + j) / 10), 150), width=self.scaled(2))
        for idx, (x, y, label) in enumerate(points):
            col = mix(a, b, idx / max(1, len(points) - 1))
            r = self.scaled(24 if len(label) <= 3 else 34)
            draw.ellipse((x - r, y - r, x + r, y + r), fill=(*rgb("#0b1117"), 236), outline=(*col, 225), width=self.scaled(2))
            self.center_text(draw, label.upper(), x, y - self.scaled(9), self.font("mono", 14 if len(label) <= 8 else 11), (*ink, 235))

    def layout_theorem_cover(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        board = (left, top, right, bottom - self.scaled(32))
        self.panel(draw, board, fill_alpha=132, outline=a)
        draw.text((left + self.scaled(28), top + self.scaled(20)), "LATTICRA SUBSTRATE THEOREM", font=self.font("display", 50), fill=(*ink, 245))
        draw.text((left + self.scaled(32), top + self.scaled(82)), "Chase Bryan / Colorado Technical University", font=self.font("sans", 22), fill=(*mix(a, ink, 0.45), 226))
        formulas = [
            "L = (L, <=, meet, join, 0, 1)",
            "E = effect semiring with zero = no-effect",
            "H = L x E x Tau",
            "T : H -> H is monotone + authority-guarded",
            "Trace(T) records movement, refusal, and evidence",
        ]
        y = top + self.scaled(132)
        for idx, formula in enumerate(formulas):
            col = mix(a, b, idx / max(1, len(formulas) - 1))
            draw.text((left + self.scaled(42), y), formula, font=self.font("mono", 25), fill=(*col, 240))
            y += self.scaled(46)
        self.draw_order_lattice(draw, right - self.scaled(270), top + self.scaled(245), self.scaled(170), a, b, ink, ("0", "rep", "auth", "trace", "T(h)", "1"))
        self.bullet_stack(draw, scene, left + self.scaled(42), bottom - self.scaled(205), int((right - left) * 0.60), a, ink, muted)

    def layout_poset_lattice(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        self.draw_order_lattice(draw, left + self.scaled(390), top + self.scaled(260), self.scaled(220), a, b, ink)
        axioms = [
            ("Reflexive", "x <= x"),
            ("Antisymmetric", "x <= y and y <= x => x = y"),
            ("Transitive", "x <= y <= z => x <= z"),
        ]
        x = left + self.scaled(760)
        y = top + self.scaled(52)
        for idx, (name, formula) in enumerate(axioms):
            self.math_box(draw, (x, y, right, y + self.scaled(105)), name, formula, mix(a, b, idx / 2), ink, muted)
            y += self.scaled(132)
        self.draw_wrapped(draw, scene.proof, left, bottom - self.scaled(72), self.font("sans", 24), (*ink, 220), right - left, max_lines=2)

    def layout_meet_join(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        mid = (left + right) // 2
        self.draw_order_lattice(draw, mid, top + self.scaled(250), self.scaled(205), a, b, ink)
        self.math_box(draw, (left, top + self.scaled(45), left + self.scaled(410), top + self.scaled(220)), "MEET", "a meet b = greatest lower bound\ncommon support below a and b", a, ink, muted)
        self.math_box(draw, (right - self.scaled(410), top + self.scaled(45), right, top + self.scaled(220)), "JOIN", "a join b = least upper bound\nweakest state containing both", b, ink, muted)
        draw.line((left + self.scaled(430), top + self.scaled(136), mid - self.scaled(95), top + self.scaled(305)), fill=(*a, 140), width=self.scaled(2))
        draw.line((right - self.scaled(430), top + self.scaled(136), mid + self.scaled(95), top + self.scaled(196)), fill=(*b, 140), width=self.scaled(2))
        self.bullet_stack(draw, scene, left, bottom - self.scaled(150), right - left, a, ink, muted)

    def layout_powerset_lattice(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        cx = left + self.scaled(430)
        cy = top + self.scaled(250)
        levels = [
            [("{}", 0)],
            [("{p}", -170), ("{s}", 0), ("{e}", 170)],
            [("{p,s}", -170), ("{p,e}", 0), ("{s,e}", 170)],
            [("{p,s,e}", 0)],
        ]
        coords: dict[str, tuple[int, int]] = {}
        for row, items in enumerate(levels):
            y = cy + self.scaled(185 - row * 120)
            for label, dx in items:
                coords[label] = (cx + self.scaled(dx), y)
        edge_pairs = [
            ("{}", "{p}"), ("{}", "{s}"), ("{}", "{e}"),
            ("{p}", "{p,s}"), ("{p}", "{p,e}"), ("{s}", "{p,s}"), ("{s}", "{s,e}"), ("{e}", "{p,e}"), ("{e}", "{s,e}"),
            ("{p,s}", "{p,s,e}"), ("{p,e}", "{p,s,e}"), ("{s,e}", "{p,s,e}"),
        ]
        for u, v in edge_pairs:
            draw.line((*coords[u], *coords[v]), fill=(*mix(a, b, 0.35), 125), width=self.scaled(2))
        for idx, (label, (x, y)) in enumerate(coords.items()):
            col = mix(a, b, idx / max(1, len(coords) - 1))
            draw.rounded_rectangle((x - self.scaled(48), y - self.scaled(20), x + self.scaled(48), y + self.scaled(20)), radius=self.scaled(8), fill=(*rgb("#0b1117"), 232), outline=(*col, 210))
            self.center_text(draw, label, x, y - self.scaled(9), self.font("mono", 17), (*ink, 235))
        self.math_box(draw, (left + self.scaled(790), top + self.scaled(60), right, top + self.scaled(210)), "OPERATIONS", "meet = intersection\njoin = union\norder = subset inclusion", b, ink, muted)
        self.bullet_stack(draw, scene, left + self.scaled(790), top + self.scaled(255), right - left - self.scaled(790), a, ink, muted)

    def layout_effect_semiring(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        effects = [("0_E", "none"), ("R", "read"), ("M", "mutate"), ("N", "network"), ("H", "hardware")]
        x0 = left + self.scaled(40)
        y = top + self.scaled(155)
        gap = self.scaled(32)
        cell_w = (right - left - self.scaled(80) - gap * (len(effects) - 1)) // len(effects)
        for idx, (sym, label) in enumerate(effects):
            x = x0 + idx * (cell_w + gap)
            col = mix(a, b, idx / max(1, len(effects) - 1))
            self.panel(draw, (x, y, x + cell_w, y + self.scaled(118)), outline=col)
            self.center_text(draw, sym, x + cell_w // 2, y + self.scaled(22), self.font("mono", 30), (*col, 240))
            self.center_text(draw, label.upper(), x + cell_w // 2, y + self.scaled(70), self.font("mono", 16), (*ink, 220))
            if idx < len(effects) - 1:
                draw.text((x + cell_w + self.scaled(7), y + self.scaled(43)), "+", font=self.font("mono", 28), fill=(*muted, 190))
        self.math_box(draw, (left, top + self.scaled(330), left + self.scaled(640), bottom - self.scaled(56)), "COMPOSITION", "e_i * e_j means sequential authority\n0_E * e = 0_E for no-effect rendering", a, ink, muted)
        self.math_box(draw, (left + self.scaled(700), top + self.scaled(330), right, bottom - self.scaled(56)), "GATE", "allow(T) iff requested effect <= admitted effect\notherwise Trace records refusal", b, ink, muted)

    def layout_hyperlattice(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        origin_x = left + self.scaled(230)
        origin_y = bottom - self.scaled(130)
        axis_len = self.scaled(300)
        axes = [("L", 0, -axis_len), ("E", axis_len, 0), ("Tau", self.scaled(210), -self.scaled(210))]
        for label, dx, dy in axes:
            draw.line((origin_x, origin_y, origin_x + dx, origin_y + dy), fill=(*mix(a, b, 0.45), 190), width=self.scaled(3))
            self.center_text(draw, label, origin_x + dx, origin_y + dy - self.scaled(24), self.font("mono", 24), (*ink, 235))
        for i in range(5):
            for j in range(5):
                x = origin_x + i * self.scaled(58) + j * self.scaled(34)
                y = origin_y - i * self.scaled(58) - j * self.scaled(34)
                draw.ellipse((x - self.scaled(5), y - self.scaled(5), x + self.scaled(5), y + self.scaled(5)), fill=(*mix(a, b, (i + j) / 8), 180))
        self.math_box(draw, (left + self.scaled(700), top + self.scaled(55), right, top + self.scaled(210)), "PRODUCT STATE", "H = L x E x Tau\nh = (representation, effect, time)", a, ink, muted)
        self.bullet_stack(draw, scene, left + self.scaled(720), top + self.scaled(260), right - left - self.scaled(720), b, ink, muted)

    def layout_simulation_tick(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        steps = [("read h_i", "state"), ("propose h'", "T"), ("check effect", "gate"), ("record row", "trace")]
        y = top + self.scaled(175)
        gap = self.scaled(34)
        box_w = (right - left - gap * (len(steps) - 1)) // len(steps)
        for idx, (head, sub) in enumerate(steps):
            x = left + idx * (box_w + gap)
            col = mix(a, b, idx / max(1, len(steps) - 1))
            self.panel(draw, (x, y, x + box_w, y + self.scaled(132)), outline=col)
            self.center_text(draw, head.upper(), x + box_w // 2, y + self.scaled(30), self.font("sans", 22), (*ink, 235))
            self.center_text(draw, sub, x + box_w // 2, y + self.scaled(79), self.font("mono", 24), (*col, 238))
            if idx < len(steps) - 1:
                ax = x + box_w
                draw.line((ax + self.scaled(5), y + self.scaled(66), ax + gap - self.scaled(5), y + self.scaled(66)), fill=(*col, 190), width=self.scaled(3))
                draw.polygon([(ax + gap - self.scaled(5), y + self.scaled(66)), (ax + gap - self.scaled(19), y + self.scaled(58)), (ax + gap - self.scaled(19), y + self.scaled(74))], fill=(*col, 210))
        self.math_box(draw, (left, top + self.scaled(360), right, bottom - self.scaled(56)), "VALID TICK", "T(h_i) = h_{i+1} requires h_i <= h_{i+1} and effect(h_i -> h_{i+1}) <= gate", a, ink, muted)

    def layout_chains(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        y = top + self.scaled(210)
        x0 = left + self.scaled(90)
        spacing = (right - left - self.scaled(180)) // 6
        for idx in range(7):
            x = x0 + idx * spacing
            col = mix(a, b, idx / 6)
            draw.ellipse((x - self.scaled(30), y - self.scaled(30), x + self.scaled(30), y + self.scaled(30)), fill=(*rgb("#0b1117"), 238), outline=(*col, 220), width=self.scaled(2))
            self.center_text(draw, f"h{idx}", x, y - self.scaled(10), self.font("mono", 18), (*ink, 235))
            if idx < 6:
                draw.line((x + self.scaled(34), y, x + spacing - self.scaled(34), y), fill=(*col, 170), width=self.scaled(3))
                draw.text((x + spacing // 2 - self.scaled(10), y - self.scaled(38)), "<=", font=self.font("mono", 20), fill=(*muted, 210))
        self.math_box(draw, (left + self.scaled(150), top + self.scaled(345), right - self.scaled(150), bottom - self.scaled(56)), "CHAIN LIMIT", "h0 <= h1 <= h2 <= ...\nlub({h_i}) is the least state containing the accumulated trace", b, ink, muted)

    def layout_fixpoint(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        cx = left + self.scaled(455)
        cy = top + self.scaled(255)
        for i in range(8):
            r = self.scaled(180 - i * 18)
            col = mix(a, b, i / 7)
            draw.arc((cx - r, cy - r, cx + r, cy + r), start=25 + i * 18, end=320 + i * 18, fill=(*col, 185), width=self.scaled(3))
        draw.ellipse((cx - self.scaled(24), cy - self.scaled(24), cx + self.scaled(24), cy + self.scaled(24)), fill=(*b, 210))
        self.center_text(draw, "x*", cx, cy - self.scaled(12), self.font("mono", 22), (*rgb("#07100c"), 245))
        self.math_box(draw, (left + self.scaled(760), top + self.scaled(65), right, top + self.scaled(215)), "FIXPOINT", "T(x*) = x*\niteration from 0 builds the least stable state", a, ink, muted)
        self.bullet_stack(draw, scene, left + self.scaled(760), top + self.scaled(270), right - left - self.scaled(760), b, ink, muted)

    def layout_abstraction_tower(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        cx = left + self.scaled(360)
        y0 = bottom - self.scaled(120)
        widths = [520, 430, 340, 250, 160]
        labels = ["L0 concrete trace", "L1 evidence report", "L2 semantic model", "L3 theory view", "L4 theorem claim"]
        for idx, (w, label) in enumerate(zip(widths, labels)):
            y = y0 - idx * self.scaled(76)
            col = mix(a, b, idx / (len(widths) - 1))
            draw.rounded_rectangle((cx - self.scaled(w // 2), y, cx + self.scaled(w // 2), y + self.scaled(46)), radius=self.scaled(8), fill=(*rgb("#0b1117"), 232), outline=(*col, 190))
            self.center_text(draw, label.upper(), cx, y + self.scaled(13), self.font("mono", 16), (*ink, 230))
            if idx < len(widths) - 1:
                draw.line((cx, y, cx, y - self.scaled(28)), fill=(*col, 160), width=self.scaled(2))
                self.center_text(draw, f"pi_{idx}", cx + self.scaled(46), y - self.scaled(28), self.font("mono", 15), (*col, 230))
        self.math_box(draw, (left + self.scaled(740), top + self.scaled(75), right, top + self.scaled(225)), "PROJECTION", "pi_i : L_{i+1} -> L_i\nx <= y implies pi_i(x) <= pi_i(y)", b, ink, muted)
        self.bullet_stack(draw, scene, left + self.scaled(740), top + self.scaled(280), right - left - self.scaled(740), a, ink, muted)

    def layout_trace_matrix(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        columns = ["t", "state", "op", "effect", "gate", "delta"]
        rows = [
            ["0", "h0", "parse", "0_E", "allow", "+span"],
            ["1", "h1", "join", "0_E", "allow", "+LIR"],
            ["2", "h2", "mutate?", "M", "deny", "+receipt"],
            ["3", "h3", "render", "0_E", "allow", "+report"],
        ]
        table_x = left
        table_y = top + self.scaled(78)
        col_w = (right - left) // len(columns)
        row_h = self.scaled(58)
        for c, name in enumerate(columns):
            x = table_x + c * col_w
            draw.rectangle((x, table_y, x + col_w, table_y + row_h), fill=(*rgb("#102018"), 220), outline=(*a, 130))
            self.center_text(draw, name.upper(), x + col_w // 2, table_y + self.scaled(18), self.font("mono", 16), (*mix(a, ink, 0.35), 235))
        for r, row in enumerate(rows):
            y = table_y + (r + 1) * row_h
            for c, value in enumerate(row):
                x = table_x + c * col_w
                col = b if value == "deny" else mix(a, b, c / max(1, len(columns) - 1))
                draw.rectangle((x, y, x + col_w, y + row_h), fill=(*rgb("#0b1117"), 210), outline=(*col, 95))
                self.center_text(draw, value, x + col_w // 2, y + self.scaled(18), self.font("mono", 16), (*ink, 225))
        self.draw_wrapped(draw, scene.proof, left, bottom - self.scaled(92), self.font("sans", 24), (*ink, 220), right - left, max_lines=2)

    def layout_qed(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        cx = (left + right) // 2
        cy = top + self.scaled(245)
        rings = [("L", "representation"), ("E", "authority"), ("T", "transition"), ("Trace", "inspection")]
        for idx, (sym, label) in enumerate(rings):
            r = self.scaled(70 + idx * 48)
            col = mix(a, b, idx / max(1, len(rings) - 1))
            draw.ellipse((cx - r, cy - r, cx + r, cy + r), outline=(*col, 185), width=self.scaled(3))
            self.center_text(draw, f"{sym}: {label}", cx, cy - self.scaled(9) + idx * self.scaled(32), self.font("mono", 16), (*mix(col, ink, 0.4), 235))
        self.math_box(draw, (left, top + self.scaled(45), left + self.scaled(510), top + self.scaled(235)), "MODEL", "Latticra = (L, E, T, Trace)\nmeet/join + guarded effects", a, ink, muted)
        self.math_box(draw, (right - self.scaled(510), top + self.scaled(45), right, top + self.scaled(235)), "RESULT", "ordered state + explicit authority\n=> inspectable simulation", b, ink, muted)
        self.bullet_stack(draw, scene, left, bottom - self.scaled(160), right - left, a, ink, muted)

    def layout_cover(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        title = "Lattice / Latticra"
        draw.text((left, top + self.scaled(10)), title, font=self.font("display", 82), fill=(*ink, 245))
        subtitle = "representation first  |  authority explicit  |  visuals accountable"
        self.draw_wrapped(draw, subtitle, left, top + self.scaled(112), self.font("sans", 28), (*mix(a, ink, 0.42), 238), int((right - left) * 0.58), line_gap=self.scaled(8), max_lines=2)
        self.bullet_stack(draw, scene, left, top + self.scaled(210), int((right - left) * 0.42), a, ink, muted)
        rail_x = int(left + (right - left) * 0.55)
        rail_w = right - rail_x
        metrics = [("720s", "timed voiceover"), ("12", "academic chapters"), ("1", "render contract")]
        for idx, (value, label) in enumerate(metrics):
            y = top + idx * self.scaled(118)
            self.panel(draw, (rail_x, y, right, y + self.scaled(86)), outline=mix(a, b, idx / 2))
            draw.text((rail_x + self.scaled(24), y + self.scaled(12)), value, font=self.font("display", 48), fill=(*mix(a, b, idx / 2), 245))
            draw.text((rail_x + self.scaled(190), y + self.scaled(29)), label.upper(), font=self.font("mono", 19), fill=(*ink, 220))

    def layout_problem(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        labels = [("Hidden state", "claim without visible transformation"), ("Weak type", "labels crop, shrink, or compete"), ("Loose audio", "voiceover lands after the visual")]
        card_w = (right - left - self.scaled(42)) // 3
        for idx, (head, body) in enumerate(labels):
            x = left + idx * (card_w + self.scaled(21))
            self.panel(draw, (x, top, x + card_w, bottom - self.scaled(64)), outline=mix(a, b, idx / 2))
            draw.text((x + self.scaled(24), top + self.scaled(28)), f"0{idx + 1}", font=self.font("mono", 28), fill=(*mix(a, b, idx / 2), 240))
            draw.text((x + self.scaled(24), top + self.scaled(86)), head, font=self.font("display", 34), fill=(*ink, 238))
            self.draw_wrapped(draw, body, x + self.scaled(24), top + self.scaled(145), self.font("sans", 24), (*muted, 228), card_w - self.scaled(48), line_gap=self.scaled(7), max_lines=4)
        self.draw_wrapped(draw, scene.proof, left, bottom - self.scaled(38), self.font("sans", 21), (*ink, 215), right - left, max_lines=2)

    def layout_pipeline(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        steps = ["Lat source", "Parser", "Semantic model", "LIR", "L-UI report", "Seal receipt"]
        center_y = top + self.scaled(170)
        gap = self.scaled(18)
        box_w = (right - left - gap * (len(steps) - 1)) // len(steps)
        for idx, step in enumerate(steps):
            x = left + idx * (box_w + gap)
            col = mix(a, b, idx / max(1, len(steps) - 1))
            self.panel(draw, (x, center_y - self.scaled(58), x + box_w, center_y + self.scaled(58)), outline=col)
            self.draw_fit_line(draw, step, x + self.scaled(14), center_y - self.scaled(9), box_w - self.scaled(28), self.font("sans", 20), (*ink, 235))
            if idx < len(steps) - 1:
                ax = x + box_w
                draw.line((ax + self.scaled(4), center_y, ax + gap - self.scaled(4), center_y), fill=(*col, 190), width=self.scaled(2))
                draw.polygon([(ax + gap - self.scaled(6), center_y), (ax + gap - self.scaled(16), center_y - self.scaled(5)), (ax + gap - self.scaled(16), center_y + self.scaled(5))], fill=(*col, 210))
        self.bullet_stack(draw, scene, left, top + self.scaled(330), right - left, a, ink, muted)

    def layout_lattice(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        cx = (left + right) // 2
        cy = top + self.scaled(230)
        levels = [
            [(cx, cy - self.scaled(170), "join")],
            [(cx - self.scaled(260), cy - self.scaled(40), "A"), (cx, cy - self.scaled(40), "boundary"), (cx + self.scaled(260), cy - self.scaled(40), "B")],
            [(cx - self.scaled(150), cy + self.scaled(100), "meet"), (cx + self.scaled(150), cy + self.scaled(100), "evidence")],
        ]
        flat = [node for level in levels for node in level]
        for i, src in enumerate(flat):
            for dst in flat[i + 1 :]:
                if abs(src[0] - dst[0]) < self.scaled(300) and src[1] < dst[1]:
                    draw.line((src[0], src[1], dst[0], dst[1]), fill=(*mix(a, b, i / len(flat)), 110), width=self.scaled(2))
        for idx, (x, y, label) in enumerate(flat):
            col = mix(a, b, idx / max(1, len(flat) - 1))
            draw.ellipse((x - self.scaled(42), y - self.scaled(42), x + self.scaled(42), y + self.scaled(42)), fill=(*rgb("#0e141b"), 230), outline=(*col, 210), width=self.scaled(2))
            self.center_text(draw, label.upper(), x, y - self.scaled(10), self.font("mono", 17), (*ink, 230))
        equation = "join(A, B) -> constrained composition    meet(A, B) -> shared support"
        self.draw_wrapped(draw, equation, left, bottom - self.scaled(72), self.font("mono", 22), (*mix(a, ink, 0.45), 235), right - left, max_lines=2)

    def layout_ui_report(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        panel_w = int((right - left) * 0.55)
        self.panel(draw, (left, top, left + panel_w, bottom - self.scaled(50)), outline=a)
        rows = [("parser", "ok"), ("semantic", "ok"), ("LIR", "bounded"), ("authority", "report-only"), ("effect", "none")]
        y = top + self.scaled(34)
        for idx, (field, value) in enumerate(rows):
            col = mix(a, b, idx / max(1, len(rows) - 1))
            draw.text((left + self.scaled(32), y), field.upper(), font=self.font("mono", 20), fill=(*muted, 220))
            draw.text((left + self.scaled(260), y), value, font=self.font("sans", 26), fill=(*mix(col, ink, 0.35), 240))
            y += self.scaled(62)
        self.bullet_stack(draw, scene, left + panel_w + self.scaled(56), top + self.scaled(10), right - left - panel_w - self.scaled(56), a, ink, muted)

    def layout_authority(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        columns = ["report", "read", "mutate", "network", "recovery", "hardware"]
        states = ["allow", "allow", "deny", "deny", "deny", "deny"]
        cell_w = (right - left) // len(columns)
        y0 = top + self.scaled(120)
        for idx, name in enumerate(columns):
            x = left + idx * cell_w
            col = mix(a, b, idx / max(1, len(columns) - 1))
            fill = rgb("#132019") if states[idx] == "allow" else rgb("#201315")
            draw.rounded_rectangle((x + self.scaled(5), y0, x + cell_w - self.scaled(5), y0 + self.scaled(150)), radius=self.scaled(8), fill=(*fill, 218), outline=(*col, 150), width=self.scaled(1))
            self.center_text(draw, name.upper(), x + cell_w // 2, y0 + self.scaled(34), self.font("mono", 16), (*muted, 220))
            self.center_text(draw, states[idx].upper(), x + cell_w // 2, y0 + self.scaled(82), self.font("display", 34), (*col, 240))
        self.bullet_stack(draw, scene, left, top + self.scaled(330), right - left, a, ink, muted)

    def layout_seal(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        steps = ["metadata", "signed request", "verification", "decision", "receipt"]
        path_y = top + self.scaled(210)
        start_x = left + self.scaled(80)
        end_x = right - self.scaled(80)
        draw.line((start_x, path_y, end_x, path_y), fill=(*mix(a, b, 0.5), 140), width=self.scaled(3))
        for idx, step in enumerate(steps):
            x = int(start_x + (end_x - start_x) * idx / (len(steps) - 1))
            col = mix(a, b, idx / (len(steps) - 1))
            draw.ellipse((x - self.scaled(46), path_y - self.scaled(46), x + self.scaled(46), path_y + self.scaled(46)), fill=(*rgb("#111820"), 240), outline=(*col, 220), width=self.scaled(2))
            self.center_text(draw, f"{idx + 1}", x, path_y - self.scaled(13), self.font("display", 35), (*col, 245))
            self.center_text(draw, step.upper(), x, path_y + self.scaled(66), self.font("mono", 15), (*ink, 220))
        self.bullet_stack(draw, scene, left, top + self.scaled(350), right - left, a, ink, muted)

    def layout_kernel(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        lanes = ["timer source", "run queue", "scheduler", "context switch", "lifecycle"]
        y = top + self.scaled(40)
        for idx, lane in enumerate(lanes):
            h = self.scaled(68)
            col = mix(a, b, idx / max(1, len(lanes) - 1))
            self.panel(draw, (left, y, right, y + h), outline=col)
            draw.text((left + self.scaled(28), y + self.scaled(20)), lane.upper(), font=self.font("mono", 18), fill=(*col, 235))
            draw.line((left + self.scaled(270), y + h // 2, right - self.scaled(36), y + h // 2), fill=(*col, 100), width=self.scaled(2))
            draw.ellipse((right - self.scaled(54), y + h // 2 - self.scaled(9), right - self.scaled(36), y + h // 2 + self.scaled(9)), fill=(*col, 180))
            y += h + self.scaled(20)
        self.draw_wrapped(draw, scene.proof, left, bottom - self.scaled(72), self.font("sans", 22), (*ink, 220), right - left, max_lines=2)

    def layout_visual_engine(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        stages = ["substrate", "matrix", "modul", "contain", "fracture", "unity", "decelerate", "regenesis"]
        y = top + self.scaled(190)
        cell_w = (right - left) // len(stages)
        for idx, stage in enumerate(stages):
            x = left + idx * cell_w + cell_w // 2
            col = mix(a, b, idx / max(1, len(stages) - 1))
            draw.line((x, y - self.scaled(90), x, y + self.scaled(90)), fill=(*col, 80), width=self.scaled(1))
            draw.ellipse((x - self.scaled(24), y - self.scaled(24), x + self.scaled(24), y + self.scaled(24)), fill=(*rgb("#10151d"), 238), outline=(*col, 210), width=self.scaled(2))
            self.center_text(draw, str(idx + 1), x, y - self.scaled(10), self.font("mono", 16), (*ink, 230))
            self.center_text(draw, stage.upper(), x, y + self.scaled(48), self.font("mono", 13), (*muted, 220))
        draw.line((left + cell_w // 2, y, right - cell_w // 2, y), fill=(*mix(a, b, 0.5), 130), width=self.scaled(2))
        self.bullet_stack(draw, scene, left, top + self.scaled(350), right - left, a, ink, muted)

    def layout_delivery(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        rows = ["Fedora", "Ubuntu", "Debian", "FreeBSD", "OpenBSD", "macOS"]
        cols = ["manifest", "validation", "receipt"]
        table_w = int((right - left) * 0.55)
        cell_h = self.scaled(48)
        draw.text((left, top), "ARTIFACT EVIDENCE MATRIX", font=self.font("sans", 18), fill=(*muted, 220))
        for r, row in enumerate(rows):
            y = top + self.scaled(48) + r * cell_h
            draw.text((left, y + self.scaled(12)), row, font=self.font("mono", 17), fill=(*ink, 220))
            for c, col_name in enumerate(cols):
                x = left + self.scaled(150) + c * self.scaled(155)
                col = mix(a, b, (r + c) / (len(rows) + len(cols)))
                draw.rounded_rectangle((x, y + self.scaled(6), x + self.scaled(120), y + self.scaled(34)), radius=self.scaled(6), fill=(*rgb("#10171d"), 230), outline=(*col, 130))
                self.center_text(draw, "tracked", x + self.scaled(60), y + self.scaled(12), self.font("sans", 15), (*col, 230))
        self.bullet_stack(draw, scene, left + table_w + self.scaled(56), top + self.scaled(12), right - left - table_w - self.scaled(56), a, ink, muted)

    def layout_research(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        rows = [
            ("Implemented", "parsers, reports, boundary checks, tests"),
            ("Prototype", "visual theorem surfaces and production video"),
            ("Open", "formal invariants, reviewer studies, proof depth"),
        ]
        for idx, (head, body) in enumerate(rows):
            y = top + idx * self.scaled(118)
            col = mix(a, b, idx / max(1, len(rows) - 1))
            self.panel(draw, (left, y, right, y + self.scaled(88)), outline=col)
            draw.text((left + self.scaled(28), y + self.scaled(23)), head.upper(), font=self.font("mono", 19), fill=(*col, 240))
            draw.text((left + self.scaled(270), y + self.scaled(23)), body, font=self.font("sans", 25), fill=(*ink, 228))
        self.draw_wrapped(draw, scene.proof, left, bottom - self.scaled(88), self.font("sans", 24), (*muted, 225), right - left, max_lines=2)

    def layout_closing(self, draw, scene, left, top, right, bottom, a, b, ink, muted) -> None:
        rings = [("representation", 0.0), ("authority", 0.5), ("visual proof", 1.0)]
        cx = left + int((right - left) * 0.38)
        cy = top + self.scaled(220)
        for idx, (label, t) in enumerate(rings):
            r = self.scaled(90 + idx * 55)
            col = mix(a, b, t)
            draw.ellipse((cx - r, cy - r, cx + r, cy + r), outline=(*col, 165), width=self.scaled(3))
            self.center_text(draw, label.upper(), cx, cy - self.scaled(16) + idx * self.scaled(34), self.font("mono", 17), (*mix(col, ink, 0.35), 235))
        command = "./scripts/render-latticra-academic-presentation.sh render"
        box = (left + int((right - left) * 0.58), top + self.scaled(88), right, top + self.scaled(244))
        self.panel(draw, box, outline=b)
        draw.text((box[0] + self.scaled(28), box[1] + self.scaled(26)), "REPRODUCIBLE COMMAND", font=self.font("mono", 18), fill=(*muted, 220))
        self.draw_wrapped(draw, command, box[0] + self.scaled(28), box[1] + self.scaled(70), self.font("mono", 26), (*mix(a, ink, 0.45), 238), box[2] - box[0] - self.scaled(56), max_lines=2)
        self.bullet_stack(draw, scene, box[0], top + self.scaled(310), box[2] - box[0], a, ink, muted)

    def center_text(self, draw: ImageDraw.ImageDraw, text: str, cx: int, y: int, font: ImageFont.ImageFont, fill: tuple[int, int, int, int]) -> None:
        bbox = draw.textbbox((0, 0), text, font=font)
        draw.text((cx - (bbox[2] - bbox[0]) // 2, y), text, font=font, fill=fill)


def parse_size(value: str) -> tuple[int, int]:
    if "x" not in value.lower():
        raise argparse.ArgumentTypeError("size must be WIDTHxHEIGHT")
    left, right = value.lower().split("x", 1)
    width, height = int(left), int(right)
    if width < 640 or height < 360:
        raise argparse.ArgumentTypeError("size must be at least 640x360")
    return width, height


def make_contact_sheet(image_paths: list[Path], out_path: Path, columns: int = 4) -> None:
    images = [Image.open(path).convert("RGB") for path in image_paths]
    if not images:
        return
    thumb_w = 480
    thumb_h = int(thumb_w * images[0].height / images[0].width)
    rows = math.ceil(len(images) / columns)
    sheet = Image.new("RGB", (columns * thumb_w, rows * thumb_h), rgb("#080b10"))
    for idx, image in enumerate(images):
        thumb = image.resize((thumb_w, thumb_h), Image.Resampling.LANCZOS)
        sheet.paste(thumb, ((idx % columns) * thumb_w, (idx // columns) * thumb_h))
    sheet.save(out_path)


def render_preview(renderer: ProductionRenderer, scenes: list[Scene], out_dir: Path) -> list[Path]:
    preview_dir = ensure_dir(out_dir / "preview")
    paths: list[Path] = []
    total = sum(scene.duration for scene in scenes)
    for scene in scenes:
        elapsed = scene.start + scene.duration * 0.5
        image = renderer.render_frame(scene, 0.5, elapsed / total, elapsed, total)
        path = preview_dir / f"scene-{scene.scene_id}.png"
        image.save(path)
        paths.append(path)
    make_contact_sheet(paths, preview_dir / "contact-sheet.png")
    return paths


def locate_executable(name: str, env_key: str | None = None, explicit: str | None = None) -> str | None:
    if explicit:
        return explicit
    if env_key:
        env_value = os.getenv(env_key)
        if env_value:
            return env_value
    return shutil.which(name)


def wav_duration(path: Path) -> float:
    with wave.open(str(path), "rb") as fh:
        return fh.getnframes() / float(fh.getframerate())


def synthesize_voiceover(scenes: list[Scene], out_dir: Path, piper_bin: str | None, piper_model: str | None, piper_config: str | None) -> tuple[Path, list[dict]]:
    piper_bin = locate_executable("piper", "PIPER_BIN", piper_bin)
    piper_python = os.environ.get("PIPER_PYTHON") or sys.executable
    piper_model = piper_model or os.environ.get("PIPER_MODEL") or os.environ.get("PIPER_VOICE")
    if not piper_model:
        raise SystemExit("Piper model was not found. Set PIPER_MODEL=/path/to/voice.onnx.")
    if not Path(piper_model).exists():
        raise SystemExit(f"Piper model does not exist: {piper_model}")

    voice_dir = ensure_dir(out_dir / "voiceover")
    wavs: list[Path] = []
    for scene in scenes:
        wav_path = voice_dir / f"scene-{scene.scene_id}.wav"
        if piper_bin:
            cmd = [piper_bin, "--model", piper_model, "--output_file", str(wav_path)]
            if piper_config:
                cmd.extend(["--config", piper_config])
            subprocess.run(cmd, input=scene.narration + "\n", text=True, check=True)
        else:
            cmd = [piper_python, "-m", "piper", "-m", piper_model, "-f", str(wav_path), "--", scene.narration]
            subprocess.run(cmd, text=True, check=True)
        wavs.append(wav_path)

    combined = voice_dir / "latticra-academic-voiceover.wav"
    timings: list[dict] = []
    start = 0.0
    first_params = None
    with wave.open(str(combined), "wb") as out_wav:
        for scene, wav_path in zip(scenes, wavs):
            with wave.open(str(wav_path), "rb") as in_wav:
                params = in_wav.getparams()
                frames = in_wav.readframes(in_wav.getnframes())
            if first_params is None:
                first_params = params
                out_wav.setparams(params)
            elif params[:3] != first_params[:3]:
                raise SystemExit("Piper WAV parameters changed across scenes; cannot concatenate safely.")
            scene_audio_duration = params.nframes / float(params.framerate)
            target_duration = max(scene.duration, scene_audio_duration)
            out_wav.writeframes(frames)
            pad_frames = max(0, int(round(target_duration * params.framerate)) - params.nframes)
            if pad_frames:
                out_wav.writeframes(b"\x00" * pad_frames * params.nchannels * params.sampwidth)
            timings.append(
                {
                    "id": scene.scene_id,
                    "start": start,
                    "planned_duration": scene.duration,
                    "audio_duration": scene_audio_duration,
                    "duration": target_duration,
                }
            )
            start += target_duration

    (voice_dir / "voiceover-timing.json").write_text(json.dumps({"total_seconds": start, "scenes": timings}, indent=2), encoding="utf-8")
    return combined, timings


def default_timings(scenes: list[Scene]) -> list[dict]:
    timings = []
    start = 0.0
    for scene in scenes:
        timings.append({"id": scene.scene_id, "start": start, "duration": scene.duration, "planned_duration": scene.duration, "audio_duration": None})
        start += scene.duration
    return timings


def render_video(renderer: ProductionRenderer, scenes: list[Scene], timings: list[dict], out_dir: Path, ffmpeg_bin: str | None, audio_path: Path | None, allow_silent: bool) -> Path:
    ffmpeg_bin = locate_executable("ffmpeg", "FFMPEG_BIN", ffmpeg_bin)
    if not ffmpeg_bin:
        raise SystemExit("ffmpeg was not found. Set FFMPEG_BIN or install ffmpeg to render MP4.")
    video_path = ensure_dir(out_dir / "video") / "latticra-academic-presentation.mp4"
    total = sum(item["duration"] for item in timings)
    scene_by_id = {scene.scene_id: scene for scene in scenes}

    cmd = [
        ffmpeg_bin,
        "-y",
        "-f",
        "rawvideo",
        "-pix_fmt",
        "rgb24",
        "-s",
        f"{renderer.width}x{renderer.height}",
        "-r",
        str(renderer.fps),
        "-i",
        "-",
    ]
    if audio_path is not None:
        cmd.extend(["-i", str(audio_path)])
    elif allow_silent:
        cmd.extend(["-f", "lavfi", "-i", "anullsrc=channel_layout=stereo:sample_rate=44100"])
    else:
        raise SystemExit("render requires a voiceover WAV unless --allow-silent is set.")
    cmd.extend(
        [
            "-c:v",
            "libx264",
            "-profile:v",
            "high",
            "-level:v",
            "4.1",
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
    )

    proc = subprocess.Popen(cmd, stdin=subprocess.PIPE)
    assert proc.stdin is not None
    try:
        frame_cursor = 0
        total_frames = int(math.ceil(total * renderer.fps))
        for timing in timings:
            scene = scene_by_id[str(timing["id"])]
            scene_frames = int(math.ceil(float(timing["duration"]) * renderer.fps))
            for frame in range(scene_frames):
                elapsed = frame_cursor / renderer.fps
                local_progress = min(1.0, frame / max(1, scene_frames - 1))
                image = renderer.render_frame(scene, local_progress, min(1.0, elapsed / total), elapsed, total)
                proc.stdin.write(image.tobytes())
                frame_cursor += 1
                if frame_cursor % renderer.fps == 0:
                    print(f"rendering {frame_cursor // renderer.fps:04d}/{math.ceil(total)} seconds", file=sys.stderr)
        proc.stdin.close()
        rc = proc.wait()
    finally:
        if proc.stdin and not proc.stdin.closed:
            proc.stdin.close()
    if rc != 0:
        raise SystemExit(f"ffmpeg exited with code {rc}")
    print(f"rendered {total_frames} frames", file=sys.stderr)
    return video_path


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="Render the Latticra academic presentation.")
    parser.add_argument("mode", choices=["storyboard", "preview", "voiceover", "render"], help="production mode")
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG, help="storyboard TOML path")
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT, help="output directory")
    parser.add_argument("--size", type=parse_size, default=DEFAULT_SIZE, help="render size, e.g. 1920x1080")
    parser.add_argument("--fps", type=int, default=DEFAULT_FPS, help="frames per second for MP4 render")
    parser.add_argument("--piper-bin", default=None, help="piper executable path")
    parser.add_argument("--piper-model", default=None, help="piper voice model .onnx path")
    parser.add_argument("--piper-config", default=None, help="optional piper voice config json")
    parser.add_argument("--ffmpeg-bin", default=None, help="ffmpeg executable path")
    parser.add_argument("--voiceover-wav", type=Path, default=None, help="use an existing combined voiceover WAV")
    parser.add_argument("--allow-silent", action="store_true", help="allow silent MP4 rendering for layout checks")
    return parser


def main(argv: Iterable[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    meta, scenes = load_storyboard(args.config)
    errors = validate_storyboard(meta, scenes)
    if errors:
        for error in errors:
            print(f"storyboard error: {error}", file=sys.stderr)
        return 2

    out_dir = ensure_dir(args.out)
    artifacts = write_story_artifacts(meta, scenes, out_dir)
    manifest = {
        "mode": args.mode,
        "config": str(args.config),
        "out": str(out_dir),
        "artifacts": artifacts,
        "target_seconds": meta.get("target_seconds"),
        "planned_seconds": sum(scene.duration for scene in scenes),
        "word_count": sum(word_count(scene.narration) for scene in scenes),
    }

    if args.mode in {"preview", "render"}:
        renderer = ProductionRenderer(args.size[0], args.size[1], args.fps)
        preview_paths = render_preview(renderer, scenes, out_dir)
        manifest["preview_count"] = len(preview_paths)
        manifest["contact_sheet"] = str(out_dir / "preview/contact-sheet.png")

    voiceover_path: Path | None = args.voiceover_wav
    timings = default_timings(scenes)
    if args.mode in {"voiceover", "render"} and args.voiceover_wav is None:
        voiceover_path, timings = synthesize_voiceover(scenes, out_dir, args.piper_bin, args.piper_model, args.piper_config)
        manifest["voiceover_wav"] = str(voiceover_path)
        manifest["actual_seconds"] = sum(item["duration"] for item in timings)
    elif args.voiceover_wav is not None:
        manifest["voiceover_wav"] = str(args.voiceover_wav)
        actual_seconds = wav_duration(args.voiceover_wav)
        planned_seconds = sum(item["duration"] for item in timings)
        if actual_seconds > planned_seconds and timings:
            timings[-1]["duration"] += actual_seconds - planned_seconds
        manifest["actual_seconds"] = actual_seconds

    if args.mode == "render":
        renderer = ProductionRenderer(args.size[0], args.size[1], args.fps)
        video_path = render_video(renderer, scenes, timings, out_dir, args.ffmpeg_bin, voiceover_path, args.allow_silent)
        manifest["video"] = str(video_path)

    manifest_path = out_dir / "render-manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    print(json.dumps(manifest, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

#!/usr/bin/env python3
"""Render the motion-first Latticra overview presentation.

This renderer is intentionally separate from the academic theorem-board
renderer. It favors sparse screen text, continuous movement, and professional
voiceover pacing.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import math
import os
import re
import shutil
import subprocess
import sys
import wave
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

try:
    import tomllib
except ModuleNotFoundError:  # pragma: no cover
    import tomli as tomllib

from PIL import Image, ImageDraw, ImageFont


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CONFIG = ROOT / "presentations" / "latticra-motion" / "latticra_motion_presentation.toml"
DEFAULT_OUT = ROOT / "build" / "presentation" / "latticra-motion"
DEFAULT_SIZE = (1920, 1080)
DEFAULT_FPS = 24
DEFAULT_ARTIFACT_SLUG = "latticra-motion"
TOKEN_RE = re.compile(r"^[a-z0-9][a-z0-9_-]*$")
ALLOWED_VISUALS = {
    "close",
    "decision",
    "delivery",
    "horizon",
    "intake",
    "language",
    "nucleus",
    "operator",
    "research",
    "roadmap",
    "seal",
    "strata",
    "umbrella",
    "veils",
}


INK = (232, 238, 232)
MUTED = (151, 164, 156)
GREEN = (111, 226, 151)
AMBER = (231, 180, 94)
BLUE = (120, 176, 255)
RED = (238, 100, 112)
VIOLET = (182, 144, 255)
CYAN = (118, 225, 224)
BLACK = (5, 8, 12)


@dataclass(frozen=True)
class Scene:
    scene_id: str
    visual: str
    duration: float
    kicker: str
    screen_title: str
    screen_line: str
    footer: str
    narration: str


def ensure_dir(path: Path) -> Path:
    path.mkdir(parents=True, exist_ok=True)
    return path


def clean_line(value: object) -> str:
    return " ".join(str(value).split())


def safe_token(value: object, fallback: str) -> str:
    raw = str(value).strip().lower()
    safe = "".join(ch if ch.isalnum() or ch in {"-", "_"} else "-" for ch in raw)
    safe = "-".join(part for part in safe.split("-") if part)
    safe = "_".join(part for part in safe.split("_") if part)
    return safe or fallback


def artifact_slug(meta: dict) -> str:
    return safe_token(meta.get("artifact_slug", DEFAULT_ARTIFACT_SLUG), DEFAULT_ARTIFACT_SLUG)


def config_sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def parse_size(value: str) -> tuple[int, int]:
    match = re.fullmatch(r"(\d+)x(\d+)", value.strip())
    if not match:
        raise argparse.ArgumentTypeError("size must look like 1920x1080")
    return (int(match.group(1)), int(match.group(2)))


def locate_executable(name: str, env_name: str, explicit: str | None) -> str | None:
    if explicit:
        return explicit
    env_value = os.environ.get(env_name)
    if env_value:
        return env_value
    return shutil.which(name)


def wav_duration(path: Path) -> float:
    with wave.open(str(path), "rb") as fh:
        return fh.getnframes() / float(fh.getframerate())


def load_config(path: Path) -> tuple[dict, list[Scene]]:
    data = tomllib.loads(path.read_text(encoding="utf-8"))
    scenes = []
    for raw in data.get("scenes", []):
        scene_id = safe_token(raw["id"], "scene")
        scenes.append(
            Scene(
                scene_id=scene_id,
                visual=safe_token(raw["visual"], "horizon"),
                duration=float(raw["duration"]),
                kicker=clean_line(raw["kicker"]),
                screen_title=clean_line(raw["screen_title"]),
                screen_line=clean_line(raw["screen_line"]),
                footer=clean_line(raw["footer"]),
                narration="\n".join(line.strip() for line in str(raw["narration"]).strip().splitlines() if line.strip()),
            )
        )
    errors = validate_config(data.get("meta", {}), scenes)
    if errors:
        raise SystemExit("invalid motion presentation config:\n- " + "\n- ".join(errors))
    return data.get("meta", {}), scenes


def validate_config(meta: dict, scenes: list[Scene]) -> list[str]:
    errors: list[str] = []
    if len(scenes) < 8:
        errors.append("motion presentation needs at least 8 scenes")
    ids = [scene.scene_id for scene in scenes]
    duplicate_ids = sorted({scene_id for scene_id in ids if ids.count(scene_id) > 1})
    if duplicate_ids:
        errors.append(f"duplicate scene ids: {', '.join(duplicate_ids)}")
    target_seconds = float(meta.get("target_seconds", 0) or 0)
    planned_seconds = sum(scene.duration for scene in scenes)
    if target_seconds and planned_seconds < target_seconds:
        errors.append(f"planned duration {planned_seconds:.1f}s is below target {target_seconds:.1f}s")
    for scene in scenes:
        if not TOKEN_RE.fullmatch(scene.scene_id):
            errors.append(f"scene id is not path-safe: {scene.scene_id}")
        if scene.visual not in ALLOWED_VISUALS:
            errors.append(f"scene {scene.scene_id} has unknown visual: {scene.visual}")
        if scene.duration <= 0:
            errors.append(f"scene {scene.scene_id} duration must be positive")
        if len(scene.screen_title) > 88:
            errors.append(f"scene {scene.scene_id} screen title is too long")
        if len(scene.screen_line) > 78:
            errors.append(f"scene {scene.scene_id} screen line is too long")
        if len(scene.footer) > 118:
            errors.append(f"scene {scene.scene_id} footer is too long")
        if word_count(scene.narration) < 90:
            errors.append(f"scene {scene.scene_id} narration is too thin")
        joined = " ".join([scene.kicker, scene.screen_title, scene.screen_line, scene.footer, scene.narration]).lower()
        if "todo" in joined or "placeholder" in joined:
            errors.append(f"scene {scene.scene_id} contains placeholder language")
    audit = phrase_audit(scenes)
    if audit["repeated_four_grams"]:
        errors.append(f"voiceover repeats four-word phrases: {audit['repeated_four_grams'][:3]}")
    return errors


def write_text_artifacts(meta: dict, scenes: list[Scene], out_dir: Path, timings: list[dict] | None = None) -> None:
    script_lines = [f"# {meta.get('title', 'Latticra motion presentation')}", ""]
    cues = []
    start = 0.0
    piper_dir = ensure_dir(out_dir / "piper-scenes")
    for idx, scene in enumerate(scenes, 1):
        duration = scene.duration
        if timings:
            duration = float(timings[idx - 1]["duration"])
            start = float(timings[idx - 1]["start"])
        end = start + duration
        script_lines.extend([f"## {idx:02d}. {scene.screen_title}", scene.narration, ""])
        (piper_dir / f"scene-{idx:02d}-{scene.scene_id}.txt").write_text(scene.narration + "\n", encoding="utf-8")
        cues.append(f"{idx}\n{format_srt_time(start)} --> {format_srt_time(end)}\n{scene.screen_title}\n")
        if not timings:
            start = end
    (out_dir / "voiceover-script.txt").write_text("\n".join(script_lines), encoding="utf-8")
    (out_dir / "voiceover-cues.srt").write_text("\n".join(cues), encoding="utf-8")


def format_srt_time(seconds: float) -> str:
    millis = int(round(seconds * 1000))
    h = millis // 3_600_000
    millis %= 3_600_000
    m = millis // 60_000
    millis %= 60_000
    s = millis // 1000
    ms = millis % 1000
    return f"{h:02d}:{m:02d}:{s:02d},{ms:03d}"


def word_count(text: str) -> int:
    return len(re.findall(r"[A-Za-z0-9][A-Za-z0-9'-]*", text))


def phrase_audit(scenes: list[Scene]) -> dict:
    text = " ".join(scene.narration.lower() for scene in scenes)
    words = re.findall(r"[a-z0-9][a-z0-9'-]*", text)
    counts = Counter(tuple(words[i : i + 4]) for i in range(max(0, len(words) - 3)))
    repeated = [
        {"phrase": " ".join(phrase), "count": count}
        for phrase, count in counts.most_common()
        if count >= 3 and not set(phrase) <= {"the", "of", "and", "to", "a", "in", "is"}
    ][:20]
    return {"word_count": len(words), "repeated_four_grams": repeated}


def build_storyboard(meta: dict, scenes: list[Scene], out_dir: Path) -> dict:
    total = sum(scene.duration for scene in scenes)
    audit = phrase_audit(scenes)
    storyboard = {
        "title": meta.get("title"),
        "artifact_slug": artifact_slug(meta),
        "scene_count": len(scenes),
        "planned_seconds": total,
        "word_count": audit["word_count"],
        "phrase_audit": audit,
        "scenes": [
            {
                "id": scene.scene_id,
                "visual": scene.visual,
                "duration": scene.duration,
                "kicker": scene.kicker,
                "screen_title": scene.screen_title,
                "screen_line": scene.screen_line,
                "footer": scene.footer,
                "narration_word_count": word_count(scene.narration),
            }
            for scene in scenes
        ],
    }
    (out_dir / "storyboard.json").write_text(json.dumps(storyboard, indent=2), encoding="utf-8")
    write_text_artifacts(meta, scenes, out_dir)
    return storyboard


class FontBook:
    def __init__(self) -> None:
        self.cache: dict[tuple[str, int], ImageFont.FreeTypeFont | ImageFont.ImageFont] = {}
        self.paths = {
            "display": [
                "/System/Library/Fonts/Supplemental/Georgia.ttf",
                "/System/Library/Fonts/Supplemental/Times New Roman.ttf",
                "/System/Library/Fonts/Times.ttc",
            ],
            "sans": [
                "/System/Library/Fonts/SFNS.ttf",
                "/System/Library/Fonts/Supplemental/Arial.ttf",
                "/Library/Fonts/Arial.ttf",
            ],
            "mono": [
                "/System/Library/Fonts/Menlo.ttc",
                "/System/Library/Fonts/SFNSMono.ttf",
                "/System/Library/Fonts/Supplemental/Courier New.ttf",
            ],
        }

    def get(self, family: str, size: int) -> ImageFont.FreeTypeFont | ImageFont.ImageFont:
        key = (family, size)
        if key in self.cache:
            return self.cache[key]
        for candidate in self.paths.get(family, []) + self.paths["sans"]:
            if Path(candidate).exists():
                try:
                    font = ImageFont.truetype(candidate, size=size)
                    self.cache[key] = font
                    return font
                except OSError:
                    pass
        font = ImageFont.load_default()
        self.cache[key] = font
        return font


def mix(a: tuple[int, int, int], b: tuple[int, int, int], t: float) -> tuple[int, int, int]:
    t = max(0.0, min(1.0, t))
    return tuple(int(a[i] + (b[i] - a[i]) * t) for i in range(3))


def with_alpha(color: tuple[int, int, int], alpha: int) -> tuple[int, int, int, int]:
    return (color[0], color[1], color[2], alpha)


def ease(t: float) -> float:
    t = max(0.0, min(1.0, t))
    return t * t * (3 - 2 * t)


class MotionRenderer:
    def __init__(self, size: tuple[int, int]) -> None:
        self.w, self.h = size
        self.fonts = FontBook()
        self.safe_left = int(self.w * 0.065)
        self.safe_top = int(self.h * 0.075)

    def font(self, family: str, size: int) -> ImageFont.FreeTypeFont | ImageFont.ImageFont:
        scale = self.w / 1920.0
        return self.fonts.get(family, max(8, int(round(size * scale))))

    def render(self, scene: Scene, scene_index: int, scene_t: float, total_t: float) -> Image.Image:
        img = Image.new("RGB", (self.w, self.h), BLACK)
        draw = ImageDraw.Draw(img, "RGBA")
        self.background(draw, scene_index, scene_t, total_t)
        visual = getattr(self, f"visual_{scene.visual}", None)
        if visual is None:
            raise SystemExit(f"unknown motion visual: {scene.visual}")
        visual(draw, scene, scene_index, scene_t, total_t)
        self.text_layer(draw, scene, scene_index, scene_t)
        return img

    def background(self, draw: ImageDraw.ImageDraw, scene_index: int, scene_t: float, total_t: float) -> None:
        for y in range(0, self.h, 4):
            ratio = y / self.h
            base = mix((6, 9, 15), (14, 18, 24), ratio)
            draw.rectangle((0, y, self.w, y + 4), fill=(*base, 255))
        accent = [GREEN, AMBER, BLUE, CYAN, VIOLET, RED][scene_index % 6]
        for i in range(78):
            x = (i * 211 + scene_index * 73) % self.w
            y = (i * 137 + scene_index * 97) % self.h
            drift = math.sin(total_t * 0.17 + i * 1.7) * 18
            r = 1 + (i % 3)
            alpha = 40 + (i % 5) * 15
            draw.ellipse((x + drift, y, x + drift + r, y + r), fill=with_alpha(mix(accent, INK, 0.45), alpha))
        for i in range(9):
            y = int(self.h * (0.18 + i * 0.08) + math.sin(total_t * 0.1 + i) * 8)
            alpha = 24 if i % 2 else 38
            draw.line((0, y, self.w, y + int(math.sin(i) * 20)), fill=with_alpha(mix(accent, BLACK, 0.45), alpha), width=1)

    def text_layer(self, draw: ImageDraw.ImageDraw, scene: Scene, scene_index: int, scene_t: float) -> None:
        accent = [GREEN, AMBER, BLUE, CYAN, VIOLET, RED][scene_index % 6]
        p = ease(min(scene_t / 2.2, 1.0))
        x = self.safe_left
        y = self.safe_top
        panel_w = int(self.w * 0.56)
        overlay = Image.new("RGBA", (self.w, self.h), (0, 0, 0, 0))
        od = ImageDraw.Draw(overlay, "RGBA")
        for i in range(panel_w):
            alpha = int(190 * (1 - i / panel_w) ** 1.4)
            od.line((i, 0, i, self.h), fill=(4, 7, 11, alpha))
        draw._image.paste(Image.alpha_composite(draw._image.convert("RGBA"), overlay).convert("RGB"))

        marker = int(12 * self.w / 1920)
        draw.rounded_rectangle((x, y, x + marker, y + marker), radius=marker // 3, fill=with_alpha(accent, int(230 * p)))
        draw.text((x + marker + 18, y - 2), scene.kicker.upper(), font=self.font("mono", 18), fill=with_alpha(mix(accent, INK, 0.35), int(230 * p)))

        title_y = y + int(54 * self.h / 1080)
        title_font = self.font("display", 58)
        self.draw_wrapped(draw, scene.screen_title, x, title_y, title_font, with_alpha(INK, int(245 * p)), panel_w, 2, 10)

        line_y = title_y + int(158 * self.h / 1080)
        self.draw_wrapped(draw, scene.screen_line, x, line_y, self.font("sans", 28), with_alpha(mix(INK, accent, 0.18), int(225 * p)), int(panel_w * 0.82), 2, 7)

        footer_y = int(self.h * 0.88)
        draw.line((x, footer_y - 24, x + int(panel_w * 0.62), footer_y - 24), fill=with_alpha(accent, 150), width=2)
        self.draw_wrapped(draw, scene.footer, x, footer_y, self.font("sans", 20), with_alpha(MUTED, int(210 * p)), int(panel_w * 0.74), 2, 5)

        page = f"{scene_index + 1:02d}"
        draw.text((self.w - self.safe_left - 58, self.h - self.safe_top - 30), page, font=self.font("mono", 20), fill=with_alpha(mix(accent, INK, 0.2), 190))

    def draw_wrapped(
        self,
        draw: ImageDraw.ImageDraw,
        text: str,
        x: int,
        y: int,
        font: ImageFont.ImageFont,
        fill: tuple[int, int, int, int],
        width: int,
        max_lines: int,
        line_gap: int,
    ) -> None:
        words = text.split()
        lines: list[str] = []
        current = ""
        for word in words:
            test = f"{current} {word}".strip()
            if draw.textbbox((0, 0), test, font=font)[2] <= width or not current:
                current = test
            else:
                lines.append(current)
                current = word
        if current:
            lines.append(current)
        lines = lines[:max_lines]
        for idx, line in enumerate(lines):
            draw.text((x, y + idx * (font.size + line_gap)), line, font=font, fill=fill)

    def visual_horizon(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        accent = GREEN
        cx = int(self.w * 0.71)
        horizon = int(self.h * 0.58)
        for ring in range(9):
            r = int((ring + 1) * self.w * 0.045 + (t * 11) % 32)
            alpha = max(18, 130 - ring * 12)
            draw.ellipse((cx - r, horizon - r // 3, cx + r, horizon + r // 3), outline=with_alpha(accent, alpha), width=2)
        for i in range(18):
            a = i / 18 * math.tau + t * 0.03
            x2 = cx + math.cos(a) * self.w * 0.32
            y2 = horizon + math.sin(a) * self.h * 0.2
            draw.line((cx, horizon, x2, y2), fill=with_alpha(mix(accent, BLUE, i / 18), 42), width=1)
        self.pulse(draw, cx, horizon, 26 + math.sin(t * 2) * 5, accent, 210)

    def visual_veils(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        colors = [AMBER, RED, VIOLET]
        for band in range(7):
            y = int(self.h * (0.22 + band * 0.08))
            offset = math.sin(t * 0.35 + band) * 80
            pts = []
            for step in range(0, self.w + 120, 120):
                pts.append((step, y + math.sin(step * 0.006 + t * 0.7 + band) * 35 + offset))
            for a, b in zip(pts, pts[1:]):
                draw.line((*a, *b), fill=with_alpha(colors[band % 3], 90), width=7)
        for i, label in enumerate(["intent", "authority", "effect"]):
            x = int(self.w * (0.63 + i * 0.1))
            y = int(self.h * (0.62 + math.sin(t * 0.45 + i) * 0.045))
            self.ghost_label(draw, label, x, y, colors[i], 120)

    def visual_intake(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        y = int(self.h * 0.56)
        start_x = int(self.w * 0.53)
        gate_x = int(self.w * 0.71)
        end_x = int(self.w * 0.9)
        draw.line((start_x, y, end_x, y), fill=with_alpha(BLUE, 130), width=4)
        draw.line((gate_x, y - 130, gate_x, y + 130), fill=with_alpha(AMBER, 190), width=3)
        for i in range(5):
            phase = (t * 0.13 + i / 5) % 1
            x = start_x + int((end_x - start_x) * phase)
            color = GREEN if x > gate_x else BLUE
            self.pulse(draw, x, y + int(math.sin(phase * math.tau) * 24), 13, color, 205)
        self.right_label(draw, "request", start_x, y - 92, BLUE)
        self.right_label(draw, "review", gate_x, y - 176, AMBER)
        self.right_label(draw, "record", end_x - 92, y + 68, GREEN)

    def visual_strata(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        colors = [GREEN, CYAN, BLUE, VIOLET, AMBER]
        left = int(self.w * 0.51)
        right = int(self.w * 0.94)
        top = int(self.h * 0.22)
        for layer in range(6):
            y = top + layer * int(self.h * 0.095)
            amp = 20 + layer * 5
            pts = []
            for x in range(left, right + 1, 70):
                pts.append((x, int(y + math.sin(x * 0.008 + t * 0.45 + layer) * amp)))
            for a, b in zip(pts, pts[1:]):
                draw.line((*a, *b), fill=with_alpha(colors[layer % len(colors)], 105), width=4)
        for i in range(9):
            x = left + (right - left) * i / 8
            y = top + int(self.h * (0.21 + 0.13 * math.sin(t * 0.22 + i)))
            self.pulse(draw, int(x), int(y), 10, colors[i % len(colors)], 180)

    def visual_decision(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        x0 = int(self.w * 0.53)
        y0 = int(self.h * 0.52)
        steps = [("ask", BLUE), ("classify", CYAN), ("allow", GREEN), ("deny", RED), ("report", AMBER)]
        for i, (label, color) in enumerate(steps):
            x = x0 + i * int(self.w * 0.085)
            y = y0 + int(math.sin(t * 0.45 + i) * 46)
            if i:
                px = x0 + (i - 1) * int(self.w * 0.085)
                py = y0 + int(math.sin(t * 0.45 + i - 1) * 46)
                draw.line((px, py, x, y), fill=with_alpha(color, 115), width=3)
            self.pulse(draw, x, y, 16, color, 220)
            self.right_label(draw, label, x - 32, y + 30, color)

    def visual_seal(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        cx = int(self.w * 0.73)
        cy = int(self.h * 0.53)
        for i in range(7):
            r = int(self.w * (0.035 + i * 0.024))
            start = int((t * 20 + i * 37) % 360)
            draw.arc((cx - r, cy - r, cx + r, cy + r), start, start + 245, fill=with_alpha(mix(GREEN, AMBER, i / 6), 170), width=3)
        for i in range(5):
            y = int(self.h * (0.28 + i * 0.105))
            x1 = int(self.w * 0.54)
            x2 = int(self.w * 0.66)
            draw.line((x1, y, x2, y), fill=with_alpha(CYAN, 120), width=3)
            self.pulse(draw, x2 + int(math.sin(t + i) * 18), y, 8, GREEN, 175)
        self.right_label(draw, "receipt path", cx - 54, cy + int(self.h * 0.18), GREEN)

    def visual_nucleus(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        cx = int(self.w * 0.74)
        cy = int(self.h * 0.53)
        self.pulse(draw, cx, cy, 34, AMBER, 230)
        for orbit in range(4):
            rx = int(self.w * (0.075 + orbit * 0.038))
            ry = int(self.h * (0.045 + orbit * 0.029))
            draw.ellipse((cx - rx, cy - ry, cx + rx, cy + ry), outline=with_alpha(mix(AMBER, BLUE, orbit / 4), 105), width=2)
            for node in range(3):
                a = t * (0.25 + orbit * 0.08) + node * math.tau / 3 + orbit
                x = cx + math.cos(a) * rx
                y = cy + math.sin(a) * ry
                self.pulse(draw, int(x), int(y), 8, mix(BLUE, GREEN, node / 3), 190)
        self.right_label(draw, "supervisor", cx - 54, cy + 52, AMBER)

    def visual_language(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        mono = self.font("mono", 18)
        snippets = ["report", "span", "edge", "node", "lir", "lat", "fyr"]
        for i in range(20):
            x = int(self.w * (0.52 + (i % 5) * 0.078))
            y = int(self.h * (0.22 + (i // 5) * 0.105 + math.sin(t * 0.5 + i) * 0.018))
            text = snippets[(i + idx) % len(snippets)]
            draw.text((x, y), text, font=mono, fill=with_alpha(mix(CYAN, INK, 0.35), 85 + (i % 4) * 28))
        for i in range(10):
            a = t * 0.2 + i * 0.63
            x = int(self.w * 0.72 + math.cos(a) * self.w * 0.18)
            y = int(self.h * 0.54 + math.sin(a * 1.3) * self.h * 0.18)
            self.pulse(draw, x, y, 9, [GREEN, CYAN, BLUE][i % 3], 185)

    def visual_umbrella(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        cx = int(self.w * 0.74)
        cy = int(self.h * 0.5)
        labels = [("Model-1", GREEN), ("Phase1", AMBER), ("Fyr", CYAN), ("l2", BLUE), ("l3", VIOLET)]
        for i, (label, color) in enumerate(labels):
            a = t * 0.09 + i * math.tau / len(labels)
            x = int(cx + math.cos(a) * self.w * 0.18)
            y = int(cy + math.sin(a) * self.h * 0.19)
            draw.line((cx, cy, x, y), fill=with_alpha(color, 72), width=2)
            self.pulse(draw, x, y, 18, color, 215)
            self.right_label(draw, label, x + 24, y - 12, color)
        self.pulse(draw, cx, cy, 25, INK, 190)
        self.right_label(draw, "Latticra", cx - 48, cy + 38, INK)

    def visual_operator(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        x = int(self.w * 0.53)
        y = int(self.h * 0.25)
        w = int(self.w * 0.39)
        h = int(self.h * 0.5)
        draw.rounded_rectangle((x, y, x + w, y + h), radius=18, outline=with_alpha(GREEN, 130), fill=(7, 13, 16, 185), width=2)
        rows = [("request", BLUE), ("capability", CYAN), ("boundary", AMBER), ("decision", GREEN), ("receipt", VIOLET)]
        for i, (label, color) in enumerate(rows):
            yy = y + int(h * (0.18 + i * 0.14))
            draw.line((x + 44, yy, x + w - 52, yy), fill=with_alpha(color, 80), width=2)
            self.pulse(draw, x + 38 + int(((t * 40) + i * 47) % (w - 130)), yy, 8, color, 190)
            self.right_label(draw, label, x + w - 160, yy - 34, color)

    def visual_research(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        cx = int(self.w * 0.75)
        cy = int(self.h * 0.51)
        for i in range(11):
            r = int(self.w * (0.025 + i * 0.019))
            draw.arc((cx - r, cy - r, cx + r, cy + r), int(t * 9 + i * 19), int(t * 9 + i * 19 + 118), fill=with_alpha(mix(VIOLET, CYAN, i / 10), 135), width=2)
        for i in range(24):
            a = i * 2.399 + t * 0.08
            r = math.sqrt(i / 24) * self.w * 0.22
            x = int(cx + math.cos(a) * r)
            y = int(cy + math.sin(a) * r * 0.62)
            self.pulse(draw, x, y, 5 + i % 4, mix(CYAN, VIOLET, i / 24), 155)
        self.right_label(draw, "simulation_proven = 0", cx - 116, cy + int(self.h * 0.22), AMBER)

    def visual_delivery(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        base_y = int(self.h * 0.68)
        left = int(self.w * 0.52)
        right = int(self.w * 0.93)
        for lane in range(5):
            y = base_y - lane * int(self.h * 0.085)
            draw.line((left, y, right, y), fill=with_alpha(mix(AMBER, GREEN, lane / 4), 100), width=3)
            x = left + int(((t * 36 + lane * 132) % (right - left)))
            self.pulse(draw, x, y, 10, mix(AMBER, GREEN, lane / 4), 210)
        self.right_label(draw, "staging", left + 20, base_y + 38, AMBER)
        self.right_label(draw, "evidence", int((left + right) / 2) - 52, base_y + 38, GREEN)
        self.right_label(draw, "review", right - 92, base_y + 38, CYAN)

    def visual_roadmap(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        pts = [
            (int(self.w * 0.52), int(self.h * 0.66)),
            (int(self.w * 0.63), int(self.h * 0.46)),
            (int(self.w * 0.75), int(self.h * 0.59)),
            (int(self.w * 0.88), int(self.h * 0.34)),
        ]
        colors = [GREEN, CYAN, AMBER, VIOLET]
        for i in range(len(pts) - 1):
            draw.line((*pts[i], *pts[i + 1]), fill=with_alpha(colors[i], 135), width=5)
        progress = (t * 0.08) % 1
        for i, pt in enumerate(pts):
            self.pulse(draw, pt[0], pt[1], 18 + (6 if i / len(pts) < progress else 0), colors[i], 220)
        labels = ["v0.3 edge", "evidence", "import", "v0.4 edge"]
        for (x, y), label, color in zip(pts, labels, colors):
            self.right_label(draw, label, x - 42, y - 48, color)

    def visual_close(self, draw: ImageDraw.ImageDraw, scene: Scene, idx: int, t: float, total: float) -> None:
        cx = int(self.w * 0.74)
        cy = int(self.h * 0.52)
        for i in range(13):
            a = i * math.tau / 13 + t * 0.04
            r = int(self.w * (0.05 + 0.012 * i))
            x = int(cx + math.cos(a) * r)
            y = int(cy + math.sin(a) * r * 0.68)
            draw.line((cx, cy, x, y), fill=with_alpha(mix(GREEN, BLUE, i / 12), 45), width=2)
            self.pulse(draw, x, y, 8, mix(GREEN, BLUE, i / 12), 165)
        self.pulse(draw, cx, cy, 40 + math.sin(t * 1.6) * 6, GREEN, 225)

    def pulse(self, draw: ImageDraw.ImageDraw, x: int, y: int, r: float, color: tuple[int, int, int], alpha: int) -> None:
        r = int(r)
        draw.ellipse((x - r, y - r, x + r, y + r), outline=with_alpha(color, alpha // 2), width=2)
        draw.ellipse((x - r // 2, y - r // 2, x + r // 2, y + r // 2), fill=with_alpha(color, min(255, alpha)))

    def right_label(self, draw: ImageDraw.ImageDraw, text: str, x: int, y: int, color: tuple[int, int, int]) -> None:
        font = self.font("mono", 16)
        pad = 8
        box = draw.textbbox((x, y), text, font=font)
        draw.rounded_rectangle((box[0] - pad, box[1] - pad // 2, box[2] + pad, box[3] + pad // 2), radius=6, fill=(5, 8, 12, 145), outline=with_alpha(color, 95), width=1)
        draw.text((x, y), text, font=font, fill=with_alpha(mix(color, INK, 0.25), 215))

    def ghost_label(self, draw: ImageDraw.ImageDraw, text: str, x: int, y: int, color: tuple[int, int, int], alpha: int) -> None:
        draw.text((x, y), text, font=self.font("display", 34), fill=with_alpha(color, alpha))


def render_preview(meta: dict, scenes: list[Scene], out_dir: Path, size: tuple[int, int]) -> Path:
    renderer = MotionRenderer(size)
    preview_dir = ensure_dir(out_dir / "preview")
    thumbs = []
    for idx, scene in enumerate(scenes):
        img = renderer.render(scene, idx, scene.duration * 0.45, idx * 71.0)
        path = preview_dir / f"scene-{idx + 1:02d}-{scene.scene_id}.png"
        img.save(path)
        thumbs.append(img.resize((480, 270), Image.Resampling.LANCZOS))
    cols = 2 if len(thumbs) <= 8 else 4
    rows = math.ceil(len(thumbs) / cols)
    sheet = Image.new("RGB", (cols * 480, rows * 270), BLACK)
    for i, thumb in enumerate(thumbs):
        sheet.paste(thumb, ((i % cols) * 480, (i // cols) * 270))
    contact = preview_dir / "contact-sheet.png"
    sheet.save(contact)
    write_text_artifacts(meta, scenes, out_dir)
    return contact


def synthesize_voiceover(
    meta: dict,
    scenes: list[Scene],
    out_dir: Path,
    piper_bin: str | None,
    piper_model: str | None,
    piper_config: str | None,
) -> tuple[Path, list[dict]]:
    piper_bin = locate_executable("piper", "PIPER_BIN", piper_bin)
    piper_python = os.environ.get("PIPER_PYTHON") or sys.executable
    piper_model = piper_model or os.environ.get("PIPER_MODEL") or os.environ.get("PIPER_VOICE")
    if not piper_model:
        raise SystemExit("Piper model was not found. Set PIPER_MODEL=/path/to/voice.onnx.")
    if not Path(piper_model).exists():
        raise SystemExit(f"Piper model does not exist: {piper_model}")

    voice_dir = ensure_dir(out_dir / "voiceover")
    wavs = []
    for idx, scene in enumerate(scenes, 1):
        wav_path = voice_dir / f"scene-{idx:02d}-{scene.scene_id}.wav"
        if piper_bin:
            cmd = [piper_bin, "--model", piper_model, "--output_file", str(wav_path)]
            if piper_config:
                cmd.extend(["--config", piper_config])
            subprocess.run(cmd, input=scene.narration + "\n", text=True, check=True)
        else:
            cmd = [piper_python, "-m", "piper", "-m", piper_model, "-f", str(wav_path), "--", scene.narration]
            subprocess.run(cmd, check=True)
        wavs.append(wav_path)

    slug = artifact_slug(meta)
    combined = voice_dir / f"{slug}-voiceover.wav"
    timings = []
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
            audio_seconds = params.nframes / float(params.framerate)
            target = max(scene.duration, audio_seconds + 1.0)
            out_wav.writeframes(frames)
            pad_frames = max(0, int(round(target * params.framerate)) - params.nframes)
            if pad_frames:
                out_wav.writeframes(b"\x00" * pad_frames * params.nchannels * params.sampwidth)
            timings.append({"id": scene.scene_id, "start": start, "planned_duration": scene.duration, "audio_duration": audio_seconds, "duration": target})
            start += target
    (voice_dir / "voiceover-timing.json").write_text(json.dumps({"total_seconds": start, "scenes": timings}, indent=2), encoding="utf-8")
    write_text_artifacts(meta, scenes, out_dir, timings)
    return combined, timings


def render_video(
    meta: dict,
    scenes: list[Scene],
    timings: list[dict],
    out_dir: Path,
    size: tuple[int, int],
    fps: int,
    ffmpeg_bin: str | None,
    voiceover: Path,
) -> Path:
    ffmpeg = locate_executable("ffmpeg", "FFMPEG_BIN", ffmpeg_bin)
    if not ffmpeg:
        raise SystemExit("ffmpeg was not found. Set FFMPEG_BIN=/path/to/ffmpeg.")
    slug = artifact_slug(meta)
    video_dir = ensure_dir(out_dir / "video")
    video_path = video_dir / f"{slug}-presentation.mp4"
    renderer = MotionRenderer(size)
    cmd = [
        ffmpeg,
        "-y",
        "-f",
        "rawvideo",
        "-pix_fmt",
        "rgb24",
        "-s",
        f"{size[0]}x{size[1]}",
        "-r",
        str(fps),
        "-i",
        "-",
        "-i",
        str(voiceover),
        "-c:v",
        "libx264",
        "-preset",
        "veryfast",
        "-crf",
        "18",
        "-pix_fmt",
        "yuv420p",
        "-c:a",
        "aac",
        "-b:a",
        "128k",
        "-shortest",
        "-movflags",
        "+faststart",
        str(video_path),
    ]
    total_frames = int(round(sum(float(t["duration"]) for t in timings) * fps))
    scene_ranges = []
    frame_start = 0
    for timing in timings:
        frame_count = int(round(float(timing["duration"]) * fps))
        scene_ranges.append((frame_start, frame_start + frame_count, timing))
        frame_start += frame_count
    with subprocess.Popen(cmd, stdin=subprocess.PIPE) as proc:
        assert proc.stdin is not None
        scene_idx = 0
        for frame in range(total_frames):
            while scene_idx < len(scene_ranges) - 1 and frame >= scene_ranges[scene_idx][1]:
                scene_idx += 1
            start_frame, _, timing = scene_ranges[scene_idx]
            local_t = (frame - start_frame) / fps
            total_t = frame / fps
            img = renderer.render(scenes[scene_idx], scene_idx, local_t, total_t)
            proc.stdin.write(img.tobytes())
            if frame % (fps * 30) == 0:
                print(f"rendering {frame // fps:04d}/{total_frames // fps} seconds", flush=True)
        proc.stdin.close()
        code = proc.wait()
    if code != 0:
        raise SystemExit(f"ffmpeg exited with status {code}")
    return video_path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("mode", choices=["storyboard", "preview", "voiceover", "render"])
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG)
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT)
    parser.add_argument("--size", type=parse_size, default=DEFAULT_SIZE)
    parser.add_argument("--fps", type=int, default=DEFAULT_FPS)
    parser.add_argument("--piper-bin")
    parser.add_argument("--piper-model")
    parser.add_argument("--piper-config")
    parser.add_argument("--ffmpeg-bin")
    args = parser.parse_args()

    meta, scenes = load_config(args.config)
    out_dir = ensure_dir(args.out)
    storyboard = build_storyboard(meta, scenes, out_dir)
    manifest = {
        "mode": args.mode,
        "config": str(args.config),
        "config_sha256": config_sha256(args.config),
        "out": str(out_dir),
        "storyboard": str(out_dir / "storyboard.json"),
        "script": str(out_dir / "voiceover-script.txt"),
        "srt": str(out_dir / "voiceover-cues.srt"),
        "scene_count": storyboard["scene_count"],
        "planned_seconds": storyboard["planned_seconds"],
        "word_count": storyboard["word_count"],
        "artifact_slug": storyboard["artifact_slug"],
    }
    if args.mode in {"preview", "render"}:
        contact = render_preview(meta, scenes, out_dir, args.size)
        manifest["contact_sheet"] = str(contact)
    if args.mode in {"voiceover", "render"}:
        voiceover, timings = synthesize_voiceover(meta, scenes, out_dir, args.piper_bin, args.piper_model, args.piper_config)
        manifest["voiceover_wav"] = str(voiceover)
        manifest["actual_seconds"] = sum(float(t["duration"]) for t in timings)
        if args.mode == "render":
            video = render_video(meta, scenes, timings, out_dir, args.size, args.fps, args.ffmpeg_bin, voiceover)
            manifest["video"] = str(video)
    manifest_path = out_dir / f"{args.mode}-manifest.json"
    manifest["manifest"] = str(manifest_path)
    manifest_path.write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    print(json.dumps(manifest, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

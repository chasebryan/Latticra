#!/usr/bin/env python3
"""Generate Latticra social-card PNG assets.

The cards are intentionally deterministic and use the official emblem at
docs/assets/latticra-official-emblem.png.
"""

from __future__ import annotations

from pathlib import Path

from PIL import Image, ImageDraw, ImageFilter, ImageFont, ImageOps


ROOT = Path(__file__).resolve().parents[1]
OUT_DIR = ROOT / "assets" / "social"
REVIEW_DIR = OUT_DIR / "review"
EMBLEM_PATH = ROOT / "docs" / "assets" / "latticra-official-emblem.png"
WORDMARK_PATH = ROOT / "docs" / "assets" / "latticra-official-wordmark.jpeg"
BACKGROUND_SOURCE_PATH = OUT_DIR / "sources" / "latticra-glass-background-source-v1.png"

SCALE = 2
WIDTH = 1600
HEIGHT = 900

COLORS = {
    "bg": "#f7faf9",
    "ink": "#121417",
    "muted": "#5d6868",
    "line": "#dfe8e5",
    "card": "#ffffff",
    "teal": "#146b63",
    "blue": "#315e9e",
    "cyan": "#0ea5cf",
    "amber": "#b6812d",
    "rust": "#a1493f",
    "pale": "#cfe3df",
    "border": "#dbe4e1",
}

FONT_REGULAR = "/System/Library/Fonts/HelveticaNeue.ttc"
FONT_BOLD = "/System/Library/Fonts/Avenir Next.ttc"


def font(size: int, bold: bool = False) -> ImageFont.FreeTypeFont:
    return ImageFont.truetype(FONT_BOLD if bold else FONT_REGULAR, size * SCALE)


def xy(point: tuple[float, float]) -> tuple[int, int]:
    return (int(point[0] * SCALE), int(point[1] * SCALE))


def box(bounds: tuple[float, float, float, float]) -> tuple[int, int, int, int]:
    return (
        int(bounds[0] * SCALE),
        int(bounds[1] * SCALE),
        int(bounds[2] * SCALE),
        int(bounds[3] * SCALE),
    )


class Card:
    def __init__(self) -> None:
        self.image = Image.new("RGB", (WIDTH * SCALE, HEIGHT * SCALE), COLORS["bg"])
        self.draw = ImageDraw.Draw(self.image)

    def text(
        self,
        position: tuple[float, float],
        value: str,
        size: int,
        fill: str = COLORS["ink"],
        bold: bool = False,
        anchor: str | None = None,
        spacing: int = 7,
    ) -> None:
        self.draw.multiline_text(
            xy(position),
            value,
            font=font(size, bold),
            fill=fill,
            anchor=anchor,
            spacing=spacing * SCALE,
        )

    def line(self, points: list[tuple[float, float]], fill: str = COLORS["line"], width: int = 2) -> None:
        self.draw.line([xy(point) for point in points], fill=fill, width=width * SCALE, joint="curve")

    def rect(
        self,
        bounds: tuple[float, float, float, float],
        fill: str,
        outline: str | None = None,
        width: int = 1,
        radius: int = 0,
    ) -> None:
        self.draw.rounded_rectangle(
            box(bounds),
            radius=radius * SCALE,
            fill=fill,
            outline=outline,
            width=width * SCALE if outline else 1,
        )

    def circle(self, center: tuple[float, float], radius: int, fill: str) -> None:
        cx, cy = center
        self.draw.ellipse(
            box((cx - radius, cy - radius, cx + radius, cy + radius)),
            fill=fill,
        )

    def arrow(self, start: tuple[float, float], end: tuple[float, float], fill: str = COLORS["blue"]) -> None:
        sx, sy = start
        ex, ey = end
        self.draw.line((sx * SCALE, sy * SCALE, (ex - 28) * SCALE, ey * SCALE), fill=fill, width=5 * SCALE)
        self.draw.polygon(
            [xy((ex - 28, ey - 14)), xy((ex, ey)), xy((ex - 28, ey + 14))],
            fill=fill,
        )

    def add_lattice(self) -> None:
        top = [(430, 154), (610, 118), (790, 166), (980, 116), (1190, 168), (1400, 126), (1490, 152)]
        bottom = [(220, 720), (390, 650), (570, 706), (760, 622), (970, 704), (1160, 638), (1380, 716)]
        self.line(top)
        self.line(bottom)
        palette = [COLORS["teal"], COLORS["blue"], COLORS["amber"], COLORS["rust"]]
        for index, point in enumerate(top + bottom):
            self.circle(point, 7, palette[index % len(palette)])

    def add_header(self, eyebrow: str) -> None:
        emblem = Image.open(EMBLEM_PATH).convert("RGBA").resize((118 * SCALE, 118 * SCALE), Image.Resampling.LANCZOS)
        self.image.paste(emblem.convert("RGB"), xy((82, 56)), emblem)
        self.text((220, 108), "LATTICRA", 25, COLORS["muted"], bold=True)
        self.text((220, 144), eyebrow, 34, COLORS["ink"], bold=True)

    def add_footer(self) -> None:
        self.text((96, 832), "@Latticra", 25, COLORS["muted"], bold=True)
        self.text(
            (1504, 832),
            "Linux-native secure computing substrates",
            25,
            COLORS["muted"],
            bold=True,
            anchor="ra",
        )

    def save(self, filename: str) -> None:
        OUT_DIR.mkdir(parents=True, exist_ok=True)
        resized = self.image.resize((WIDTH, HEIGHT), Image.Resampling.LANCZOS)
        resized.save(OUT_DIR / filename, optimize=True)


def fitted_multiline_size(value: str, max_width: int, start_size: int, min_size: int, *, bold: bool = True) -> int:
    scratch = Image.new("RGB", (10, 10))
    draw = ImageDraw.Draw(scratch)
    for size in range(start_size, min_size - 1, -2):
        face = font(size, bold)
        if all(draw.textlength(line, font=face) / SCALE <= max_width for line in value.splitlines()):
            return size
    return min_size


def draw_title(card: Card, title: str, subtitle: str) -> None:
    card.text((96, 270), title, 82, bold=True)
    card.text((100, 350), subtitle, 35, COLORS["muted"])


def request_to_effect() -> None:
    card = Card()
    card.add_lattice()
    card.add_header("Boundary Literacy")
    draw_title(card, "Request to Effect", "Make authority visible before behavior becomes consequential.")
    cards = [
        (98, "Request", "Who asked?", COLORS["teal"]),
        (486, "Policy", "What rule applies?", COLORS["blue"]),
        (874, "Receipt", "What evidence remains?", COLORS["amber"]),
        (1262, "Gate", "What is allowed?", COLORS["rust"]),
    ]
    for x, label, subtext, color in cards:
        card.rect((x, 430, x + 240, 572), COLORS["card"], outline=COLORS["border"], width=2, radius=22)
        card.circle((x + 42, 478), 15, color)
        card.text((x + 76, 487), label, 34, bold=True)
        card.text((x + 42, 534), subtext, 24, COLORS["muted"], bold=True)
    for x in (358, 746, 1134):
        card.arrow((x, 501), (x + 96, 501))
    card.rect((410, 642, 1190, 766), COLORS["ink"], radius=28)
    card.text((464, 683), "Outcome: Effect or Denial", 37, "#ffffff", bold=True)
    card.text((464, 728), "Both should be legible.", 27, COLORS["pale"], bold=True)
    card.add_footer()
    card.save("latticra-request-to-effect-card.png")


def evidence_before_claims() -> None:
    card = Card()
    card.add_lattice()
    card.add_header("Evidence-Bound Build Log")
    draw_title(card, "Evidence Before Claims", "Public language should grow only as the review trail grows.")
    steps = [
        ("Contract", COLORS["teal"]),
        ("Implementation", COLORS["blue"]),
        ("Test", COLORS["amber"]),
        ("Report", COLORS["rust"]),
        ("Public claim", COLORS["cyan"]),
    ]
    start_x = 112
    for index, (label, color) in enumerate(steps):
        x = start_x + index * 294
        card.circle((x + 72, 512), 50, color)
        card.text((x + 72, 521), str(index + 1), 42, "#ffffff", bold=True, anchor="mm")
        card.text((x + 72, 600), label, 29, COLORS["ink"], bold=True, anchor="mm")
        if index < len(steps) - 1:
            card.arrow((x + 138, 512), (x + 244, 512))
    card.rect((414, 690, 1186, 760), COLORS["ink"], radius=24)
    card.text((800, 735), "Say what exists. Show where the evidence lives.", 31, "#ffffff", bold=True, anchor="mm")
    card.add_footer()
    card.save("latticra-evidence-before-claims-card.png")


def denial_is_legible() -> None:
    card = Card()
    card.add_lattice()
    card.add_header("Boundary Literacy")
    draw_title(card, "Denial Is Legible", "A system saying no should still teach the operator what happened.")
    left = (154, 454, 690, 672)
    right = (910, 454, 1446, 716)
    card.rect(left, COLORS["card"], outline=COLORS["border"], width=2, radius=26)
    card.rect(right, COLORS["ink"], radius=26)
    card.text((206, 520), "Not silence", 46, bold=True)
    card.text((206, 585), "A denied action should leave a\nclear reason and boundary.", 28, COLORS["muted"], bold=True, spacing=11)
    card.text((962, 520), "Useful evidence", 46, "#ffffff", bold=True)
    card.text((962, 582), "reason\nstatus\nnext safe step", 28, COLORS["pale"], bold=True, spacing=8)
    card.arrow((728, 563), (872, 563), COLORS["blue"])
    card.add_footer()
    card.save("latticra-denial-is-legible-card.png")


def q_seal_posture() -> None:
    card = Card()
    card.add_lattice()
    card.add_header("Cryptography Without Hype")
    draw_title(card, "Q-Seal Posture", "Quantum-resistant planning starts with limits, tests, and careful language.")
    items = [
        ("Inspectable", COLORS["teal"]),
        ("Testable", COLORS["blue"]),
        ("Portable", COLORS["amber"]),
        ("Limited", COLORS["rust"]),
        ("Not overclaimed", COLORS["cyan"]),
    ]
    for index, (label, color) in enumerate(items):
        x = 150 + (index % 3) * 430
        y = 454 + (index // 3) * 126
        width = 360 if index < 3 else 500
        card.rect((x, y, x + width, y + 92), COLORS["card"], outline=COLORS["border"], width=2, radius=24)
        card.circle((x + 48, y + 42), 15, color)
        card.text((x + 84, y + 46), label, 32, bold=True, anchor="lm")
    card.rect((314, 712, 1286, 772), COLORS["ink"], radius=22)
    card.text((800, 751), "Good security engineering starts with what is not yet proven.", 25, "#ffffff", bold=True, anchor="mm")
    card.add_footer()
    card.save("latticra-q-seal-posture-card.png")


def boundary_literacy_v2() -> None:
    card = Card()
    card.image = Image.new("RGB", (WIDTH * SCALE, HEIGHT * SCALE), "#f5f7f5")
    card.draw = ImageDraw.Draw(card.image)

    emblem = Image.open(EMBLEM_PATH).convert("RGBA").resize((148 * SCALE, 148 * SCALE), Image.Resampling.LANCZOS)
    card.image.paste(emblem.convert("RGB"), xy((96, 88)), emblem)
    card.text((276, 145), "LATTICRA", 28, COLORS["muted"], bold=True)
    card.text((276, 187), "Educational note", 34, COLORS["ink"], bold=True)

    card.text((96, 358), "Boundary\nLiteracy", 104, COLORS["ink"], bold=True, spacing=2)
    card.text(
        (100, 600),
        "Where request becomes authority,\nevidence should stay visible.",
        38,
        COLORS["muted"],
        spacing=12,
    )

    spine_x = 970
    card.line([(spine_x, 172), (spine_x, 724)], COLORS["blue"], 4)
    nodes = [
        (spine_x, 218, "request", "who asked?", COLORS["teal"]),
        (spine_x, 352, "authority", "what can move?", COLORS["blue"]),
        (spine_x, 486, "evidence", "what remains?", COLORS["amber"]),
        (spine_x, 620, "denial", "what stays closed?", COLORS["rust"]),
    ]
    for cx, cy, label, caption, color in nodes:
        card.circle((cx, cy), 16, color)
        card.text((cx + 56, cy - 12), label, 42, COLORS["ink"], bold=True)
        card.text((cx + 58, cy + 34), caption, 26, COLORS["muted"], bold=True)

    card.rect((1060, 732, 1460, 788), COLORS["ink"], radius=18)
    card.text((1260, 767), "Not more noise. Better boundaries.", 24, "#ffffff", bold=True, anchor="mm")
    card.add_footer()
    card.save("latticra-boundary-literacy-v2-card.png")


def boundary_literacy_v3() -> None:
    card = Card()
    card.image = Image.new("RGB", (WIDTH * SCALE, HEIGHT * SCALE), "#f6f8f7")
    card.draw = ImageDraw.Draw(card.image)

    emblem = Image.open(EMBLEM_PATH).convert("RGBA").resize((124 * SCALE, 124 * SCALE), Image.Resampling.LANCZOS)
    card.image.paste(emblem.convert("RGB"), xy((94, 74)), emblem)
    card.text((248, 128), "LATTICRA", 25, COLORS["muted"], bold=True)
    card.text((248, 166), "Educational Series / 01", 28, COLORS["ink"], bold=True)

    card.text((96, 330), "Boundary\nLiteracy", 95, COLORS["ink"], bold=True, spacing=0)
    card.text(
        (100, 582),
        "A useful system makes the transition\nfrom request to authority visible.",
        35,
        COLORS["muted"],
        spacing=10,
    )

    panel = (872, 112, 1464, 752)
    card.rect(panel, COLORS["card"], outline=COLORS["border"], width=2, radius=34)
    card.text((926, 184), "A boundary should answer:", 30, COLORS["muted"], bold=True)

    rows = [
        ("request", "who asked?", COLORS["teal"]),
        ("authority", "what can move?", COLORS["blue"]),
        ("evidence", "what remains?", COLORS["amber"]),
        ("denial", "what stays closed?", COLORS["rust"]),
    ]
    y = 278
    for index, (label, prompt, color) in enumerate(rows):
        if index:
            card.line([(926, y - 34), (1410, y - 34)], "#eef2f0", 2)
        card.circle((944, y + 18), 12, color)
        card.text((986, y), label, 42, COLORS["ink"], bold=True)
        card.text((986, y + 50), prompt, 25, COLORS["muted"], bold=True)
        y += 116

    card.line([(104, 720), (514, 720)], COLORS["blue"], 4)
    card.circle((104, 720), 7, COLORS["teal"])
    card.circle((514, 720), 7, COLORS["amber"])
    card.add_footer()
    card.save("latticra-boundary-literacy-v3-card.png")


def boundary_literacy_wordmark() -> None:
    wordmark_card(
        filename="latticra-boundary-literacy-wordmark-card.png",
        series="Educational Series / 01",
        title="Boundary Literacy",
        subtitle="Where request becomes authority, evidence should stay visible.",
        labels=[
            ("request", COLORS["teal"]),
            ("authority", COLORS["blue"]),
            ("evidence", COLORS["amber"]),
            ("denial", COLORS["rust"]),
        ],
    )


def wordmark_card(
    *,
    filename: str,
    series: str,
    title: str,
    subtitle: str,
    labels: list[tuple[str, str]],
) -> None:
    card = Card()
    card.image = Image.new("RGB", (WIDTH * SCALE, HEIGHT * SCALE), "#f7f9fb")
    card.draw = ImageDraw.Draw(card.image)

    wordmark = Image.open(WORDMARK_PATH).convert("RGB").resize((1500 * SCALE, 500 * SCALE), Image.Resampling.LANCZOS)
    card.image.paste(wordmark, xy((50, 0)))

    card.rect((96, 482, 1504, 820), "#ffffff", outline="#e3e9ed", width=2, radius=34)
    card.text((144, 568), title, 68, COLORS["ink"], bold=True)
    card.text((148, 645), subtitle, 34, COLORS["muted"])

    start_x = 152
    y = 750
    step = 1320 / max(len(labels), 1)
    for index, (label, color) in enumerate(labels):
        x = start_x + index * step
        card.circle((x, y), 9, color)
        card.text((x + 28, y - 16), label, 27, COLORS["ink"], bold=True)
        if index < len(labels) - 1:
            next_x = start_x + (index + 1) * step
            card.line([(x + 150, y), (next_x - 40, y)], "#cfd9df", 2)

    card.text((1504, 866), series, 22, COLORS["muted"], bold=True, anchor="ra")
    card.save(filename)


def denial_is_legible_wordmark() -> None:
    wordmark_card(
        filename="latticra-denial-is-legible-wordmark-card.png",
        series="Educational Series / 02",
        title="Denial Is Legible",
        subtitle="A system saying no should still teach the operator what happened.",
        labels=[
            ("reason", COLORS["teal"]),
            ("status", COLORS["blue"]),
            ("boundary", COLORS["amber"]),
            ("next safe step", COLORS["rust"]),
        ],
    )


def evidence_before_claims_wordmark() -> None:
    wordmark_card(
        filename="latticra-evidence-before-claims-wordmark-card.png",
        series="Educational Series / 03",
        title="Evidence Before Claims",
        subtitle="Public language should grow only as the review trail grows.",
        labels=[
            ("contract", COLORS["teal"]),
            ("test", COLORS["blue"]),
            ("report", COLORS["amber"]),
            ("claim", COLORS["rust"]),
        ],
    )


def q_seal_posture_wordmark() -> None:
    wordmark_card(
        filename="latticra-q-seal-posture-wordmark-card.png",
        series="Educational Series / 04",
        title="Cryptography Without Hype",
        subtitle="Quantum-resistant planning starts with limits, tests, and careful language.",
        labels=[
            ("inspectable", COLORS["teal"]),
            ("testable", COLORS["blue"]),
            ("portable", COLORS["amber"]),
            ("not overclaimed", COLORS["rust"]),
        ],
    )


def glass_rect(
    image: Image.Image,
    bounds: tuple[int, int, int, int],
    *,
    radius: int,
    fill: tuple[int, int, int, int],
    outline: tuple[int, int, int, int] | None = None,
    shadow: tuple[int, int] = (0, 18),
    blur: int = 24,
) -> None:
    shadow_layer = Image.new("RGBA", image.size, (0, 0, 0, 0))
    shadow_draw = ImageDraw.Draw(shadow_layer)
    shifted = (bounds[0] + shadow[0], bounds[1] + shadow[1], bounds[2] + shadow[0], bounds[3] + shadow[1])
    shadow_draw.rounded_rectangle(shifted, radius=radius, fill=(35, 70, 100, 28))
    image.alpha_composite(shadow_layer.filter(ImageFilter.GaussianBlur(blur)))

    overlay = Image.new("RGBA", image.size, (0, 0, 0, 0))
    draw = ImageDraw.Draw(overlay)
    draw.rounded_rectangle(bounds, radius=radius, fill=fill, outline=outline, width=2 if outline else 1)
    image.alpha_composite(overlay)


def vertical_gradient(size: tuple[int, int], top: tuple[int, int, int, int], bottom: tuple[int, int, int, int]) -> Image.Image:
    width, height = size
    strip = Image.new("RGBA", (1, height), top)
    pixels = strip.load()
    for y in range(height):
        t = y / max(height - 1, 1)
        pixels[0, y] = tuple(int(top[index] + (bottom[index] - top[index]) * t) for index in range(4))
    return strip.resize((width, height), Image.Resampling.BICUBIC)


def add_soft_tile(
    canvas: Image.Image,
    center: tuple[float, float],
    size: tuple[float, float],
    angle: float,
    *,
    radius: int = 34,
    fill: tuple[int, int, int, int] = (255, 255, 255, 128),
    outline: tuple[int, int, int, int] = (255, 255, 255, 190),
    shadow: tuple[int, int, int, int] = (39, 92, 130, 24),
) -> None:
    scale = SCALE
    pad = 56 * scale
    width = int(size[0] * scale)
    height = int(size[1] * scale)
    tile = Image.new("RGBA", (width + pad * 2, height + pad * 2), (0, 0, 0, 0))

    shadow_layer = Image.new("RGBA", tile.size, (0, 0, 0, 0))
    shadow_draw = ImageDraw.Draw(shadow_layer)
    shadow_draw.rounded_rectangle(
        (pad + 8 * scale, pad + 12 * scale, pad + width + 8 * scale, pad + height + 12 * scale),
        radius=radius * scale,
        fill=shadow,
    )
    tile.alpha_composite(shadow_layer.filter(ImageFilter.GaussianBlur(18 * scale)))

    draw = ImageDraw.Draw(tile)
    draw.rounded_rectangle(
        (pad, pad, pad + width, pad + height),
        radius=radius * scale,
        fill=fill,
        outline=outline,
        width=2 * scale,
    )

    rotated = tile.rotate(angle, resample=Image.Resampling.BICUBIC, expand=True)
    position = (
        int(center[0] * scale - rotated.size[0] / 2),
        int(center[1] * scale - rotated.size[1] / 2),
    )
    canvas.alpha_composite(rotated, position)


def add_glow(canvas: Image.Image, center: tuple[float, float], radius: int, color: tuple[int, int, int, int]) -> None:
    scale = SCALE
    layer = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    draw = ImageDraw.Draw(layer)
    cx, cy = center
    draw.ellipse(
        box((cx - radius, cy - radius, cx + radius, cy + radius)),
        fill=color,
    )
    canvas.alpha_composite(layer.filter(ImageFilter.GaussianBlur(70 * scale)))


def paste_emblem(
    canvas: Image.Image,
    center: tuple[float, float],
    size: int,
    *,
    opacity: float = 1.0,
) -> None:
    scale = SCALE
    emblem = Image.open(EMBLEM_PATH).convert("RGBA").resize((size * scale, size * scale), Image.Resampling.LANCZOS)
    if opacity < 1:
        alpha = emblem.getchannel("A").point(lambda value: int(value * opacity))
        emblem.putalpha(alpha)

    x = int((center[0] - size / 2) * scale)
    y = int((center[1] - size / 2) * scale)
    alpha = emblem.getchannel("A")

    glow = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    glow_piece = Image.new("RGBA", emblem.size, (0, 124, 255, 72))
    glow_piece.putalpha(alpha.filter(ImageFilter.GaussianBlur(18 * scale)))
    glow.alpha_composite(glow_piece, (x, y))
    canvas.alpha_composite(glow.filter(ImageFilter.GaussianBlur(10 * scale)))

    shadow = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    shadow_piece = Image.new("RGBA", emblem.size, (3, 18, 44, 84))
    shadow_piece.putalpha(alpha.filter(ImageFilter.GaussianBlur(15 * scale)))
    shadow.alpha_composite(shadow_piece, (x + 12 * scale, y + 18 * scale))
    canvas.alpha_composite(shadow)

    canvas.alpha_composite(emblem, (x, y))


def load_glass_background() -> Image.Image:
    source = Image.open(BACKGROUND_SOURCE_PATH).convert("RGB")
    return ImageOps.fit(
        source,
        (WIDTH * SCALE, HEIGHT * SCALE),
        method=Image.Resampling.LANCZOS,
        centering=(0.5, 0.5),
    ).convert("RGBA")


def glass_background_v1() -> None:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    background = load_glass_background().convert("RGB")
    background.resize((WIDTH, HEIGHT), Image.Resampling.LANCZOS).save(
        OUT_DIR / "latticra-glass-background-v1.png",
        optimize=True,
    )


def boundary_literacy_premium() -> None:
    scale = SCALE
    canvas = vertical_gradient(
        (WIDTH * scale, HEIGHT * scale),
        (251, 253, 255, 255),
        (237, 244, 250, 255),
    )

    for center, size, angle, alpha in (
        ((-24, 40), (310, 220), -37, 148),
        ((184, 44), (330, 240), -37, 106),
        ((1356, 48), (330, 242), 38, 112),
        ((1580, 78), (300, 220), 38, 150),
        ((1422, 278), (318, 232), 39, 82),
        ((722, -30), (370, 255), -37, 54),
    ):
        add_soft_tile(
            canvas,
            center,
            size,
            angle,
            radius=32,
            fill=(255, 255, 255, alpha),
            outline=(255, 255, 255, min(alpha + 44, 210)),
            shadow=(44, 88, 122, 14),
        )

    line_layer = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    line_draw = ImageDraw.Draw(line_layer)
    for offset in range(-360, 1880, 280):
        line_draw.line(
            [xy((offset, 0)), xy((offset + 520, 900))],
            fill=(255, 255, 255, 128),
            width=2 * scale,
        )
        line_draw.line(
            [xy((offset + 122, 0)), xy((offset + 642, 900))],
            fill=(186, 210, 226, 36),
            width=1 * scale,
        )
    canvas.alpha_composite(line_layer)

    wave = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    wave_draw = ImageDraw.Draw(wave)
    wave_draw.pieslice(box((-210, 526, 700, 1100)), 180, 360, fill=(255, 255, 255, 186))
    wave_draw.pieslice(box((388, 500, 1820, 1136)), 180, 360, fill=(255, 255, 255, 152))
    wave_draw.arc(box((-210, 526, 700, 1100)), 180, 360, fill=(182, 231, 255, 118), width=4 * scale)
    wave_draw.arc(box((388, 500, 1820, 1136)), 180, 360, fill=(0, 145, 255, 104), width=4 * scale)
    wave_draw.line([xy((126, 816)), xy((1510, 816))], fill=(255, 255, 255, 180), width=2 * scale)
    canvas.alpha_composite(wave.filter(ImageFilter.GaussianBlur(1 * scale)))

    add_glow(canvas, (1204, 446), 310, (0, 151, 255, 58))
    add_glow(canvas, (1088, 572), 240, (37, 208, 226, 34))
    paste_emblem(canvas, (1218, 452), 430, opacity=0.96)

    card = Card()
    card.image = canvas.convert("RGB")
    card.draw = ImageDraw.Draw(card.image)

    card.text((132, 112), "Latticra", 46, "#07182d", bold=True)
    card.text((136, 166), "Educational Series / 01", 23, COLORS["muted"], bold=True)
    card.line([(136, 214), (464, 214)], "#0b89ff", 3)
    card.circle((136, 214), 6, "#0f766e")
    card.circle((464, 214), 6, "#1d4ed8")

    card.text((132, 348), "Boundary\nLiteracy", 96, "#101418", bold=True, spacing=0)
    card.text(
        (138, 586),
        "Make authority visible before\nbehavior becomes consequential.",
        35,
        "#5c666d",
        bold=False,
        spacing=12,
    )

    labels = [
        ("request", "#0f766e"),
        ("authority", "#2563a8"),
        ("evidence", "#b98022"),
        ("denial", "#a34a40"),
    ]
    x = 138
    y = 748
    for index, (label, color) in enumerate(labels):
        card.circle((x, y), 7, color)
        card.text((x + 22, y - 16), label, 24, "#1b2329", bold=True)
        x += 154 if index != 1 else 172
    card.line([(138, 794), (676, 794)], "#c6d7e5", 2)
    card.line([(138, 794), (326, 794)], "#1c91ff", 3)

    card.save("latticra-boundary-literacy-premium-card.png")


def glass_base_card(
    *,
    filename: str,
    series: str,
    title: str,
    subtitle: str,
    labels: tuple[tuple[str, str], ...],
) -> None:
    scale = SCALE
    canvas = load_glass_background()

    veil = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    veil_draw = ImageDraw.Draw(veil)
    veil_draw.ellipse(box((-190, 22, 838, 920)), fill=(255, 255, 255, 122))
    veil_draw.rectangle(box((0, 0, 720, 900)), fill=(255, 255, 255, 54))
    canvas.alpha_composite(veil.filter(ImageFilter.GaussianBlur(34 * scale)))

    add_glow(canvas, (1160, 460), 260, (0, 132, 255, 46))
    paste_emblem(canvas, (1192, 466), 340, opacity=0.98)

    card = Card()
    card.image = canvas.convert("RGB")
    card.draw = ImageDraw.Draw(card.image)

    card.text((126, 112), "Latticra", 45, "#06182d", bold=True)
    card.text((130, 164), series, 23, "#5f6970", bold=True)
    card.line([(132, 214), (476, 214)], "#0096ff", 3)
    card.circle((132, 214), 6, "#0e7d78")
    card.circle((476, 214), 6, "#1f5bd8")

    title_size = fitted_multiline_size(title, 760, 98, 78)
    card.text((126, 348), title, title_size, "#101418", bold=True, spacing=0)
    card.text(
        (132, 594),
        subtitle,
        35,
        "#56616a",
        spacing=12,
    )

    x = 134
    y = 760
    for index, (label, color) in enumerate(labels):
        card.circle((x, y), 7, color)
        card.text((x + 22, y - 16), label, 23, "#1a2228", bold=True)
        text_width = card.draw.textlength(label, font=font(23, True)) / SCALE
        x += max(132, text_width + 62)

    card.save(filename)


def boundary_literacy_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-boundary-literacy-glass-base-card.png",
        series="Educational Series / 01",
        title="Boundary\nLiteracy",
        subtitle="Make authority visible before\nbehavior becomes consequential.",
        labels=(
            ("request", "#0f766e"),
            ("authority", "#2563a8"),
            ("evidence", "#b98022"),
            ("denial", "#a34a40"),
        ),
    )


def public_research_standard_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-public-research-standard-glass-base-card.png",
        series="Educational Series / 02",
        title="Public\nResearch Standard",
        subtitle="Say what exists, what is missing,\nand what is not claimed.",
        labels=(
            ("exists", "#0f766e"),
            ("missing", "#2563a8"),
            ("limits", "#b98022"),
            ("evidence", "#a34a40"),
        ),
    )


def evidence_before_claims_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-evidence-before-claims-glass-base-card.png",
        series="Educational Series / 03",
        title="Evidence\nBefore Claims",
        subtitle="Public language should grow only\nas the review trail grows.",
        labels=(
            ("contract", "#0f766e"),
            ("test", "#2563a8"),
            ("report", "#b98022"),
            ("claim", "#a34a40"),
        ),
    )


def denial_is_legible_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-denial-is-legible-glass-base-card.png",
        series="Educational Series / 04",
        title="Denial\nIs Legible",
        subtitle="A denied action should leave\na reason people can inspect.",
        labels=(
            ("reason", "#0f766e"),
            ("status", "#2563a8"),
            ("boundary", "#b98022"),
            ("next step", "#a34a40"),
        ),
    )


def cryptography_without_hype_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-cryptography-without-hype-glass-base-card.png",
        series="Educational Series / 05",
        title="Cryptography\nWithout Hype",
        subtitle="Plan with limits, tests, and careful\nlanguage before promises.",
        labels=(
            ("inspectable", "#0f766e"),
            ("testable", "#2563a8"),
            ("portable", "#b98022"),
            ("limited", "#a34a40"),
        ),
    )


def visible_gates_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-visible-gates-glass-base-card.png",
        series="Educational Series / 06",
        title="Visible\nGates",
        subtitle="Authority should be checked\nbefore effects are trusted.",
        labels=(
            ("request", "#0f766e"),
            ("policy", "#2563a8"),
            ("decision", "#b98022"),
            ("receipt", "#a34a40"),
        ),
    )


def receipts_matter_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-receipts-matter-glass-base-card.png",
        series="Educational Series / 07",
        title="Receipts\nMatter",
        subtitle="Useful systems leave evidence\npeople can inspect.",
        labels=(
            ("change", "#0f766e"),
            ("source", "#2563a8"),
            ("reason", "#b98022"),
            ("record", "#a34a40"),
        ),
    )


def no_effect_evaluation_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-no-effect-evaluation-glass-base-card.png",
        series="Educational Series / 08",
        title="No-Effect\nEvaluation",
        subtitle="A dry run should teach before\nit changes anything.",
        labels=(
            ("inspect", "#0f766e"),
            ("simulate", "#2563a8"),
            ("report", "#b98022"),
            ("decide", "#a34a40"),
        ),
    )


def operator_trust_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-operator-trust-glass-base-card.png",
        series="Educational Series / 09",
        title="Operator\nTrust",
        subtitle="Trust grows when state is\nreadable, not implied.",
        labels=(
            ("status", "#0f766e"),
            ("boundary", "#2563a8"),
            ("limits", "#b98022"),
            ("next step", "#a34a40"),
        ),
    )


def open_review_glass_base_card() -> None:
    glass_base_card(
        filename="latticra-open-review-glass-base-card.png",
        series="Educational Series / 10",
        title="Open\nReview",
        subtitle="Public claims should invite\ninspection and correction.",
        labels=(
            ("claim", "#0f766e"),
            ("evidence", "#2563a8"),
            ("limit", "#b98022"),
            ("review", "#a34a40"),
        ),
    )


def glass_base_series_contact_sheet() -> None:
    REVIEW_DIR.mkdir(parents=True, exist_ok=True)
    sheet_width = 2400
    sheet_height = 1560
    sheet = Image.new("RGB", (sheet_width, sheet_height), "#f5f9fc")
    draw = ImageDraw.Draw(sheet)

    base = Image.open(OUT_DIR / "latticra-glass-background-v1.png").convert("RGB").resize(
        (sheet_width, sheet_height),
        Image.Resampling.LANCZOS,
    )
    overlay = Image.new("RGBA", (sheet_width, sheet_height), (255, 255, 255, 176))
    sheet = Image.alpha_composite(base.convert("RGBA"), overlay).convert("RGB")
    draw = ImageDraw.Draw(sheet)

    title_font = ImageFont.truetype(FONT_BOLD, 52)
    meta_font = ImageFont.truetype(FONT_BOLD, 28)
    label_font = ImageFont.truetype(FONT_BOLD, 24)
    draw.text((96, 64), "Latticra Glass-Base Visual Series", font=title_font, fill="#06182d")
    draw.text((98, 124), "Internal review only - no public X action approved", font=meta_font, fill="#5b6770")

    cards = [
        ("01 Boundary Literacy", "latticra-boundary-literacy-glass-base-card.png"),
        ("02 Public Research Standard", "latticra-public-research-standard-glass-base-card.png"),
        ("03 Evidence Before Claims", "latticra-evidence-before-claims-glass-base-card.png"),
        ("04 Denial Is Legible", "latticra-denial-is-legible-glass-base-card.png"),
        ("05 Cryptography Without Hype", "latticra-cryptography-without-hype-glass-base-card.png"),
    ]
    thumb_w = 680
    thumb_h = 382
    x_positions = [96, 860, 1624]
    y_positions = [230, 820]
    for index, (label, filename) in enumerate(cards):
        row = index // 3
        col = index % 3
        if row == 1 and index == 3:
            x = 478
        elif row == 1 and index == 4:
            x = 1242
        else:
            x = x_positions[col]
        y = y_positions[row]
        card = Image.open(OUT_DIR / filename).convert("RGB").resize((thumb_w, thumb_h), Image.Resampling.LANCZOS)
        shadow = Image.new("RGBA", sheet.size, (0, 0, 0, 0))
        shadow_draw = ImageDraw.Draw(shadow)
        shadow_draw.rounded_rectangle((x + 8, y + 16, x + thumb_w + 8, y + thumb_h + 16), radius=24, fill=(18, 48, 78, 34))
        sheet = Image.alpha_composite(sheet.convert("RGBA"), shadow.filter(ImageFilter.GaussianBlur(18))).convert("RGB")
        draw = ImageDraw.Draw(sheet)
        draw.rounded_rectangle((x - 1, y - 1, x + thumb_w + 1, y + thumb_h + 1), radius=18, fill="#ffffff")
        sheet.paste(card, (x, y))
        draw.rounded_rectangle((x, y, x + thumb_w, y + thumb_h), radius=18, outline="#d6e1e8", width=2)
        draw.text((x, y + thumb_h + 24), label, font=label_font, fill="#1a232b")
        draw.text((x, y + thumb_h + 58), "not approved", font=label_font, fill="#8a3f38")

    sheet.save(REVIEW_DIR / "latticra-glass-base-series-contact-sheet.png", optimize=True)


def glass_base_series_02_contact_sheet() -> None:
    REVIEW_DIR.mkdir(parents=True, exist_ok=True)
    sheet_width = 2400
    sheet_height = 1560
    sheet = Image.new("RGB", (sheet_width, sheet_height), "#f5f9fc")
    draw = ImageDraw.Draw(sheet)

    base = Image.open(OUT_DIR / "latticra-glass-background-v1.png").convert("RGB").resize(
        (sheet_width, sheet_height),
        Image.Resampling.LANCZOS,
    )
    overlay = Image.new("RGBA", (sheet_width, sheet_height), (255, 255, 255, 176))
    sheet = Image.alpha_composite(base.convert("RGBA"), overlay).convert("RGB")
    draw = ImageDraw.Draw(sheet)

    title_font = ImageFont.truetype(FONT_BOLD, 52)
    meta_font = ImageFont.truetype(FONT_BOLD, 28)
    label_font = ImageFont.truetype(FONT_BOLD, 24)
    draw.text((96, 64), "Latticra Glass-Base Visual Series 02", font=title_font, fill="#06182d")
    draw.text((98, 124), "Internal review only - exact owner approval required before public use", font=meta_font, fill="#5b6770")

    cards = [
        ("06 Visible Gates", "latticra-visible-gates-glass-base-card.png"),
        ("07 Receipts Matter", "latticra-receipts-matter-glass-base-card.png"),
        ("08 No-Effect Evaluation", "latticra-no-effect-evaluation-glass-base-card.png"),
        ("09 Operator Trust", "latticra-operator-trust-glass-base-card.png"),
        ("10 Open Review", "latticra-open-review-glass-base-card.png"),
    ]
    thumb_w = 680
    thumb_h = 382
    x_positions = [96, 860, 1624]
    y_positions = [230, 820]
    for index, (label, filename) in enumerate(cards):
        row = index // 3
        col = index % 3
        if row == 1 and index == 3:
            x = 478
        elif row == 1 and index == 4:
            x = 1242
        else:
            x = x_positions[col]
        y = y_positions[row]
        card = Image.open(OUT_DIR / filename).convert("RGB").resize((thumb_w, thumb_h), Image.Resampling.LANCZOS)
        shadow = Image.new("RGBA", sheet.size, (0, 0, 0, 0))
        shadow_draw = ImageDraw.Draw(shadow)
        shadow_draw.rounded_rectangle((x + 8, y + 16, x + thumb_w + 8, y + thumb_h + 16), radius=24, fill=(18, 48, 78, 34))
        sheet = Image.alpha_composite(sheet.convert("RGBA"), shadow.filter(ImageFilter.GaussianBlur(18))).convert("RGB")
        draw = ImageDraw.Draw(sheet)
        draw.rounded_rectangle((x - 1, y - 1, x + thumb_w + 1, y + thumb_h + 1), radius=18, fill="#ffffff")
        sheet.paste(card, (x, y))
        draw.rounded_rectangle((x, y, x + thumb_w, y + thumb_h), radius=18, outline="#d6e1e8", width=2)
        draw.text((x, y + thumb_h + 24), label, font=label_font, fill="#1a232b")
        draw.text((x, y + thumb_h + 58), "not approved", font=label_font, fill="#8a3f38")

    sheet.save(REVIEW_DIR / "latticra-glass-base-series-02-contact-sheet.png", optimize=True)


def boundary_literacy_glass() -> None:
    scale = SCALE
    canvas = Image.new("RGBA", (WIDTH * scale, HEIGHT * scale), (247, 249, 251, 255))

    background = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    draw = ImageDraw.Draw(background)
    draw.rectangle((0, 0, WIDTH * scale, HEIGHT * scale), fill=(247, 249, 251, 255))
    for offset, alpha in ((-140, 78), (210, 54), (560, 42), (980, 42), (1320, 50)):
        draw.rounded_rectangle(
            box((offset, -96, offset + 420, 330)),
            radius=42 * scale,
            fill=(255, 255, 255, alpha),
            outline=(214, 226, 238, 76),
            width=2 * scale,
        )
        draw.rounded_rectangle(
            box((offset + 96, -42, offset + 530, 272)),
            radius=34 * scale,
            fill=(229, 237, 247, alpha),
            outline=(255, 255, 255, 92),
            width=2 * scale,
        )
    for offset in (-80, 390, 850, 1290):
        draw.line(
            [xy((offset, 0)), xy((offset + 440, 450)), xy((offset + 900, 900))],
            fill=(255, 255, 255, 125),
            width=2 * scale,
        )
    canvas.alpha_composite(background.filter(ImageFilter.GaussianBlur(1)))

    waves = Image.new("RGBA", canvas.size, (0, 0, 0, 0))
    wdraw = ImageDraw.Draw(waves)
    wdraw.pieslice(box((-160, 552, 820, 1110)), 180, 360, fill=(255, 255, 255, 188))
    wdraw.pieslice(box((480, 514, 1760, 1160)), 180, 360, fill=(255, 255, 255, 150))
    wdraw.arc(box((-160, 552, 820, 1110)), 180, 360, fill=(181, 229, 255, 120), width=4 * scale)
    wdraw.arc(box((480, 514, 1760, 1160)), 180, 360, fill=(53, 160, 255, 105), width=4 * scale)
    canvas.alpha_composite(waves.filter(ImageFilter.GaussianBlur(1)))

    glass_rect(
        canvas,
        box((96, 110, 1504, 790)),
        radius=42 * scale,
        fill=(255, 255, 255, 188),
        outline=(223, 232, 238, 170),
        shadow=(0, 22 * scale),
        blur=24 * scale,
    )
    glass_rect(
        canvas,
        box((962, 194, 1410, 690)),
        radius=34 * scale,
        fill=(250, 253, 255, 168),
        outline=(222, 231, 238, 185),
        shadow=(-12 * scale, 18 * scale),
        blur=18 * scale,
    )

    card = Card()
    card.image = canvas.convert("RGB")
    card.draw = ImageDraw.Draw(card.image)

    emblem = Image.open(EMBLEM_PATH).convert("RGBA").resize((76 * scale, 76 * scale), Image.Resampling.LANCZOS)
    card.image.paste(emblem.convert("RGB"), xy((146, 156)), emblem)
    card.text((240, 188), "Latticra", 34, COLORS["ink"], bold=True)
    card.text((240, 224), "Educational Series / 01", 20, COLORS["muted"], bold=True)

    card.text((146, 366), "Boundary\nLiteracy", 78, COLORS["ink"], bold=True, spacing=0)
    card.text(
        (150, 572),
        "Make authority visible\nbefore behavior becomes consequential.",
        35,
        COLORS["muted"],
        spacing=10,
    )

    rows = [
        ("request", "who asked?", COLORS["teal"]),
        ("authority", "what can move?", COLORS["blue"]),
        ("evidence", "what remains?", COLORS["amber"]),
        ("denial", "what stays closed?", COLORS["rust"]),
    ]
    y = 282
    for index, (label, prompt, color) in enumerate(rows):
        if index:
            card.line([(1024, y - 30), (1352, y - 30)], "#e5edf1", 2)
        card.circle((1038, y + 14), 10, color)
        card.text((1070, y - 5), label, 32, COLORS["ink"], bold=True)
        card.text((1070, y + 34), prompt, 21, COLORS["muted"], bold=True)
        y += 100

    card.text((150, 738), "request -> authority -> evidence -> denial", 22, COLORS["blue"], bold=True)
    card.save("latticra-boundary-literacy-glass-card.png")


def main() -> None:
    request_to_effect()
    evidence_before_claims()
    denial_is_legible()
    q_seal_posture()
    boundary_literacy_v2()
    boundary_literacy_v3()
    boundary_literacy_wordmark()
    denial_is_legible_wordmark()
    evidence_before_claims_wordmark()
    q_seal_posture_wordmark()
    glass_background_v1()
    boundary_literacy_premium()
    boundary_literacy_glass_base_card()
    public_research_standard_glass_base_card()
    evidence_before_claims_glass_base_card()
    denial_is_legible_glass_base_card()
    cryptography_without_hype_glass_base_card()
    glass_base_series_contact_sheet()
    visible_gates_glass_base_card()
    receipts_matter_glass_base_card()
    no_effect_evaluation_glass_base_card()
    operator_trust_glass_base_card()
    open_review_glass_base_card()
    glass_base_series_02_contact_sheet()
    boundary_literacy_glass()


if __name__ == "__main__":
    main()

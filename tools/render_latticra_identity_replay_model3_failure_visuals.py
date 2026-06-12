#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Render SVG visuals for the Model-3 identity-replay failure analysis."""

from __future__ import annotations

import html
import json
import math
import os
from decimal import Decimal, getcontext
from pathlib import Path

from latticra_identity_replay_model3_evaluate import build_evaluation_receipt
from latticra_identity_replay_model3_rejection_analysis import build_analysis
from latticra_identity_replay_model3_runner import build_prediction_receipt


getcontext().prec = 80

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "docs/assets/identity-replay-model3-failure"
TARGETS = ROOT / "docs/LATTICRA_IDENTITY_REPLAY_IMPEDANCE_CANDIDATE_PARTICLE_TABLE.md"
IDENTITY_LABELS = {
    "electron": "electron",
    "muon": "muon",
    "tau": "tau",
    "W boson": "W",
    "Z boson": "Z",
    "Higgs boson": "Higgs",
    "top quark": "top",
}
TARGET_ORDER = [
    "electron",
    "muon",
    "tau",
    "W boson",
    "Z boson",
    "Higgs boson",
    "top quark",
]


def decimal_text(value: object) -> str:
    return str(value)


def svg_text(x: float, y: float, value: str, size: int = 18, weight: str = "400", anchor: str = "start", fill: str = "#17202a") -> str:
    return (
        f'<text x="{x:.1f}" y="{y:.1f}" font-family="Avenir, Inter, Arial, sans-serif" '
        f'font-size="{size}" font-weight="{weight}" text-anchor="{anchor}" fill="{fill}">'
        f"{html.escape(value)}</text>"
    )


def svg_rect(x: float, y: float, width: float, height: float, fill: str, stroke: str = "none", radius: float = 0, opacity: float = 1) -> str:
    return (
        f'<rect x="{x:.1f}" y="{y:.1f}" width="{width:.1f}" height="{height:.1f}" '
        f'rx="{radius:.1f}" fill="{fill}" stroke="{stroke}" opacity="{opacity:.3f}" />'
    )


def log10_decimal(value: Decimal) -> float:
    return math.log10(float(value))


def write_svg(path: Path, content: str) -> None:
    path.write_text(content.rstrip() + "\n", encoding="utf-8")


def write_json(
    path: Path, payload: dict[str, object], *, trailing_newline: bool = False
) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(f".{path.name}.{os.getpid()}.tmp")
    content = json.dumps(payload, indent=2, sort_keys=True)
    if trailing_newline:
        content += "\n"
    tmp.write_text(content, encoding="utf-8")
    tmp.replace(path)


def load_receipts() -> tuple[dict[str, object], dict[str, object], dict[str, object]]:
    prediction = build_prediction_receipt()
    receipt_dir = Path("docs/assets/identity-replay-model3-failure")
    prediction_path = receipt_dir / "model3-failure-prediction.json"
    evaluation_path = receipt_dir / "model3-failure-evaluation.json"
    analysis_path = receipt_dir / "model3-failure-rejection-analysis.json"
    write_json(prediction_path, prediction)
    evaluation = build_evaluation_receipt(prediction_path, TARGETS)
    write_json(evaluation_path, evaluation)
    analysis = build_analysis(prediction_path, evaluation_path)
    write_json(analysis_path, analysis)
    return prediction, evaluation, analysis


def target_ratios(evaluation: dict[str, object]) -> dict[str, Decimal]:
    raw = evaluation["target_ratios"]
    assert isinstance(raw, dict)
    return {
        target: Decimal(str(row["ratio_to_electron"]))
        for target, row in raw.items()
        if isinstance(row, dict)
    }


def predicted_ratios(prediction: dict[str, object]) -> dict[str, Decimal]:
    raw = prediction["mass_ratio_predictions"]
    assert isinstance(raw, dict)
    return {target: Decimal(str(value)) for target, value in raw.items()}


def render_ratio_chart(prediction: dict[str, object], evaluation: dict[str, object]) -> str:
    predictions = predicted_ratios(prediction)
    targets = target_ratios(evaluation)
    width = 1280
    height = 720
    plot_x = 120
    plot_y = 130
    plot_w = 1040
    plot_h = 430
    y_min = -1.0
    y_max = 6.0
    slot = plot_w / len(TARGET_ORDER)

    def y_for(value: Decimal) -> float:
        ratio = (log10_decimal(value) - y_min) / (y_max - y_min)
        return plot_y + plot_h - (ratio * plot_h)

    parts = [
        '<svg xmlns="http://www.w3.org/2000/svg" width="1280" height="720" viewBox="0 0 1280 720">',
        svg_rect(0, 0, width, height, "#f7f8fb"),
        svg_text(64, 58, "Model-3 Failure: Predicted vs Target Mass Ratios", 30, "700"),
        svg_text(64, 92, "Log10 electron-normalized ratio. Prediction receipt is emitted before target load.", 17, "400", fill="#53606f"),
        svg_rect(plot_x, plot_y, plot_w, plot_h, "#ffffff", "#d8dee8", 6),
    ]
    for tick in range(-1, 7):
        y = plot_y + plot_h - ((tick - y_min) / (y_max - y_min) * plot_h)
        color = "#d9e0ea" if tick != 0 else "#748295"
        parts.append(f'<line x1="{plot_x}" y1="{y:.1f}" x2="{plot_x + plot_w}" y2="{y:.1f}" stroke="{color}" stroke-width="1" />')
        parts.append(svg_text(plot_x - 16, y + 6, f"10^{tick}", 14, "500", "end", "#53606f"))

    for idx, target in enumerate(TARGET_ORDER):
        center = plot_x + slot * idx + slot / 2
        pred_y = y_for(predictions[target])
        target_y = y_for(targets[target])
        parts.append(f'<line x1="{center:.1f}" y1="{target_y:.1f}" x2="{center:.1f}" y2="{pred_y:.1f}" stroke="#aeb8c7" stroke-width="2" />')
        parts.append(f'<circle cx="{center:.1f}" cy="{target_y:.1f}" r="10" fill="#1f7a8c" />')
        parts.append(f'<circle cx="{center:.1f}" cy="{pred_y:.1f}" r="10" fill="#d94f45" />')
        parts.append(svg_text(center, plot_y + plot_h + 42, IDENTITY_LABELS[target], 16, "700", "middle", "#17202a"))

    parts.extend(
        [
            svg_rect(780, 48, 18, 18, "#1f7a8c", radius=3),
            svg_text(806, 63, "target", 16, "600", fill="#17202a"),
            svg_rect(880, 48, 18, 18, "#d94f45", radius=3),
            svg_text(906, 63, "Model-3 prediction", 16, "600", fill="#17202a"),
            svg_text(64, 636, "Current result: dynamic range improved, but six identities fail the guarded target table.", 20, "700", fill="#17202a"),
            svg_text(64, 668, "Non-claim: this is not Higgs denial, not mass recovery, and not simulation proof.", 16, "500", fill="#53606f"),
            "</svg>",
        ]
    )
    return "\n".join(parts)


def render_ordering_chart(analysis: dict[str, object]) -> str:
    width = 1280
    height = 720
    predicted = list(analysis["predicted_identity_order_by_ratio"])
    target = list(analysis["target_identity_order_by_ratio"])
    colors = {
        "I_e": "#2f80ed",
        "I_mu": "#56a36c",
        "I_tau": "#8a63d2",
        "I_W": "#e2a93b",
        "I_Z": "#1f7a8c",
        "I_H": "#d94f45",
        "I_top": "#2d3748",
    }

    def row(y: int, title: str, identities: list[str]) -> list[str]:
        parts = [svg_text(70, y + 38, title, 24, "700")]
        x = 330
        step = 120
        for idx, identity in enumerate(identities):
            box_x = x + idx * step
            parts.append(svg_rect(box_x, y, 92, 58, colors[identity], "#ffffff", 8, 0.95))
            parts.append(svg_text(box_x + 46, y + 37, identity, 20, "700", "middle", "#ffffff"))
            if idx < len(identities) - 1:
                parts.append(f'<line x1="{box_x + 98:.1f}" y1="{y + 29:.1f}" x2="{box_x + step - 8:.1f}" y2="{y + 29:.1f}" stroke="#8792a3" stroke-width="2" marker-end="url(#arrow)" />')
        return parts

    parts = [
        '<svg xmlns="http://www.w3.org/2000/svg" width="1280" height="720" viewBox="0 0 1280 720">',
        '<defs><marker id="arrow" markerWidth="10" markerHeight="10" refX="8" refY="3" orient="auto" markerUnits="strokeWidth"><path d="M0,0 L0,6 L9,3 z" fill="#8792a3" /></marker></defs>',
        svg_rect(0, 0, width, height, "#f7f8fb"),
        svg_text(64, 58, "Model-3 Failure: Identity Ordering Mismatch", 30, "700"),
        svg_text(64, 92, "A larger multiplier alone cannot fix the wrong order.", 17, "400", fill="#53606f"),
        *row(190, "Predicted order", predicted),
        *row(340, "Target order", target),
        svg_rect(74, 540, 1130, 74, "#ffffff", "#d8dee8", 8),
        svg_text(104, 576, "Structural failure", 20, "700", fill="#17202a"),
        svg_text(104, 604, "Higgs and Z appear below electron-scale impedance, and muon/tau ordering is inverted.", 17, "500", fill="#53606f"),
        svg_text(64, 668, "Next requirement: target-blind sector-resolved topological charge with family monotonicity.", 18, "700", fill="#17202a"),
        "</svg>",
    ]
    return "\n".join(parts)


def render_sector_chart(prediction: dict[str, object], evaluation: dict[str, object]) -> str:
    predictions = predicted_ratios(prediction)
    targets = target_ratios(evaluation)
    width = 1280
    height = 720
    plot_x = 110
    plot_y = 150
    plot_w = 1060
    plot_h = 390
    y_min = -1.0
    y_max = 6.0
    sector_bands = [
        ("electron anchor", -0.12, 0.12, "#dbeafe"),
        ("lepton family", 1.0, 4.0, "#dcfce7"),
        ("heavy electroweak/top", 5.0, 5.7, "#fee2e2"),
    ]

    def y_for_log(log_value: float) -> float:
        ratio = (log_value - y_min) / (y_max - y_min)
        return plot_y + plot_h - (ratio * plot_h)

    def y_for(value: Decimal) -> float:
        return y_for_log(log10_decimal(value))

    parts = [
        '<svg xmlns="http://www.w3.org/2000/svg" width="1280" height="720" viewBox="0 0 1280 720">',
        svg_rect(0, 0, width, height, "#f7f8fb"),
        svg_text(64, 58, "Model-3 Failure: Sector Placement", 30, "700"),
        svg_text(64, 92, "The first law places some heavy-sector identities below the electron anchor.", 17, "400", fill="#53606f"),
        svg_rect(plot_x, plot_y, plot_w, plot_h, "#ffffff", "#d8dee8", 6),
    ]

    for label, low, high, color in sector_bands:
        y_high = y_for_log(high)
        y_low = y_for_log(low)
        parts.append(svg_rect(plot_x, y_high, plot_w, y_low - y_high, color, "none", 0, 0.82))
        parts.append(svg_text(plot_x + 16, y_high + 24, label, 15, "700", fill="#3d4654"))

    slot = plot_w / len(TARGET_ORDER)
    for idx, target in enumerate(TARGET_ORDER):
        center = plot_x + slot * idx + slot / 2
        target_y = y_for(targets[target])
        pred_y = y_for(predictions[target])
        parts.append(f'<line x1="{center:.1f}" y1="{plot_y + plot_h:.1f}" x2="{center:.1f}" y2="{plot_y:.1f}" stroke="#edf1f6" stroke-width="1" />')
        parts.append(f'<circle cx="{center - 13:.1f}" cy="{target_y:.1f}" r="9" fill="#1f7a8c" />')
        parts.append(f'<circle cx="{center + 13:.1f}" cy="{pred_y:.1f}" r="9" fill="#d94f45" />')
        parts.append(svg_text(center, plot_y + plot_h + 42, IDENTITY_LABELS[target], 16, "700", "middle"))

    for tick in range(-1, 7):
        y = y_for_log(tick)
        parts.append(f'<line x1="{plot_x}" y1="{y:.1f}" x2="{plot_x + plot_w}" y2="{y:.1f}" stroke="#cfd7e3" stroke-width="1" opacity="0.7" />')
        parts.append(svg_text(plot_x - 14, y + 5, f"10^{tick}", 14, "500", "end", "#53606f"))

    parts.extend(
        [
            svg_rect(810, 48, 18, 18, "#1f7a8c", radius=3),
            svg_text(836, 63, "target", 16, "600"),
            svg_rect(910, 48, 18, 18, "#d94f45", radius=3),
            svg_text(936, 63, "prediction", 16, "600"),
            svg_text(64, 636, "Failure insight: sector resolution must be derived before target loading.", 20, "700"),
            svg_text(64, 668, "A refined law must explain family monotonicity and heavy-sector placement without particle labels.", 16, "500", fill="#53606f"),
            "</svg>",
        ]
    )
    return "\n".join(parts)


def write_manifest(prediction: dict[str, object], evaluation: dict[str, object], analysis: dict[str, object]) -> None:
    rel_out = Path("docs/assets/identity-replay-model3-failure")
    manifest = {
        "latticra_identity_replay_model3_failure_visual_suite_rendered": 1,
        "visual_suite_id": "latticra-identity-replay-model3-failure-visual-suite",
        "visual_mode": "static-svg-from-receipted-model3-rejection-analysis",
        "ratio_chart": str(rel_out / "model3-failure-ratio-chart.svg"),
        "ordering_chart": str(rel_out / "model3-failure-ordering-chart.svg"),
        "sector_chart": str(rel_out / "model3-failure-sector-chart.svg"),
        "model3_prediction_receipt_hash": prediction["model3_prediction_receipt_hash"],
        "model3_evaluation_receipt_hash": evaluation["model3_evaluation_receipt_hash"],
        "model3_rejection_analysis_receipt_hash": analysis["model3_rejection_analysis_receipt_hash"],
        "model3_prediction_law_rejected": analysis["model3_prediction_law_rejected"],
        "dynamic_range_deficit_factor": analysis["dynamic_range_deficit_factor"],
        "low_electroweak_below_electron_targets": analysis["low_electroweak_below_electron_targets"],
        "single_global_amplifier_insufficient": analysis["single_global_amplifier_insufficient"],
        "required_refined_model3_property": analysis["required_refined_model3_property"],
        "mass_ratio_recovery_claimed": 0,
        "higgs_checkmate_claimed": 0,
        "simulation_proven": 0,
        "scientific_claim_promoted": 0,
    }
    write_json(OUT / "render-manifest.json", manifest, trailing_newline=True)
    (OUT / "render-manifest.txt").write_text(
        "\n".join(f"{key}={value}" for key, value in manifest.items()) + "\n",
        encoding="utf-8",
    )


def main() -> int:
    os.chdir(ROOT)
    OUT.mkdir(parents=True, exist_ok=True)
    prediction, evaluation, analysis = load_receipts()
    write_svg(OUT / "model3-failure-ratio-chart.svg", render_ratio_chart(prediction, evaluation))
    write_svg(OUT / "model3-failure-ordering-chart.svg", render_ordering_chart(analysis))
    write_svg(OUT / "model3-failure-sector-chart.svg", render_sector_chart(prediction, evaluation))
    write_manifest(prediction, evaluation, analysis)
    print(f"Rendered Model-3 failure visual suite: {OUT}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

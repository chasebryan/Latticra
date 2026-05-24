#!/usr/bin/env python3
from pathlib import Path
from reportlab.lib.pagesizes import letter
from reportlab.lib.units import inch
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Preformatted, PageBreak
from xml.sax.saxutils import escape

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "docs/latticra-seal/latticra-seal-handbook.pdf"

DOCS = [
    "README.md",
    "STATUS.md",
    "ARCHITECTURE.md",
    "USAGE.md",
    "POLICY.md",
    "REPORTS.md",
    "BOUNDARIES.md",
    "ROADMAP.md",
]

styles = getSampleStyleSheet()
story = []

story.append(Paragraph("Latticra Seal Documentation Handbook", styles["Title"]))
story.append(Spacer(1, 0.25 * inch))
story.append(Paragraph("Generated from docs/latticra-seal Markdown sources.", styles["BodyText"]))
story.append(PageBreak())

for name in DOCS:
    path = ROOT / "docs/latticra-seal" / name
    if not path.exists():
        raise SystemExit(f"missing required doc: {path}")

    story.append(Paragraph(escape(name), styles["Heading1"]))
    story.append(Spacer(1, 0.1 * inch))

    in_code = False
    code = []

    for line in path.read_text(encoding="utf-8").splitlines():
        stripped = line.strip()

        if stripped.startswith("```"):
            if in_code:
                story.append(Preformatted("\n".join(code), styles["Code"]))
                code = []
                in_code = False
            else:
                in_code = True
                code = []
            continue

        if in_code:
            code.append(line)
            continue

        if not stripped:
            story.append(Spacer(1, 0.05 * inch))
        elif stripped.startswith("# "):
            story.append(Paragraph(escape(stripped[2:]), styles["Heading1"]))
        elif stripped.startswith("## "):
            story.append(Paragraph(escape(stripped[3:]), styles["Heading2"]))
        elif stripped.startswith("### "):
            story.append(Paragraph(escape(stripped[4:]), styles["Heading3"]))
        elif stripped.startswith("- "):
            story.append(Paragraph("• " + escape(stripped[2:]), styles["BodyText"]))
        else:
            story.append(Paragraph(escape(stripped), styles["BodyText"]))

    story.append(PageBreak())

OUT.parent.mkdir(parents=True, exist_ok=True)

doc = SimpleDocTemplate(
    str(OUT),
    pagesize=letter,
    rightMargin=0.7 * inch,
    leftMargin=0.7 * inch,
    topMargin=0.7 * inch,
    bottomMargin=0.7 * inch,
)

doc.build(story)
print(f"wrote {OUT}")

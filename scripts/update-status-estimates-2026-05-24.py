import argparse
from pathlib import Path
import re

STAMP = "2026-05-24 CDT"

parser = argparse.ArgumentParser()
parser.add_argument("--estimates", required=True)
parser.add_argument("--review", required=True)
args = parser.parse_args()

EST = Path(args.estimates).read_text(encoding="utf-8")
REVIEW = Path(args.review).read_text(encoding="utf-8")

def write(path, text):
    Path(path).write_text(text, encoding="utf-8")
    print("updated:", path)

def update_line(text, prefix, value):
    pattern = rf"^{re.escape(prefix)}.*$"
    repl = f"{prefix}{value}"
    return re.sub(pattern, repl, text, count=1, flags=re.MULTILINE)

def ensure_after(text, anchor_prefix, line):
    if line in text:
        return text
    lines = text.splitlines()
    out = []
    inserted = False
    for current in lines:
        out.append(current)
        if not inserted and current.startswith(anchor_prefix):
            out.append(line)
            inserted = True
    return "\n".join(out) + "\n"

def replace_between(text, start, end, replacement):
    if start not in text:
        raise SystemExit(f"missing start marker: {start}")
    if end not in text:
        raise SystemExit(f"missing end marker: {end}")
    a = text.index(start) + len(start)
    b = text.index(end, a)
    return text[:a] + replacement + text[b:]

root = Path("STATUS.md").read_text(encoding="utf-8")
root = update_line(root, "Last updated: ", STAMP)
root = ensure_after(root, "Last updated:", f"Latest current estimate refresh note: {STAMP}")
root = replace_between(root, "## Current high-level estimate\n\n", "\n## Current direction checkpoint", EST + "\n\n")
root = root.replace("Completion estimate review only if capability posture changes", "Panel, Seal, and estimate review only when capability posture changes")
write("STATUS.md", root)

current = Path("docs/status/CURRENT_STATUS.md").read_text(encoding="utf-8")
current = update_line(current, "Last updated: ", STAMP)
current = ensure_after(current, "Last updated:", f"Latest current estimate refresh note: {STAMP}")
current = replace_between(current, "## Rough completion estimates\n\nThese percentages are planning estimates only.\n\n", "\n## Current implemented evidence areas", EST + "\n")
current = current.replace("Completion estimate review only if capability posture changes", "Panel, Seal, and estimate review only when capability posture changes")
write("docs/status/CURRENT_STATUS.md", current)

index = Path("docs/status/README.md").read_text(encoding="utf-8")
index = update_line(index, "Last updated: ", "2026-05-24")
entry = "- [`CURRENT_ESTIMATE_REFRESH_2026_05_24.md`](CURRENT_ESTIMATE_REFRESH_2026_05_24.md) - current planning-estimate refresh after Panel, Seal, documentation, and local evidence work."
if entry not in index:
    index = index.replace("- [`CURRENT_STATUS.md`](CURRENT_STATUS.md) — current project status, completion estimates, and next priorities.", "- [`CURRENT_STATUS.md`](CURRENT_STATUS.md) — current project status, completion estimates, and next priorities.\n" + entry)
write("docs/status/README.md", index)

Path("docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md").write_text(REVIEW, encoding="utf-8")
print("updated: docs/status/CURRENT_ESTIMATE_REFRESH_2026_05_24.md")

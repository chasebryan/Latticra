#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Shared utilities for portable receipt references and common receipt helpers.

This module centralizes logic for producing machine-independent references
inside Latticra evidence receipts and related artifacts. The primary goal is
receipt reference portability: references recorded in JSON receipts, manifests,
and ledgers must remain valid when the repository is checked out at a different
absolute path or on a different machine.

All path references emitted for cross-receipt linking must resolve to paths
relative to the repository root using POSIX-style separators.
"""

from __future__ import annotations

import hashlib
import json
from decimal import Decimal
from pathlib import Path
from typing import Iterable

REPO_ROOT = Path(__file__).resolve().parents[1]

__all__ = [
    "REPO_ROOT",
    "path_reference",
    "decimal_to_text",
    "canonical_receipt_hash",
    "receipt_hash",
    "file_sha256",
]


def path_reference(path: Path | str) -> str:
    if isinstance(path, str):
        p = Path(path)
    else:
        p = path
    candidate = p if p.is_absolute() else REPO_ROOT / p
    try:
        return candidate.resolve().relative_to(REPO_ROOT).as_posix()
    except (ValueError, FileNotFoundError, RuntimeError):
        try:
            return p.as_posix()
        except Exception:
            return str(p)


def decimal_to_text(value: Decimal) -> str:
    normalized = value.normalize()
    if normalized == normalized.to_integral():
        return format(normalized, "f")
    return format(normalized, "f")


def canonical_receipt_hash(payload: dict[str, object]) -> str:
    canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"))
    return "sha256:" + hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def receipt_hash(payload: dict[str, object], *, exclude_keys: Iterable[str] = ()) -> str:
    p = dict(payload)
    for k in exclude_keys:
        p.pop(k, None)
    return canonical_receipt_hash(p)


def file_sha256(path: Path | str) -> str:
    p = Path(path)
    data = p.read_bytes()
    return "sha256:" + hashlib.sha256(data).hexdigest()


def _self_test() -> int:
    from pathlib import Path as _P

    r1 = path_reference("README.md")
    r2 = path_reference(_P("tools/latticra_receipt_utils.py"))
    r3 = path_reference("/tmp/not-in-repo-xyz")
    h = canonical_receipt_hash({"a": 1, "b": 2})
    h2 = receipt_hash({"x": 9, "receipt_hash": "sha256:ignore"}, exclude_keys=("receipt_hash",))
    f = file_sha256("README.md")
    ok = (
        r1 == "README.md"
        and r2 == "tools/latticra_receipt_utils.py"
        and r3 == "/tmp/not-in-repo-xyz"
        and h.startswith("sha256:")
        and len(h) > 20
        and h2.startswith("sha256:")
        and f.startswith("sha256:")
    )
    if not ok:
        print("FAIL receipt utils self test")
        return 1
    print("latticra_receipt_utils self test: ok")
    print(f"  sample references: {r1}, {r2}")
    return 0


if __name__ == "__main__":
    raise SystemExit(_self_test())

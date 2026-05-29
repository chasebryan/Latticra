#!/usr/bin/env python3
"""Decode X status IDs/URLs and print review-friendly timing metadata."""

from __future__ import annotations

import argparse
import re
from datetime import datetime, timezone
from zoneinfo import ZoneInfo


X_EPOCH_MS = 1288834974657
STATUS_RE = re.compile(r"(?:status/)?(\d{15,25})")


def parse_status_id(value: str) -> int:
    match = STATUS_RE.search(value)
    if not match:
        raise ValueError(f"could not find an X status id in {value!r}")
    return int(match.group(1))


def decode_status_time(status_id: int) -> datetime:
    timestamp_ms = (status_id >> 22) + X_EPOCH_MS
    return datetime.fromtimestamp(timestamp_ms / 1000, timezone.utc)


def format_delta(seconds: float) -> str:
    sign = "-" if seconds < 0 else ""
    total_seconds = abs(int(round(seconds)))
    hours, remainder = divmod(total_seconds, 3600)
    minutes, secs = divmod(remainder, 60)
    return f"{sign}{hours}h {minutes:02d}m {secs:02d}s"


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("status", nargs="+", help="X status ID or URL")
    parser.add_argument("--timezone", default="America/Chicago", help="IANA timezone for local output")
    args = parser.parse_args()

    local_zone = ZoneInfo(args.timezone)
    previous: datetime | None = None

    for index, value in enumerate(args.status, start=1):
        status_id = parse_status_id(value)
        created_utc = decode_status_time(status_id)
        created_local = created_utc.astimezone(local_zone)

        print(f"item={index}")
        print(f"status_id={status_id}")
        print(f"created_at_utc={created_utc.isoformat(timespec='seconds')}")
        print(f"created_at_local={created_local.isoformat(timespec='seconds')}")
        print(f"created_at_local_readable={created_local.strftime('%Y-%m-%d %H:%M:%S %Z')}")
        if previous is not None:
            elapsed = (created_utc - previous).total_seconds()
            print(f"elapsed_from_previous={format_delta(elapsed)}")
        previous = created_utc
        if index != len(args.status):
            print()


if __name__ == "__main__":
    main()

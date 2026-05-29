#!/usr/bin/env python3
"""Validate Latticra X content queue and social-card assets."""

from __future__ import annotations

import re
import sys
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[1]
QUEUE = ROOT / "docs" / "strategy" / "2026-05-28-0343-cdt-x-content-approval-queue.md"
CALENDAR = ROOT / "docs" / "strategy" / "2026-05-28-0332-cdt-x-launch-week-education-calendar.md"
TEXT_BANK = ROOT / "docs" / "strategy" / "2026-05-28-0358-cdt-x-text-first-education-bank.md"
ENGAGEMENT_PLAYBOOK = ROOT / "docs" / "strategy" / "2026-05-28-0400-cdt-x-engagement-measurement-playbook.md"
PERFORMANCE_LEDGER = ROOT / "docs" / "strategy" / "2026-05-28-0400-cdt-x-post-performance-ledger.md"
PROFILE_CONVERSION = ROOT / "docs" / "strategy" / "2026-05-28-0403-cdt-x-profile-conversion-packet.md"
PUBLISH_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-0406-cdt-x-week-one-text-only-publish-packet.md"
VISUAL_SERIES_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-0421-cdt-x-glass-base-visual-series-review-packet.md"
MEDIA_APPROVAL_MATRIX = ROOT / "docs" / "strategy" / "2026-05-28-0430-cdt-x-media-ready-approval-matrix.md"
REVIEW_BOARD = ROOT / "docs" / "strategy" / "2026-05-28-0430-cdt-x-review-board.html"
FIRST_LIVE_POST_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-0504-cdt-x-first-live-post-packet.md"
MENTION_RESPONSE_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-0552-cdt-x-mention-response-readiness-packet.md"
MENTION_INTAKE_LOG = ROOT / "docs" / "strategy" / "2026-05-28-0558-cdt-x-mention-intake-log.md"
EARLY_MONITORING_CHECKPOINT = ROOT / "docs" / "strategy" / "2026-05-28-0601-cdt-x-early-monitoring-checkpoint.md"
TEN_AM_VERIFICATION_RUNBOOK = ROOT / "docs" / "strategy" / "2026-05-28-0606-cdt-x-10am-verification-runbook.md"
SCHEDULED_QUEUE_VERIFICATION_CHAIN = ROOT / "docs" / "strategy" / "2026-05-28-0610-cdt-x-scheduled-queue-verification-chain.md"
NEXT_SEQUENCE_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-0555-cdt-x-next-education-sequence-packet.md"
NEXT_MANUAL_APPROVAL_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-1605-cdt-x-next-manual-post-approval-packet.md"
GROWTH_CONVERSATION_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-1905-cdt-x-growth-conversation-packet.md"
APPROVAL_SHORTLIST_LADDER = ROOT / "docs" / "strategy" / "2026-05-28-1908-cdt-x-approval-shortlist-cadence-ladder.md"
DENIAL_POST_HANDOFF = ROOT / "docs" / "strategy" / "2026-05-28-1910-cdt-x-20pm-denial-post-handoff.md"
DENIAL_POST_DECISION_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-1913-cdt-x-denial-post-verification-decision-packet.md"
CRYPTOGRAPHY_POST_HANDOFF = ROOT / "docs" / "strategy" / "2026-05-28-1916-cdt-x-1am-cryptography-post-handoff.md"
ROLLING_APPROVAL_CALENDAR = ROOT / "docs" / "strategy" / "2026-05-28-1918-cdt-x-rolling-approval-calendar.md"
LIVE_GROWTH_CHECKPOINT = ROOT / "docs" / "strategy" / "2026-05-28-1924-cdt-x-live-growth-checkpoint.md"
PROFILE_PIN_DECISION_PACKET = ROOT / "docs" / "strategy" / "2026-05-28-1932-cdt-x-profile-pin-conversion-decision-packet.md"
SOCIAL_DIR = ROOT / "assets" / "social"
BACKGROUND_SOURCE = SOCIAL_DIR / "sources" / "latticra-glass-background-source-v1.png"
BACKGROUND_BASE = SOCIAL_DIR / "latticra-glass-background-v1.png"
CONTACT_SHEET = SOCIAL_DIR / "review" / "latticra-glass-base-series-contact-sheet.png"
CONTACT_SHEET_02 = SOCIAL_DIR / "review" / "latticra-glass-base-series-02-contact-sheet.png"
STATUS_METRICS_SCRIPT = ROOT / "scripts" / "latticra-x-status-metrics.py"

IMAGE_SIZE = (1600, 900)
CONTACT_SHEET_SIZE = (2400, 1560)
MAX_POST_CHARS = 280

INTERNAL_DRAFTS = {
    "latticra-request-to-effect-card.png",
    "latticra-denial-is-legible-card.png",
    "latticra-q-seal-posture-card.png",
    "latticra-evidence-before-claims-card.png",
    "latticra-boundary-literacy-v2-card.png",
    "latticra-boundary-literacy-wordmark-card.png",
    "latticra-boundary-literacy-premium-card.png",
}

CURRENT_CANDIDATE = "latticra-boundary-literacy-glass-base-card.png"
GLASS_BASE_CANDIDATES = (
    "latticra-boundary-literacy-glass-base-card.png",
    "latticra-public-research-standard-glass-base-card.png",
    "latticra-evidence-before-claims-glass-base-card.png",
    "latticra-denial-is-legible-glass-base-card.png",
    "latticra-cryptography-without-hype-glass-base-card.png",
)

GLASS_BASE_SECOND_SEQUENCE = (
    "latticra-visible-gates-glass-base-card.png",
    "latticra-receipts-matter-glass-base-card.png",
    "latticra-no-effect-evaluation-glass-base-card.png",
    "latticra-operator-trust-glass-base-card.png",
    "latticra-open-review-glass-base-card.png",
)


def fail(message: str) -> None:
    print(f"FAIL: {message}", file=sys.stderr)
    raise SystemExit(1)


def validate_post_lengths(path: Path) -> None:
    text = path.read_text(encoding="utf-8")
    for index, match in enumerate(re.finditer(r"Post:\n\n```text\n([\s\S]*?)\n```", text), start=1):
        content = match.group(1)
        length = len(content)
        print(f"{path.relative_to(ROOT)} post {index}: {length} chars")
        if length > MAX_POST_CHARS:
            fail(f"{path.relative_to(ROOT)} post {index} is {length} chars")


def validate_reply_lengths(path: Path) -> None:
    text = path.read_text(encoding="utf-8")
    for index, match in enumerate(re.finditer(r"Reply:\n\n```text\n([\s\S]*?)\n```", text), start=1):
        content = match.group(1)
        length = len(content)
        print(f"{path.relative_to(ROOT)} reply {index}: {length} chars")
        if length > MAX_POST_CHARS:
            fail(f"{path.relative_to(ROOT)} reply {index} is {length} chars")


def validate_media_references(path: Path) -> None:
    text = path.read_text(encoding="utf-8")
    for match in re.finditer(r"assets/social/[A-Za-z0-9_.-]+\.png", text):
        rel = match.group(0)
        media = ROOT / rel
        if not media.exists():
            fail(f"missing referenced media: {rel}")
        if media.name in INTERNAL_DRAFTS and "not approved" not in text[max(0, match.start() - 160): match.end() + 160]:
            fail(f"internal draft referenced without not-approved context: {rel}")


def validate_images() -> None:
    for path in sorted(SOCIAL_DIR.glob("*.png")):
        with Image.open(path) as image:
            print(f"{path.relative_to(ROOT)}: {image.size} {image.mode}")
            if image.size != IMAGE_SIZE:
                fail(f"{path.relative_to(ROOT)} is {image.size}, expected {IMAGE_SIZE}")
            if image.mode != "RGB":
                fail(f"{path.relative_to(ROOT)} is {image.mode}, expected RGB")
    if not BACKGROUND_SOURCE.exists():
        fail("missing approved glass background source")
    with Image.open(BACKGROUND_SOURCE) as source:
        print(f"{BACKGROUND_SOURCE.relative_to(ROOT)}: {source.size} {source.mode}")
        if source.size[0] < IMAGE_SIZE[0] or source.size[1] < IMAGE_SIZE[1]:
            fail("approved glass background source is too small")
        if source.mode != "RGB":
            fail("approved glass background source should be RGB")
    if not CONTACT_SHEET.exists():
        fail("missing glass-base visual series contact sheet")
    with Image.open(CONTACT_SHEET) as contact_sheet:
        print(f"{CONTACT_SHEET.relative_to(ROOT)}: {contact_sheet.size} {contact_sheet.mode}")
        if contact_sheet.size != CONTACT_SHEET_SIZE:
            fail(f"{CONTACT_SHEET.relative_to(ROOT)} is {contact_sheet.size}, expected {CONTACT_SHEET_SIZE}")
        if contact_sheet.mode != "RGB":
            fail("contact sheet should be RGB")
    if not CONTACT_SHEET_02.exists():
        fail("missing second glass-base visual series contact sheet")
    with Image.open(CONTACT_SHEET_02) as contact_sheet:
        print(f"{CONTACT_SHEET_02.relative_to(ROOT)}: {contact_sheet.size} {contact_sheet.mode}")
        if contact_sheet.size != CONTACT_SHEET_SIZE:
            fail(f"{CONTACT_SHEET_02.relative_to(ROOT)} is {contact_sheet.size}, expected {CONTACT_SHEET_SIZE}")
        if contact_sheet.mode != "RGB":
            fail("second contact sheet should be RGB")


def validate_wordmark_rule() -> None:
    readme = (SOCIAL_DIR / "README.md").read_text(encoding="utf-8")
    if "the word Latticra no more than once per card" not in readme:
        fail("social README is missing the one-Latticra rule")
    generator = (ROOT / "scripts" / "generate-latticra-social-cards.py").read_text(encoding="utf-8")
    wordmark_section = generator.split("def wordmark_card", 1)[1]
    if "@Latticra" in wordmark_section:
        fail("wordmark card generator repeats @Latticra")
    if CURRENT_CANDIDATE is None:
        if "Current review candidate:\n\n```text\nnone\n```" not in readme:
            fail("social README should show no current candidate")
        if "Current visual candidate:\n\n```text\nnone\n```" not in QUEUE.read_text(encoding="utf-8"):
            fail("approval queue should show no current visual candidate")
    else:
        if not (SOCIAL_DIR / CURRENT_CANDIDATE).exists():
            fail("current candidate image does not exist")
        if CURRENT_CANDIDATE not in readme:
            fail("social README does not name the current candidate")
        queue = QUEUE.read_text(encoding="utf-8")
        if CURRENT_CANDIDATE not in queue:
            fail("approval queue does not name the current candidate")
        for label, text in (("social README", readme), ("approval queue", queue)):
            position = text.find(CURRENT_CANDIDATE)
            context = text[max(0, position - 220): position + len(CURRENT_CANDIDATE) + 220]
            if "approved visual" not in context and "approved as visual" not in context:
                fail(f"{label} current candidate lacks visual-approval context")
    candidate_section = generator.split("def glass_base_card", 1)[1].split("\ndef boundary_literacy_glass() -> None:", 1)[0]
    emblem_helper = generator.split("def paste_emblem", 1)[1].split("\ndef boundary_literacy_premium", 1)[0]
    if "EMBLEM_PATH" not in emblem_helper or "paste_emblem(" not in candidate_section:
        fail("current candidate generator does not use the official emblem")
    background_helper = generator.split("def load_glass_background", 1)[1].split("\ndef glass_background_v1", 1)[0]
    if "BACKGROUND_SOURCE_PATH" not in background_helper or "load_glass_background()" not in candidate_section:
        fail("current candidate generator does not use the approved glass background source")
    if not BACKGROUND_BASE.exists():
        fail("normalized approved glass background does not exist")
    if "WORDMARK_PATH" in candidate_section:
        fail("current candidate generator uses the wordmark banner as a background")
    if candidate_section.count('"Latticra"') != 1:
        fail("current candidate generator should write Latticra exactly once")
    if "@Latticra" in candidate_section:
        fail("current candidate generator repeats @Latticra")
    for candidate in GLASS_BASE_CANDIDATES:
        if candidate not in candidate_section:
            fail(f"glass-base candidate is not generated: {candidate}")
    for candidate in GLASS_BASE_SECOND_SEQUENCE:
        if candidate not in candidate_section:
            fail(f"second-sequence glass-base candidate is not generated: {candidate}")


def validate_visual_series_artifacts() -> None:
    readme = (SOCIAL_DIR / "README.md").read_text(encoding="utf-8")
    packet = VISUAL_SERIES_PACKET.read_text(encoding="utf-8")
    matrix = MEDIA_APPROVAL_MATRIX.read_text(encoding="utf-8")
    queue = QUEUE.read_text(encoding="utf-8")
    for candidate in GLASS_BASE_CANDIDATES:
        if not (SOCIAL_DIR / candidate).exists():
            fail(f"missing glass-base candidate: {candidate}")
        for label, text in (("social README", readme), ("visual series packet", packet), ("media approval matrix", matrix)):
            if candidate not in text:
                fail(f"{label} does not reference {candidate}")
            position = text.find(candidate)
            context = text[max(0, position - 520): position + len(candidate) + 520]
            if "approved visual" not in context and "approved as visual" not in context:
                fail(f"{label} lacks visual-approval context near {candidate}")
            if (
                "public post not approved" not in context
                and "not approved for public posting" not in context
                and "exact-action approval" not in context
                and "owner-approved for execution" not in context
            ):
                fail(f"{label} lacks public-post boundary or execution context near {candidate}")
    for required in (
        "owner rating: 10/10 as a base",
        "No public X action is approved by this packet alone.",
        "exact alt-text approval",
        "write the word Latticra only once per card",
    ):
        if required not in packet:
            fail(f"visual series packet missing required item: {required}")
    if "five-card overlay series" not in queue:
        fail("approval queue does not describe the five-card visual series")
    contact_rel = "assets/social/review/latticra-glass-base-series-contact-sheet.png"
    if "review/latticra-glass-base-series-contact-sheet.png" not in readme:
        fail("social README does not reference contact sheet")
    for label, text in (("visual series packet", packet), ("media approval matrix", matrix)):
        if contact_rel not in text:
            fail(f"{label} does not reference contact sheet")
        position = text.find(contact_rel)
        context = text[max(0, position - 220): position + len(contact_rel) + 220]
        if "not approved" not in context or "internal review" not in context:
            fail(f"{label} contact sheet lacks review-only context")


def validate_media_approval_matrix() -> None:
    matrix = MEDIA_APPROVAL_MATRIX.read_text(encoding="utf-8")
    for required in (
        "No public X action is approved by this matrix alone.",
        "exact post text must be approved",
        "exact card asset must be one of the approved good glass-base cards",
        "exact alt text must be approved",
        "no outbound public action within about 5 hours",
        "approved visual assets can move into publication review",
        "approve another exact post using an approved card",
        "owner-authorized execution logged",
        "https://x.com/Latticra/status/2059941871787347985",
    ):
        if required not in matrix:
            fail(f"media approval matrix missing required item: {required}")
    if matrix.count("Approval line:\n\n```text\nowner approved;") != len(GLASS_BASE_CANDIDATES):
        fail("media approval matrix should show every package as owner-approved for execution")
    if matrix.count("Media status:\n\n```text\napproved visual asset; owner-approved for execution\n```") != len(GLASS_BASE_CANDIDATES):
        fail("media approval matrix should show every package as visual-approved and owner-approved for execution")
    if matrix.count("Alt text:\n\n```text\n") != len(GLASS_BASE_CANDIDATES):
        fail("media approval matrix should include alt text for every package")


def validate_next_sequence_packet() -> None:
    packet = NEXT_SEQUENCE_PACKET.read_text(encoding="utf-8")
    readme = (SOCIAL_DIR / "README.md").read_text(encoding="utf-8")
    strategy_readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    if NEXT_SEQUENCE_PACKET.name not in strategy_readme:
        fail("strategy README does not reference next education sequence packet")
    for required in (
        "prepared for owner review; no public posting approved",
        "no public post without exact owner approval",
        "assets/social/review/latticra-glass-base-series-02-contact-sheet.png",
        "not approved for public posting",
        "earliest practical next slot after the corrected Evidence post: 2026-05-28 20:00 CDT",
        "more conservative next slot: 2026-05-29 10:00 CDT",
        "2026-05-28-1605-cdt-x-next-manual-post-approval-packet.md",
    ):
        if required not in packet:
            fail(f"next sequence packet missing required item: {required}")
    for candidate in GLASS_BASE_SECOND_SEQUENCE:
        if not (SOCIAL_DIR / candidate).exists():
            fail(f"missing second-sequence candidate: {candidate}")
        for label, text in (("social README", readme), ("next sequence packet", packet)):
            if candidate not in text:
                fail(f"{label} does not reference {candidate}")
            position = text.find(candidate)
            context = text[max(0, position - 320): position + len(candidate) + 320]
            if "not approved" not in context or "internal candidate" not in context:
                fail(f"{label} lacks internal not-approved context near {candidate}")
    if "review/latticra-glass-base-series-02-contact-sheet.png" not in readme:
        fail("social README does not reference second contact sheet")


def validate_mention_response_packet() -> None:
    packet = MENTION_RESPONSE_PACKET.read_text(encoding="utf-8")
    readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    playbook = ENGAGEMENT_PLAYBOOK.read_text(encoding="utf-8")
    if MENTION_RESPONSE_PACKET.name not in readme:
        fail("strategy README does not reference mention response packet")
    if MENTION_RESPONSE_PACKET.as_posix().replace(str(ROOT) + "/", "") not in playbook:
        fail("engagement playbook does not reference mention response packet")
    for required in (
        "no public replies approved by this packet alone",
        "get exact action-time approval before posting",
        "do not create bursts of public replies",
        "What Is Latticra?",
        "Post-Quantum Question",
        "Too-Broad Security Claim",
        "Mention Review Form",
        "reply timestamp",
    ):
        if required not in packet:
            fail(f"mention response packet missing required item: {required}")


def validate_mention_intake_log() -> None:
    log = MENTION_INTAKE_LOG.read_text(encoding="utf-8")
    readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    ledger = PERFORMANCE_LEDGER.read_text(encoding="utf-8")
    if MENTION_INTAKE_LOG.name not in readme:
        fail("strategy README does not reference mention intake log")
    if MENTION_INTAKE_LOG.as_posix().replace(str(ROOT) + "/", "") not in ledger:
        fail("performance ledger does not reference mention intake log")
    for required in (
        "public_action_taken=none",
        "outside_commenters_seen=0",
        "visible_replies=0",
        "No public replies are recommended from the current mention snapshot.",
        "https://x.com/ckbryan91/status/2059947073403826282",
        "https://x.com/ckbryan91/status/2059914666680168859",
        "https://x.com/ckbryan91/status/2059912077578318152",
        "https://x.com/ckbryan91/status/2059786024989950328",
        "https://x.com/ckbryan91/status/2059163031028879383",
    ):
        if required not in log:
            fail(f"mention intake log missing required item: {required}")
    if log.count("Approval status:\n\n```text\nnot approved\n```") != 5:
        fail("mention intake log should keep every drafted reply not approved")


def validate_early_monitoring_checkpoint() -> None:
    checkpoint = EARLY_MONITORING_CHECKPOINT.read_text(encoding="utf-8")
    readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    ledger = PERFORMANCE_LEDGER.read_text(encoding="utf-8")
    if EARLY_MONITORING_CHECKPOINT.name not in readme:
        fail("strategy README does not reference early monitoring checkpoint")
    if EARLY_MONITORING_CHECKPOINT.as_posix().replace(str(ROOT) + "/", "") not in ledger:
        fail("performance ledger does not reference early monitoring checkpoint")
    for required in (
        "read-only monitoring checkpoint",
        "public_action_taken=none",
        "checked_at_cdt=2026-05-28 06:01",
        "profile_followers=1",
        "following=24",
        "visible_replies=0",
        "visible_reposts=1",
        "visible_likes=1",
        "visible_views=15",
        "outside_commenters_seen=0",
        "recommended_public_replies=0",
        "2026-05-28 10:00 CDT",
    ):
        if required not in checkpoint:
            fail(f"early monitoring checkpoint missing required item: {required}")


def validate_ten_am_verification_runbook() -> None:
    runbook = TEN_AM_VERIFICATION_RUNBOOK.read_text(encoding="utf-8")
    readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    ledger = PERFORMANCE_LEDGER.read_text(encoding="utf-8")
    if TEN_AM_VERIFICATION_RUNBOOK.name not in readme:
        fail("strategy README does not reference 10am verification runbook")
    if TEN_AM_VERIFICATION_RUNBOOK.as_posix().replace(str(ROOT) + "/", "") not in ledger:
        fail("performance ledger does not reference 10am verification runbook")
    for required in (
        "active post-publication verification runbook",
        "scheduled_for_cdt=2026-05-28 10:00",
        "topic=Boundary Literacy",
        "assets/social/latticra-boundary-literacy-glass-base-card.png",
        "take no public action without exact action-time approval",
        "move the scheduled Boundary Literacy row into the ledger as a published post",
        "do not retry-post manually",
        "automation_id=verify-latticra-10am-post",
        "public_action_authorization=none",
        "chain_plan=docs/strategy/2026-05-28-0610-cdt-x-scheduled-queue-verification-chain.md",
        "after_success_next_target=2026-05-28 15:05 CDT",
        "do not create workaround cron automations",
    ):
        if required not in runbook:
            fail(f"10am verification runbook missing required item: {required}")


def validate_scheduled_queue_verification_chain() -> None:
    chain = SCHEDULED_QUEUE_VERIFICATION_CHAIN.read_text(encoding="utf-8")
    readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    ledger = PERFORMANCE_LEDGER.read_text(encoding="utf-8")
    if SCHEDULED_QUEUE_VERIFICATION_CHAIN.name not in readme:
        fail("strategy README does not reference scheduled queue verification chain")
    if SCHEDULED_QUEUE_VERIFICATION_CHAIN.as_posix().replace(str(ROOT) + "/", "") not in ledger:
        fail("performance ledger does not reference scheduled queue verification chain")
    for required in (
        "active verification chain plan",
        "automation_id=verify-latticra-10am-post",
        "single active thread heartbeat",
        "do not create workaround cron automations",
        "verification_time_cdt=2026-05-28 10:05",
        "verification_time_cdt=2026-05-28 15:05",
        "verification_time_cdt=2026-05-28 20:05",
        "verification_time_cdt=2026-05-29 01:05",
        "assets/social/latticra-boundary-literacy-glass-base-card.png",
        "assets/social/latticra-evidence-before-claims-glass-base-card.png",
        "assets/social/latticra-denial-is-legible-glass-base-card.png",
        "assets/social/latticra-cryptography-without-hype-glass-base-card.png",
        "take no public X actions without exact action-time approval",
        "do not manually repost",
    ):
        if required not in chain:
            fail(f"scheduled queue verification chain missing required item: {required}")


def validate_status_metrics_tooling() -> None:
    if not STATUS_METRICS_SCRIPT.exists():
        fail("missing X status metrics helper")
    script = STATUS_METRICS_SCRIPT.read_text(encoding="utf-8")
    readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    ledger = PERFORMANCE_LEDGER.read_text(encoding="utf-8")
    ten_am = TEN_AM_VERIFICATION_RUNBOOK.read_text(encoding="utf-8")
    chain = SCHEDULED_QUEUE_VERIFICATION_CHAIN.read_text(encoding="utf-8")
    for required in (
        "X_EPOCH_MS = 1288834974657",
        "def parse_status_id",
        "def decode_status_time",
        "created_at_local_readable",
        "elapsed_from_previous",
    ):
        if required not in script:
            fail(f"X status metrics helper missing required item: {required}")
    for label, text in (
        ("strategy README", readme),
        ("performance ledger", ledger),
        ("10am verification runbook", ten_am),
        ("scheduled queue verification chain", chain),
    ):
        if "scripts/latticra-x-status-metrics.py" not in text:
            fail(f"{label} does not reference X status metrics helper")


def validate_review_board() -> None:
    board = REVIEW_BOARD.read_text(encoding="utf-8")
    readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    social_readme = (SOCIAL_DIR / "README.md").read_text(encoding="utf-8")
    if REVIEW_BOARD.name not in readme:
        fail("strategy README does not reference the local review board")
    if f"../../docs/strategy/{REVIEW_BOARD.name}" not in social_readme:
        fail("social README does not reference the local review board")
    for candidate in GLASS_BASE_CANDIDATES:
        rel = f"../../assets/social/{candidate}"
        if rel not in board:
            fail(f"review board does not reference {rel}")
    for required in (
        "../../assets/social/review/latticra-glass-base-series-contact-sheet.png",
        "Internal review only",
        "nothing here authorizes posting",
        "visual approved; post not approved",
        "about-5-hour public-action cadence",
        "Copy post",
        "Copy alt text",
        "public posting still requires exact post, alt text, and window approval",
    ):
        if required not in board:
            fail(f"review board missing required item: {required}")


def validate_growth_artifacts() -> None:
    queue = QUEUE.read_text(encoding="utf-8")
    readme = (ROOT / "docs" / "strategy" / "README.md").read_text(encoding="utf-8")
    playbook = ENGAGEMENT_PLAYBOOK.read_text(encoding="utf-8")
    ledger = PERFORMANCE_LEDGER.read_text(encoding="utf-8")
    for path in (
        TEXT_BANK,
        ENGAGEMENT_PLAYBOOK,
        PERFORMANCE_LEDGER,
        PROFILE_CONVERSION,
        PUBLISH_PACKET,
        VISUAL_SERIES_PACKET,
        MEDIA_APPROVAL_MATRIX,
        REVIEW_BOARD,
        FIRST_LIVE_POST_PACKET,
        MENTION_RESPONSE_PACKET,
        MENTION_INTAKE_LOG,
        EARLY_MONITORING_CHECKPOINT,
        TEN_AM_VERIFICATION_RUNBOOK,
        SCHEDULED_QUEUE_VERIFICATION_CHAIN,
        NEXT_SEQUENCE_PACKET,
        NEXT_MANUAL_APPROVAL_PACKET,
        GROWTH_CONVERSATION_PACKET,
        APPROVAL_SHORTLIST_LADDER,
        DENIAL_POST_HANDOFF,
        DENIAL_POST_DECISION_PACKET,
        CRYPTOGRAPHY_POST_HANDOFF,
        ROLLING_APPROVAL_CALENDAR,
        LIVE_GROWTH_CHECKPOINT,
        PROFILE_PIN_DECISION_PACKET,
    ):
        if not path.exists():
            fail(f"missing growth artifact: {path.relative_to(ROOT)}")
        if path.name not in readme:
            fail(f"strategy README does not reference {path.name}")
    if TEXT_BANK.as_posix().replace(str(ROOT) + "/", "") not in queue:
        fail("approval queue does not reference the text-first bank")
    for required in (
        "one public action about every 5 hours",
        "no hashtags",
        "Non-Claim Guard",
        "Mention Readiness",
        "ask for exact action-time approval before posting",
        "docs/strategy/2026-05-28-1905-cdt-x-growth-conversation-packet.md",
        "docs/strategy/2026-05-28-1908-cdt-x-approval-shortlist-cadence-ladder.md",
        "docs/strategy/2026-05-28-1910-cdt-x-20pm-denial-post-handoff.md",
        "docs/strategy/2026-05-28-1913-cdt-x-denial-post-verification-decision-packet.md",
        "docs/strategy/2026-05-28-1916-cdt-x-1am-cryptography-post-handoff.md",
        "docs/strategy/2026-05-28-1918-cdt-x-rolling-approval-calendar.md",
        "docs/strategy/2026-05-28-1924-cdt-x-live-growth-checkpoint.md",
        "docs/strategy/2026-05-28-1932-cdt-x-profile-pin-conversion-decision-packet.md",
    ):
        if required not in playbook:
            fail(f"engagement playbook missing required rule: {required}")
    for required in (
        "Baseline follower count: 1",
        "First public X action is logged.",
        "https://x.com/Latticra/status/2059941871787347985",
        "https://x.com/Latticra/status/2060013233248104679",
        "https://x.com/Latticra/status/2060093439945936993",
        "2026-05-28 10:00",
        "2026-05-28 15:00",
        "2026-05-28 20:00",
        "2026-05-29 01:00",
        "5h Cadence Kept",
        "Latest read-only mention check",
        "outside_commenters_seen=0",
        "Early Performance Checkpoints",
        "first_post_visible_views=15",
        "recommended_public_replies=0",
        "Current Verification",
        "next_public_action_status=approval required",
        "Scheduled queue verification chain",
        "remaining_scheduled_queue=deleted from X scheduled drafts at 2026-05-28 15:20 CDT",
        "new_posting_rule=attach media, add alt text, paste caption from clipboard, visually verify visible caption text in composer, then post",
        "scheduled_posts_visible_in_x=0",
        "next_recommended_window=2026-05-28 20:00 CDT only if owner explicitly approves a manually verified post",
        "checkpoint_4=2026-05-29 01:05 CDT Cryptography Without Hype canceled from X scheduled drafts",
        "live_growth_checkpoint=docs/strategy/2026-05-28-1924-cdt-x-live-growth-checkpoint.md",
        "checked_at_cdt=2026-05-28 19:24",
        "first_post_visible_views=24",
        "boundary_post_visible_views=4",
        "evidence_post_visible_views=38",
        "known_image_only_duplicate_urls_unavailable=yes",
        "log=docs/strategy/2026-05-28-1932-cdt-x-profile-pin-conversion-decision-packet.md",
        "public_research_standard_visible_views=25",
        "evidence_before_claims_visible_views=39",
        "profile_action_status=approval required",
        "recommended_profile_default=wait until the 24-hour review before pinning or editing the bio",
        "profile_pin_decision_at_1932=wait until the 24-hour review unless the owner gives exact approval for an immediate pin",
    ):
        if required not in ledger:
            fail(f"performance ledger missing required baseline: {required}")
    profile = PROFILE_CONVERSION.read_text(encoding="utf-8")
    for required in (
        "Bio Option C",
        "Pinned Option A",
        "No profile action is approved by this packet alone.",
        "followers: 1",
        "docs/strategy/2026-05-28-1932-cdt-x-profile-pin-conversion-decision-packet.md",
        "before approving any pin, unpin, bio edit, header edit, or pinned-orientation post",
    ):
        if required not in profile:
            fail(f"profile conversion packet missing required item: {required}")
    publish_packet = PUBLISH_PACKET.read_text(encoding="utf-8")
    for required in (
        "No public X action is approved by this packet alone.",
        "about 5 hours",
        "Queue Item 1",
        "text-only posting",
        "generated glass background source rated 10/10 as a base direction",
        "five glass-base cards are approved as visual assets",
        "media-ready approval matrix exists for exact package review",
    ):
        if required not in publish_packet:
            fail(f"publish packet missing required item: {required}")
    first_packet = FIRST_LIVE_POST_PACKET.read_text(encoding="utf-8")
    for required in (
        "first post published; follow-up queue scheduled",
        "published after owner confirmation and live browser preparation",
        "https://x.com/Latticra/status/2059941871787347985",
        "assets/social/latticra-public-research-standard-glass-base-card.png",
        "assets/social/latticra-boundary-literacy-glass-base-card.png",
        "assets/social/latticra-evidence-before-claims-glass-base-card.png",
        "assets/social/latticra-denial-is-legible-glass-base-card.png",
        "assets/social/latticra-cryptography-without-hype-glass-base-card.png",
        "2026-05-28 10:00 CDT",
        "2026-05-28 15:00 CDT",
        "2026-05-28 20:00 CDT",
        "2026-05-29 01:00 CDT",
        "next_slot = first_live_timestamp + 5 hours - extra minutes and seconds from first_live_timestamp",
        "keep posts on an even hour",
        "about 5 hours",
    ):
        if required not in first_packet:
            fail(f"first live post packet missing required item: {required}")
    manual_packet = NEXT_MANUAL_APPROVAL_PACKET.read_text(encoding="utf-8")
    for required in (
        "No public X action is approved by this packet alone.",
        "next_public_action_status=approval required",
        "candidate_window_cdt=2026-05-28 20:00",
        "assets/social/latticra-denial-is-legible-glass-base-card.png",
        "assets/social/latticra-cryptography-without-hype-glass-base-card.png",
        "paste caption from clipboard",
        "visually verify visible caption text in composer",
        "latticra-3-day-content-cadence",
        "no public reply, like, repost, follow, message, schedule action, or new post without exact owner approval",
        "docs/strategy/2026-05-28-1910-cdt-x-20pm-denial-post-handoff.md",
    ):
        if required not in manual_packet:
            fail(f"next manual approval packet missing required item: {required}")
    growth_packet = GROWTH_CONVERSATION_PACKET.read_text(encoding="utf-8")
    for required in (
        "prepared for owner review; no public action approved",
        "no public X action is approved by this packet alone",
        "exact owner approval is required at action time",
        "no production-readiness claim",
        "Conversation Post Seeds",
        "Reply Starters",
        "What Are You Building?",
        "Crypto Question",
        "approval_shortlist=docs/strategy/2026-05-28-1908-cdt-x-approval-shortlist-cadence-ladder.md",
        "recommended_public_action_now=none without exact owner approval",
    ):
        if required not in growth_packet:
            fail(f"growth conversation packet missing required item: {required}")
    ladder = APPROVAL_SHORTLIST_LADDER.read_text(encoding="utf-8")
    for required in (
        "prepared for owner review; no public action approved",
        "no public X action is approved by this ladder alone",
        "exact owner approval is required for each post, media item, alt text, and action time",
        "last_live_time_cdt=2026-05-28 15:18:45",
        "next_even_hour_candidate=2026-05-28 20:00 CDT",
        "docs/strategy/2026-05-28-1910-cdt-x-20pm-denial-post-handoff.md",
        "post_publication_decision=docs/strategy/2026-05-28-1913-cdt-x-denial-post-verification-decision-packet.md",
        "Execution handoff: docs/strategy/2026-05-28-1916-cdt-x-1am-cryptography-post-handoff.md",
        "rolling_calendar=docs/strategy/2026-05-28-1918-cdt-x-rolling-approval-calendar.md",
        "assets/social/latticra-denial-is-legible-glass-base-card.png",
        "assets/social/latticra-cryptography-without-hype-glass-base-card.png",
        "AI tools make intent easy to express.",
        "Linux-native evaluation matters because people can challenge the work locally.",
        "long-term content automation remains approval-only through latticra-3-day-content-cadence",
    ):
        if required not in ladder:
            fail(f"approval shortlist ladder missing required item: {required}")
    handoff = DENIAL_POST_HANDOFF.read_text(encoding="utf-8")
    for required in (
        "prepared for owner review; no public action approved",
        "no public X action is approved by this handoff alone",
        "exact owner approval is required at action time",
        "do not schedule this post unless the owner explicitly approves scheduling",
        "assets/social/latticra-denial-is-legible-glass-base-card.png",
        "A denied action should still produce useful information:",
        "Latticra educational card on a luminous white and pale blue glass background.",
        "previous_public_time_cdt=2026-05-28 15:18:45",
        "target_window_cdt=2026-05-28 20:00:00",
        "paste caption from clipboard and visually verify it before pressing Post",
        "post_publication_decision_packet=docs/strategy/2026-05-28-1913-cdt-x-denial-post-verification-decision-packet.md",
        "public_action_status=not approved",
    ):
        if required not in handoff:
            fail(f"denial post handoff missing required item: {required}")
    decision_packet = DENIAL_POST_DECISION_PACKET.read_text(encoding="utf-8")
    for required in (
        "prepared for owner review; no public action approved",
        "No public action is approved by this packet alone.",
        "handoff=docs/strategy/2026-05-28-1910-cdt-x-20pm-denial-post-handoff.md",
        "handoff_packet=docs/strategy/2026-05-28-1916-cdt-x-1am-cryptography-post-handoff.md",
        "expected_media=assets/social/latticra-denial-is-legible-glass-base-card.png",
        "python3 scripts/latticra-x-status-metrics.py https://x.com/Latticra/status/<status_id>",
        "do not decide the 01:00 follow-up from views alone",
        "candidate_window_cdt=2026-05-29 01:00",
        "candidate_media=assets/social/latticra-cryptography-without-hype-glass-base-card.png",
        "resume_candidate_source=docs/strategy/2026-05-28-1918-cdt-x-rolling-approval-calendar.md",
        "the owner explicitly approves the 01:00 post text, media, alt text, and action time",
        "no public reply, like, repost, follow, message, schedule action, profile edit, or new post without exact owner approval",
    ):
        if required not in decision_packet:
            fail(f"denial post decision packet missing required item: {required}")
    crypto_handoff = CRYPTOGRAPHY_POST_HANDOFF.read_text(encoding="utf-8")
    for required in (
        "prepared for owner review; no public action approved",
        "no public X action is approved by this handoff alone",
        "exact owner approval is required at action time",
        "denial_post_status=published and verified",
        "assets/social/latticra-cryptography-without-hype-glass-base-card.png",
        "Cryptography without hype:",
        "Quantum-resistant planning should not begin with promises.",
        "does not claim quantum resistance is delivered",
        "expected_previous_public_time_cdt=2026-05-28 20:00:00",
        "target_window_cdt=2026-05-29 01:00:00",
        "public_action_status=not approved",
    ):
        if required not in crypto_handoff:
            fail(f"cryptography post handoff missing required item: {required}")
    rolling_calendar = ROLLING_APPROVAL_CALENDAR.read_text(encoding="utf-8")
    for required in (
        "prepared for owner review; no public action approved",
        "no public X action is approved by this calendar alone",
        "keep at least one prepared educational post available every 3 days",
        "Friday, 2026-05-29, 10:00 CDT",
        "AI tools make intent easy to express.",
        "Linux-native evaluation matters because people can challenge the work locally.",
        "Careful cryptography language should leave room for inspection.",
        "automation_id=latticra-3-day-content-cadence",
        "public_action_status=approval required",
    ):
        if required not in rolling_calendar:
            fail(f"rolling approval calendar missing required item: {required}")
    live_checkpoint = LIVE_GROWTH_CHECKPOINT.read_text(encoding="utf-8")
    for required in (
        "read-only monitoring and owner-review packet; no public action approved",
        "no public X action is approved by this checkpoint alone",
        "exact owner approval is required for any post, reply, like, repost, follow, schedule action, message, or profile edit",
        "public_action_taken=none",
        "visible_profile_posts=Public Research Standard, Boundary Literacy, Evidence Before Claims",
        "unexpected_card_only_duplicate_seen=no",
        "https://x.com/Latticra/status/2060088723979808903 unavailable; X showed page does not exist",
        "https://x.com/Latticra/status/2060092399032893780 unavailable; X showed page does not exist",
        "first_post_visible_views=24",
        "boundary_post_visible_views=4",
        "evidence_post_visible_views=38",
        "outside_commenters_seen=0",
        "recommended_public_replies=0",
        "docs/strategy/2026-05-28-1910-cdt-x-20pm-denial-post-handoff.md",
        "assets/social/latticra-denial-is-legible-glass-base-card.png",
        "resume from docs/strategy/2026-05-28-1918-cdt-x-rolling-approval-calendar.md",
        "preferred_resume_window=2026-05-29 10:00 CDT or the next owner-approved 10:00 CDT slot",
        "AI tools make intent easy to express.",
        "no public reply, like, repost, follow, message, schedule action, profile edit, or new post without exact owner approval",
    ):
        if required not in live_checkpoint:
            fail(f"live growth checkpoint missing required item: {required}")
    profile_pin_packet = PROFILE_PIN_DECISION_PACKET.read_text(encoding="utf-8")
    for required in (
        "prepared for owner review; no public profile action approved",
        "no public X action is approved by this packet alone",
        "pinning, unpinning, editing the bio, editing the header, or publishing a pinned-orientation post all require exact owner approval",
        "do not change the profile before the 2026-05-28 20:00 CDT Denial decision window",
        "public_action_taken=none",
        "Evidence Before Claims",
        "https://x.com/Latticra/status/2060093439945936993",
        "https://x.com/Latticra/status/2059941871787347985",
        "public_research_standard_visible_views=25",
        "boundary_literacy_visible_views=4",
        "evidence_before_claims_visible_views=39",
        "outside_commenters_seen=0",
        "Option A - Pin Evidence Before Claims",
        "Option B - Pin Public Research Standard",
        "Option C - Wait And Pin After 24-Hour Review",
        "What to expect here:",
        "Systems research for Linux-native secure substrates. Teaching boundary literacy, operator-visible evidence, and cryptographic planning without hype.",
        "wait until the 24-hour review before pinning or editing the bio",
        "no profile edit, pin, unpin, post, reply, like, repost, follow, message, or schedule action without exact owner approval",
    ):
        if required not in profile_pin_packet:
            fail(f"profile pin conversion packet missing required item: {required}")


def main() -> None:
    validate_post_lengths(QUEUE)
    validate_post_lengths(CALENDAR)
    validate_post_lengths(TEXT_BANK)
    validate_post_lengths(PUBLISH_PACKET)
    validate_post_lengths(MEDIA_APPROVAL_MATRIX)
    validate_post_lengths(FIRST_LIVE_POST_PACKET)
    validate_post_lengths(TEN_AM_VERIFICATION_RUNBOOK)
    validate_post_lengths(SCHEDULED_QUEUE_VERIFICATION_CHAIN)
    validate_post_lengths(NEXT_SEQUENCE_PACKET)
    validate_post_lengths(NEXT_MANUAL_APPROVAL_PACKET)
    validate_post_lengths(GROWTH_CONVERSATION_PACKET)
    validate_post_lengths(APPROVAL_SHORTLIST_LADDER)
    validate_post_lengths(DENIAL_POST_HANDOFF)
    validate_post_lengths(DENIAL_POST_DECISION_PACKET)
    validate_post_lengths(CRYPTOGRAPHY_POST_HANDOFF)
    validate_post_lengths(ROLLING_APPROVAL_CALENDAR)
    validate_post_lengths(LIVE_GROWTH_CHECKPOINT)
    validate_post_lengths(PROFILE_PIN_DECISION_PACKET)
    validate_reply_lengths(MENTION_RESPONSE_PACKET)
    validate_reply_lengths(GROWTH_CONVERSATION_PACKET)
    validate_media_references(QUEUE)
    validate_media_references(CALENDAR)
    validate_media_references(TEXT_BANK)
    validate_media_references(PUBLISH_PACKET)
    validate_media_references(MEDIA_APPROVAL_MATRIX)
    validate_media_references(FIRST_LIVE_POST_PACKET)
    validate_media_references(TEN_AM_VERIFICATION_RUNBOOK)
    validate_media_references(SCHEDULED_QUEUE_VERIFICATION_CHAIN)
    validate_media_references(NEXT_MANUAL_APPROVAL_PACKET)
    validate_media_references(NEXT_SEQUENCE_PACKET)
    validate_media_references(GROWTH_CONVERSATION_PACKET)
    validate_media_references(APPROVAL_SHORTLIST_LADDER)
    validate_media_references(DENIAL_POST_HANDOFF)
    validate_media_references(DENIAL_POST_DECISION_PACKET)
    validate_media_references(CRYPTOGRAPHY_POST_HANDOFF)
    validate_media_references(ROLLING_APPROVAL_CALENDAR)
    validate_media_references(LIVE_GROWTH_CHECKPOINT)
    validate_media_references(PROFILE_PIN_DECISION_PACKET)
    validate_images()
    validate_wordmark_rule()
    validate_visual_series_artifacts()
    validate_media_approval_matrix()
    validate_next_sequence_packet()
    validate_mention_response_packet()
    validate_mention_intake_log()
    validate_early_monitoring_checkpoint()
    validate_ten_am_verification_runbook()
    validate_scheduled_queue_verification_chain()
    validate_status_metrics_tooling()
    validate_review_board()
    validate_growth_artifacts()
    print("OK: Latticra social content validation passed")


if __name__ == "__main__":
    main()

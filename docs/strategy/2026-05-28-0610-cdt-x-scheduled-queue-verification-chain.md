# Latticra X Scheduled Queue Verification Chain

Status: active verification chain plan
Created: 2026-05-28 06:10 CDT
Account: @Latticra
Scope: chained thread follow-ups for the first scheduled @Latticra launch queue.

## Purpose

This plan keeps the launch queue monitored without creating public noise.

The Codex app currently allows one active heartbeat attached to this thread. The active 10:05 CDT heartbeat therefore needs to update itself to the next checkpoint after it verifies the 10:00 CDT scheduled post.

Machine-readable automation boundary:

```text
single active thread heartbeat
take no public X actions without exact action-time approval
```

## Active Heartbeat

Current thread heartbeat:

```text
automation_id=verify-latticra-10am-post
current_target=2026-05-28 10:05 CDT
target_post=Boundary Literacy
public_action_authorization=none
```

Heartbeat chaining rule:

```text
after each checkpoint finishes, update the same thread heartbeat to the next scheduled-post verification time
do not create workaround cron automations
do not take public X actions without exact action-time approval
```

## Verification Sequence

### Checkpoint 1

```text
verification_time_cdt=2026-05-28 10:05
scheduled_post_time_cdt=2026-05-28 10:00
topic=Boundary Literacy
media=assets/social/latticra-boundary-literacy-glass-base-card.png
expected_action=verify live URL, metrics, comments, mentions, and ledger state
next_heartbeat_target=2026-05-28 15:05 CDT
```

### Checkpoint 2

```text
verification_time_cdt=2026-05-28 15:05
scheduled_post_time_cdt=2026-05-28 15:00
topic=Evidence Before Claims
media=assets/social/latticra-evidence-before-claims-glass-base-card.png
expected_action=verify live URL, metrics, comments, mentions, and ledger state
next_heartbeat_target=2026-05-28 20:05 CDT
```

### Checkpoint 3

```text
verification_time_cdt=2026-05-28 20:05
scheduled_post_time_cdt=2026-05-28 20:00
topic=Denial Is Legible
media=assets/social/latticra-denial-is-legible-glass-base-card.png
expected_action=verify live URL, metrics, comments, mentions, and ledger state
next_heartbeat_target=2026-05-29 01:05 CDT
```

### Checkpoint 4

```text
verification_time_cdt=2026-05-29 01:05
scheduled_post_time_cdt=2026-05-29 01:00
topic=Cryptography Without Hype
media=assets/social/latticra-cryptography-without-hype-glass-base-card.png
expected_action=verify live URL, metrics, comments, mentions, and ledger state
next_heartbeat_target=2026-05-29 05:20 CDT first-post 24h review if still useful
```

## Checkpoint Procedure

At each checkpoint:

```text
inspect @Latticra profile read-only
confirm whether the expected scheduled post is public
capture the status URL if visible
decode the status URL with scripts/latticra-x-status-metrics.py
record visible replies, reposts, likes, views, bookmarks when shown, and follower count
inspect mentions/comments read-only
draft replies only for sincere questions, good-faith critiques, evidence requests, or materially misleading claims
take no public reply, like, repost, follow, profile edit, or new post without exact action-time approval
update the performance ledger and monitoring docs
run python3 scripts/validate-latticra-social-content.py
run python3 -m py_compile scripts/generate-latticra-social-cards.py scripts/validate-latticra-social-content.py
```

Status timing helper:

```text
python3 scripts/latticra-x-status-metrics.py https://x.com/Latticra/status/<status_id>
python3 scripts/latticra-x-status-metrics.py <previous_status_url> <current_status_url>
```

## Failure Procedure

If a scheduled post is not visible after its checkpoint:

```text
do not manually repost
record the scheduler verification failure
inspect scheduled-post state only if available without public side effects
ask the owner before any corrective public action
preserve the remaining scheduled queue
```

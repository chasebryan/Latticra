# Latticra X 10:00 CDT Verification Runbook

Status: active post-publication verification runbook
Created: 2026-05-28 06:06 CDT
Account: @Latticra
Scope: verification steps for the scheduled 2026-05-28 10:00 CDT Boundary Literacy post.

## Purpose

This runbook keeps the next checkpoint precise.

The goal after 10:00 CDT is to verify publication, capture evidence, and decide whether any comment deserves a drafted response. It does not authorize any public reply, like, repost, follow, profile edit, or new post.

## Scheduled Post To Verify

Expected scheduled post:

```text
scheduled_for_cdt=2026-05-28 10:00
topic=Boundary Literacy
media=assets/social/latticra-boundary-literacy-glass-base-card.png
expected_status=published by X scheduler after 10:00 CDT
```

Expected post text:

```text
Boundary literacy:

In Latticra, a denial path is not a failure to hide. It is a result to make visible.

If a system says no, the operator should be able to understand why.
```

Expected alt text:

```text
Latticra educational card on a luminous white and pale blue glass background. The card says "Boundary Literacy" and explains that authority should be visible before behavior becomes consequential. The official blue Latticra emblem appears on the right.
```

## Read-Only Verification Steps

After 2026-05-28 10:00 CDT:

```text
open the existing Chrome/X session if available
go to https://x.com/Latticra
verify whether the Boundary Literacy post is visible on the profile timeline
capture the live status URL if visible
decode the status URL with scripts/latticra-x-status-metrics.py
record visible age, replies, reposts, likes, views, and follower count
open notifications/mentions read-only
record direct comments or mentions needing response
draft replies only when they satisfy the mention response readiness packet
take no public action without exact action-time approval
```

## Ledger Update Rules

If the post is live:

```text
move the scheduled Boundary Literacy row into the ledger as a published post
add the live status URL
record the publication time as shown or inferred from the status ID when available
use scripts/latticra-x-status-metrics.py for status-ID timestamp decoding
keep 24h metrics as TBD until the proper review window
preserve the remaining scheduled queue
```

Status timing helper:

```text
python3 scripts/latticra-x-status-metrics.py https://x.com/Latticra/status/<status_id>
```

If the post is not live:

```text
do not retry-post manually
record scheduler verification failure
inspect scheduled posts only if available without public side effects
ask for owner approval before any corrective public action
```

## Response Boundary

Reply only if a comment is:

```text
a sincere technical question
a request for current evidence or limits
a good-faith critique
a materially misleading claim that needs careful correction
```

Otherwise:

```text
log the mention
recommend no public reply
preserve cadence
```

## Follow-Up Automation

Thread follow-up:

```text
automation_id=verify-latticra-10am-post
purpose=return after the 10:00 CDT scheduled post to verify publication and update tracking evidence
public_action_authorization=none
```

Chaining:

```text
chain_plan=docs/strategy/2026-05-28-0610-cdt-x-scheduled-queue-verification-chain.md
after_success_next_target=2026-05-28 15:05 CDT
after_success_next_topic=Evidence Before Claims
automation_policy=update the same heartbeat; do not create workaround cron automations
```

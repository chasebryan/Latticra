# Latticra X 20:00 CDT Verification Runbook

Status: converted to approval-only manual-post checkpoint
Created: 2026-05-28 07:22 CDT
Account: @Latticra
Scope: verification and approval-prep steps for the canceled 2026-05-28 20:00 CDT Denial Is Legible scheduled draft.

## Purpose

This runbook keeps the old third scheduled-post checkpoint precise after the draft was canceled.

The goal around 20:00 CDT is to confirm no image-only duplicate reappeared, check comments and public @Latticra mentions read-only, and prepare the Denial Is Legible candidate for exact owner approval if the owner wants it. It does not authorize any public reply, like, repost, follow, profile edit, schedule action, or new post.

## Scheduled Post To Verify

Expected scheduled post:

```text
scheduled_for_cdt=2026-05-28 20:00
topic=Denial Is Legible
media=assets/social/latticra-denial-is-legible-glass-base-card.png
expected_status=canceled from X scheduled drafts; manual approval required before any publication
```

Expected post text:

```text
A denied action should still produce useful information:

reason
status
boundary
next safe step

Denial is more trustworthy when people can inspect it.
```

Expected alt text:

```text
Latticra educational card on a luminous white and pale blue glass background. The card says "Denial Is Legible" and explains that a denied action should leave a reason people can inspect. The official blue Latticra emblem appears on the right.
```

## Read-Only Verification Steps

At or after 2026-05-28 20:00 CDT:

```text
open the existing Chrome/X session if available
go to https://x.com/Latticra
verify the corrected Evidence, Boundary, and Public Research posts remain visible
verify the known image-only duplicate URLs still do not exist if there is any doubt
verify the Denial Is Legible post is not public unless the owner separately approved a manual post
capture the live status URL only if a manual post was separately approved and published
decode any new status URL with scripts/latticra-x-status-metrics.py
record visible age, replies, reposts, likes, views, and follower count
open public @Latticra search and comments read-only
record direct comments or mentions needing response
draft replies only when they satisfy the mention response readiness packet
take no public action without exact action-time approval
```

## Ledger Update Rules

If a separately approved manual post is live:

```text
move the scheduled Denial Is Legible row into the ledger as a published post
add the live status URL
record the publication time as shown or inferred from the status ID when available
use scripts/latticra-x-status-metrics.py for status-ID timestamp decoding
keep 24h metrics as TBD until the proper review window
preserve the 2026-05-29 01:00 CDT draft as approval-only unless the owner separately approves it
```

Status timing helper:

```text
python3 scripts/latticra-x-status-metrics.py https://x.com/Latticra/status/<status_id>
```

If the post is not live:

```text
do not retry-post manually
record that the canceled scheduled draft stayed absent
inspect scheduled posts only if available without public side effects
ask for owner approval before any corrective public action
preserve the approval-only manual posting boundary
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
purpose=return around the old 20:00 CDT slot to verify the canceled draft stayed absent and prepare approval-only next steps
public_action_authorization=none
```

Chaining:

```text
chain_plan=docs/strategy/2026-05-28-0610-cdt-x-scheduled-queue-verification-chain.md
after_success_next_target=2026-05-28 21:45 CDT if read-only monitoring remains useful
after_success_next_topic=post-incident approval prep
automation_policy=update the same heartbeat only; do not create workaround cron automations
```

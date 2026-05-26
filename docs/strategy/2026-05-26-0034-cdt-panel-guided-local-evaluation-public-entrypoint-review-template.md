# Latticra Panel-Guided Local Evaluation Public-Entrypoint Review Template

Status: draft public-entrypoint review template
Created: 2026-05-26 00:34 CDT
Decision: review template only
Promotion decision: no product-readiness promotion recommended
Scope: public-entrypoint review for future Panel-guided local evaluation evidence.

## Purpose

This template defines when future Panel-guided local evaluation evidence may justify updates to public reader-facing entry points.

It does not perform the review, update public entry points, or change project posture.

## Source review

This template follows:

```text
docs/strategy/2026-05-26-0019-cdt-panel-guided-local-evaluation-non-claim-review-template.md
```

The target workflow remains:

```text
Evaluate Latticra locally through Latticra Panel without granting runtime authority.
```

## Review header

```text
review name:
created:
reviewer:
review status: not_started|blocked|partial|complete|rejected
workflow evidence bundle:
non-claim review:
estimate-impact review:
repository commit:
```

## Required review outcome

Use one outcome:

```text
no_public_entrypoint_change
public_entrypoint_change_allowed_with_edits
public_entrypoint_change_blocked
insufficient_evidence
```

This template result:

```text
review_performed=0
public_entrypoint_change_recommended=0
README_update_required=0
STATUS_update_required=0
CURRENT_STATUS_update_required=0
project_notes_update_required=0
announcement_review_required=0
reason=this file defines the future review shape only
```

## Review prerequisites

Public-entrypoint review is blocked unless:

```text
workflow_evidence_bundle_present=1
acceptance_checklist_result_present=1
non_claim_review_present=1
claim_expansion_detected=0
guard_or_test_reference_present=1
estimate_impact_review_present=1
```

If any prerequisite is missing, use:

```text
review_outcome=insufficient_evidence
public_entrypoint_change_recommended=0
```

## Entry points under review

Review only these public surfaces for this workflow:

```text
README.md
STATUS.md
docs/status/CURRENT_STATUS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/strategy/README.md
```

Do not update broader foundation docs, announcement logs, package docs, installer docs, or platform docs from this review unless a separate review explicitly names them.

## Allowed public-entrypoint changes

Allowed only after prerequisites pass:

```text
add pointer to completed evidence bundle
add pointer to non-claim review
add pointer to estimate-impact review
clarify that Panel-guided local evaluation evidence exists
clarify limitations for technical evaluators
clarify no product-readiness promotion if estimate remains unchanged
```

Allowed wording:

```text
Panel-guided local evaluation evidence bundle
technical evaluator workflow evidence
dry-run-first local evaluation evidence
operator-visible local evaluation record
no product-readiness promotion from this evidence alone
```

## Blocked public-entrypoint changes

Blocked unless a separate capability promotion has been accepted:

```text
increase public product-readiness estimate
claim production readiness
claim installer readiness
claim platform package readiness
claim daily-driver readiness
claim security protection
claim malware prevention
claim ransomware prevention
claim sandboxing
claim operating-system replacement
claim runtime authority
claim effect execution
claim capability enforcement
claim cryptographic trust
claim signing authority
```

If any blocked change is requested, the review outcome must be:

```text
public_entrypoint_change_blocked
```

## README review questions

```text
Does README need a new link? yes|no
Does README wording stay bounded to local evaluation evidence? yes|no
Does README avoid product-readiness promotion? yes|no
Does README avoid security or installer claims? yes|no
Does README preserve current estimate wording unless estimate review changes it? yes|no
```

README update is allowed only if every preservation answer is `yes`.

## STATUS.md review questions

```text
Does STATUS.md need a new latest-note line? yes|no
Does STATUS.md need estimate table changes? yes|no
Does STATUS.md preserve planning-estimate caveats? yes|no
Does STATUS.md avoid capability posture promotion? yes|no
Does STATUS.md point to the evidence bundle only as evidence? yes|no
```

Estimate table changes require a separate estimate-impact review with `estimate_change_recommended=1`.

## CURRENT_STATUS review questions

```text
Does CURRENT_STATUS need a detailed evidence note? yes|no
Does CURRENT_STATUS preserve no runtime authority? yes|no
Does CURRENT_STATUS preserve no effect execution? yes|no
Does CURRENT_STATUS preserve no security-hardening promotion? yes|no
Does CURRENT_STATUS preserve no product-readiness promotion unless separately reviewed? yes|no
```

## Project-notes review questions

```text
Does CURRENT_DIRECTION need narrative alignment? yes|no
Does UPCOMING_WORK need queue alignment? yes|no
Does the current next-step rule remain unchanged? yes|no
Does the workflow evidence change near-term strategy? yes|no
```

If the current next-step rule changes, a strategy posture review is required.

## Strategy index review questions

```text
Does docs/strategy/README.md need only a link update? yes|no
Does the new entry remain dated and reviewable? yes|no
Does the index avoid implying capability promotion? yes|no
```

Strategy index link updates are allowed when a dated review record exists, even if no capability posture changes.

## Announcement review trigger

Announcement review is required only if:

```text
public capability posture changed=1
product_readiness_estimate_changed=1
security_hardening_posture_changed=1
runtime_authority_changed=1
user-facing workflow accepted for public posture=1
```

This template result:

```text
announcement_review_required=0
reason=no evidence or posture change in this template
```

## Required edit log

If public-entrypoint edits are allowed, record:

```text
entrypoint:
edit type:
source evidence:
non-claim review:
estimate-impact review:
old wording:
new wording:
reviewer note:
```

## Review gate output

```text
public_entrypoint_review_present=0|1
public_entrypoint_change_recommended=0|1
README_update_required=0|1
STATUS_update_required=0|1
CURRENT_STATUS_update_required=0|1
project_notes_update_required=0|1
strategy_index_update_required=0|1
announcement_review_required=0|1
blocked_claim_detected=0|1
review_outcome:
```

This template output:

```text
public_entrypoint_review_present=0
public_entrypoint_change_recommended=0
README_update_required=0
STATUS_update_required=0
CURRENT_STATUS_update_required=0
project_notes_update_required=0
strategy_index_update_required=0
announcement_review_required=0
blocked_claim_detected=0
review_outcome=not_performed
```

## Non-claims

This template does not perform a public-entrypoint review, update README, update status files, update project notes, create an announcement, validate workflow evidence, provide product readiness, provide Panel readiness, provide installer readiness, grant runtime authority, execute effects, enforce capabilities, provide cryptographic authority, provide signing authority, perform host behavior, perform network behavior, execute models, execute tools, execute shell behavior, harden security, prevent malware, prevent ransomware, provide sandboxing, provide operating-system behavior, or provide production support.

It records a public-entrypoint review form only.

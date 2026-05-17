# Latticra Defensive Threat Model Contract

Status: Defensive threat model contract
Scope: protected assets, trust boundaries, assumptions, capability categories, abuse cases, evidence expectations, validation path, future files, compatibility expectations, and non-claims before additional security-facing implementation work.

## Purpose

This document defines the first defensive threat model contract for Latticra.

The purpose is to establish a disciplined vocabulary for what Latticra is trying to protect, what boundaries exist today, what assumptions are allowed, what adversary capability categories may be modeled, what abuse cases should be considered, and what evidence is required before security-facing claims can be promoted.

This document does not implement security controls.

## Relationship to previous work

This contract depends on:

```text
docs/REAL_SYSTEM_CONTRACT.md
docs/NON_CLAIMS.md
docs/EVIDENCE_LADDER.md
docs/EFFECT_GATES.md
docs/RUNTIME_BOUNDARY_CONTRACT.md
docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md
docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
docs/L_UI_RENDERING_IMPLEMENTATION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
```

Those files remain the source of truth for current architecture boundaries, evidence rules, non-claims, authority behavior, task classification, runtime boundary posture, rendering, LIR metadata, and Lat metadata.

## Threat model posture

The first threat model posture is evidence-bound and defensive.

Initial posture:

```text
security controls implemented? limited/no-effect only
runtime protection implemented? no
production protection claim allowed? no
malware prevention claim allowed? no
ransomware prevention claim allowed? no
sandbox claim allowed? no
operator-visible report claim allowed? yes, where implemented and tested
denied-by-default boundary claim allowed? yes, where implemented and tested
```

The threat model records intended defensive reasoning. It does not certify effectiveness.

## Protected assets

Initial protected assets include:

```text
source text integrity
parse results
diagnostic metadata
source spans
AST metadata
semantic validation results
LIR metadata
Lat parse metadata
L-UI render metadata
Nucleus preview records
Nucleus task records
runtime boundary records
authority audit records
operator-visible reports
effect-gate decisions
project claims and status records
```

Future protected assets may include:

```text
runtime execution context
configuration policy
operator approval records
file-system mediation records
network mediation records
recovery records
hardware interaction records
boot records
update records
```

Future assets require separate contracts before implementation claims.

## Trust boundaries

Current trust boundaries:

```text
source input boundary
parser boundary
semantic validation boundary
LIR lowering boundary
Lat grammar boundary
L-UI rendering boundary
Nucleus preview boundary
Nucleus task classification boundary
runtime boundary
authority validation boundary
operator report boundary
repository documentation boundary
```

Current boundaries are primarily metadata, validation, classification, and reporting boundaries.

They are not production isolation boundaries.

## Assumptions

Current allowed assumptions:

```text
source buffers may be malformed
input may be adversarial
reported metadata must be deterministic
unknown requests must be denied or classified as unsupported
unknown effects must be denied or classified as unsupported
effect-performing behavior must require explicit future gates
operator confirmation must not override policy by itself
security claims must follow evidence
no-effect slices must remain no-effect
```

Disallowed assumptions:

```text
trusted input
trusted caller behavior
implicit execution safety
implicit runtime isolation
implicit sandboxing
implicit malware prevention
implicit ransomware prevention
implicit production readiness
implicit certification
```

## Capability categories

Adversary or misuse capability categories may include:

```text
malformed input construction
ambiguous source construction
oversized input pressure
unexpected escape sequence use
metadata confusion attempts
request-kind confusion attempts
effect-kind confusion attempts
boundary bypass attempts
operator-report confusion attempts
policy downgrade attempts
status-record exaggeration attempts
```

Future runtime capability categories may include:

```text
unauthorized command request
unauthorized mutation request
unauthorized file request
unauthorized network request
unauthorized recovery request
unauthorized hardware request
unauthorized boot request
unauthorized update request
```

These categories are for defensive modeling only.

## Abuse cases

Initial abuse cases:

```text
malformed source causes unclear diagnostics
escaped data hides operator-visible content
literal source-buffer NUL causes parser confusion
duplicate names cause ambiguous binding
invalid binding prefix bypasses semantic validation
invalid LIR input reaches rendering
failed authority metadata is treated as allowed
unknown request is treated as allowed
unknown effect is treated as allowed
future-gated request is treated as executable
operator confirmation overrides policy
report omits denial reason
status documentation overclaims implementation state
```

Every abuse case should map to one of:

```text
existing test
future test
explicit non-goal
explicit non-claim
implementation gap
```

## Defensive controls currently represented

Current represented controls include:

```text
parser structural checks
parser diagnostics
source-span metadata
string escape diagnostics
literal source-buffer NUL rejection
escaped decoded NUL visibility
AST metadata reports
semantic validation checks
LIR shape checks
L-UI rendering prerequisites
constrained C++ authority validation/reporting
Nucleus preview denial behavior
Nucleus task classification/reporting
runtime boundary disabled-by-default posture
static documentation guards
project status/non-claim records
```

These are engineering controls and guardrails. They are not certifications.

## Evidence expectations

Security-facing promotion requires evidence.

Required evidence classes:

```text
contract document
implementation plan
implementation document
unit or invariant tests
static guard when applicable
deterministic report output when applicable
negative tests for denied behavior
status update
non-claim update
compatibility check
```

No defensive claim should be promoted from concept to implementation status without these evidence classes.

## Validation expectations

Future defensive validation should include:

```text
positive tests for allowed no-effect behavior
negative tests for denied effect behavior
unknown request tests
unknown effect tests
malformed input tests
small-buffer tests
deterministic report tests
no-mutation tests
no-network tests
no-hardware tests
no-recovery tests
operator confirmation non-override tests
status/non-claim guard tests
```

## Non-goals

Current non-goals:

```text
attack tooling
exploit development
payload generation
malware simulation
credential access
stealth behavior
bypass instructions
persistence mechanisms
exfiltration behavior
```

Latticra threat modeling is defensive architecture work, not offensive tooling.

## Future file policy

Recommended future files:

```text
docs/DEFENSIVE_THREAT_MODEL_IMPLEMENTATION_PLAN.md
docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
scripts/test-defensive-threat-model-contract.sh
scripts/test-defensive-threat-model-validation.sh
tests/defensive_threat_model_invariants.c
```

Implementation or validation files should only be added after the contract is merged.

## Future test list

Future validation should consider tests named:

```text
defensive_threat_model_names_assets
defensive_threat_model_names_boundaries
defensive_threat_model_names_assumptions
defensive_threat_model_names_non_goals
defensive_threat_model_preserves_non_claims
defensive_threat_model_requires_evidence_classes
defensive_threat_model_maps_abuse_cases_to_tests_or_gaps
defensive_threat_model_forbids_operator_confirmation_override
defensive_threat_model_forbids_runtime_protection_claims
defensive_threat_model_forbids_malware_prevention_claims
defensive_threat_model_forbids_ransomware_prevention_claims
```

## Compatibility expectations

Future work must not weaken:

```text
existing non-claims
runtime boundary disabled-by-default posture
Nucleus task no-effect posture
constrained authority no-effect posture
L-UI rendering no-effect posture
LIR metadata-only posture
Lat parser metadata-only posture
source-buffer literal NUL rejection
escaped decoded NUL visibility
semantic validation prerequisites
operator confirmation non-override policy
```

## Forbidden behavior

Threat model work must not:

- provide attack instructions;
- provide exploit steps;
- provide payload construction;
- provide stealth guidance;
- provide credential access guidance;
- provide persistence guidance;
- claim production protection;
- claim malware prevention;
- claim ransomware prevention;
- claim sandboxing;
- claim certification;
- claim operating-system completeness.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-defensive-threat-model-contract.sh
```

The guard is static. It does not implement security controls.

## Non-claims

This document does not implement security controls, runtime protection, malware prevention, ransomware prevention, sandboxing, exploit prevention, incident response, recovery behavior, certification, accreditation, production hardening, or operating-system completeness.

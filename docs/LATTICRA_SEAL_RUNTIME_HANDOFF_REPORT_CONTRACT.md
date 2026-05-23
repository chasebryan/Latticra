# Latticra Seal Runtime Handoff Report Contract

Status: Latticra Seal runtime handoff report contract
Scope: contract for a future report surface after runtime handoff evaluation metadata. This document does not implement runtime handoff execution, runtime authority, host reads, host writes, network behavior, shell execution, tool execution, capability enforcement, policy persistence, signing, key generation, private-key storage, trust-store loading, revocation lookup, object sealing, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first Latticra Seal runtime handoff report boundary that may consume an eligible metadata-only runtime handoff evaluation.

The purpose of this layer is to decide whether a previously eligible metadata-only runtime handoff evaluation may be surfaced as a deterministic report record before any future runtime bridge exists.

The report surface is report classification, not runtime handoff.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_IMPLEMENTATION.md
include/latticra/seal_runtime_handoff_evaluation.h
src/seal_runtime_handoff_evaluation.c
tests/seal_runtime_handoff_evaluation_invariants.c
scripts/test-latticra-seal-runtime-handoff-evaluation.sh
```

The runtime handoff evaluation metadata surface remains the source of eligibility evidence for this report surface.

## Report boundary

Allowed in the next implementation slice:

```text
accept runtime handoff evaluation metadata
require handoff_eligible=1
require handoff_state=eligible-report-only or handoff_state=eligible-evaluate-only
require handoff_performed=0
require runtime_authority_granted=0
require effect_performed=0
require host_read_performed=0
require host_write_performed=0
require network_performed=0
accept requested report metadata
classify report-only as report_state=ready-report-only
classify evaluate-only as report_state=ready-evaluate-only
produce deterministic runtime handoff report metadata
```

Forbidden in the next implementation slice:

```text
runtime handoff execution
runtime authority grants
host reads
host writes
network access
shell execution
tool execution
capability enforcement
policy persistence
trust-store loading
revocation lookup
key generation
private-key handling
object sealing
kernel interaction
```

## Initial report policy

Allowed input handoff states:

```text
handoff_state=eligible-report-only
handoff_state=eligible-evaluate-only
```

Allowed requested report labels:

```text
report-only
evaluate-only
```

Planned report states:

```text
report_state=ready-report-only
report_state=ready-evaluate-only
report_state=denied-evaluation
report_state=denied-handoff
report_state=denied-report
report_state=denied-runtime-authority
report_state=denied-host-effect
report_state=denied-network-effect
```

The first implementation may set:

```text
report_ready=1
```

only for metadata-only report/evaluate handoff reports.

Even when report_ready=1, these must remain zero:

```text
handoff_performed=0
effect_performed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Planned fields

A future runtime handoff report record should be bounded and deterministic.

Planned fields:

```text
report_profile
handoff_profile
decision_profile
gate_profile
receipt_profile
verify_profile
message_digest_algorithm
message_digest_hex
public_key_identity_label
requested_capability
requested_effect
requested_handoff
requested_report
requested_scope
handoff_state
handoff_eligible
report_state
report_ready
handoff_performed
effect_performed
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
status
```

## Failure behavior

Future runtime handoff report handling must fail closed.

Required failure states:

```text
null output -> invalid
null runtime handoff evaluation -> invalid
invalid runtime handoff evaluation -> denied-evaluation
handoff_eligible=0 -> denied-handoff
handoff_state not eligible-report-only or eligible-evaluate-only -> denied-handoff
missing requested report -> denied-report
unknown requested report -> denied-report
requested report mismatch -> denied-report
runtime authority already granted -> denied-runtime-authority
handoff already performed -> denied-host-effect
effect already performed -> denied-host-effect
host read already performed -> denied-host-effect
host write already performed -> denied-host-effect
network already performed -> denied-network-effect
```

Failures must not read host files, write host files, contact networks, execute tools, execute shells, enforce capabilities, perform handoff, persist policy, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
runtime handoff report metadata implementation
```

It does not permit runtime handoff execution, effect execution, capability enforcement, runtime authority, host behavior, network behavior, trust-store behavior, revocation lookup, key handling, object sealing, or kernel behavior.

After runtime handoff report metadata exists and is guarded, the next valid planning slice is a sealed report envelope contract that still performs no runtime handoff.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-runtime-handoff-report-contract.sh
```

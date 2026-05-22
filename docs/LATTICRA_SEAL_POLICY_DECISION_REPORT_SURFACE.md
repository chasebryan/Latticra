# Latticra Seal Policy Decision Report Surface

Status: report-only policy decision report surface
Scope: deterministic local report surface for the existing Latticra Seal policy decision metadata layer. This document does not implement policy evaluation, policy enforcement, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, signature verification, public-key parsing, trust-store loading, key generation, private-key storage, hardware key use, revocation lookup, network trust lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document records the first operator-visible report surface for Latticra Seal policy decision metadata.

The surface renders the existing default-deny, report-only policy decision posture using a deterministic local fixture.

## Added files

```text
tests/seal_policy_decision_report_surface.c
scripts/latticra-seal-policy-decision-report.sh
```

## Report runner

```sh
sh scripts/latticra-seal-policy-decision-report.sh
```

## Expected report posture

The report surface renders the current policy-decision posture, including:

```text
LATTICRA SEAL POLICY DECISION
policy_decision_profile=latticra-seal-policy-decision/0.1
policy_decision_supported=0
policy_evaluation_supported=0
policy_enforcement_supported=0
default_decision=deny
decision_state=report-only
decision_allowed=0
decision_denied=1
operator_review_required=1
unknown_tool_denied=1
unsigned_request_denied=1
invalid_schema_denied=1
stale_request_denied=1
replayed_request_denied=1
invalid_signature_denied=1
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
mode=report-only
decision=report-only
reason=policy-decision-metadata-only
status=policy-decision-metadata
```

## Boundary

This report surface compiles and runs a local deterministic fixture only.

It does not evaluate policy, enforce policy, execute tools, execute shell commands, call runtime components, contact networks, read host files, write host files, verify signatures, validate freshness, detect replay, enforce capabilities, or grant authority.

It renders metadata only.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-policy-decision-report-surface.sh
```

Expected output:

```text
latticra seal policy decision report surface: ok
```

The underlying policy decision implementation remains covered by:

```sh
sh scripts/test-latticra-seal-policy-decision-contract.sh
sh scripts/test-latticra-seal-policy-decision.sh
sh scripts/test-latticra-seal-policy-decision-status.sh
```

## Claim boundary

This report surface does not justify the public claim that Latticra secures AI agents.

It makes the default-deny policy decision posture easier to inspect before any future runtime work is considered.

## Next valid slice

The next valid Latticra Seal slice is policy-decision report status alignment or a no-effect dry-run planning contract for future runtime behavior.

That future slice must preserve the report-only posture until a specific contract, deterministic local fixture, no-effect dry-run report, guarded allowlist posture, and validation path justify any later runtime work.
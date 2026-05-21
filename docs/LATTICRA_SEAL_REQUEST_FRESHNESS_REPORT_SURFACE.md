# Latticra Seal Request Freshness Report Surface

Status: report surface for Latticra Seal request freshness metadata
Scope: no-effect report-surface fixture and shell runner for deterministic Seal request freshness metadata. This slice does not implement timestamp parsing, trusted clock behavior, nonce storage, replay-cache storage, context hashing, parameter hashing, freshness validation, replay detection, signature verification, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document records the first dedicated report surface for Latticra Seal request freshness metadata.

The report surface exists so operators and contributors can render the current report-only request freshness posture without adding timestamp validation, replay detection, runtime behavior, or authority.

## Added files

```text
tests/seal_request_freshness_report_surface.c
scripts/latticra-seal-request-freshness-report.sh
scripts/test-latticra-seal-request-freshness-report-surface.sh
```

## Behavior

The report surface:

```text
builds a report-only Seal parameter schema fixture
constructs Seal request freshness metadata from that fixture
renders the deterministic Seal request freshness report
prints the report to stdout
```

The guard verifies report output fields including:

```text
freshness_profile=latticra-seal-request-freshness/0.1
request_id=unset
caller_id=unset
tool_id=unset
request_timestamp=unset
request_expiration=unset
nonce=unset
context_hash=unset
parameter_hash=unset
request_freshness_supported=0
request_freshness_validation_supported=0
replay_protection_supported=0
request_id_present=0
caller_id_present=0
tool_id_present=0
request_timestamp_present=0
request_expiration_present=0
nonce_present=0
context_hash_present=0
parameter_hash_present=0
freshness_valid=0
replay_detected=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
mode=report-only
decision=report-only
reason=request-freshness-metadata-only
status=request-freshness-metadata
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-request-freshness-report-surface.sh
```

The underlying metadata implementation remains covered by:

```sh
sh scripts/test-latticra-seal-request-freshness.sh
```

## Boundary

This report surface does not parse timestamps, read trusted clocks, store nonces, maintain a replay cache, compute hashes, validate freshness, detect replay, verify signatures, execute tools, execute shell commands on behalf of a model, contact networks, read host files, write host files, parse keys, create receipts, enforce capabilities, call runtime components, or grant runtime authority.

It compiles and runs a local deterministic fixture only.

## Claim boundary

This report surface still does not justify the public claim that Latticra secures AI agents.

It makes the freshness/replay metadata visible, but the stronger claim requires signed request metadata, policy decision metadata, a runtime enforcement gate, and negative tests for denied unknown, unsigned, stale, and replayed requests.

## Next valid slice

The next valid Latticra Seal slice is a request freshness report surface status record or a signed request metadata contract.

That future slice must not implement runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, freshness validation, replay detection, or authority grants unless a specific contract and validation path justify it.

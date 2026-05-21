# Latticra Seal Policy Decision Implementation

Status: initial report-only policy decision metadata implementation
Scope: bounded C metadata surface for policy decision posture after the report-only Seal signed request layer. This slice does not implement policy evaluation, policy enforcement, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, signature verification, public-key parsing, trust-store loading, key generation, private-key storage, hardware key use, revocation lookup, network trust lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document records the first Latticra Seal policy decision metadata implementation.

The implementation accepts an existing report-only Seal signed request metadata record and produces deterministic report-only policy decision metadata.

## Added files

```text
include/latticra/seal_policy_decision.h
src/seal_policy_decision.c
tests/seal_policy_decision_invariants.c
scripts/test-latticra-seal-policy-decision.sh
```

## API summary

The policy decision metadata surface adds:

```text
latticra_seal_policy_decision_t
latticra_seal_policy_decision_error_t
latticra_seal_policy_decision_error_label
latticra_seal_policy_decision_from_signed_request
latticra_seal_policy_decision_is_report_only
latticra_seal_policy_decision_report
```

## Metadata behavior

The implementation:

```text
accepts a valid report-only Seal signed request metadata record
sets policy_decision_profile=latticra-seal-policy-decision/0.1
sets policy_id=unset
sets policy_version=unset
sets requested_action=unset
sets requested_tool=unset
sets policy_decision_supported=0
sets policy_evaluation_supported=0
sets policy_enforcement_supported=0
sets policy_id_present=0
sets policy_version_present=0
sets requested_action_present=0
sets requested_tool_present=0
sets signed_request_present=0
sets signature_valid=0
sets schema_valid=0
sets freshness_valid=0
sets replay_detected=0
sets default_decision=deny
sets decision_state=report-only
sets decision_allowed=0
sets decision_denied=1
sets operator_review_required=1
sets unknown_tool_denied=1
sets unsigned_request_denied=1
sets invalid_schema_denied=1
sets stale_request_denied=1
sets replayed_request_denied=1
sets invalid_signature_denied=1
copies runtime_authority_granted from signed request metadata
copies host_read_performed from signed request metadata
copies host_write_performed from signed request metadata
copies network_performed from signed request metadata
sets mode=report-only
sets decision=report-only
sets reason=policy-decision-metadata-only
renders deterministic policy decision metadata
```

## Boundary

This implementation does not evaluate policies, enforce policies, execute tools, execute shell commands, call runtime components, contact networks, read host files, write host files, verify signatures, validate freshness, detect replay, enforce capabilities, or grant authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null signed request metadata input -> invalid-input
invalid signed request metadata -> invalid-signed-request
non-report-only signed request metadata -> invalid-signed-request
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not evaluate policy, contact networks, read host files, write host files, execute tools, enforce capabilities, or grant authority.

## Invariants

The invariant test verifies:

```text
valid report-only signed request metadata produces deterministic policy decision metadata
policy_decision_profile is stable
policy_id remains unset
policy_version remains unset
requested_action remains unset
requested_tool remains unset
policy_decision_supported remains zero
policy_evaluation_supported remains zero
policy_enforcement_supported remains zero
signed_request_present remains zero
signature_valid remains zero
schema_valid remains zero
freshness_valid remains zero
replay_detected remains zero
default_decision remains deny
decision_state remains report-only
decision_allowed remains zero
decision_denied remains one
operator_review_required remains one
unknown_tool_denied remains one
unsigned_request_denied remains one
invalid_schema_denied remains one
stale_request_denied remains one
replayed_request_denied remains one
invalid_signature_denied remains one
runtime_authority_granted remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
mode remains report-only
decision remains report-only
reason remains policy-decision-metadata-only
small report buffer fails closed
null inputs fail closed
invalid signed request metadata fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-policy-decision-contract.sh
sh scripts/test-latticra-seal-policy-decision.sh
```

## Claim boundary

This implementation still does not justify the public claim that Latticra secures AI agents.

It moves the project closer by adding report-only default-deny policy decision metadata, but the stronger claim requires a runtime enforcement gate and negative tests for denied unknown, unsigned, stale, and replayed requests.

## Next valid slice

The next valid Latticra Seal slice is a policy decision report surface or runtime enforcement gate contract.

That future slice must not implement runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, policy enforcement, or authority grants unless a specific contract and validation path justify it.

# Latticra Seal Guarded Allowlist Report Surface

Status: report surface for the Latticra Seal guarded allowlist metadata layer
Scope: deterministic local report surface after the no-effect guarded allowlist metadata implementation. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This document records the first operator-visible report surface for Latticra Seal guarded allowlist metadata.

The report surface renders whether a deterministic local fixture tool name is known only as a candidate while still denying execution, host access, network use, and runtime authority.

## Added files

```text
tests/seal_guarded_allowlist_report_surface.c
scripts/latticra-seal-guarded-allowlist-report.sh
```

## Report runner

```sh
sh scripts/latticra-seal-guarded-allowlist-report.sh
```

## Expected report posture

The report surface renders the current guarded allowlist posture for a known local fixture tool candidate, including:

```text
LATTICRA SEAL GUARDED ALLOWLIST
guarded_allowlist_profile=latticra-seal-guarded-allowlist/0.1
tool_name=latticra.seal.report
allowlist_source=deterministic-local-fixture
allowlist_entry_count=3
allowlist_lookup_performed=1
requested_tool_name_present=1
requested_tool_known=1
requested_tool_unknown=0
requested_tool_candidate=1
requested_tool_allow_candidate=1
allow_candidate_requires_policy_decision=1
allow_candidate_requires_runtime_gate=1
allow_candidate_requires_runtime_dry_run=1
allow_candidate_requires_operator_review=1
allow_candidate_grants_authority=0
allow_candidate_executes_tool=0
allow_candidate_reads_host=0
allow_candidate_writes_host=0
allow_candidate_uses_network=0
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
blocked_reason=known-tool-candidate-still-denied
report_only=1
mode=report-only
status=guarded-allowlist-metadata
```

## Boundary

This report surface compiles and runs a local deterministic fixture only.

It does not execute tools, execute shell commands beyond compiling and running the local test fixture, read host files beyond the repository sources needed for local compilation, write host files beyond the temporary test binary/report path, use the network, evaluate external policies, load policy files, load production allowlist files, verify signatures, validate freshness against live time, mutate replay caches, grant authority, turn allowlist matches into execution grants, claim production readiness, claim AI-agent security, or claim MCP implementation.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-guarded-allowlist-report-surface.sh
```

Expected output:

```text
latticra seal guarded allowlist report surface: ok
```

The underlying guarded allowlist implementation remains covered by:

```sh
sh scripts/test-latticra-seal-guarded-allowlist.sh
```

## Claim boundary

This report surface does not justify the public claim that Latticra secures AI agents.

It makes the allowlist candidate denial posture easier to inspect before any future runtime authority path is considered.

## Next valid slice

The next valid Latticra Seal slice is guarded allowlist report status alignment.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.
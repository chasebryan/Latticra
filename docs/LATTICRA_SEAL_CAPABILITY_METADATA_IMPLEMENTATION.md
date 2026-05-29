# Latticra Seal Capability Metadata Implementation

Status: no-effect implementation record for the Latticra Seal capability metadata surface
Source: follows `docs/LATTICRA_SEAL_CAPABILITY_METADATA_IMPLEMENTATION_PLAN.md`
Scope: deterministic local capability metadata only. This implementation does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This implementation adds a small, deterministic, local capability metadata surface.

The capability metadata surface can classify a known local fixture capability name as a candidate for later review, but it still denies execution, host access, network use, effects, and runtime authority.

## Added files

```text
include/latticra/seal_capability_metadata.h
src/seal_capability_metadata.c
tests/seal_capability_metadata_invariants.c
scripts/test-latticra-seal-capability-metadata.sh
docs/LATTICRA_SEAL_CAPABILITY_METADATA_IMPLEMENTATION.md
```

## Deterministic local fixture

The implementation uses only this local fixture set:

```text
seal.capability.inspect
seal.capability.report
seal.capability.dry_run
```

The fixture is compiled into the local C implementation.

It is not loaded from host files, policy files, network sources, MCP servers, tools, trust stores, or external services.

## Missing capability posture

Missing capability names remain denied:

```text
capability_metadata_profile=latticra-seal-capability-metadata/0.1
capability_fixture_source=deterministic-local-fixture
capability_fixture_entry_count=3
capability_lookup_performed=1
capability_name_present=0
capability_known=0
capability_unknown=1
capability_candidate=0
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
unknown_capability_denied=1
missing_capability_denied=1
blocked_reason=missing-capability-denied
report_only=1
mode=report-only
status=capability-metadata
```

## Unknown capability posture

Unknown capability names remain denied:

```text
capability_name_present=1
capability_known=0
capability_unknown=1
capability_candidate=0
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
would_allow=0
would_deny=1
would_require_operator_review=1
unknown_capability_denied=1
blocked_reason=default-deny-capability-metadata
report_only=1
mode=report-only
status=capability-metadata
```

## Known capability candidate posture

Known fixture capabilities become candidates only:

```text
capability_name_present=1
capability_known=1
capability_unknown=0
capability_candidate=1
capability_grants_authority=0
capability_executes_tool=0
capability_reads_host=0
capability_writes_host=0
capability_uses_network=0
would_allow=0
would_deny=1
would_require_operator_review=1
blocked_reason=known-capability-candidate-still-denied
report_only=1
mode=report-only
status=capability-metadata
```

A known fixture capability improves reporting but does not authorize execution or effects.

## API surface

The implementation exposes:

```text
latticra_seal_capability_metadata_error_label
latticra_seal_capability_metadata_fixture
latticra_seal_capability_metadata_result_missing
latticra_seal_capability_metadata_result_unknown
latticra_seal_capability_metadata_result_candidate
latticra_seal_capability_metadata_evaluate
latticra_seal_capability_metadata_is_report_only
latticra_seal_capability_metadata_report
```

## Report format

The report begins with:

```text
LATTICRA SEAL CAPABILITY METADATA
```

It renders deterministic `key=value` metadata, including missing/unknown/known/candidate state, authority-denial state, effect-denial state, core blocked-case state, report-only state, error label, and status.

## Validation

Run:

```sh
sh scripts/test-latticra-seal-capability-metadata.sh
```

Expected output:

```text
seal capability metadata invariants: ok
```

The invariant test proves:

```text
missing capability remains denied
missing capability is not a candidate
unknown capability remains denied
unknown capability is not a candidate
known capability becomes candidate only
known capability remains denied
known capability grants no authority
known capability executes no tools
known capability reads no host state
known capability writes no host state
known capability uses no network
capability effect class is descriptive only
capability lookup uses deterministic local fixture
capability fixture entry count is stable
profile is stable
status remains capability-metadata
report_only remains one
mode remains report-only
unterminated input strings fail closed before copy
unterminated result strings fail closed before render
tampered authority or effect flags fail closed before render
small report buffers fail closed
null output fails closed
empty capability name fails closed as missing capability
oversized capability name fails closed
```

## Boundary

This implementation is metadata-only and no-effect.

It does not execute tools, execute shell commands, read host files, write host files, use the network, evaluate external policies, load policy files, load production capability files, load production allowlist files, verify signatures, validate freshness against live time, mutate replay caches, grant authority, turn capability matches into execution grants, turn capability matches into effect grants, claim production readiness, claim AI-agent security, or claim MCP implementation.

## Current next valid slice

The next valid Latticra Seal slice is a capability metadata report surface.

That future slice must render the current deterministic metadata through a local fixture runner and must not perform effects or grant authority.

# Latticra Zero-Trust Runtime Authority Baseline

Status: zero-trust runtime authority baseline
Source refresh date: 2026-05-26
Scope: future runtime, tool, host I/O, network, server/MCP, update, recovery, boot, hardware, agentic automation, and authority-bearing request paths.

This baseline turns the current defensive threat model and runtime-boundary policy expansion into a guarded Latticra runtime-authority contract.

It does not implement runtime execution, network access, host I/O, tool execution, MCP behavior, recovery behavior, boot behavior, hardware behavior, policy enforcement, capability enforcement, or production protection.

## Authoritative Zero-Trust Sources

Date checked: 2026-05-26

| Source | Latticra use |
| --- | --- |
| NSA Zero Trust Implementation Guidelines: Primer, Discovery Phase, Phase One, and Phase Two | phased runtime-authority prerequisites, dependency ordering, and evidence visibility |
| CISA Zero Trust Maturity Model Version 2.0 | pillars and cross-cutting capabilities for maturity vocabulary |
| NIST SP 800-207 Zero Trust Architecture | per-request, least-privilege, resource-focused access decision model |
| NIST SP 800-207A | future cloud-native/service-mesh access-control vocabulary if server or MCP surfaces appear |

Follow-on source review, 2026-05-27:

- NSA MCP security-design guidance is now relevant to future MCP, tool, and agentic-automation authority because Latticra already reserves future server/MCP surfaces.
- NSA and partners' careful-adoption guidance reinforces treating agentic automation as a system-wide authority and context-sharing problem rather than a narrow tool wrapper.

Follow-on source review, 2026-05-28:

- NIST's May 18, 2026 summary analysis of AI-agent security RFI responses reinforces that agent security needs explicit threat, mitigation, and evaluation planning beyond generic cybersecurity carryover.
- NIST's February 2026 concept paper on identity and authority of software agents reinforces that future agentic, MCP, and automation surfaces should carry explicit software-agent identity and authorization vocabulary instead of inferring trust from execution context alone.

Authoritative URLs:

```text
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4393480/nsa-releases-phase-one-and-phase-two-of-the-zero-trust-implementation-guidelines/
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4378980/nsa-releases-first-in-series-of-zero-trust-implementation-guidelines/
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4496698/nsa-releases-security-design-considerations-for-ai-driven-automation-leveraging/
https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4475134/nsa-joins-the-asds-acsc-and-others-to-release-guidance-on-agentic-artificial-in/
https://www.cisa.gov/resources-tools/resources/zero-trust-maturity-model
https://www.nist.gov/publications/zero-trust-architecture-0
https://csrc.nist.gov/pubs/sp/800/207/a/final
```

## Current Fields

```text
zero_trust_runtime_authority_baseline_present=1
zero_trust_runtime_authority_guard_present=1
defensive_threat_model_validation_refinement_present=1
runtime_boundary_policy_expansion_after_threat_model_present=1
zero_trust_runtime_boundary_required=1
per_request_authorization_required=1
least_privilege_effect_scope_required=1
resource_identity_required=1
caller_identity_required=1
asset_inventory_required_before_authority=1
policy_decision_visibility_required=1
denial_reason_visibility_required=1
audit_record_required_before_authority=1
operator_confirmation_metadata_only_required=1
unknown_request_denial_required=1
unknown_effect_denial_required=1
future_gate_denial_required=1
runtime_execution_added=0
tool_execution_added=0
host_behavior_changed=0
network_behavior_changed=0
mcp_behavior_changed=0
runtime_authority_granted=0
production_protection_claim_allowed=0
zero_trust_certification_claim_allowed=0
external_endorsement_claimed=0
```

## Pillar Mapping

| Pillar | Latticra requirement before authority |
| --- | --- |
| Identity | caller, operator, automation profile, and request family must be explicit |
| Devices / execution environment | local runner, host context, workspace boundary, and platform scope must be recorded |
| Networks / environment | network effects remain denied until a network authority contract and telemetry path exist |
| Applications / workloads | tool, MCP, model, runtime, signer, updater, and installer workloads require separate authority contracts |
| Data | target resources, files, manifests, receipts, keys, artifacts, and reports must be identified and bounded |
| Visibility and analytics | decision, denial reason, gate state, matrix cell, and evidence level must be reportable |
| Automation and orchestration | automation cannot bypass policy, and operator confirmation cannot override denied effects |
| Governance | status records, non-claims, and guard scripts must block promotion by wording alone |

## Required Runtime Authority Gate

No future request may execute, mutate, read host files, write host files, open network connections, run tools, invoke MCP, load model artifacts, sign, update, recover, touch boot state, or affect hardware until this gate is complete:

```text
request_kind_known=1
requested_effect_known=1
caller_identity_known=1
operator_or_automation_context_known=1
software_agent_identity_known=1
resource_identity_known=1
resource_sensitivity_classified=1
execution_environment_known=1
tool_or_mcp_boundary_known=1
context_sharing_scope_known=1
mode_matches_request_family=1
authority_prerequisites_satisfied=1
least_privilege_scope_recorded=1
policy_decision_reported=1
denial_reason_reported=1
audit_record_emitted=1
evidence_level_recorded=1
operator_confirmation_recorded_as_metadata_only=1
operator_confirmation_non_override_test_present=1
unknown_request_denial_test_present=1
unknown_effect_denial_test_present=1
future_gate_denial_test_present=1
blocked_effect_denial_test_present=1
rollback_or_failure_behavior_defined_for_mutation=1
non_claim_review_completed=1
```

Until this gate is complete:

```text
runtime_execution_allowed=0
tool_execution_allowed=0
host_read_allowed=0
host_write_allowed=0
network_open_allowed=0
mcp_invocation_allowed=0
model_execution_allowed=0
signing_authority_allowed=0
update_authority_allowed=0
recovery_authority_allowed=0
boot_authority_allowed=0
hardware_authority_allowed=0
operator_confirmation_override_allowed=0
```

## Current Evidence

Current supporting evidence:

```text
docs/RUNTIME_BOUNDARY_POLICY_EXPANSION_AFTER_THREAT_MODEL.md
docs/RUNTIME_BOUNDARY_ABUSE_CASE_FIXTURES_AFTER_POLICY_EXPANSION.md
docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md
scripts/test-runtime-boundary-policy-expansion-after-threat-model.sh
scripts/test-runtime-boundary-abuse-case-fixtures.sh
scripts/test-zero-trust-runtime-authority-baseline.sh
```

## Validation

This baseline is guarded by:

```sh
sh scripts/test-zero-trust-runtime-authority-baseline.sh
```

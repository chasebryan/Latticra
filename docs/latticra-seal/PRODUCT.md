# Latticra Seal Product Spine

Status: product spine for Latticra Seal security-product direction
Scope: product direction, operating model, and earned-capability path for Latticra Seal. This document does not implement runtime enforcement, malware prevention, ransomware prevention, sandboxing, endpoint detection, kernel enforcement, network authority, root authority, cloud trust services, production cryptographic authority, capability enforcement, effect execution, AI-agent execution control, or production security readiness.

## Product Thesis

Latticra Seal should become a local-first trust-boundary product for software, operators, and agentic toolchains.

The product promise to earn is:

```text
Every security-relevant request should have explicit identity, capability, policy, measurement, verification, dry-run decision, and receipt evidence before any effect is allowed.
```

Current Seal does not yet allow effects. That is a strength of the present foundation: the product can mature from visible evidence to verified decisions to future enforcement without hiding authority jumps.

## Current Truth

Seal currently has an evidence-bound base:

```text
manifest_hash_baseline=1
report_only_runtime_gate_path=1
guarded_allowlist_metadata=1
capability_metadata=1
request_freshness_metadata=1
signed_request_metadata=1
policy_decision_metadata=1
verification_policy_metadata=1
verification_receipt_metadata=1
runtime_dry_run_metadata=1
runtime_handoff_metadata=1
operator_receipt_report_metadata=1
operator_receipt_report_surface=1
local_capability_registry_schema_contract=1
local_capability_registry_schema_implementation_plan=1
local_capability_registry_schema_implementation=1
local_capability_registry_schema_surface=1
local_capability_registry_schema_status=1
panel_dashboard_planning_checkpoint=1
panel_dashboard_planning_status=1
operator_visible_reports=1
production_security_product=0
runtime_authority_granted=0
```

## Product Modes

Seal should mature through explicit modes.

```text
observe_mode=current
verify_mode=partial-local
decide_mode=metadata-only
handoff_mode=metadata-only
enforce_mode=future-closed
```

### Observe

Observe mode describes local state, manifests, baselines, request posture, capability candidates, and denial reasons.

Current status: present through report-only surfaces.

### Verify

Verify mode should bind artifacts, identities, signatures, and receipts to deterministic verification outcomes.

Current status: partial local verification primitives exist, but no production trust root, no trust-store behavior, no revocation lookup, and no production cryptography claim exist.

### Decide

Decide mode should combine request, capability, policy, freshness, signature, receipt, allowlist, and operator-review posture into a deterministic allow/deny/review decision.

Current status: metadata-only and denied by default.

### Handoff

Handoff mode should create explicit runtime-boundary evidence for a future effect-capable layer.

Current status: metadata-only and inactive.

### Enforce

Enforce mode is the future production boundary. It must remain closed until implementation, tests, threat-model evidence, operator controls, failure behavior, and security review exist.

Current status: not implemented.

## Product Pillars

### Evidence Graph

Seal should connect manifests, file hashes, request records, capability metadata, policy decisions, verification receipts, dry-run decisions, and handoff reports into one inspectable evidence graph.

### Capability Intent

Seal should make every requested capability explicit before a tool, agent, script, package, installer, or runtime component can move toward effects.

### Verification Receipts

Seal should produce receipts that are deterministic, machine-readable, human-readable, signed when future prerequisites exist, and traceable to input evidence.

### Deny-By-Default Decisions

Seal should treat unknown, unsigned, stale, replayed, malformed, or unsupported requests as denied unless a guarded future authority path proves otherwise.

### Operator Review

Seal should make review easy: what was requested, what evidence exists, what policy decided, what would happen, what remains blocked, and what authority is still absent.

### Local-First Control

Seal should preserve local operation by default. Future cloud or network trust features, if ever introduced, must be optional, signed, inspectable, and disabled unless explicitly authorized.

## Product Surfaces

Near-term product surfaces should be:

```text
seal_cli_report=1
seal_cli_manifest_hash_baseline=1
seal_capability_metadata_report=1
seal_policy_decision_report=1
seal_runtime_dry_run_report=1
seal_operator_receipt_report=1
seal_local_capability_registry_schema=report-surface
seal_panel_status_surface=planning-checkpoint
seal_panel_dashboard=planning-checkpoint
seal_receipt_bundle=partial-local
seal_operator_review_queue=planned
```

## Near-Term Build Queue

Completed recent checkpoints:

1. Capability metadata report status/index alignment.
2. A Seal product-spine status record and guard.
3. A bundled operator receipt report that ties capability metadata, policy decision, request freshness, signed request metadata, runtime dry-run, and denial reason into one local artifact.
4. A local capability registry schema contract before any production registry loader exists.
5. A no-effect local capability registry schema implementation plan before any schema C code exists.
6. A no-effect local capability registry schema implementation with bounded entries, deterministic validation, and zero authority.
7. A deterministic local capability registry schema report surface and status checkpoint.
8. A Panel-visible Seal dashboard planning checkpoint that defines future read-only evidence display without UI implementation or authority.

The product path should now prioritize:

1. A Seal Panel dashboard view-model contract that maps current reports into read-only display rows without root, network, host scanning, or runtime authority.
2. A signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.
3. A future enforcement preflight contract that keeps enforce mode closed until all predecessor evidence is present.

Current completed product-spine checkpoint:

```text
seal_product_spine_status_present=1
product_spine_changes_authority=0
operator_receipt_report_contract_present=1
operator_receipt_report_implementation_plan_present=1
operator_receipt_report_implementation_present=1
operator_receipt_report_surface_present=1
operator_receipt_report_status_present=1
local_capability_registry_schema_contract_present=1
local_capability_registry_schema_implementation_plan_present=1
local_capability_registry_schema_implementation_present=1
local_capability_registry_schema_surface_present=1
local_capability_registry_schema_status_present=1
panel_dashboard_planning_checkpoint_present=1
panel_dashboard_planning_status_present=1
```

## Non-Claims

The product target does not change current authority.

```text
production_security_product=0
malware_prevention=0
ransomware_prevention=0
runtime_enforcement=0
kernel_enforcement=0
root_authority=0
network_authority=0
capability_enforcement=0
effect_execution=0
ai_agent_execution_control=0
runtime_authority_granted=0
```

## Definition Of Earned Progress

Seal becomes more product-real only when a new slice adds reproducible evidence, tests, failure behavior, public status alignment, and a narrower authority boundary.

Security language must follow evidence. The product can aim high, but every claim must stay attached to code, tests, reports, and explicit non-claims.

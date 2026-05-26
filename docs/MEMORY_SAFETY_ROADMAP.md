# Latticra Memory-Safety Roadmap

Status: memory-safety roadmap
Source refresh date: 2026-05-26
Scope: component-level memory-safety allocation for Latticra C, restricted C++, Rust installer, shell guards, parser surfaces, Seal metadata, runtime-boundary metadata, and future high-risk infrastructure surfaces.

This roadmap responds to the NSA/CISA memory-safe-language guidance, CISA The Case for Memory Safe Roadmaps, the CISA/FBI buffer overflow alert, the CISA secure-design alert on OS command injection, and CISA/FBI product-security bad-practice guidance tracked in `docs/HIGH_ASSURANCE_SECURITY_BASELINE.md`.

It does not rewrite current components, certify memory safety, claim production hardening, or create a security boundary.

## Current Fields

```text
memory_safety_roadmap_present=1
memory_safety_roadmap_guard_present=1
high_assurance_security_baseline_present=1
c_cpp_security_profile_present=1
c_abi_boundary_policy_present=1
restricted_c_cpp_profile_required=1
memory_safe_language_preferred_for_new_high_risk_components=1
memory_safe_language_exception_contract_required=1
parser_fuzzing_required_before_security_boundary_claim=1
unsafe_exception_record_required=1
component_memory_safety_inventory_present=1
implementation_behavior_changed=0
runtime_authority_granted=0
security_boundary_claimed=0
memory_safety_guarantee_claimed=0
production_protection_claim_allowed=0
```

## Component Inventory

| Component family | Current language posture | Current mitigation | Promotion blocker |
| --- | --- | --- | --- |
| L-UI source buffer and parser surfaces | C | length-aware source buffers, literal-NUL policy, escaped decoded-NUL visibility, malformed-input tests, source-span tests, explicit attention to truncation, off-by-one, and lifetime faults | fuzzing corpus, hostile input budget, parser security-boundary contract |
| Lat parser, semantic validation, and LIR lowering | C | parse/semantic/lowering invariant tests, no runtime execution, deterministic diagnostics, explicit attention to buffer-overflow-class and format-string hazards | fuzzing corpus, memory-safe rewrite or exception contract before untrusted-service use |
| Seal key, public-key, signature, freshness, and receipt metadata | C | bounded key parsing tests, malformed-key tests, replay/stale request cases, metadata-only crypto posture | cryptographic module boundary, FIPS 140-3 applicability decision, sensitive-data handling review |
| Runtime boundary, Nucleus task, and effect-decision records | C | deny-by-default behavior, no-effect reports, unknown request/effect denial tests, operator confirmation non-override tests, no shell mutation or workload authority | zero-trust policy prerequisites, audit records, authority tests, distinct operator/workload identity context, no production runtime claim |
| Kernel metadata seed surfaces | C | metadata-only state reports, no boot/hardware/kernel isolation claim, bounded local tests | separate kernel safety contract, memory-safe or restricted-C exception plan before real kernel authority |
| Restricted C++ authority layer | C++ | constrained profile, RAII/value-type preference, no exceptions across C/security boundaries, no raw owning pointers, explicit review of allocator and ownership expansion | exception review for any unsafe ownership, allocator, ABI, or dependency expansion |
| Installer UI and engine | Rust | `cargo check --locked`, no Rust unsafe blocks, centralized process-launch boundary, symlink/path traversal guards, no raw shell interpolation path | no live mutation without evidence bundle, rollback contract, update authenticity evidence, and verification transcript |
| Shell guard and packaging lanes | POSIX shell | fail-fast scripts, private tempdirs, no ad hoc network clients, reviewed privilege/package-manager allowlists, centralized shell boundary rules | no production installer or release lane without SBOM, dependency review, and command-boundary review |
| GitHub workflow surface | YAML and shell commands | pinned actions, read-only permissions, no `pull_request_target`, no secrets, no implicit token use | dedicated review guard before write tokens, OIDC, secrets, or release publishing |
| Future network, MCP, server, update, recovery, boot, or hardware surfaces | not implemented | future-gated and denied | memory-safe implementation preferred; restricted C/C++ requires exception contract and tests |

## Required Rules

New high-risk components must follow this decision path:

```text
1. Prefer Rust or another memory-safe implementation language.
2. If C/C++ is used, document why a memory-safe implementation is not practical.
3. Apply docs/security/C_CPP_SECURITY_PROFILE.md and docs/security/C_ABI_BOUNDARY_POLICY.md.
4. Add malformed-input, boundary-length, truncation, null-rule, ownership, lifetime, and failure-mode tests.
5. Add explicit review for buffer overflow, format-string, off-by-one, use-after-free, and command-construction hazards where applicable.
6. Add fuzzing before parser or external-input code can be promoted as a security boundary.
7. Keep production protection, memory-safety guarantee, compliance, certification, and external endorsement claims closed until evidence exists.
```

## Current Guard Coverage

Current guard coverage includes:

```text
unsafe_c_string_api_guard=1
source_shell_exec_guard=1
unsafe_python_api_guard=1
rust_installer_unsafe_block_guard=1
rust_installer_process_launch_boundary_guard=1
workflow_pinned_action_guard=1
workflow_read_only_permission_guard=1
workflow_secret_usage_guard=1
private_tempdir_guard=1
strict_warning_flag_guard=1
```

These guards reduce risk; they do not prove memory safety.

## Required Future Evidence Before Promotion

Before any Latticra component is described as memory-safe, hardened, production-ready, or a security boundary, it needs:

- component-specific threat model;
- input-size and allocation limits;
- malformed-input and edge-case tests;
- hazard-class review for buffer overflow, format-string, off-by-one, lifetime, and command-construction failure modes where applicable;
- sanitizer or static-analysis transcript where supported;
- fuzzing plan and corpus for parsers or external-input surfaces;
- unsafe exception inventory for any remaining C/C++ high-risk code;
- dependency and SBOM review for shipped artifacts;
- public non-claim review.

## Validation

This roadmap is guarded by:

```sh
sh scripts/test-memory-safety-roadmap.sh
```

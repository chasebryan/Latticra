#!/usr/bin/env sh
set -eu

doc="docs/MEMORY_SAFETY_ROADMAP.md"
status_doc="docs/status/MEMORY_SAFETY_ROADMAP_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'memory safety roadmap: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'memory safety roadmap: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_file docs/security/C_CPP_SECURITY_PROFILE.md
require_file docs/security/C_ABI_BOUNDARY_POLICY.md
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/security.html
require_file Makefile
require_file scripts/test-high-assurance-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: memory-safety roadmap' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'NSA/CISA memory-safe-language guidance' "$doc"
require_contains 'CISA The Case for Memory Safe Roadmaps' "$doc"
require_contains 'buffer overflow alert' "$doc"
require_contains 'OS command injection' "$doc"
require_contains 'CISA/FBI product-security bad-practice guidance' "$doc"
require_contains 'Component Inventory' "$doc"
require_contains 'Required Rules' "$doc"
require_contains 'Current Guard Coverage' "$doc"
require_contains 'Required Future Evidence Before Promotion' "$doc"

for field in \
  'memory_safety_roadmap_present=1' \
  'memory_safety_roadmap_guard_present=1' \
  'high_assurance_security_baseline_present=1' \
  'c_cpp_security_profile_present=1' \
  'c_abi_boundary_policy_present=1' \
  'restricted_c_cpp_profile_required=1' \
  'memory_safe_language_preferred_for_new_high_risk_components=1' \
  'memory_safe_language_exception_contract_required=1' \
  'parser_fuzzing_required_before_security_boundary_claim=1' \
  'unsafe_exception_record_required=1' \
  'component_memory_safety_inventory_present=1' \
  'implementation_behavior_changed=0' \
  'runtime_authority_granted=0' \
  'security_boundary_claimed=0' \
  'memory_safety_guarantee_claimed=0' \
  'production_protection_claim_allowed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

require_contains 'memory_safety_roadmap_status_present=1' "$status_doc"

for component in \
  'L-UI source buffer and parser surfaces' \
  'Lat parser, semantic validation, and LIR lowering' \
  'Seal key, public-key, signature, freshness, and receipt metadata' \
  'Runtime boundary, Nucleus task, and effect-decision records' \
  'Kernel metadata seed surfaces' \
  'Restricted C++ authority layer' \
  'Installer UI and engine' \
  'Shell guard and packaging lanes' \
  'GitHub workflow surface' \
  'Future network, MCP, server, update, recovery, boot, or hardware surfaces'
do
  require_contains "$component" "$doc"
done

for allocation in \
  'buffer-overflow-class and format-string hazards' \
  'truncation, off-by-one, and lifetime faults' \
  'distinct operator/workload identity context' \
  'no raw shell interpolation path' \
  'command-boundary review' \
  'buffer overflow, format-string, off-by-one, use-after-free, and command-construction hazards'
do
  require_contains "$allocation" "$doc"
done

for guard in \
  'unsafe_c_string_api_guard=1' \
  'source_shell_exec_guard=1' \
  'unsafe_python_api_guard=1' \
  'rust_installer_unsafe_block_guard=1' \
  'rust_installer_process_launch_boundary_guard=1' \
  'workflow_pinned_action_guard=1' \
  'workflow_read_only_permission_guard=1' \
  'workflow_secret_usage_guard=1' \
  'private_tempdir_guard=1' \
  'strict_warning_flag_guard=1'
do
  require_contains "$guard" "$doc"
done

require_contains 'docs/MEMORY_SAFETY_ROADMAP.md' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'scripts/test-memory-safety-roadmap.sh' docs/HIGH_ASSURANCE_SECURITY_BASELINE.md
require_contains 'docs/MEMORY_SAFETY_ROADMAP.md' SECURITY.md
require_contains 'memory_safety_roadmap_present=1' README.md
require_contains 'memory_safety_roadmap_present=1' STATUS.md
require_contains 'MEMORY_SAFETY_ROADMAP_STATUS.md' docs/status/README.md
require_contains 'memory_safety_roadmap_present=1' docs/status/README.md
require_contains 'Latest memory-safety roadmap note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'MEMORY_SAFETY_ROADMAP.md' docs/FOUNDATION_INDEX.md
require_contains 'Memory-safety roadmap' docs/security.html
require_contains 'MEMORY_SAFETY_ROADMAP.md' docs/security.html
require_contains 'sh ./scripts/test-memory-safety-roadmap.sh' Makefile
require_contains 'memory-safety-roadmap:' Makefile
require_contains 'test-memory-safety-roadmap.sh' scripts/test-quality-safety-guards.sh

printf 'memory_safety_roadmap: ok\n'

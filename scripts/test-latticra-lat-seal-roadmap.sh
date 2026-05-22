#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra lat seal roadmap: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra lat seal roadmap: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

strategy="docs/POLYMORPHIC_LANGUAGE_STRATEGY.md"
roadmap="docs/LATTICRA_LAT_SEAL_ROADMAP.md"
targets="docs/LATTICRA_ARCHITECTURE_TARGETS.md"

require_file "$strategy"
require_file "$roadmap"
require_file "$targets"

require_contains 'Status: active architecture strategy' "$strategy"
require_contains 'C owns the substrate.' "$strategy"
require_contains 'C++ owns governed architecture and policy modeling.' "$strategy"
require_contains 'Rust owns safe tooling and high-risk input surfaces.' "$strategy"
require_contains 'Lat owns Latticra-native declaration and system intent.' "$strategy"
require_contains 'LIR owns bounded intermediate representation and evidence-bearing shape.' "$strategy"
require_contains 'plain C ABI' "$strategy"
require_contains 'no implicit authority grant' "$strategy"
require_contains 'no effect without a named gate' "$strategy"
require_contains 'runtime authority' "$strategy"

require_contains 'Status: active strategy roadmap' "$roadmap"
require_contains 'Latticra' "$roadmap"
require_contains 'Lat' "$roadmap"
require_contains 'LIR' "$roadmap"
require_contains 'Latticra Seal' "$roadmap"
require_contains 'Fedora/Linux remains the proving lane' "$roadmap"
require_contains 'evidence first' "$roadmap"
require_contains 'reports before authority' "$roadmap"
require_contains 'allow_candidate_grants_authority=0' "$roadmap"
require_contains 'runtime_authority_granted=0' "$roadmap"
require_contains 'effect_performed=0' "$roadmap"
require_contains 'tools/seal-report' "$roadmap"
require_contains 'CapabilityGraph' "$roadmap"
require_contains 'Do not claim:' "$roadmap"

require_contains 'Status: active architecture target plan' "$targets"
require_contains 'C substrate targets' "$targets"
require_contains 'Constrained C++ targets' "$targets"
require_contains 'Rust targets' "$targets"
require_contains 'Lat targets' "$targets"
require_contains 'LIR targets' "$targets"
require_contains 'Seal targets' "$targets"
require_contains 'Fedora/Linux targets' "$targets"
require_contains 'MCP and AI-era tool-boundary targets' "$targets"
require_contains 'runtime_authority_granted=0' "$targets"
require_contains 'effect_performed=0' "$targets"
require_contains 'mcp_server=0' "$targets"
require_contains 'ai_agent_execution_control=0' "$targets"

printf 'latticra lat seal roadmap: ok\n'

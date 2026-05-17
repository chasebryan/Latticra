#!/usr/bin/env sh
set -eu

doc="docs/DEFENSIVE_THREAT_MODEL_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'defensive threat model contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'defensive threat model contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: Defensive threat model contract' "$doc"
require_contains 'This document does not implement security controls.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Threat model posture' "$doc"
require_contains 'Protected assets' "$doc"
require_contains 'Trust boundaries' "$doc"
require_contains 'Assumptions' "$doc"
require_contains 'Capability categories' "$doc"
require_contains 'Abuse cases' "$doc"
require_contains 'Defensive controls currently represented' "$doc"
require_contains 'Evidence expectations' "$doc"
require_contains 'Validation expectations' "$doc"
require_contains 'Non-goals' "$doc"
require_contains 'Future file policy' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/REAL_SYSTEM_CONTRACT.md \
  docs/NON_CLAIMS.md \
  docs/EVIDENCE_LADDER.md \
  docs/EFFECT_GATES.md \
  docs/RUNTIME_BOUNDARY_CONTRACT.md \
  docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md \
  docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md \
  docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md \
  docs/L_UI_RENDERING_IMPLEMENTATION.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
do
  require_contains "$related" "$doc"
done

for asset in \
  'source text integrity' \
  'parse results' \
  'diagnostic metadata' \
  'source spans' \
  'AST metadata' \
  'semantic validation results' \
  'LIR metadata' \
  'Lat parse metadata' \
  'L-UI render metadata' \
  'Nucleus preview records' \
  'Nucleus task records' \
  'runtime boundary records' \
  'authority audit records' \
  'operator-visible reports' \
  'effect-gate decisions' \
  'project claims and status records'
do
  require_contains "$asset" "$doc"
done

for boundary in \
  'source input boundary' \
  'parser boundary' \
  'semantic validation boundary' \
  'LIR lowering boundary' \
  'Lat grammar boundary' \
  'L-UI rendering boundary' \
  'Nucleus preview boundary' \
  'Nucleus task classification boundary' \
  'runtime boundary' \
  'authority validation boundary' \
  'operator report boundary' \
  'repository documentation boundary'
do
  require_contains "$boundary" "$doc"
done

for posture in \
  'security controls implemented? limited/no-effect only' \
  'runtime protection implemented? no' \
  'production protection claim allowed? no' \
  'malware prevention claim allowed? no' \
  'ransomware prevention claim allowed? no' \
  'sandbox claim allowed? no' \
  'operator-visible report claim allowed? yes, where implemented and tested' \
  'denied-by-default boundary claim allowed? yes, where implemented and tested'
do
  require_contains "$posture" "$doc"
done

for assumption in \
  'source buffers may be malformed' \
  'input may be adversarial' \
  'reported metadata must be deterministic' \
  'unknown requests must be denied or classified as unsupported' \
  'unknown effects must be denied or classified as unsupported' \
  'effect-performing behavior must require explicit future gates' \
  'operator confirmation must not override policy by itself' \
  'security claims must follow evidence' \
  'no-effect slices must remain no-effect'
do
  require_contains "$assumption" "$doc"
done

for category in \
  'malformed input construction' \
  'ambiguous source construction' \
  'oversized input pressure' \
  'unexpected escape sequence use' \
  'metadata confusion attempts' \
  'request-kind confusion attempts' \
  'effect-kind confusion attempts' \
  'boundary bypass attempts' \
  'operator-report confusion attempts' \
  'policy downgrade attempts' \
  'status-record exaggeration attempts'
do
  require_contains "$category" "$doc"
done

for abuse in \
  'malformed source causes unclear diagnostics' \
  'escaped data hides operator-visible content' \
  'literal source-buffer NUL causes parser confusion' \
  'duplicate names cause ambiguous binding' \
  'invalid binding prefix bypasses semantic validation' \
  'invalid LIR input reaches rendering' \
  'failed authority metadata is treated as allowed' \
  'unknown request is treated as allowed' \
  'unknown effect is treated as allowed' \
  'future-gated request is treated as executable' \
  'operator confirmation overrides policy' \
  'report omits denial reason' \
  'status documentation overclaims implementation state'
do
  require_contains "$abuse" "$doc"
done

for evidence in \
  'contract document' \
  'implementation plan' \
  'implementation document' \
  'unit or invariant tests' \
  'static guard when applicable' \
  'deterministic report output when applicable' \
  'negative tests for denied behavior' \
  'status update' \
  'non-claim update' \
  'compatibility check'
do
  require_contains "$evidence" "$doc"
done

for validation in \
  'positive tests for allowed no-effect behavior' \
  'negative tests for denied effect behavior' \
  'unknown request tests' \
  'unknown effect tests' \
  'malformed input tests' \
  'small-buffer tests' \
  'deterministic report tests' \
  'no-mutation tests' \
  'no-network tests' \
  'no-hardware tests' \
  'no-recovery tests' \
  'operator confirmation non-override tests' \
  'status/non-claim guard tests'
do
  require_contains "$validation" "$doc"
done

for non_goal in \
  'attack tooling' \
  'exploit development' \
  'payload generation' \
  'malware simulation' \
  'credential access' \
  'stealth behavior' \
  'bypass instructions' \
  'persistence mechanisms' \
  'exfiltration behavior'
do
  require_contains "$non_goal" "$doc"
done

for path in \
  docs/DEFENSIVE_THREAT_MODEL_IMPLEMENTATION_PLAN.md \
  docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md \
  scripts/test-defensive-threat-model-contract.sh \
  scripts/test-defensive-threat-model-validation.sh \
  tests/defensive_threat_model_invariants.c
do
  require_contains "$path" "$doc"
done

for test_name in \
  defensive_threat_model_names_assets \
  defensive_threat_model_names_boundaries \
  defensive_threat_model_names_assumptions \
  defensive_threat_model_names_non_goals \
  defensive_threat_model_preserves_non_claims \
  defensive_threat_model_requires_evidence_classes \
  defensive_threat_model_maps_abuse_cases_to_tests_or_gaps \
  defensive_threat_model_forbids_operator_confirmation_override \
  defensive_threat_model_forbids_runtime_protection_claims \
  defensive_threat_model_forbids_malware_prevention_claims \
  defensive_threat_model_forbids_ransomware_prevention_claims
do
  require_contains "$test_name" "$doc"
done

for compat in \
  'existing non-claims' \
  'runtime boundary disabled-by-default posture' \
  'Nucleus task no-effect posture' \
  'constrained authority no-effect posture' \
  'L-UI rendering no-effect posture' \
  'LIR metadata-only posture' \
  'Lat parser metadata-only posture' \
  'source-buffer literal NUL rejection' \
  'escaped decoded NUL visibility' \
  'semantic validation prerequisites' \
  'operator confirmation non-override policy'
do
  require_contains "$compat" "$doc"
done

for forbidden in \
  'provide attack instructions' \
  'provide exploit steps' \
  'provide payload construction' \
  'provide stealth guidance' \
  'provide credential access guidance' \
  'provide persistence guidance' \
  'claim production protection' \
  'claim malware prevention' \
  'claim ransomware prevention' \
  'claim sandboxing' \
  'claim certification' \
  'claim operating-system completeness'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-defensive-threat-model-contract.sh' "$doc"

printf 'defensive_threat_model_contract: ok\n'

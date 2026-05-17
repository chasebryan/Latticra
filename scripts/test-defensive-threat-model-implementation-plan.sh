#!/usr/bin/env sh
set -eu

doc="docs/DEFENSIVE_THREAT_MODEL_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'defensive threat model implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'defensive threat model implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement security controls.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation decision' "$doc"
require_contains 'External standards alignment' "$doc"
require_contains 'Validation document shape' "$doc"
require_contains 'Protected asset matrix' "$doc"
require_contains 'Trust boundary matrix' "$doc"
require_contains 'Abuse-case mapping' "$doc"
require_contains 'Evidence matrix' "$doc"
require_contains 'Guard behavior' "$doc"
require_contains 'Workflow behavior' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/DEFENSIVE_THREAT_MODEL_CONTRACT.md \
  docs/REAL_SYSTEM_CONTRACT.md \
  docs/NON_CLAIMS.md \
  docs/EVIDENCE_LADDER.md \
  docs/EFFECT_GATES.md \
  docs/RUNTIME_BOUNDARY_CONTRACT.md \
  docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md \
  docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md \
  docs/L_UI_RENDERING_IMPLEMENTATION.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md \
  scripts/test-defensive-threat-model-contract.sh
do
  require_contains "$related" "$doc"
done

for external in \
  'NSA Cybersecurity guidance and standards/certification resources' \
  'CISA Secure by Design guidance' \
  'CISA Cross-Sector Cybersecurity Performance Goals' \
  'CISA Known Exploited Vulnerabilities catalog' \
  'CISA joint cybersecurity advisories where relevant' \
  'FBI Cyber alerts, cyber threat reporting, and joint advisories where relevant' \
  'source agency' \
  'source title' \
  'authoritative URL' \
  'date checked' \
  'version or publication date when available' \
  'applicability to Latticra' \
  'mapped Latticra document' \
  'mapped Latticra control or boundary' \
  'current evidence' \
  'missing evidence' \
  'claim allowed' \
  'claim forbidden' \
  'review cadence'
do
  require_contains "$external" "$doc"
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
  'repository documentation boundary' \
  'external standards alignment boundary'
do
  require_contains "$boundary" "$doc"
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
  'status documentation overclaims implementation state' \
  'external standard is referenced as if it were certification' \
  'outdated external guidance remains marked current'
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
  'compatibility check' \
  'external standards source check' \
  'standards alignment gap entry'
do
  require_contains "$evidence" "$doc"
done

for validation in \
  docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md \
  scripts/test-defensive-threat-model-validation.sh \
  'Protected asset matrix' \
  'Trust boundary matrix' \
  'Assumption matrix' \
  'Abuse-case mapping' \
  'Evidence matrix' \
  'External standards alignment ledger' \
  'Validation matrix' \
  'Non-goal matrix' \
  'Compatibility expectations' \
  'Current gaps' \
  'Non-claims'
do
  require_contains "$validation" "$doc"
done

for forbidden in \
  'claim certification' \
  'claim accreditation' \
  'claim compliance' \
  'claim malware prevention' \
  'claim ransomware prevention' \
  'claim sandboxing' \
  'claim production protection' \
  'claim operational readiness' \
  'provide attack instructions' \
  'provide exploit steps' \
  'provide payload construction' \
  'provide stealth guidance' \
  'provide persistence guidance' \
  'provide credential access guidance' \
  'treat external standards alignment as proof of protection'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-defensive-threat-model-implementation-plan.sh' "$doc"
require_contains 'Defensive threat model validation files may be added only after this plan is merged.' "$doc"

printf 'defensive_threat_model_implementation_plan: ok\n'

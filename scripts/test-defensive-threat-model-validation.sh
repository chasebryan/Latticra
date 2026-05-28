#!/usr/bin/env sh
set -eu

doc="docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'defensive threat model validation: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'defensive threat model validation: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: defensive threat model validation ledger' "$doc"
require_contains 'This document does not implement security controls.' "$doc"
require_contains 'Protected asset matrix' "$doc"
require_contains 'Trust boundary matrix' "$doc"
require_contains 'Assumption matrix' "$doc"
require_contains 'Abuse-case mapping' "$doc"
require_contains 'Evidence matrix' "$doc"
require_contains 'External standards alignment ledger' "$doc"
require_contains 'Validation matrix' "$doc"
require_contains 'Non-goal matrix' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Validation refinement checkpoint' "$doc"
require_contains 'Current gaps' "$doc"
require_contains 'Non-claims' "$doc"

for source_doc in \
  docs/DEFENSIVE_THREAT_MODEL_CONTRACT.md \
  docs/DEFENSIVE_THREAT_MODEL_IMPLEMENTATION_PLAN.md \
  docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
do
  require_contains "$source_doc" "$doc"
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
  'retained C/C++ high-risk code leaves buffer-overflow-class defects untracked' \
  'command construction reaches a shell boundary without a reviewed contract' \
  'future workload or service authority lacks distinct workload identity' \
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

for external in \
  'NSA Zero Trust Implementation Guidelines' \
  'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4393480/nsa-releases-phase-one-and-phase-two-of-the-zero-trust-implementation-guidelines/' \
  'NSA/CISA Memory Safe Languages CSI' \
  'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4223298/nsa-and-cisa-release-csi-highlighting-importance-of-memory-safe-languages-in-so/' \
  'NSA MCP Security Design Considerations for AI-Driven Automation' \
  'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4496698/nsa-releases-security-design-considerations-for-ai-driven-automation-leveraging/' \
  'NSA/partners Careful Adoption of Agentic AI Services' \
  'https://www.nsa.gov/Press-Room/Press-Releases-Statements/Press-Release-View/Article/4475134/nsa-joins-the-asds-acsc-and-others-to-release-guidance-on-agentic-artificial-in/' \
  'NIST Summary Analysis of Responses to the RFI Regarding Security Considerations for AI Agents' \
  'https://www.nist.gov/publications/summary-analysis-responses-request-information-regarding-security-considerations-ai' \
  'NIST NCCoE concept paper on identity and authority of software agents' \
  'https://www.nist.gov/news-events/news/2026/02/new-concept-paper-identity-and-authority-software-agents' \
  'CISA The Case for Memory Safe Roadmaps' \
  'https://www.cisa.gov/resources-tools/resources/case-memory-safe-roadmaps' \
  'CISA Secure by Design' \
  'https://www.cisa.gov/securebydesign' \
  'CISA Secure by Design Alert: Eliminating Buffer Overflow Vulnerabilities' \
  'https://www.cisa.gov/news-events/alerts/2025/02/12/cisa-and-fbi-warn-malicious-cyber-actors-using-buffer-overflow-vulnerabilities-compromise-software' \
  'CISA Secure by Design Alert: Eliminating OS Command Injection Vulnerabilities' \
  'https://www.cisa.gov/resources-tools/resources/secure-design-alert-eliminating-os-command-injection-vulnerabilities' \
  'CISA/FBI Product Security Bad Practices' \
  'https://www.cisa.gov/resources-tools/resources/product-security-bad-practices' \
  'CISA Cross-Sector Cybersecurity Performance Goals' \
  'https://www.cisa.gov/cybersecurity-performance-goals' \
  'CISA Zero Trust Maturity Model' \
  'https://www.cisa.gov/resources-tools/resources/zero-trust-maturity-model' \
  'CISA Known Exploited Vulnerabilities Catalog' \
  'https://www.cisa.gov/resources-tools/resources/known-exploited-vulnerabilities-catalog' \
  'FBI Cyber' \
  'https://www.fbi.gov/investigate/cyber' \
  'NIST Cybersecurity Framework 2.0' \
  'https://www.nist.gov/cyberframework' \
  'NIST SP 800-218 SSDF' \
  'https://csrc.nist.gov/pubs/sp/800/218/final' \
  'NIST SP 800-53 Rev. 5' \
  'https://csrc.nist.gov/Pubs/sp/800/53/r5/upd1/Final' \
  'NIST SP 800-160 Vol. 2 Rev. 1' \
  'https://csrc.nist.gov/pubs/sp/800/160/v2/r1/final' \
  'NIST SP 800-207 Zero Trust Architecture' \
  'https://www.nist.gov/publications/zero-trust-architecture-0' \
  'NIST SP 800-207A Zero Trust Architecture: A Practitioner'\''s Guide' \
  'https://csrc.nist.gov/pubs/sp/800/207/a/final' \
  'NIST SP 1800-35 Implementing a Zero Trust Architecture' \
  'https://csrc.nist.gov/pubs/sp/1800/35/final' \
  'FIPS 140-3' \
  'https://csrc.nist.gov/pubs/fips/140-3/final' \
  'Date checked: 2026-05-26' \
  'manual source review' \
  'certification/compliance/protection'
do
  require_contains "$external" "$doc"
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
  'command-boundary tests' \
  'workload/service identity zero-trust tests' \
  'mcp/tool-boundary and context-sharing tests' \
  'software-agent identity and authorization tests' \
  'status/non-claim guard tests'
do
  require_contains "$validation" "$doc"
done

for non_goal in \
  'attack tooling' \
  'exploit development' \
  'payload generation' \
  'credential access' \
  'stealth behavior' \
  'bypass instructions' \
  'persistence mechanisms' \
  'exfiltration behavior' \
  'certification claim' \
  'compliance claim' \
  'production protection claim'
do
  require_contains "$non_goal" "$doc"
done

for gap in \
  'defensive_threat_model_validation_refinement_present=1' \
  'external_source_refresh_checkpoint_present=1' \
  'external_source_refresh_date=2026-05-26' \
  'manual_source_review_required=1' \
  'manual_source_review_completed_for_current_baseline=1' \
  'high_assurance_security_baseline_present=1' \
  'nsa_zero_trust_guideline_observed=1' \
  'nsa_cisa_memory_safe_languages_observed=1' \
  'cisa_fbi_product_security_bad_practices_observed=1' \
  'nist_high_assurance_references_observed=1' \
  'runtime_boundary_policy_expansion_next=1' \
  'abuse_case_fixture_expansion_next=1' \
  'certification_from_external_alignment=0' \
  'compliance_from_external_alignment=0' \
  'protection_from_external_alignment=0' \
  'security_controls_added=0' \
  'runtime_authority_granted=0' \
  'external standards ledger needs recurring manual review before release' \
  'runtime boundary source needs fuller policy expansion' \
  'abuse-case mapping needs broader fixture coverage' \
  'external advisory-by-advisory mapping is not complete' \
  'workload/service identity and host-integrity prerequisites are not yet profiled for future authority' \
  'mcp/tool-boundary and context-sharing prerequisites are not yet profiled for future authority' \
  'software-agent identity and authorization prerequisites are not yet profiled for future authority' \
  'no certification or compliance mapping exists'
do
  require_contains "$gap" "$doc"
done

require_contains 'sh scripts/test-defensive-threat-model-validation.sh' "$doc"

printf 'defensive_threat_model_validation: ok\n'

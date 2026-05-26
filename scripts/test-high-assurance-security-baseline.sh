#!/usr/bin/env sh
set -eu

doc="docs/HIGH_ASSURANCE_SECURITY_BASELINE.md"
status_doc="docs/status/HIGH_ASSURANCE_SECURITY_BASELINE_STATUS.md"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'high assurance security baseline: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'high assurance security baseline: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file "$doc"
require_file "$status_doc"
require_file SECURITY.md
require_file README.md
require_file STATUS.md
require_file docs/security.html
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION.md
require_file docs/DEFENSIVE_THREAT_MODEL_VALIDATION_REFINEMENT.md
require_file docs/MEMORY_SAFETY_ROADMAP.md
require_file docs/SUPPLY_CHAIN_SECURITY_BASELINE.md
require_file docs/security/C_CPP_SECURITY_PROFILE.md
require_file docs/security/C_ABI_BOUNDARY_POLICY.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file scripts/test-defensive-threat-model-validation.sh
require_file scripts/test-defensive-threat-model-validation-refinement.sh
require_file scripts/test-memory-safety-roadmap.sh
require_file scripts/test-supply-chain-security-baseline.sh
require_file scripts/test-quality-safety-guards.sh

require_contains 'Status: high-assurance security baseline checkpoint' "$doc"
require_contains 'Source refresh date: 2026-05-26' "$doc"
require_contains 'Date checked: 2026-05-26' "$doc"
require_contains 'Authoritative Source Inventory' "$doc"
require_contains 'NSA Zero Trust Implementation Guidelines, Primer, Discovery Phase, Phase One, and Phase Two' "$doc"
require_contains 'NSA/CISA Memory Safe Languages CSI' "$doc"
require_contains 'CISA Secure by Design' "$doc"
require_contains 'CISA/FBI Product Security Bad Practices' "$doc"
require_contains 'CISA Cross-Sector Cybersecurity Performance Goals' "$doc"
require_contains 'CISA Zero Trust Maturity Model v2' "$doc"
require_contains 'CISA Known Exploited Vulnerabilities Catalog' "$doc"
require_contains 'FBI Cyber' "$doc"
require_contains 'NIST Cybersecurity Framework 2.0' "$doc"
require_contains 'NIST SP 800-218 SSDF v1.1' "$doc"
require_contains 'NIST SP 800-53 Rev. 5, Release 5.2.0' "$doc"
require_contains 'NIST SP 800-160 Vol. 2 Rev. 1' "$doc"
require_contains 'NIST SP 800-207 Zero Trust Architecture' "$doc"
require_contains 'FIPS 140-3' "$doc"

for field in \
  'high_assurance_security_baseline_present=1' \
  'source_refresh_date=2026-05-26' \
  'official_source_inventory_present=1' \
  'memory_safety_roadmap_required=1' \
  'memory_safety_roadmap_present=1' \
  'zero_trust_runtime_boundary_required=1' \
  'ssdf_secure_development_required=1' \
  'cpg_operational_baseline_required=1' \
  'supply_chain_security_baseline_present=1' \
  'kev_release_review_required=1' \
  'fips_crypto_boundary_required_before_production_crypto=1' \
  'sbom_required_before_production_installer=1' \
  'third_party_security_validation_required_before_security_release=1' \
  'incident_response_plan_required_before_production_service=1' \
  'recurring_source_review_required=1' \
  'implementation_behavior_changed=0' \
  'runtime_authority_granted=0' \
  'security_boundary_claimed=0' \
  'certification_claim_allowed=0' \
  'compliance_claim_allowed=0' \
  'external_endorsement_claimed=0' \
  'production_protection_claim_allowed=0'
do
  require_contains "$field" "$doc"
  require_contains "$field" "$status_doc"
done

for allocation in \
  'new network-facing code -> memory-safe language preferred' \
  'new cryptographic key-handling code -> memory-safe language preferred' \
  'new parser for untrusted external input -> memory-safe language preferred or restricted C profile with fuzzing and exception record' \
  'strcpy' \
  'system()' \
  'request_kind_known=1' \
  'unknown_request_denied=1' \
  'future_gate_denied_until_contract=1' \
  'SBOM evidence for shipped artifacts' \
  'KEV/NVD review or documented offline exception before release' \
  'defined cryptographic module boundary' \
  'FIPS 140-3 applicability decision' \
  'assign a named cybersecurity owner' \
  'schedule table-top or third-party validation before security release'
do
  require_contains "$allocation" "$doc"
done

require_contains 'Memory-safety roadmap alignment' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'memory-safe implementation language for new high-risk components' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'CISA/FBI product-security bad-practice exclusions' docs/security/C_CPP_SECURITY_PROFILE.md
require_contains 'FIPS 140-3' docs/security/C_CPP_SECURITY_PROFILE.md

require_contains 'High-assurance standards posture' SECURITY.md
require_contains 'docs/HIGH_ASSURANCE_SECURITY_BASELINE.md' SECURITY.md
require_contains 'docs/MEMORY_SAFETY_ROADMAP.md' SECURITY.md
require_contains 'docs/SUPPLY_CHAIN_SECURITY_BASELINE.md' SECURITY.md
require_contains 'high_assurance_security_baseline_present=1' README.md
require_contains 'memory_safety_roadmap_present=1' README.md
require_contains 'supply_chain_security_baseline_present=1' README.md
require_contains 'source_refresh_date=2026-05-26' README.md
require_contains 'high_assurance_security_baseline_present=1' STATUS.md
require_contains 'memory_safety_roadmap_present=1' STATUS.md
require_contains 'supply_chain_security_baseline_present=1' STATUS.md
require_contains 'High-assurance security baseline' docs/status/README.md
require_contains 'HIGH_ASSURANCE_SECURITY_BASELINE_STATUS.md' docs/status/README.md
require_contains 'Latest high-assurance security baseline note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'High-assurance baseline' docs/security.html
require_contains 'HIGH_ASSURANCE_SECURITY_BASELINE.md' docs/security.html
require_contains 'sh ./scripts/test-high-assurance-security-baseline.sh' Makefile
require_contains 'sh ./scripts/test-memory-safety-roadmap.sh' Makefile
require_contains 'sh ./scripts/test-supply-chain-security-baseline.sh' Makefile
require_contains 'quality-security-standards:' Makefile
require_contains 'quality-security-standards' Makefile
require_contains 'test-high-assurance-security-baseline.sh' scripts/test-quality-safety-guards.sh

printf 'high_assurance_security_baseline: ok\n'

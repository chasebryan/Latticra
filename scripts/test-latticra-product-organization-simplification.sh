#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra product organization simplification: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing pattern in $file: $pattern"
}

doc='docs/LATTICRA_PRODUCT_ORGANIZATION_SIMPLIFICATION_PLAN.md'
status='docs/status/LATTICRA_PRODUCT_ORGANIZATION_SIMPLIFICATION_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-product-organization-simplification.yml'

for file in "$doc" "$status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow"
do
  require_file "$file"
done

for file in "$doc" "$status"
do
  require_contains 'latticra_product_organization_simplification_present=1' "$file"
  require_contains 'product_organization_simplification_guard_present=1' "$file"
  require_contains 'decision_id=latticra-product-organization-simplification' "$file"
  require_contains 'decision_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'product_route_layer_present=1' "$file"
  require_contains 'physical_reorganization_performed=0' "$file"
  require_contains 'active_repo_relocation_performed=0' "$file"
  require_contains 'source_import_performed=0' "$file"
  require_contains 'artifact_copy_performed=0' "$file"
  require_contains 'sibling_repo_mutation_performed=0' "$file"
  require_contains 'network_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'cybersecurity_certification_claim=0' "$file"
  require_contains 'set_and_forget_security_claim=0' "$file"
  require_contains 'central_hub_role=Latticra Core plus Netplane routing' "$file"
  require_contains 'simplified_user_route=Latticra Guard' "$file"
  require_contains 'integration_route=Latticra Netplane' "$file"
  require_contains 'research_route=Latticra Research' "$file"
  require_contains 'separate_channel=WARLOCK-INDEX' "$file"
  require_contains 'next_recommended_lane=latticra-guard-simplified-installer-intake' "$file"
  require_contains 'ready_for_next_when=guarded-routing-present-and-quality-status-green' "$file"
  require_contains 'latticra_product_organization_simplification: ok' "$file"
done

for pattern in \
  'Latticra Guard' \
  'Latticra Core' \
  'Latticra Netplane' \
  'Latticra Research' \
  'WARLOCK-INDEX' \
  'Kaiju, l2, l3, L4, fyr, Rainbow' \
  'Nadia remains a separate offline AI lane' \
  'The existing guarded file layout should stay in place for now' \
  'What do I install?' \
  'What does it not claim?' \
  'latticra-guard-simplified-installer-intake'
do
  require_contains "$pattern" "$doc"
done

require_contains 'LATTICRA_PRODUCT_ORGANIZATION_SIMPLIFICATION_STATUS.md' "$status_index"
require_contains 'Product Organization Simplification' "$docs_hub"
require_contains 'Latticra Guard' "$root_readme"
require_contains 'Latticra Core' "$root_readme"
require_contains 'Latticra Netplane' "$root_readme"
require_contains 'Latticra Research' "$root_readme"
require_contains 'WARLOCK-INDEX' "$root_readme"
require_contains 'Product organization simplification plan](docs/LATTICRA_PRODUCT_ORGANIZATION_SIMPLIFICATION_PLAN.md)' "$root_readme"
require_contains 'Latest Latticra product organization simplification note: 2026-06-19 CDT' "$root_status"
require_contains 'Latest Latticra product organization simplification note: 2026-06-19 CDT' "$current_status"
require_contains 'Latest Latticra product organization simplification note: 2026-06-19 CDT' "$current_direction"
require_contains 'Latest Latticra product organization simplification note: 2026-06-19 CDT' "$upcoming_work"
require_contains 'latticra-product-organization-simplification:' "$makefile"
require_contains 'sh ./scripts/test-latticra-product-organization-simplification.sh' "$makefile"
require_contains 'latticra-product-organization-simplification:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-product-organization-simplification.sh' "$quality_guard"
require_contains 'Run Latticra product organization simplification guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-product-organization-simplification.sh' "$workflow"

printf 'latticra_product_organization_simplification: ok\n'

#!/usr/bin/env sh
set -eu

fixture="examples/l-ui/nucleus-preview-card.lui"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq "$pattern" "$file"; then
    printf 'l-ui grammar fixture: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

reject_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq "$pattern" "$file"; then
    printf 'l-ui grammar fixture: forbidden pattern present: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$fixture" ]; then
  printf 'l-ui grammar fixture: missing fixture: %s\n' "$fixture" >&2
  exit 1
fi

require_contains 'lui 0.1' "$fixture"
require_contains 'card NucleusPreview {' "$fixture"
require_contains 'purpose "operator-visible Nucleus preview report"' "$fixture"
require_contains 'effect none' "$fixture"
require_contains 'boundary preview_only' "$fixture"

for rail in top state trace safety gates effects policy execution bottom; do
  require_contains "rail $rail {" "$fixture"
done

for binding in \
  'field origin bind state.origin' \
  'field route bind state.route' \
  'field axis bind state.axis' \
  'field path bind state.path' \
  'field breadcrumb bind state.breadcrumb' \
  'field trace bind state.trace' \
  'field health bind state.health' \
  'field risk bind state.risk' \
  'field lock bind state.lock' \
  'field dark_phase bind state.dark_phase' \
  'field safe_portal bind state.safe_portal' \
  'field rollback bind state.rollback' \
  'field host bind state.host_effect' \
  'field external bind state.external_effect' \
  'field requested bind preview.requested_effect' \
  'field request bind preview.request' \
  'field policy bind preview.policy' \
  'field reason bind preview.reason' \
  'field executed bind preview.executed' \
  'field mutation bind preview.mutation_allowed' \
  'field server bind preview.server_interaction_allowed' \
  'field recovery bind preview.recovery_allowed' \
  'field hardware bind preview.hardware_allowed'
do
  require_contains "$binding" "$fixture"
done

require_contains 'text "Latticra / Nucleus Preview / effect-bound"' "$fixture"
require_contains 'text "preview-only no-live-movement no-host-effect no-external-effect"' "$fixture"

reject_contains 'effect read' "$fixture"
reject_contains 'effect local_mutation' "$fixture"
reject_contains 'effect host_mutation' "$fixture"
reject_contains 'effect network' "$fixture"
reject_contains 'effect hardware' "$fixture"
reject_contains 'effect boot' "$fixture"
reject_contains 'effect recovery' "$fixture"
reject_contains 'effect external' "$fixture"
reject_contains 'execute ' "$fixture"
reject_contains 'server {' "$fixture"
reject_contains 'server call' "$fixture"
reject_contains 'server_interaction {' "$fixture"
reject_contains 'self_update' "$fixture"
reject_contains 'host_mutation' "$fixture"

printf 'l_ui_grammar_fixtures: ok\n'

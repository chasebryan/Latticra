#!/usr/bin/env sh
set -eu

doc="docs/L_UI_PARSER_DESIGN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq "$pattern" "$file"; then
    printf 'l-ui parser design: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'l-ui parser design: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: parser design contract' "$doc"
require_contains 'This document does not implement a parser.' "$doc"
require_contains 'The parser must not:' "$doc"
require_contains 'Allowed parser behavior' "$doc"
require_contains 'Error categories' "$doc"
require_contains 'Parse result shape' "$doc"
require_contains 'Required no-effect flags:' "$doc"
require_contains 'Test plan for future parser implementation' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for category in \
  ok \
  null_argument \
  empty_source \
  unsupported_version \
  missing_card \
  missing_purpose \
  missing_effect \
  unsupported_effect \
  missing_boundary \
  unsupported_boundary \
  missing_rail \
  unknown_rail \
  unknown_binding_prefix \
  missing_required_binding \
  unterminated_string \
  unbalanced_brace \
  forbidden_behavior_marker \
  source_too_large \
  internal_error
do
  require_contains "$category" "$doc"
done

for marker in \
  'effect none' \
  'boundary preview_only' \
  'state.' \
  'preview.' \
  'no_effect=1' \
  'execution_allowed=0' \
  'mutation_allowed=0' \
  'server_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0'
do
  require_contains "$marker" "$doc"
done

for forbidden_boundary in \
  'execute commands' \
  'render UI' \
  'mutate state' \
  'perform live movement' \
  'interact with servers' \
  'access networking' \
  'access hardware' \
  'change boot state'
do
  require_contains "$forbidden_boundary" "$doc"
done

printf 'l_ui_parser_design: ok\n'

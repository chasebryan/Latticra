#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

fail() {
  printf 'latticra effect status surface: %s\n' "$1" >&2
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

require_output_field() {
  field="$1"
  file="$2"
  grep -Fxq -- "$field" "$file" || fail "missing output field in $file: $field"
}

cli='src/latticra_cli.c'
contract='docs/LATTICRA_NO_EFFECT_CLI_PAYLOAD_CONTRACT.md'
implementation='docs/LATTICRA_NO_EFFECT_CLI_STATUS_SURFACE_IMPLEMENTATION.md'
status='docs/status/LATTICRA_EFFECT_STATUS_SURFACE_STATUS.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
status_index='docs/status/README.md'
project_notes='docs/project_notes/UPCOMING_WORK.md'
workflow='.github/workflows/latticra-effect-status-surface.yml'

for file in "$cli" "$contract" "$implementation" "$status" "$readme" "$root_status" "$current_status" "$status_index" "$project_notes" "$workflow"
do
  require_file "$file"
done

for file in "$contract" "$implementation" "$status"
do
  require_contains 'latticra --effect-status' "$file"
  require_contains 'LATTICRA EFFECT STATUS REPORT' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'cli_effect_performed=0' "$file"
  require_contains 'local_operator_effects_present=1' "$file"
  require_contains 'user_local_install_effect_present=1' "$file"
  require_contains 'user_local_copy_effect_present=1' "$file"
  require_contains 'receipt_write_effect_present=1' "$file"
  require_contains 'operator_bundle_write_effect_present=1' "$file"
  require_contains 'effect_authority=bounded-local-visible' "$file"
  require_contains 'host_mutation_allowed=0' "$file"
  require_contains 'root_authority_allowed=0' "$file"
  require_contains 'network_allowed=0' "$file"
  require_contains 'usb_write_allowed=0' "$file"
  require_contains 'qemu_run_allowed=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
done

require_contains 'Edge edition checkpoint: `v0.3.0edge`' "$readme"
require_contains '| Edge edition checkpoint | `v0.3.0edge` |' "$readme"
require_contains 'Edge edition checkpoint: `v0.3.0edge`' "$root_status"
require_contains 'Edge edition checkpoint: `v0.3.0edge`' "$current_status"
require_contains 'Latest Latticra effect status surface note: 2026-05-29 CDT' "$project_notes"
require_contains 'LATTICRA_EFFECT_STATUS_SURFACE_STATUS.md' "$status_index"
require_contains 'Run Latticra effect status surface guard' "$workflow"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-effect-status.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

bin="$tmpdir/latticra"
out="$tmpdir/effect-status.out"
expected="$tmpdir/effect-status.expected"

cc $CFLAGS "$cli" -o "$bin"
"$bin" --effect-status > "$out"

cat > "$expected" <<'EOF'
LATTICRA EFFECT STATUS REPORT
project=latticra
edge_checkpoint=v0.3.0edge
effect_surface_version=1
cli_report_mode=effect-status-report
cli_effect_performed=0
local_operator_effects_present=1
user_local_install_effect_present=1
user_local_copy_effect_present=1
receipt_write_effect_present=1
operator_bundle_write_effect_present=1
effect_boundary=bounded-user-local-or-requested-output-dir
effect_gate=scripted-guarded-path
effect_authority=bounded-local-visible
host_mutation_allowed=0
root_authority_allowed=0
network_allowed=0
kernel_operation_allowed=0
service_operation_allowed=0
package_manager_operation_allowed=0
boot_operation_allowed=0
usb_write_allowed=0
qemu_run_allowed=0
production_readiness_claim=0
EOF

cmp "$expected" "$out"
require_output_field 'cli_effect_performed=0' "$out"
require_output_field 'local_operator_effects_present=1' "$out"
require_output_field 'network_allowed=0' "$out"
require_output_field 'production_readiness_claim=0' "$out"

printf 'latticra_effect_status_surface: ok\n'

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'nadia command surface: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_output_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf '%s\n' "--- output: $file ---" >&2
    sed -n '1,180p' "$file" >&2
    fail "missing required output pattern: $pattern"
  fi
}

ui='installer/latticra-installer/src/ui.rs'
apply='installer/scripts/latticra-installer-apply.sh'
root_readme='README.md'
installer_readme='installer/README.md'
nadia_doc='docs/NADIA_OFFLINE_AI_FOUNDATION.md'

for file in \
  "$ui" \
  "$apply" \
  "$root_readme" \
  "$installer_readme" \
  "$nadia_doc" \
  Makefile
do
  require_file "$file"
done

require_contains 'NADIA_PANEL_COMMANDS' "$ui"
require_contains 'NADIA COMMAND SURFACE' "$ui"
require_contains 'panel_command=nadia commands' "$ui"
require_contains 'installed_wrapper=latticra-nadia commands' "$ui"
require_contains '"prompt-evaluation-result-review"' "$ui"
require_contains 'Stage-36 prompt-evaluation result release receipt review contract' "$ui"
require_contains 'Stage-37 prompt-evaluation result release receipt review disposition contract' "$ui"
require_contains 'Stage-38 prompt-evaluation result release receipt review disposition release contract' "$ui"
require_contains 'prompt-evaluation-result-release' "$ui"
require_contains 'prompt-evaluation-result-release-receipt' "$ui"
require_contains 'prompt-evaluation-result-release-receipt-review' "$ui"
require_contains 'prompt-evaluation-result-release-receipt-review-disposition' "$ui"
require_contains 'prompt-evaluation-result-release-receipt-review-disposition-release' "$ui"
require_contains 'render_nadia_commands()' "$apply"
require_contains 'commands_command=latticra-nadia commands' "$apply"
require_contains 'command=prompt-evaluation-result-disposition stage=33' "$apply"
require_contains 'command=prompt-evaluation-result-release stage=34' "$apply"
require_contains 'command=prompt-evaluation-result-release-receipt stage=35' "$apply"
require_contains 'command=prompt-evaluation-result-release-receipt-review stage=36' "$apply"
require_contains 'command=prompt-evaluation-result-release-receipt-review-disposition stage=37' "$apply"
require_contains 'command=prompt-evaluation-result-release-receipt-review-disposition-release stage=38' "$apply"
require_contains 'usage: latticra-nadia {status|commands|' "$apply"
require_contains 'nadia commands' "$root_readme"
require_contains 'latticra-nadia commands' "$root_readme"
require_contains 'nadia commands' "$installer_readme"
require_contains 'latticra-nadia commands' "$installer_readme"
require_contains 'nadia commands' "$nadia_doc"
require_contains 'latticra nadia commands' "$nadia_doc"
require_contains 'test-nadia-command-surface.sh' Makefile

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-command-surface.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

home="$tmpdir/home"
config="$tmpdir/nadia.installer.toml"
plan="$tmpdir/plan.txt"
receipt_dir="$tmpdir/receipts"
commands_out="$tmpdir/nadia-commands.txt"
help_out="$tmpdir/nadia-help.txt"
via_latticra_out="$tmpdir/latticra-nadia-commands.txt"
status_out="$tmpdir/nadia-status.txt"
mkdir -p "$home"

cat > "$config" <<NADIACONFIG
profile = "developer_local"
install_prefix = "$home/.local/share/latticra"
latticra_console = false
lat_tooling = false
lir_contracts = false
seal_report_only = false
nadia_offline_ai = true
fedora_validation = false
docs_and_examples = false
developer_cli_helpers = false
dry_run = false
allow_host_mutation = true
allow_network_effect = false
require_component_manifest = false
require_artifact_measurements = false
require_verification_policy_metadata = false
write_operator_receipt = true
create_prefix_layout = true
create_component_markers = true
create_cli_shims = true
preserve_existing_files = true
build_gui_installer = false
build_latticra_from_source = false
install_payload_tree = false
install_desktop_entry = false
install_user_bin_wrappers = true
NADIACONFIG

HOME="$home" sh "$apply" \
  --config "$config" \
  --plan "$plan" \
  --receipt-dir "$receipt_dir" > "$tmpdir/install.log"

nadia="$home/.local/bin/latticra-nadia"
latticra="$home/.local/bin/latticra"

[ -x "$nadia" ] || fail "missing executable Nadia wrapper"
[ -x "$latticra" ] || fail "missing executable Latticra wrapper"

HOME="$home" "$nadia" commands > "$commands_out"
HOME="$home" "$nadia" help > "$help_out"
HOME="$home" "$latticra" nadia commands > "$via_latticra_out"
HOME="$home" "$nadia" status > "$status_out"

require_output_contains 'NADIA COMMAND SURFACE' "$commands_out"
require_output_contains 'wrapper=latticra-nadia' "$commands_out"
require_output_contains 'command=status stage=38' "$commands_out"
require_output_contains 'command=context-pack stage=1' "$commands_out"
require_output_contains 'command=prompt-evaluation-result-review stage=32' "$commands_out"
require_output_contains 'command=prompt-evaluation-result-disposition stage=33' "$commands_out"
require_output_contains 'command=prompt-evaluation-result-release stage=34' "$commands_out"
require_output_contains 'command=prompt-evaluation-result-release-receipt stage=35' "$commands_out"
require_output_contains 'command=prompt-evaluation-result-release-receipt-review stage=36' "$commands_out"
require_output_contains 'command=prompt-evaluation-result-release-receipt-review-disposition stage=37' "$commands_out"
require_output_contains 'command=prompt-evaluation-result-release-receipt-review-disposition-release stage=38' "$commands_out"
require_output_contains 'network_authority=0' "$commands_out"
require_output_contains 'tool_execution_authority=0' "$commands_out"
require_output_contains 'runtime_invocation_authority=0' "$commands_out"
require_output_contains 'prompt_evaluation_authority=0' "$commands_out"
require_output_contains 'inference_authority=0' "$commands_out"
require_output_contains 'model_load_authority=0' "$commands_out"
require_output_contains 'source_mutation_authority=0' "$commands_out"
require_output_contains 'commands_command=latticra-nadia commands' "$status_out"

cmp "$commands_out" "$help_out" >/dev/null ||
  fail "latticra-nadia help must match latticra-nadia commands"
cmp "$commands_out" "$via_latticra_out" >/dev/null ||
  fail "latticra nadia commands must match latticra-nadia commands"

printf 'nadia_command_surface: ok\n'

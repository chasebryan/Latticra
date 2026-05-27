#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'installer config authority allowlist: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq -- "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

config_rs="installer/latticra-installer/src/config.rs"
apply_script="installer/scripts/latticra-installer-apply.sh"

require_contains "AUTHORITY_SLUG_MAX_LEN" "$config_rs"
require_contains "COMMAND_WRAPPER_MAX_LEN" "$config_rs"
require_contains "fn validate_authority_slug" "$config_rs"
require_contains "fn validate_authority_fields" "$config_rs"
require_contains "pub fn network_authority_denied(&self)" "$config_rs"
require_contains "fn reject_network_authority(&self)" "$config_rs"
require_contains "self.reject_network_authority()?" "$config_rs"
require_contains "validate_authority_slug(\"LC install profile\"" "$config_rs"
require_contains "LC packages contract profile" "$config_rs"
require_contains "validate_authority_slug(\"Updater update channel\"" "$config_rs"
require_contains "default_authority_labels_pass_slug_validation" "$config_rs"
require_contains "profile_defaults_force_network_authority_floor" "$config_rs"
require_contains "render_plan_reports_network_authority_floor" "$config_rs"
require_contains "installer_rejects_lc_profile_traversal_slug" "$config_rs"
require_contains "installer_rejects_option_like_or_path_like_command_wrappers" "$config_rs"

if grep -Fq 'validate_nonempty_field("LC install profile"' "$config_rs"; then
  fail "$config_rs must validate LC install_profile as an authority slug"
fi

require_contains "valid_authority_slug()" "$apply_script"
require_contains "valid_command_name()" "$apply_script"
require_contains "LC session_contract_profile=\$LC_SESSION_CONTRACT_PROFILE" "$apply_script"
require_contains "LC install_profile=\$LC_INSTALL_PROFILE" "$apply_script"
require_contains "updater update_channel=\$UPDATER_UPDATE_CHANNEL" "$apply_script"
require_contains 'valid_command_name "$LC_INSTALL_COMMAND_WRAPPER"' "$apply_script"

tmp_dir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-installer-config-authority.XXXXXX")"
cleanup() {
  rm -rf "$tmp_dir"
}
trap cleanup EXIT INT HUP TERM

run_rejected_config() {
  name="$1"
  from="$2"
  to="$3"
  expected="$4"
  config="$tmp_dir/$name.toml"
  stdout="$tmp_dir/$name.out"
  stderr="$tmp_dir/$name.err"

  sed "s|$from|$to|" installer/configs/default.installer.toml >"$config"

  if sh "$apply_script" --config "$config" --receipt-dir "$tmp_dir/receipts-$name" >"$stdout" 2>"$stderr"; then
    fail "$name config was accepted unexpectedly"
  fi

  if ! grep -Fq -- "$expected" "$stderr"; then
    sed -n '1,20p' "$stderr" >&2
    fail "$name config did not fail with expected authority allowlist message"
  fi
}

run_rejected_config \
  "bad-lc-session-profile" \
  'session_contract_profile = "lc-session-v0"' \
  'session_contract_profile = "../escape"' \
  "LC session_contract_profile must be an ASCII authority slug"

run_rejected_config \
  "bad-updater-channel" \
  'update_channel = "local-checkout"' \
  'update_channel = "local checkout"' \
  "updater update_channel must be an ASCII authority slug"

run_rejected_config \
  "bad-command-wrapper" \
  'command_wrapper = "latticra-lc"' \
  'command_wrapper = "-latticra"' \
  "LC install command_wrapper must be a single command name"

printf 'installer_config_authority_allowlist: ok\n'

#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

script_dir=$(CDPATH= cd -- "$(dirname "$0")" && pwd)
repo_root=$(CDPATH= cd -- "$script_dir/.." && pwd)

host_override=''
component_manifest_path='installer/manifests/components.toml'
capability_manifest_path='installer/manifests/universal-installer-capabilities.toml'

usage() {
  cat <<'USAGE'
Usage: sh scripts/latticra-universal-installer-preflight.sh [--host HOST] [--component-manifest PATH] [--capability-manifest PATH]

Classifies the current host for a future universal installer and checks that
the installer component manifest declares the runnable Latticra feature set.
This is a no-effect preflight: it performs no install, mutation, network access,
or privilege escalation.
USAGE
}

fail() {
  printf 'latticra universal installer preflight: %s\n' "$1" >&2
  exit 2
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --host)
      [ "$#" -ge 2 ] || fail '--host requires a value'
      host_override="$2"
      shift 2
      ;;
    --component-manifest)
      [ "$#" -ge 2 ] || fail '--component-manifest requires a value'
      component_manifest_path="$2"
      shift 2
      ;;
    --capability-manifest)
      [ "$#" -ge 2 ] || fail '--capability-manifest requires a value'
      capability_manifest_path="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unsupported argument: $1"
      ;;
  esac
done

resolve_path() {
  case "$1" in
    /*) printf '%s\n' "$1" ;;
    *) printf '%s/%s\n' "$repo_root" "$1" ;;
  esac
}

component_manifest=$(resolve_path "$component_manifest_path")
capability_manifest=$(resolve_path "$capability_manifest_path")

if [ -n "$host_override" ]; then
  host_kernel="$host_override"
else
  host_kernel=$(uname -s 2>/dev/null || printf 'unknown')
fi

host_key=$(printf '%s' "$host_kernel" | tr '[:upper:]' '[:lower:]')
host_family='unknown-posix'
local_prefix_install_supported=0
posix_shell_install_supported=0
native_package_lane_present=0
native_package_install_ready=0
os_image_install_ready=0
native_windows_supported=0
windows_wsl_required=0
unsupported_host_blocked=1
next_lane='universal-installer-host-package-selector'

case "$host_key" in
  linux*)
    host_family='linux'
    local_prefix_install_supported=1
    posix_shell_install_supported=1
    native_package_lane_present=1
    unsupported_host_blocked=0
    ;;
  darwin*)
    host_family='macos'
    local_prefix_install_supported=1
    posix_shell_install_supported=1
    native_package_lane_present=1
    unsupported_host_blocked=0
    ;;
  freebsd*)
    host_family='freebsd'
    local_prefix_install_supported=1
    posix_shell_install_supported=1
    native_package_lane_present=1
    unsupported_host_blocked=0
    ;;
  openbsd*)
    host_family='openbsd'
    local_prefix_install_supported=1
    posix_shell_install_supported=1
    native_package_lane_present=1
    unsupported_host_blocked=0
    ;;
  netbsd*)
    host_family='netbsd'
    local_prefix_install_supported=1
    posix_shell_install_supported=1
    native_package_lane_present=1
    unsupported_host_blocked=0
    ;;
  sunos*|illumos*)
    host_family='solaris'
    local_prefix_install_supported=1
    posix_shell_install_supported=1
    native_package_lane_present=0
    unsupported_host_blocked=0
    ;;
  msys*|mingw*|cygwin*|windows*)
    host_family='windows-compat-shell'
    windows_wsl_required=1
    ;;
esac

file_present() {
  if [ -f "$1" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

component_count() {
  [ -f "$component_manifest" ] || {
    printf '0\n'
    return
  }
  awk '/^\[components\.[^]]+\]/{ count++ } END { print count + 0 }' "$component_manifest"
}

default_enabled_count() {
  [ -f "$component_manifest" ] || {
    printf '0\n'
    return
  }
  awk '
    /^\[components\.[^]]+\]/ { in_component = 1; next }
    /^\[/ { in_component = 0; next }
    in_component && /^[[:space:]]*default_enabled[[:space:]]*=[[:space:]]*true[[:space:]]*$/ { count++ }
    END { print count + 0 }
  ' "$component_manifest"
}

component_declared() {
  [ -f "$component_manifest" ] || {
    printf '0\n'
    return
  }
  if grep -Fq "[components.$1]" "$component_manifest"; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

component_default_enabled() {
  [ -f "$component_manifest" ] || {
    printf '0\n'
    return
  }
  awk -v name="$1" '
    $0 == "[components." name "]" { in_target = 1; found = 1; next }
    /^\[/ { if (in_target) in_target = 0; next }
    in_target && /^[[:space:]]*default_enabled[[:space:]]*=[[:space:]]*true[[:space:]]*$/ { enabled = 1 }
    END {
      if (found && enabled) {
        print 1
      } else {
        print 0
      }
    }
  ' "$component_manifest"
}

required_feature_components='latticra_console lat_tooling lir_contracts seal_report_only nadia_offline_ai fedora_validation docs_and_examples developer_cli_helpers'
default_safe_components='latticra_console lat_tooling lir_contracts seal_report_only docs_and_examples developer_cli_helpers'

feature_components_declared_count=0
all_feature_components_declared=1
feature_component_lines=''

for component in $required_feature_components; do
  declared=$(component_declared "$component")
  feature_component_lines="${feature_component_lines}component_${component}_declared=$declared
"
  if [ "$declared" -eq 1 ]; then
    feature_components_declared_count=$((feature_components_declared_count + 1))
  else
    all_feature_components_declared=0
  fi
done

default_safe_components_enabled_count=0
all_default_safe_components_enabled=1
default_component_lines=''

for component in $default_safe_components; do
  enabled=$(component_default_enabled "$component")
  default_component_lines="${default_component_lines}component_${component}_default_enabled=$enabled
"
  if [ "$enabled" -eq 1 ]; then
    default_safe_components_enabled_count=$((default_safe_components_enabled_count + 1))
  else
    all_default_safe_components_enabled=0
  fi
done

optional_ai_component_declared=$(component_declared 'nadia_offline_ai')
optional_ai_default_enabled=$(component_default_enabled 'nadia_offline_ai')
optional_fedora_validation_component_declared=$(component_declared 'fedora_validation')
optional_fedora_validation_default_enabled=$(component_default_enabled 'fedora_validation')

printf '%s\n' \
  'LATTICRA UNIVERSAL INSTALLER PREFLIGHT' \
  'universal_installer_preflight_present=1' \
  'universal_installer_preflight_version=1' \
  'preflight_mode=no-effect-cross-platform-classifier' \
  "host_os_kernel=$host_kernel" \
  "host_os_family=$host_family" \
  "posix_shell_install_supported=$posix_shell_install_supported" \
  "local_prefix_install_supported=$local_prefix_install_supported" \
  "native_package_lane_present=$native_package_lane_present" \
  "native_package_install_ready=$native_package_install_ready" \
  "os_image_install_ready=$os_image_install_ready" \
  "native_windows_supported=$native_windows_supported" \
  "windows_wsl_required=$windows_wsl_required" \
  "unsupported_host_blocked=$unsupported_host_blocked" \
  "component_manifest_path=$component_manifest_path" \
  "component_manifest_present=$(file_present "$component_manifest")" \
  "capability_manifest_path=$capability_manifest_path" \
  "capability_manifest_present=$(file_present "$capability_manifest")" \
  "components_total=$(component_count)" \
  "components_default_enabled=$(default_enabled_count)" \
  "feature_components_required=8" \
  "feature_components_declared_count=$feature_components_declared_count" \
  "all_feature_components_declared=$all_feature_components_declared"

printf '%s' "$feature_component_lines"

printf '%s\n' \
  "default_safe_components_required=6" \
  "default_safe_components_enabled_count=$default_safe_components_enabled_count" \
  "all_default_safe_components_enabled=$all_default_safe_components_enabled"

printf '%s' "$default_component_lines"

printf '%s\n' \
  "optional_ai_component_declared=$optional_ai_component_declared" \
  "optional_ai_default_enabled=$optional_ai_default_enabled" \
  "optional_fedora_validation_component_declared=$optional_fedora_validation_component_declared" \
  "optional_fedora_validation_default_enabled=$optional_fedora_validation_default_enabled" \
  'network_required=0' \
  'root_required=0' \
  'install_performed=0' \
  'host_mutation_performed=0' \
  'production_installer_ready=0' \
  'comprehensive_installer_ready=0' \
  "next_lane=$next_lane"

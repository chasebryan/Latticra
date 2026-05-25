#!/usr/bin/env sh
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-installer-apply.sh --config <file> [--plan <file>] [--receipt-dir <dir>]

This is the real guarded Latticra Panel user-local install engine.
It installs only under the configured user-local prefix and ~/.local/bin.
It does not require root, change the kernel, change systemd, change SELinux, or use the network.
USAGE
}

CONFIG=""
PLAN=""
RECEIPT_DIR=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --config)
      [ "$#" -ge 2 ] || { echo "missing value for --config" >&2; exit 64; }
      CONFIG="$2"
      shift 2
      ;;
    --plan)
      [ "$#" -ge 2 ] || { echo "missing value for --plan" >&2; exit 64; }
      PLAN="$2"
      shift 2
      ;;
    --receipt-dir)
      [ "$#" -ge 2 ] || { echo "missing value for --receipt-dir" >&2; exit 64; }
      RECEIPT_DIR="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "unknown argument: $1" >&2
      usage >&2
      exit 64
      ;;
  esac
done

[ -n "$CONFIG" ] || { echo "--config is required" >&2; exit 64; }
[ -f "$CONFIG" ] || { echo "config not found: $CONFIG" >&2; exit 66; }

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
INSTALLER_ROOT=$(CDPATH= cd -- "$SCRIPT_DIR/.." && pwd)
REPO_ROOT=$(CDPATH= cd -- "$INSTALLER_ROOT/.." && pwd)
MANIFEST="$INSTALLER_ROOT/manifests/components.toml"

if [ -z "$RECEIPT_DIR" ]; then
  RECEIPT_DIR="$INSTALLER_ROOT/latticra-installer-receipts"
fi

if [ -z "$PLAN" ]; then
  PLAN="$RECEIPT_DIR/latticra-installer-plan.txt"
fi

TOTAL_PHASES=10

phase() {
  printf 'PHASE %s/%s: %s\n' "$1" "$TOTAL_PHASES" "$2"
}

fail() {
  printf 'ERROR: %s\n' "$1" >&2
  exit "${2:-1}"
}

log() {
  printf '%s\n' "$*"
}

toml_get() {
  key="$1"
  awk -F '=' -v key="$key" '
    /^[[:space:]]*#/ { next }
    /^[[:space:]]*\[/ { next }
    {
      left = $1
      gsub(/^[ \t]+|[ \t]+$/, "", left)
      if (left == key) {
        val = $2
        for (i = 3; i <= NF; i++) val = val "=" $i
        sub(/[ \t]+#.*/, "", val)
        gsub(/^[ \t]+|[ \t]+$/, "", val)
        gsub(/^"/, "", val)
        gsub(/"$/, "", val)
        print val
        exit
      }
    }
  ' "$CONFIG"
}

cfg() {
  key="$1"
  default="$2"
  value=$(toml_get "$key" || true)
  if [ -n "$value" ]; then
    printf '%s\n' "$value"
  else
    printf '%s\n' "$default"
  fi
}

toml_get_section() {
  section="$1"
  key="$2"
  awk -F '=' -v section="$section" -v key="$key" '
    /^[[:space:]]*#/ { next }
    /^[[:space:]]*\[/ {
      current = $0
      sub(/^[[:space:]]*\[/, "", current)
      sub(/\][[:space:]]*$/, "", current)
      in_section = (current == section)
      next
    }
    in_section {
      left = $1
      gsub(/^[ \t]+|[ \t]+$/, "", left)
      if (left == key) {
        val = $2
        for (i = 3; i <= NF; i++) val = val "=" $i
        sub(/[ \t]+#.*/, "", val)
        gsub(/^[ \t]+|[ \t]+$/, "", val)
        gsub(/^"/, "", val)
        gsub(/"$/, "", val)
        print val
        exit
      }
    }
  ' "$CONFIG"
}

cfg_section() {
  section="$1"
  key="$2"
  default="$3"
  value=$(toml_get_section "$section" "$key" || true)
  if [ -n "$value" ]; then
    printf '%s\n' "$value"
  else
    printf '%s\n' "$default"
  fi
}

bool_true() {
  case "${1:-false}" in
    true|1|yes|on) return 0 ;;
    *) return 1 ;;
  esac
}

bool01() {
  if bool_true "$1"; then printf '1\n'; else printf '0\n'; fi
}

expand_prefix() {
  raw="$1"
  case "$raw" in
    "~") printf '%s\n' "$HOME" ;;
    "~/"*) printf '%s/%s\n' "$HOME" "${raw#\~/}" ;;
    *) printf '%s\n' "$raw" ;;
  esac
}

measure_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    cksum "$file" | awk '{ print "cksum:" $1 ":" $2 }'
  fi
}

path_has_parent_reference() {
  case "$1" in
    ..|../*|*/..|*/../*) return 0 ;;
    *) return 1 ;;
  esac
}

prefix_is_allowed_user_local() {
  candidate="$1"
  home_real=$(canonical_existing_path "$HOME")

  case "$candidate" in
    "$HOME"/.local/share/latticra|"$HOME"/.local/share/latticra/*|"$HOME"/.local/share/latticra-validation|"$HOME"/.local/share/latticra-validation/*)
      return 0
      ;;
    "$home_real"/.local/share/latticra|"$home_real"/.local/share/latticra/*|"$home_real"/.local/share/latticra-validation|"$home_real"/.local/share/latticra-validation/*)
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

safe_prefix_guard() {
  prefix="$1"
  [ -n "$prefix" ] || fail "resolved install prefix is empty" 73

  case "$prefix" in
    /*) ;;
    *) fail "resolved install prefix must be absolute: $prefix" 73 ;;
  esac

  if path_has_parent_reference "$prefix"; then
    fail "refusing install prefix with parent-directory traversal: $prefix" 73
  fi

  if [ -L "$prefix" ]; then
    fail "refusing symlink install prefix: $prefix" 73
  fi

  case "$prefix" in
    /|/usr|/usr/*|/bin|/bin/*|/sbin|/sbin/*|/etc|/etc/*|/boot|/boot/*|/var|/var/lib|/var/lib/*|/System|/System/*|/Library|/Library/*)
      fail "refusing unsafe system prefix: $prefix" 73
      ;;
  esac

  prefix_real=$(canonical_existing_path "$prefix")
  if path_has_parent_reference "$prefix_real"; then
    fail "refusing install prefix with parent-directory traversal: $prefix" 73
  fi

  case "$prefix_real" in
    /|/usr|/usr/*|/bin|/bin/*|/sbin|/sbin/*|/etc|/etc/*|/boot|/boot/*|/var|/var/lib|/var/lib/*|/System|/System/*|/Library|/Library/*)
      fail "refusing unsafe system prefix: $prefix" 73
      ;;
  esac

  prefix_is_allowed_user_local "$prefix" &&
    prefix_is_allowed_user_local "$prefix_real" ||
    fail "installer only allows Latticra user-local prefixes under $HOME/.local/share/latticra* : $prefix" 73
}

write_file() {
  target="$1"
  mode="$2"
  mkdir -p "$(dirname -- "$target")"
  if [ -L "$target" ]; then
    fail "refusing to overwrite symlink file: $target" 74
  fi
  cat > "$target"
  chmod "$mode" "$target"
  log "[write] $target"
}

write_managed_file() {
  target="$1"
  mode="$2"
  mkdir -p "$(dirname -- "$target")"
  tmp=$(mktemp "$(dirname -- "$target")/.latticra-installer.$(basename -- "$target").XXXXXX") ||
    fail "could not create temporary managed file for: $target" 74
  cat > "$tmp"
  if [ -L "$target" ]; then
    rm -f "$tmp"
    fail "refusing to overwrite symlink managed file: $target" 74
  fi
  if [ -e "$target" ] && ! grep -q 'LATTICRA_INSTALLER_MANAGED=1' "$target" 2>/dev/null; then
    rm -f "$tmp"
    fail "refusing to overwrite unmanaged file: $target" 74
  fi
  mv "$tmp" "$target"
  chmod "$mode" "$target"
  log "[write-managed] $target"
}

canonical_existing_path() {
  path="$1"
  dir=$(dirname -- "$path")
  base=$(basename -- "$path")
  if cd -- "$dir" 2>/dev/null; then
    printf '%s/%s\n' "$(pwd -P)" "$base"
  else
    printf '%s\n' "$path"
  fi
}

copy_if_exists() {
  src="$1"
  dest_dir="$2"
  if [ -e "$src" ]; then
    mkdir -p "$dest_dir"
    base=$(basename -- "$src")
    dest="$dest_dir/$base"

    src_real=$(canonical_existing_path "$src")
    dest_real=$(canonical_existing_path "$dest")

    if [ "$src_real" = "$dest_real" ]; then
      log "[preserve] $src already exists at install destination"
      return 0
    fi

    rm -rf "$dest"
    cp -R "$src" "$dest_dir/"
    log "[copy] $src -> $dest"
  fi
}

install_built_executables_from_dir() {
  srcdir="$1"
  [ -d "$srcdir" ] || return 0
  find "$srcdir" -maxdepth 1 -type f -perm -111 2>/dev/null | while IFS= read -r exe; do
    name=$(basename -- "$exe")
    case "$name" in
      build-script-*|deps|examples|incremental|*.d|*.rlib|*.rmeta) continue ;;
    esac
    cp "$exe" "$PREFIX/bin/$name"
    chmod 0755 "$PREFIX/bin/$name"
    log "[binary] $PREFIX/bin/$name"
  done
}

write_component_marker() {
  marker="$1"
  component="$2"
  write_file "$marker" 0644 <<MARKER
component=$component
profile=$PROFILE
mode=$MODE
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0
MARKER
}

PROFILE=$(cfg profile custom)
INSTALL_PREFIX_RAW=$(cfg install_prefix '~/.local/share/latticra')
DRY_RUN=$(cfg dry_run true)
ALLOW_HOST_MUTATION=$(cfg allow_host_mutation false)
ALLOW_NETWORK_EFFECT=$(cfg allow_network_effect false)
REQUIRE_COMPONENT_MANIFEST=$(cfg require_component_manifest true)
REQUIRE_ARTIFACT_MEASUREMENTS=$(cfg require_artifact_measurements true)
REQUIRE_VERIFICATION_POLICY_METADATA=$(cfg require_verification_policy_metadata true)
WRITE_OPERATOR_RECEIPT=$(cfg write_operator_receipt true)

LATTICRA_CONSOLE=$(cfg latticra_console true)
LAT_TOOLING=$(cfg lat_tooling true)
LIR_CONTRACTS=$(cfg lir_contracts true)
SEAL_REPORT_ONLY=$(cfg seal_report_only true)
NADIA_OFFLINE_AI=$(cfg nadia_offline_ai false)
FEDORA_VALIDATION=$(cfg fedora_validation false)
DOCS_AND_EXAMPLES=$(cfg docs_and_examples true)
DEVELOPER_CLI_HELPERS=$(cfg developer_cli_helpers true)

LC_PROFILE=$(cfg_section lc profile panel_embedded)
LC_COMMAND_REGISTRY_PROFILE=$(cfg_section lc command_registry_profile c-static-table)
LC_SUBSTRATE_BRIDGE_PROFILE=$(cfg_section lc substrate_bridge_profile metadata-bound)
LC_HOST_EMBEDDING_PROFILE=$(cfg_section lc host_embedding_profile panel-contained)
LC_HOST_EMBEDDING_CONTRACT_PROFILE=$(cfg_section lc host_embedding_contract_profile lc-host-embedding-v0)
LC_HOST_INVENTORY_CONTRACT_PROFILE=$(cfg_section lc host_inventory_contract_profile lc-host-inventory-v0)
LC_OS_BASE_PROFILE=$(cfg_section lc os_base_profile planned-no-boot-authority)
LC_PANEL_BRIDGE=$(cfg_section lc panel_bridge panel-aware)
LC_REPORT_ONLY=$(cfg_section lc report_only true)
LC_REQUIRE_HOST_EMBEDDING_CONTRACT=$(cfg_section lc require_host_embedding_contract true)
LC_REQUIRE_READ_ONLY_HOST_INVENTORY_CONTRACT=$(cfg_section lc require_read_only_host_inventory_contract true)
LC_REQUIRE_RUNTIME_BOUNDARY_BINDING=$(cfg_section lc require_runtime_boundary_binding true)
LC_REQUIRE_SEAL_CAPABILITY_LABELS=$(cfg_section lc require_seal_capability_labels true)

CREATE_PREFIX_LAYOUT=$(cfg create_prefix_layout true)
CREATE_COMPONENT_MARKERS=$(cfg create_component_markers true)
CREATE_CLI_SHIMS=$(cfg create_cli_shims true)
PRESERVE_EXISTING_FILES=$(cfg preserve_existing_files true)

BUILD_GUI_INSTALLER=$(cfg build_gui_installer true)
BUILD_LATTICRA_FROM_SOURCE=$(cfg build_latticra_from_source true)
INSTALL_PAYLOAD_TREE=$(cfg install_payload_tree true)
INSTALL_DESKTOP_ENTRY=$(cfg install_desktop_entry true)
INSTALL_USER_BIN_WRAPPERS=$(cfg install_user_bin_wrappers true)

PREFIX=$(expand_prefix "$INSTALL_PREFIX_RAW")
USER_BIN="$HOME/.local/bin"
PAYLOAD_DIR="$PREFIX/lib/latticra"
RECEIPTS_IN_PREFIX="$PREFIX/share/latticra/receipts"
TS=$(date -u +"%Y%m%dT%H%M%SZ")

if bool_true "$DRY_RUN"; then
  MODE="dry-install"
else
  MODE="local-prefix-install"
fi

phase 1 "validate installer configuration"

if ! bool_true "$DRY_RUN" && ! bool_true "$ALLOW_HOST_MUTATION"; then
  fail "real install requested, but allow_host_mutation is false" 77
fi

if bool_true "$ALLOW_NETWORK_EFFECT"; then
  fail "network authority is not implemented in this installer" 78
fi

phase 2 "load component manifest"

if bool_true "$REQUIRE_COMPONENT_MANIFEST" && [ ! -f "$MANIFEST" ]; then
  fail "required component manifest missing: $MANIFEST" 66
fi

phase 3 "resolve and guard install prefix"

safe_prefix_guard "$PREFIX"

phase 4 "generate install plan"

mkdir -p "$(dirname -- "$PLAN")"
cat > "$PLAN" <<PLANFILE
LATTICRA INSTALLER PLAN

timestamp_utc=$TS
repo_root=$REPO_ROOT
installer_root=$INSTALLER_ROOT
config=$CONFIG
profile=$PROFILE
mode=$MODE
install_prefix=$PREFIX
user_bin=$USER_BIN
payload_dir=$PAYLOAD_DIR
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0

[components]
latticra_console=$LATTICRA_CONSOLE
lat_tooling=$LAT_TOOLING
lir_contracts=$LIR_CONTRACTS
seal_report_only=$SEAL_REPORT_ONLY
nadia_offline_ai=$NADIA_OFFLINE_AI
fedora_validation=$FEDORA_VALIDATION
docs_and_examples=$DOCS_AND_EXAMPLES
developer_cli_helpers=$DEVELOPER_CLI_HELPERS

[lc]
component_key=latticra_console
console_name=Latticra Console
short_name=LC
component_selected=$LATTICRA_CONSOLE
configurable=1
panel_installable=1
profile=$LC_PROFILE
panel_console_bridge=$LC_PANEL_BRIDGE
command_registry_profile=$LC_COMMAND_REGISTRY_PROFILE
substrate_bridge_profile=$LC_SUBSTRATE_BRIDGE_PROFILE
host_embedding_profile=$LC_HOST_EMBEDDING_PROFILE
host_embedding_contract_profile=$LC_HOST_EMBEDDING_CONTRACT_PROFILE
host_inventory_contract_profile=$LC_HOST_INVENTORY_CONTRACT_PROFILE
os_base_profile=$LC_OS_BASE_PROFILE
report_only=$LC_REPORT_ONLY
host_embedding_contract_required=$LC_REQUIRE_HOST_EMBEDDING_CONTRACT
read_only_host_inventory_contract_required=$LC_REQUIRE_READ_ONLY_HOST_INVENTORY_CONTRACT
runtime_boundary_binding_required=$LC_REQUIRE_RUNTIME_BOUNDARY_BINDING
seal_capability_labels_required=$LC_REQUIRE_SEAL_CAPABILITY_LABELS
command_registry_status=seed-registry
substrate_bridge_status=$LC_SUBSTRATE_BRIDGE_PROFILE
host_embedding_status=$LC_HOST_EMBEDDING_PROFILE
host_embedding_contract_status=metadata-only-contract
host_inventory_contract_status=metadata-only-contract
os_base_status=$LC_OS_BASE_PROFILE
operator_shell_present=1
execution_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
future_os_base_claim=planned_not_claimed

[nadia]
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=26-prompt-token-sequence-contract
component_selected=$NADIA_OFFLINE_AI
context_engine_stage=1-local-context-engine
context_pack_command=scripts/nadia-context-pack.sh
installed_context_pack_command=latticra-nadia context-pack
local_file_read_for_indexing=operator_invoked
runtime_profile_stage=2-runtime-profile-boundary
runtime_profile_command=scripts/nadia-runtime-profile.sh
installed_runtime_profile_command=latticra-nadia runtime-profile
runtime_family=llama.cpp-compatible
model_format=gguf
developer_workbench_stage=3-developer-workbench-planning
prompt_plan_command=scripts/nadia-prompt-plan.sh
installed_prompt_plan_command=latticra-nadia prompt-plan
systems_engineering_mode_stage=4-systems-engineering-mode-validation
mode_validation_command=scripts/nadia-mode-validate.sh
installed_mode_validation_command=latticra-nadia mode-validate
mode_taxonomy_present=1
productivity_loop_stage=5-productivity-ledger-loop
productivity_ledger_command=scripts/nadia-productivity-ledger.sh
installed_productivity_ledger_command=latticra-nadia productivity-ledger
learning_scope=operator-reviewed-local-productivity
ledger_append_only=1
protective_safety_stage=6-protective-safety-boundary
protective_safety_command=scripts/nadia-protective-safety-boundary.sh
installed_protective_safety_command=latticra-nadia protective-safety
absolute_protective_boundary=1
sexual_user_request_authority=0
sexual_content_generation=0
sexual_roleplay_authority=0
sexualized_namesake_or_survivor_content=0
sexual_request_refusal=always
user_override_authority=0
prompt_injection_override_authority=0
manipulation_resistance=required
policy_bypass_authority=0
namesake_cause_awareness=1
tool_authority_stage=7-guarded-tool-authority-preflight
tool_authority_preflight_command=scripts/nadia-tool-authority-preflight.sh
installed_tool_authority_preflight_command=latticra-nadia tool-preflight
preflight_decision=report_only_no_execution
tool_execution_performed=0
tool_selection_authority=0
shell_execution_authority=0
network_tool_authority=0
destructive_action_authority=0
credential_access_authority=0
requires_operator_approval=1
requires_nucleus_gate=1
requires_runtime_boundary_gate=1
requires_seal_receipt=1
requires_protective_safety_boundary=1
authority_transition_allowed=0
prompt_evaluation_contract_stage=8-prompt-evaluation-contract
prompt_evaluation_contract_command=scripts/nadia-prompt-evaluation-contract.sh
installed_prompt_evaluation_contract_command=latticra-nadia prompt-contract
prompt_contract_status=contract_only
prompt_evaluation_stage=contract-only
prompt_materialized=0
prompt_text_materialized=0
prompt_evaluation_authority=0
prompt_receipt_required=1
refusal_policy_required=1
protective_safety_required=1
tool_preflight_required=1
runtime_profile_required=1
model_registry_review_required=1
operator_review_required=1
contract_promotion_allowed=0
local_model_registry_contract_stage=9-local-model-registry-contract
model_registry_contract_command=scripts/nadia-local-model-registry-contract.sh
installed_model_registry_contract_command=latticra-nadia model-registry
local_model_registry_stage=contract-only
registry_contract_status=metadata_only
model_registry_authority=0
requires_prompt_contract=1
candidate_review_status=operator_review_required
candidate_usable_for_inference=0
candidate_selected_for_runtime=0
model_selection_authority=0
model_install_authority=0
model_download_authority=0
model_copy_authority=0
model_load_authority=0
model_benchmark_authority=0
model_weight_inspection_authority=0
registry_promotion_allowed=0
inference_readiness_contract_stage=10-inference-readiness-contract
inference_readiness_contract_command=scripts/nadia-inference-readiness-contract.sh
installed_inference_readiness_contract_command=latticra-nadia inference-readiness
inference_readiness_stage=contract-only
inference_readiness_contract_status=contract_only
inference_readiness_authority=0
inference_ready=0
readiness_decision=blocked_contract_only
readiness_evidence_present=1
requires_model_registry_contract=1
requires_future_runtime_invocation_contract=1
readiness_promotion_allowed=0
runtime_invocation_authority=0
token_generation_authority=0
model_session_authority=0
runtime_invocation_contract_stage=11-runtime-invocation-contract
runtime_invocation_contract_command=scripts/nadia-runtime-invocation-contract.sh
installed_runtime_invocation_contract_command=latticra-nadia runtime-invocation
runtime_invocation_stage=contract-only
runtime_invocation_contract_status=contract_only
runtime_invocation_allowed=0
invocation_decision=blocked_contract_only
invocation_evidence_present=1
requires_inference_readiness_contract=1
requires_future_model_load_contract=1
invocation_promotion_allowed=0
runtime_process_spawn_authority=0
runtime_binary_execution_authority=0
runtime_session_authority=0
runtime_process_spawned=0
runtime_binary_executed=0
runtime_session_created=0
token_generation_performed=0
model_load_contract_stage=12-model-load-contract
model_load_contract_command=scripts/nadia-model-load-contract.sh
installed_model_load_contract_command=latticra-nadia model-load
model_load_stage=contract-only
model_load_contract_status=contract_only
model_load_authority=0
model_load_allowed=0
model_loaded=0
load_decision=blocked_contract_only
load_evidence_present=1
requires_runtime_invocation_contract=1
requires_model_weight_measurement_contract=1
requires_future_prompt_receipt_contract=1
load_promotion_allowed=0
model_file_open_authority=0
model_weight_read_authority=0
model_weight_mapping_authority=0
model_weight_verification_authority=0
runtime_model_attach_authority=0
model_file_opened=0
model_file_descriptor_opened=0
model_memory_map_created=0
model_weights_mapped=0
model_weights_attached=0
model_weight_measurement_performed=0
model_weight_verification_performed=0
model_load_performed=0
prompt_receipt_contract_stage=13-prompt-receipt-contract
prompt_receipt_contract_command=scripts/nadia-prompt-receipt-contract.sh
installed_prompt_receipt_contract_command=latticra-nadia prompt-receipt
prompt_receipt_stage=contract-only
prompt_receipt_contract_status=contract_only
prompt_receipt_authority=0
prompt_receipt_allowed=0
prompt_received=0
receipt_decision=blocked_contract_only
receipt_evidence_present=1
requires_model_load_contract=1
requires_prompt_source_boundary=1
requires_future_prompt_materialization_contract=1
prompt_receipt_promotion_allowed=0
prompt_source_open_authority=0
prompt_source_read_authority=0
prompt_text_materialization_authority=0
prompt_content_storage_authority=0
prompt_hash_authority=0
prompt_classification_authority=0
prompt_source_opened=0
prompt_source_read=0
prompt_bytes_read=0
prompt_text_received=0
prompt_text_materialized=0
prompt_content_stored=0
prompt_hash_computed=0
prompt_classified=0
prompt_materialization_contract_stage=14-prompt-materialization-contract
prompt_materialization_contract_command=scripts/nadia-prompt-materialization-contract.sh
installed_prompt_materialization_contract_command=latticra-nadia prompt-materialization
prompt_materialization_stage=contract-only
prompt_materialization_contract_status=contract_only
prompt_materialization_authority=0
prompt_materialization_allowed=0
prompt_materialized=0
materialization_decision=blocked_contract_only
materialization_evidence_present=1
requires_prompt_receipt_contract=1
requires_prompt_buffer_boundary=1
requires_future_prompt_evaluation_handoff_contract=1
prompt_materialization_promotion_allowed=0
prompt_buffer_allocation_authority=0
prompt_buffer_write_authority=0
prompt_tokenization_authority=0
prompt_materialization_performed=0
prompt_buffer_allocated=0
prompt_buffer_written=0
prompt_bytes_materialized=0
prompt_tokens_created=0
prompt_tokenized=0
awareness_dialogue_contract_stage=15-awareness-dialogue-contract
awareness_dialogue_contract_command=scripts/nadia-awareness-dialogue-contract.sh
installed_awareness_dialogue_contract_command=latticra-nadia awareness-dialogue
future_qa_dialogue_capability_planned=1
awareness_dialogue_stage=contract-only
awareness_dialogue_contract_status=contract_only
awareness_dialogue_authority=0
awareness_dialogue_allowed=0
dialogue_generation_authority=0
dialogue_generation_allowed=0
qa_dialogue_generated=0
dialogue_scope=official-nadia-initiative-awareness-work
dialogue_format=question-and-answer
q_and_a_format_required=1
survivor_centered_dialogue_required=1
official_source_grounding_required=1
live_web_lookup_authority=0
topic_yazidi_genocide_awareness=1
topic_survivor_voice_and_dignity=1
topic_conflict_related_sexual_violence_awareness_non_graphic=1
topic_genocide_prevention=1
topic_justice_and_accountability=1
topic_sinjar_reconstruction=1
topic_womens_empowerment=1
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
prompt_evaluation_handoff_contract_stage=16-prompt-evaluation-handoff-contract
prompt_evaluation_handoff_contract_command=scripts/nadia-prompt-evaluation-handoff-contract.sh
installed_prompt_evaluation_handoff_contract_command=latticra-nadia prompt-evaluation-handoff
prompt_evaluation_handoff_stage=contract-only
prompt_evaluation_handoff_contract_status=contract_only
prompt_evaluation_handoff_authority=0
prompt_evaluation_handoff_allowed=0
prompt_evaluation_handoff_performed=0
evaluation_handoff_decision=blocked_contract_only
requires_awareness_dialogue_contract=1
requires_future_tokenization_contract=1
prompt_evaluation_handoff_promotion_allowed=0
tokenization_boundary_contract_stage=17-tokenization-boundary-contract
tokenization_boundary_contract_command=scripts/nadia-tokenization-boundary-contract.sh
installed_tokenization_boundary_contract_command=latticra-nadia tokenization-boundary
tokenization_boundary_stage=contract-only
tokenization_boundary_contract_status=contract_only
tokenization_boundary_authority=0
tokenization_boundary_allowed=0
tokenization_boundary_performed=0
prompt_tokenization_allowed=0
prompt_tokenized=0
prompt_tokens_created=0
tokenizer_file_opened=0
tokenizer_vocab_loaded=0
tokenization_decision=blocked_contract_only
requires_prompt_evaluation_handoff_contract=1
requires_future_tokenizer_specification_contract=1
tokenization_boundary_promotion_allowed=0
tokenizer_specification_contract_stage=18-tokenizer-specification-contract
tokenizer_specification_contract_command=scripts/nadia-tokenizer-specification-contract.sh
installed_tokenizer_specification_contract_command=latticra-nadia tokenizer-specification
tokenizer_specification_stage=contract-only
tokenizer_specification_contract_status=contract_only
tokenizer_specification_authority=0
tokenizer_specification_allowed=0
tokenizer_specification_performed=0
tokenizer_specification_metadata_present=1
tokenizer_family=model-compatible-tokenizer
tokenizer_format=operator-reviewed-offline-specification
tokenizer_specification_decision=blocked_contract_only
tokenizer_path_recorded=0
tokenizer_manifest_loaded=0
requires_tokenization_boundary_contract=1
requires_future_tokenizer_manifest_contract=1
tokenizer_specification_promotion_allowed=0
tokenizer_manifest_contract_stage=19-tokenizer-manifest-contract
tokenizer_manifest_contract_command=scripts/nadia-tokenizer-manifest-contract.sh
installed_tokenizer_manifest_contract_command=latticra-nadia tokenizer-manifest
tokenizer_manifest_stage=contract-only
tokenizer_manifest_contract_status=contract_only
tokenizer_manifest_authority=0
tokenizer_manifest_allowed=0
tokenizer_manifest_performed=0
tokenizer_manifest_metadata_present=1
tokenizer_manifest_family=operator-reviewed-tokenizer-manifest
tokenizer_manifest_format=contract-only-offline-manifest
tokenizer_manifest_decision=blocked_contract_only
tokenizer_manifest_path_recorded=0
tokenizer_manifest_schema_planned=1
tokenizer_manifest_opened=0
tokenizer_manifest_read=0
tokenizer_manifest_parsed=0
tokenizer_manifest_validated=0
tokenizer_manifest_loaded=0
requires_tokenizer_specification_contract=1
requires_future_tokenizer_artifact_inventory_contract=1
tokenizer_manifest_promotion_allowed=0
tokenizer_artifact_inventory_contract_stage=20-tokenizer-artifact-inventory-contract
tokenizer_artifact_inventory_contract_command=scripts/nadia-tokenizer-artifact-inventory-contract.sh
installed_tokenizer_artifact_inventory_contract_command=latticra-nadia tokenizer-artifact-inventory
tokenizer_artifact_inventory_stage=contract-only
tokenizer_artifact_inventory_contract_status=contract_only
tokenizer_artifact_inventory_authority=0
tokenizer_artifact_inventory_allowed=0
tokenizer_artifact_inventory_performed=0
tokenizer_artifact_inventory_metadata_present=1
tokenizer_artifact_inventory_family=operator-reviewed-tokenizer-artifact-inventory
tokenizer_artifact_inventory_format=contract-only-offline-inventory
tokenizer_artifact_inventory_decision=blocked_contract_only
tokenizer_artifact_inventory_path_recorded=0
tokenizer_artifact_inventory_schema_planned=1
tokenizer_artifact_inventory_entry_count=0
tokenizer_artifact_inventory_file_count=0
tokenizer_artifact_path_resolved=0
tokenizer_artifact_scan_performed=0
tokenizer_artifact_stat_performed=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_hash_computed=0
tokenizer_artifact_measurement_performed=0
requires_tokenizer_manifest_contract=1
requires_future_tokenizer_artifact_measurement_contract=1
tokenizer_artifact_inventory_promotion_allowed=0
tokenizer_artifact_measurement_contract_stage=21-tokenizer-artifact-measurement-contract
tokenizer_artifact_measurement_contract_command=scripts/nadia-tokenizer-artifact-measurement-contract.sh
installed_tokenizer_artifact_measurement_contract_command=latticra-nadia tokenizer-artifact-measurement
tokenizer_artifact_measurement_stage=contract-only
tokenizer_artifact_measurement_contract_status=contract_only
tokenizer_artifact_measurement_authority=0
tokenizer_artifact_measurement_allowed=0
tokenizer_artifact_measurement_performed=0
tokenizer_artifact_measurement_metadata_present=1
tokenizer_artifact_measurement_family=operator-reviewed-tokenizer-artifact-measurement
tokenizer_artifact_measurement_format=contract-only-offline-measurement
tokenizer_artifact_measurement_decision=blocked_contract_only
tokenizer_artifact_measurement_plan_recorded=1
tokenizer_artifact_measurement_result_recorded=0
tokenizer_artifact_measurement_digest_recorded=0
tokenizer_artifact_measurement_size_recorded=0
tokenizer_artifact_measurement_hash_computed=0
requires_tokenizer_artifact_inventory_contract=1
requires_future_tokenizer_artifact_verification_contract=1
tokenizer_artifact_measurement_promotion_allowed=0
tokenizer_artifact_verification_contract_stage=22-tokenizer-artifact-verification-contract
tokenizer_artifact_verification_contract_command=scripts/nadia-tokenizer-artifact-verification-contract.sh
installed_tokenizer_artifact_verification_contract_command=latticra-nadia tokenizer-artifact-verification
tokenizer_artifact_verification_stage=contract-only
tokenizer_artifact_verification_contract_status=contract_only
tokenizer_artifact_verification_authority=0
tokenizer_artifact_verification_allowed=0
tokenizer_artifact_verification_performed=0
tokenizer_artifact_verification_metadata_present=1
tokenizer_artifact_verification_family=operator-reviewed-tokenizer-artifact-verification
tokenizer_artifact_verification_format=contract-only-offline-verification
tokenizer_artifact_verification_decision=blocked_contract_only
tokenizer_artifact_verification_plan_recorded=1
tokenizer_artifact_verification_comparison_performed=0
tokenizer_artifact_verification_result_recorded=0
tokenizer_artifact_verification_digest_match_recorded=0
tokenizer_artifact_verification_size_match_recorded=0
tokenizer_artifact_verification_hash_computed=0
requires_tokenizer_artifact_measurement_contract=1
requires_future_tokenizer_artifact_binding_contract=1
tokenizer_artifact_verification_promotion_allowed=0
tokenizer_artifact_binding_contract_stage=23-tokenizer-artifact-binding-contract
tokenizer_artifact_binding_contract_command=scripts/nadia-tokenizer-artifact-binding-contract.sh
installed_tokenizer_artifact_binding_contract_command=latticra-nadia tokenizer-artifact-binding
tokenizer_artifact_binding_stage=contract-only
tokenizer_artifact_binding_contract_status=contract_only
tokenizer_artifact_binding_authority=0
tokenizer_artifact_binding_allowed=0
tokenizer_artifact_binding_performed=0
tokenizer_artifact_binding_metadata_present=1
tokenizer_artifact_binding_family=operator-reviewed-tokenizer-artifact-binding
tokenizer_artifact_binding_format=contract-only-offline-binding
tokenizer_artifact_binding_decision=blocked_contract_only
tokenizer_artifact_binding_plan_recorded=1
tokenizer_artifact_binding_result_recorded=0
tokenizer_artifact_binding_record_created=0
tokenizer_artifact_binding_hash_computed=0
tokenizer_artifact_binding_bound=0
tokenizer_artifact_binding_runtime_attachment_performed=0
tokenizer_artifact_bound_to_manifest=0
tokenizer_artifact_bound_to_tokenizer=0
tokenizer_attached_to_runtime=0
requires_tokenizer_artifact_verification_contract=1
requires_future_tokenizer_runtime_attachment_contract=1
tokenizer_artifact_binding_promotion_allowed=0
tokenizer_runtime_attachment_contract_stage=24-tokenizer-runtime-attachment-contract
tokenizer_runtime_attachment_contract_command=scripts/nadia-tokenizer-runtime-attachment-contract.sh
installed_tokenizer_runtime_attachment_contract_command=latticra-nadia tokenizer-runtime-attachment
tokenizer_runtime_attachment_stage=contract-only
tokenizer_runtime_attachment_contract_status=contract_only
tokenizer_runtime_attachment_authority=0
tokenizer_runtime_attachment_allowed=0
tokenizer_runtime_attachment_performed=0
tokenizer_runtime_attachment_metadata_present=1
tokenizer_runtime_attachment_family=operator-reviewed-tokenizer-runtime-attachment
tokenizer_runtime_attachment_format=contract-only-offline-attachment
tokenizer_runtime_attachment_decision=blocked_contract_only
tokenizer_runtime_attachment_plan_recorded=1
tokenizer_runtime_attachment_result_recorded=0
tokenizer_runtime_attachment_record_created=0
tokenizer_runtime_attachment_attached=0
tokenizer_runtime_attachment_runtime_invoked=0
tokenizer_runtime_attachment_session_created=0
runtime_session_created=0
runtime_invoked=0
requires_tokenizer_artifact_binding_contract=1
requires_future_prompt_tokenization_contract=1
tokenizer_runtime_attachment_promotion_allowed=0
prompt_tokenization_contract_stage=25-prompt-tokenization-contract
prompt_tokenization_contract_command=scripts/nadia-prompt-tokenization-contract.sh
installed_prompt_tokenization_contract_command=latticra-nadia prompt-tokenization
prompt_tokenization_stage=contract-only
prompt_tokenization_contract_status=contract_only
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenization_performed=0
prompt_tokenization_metadata_present=1
prompt_tokenization_family=operator-reviewed-prompt-tokenization
prompt_tokenization_format=contract-only-offline-tokenization
prompt_tokenization_decision=blocked_contract_only
prompt_tokenization_plan_recorded=1
prompt_tokenization_result_recorded=0
prompt_tokenization_token_count_recorded=0
prompt_tokenization_token_sequence_recorded=0
prompt_tokenization_runtime_invoked=0
prompt_tokens_created=0
prompt_token_count_recorded=0
prompt_token_sequence_recorded=0
prompt_token_buffer_created=0
prompt_tokenized=0
requires_tokenizer_runtime_attachment_contract=1
requires_future_prompt_token_sequence_contract=1
prompt_tokenization_promotion_allowed=0
prompt_token_sequence_contract_stage=26-prompt-token-sequence-contract
prompt_token_sequence_contract_command=scripts/nadia-prompt-token-sequence-contract.sh
installed_prompt_token_sequence_contract_command=latticra-nadia prompt-token-sequence
prompt_token_sequence_stage=contract-only
prompt_token_sequence_contract_status=contract_only
prompt_token_sequence_authority=0
prompt_token_sequence_allowed=0
prompt_token_sequence_recorded=0
prompt_token_sequence_metadata_present=1
prompt_token_sequence_family=operator-reviewed-prompt-token-sequence
prompt_token_sequence_format=contract-only-offline-sequence
prompt_token_sequence_decision=blocked_contract_only
prompt_token_sequence_plan_recorded=1
prompt_token_sequence_result_recorded=0
prompt_token_sequence_count_recorded=0
prompt_token_sequence_order_recorded=0
prompt_token_sequence_runtime_invoked=0
prompt_token_ids_recorded=0
prompt_attention_mask_created=0
context_window_assembled=0
requires_prompt_tokenization_contract=1
requires_future_context_window_assembly_contract=1
prompt_token_sequence_promotion_allowed=0
requires_context_pack=1
requires_runtime_profile=1
human_dignity_principle=1
survivor_witness_respect=1
community_awareness_posture=1
harm_aware_development=1
model_runtime_present=0
model_runtime_invoked=0
inference_performed=0
inference_authority=0
runtime_invoked=0
prompt_evaluated=0
model_weights_installed=0
model_weights_loaded=0
model_weights_copied=0
model_weights_downloaded=0
model_weights_inspected=0
tool_execution_authority=0
source_mutation_authority=0

[behavior]
create_prefix_layout=$CREATE_PREFIX_LAYOUT
create_component_markers=$CREATE_COMPONENT_MARKERS
create_cli_shims=$CREATE_CLI_SHIMS
preserve_existing_files=$PRESERVE_EXISTING_FILES
build_gui_installer=$BUILD_GUI_INSTALLER
build_latticra_from_source=$BUILD_LATTICRA_FROM_SOURCE
install_payload_tree=$INSTALL_PAYLOAD_TREE
install_desktop_entry=$INSTALL_DESKTOP_ENTRY
install_user_bin_wrappers=$INSTALL_USER_BIN_WRAPPERS
PLANFILE
log "[plan] $PLAN"

if bool_true "$DRY_RUN"; then
  phase 5 "dry-run prefix layout"
  log "[dry-run] would create $PREFIX"
  log "[dry-run] would install payload tree to $PAYLOAD_DIR"
  log "[dry-run] would install user commands in $USER_BIN"
  log "[dry-run] would install Nadia offline AI foundation when enabled"
  log "[dry-run] would build/copy Latticra Panel when cargo is available"
  phase 6 "dry-run build project"
  log "[dry-run] would try Cargo/CMake/Make builds when configured"
  phase 7 "dry-run install wrappers"
  log "[dry-run] would write latticra, lat, latticra-seal, latticra-nadia, latticra-panel commands"
  phase 8 "dry-run desktop integration"
  log "[dry-run] would write desktop entry when configured"
  phase 9 "dry-run manifest"
  log "[dry-run] would measure installed files"
  phase 10 "write operator receipt"
  mkdir -p "$RECEIPT_DIR"
  RECEIPT="$RECEIPT_DIR/latticra-installer-receipt-$TS.txt"
  cat > "$RECEIPT" <<RECEIPTFILE
LATTICRA INSTALLER RECEIPT

timestamp_utc=$TS
profile=$PROFILE
mode=$MODE
result=ok
install_prefix=$PREFIX
dry_run=true
plan_file=$PLAN
config=$CONFIG
RECEIPTFILE
  cp "$RECEIPT" "$RECEIPT_DIR/latest-receipt.txt"
  log "RECEIPT: $RECEIPT"
  log "INSTALLER_RESULT: success mode=$MODE prefix=$PREFIX"
  exit 0
fi

phase 5 "build local prefix layout"

if bool_true "$CREATE_PREFIX_LAYOUT"; then
  mkdir -p \
    "$PREFIX/bin" \
    "$PREFIX/etc/latticra" \
    "$PREFIX/lib" \
    "$PREFIX/share/doc/latticra" \
    "$PREFIX/share/latticra" \
    "$PREFIX/share/latticra/components" \
    "$PREFIX/share/latticra/fedora-validation" \
    "$PREFIX/share/latticra/lc" \
    "$PREFIX/share/latticra/lc/commands" \
    "$PREFIX/share/latticra/lc/host-embedding" \
    "$PREFIX/share/latticra/lc/profiles" \
    "$PREFIX/share/latticra/lc/substrate" \
    "$PREFIX/share/latticra/lir-contracts" \
    "$PREFIX/share/latticra/receipts" \
    "$PAYLOAD_DIR" \
    "$USER_BIN"
  log "[mkdir] $PREFIX"
fi

cp "$CONFIG" "$PREFIX/etc/latticra/installer-config.toml"
cp "$PLAN" "$RECEIPTS_IN_PREFIX/install-plan-$TS.txt"

phase 6 "install Latticra payload tree"

if bool_true "$INSTALL_PAYLOAD_TREE"; then
  mkdir -p "$PAYLOAD_DIR"
  for item in assets docs examples fixtures include packaging scripts src tests tools README.md STATUS.md SECURITY.md CONTRIBUTING.md TRADEMARK_POLICY.md LICENSE LICENSES; do
    copy_if_exists "$REPO_ROOT/$item" "$PAYLOAD_DIR"
  done
  mkdir -p "$PAYLOAD_DIR/installer"
  for item in README.md INSTALLER_ROADMAP.md TREE.txt configs docs manifests scripts; do
    copy_if_exists "$INSTALLER_ROOT/$item" "$PAYLOAD_DIR/installer"
  done

  if [ -d "$INSTALLER_ROOT/latticra-installer" ]; then
    mkdir -p "$PAYLOAD_DIR/installer/latticra-installer"
    for item in Cargo.toml Cargo.lock .gitignore assets src; do
      copy_if_exists "$INSTALLER_ROOT/latticra-installer/$item" "$PAYLOAD_DIR/installer/latticra-installer"
    done
  fi
fi

phase 7 "build available binaries"

if bool_true "$BUILD_GUI_INSTALLER" && [ -f "$INSTALLER_ROOT/latticra-installer/Cargo.toml" ]; then
  if command -v cargo >/dev/null 2>&1; then
    log "[cargo] building graphical installer release binary with locked offline dependencies"
    (cd "$INSTALLER_ROOT/latticra-installer" && cargo build --release --locked --offline)
    if [ -x "$INSTALLER_ROOT/latticra-installer/target/release/latticra-panel" ]; then
      cp "$INSTALLER_ROOT/latticra-installer/target/release/latticra-panel" "$PREFIX/bin/latticra-panel"
      chmod 0755 "$PREFIX/bin/latticra-panel"
      log "[binary] $PREFIX/bin/latticra-panel"
    fi
  else
    log "[skip] cargo not found; GUI binary was not built"
  fi
fi

if bool_true "$BUILD_LATTICRA_FROM_SOURCE"; then
  if [ -f "$REPO_ROOT/Cargo.toml" ] && command -v cargo >/dev/null 2>&1; then
    log "[cargo] building repo root release binaries"
    (cd "$REPO_ROOT" && cargo build --release --locked --offline)
    install_built_executables_from_dir "$REPO_ROOT/target/release"
  elif [ -f "$REPO_ROOT/CMakeLists.txt" ] && command -v cmake >/dev/null 2>&1; then
    log "[cmake] building repo root"
    (cd "$REPO_ROOT" && cmake -S . -B build/latticra-release -DCMAKE_BUILD_TYPE=Release && cmake --build build/latticra-release)
    find "$REPO_ROOT/build/latticra-release" -type f -perm -111 2>/dev/null | while IFS= read -r exe; do
      name=$(basename -- "$exe")
      cp "$exe" "$PREFIX/bin/$name"
      chmod 0755 "$PREFIX/bin/$name"
      log "[binary] $PREFIX/bin/$name"
    done
  elif [ -f "$REPO_ROOT/Makefile" ]; then
    log "[make] building repo root with default Makefile target"
    (cd "$REPO_ROOT" && make)
    for dir in "$REPO_ROOT/bin" "$REPO_ROOT/build" "$REPO_ROOT/target/release"; do
      install_built_executables_from_dir "$dir"
    done
  else
    log "[skip] no Cargo.toml, CMakeLists.txt, or Makefile found at repo root"
  fi
fi

phase 8 "install selected components and commands"

if bool_true "$CREATE_COMPONENT_MARKERS"; then
  if bool_true "$LATTICRA_CONSOLE"; then
    write_component_marker "$PREFIX/share/latticra/components/latticra-console.installed" "latticra_console"
  fi
  if bool_true "$LAT_TOOLING"; then
    write_component_marker "$PREFIX/share/latticra/components/lat-tooling.installed" "lat_tooling"
  fi
  if bool_true "$LIR_CONTRACTS"; then
    write_component_marker "$PREFIX/share/latticra/components/lir-contracts.installed" "lir_contracts"
  fi
  if bool_true "$SEAL_REPORT_ONLY"; then
    write_component_marker "$PREFIX/share/latticra/components/latticra-seal.installed" "seal_report_only"
  fi
  if bool_true "$NADIA_OFFLINE_AI"; then
    write_component_marker "$PREFIX/share/latticra/components/nadia-offline-ai.installed" "nadia_offline_ai"
  fi
  if bool_true "$FEDORA_VALIDATION"; then
    write_component_marker "$PREFIX/share/latticra/components/fedora-validation.installed" "fedora_validation"
  fi
  if bool_true "$DOCS_AND_EXAMPLES"; then
    write_component_marker "$PREFIX/share/latticra/components/docs-and-examples.installed" "docs_and_examples"
  fi
  if bool_true "$DEVELOPER_CLI_HELPERS"; then
    write_component_marker "$PREFIX/share/latticra/components/developer-cli-helpers.installed" "developer_cli_helpers"
  fi
fi

if bool_true "$LATTICRA_CONSOLE"; then
  mkdir -p \
    "$PREFIX/share/latticra/lc/commands" \
    "$PREFIX/share/latticra/lc/host-embedding" \
    "$PREFIX/share/latticra/lc/host-inventory" \
    "$PREFIX/share/latticra/lc/profiles" \
    "$PREFIX/share/latticra/lc/substrate"
  write_file "$PREFIX/etc/latticra/lc.toml" 0644 <<LCCONF
name = "Latticra Console"
short_name = "LC"
component_key = "latticra_console"
mode = "metadata-only-console-foundation"
profile = "$LC_PROFILE"
panel_console_bridge = "$LC_PANEL_BRIDGE"
command_registry_profile = "$LC_COMMAND_REGISTRY_PROFILE"
substrate_bridge_profile = "$LC_SUBSTRATE_BRIDGE_PROFILE"
host_embedding_profile = "$LC_HOST_EMBEDDING_PROFILE"
host_embedding_contract_profile = "$LC_HOST_EMBEDDING_CONTRACT_PROFILE"
host_inventory_contract_profile = "$LC_HOST_INVENTORY_CONTRACT_PROFILE"
os_base_profile = "$LC_OS_BASE_PROFILE"
report_only = $LC_REPORT_ONLY
host_embedding_contract_required = $LC_REQUIRE_HOST_EMBEDDING_CONTRACT
read_only_host_inventory_contract_required = $LC_REQUIRE_READ_ONLY_HOST_INVENTORY_CONTRACT
runtime_boundary_binding_required = $LC_REQUIRE_RUNTIME_BOUNDARY_BINDING
seal_capability_labels_required = $LC_REQUIRE_SEAL_CAPABILITY_LABELS
command_registry_status = "seed-registry"
substrate_bridge_status = "$LC_SUBSTRATE_BRIDGE_PROFILE"
host_embedding_status = "$LC_HOST_EMBEDDING_PROFILE"
host_embedding_contract_status = "metadata-only-contract"
host_inventory_contract_status = "metadata-only-contract"
os_base_status = "$LC_OS_BASE_PROFILE"
configurable = true
panel_installable = true
operator_shell_present = true
execution_allowed = false
host_mutation_allowed = false
file_io_allowed = false
network_allowed = false
runtime_enforcement_allowed = false
boot_allowed = false
future_os_base_claim = "planned_not_claimed"
LCCONF
  write_file "$PREFIX/share/latticra/lc/profiles/hosted-reference.toml" 0644 <<'LCPROFILE'
profile = "hosted_reference"
label = "Hosted Reference"
panel_console_bridge = "hosted-reference"
command_registry_profile = "c-static-table"
substrate_bridge_profile = "metadata-bound"
host_embedding_profile = "not-embedded"
host_embedding_contract_profile = "lc-host-embedding-v0"
host_inventory_contract_profile = "lc-host-inventory-v0"
os_base_profile = "planned-no-boot-authority"
report_only = true
host_embedding_contract_required = true
read_only_host_inventory_contract_required = true
runtime_boundary_binding_required = true
seal_capability_labels_required = true
execution_allowed = false
host_mutation_allowed = false
network_allowed = false
runtime_enforcement_allowed = false
boot_allowed = false
LCPROFILE
  write_file "$PREFIX/share/latticra/lc/profiles/panel-embedded.toml" 0644 <<'LCPROFILE'
profile = "panel_embedded"
label = "Panel Embedded"
panel_console_bridge = "panel-aware"
command_registry_profile = "c-static-table"
substrate_bridge_profile = "metadata-bound"
host_embedding_profile = "panel-contained"
host_embedding_contract_profile = "lc-host-embedding-v0"
host_inventory_contract_profile = "lc-host-inventory-v0"
os_base_profile = "planned-no-boot-authority"
report_only = true
host_embedding_contract_required = true
read_only_host_inventory_contract_required = true
runtime_boundary_binding_required = true
seal_capability_labels_required = true
execution_allowed = false
host_mutation_allowed = false
network_allowed = false
runtime_enforcement_allowed = false
boot_allowed = false
LCPROFILE
  write_file "$PREFIX/share/latticra/lc/profiles/host-embedded-planning.toml" 0644 <<'LCPROFILE'
profile = "host_embedded_planning"
label = "Host-Embedded Planning"
panel_console_bridge = "panel-aware"
command_registry_profile = "c-static-table"
substrate_bridge_profile = "metadata-bound"
host_embedding_profile = "host-embedded-planning"
host_embedding_contract_profile = "lc-host-embedding-v0"
host_inventory_contract_profile = "lc-host-inventory-v0"
os_base_profile = "planned-no-boot-authority"
report_only = true
host_embedding_contract_required = true
read_only_host_inventory_contract_required = true
runtime_boundary_binding_required = true
seal_capability_labels_required = true
execution_allowed = false
host_mutation_allowed = false
network_allowed = false
runtime_enforcement_allowed = false
boot_allowed = false
LCPROFILE
  write_file "$PREFIX/share/latticra/lc/profiles/os-base-planning.toml" 0644 <<'LCPROFILE'
profile = "os_base_planning"
label = "OS-Base Planning"
panel_console_bridge = "panel-aware"
command_registry_profile = "c-static-table"
substrate_bridge_profile = "metadata-bound"
host_embedding_profile = "host-embedded-planning"
host_embedding_contract_profile = "lc-host-embedding-v0"
host_inventory_contract_profile = "lc-host-inventory-v0"
os_base_profile = "os-base-planning-no-boot-authority"
report_only = true
host_embedding_contract_required = true
read_only_host_inventory_contract_required = true
runtime_boundary_binding_required = true
seal_capability_labels_required = true
execution_allowed = false
host_mutation_allowed = false
network_allowed = false
runtime_enforcement_allowed = false
boot_allowed = false
LCPROFILE
  write_file "$PREFIX/share/latticra/lc/host-embedding/contract.toml" 0644 <<LC_HOST_CONTRACT
contract_name = "Latticra Console Host Embedding Contract"
contract_profile = "$LC_HOST_EMBEDDING_CONTRACT_PROFILE"
contract_status = "metadata-only"
host_embedding_profile = "$LC_HOST_EMBEDDING_PROFILE"
host_adapter_required = true
panel_install_required = true
runtime_boundary_required = true
seal_capability_labels_required = true
operator_consent_required = true
read_only_host_inventory_required_before_embedding = true
receipt_required_before_embedding = true
promotion_gate = "contract_receipt_and_read_only_host_inventory"
command_surface = "lc host-contract"
future_embedding_command = "lc host"
no_effect = true
host_embedded_now = false
host_process_launch_allowed = false
host_file_read_allowed = false
host_file_write_allowed = false
host_mutation_allowed = false
network_allowed = false
runtime_enforcement_allowed = false
boot_allowed = false
LC_HOST_CONTRACT
  write_file "$PREFIX/share/latticra/lc/host-inventory/contract.toml" 0644 <<LC_HOST_INVENTORY
contract_name = "Latticra Console Read-Only Host Inventory Contract"
contract_profile = "$LC_HOST_INVENTORY_CONTRACT_PROFILE"
contract_status = "metadata-only"
required_before_host_embedding = true
host_adapter_present = false
inventory_schema_status = "planned"
inventory_performed = false
inventory_artifact_present = false
inventory_receipt_required = true
operator_consent_required = true
runtime_boundary_required = true
seal_capability_labels_required = true
allowed_future_scope = "os_family,kernel_version,cpu_arch,memory_class,filesystem_roots,user_scope,prefix_scope"
excluded_future_scope = "secrets,private_files,network_scan,process_launch,kernel_change,system_mutation"
promotion_gate = "host_inventory_contract_receipt_before_host_adapter"
command_surface = "lc host-inventory"
future_embedding_command = "lc host"
no_effect = true
host_embedded_now = false
host_process_launch_allowed = false
host_probe_allowed = false
host_file_read_allowed = false
host_file_write_allowed = false
host_mutation_allowed = false
network_allowed = false
runtime_enforcement_allowed = false
boot_allowed = false
LC_HOST_INVENTORY
  write_file "$PREFIX/share/latticra/lc/README.md" 0644 <<'LCREADME'
# Latticra Console (LC)

LC is the configurable Latticra operator base installed through Latticra Panel.

This first installed surface is metadata-only. It records the Console identity,
seed command registry, substrate bridge, host-embedding plan, and future OS-base
direction without launching external host commands, mutating the host, using the
network, granting runtime enforcement authority, booting hardware, or claiming a
production operating system.

The host-embedding lane includes a contract file at
share/latticra/lc/host-embedding/contract.toml. That contract is an evidence
gate only; it does not grant host adapter, file, process, network, runtime, or
boot authority.

The host-inventory lane includes a contract file at
share/latticra/lc/host-inventory/contract.toml. It defines future read-only
inventory evidence but does not read the host, probe the host, or launch host
commands.
LCREADME
  write_file "$PREFIX/share/latticra/lc/commands/seed-registry.txt" 0644 <<'LCCOMMANDS'
name=help category=core effect=none capability=lc.core.help
name=status category=core effect=none capability=lc.core.status
name=plan category=panel effect=local-metadata capability=lc.panel.plan
name=save category=panel effect=local-metadata capability=lc.panel.save
name=dry-run category=panel effect=local-metadata capability=lc.panel.dry_run
name=reset category=panel effect=local-metadata capability=lc.panel.reset
name=uninstall category=panel effect=local-metadata capability=lc.panel.uninstall
name=clear category=panel effect=local-metadata capability=lc.panel.clear
name=lc status category=core effect=none capability=lc.core.status
name=lc commands category=core effect=none capability=lc.core.registry
name=lc profiles category=core effect=none capability=lc.core.profiles
name=lc substrate category=substrate effect=none capability=lc.substrate.inspect
name=lc host category=host effect=future-gated capability=lc.host.inspect
name=lc host-contract category=host effect=none capability=lc.host.contract
name=lc host-inventory category=host effect=none capability=lc.host.inventory
name=lc os category=os-base effect=future-gated capability=lc.os.inspect
name=pwd category=panel effect=none capability=lc.panel.navigation
name=cd category=panel effect=none capability=lc.panel.navigation
LCCOMMANDS
fi

if bool_true "$LIR_CONTRACTS"; then
  write_file "$PREFIX/share/latticra/lir-contracts/README.md" 0644 <<'LIRREADME'
# LIR Contracts

This directory is reserved for installed Latticra Intermediate Representation contracts and validated contract artifacts.
LIRREADME
fi

if bool_true "$SEAL_REPORT_ONLY"; then
  write_file "$PREFIX/etc/latticra/seal.toml" 0644 <<'SEALCONF'
mode = "report-only"
production_enforcement_ready = false
operator_receipts = true
SEALCONF
fi

if bool_true "$NADIA_OFFLINE_AI"; then
  mkdir -p \
    "$PREFIX/share/latticra/nadia/context-packs" \
    "$PREFIX/share/latticra/nadia/model-registry" \
    "$PREFIX/share/latticra/nadia/productivity-ledger" \
    "$PREFIX/share/latticra/nadia/runtime-profiles" \
    "$PREFIX/share/latticra/nadia/prompt-plans" \
    "$PREFIX/share/latticra/nadia/mode-validations" \
    "$PREFIX/share/latticra/nadia/protective-safety" \
    "$PREFIX/share/latticra/nadia/tool-preflights" \
    "$PREFIX/share/latticra/nadia/prompt-contracts" \
    "$PREFIX/share/latticra/nadia/inference-readiness" \
    "$PREFIX/share/latticra/nadia/runtime-invocation" \
    "$PREFIX/share/latticra/nadia/model-load" \
    "$PREFIX/share/latticra/nadia/prompt-receipt" \
    "$PREFIX/share/latticra/nadia/prompt-materialization" \
    "$PREFIX/share/latticra/nadia/awareness-dialogue" \
    "$PREFIX/share/latticra/nadia/prompt-evaluation-handoff" \
    "$PREFIX/share/latticra/nadia/tokenization-boundary" \
    "$PREFIX/share/latticra/nadia/tokenizer-specification" \
    "$PREFIX/share/latticra/nadia/tokenizer-manifest" \
    "$PREFIX/share/latticra/nadia/tokenizer-artifact-inventory" \
    "$PREFIX/share/latticra/nadia/tokenizer-artifact-measurement" \
    "$PREFIX/share/latticra/nadia/tokenizer-artifact-verification" \
    "$PREFIX/share/latticra/nadia/tokenizer-artifact-binding" \
    "$PREFIX/share/latticra/nadia/tokenizer-runtime-attachment" \
    "$PREFIX/share/latticra/nadia/prompt-tokenization" \
    "$PREFIX/share/latticra/nadia/prompt-token-sequence"
  write_file "$PREFIX/etc/latticra/nadia.toml" 0644 <<'NADIACONF'
name = "Nadia"
system_name = "Latticra Nadia Witness Foundation"
public_name = "Nadia"
interactive_name = "Nadia"
implementation_name = "Nadia Witness Foundation"
documentation_code_name = "Nadia Witness Foundation"
stage = "26-prompt-token-sequence-contract"
mode = "offline-prompt-token-sequence-contract"
console_bridge = "panel-aware"
productivity_ledger = "operator-reviewed-local"
context_engine_stage = "1-local-context-engine"
context_pack_command = "scripts/nadia-context-pack.sh"
local_file_read_for_indexing = "operator-invoked"
runtime_profile_stage = "2-runtime-profile-boundary"
runtime_profile_command = "scripts/nadia-runtime-profile.sh"
runtime_family = "llama.cpp-compatible"
model_format = "gguf"
developer_workbench_stage = "3-developer-workbench-planning"
prompt_plan_command = "scripts/nadia-prompt-plan.sh"
systems_engineering_mode_stage = "4-systems-engineering-mode-validation"
mode_validation_command = "scripts/nadia-mode-validate.sh"
mode_taxonomy_present = true
productivity_loop_stage = "5-productivity-ledger-loop"
productivity_ledger_command = "scripts/nadia-productivity-ledger.sh"
learning_scope = "operator-reviewed-local-productivity"
ledger_append_only = true
protective_safety_stage = "6-protective-safety-boundary"
protective_safety_command = "scripts/nadia-protective-safety-boundary.sh"
absolute_protective_boundary = true
sexual_user_request_authority = false
sexual_content_generation = false
sexual_roleplay_authority = false
sexualized_namesake_or_survivor_content = false
sexual_request_refusal = "always"
user_override_authority = false
prompt_injection_override_authority = false
manipulation_resistance = "required"
policy_bypass_authority = false
namesake_cause_awareness = true
tool_authority_stage = "7-guarded-tool-authority-preflight"
tool_authority_preflight_command = "scripts/nadia-tool-authority-preflight.sh"
preflight_decision = "report_only_no_execution"
tool_execution_performed = false
tool_selection_authority = false
shell_execution_authority = false
network_tool_authority = false
destructive_action_authority = false
credential_access_authority = false
requires_operator_approval = true
requires_nucleus_gate = true
requires_runtime_boundary_gate = true
requires_seal_receipt = true
requires_protective_safety_boundary = true
authority_transition_allowed = false
prompt_evaluation_contract_stage = "8-prompt-evaluation-contract"
prompt_evaluation_contract_command = "scripts/nadia-prompt-evaluation-contract.sh"
prompt_contract_status = "contract_only"
prompt_evaluation_stage = "contract-only"
prompt_materialized = false
prompt_text_materialized = false
prompt_evaluation_authority = false
prompt_receipt_required = true
refusal_policy_required = true
protective_safety_required = true
tool_preflight_required = true
runtime_profile_required = true
model_registry_review_required = true
operator_review_required = true
contract_promotion_allowed = false
local_model_registry_contract_stage = "9-local-model-registry-contract"
model_registry_contract_command = "scripts/nadia-local-model-registry-contract.sh"
local_model_registry_stage = "contract-only"
registry_contract_status = "metadata_only"
model_registry_authority = false
requires_prompt_contract = true
candidate_review_status = "operator_review_required"
candidate_usable_for_inference = false
candidate_selected_for_runtime = false
model_selection_authority = false
model_install_authority = false
model_download_authority = false
model_copy_authority = false
model_load_authority = false
model_benchmark_authority = false
model_weight_inspection_authority = false
registry_promotion_allowed = false
inference_readiness_contract_stage = "10-inference-readiness-contract"
inference_readiness_contract_command = "scripts/nadia-inference-readiness-contract.sh"
inference_readiness_stage = "contract-only"
inference_readiness_contract_status = "contract_only"
inference_readiness_authority = false
inference_ready = false
readiness_decision = "blocked_contract_only"
readiness_evidence_present = true
requires_model_registry_contract = true
requires_future_runtime_invocation_contract = true
readiness_promotion_allowed = false
runtime_invocation_authority = false
token_generation_authority = false
model_session_authority = false
runtime_invocation_contract_stage = "11-runtime-invocation-contract"
runtime_invocation_contract_command = "scripts/nadia-runtime-invocation-contract.sh"
runtime_invocation_stage = "contract-only"
runtime_invocation_contract_status = "contract_only"
runtime_invocation_allowed = false
invocation_decision = "blocked_contract_only"
invocation_evidence_present = true
requires_inference_readiness_contract = true
requires_future_model_load_contract = true
invocation_promotion_allowed = false
runtime_process_spawn_authority = false
runtime_binary_execution_authority = false
runtime_session_authority = false
runtime_process_spawned = false
runtime_binary_executed = false
runtime_session_created = false
token_generation_performed = false
model_load_contract_stage = "12-model-load-contract"
model_load_contract_command = "scripts/nadia-model-load-contract.sh"
model_load_stage = "contract-only"
model_load_contract_status = "contract_only"
model_load_authority = false
model_load_allowed = false
model_loaded = false
load_decision = "blocked_contract_only"
load_evidence_present = true
requires_runtime_invocation_contract = true
requires_model_weight_measurement_contract = true
requires_future_prompt_receipt_contract = true
load_promotion_allowed = false
model_file_open_authority = false
model_weight_read_authority = false
model_weight_mapping_authority = false
model_weight_verification_authority = false
runtime_model_attach_authority = false
model_file_opened = false
model_file_descriptor_opened = false
model_memory_map_created = false
model_weights_mapped = false
model_weights_attached = false
model_weight_measurement_performed = false
model_weight_verification_performed = false
model_load_performed = false
prompt_receipt_contract_stage = "13-prompt-receipt-contract"
prompt_receipt_contract_command = "scripts/nadia-prompt-receipt-contract.sh"
installed_prompt_receipt_contract_command = "latticra-nadia prompt-receipt"
prompt_receipt_stage = "contract-only"
prompt_receipt_contract_status = "contract_only"
prompt_receipt_authority = false
prompt_receipt_allowed = false
prompt_received = false
receipt_decision = "blocked_contract_only"
receipt_evidence_present = true
requires_model_load_contract = true
requires_prompt_source_boundary = true
requires_future_prompt_materialization_contract = true
prompt_receipt_promotion_allowed = false
prompt_source_open_authority = false
prompt_source_read_authority = false
prompt_text_materialization_authority = false
prompt_content_storage_authority = false
prompt_hash_authority = false
prompt_classification_authority = false
prompt_source_opened = false
prompt_source_read = false
prompt_bytes_read = false
prompt_text_received = false
prompt_text_materialized = false
prompt_content_stored = false
prompt_hash_computed = false
prompt_classified = false
prompt_materialization_contract_stage = "14-prompt-materialization-contract"
prompt_materialization_contract_command = "scripts/nadia-prompt-materialization-contract.sh"
installed_prompt_materialization_contract_command = "latticra-nadia prompt-materialization"
prompt_materialization_stage = "contract-only"
prompt_materialization_contract_status = "contract_only"
prompt_materialization_authority = false
prompt_materialization_allowed = false
prompt_materialized = false
materialization_decision = "blocked_contract_only"
materialization_evidence_present = true
requires_prompt_receipt_contract = true
requires_prompt_buffer_boundary = true
requires_future_prompt_evaluation_handoff_contract = true
prompt_materialization_promotion_allowed = false
prompt_buffer_allocation_authority = false
prompt_buffer_write_authority = false
prompt_tokenization_authority = false
prompt_materialization_performed = false
prompt_buffer_allocated = false
prompt_buffer_written = false
prompt_bytes_materialized = false
prompt_tokens_created = false
prompt_tokenized = false
awareness_dialogue_contract_stage = "15-awareness-dialogue-contract"
awareness_dialogue_contract_command = "scripts/nadia-awareness-dialogue-contract.sh"
installed_awareness_dialogue_contract_command = "latticra-nadia awareness-dialogue"
future_qa_dialogue_capability_planned = true
awareness_dialogue_stage = "contract-only"
awareness_dialogue_contract_status = "contract_only"
awareness_dialogue_authority = false
awareness_dialogue_allowed = false
dialogue_generation_authority = false
dialogue_generation_allowed = false
qa_dialogue_generated = false
dialogue_scope = "official-nadia-initiative-awareness-work"
dialogue_format = "question-and-answer"
q_and_a_format_required = true
survivor_centered_dialogue_required = true
official_source_grounding_required = true
live_web_lookup_authority = false
topic_yazidi_genocide_awareness = true
topic_survivor_voice_and_dignity = true
topic_conflict_related_sexual_violence_awareness_non_graphic = true
topic_genocide_prevention = true
topic_justice_and_accountability = true
topic_sinjar_reconstruction = true
topic_womens_empowerment = true
sexualized_dialogue_generation = false
graphic_sexual_detail_allowed = false
victim_blaming_allowed = false
genocide_denial_allowed = false
prompt_evaluation_handoff_contract_stage = "16-prompt-evaluation-handoff-contract"
prompt_evaluation_handoff_contract_command = "scripts/nadia-prompt-evaluation-handoff-contract.sh"
installed_prompt_evaluation_handoff_contract_command = "latticra-nadia prompt-evaluation-handoff"
prompt_evaluation_handoff_stage = "contract-only"
prompt_evaluation_handoff_contract_status = "contract_only"
prompt_evaluation_handoff_authority = false
prompt_evaluation_handoff_allowed = false
prompt_evaluation_handoff_performed = false
evaluation_handoff_decision = "blocked_contract_only"
requires_awareness_dialogue_contract = true
requires_future_tokenization_contract = true
prompt_evaluation_handoff_promotion_allowed = false
tokenization_boundary_contract_stage = "17-tokenization-boundary-contract"
tokenization_boundary_contract_command = "scripts/nadia-tokenization-boundary-contract.sh"
installed_tokenization_boundary_contract_command = "latticra-nadia tokenization-boundary"
tokenization_boundary_stage = "contract-only"
tokenization_boundary_contract_status = "contract_only"
tokenization_boundary_authority = false
tokenization_boundary_allowed = false
tokenization_boundary_performed = false
prompt_tokenization_allowed = false
prompt_tokenized = false
prompt_tokens_created = false
tokenizer_file_opened = false
tokenizer_vocab_loaded = false
tokenization_decision = "blocked_contract_only"
requires_prompt_evaluation_handoff_contract = true
requires_future_tokenizer_specification_contract = true
tokenization_boundary_promotion_allowed = false
tokenizer_specification_contract_stage = "18-tokenizer-specification-contract"
tokenizer_specification_contract_command = "scripts/nadia-tokenizer-specification-contract.sh"
installed_tokenizer_specification_contract_command = "latticra-nadia tokenizer-specification"
tokenizer_specification_stage = "contract-only"
tokenizer_specification_contract_status = "contract_only"
tokenizer_specification_authority = false
tokenizer_specification_allowed = false
tokenizer_specification_performed = false
tokenizer_specification_metadata_present = true
tokenizer_family = "model-compatible-tokenizer"
tokenizer_format = "operator-reviewed-offline-specification"
tokenizer_specification_decision = "blocked_contract_only"
tokenizer_path_recorded = false
requires_tokenization_boundary_contract = true
requires_future_tokenizer_manifest_contract = true
tokenizer_specification_promotion_allowed = false
tokenizer_manifest_contract_stage = "19-tokenizer-manifest-contract"
tokenizer_manifest_contract_command = "scripts/nadia-tokenizer-manifest-contract.sh"
installed_tokenizer_manifest_contract_command = "latticra-nadia tokenizer-manifest"
tokenizer_manifest_stage = "contract-only"
tokenizer_manifest_contract_status = "contract_only"
tokenizer_manifest_authority = false
tokenizer_manifest_allowed = false
tokenizer_manifest_performed = false
tokenizer_manifest_metadata_present = true
tokenizer_manifest_family = "operator-reviewed-tokenizer-manifest"
tokenizer_manifest_format = "contract-only-offline-manifest"
tokenizer_manifest_decision = "blocked_contract_only"
tokenizer_manifest_path_recorded = false
tokenizer_manifest_schema_planned = true
tokenizer_manifest_opened = false
tokenizer_manifest_read = false
tokenizer_manifest_parsed = false
tokenizer_manifest_validated = false
tokenizer_manifest_loaded = false
requires_tokenizer_specification_contract = true
requires_future_tokenizer_artifact_inventory_contract = true
tokenizer_manifest_promotion_allowed = false
tokenizer_artifact_inventory_contract_stage = "20-tokenizer-artifact-inventory-contract"
tokenizer_artifact_inventory_contract_command = "scripts/nadia-tokenizer-artifact-inventory-contract.sh"
installed_tokenizer_artifact_inventory_contract_command = "latticra-nadia tokenizer-artifact-inventory"
tokenizer_artifact_inventory_stage = "contract-only"
tokenizer_artifact_inventory_contract_status = "contract_only"
tokenizer_artifact_inventory_authority = false
tokenizer_artifact_inventory_allowed = false
tokenizer_artifact_inventory_performed = false
tokenizer_artifact_inventory_metadata_present = true
tokenizer_artifact_inventory_family = "operator-reviewed-tokenizer-artifact-inventory"
tokenizer_artifact_inventory_format = "contract-only-offline-inventory"
tokenizer_artifact_inventory_decision = "blocked_contract_only"
tokenizer_artifact_inventory_path_recorded = false
tokenizer_artifact_inventory_schema_planned = true
tokenizer_artifact_inventory_entry_count = 0
tokenizer_artifact_inventory_file_count = 0
tokenizer_artifact_path_resolved = false
tokenizer_artifact_scan_performed = false
tokenizer_artifact_stat_performed = false
tokenizer_artifact_file_opened = false
tokenizer_artifact_file_read = false
tokenizer_artifact_hash_computed = false
requires_tokenizer_manifest_contract = true
requires_future_tokenizer_artifact_measurement_contract = true
tokenizer_artifact_inventory_promotion_allowed = false
tokenizer_artifact_measurement_contract_stage = "21-tokenizer-artifact-measurement-contract"
tokenizer_artifact_measurement_contract_command = "scripts/nadia-tokenizer-artifact-measurement-contract.sh"
installed_tokenizer_artifact_measurement_contract_command = "latticra-nadia tokenizer-artifact-measurement"
tokenizer_artifact_measurement_stage = "contract-only"
tokenizer_artifact_measurement_contract_status = "contract_only"
tokenizer_artifact_measurement_authority = false
tokenizer_artifact_measurement_allowed = false
tokenizer_artifact_measurement_performed = false
tokenizer_artifact_measurement_metadata_present = true
tokenizer_artifact_measurement_family = "operator-reviewed-tokenizer-artifact-measurement"
tokenizer_artifact_measurement_format = "contract-only-offline-measurement"
tokenizer_artifact_measurement_decision = "blocked_contract_only"
tokenizer_artifact_measurement_plan_recorded = true
tokenizer_artifact_measurement_result_recorded = false
tokenizer_artifact_measurement_digest_recorded = false
tokenizer_artifact_measurement_size_recorded = false
tokenizer_artifact_measurement_hash_computed = false
requires_tokenizer_artifact_inventory_contract = true
requires_future_tokenizer_artifact_verification_contract = true
tokenizer_artifact_measurement_promotion_allowed = false
tokenizer_artifact_verification_contract_stage = "22-tokenizer-artifact-verification-contract"
tokenizer_artifact_verification_contract_command = "scripts/nadia-tokenizer-artifact-verification-contract.sh"
installed_tokenizer_artifact_verification_contract_command = "latticra-nadia tokenizer-artifact-verification"
tokenizer_artifact_verification_stage = "contract-only"
tokenizer_artifact_verification_contract_status = "contract_only"
tokenizer_artifact_verification_authority = false
tokenizer_artifact_verification_allowed = false
tokenizer_artifact_verification_performed = false
tokenizer_artifact_verification_metadata_present = true
tokenizer_artifact_verification_family = "operator-reviewed-tokenizer-artifact-verification"
tokenizer_artifact_verification_format = "contract-only-offline-verification"
tokenizer_artifact_verification_decision = "blocked_contract_only"
tokenizer_artifact_verification_plan_recorded = true
tokenizer_artifact_verification_comparison_performed = false
tokenizer_artifact_verification_result_recorded = false
tokenizer_artifact_verification_digest_match_recorded = false
tokenizer_artifact_verification_size_match_recorded = false
tokenizer_artifact_verification_hash_computed = false
requires_tokenizer_artifact_measurement_contract = true
requires_future_tokenizer_artifact_binding_contract = true
tokenizer_artifact_verification_promotion_allowed = false
tokenizer_artifact_binding_contract_stage = "23-tokenizer-artifact-binding-contract"
tokenizer_artifact_binding_contract_command = "scripts/nadia-tokenizer-artifact-binding-contract.sh"
installed_tokenizer_artifact_binding_contract_command = "latticra-nadia tokenizer-artifact-binding"
tokenizer_artifact_binding_stage = "contract-only"
tokenizer_artifact_binding_contract_status = "contract_only"
tokenizer_artifact_binding_authority = false
tokenizer_artifact_binding_allowed = false
tokenizer_artifact_binding_performed = false
tokenizer_artifact_binding_metadata_present = true
tokenizer_artifact_binding_family = "operator-reviewed-tokenizer-artifact-binding"
tokenizer_artifact_binding_format = "contract-only-offline-binding"
tokenizer_artifact_binding_decision = "blocked_contract_only"
tokenizer_artifact_binding_plan_recorded = true
tokenizer_artifact_binding_result_recorded = false
tokenizer_artifact_binding_record_created = false
tokenizer_artifact_binding_hash_computed = false
tokenizer_artifact_binding_bound = false
tokenizer_artifact_binding_runtime_attachment_performed = false
tokenizer_artifact_bound_to_manifest = false
tokenizer_artifact_bound_to_tokenizer = false
tokenizer_attached_to_runtime = false
requires_tokenizer_artifact_verification_contract = true
requires_future_tokenizer_runtime_attachment_contract = true
tokenizer_artifact_binding_promotion_allowed = false
tokenizer_runtime_attachment_contract_stage = "24-tokenizer-runtime-attachment-contract"
tokenizer_runtime_attachment_contract_command = "scripts/nadia-tokenizer-runtime-attachment-contract.sh"
installed_tokenizer_runtime_attachment_contract_command = "latticra-nadia tokenizer-runtime-attachment"
tokenizer_runtime_attachment_stage = "contract-only"
tokenizer_runtime_attachment_contract_status = "contract_only"
tokenizer_runtime_attachment_authority = false
tokenizer_runtime_attachment_allowed = false
tokenizer_runtime_attachment_performed = false
tokenizer_runtime_attachment_metadata_present = true
tokenizer_runtime_attachment_family = "operator-reviewed-tokenizer-runtime-attachment"
tokenizer_runtime_attachment_format = "contract-only-offline-attachment"
tokenizer_runtime_attachment_decision = "blocked_contract_only"
tokenizer_runtime_attachment_plan_recorded = true
tokenizer_runtime_attachment_result_recorded = false
tokenizer_runtime_attachment_record_created = false
tokenizer_runtime_attachment_attached = false
tokenizer_runtime_attachment_runtime_invoked = false
tokenizer_runtime_attachment_session_created = false
runtime_session_created = false
runtime_invoked = false
requires_tokenizer_artifact_binding_contract = true
requires_future_prompt_tokenization_contract = true
tokenizer_runtime_attachment_promotion_allowed = false
prompt_tokenization_contract_stage = "25-prompt-tokenization-contract"
prompt_tokenization_contract_command = "scripts/nadia-prompt-tokenization-contract.sh"
installed_prompt_tokenization_contract_command = "latticra-nadia prompt-tokenization"
prompt_tokenization_stage = "contract-only"
prompt_tokenization_contract_status = "contract_only"
prompt_tokenization_authority = false
prompt_tokenization_allowed = false
prompt_tokenization_performed = false
prompt_tokenization_metadata_present = true
prompt_tokenization_family = "operator-reviewed-prompt-tokenization"
prompt_tokenization_format = "contract-only-offline-tokenization"
prompt_tokenization_decision = "blocked_contract_only"
prompt_tokenization_plan_recorded = true
prompt_tokenization_result_recorded = false
prompt_tokenization_token_count_recorded = false
prompt_tokenization_token_sequence_recorded = false
prompt_tokenization_runtime_invoked = false
prompt_tokens_created = false
prompt_token_count_recorded = false
prompt_token_sequence_recorded = false
prompt_token_buffer_created = false
prompt_tokenized = false
requires_tokenizer_runtime_attachment_contract = true
requires_future_prompt_token_sequence_contract = true
prompt_tokenization_promotion_allowed = false
prompt_token_sequence_contract_stage = "26-prompt-token-sequence-contract"
prompt_token_sequence_contract_command = "scripts/nadia-prompt-token-sequence-contract.sh"
installed_prompt_token_sequence_contract_command = "latticra-nadia prompt-token-sequence"
prompt_token_sequence_stage = "contract-only"
prompt_token_sequence_contract_status = "contract_only"
prompt_token_sequence_authority = false
prompt_token_sequence_allowed = false
prompt_token_sequence_recorded = false
prompt_token_sequence_metadata_present = true
prompt_token_sequence_family = "operator-reviewed-prompt-token-sequence"
prompt_token_sequence_format = "contract-only-offline-sequence"
prompt_token_sequence_decision = "blocked_contract_only"
prompt_token_sequence_plan_recorded = true
prompt_token_sequence_result_recorded = false
prompt_token_sequence_count_recorded = false
prompt_token_sequence_order_recorded = false
prompt_token_sequence_runtime_invoked = false
prompt_token_ids_recorded = false
prompt_attention_mask_created = false
context_window_assembled = false
requires_prompt_tokenization_contract = true
requires_future_context_window_assembly_contract = true
prompt_token_sequence_promotion_allowed = false
human_dignity_principle = true
survivor_witness_respect = true
community_awareness_posture = true
harm_aware_development = true
model_runtime_present = false
runtime_invoked = false
inference_authority = false
model_weights_installed = false
model_weights_loaded = false
model_weights_copied = false
model_weights_downloaded = false
model_weights_inspected = false
network_authority = false
tool_execution_authority = false
self_modification_authority = false
production_ai_claimed = false
NADIACONF
  write_file "$PREFIX/share/latticra/nadia/README.md" 0644 <<'NADIAREADME'
# Nadia Offline AI Foundation

Nadia is the offline AI foundation for Latticra, currently installed through the Stage-26 prompt-token-sequence contract metadata lane. Documentation and code identify this implementation as Nadia Witness Foundation while the human-facing interactive name remains Nadia.

The name honors Nobel Peace Prize laureate Nadia Murad and keeps human dignity, survivor-witness respect, community awareness, and harm-aware development visible in the system direction.

This installed component reserves local context-pack, runtime-profile, prompt-plan, mode-validation, protective-safety, tool-preflight, prompt-contract, model-registry, inference-readiness, runtime-invocation, model-load, prompt-receipt, prompt-materialization, awareness-dialogue, prompt-evaluation-handoff, tokenization-boundary, tokenizer-specification, tokenizer-manifest, tokenizer-artifact-inventory, tokenizer-artifact-measurement, tokenizer-artifact-verification, tokenizer-artifact-binding, tokenizer-runtime-attachment, prompt-tokenization, prompt-token-sequence, and productivity-ledger paths. It can generate local context packs when the operator runs latticra-nadia context-pack, runtime-readiness metadata when the operator runs latticra-nadia runtime-profile, prompt plans when the operator runs latticra-nadia prompt-plan, mode-validation metadata when the operator runs latticra-nadia mode-validate, productivity-ledger entries when the operator runs latticra-nadia productivity-ledger, protective-safety metadata when the operator runs latticra-nadia protective-safety, report-only tool-preflight metadata when the operator runs latticra-nadia tool-preflight, prompt-evaluation contract metadata when the operator runs latticra-nadia prompt-contract, local model-registry contract metadata when the operator runs latticra-nadia model-registry, inference-readiness contract metadata when the operator runs latticra-nadia inference-readiness, runtime-invocation contract metadata when the operator runs latticra-nadia runtime-invocation, model-load contract metadata when the operator runs latticra-nadia model-load, prompt-receipt contract metadata when the operator runs latticra-nadia prompt-receipt, prompt-materialization contract metadata when the operator runs latticra-nadia prompt-materialization, awareness-dialogue contract metadata when the operator runs latticra-nadia awareness-dialogue, prompt-evaluation handoff contract metadata when the operator runs latticra-nadia prompt-evaluation-handoff, tokenization-boundary contract metadata when the operator runs latticra-nadia tokenization-boundary, tokenizer-specification contract metadata when the operator runs latticra-nadia tokenizer-specification, tokenizer-manifest contract metadata when the operator runs latticra-nadia tokenizer-manifest, tokenizer-artifact-inventory contract metadata when the operator runs latticra-nadia tokenizer-artifact-inventory, tokenizer-artifact-measurement contract metadata when the operator runs latticra-nadia tokenizer-artifact-measurement, tokenizer-artifact-verification contract metadata when the operator runs latticra-nadia tokenizer-artifact-verification, tokenizer-artifact-binding contract metadata when the operator runs latticra-nadia tokenizer-artifact-binding, tokenizer-runtime-attachment contract metadata when the operator runs latticra-nadia tokenizer-runtime-attachment, prompt-tokenization contract metadata when the operator runs latticra-nadia prompt-tokenization, and prompt-token-sequence contract metadata when the operator runs latticra-nadia prompt-token-sequence. It does not provide sexual user functionality, generate dialogue, receive prompt text, read prompt text, read prompt sources, allocate prompt buffers, tokenize prompts, create prompt tokens, record prompt token sequences, record prompt token IDs, record prompt token order, record prompt token offsets, assemble context windows, resolve tokenizer artifact paths, open tokenizer artifacts, read tokenizer artifacts, scan tokenizer artifacts, hash tokenizer artifacts, measure tokenizer artifacts, verify tokenizer artifacts, compare tokenizer artifact digests, compare tokenizer artifact sizes, bind tokenizer artifacts, attach tokenizers to a runtime, create runtime sessions, record tokenizer artifact digests, record tokenizer artifact sizes, load tokenizer manifests, parse tokenizer manifests, open tokenizer files, load tokenizer vocabularies, materialize prompts, evaluate prompts, select models, open model files, map model weights, install model weights, load model weights, spawn a runtime process, create a runtime session, generate tokens, run inference, execute tools, use the network, train or distill a model, or mutate source. Prompt-token-sequence metadata records future context window assembly requirements; it grants no prompt evaluation, dialogue generation, inference, or tool execution authority.
NADIAREADME
fi

if bool_true "$FEDORA_VALIDATION"; then
  write_file "$PREFIX/share/latticra/fedora-validation/README.md" 0644 <<'FEDORAREADME'
# Fedora Validation Workspace

This directory is reserved for Fedora/Linux validation outputs, notes, and generated reports.
This installer does not change Fedora system configuration.
FEDORAREADME
fi

if bool_true "$DOCS_AND_EXAMPLES"; then
  write_file "$PREFIX/share/doc/latticra/README.installed.md" 0644 <<DOCSREADME
# Latticra local-prefix installation

Prefix: $PREFIX
Payload tree: $PAYLOAD_DIR
Receipts: $RECEIPTS_IN_PREFIX

This user-local install does not modify kernel, systemd, SELinux, or system package state.
DOCSREADME
fi

if bool_true "$CREATE_CLI_SHIMS" && bool_true "$INSTALL_USER_BIN_WRAPPERS"; then
  write_managed_file "$USER_BIN/latticra" 0755 <<LATTICRAWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
PREFIX="\${LATTICRA_PREFIX:-$PREFIX}"
case "\${1:-status}" in
  status)
    echo "Latticra is installed."
    echo "prefix=\$PREFIX"
    echo "payload=\$PREFIX/lib/latticra"
    echo "receipts=\$PREFIX/share/latticra/receipts"
    ;;
  path)
    echo "\$PREFIX"
    ;;
  gui)
    exec "\$HOME/.local/bin/latticra-panel"
    ;;
  receipts)
    ls -la "\$PREFIX/share/latticra/receipts"
    ;;
  docs)
    echo "\$PREFIX/share/doc/latticra"
    ;;
  lc|console)
    shift
    if [ -x "\$HOME/.local/bin/latticra-lc" ]; then
      exec "\$HOME/.local/bin/latticra-lc" "\$@"
    fi
    echo "Latticra Console (LC) is not installed in this local prefix." >&2
    echo "Enable the latticra_console component in Latticra Panel first." >&2
    exit 1
    ;;
  reset|uninstall)
    ACTION="\$1"
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/installer/scripts/latticra-installer-uninstall.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Latticra reset script not found: \$SCRIPT" >&2
      exit 66
    fi
    exec sh "\$SCRIPT" --prefix "\$PREFIX" --operation "\$ACTION" "\$@"
    ;;
  seal)
    shift
    exec "\$HOME/.local/bin/latticra-seal" "\$@"
    ;;
  nadia)
    shift
    if [ -x "\$HOME/.local/bin/latticra-nadia" ]; then
      exec "\$HOME/.local/bin/latticra-nadia" "\$@"
    fi
    echo "Nadia offline AI foundation is not installed in this local prefix." >&2
    echo "Enable the nadia_offline_ai component in Latticra Panel first." >&2
    exit 1
    ;;
  run)
    shift
    if [ -x "\$PREFIX/bin/latticra" ]; then
      exec "\$PREFIX/bin/latticra" "\$@"
    fi
    echo "No compiled Latticra runtime binary named latticra was found in \$PREFIX/bin." >&2
    echo "Installed source/payload is available at \$PREFIX/lib/latticra." >&2
    exit 1
    ;;
  *)
    if [ -x "\$PREFIX/bin/latticra" ]; then
      exec "\$PREFIX/bin/latticra" "\$@"
    fi
    echo "usage: latticra {status|path|gui|receipts|docs|lc|reset|seal|nadia|run}" >&2
    exit 64
    ;;
esac
LATTICRAWRAP

  write_managed_file "$USER_BIN/lat" 0755 <<LATWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
PREFIX="\${LATTICRA_PREFIX:-$PREFIX}"
if [ -x "\$PREFIX/bin/lat" ]; then
  exec "\$PREFIX/bin/lat" "\$@"
fi
if [ -x "\$PREFIX/lib/latticra/tools/lat" ]; then
  exec "\$PREFIX/lib/latticra/tools/lat" "\$@"
fi
echo "Lat tooling is installed as part of the Latticra payload."
echo "prefix=\$PREFIX"
echo "payload=\$PREFIX/lib/latticra"
echo "No compiled lat binary was found yet."
LATWRAP

  if bool_true "$LATTICRA_CONSOLE"; then
    write_managed_file "$USER_BIN/latticra-lc" 0755 <<LCWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
PREFIX="\${LATTICRA_PREFIX:-$PREFIX}"
LC_DIR="\$PREFIX/share/latticra/lc"
render_lc_help() {
  REGISTRY="\$LC_DIR/commands/seed-registry.txt"
  echo "LATTICRA CONSOLE HELP"
  echo "short_name=LC"
  echo "registry_source=installed-seed-registry"
  echo "host_process_launch_allowed=0"
  echo
  echo "Commands:"
  if [ ! -f "\$REGISTRY" ]; then
    echo "LC seed registry not found: \$REGISTRY" >&2
    return 66
  fi
  while IFS= read -r line; do
    name="\${line#name=}"
    name="\${name%% category=*}"
    category="\${line#* category=}"
    category="\${category%% effect=*}"
    effect="\${line#* effect=}"
    effect="\${effect%% capability=*}"
    capability="\${line##* capability=}"
    printf '  %-14s category=%s effect=%s capability=%s\n' "\$name" "\$category" "\$effect" "\$capability"
  done < "\$REGISTRY"
  echo
  echo "Authority:"
  echo "  execution_allowed=0"
  echo "  host_mutation_allowed=0"
  echo "  network_allowed=0"
  echo "  runtime_enforcement_allowed=0"
  echo "  boot_allowed=0"
}
render_lc_man() {
  echo "LATTICRA-CONSOLE(1)"
  echo
  echo "NAME"
  echo "  latticra-lc - Latticra Console metadata and operator-base surface"
  echo
  echo "SYNOPSIS"
  echo "  latticra-lc status"
  echo "  latticra-lc help"
  echo "  latticra-lc commands"
  echo "  latticra-lc profiles"
  echo "  latticra-lc substrate"
  echo "  latticra-lc host"
  echo "  latticra-lc host-contract"
  echo "  latticra-lc host-inventory"
  echo "  latticra-lc os"
  echo
  render_lc_help || return \$?
  echo
  echo "AUTHORITY"
  echo "  shell_execution_authority=0"
  echo "  external_host_process_launch=0"
  echo "  host_mutation_authority=0"
  echo "  network_authority=0"
  echo "  runtime_enforcement_authority=0"
  echo "  boot_authority=0"
  echo "  production_os_claim=0"
}
render_lc_boundary() {
  REGISTRY="\$LC_DIR/commands/seed-registry.txt"
  echo "LATTICRA CONSOLE COMMAND BOUNDARY REPORT"
  echo "registry_source=installed-seed-registry"
  echo "runtime_boundary_bound=1"
  echo "seal_capability_labels_bound=1"
  echo "no_effect_registry=1"
  echo "host_process_launch_allowed=0"
  if [ ! -f "\$REGISTRY" ]; then
    echo "LC seed registry not found: \$REGISTRY" >&2
    return 66
  fi
  while IFS= read -r line; do
    name="\${line#name=}"
    name="\${name%% category=*}"
    capability="\${line##* capability=}"
    runtime_request=authority-check
    runtime_mode=validation-only
    runtime_policy=allow-validation
    policy_matrix_cell=no-effect-validation
    requires_future_gate=0
    seal_capability=seal.capability.report
    case "\$name" in
      dry-run|save|reset|uninstall)
        seal_capability=seal.capability.dry_run
        ;;
      "lc substrate")
        seal_capability=seal.capability.inspect
        ;;
      "lc host-contract")
        seal_capability=seal.capability.inspect
        ;;
      "lc host-inventory")
        seal_capability=seal.capability.inspect
        ;;
      "lc host")
        seal_capability=seal.capability.inspect
        runtime_request=future-gated
        runtime_mode=future-gated
        runtime_policy=future-gated
        policy_matrix_cell=future-gated-operation
        requires_future_gate=1
        ;;
      "lc os")
        seal_capability=seal.capability.inspect
        runtime_request=future-gated
        runtime_mode=future-gated
        runtime_policy=future-gated
        policy_matrix_cell=future-gated-operation
        requires_future_gate=1
        ;;
    esac
    echo "command=\$name capability=\$capability seal_capability=\$seal_capability runtime_request=\$runtime_request runtime_effect=none runtime_mode=\$runtime_mode runtime_policy=\$runtime_policy policy_matrix_cell=\$policy_matrix_cell requires_future_gate=\$requires_future_gate no_effect=1 execution_allowed=0 host_mutation_allowed=0 network_allowed=0 runtime_enforcement_allowed=0 boot_allowed=0 seal_capability_grants_authority=0"
  done < "\$REGISTRY"
}
case "\${1:-status}" in
  status)
    echo "LATTICRA CONSOLE"
    echo
    echo "console_name=Latticra Console"
    echo "short_name=LC"
    echo "component_key=latticra_console"
    echo "mode=metadata-only-console-foundation"
    echo "prefix=\$PREFIX"
    echo "config=\$PREFIX/etc/latticra/lc.toml"
    echo "commands=\$LC_DIR/commands/seed-registry.txt"
    echo "configurable=1"
    echo "panel_installable=1"
    echo "profile=$LC_PROFILE"
    echo "panel_console_bridge=$LC_PANEL_BRIDGE"
    echo "command_registry_profile=$LC_COMMAND_REGISTRY_PROFILE"
    echo "substrate_bridge_profile=$LC_SUBSTRATE_BRIDGE_PROFILE"
    echo "host_embedding_profile=$LC_HOST_EMBEDDING_PROFILE"
    echo "host_embedding_contract_profile=$LC_HOST_EMBEDDING_CONTRACT_PROFILE"
    echo "host_inventory_contract_profile=$LC_HOST_INVENTORY_CONTRACT_PROFILE"
    echo "os_base_profile=$LC_OS_BASE_PROFILE"
    echo "report_only=$LC_REPORT_ONLY"
    echo "host_embedding_contract_required=$LC_REQUIRE_HOST_EMBEDDING_CONTRACT"
    echo "read_only_host_inventory_contract_required=$LC_REQUIRE_READ_ONLY_HOST_INVENTORY_CONTRACT"
    echo "runtime_boundary_binding_required=$LC_REQUIRE_RUNTIME_BOUNDARY_BINDING"
    echo "seal_capability_labels_required=$LC_REQUIRE_SEAL_CAPABILITY_LABELS"
    echo "command_registry_status=seed-registry"
    echo "substrate_bridge_status=$LC_SUBSTRATE_BRIDGE_PROFILE"
    echo "host_embedding_status=$LC_HOST_EMBEDDING_PROFILE"
    echo "host_embedding_contract_status=metadata-only-contract"
    echo "host_inventory_contract_status=metadata-only-contract"
    echo "os_base_status=$LC_OS_BASE_PROFILE"
    echo "operator_shell_present=1"
    echo "future_os_base_claim=planned_not_claimed"
    echo "execution_allowed=0"
    echo "host_mutation_allowed=0"
    echo "file_io_allowed=0"
    echo "network_allowed=0"
    echo "runtime_enforcement_allowed=0"
    echo "boot_allowed=0"
    ;;
  help)
    render_lc_help
    ;;
  man|manual)
    render_lc_man
    ;;
  boundary)
    render_lc_boundary
    ;;
  commands|registry)
    if [ -f "\$LC_DIR/commands/seed-registry.txt" ]; then
      cat "\$LC_DIR/commands/seed-registry.txt"
    else
      echo "LC seed registry not found: \$LC_DIR/commands/seed-registry.txt" >&2
      exit 66
    fi
    ;;
  profiles)
    if [ -d "\$LC_DIR/profiles" ]; then
      for profile in "\$LC_DIR"/profiles/*.toml; do
        [ -f "\$profile" ] || continue
        echo "\$profile"
      done
    else
      echo "LC profiles not found: \$LC_DIR/profiles" >&2
      exit 66
    fi
    ;;
  substrate)
    echo "lc_substrate_bridge=$LC_SUBSTRATE_BRIDGE_PROFILE"
    echo "linked_surfaces=Lat,LIR,Nucleus,Runtime Boundary,Seal,Panel,Nadia"
    echo "effect_boundary=no-effect"
    echo "runtime_enforcement_authority=0"
    ;;
  host)
    echo "lc_host_embedding=$LC_HOST_EMBEDDING_PROFILE"
    echo "host_embedding_contract=$LC_HOST_EMBEDDING_CONTRACT_PROFILE"
    echo "host_inventory_contract=$LC_HOST_INVENTORY_CONTRACT_PROFILE"
    echo "host_embedding_contract_required=$LC_REQUIRE_HOST_EMBEDDING_CONTRACT"
    echo "read_only_host_inventory_contract_required=$LC_REQUIRE_READ_ONLY_HOST_INVENTORY_CONTRACT"
    echo "host_embedded_now=0"
    echo "host_mutation_allowed=0"
    echo "file_io_allowed=0"
    echo "future_host_role=embed-within-host-after-gates"
    ;;
  host-contract|contract)
    echo "LATTICRA CONSOLE HOST EMBEDDING CONTRACT"
    echo "contract_profile=$LC_HOST_EMBEDDING_CONTRACT_PROFILE"
    echo "contract_status=metadata-only"
    echo "contract_file=\$LC_DIR/host-embedding/contract.toml"
    echo "host_embedding_profile=$LC_HOST_EMBEDDING_PROFILE"
    echo "host_adapter_required=1"
    echo "panel_install_required=1"
    echo "runtime_boundary_required=1"
    echo "seal_capability_labels_required=1"
    echo "operator_consent_required=1"
    echo "read_only_host_inventory_required_before_embedding=1"
    echo "receipt_required_before_embedding=1"
    echo "promotion_gate=contract_receipt_and_read_only_host_inventory"
    echo "command_surface=lc host-contract"
    echo "future_embedding_command=lc host"
    echo "no_effect=1"
    echo "host_embedded_now=0"
    echo "host_process_launch_allowed=0"
    echo "host_file_read_allowed=0"
    echo "host_file_write_allowed=0"
    echo "host_mutation_allowed=0"
    echo "network_allowed=0"
    echo "runtime_enforcement_allowed=0"
    echo "boot_allowed=0"
    ;;
  host-inventory|inventory)
    echo "LATTICRA CONSOLE READ-ONLY HOST INVENTORY CONTRACT"
    echo "contract_profile=$LC_HOST_INVENTORY_CONTRACT_PROFILE"
    echo "contract_status=metadata-only"
    echo "contract_file=\$LC_DIR/host-inventory/contract.toml"
    echo "required_before_host_embedding=1"
    echo "host_adapter_present=0"
    echo "inventory_schema_status=planned"
    echo "inventory_performed=0"
    echo "inventory_artifact_present=0"
    echo "inventory_receipt_required=1"
    echo "operator_consent_required=1"
    echo "runtime_boundary_required=1"
    echo "seal_capability_labels_required=1"
    echo "allowed_future_scope=os_family,kernel_version,cpu_arch,memory_class,filesystem_roots,user_scope,prefix_scope"
    echo "excluded_future_scope=secrets,private_files,network_scan,process_launch,kernel_change,system_mutation"
    echo "promotion_gate=host_inventory_contract_receipt_before_host_adapter"
    echo "command_surface=lc host-inventory"
    echo "future_embedding_command=lc host"
    echo "no_effect=1"
    echo "host_embedded_now=0"
    echo "host_process_launch_allowed=0"
    echo "host_probe_allowed=0"
    echo "host_file_read_allowed=0"
    echo "host_file_write_allowed=0"
    echo "host_mutation_allowed=0"
    echo "network_allowed=0"
    echo "runtime_enforcement_allowed=0"
    echo "boot_allowed=0"
    ;;
  os|base)
    echo "lc_os_base_status=$LC_OS_BASE_PROFILE"
    echo "future_os_base_claim=planned_not_claimed"
    echo "boot_allowed=0"
    echo "kernel_enforcement_authority=0"
    echo "production_os_claim=0"
    ;;
  path)
    echo "\$LC_DIR"
    ;;
  *)
    echo "usage: latticra-lc {status|help|man|boundary|commands|substrate|host|os|path}" >&2
    exit 64
    ;;
esac
LCWRAP
  fi

  write_managed_file "$USER_BIN/latticra-seal" 0755 <<SEALWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
PREFIX="\${LATTICRA_PREFIX:-$PREFIX}"
REPORT_DIR="\$PREFIX/share/latticra/receipts"
mkdir -p "\$REPORT_DIR"
case "\${1:-report}" in
  report)
    TS=\$(date -u +"%Y%m%dT%H%M%SZ")
    REPORT="\$REPORT_DIR/latticra-seal-report-\$TS.txt"
    {
      echo "LATTICRA SEAL REPORT"
      echo
      echo "timestamp_utc=\$TS"
      echo "mode=report-only"
      echo "prefix=\$PREFIX"
      echo "kernel=\$(uname -srmo 2>/dev/null || uname -a)"
      if [ -f /etc/os-release ]; then
        . /etc/os-release
        echo "os=\${PRETTY_NAME:-unknown}"
      fi
      echo "network_authority=0"
      echo "runtime_enforcement_authority=0"
      echo
      echo "components:"
      ls "\$PREFIX/share/latticra/components" 2>/dev/null || true
    } > "\$REPORT"
    cat "\$REPORT"
    ;;
  path)
    echo "\$REPORT_DIR"
    ;;
  *)
    echo "usage: latticra-seal {report|path}" >&2
    exit 64
    ;;
esac
SEALWRAP

  if bool_true "$NADIA_OFFLINE_AI"; then
    write_managed_file "$USER_BIN/latticra-nadia" 0755 <<NADIAWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
PREFIX="\${LATTICRA_PREFIX:-$PREFIX}"
NADIA_DIR="\$PREFIX/share/latticra/nadia"
case "\${1:-status}" in
  status)
    echo "NADIA OFFLINE AI FOUNDATION"
    echo
    echo "name=Nadia"
    echo "system_name=Latticra Nadia Witness Foundation"
    echo "public_name=Nadia"
    echo "interactive_name=Nadia"
    echo "implementation_name=Nadia Witness Foundation"
    echo "documentation_code_name=Nadia Witness Foundation"
    echo "stage=26-prompt-token-sequence-contract"
    echo "mode=offline-prompt-token-sequence-contract"
    echo "prefix=\$PREFIX"
    echo "config=\$PREFIX/etc/latticra/nadia.toml"
    echo "context_packs=\$NADIA_DIR/context-packs"
    echo "model_registry=\$NADIA_DIR/model-registry"
    echo "productivity_ledger=\$NADIA_DIR/productivity-ledger"
    echo "runtime_profiles=\$NADIA_DIR/runtime-profiles"
    echo "prompt_plans=\$NADIA_DIR/prompt-plans"
    echo "mode_validations=\$NADIA_DIR/mode-validations"
    echo "protective_safety=\$NADIA_DIR/protective-safety"
    echo "tool_preflights=\$NADIA_DIR/tool-preflights"
    echo "prompt_contracts=\$NADIA_DIR/prompt-contracts"
    echo "model_registry_contracts=\$NADIA_DIR/model-registry"
    echo "inference_readiness_contracts=\$NADIA_DIR/inference-readiness"
    echo "runtime_invocation_contracts=\$NADIA_DIR/runtime-invocation"
    echo "model_load_contracts=\$NADIA_DIR/model-load"
    echo "prompt_receipt_contracts=\$NADIA_DIR/prompt-receipt"
    echo "prompt_materialization_contracts=\$NADIA_DIR/prompt-materialization"
    echo "awareness_dialogue_contracts=\$NADIA_DIR/awareness-dialogue"
    echo "prompt_evaluation_handoff_contracts=\$NADIA_DIR/prompt-evaluation-handoff"
    echo "tokenization_boundary_contracts=\$NADIA_DIR/tokenization-boundary"
    echo "tokenizer_specification_contracts=\$NADIA_DIR/tokenizer-specification"
    echo "tokenizer_manifest_contracts=\$NADIA_DIR/tokenizer-manifest"
    echo "tokenizer_artifact_inventory_contracts=\$NADIA_DIR/tokenizer-artifact-inventory"
    echo "tokenizer_artifact_measurement_contracts=\$NADIA_DIR/tokenizer-artifact-measurement"
    echo "tokenizer_artifact_verification_contracts=\$NADIA_DIR/tokenizer-artifact-verification"
    echo "tokenizer_artifact_binding_contracts=\$NADIA_DIR/tokenizer-artifact-binding"
    echo "tokenizer_runtime_attachment_contracts=\$NADIA_DIR/tokenizer-runtime-attachment"
    echo "prompt_tokenization_contracts=\$NADIA_DIR/prompt-tokenization"
    echo "prompt_token_sequence_contracts=\$NADIA_DIR/prompt-token-sequence"
    echo "context_pack_command=latticra-nadia context-pack"
    echo "runtime_profile_command=latticra-nadia runtime-profile"
    echo "prompt_plan_command=latticra-nadia prompt-plan"
    echo "systems_engineering_mode_stage=4-systems-engineering-mode-validation"
    echo "mode_validation_command=latticra-nadia mode-validate"
    echo "mode_taxonomy_present=1"
    echo "productivity_loop_stage=5-productivity-ledger-loop"
    echo "productivity_ledger_command=latticra-nadia productivity-ledger"
    echo "learning_scope=operator-reviewed-local-productivity"
    echo "ledger_append_only=1"
    echo "protective_safety_stage=6-protective-safety-boundary"
    echo "protective_safety_command=latticra-nadia protective-safety"
    echo "absolute_protective_boundary=1"
    echo "sexual_user_request_authority=0"
    echo "sexual_content_generation=0"
    echo "sexual_roleplay_authority=0"
    echo "sexualized_namesake_or_survivor_content=0"
    echo "sexual_request_refusal=always"
    echo "user_override_authority=0"
    echo "prompt_injection_override_authority=0"
    echo "manipulation_resistance=required"
    echo "policy_bypass_authority=0"
    echo "namesake_cause_awareness=1"
    echo "tool_authority_stage=7-guarded-tool-authority-preflight"
    echo "tool_authority_preflight_command=latticra-nadia tool-preflight"
    echo "preflight_decision=report_only_no_execution"
    echo "tool_execution_performed=0"
    echo "tool_selection_authority=0"
    echo "shell_execution_authority=0"
    echo "network_tool_authority=0"
    echo "destructive_action_authority=0"
    echo "credential_access_authority=0"
    echo "requires_operator_approval=1"
    echo "requires_nucleus_gate=1"
    echo "requires_runtime_boundary_gate=1"
    echo "requires_seal_receipt=1"
    echo "requires_protective_safety_boundary=1"
    echo "authority_transition_allowed=0"
    echo "prompt_evaluation_contract_stage=8-prompt-evaluation-contract"
    echo "prompt_evaluation_contract_command=latticra-nadia prompt-contract"
    echo "prompt_contract_status=contract_only"
    echo "prompt_evaluation_stage=contract-only"
    echo "prompt_materialized=0"
    echo "prompt_text_materialized=0"
    echo "prompt_evaluation_authority=0"
    echo "prompt_receipt_required=1"
    echo "refusal_policy_required=1"
    echo "protective_safety_required=1"
    echo "tool_preflight_required=1"
    echo "runtime_profile_required=1"
    echo "model_registry_review_required=1"
    echo "operator_review_required=1"
    echo "contract_promotion_allowed=0"
    echo "local_model_registry_contract_stage=9-local-model-registry-contract"
    echo "model_registry_contract_command=latticra-nadia model-registry"
    echo "local_model_registry_stage=contract-only"
    echo "registry_contract_status=metadata_only"
    echo "model_registry_authority=0"
    echo "requires_prompt_contract=1"
    echo "candidate_review_status=operator_review_required"
    echo "candidate_usable_for_inference=0"
    echo "candidate_selected_for_runtime=0"
    echo "model_selection_authority=0"
    echo "model_install_authority=0"
    echo "model_download_authority=0"
    echo "model_copy_authority=0"
    echo "model_load_authority=0"
    echo "model_benchmark_authority=0"
    echo "model_weight_inspection_authority=0"
    echo "registry_promotion_allowed=0"
    echo "inference_readiness_contract_stage=10-inference-readiness-contract"
    echo "inference_readiness_contract_command=latticra-nadia inference-readiness"
    echo "inference_readiness_stage=contract-only"
    echo "inference_readiness_contract_status=contract_only"
    echo "inference_readiness_authority=0"
    echo "inference_ready=0"
    echo "readiness_decision=blocked_contract_only"
    echo "readiness_evidence_present=1"
    echo "requires_model_registry_contract=1"
    echo "requires_future_runtime_invocation_contract=1"
    echo "readiness_promotion_allowed=0"
    echo "runtime_invocation_authority=0"
    echo "token_generation_authority=0"
    echo "model_session_authority=0"
    echo "runtime_invocation_contract_stage=11-runtime-invocation-contract"
    echo "runtime_invocation_contract_command=latticra-nadia runtime-invocation"
    echo "runtime_invocation_stage=contract-only"
    echo "runtime_invocation_contract_status=contract_only"
    echo "runtime_invocation_allowed=0"
    echo "invocation_decision=blocked_contract_only"
    echo "invocation_evidence_present=1"
    echo "requires_inference_readiness_contract=1"
    echo "requires_future_model_load_contract=1"
    echo "invocation_promotion_allowed=0"
    echo "runtime_process_spawn_authority=0"
    echo "runtime_binary_execution_authority=0"
    echo "runtime_session_authority=0"
    echo "runtime_process_spawned=0"
    echo "runtime_binary_executed=0"
    echo "runtime_session_created=0"
    echo "token_generation_performed=0"
    echo "model_load_contract_stage=12-model-load-contract"
    echo "model_load_contract_command=latticra-nadia model-load"
    echo "model_load_stage=contract-only"
    echo "model_load_contract_status=contract_only"
    echo "model_load_authority=0"
    echo "model_load_allowed=0"
    echo "model_loaded=0"
    echo "load_decision=blocked_contract_only"
    echo "load_evidence_present=1"
    echo "requires_runtime_invocation_contract=1"
    echo "requires_model_weight_measurement_contract=1"
    echo "requires_future_prompt_receipt_contract=1"
    echo "load_promotion_allowed=0"
    echo "model_file_open_authority=0"
    echo "model_weight_read_authority=0"
    echo "model_weight_mapping_authority=0"
    echo "model_weight_verification_authority=0"
    echo "runtime_model_attach_authority=0"
    echo "model_file_opened=0"
    echo "model_file_descriptor_opened=0"
    echo "model_memory_map_created=0"
    echo "model_weights_mapped=0"
    echo "model_weights_attached=0"
    echo "model_weight_measurement_performed=0"
    echo "model_weight_verification_performed=0"
    echo "model_load_performed=0"
    echo "prompt_receipt_contract_stage=13-prompt-receipt-contract"
    echo "prompt_receipt_contract_command=latticra-nadia prompt-receipt"
    echo "installed_prompt_receipt_contract_command=latticra-nadia prompt-receipt"
    echo "prompt_receipt_stage=contract-only"
    echo "prompt_receipt_contract_status=contract_only"
    echo "prompt_receipt_authority=0"
    echo "prompt_receipt_allowed=0"
    echo "prompt_received=0"
    echo "receipt_decision=blocked_contract_only"
    echo "receipt_evidence_present=1"
    echo "requires_model_load_contract=1"
    echo "requires_prompt_source_boundary=1"
    echo "requires_future_prompt_materialization_contract=1"
    echo "prompt_receipt_promotion_allowed=0"
    echo "prompt_source_open_authority=0"
    echo "prompt_source_read_authority=0"
    echo "prompt_text_materialization_authority=0"
    echo "prompt_content_storage_authority=0"
    echo "prompt_hash_authority=0"
    echo "prompt_classification_authority=0"
    echo "prompt_source_opened=0"
    echo "prompt_source_read=0"
    echo "prompt_bytes_read=0"
    echo "prompt_text_received=0"
    echo "prompt_text_materialized=0"
    echo "prompt_content_stored=0"
    echo "prompt_hash_computed=0"
    echo "prompt_classified=0"
    echo "prompt_materialization_contract_stage=14-prompt-materialization-contract"
    echo "prompt_materialization_contract_command=latticra-nadia prompt-materialization"
    echo "installed_prompt_materialization_contract_command=latticra-nadia prompt-materialization"
    echo "prompt_materialization_stage=contract-only"
    echo "prompt_materialization_contract_status=contract_only"
    echo "prompt_materialization_authority=0"
    echo "prompt_materialization_allowed=0"
    echo "prompt_materialized=0"
    echo "materialization_decision=blocked_contract_only"
    echo "materialization_evidence_present=1"
    echo "requires_prompt_receipt_contract=1"
    echo "requires_prompt_buffer_boundary=1"
    echo "requires_future_prompt_evaluation_handoff_contract=1"
    echo "prompt_materialization_promotion_allowed=0"
    echo "prompt_buffer_allocation_authority=0"
    echo "prompt_buffer_write_authority=0"
    echo "prompt_tokenization_authority=0"
    echo "prompt_materialization_performed=0"
    echo "prompt_buffer_allocated=0"
    echo "prompt_buffer_written=0"
    echo "prompt_bytes_materialized=0"
    echo "prompt_tokens_created=0"
    echo "prompt_tokenized=0"
    echo "awareness_dialogue_contract_stage=15-awareness-dialogue-contract"
    echo "awareness_dialogue_contract_command=latticra-nadia awareness-dialogue"
    echo "installed_awareness_dialogue_contract_command=latticra-nadia awareness-dialogue"
    echo "future_qa_dialogue_capability_planned=1"
    echo "awareness_dialogue_stage=contract-only"
    echo "awareness_dialogue_contract_status=contract_only"
    echo "awareness_dialogue_authority=0"
    echo "awareness_dialogue_allowed=0"
    echo "dialogue_generation_authority=0"
    echo "dialogue_generation_allowed=0"
    echo "qa_dialogue_generated=0"
    echo "dialogue_scope=official-nadia-initiative-awareness-work"
    echo "dialogue_format=question-and-answer"
    echo "q_and_a_format_required=1"
    echo "survivor_centered_dialogue_required=1"
    echo "official_source_grounding_required=1"
    echo "live_web_lookup_authority=0"
    echo "topic_yazidi_genocide_awareness=1"
    echo "topic_survivor_voice_and_dignity=1"
    echo "topic_conflict_related_sexual_violence_awareness_non_graphic=1"
    echo "topic_genocide_prevention=1"
    echo "topic_justice_and_accountability=1"
    echo "topic_sinjar_reconstruction=1"
    echo "topic_womens_empowerment=1"
    echo "sexualized_dialogue_generation=0"
    echo "graphic_sexual_detail_allowed=0"
    echo "victim_blaming_allowed=0"
    echo "genocide_denial_allowed=0"
    echo "prompt_evaluation_handoff_contract_stage=16-prompt-evaluation-handoff-contract"
    echo "prompt_evaluation_handoff_contract_command=latticra-nadia prompt-evaluation-handoff"
    echo "installed_prompt_evaluation_handoff_contract_command=latticra-nadia prompt-evaluation-handoff"
    echo "prompt_evaluation_handoff_stage=contract-only"
    echo "prompt_evaluation_handoff_contract_status=contract_only"
    echo "prompt_evaluation_handoff_authority=0"
    echo "prompt_evaluation_handoff_allowed=0"
    echo "prompt_evaluation_handoff_performed=0"
    echo "evaluation_handoff_decision=blocked_contract_only"
    echo "requires_awareness_dialogue_contract=1"
    echo "requires_future_tokenization_contract=1"
    echo "prompt_evaluation_handoff_promotion_allowed=0"
    echo "tokenization_boundary_contract_stage=17-tokenization-boundary-contract"
    echo "tokenization_boundary_contract_command=latticra-nadia tokenization-boundary"
    echo "installed_tokenization_boundary_contract_command=latticra-nadia tokenization-boundary"
    echo "tokenization_boundary_stage=contract-only"
    echo "tokenization_boundary_contract_status=contract_only"
    echo "tokenization_boundary_authority=0"
    echo "tokenization_boundary_allowed=0"
    echo "tokenization_boundary_performed=0"
    echo "prompt_tokenization_allowed=0"
    echo "prompt_tokenized=0"
    echo "prompt_tokens_created=0"
    echo "tokenizer_file_opened=0"
    echo "tokenizer_vocab_loaded=0"
    echo "tokenization_decision=blocked_contract_only"
    echo "requires_prompt_evaluation_handoff_contract=1"
    echo "requires_future_tokenizer_specification_contract=1"
    echo "tokenization_boundary_promotion_allowed=0"
    echo "tokenizer_specification_contract_stage=18-tokenizer-specification-contract"
    echo "tokenizer_specification_contract_command=latticra-nadia tokenizer-specification"
    echo "installed_tokenizer_specification_contract_command=latticra-nadia tokenizer-specification"
    echo "tokenizer_specification_stage=contract-only"
    echo "tokenizer_specification_contract_status=contract_only"
    echo "tokenizer_specification_authority=0"
    echo "tokenizer_specification_allowed=0"
    echo "tokenizer_specification_performed=0"
    echo "tokenizer_specification_metadata_present=1"
    echo "tokenizer_family=model-compatible-tokenizer"
    echo "tokenizer_format=operator-reviewed-offline-specification"
    echo "tokenizer_specification_decision=blocked_contract_only"
    echo "tokenizer_path_recorded=0"
    echo "tokenizer_manifest_loaded=0"
    echo "requires_tokenization_boundary_contract=1"
    echo "requires_future_tokenizer_manifest_contract=1"
    echo "tokenizer_specification_promotion_allowed=0"
    echo "tokenizer_manifest_contract_stage=19-tokenizer-manifest-contract"
    echo "tokenizer_manifest_contract_command=latticra-nadia tokenizer-manifest"
    echo "installed_tokenizer_manifest_contract_command=latticra-nadia tokenizer-manifest"
    echo "tokenizer_manifest_stage=contract-only"
    echo "tokenizer_manifest_contract_status=contract_only"
    echo "tokenizer_manifest_authority=0"
    echo "tokenizer_manifest_allowed=0"
    echo "tokenizer_manifest_performed=0"
    echo "tokenizer_manifest_metadata_present=1"
    echo "tokenizer_manifest_family=operator-reviewed-tokenizer-manifest"
    echo "tokenizer_manifest_format=contract-only-offline-manifest"
    echo "tokenizer_manifest_decision=blocked_contract_only"
    echo "tokenizer_manifest_path_recorded=0"
    echo "tokenizer_manifest_schema_planned=1"
    echo "tokenizer_manifest_opened=0"
    echo "tokenizer_manifest_read=0"
    echo "tokenizer_manifest_parsed=0"
    echo "tokenizer_manifest_validated=0"
    echo "tokenizer_manifest_loaded=0"
    echo "requires_tokenizer_specification_contract=1"
    echo "requires_future_tokenizer_artifact_inventory_contract=1"
    echo "tokenizer_manifest_promotion_allowed=0"
    echo "tokenizer_artifact_inventory_contract_stage=20-tokenizer-artifact-inventory-contract"
    echo "tokenizer_artifact_inventory_contract_command=latticra-nadia tokenizer-artifact-inventory"
    echo "installed_tokenizer_artifact_inventory_contract_command=latticra-nadia tokenizer-artifact-inventory"
    echo "tokenizer_artifact_inventory_stage=contract-only"
    echo "tokenizer_artifact_inventory_contract_status=contract_only"
    echo "tokenizer_artifact_inventory_authority=0"
    echo "tokenizer_artifact_inventory_allowed=0"
    echo "tokenizer_artifact_inventory_performed=0"
    echo "tokenizer_artifact_inventory_metadata_present=1"
    echo "tokenizer_artifact_inventory_family=operator-reviewed-tokenizer-artifact-inventory"
    echo "tokenizer_artifact_inventory_format=contract-only-offline-inventory"
    echo "tokenizer_artifact_inventory_decision=blocked_contract_only"
    echo "tokenizer_artifact_inventory_path_recorded=0"
    echo "tokenizer_artifact_inventory_schema_planned=1"
    echo "tokenizer_artifact_inventory_entry_count=0"
    echo "tokenizer_artifact_inventory_file_count=0"
    echo "tokenizer_artifact_path_resolved=0"
    echo "tokenizer_artifact_scan_performed=0"
    echo "tokenizer_artifact_stat_performed=0"
    echo "tokenizer_artifact_file_opened=0"
    echo "tokenizer_artifact_file_read=0"
    echo "tokenizer_artifact_hash_computed=0"
    echo "tokenizer_artifact_measurement_performed=0"
    echo "requires_tokenizer_manifest_contract=1"
    echo "requires_future_tokenizer_artifact_measurement_contract=1"
    echo "tokenizer_artifact_inventory_promotion_allowed=0"
    echo "tokenizer_artifact_measurement_contract_stage=21-tokenizer-artifact-measurement-contract"
    echo "tokenizer_artifact_measurement_contract_command=latticra-nadia tokenizer-artifact-measurement"
    echo "installed_tokenizer_artifact_measurement_contract_command=latticra-nadia tokenizer-artifact-measurement"
    echo "tokenizer_artifact_measurement_stage=contract-only"
    echo "tokenizer_artifact_measurement_contract_status=contract_only"
    echo "tokenizer_artifact_measurement_authority=0"
    echo "tokenizer_artifact_measurement_allowed=0"
    echo "tokenizer_artifact_measurement_performed=0"
    echo "tokenizer_artifact_measurement_metadata_present=1"
    echo "tokenizer_artifact_measurement_family=operator-reviewed-tokenizer-artifact-measurement"
    echo "tokenizer_artifact_measurement_format=contract-only-offline-measurement"
    echo "tokenizer_artifact_measurement_decision=blocked_contract_only"
    echo "tokenizer_artifact_measurement_plan_recorded=1"
    echo "tokenizer_artifact_measurement_result_recorded=0"
    echo "tokenizer_artifact_measurement_digest_recorded=0"
    echo "tokenizer_artifact_measurement_size_recorded=0"
    echo "tokenizer_artifact_measurement_hash_computed=0"
    echo "tokenizer_artifact_digest_recorded=0"
    echo "tokenizer_artifact_size_recorded=0"
    echo "requires_tokenizer_artifact_inventory_contract=1"
    echo "requires_future_tokenizer_artifact_verification_contract=1"
    echo "tokenizer_artifact_measurement_promotion_allowed=0"
    echo "tokenizer_artifact_verification_contract_stage=22-tokenizer-artifact-verification-contract"
    echo "tokenizer_artifact_verification_contract_command=latticra-nadia tokenizer-artifact-verification"
    echo "installed_tokenizer_artifact_verification_contract_command=latticra-nadia tokenizer-artifact-verification"
    echo "tokenizer_artifact_verification_stage=contract-only"
    echo "tokenizer_artifact_verification_contract_status=contract_only"
    echo "tokenizer_artifact_verification_authority=0"
    echo "tokenizer_artifact_verification_allowed=0"
    echo "tokenizer_artifact_verification_performed=0"
    echo "tokenizer_artifact_verification_metadata_present=1"
    echo "tokenizer_artifact_verification_family=operator-reviewed-tokenizer-artifact-verification"
    echo "tokenizer_artifact_verification_format=contract-only-offline-verification"
    echo "tokenizer_artifact_verification_decision=blocked_contract_only"
    echo "tokenizer_artifact_verification_plan_recorded=1"
    echo "tokenizer_artifact_verification_comparison_performed=0"
    echo "tokenizer_artifact_verification_result_recorded=0"
    echo "tokenizer_artifact_verification_digest_match_recorded=0"
    echo "tokenizer_artifact_verification_size_match_recorded=0"
    echo "tokenizer_artifact_verification_hash_computed=0"
    echo "requires_tokenizer_artifact_measurement_contract=1"
    echo "requires_future_tokenizer_artifact_binding_contract=1"
    echo "tokenizer_artifact_verification_promotion_allowed=0"
    echo "tokenizer_artifact_binding_contract_stage=23-tokenizer-artifact-binding-contract"
    echo "tokenizer_artifact_binding_contract_command=latticra-nadia tokenizer-artifact-binding"
    echo "installed_tokenizer_artifact_binding_contract_command=latticra-nadia tokenizer-artifact-binding"
    echo "tokenizer_artifact_binding_stage=contract-only"
    echo "tokenizer_artifact_binding_contract_status=contract_only"
    echo "tokenizer_artifact_binding_authority=0"
    echo "tokenizer_artifact_binding_allowed=0"
    echo "tokenizer_artifact_binding_performed=0"
    echo "tokenizer_artifact_binding_metadata_present=1"
    echo "tokenizer_artifact_binding_family=operator-reviewed-tokenizer-artifact-binding"
    echo "tokenizer_artifact_binding_format=contract-only-offline-binding"
    echo "tokenizer_artifact_binding_decision=blocked_contract_only"
    echo "tokenizer_artifact_binding_plan_recorded=1"
    echo "tokenizer_artifact_binding_result_recorded=0"
    echo "tokenizer_artifact_binding_record_created=0"
    echo "tokenizer_artifact_binding_hash_computed=0"
    echo "tokenizer_artifact_binding_bound=0"
    echo "tokenizer_artifact_binding_runtime_attachment_performed=0"
    echo "tokenizer_artifact_bound_to_manifest=0"
    echo "tokenizer_artifact_bound_to_tokenizer=0"
    echo "tokenizer_attached_to_runtime=0"
    echo "requires_tokenizer_artifact_verification_contract=1"
    echo "requires_future_tokenizer_runtime_attachment_contract=1"
    echo "tokenizer_artifact_binding_promotion_allowed=0"
    echo "tokenizer_runtime_attachment_contract_stage=24-tokenizer-runtime-attachment-contract"
    echo "tokenizer_runtime_attachment_contract_command=latticra-nadia tokenizer-runtime-attachment"
    echo "installed_tokenizer_runtime_attachment_contract_command=latticra-nadia tokenizer-runtime-attachment"
    echo "tokenizer_runtime_attachment_stage=contract-only"
    echo "tokenizer_runtime_attachment_contract_status=contract_only"
    echo "tokenizer_runtime_attachment_authority=0"
    echo "tokenizer_runtime_attachment_allowed=0"
    echo "tokenizer_runtime_attachment_performed=0"
    echo "tokenizer_runtime_attachment_metadata_present=1"
    echo "tokenizer_runtime_attachment_family=operator-reviewed-tokenizer-runtime-attachment"
    echo "tokenizer_runtime_attachment_format=contract-only-offline-attachment"
    echo "tokenizer_runtime_attachment_decision=blocked_contract_only"
    echo "tokenizer_runtime_attachment_plan_recorded=1"
    echo "tokenizer_runtime_attachment_result_recorded=0"
    echo "tokenizer_runtime_attachment_record_created=0"
    echo "tokenizer_runtime_attachment_attached=0"
    echo "tokenizer_runtime_attachment_runtime_invoked=0"
    echo "tokenizer_runtime_attachment_session_created=0"
    echo "runtime_session_created=0"
    echo "runtime_invoked=0"
    echo "requires_tokenizer_artifact_binding_contract=1"
    echo "requires_future_prompt_tokenization_contract=1"
    echo "tokenizer_runtime_attachment_promotion_allowed=0"
    echo "prompt_tokenization_contract_stage=25-prompt-tokenization-contract"
    echo "prompt_tokenization_contract_command=latticra-nadia prompt-tokenization"
    echo "installed_prompt_tokenization_contract_command=latticra-nadia prompt-tokenization"
    echo "prompt_tokenization_stage=contract-only"
    echo "prompt_tokenization_contract_status=contract_only"
    echo "prompt_tokenization_authority=0"
    echo "prompt_tokenization_allowed=0"
    echo "prompt_tokenization_performed=0"
    echo "prompt_tokenization_metadata_present=1"
    echo "prompt_tokenization_family=operator-reviewed-prompt-tokenization"
    echo "prompt_tokenization_format=contract-only-offline-tokenization"
    echo "prompt_tokenization_decision=blocked_contract_only"
    echo "prompt_tokenization_plan_recorded=1"
    echo "prompt_tokenization_result_recorded=0"
    echo "prompt_tokenization_token_count_recorded=0"
    echo "prompt_tokenization_token_sequence_recorded=0"
    echo "prompt_tokenization_runtime_invoked=0"
    echo "prompt_tokens_created=0"
    echo "prompt_token_count_recorded=0"
    echo "prompt_token_sequence_recorded=0"
    echo "prompt_token_buffer_created=0"
    echo "prompt_tokenized=0"
    echo "requires_tokenizer_runtime_attachment_contract=1"
    echo "requires_future_prompt_token_sequence_contract=1"
    echo "prompt_tokenization_promotion_allowed=0"
    echo "prompt_token_sequence_contract_stage=26-prompt-token-sequence-contract"
    echo "prompt_token_sequence_contract_command=latticra-nadia prompt-token-sequence"
    echo "installed_prompt_token_sequence_contract_command=latticra-nadia prompt-token-sequence"
    echo "prompt_token_sequence_stage=contract-only"
    echo "prompt_token_sequence_contract_status=contract_only"
    echo "prompt_token_sequence_authority=0"
    echo "prompt_token_sequence_allowed=0"
    echo "prompt_token_sequence_recorded=0"
    echo "prompt_token_sequence_metadata_present=1"
    echo "prompt_token_sequence_family=operator-reviewed-prompt-token-sequence"
    echo "prompt_token_sequence_format=contract-only-offline-sequence"
    echo "prompt_token_sequence_decision=blocked_contract_only"
    echo "prompt_token_sequence_plan_recorded=1"
    echo "prompt_token_sequence_result_recorded=0"
    echo "prompt_token_sequence_count_recorded=0"
    echo "prompt_token_sequence_order_recorded=0"
    echo "prompt_token_sequence_runtime_invoked=0"
    echo "prompt_token_ids_recorded=0"
    echo "prompt_attention_mask_created=0"
    echo "context_window_assembled=0"
    echo "requires_prompt_tokenization_contract=1"
    echo "requires_future_context_window_assembly_contract=1"
    echo "prompt_token_sequence_promotion_allowed=0"
    echo "human_dignity_principle=1"
    echo "survivor_witness_respect=1"
    echo "community_awareness_posture=1"
    echo "harm_aware_development=1"
    echo "console_interop_surface_present=1"
    echo "panel_install_surface_present=1"
    echo "model_runtime_present=0"
    echo "model_runtime_invoked=0"
    echo "inference_performed=0"
    echo "inference_authority=0"
    echo "runtime_invoked=0"
    echo "prompt_evaluated=0"
    echo "model_weights_installed=0"
    echo "model_weights_loaded=0"
    echo "model_weights_copied=0"
    echo "model_weights_downloaded=0"
    echo "model_weights_inspected=0"
    echo "network_authority=0"
    echo "tool_execution_authority=0"
    echo "source_mutation_authority=0"
    echo "training_performed=0"
    echo "distillation_performed=0"
    echo "self_modification_authority=0"
    echo "production_ai_claimed=0"
    ;;
  context-pack|pack|index)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-context-pack.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia context-pack script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" --repo "\$PREFIX/lib/latticra" --output "\$NADIA_DIR/context-packs"
    ;;
  runtime-profile|runtime|profile)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-runtime-profile.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia runtime-profile script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" --output "\$NADIA_DIR/runtime-profiles"
    ;;
  prompt-plan|plan|workbench)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-prompt-plan.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia prompt-plan script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --context-pack "\$NADIA_DIR/context-packs/latest-context-pack.txt" \
      --runtime-profile "\$NADIA_DIR/runtime-profiles/latest-runtime-profile.txt" \
      --output "\$NADIA_DIR/prompt-plans"
    ;;
  mode-validate|mode|validate-mode)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-mode-validate.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia mode-validation script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --prompt-plan "\$NADIA_DIR/prompt-plans/latest-prompt-plan.txt" \
      --output "\$NADIA_DIR/mode-validations"
    ;;
  productivity-ledger|ledger|productivity)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-productivity-ledger.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia productivity-ledger script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --mode-validation "\$NADIA_DIR/mode-validations/latest-mode-validation.txt" \
      --output "\$NADIA_DIR/productivity-ledger"
    ;;
  protective-safety|safety|safety-boundary)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-protective-safety-boundary.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia protective-safety script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --productivity-entry "\$NADIA_DIR/productivity-ledger/latest-productivity-entry.txt" \
      --output "\$NADIA_DIR/protective-safety"
    ;;
  tool-preflight|tool|tool-authority|preflight)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tool-authority-preflight.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tool-authority preflight script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --protective-safety "\$NADIA_DIR/protective-safety/latest-protective-safety.txt" \
      --output "\$NADIA_DIR/tool-preflights"
    ;;
  prompt-contract|prompt-evaluation-contract|evaluation-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-prompt-evaluation-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia prompt-evaluation contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tool-preflight "\$NADIA_DIR/tool-preflights/latest-tool-preflight.txt" \
      --output "\$NADIA_DIR/prompt-contracts"
    ;;
  model-registry|registry|model-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-local-model-registry-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia local model-registry contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --prompt-contract "\$NADIA_DIR/prompt-contracts/latest-prompt-contract.txt" \
      --runtime-profile "\$NADIA_DIR/runtime-profiles/latest-runtime-profile.txt" \
      --output "\$NADIA_DIR/model-registry"
    ;;
  inference-readiness|readiness|inference-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-inference-readiness-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia inference-readiness contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --model-registry "\$NADIA_DIR/model-registry/latest-model-registry-contract.txt" \
      --output "\$NADIA_DIR/inference-readiness"
    ;;
  runtime-invocation|invocation|runtime-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-runtime-invocation-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia runtime-invocation contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --inference-readiness "\$NADIA_DIR/inference-readiness/latest-inference-readiness-contract.txt" \
      --output "\$NADIA_DIR/runtime-invocation"
    ;;
  model-load|load|model-load-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-model-load-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia model-load contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --runtime-invocation "\$NADIA_DIR/runtime-invocation/latest-runtime-invocation-contract.txt" \
      --output "\$NADIA_DIR/model-load"
    ;;
  prompt-receipt|receipt|prompt-receipt-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-prompt-receipt-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia prompt-receipt contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --model-load "\$NADIA_DIR/model-load/latest-model-load-contract.txt" \
      --output "\$NADIA_DIR/prompt-receipt"
    ;;
  prompt-materialization|materialization|prompt-materialization-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-prompt-materialization-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia prompt-materialization contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --prompt-receipt "\$NADIA_DIR/prompt-receipt/latest-prompt-receipt-contract.txt" \
      --output "\$NADIA_DIR/prompt-materialization"
    ;;
  awareness-dialogue|awareness|dialogue)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-awareness-dialogue-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia awareness-dialogue contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --prompt-materialization "\$NADIA_DIR/prompt-materialization/latest-prompt-materialization-contract.txt" \
      --output "\$NADIA_DIR/awareness-dialogue"
    ;;
  prompt-evaluation-handoff|evaluation-handoff|prompt-eval-handoff)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-prompt-evaluation-handoff-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia prompt-evaluation handoff contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --awareness-dialogue "\$NADIA_DIR/awareness-dialogue/latest-awareness-dialogue-contract.txt" \
      --output "\$NADIA_DIR/prompt-evaluation-handoff"
    ;;
  tokenization-boundary|tokenization|tokenization-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tokenization-boundary-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tokenization-boundary contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --prompt-evaluation-handoff "\$NADIA_DIR/prompt-evaluation-handoff/latest-prompt-evaluation-handoff-contract.txt" \
      --output "\$NADIA_DIR/tokenization-boundary"
    ;;
  tokenizer-specification|tokenizer-spec|tokenizer-spec-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tokenizer-specification-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tokenizer-specification contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tokenization-boundary "\$NADIA_DIR/tokenization-boundary/latest-tokenization-boundary-contract.txt" \
      --output "\$NADIA_DIR/tokenizer-specification"
    ;;
  tokenizer-manifest|tokenizer-manifest-contract|manifest)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tokenizer-manifest-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tokenizer-manifest contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tokenizer-specification "\$NADIA_DIR/tokenizer-specification/latest-tokenizer-specification-contract.txt" \
      --output "\$NADIA_DIR/tokenizer-manifest"
    ;;
  tokenizer-artifact-inventory|tokenizer-artifacts|tokenizer-inventory)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tokenizer-artifact-inventory-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tokenizer-artifact-inventory contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tokenizer-manifest "\$NADIA_DIR/tokenizer-manifest/latest-tokenizer-manifest-contract.txt" \
      --output "\$NADIA_DIR/tokenizer-artifact-inventory"
    ;;
  tokenizer-artifact-measurement|tokenizer-measurement|artifact-measurement)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tokenizer-artifact-measurement-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tokenizer-artifact-measurement contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tokenizer-artifact-inventory "\$NADIA_DIR/tokenizer-artifact-inventory/latest-tokenizer-artifact-inventory-contract.txt" \
      --output "\$NADIA_DIR/tokenizer-artifact-measurement"
    ;;
  tokenizer-artifact-verification|tokenizer-verification|artifact-verification)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tokenizer-artifact-verification-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tokenizer-artifact-verification contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tokenizer-artifact-measurement "\$NADIA_DIR/tokenizer-artifact-measurement/latest-tokenizer-artifact-measurement-contract.txt" \
      --output "\$NADIA_DIR/tokenizer-artifact-verification"
    ;;
  tokenizer-artifact-binding|tokenizer-binding|artifact-binding)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tokenizer-artifact-binding-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tokenizer-artifact-binding contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tokenizer-artifact-verification "\$NADIA_DIR/tokenizer-artifact-verification/latest-tokenizer-artifact-verification-contract.txt" \
      --output "\$NADIA_DIR/tokenizer-artifact-binding"
    ;;
  tokenizer-runtime-attachment|runtime-attachment|tokenizer-attachment)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-tokenizer-runtime-attachment-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia tokenizer-runtime-attachment contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tokenizer-artifact-binding "\$NADIA_DIR/tokenizer-artifact-binding/latest-tokenizer-artifact-binding-contract.txt" \
      --output "\$NADIA_DIR/tokenizer-runtime-attachment"
    ;;
  prompt-tokenization|prompt-tokenization-contract|prompt-tokenizer)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-prompt-tokenization-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia prompt-tokenization contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --tokenizer-runtime-attachment "\$NADIA_DIR/tokenizer-runtime-attachment/latest-tokenizer-runtime-attachment-contract.txt" \
      --output "\$NADIA_DIR/prompt-tokenization"
    ;;
  prompt-token-sequence|token-sequence|prompt-sequence|prompt-token-sequence-contract)
    shift || true
    SCRIPT="\$PREFIX/lib/latticra/scripts/nadia-prompt-token-sequence-contract.sh"
    if [ ! -f "\$SCRIPT" ]; then
      echo "Nadia prompt-token-sequence contract script not found: \$SCRIPT" >&2
      exit 66
    fi
    if [ "\$#" -gt 0 ]; then
      exec sh "\$SCRIPT" "\$@"
    fi
    exec sh "\$SCRIPT" \
      --prompt-tokenization "\$NADIA_DIR/prompt-tokenization/latest-prompt-tokenization-contract.txt" \
      --output "\$NADIA_DIR/prompt-token-sequence"
    ;;
  path)
    echo "\$NADIA_DIR"
    ;;
  *)
    echo "usage: latticra-nadia {status|context-pack|runtime-profile|prompt-plan|mode-validate|productivity-ledger|protective-safety|tool-preflight|prompt-contract|model-registry|inference-readiness|runtime-invocation|model-load|prompt-receipt|prompt-materialization|awareness-dialogue|prompt-evaluation-handoff|tokenization-boundary|tokenizer-specification|tokenizer-manifest|tokenizer-artifact-inventory|tokenizer-artifact-measurement|tokenizer-artifact-verification|tokenizer-artifact-binding|tokenizer-runtime-attachment|prompt-tokenization|prompt-token-sequence|path}" >&2
    exit 64
    ;;
esac
NADIAWRAP
  fi

  if [ -x "$PREFIX/bin/latticra-panel" ]; then
    write_managed_file "$USER_BIN/latticra-panel" 0755 <<GUIWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
export LATTICRA_INSTALLER_ROOT="$PAYLOAD_DIR/installer"
exec "$PREFIX/bin/latticra-panel" "\$@"
GUIWRAP

    # Compatibility wrapper for older docs/scripts that still call latticra-installer.
    write_managed_file "$USER_BIN/latticra-installer" 0755 <<OLDGUIWRAP
#!/usr/bin/env sh
# LATTICRA_INSTALLER_MANAGED=1
exec "$USER_BIN/latticra-panel" "\$@"
OLDGUIWRAP
  fi
fi

phase 9 "install desktop entry and measurements"

if bool_true "$INSTALL_DESKTOP_ENTRY" && [ -x "$PREFIX/bin/latticra-panel" ]; then
  ICON_DIR="$HOME/.local/share/icons/hicolor/256x256/apps"
  APP_DIR="$HOME/.local/share/applications"
  mkdir -p "$ICON_DIR" "$APP_DIR"

  # Remove old managed desktop metadata so GNOME/Fedora does not keep showing
  # the previous "Latticra Installer" application identity.
  OLD_DESKTOP="$APP_DIR/latticra-installer.desktop"
  if [ -f "$OLD_DESKTOP" ] && grep -q 'LATTICRA_INSTALLER_MANAGED=1' "$OLD_DESKTOP" 2>/dev/null; then
    rm -f "$OLD_DESKTOP"
    log "[remove-managed] $OLD_DESKTOP"
  fi

  if [ -f "$INSTALLER_ROOT/latticra-installer/assets/latticra-seal.png" ]; then
    cp "$INSTALLER_ROOT/latticra-installer/assets/latticra-seal.png" "$ICON_DIR/latticra-panel.png"
    log "[icon] $ICON_DIR/latticra-panel.png"
  fi

  write_managed_file "$APP_DIR/latticra-panel.desktop" 0644 <<DESKTOP
[Desktop Entry]
# LATTICRA_INSTALLER_MANAGED=1
Version=1.0
Type=Application
Name=Latticra Panel
GenericName=Latticra Control Panel
Comment=Install and manage Latticra, Lat, LIR, and Latticra Seal
Exec=$USER_BIN/latticra-panel
Icon=latticra-panel
Terminal=false
Categories=Development;System;
Keywords=Latticra;Lat;LIR;Seal;Installer;Panel;
StartupNotify=true
StartupWMClass=latticra-panel
DESKTOP

  if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database "$APP_DIR" >/dev/null 2>&1 || true
  fi

  if command -v gtk-update-icon-cache >/dev/null 2>&1; then
    gtk-update-icon-cache -q "$HOME/.local/share/icons/hicolor" >/dev/null 2>&1 || true
  fi
fi

MEASUREMENTS="$RECEIPTS_IN_PREFIX/manifest-$TS.sha256"
mkdir -p "$RECEIPTS_IN_PREFIX"
if command -v sha256sum >/dev/null 2>&1; then
  (cd / && find "${PREFIX#/}" "${USER_BIN#/}" -type f 2>/dev/null | sort | while IFS= read -r f; do sha256sum "/$f"; done) > "$MEASUREMENTS" || true
elif command -v shasum >/dev/null 2>&1; then
  (cd / && find "${PREFIX#/}" "${USER_BIN#/}" -type f 2>/dev/null | sort | while IFS= read -r f; do shasum -a 256 "/$f"; done) > "$MEASUREMENTS" || true
else
  (cd / && find "${PREFIX#/}" "${USER_BIN#/}" -type f 2>/dev/null | sort | while IFS= read -r f; do cksum "/$f"; done) > "$MEASUREMENTS" || true
fi
log "[measurements] $MEASUREMENTS"

phase 10 "write operator receipt"

mkdir -p "$RECEIPT_DIR" "$RECEIPTS_IN_PREFIX"
RECEIPT="$RECEIPT_DIR/latticra-installer-receipt-$TS.txt"
CONFIG_MEASUREMENT=$(measure_file "$CONFIG")
SCRIPT_MEASUREMENT=$(measure_file "$0")
if [ -f "$MANIFEST" ]; then
  MANIFEST_MEASUREMENT=$(measure_file "$MANIFEST")
else
  MANIFEST_MEASUREMENT="missing"
fi

cat > "$RECEIPT" <<RECEIPTFILE
LATTICRA INSTALLER RECEIPT

timestamp_utc=$TS
profile=$PROFILE
mode=$MODE
result=ok
repo_root=$REPO_ROOT
install_prefix=$PREFIX
payload_dir=$PAYLOAD_DIR
user_bin=$USER_BIN
production_installer_ready=0
root_authority=0
network_authority=0
runtime_enforcement_authority=0

dry_run=$DRY_RUN
allow_host_mutation=$ALLOW_HOST_MUTATION
allow_network_effect=$ALLOW_NETWORK_EFFECT
require_component_manifest=$REQUIRE_COMPONENT_MANIFEST
require_artifact_measurements=$REQUIRE_ARTIFACT_MEASUREMENTS
require_verification_policy_metadata=$REQUIRE_VERIFICATION_POLICY_METADATA

component_manifest=$MANIFEST
component_manifest_measurement=$MANIFEST_MEASUREMENT
config_measurement=$CONFIG_MEASUREMENT
installer_script_measurement=$SCRIPT_MEASUREMENT
installed_manifest=$MEASUREMENTS
plan_file=$PLAN

installed_commands:
  $USER_BIN/latticra
  $USER_BIN/lat
  $USER_BIN/latticra-seal
  $USER_BIN/latticra-nadia (when enabled)
  $USER_BIN/latticra-panel
  $USER_BIN/latticra-installer (compatibility)

--- plan ---
$(cat "$PLAN")
RECEIPTFILE

cp "$RECEIPT" "$RECEIPT_DIR/latest-receipt.txt"
cp "$RECEIPT" "$RECEIPTS_IN_PREFIX/install-receipt-$TS.txt"
cp "$RECEIPT" "$RECEIPTS_IN_PREFIX/latest-receipt.txt"
log "RECEIPT: $RECEIPT"
log "INSTALLER_RESULT: success mode=$MODE prefix=$PREFIX"

if ! printf '%s' ":$PATH:" | grep -q ":$USER_BIN:"; then
  log "NOTE: $USER_BIN is not currently in PATH. Add this to your shell profile:"
  log "  export PATH=\"$USER_BIN:\$PATH\""
fi

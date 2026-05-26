#!/usr/bin/env sh
set -eu

PREFIX="$HOME/.local/share/latticra"
while [ "$#" -gt 0 ]; do
  case "$1" in
    --prefix)
      PREFIX="$2"
      shift 2
      ;;
    *)
      echo "unknown argument: $1" >&2
      exit 64
      ;;
  esac
done

USER_BIN="$HOME/.local/bin"
LC_CONFIG="$PREFIX/share/latticra/lc/install/config.toml"
LC_REGISTRY="$PREFIX/share/latticra/lc/commands/seed-registry.txt"
LC_CONTRACT="$PREFIX/share/latticra/lc/standalone/contract.toml"
LC_SESSION_CONTRACT="$PREFIX/share/latticra/lc/session/contract.toml"
LC_PROFILE="$PREFIX/share/latticra/lc/profiles/standalone-console.toml"
TMP_DIR="$(mktemp -d "${TMPDIR:-/tmp}/latticra-lc-standalone-verify.XXXXXX")"
failures=0

cleanup() {
  rm -rf "$TMP_DIR"
}

trap cleanup EXIT INT HUP TERM

check() {
  label="$1"
  path="$2"
  if [ -e "$path" ]; then
    echo "ok: $label -> $path"
  else
    echo "missing: $label -> $path" >&2
    failures=$((failures + 1))
  fi
}

check_exec() {
  label="$1"
  path="$2"
  if [ -x "$path" ]; then
    echo "ok: $label -> $path"
  else
    echo "missing/not executable: $label -> $path" >&2
    failures=$((failures + 1))
  fi
}

check_absent() {
  label="$1"
  path="$2"
  if [ ! -e "$path" ]; then
    echo "ok: absent $label -> $path"
  else
    echo "unexpected: $label -> $path" >&2
    failures=$((failures + 1))
  fi
}

check_contains() {
  label="$1"
  pattern="$2"
  path="$3"
  if [ -f "$path" ] && grep -Fq -- "$pattern" "$path"; then
    echo "ok: $label"
  else
    echo "missing pattern: $label -> $path :: $pattern" >&2
    failures=$((failures + 1))
  fi
}

check "prefix" "$PREFIX"
check "LC install config" "$LC_CONFIG"
check "LC seed registry" "$LC_REGISTRY"
check "LC standalone contract" "$LC_CONTRACT"
check "LC session contract" "$LC_SESSION_CONTRACT"
check "LC standalone profile" "$LC_PROFILE"
check_exec "latticra command" "$USER_BIN/latticra"
check_exec "LC command wrapper" "$USER_BIN/latticra-lc"
check_absent "Latticra Panel launcher" "$USER_BIN/latticra-panel"
check_absent "Latticra Panel desktop entry" "$HOME/.local/share/applications/latticra-panel.desktop"

check_contains "standalone install profile" 'install_profile = "lc-standalone-install-v0"' "$LC_CONFIG"
check_contains "standalone install mode" 'install_mode = "metadata-only-standalone-console"' "$LC_CONFIG"
check_contains "standalone console enabled" 'standalone_console = true' "$LC_CONFIG"
check_contains "standalone requires Panel disabled" 'standalone_requires_panel = false' "$LC_CONFIG"
check_contains "standalone contract present" 'standalone_contract_present = true' "$LC_CONFIG"
check_contains "session contract profile" 'session_contract_profile = "lc-session-v0"' "$LC_CONFIG"
check_contains "session contract present" 'session_contract_present = true' "$LC_CONFIG"
check_contains "Panel embedding disabled" 'panel_embedded_console = false' "$LC_CONFIG"
check_contains "external host commands disabled" 'allow_external_host_commands = false' "$LC_CONFIG"
check_contains "standalone registry command" 'name=lc standalone category=core effect=none capability=lc.standalone.inspect' "$LC_REGISTRY"
check_contains "session registry command" 'name=lc session category=core effect=none capability=lc.session.contract' "$LC_REGISTRY"
check_contains "standalone command surface" 'command_surface = "lc standalone"' "$LC_CONTRACT"
check_contains "standalone host process denial" 'host_process_launch_allowed = false' "$LC_CONTRACT"
check_contains "standalone network denial" 'network_allowed = false' "$LC_CONTRACT"
check_contains "session command surface" 'command_surface = "lc session"' "$LC_SESSION_CONTRACT"
check_contains "session runtime denied" 'runtime_session_created = false' "$LC_SESSION_CONTRACT"
check_contains "session host process denied" 'host_process_launch_allowed = false' "$LC_SESSION_CONTRACT"

if [ -x "$USER_BIN/latticra-lc" ]; then
  if "$USER_BIN/latticra-lc" install-config > "$TMP_DIR/install-config.txt"; then
    check_contains "LC wrapper install-config report" 'LATTICRA CONSOLE INSTALL CONFIGURATION' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper standalone install profile" 'install_profile=lc-standalone-install-v0' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper standalone enabled" 'standalone_console=true' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper session contract present" 'session_contract_present=1' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper Panel embedding disabled" 'panel_embedded_console=false' "$TMP_DIR/install-config.txt"
    check_contains "LC wrapper host process denial" 'host_process_launch_allowed=0' "$TMP_DIR/install-config.txt"
  else
    echo "failed: latticra-lc install-config" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" standalone > "$TMP_DIR/standalone.txt"; then
    check_contains "LC wrapper standalone report" 'LATTICRA CONSOLE STANDALONE CONTRACT' "$TMP_DIR/standalone.txt"
    check_contains "LC wrapper standalone requires Panel denied" 'standalone_requires_panel=0' "$TMP_DIR/standalone.txt"
    check_contains "LC wrapper Panel runtime denied" 'panel_required_for_runtime=0' "$TMP_DIR/standalone.txt"
    check_contains "LC wrapper host process denial" 'host_process_launch_allowed=0' "$TMP_DIR/standalone.txt"
    check_contains "LC wrapper production OS claim denied" 'production_os_claim=0' "$TMP_DIR/standalone.txt"
  else
    echo "failed: latticra-lc standalone" >&2
    failures=$((failures + 1))
  fi

  if "$USER_BIN/latticra-lc" session > "$TMP_DIR/session.txt"; then
    check_contains "LC wrapper session report" 'LATTICRA CONSOLE SESSION CONTRACT' "$TMP_DIR/session.txt"
    check_contains "LC wrapper session command surface" 'command_surface=lc session' "$TMP_DIR/session.txt"
    check_contains "LC wrapper session runtime denied" 'runtime_session_created=0' "$TMP_DIR/session.txt"
    check_contains "LC wrapper session host process denied" 'host_process_launch_allowed=0' "$TMP_DIR/session.txt"
    check_contains "LC wrapper session production OS claim denied" 'production_os_claim=0' "$TMP_DIR/session.txt"
  else
    echo "failed: latticra-lc session" >&2
    failures=$((failures + 1))
  fi
fi

if [ "$failures" -eq 0 ]; then
  echo "Latticra standalone LC verification: ok"
  exit 0
fi

echo "Latticra standalone LC verification: failed checks=$failures" >&2
exit 1

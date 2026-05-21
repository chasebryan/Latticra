#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra no-effect cli status surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli status surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli status surface: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

cli='src/latticra_cli.c'
contract='docs/LATTICRA_NO_EFFECT_CLI_PAYLOAD_CONTRACT.md'

require_file "$cli"
require_file "$contract"

require_contains 'latticra --status' "$contract"
require_contains 'latticra --version' "$contract"
require_contains 'latticra --report' "$contract"
require_contains 'cli_report_only=1' "$contract"
require_contains 'cli_runtime_behavior_allowed=0' "$contract"
require_contains 'cli_host_mutation_allowed=0' "$contract"
require_contains 'cli_network_allowed=0' "$contract"
require_contains 'cli_root_required=0' "$contract"
require_contains 'cli_file_write_allowed=0' "$contract"
require_contains 'cli_service_operation_allowed=0' "$contract"
require_contains 'cli_kernel_operation_allowed=0' "$contract"
require_contains 'cli_package_manager_allowed=0' "$contract"
require_contains 'cli_boot_operation_allowed=0' "$contract"
require_contains 'cli_selinux_policy_operation_allowed=0' "$contract"

require_contains 'LATTICRA STATUS REPORT' "$cli"
require_contains 'project=latticra' "$cli"
require_contains 'mode=no-effect' "$cli"
require_contains 'runtime_behavior=disabled' "$cli"
require_contains 'host_mutation=0' "$cli"
require_contains 'network=0' "$cli"
require_contains 'kernel_operation=0' "$cli"
require_contains 'service_operation=0' "$cli"
require_contains 'package_manager_operation=0' "$cli"
require_contains 'boot_operation=0' "$cli"
require_contains 'selinux_policy_operation=0' "$cli"
require_contains 'effect_authority=denied' "$cli"
require_contains 'strcmp(argv[1], "--status")' "$cli"
require_contains 'strcmp(argv[1], "--version")' "$cli"
require_contains 'strcmp(argv[1], "--report")' "$cli"

require_absent 'system(' "$cli"
require_absent 'popen(' "$cli"
require_absent 'fork(' "$cli"
require_absent 'exec' "$cli"
require_absent 'socket(' "$cli"
require_absent 'connect(' "$cli"
require_absent 'open(' "$cli"
require_absent 'fopen(' "$cli"
require_absent 'freopen(' "$cli"
require_absent 'remove(' "$cli"
require_absent 'rename(' "$cli"
require_absent 'unlink(' "$cli"
require_absent 'mkdir(' "$cli"
require_absent 'rmdir(' "$cli"
require_absent 'chmod(' "$cli"
require_absent 'chown(' "$cli"
require_absent 'mount(' "$cli"
require_absent 'setuid(' "$cli"
require_absent 'setgid(' "$cli"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-cli-status.XXXXXX")"
bin="$tmpdir/latticra"
status_out="$tmpdir/status.out"
status_expected="$tmpdir/status.expected"
report_out="$tmpdir/report.out"
version_out="$tmpdir/version.out"
version_expected="$tmpdir/version.expected"
usage_err="$tmpdir/usage.err"
usage_expected="$tmpdir/usage.expected"

cc $CFLAGS src/latticra_cli.c -o "$bin"

"$bin" --status > "$status_out"
cat > "$status_expected" <<'EOF'
LATTICRA STATUS REPORT
project=latticra
mode=no-effect
runtime_behavior=disabled
host_mutation=0
network=0
kernel_operation=0
service_operation=0
package_manager_operation=0
boot_operation=0
selinux_policy_operation=0
effect_authority=denied
EOF
cmp "$status_expected" "$status_out"

"$bin" --report > "$report_out"
cmp "$status_expected" "$report_out"

"$bin" --version > "$version_out"
cat > "$version_expected" <<'EOF'
latticra 0.0.0
mode=no-effect
runtime_behavior=disabled
EOF
cmp "$version_expected" "$version_out"

set +e
"$bin" --unknown > "$tmpdir/usage.out" 2> "$usage_err"
code="$?"
set -e

if [ "$code" -ne 2 ]; then
  printf 'latticra no-effect cli status surface: expected invalid command exit code 2, got %s\n' "$code" >&2
  exit 1
fi

cat > "$usage_expected" <<'EOF'
usage: latticra [--status|--version|--report]
EOF
cmp "$usage_expected" "$usage_err"

if [ -s "$tmpdir/usage.out" ]; then
  printf 'latticra no-effect cli status surface: invalid command wrote to stdout\n' >&2
  exit 1
fi

printf 'latticra_no_effect_cli_status_surface: ok\n'

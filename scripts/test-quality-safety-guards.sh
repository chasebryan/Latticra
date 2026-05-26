#!/usr/bin/env sh
set -eu

if [ -n "${LATTICRA_ROOT:-}" ]; then
  ROOT="$LATTICRA_ROOT"
else
  ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
fi
cd "$ROOT"

fail() {
  printf 'FAIL: %s\n' "$1" >&2
  exit 1
}

pass() {
  printf 'PASS: %s\n' "$1"
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

require_line() {
  pattern="$1"
  file="$2"

  grep -Fxq "$pattern" "$file" ||
    fail "$file must contain line: $pattern"
}

require_make_quality_prereq() {
  prereq="$1"
  quality_line="$(grep -E '^quality:' Makefile || :)"

  [ -n "$quality_line" ] ||
    fail "Makefile must declare a quality target"
  printf '%s\n' "$quality_line" | grep -Eq "(^|[[:space:]])$prereq([[:space:]]|$)" ||
    fail "Makefile quality target must include prerequisite: $prereq"
}

make_target_exists() {
  makefile="$1"
  target="$2"

  [ -f "$makefile" ] ||
    fail "missing makefile for target reference check: $makefile"

  awk -v target="$target" '
    /^[[:space:]]*#/ || /^[[:space:]]*$/ {
      next
    }
    /^[^[:space:]][^=]*:/ {
      line = $0
      sub(/:.*/, "", line)
      count = split(line, targets, /[[:space:]]+/)
      for (i = 1; i <= count; i++) {
        if (targets[i] == target) {
          found = 1
        }
      }
    }
    END {
      exit found ? 0 : 1
    }
  ' "$makefile"
}

check_workflow_make_refs() {
  workflow="$1"
  make_runs="$(grep -En '^[[:space:]]*run:[[:space:]]*make([[:space:]]|$)' "$workflow" || :)"

  [ -n "$make_runs" ] || return 0

  printf '%s\n' "$make_runs" |
    while IFS= read -r make_run; do
      command="${make_run#*:}"
      command="${command#*run:}"
      set -- $command

      [ "${1:-}" = "make" ] || continue
      shift || true

      makefile="Makefile"
      target=""
      while [ "$#" -gt 0 ]; do
        case "$1" in
          -C)
            [ "$#" -ge 2 ] ||
              fail "$workflow has make -C without a directory"
            makefile="$2/Makefile"
            shift 2
            ;;
          --directory=*)
            makefile="${1#--directory=}/Makefile"
            shift
            ;;
          -*|*=*)
            shift
            ;;
          *)
            target="$1"
            break
            ;;
        esac
      done

      [ -n "$target" ] || continue
      make_target_exists "$makefile" "$target" ||
        fail "$workflow references missing make target $target in $makefile"
    done
}

check_no_conflict_markers() {
  if command -v rg >/dev/null 2>&1; then
    conflict_markers="$(rg --hidden -n -S '^(<<<<<<<|=======|>>>>>>>)' --glob '!.git' . || :)"
  else
    conflict_markers="$(git grep -n -E '^(<<<<<<<|=======|>>>>>>>)' -- . || :)"
  fi

  [ -z "$conflict_markers" ] ||
    fail "working tree contains unresolved merge conflict markers"
}

check_status_index_completeness() {
  index="docs/status/README.md"

  [ -f "$index" ] ||
    fail "missing status index: $index"

  missing=""
  for record in docs/status/*.md; do
    [ -f "$record" ] || continue
    record_name="$(basename "$record")"

    [ "$record_name" != "README.md" ] || continue

    if ! grep -Fq "$record_name" "$index"; then
      missing="${missing}${record_name}
"
    fi
  done

  [ -z "$missing" ] ||
    fail "docs/status/README.md is missing status records:
$missing"
}

check_no_source_shell_exec() {
  for source_root in latt-field-engines src include tools; do
    [ -d "$source_root" ] || continue
    find "$source_root" -type f \( -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' \) |
      while IFS= read -r source; do
        if grep -Eq '(^|[^A-Za-z0-9_])popen[[:space:]]*\(' "$source"; then
          fail "$source must not use popen; use explicit argv process launch instead"
        fi
        if grep -Eq '(^|[^A-Za-z0-9_])system[[:space:]]*\(' "$source"; then
          fail "$source must not use system; use explicit argv process launch instead"
        fi
      done
  done
}

check_no_unsafe_c_string_apis() {
  for source_root in latt-field-engines src include tools tests; do
    [ -d "$source_root" ] || continue
    find "$source_root" -type f \( -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' \) |
      while IFS= read -r source; do
        if grep -Eq '(^|[^A-Za-z0-9_])(strcpy|strcat|sprintf|vsprintf|gets|tmpnam|tempnam)[[:space:]]*\(' "$source"; then
          fail "$source must not use unsafe C string/temp APIs; use bounded copies or private temp helpers"
        fi
      done
  done
}

check_no_unsafe_python_apis() {
  for py_root in scripts tools tests installer; do
    [ -d "$py_root" ] || continue
    find "$py_root" -type f -name '*.py' ! -path '*/target/*' |
      while IFS= read -r helper; do
        if grep -Eq 'shell[[:space:]]*=[[:space:]]*True' "$helper"; then
          fail "$helper must not use shell=True; pass explicit argv lists instead"
        fi
        if grep -Eq '(^|[^A-Za-z0-9_])(os[.]system|os[.]popen|subprocess[.](getoutput|getstatusoutput)|tempfile[.]mktemp)[[:space:]]*\(' "$helper"; then
          fail "$helper must not use shell execution helpers or tempfile.mktemp"
        fi
        if grep -Eq '(^|[^A-Za-z0-9_])(pickle[.](load|loads)|marshal[.](load|loads)|yaml[.]load)[[:space:]]*\(' "$helper"; then
          fail "$helper must not use unsafe deserialization helpers"
        fi
        if grep -Eq '(^|[^A-Za-z0-9_])(eval|exec)[[:space:]]*\(' "$helper"; then
          fail "$helper must not use Python dynamic evaluation APIs"
        fi
      done
  done
}

check_rust_installer_engine_shell_boundary() {
  engine="installer/latticra-installer/src/engine.rs"

  require_contains 'const SYSTEM_SHELL: &str = "/bin/sh";' "$engine"
  require_contains 'trusted_installer_script(&installer_root, APPLY_SCRIPT)' "$engine"
  require_contains 'trusted_installer_script(&installer_root, UNINSTALL_SCRIPT)' "$engine"
  require_contains 'regular_non_symlink_file(&script)' "$engine"

  if grep -Eq 'Command::new\("(sh|bash)"\)' "$engine"; then
    fail "$engine must use an absolute shell path instead of PATH-discovered sh/bash"
  fi
  if grep -Fq 'std::env::current_dir()' "$engine"; then
    fail "$engine must not discover installer scripts from ambient current working directory"
  fi
  unexpected_command_new="$(grep -En 'Command::new[[:space:]]*\(' "$engine" | grep -Ev 'Command::new[[:space:]]*\([[:space:]]*SYSTEM_SHELL[[:space:]]*\)' || :)"
  [ -z "$unexpected_command_new" ] ||
    fail "$engine must launch installer scripts through SYSTEM_SHELL only"

  find installer/latticra-installer/src -type f -name '*.rs' |
    while IFS= read -r source; do
      if grep -Eq '(^|[^A-Za-z0-9_])unsafe[[:space:]]*\{' "$source"; then
        fail "$source must not use Rust unsafe blocks in the installer"
      fi
      if [ "$source" != "$engine" ] &&
        grep -Eq '(^|[^A-Za-z0-9_])(Command::new|std::process::Command|use[[:space:]]+std::process::Command)' "$source"; then
        fail "$source must not add installer process launch authority outside engine.rs"
      fi
      destructive_fs="$(awk '
        /#\[cfg\(test\)\]/ {
          in_tests = 1
        }
        !in_tests && /(fs::|std::fs::)(remove_file|remove_dir_all)[[:space:]]*\(/ {
          print FNR
        }
      ' "$source")"
      [ -z "$destructive_fs" ] ||
        fail "$source must not remove files or directories outside Rust test fixtures"
      if grep -Eq 'Command::new\("(sh|bash)"\)' "$source"; then
        fail "$source must not invoke PATH-discovered sh/bash"
      fi
    done
}

check_no_c_test_fixed_latticra_tmp() {
  [ -d tests ] || return 0

  find tests -type f -name '*.c' |
    while IFS= read -r source; do
      if grep -Eq '/tmp/latticra|/private/tmp/latticra' "$source"; then
        fail "$source must use private temp fixtures or repository-relative strings instead of fixed /tmp/latticra paths"
      fi
    done
}

check_no_doc_fixed_latticra_tmp() {
  for doc_root in README.md docs; do
    [ -e "$doc_root" ] || continue
    find "$doc_root" \( -name '*.md' -o -name '*.html' \) -type f |
      while IFS= read -r doc; do
        if grep -Eq '/tmp/latticra|/private/tmp/latticra' "$doc"; then
          fail "$doc must show private mktemp workdirs instead of fixed /tmp/latticra paths"
        fi
      done
  done
}

check_workflow() {
  workflow="$1"

  grep -q '^name:' "$workflow" ||
    fail "$workflow must declare a workflow name"
  grep -q '^on:' "$workflow" ||
    fail "$workflow must declare triggers"
  grep -Eq '^[[:space:]]*pull_request:' "$workflow" ||
    fail "$workflow must run on pull_request"
  grep -Eq '^[[:space:]]*push:' "$workflow" ||
    fail "$workflow must run on push"
  grep -q '^permissions:' "$workflow" ||
    fail "$workflow must declare explicit permissions"
  grep -q '^  contents: read' "$workflow" ||
    fail "$workflow must keep repository token permissions read-only"

  runs_on_count=$(grep -Ec '^[[:space:]]*runs-on:' "$workflow" || :)
  timeout_count=$(grep -Ec '^[[:space:]]*timeout-minutes:[[:space:]]*[1-9][0-9]*[[:space:]]*$' "$workflow" || :)
  [ "$runs_on_count" -eq 0 ] ||
    [ "$timeout_count" -ge "$runs_on_count" ] ||
    fail "$workflow must set timeout-minutes for every job"

  long_timeouts="$(awk '
    /^[[:space:]]*timeout-minutes:[[:space:]]*[0-9]+[[:space:]]*$/ {
      value = $0
      sub(/^[^0-9]*/, "", value)
      sub(/[^0-9].*$/, "", value)
      if ((value + 0) > 30) {
        print NR
      }
    }
  ' "$workflow")"
  [ -z "$long_timeouts" ] ||
    fail "$workflow must keep job timeout-minutes at or below 30"

  checkout_missing_persistence="$(awk '
    /^[[:space:]]*(-[[:space:]]*)?uses:[[:space:]]*actions\/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5[[:space:]]*$/ {
      pending = NR
      next
    }
    pending && /^[[:space:]]*persist-credentials:[[:space:]]*false[[:space:]]*$/ {
      pending = 0
      next
    }
    pending && /^[[:space:]]*-[[:space:]]*(name|uses|run):/ {
      print pending
      pending = 0
    }
    END {
      if (pending) {
        print pending
      }
    }
  ' "$workflow")"
  [ -z "$checkout_missing_persistence" ] ||
    fail "$workflow must set persist-credentials: false in every checkout step"

  if grep -Eq '^[[:space:]]*[A-Za-z0-9_-]+:[[:space:]]*write([[:space:]]|$)' "$workflow"; then
    fail "$workflow must not request write-scoped token permissions"
  fi

  if grep -Eq 'permissions:[[:space:]]*(write-all|read-all)([[:space:]]|$)|^[[:space:]]*(write-all|read-all)([[:space:]]|$)' "$workflow"; then
    fail "$workflow must not request broad token permissions"
  fi

  if grep -Eq 'pull_request_target:' "$workflow"; then
    fail "$workflow must not use pull_request_target"
  fi

  if grep -Eq 'continue-on-error:' "$workflow"; then
    fail "$workflow must not use continue-on-error"
  fi

  if grep -Eq 'secrets\.' "$workflow"; then
    fail "$workflow must not consume repository secrets without a dedicated review guard"
  fi

  if grep -Eq 'github\.token|GITHUB_TOKEN|GH_TOKEN|ACTIONS_ID_TOKEN|ACTIONS_RUNTIME_TOKEN' "$workflow"; then
    fail "$workflow must not consume implicit GitHub token surfaces without a dedicated review guard"
  fi

  if grep -Eq '^[[:space:]]*(run:[[:space:]]*)?(curl|wget|ssh|scp|sftp|ftp|nc|ncat|telnet)[[:space:]]' "$workflow"; then
    fail "$workflow must not add ad hoc network client commands without a dedicated review guard"
  fi

  privilege_lines="$(grep -En '^[[:space:]]*(run:[[:space:]]*)?(sudo|su|doas)[[:space:]]' "$workflow" || :)"
  if [ -n "$privilege_lines" ]; then
    case "$workflow" in
      .github/workflows/quality.yml|.github/workflows/latticra-panel-installer.yml)
        unexpected_privilege_lines="$(printf '%s\n' "$privilege_lines" | grep -Ev ':[[:space:]]*sudo[[:space:]]+apt-get[[:space:]]+(update|install[[:space:]]+-y)([[:space:]]|\\|$)' || :)"
        ;;
      *)
        fail "$workflow must not add privilege escalation commands outside reviewed bootstrap workflows"
        ;;
    esac

    [ -z "$unexpected_privilege_lines" ] ||
      fail "$workflow privilege escalation commands must stay on the reviewed bootstrap allowlist"
  fi

  package_manager_lines="$(grep -En '(^|[[:space:]])(sudo[[:space:]]+)?(apt-get|apt|dnf|yum|zypper|brew|pip[0-9]*|python[0-9]*[[:space:]]+-m[[:space:]]+pip|npm|pnpm|yarn)([[:space:]]|$)' "$workflow" || :)"
  if [ -n "$package_manager_lines" ]; then
    case "$workflow" in
      .github/workflows/quality.yml|.github/workflows/latticra-panel-installer.yml)
        unexpected_package_lines="$(printf '%s\n' "$package_manager_lines" | grep -Ev ':[[:space:]]*sudo[[:space:]]+apt-get[[:space:]]+(update|install[[:space:]]+-y)([[:space:]]|$)' || :)"
        ;;
      .github/workflows/compat-linux.yml|.github/workflows/fedora-build-lane.yml|.github/workflows/fedora-rpmlint-availability.yml|.github/workflows/fedora-rpmlint-static-spec-lane.yml)
        unexpected_package_lines="$(printf '%s\n' "$package_manager_lines" | grep -Ev ':[[:space:]]*run:[[:space:]]*dnf[[:space:]]+-y[[:space:]]+install[[:space:]]+git[[:space:]]+tar[[:space:]]+gzip[[:space:]]*$' || :)"
        ;;
      .github/workflows/opensuse-rpmlint-osc-availability.yml|.github/workflows/opensuse-rpmlint-static-spec-lane.yml)
        unexpected_package_lines="$(printf '%s\n' "$package_manager_lines" | grep -Ev ':[[:space:]]*run:[[:space:]]*zypper[[:space:]]+--non-interactive[[:space:]]+install[[:space:]]+git[[:space:]]+tar[[:space:]]+gzip[[:space:]]*$' || :)"
        ;;
      *)
        fail "$workflow must not add package-manager commands outside reviewed bootstrap workflows"
        ;;
    esac

    [ -z "$unexpected_package_lines" ] ||
      fail "$workflow package-manager commands must stay on the reviewed bootstrap allowlist"
  fi

  if grep -Eq 'curl[^|]*\|[[:space:]]*(sh|bash)|wget[^|]*\|[[:space:]]*(sh|bash)|bash[[:space:]]+<|sh[[:space:]]+<' "$workflow"; then
    fail "$workflow must not pipe remote content into a shell"
  fi

  if grep -Eq 'git[[:space:]]+reset[[:space:]]+--hard|chmod[[:space:]]+-R[[:space:]]+777|rm[[:space:]]+-rf[[:space:]]+/' "$workflow"; then
    fail "$workflow contains an unsafe broad mutation command"
  fi

  action_refs="$(sed -nE 's/^[[:space:]]*(-[[:space:]]*)?uses:[[:space:]]*([^[:space:]]+).*/\2/p' "$workflow")"
  for action_ref in $action_refs; do
    case "$action_ref" in
      ./*|../*)
        continue
        ;;
    esac

    case "$action_ref" in
      *@*) ;;
      *) fail "$workflow uses an unpinned action reference: $action_ref" ;;
    esac

    action_pin="${action_ref##*@}"
    printf '%s\n' "$action_pin" | grep -Eq '^[0-9a-f]{40}$' ||
      fail "$workflow must pin external action refs to a 40-character commit SHA: $action_ref"

    case "$action_ref" in
      actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5 | \
        dtolnay/rust-toolchain@29eef336d9b2848a0b548edc03f92a220660cdb8)
        ;;
      *)
        fail "$workflow uses an unapproved external action ref: $action_ref"
        ;;
    esac
  done

  script_refs="$(grep -Eo '(scripts|installer/scripts)/[A-Za-z0-9._/-]+\.sh' "$workflow" || :)"
  for script_ref in $script_refs; do
    [ -f "$script_ref" ] ||
      fail "$workflow references missing guard script $script_ref"
  done

  check_workflow_make_refs "$workflow"
}

check_makefile_script_refs() {
  script_refs="$(grep -Eo '(scripts|installer/scripts)/[A-Za-z0-9._/-]+\.sh' Makefile || :)"
  for script_ref in $script_refs; do
    [ -f "$script_ref" ] ||
      fail "Makefile references missing guard script $script_ref"
  done
}

check_shell_script() {
  script="$1"

  if [ "$script" != "scripts/test-quality-safety-guards.sh" ]; then
    sh -n "$script" ||
      fail "$script failed shell syntax validation"
  fi

  if ! sed -n '1,6p' "$script" | grep -Eq '^set -e'; then
    fail "$script must enable fail-fast shell behavior near the top"
  fi

  if grep -Eq 'eval[[:space:]]' "$script"; then
    fail "$script must not use eval"
  fi

  if grep -Eq 'curl[^|]*\|[[:space:]]*(sh|bash)|wget[^|]*\|[[:space:]]*(sh|bash)|bash[[:space:]]+<|sh[[:space:]]+<' "$script"; then
    fail "$script must not pipe remote content into a shell"
  fi

  if grep -Eq '^[[:space:]]*(curl|wget|ssh|scp|sftp|ftp|nc|ncat|telnet)[[:space:]]' "$script"; then
    fail "$script must not add ad hoc network client commands without a dedicated review guard"
  fi

  if grep -Eq 'mktemp[[:space:]]+-u|chmod[[:space:]]+-R[[:space:]]+777|rm[[:space:]]+-rf[[:space:]]+/' "$script"; then
    fail "$script contains an unsafe broad mutation command"
  fi

  privilege_lines="$(grep -En '^[[:space:]]*(sudo|su|doas)[[:space:]]' "$script" || :)"
  if [ -n "$privilege_lines" ]; then
    case "$script" in
      scripts/test-ubuntu-build-lane.sh|scripts/test-ubuntu-lintian-availability.sh)
        unexpected_privilege_lines="$(printf '%s\n' "$privilege_lines" | grep -Ev ':[[:space:]]*sudo[[:space:]]+(apt-get[[:space:]]+update|env[[:space:]]+DEBIAN_FRONTEND=noninteractive[[:space:]]+apt-get[[:space:]]+install[[:space:]]+-y[[:space:]]+"\$@")[[:space:]]*$' || :)"
        ;;
      scripts/test-opensuse-rpmlint-osc-availability.sh)
        unexpected_privilege_lines="$(printf '%s\n' "$privilege_lines" | grep -Ev ':[[:space:]]*sudo[[:space:]]+zypper[[:space:]]+--non-interactive[[:space:]]+(refresh|install[[:space:]]+--force-resolution[[:space:]]+"\$@")[[:space:]]*$' || :)"
        ;;
      scripts/run-fedora-vm-cli-payload-validation-lane.sh)
        unexpected_privilege_lines="$(printf '%s\n' "$privilege_lines" | grep -Ev ':[[:space:]]*sudo[[:space:]]+rpm[[:space:]]+(-Uvh[[:space:]]+--nodeps[[:space:]]+"\$rpm_path"|-e[[:space:]]+"\$name")[[:space:]]*$' || :)"
        ;;
      *)
        fail "$script must not add privilege escalation commands outside reviewed packaging lanes"
        ;;
    esac

    [ -z "$unexpected_privilege_lines" ] ||
      fail "$script privilege escalation commands must stay on the reviewed packaging allowlist"
  fi

  package_manager_mutation_lines="$(grep -En '^[[:space:]]*((sudo[[:space:]]+)?(apt-get|zypper)|env[[:space:]]+DEBIAN_FRONTEND=noninteractive[[:space:]]+apt-get|sudo[[:space:]]+env[[:space:]]+DEBIAN_FRONTEND=noninteractive[[:space:]]+apt-get|sudo[[:space:]]+rpm[[:space:]]+(-Uvh|-e))([[:space:]]|$)' "$script" || :)"
  if [ -n "$package_manager_mutation_lines" ]; then
    case "$script" in
      scripts/test-ubuntu-build-lane.sh|scripts/test-ubuntu-lintian-availability.sh)
        unexpected_package_mutation_lines="$(printf '%s\n' "$package_manager_mutation_lines" | grep -Ev ':[[:space:]]*(sudo[[:space:]]+)?(apt-get[[:space:]]+update|env[[:space:]]+DEBIAN_FRONTEND=noninteractive[[:space:]]+apt-get[[:space:]]+install[[:space:]]+-y[[:space:]]+"\$@")[[:space:]]*$' || :)"
        ;;
      scripts/test-opensuse-rpmlint-osc-availability.sh)
        unexpected_package_mutation_lines="$(printf '%s\n' "$package_manager_mutation_lines" | grep -Ev ':[[:space:]]*(sudo[[:space:]]+)?zypper[[:space:]]+--non-interactive[[:space:]]+(refresh|install[[:space:]]+--force-resolution[[:space:]]+"\$@")[[:space:]]*$' || :)"
        ;;
      scripts/run-fedora-vm-cli-payload-validation-lane.sh)
        unexpected_package_mutation_lines="$(printf '%s\n' "$package_manager_mutation_lines" | grep -Ev ':[[:space:]]*sudo[[:space:]]+rpm[[:space:]]+(-Uvh[[:space:]]+--nodeps[[:space:]]+"\$rpm_path"|-e[[:space:]]+"\$name")[[:space:]]*$' || :)"
        ;;
      *)
        fail "$script must not add package-manager mutation commands outside reviewed packaging lanes"
        ;;
    esac

    [ -z "$unexpected_package_mutation_lines" ] ||
      fail "$script package-manager mutation commands must stay on the reviewed packaging allowlist"
  fi

  if grep -Fq 'mktemp -d' "$script" &&
    ! grep -Eq 'trap[[:space:]].*(rm -rf|cleanup)' "$script"; then
    fail "$script must register a cleanup trap for mktemp workdirs"
  fi

  if grep -Fq '$''$' "$script"; then
    fail "$script must not use PID-based temporary paths"
  fi

  if [ "$script" != "scripts/test-quality-safety-guards.sh" ]; then
    if grep -Eq '/tmp/latticra|/private/tmp/latticra|-o[[:space:]]+/tmp/latticra|>[[:space:]]*/tmp/latticra' "$script"; then
      fail "$script must use a private mktemp workdir instead of fixed /tmp/latticra paths"
    fi
  fi

  if grep -Eq '^[[:space:]]*cc[[:space:]]' "$script" &&
    grep -Eq '^[[:space:]]*src/runtime_boundary\.c[[:space:]]*\\[[:space:]]*$' "$script"; then
    grep -Eq '^[[:space:]]*src/lat_parser\.c[[:space:]]*\\[[:space:]]*$' "$script" ||
      fail "$script runtime-boundary compile must include src/lat_parser.c for parse-error labels"
    require_contains 'mktemp -d' "$script"
    require_contains 'trap '\''rm -rf "$tmpdir"'\'' EXIT INT HUP TERM' "$script"
    if grep -Eq '(^|[[:space:]])-o[[:space:]]*"?/tmp/latticra|^[[:space:]]*"?/tmp/latticra' "$script"; then
      fail "$script runtime-boundary compile must use its private mktemp workdir"
    fi
  fi

  case "$script" in
    scripts/*report-runner.sh)
      if grep -Eq '/tmp/latticra|-o[[:space:]]+/tmp/latticra|>[[:space:]]*/tmp/latticra' "$script"; then
        fail "$script must use a private mktemp workdir instead of fixed /tmp/latticra paths"
      fi
      require_contains 'mktemp -d' "$script"
      require_contains 'trap '\''rm -rf "$tmpdir"'\'' EXIT INT HUP TERM' "$script"
      ;;
    scripts/test-kernel.sh|scripts/test-kernel-lifecycle.sh|scripts/test-kernel-lifecycle-subsystem-summary.sh|scripts/test-kernel-memory-map.sh|scripts/test-kernel-scheduler.sh|scripts/test-kernel-state.sh|scripts/test-kernel-state-machine.sh|scripts/test-kernel-subsystem-registry.sh)
      if grep -Eq '/tmp/latticra|-o[[:space:]]+/tmp/latticra|>[[:space:]]*/tmp/latticra' "$script"; then
        fail "$script must use a private mktemp workdir instead of fixed /tmp/latticra paths"
      fi
      require_contains 'mktemp -d' "$script"
      require_contains 'trap '\''rm -rf "$tmpdir"'\'' EXIT INT HUP TERM' "$script"
      ;;
    scripts/test-latticra-seal*.sh|scripts/latticra-seal-*.sh|scripts/demo-latticra-seal.sh)
      if grep -Eq '/tmp/latticra-seal|-o[[:space:]]+/tmp/latticra-seal|>[[:space:]]*/tmp/latticra-seal' "$script"; then
        fail "$script must use a private mktemp workdir instead of fixed /tmp/latticra-seal paths"
      fi
      if grep -Fq '$tmpdir/latticra-seal' "$script"; then
        require_contains 'mktemp -d' "$script"
        require_contains 'trap '\''rm -rf "$tmpdir"'\'' EXIT INT HUP TERM' "$script"
      fi
      ;;
    scripts/test-l-ui-*.sh|scripts/test-lat-*.sh|scripts/test-lat-to-lir-*.sh|scripts/test-lir-*.sh)
      if grep -Eq '/tmp/latticra-l|-o[[:space:]]+/tmp/latticra-l|>[[:space:]]*/tmp/latticra-l' "$script"; then
        fail "$script must use a private mktemp workdir instead of fixed /tmp/latticra-l paths"
      fi
      if grep -Fq '$tmpdir/latticra-l' "$script"; then
        require_contains 'mktemp -d' "$script"
        require_contains 'trap '\''rm -rf "$tmpdir"'\'' EXIT INT HUP TERM' "$script"
      fi
      ;;
    scripts/test-nucleus*.sh|scripts/test-fedora*.sh)
      if grep -Eq '/tmp/latticra-(nucleus|fedora)|-o[[:space:]]+/tmp/latticra-(nucleus|fedora)|>[[:space:]]*/tmp/latticra-(nucleus|fedora)' "$script"; then
        fail "$script must use a private mktemp workdir instead of fixed /tmp/latticra-nucleus or /tmp/latticra-fedora paths"
      fi
      if grep -Eq '\$tmpdir/latticra-(nucleus|fedora)' "$script"; then
        require_contains 'mktemp -d' "$script"
        require_contains 'trap '\''rm -rf "$tmpdir"'\'' EXIT INT HUP TERM' "$script"
      fi
      ;;
    scripts/test-nadia-local-context-engine-stage-1.sh|scripts/test-nadia-runtime-profile-stage-2.sh|scripts/test-nadia-developer-workbench-stage-3.sh|scripts/test-nadia-systems-engineering-mode-stage-4.sh|scripts/test-nadia-productivity-loop-stage-5.sh|scripts/test-nadia-protective-safety-boundary-stage-6.sh|scripts/test-nadia-guarded-tool-authority-stage-7.sh|scripts/test-nadia-prompt-evaluation-contract-stage-8.sh|scripts/test-nadia-local-model-registry-contract-stage-9.sh|scripts/test-nadia-inference-readiness-contract-stage-10.sh|scripts/test-nadia-runtime-invocation-contract-stage-11.sh|scripts/test-nadia-model-load-contract-stage-12.sh|scripts/test-nadia-context-window-assembly-contract-stage-27.sh|scripts/test-nadia-prompt-evaluation-input-contract-stage-28.sh|scripts/test-nadia-prompt-evaluation-runtime-handoff-contract-stage-29.sh)
      if grep -Eq '/tmp/latticra-nadia|/private/tmp/latticra-nadia|>[[:space:]]*/tmp/latticra-nadia' "$script"; then
        fail "$script must use a private mktemp workdir instead of fixed Nadia /tmp paths"
      fi
      require_contains 'mktemp -d' "$script"
      require_contains 'trap '\''rm -rf "$tmpdir"'\'' EXIT INT HUP TERM' "$script"
      ;;
  esac

  if grep -q 'CFLAGS:=' "$script"; then
    for flag in -Wall -Wextra -Werror; do
      grep -q -- "$flag" "$script" ||
        fail "$script CFLAGS must include $flag"
    done
  fi

  case "$script" in
    scripts/test-*.sh|scripts/latticra-seal-*.sh)
      if grep -Eq '^[[:space:]]*(cc|gcc|clang|\$CC)[[:space:]]' "$script"; then
        for flag in -Wall -Wextra -Werror; do
          grep -q -- "$flag" "$script" ||
            fail "$script C compiler invocations must keep strict warning flag $flag"
        done
      fi
      ;;
  esac

  if grep -q 'CXXFLAGS:=' "$script"; then
    for flag in -Wall -Wextra -Werror; do
      grep -q -- "$flag" "$script" ||
        fail "$script CXXFLAGS must include $flag"
    done
  fi

  case "$script" in
    scripts/test-*.sh|scripts/latticra-seal-*.sh)
      if grep -Eq '^[[:space:]]*(c\+\+|g\+\+|clang\+\+|\$CXX)[[:space:]]' "$script"; then
        for flag in -Wall -Wextra -Werror; do
          grep -q -- "$flag" "$script" ||
            fail "$script C++ compiler invocations must keep strict warning flag $flag"
        done
      fi
      ;;
  esac

  if [ "$script" = "installer/scripts/latticra-installer-apply.sh" ]; then
    bad_cargo_builds=$(grep -n 'cargo build' "$script" | grep -Ev -- '--locked.*--offline|--offline.*--locked' || :)
    [ -z "$bad_cargo_builds" ] ||
      fail "$script cargo builds must use locked offline dependencies"

    require_contains "path_has_parent_reference()" "$script"
    require_contains "refusing install prefix with parent-directory traversal" "$script"
    require_contains "refusing symlink install prefix" "$script"
    require_contains "refusing symlink payload source" "$script"
    require_contains "refusing payload tree with symlink entry" "$script"
  fi

  if [ "$script" = "installer/scripts/latticra-installer-uninstall.sh" ]; then
    require_contains "path_has_parent_reference()" "$script"
    require_contains "parent-directory traversal" "$script"
    require_contains "refusing to reset symlink prefix" "$script"
  fi
}

workflow_count=0
check_no_conflict_markers
check_status_index_completeness
check_no_source_shell_exec
check_no_unsafe_c_string_apis
check_no_unsafe_python_apis
check_rust_installer_engine_shell_boundary
check_no_c_test_fixed_latticra_tmp
check_no_doc_fixed_latticra_tmp

for workflow in .github/workflows/*.yml .github/workflows/*.yaml; do
  [ -f "$workflow" ] || continue
  workflow_count=$((workflow_count + 1))
  check_workflow "$workflow"
done

[ "$workflow_count" -gt 0 ] ||
  fail "no GitHub workflow files found"

check_makefile_script_refs

require_contains "quality-safety-guards:" "Makefile"
for prereq in quality-worktree quality-safety-guards quality-defensive-threat-model quality-security-standards seal-policy-denials quality-rust-installer quality-panel-installer quality-installer-readiness quality-nadia quality-c-foundation; do
  require_make_quality_prereq "$prereq"
done
require_contains "git diff --check" "Makefile"
require_contains "test-quality-safety-guards.sh" "Makefile"
require_contains "sh ./scripts/test-defensive-threat-model-contract.sh" "Makefile"
require_contains "sh ./scripts/test-defensive-threat-model-implementation-plan.sh" "Makefile"
require_contains "sh ./scripts/test-defensive-threat-model-validation.sh" "Makefile"
require_contains "quality-security-standards:" "Makefile"
require_contains "sh ./scripts/test-defensive-threat-model-validation-refinement.sh" "Makefile"
require_contains "sh ./scripts/test-high-assurance-security-baseline.sh" "Makefile"
require_contains "high-assurance-security-baseline:" "Makefile"
require_contains "cargo fmt --manifest-path installer/latticra-installer/Cargo.toml -- --check" "Makefile"
require_contains "cargo check --locked --manifest-path installer/latticra-installer/Cargo.toml" "Makefile"
require_contains "python3 scripts/check_latticra_panel_ui_design.py" "Makefile"
require_contains "sh ./scripts/test-latticra-panel-local-install-evidence-status.sh" "Makefile"
require_contains "sh ./scripts/test-latticra-panel-local-install-public-entrypoint-alignment.sh" "Makefile"
require_contains "sh ./scripts/test-latticra-panel-local-uninstall-reset.sh" "Makefile"
require_contains "sh ./scripts/test-production-installer-readiness-contract.sh" "Makefile"
require_contains "sh ./scripts/test-local-installer-artifact-manifest-contract.sh" "Makefile"
require_contains "sh ./scripts/test-local-artifact-manifest-fixture.sh" "Makefile"
require_contains "sh ./scripts/test-seabios-grub-compatibility-contract.sh" "Makefile"
require_contains "sh ./scripts/test-seabios-grub-boot-preview-evidence-contract.sh" "Makefile"
require_contains "sh ./scripts/test-seabios-grub-boot-preview-preflight.sh" "Makefile"
require_contains "sh ./scripts/test-seabios-grub-boot-preview-evidence-template.sh" "Makefile"
require_contains "sh ./scripts/test-seabios-grub-boot-preview-qemu-argv-template.sh" "Makefile"
require_contains "sh ./scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-template.sh" "Makefile"
require_contains "sh ./scripts/test-seabios-grub-boot-preview-boot-artifact-manifest-validate.sh" "Makefile"
require_contains "macos-reset-uninstall-live-denial-transcript:" "Makefile"
require_contains "sh ./scripts/test-macos-reset-uninstall-live-denial-transcript-contract.sh" "Makefile"
require_contains "macos-reset-uninstall-live-runner-interface:" "Makefile"
require_contains "sh ./scripts/test-macos-reset-uninstall-live-runner-interface-contract.sh" "Makefile"
require_contains "macos-reset-uninstall-live-runner-noop-prototype:" "Makefile"
require_contains "sh ./scripts/test-macos-reset-uninstall-live-runner-noop-prototype-contract.sh" "Makefile"
require_contains "macos-reset-uninstall-live-runner-denied-dispatch-transcript:" "Makefile"
require_contains "sh ./scripts/test-macos-reset-uninstall-live-runner-denied-dispatch-transcript-contract.sh" "Makefile"
require_contains "sh ./scripts/test-nadia-command-surface.sh" "Makefile"
require_contains "sh ./scripts/test-nadia-prompt-evaluation-result-review-contract-stage-32.sh" "Makefile"
require_contains "sh ./scripts/test-nadia-prompt-evaluation-result-disposition-contract-stage-33.sh" "Makefile"
require_contains "sh ./scripts/test-nadia-prompt-evaluation-result-release-contract-stage-34.sh" "Makefile"
require_contains "sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-contract-stage-35.sh" "Makefile"
require_contains "sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-review-contract-stage-36.sh" "Makefile"
require_contains "sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.sh" "Makefile"
require_contains "sh ./scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.sh" "Makefile"
require_contains "sh ./scripts/nadia-prompt-evaluation-result-release-contract.sh" "Makefile"
require_contains "sh ./scripts/nadia-prompt-evaluation-result-release-receipt-contract.sh" "Makefile"
require_contains "sh ./scripts/nadia-prompt-evaluation-result-release-receipt-review-contract.sh" "Makefile"
require_contains "sh ./scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract.sh" "Makefile"
require_contains "sh ./scripts/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract.sh" "Makefile"
require_contains "sh ./scripts/test-latticra-console-foundation.sh" "Makefile"
require_contains "sh ./scripts/test-cpp-authority-layer.sh" "Makefile"
require_contains "sh ./scripts/test-kernel-timer-source.sh" "Makefile"
require_contains "sh ./scripts/test-kernel-timer-source-report-runner.sh" "Makefile"
require_contains "sh ./scripts/test-kernel-scheduler-tick.sh" "Makefile"
require_contains "sh ./scripts/test-kernel-scheduler-tick-report-runner.sh" "Makefile"
require_contains "sh ./scripts/test-kernel-run-queue.sh" "Makefile"
require_contains "sh ./scripts/test-kernel-run-queue-report-runner.sh" "Makefile"
require_contains "sh ./scripts/test-kernel-context-switch.sh" "Makefile"
require_contains "sh ./scripts/test-kernel-context-switch-report-runner.sh" "Makefile"
require_contains "make quality" ".github/workflows/quality.yml"
require_contains "uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5" ".github/workflows/quality.yml"
require_contains "persist-credentials: false" ".github/workflows/quality.yml"
require_contains "uses: dtolnay/rust-toolchain@29eef336d9b2848a0b548edc03f92a220660cdb8" ".github/workflows/quality.yml"
require_contains "gcc \\" ".github/workflows/quality.yml"
require_contains "g++ \\" ".github/workflows/quality.yml"
require_contains "timeout-minutes: 20" ".github/workflows/quality.yml"
require_contains "make quality-safety-guards" ".github/workflows/quality-safety-guards.yml"
require_contains "uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5" ".github/workflows/quality-safety-guards.yml"
require_contains "persist-credentials: false" ".github/workflows/quality-safety-guards.yml"
require_contains "timeout-minutes: 10" ".github/workflows/quality-safety-guards.yml"
require_contains "sh scripts/test-nadia-prompt-evaluation-result-release-contract-stage-34.sh" ".github/workflows/nadia-prompt-evaluation-result-release-contract-stage-34.yml"
require_contains "sh scripts/test-nadia-prompt-evaluation-result-release-receipt-contract-stage-35.sh" ".github/workflows/nadia-prompt-evaluation-result-release-receipt-contract-stage-35.yml"
require_contains "sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-contract-stage-36.sh" ".github/workflows/nadia-prompt-evaluation-result-release-receipt-review-contract-stage-36.yml"
require_contains "sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.sh" ".github/workflows/nadia-prompt-evaluation-result-release-receipt-review-disposition-contract-stage-37.yml"
require_contains "sh scripts/test-nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.sh" ".github/workflows/nadia-prompt-evaluation-result-release-receipt-review-disposition-release-contract-stage-38.yml"
require_contains "cargo check --locked --manifest-path installer/latticra-installer/Cargo.toml" ".github/workflows/latticra-panel-installer.yml"
require_contains "uses: dtolnay/rust-toolchain@29eef336d9b2848a0b548edc03f92a220660cdb8" ".github/workflows/latticra-panel-installer.yml"
require_contains "persist-credentials: false" ".github/workflows/latticra-panel-installer.yml"
require_line "make quality" "README.md"
require_line "make quality-safety-guards" "README.md"
require_line "make quality" "CONTRIBUTING.md"
require_line "make quality-safety-guards" "CONTRIBUTING.md"

script_count=0
for script in scripts/*.sh installer/scripts/*.sh; do
  [ -f "$script" ] || continue
  script_count=$((script_count + 1))
  check_shell_script "$script"
done

[ "$script_count" -gt 0 ] ||
  fail "no shell guard scripts found"

for helper in scripts/*.py; do
  [ -f "$helper" ] || continue
  if grep -Eq '/tmp/latticra|/private/tmp/latticra' "$helper"; then
    fail "$helper must not hardcode Latticra helper inputs under shared /tmp"
  fi
done

pass "quality safety guards validated workflows=$workflow_count scripts=$script_count"

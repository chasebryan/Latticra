#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c11 -Wall -Wextra -Werror}"

ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$ROOT"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-manifest-command.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

fail() {
  printf 'FAIL: %s\n' "$1" >&2
  exit 1
}

require_contains() {
  pattern="$1"
  file="$2"

  grep -Fq "$pattern" "$file" ||
    fail "$file must contain: $pattern"
}

OPENSSL_CFLAGS="${OPENSSL_CFLAGS:-}"
OPENSSL_LIBS="${OPENSSL_LIBS:-}"

if [ -z "$OPENSSL_CFLAGS$OPENSSL_LIBS" ] && command -v pkg-config >/dev/null 2>&1; then
  if pkg-config --exists openssl; then
    OPENSSL_CFLAGS="$(pkg-config --cflags openssl)"
    OPENSSL_LIBS="$(pkg-config --libs openssl)"
  fi
fi

if [ -z "$OPENSSL_LIBS" ]; then
  OPENSSL_LIBS="-lcrypto"
fi

$CC $CFLAGS $OPENSSL_CFLAGS -Iinclude \
  seal/latticra-seal.c \
  src/seal_hybrid_envelope.c \
  src/seal_hybrid_provider_self_test.c \
  $OPENSSL_LIBS \
  -o "$tmpdir/latticra-seal"

write_manifest() {
  case_dir="$1"
  schema_line="$2"
  project_name_line="$3"
  seal_status_line="$4"

  mkdir "$case_dir"
  cat > "$case_dir/latticra.seal" <<MANIFEST
$schema_line
format = "toml"
kind = "local-integrity-manifest"

[project]
$project_name_line
version = "0.1.0"

[seal]
mode = "local-integrity"
$seal_status_line
algorithm = "sha256"
digest_encoding = "hex"
canonicalization = "relative-path + raw-bytes + unix-lf-preferred"
trust_boundary = "project-root"
MANIFEST
}

valid_case="$tmpdir/valid-case"
mkdir "$valid_case"
cp latticra.seal "$valid_case/latticra.seal"

if ! (cd "$valid_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/valid.out" 2> "$tmpdir/valid.err"); then
  cat "$tmpdir/valid.out" >&2 || true
  cat "$tmpdir/valid.err" >&2 || true
  fail "Seal manifest summary must pass for the repository manifest"
fi

require_contains "Schema: latticra.seal/v0.1" "$tmpdir/valid.out"
require_contains "Format: toml" "$tmpdir/valid.out"
require_contains "Canonicalization: relative-path + raw-bytes + unix-lf-preferred" "$tmpdir/valid.out"

bad_schema_case="$tmpdir/bad-schema-case"
write_manifest "$bad_schema_case" 'schema = "latticra.seal/v9.9"' 'name = "Latticra"' 'status = "unsigned"'

if (cd "$bad_schema_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/bad-schema.out" 2> "$tmpdir/bad-schema.err"); then
  fail "Seal manifest summary must fail closed on unsupported schema values"
fi

require_contains "Schema: latticra.seal/v9.9 (unsupported)" "$tmpdir/bad-schema.out"
require_contains "manifest summary failed" "$tmpdir/bad-schema.err"

missing_status_case="$tmpdir/missing-status-case"
write_manifest "$missing_status_case" 'schema = "latticra.seal/v0.1"' 'name = "Latticra"' '# status intentionally omitted'

if (cd "$missing_status_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/missing-status.out" 2> "$tmpdir/missing-status.err"); then
  fail "Seal manifest summary must fail closed on missing required fields"
fi

require_contains "Seal Status: missing" "$tmpdir/missing-status.out"
require_contains "manifest summary failed" "$tmpdir/missing-status.err"

duplicate_schema_case="$tmpdir/duplicate-schema-case"
write_manifest "$duplicate_schema_case" 'schema = "latticra.seal/v0.1"
schema = "latticra.seal/v0.1"' 'name = "Latticra"' 'status = "unsigned"'

if (cd "$duplicate_schema_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/duplicate-schema.out" 2> "$tmpdir/duplicate-schema.err"); then
  fail "Seal manifest summary must fail closed on duplicate required fields"
fi

require_contains "Schema: duplicate" "$tmpdir/duplicate-schema.out"
require_contains "manifest summary failed" "$tmpdir/duplicate-schema.err"

malformed_schema_case="$tmpdir/malformed-schema-case"
write_manifest "$malformed_schema_case" 'schema = latticra.seal/v0.1' 'name = "Latticra"' 'status = "unsigned"'

if (cd "$malformed_schema_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/malformed-schema.out" 2> "$tmpdir/malformed-schema.err"); then
  fail "Seal manifest summary must fail closed on malformed required fields"
fi

require_contains "Schema: malformed" "$tmpdir/malformed-schema.out"
require_contains "manifest summary failed" "$tmpdir/malformed-schema.err"

empty_project_case="$tmpdir/empty-project-case"
write_manifest "$empty_project_case" 'schema = "latticra.seal/v0.1"' 'name = ""' 'status = "unsigned"'

if (cd "$empty_project_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/empty-project.out" 2> "$tmpdir/empty-project.err"); then
  fail "Seal manifest summary must fail closed on empty required fields"
fi

require_contains "Project: empty" "$tmpdir/empty-project.out"
require_contains "manifest summary failed" "$tmpdir/empty-project.err"

printf 'PASS: Latticra Seal manifest command fails closed on invalid summaries\n'

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
id = "latticra"
version = "0.1.0"
repository = "https://github.com/Bryforge/Latticra"
license = "SEE LICENSE"

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
require_contains "Manifest Sections: supported" "$tmpdir/valid.out"
require_contains "Project ID: latticra" "$tmpdir/valid.out"
require_contains "Repository: https://github.com/Bryforge/Latticra" "$tmpdir/valid.out"
require_contains "License: SEE LICENSE" "$tmpdir/valid.out"
require_contains "Canonicalization: relative-path + raw-bytes + unix-lf-preferred" "$tmpdir/valid.out"

hardlink_manifest_case="$tmpdir/hardlink-manifest-case"
mkdir "$hardlink_manifest_case"
hardlink_manifest_source="$tmpdir/hardlink-manifest-source"
cp latticra.seal "$hardlink_manifest_source"
ln "$hardlink_manifest_source" "$hardlink_manifest_case/latticra.seal"

if (cd "$hardlink_manifest_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/hardlink-manifest.out" 2> "$tmpdir/hardlink-manifest.err"); then
  fail "Seal manifest summary must fail closed on hard-linked manifests"
fi

require_contains "could not read latticra.seal" "$tmpdir/hardlink-manifest.err"

nul_manifest_case="$tmpdir/nul-manifest-case"
mkdir "$nul_manifest_case"
cp latticra.seal "$nul_manifest_case/latticra.seal"
printf '\000ignored_after_nul = "true"\n' >> "$nul_manifest_case/latticra.seal"

if (cd "$nul_manifest_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/nul-manifest.out" 2> "$tmpdir/nul-manifest.err"); then
  fail "Seal manifest summary must fail closed on manifests with embedded NUL bytes"
fi

require_contains "could not read latticra.seal" "$tmpdir/nul-manifest.err"

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

missing_project_id_case="$tmpdir/missing-project-id-case"
mkdir "$missing_project_id_case"
sed '/^id = "latticra"$/d' latticra.seal > "$missing_project_id_case/latticra.seal"

if (cd "$missing_project_id_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/missing-project-id.out" 2> "$tmpdir/missing-project-id.err"); then
  fail "Seal manifest summary must fail closed on missing project identity fields"
fi

require_contains "Project ID: missing" "$tmpdir/missing-project-id.out"
require_contains "manifest summary failed" "$tmpdir/missing-project-id.err"

unsupported_project_id_case="$tmpdir/unsupported-project-id-case"
mkdir "$unsupported_project_id_case"
sed 's/id = "latticra"/id = "other-project"/' latticra.seal > "$unsupported_project_id_case/latticra.seal"

if (cd "$unsupported_project_id_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/unsupported-project-id.out" 2> "$tmpdir/unsupported-project-id.err"); then
  fail "Seal manifest summary must fail closed on unsupported project identity fields"
fi

require_contains "Project ID: other-project (unsupported)" "$tmpdir/unsupported-project-id.out"
require_contains "manifest summary failed" "$tmpdir/unsupported-project-id.err"

unsupported_section_case="$tmpdir/unsupported-section-case"
mkdir "$unsupported_section_case"
cp latticra.seal "$unsupported_section_case/latticra.seal"
printf '\n[unsupported]\nclaim = "ignored"\n' >> "$unsupported_section_case/latticra.seal"

if (cd "$unsupported_section_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/unsupported-section.out" 2> "$tmpdir/unsupported-section.err"); then
  fail "Seal manifest summary must fail closed on unsupported manifest sections"
fi

require_contains "Manifest Sections: malformed or unsupported" "$tmpdir/unsupported-section.out"
require_contains "manifest summary failed" "$tmpdir/unsupported-section.err"

quoted_unsupported_section_case="$tmpdir/quoted-unsupported-section-case"
mkdir "$quoted_unsupported_section_case"
cp latticra.seal "$quoted_unsupported_section_case/latticra.seal"
printf '\n["unsupported"]\nclaim = "ignored"\n' >> "$quoted_unsupported_section_case/latticra.seal"

if (cd "$quoted_unsupported_section_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/quoted-unsupported-section.out" 2> "$tmpdir/quoted-unsupported-section.err"); then
  fail "Seal manifest summary must fail closed on quoted unsupported manifest sections"
fi

require_contains "Manifest Sections: malformed or unsupported" "$tmpdir/quoted-unsupported-section.out"
require_contains "manifest summary failed" "$tmpdir/quoted-unsupported-section.err"

malformed_section_case="$tmpdir/malformed-section-case"
mkdir "$malformed_section_case"
cp latticra.seal "$malformed_section_case/latticra.seal"
printf '\n[broken-section\nclaim = "ignored"\n' >> "$malformed_section_case/latticra.seal"

if (cd "$malformed_section_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/malformed-section.out" 2> "$tmpdir/malformed-section.err"); then
  fail "Seal manifest summary must fail closed on malformed manifest section headers"
fi

require_contains "Manifest Sections: malformed or unsupported" "$tmpdir/malformed-section.out"
require_contains "manifest summary failed" "$tmpdir/malformed-section.err"

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

escaped_project_case="$tmpdir/escaped-project-case"
write_manifest "$escaped_project_case" 'schema = "latticra.seal/v0.1"' 'name = "Lat\ticra"' 'status = "unsigned"'

if (cd "$escaped_project_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/escaped-project.out" 2> "$tmpdir/escaped-project.err"); then
  fail "Seal manifest summary must fail closed on escaped summary fields"
fi

require_contains "Project: malformed" "$tmpdir/escaped-project.out"
require_contains "manifest summary failed" "$tmpdir/escaped-project.err"

control_project_case="$tmpdir/control-project-case"
mkdir "$control_project_case"
{
  printf '%s\n' 'schema = "latticra.seal/v0.1"'
  printf '%s\n' 'format = "toml"'
  printf '%s\n' 'kind = "local-integrity-manifest"'
  printf '\n'
  printf '%s\n' '[project]'
  printf 'name = "Lat\001ticra"\n'
  printf '%s\n' 'id = "latticra"'
  printf '%s\n' 'version = "0.1.0"'
  printf '%s\n' 'repository = "https://github.com/Bryforge/Latticra"'
  printf '%s\n' 'license = "SEE LICENSE"'
  printf '\n'
  printf '%s\n' '[seal]'
  printf '%s\n' 'mode = "local-integrity"'
  printf '%s\n' 'status = "unsigned"'
  printf '%s\n' 'algorithm = "sha256"'
  printf '%s\n' 'digest_encoding = "hex"'
  printf '%s\n' 'canonicalization = "relative-path + raw-bytes + unix-lf-preferred"'
  printf '%s\n' 'trust_boundary = "project-root"'
} > "$control_project_case/latticra.seal"

if (cd "$control_project_case" && "$tmpdir/latticra-seal" manifest > "$tmpdir/control-project.out" 2> "$tmpdir/control-project.err"); then
  fail "Seal manifest summary must fail closed on raw-control summary fields"
fi

require_contains "Project: malformed" "$tmpdir/control-project.out"
require_contains "manifest summary failed" "$tmpdir/control-project.err"

printf 'PASS: Latticra Seal manifest command fails closed on invalid summaries\n'

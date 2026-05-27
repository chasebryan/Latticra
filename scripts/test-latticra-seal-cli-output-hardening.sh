#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c11 -Wall -Wextra -Werror}"

ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
cd "$ROOT"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-cli-output-hardening.XXXXXX")"
trap 'chmod -R u+rwx "$tmpdir" 2>/dev/null || true; rm -rf "$tmpdir"' EXIT INT HUP TERM

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

$CC $CFLAGS $OPENSSL_CFLAGS seal/latticra-seal.c $OPENSSL_LIBS -o "$tmpdir/latticra-seal"

make_case="$tmpdir/make-seal-case"
mkdir -p "$make_case/seal"
cp Makefile latticra.seal README.md LICENSE "$make_case/"
cp seal/latticra-seal.c "$make_case/seal/"

if ! (
  cd "$make_case" &&
    make seal \
      CC="$CC" \
      SEAL_CFLAGS="$CFLAGS" \
      SEAL_OPENSSL_CFLAGS="$OPENSSL_CFLAGS" \
      SEAL_OPENSSL_LIBS="$OPENSSL_LIBS" \
      > "$tmpdir/make-seal.out" 2>&1
); then
  cat "$tmpdir/make-seal.out" >&2 || true
  fail "make seal must run the hardened native Seal CLI"
fi

require_contains "Latticra Seal CLI Report" "$tmpdir/make-seal.out"
require_contains "STATUS: PASS" "$tmpdir/make-seal.out"

[ -f "$make_case/reports/latticra-seal-cli-report.txt" ] ||
  fail "make seal must write the native Seal CLI report"

[ ! -e "$make_case/reports/latticra-seal-report.txt" ] ||
  fail "make seal must not route through the legacy shell smoke report"

case_root="$tmpdir/case-root"
mkdir "$case_root"
cp latticra.seal README.md LICENSE "$case_root/"

victim_reports="$tmpdir/victim-reports"
mkdir "$victim_reports"
ln -s "$victim_reports" "$case_root/reports"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-report.out" 2>&1); then
  fail "Seal CLI check must refuse a symlinked reports directory"
fi

require_contains "refusing symlink report directory" "$tmpdir/symlink-report.out"

[ ! -e "$victim_reports/latticra-seal-cli-report.txt" ] ||
  fail "Seal CLI must not write reports through a symlinked reports directory"

rm "$case_root/reports"
mkdir "$case_root/reports"
chmod 0777 "$case_root/reports"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/writable-report-dir.out" 2>&1); then
  fail "Seal CLI check must refuse a group/world-writable reports directory"
fi

require_contains "refusing writable report directory" "$tmpdir/writable-report-dir.out"

[ ! -e "$case_root/reports/latticra-seal-cli-report.txt" ] ||
  fail "Seal CLI must not write reports into a group/world-writable reports directory"

chmod 0700 "$case_root/reports"
rm -rf "$case_root/reports"
mkdir "$case_root/reports"

mkdir -p "$case_root/.venv-piper/bin"
printf 'local tool that must not enter Seal digests\n' > "$case_root/.venv-piper/bin/local-tool"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/local-venv-check.out" 2>&1); then
  fail "Seal CLI check must pass with local virtualenv-style directories present"
fi

require_contains "STATUS: PASS" "$tmpdir/local-venv-check.out"

if grep -Fq ".venv-piper" "$case_root/reports/latticra-seal-cli-hashes.txt"; then
  fail "Seal CLI hash list must exclude local virtualenv-style directories"
fi

printf 'local env marker\n' > "$case_root/.env"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/native-env-denial.out" 2>&1); then
  fail "Seal CLI check must deny .env files in the native policy scan"
fi

require_contains "FAIL: possible secret-bearing filename: .env" "$tmpdir/native-env-denial.out"
require_contains "STATUS: FAIL" "$tmpdir/native-env-denial.out"
rm "$case_root/.env"

printf 'local key marker\n' > "$case_root/id_ed25519"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/native-key-denial.out" 2>&1); then
  fail "Seal CLI check must deny private-key filenames in the native policy scan"
fi

require_contains "FAIL: possible secret-bearing filename: id_ed25519" "$tmpdir/native-key-denial.out"
require_contains "STATUS: FAIL" "$tmpdir/native-key-denial.out"
rm "$case_root/id_ed25519"

printf '%s%s%s\n' 'BEGIN ' 'PRIVATE' ' KEY' > "$case_root/notes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/native-content-denial.out" 2>&1); then
  fail "Seal CLI check must deny obvious secret content markers in the native policy scan"
fi

require_contains "FAIL: possible secret content marker in: notes.txt" "$tmpdir/native-content-denial.out"
require_contains "STATUS: FAIL" "$tmpdir/native-content-denial.out"
rm "$case_root/notes.txt"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/native-policy-recovery.out" 2>&1); then
  fail "Seal CLI check must recover after denied policy fixtures are removed"
fi

require_contains "PASS: no obvious secret-bearing filenames found" "$tmpdir/native-policy-recovery.out"
require_contains "PASS: no obvious secret content markers found" "$tmpdir/native-policy-recovery.out"
require_contains "STATUS: PASS" "$tmpdir/native-policy-recovery.out"

custom_policy_case="$tmpdir/custom-policy-case"
mkdir "$custom_policy_case"
cp README.md LICENSE "$custom_policy_case/"
cat > "$custom_policy_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
mode = "local-integrity"
status = "unsigned"
algorithm = "sha256"
digest_encoding = "hex"
canonicalization = "relative-path + raw-bytes + unix-lf-preferred"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  "*.customsecret",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]

[report]
default_output = "reports/latticra-seal-cli-report.txt"
hash_list_output = "reports/latticra-seal-cli-hashes.txt"
legacy_smoke_output = "reports/latticra-seal-report.txt"
legacy_smoke_hash_list_output = "reports/latticra-seal-file-hashes.txt"
include_file_list = true
include_policy_results = true
include_digest_summary = true
MANIFEST

printf 'not a default deny filename\n' > "$custom_policy_case/example.customsecret"
printf '%s%s\n' 'CUSTOM' '_MARKER=value' > "$custom_policy_case/notes.txt"

if (cd "$custom_policy_case" && "$tmpdir/latticra-seal" check > "$tmpdir/custom-policy.out" 2>&1); then
  fail "Seal CLI check must enforce deny patterns loaded from the manifest"
fi

require_contains "PASS: loaded 1 deny filename pattern(s)" "$tmpdir/custom-policy.out"
require_contains "PASS: loaded 1 deny content marker(s)" "$tmpdir/custom-policy.out"
require_contains "FAIL: possible secret-bearing filename: example.customsecret" "$tmpdir/custom-policy.out"
require_contains "FAIL: possible secret content marker in: notes.txt" "$tmpdir/custom-policy.out"
require_contains "STATUS: FAIL" "$tmpdir/custom-policy.out"

malformed_policy_case="$tmpdir/malformed-policy-case"
mkdir "$malformed_policy_case"
cp README.md LICENSE "$malformed_policy_case/"
cat > "$malformed_policy_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
mode = "local-integrity"
status = "unsigned"
algorithm = "sha256"
digest_encoding = "hex"
canonicalization = "relative-path + raw-bytes + unix-lf-preferred"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  ".env",
]
MANIFEST

if (cd "$malformed_policy_case" && "$tmpdir/latticra-seal" check > "$tmpdir/malformed-policy.out" 2>&1); then
  fail "Seal CLI check must fail closed when manifest deny content policy is missing"
fi

require_contains "FAIL: policy deny content pattern parts are missing, duplicate, or malformed" "$tmpdir/malformed-policy.out"
require_contains "FAIL: policy denial scan skipped because policy configuration was invalid" "$tmpdir/malformed-policy.out"
require_contains "STATUS: FAIL" "$tmpdir/malformed-policy.out"

custom_scope_case="$tmpdir/custom-scope-case"
mkdir -p "$custom_scope_case/excluded"
cp README.md LICENSE "$custom_scope_case/"
cat > "$custom_scope_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
mode = "local-integrity"
status = "unsigned"
algorithm = "sha256"
digest_encoding = "hex"
canonicalization = "relative-path + raw-bytes + unix-lf-preferred"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "excluded/",
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]

[report]
default_output = "reports/latticra-seal-cli-report.txt"
hash_list_output = "reports/latticra-seal-cli-hashes.txt"
legacy_smoke_output = "reports/latticra-seal-report.txt"
legacy_smoke_hash_list_output = "reports/latticra-seal-file-hashes.txt"
include_file_list = true
include_policy_results = true
include_digest_summary = true
MANIFEST

printf 'excluded secret filename must stay out of scope\n' > "$custom_scope_case/excluded/.env"
printf '%s%s\n' 'CUSTOM' '_MARKER=value' > "$custom_scope_case/excluded/notes.txt"

if ! (cd "$custom_scope_case" && "$tmpdir/latticra-seal" check > "$tmpdir/custom-scope.out" 2>&1); then
  cat "$tmpdir/custom-scope.out" >&2 || true
  fail "Seal CLI check must honor manifest path exclusions during policy and digest scans"
fi

require_contains "PASS: loaded 5 path exclude pattern(s)" "$tmpdir/custom-scope.out"
require_contains "PASS: no obvious secret-bearing filenames found" "$tmpdir/custom-scope.out"
require_contains "PASS: no obvious secret content markers found" "$tmpdir/custom-scope.out"
require_contains "STATUS: PASS" "$tmpdir/custom-scope.out"

if grep -Fq "excluded/" "$custom_scope_case/reports/latticra-seal-cli-hashes.txt"; then
  fail "Seal CLI hash list must honor manifest path exclusions"
fi

malformed_scope_case="$tmpdir/malformed-scope-case"
mkdir "$malformed_scope_case"
cp README.md LICENSE "$malformed_scope_case/"
cat > "$malformed_scope_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
mode = "local-integrity"
status = "unsigned"
algorithm = "sha256"
digest_encoding = "hex"
canonicalization = "relative-path + raw-bytes + unix-lf-preferred"
trust_boundary = "project-root"

[paths]
include = [
  "src",
]
exclude = [
  "reports/*.txt",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]

[report]
default_output = "reports/latticra-seal-cli-report.txt"
hash_list_output = "reports/latticra-seal-cli-hashes.txt"
legacy_smoke_output = "reports/latticra-seal-report.txt"
legacy_smoke_hash_list_output = "reports/latticra-seal-file-hashes.txt"
include_file_list = true
include_policy_results = true
include_digest_summary = true
MANIFEST

if (cd "$malformed_scope_case" && "$tmpdir/latticra-seal" check > "$tmpdir/malformed-scope.out" 2>&1); then
  fail "Seal CLI check must fail closed on unsupported path include scope"
fi

require_contains "FAIL: path include scope must be project root" "$tmpdir/malformed-scope.out"
require_contains "FAIL: policy denial scan skipped because path scope was invalid" "$tmpdir/malformed-scope.out"
require_contains "FAIL: hash list not written because path scope was invalid" "$tmpdir/malformed-scope.out"
require_contains "STATUS: FAIL" "$tmpdir/malformed-scope.out"

custom_required_case="$tmpdir/custom-required-case"
mkdir "$custom_required_case"
cp README.md LICENSE "$custom_required_case/"
printf 'custom required evidence\n' > "$custom_required_case/CUSTOM_REQUIRED.md"
cat > "$custom_required_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
mode = "local-integrity"
status = "unsigned"
algorithm = "sha256"
digest_encoding = "hex"
canonicalization = "relative-path + raw-bytes + unix-lf-preferred"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "CUSTOM_REQUIRED.md",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]

[report]
default_output = "reports/latticra-seal-cli-report.txt"
hash_list_output = "reports/latticra-seal-cli-hashes.txt"
legacy_smoke_output = "reports/latticra-seal-report.txt"
legacy_smoke_hash_list_output = "reports/latticra-seal-file-hashes.txt"
include_file_list = true
include_policy_results = true
include_digest_summary = true
MANIFEST

if ! (cd "$custom_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/custom-required.out" 2>&1); then
  cat "$tmpdir/custom-required.out" >&2 || true
  fail "Seal CLI check must honor manifest-declared required files"
fi

require_contains "PASS: loaded 1 required file path(s)" "$tmpdir/custom-required.out"
require_contains "PASS: required file exists: CUSTOM_REQUIRED.md" "$tmpdir/custom-required.out"
require_contains "STATUS: PASS" "$tmpdir/custom-required.out"

rm "$custom_required_case/CUSTOM_REQUIRED.md"

if (cd "$custom_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/custom-required-missing.out" 2>&1); then
  fail "Seal CLI check must fail when a manifest-declared required file is missing"
fi

require_contains "FAIL: required file missing: CUSTOM_REQUIRED.md" "$tmpdir/custom-required-missing.out"
require_contains "STATUS: FAIL" "$tmpdir/custom-required-missing.out"

malformed_required_case="$tmpdir/malformed-required-case"
mkdir "$malformed_required_case"
cp README.md LICENSE "$malformed_required_case/"
cat > "$malformed_required_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "README.md",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]
MANIFEST

if (cd "$malformed_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/malformed-required.out" 2>&1); then
  fail "Seal CLI check must fail closed on duplicate manifest required files"
fi

require_contains "FAIL: policy required files are missing, duplicate, or malformed" "$tmpdir/malformed-required.out"
require_contains "STATUS: FAIL" "$tmpdir/malformed-required.out"

missing_comma_required_case="$tmpdir/missing-comma-required-case"
mkdir "$missing_comma_required_case"
cp README.md LICENSE "$missing_comma_required_case/"
cat > "$missing_comma_required_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md"
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]
MANIFEST

if (cd "$missing_comma_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/missing-comma-required.out" 2>&1); then
  fail "Seal CLI check must fail closed on required-file arrays with missing commas"
fi

require_contains "FAIL: policy required files are missing, duplicate, or malformed" "$tmpdir/missing-comma-required.out"
require_contains "STATUS: FAIL" "$tmpdir/missing-comma-required.out"

double_comma_policy_case="$tmpdir/double-comma-policy-case"
mkdir "$double_comma_policy_case"
cp README.md LICENSE "$double_comma_policy_case/"
cat > "$double_comma_policy_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM",, "_MARKER="],
]
MANIFEST

if (cd "$double_comma_policy_case" && "$tmpdir/latticra-seal" check > "$tmpdir/double-comma-policy.out" 2>&1); then
  fail "Seal CLI check must fail closed on deny-content arrays with doubled commas"
fi

require_contains "FAIL: policy deny content pattern parts are missing, duplicate, or malformed" "$tmpdir/double-comma-policy.out"
require_contains "STATUS: FAIL" "$tmpdir/double-comma-policy.out"

duplicate_exclude_case="$tmpdir/duplicate-exclude-case"
mkdir "$duplicate_exclude_case"
cp README.md LICENSE "$duplicate_exclude_case/"
cat > "$duplicate_exclude_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]
MANIFEST

if (cd "$duplicate_exclude_case" && "$tmpdir/latticra-seal" check > "$tmpdir/duplicate-exclude.out" 2>&1); then
  fail "Seal CLI check must fail closed on duplicate manifest path exclusions"
fi

require_contains "FAIL: path exclude scope is missing, duplicate, or malformed" "$tmpdir/duplicate-exclude.out"
require_contains "FAIL: policy denial scan skipped because path scope was invalid" "$tmpdir/duplicate-exclude.out"
require_contains "FAIL: hash list not written because path scope was invalid" "$tmpdir/duplicate-exclude.out"
require_contains "STATUS: FAIL" "$tmpdir/duplicate-exclude.out"

unsafe_required_case="$tmpdir/unsafe-required-case"
mkdir "$unsafe_required_case"
cp README.md LICENSE "$unsafe_required_case/"
cat > "$unsafe_required_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "../README.md",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]
MANIFEST

if (cd "$unsafe_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/unsafe-required.out" 2>&1); then
  fail "Seal CLI check must fail closed on required files outside the project root"
fi

require_contains "FAIL: policy required files are missing, duplicate, or malformed" "$tmpdir/unsafe-required.out"
require_contains "STATUS: FAIL" "$tmpdir/unsafe-required.out"

unsafe_filename_policy_case="$tmpdir/unsafe-filename-policy-case"
mkdir "$unsafe_filename_policy_case"
cp README.md LICENSE "$unsafe_filename_policy_case/"
cat > "$unsafe_filename_policy_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  "secrets/.env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
]
MANIFEST

if (cd "$unsafe_filename_policy_case" && "$tmpdir/latticra-seal" check > "$tmpdir/unsafe-filename-policy.out" 2>&1); then
  fail "Seal CLI check must fail closed on path-shaped deny filename patterns"
fi

require_contains "FAIL: policy deny filename patterns are missing, duplicate, or malformed" "$tmpdir/unsafe-filename-policy.out"
require_contains "FAIL: policy denial scan skipped because policy configuration was invalid" "$tmpdir/unsafe-filename-policy.out"
require_contains "STATUS: FAIL" "$tmpdir/unsafe-filename-policy.out"

duplicate_marker_policy_case="$tmpdir/duplicate-marker-policy-case"
mkdir "$duplicate_marker_policy_case"
cp README.md LICENSE "$duplicate_marker_policy_case/"
cat > "$duplicate_marker_policy_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[paths]
include = [
  ".",
]
exclude = [
  "reports/*.txt",
  "reports/*.json",
  "latticra.seal.lock",
  "*.tmp",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  ".env",
]

[policy.deny_contents]
pattern_parts = [
  ["CUSTOM", "_MARKER="],
  ["CUSTOM", "_MARKER="],
]
MANIFEST

if (cd "$duplicate_marker_policy_case" && "$tmpdir/latticra-seal" check > "$tmpdir/duplicate-marker-policy.out" 2>&1); then
  fail "Seal CLI check must fail closed on duplicate deny content markers"
fi

require_contains "FAIL: policy deny content pattern parts are missing, duplicate, or malformed" "$tmpdir/duplicate-marker-policy.out"
require_contains "FAIL: policy denial scan skipped because policy configuration was invalid" "$tmpdir/duplicate-marker-policy.out"
require_contains "STATUS: FAIL" "$tmpdir/duplicate-marker-policy.out"

seal_shape_drift_case="$tmpdir/seal-shape-drift-case"
mkdir "$seal_shape_drift_case"
cp README.md LICENSE "$seal_shape_drift_case/"
sed 's/mode = "local-integrity"/mode = "runtime-enforcement"/' latticra.seal > "$seal_shape_drift_case/latticra.seal"

if (cd "$seal_shape_drift_case" && "$tmpdir/latticra-seal" check > "$tmpdir/seal-shape-drift.out" 2>&1); then
  fail "Seal CLI check must fail closed when declared seal mode drifts from CLI authority"
fi

require_contains "FAIL: seal mode is local-integrity" "$tmpdir/seal-shape-drift.out"
require_contains "STATUS: FAIL" "$tmpdir/seal-shape-drift.out"

report_shape_drift_case="$tmpdir/report-shape-drift-case"
mkdir "$report_shape_drift_case"
cp README.md LICENSE "$report_shape_drift_case/"
sed 's#default_output = "reports/latticra-seal-cli-report.txt"#default_output = "reports/drifted-report.txt"#' latticra.seal > "$report_shape_drift_case/latticra.seal"

if (cd "$report_shape_drift_case" && "$tmpdir/latticra-seal" check > "$tmpdir/report-shape-drift.out" 2>&1); then
  fail "Seal CLI check must fail closed when declared report output drifts from CLI output"
fi

require_contains "FAIL: report default output is reports/latticra-seal-cli-report.txt" "$tmpdir/report-shape-drift.out"
require_contains "STATUS: FAIL" "$tmpdir/report-shape-drift.out"

ln -s README.md "$case_root/readme-link"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-scope.out" 2>&1); then
  fail "Seal CLI check must fail closed on in-scope symlinks"
fi

require_contains "FAIL: refusing symlink in digest scope: readme-link" "$tmpdir/symlink-scope.out"
require_contains "hash list not written because digest traversal failed" "$tmpdir/symlink-scope.out"
require_contains "STATUS: FAIL" "$tmpdir/symlink-scope.out"

[ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must remove stale hash lists when an in-scope symlink is refused"

rm "$case_root/readme-link"

manifest_case="$tmpdir/manifest-case"
mkdir "$manifest_case"
cp README.md LICENSE "$manifest_case/"
cat > "$manifest_case/latticra.seal" <<'MANIFEST'
# schema = "latticra.seal/v0.1"
schema_hint = "latticra.seal/v0.1"
format_hint = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true
MANIFEST

if (cd "$manifest_case" && "$tmpdir/latticra-seal" check > "$tmpdir/misleading-manifest.out" 2>&1); then
  fail "Seal CLI check must reject manifest fields that only appear in comments or prefixed keys"
fi

require_contains "FAIL: schema is latticra.seal/v0.1" "$tmpdir/misleading-manifest.out"
require_contains "FAIL: format is TOML-compatible" "$tmpdir/misleading-manifest.out"
require_contains "STATUS: FAIL" "$tmpdir/misleading-manifest.out"

duplicate_manifest_case="$tmpdir/duplicate-manifest-case"
mkdir "$duplicate_manifest_case"
cp README.md LICENSE "$duplicate_manifest_case/"
cat > "$duplicate_manifest_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[seal]
algorithm = "sha256"
trust_boundary = "project-root"

[policy]
require_readme = true
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true
MANIFEST

if (cd "$duplicate_manifest_case" && "$tmpdir/latticra-seal" check > "$tmpdir/duplicate-manifest.out" 2>&1); then
  fail "Seal CLI check must reject duplicate required manifest keys"
fi

require_contains "FAIL: schema is latticra.seal/v0.1" "$tmpdir/duplicate-manifest.out"
require_contains "FAIL: policy requires README" "$tmpdir/duplicate-manifest.out"
require_contains "STATUS: FAIL" "$tmpdir/duplicate-manifest.out"

wrong_section_manifest_case="$tmpdir/wrong-section-manifest-case"
mkdir "$wrong_section_manifest_case"
cp README.md LICENSE "$wrong_section_manifest_case/"
cat > "$wrong_section_manifest_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[project]
algorithm = "sha256"
trust_boundary = "project-root"

[seal]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true
MANIFEST

if (cd "$wrong_section_manifest_case" && "$tmpdir/latticra-seal" check > "$tmpdir/wrong-section-manifest.out" 2>&1); then
  fail "Seal CLI check must reject required manifest keys in the wrong section"
fi

require_contains "FAIL: hash algorithm is sha256" "$tmpdir/wrong-section-manifest.out"
require_contains "FAIL: trust boundary is project-root" "$tmpdir/wrong-section-manifest.out"
require_contains "FAIL: policy requires README" "$tmpdir/wrong-section-manifest.out"
require_contains "STATUS: FAIL" "$tmpdir/wrong-section-manifest.out"

mkdir -p "$case_root/unreadable-dir"
printf 'hidden material must not be missed silently\n' > "$case_root/unreadable-dir/hidden.txt"
chmod 000 "$case_root/unreadable-dir"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/unreadable-dir.out" 2>&1); then
  chmod 700 "$case_root/unreadable-dir"
  fail "Seal CLI check must fail when the digest walk cannot inspect a directory"
fi

chmod 700 "$case_root/unreadable-dir"
rm -rf "$case_root/unreadable-dir"

require_contains "FAIL: could not open directory" "$tmpdir/unreadable-dir.out"
require_contains "hash list not written because digest traversal failed" "$tmpdir/unreadable-dir.out"
require_contains "STATUS: FAIL" "$tmpdir/unreadable-dir.out"

[ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must remove stale hash lists when digest traversal fails"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/post-traversal-check.out" 2>&1); then
  fail "Seal CLI check must recover after an unreadable directory is removed"
fi

require_contains "STATUS: PASS" "$tmpdir/post-traversal-check.out"

printf 'hidden material must not be partially hashed\n' > "$case_root/unreadable-file.txt"
chmod 000 "$case_root/unreadable-file.txt"

if cat "$case_root/unreadable-file.txt" >/dev/null 2>&1; then
  chmod 600 "$case_root/unreadable-file.txt"
  rm "$case_root/unreadable-file.txt"
else
  if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/unreadable-file.out" 2>&1); then
    chmod 600 "$case_root/unreadable-file.txt"
    fail "Seal CLI check must fail when a discovered file cannot be hashed"
  fi

  chmod 600 "$case_root/unreadable-file.txt"
  rm "$case_root/unreadable-file.txt"

  require_contains "FAIL: could not hash file: unreadable-file.txt" "$tmpdir/unreadable-file.out"
  require_contains "hash list not written because file hashing failed" "$tmpdir/unreadable-file.out"
  require_contains "STATUS: FAIL" "$tmpdir/unreadable-file.out"

  [ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
    fail "Seal CLI must remove stale hash lists when file hashing fails"
fi

if ! (cd "$case_root" && "$tmpdir/latticra-seal" baseline > "$tmpdir/baseline-success.out" 2>&1); then
  cat "$tmpdir/baseline-success.out" >&2 || true
  fail "Seal CLI baseline must write a valid baseline after check passes"
fi

require_contains "Baseline written to: latticra.seal.lock" "$tmpdir/baseline-success.out"

[ -s "$case_root/latticra.seal.lock" ] ||
  fail "Seal CLI baseline must leave a non-empty lockfile"

printf 'not-a-valid-baseline\n' > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/malformed-baseline.out" 2>&1); then
  fail "Seal CLI verify must refuse a malformed baseline"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/malformed-baseline.out"

{
  printf '0000000000000000000000000000000000000000000000000000000000000000  README.md\n'
  printf '1111111111111111111111111111111111111111111111111111111111111111  README.md\n'
} > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/duplicate-baseline.out" 2>&1); then
  fail "Seal CLI verify must refuse duplicate baseline paths"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/duplicate-baseline.out"

printf '0000000000000000000000000000000000000000000000000000000000000000  ../README.md\n' > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/unsafe-baseline-path.out" 2>&1); then
  fail "Seal CLI verify must refuse baseline paths outside the project root"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/unsafe-baseline-path.out"

{
  printf '0000000000000000000000000000000000000000000000000000000000000000  notes.txt\n'
  printf '1111111111111111111111111111111111111111111111111111111111111111  README.md\n'
} > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/unsorted-baseline.out" 2>&1); then
  fail "Seal CLI verify must refuse non-canonical unsorted baselines"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/unsorted-baseline.out"

rm "$case_root/latticra.seal.lock"

victim_lock="$tmpdir/victim-lock"
printf 'do-not-overwrite\n' > "$victim_lock"
ln -s "$victim_lock" "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" baseline > "$tmpdir/symlink-baseline.out" 2>&1); then
  fail "Seal CLI baseline must refuse a symlinked baseline path"
fi

require_contains "could not write baseline: latticra.seal.lock" "$tmpdir/symlink-baseline.out"

if [ "$(cat "$victim_lock")" != "do-not-overwrite" ]; then
  fail "Seal CLI must not overwrite a symlink target while writing the baseline"
fi

rm "$case_root/latticra.seal.lock"

victim_tmp_lock="$tmpdir/victim-tmp-lock"
printf 'do-not-overwrite-tmp\n' > "$victim_tmp_lock"
ln -s "$victim_tmp_lock" "$case_root/latticra.seal.lock.tmp"

if (cd "$case_root" && "$tmpdir/latticra-seal" baseline > "$tmpdir/symlink-baseline-tmp.out" 2>&1); then
  fail "Seal CLI baseline must refuse a symlinked temporary baseline path"
fi

require_contains "could not write baseline: latticra.seal.lock" "$tmpdir/symlink-baseline-tmp.out"

if [ "$(cat "$victim_tmp_lock")" != "do-not-overwrite-tmp" ]; then
  fail "Seal CLI must not overwrite a symlink target while writing the temporary baseline"
fi

[ ! -e "$case_root/latticra.seal.lock" ] ||
  fail "Seal CLI must not promote a baseline when the temporary baseline path is refused"

printf 'PASS: Latticra Seal CLI output hardening rejects symlink writes\n'

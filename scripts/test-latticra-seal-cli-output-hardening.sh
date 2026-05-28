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

$CC $CFLAGS $OPENSSL_CFLAGS -Iinclude \
  seal/latticra-seal.c \
  src/seal_hybrid_envelope.c \
  src/seal_hybrid_provider_self_test.c \
  $OPENSSL_LIBS \
  -o "$tmpdir/latticra-seal"

require_contains "open_new_regular_file_for_write" seal/latticra-seal.c
require_contains "open_report_dir_for_artifacts" seal/latticra-seal.c
require_contains "open_new_regular_file_at_for_write" seal/latticra-seal.c
require_contains "open_single_link_regular_file_at_for_read" seal/latticra-seal.c
require_contains "fstatat(dirfd" seal/latticra-seal.c
require_contains "unlinkat(dirfd" seal/latticra-seal.c
require_contains "renameat(" seal/latticra-seal.c
require_contains "flush_and_sync_file" seal/latticra-seal.c
require_contains "fsync(fd)" seal/latticra-seal.c
require_contains "sync_directory_fd" seal/latticra-seal.c
require_contains "sync_cwd_directory" seal/latticra-seal.c
require_contains "clear_stale_hash_artifacts" seal/latticra-seal.c
require_contains "open_single_link_regular_file_for_read(path)" seal/latticra-seal.c
require_contains "struct stat before_read_st" seal/latticra-seal.c
require_contains "struct stat after_read_st" seal/latticra-seal.c
require_contains "fstat(fileno(f), &before_read_st)" seal/latticra-seal.c
require_contains "fstat(fileno(f), &after_read_st)" seal/latticra-seal.c
require_contains "after_read_st.st_size == before_read_st.st_size" seal/latticra-seal.c
require_contains "fd_single_link_regular_size" seal/latticra-seal.c
require_contains "fd_size_matches" seal/latticra-seal.c
require_contains "memchr(buf" seal/latticra-seal.c
require_contains "sha256_bytes((const unsigned char *)manifest" seal/latticra-seal.c
require_contains "uc < 32" seal/latticra-seal.c
require_contains "uc == 127" seal/latticra-seal.c
require_contains "if (token[0] == '\\0')" seal/latticra-seal.c
require_contains "refusing unsafe path in digest scope" seal/latticra-seal.c
require_contains "refusing hard-linked file in digest scope" seal/latticra-seal.c
require_contains "CollectedFileList" seal/latticra-seal.c
require_contains "collected_file_stat_matches" seal/latticra-seal.c
require_contains "collected_file_stream_observed_size" seal/latticra-seal.c
require_contains "collected_file_stream_size_matches" seal/latticra-seal.c
require_contains "current_size == expected_size" seal/latticra-seal.c
require_contains "refusing invalid-size file in digest scope" seal/latticra-seal.c
require_contains "open_collected_file_for_read" seal/latticra-seal.c
require_contains "open_directory_for_traversal" seal/latticra-seal.c
require_contains "fdopendir" seal/latticra-seal.c
require_contains "same_file_identity(&st, expected_dir)" seal/latticra-seal.c
require_contains "errno = 0" seal/latticra-seal.c
require_contains "could not read directory" seal/latticra-seal.c
require_contains "closedir(dir) != 0" seal/latticra-seal.c
require_contains "could not close directory" seal/latticra-seal.c
require_contains "sha256_collected_file" seal/latticra-seal.c
require_contains "cmp_collected_file_path" seal/latticra-seal.c
require_contains "required_file_is_single_link_regular" seal/latticra-seal.c
require_contains "required_path_excluded_by_scope" seal/latticra-seal.c
require_contains "first_required_file_excluded_from_scope" seal/latticra-seal.c
require_contains "first_unusable_required_file" seal/latticra-seal.c
require_contains "required file excluded from digest scope" seal/latticra-seal.c
require_contains "hash list not written because required file is missing or unsafe" seal/latticra-seal.c
require_contains "hash list not written because manifest, policy, or report shape was invalid" seal/latticra-seal.c
require_contains "hash list not written because earlier checks failed" seal/latticra-seal.c
require_contains "policy large binary denial is disabled" seal/latticra-seal.c
require_contains "policy max file size is 25 MB" seal/latticra-seal.c
require_contains "manifest_section_headers_supported" seal/latticra-seal.c
require_contains "update_manifest_array_depth" seal/latticra-seal.c
require_contains "manifest section headers are supported" seal/latticra-seal.c
require_contains "check_proof_shape" seal/latticra-seal.c
require_contains "check_empty_proof_field" seal/latticra-seal.c
require_contains "proof %s is empty" seal/latticra-seal.c
require_contains "\"manifest_hash\", \"manifest hash\"" seal/latticra-seal.c
require_contains "\"root_hash\", \"root hash\"" seal/latticra-seal.c
require_contains "check_project_identity_shape" seal/latticra-seal.c
require_contains "check_optional_manifest_text_assignment" seal/latticra-seal.c
require_contains "project name is Latticra" seal/latticra-seal.c
require_contains "project id is latticra" seal/latticra-seal.c
require_contains "native_generated_artifact_path_is" seal/latticra-seal.c
require_contains "preserve_hash_list_fd" seal/latticra-seal.c
require_contains "run_check(true, &hash_list_fd)" seal/latticra-seal.c
require_contains "write_baseline_atomic(hash_list_fd)" seal/latticra-seal.c
require_contains "copy_file_fd_to_path" seal/latticra-seal.c
require_contains "open_single_link_regular_file_for_read_fd(BASELINE_PATH)" seal/latticra-seal.c
require_contains "compare_hash_lists_report(&run, baseline_fd, run.hash_list_fd)" seal/latticra-seal.c
require_contains "read_hash_list_fd(baseline_fd" seal/latticra-seal.c
require_contains "read_hash_list_fd(hash_list_fd" seal/latticra-seal.c
require_contains "getline(&line" seal/latticra-seal.c
require_contains "memchr(line, '\\0', line_len)" seal/latticra-seal.c
require_contains "memchr(line, '\\r', line_len)" seal/latticra-seal.c
require_contains "line[line_len - 1] != '\\n'" seal/latticra-seal.c
require_contains "return ok && list->len > 0" seal/latticra-seal.c
require_contains "hash list artifact is malformed" seal/latticra-seal.c
require_contains "report artifact is empty" seal/latticra-seal.c
require_contains "OPENSSL_cleanse(record, sizeof(record))" seal/latticra-seal.c
require_contains "OPENSSL_cleanse(recovered, sizeof(recovered))" seal/latticra-seal.c
require_contains "cli_record_buffer_zeroized=1" seal/latticra-seal.c
require_contains "cli_recovered_plaintext_buffer_zeroized=1" seal/latticra-seal.c
require_contains "O_EXCL" seal/latticra-seal.c
require_contains "fchmod(fd, 0600) != 0" seal/latticra-seal.c
if grep -Fq "O_TRUNC" seal/latticra-seal.c; then
  fail "Seal CLI artifact writers must not use truncate-before-check semantics"
fi
if ! sed -n '/static FILE \*open_new_regular_file_at_for_write/,/^}/p' seal/latticra-seal.c |
  grep -Fq "unlink_regular_at_if_present(dirfd, path)"; then
  fail "Seal CLI temp artifact writer must remove created temp paths after setup failures"
fi
if ! sed -n '/collect_files(run, &list, ".", &excludes, NULL);/,/FILE \\*hashes =/p' seal/latticra-seal.c |
  grep -Fq "if (pre_digest_failures != 0)"; then
  fail "Seal CLI must stop before temporary hash-list creation when earlier checks failed"
fi
if sed -n '/static int command_baseline(void)/,/^}/p' seal/latticra-seal.c |
  grep -Fq "open_report_dir_for_artifacts"; then
  fail "Seal CLI baseline must promote from the retained check hash-list descriptor"
fi

make_case="$tmpdir/make-seal-case"
mkdir -p "$make_case/include/latticra" "$make_case/seal" "$make_case/src"
cp Makefile latticra.seal README.md LICENSE "$make_case/"
cp include/latticra/state_lattice.h "$make_case/include/latticra/"
cp include/latticra/seal_hybrid_envelope.h "$make_case/include/latticra/"
cp include/latticra/seal_hybrid_provider_self_test.h "$make_case/include/latticra/"
cp seal/latticra-seal.c "$make_case/seal/"
cp src/seal_hybrid_envelope.c "$make_case/src/"
cp src/seal_hybrid_provider_self_test.c "$make_case/src/"

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

if (cd "$case_root" && "$tmpdir/latticra-seal" report > "$tmpdir/missing-report-read.out" 2>&1); then
  fail "Seal CLI report command must exit nonzero when the reports directory is absent"
fi

require_contains "no file found at reports/latticra-seal-cli-report.txt" "$tmpdir/missing-report-read.out"

if [ -e "$case_root/reports" ]; then
  fail "Seal CLI report command must not create a reports directory while reading"
fi

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/missing-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must exit nonzero when the reports directory is absent"
fi

require_contains "no file found at reports/latticra-seal-cli-hashes.txt" "$tmpdir/missing-hashes-read.out"

if [ -e "$case_root/reports" ]; then
  fail "Seal CLI hashes command must not create a reports directory while reading"
fi

mkdir "$case_root/reports"
: > "$case_root/reports/latticra-seal-cli-report.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" report > "$tmpdir/empty-report-read.out" 2>&1); then
  fail "Seal CLI report command must fail closed on empty report artifacts"
fi

require_contains "report artifact is empty: reports/latticra-seal-cli-report.txt" "$tmpdir/empty-report-read.out"
rm -rf "$case_root/reports"

victim_reports="$tmpdir/victim-reports"
mkdir "$victim_reports"
ln -s "$victim_reports" "$case_root/reports"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-report.out" 2>&1); then
  fail "Seal CLI check must refuse a symlinked reports directory"
fi

require_contains "refusing symlink report directory" "$tmpdir/symlink-report.out"

[ ! -e "$victim_reports/latticra-seal-cli-report.txt" ] ||
  fail "Seal CLI must not write reports through a symlinked reports directory"

printf 'do-not-stream-report\n' > "$victim_reports/latticra-seal-cli-report.txt"
printf 'do-not-stream-hashes\n' > "$victim_reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" report > "$tmpdir/symlink-report-read.out" 2>&1); then
  fail "Seal CLI report command must refuse a symlinked reports directory"
fi

require_contains "refusing symlink report directory" "$tmpdir/symlink-report-read.out"

if grep -Fq "do-not-stream-report" "$tmpdir/symlink-report-read.out"; then
  fail "Seal CLI report command must not read through a symlinked reports directory"
fi

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/symlink-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must refuse a symlinked reports directory"
fi

require_contains "refusing symlink report directory" "$tmpdir/symlink-hashes-read.out"

if grep -Fq "do-not-stream-hashes" "$tmpdir/symlink-hashes-read.out"; then
  fail "Seal CLI hashes command must not read through a symlinked reports directory"
fi

rm "$case_root/reports"
mkdir "$case_root/reports"
chmod 0777 "$case_root/reports"
printf 'do-not-stream-writable-report\n' > "$case_root/reports/latticra-seal-cli-report.txt"
printf 'do-not-stream-writable-hashes\n' > "$case_root/reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/writable-report-dir.out" 2>&1); then
  fail "Seal CLI check must refuse a group/world-writable reports directory"
fi

require_contains "refusing writable report directory" "$tmpdir/writable-report-dir.out"

if (cd "$case_root" && "$tmpdir/latticra-seal" report > "$tmpdir/writable-report-read.out" 2>&1); then
  fail "Seal CLI report command must refuse a group/world-writable reports directory"
fi

require_contains "refusing writable report directory" "$tmpdir/writable-report-read.out"

if grep -Fq "do-not-stream-writable-report" "$tmpdir/writable-report-read.out"; then
  fail "Seal CLI report command must not read from a group/world-writable reports directory"
fi

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/writable-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must refuse a group/world-writable reports directory"
fi

require_contains "refusing writable report directory" "$tmpdir/writable-hashes-read.out"

if grep -Fq "do-not-stream-writable-hashes" "$tmpdir/writable-hashes-read.out"; then
  fail "Seal CLI hashes command must not read from a group/world-writable reports directory"
fi

if [ "$(cat "$case_root/reports/latticra-seal-cli-report.txt")" != "do-not-stream-writable-report" ]; then
  fail "Seal CLI must not overwrite reports inside a group/world-writable reports directory"
fi

chmod 0700 "$case_root/reports"
rm -rf "$case_root/reports"
mkdir "$case_root/reports"

victim_report_file="$tmpdir/victim-report-file"
printf 'do-not-overwrite-report\n' > "$victim_report_file"
ln -s "$victim_report_file" "$case_root/reports/latticra-seal-cli-report.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-report-file.out" 2>&1); then
  fail "Seal CLI check must refuse a symlinked report file path"
fi

require_contains "could not open report: reports/latticra-seal-cli-report.txt" "$tmpdir/symlink-report-file.out"

if [ "$(cat "$victim_report_file")" != "do-not-overwrite-report" ]; then
  fail "Seal CLI must not overwrite a symlink target while writing the report"
fi

rm "$case_root/reports/latticra-seal-cli-report.txt"

victim_report_hardlink="$tmpdir/victim-report-hardlink"
printf 'do-not-overwrite-report-hardlink\n' > "$victim_report_hardlink"
ln "$victim_report_hardlink" "$case_root/reports/latticra-seal-cli-report.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" report > "$tmpdir/hardlink-report-read.out" 2>&1); then
  fail "Seal CLI report command must refuse a hard-linked report artifact"
fi

require_contains "no file found at reports/latticra-seal-cli-report.txt" "$tmpdir/hardlink-report-read.out"

if grep -Fq "do-not-overwrite-report-hardlink" "$tmpdir/hardlink-report-read.out"; then
  fail "Seal CLI report command must not read from a hard-linked report artifact"
fi

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/hardlink-report-file.out" 2>&1); then
  fail "Seal CLI check must refuse a hard-linked report file path"
fi

require_contains "could not open report: reports/latticra-seal-cli-report.txt" "$tmpdir/hardlink-report-file.out"

if [ "$(cat "$victim_report_hardlink")" != "do-not-overwrite-report-hardlink" ]; then
  fail "Seal CLI must not overwrite a hard-linked target while writing the report"
fi

rm "$case_root/reports/latticra-seal-cli-report.txt"

printf 'stale-report-temp\n' > "$case_root/reports/latticra-seal-cli-report.tmp"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/stale-report-tmp.out" 2>&1); then
  cat "$tmpdir/stale-report-tmp.out" >&2 || true
  fail "Seal CLI check must clear a stale single-link temporary report before writing"
fi

require_contains "STATUS: PASS" "$tmpdir/stale-report-tmp.out"

[ ! -e "$case_root/reports/latticra-seal-cli-report.tmp" ] ||
  fail "Seal CLI must not leave a stale temporary report after successful promotion"

rm "$case_root/reports/latticra-seal-cli-report.txt"
rm "$case_root/reports/latticra-seal-cli-hashes.txt"

victim_report_tmp="$tmpdir/victim-report-tmp"
printf 'do-not-overwrite-report-tmp\n' > "$victim_report_tmp"
ln -s "$victim_report_tmp" "$case_root/reports/latticra-seal-cli-report.tmp"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-report-tmp.out" 2>&1); then
  fail "Seal CLI check must refuse a symlinked temporary report file path"
fi

require_contains "could not open report: reports/latticra-seal-cli-report.txt" "$tmpdir/symlink-report-tmp.out"

if [ "$(cat "$victim_report_tmp")" != "do-not-overwrite-report-tmp" ]; then
  fail "Seal CLI must not overwrite a symlink target while writing the temporary report"
fi

[ ! -e "$case_root/reports/latticra-seal-cli-report.txt" ] ||
  fail "Seal CLI must not promote a report when the temporary report path is refused"

rm "$case_root/reports/latticra-seal-cli-report.tmp"

victim_report_tmp_hardlink="$tmpdir/victim-report-tmp-hardlink"
printf 'do-not-overwrite-report-tmp-hardlink\n' > "$victim_report_tmp_hardlink"
ln "$victim_report_tmp_hardlink" "$case_root/reports/latticra-seal-cli-report.tmp"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/hardlink-report-tmp.out" 2>&1); then
  fail "Seal CLI check must refuse a hard-linked temporary report file path"
fi

require_contains "could not open report: reports/latticra-seal-cli-report.txt" "$tmpdir/hardlink-report-tmp.out"

if [ "$(cat "$victim_report_tmp_hardlink")" != "do-not-overwrite-report-tmp-hardlink" ]; then
  fail "Seal CLI must not overwrite a hard-linked target while writing the temporary report"
fi

[ ! -e "$case_root/reports/latticra-seal-cli-report.txt" ] ||
  fail "Seal CLI must not promote a report when the temporary report hardlink is refused"

rm "$case_root/reports/latticra-seal-cli-report.tmp"

victim_hash_file="$tmpdir/victim-hash-file"
printf 'do-not-overwrite-hash\n' > "$victim_hash_file"
ln -s "$victim_hash_file" "$case_root/reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-hash-file.out" 2>&1); then
  fail "Seal CLI check must refuse a symlinked hash-list file path"
fi

require_contains "FAIL: could not clear previous hash list" "$tmpdir/symlink-hash-file.out"
require_contains "STATUS: FAIL" "$tmpdir/symlink-hash-file.out"

if [ "$(cat "$victim_hash_file")" != "do-not-overwrite-hash" ]; then
  fail "Seal CLI must not overwrite a symlink target while writing the hash list"
fi

rm "$case_root/reports/latticra-seal-cli-hashes.txt"

victim_hash_hardlink="$tmpdir/victim-hash-hardlink"
printf 'do-not-overwrite-hash-hardlink\n' > "$victim_hash_hardlink"
ln "$victim_hash_hardlink" "$case_root/reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/hardlink-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must refuse a hard-linked hash-list artifact"
fi

require_contains "no file found at reports/latticra-seal-cli-hashes.txt" "$tmpdir/hardlink-hashes-read.out"

if grep -Fq "do-not-overwrite-hash-hardlink" "$tmpdir/hardlink-hashes-read.out"; then
  fail "Seal CLI hashes command must not read from a hard-linked hash-list artifact"
fi

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/hardlink-hash-file.out" 2>&1); then
  fail "Seal CLI check must refuse a hard-linked hash-list file path"
fi

require_contains "FAIL: could not clear previous hash list" "$tmpdir/hardlink-hash-file.out"
require_contains "STATUS: FAIL" "$tmpdir/hardlink-hash-file.out"

if [ "$(cat "$victim_hash_hardlink")" != "do-not-overwrite-hash-hardlink" ]; then
  fail "Seal CLI must not overwrite a hard-linked target while writing the hash list"
fi

rm "$case_root/reports/latticra-seal-cli-hashes.txt"

printf 'stale-hash-temp\n' > "$case_root/reports/latticra-seal-cli-hashes.tmp"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/stale-hash-tmp.out" 2>&1); then
  cat "$tmpdir/stale-hash-tmp.out" >&2 || true
  fail "Seal CLI check must clear a stale single-link temporary hash list before writing"
fi

require_contains "STATUS: PASS" "$tmpdir/stale-hash-tmp.out"

[ ! -e "$case_root/reports/latticra-seal-cli-hashes.tmp" ] ||
  fail "Seal CLI must not leave a stale temporary hash list after successful promotion"

rm "$case_root/reports/latticra-seal-cli-report.txt"
rm "$case_root/reports/latticra-seal-cli-hashes.txt"

victim_hash_tmp="$tmpdir/victim-hash-tmp"
printf 'do-not-overwrite-hash-tmp\n' > "$victim_hash_tmp"
ln -s "$victim_hash_tmp" "$case_root/reports/latticra-seal-cli-hashes.tmp"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-hash-tmp.out" 2>&1); then
  fail "Seal CLI check must refuse a symlinked temporary hash-list path"
fi

require_contains "FAIL: could not clear temporary hash list" "$tmpdir/symlink-hash-tmp.out"
require_contains "STATUS: FAIL" "$tmpdir/symlink-hash-tmp.out"

if [ "$(cat "$victim_hash_tmp")" != "do-not-overwrite-hash-tmp" ]; then
  fail "Seal CLI must not overwrite a symlink target while writing the temporary hash list"
fi

[ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when the temporary hash-list path is refused"

rm "$case_root/reports/latticra-seal-cli-hashes.tmp"

victim_hash_tmp_hardlink="$tmpdir/victim-hash-tmp-hardlink"
printf 'do-not-overwrite-hash-tmp-hardlink\n' > "$victim_hash_tmp_hardlink"
ln "$victim_hash_tmp_hardlink" "$case_root/reports/latticra-seal-cli-hashes.tmp"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/hardlink-hash-tmp.out" 2>&1); then
  fail "Seal CLI check must refuse a hard-linked temporary hash-list path"
fi

require_contains "FAIL: could not clear temporary hash list" "$tmpdir/hardlink-hash-tmp.out"
require_contains "STATUS: FAIL" "$tmpdir/hardlink-hash-tmp.out"

if [ "$(cat "$victim_hash_tmp_hardlink")" != "do-not-overwrite-hash-tmp-hardlink" ]; then
  fail "Seal CLI must not overwrite a hard-linked target while writing the temporary hash list"
fi

[ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when the temporary hash-list hardlink is refused"

rm "$case_root/reports/latticra-seal-cli-hashes.tmp"

mkdir -p "$case_root/.venv-piper/bin"
printf 'local tool that must not enter Seal digests\n' > "$case_root/.venv-piper/bin/local-tool"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/local-venv-check.out" 2>&1); then
  fail "Seal CLI check must pass with local virtualenv-style directories present"
fi

require_contains "STATUS: PASS" "$tmpdir/local-venv-check.out"

if grep -Fq ".venv-piper" "$case_root/reports/latticra-seal-cli-hashes.txt"; then
  fail "Seal CLI hash list must exclude local virtualenv-style directories"
fi

printf 'not-a-canonical-hash-list\n' > "$case_root/reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/malformed-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must fail closed on malformed hash-list artifacts"
fi

require_contains "hash list artifact is malformed: reports/latticra-seal-cli-hashes.txt" "$tmpdir/malformed-hashes-read.out"

if grep -Fq "not-a-canonical-hash-list" "$tmpdir/malformed-hashes-read.out"; then
  fail "Seal CLI hashes command must not stream malformed hash-list artifacts"
fi

: > "$case_root/reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/empty-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must fail closed on empty hash-list artifacts"
fi

require_contains "hash list artifact is malformed: reports/latticra-seal-cli-hashes.txt" "$tmpdir/empty-hashes-read.out"

printf '0000000000000000000000000000000000000000000000000000000000000000  README.md\000hidden-hash-payload\n' \
  > "$case_root/reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/nul-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must fail closed on embedded-NUL hash-list artifacts"
fi

require_contains "hash list artifact is malformed: reports/latticra-seal-cli-hashes.txt" "$tmpdir/nul-hashes-read.out"

if grep -Fq "hidden-hash-payload" "$tmpdir/nul-hashes-read.out"; then
  fail "Seal CLI hashes command must not stream embedded-NUL hash-list artifacts"
fi

printf '0000000000000000000000000000000000000000000000000000000000000000  README.md\r\n' \
  > "$case_root/reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/crlf-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must fail closed on CRLF hash-list artifacts"
fi

require_contains "hash list artifact is malformed: reports/latticra-seal-cli-hashes.txt" "$tmpdir/crlf-hashes-read.out"

printf '0000000000000000000000000000000000000000000000000000000000000000  README.md' \
  > "$case_root/reports/latticra-seal-cli-hashes.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" hashes > "$tmpdir/no-lf-hashes-read.out" 2>&1); then
  fail "Seal CLI hashes command must fail closed on non-LF-terminated hash-list artifacts"
fi

require_contains "hash list artifact is malformed: reports/latticra-seal-cli-hashes.txt" "$tmpdir/no-lf-hashes-read.out"

native_artifact_scope_case="$tmpdir/native-artifact-scope-case"
mkdir "$native_artifact_scope_case" "$native_artifact_scope_case/reports"
cp README.md LICENSE "$native_artifact_scope_case/"
cat > "$native_artifact_scope_case/latticra.seal" <<'MANIFEST'
schema = "latticra.seal/v0.1"
format = "toml"
kind = "local-integrity-manifest"

[project]
name = "Latticra"
id = "latticra"
version = "0.1.0"
repository = "https://github.com/Bryforge/Latticra"
description = "Native generated artifacts must stay out of digest evidence."
license = "SEE LICENSE"

[seal]
mode = "local-integrity"
status = "unsigned"
algorithm = "sha256"
digest_encoding = "hex"
canonicalization = "relative-path + raw-bytes + unix-lf-preferred"
trust_boundary = "project-root"
created_by = "Latticra Seal test"
created_at = "2026-05-24"

[paths]
include = [
  ".",
]

exclude = [
  ".git/",
]

[policy]
require_readme = true
require_license = true
deny_private_keys = true
deny_env_files = true
deny_obvious_tokens = true
deny_large_binaries = false
max_file_size_mb = 25

[policy.required_files]
paths = [
  "README.md",
  "LICENSE",
]

[policy.deny_filenames]
patterns = [
  ".env",
  "id_rsa",
  "id_ed25519",
  "*.pem",
  "*.key",
]

[policy.deny_contents]
pattern_parts = [
  ["BEGIN ", "PRIVATE", " KEY"],
  ["BEGIN ", "RSA PRIVATE", " KEY"],
  ["BEGIN ", "OPENSSH PRIVATE", " KEY"],
  ["OPENAI", "_API_KEY="],
  ["GITHUB", "_TOKEN="],
  ["AWS", "_SECRET_ACCESS_KEY="],
]

[report]
default_output = "reports/latticra-seal-cli-report.txt"
hash_list_output = "reports/latticra-seal-cli-hashes.txt"
legacy_smoke_output = "reports/latticra-seal-report.txt"
legacy_smoke_hash_list_output = "reports/latticra-seal-file-hashes.txt"
include_file_list = true
include_policy_results = true
include_digest_summary = true

[proof]
manifest_hash = ""
MANIFEST

printf 'stale native report\n' > "$native_artifact_scope_case/reports/latticra-seal-cli-report.txt"
printf 'stale native report temp\n' > "$native_artifact_scope_case/reports/latticra-seal-cli-report.tmp"
printf 'legacy smoke report\n' > "$native_artifact_scope_case/reports/latticra-seal-report.txt"
printf 'legacy smoke hash list\n' > "$native_artifact_scope_case/reports/latticra-seal-file-hashes.txt"
printf 'baseline lock\n' > "$native_artifact_scope_case/latticra.seal.lock"
printf 'baseline temp lock\n' > "$native_artifact_scope_case/latticra.seal.lock.tmp"

if ! (cd "$native_artifact_scope_case" && "$tmpdir/latticra-seal" check > "$tmpdir/native-artifact-scope.out" 2>&1); then
  cat "$tmpdir/native-artifact-scope.out" >&2 || true
  fail "Seal CLI check must pass while suppressing native generated artifacts from digest scope"
fi

require_contains "STATUS: PASS" "$tmpdir/native-artifact-scope.out"

for generated_path in \
  "reports/latticra-seal-cli-report.txt" \
  "reports/latticra-seal-cli-report.tmp" \
  "reports/latticra-seal-cli-hashes.txt" \
  "reports/latticra-seal-cli-hashes.tmp" \
  "reports/latticra-seal-report.txt" \
  "reports/latticra-seal-file-hashes.txt" \
  "latticra.seal.lock" \
  "latticra.seal.lock.tmp"
do
  if grep -Fq "  $generated_path" "$native_artifact_scope_case/reports/latticra-seal-cli-hashes.txt"; then
    fail "Seal CLI hash list must suppress generated artifact path: $generated_path"
  fi
done

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

[project]
name = "Latticra"
id = "latticra"
version = "0.1.0"
repository = "https://github.com/Bryforge/Latticra"
license = "SEE LICENSE"

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

[project]
name = "Latticra"
id = "latticra"
version = "0.1.0"
repository = "https://github.com/Bryforge/Latticra"
license = "SEE LICENSE"

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

[project]
name = "Latticra"
id = "latticra"
version = "0.1.0"
repository = "https://github.com/Bryforge/Latticra"
license = "SEE LICENSE"

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

[project]
name = "Latticra"
id = "latticra"
version = "0.1.0"
repository = "https://github.com/Bryforge/Latticra"
license = "SEE LICENSE"

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

excluded_required_case="$tmpdir/excluded-required-case"
mkdir -p "$excluded_required_case/docs"
cp README.md LICENSE "$excluded_required_case/"
printf 'required file must remain in digest scope\n' > "$excluded_required_case/docs/REQUIRED.md"
cat > "$excluded_required_case/latticra.seal" <<'MANIFEST'
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
  "docs/",
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
  "docs/REQUIRED.md",
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

if (cd "$excluded_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/excluded-required.out" 2>&1); then
  fail "Seal CLI check must fail closed when a required file is excluded from digest scope"
fi

require_contains "FAIL: required file excluded from digest scope: docs/REQUIRED.md" "$tmpdir/excluded-required.out"
require_contains "FAIL: hash list not written because required file is excluded from digest scope: docs/REQUIRED.md" "$tmpdir/excluded-required.out"
require_contains "STATUS: FAIL" "$tmpdir/excluded-required.out"

[ ! -e "$excluded_required_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when a required file is excluded from digest scope"

rm "$custom_required_case/CUSTOM_REQUIRED.md"

if (cd "$custom_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/custom-required-missing.out" 2>&1); then
  fail "Seal CLI check must fail when a manifest-declared required file is missing"
fi

require_contains "FAIL: required file missing or unsafe: CUSTOM_REQUIRED.md" "$tmpdir/custom-required-missing.out"
require_contains "FAIL: hash list not written because required file is missing or unsafe: CUSTOM_REQUIRED.md" "$tmpdir/custom-required-missing.out"
require_contains "STATUS: FAIL" "$tmpdir/custom-required-missing.out"

[ ! -e "$custom_required_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must remove stale hash lists when a required file is missing"

hardlink_required_case="$tmpdir/hardlink-required-case"
mkdir "$hardlink_required_case"
cp README.md LICENSE "$hardlink_required_case/"
hardlink_required_source="$tmpdir/hardlink-required-source"
printf 'hard-linked required evidence must fail closed\n' > "$hardlink_required_source"
ln "$hardlink_required_source" "$hardlink_required_case/CUSTOM_REQUIRED.md"
cp "$custom_required_case/latticra.seal" "$hardlink_required_case/"

if (cd "$hardlink_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/hardlink-required.out" 2>&1); then
  fail "Seal CLI check must fail when a manifest-declared required file is hard-linked"
fi

require_contains "FAIL: required file missing or unsafe: CUSTOM_REQUIRED.md" "$tmpdir/hardlink-required.out"
require_contains "FAIL: hash list not written because required file is missing or unsafe: CUSTOM_REQUIRED.md" "$tmpdir/hardlink-required.out"
require_contains "STATUS: FAIL" "$tmpdir/hardlink-required.out"

[ ! -e "$hardlink_required_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when a required file is hard-linked"

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

escaped_required_case="$tmpdir/escaped-required-case"
mkdir "$escaped_required_case"
cp README.md LICENSE "$escaped_required_case/"
cat > "$escaped_required_case/latticra.seal" <<'MANIFEST'
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
  "READ\ME.md",
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

if (cd "$escaped_required_case" && "$tmpdir/latticra-seal" check > "$tmpdir/escaped-required.out" 2>&1); then
  fail "Seal CLI check must fail closed on escaped manifest required-file paths"
fi

require_contains "FAIL: policy required files are missing, duplicate, or malformed" "$tmpdir/escaped-required.out"
require_contains "STATUS: FAIL" "$tmpdir/escaped-required.out"

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

escaped_policy_case="$tmpdir/escaped-policy-case"
mkdir "$escaped_policy_case"
cp README.md LICENSE "$escaped_policy_case/"
cat > "$escaped_policy_case/latticra.seal" <<'MANIFEST'
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
  ["CUSTOM", "\_MARKER="],
]
MANIFEST

if (cd "$escaped_policy_case" && "$tmpdir/latticra-seal" check > "$tmpdir/escaped-policy.out" 2>&1); then
  fail "Seal CLI check must fail closed on escaped deny content marker parts"
fi

require_contains "FAIL: policy deny content pattern parts are missing, duplicate, or malformed" "$tmpdir/escaped-policy.out"
require_contains "FAIL: policy denial scan skipped because policy configuration was invalid" "$tmpdir/escaped-policy.out"
require_contains "STATUS: FAIL" "$tmpdir/escaped-policy.out"

empty_policy_part_case="$tmpdir/empty-policy-part-case"
mkdir "$empty_policy_part_case"
cp README.md LICENSE "$empty_policy_part_case/"
cat > "$empty_policy_part_case/latticra.seal" <<'MANIFEST'
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
  ["CUSTOM", "", "_MARKER="],
]
MANIFEST

if (cd "$empty_policy_part_case" && "$tmpdir/latticra-seal" check > "$tmpdir/empty-policy-part.out" 2>&1); then
  fail "Seal CLI check must fail closed on empty deny content marker parts"
fi

require_contains "FAIL: policy deny content pattern parts are missing, duplicate, or malformed" "$tmpdir/empty-policy-part.out"
require_contains "FAIL: policy denial scan skipped because policy configuration was invalid" "$tmpdir/empty-policy-part.out"
require_contains "STATUS: FAIL" "$tmpdir/empty-policy-part.out"

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

unsupported_section_case="$tmpdir/unsupported-section-case"
mkdir "$unsupported_section_case"
cp README.md LICENSE "$unsupported_section_case/"
cp latticra.seal "$unsupported_section_case/latticra.seal"
printf '\n[unsupported]\nclaim = "ignored"\n' >> "$unsupported_section_case/latticra.seal"

if (cd "$unsupported_section_case" && "$tmpdir/latticra-seal" check > "$tmpdir/unsupported-section.out" 2>&1); then
  fail "Seal CLI check must fail closed on unsupported manifest sections"
fi

require_contains "FAIL: manifest section headers are supported" "$tmpdir/unsupported-section.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/unsupported-section.out"
require_contains "STATUS: FAIL" "$tmpdir/unsupported-section.out"

[ ! -e "$unsupported_section_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when manifest sections are unsupported"

quoted_unsupported_section_case="$tmpdir/quoted-unsupported-section-case"
mkdir "$quoted_unsupported_section_case"
cp README.md LICENSE "$quoted_unsupported_section_case/"
cp latticra.seal "$quoted_unsupported_section_case/latticra.seal"
printf '\n["unsupported"]\nclaim = "ignored"\n' >> "$quoted_unsupported_section_case/latticra.seal"

if (cd "$quoted_unsupported_section_case" && "$tmpdir/latticra-seal" check > "$tmpdir/quoted-unsupported-section.out" 2>&1); then
  fail "Seal CLI check must fail closed on quoted unsupported manifest sections"
fi

require_contains "FAIL: manifest section headers are supported" "$tmpdir/quoted-unsupported-section.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/quoted-unsupported-section.out"
require_contains "STATUS: FAIL" "$tmpdir/quoted-unsupported-section.out"

[ ! -e "$quoted_unsupported_section_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when quoted manifest sections are unsupported"

malformed_section_case="$tmpdir/malformed-section-case"
mkdir "$malformed_section_case"
cp README.md LICENSE "$malformed_section_case/"
cp latticra.seal "$malformed_section_case/latticra.seal"
printf '\n[broken-section\nclaim = "ignored"\n' >> "$malformed_section_case/latticra.seal"

if (cd "$malformed_section_case" && "$tmpdir/latticra-seal" check > "$tmpdir/malformed-section.out" 2>&1); then
  fail "Seal CLI check must fail closed on malformed manifest section headers"
fi

require_contains "FAIL: manifest section headers are supported" "$tmpdir/malformed-section.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/malformed-section.out"
require_contains "STATUS: FAIL" "$tmpdir/malformed-section.out"

[ ! -e "$malformed_section_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when manifest section headers are malformed"

missing_project_identity_case="$tmpdir/missing-project-identity-case"
mkdir "$missing_project_identity_case"
cp README.md LICENSE "$missing_project_identity_case/"
sed '/^id = "latticra"$/d' latticra.seal > "$missing_project_identity_case/latticra.seal"

if (cd "$missing_project_identity_case" && "$tmpdir/latticra-seal" check > "$tmpdir/missing-project-identity.out" 2>&1); then
  fail "Seal CLI check must fail closed when project identity is missing"
fi

require_contains "FAIL: project id is latticra" "$tmpdir/missing-project-identity.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/missing-project-identity.out"
require_contains "STATUS: FAIL" "$tmpdir/missing-project-identity.out"

[ ! -e "$missing_project_identity_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when project identity is missing"

project_identity_drift_case="$tmpdir/project-identity-drift-case"
mkdir "$project_identity_drift_case"
cp README.md LICENSE "$project_identity_drift_case/"
sed 's/id = "latticra"/id = "other-project"/' latticra.seal > "$project_identity_drift_case/latticra.seal"

if (cd "$project_identity_drift_case" && "$tmpdir/latticra-seal" check > "$tmpdir/project-identity-drift.out" 2>&1); then
  fail "Seal CLI check must fail closed when declared project identity drifts"
fi

require_contains "FAIL: project id is latticra" "$tmpdir/project-identity-drift.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/project-identity-drift.out"
require_contains "STATUS: FAIL" "$tmpdir/project-identity-drift.out"

[ ! -e "$project_identity_drift_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when project identity drifts"

large_binary_claim_case="$tmpdir/large-binary-claim-case"
mkdir "$large_binary_claim_case"
cp README.md LICENSE "$large_binary_claim_case/"
sed 's/deny_large_binaries = false/deny_large_binaries = true/' latticra.seal > "$large_binary_claim_case/latticra.seal"

if (cd "$large_binary_claim_case" && "$tmpdir/latticra-seal" check > "$tmpdir/large-binary-claim.out" 2>&1); then
  fail "Seal CLI check must fail closed on unsupported large-binary denial claims"
fi

require_contains "FAIL: policy large binary denial is disabled" "$tmpdir/large-binary-claim.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/large-binary-claim.out"
require_contains "STATUS: FAIL" "$tmpdir/large-binary-claim.out"

[ ! -e "$large_binary_claim_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when large-binary policy is unsupported"

max_file_size_drift_case="$tmpdir/max-file-size-drift-case"
mkdir "$max_file_size_drift_case"
cp README.md LICENSE "$max_file_size_drift_case/"
sed 's/max_file_size_mb = 25/max_file_size_mb = 100/' latticra.seal > "$max_file_size_drift_case/latticra.seal"

if (cd "$max_file_size_drift_case" && "$tmpdir/latticra-seal" check > "$tmpdir/max-file-size-drift.out" 2>&1); then
  fail "Seal CLI check must fail closed when inactive max-file-size policy drifts"
fi

require_contains "FAIL: policy max file size is 25 MB" "$tmpdir/max-file-size-drift.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/max-file-size-drift.out"
require_contains "STATUS: FAIL" "$tmpdir/max-file-size-drift.out"

[ ! -e "$max_file_size_drift_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when max-file-size policy drifts"

report_shape_drift_case="$tmpdir/report-shape-drift-case"
mkdir "$report_shape_drift_case"
cp README.md LICENSE "$report_shape_drift_case/"
sed 's#default_output = "reports/latticra-seal-cli-report.txt"#default_output = "reports/drifted-report.txt"#' latticra.seal > "$report_shape_drift_case/latticra.seal"

if (cd "$report_shape_drift_case" && "$tmpdir/latticra-seal" check > "$tmpdir/report-shape-drift.out" 2>&1); then
  fail "Seal CLI check must fail closed when declared report output drifts from CLI output"
fi

require_contains "FAIL: report default output is reports/latticra-seal-cli-report.txt" "$tmpdir/report-shape-drift.out"
require_contains "STATUS: FAIL" "$tmpdir/report-shape-drift.out"

proof_shape_claim_case="$tmpdir/proof-shape-claim-case"
mkdir "$proof_shape_claim_case"
cp README.md LICENSE "$proof_shape_claim_case/"
sed 's/manifest_hash = ""/manifest_hash = "claimed-proof"/' latticra.seal > "$proof_shape_claim_case/latticra.seal"

if (cd "$proof_shape_claim_case" && "$tmpdir/latticra-seal" check > "$tmpdir/proof-shape-claim.out" 2>&1); then
  fail "Seal CLI check must fail closed on unsupported proof manifest hash claims"
fi

require_contains "FAIL: proof manifest hash is empty" "$tmpdir/proof-shape-claim.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/proof-shape-claim.out"
require_contains "STATUS: FAIL" "$tmpdir/proof-shape-claim.out"

[ ! -e "$proof_shape_claim_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when proof metadata is unsupported"

proof_root_claim_case="$tmpdir/proof-root-claim-case"
mkdir "$proof_root_claim_case"
cp README.md LICENSE "$proof_root_claim_case/"
sed 's/root_hash = ""/root_hash = "claimed-root"/' latticra.seal > "$proof_root_claim_case/latticra.seal"

if (cd "$proof_root_claim_case" && "$tmpdir/latticra-seal" check > "$tmpdir/proof-root-claim.out" 2>&1); then
  fail "Seal CLI check must fail closed on unsupported proof root hash claims"
fi

require_contains "FAIL: proof root hash is empty" "$tmpdir/proof-root-claim.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/proof-root-claim.out"
require_contains "STATUS: FAIL" "$tmpdir/proof-root-claim.out"

[ ! -e "$proof_root_claim_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must not promote a hash list when proof root metadata is unsupported"

symlink_dir_target="$tmpdir/symlink-dir-target"
mkdir "$symlink_dir_target"
printf 'outside directory content must not enter Seal evidence\n' > "$symlink_dir_target/secret.txt"
ln -s "$symlink_dir_target" "$case_root/symlink-dir"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/symlink-dir-scope.out" 2>&1); then
  fail "Seal CLI check must fail closed on in-scope symlinked directories"
fi

require_contains "FAIL: refusing symlink in digest scope: symlink-dir" "$tmpdir/symlink-dir-scope.out"
require_contains "hash list not written because digest traversal failed" "$tmpdir/symlink-dir-scope.out"
require_contains "STATUS: FAIL" "$tmpdir/symlink-dir-scope.out"

[ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must remove stale hash lists when an in-scope symlinked directory is refused"

rm "$case_root/symlink-dir"

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

unsafe_digest_path="$case_root/unsafe\\path.txt"
printf 'unsafe path spelling must not enter canonical Seal hashes\n' > "$unsafe_digest_path"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/unsafe-digest-path.out" 2>&1); then
  fail "Seal CLI check must fail closed on in-scope paths that cannot be represented canonically"
fi

require_contains "FAIL: refusing unsafe path in digest scope: unsafe\\path.txt" "$tmpdir/unsafe-digest-path.out"
require_contains "hash list not written because digest traversal failed" "$tmpdir/unsafe-digest-path.out"
require_contains "STATUS: FAIL" "$tmpdir/unsafe-digest-path.out"

[ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must remove stale hash lists when an unsafe in-scope path is refused"

rm "$unsafe_digest_path"

printf 'hard-linked content must not enter Seal evidence\n' > "$case_root/reports/hardlink-scope-source"
ln "$case_root/reports/hardlink-scope-source" "$case_root/hardlink-scope.txt"

if (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/hardlink-scope.out" 2>&1); then
  fail "Seal CLI check must fail closed on in-scope hard-linked files"
fi

require_contains "FAIL: refusing hard-linked file in digest scope: hardlink-scope.txt" "$tmpdir/hardlink-scope.out"
require_contains "hash list not written because digest traversal failed" "$tmpdir/hardlink-scope.out"
require_contains "STATUS: FAIL" "$tmpdir/hardlink-scope.out"

[ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must remove stale hash lists when an in-scope hard-linked file is refused"

rm "$case_root/hardlink-scope.txt"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" check > "$tmpdir/post-hardlink-scope.out" 2>&1); then
  fail "Seal CLI check must recover after an in-scope hard-linked file is removed"
fi

require_contains "STATUS: PASS" "$tmpdir/post-hardlink-scope.out"

hardlink_manifest_case="$tmpdir/hardlink-manifest-case"
mkdir "$hardlink_manifest_case"
cp README.md LICENSE latticra.seal "$hardlink_manifest_case/"

if ! (cd "$hardlink_manifest_case" && "$tmpdir/latticra-seal" check > "$tmpdir/hardlink-manifest-prime.out" 2>&1); then
  cat "$tmpdir/hardlink-manifest-prime.out" >&2 || true
  fail "Seal CLI check must prime a hash list before the hard-linked manifest case"
fi

[ -s "$hardlink_manifest_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI check must write a priming hash list before the hard-linked manifest case"

manifest_hardlink_source="$tmpdir/manifest-hardlink-source"
cp "$hardlink_manifest_case/latticra.seal" "$manifest_hardlink_source"
rm "$hardlink_manifest_case/latticra.seal"
ln "$manifest_hardlink_source" "$hardlink_manifest_case/latticra.seal"

if (cd "$hardlink_manifest_case" && "$tmpdir/latticra-seal" check > "$tmpdir/hardlink-manifest.out" 2>&1); then
  fail "Seal CLI check must fail closed on a hard-linked manifest"
fi

require_contains "PASS: stale hash artifacts cleared before check" "$tmpdir/hardlink-manifest.out"
require_contains "FAIL: latticra.seal is missing or unreadable" "$tmpdir/hardlink-manifest.out"
require_contains "STATUS: FAIL" "$tmpdir/hardlink-manifest.out"

[ ! -e "$hardlink_manifest_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must clear stale hash lists before failing on a hard-linked manifest"

verify_hardlink_manifest_case="$tmpdir/verify-hardlink-manifest-case"
mkdir "$verify_hardlink_manifest_case"
cp README.md LICENSE latticra.seal "$verify_hardlink_manifest_case/"

if ! (cd "$verify_hardlink_manifest_case" && "$tmpdir/latticra-seal" baseline > "$tmpdir/verify-hardlink-manifest-prime.out" 2>&1); then
  cat "$tmpdir/verify-hardlink-manifest-prime.out" >&2 || true
  fail "Seal CLI baseline must prime a lockfile before the verify hard-linked manifest case"
fi

[ -s "$verify_hardlink_manifest_case/latticra.seal.lock" ] ||
  fail "Seal CLI baseline must write a priming lockfile before the verify hard-linked manifest case"

[ -s "$verify_hardlink_manifest_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI baseline must leave a priming hash list before the verify hard-linked manifest case"

verify_manifest_hardlink_source="$tmpdir/verify-manifest-hardlink-source"
cp "$verify_hardlink_manifest_case/latticra.seal" "$verify_manifest_hardlink_source"
rm "$verify_hardlink_manifest_case/latticra.seal"
ln "$verify_manifest_hardlink_source" "$verify_hardlink_manifest_case/latticra.seal"

if (cd "$verify_hardlink_manifest_case" && "$tmpdir/latticra-seal" verify > "$tmpdir/verify-hardlink-manifest.out" 2>&1); then
  fail "Seal CLI verify must fail closed on a hard-linked manifest"
fi

require_contains "PASS: stale hash artifacts cleared before verify" "$tmpdir/verify-hardlink-manifest.out"
require_contains "PASS: latticra.seal.lock exists" "$tmpdir/verify-hardlink-manifest.out"
require_contains "FAIL: latticra.seal is missing or unreadable" "$tmpdir/verify-hardlink-manifest.out"
require_contains "STATUS: FAIL" "$tmpdir/verify-hardlink-manifest.out"

[ ! -e "$verify_hardlink_manifest_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI verify must clear stale hash lists before failing on a hard-linked manifest"

nul_manifest_case="$tmpdir/nul-manifest-case"
mkdir "$nul_manifest_case"
cp README.md LICENSE latticra.seal "$nul_manifest_case/"

if ! (cd "$nul_manifest_case" && "$tmpdir/latticra-seal" check > "$tmpdir/nul-manifest-prime.out" 2>&1); then
  cat "$tmpdir/nul-manifest-prime.out" >&2 || true
  fail "Seal CLI check must prime a hash list before the embedded-NUL manifest case"
fi

[ -s "$nul_manifest_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI check must write a priming hash list before the embedded-NUL manifest case"

printf '\000ignored_after_nul = "true"\n' >> "$nul_manifest_case/latticra.seal"

if (cd "$nul_manifest_case" && "$tmpdir/latticra-seal" check > "$tmpdir/nul-manifest.out" 2>&1); then
  fail "Seal CLI check must fail closed on manifests with embedded NUL bytes"
fi

require_contains "PASS: stale hash artifacts cleared before check" "$tmpdir/nul-manifest.out"
require_contains "FAIL: latticra.seal is missing or unreadable" "$tmpdir/nul-manifest.out"
require_contains "STATUS: FAIL" "$tmpdir/nul-manifest.out"

[ ! -e "$nul_manifest_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must clear stale hash lists before failing on an embedded-NUL manifest"

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

manifest_shape_hash_case="$tmpdir/manifest-shape-hash-case"
mkdir "$manifest_shape_hash_case"
cp README.md LICENSE latticra.seal "$manifest_shape_hash_case/"

if ! (cd "$manifest_shape_hash_case" && "$tmpdir/latticra-seal" check > "$tmpdir/manifest-shape-hash-prime.out" 2>&1); then
  cat "$tmpdir/manifest-shape-hash-prime.out" >&2 || true
  fail "Seal CLI check must prime a hash list before the manifest-shape hash-list case"
fi

[ -s "$manifest_shape_hash_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI check must write a priming hash list before the manifest-shape hash-list case"

awk '
  /^schema = / && injected == 0 {
    print
    injected = 1
  }
  { print }
' "$manifest_shape_hash_case/latticra.seal" > "$tmpdir/manifest-shape-hash.seal"
mv "$tmpdir/manifest-shape-hash.seal" "$manifest_shape_hash_case/latticra.seal"

if (cd "$manifest_shape_hash_case" && "$tmpdir/latticra-seal" check > "$tmpdir/manifest-shape-hash.out" 2>&1); then
  fail "Seal CLI check must reject malformed manifest shape before promoting a hash list"
fi

require_contains "FAIL: schema is latticra.seal/v0.1" "$tmpdir/manifest-shape-hash.out"
require_contains "FAIL: hash list not written because manifest, policy, or report shape was invalid" "$tmpdir/manifest-shape-hash.out"
require_contains "STATUS: FAIL" "$tmpdir/manifest-shape-hash.out"

[ ! -e "$manifest_shape_hash_case/reports/latticra-seal-cli-hashes.txt" ] ||
  fail "Seal CLI must clear stale hash lists and refuse promotion when manifest shape is invalid"

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

  require_contains "FAIL: could not inspect file for policy markers: unreadable-file.txt" "$tmpdir/unreadable-file.out"
  require_contains "hash list not written because earlier checks failed" "$tmpdir/unreadable-file.out"
  require_contains "STATUS: FAIL" "$tmpdir/unreadable-file.out"

  [ ! -e "$case_root/reports/latticra-seal-cli-hashes.txt" ] ||
    fail "Seal CLI must remove stale hash lists when policy inspection fails"
fi

printf 'stale-baseline-temp\n' > "$case_root/latticra.seal.lock.tmp"

if ! (cd "$case_root" && "$tmpdir/latticra-seal" baseline > "$tmpdir/baseline-success.out" 2>&1); then
  cat "$tmpdir/baseline-success.out" >&2 || true
  fail "Seal CLI baseline must write a valid baseline after check passes"
fi

require_contains "Baseline written to: latticra.seal.lock" "$tmpdir/baseline-success.out"

[ -s "$case_root/latticra.seal.lock" ] ||
  fail "Seal CLI baseline must leave a non-empty lockfile"

cmp -s "$case_root/reports/latticra-seal-cli-hashes.txt" "$case_root/latticra.seal.lock" ||
  fail "Seal CLI baseline must copy the generated native hash list exactly"

[ ! -e "$case_root/latticra.seal.lock.tmp" ] ||
  fail "Seal CLI baseline must not leave a stale temporary lockfile after successful promotion"

printf 'not-a-valid-baseline\n' > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/malformed-baseline.out" 2>&1); then
  fail "Seal CLI verify must refuse a malformed baseline"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/malformed-baseline.out"

: > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/empty-baseline.out" 2>&1); then
  fail "Seal CLI verify must refuse an empty baseline"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/empty-baseline.out"

printf '0000000000000000000000000000000000000000000000000000000000000000  README.md\000hidden-baseline-payload\n' \
  > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/nul-baseline.out" 2>&1); then
  fail "Seal CLI verify must refuse embedded-NUL baselines"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/nul-baseline.out"

if grep -Fq "hidden-baseline-payload" "$tmpdir/nul-baseline.out"; then
  fail "Seal CLI verify must not echo embedded-NUL baseline payloads"
fi

printf '0000000000000000000000000000000000000000000000000000000000000000  README.md\r\n' \
  > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/crlf-baseline.out" 2>&1); then
  fail "Seal CLI verify must refuse CRLF baselines"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/crlf-baseline.out"

printf '0000000000000000000000000000000000000000000000000000000000000000  README.md' \
  > "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/no-lf-baseline.out" 2>&1); then
  fail "Seal CLI verify must refuse non-LF-terminated baselines"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/no-lf-baseline.out"

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

victim_lock_hardlink="$tmpdir/victim-lock-hardlink"
printf 'do-not-overwrite-hardlink\n' > "$victim_lock_hardlink"
ln "$victim_lock_hardlink" "$case_root/latticra.seal.lock"

if (cd "$case_root" && "$tmpdir/latticra-seal" verify > "$tmpdir/hardlink-baseline-verify.out" 2>&1); then
  fail "Seal CLI verify must refuse a hard-linked baseline path"
fi

require_contains "latticra.seal.lock is missing or unreadable" "$tmpdir/hardlink-baseline-verify.out"

if (cd "$case_root" && "$tmpdir/latticra-seal" baseline > "$tmpdir/hardlink-baseline.out" 2>&1); then
  fail "Seal CLI baseline must refuse a hard-linked baseline path"
fi

require_contains "could not write baseline: latticra.seal.lock" "$tmpdir/hardlink-baseline.out"

if [ "$(cat "$victim_lock_hardlink")" != "do-not-overwrite-hardlink" ]; then
  fail "Seal CLI must not overwrite a hard-linked target while writing the baseline"
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

rm "$case_root/latticra.seal.lock.tmp"

victim_tmp_lock_hardlink="$tmpdir/victim-tmp-lock-hardlink"
printf 'do-not-overwrite-tmp-hardlink\n' > "$victim_tmp_lock_hardlink"
ln "$victim_tmp_lock_hardlink" "$case_root/latticra.seal.lock.tmp"

if (cd "$case_root" && "$tmpdir/latticra-seal" baseline > "$tmpdir/hardlink-baseline-tmp.out" 2>&1); then
  fail "Seal CLI baseline must refuse a hard-linked temporary baseline path"
fi

require_contains "could not write baseline: latticra.seal.lock" "$tmpdir/hardlink-baseline-tmp.out"

if [ "$(cat "$victim_tmp_lock_hardlink")" != "do-not-overwrite-tmp-hardlink" ]; then
  fail "Seal CLI must not overwrite a hard-linked target while writing the temporary baseline"
fi

[ ! -e "$case_root/latticra.seal.lock" ] ||
  fail "Seal CLI must not promote a baseline when the temporary baseline hardlink is refused"

printf 'PASS: Latticra Seal CLI output hardening rejects unsafe artifact links\n'

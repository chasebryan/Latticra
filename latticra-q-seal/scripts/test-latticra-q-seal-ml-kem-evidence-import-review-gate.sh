#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-evidence-import-review-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem evidence import review gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem evidence import review gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-evidence-import-review-gate"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_evidence_import_review_gate.h
require_file latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_file latticra-q-seal/tests/q_seal_ml_kem_evidence_import_review_gate_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-import-review-gate.sh
require_file scripts/test-latticra-q-seal-ml-kem-evidence-import-review-gate.sh

require_contains 'latticra_q_seal_ml_kem_evidence_import_review_gate_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_evidence_import_review_gate.h
require_contains 'latticra-q-seal-ml-kem-evidence-import-review-gate/0.1' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'evidence_import_packet_manifest_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'vector_fixture_digest_ledger_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'receipt_replay_results_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'reviewer_role_mapping_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'fixture_digest_rows_imported = 0u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'receipt_replay_transcripts_imported = 0u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'reviewer_role_records_imported = 0u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'required_evidence_import_items_total = 37u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c
require_contains 'latticra q-seal ml-kem evidence import review gate invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_evidence_import_review_gate_invariants.c
require_contains 'evidence_import_review_gate_present=1' latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_contains 'fixture_digest_rows_imported=0' latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_contains 'evidence_import_packet_manifest_bound=1' latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_contains 'receipt_replay_transcripts_imported=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_contains 'reviewer_role_records_imported=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_contains 'required_evidence_import_items_total=37' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md
require_contains 'LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_REVIEW_GATE.md' docs/FOUNDATION_INDEX.md
require_contains 'evidence_import_review_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_evidence_import_review_gate.c \
  latticra-q-seal/tests/q_seal_ml_kem_evidence_import_review_gate_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem evidence import review gate: ok\n'

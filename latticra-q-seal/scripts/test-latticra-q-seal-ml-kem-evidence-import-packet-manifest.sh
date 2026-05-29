#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-evidence-import-packet-manifest.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem evidence import packet manifest: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem evidence import packet manifest: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-evidence-import-packet-manifest"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_evidence_import_packet_manifest.h
require_file latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_file latticra-q-seal/tests/q_seal_ml_kem_evidence_import_packet_manifest_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-evidence-import-packet-manifest.sh
require_file scripts/test-latticra-q-seal-ml-kem-evidence-import-packet-manifest.sh

require_contains 'latticra_q_seal_ml_kem_evidence_import_packet_manifest_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_evidence_import_packet_manifest.h
require_contains 'latticra-q-seal-ml-kem-evidence-import-packet-manifest/0.1' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'evidence_import_review_gate_bound = 1u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'source_digest_column_required = 1u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'reviewer_role_column_required = 1u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'fixture_digest_packet_rows_imported = 0u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'reviewer_role_packet_rows_imported = 0u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'operation_execution_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'required_evidence_packet_items_total = 41u' latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c
require_contains 'latticra q-seal ml-kem evidence import packet manifest invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_evidence_import_packet_manifest_invariants.c
require_contains 'ml_kem_evidence_import_packet_manifest_present=1' latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
require_contains 'fixture_digest_packet_rows_imported=0' latticra-q-seal/evidence/ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
require_contains 'reviewer_role_packet_rows_imported=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
require_contains 'required_evidence_packet_items_total=41' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md
require_contains 'LATTICRA_Q_SEAL_ML_KEM_EVIDENCE_IMPORT_PACKET_MANIFEST.md' docs/FOUNDATION_INDEX.md
require_contains 'evidence_import_packet_manifest_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_evidence_import_packet_manifest.c \
  latticra-q-seal/tests/q_seal_ml_kem_evidence_import_packet_manifest_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem evidence import packet manifest: ok\n'

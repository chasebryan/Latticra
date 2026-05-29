#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem kat acvp replay transcript gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem kat acvp replay transcript gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_kat_acvp_replay_transcript_gate.h
require_file latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
require_file latticra-q-seal/tests/q_seal_ml_kem_kat_acvp_replay_transcript_gate_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate.sh

require_contains 'latticra_q_seal_ml_kem_kat_acvp_replay_transcript_gate_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_kat_acvp_replay_transcript_gate.h
require_contains 'latticra-q-seal-ml-kem-kat-acvp-replay-transcript-gate/0.1' latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
require_contains 'NIST-FIPS-203,NIST-ACVP-ML-KEM,NIST-SP-800-218-SSDF' latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
require_contains 'acvp_key_check_transcript_lane_recorded = 1u' latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
require_contains 'kat_replay_transcripts_recorded = 0u' latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
require_contains 'required_transcript_items_total = 44u' latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
require_contains 'operation_execution_allowed == 1u' latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c
require_contains 'latticra q-seal ml-kem kat acvp replay transcript gate invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_kat_acvp_replay_transcript_gate_invariants.c
require_contains 'ml_kem_kat_acvp_replay_transcript_gate_present=1' latticra-q-seal/evidence/ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
require_contains 'acvp_key_check_transcript_lane_recorded=1' latticra-q-seal/evidence/ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
require_contains 'kat_replay_transcripts_recorded=0' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md
require_contains 'required_transcript_items_total=44' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_KAT_ACVP_REPLAY_TRANSCRIPT_GATE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem.c \
  latticra-q-seal/src/q_seal_ml_kem_kat_acvp_replay_transcript_gate.c \
  latticra-q-seal/tests/q_seal_ml_kem_kat_acvp_replay_transcript_gate_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem kat acvp replay transcript gate: ok\n'

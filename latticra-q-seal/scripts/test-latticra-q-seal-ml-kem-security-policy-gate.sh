#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-security-policy-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem security policy gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem security policy gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-security-policy-gate"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_security_policy_gate.h
require_file latticra-q-seal/src/q_seal_ml_kem_security_policy_gate.c
require_file latticra-q-seal/tests/q_seal_ml_kem_security_policy_gate_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_SECURITY_POLICY_GATE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_GATE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh
require_file scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh

require_contains 'latticra_q_seal_ml_kem_security_policy_gate_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_security_policy_gate.h
require_contains 'latticra-q-seal-ml-kem-security-policy-gate/0.1' latticra-q-seal/src/q_seal_ml_kem_security_policy_gate.c
require_contains 'NIST-FIPS-140-3,NIST-SP-800-140B-REV-1,NIST-CMVP,NIST-FIPS-203,NIST-SP-800-218-SSDF' latticra-q-seal/src/q_seal_ml_kem_security_policy_gate.c
require_contains 'security_policy_gate_present=1' latticra-q-seal/evidence/ML_KEM_SECURITY_POLICY_GATE.md
require_contains 'sp800_140b_rev1_security_policy_bound=1' latticra-q-seal/evidence/ML_KEM_SECURITY_POLICY_GATE.md
require_contains 'security_policy_evidence_recorded=0' latticra-q-seal/evidence/ML_KEM_SECURITY_POLICY_GATE.md
require_contains 'operation_execution_allowed=0' latticra-q-seal/evidence/ML_KEM_SECURITY_POLICY_GATE.md
require_contains 'required_security_policy_items_total=41' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_GATE.md
require_contains 'required_security_policy_items_satisfied=29' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_GATE.md
require_contains 'latticra q-seal ml-kem security policy gate invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_security_policy_gate_invariants.c
require_contains 'sh ./scripts/test-latticra-q-seal-ml-kem-security-policy-gate.sh' Makefile
require_contains 'LATTICRA_Q_SEAL_ML_KEM_SECURITY_POLICY_GATE.md' docs/FOUNDATION_INDEX.md
require_contains 'security_policy_gate_bound=1' latticra-q-seal/evidence/ML_KEM_MODULE_BOUNDARY_GATE.md
require_contains 'security_policy_gate_bound=1' latticra-q-seal/evidence/ML_KEM_VALIDATION_CLAIM_GATE.md
require_contains 'security_policy_gate_present=1' latticra-q-seal/evidence/Q_SEAL_READINESS.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_security_policy_gate.c \
  latticra-q-seal/tests/q_seal_ml_kem_security_policy_gate_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem security policy gate: ok\n'

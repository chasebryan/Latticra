#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
qseal_root=$(CDPATH= cd -- "$script_dir/.." && pwd)
repo_root=$(CDPATH= cd -- "$qseal_root/.." && pwd)

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$repo_root/$file" ]; then
    printf 'latticra q-seal ml-kem sp800-227 usage profile: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$repo_root/$file"; then
    printf 'latticra q-seal ml-kem sp800-227 usage profile: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

binary="$tmpdir/latticra-q-seal-ml-kem-sp800-227-usage-profile"

require_file latticra-q-seal/include/latticra/q_seal_ml_kem_sp800_227_usage_profile.h
require_file latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_file latticra-q-seal/tests/q_seal_ml_kem_sp800_227_usage_profile_invariants.c
require_file latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_file latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE.md
require_file latticra-q-seal/scripts/test-latticra-q-seal-ml-kem-sp800-227-usage-profile.sh

require_contains 'latticra_q_seal_ml_kem_sp800_227_usage_profile_prepare' latticra-q-seal/include/latticra/q_seal_ml_kem_sp800_227_usage_profile.h
require_contains 'latticra-q-seal-ml-kem-sp800-227-usage-profile/0.1' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'NIST-SP-800-227' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'https://csrc.nist.gov/pubs/sp/800/227/final' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'September-2025' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'application_protocol_binding_required = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'key_confirmation_decision_required = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'kem_use_case_review_recorded = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'application_protocol_binding_recorded = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'key_confirmation_decision_recorded = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'kdf_binding_recorded = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'domain_separation_reviewed = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'shared_secret_lifecycle_reviewed = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'failure_handling_reviewed = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'key_separation_reviewed = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'algorithm_agility_reviewed = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'kem_usage_profile_accepted = 1u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'shared_secret_emission_allowed = 0u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'required_usage_items_total = 30u' latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c
require_contains 'latticra q-seal ml-kem sp800-227 usage profile invariants: ok' latticra-q-seal/tests/q_seal_ml_kem_sp800_227_usage_profile_invariants.c
require_contains 'sp800_227_usage_profile_present=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'sp_800_227_source_url=https://csrc.nist.gov/pubs/sp/800/227/final' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'sp_800_227_publication_date=September-2025' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'kem_use_case_review_recorded=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'application_protocol_binding_recorded=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'key_confirmation_decision_recorded=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'kdf_binding_recorded=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'domain_separation_reviewed=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'shared_secret_lifecycle_reviewed=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'failure_handling_reviewed=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'key_separation_reviewed=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'algorithm_agility_reviewed=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'kem_usage_profile_accepted=1' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'shared_secret_emission_allowed=0' latticra-q-seal/evidence/ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'required_usage_items_total=30' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'required_usage_items_satisfied=30' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE.md
require_contains 'status=ml-kem-sp800-227-usage-profile-accepted-runtime-closed' latticra-q-seal/docs/LATTICRA_Q_SEAL_ML_KEM_SP800_227_USAGE_PROFILE.md

cc $CFLAGS -Ilatticra-q-seal/include \
  latticra-q-seal/src/q_seal_ml_kem_sp800_227_usage_profile.c \
  latticra-q-seal/tests/q_seal_ml_kem_sp800_227_usage_profile_invariants.c \
  -o "$binary"

"$binary"

printf 'latticra q-seal ml-kem sp800-227 usage profile: ok\n'

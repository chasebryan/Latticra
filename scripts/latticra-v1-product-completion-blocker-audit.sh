#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-v1-product-completion-blocker-audit.sh

Reports the current no-effect decomposition of the product-completion blockers
that keep the v1.0.0 release readiness gate closed. The audit reads existing
status records only. It does not create artifacts, accept evidence, run
runtime cryptography, launch models, install packages, or mutate the host.
USAGE
}

fail() {
  printf 'latticra v1 product completion blocker audit: %s\n' "$1" >&2
  exit "${2:-1}"
}

status_value() {
  key="$1"
  file="$2"
  value="$(awk -F= -v key="$key" '$1 == key { print substr($0, length(key) + 2); exit }' "$file")"
  [ -n "$value" ] || fail "missing status value in $file: $key" 65
  printf '%s\n' "$value"
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

PRODUCTION_LEDGER='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
FEDORA_STATUS='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
NADIA_STATUS='docs/status/NADIA_PRODUCTION_READINESS_BLOCKER_STATUS.md'
Q_SEAL_STATUS='latticra-q-seal/evidence/Q_SEAL_READINESS.md'

PRODUCTION_PLATFORM_CLAIM_ALLOWED="$(status_value production_platform_claim_allowed "$PRODUCTION_LEDGER")"
PRODUCTION_INSTALLER_READY="$(status_value production_installer_ready "$PRODUCTION_LEDGER")"
PRODUCTION_AI_CLAIMED="$(status_value production_ai_claimed "$PRODUCTION_LEDGER")"
PRODUCTION_CRYPTOGRAPHY_CLAIMED="$(status_value production_cryptography_claimed "$PRODUCTION_LEDGER")"
PRODUCTION_ENFORCEMENT_CLAIMED="$(status_value production_enforcement_claimed "$PRODUCTION_LEDGER")"

FEDORA_PRODUCTION_READINESS_EVIDENCE_COMPLETE="$(status_value fedora_production_readiness_evidence_complete "$FEDORA_STATUS")"
FEDORA_PRODUCTION_READINESS_PROMOTION_ALLOWED="$(status_value fedora_production_readiness_promotion_allowed "$FEDORA_STATUS")"
FEDORA_MOCK_BUILD_EVIDENCE_PRESENT="$(status_value fedora_mock_build_evidence_present "$FEDORA_STATUS")"
FEDORA_RPMLINT_EVIDENCE_PRESENT="$(status_value fedora_rpmlint_evidence_present "$FEDORA_STATUS")"
FEDORA_DISPOSABLE_VALIDATION_ENVIRONMENT_PROVISIONED="$(status_value disposable_validation_environment_provisioned "$FEDORA_STATUS")"
FEDORA_INSTALL_REMOVE_TRANSCRIPT_PRESENT="$(status_value rpm_install_remove_transcript_present "$FEDORA_STATUS")"
FEDORA_DISTRIBUTION_READY="$(status_value fedora_distribution_ready "$FEDORA_STATUS")"
DAILY_DRIVER_INSTALL_READY="$(status_value daily_driver_install_ready "$FEDORA_STATUS")"
IMMUTABLE_FEDORA_READY="$(status_value immutable_fedora_ready "$FEDORA_STATUS")"

NADIA_SEXUAL_SAFETY_RUNTIME_ENFORCEMENT_VALIDATED="$(status_value sexual_safety_runtime_enforcement_validated "$NADIA_STATUS")"
NADIA_SEXUAL_SAFETY_ADVERSARIAL_EVAL_REVIEWED="$(status_value sexual_safety_adversarial_eval_reviewed "$NADIA_STATUS")"
NADIA_MANIPULATION_RESISTANCE_RED_TEAM_REVIEWED="$(status_value manipulation_resistance_red_team_reviewed "$NADIA_STATUS")"
NADIA_SURVIVOR_SENSITIVE_CONTENT_REVIEWED="$(status_value survivor_sensitive_content_reviewed "$NADIA_STATUS")"
NADIA_OFFLINE_MODEL_ARTIFACT_PRESENT="$(status_value offline_model_artifact_present "$NADIA_STATUS")"
NADIA_OFFLINE_MODEL_INTEGRITY_VERIFIED="$(status_value offline_model_integrity_verified "$NADIA_STATUS")"
NADIA_MODEL_LOAD_RUNTIME_VALIDATED="$(status_value model_load_runtime_validated "$NADIA_STATUS")"
NADIA_INFERENCE_RUNTIME_VALIDATED="$(status_value inference_runtime_validated "$NADIA_STATUS")"
NADIA_RUNTIME_SANDBOX_VALIDATED="$(status_value runtime_sandbox_validated "$NADIA_STATUS")"
NADIA_CONSOLE_INTEROPERABILITY_E2E_VALIDATED="$(status_value console_interoperability_e2e_validated "$NADIA_STATUS")"
NADIA_PANEL_INSTALL_E2E_VALIDATED="$(status_value panel_install_e2e_validated "$NADIA_STATUS")"
NADIA_RELEASE_RECEIPT_SIGNED="$(status_value release_receipt_signed "$NADIA_STATUS")"
NADIA_RELEASE_RECEIPT_REVIEWED="$(status_value release_receipt_reviewed "$NADIA_STATUS")"
PRODUCTION_NADIA_READY="$(status_value production_nadia_ready "$NADIA_STATUS")"
NADIA_PUBLIC_RELEASE_ALLOWED="$(status_value public_release_allowed "$NADIA_STATUS")"

Q_SEAL_RUNTIME_CRYPTO_READY="$(status_value runtime_crypto_ready "$Q_SEAL_STATUS")"
Q_SEAL_OPERATIONS_ENABLED="$(status_value operations_enabled "$Q_SEAL_STATUS")"
Q_SEAL_KEY_GENERATION_ENABLED="$(status_value key_generation_enabled "$Q_SEAL_STATUS")"
Q_SEAL_ENCAPSULATION_ENABLED="$(status_value encapsulation_enabled "$Q_SEAL_STATUS")"
Q_SEAL_DECAPSULATION_ENABLED="$(status_value decapsulation_enabled "$Q_SEAL_STATUS")"
Q_SEAL_SHARED_SECRET_EMITTED="$(status_value shared_secret_emitted "$Q_SEAL_STATUS")"
Q_SEAL_RUNTIME_BLOCKERS_TOTAL="$(status_value runtime_blockers_total "$Q_SEAL_STATUS")"
Q_SEAL_REQUIRED_READINESS_ITEMS_TOTAL="$(status_value required_readiness_items_total "$Q_SEAL_STATUS")"
Q_SEAL_REQUIRED_READINESS_ITEMS_SATISFIED="$(status_value required_readiness_items_satisfied "$Q_SEAL_STATUS")"
Q_SEAL_PRODUCTION_CRYPTO_CLAIM_ALLOWED="$(status_value production_crypto_claim_allowed "$Q_SEAL_STATUS")"
RUNTIME_AUTHORITY_GRANTED="$(status_value runtime_authority_granted "$Q_SEAL_STATUS")"

DETAIL_BLOCKER_COUNT=0
DETAIL_BLOCKERS='none'
add_detail_blocker() {
  blocker="$1"
  if [ "$DETAIL_BLOCKERS" = "none" ]; then
    DETAIL_BLOCKERS="$blocker"
  else
    DETAIL_BLOCKERS="$DETAIL_BLOCKERS,$blocker"
  fi
  DETAIL_BLOCKER_COUNT=$((DETAIL_BLOCKER_COUNT + 1))
}

add_detail_blocker 'current_edge_checkpoint_not_v1'
add_detail_blocker 'v040edge_not_current_release'
[ "$PRODUCTION_PLATFORM_CLAIM_ALLOWED" = "1" ] || add_detail_blocker 'production_platform_claim_closed'
[ "$PRODUCTION_INSTALLER_READY" = "1" ] || add_detail_blocker 'production_installer_not_ready'

[ "$FEDORA_PRODUCTION_READINESS_EVIDENCE_COMPLETE" = "1" ] || add_detail_blocker 'fedora_evidence_matrix_incomplete'
[ "$FEDORA_PRODUCTION_READINESS_PROMOTION_ALLOWED" = "1" ] || add_detail_blocker 'fedora_promotion_not_allowed'
[ "$FEDORA_MOCK_BUILD_EVIDENCE_PRESENT" = "1" ] || add_detail_blocker 'fedora_mock_build_evidence_missing'
[ "$FEDORA_RPMLINT_EVIDENCE_PRESENT" = "1" ] || add_detail_blocker 'fedora_rpmlint_evidence_missing'
[ "$FEDORA_DISPOSABLE_VALIDATION_ENVIRONMENT_PROVISIONED" = "1" ] || add_detail_blocker 'fedora_disposable_validation_environment_missing'
[ "$FEDORA_INSTALL_REMOVE_TRANSCRIPT_PRESENT" = "1" ] || add_detail_blocker 'fedora_install_remove_transcript_missing'
[ "$FEDORA_DISTRIBUTION_READY" = "1" ] || add_detail_blocker 'fedora_distribution_not_ready'
[ "$DAILY_DRIVER_INSTALL_READY" = "1" ] || add_detail_blocker 'daily_driver_install_not_ready'
[ "$IMMUTABLE_FEDORA_READY" = "1" ] || add_detail_blocker 'immutable_fedora_not_ready'

[ "$NADIA_SEXUAL_SAFETY_RUNTIME_ENFORCEMENT_VALIDATED" = "1" ] || add_detail_blocker 'nadia_safety_runtime_not_validated'
[ "$NADIA_SEXUAL_SAFETY_ADVERSARIAL_EVAL_REVIEWED" = "1" ] || add_detail_blocker 'nadia_safety_adversarial_review_missing'
[ "$NADIA_MANIPULATION_RESISTANCE_RED_TEAM_REVIEWED" = "1" ] || add_detail_blocker 'nadia_manipulation_red_team_review_missing'
[ "$NADIA_SURVIVOR_SENSITIVE_CONTENT_REVIEWED" = "1" ] || add_detail_blocker 'nadia_survivor_sensitive_review_missing'
[ "$NADIA_OFFLINE_MODEL_ARTIFACT_PRESENT" = "1" ] || add_detail_blocker 'nadia_offline_model_artifact_missing'
[ "$NADIA_OFFLINE_MODEL_INTEGRITY_VERIFIED" = "1" ] || add_detail_blocker 'nadia_offline_model_integrity_unverified'
[ "$NADIA_MODEL_LOAD_RUNTIME_VALIDATED" = "1" ] || add_detail_blocker 'nadia_model_load_runtime_not_validated'
[ "$NADIA_INFERENCE_RUNTIME_VALIDATED" = "1" ] || add_detail_blocker 'nadia_inference_runtime_not_validated'
[ "$NADIA_RUNTIME_SANDBOX_VALIDATED" = "1" ] || add_detail_blocker 'nadia_runtime_sandbox_not_validated'
[ "$NADIA_CONSOLE_INTEROPERABILITY_E2E_VALIDATED" = "1" ] || add_detail_blocker 'nadia_console_e2e_not_validated'
[ "$NADIA_PANEL_INSTALL_E2E_VALIDATED" = "1" ] || add_detail_blocker 'nadia_panel_install_e2e_not_validated'
[ "$NADIA_RELEASE_RECEIPT_SIGNED" = "1" ] || add_detail_blocker 'nadia_release_receipt_not_signed'
[ "$NADIA_RELEASE_RECEIPT_REVIEWED" = "1" ] || add_detail_blocker 'nadia_release_receipt_not_reviewed'
[ "$PRODUCTION_NADIA_READY" = "1" ] || add_detail_blocker 'production_nadia_not_ready'
[ "$NADIA_PUBLIC_RELEASE_ALLOWED" = "1" ] || add_detail_blocker 'nadia_public_release_not_allowed'

[ "$Q_SEAL_RUNTIME_CRYPTO_READY" = "1" ] || add_detail_blocker 'q_seal_runtime_crypto_blocked'
[ "$Q_SEAL_OPERATIONS_ENABLED" = "1" ] || add_detail_blocker 'q_seal_operations_disabled'
[ "$Q_SEAL_KEY_GENERATION_ENABLED" = "1" ] || add_detail_blocker 'q_seal_key_generation_disabled'
[ "$Q_SEAL_ENCAPSULATION_ENABLED" = "1" ] || add_detail_blocker 'q_seal_encapsulation_disabled'
[ "$Q_SEAL_DECAPSULATION_ENABLED" = "1" ] || add_detail_blocker 'q_seal_decapsulation_disabled'
[ "$Q_SEAL_SHARED_SECRET_EMITTED" = "1" ] || add_detail_blocker 'q_seal_shared_secret_emission_blocked'
[ "$Q_SEAL_RUNTIME_BLOCKERS_TOTAL" = "0" ] || add_detail_blocker 'q_seal_runtime_blockers_open'
[ "$Q_SEAL_REQUIRED_READINESS_ITEMS_SATISFIED" = "$Q_SEAL_REQUIRED_READINESS_ITEMS_TOTAL" ] || add_detail_blocker 'q_seal_readiness_items_incomplete'
[ "$Q_SEAL_PRODUCTION_CRYPTO_CLAIM_ALLOWED" = "1" ] || add_detail_blocker 'q_seal_production_crypto_claim_closed'
[ "$RUNTIME_AUTHORITY_GRANTED" = "1" ] || add_detail_blocker 'runtime_authority_closed'

PASSED=0
if [ "$DETAIL_BLOCKER_COUNT" = "0" ]; then
  PASSED=1
fi

cat <<REPORT
LATTICRA V1 PRODUCT COMPLETION BLOCKER AUDIT
v1_product_completion_blocker_audit_status=ok
v1_product_completion_blocker_audit_present=1
v1_product_completion_blocker_audit_mode=no-effect-product-blocker-decomposition
v1_product_completion_blocker_audit_passed=$PASSED
v1_product_completion_detail_blocker_count=$DETAIL_BLOCKER_COUNT
v1_product_completion_detail_blockers=$DETAIL_BLOCKERS
current_edge_checkpoint=v0.3.0edge
next_main_edge_line=v0.4.0edge
current_edge_checkpoint_ready_for_v1=0
v040edge_current_release=0
production_platform_claim_allowed=$PRODUCTION_PLATFORM_CLAIM_ALLOWED
production_installer_ready=$PRODUCTION_INSTALLER_READY
production_ai_claimed=$PRODUCTION_AI_CLAIMED
production_cryptography_claimed=$PRODUCTION_CRYPTOGRAPHY_CLAIMED
production_enforcement_claimed=$PRODUCTION_ENFORCEMENT_CLAIMED
fedora_production_readiness_evidence_complete=$FEDORA_PRODUCTION_READINESS_EVIDENCE_COMPLETE
fedora_production_readiness_promotion_allowed=$FEDORA_PRODUCTION_READINESS_PROMOTION_ALLOWED
fedora_mock_build_evidence_present=$FEDORA_MOCK_BUILD_EVIDENCE_PRESENT
fedora_rpmlint_evidence_present=$FEDORA_RPMLINT_EVIDENCE_PRESENT
fedora_disposable_validation_environment_provisioned=$FEDORA_DISPOSABLE_VALIDATION_ENVIRONMENT_PROVISIONED
fedora_install_remove_transcript_present=$FEDORA_INSTALL_REMOVE_TRANSCRIPT_PRESENT
fedora_distribution_ready=$FEDORA_DISTRIBUTION_READY
daily_driver_install_ready=$DAILY_DRIVER_INSTALL_READY
immutable_fedora_ready=$IMMUTABLE_FEDORA_READY
nadia_sexual_safety_runtime_enforcement_validated=$NADIA_SEXUAL_SAFETY_RUNTIME_ENFORCEMENT_VALIDATED
nadia_sexual_safety_adversarial_eval_reviewed=$NADIA_SEXUAL_SAFETY_ADVERSARIAL_EVAL_REVIEWED
nadia_manipulation_resistance_red_team_reviewed=$NADIA_MANIPULATION_RESISTANCE_RED_TEAM_REVIEWED
nadia_survivor_sensitive_content_reviewed=$NADIA_SURVIVOR_SENSITIVE_CONTENT_REVIEWED
nadia_offline_model_artifact_present=$NADIA_OFFLINE_MODEL_ARTIFACT_PRESENT
nadia_offline_model_integrity_verified=$NADIA_OFFLINE_MODEL_INTEGRITY_VERIFIED
nadia_model_load_runtime_validated=$NADIA_MODEL_LOAD_RUNTIME_VALIDATED
nadia_inference_runtime_validated=$NADIA_INFERENCE_RUNTIME_VALIDATED
nadia_runtime_sandbox_validated=$NADIA_RUNTIME_SANDBOX_VALIDATED
nadia_console_interoperability_e2e_validated=$NADIA_CONSOLE_INTEROPERABILITY_E2E_VALIDATED
nadia_panel_install_e2e_validated=$NADIA_PANEL_INSTALL_E2E_VALIDATED
nadia_release_receipt_signed=$NADIA_RELEASE_RECEIPT_SIGNED
nadia_release_receipt_reviewed=$NADIA_RELEASE_RECEIPT_REVIEWED
production_nadia_ready=$PRODUCTION_NADIA_READY
nadia_public_release_allowed=$NADIA_PUBLIC_RELEASE_ALLOWED
q_seal_runtime_crypto_ready=$Q_SEAL_RUNTIME_CRYPTO_READY
q_seal_operations_enabled=$Q_SEAL_OPERATIONS_ENABLED
q_seal_key_generation_enabled=$Q_SEAL_KEY_GENERATION_ENABLED
q_seal_encapsulation_enabled=$Q_SEAL_ENCAPSULATION_ENABLED
q_seal_decapsulation_enabled=$Q_SEAL_DECAPSULATION_ENABLED
q_seal_shared_secret_emitted=$Q_SEAL_SHARED_SECRET_EMITTED
q_seal_runtime_blockers_total=$Q_SEAL_RUNTIME_BLOCKERS_TOTAL
q_seal_required_readiness_items_total=$Q_SEAL_REQUIRED_READINESS_ITEMS_TOTAL
q_seal_required_readiness_items_satisfied=$Q_SEAL_REQUIRED_READINESS_ITEMS_SATISFIED
q_seal_production_crypto_claim_allowed=$Q_SEAL_PRODUCTION_CRYPTO_CLAIM_ALLOWED
runtime_authority_granted=$RUNTIME_AUTHORITY_GRANTED

[non_effects]
release_artifact_created=0
evidence_accepted=0
model1_process_launch_performed=0
runtime_crypto_enabled=0
shared_secret_emitted_by_audit=0
production_claim_opened=0
public_release_allowed_by_audit=0
host_mutation_performed=0
REPORT

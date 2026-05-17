#!/usr/bin/env sh
set -eu

doc="docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nucleus task execution implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'nucleus task execution implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement Nucleus task execution.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Implementation files' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Capacity constants' "$doc"
require_contains 'Request kind enum' "$doc"
require_contains 'Effect enum' "$doc"
require_contains 'Policy enum' "$doc"
require_contains 'Denial enum' "$doc"
require_contains 'Gate state enum' "$doc"
require_contains 'Operator confirmation enum' "$doc"
require_contains 'Rollback state enum' "$doc"
require_contains 'Authority summary struct' "$doc"
require_contains 'Task request struct' "$doc"
require_contains 'Task record struct' "$doc"
require_contains 'Task result struct' "$doc"
require_contains 'Classification rules' "$doc"
require_contains 'Prerequisite behavior' "$doc"
require_contains 'Report format' "$doc"
require_contains 'Output buffer behavior' "$doc"
require_contains 'Exact implementation test list' "$doc"
require_contains 'Test file plan' "$doc"
require_contains 'Documentation update plan' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden implementation behavior' "$doc"
require_contains 'Implementation gate' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md \
  docs/NUCLEUS_PREVIEW.md \
  docs/EFFECT_GATES.md \
  docs/STATE_LATTICE.md \
  docs/TRI_PLANE_TRANSITION.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md \
  docs/L_UI_RENDERING_IMPLEMENTATION.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md \
  include/latticra/nucleus_preview.h \
  include/latticra/state_lattice.h \
  include/latticra/tri_plane_transition.h \
  include/latticra/l_ui_renderer.h \
  include/latticra/lir.h \
  include/latticra/lat_parser.h \
  include/latticra/cpp/authority.hpp \
  src/nucleus_preview.c \
  src/l_ui_renderer.c \
  src/lir.c \
  src/lat_parser.c \
  src/cpp/authority.cpp
do
  require_contains "$related" "$doc"
done

for impl_file in \
  include/latticra/nucleus_task.h \
  src/nucleus_task.c \
  tests/nucleus_task_execution_invariants.c \
  scripts/test-nucleus-task-execution.sh \
  .github/workflows/c.yml \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
do
  require_contains "$impl_file" "$doc"
done

for api in \
  latticra_nucleus_task_request_kind_t \
  latticra_nucleus_task_effect_t \
  latticra_nucleus_task_policy_t \
  latticra_nucleus_task_denial_t \
  latticra_nucleus_task_gate_state_t \
  latticra_nucleus_task_operator_confirmation_t \
  latticra_nucleus_task_rollback_state_t \
  latticra_nucleus_task_authority_summary_t \
  latticra_nucleus_task_request_t \
  latticra_nucleus_task_record_t \
  latticra_nucleus_task_result_t \
  latticra_nucleus_task_request_kind_label \
  latticra_nucleus_task_effect_label \
  latticra_nucleus_task_policy_label \
  latticra_nucleus_task_denial_label \
  latticra_nucleus_task_gate_state_label \
  latticra_nucleus_task_operator_confirmation_label \
  latticra_nucleus_task_rollback_state_label \
  latticra_nucleus_task_classify \
  latticra_nucleus_task_report
do
  require_contains "$api" "$doc"
done

for constant in \
  'LATTICRA_NUCLEUS_TASK_ID_MAX 64u' \
  'LATTICRA_NUCLEUS_TASK_LABEL_MAX 64u' \
  'LATTICRA_NUCLEUS_TASK_REASON_MAX 128u' \
  'LATTICRA_NUCLEUS_TASK_SOURCE_IDENTITY_MAX 128u' \
  'LATTICRA_NUCLEUS_TASK_REPORT_MAX 4096u' \
  'LATTICRA_NUCLEUS_TASK_RECORD_MAX 16u'
do
  require_contains "$constant" "$doc"
done

for request in \
  LATTICRA_NUCLEUS_TASK_STATE_REPORT \
  LATTICRA_NUCLEUS_TASK_TRANSITION_PREVIEW \
  LATTICRA_NUCLEUS_TASK_RENDER_REPORT \
  LATTICRA_NUCLEUS_TASK_LAT_VALIDATE \
  LATTICRA_NUCLEUS_TASK_LIR_VALIDATE \
  LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK \
  LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION \
  LATTICRA_NUCLEUS_TASK_SELF_UPDATE \
  LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION \
  LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION \
  LATTICRA_NUCLEUS_TASK_BOOT_ACTION \
  LATTICRA_NUCLEUS_TASK_UNKNOWN \
  state-report \
  transition-preview \
  render-report \
  lat-validate \
  lir-validate \
  authority-check \
  server-interaction \
  self-update \
  recovery-action \
  hardware-action \
  boot-action \
  unknown
do
  require_contains "$request" "$doc"
done

for effect in \
  LATTICRA_NUCLEUS_TASK_EFFECT_NONE \
  LATTICRA_NUCLEUS_TASK_EFFECT_READ \
  LATTICRA_NUCLEUS_TASK_EFFECT_LOCAL_MUTATION \
  LATTICRA_NUCLEUS_TASK_EFFECT_HOST_MUTATION \
  LATTICRA_NUCLEUS_TASK_EFFECT_NETWORK \
  LATTICRA_NUCLEUS_TASK_EFFECT_HARDWARE \
  LATTICRA_NUCLEUS_TASK_EFFECT_BOOT \
  LATTICRA_NUCLEUS_TASK_EFFECT_RECOVERY \
  LATTICRA_NUCLEUS_TASK_EFFECT_EXTERNAL \
  LATTICRA_NUCLEUS_TASK_EFFECT_UNKNOWN \
  none \
  read \
  local_mutation \
  host_mutation \
  network \
  hardware \
  boot \
  recovery \
  external \
  unknown
do
  require_contains "$effect" "$doc"
done

for policy in \
  LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW \
  LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT \
  LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION \
  LATTICRA_NUCLEUS_TASK_POLICY_DENY \
  LATTICRA_NUCLEUS_TASK_POLICY_BLOCKED \
  LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE \
  LATTICRA_NUCLEUS_TASK_POLICY_UNSUPPORTED \
  LATTICRA_NUCLEUS_TASK_POLICY_INTERNAL_ERROR \
  allow-preview \
  allow-report \
  allow-validation \
  deny \
  blocked \
  requires-future-gate \
  unsupported \
  internal-error
do
  require_contains "$policy" "$doc"
done

for denial in \
  LATTICRA_NUCLEUS_TASK_DENIAL_OK \
  LATTICRA_NUCLEUS_TASK_DENIAL_NULL_ARGUMENT \
  LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_REQUEST \
  LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_EFFECT \
  LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_REQUEST \
  LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_EFFECT \
  LATTICRA_NUCLEUS_TASK_DENIAL_PARSER_FAILED \
  LATTICRA_NUCLEUS_TASK_DENIAL_SEMANTIC_FAILED \
  LATTICRA_NUCLEUS_TASK_DENIAL_LIR_FAILED \
  LATTICRA_NUCLEUS_TASK_DENIAL_RENDER_FAILED \
  LATTICRA_NUCLEUS_TASK_DENIAL_AUTHORITY_FAILED \
  LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_BLOCKED \
  LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_REQUIRES_FUTURE_GATE \
  LATTICRA_NUCLEUS_TASK_DENIAL_NON_NO_EFFECT_FLAGS \
  LATTICRA_NUCLEUS_TASK_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED \
  LATTICRA_NUCLEUS_TASK_DENIAL_IMPLEMENTATION_NOT_PRESENT \
  LATTICRA_NUCLEUS_TASK_DENIAL_INTERNAL_ERROR \
  parser-failed \
  semantic-failed \
  lir-failed \
  render-failed \
  authority-failed \
  non-no-effect-flags \
  implementation-not-present
do
  require_contains "$denial" "$doc"
done

for state in \
  LATTICRA_NUCLEUS_TASK_GATE_DISABLED \
  LATTICRA_NUCLEUS_TASK_GATE_BLOCKED \
  LATTICRA_NUCLEUS_TASK_GATE_PLANNED \
  LATTICRA_NUCLEUS_TASK_GATE_AVAILABLE \
  LATTICRA_NUCLEUS_TASK_GATE_ARMED \
  LATTICRA_NUCLEUS_TASK_GATE_EXECUTED \
  LATTICRA_NUCLEUS_TASK_GATE_FAILED \
  disabled \
  blocked \
  planned \
  available \
  armed \
  executed \
  failed
do
  require_contains "$state" "$doc"
done

for confirmation in \
  LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE \
  LATTICRA_NUCLEUS_TASK_OPERATOR_REQUIRED \
  LATTICRA_NUCLEUS_TASK_OPERATOR_PRESENT \
  LATTICRA_NUCLEUS_TASK_OPERATOR_REJECTED \
  LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_SUPPORTED \
  not-applicable \
  required \
  present \
  rejected \
  not-supported \
  'Confirmation must not override policy.'
do
  require_contains "$confirmation" "$doc"
done

for rollback in \
  LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE \
  LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_AVAILABLE \
  LATTICRA_NUCLEUS_TASK_ROLLBACK_REQUIRED \
  LATTICRA_NUCLEUS_TASK_ROLLBACK_READY \
  LATTICRA_NUCLEUS_TASK_ROLLBACK_BLOCKED \
  not-applicable \
  not-available \
  required \
  ready \
  blocked \
  'The first implementation must not perform rollback.'
do
  require_contains "$rollback" "$doc"
done

for field in \
  'char task_id[LATTICRA_NUCLEUS_TASK_ID_MAX];' \
  'latticra_nucleus_task_request_kind_t request_kind;' \
  'latticra_nucleus_task_effect_t requested_effect;' \
  'latticra_nucleus_task_effect_t allowed_effect;' \
  'latticra_nucleus_task_policy_t policy;' \
  'latticra_nucleus_task_denial_t denial;' \
  'latticra_nucleus_task_gate_state_t gate_state;' \
  'latticra_nucleus_task_operator_confirmation_t operator_confirmation;' \
  'latticra_nucleus_task_rollback_state_t rollback_state;' \
  'latticra_nucleus_task_authority_summary_t authority;' \
  'char source_identity[LATTICRA_NUCLEUS_TASK_SOURCE_IDENTITY_MAX];' \
  'latticra_l_ui_source_span_t source_span;' \
  'int executed;' \
  'int mutation_allowed;' \
  'int server_interaction_allowed;' \
  'int recovery_allowed;' \
  'int hardware_allowed;' \
  'unsigned int evidence_level;' \
  'latticra_status_t status;' \
  'size_t record_count;'
do
  require_contains "$field" "$doc"
done

for classification in \
  'state-report + none -> allow-report' \
  'state-report + read -> allow-report' \
  'transition-preview + none -> allow-preview' \
  'transition-preview + read -> allow-preview' \
  'render-report + none -> allow-report' \
  'render-report + read -> allow-report' \
  'lat-validate + none -> allow-validation' \
  'lat-validate + read -> allow-validation' \
  'lir-validate + none -> allow-validation' \
  'lir-validate + read -> allow-validation' \
  'authority-check + none -> allow-validation' \
  'authority-check + read -> allow-validation' \
  'server-interaction -> requires-future-gate' \
  'self-update -> requires-future-gate' \
  'recovery-action -> requires-future-gate' \
  'hardware-action -> requires-future-gate' \
  'boot-action -> requires-future-gate' \
  'unknown -> deny' \
  'unknown effect -> deny' \
  'local_mutation -> deny' \
  'host_mutation -> deny' \
  'network -> deny' \
  'hardware -> deny' \
  'boot -> deny' \
  'recovery -> deny' \
  'external -> deny'
do
  require_contains "$classification" "$doc"
done

for prereq in \
  'missing request -> null-argument' \
  'missing result -> null-argument' \
  'missing authority -> authority-failed' \
  'non-ok authority -> authority-failed' \
  'non-no-effect authority flags -> non-no-effect-flags' \
  'operator confirmation present -> operator-confirmation-not-supported' \
  'render-report requires render_status=ok' \
  'lat-validate requires parser_error=ok' \
  'lir-validate requires lir_error=ok' \
  'transition-preview requires preview policy allow-preview' \
  'state-report requires preview policy allow-preview or allow-report'
do
  require_contains "$prereq" "$doc"
done

for report in \
  'LATTICRA NUCLEUS TASK REPORT' \
  'status=<integer-status>' \
  'task_id=<id>' \
  'request=<request-kind>' \
  'requested_effect=<effect>' \
  'allowed_effect=<effect>' \
  'policy=<policy-result>' \
  'reason=<denial-reason>' \
  'authority_status=<authority-status>' \
  'authority_validator=<authority-validator>' \
  'authority_reason=<authority-reason>' \
  'gate_state=<gate-state>' \
  'operator_confirmation=<confirmation-state>' \
  'executed=0' \
  'mutation_allowed=0' \
  'server_interaction_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0' \
  'rollback_state=<rollback-state>' \
  'evidence_level=<level>' \
  'source_identity=<source>' \
  'span_start_offset=<offset>' \
  'span_end_offset=<offset>'
do
  require_contains "$report" "$doc"
done

for output_rule in \
  'write only to caller-provided buffers' \
  'require explicit buffer length' \
  'NUL-terminate on success' \
  'clear the buffer on too-small failure' \
  'return LATTICRA_STATUS_BUFFER_TOO_SMALL for small buffers' \
  'avoid heap allocation' \
  'avoid file output' \
  'avoid stdout' \
  'avoid stderr' \
  'avoid terminal escape control'
do
  require_contains "$output_rule" "$doc"
done

for test_name in \
  nucleus_task_execution_denies_unknown_request \
  nucleus_task_execution_denies_unknown_effect \
  nucleus_task_execution_preserves_preview_only_boundary \
  nucleus_task_execution_requires_authority_success \
  nucleus_task_execution_requires_effect_gate_success \
  nucleus_task_execution_requires_no_effect_flags \
  nucleus_task_execution_allows_state_report_preview_only \
  nucleus_task_execution_allows_transition_preview_only \
  nucleus_task_execution_allows_render_report_only \
  nucleus_task_execution_allows_lat_validation_only \
  nucleus_task_execution_allows_lir_validation_only \
  nucleus_task_execution_denies_server_interaction \
  nucleus_task_execution_denies_self_update \
  nucleus_task_execution_denies_recovery_action \
  nucleus_task_execution_denies_hardware_action \
  nucleus_task_execution_denies_boot_action \
  nucleus_task_execution_report_is_deterministic \
  nucleus_task_execution_report_rejects_small_buffer \
  nucleus_task_execution_does_not_mutate_state \
  nucleus_task_execution_does_not_open_network \
  nucleus_task_execution_does_not_touch_hardware \
  nucleus_task_execution_does_not_write_files \
  nucleus_task_execution_does_not_call_recovery \
  nucleus_task_execution_does_not_override_policy_with_operator_confirmation
do
  require_contains "$test_name" "$doc"
done

for doc_path in \
  README.md \
  STATUS.md \
  docs/FOUNDATION_INDEX.md \
  docs/status/CURRENT_STATUS.md \
  docs/status/ANNOUNCEMENTS.md \
  docs/project_notes/CURRENT_DIRECTION.md \
  docs/project_notes/UPCOMING_WORK.md \
  docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md \
  docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md \
  scripts/test-project-strategy-status-framework.sh \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
do
  require_contains "$doc_path" "$doc"
done

for compat in \
  'existing Nucleus preview classification behavior' \
  'existing Nucleus preview report behavior' \
  'state lattice behavior' \
  'tri-plane transition behavior' \
  'L-UI parser behavior' \
  'L-UI semantic validation behavior' \
  'LIR shape behavior' \
  'L-UI rendering behavior' \
  'Lat grammar behavior' \
  'constrained C++ authority behavior' \
  'no-effect flags' \
  'current accepted fixture counts'
do
  require_contains "$compat" "$doc"
done

for forbidden in \
  'bypass Nucleus preview classification' \
  'bypass effect gates' \
  'bypass constrained C++ authority validation' \
  'bypass parser, semantic, LIR, or render prerequisites when relevant' \
  'execute unknown requests' \
  'execute unknown effects' \
  'mutate state' \
  'write files' \
  'read host files outside approved metadata' \
  'open network connections' \
  'call server code' \
  'call update code' \
  'call recovery code' \
  'touch hardware' \
  'alter boot state' \
  'perform rollback' \
  'let operator confirmation override policy' \
  'hide denial reasons' \
  'omit task records' \
  'emit secrets, host environment values, credentials, or hardware identifiers' \
  'imply a production runtime, sandbox, malware prevention, ransomware prevention, recovery system, update system, or operating-system surface'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-nucleus-task-execution-implementation-plan.sh' "$doc"
require_contains 'Nucleus task execution code may be added only after this plan is merged.' "$doc"

printf 'nucleus_task_execution_implementation_plan: ok\n'

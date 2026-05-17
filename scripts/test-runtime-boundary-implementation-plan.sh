#!/usr/bin/env sh
set -eu

doc="docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime boundary implementation plan: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'runtime boundary implementation plan: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: implementation planning contract' "$doc"
require_contains 'This document does not implement runtime behavior.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Implementation language decision' "$doc"
require_contains 'Implementation files' "$doc"
require_contains 'Public API shape' "$doc"
require_contains 'Capacity constants' "$doc"
require_contains 'Request kind enum' "$doc"
require_contains 'Effect enum' "$doc"
require_contains 'Runtime mode enum' "$doc"
require_contains 'Policy enum' "$doc"
require_contains 'Denial enum' "$doc"
require_contains 'Gate state enum' "$doc"
require_contains 'Operator confirmation enum' "$doc"
require_contains 'Authority summary struct' "$doc"
require_contains 'Runtime request struct' "$doc"
require_contains 'Runtime record struct' "$doc"
require_contains 'Runtime result struct' "$doc"
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
  docs/RUNTIME_BOUNDARY_CONTRACT.md \
  docs/EFFECT_GATES.md \
  docs/SUPERVISOR_ARCHITECTURE.md \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md \
  docs/NUCLEUS_PREVIEW.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md \
  docs/L_UI_RENDERING_IMPLEMENTATION.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md \
  include/latticra/nucleus_task.h \
  include/latticra/nucleus_preview.h \
  include/latticra/l_ui_renderer.h \
  include/latticra/lir.h \
  include/latticra/lat_parser.h \
  include/latticra/cpp/authority.hpp \
  src/nucleus_task.c \
  src/nucleus_preview.c \
  src/l_ui_renderer.c \
  src/lir.c \
  src/lat_parser.c \
  src/cpp/authority.cpp
do
  require_contains "$related" "$doc"
done

for impl_file in \
  include/latticra/runtime_boundary.h \
  src/runtime_boundary.c \
  tests/runtime_boundary_invariants.c \
  scripts/test-runtime-boundary.sh \
  .github/workflows/c.yml \
  docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
do
  require_contains "$impl_file" "$doc"
done

for api in \
  latticra_runtime_boundary_request_kind_t \
  latticra_runtime_boundary_effect_t \
  latticra_runtime_boundary_mode_t \
  latticra_runtime_boundary_policy_t \
  latticra_runtime_boundary_denial_t \
  latticra_runtime_boundary_gate_state_t \
  latticra_runtime_boundary_operator_confirmation_t \
  latticra_runtime_boundary_authority_summary_t \
  latticra_runtime_boundary_request_t \
  latticra_runtime_boundary_record_t \
  latticra_runtime_boundary_result_t \
  latticra_runtime_boundary_request_kind_label \
  latticra_runtime_boundary_effect_label \
  latticra_runtime_boundary_mode_label \
  latticra_runtime_boundary_policy_label \
  latticra_runtime_boundary_denial_label \
  latticra_runtime_boundary_gate_state_label \
  latticra_runtime_boundary_operator_confirmation_label \
  latticra_runtime_boundary_classify \
  latticra_runtime_boundary_report
do
  require_contains "$api" "$doc"
done

for constant in \
  'LATTICRA_RUNTIME_BOUNDARY_ID_MAX 64u' \
  'LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX 64u' \
  'LATTICRA_RUNTIME_BOUNDARY_REASON_MAX 128u' \
  'LATTICRA_RUNTIME_BOUNDARY_SOURCE_IDENTITY_MAX 128u' \
  'LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX 4096u' \
  'LATTICRA_RUNTIME_BOUNDARY_RECORD_MAX 16u'
do
  require_contains "$constant" "$doc"
done

for request in \
  LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY \
  LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY \
  LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY \
  LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT \
  LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT \
  LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE \
  LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE \
  LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK \
  LATTICRA_RUNTIME_BOUNDARY_RUNTIME_EXECUTE \
  LATTICRA_RUNTIME_BOUNDARY_COMMAND_EXECUTE \
  LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE \
  LATTICRA_RUNTIME_BOUNDARY_LIR_EXECUTE \
  LATTICRA_RUNTIME_BOUNDARY_FILE_READ \
  LATTICRA_RUNTIME_BOUNDARY_FILE_WRITE \
  LATTICRA_RUNTIME_BOUNDARY_NETWORK_OPEN \
  LATTICRA_RUNTIME_BOUNDARY_SERVER_INTERACTION \
  LATTICRA_RUNTIME_BOUNDARY_SELF_UPDATE \
  LATTICRA_RUNTIME_BOUNDARY_RECOVERY_ACTION \
  LATTICRA_RUNTIME_BOUNDARY_ROLLBACK_ACTION \
  LATTICRA_RUNTIME_BOUNDARY_HARDWARE_ACTION \
  LATTICRA_RUNTIME_BOUNDARY_BOOT_ACTION \
  LATTICRA_RUNTIME_BOUNDARY_UNKNOWN \
  parse-only \
  validate-only \
  classify-only \
  render-report \
  nucleus-task-report \
  lat-validate \
  lir-validate \
  authority-check \
  runtime-execute \
  command-execute \
  lat-execute \
  lir-execute \
  file-read \
  file-write \
  network-open \
  server-interaction \
  self-update \
  recovery-action \
  rollback-action \
  hardware-action \
  boot-action \
  unknown
do
  require_contains "$request" "$doc"
done

for effect in \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_LOCAL_MUTATION \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_HOST_MUTATION \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_NETWORK \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_HARDWARE \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_BOOT \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_RECOVERY \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_EXTERNAL \
  LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN \
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

for mode in \
  LATTICRA_RUNTIME_BOUNDARY_MODE_DISABLED \
  LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY \
  LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY \
  LATTICRA_RUNTIME_BOUNDARY_MODE_PREVIEW_ONLY \
  LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY \
  LATTICRA_RUNTIME_BOUNDARY_MODE_DENY_ALL \
  LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE \
  disabled \
  report-only \
  validation-only \
  preview-only \
  classification-only \
  deny-all \
  requires-future-gate
do
  require_contains "$mode" "$doc"
done

for policy in \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_PREVIEW \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_BLOCKED \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_UNSUPPORTED \
  LATTICRA_RUNTIME_BOUNDARY_POLICY_INTERNAL_ERROR \
  allow-report \
  allow-validation \
  allow-classification \
  allow-preview \
  deny \
  blocked \
  requires-future-gate \
  unsupported \
  internal-error
do
  require_contains "$policy" "$doc"
done

for denial in \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNSUPPORTED_REQUEST \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNSUPPORTED_EFFECT \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_SEMANTIC_FAILED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_BLOCKED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_IMPLEMENTATION_NOT_PRESENT \
  LATTICRA_RUNTIME_BOUNDARY_DENIAL_INTERNAL_ERROR \
  parser-failed \
  semantic-failed \
  lir-failed \
  render-failed \
  authority-failed \
  task-failed \
  runtime-disabled \
  implementation-not-present
do
  require_contains "$denial" "$doc"
done

for field in \
  'char runtime_id[LATTICRA_RUNTIME_BOUNDARY_ID_MAX];' \
  'latticra_runtime_boundary_request_kind_t request_kind;' \
  'latticra_runtime_boundary_effect_t requested_effect;' \
  'latticra_runtime_boundary_effect_t allowed_effect;' \
  'latticra_runtime_boundary_mode_t mode;' \
  'latticra_runtime_boundary_policy_t policy;' \
  'latticra_runtime_boundary_denial_t denial;' \
  'latticra_runtime_boundary_gate_state_t gate_state;' \
  'latticra_runtime_boundary_operator_confirmation_t operator_confirmation;' \
  'latticra_runtime_boundary_authority_summary_t authority;' \
  'latticra_nucleus_task_policy_t task_policy;' \
  'latticra_nucleus_task_denial_t task_reason;' \
  'char source_identity[LATTICRA_RUNTIME_BOUNDARY_SOURCE_IDENTITY_MAX];' \
  'latticra_l_ui_source_span_t source_span;' \
  'int executed;' \
  'int mutation_allowed;' \
  'int file_io_allowed;' \
  'int network_allowed;' \
  'int server_interaction_allowed;' \
  'int recovery_allowed;' \
  'int rollback_allowed;' \
  'int hardware_allowed;' \
  'int boot_allowed;' \
  'unsigned int evidence_level;'
do
  require_contains "$field" "$doc"
done

for classification in \
  'parse-only + none -> allow-report' \
  'parse-only + read -> allow-report' \
  'validate-only + none -> allow-validation' \
  'validate-only + read -> allow-validation' \
  'classify-only + none -> allow-classification' \
  'classify-only + read -> allow-classification' \
  'render-report + none -> allow-report' \
  'render-report + read -> allow-report' \
  'nucleus-task-report + none -> allow-report' \
  'nucleus-task-report + read -> allow-report' \
  'lat-validate + none -> allow-validation' \
  'lat-validate + read -> allow-validation' \
  'lir-validate + none -> allow-validation' \
  'lir-validate + read -> allow-validation' \
  'authority-check + none -> allow-validation' \
  'authority-check + read -> allow-validation' \
  'runtime-execute -> requires-future-gate' \
  'command-execute -> requires-future-gate' \
  'lat-execute -> requires-future-gate' \
  'lir-execute -> requires-future-gate' \
  'file-read -> requires-future-gate' \
  'file-write -> requires-future-gate' \
  'network-open -> requires-future-gate' \
  'server-interaction -> requires-future-gate' \
  'self-update -> requires-future-gate' \
  'recovery-action -> requires-future-gate' \
  'rollback-action -> requires-future-gate' \
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
  'runtime mode disabled -> runtime-disabled unless request is report-only metadata' \
  'render-report requires render_status=ok' \
  'nucleus-task-report requires task policy allow-report or allow-validation or allow-classification or allow-preview' \
  'lat-validate requires parser_error=ok' \
  'lir-validate requires lir_error=ok' \
  'runtime-execute requires future gate' \
  'command-execute requires future gate' \
  'lat-execute requires future gate' \
  'lir-execute requires future gate' \
  'file-read requires future gate' \
  'file-write requires future gate' \
  'network-open requires future gate' \
  'server-interaction requires future gate' \
  'self-update requires future gate' \
  'recovery-action requires future gate' \
  'rollback-action requires future gate' \
  'hardware-action requires future gate' \
  'boot-action requires future gate'
do
  require_contains "$prereq" "$doc"
done

for report in \
  'LATTICRA RUNTIME BOUNDARY REPORT' \
  'status=<integer-status>' \
  'runtime_id=<id>' \
  'request=<request-kind>' \
  'requested_effect=<effect>' \
  'allowed_effect=<effect>' \
  'mode=<runtime-mode>' \
  'policy=<policy-result>' \
  'reason=<denial-reason>' \
  'authority_status=<authority-status>' \
  'authority_validator=<authority-validator>' \
  'authority_reason=<authority-reason>' \
  'task_policy=<task-policy>' \
  'task_reason=<task-reason>' \
  'effect_gate_state=<gate-state>' \
  'operator_confirmation=<confirmation-state>' \
  'executed=0' \
  'mutation_allowed=0' \
  'file_io_allowed=0' \
  'network_allowed=0' \
  'server_interaction_allowed=0' \
  'recovery_allowed=0' \
  'rollback_allowed=0' \
  'hardware_allowed=0' \
  'boot_allowed=0' \
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
  runtime_boundary_denies_unknown_request \
  runtime_boundary_denies_unknown_effect \
  runtime_boundary_denies_runtime_execute \
  runtime_boundary_denies_command_execute \
  runtime_boundary_denies_lat_execute \
  runtime_boundary_denies_lir_execute \
  runtime_boundary_denies_file_read \
  runtime_boundary_denies_file_write \
  runtime_boundary_denies_network_open \
  runtime_boundary_denies_server_interaction \
  runtime_boundary_denies_self_update \
  runtime_boundary_denies_recovery_action \
  runtime_boundary_denies_rollback_action \
  runtime_boundary_denies_hardware_action \
  runtime_boundary_denies_boot_action \
  runtime_boundary_requires_authority_success \
  runtime_boundary_requires_task_success \
  runtime_boundary_requires_no_effect_flags \
  runtime_boundary_allows_parse_only_report_only \
  runtime_boundary_allows_validate_only \
  runtime_boundary_allows_classify_only \
  runtime_boundary_allows_render_report_only \
  runtime_boundary_report_is_deterministic \
  runtime_boundary_report_rejects_small_buffer \
  runtime_boundary_does_not_mutate_state \
  runtime_boundary_does_not_write_files \
  runtime_boundary_does_not_open_network \
  runtime_boundary_does_not_touch_hardware \
  runtime_boundary_does_not_call_recovery \
  runtime_boundary_does_not_override_policy_with_operator_confirmation
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
  docs/RUNTIME_BOUNDARY_CONTRACT.md \
  scripts/test-project-strategy-status-framework.sh \
  docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
do
  require_contains "$doc_path" "$doc"
done

for compat in \
  'existing Nucleus preview classification behavior' \
  'existing Nucleus task classification behavior' \
  'existing Nucleus task report behavior' \
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
  'bypass Nucleus task classification' \
  'bypass effect gates' \
  'bypass constrained C++ authority validation' \
  'bypass parser, semantic, LIR, render, or task prerequisites when relevant' \
  'execute unknown requests' \
  'execute unknown effects' \
  'execute commands' \
  'execute Lat' \
  'execute LIR' \
  'launch processes' \
  'load plugins' \
  'mutate state' \
  'write files' \
  'read host files outside approved metadata' \
  'open network connections' \
  'call server code' \
  'call update code' \
  'call recovery code' \
  'perform rollback' \
  'touch hardware' \
  'alter boot state' \
  'use terminal control' \
  'let operator confirmation override policy' \
  'hide denial reasons' \
  'omit runtime records' \
  'emit secrets, host environment values, credentials, tokens, keys, hardware identifiers, or process information' \
  'imply a production runtime, sandbox, malware prevention, ransomware prevention, recovery system, update system, or operating-system surface'
do
  require_contains "$forbidden" "$doc"
done

require_contains 'sh scripts/test-runtime-boundary-implementation-plan.sh' "$doc"
require_contains 'Runtime boundary code may be added only after this plan is merged.' "$doc"

printf 'runtime_boundary_implementation_plan: ok\n'

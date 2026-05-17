#!/usr/bin/env sh
set -eu

doc="docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nucleus task execution contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'nucleus task execution contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: Nucleus task execution contract' "$doc"
require_contains 'This document does not implement Nucleus task execution.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Direction checkpoint' "$doc"
require_contains 'Current Nucleus boundary' "$doc"
require_contains 'First task execution posture' "$doc"
require_contains 'Task request kinds' "$doc"
require_contains 'Task effects' "$doc"
require_contains 'Task policy results' "$doc"
require_contains 'Task denial reasons' "$doc"
require_contains 'Required prerequisites' "$doc"
require_contains 'Required authority checks' "$doc"
require_contains 'Required effect-gate checks' "$doc"
require_contains 'Task record shape' "$doc"
require_contains 'Task report format' "$doc"
require_contains 'First implementation gate' "$doc"
require_contains 'Future file policy' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/NUCLEUS_PREVIEW.md \
  docs/EFFECT_GATES.md \
  docs/STATE_LATTICE.md \
  docs/TRI_PLANE_TRANSITION.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION_PLAN.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md \
  docs/L_UI_RENDERING_CONTRACT.md \
  docs/L_UI_RENDERING_IMPLEMENTATION_PLAN.md \
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

for direction in \
  'C is the metal.' \
  'C++ is the disciplined structure.' \
  'Latticra is the contract.' \
  'Lat / Latticra Language: declares contract and intended effects' \
  'LIR: carries validated metadata' \
  'C++ authority layer: validates authority and reports decisions' \
  'C substrate: owns bounded execution-adjacent records and ABI-compatible surfaces' \
  'Nucleus: coordinates only after contracts and gates permit it'
do
  require_contains "$direction" "$doc"
done

for request in \
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

for posture in \
  'task execution implemented? no' \
  'default policy: deny' \
  'preview allowed: yes' \
  'mutation allowed: no' \
  'network allowed: no' \
  'hardware allowed: no' \
  'boot allowed: no' \
  'recovery allowed: no' \
  'server interaction allowed: no' \
  'self-update allowed: no' \
  'operator confirmation allowed to override: no'
do
  require_contains "$posture" "$doc"
done

for policy in \
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

for reason in \
  ok \
  null-argument \
  unknown-request \
  unknown-effect \
  unsupported-request \
  unsupported-effect \
  parser-failed \
  semantic-failed \
  lir-failed \
  authority-failed \
  effect-blocked \
  effect-requires-future-gate \
  non-no-effect-flags \
  operator-confirmation-not-supported \
  implementation-not-present \
  internal-error
do
  require_contains "$reason" "$doc"
done

for prereq in \
  'parser_error=ok' \
  'semantic_error=ok' \
  'lir_error=ok' \
  'authority_status=ok' \
  'render_status=ok' \
  'preview_policy=allow-preview or allow-report or allow-validation' \
  'effect_gate=allowed-preview or allowed-report or allowed-validation' \
  'no_effect=1' \
  'execution_allowed=0' \
  'mutation_allowed=0' \
  'server_allowed=0' \
  'recovery_allowed=0' \
  'hardware_allowed=0' \
  'operator_confirmation=not-applicable'
do
  require_contains "$prereq" "$doc"
done

for authority in \
  'authority status' \
  'authority validator' \
  'authority requested effect' \
  'authority denial reason' \
  'authority no-effect flags' \
  'source identity' \
  'request kind' \
  'effect kind' \
  'boundary kind' \
  'Authority failure must deny the task.' \
  'Authority success must not by itself execute a task.'
do
  require_contains "$authority" "$doc"
done

for gate in \
  'requested effect' \
  'allowed effect' \
  'gate state' \
  'policy result' \
  reason \
  'rollback state' \
  disabled \
  blocked \
  planned \
  armed \
  executed \
  failed
do
  require_contains "$gate" "$doc"
done

for record in \
  task_id \
  request_kind \
  requested_effect \
  allowed_effect \
  policy_result \
  policy_reason \
  authority_status \
  authority_validator \
  authority_reason \
  gate_state \
  operator_confirmation \
  executed \
  mutation_allowed \
  server_interaction_allowed \
  recovery_allowed \
  hardware_allowed \
  rollback_state \
  evidence_level \
  source_identity \
  source_span
do
  require_contains "$record" "$doc"
done

for report in \
  'LATTICRA NUCLEUS TASK REPORT' \
  'task_id=<id>' \
  'request=<request-kind>' \
  'requested_effect=<effect>' \
  'allowed_effect=<effect>' \
  'policy=<policy-result>' \
  'reason=<policy-reason>' \
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

for gate_item in \
  'implementation language' \
  'public header path' \
  'source file path' \
  'task request struct' \
  'task result struct' \
  'task record struct' \
  'task policy enum' \
  'task denial enum' \
  'effect-gate enum usage' \
  'authority summary usage' \
  'operator-confirmation metadata shape' \
  'rollback metadata shape' \
  'report format' \
  'capacity constants' \
  'output-buffer behavior' \
  'exact tests' \
  'compatibility expectations' \
  'non-claims'
do
  require_contains "$gate_item" "$doc"
done

for path in \
  include/latticra/nucleus_task.h \
  src/nucleus_task.c \
  tests/nucleus_task_execution_invariants.c \
  scripts/test-nucleus-task-execution.sh \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
do
  require_contains "$path" "$doc"
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
  'mutate state without a separate mutation contract' \
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

require_contains 'NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md' "$doc"
require_contains 'sh scripts/test-nucleus-task-execution-contract.sh' "$doc"

printf 'nucleus_task_execution_contract: ok\n'

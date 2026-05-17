#!/usr/bin/env sh
set -eu

doc="docs/RUNTIME_BOUNDARY_CONTRACT.md"

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'runtime boundary contract: missing required pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

if [ ! -f "$doc" ]; then
  printf 'runtime boundary contract: missing doc: %s\n' "$doc" >&2
  exit 1
fi

require_contains 'Status: Runtime boundary contract' "$doc"
require_contains 'This document does not implement a runtime.' "$doc"
require_contains 'Relationship to previous work' "$doc"
require_contains 'Direction checkpoint' "$doc"
require_contains 'Current runtime boundary' "$doc"
require_contains 'Runtime posture' "$doc"
require_contains 'Runtime boundary modes' "$doc"
require_contains 'Runtime request kinds' "$doc"
require_contains 'Runtime effects' "$doc"
require_contains 'Runtime policy results' "$doc"
require_contains 'Runtime denial reasons' "$doc"
require_contains 'Required prerequisites' "$doc"
require_contains 'Authority requirements' "$doc"
require_contains 'Task requirements' "$doc"
require_contains 'Runtime record shape' "$doc"
require_contains 'Runtime report format' "$doc"
require_contains 'Output buffer policy' "$doc"
require_contains 'First implementation gate' "$doc"
require_contains 'Future file policy' "$doc"
require_contains 'Future test list' "$doc"
require_contains 'Compatibility expectations' "$doc"
require_contains 'Forbidden behavior' "$doc"
require_contains 'Non-claims' "$doc"

for related in \
  docs/EFFECT_GATES.md \
  docs/SUPERVISOR_ARCHITECTURE.md \
  docs/NUCLEUS_PREVIEW.md \
  docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md \
  docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md \
  docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md \
  docs/L_UI_RENDERING_IMPLEMENTATION.md \
  docs/LIR_SHAPE_IMPLEMENTATION.md \
  docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md \
  docs/STATE_LATTICE.md \
  docs/TRI_PLANE_TRANSITION.md \
  include/latticra/nucleus_preview.h \
  include/latticra/nucleus_task.h \
  include/latticra/l_ui_renderer.h \
  include/latticra/lir.h \
  include/latticra/lat_parser.h \
  include/latticra/cpp/authority.hpp \
  src/nucleus_preview.c \
  src/nucleus_task.c \
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
  'Lat / Latticra Language: declares contracts and intended effects' \
  'LIR: carries validated metadata' \
  'C++ authority layer: validates authority and reports decisions' \
  'C substrate: owns bounded runtime-adjacent records and ABI-compatible surfaces' \
  'Nucleus: coordinates only after contracts and gates permit it' \
  'Runtime: remains disabled until explicit boundaries, authority, tests, and evidence exist'
do
  require_contains "$direction" "$doc"
done

for current in \
  parsing \
  validation \
  classification \
  preview \
  reporting \
  'rendering metadata' \
  'no-effect task classification'
do
  require_contains "$current" "$doc"
done

for posture in \
  'runtime implemented? no' \
  'default policy: deny' \
  'report-only allowed: yes' \
  'validation-only allowed: yes' \
  'preview-only allowed: yes' \
  'classification-only allowed: yes' \
  'command execution allowed: no' \
  'Lat execution allowed: no' \
  'LIR execution allowed: no' \
  'mutation allowed: no' \
  'file I/O allowed: no' \
  'network I/O allowed: no' \
  'server interaction allowed: no' \
  'self-update allowed: no' \
  'recovery allowed: no' \
  'rollback allowed: no' \
  'hardware allowed: no' \
  'boot behavior allowed: no' \
  'operator confirmation allowed to override: no'
do
  require_contains "$posture" "$doc"
done

for mode in \
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

for request in \
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
  render-failed \
  authority-failed \
  task-failed \
  runtime-disabled \
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
  'render_status=ok' \
  'authority_status=ok' \
  'task_policy=allow-report or allow-validation or allow-classification or allow-preview' \
  'runtime_mode=report-only or validation-only or classification-only or preview-only' \
  'effect_gate=allowed-report or allowed-validation or allowed-classification or allowed-preview' \
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
  'runtime request kind' \
  'runtime effect kind' \
  'runtime boundary mode' \
  'Authority failure must deny the request.' \
  'Authority success must not by itself execute a request.'
do
  require_contains "$authority" "$doc"
done

for task in \
  'task policy' \
  'task denial reason' \
  'task requested effect' \
  'task allowed effect' \
  'task executed flag' \
  'task mutation_allowed flag' \
  'task server_interaction_allowed flag' \
  'task recovery_allowed flag' \
  'task hardware_allowed flag'
do
  require_contains "$task" "$doc"
done

for record in \
  runtime_id \
  request_kind \
  requested_effect \
  allowed_effect \
  runtime_mode \
  policy_result \
  denial_reason \
  authority_status \
  task_policy \
  task_reason \
  effect_gate_state \
  operator_confirmation \
  executed \
  mutation_allowed \
  file_io_allowed \
  network_allowed \
  server_interaction_allowed \
  recovery_allowed \
  rollback_allowed \
  hardware_allowed \
  boot_allowed \
  evidence_level \
  source_identity \
  source_span
do
  require_contains "$record" "$doc"
done

for report in \
  'LATTICRA RUNTIME BOUNDARY REPORT' \
  'runtime_id=<id>' \
  'request=<request-kind>' \
  'requested_effect=<effect>' \
  'allowed_effect=<effect>' \
  'mode=<runtime-mode>' \
  'policy=<policy-result>' \
  'reason=<denial-reason>' \
  'authority_status=<authority-status>' \
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
  'avoid heap allocation' \
  'avoid file output' \
  'avoid stdout' \
  'avoid stderr' \
  'avoid terminal escape control'
do
  require_contains "$output_rule" "$doc"
done

for gate_item in \
  'implementation language' \
  'public header path' \
  'source file path' \
  'runtime request struct' \
  'runtime record struct' \
  'runtime result struct' \
  'runtime mode enum' \
  'runtime policy enum' \
  'runtime denial enum' \
  'authority summary usage' \
  'Nucleus task result usage' \
  'effect-gate state usage' \
  'operator-confirmation metadata shape' \
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
  include/latticra/runtime_boundary.h \
  src/runtime_boundary.c \
  tests/runtime_boundary_invariants.c \
  scripts/test-runtime-boundary.sh \
  docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md \
  docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
do
  require_contains "$path" "$doc"
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

require_contains 'RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md' "$doc"
require_contains 'sh scripts/test-runtime-boundary-contract.sh' "$doc"

printf 'runtime_boundary_contract: ok\n'

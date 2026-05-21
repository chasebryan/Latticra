#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload transcript capture docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload transcript capture docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_TRANSCRIPT_CAPTURE.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md'

require_file "$doc"
require_file "$status"

require_contains 'Status: manual evidence-capture preparation' "$doc"
require_contains 'Evidence level: capture preparation only' "$doc"
require_contains 'This page does not run the validation lane.' "$doc"
require_contains 'This page does not create completed evidence.' "$doc"
require_contains 'This page does not claim that a disposable Fedora VM run has succeeded.' "$doc"
require_contains 'This page does not claim host install readiness for the CLI payload.' "$doc"
require_contains 'disposable_vm_cli_validation_transcript_present=0' "$doc"
require_contains 'disposable_vm_cli_validation_completed=0' "$doc"
require_contains 'host_install_ready_for_cli_payload=0' "$doc"
require_contains 'reviewed_disposable_fedora_vm_target=1' "$doc"
require_contains 'reviewed_clean_snapshot_evidence=1' "$doc"
require_contains 'reviewed_recovery_path_evidence=1' "$doc"
require_contains 'reviewed_operator_consent=1' "$doc"
require_contains 'reviewed_runner_success_marker=1' "$doc"
require_contains 'reviewed_cli_payload_present=1' "$doc"
require_contains 'reviewed_readme_payload_present=1' "$doc"
require_contains 'reviewed_non_claims_preserved=1' "$doc"
require_contains 'CI must not run the manual validation runner.' "$doc"
require_contains 'Run the real disposable Fedora VM CLI payload validation lane and commit reviewed transcript evidence' "$doc"
require_contains 'not completed VM evidence' "$doc"
require_contains 'not host install readiness for the CLI payload' "$doc"
require_contains 'not production readiness' "$doc"
require_contains 'not Fedora approval' "$doc"
require_contains 'not a production installer claim' "$doc"

require_contains 'fedora_vm_cli_payload_validation_status=blocked-pending-real-vm-run' "$status"
require_contains 'disposable_vm_cli_validation_transcript_present=0' "$status"
require_contains 'host_install_ready_for_cli_payload=0' "$status"

printf 'fedora_vm_cli_payload_transcript_capture_docs: ok\n'

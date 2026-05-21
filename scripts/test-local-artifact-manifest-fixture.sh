#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'local artifact manifest fixture: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'local artifact manifest fixture: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

fixture='fixtures/artifact/local-artifact-manifest.txt'
contract='docs/LOCAL_INSTALLER_ARTIFACT_MANIFEST_CONTRACT.md'

require_file "$fixture"
require_file "$contract"

require_contains 'LATTICRA LOCAL ARTIFACT MANIFEST' "$fixture"
require_contains 'manifest_version=1' "$fixture"
require_contains 'fixture_name=latticra-local-artifact-manifest-fixture' "$fixture"
require_contains 'fixture_only=1' "$fixture"
require_contains 'artifact_name=latticra-local-no-effect-cli-rpm' "$fixture"
require_contains 'artifact_version=0.0.0' "$fixture"
require_contains 'artifact_arch=noarch' "$fixture"
require_contains 'artifact_format=rpm' "$fixture"
require_contains 'artifact_filename=latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$fixture"
require_contains 'artifact_sha256=fixture-placeholder-not-release-checksum' "$fixture"
require_contains 'artifact_signature=none' "$fixture"
require_contains 'artifact_sbom_path=none' "$fixture"
require_contains 'source_repository=Bryforge/Latticra' "$fixture"
require_contains 'build_command_recorded=1' "$fixture"
require_contains 'build_reproducible=0' "$fixture"
require_contains 'supported_target_family=fedora-disposable-vm' "$fixture"
require_contains 'unsupported_targets_declared=1' "$fixture"
require_contains 'requires_operator_consent=1' "$fixture"
require_contains 'payload_listing_recorded=1' "$fixture"
require_contains 'payload_entry=/usr/bin/latticra' "$fixture"
require_contains 'payload_entry=/usr/share/doc/latticra/README.md' "$fixture"
require_contains 'host_install_ready_for_cli_payload=1' "$fixture"
require_contains 'artifact_manifest_fixture_present=1' "$fixture"
require_contains 'artifact_manifest_validated=1' "$fixture"
require_contains 'artifact_checksum_recorded=0' "$fixture"
require_contains 'artifact_signature_recorded=0' "$fixture"
require_contains 'artifact_sbom_recorded=0' "$fixture"
require_contains 'production_installer_ready=0' "$fixture"
require_contains 'fedora_distribution_ready=0' "$fixture"
require_contains 'fedora_approval_claimed=0' "$fixture"
require_contains 'daily_driver_install_ready=0' "$fixture"
require_contains 'immutable_fedora_ready=0' "$fixture"
require_contains 'not_os_replacement_claim=1' "$fixture"

require_contains 'Add installer artifact manifest fixture' "$contract"

printf 'local_artifact_manifest_fixture: ok\n'

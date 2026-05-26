#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian/freebsd/openbsd package build environment contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian/freebsd/openbsd package build environment contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf 'debian/freebsd/openbsd package build environment contract: unexpected file exists: %s\n' "$file" >&2
    exit 1
  fi
}

contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md'

require_file "$contract"
require_file "$gate_contract"
require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_INPUT_HANDOFF_LANE.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/DEBIAN_FREEBSD_OPENBSD_SOURCE_ARCHIVE_CONTRACT.md
require_file docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/README.md
require_file docs/status/README.md
require_file packaging/debian/README.md
require_file packaging/debian/debian/control
require_file packaging/debian/debian/changelog
require_file packaging/debian/debian/copyright
require_file packaging/debian/debian/rules
require_file packaging/debian/debian/install
require_file packaging/debian/debian/source/format
require_file packaging/freebsd/README.md
require_file packaging/freebsd/Makefile
require_file packaging/freebsd/pkg-descr
require_file packaging/freebsd/pkg-plist
require_file packaging/openbsd/README.md
require_file packaging/openbsd/Makefile
require_file packaging/openbsd/pkg/DESCR
require_file packaging/openbsd/pkg/PLIST
require_file README.md
require_file .github/workflows/debian-freebsd-openbsd-package-build-environment-contract.yml

require_contains 'Status: active package-build environment contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'debian_freebsd_openbsd_package_build_environment_contract_present=1' "$contract"
require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract_present=1' "$contract"
require_contains 'package_build_environment_contract_state=specified-no-effect' "$contract"
require_contains 'artifact_naming_contract_state=specified-no-effect' "$contract"
require_contains 'package_build_gate_state=closed-no-effect' "$contract"
require_contains 'debian_clean_build_environment_documented=1' "$contract"
require_contains 'freebsd_ports_environment_documented=1' "$contract"
require_contains 'openbsd_ports_environment_documented=1' "$contract"
require_contains 'debian_build_environment_provisioned=0' "$contract"
require_contains 'freebsd_build_environment_provisioned=0' "$contract"
require_contains 'openbsd_build_environment_provisioned=0' "$contract"
require_contains 'explicit_operator_build_authorization=0' "$contract"
require_contains 'disposable_validation_environment_required=1' "$contract"
require_contains 'disposable_validation_environment_provisioned=0' "$contract"
require_contains 'environment_transcript_present=0' "$contract"
require_contains 'toolchain_version_capture_required=1' "$contract"
require_contains 'package_input_digest_binding_required=1' "$contract"
require_contains 'package_build_command_allowed=0' "$contract"
require_contains 'package_artifact_created=0' "$contract"
require_contains 'install_on_host_run=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'debian_clean_chroot_or_container_required=1' "$contract"
require_contains 'debian_build_host_identity_required=1' "$contract"
require_contains 'debian_suite_record_required=1' "$contract"
require_contains 'debian_architecture_record_required=1' "$contract"
require_contains 'debian_build_dependency_resolution_transcript_required=1' "$contract"
require_contains 'debian_toolchain_versions_required=1' "$contract"
require_contains 'debian_source_archive_digest_required=1' "$contract"
require_contains 'debian_package_input_path_required=1' "$contract"
require_contains 'dpkg_buildpackage_run=0' "$contract"
require_contains 'debuild_run=0' "$contract"
require_contains 'lintian_run=0' "$contract"

require_contains 'freebsd_jail_or_vm_required=1' "$contract"
require_contains 'freebsd_version_record_required=1' "$contract"
require_contains 'freebsd_architecture_record_required=1' "$contract"
require_contains 'freebsd_ports_tree_revision_required=1' "$contract"
require_contains 'freebsd_distfile_digest_required=1' "$contract"
require_contains 'freebsd_port_origin_required=1' "$contract"
require_contains 'freebsd_toolchain_versions_required=1' "$contract"
require_contains 'freebsd_distinfo_review_required=1' "$contract"
require_contains 'freebsd_make_makesum_run=0' "$contract"
require_contains 'freebsd_make_stage_run=0' "$contract"
require_contains 'freebsd_make_package_run=0' "$contract"
require_contains 'portlint_run=0' "$contract"
require_contains 'poudriere_run=0' "$contract"

require_contains 'openbsd_vm_or_disposable_host_required=1' "$contract"
require_contains 'openbsd_version_record_required=1' "$contract"
require_contains 'openbsd_architecture_record_required=1' "$contract"
require_contains 'openbsd_ports_tree_revision_required=1' "$contract"
require_contains 'openbsd_distfile_digest_required=1' "$contract"
require_contains 'openbsd_port_origin_required=1' "$contract"
require_contains 'openbsd_toolchain_versions_required=1' "$contract"
require_contains 'openbsd_permit_package_review_required=1' "$contract"
require_contains 'openbsd_make_makesum_run=0' "$contract"
require_contains 'openbsd_make_plist_run=0' "$contract"
require_contains 'openbsd_make_package_run=0' "$contract"
require_contains 'portcheck_run=0' "$contract"
require_contains 'openbsd_bulk_build_run=0' "$contract"

require_contains 'environment_identifier' "$contract"
require_contains 'operator_authorization_reference' "$contract"
require_contains 'source_archive_accepted_for_build=0' "$contract"
require_contains 'license_expression_reviewed=1' "$contract"
require_contains 'package_notice_obligations_reviewed=0' "$contract"
require_contains 'artifact_naming_contract_present=1' "$contract"
require_contains 'install_remove_transcript_contract_present=0' "$contract"
require_contains 'payload_inspection_contract_present=0' "$contract"
require_contains 'publication_non_claim_review_present=0' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package artifact naming contract' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package payload inspection contract' "$contract"
require_contains 'debian_freebsd_openbsd_package_build_environment_contract: ok' "$contract"

require_contains "$contract" "$gate_contract"
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md' "$contract"
require_contains "$contract" docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/debian/README.md
require_contains "$contract" packaging/freebsd/README.md
require_contains "$contract" packaging/openbsd/README.md
require_contains "$contract" README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md' docs/README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md' docs/status/README.md

require_contains 'debian_freebsd_openbsd_package_build_environment_contract_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'package_build_environment_contract_state=specified-no-effect' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_clean_build_environment_documented=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_build_environment_provisioned=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'explicit_operator_build_authorization=0' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_build_environment_contract_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'package_build_environment_contract_state=specified-no-effect' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_ports_environment_documented=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_build_environment_provisioned=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'explicit_operator_build_authorization=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_build_environment_contract_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'package_build_environment_contract_state=specified-no-effect' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_ports_environment_documented=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_build_environment_provisioned=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'explicit_operator_build_authorization=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_build_environment_contract_present=1' packaging/debian/README.md
require_contains 'package_build_environment_contract_state=specified-no-effect' packaging/debian/README.md
require_contains 'debian_clean_build_environment_documented=1' packaging/debian/README.md
require_contains 'debian_build_environment_provisioned=0' packaging/debian/README.md
require_contains 'explicit_operator_build_authorization=0' packaging/debian/README.md

require_contains 'debian_freebsd_openbsd_package_build_environment_contract_present=1' packaging/freebsd/README.md
require_contains 'package_build_environment_contract_state=specified-no-effect' packaging/freebsd/README.md
require_contains 'freebsd_ports_environment_documented=1' packaging/freebsd/README.md
require_contains 'freebsd_build_environment_provisioned=0' packaging/freebsd/README.md
require_contains 'explicit_operator_build_authorization=0' packaging/freebsd/README.md

require_contains 'debian_freebsd_openbsd_package_build_environment_contract_present=1' packaging/openbsd/README.md
require_contains 'package_build_environment_contract_state=specified-no-effect' packaging/openbsd/README.md
require_contains 'openbsd_ports_environment_documented=1' packaging/openbsd/README.md
require_contains 'openbsd_build_environment_provisioned=0' packaging/openbsd/README.md
require_contains 'explicit_operator_build_authorization=0' packaging/openbsd/README.md

require_contains 'Rules-Requires-Root: no' packaging/debian/debian/control
require_contains 'LICENSE=	AGPL-3.0-or-later CC-BY-4.0' packaging/freebsd/Makefile
require_contains 'PERMIT_PACKAGE=	No' packaging/openbsd/Makefile

require_absent_file packaging/freebsd/distinfo
require_absent_file packaging/openbsd/distinfo

require_contains 'Run Debian FreeBSD OpenBSD package build environment contract guard' .github/workflows/debian-freebsd-openbsd-package-build-environment-contract.yml
require_contains 'sh scripts/test-debian-freebsd-openbsd-package-build-environment-contract.sh' .github/workflows/debian-freebsd-openbsd-package-build-environment-contract.yml

printf 'debian_freebsd_openbsd_package_build_environment_contract: ok\n'

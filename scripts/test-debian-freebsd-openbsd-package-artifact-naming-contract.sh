#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'debian/freebsd/openbsd package artifact naming contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'debian/freebsd/openbsd package artifact naming contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf 'debian/freebsd/openbsd package artifact naming contract: unexpected file exists: %s\n' "$file" >&2
    exit 1
  fi
}

contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md'
environment_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_BUILD_GATE_CONTRACT.md'

require_file "$contract"
require_file "$environment_contract"
require_file "$gate_contract"
require_file docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md
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
require_file .github/workflows/debian-freebsd-openbsd-package-artifact-naming-contract.yml

require_contains 'Status: active package artifact naming contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract_present=1' "$contract"
require_contains 'debian_freebsd_openbsd_package_payload_inspection_contract_present=1' "$contract"
require_contains 'artifact_naming_contract_present=1' "$contract"
require_contains 'artifact_naming_contract_state=specified-no-effect' "$contract"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$contract"
require_contains 'package_build_gate_state=closed-no-effect' "$contract"
require_contains 'package_build_environment_contract_state=specified-no-effect' "$contract"
require_contains 'package_artifact_output_directory_required_under_disposable_environment=1' "$contract"
require_contains 'package_artifact_output_directory_created=0' "$contract"
require_contains 'repository_package_artifact_write_allowed=0' "$contract"
require_contains 'publication_directory_write_allowed=0' "$contract"
require_contains 'package_artifact_created=0' "$contract"
require_contains 'deb_artifact_created=0' "$contract"
require_contains 'debian_source_package_created=0' "$contract"
require_contains 'freebsd_package_artifact_created=0' "$contract"
require_contains 'openbsd_package_artifact_created=0' "$contract"
require_contains 'package_artifact_sha256_recorded=0' "$contract"
require_contains 'package_artifact_published=0' "$contract"
require_contains 'install_on_host_run=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'debian_source_package_name=latticra_0.0.0-1local1.dsc' "$contract"
require_contains 'debian_orig_archive_name=latticra_0.0.0.orig.tar.gz' "$contract"
require_contains 'debian_debian_tar_name=latticra_0.0.0-1local1.debian.tar.xz' "$contract"
require_contains 'debian_binary_package_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.deb' "$contract"
require_contains 'debian_changes_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.changes' "$contract"
require_contains 'debian_buildinfo_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.buildinfo' "$contract"
require_contains 'debian_artifact_name_pattern_recorded=1' "$contract"
require_contains 'dpkg_buildpackage_run=0' "$contract"
require_contains 'debuild_run=0' "$contract"
require_contains 'lintian_run=0' "$contract"

require_contains 'freebsd_package_name=latticra-0.0.0.pkg' "$contract"
require_contains 'freebsd_distfile_name=latticra-0.0.0.tar.gz' "$contract"
require_contains 'freebsd_artifact_name_pattern_recorded=1' "$contract"
require_contains 'freebsd_package_artifact_created=0' "$contract"
require_contains 'freebsd_make_stage_run=0' "$contract"
require_contains 'freebsd_make_package_run=0' "$contract"
require_contains 'portlint_run=0' "$contract"
require_contains 'poudriere_run=0' "$contract"

require_contains 'openbsd_package_name=latticra-0.0.0.tgz' "$contract"
require_contains 'openbsd_distfile_name=latticra-0.0.0.tar.gz' "$contract"
require_contains 'openbsd_artifact_name_pattern_recorded=1' "$contract"
require_contains 'openbsd_package_artifact_created=0' "$contract"
require_contains 'openbsd_make_plist_run=0' "$contract"
require_contains 'openbsd_make_package_run=0' "$contract"
require_contains 'portcheck_run=0' "$contract"
require_contains 'openbsd_bulk_build_run=0' "$contract"

require_contains 'artifact_output_root_under_disposable_environment=1' "$contract"
require_contains 'debian_artifact_output_directory=artifacts/debian/' "$contract"
require_contains 'freebsd_artifact_output_directory=artifacts/freebsd/' "$contract"
require_contains 'openbsd_artifact_output_directory=artifacts/openbsd/' "$contract"
require_contains 'root_workspace_package_artifact_write_allowed=0' "$contract"
require_contains 'artifact_retention_policy_required=1' "$contract"
require_contains 'artifact_cleanup_policy_required=1' "$contract"
require_contains 'package_artifact_sha256' "$contract"
require_contains 'operator_authorization_reference' "$contract"
require_contains 'source_archive_accepted_for_build=0' "$contract"
require_contains 'environment_transcript_present=0' "$contract"
require_contains 'payload_inspection_contract_present=1' "$contract"
require_contains 'publication_non_claim_review_present=0' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package payload inspection contract' "$contract"
require_contains 'Add a Debian, FreeBSD, and OpenBSD package install/remove transcript contract' "$contract"
require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract: ok' "$contract"

require_contains "$contract" "$environment_contract"
require_contains "$contract" "$gate_contract"
require_contains 'docs/DEBIAN_FREEBSD_OPENBSD_PACKAGE_PAYLOAD_INSPECTION_CONTRACT.md' "$contract"
require_contains "$contract" docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/debian/README.md
require_contains "$contract" packaging/freebsd/README.md
require_contains "$contract" packaging/openbsd/README.md
require_contains "$contract" README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md' docs/README.md
require_contains 'DEBIAN_FREEBSD_OPENBSD_PACKAGE_ARTIFACT_NAMING_CONTRACT.md' docs/status/README.md

require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract_present=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'artifact_naming_contract_state=specified-no-effect' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_artifact_name_pattern_recorded=1' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_source_package_name=latticra_0.0.0-1local1.dsc' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'debian_binary_package_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.deb' docs/status/DEBIAN_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract_present=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'artifact_naming_contract_state=specified-no-effect' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_artifact_name_pattern_recorded=1' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_package_name=latticra-0.0.0.pkg' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'freebsd_package_artifact_created=0' docs/status/FREEBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract_present=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'artifact_naming_contract_state=specified-no-effect' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_artifact_name_pattern_recorded=1' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_package_name=latticra-0.0.0.tgz' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'openbsd_package_artifact_created=0' docs/status/OPENBSD_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract_present=1' packaging/debian/README.md
require_contains 'artifact_naming_contract_state=specified-no-effect' packaging/debian/README.md
require_contains 'debian_artifact_name_pattern_recorded=1' packaging/debian/README.md
require_contains 'debian_source_package_name=latticra_0.0.0-1local1.dsc' packaging/debian/README.md
require_contains 'debian_binary_package_name_pattern=latticra_0.0.0-1local1_${DEB_HOST_ARCH}.deb' packaging/debian/README.md

require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract_present=1' packaging/freebsd/README.md
require_contains 'artifact_naming_contract_state=specified-no-effect' packaging/freebsd/README.md
require_contains 'freebsd_artifact_name_pattern_recorded=1' packaging/freebsd/README.md
require_contains 'freebsd_package_name=latticra-0.0.0.pkg' packaging/freebsd/README.md
require_contains 'freebsd_package_artifact_created=0' packaging/freebsd/README.md

require_contains 'debian_freebsd_openbsd_package_artifact_naming_contract_present=1' packaging/openbsd/README.md
require_contains 'artifact_naming_contract_state=specified-no-effect' packaging/openbsd/README.md
require_contains 'openbsd_artifact_name_pattern_recorded=1' packaging/openbsd/README.md
require_contains 'openbsd_package_name=latticra-0.0.0.tgz' packaging/openbsd/README.md
require_contains 'openbsd_package_artifact_created=0' packaging/openbsd/README.md

require_contains 'Rules-Requires-Root: no' packaging/debian/debian/control
require_contains 'LICENSE=	AGPL-3.0-or-later CC-BY-4.0' packaging/freebsd/Makefile
require_contains 'PERMIT_PACKAGE=	No' packaging/openbsd/Makefile

require_absent_file packaging/freebsd/distinfo
require_absent_file packaging/openbsd/distinfo

require_contains 'Run Debian FreeBSD OpenBSD package artifact naming contract guard' .github/workflows/debian-freebsd-openbsd-package-artifact-naming-contract.yml
require_contains 'sh scripts/test-debian-freebsd-openbsd-package-artifact-naming-contract.sh' .github/workflows/debian-freebsd-openbsd-package-artifact-naming-contract.yml

printf 'debian_freebsd_openbsd_package_artifact_naming_contract: ok\n'
